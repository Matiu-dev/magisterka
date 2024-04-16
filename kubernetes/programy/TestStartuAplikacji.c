#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

#define BUFFER_SIZE 128

int containsExchangeValue(const char *buffer) {
    return strstr(buffer, "3.94") != NULL; 
}

long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

void writeToFile(double execution_time) {
    FILE *file = fopen("wyniki.txt", "a");
    if (file == NULL) {
        printf("Błąd podczas otwierania pliku.\n");
        return;
    }

    fprintf(file, "%.4f\n", execution_time);
    fclose(file);
}

void startProgram() {
    long long start_time, end_time;
    double execution_time;

    start_time = timeInMilliseconds();

    //tworzenie deploymentu
    FILE *fp = popen("kubectl apply -f quarkusDeployment.yml", "r");
    pclose(fp);

    // fp = popen("kubectl wait --for=condition=Ready pods --all ", "r");
    // pclose(fp);


    char buffer[BUFFER_SIZE];
    FILE *curl_output;

    do {
        curl_output = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://127.0.0.1:8080/currency/currencyExchangeValue", "r");
        // if (curl_output == NULL) {
        //     printf("Błąd podczas wykonania zapytania.\n");
        //     return 1;
        // }
        
        fgets(buffer, BUFFER_SIZE, curl_output);

    } while(!containsExchangeValue(buffer));

    pclose(curl_output);

    memset(buffer, 0, sizeof(buffer));

    end_time = timeInMilliseconds();
    execution_time = (double)(end_time - start_time) / 1000; 
    printf("Czas wykonania: %.4f sekund.\n", execution_time);

    writeToFile(execution_time);

    fp = popen("kubectl delete -n default deployment nbp-app", "r");
    pclose(fp);

    // fp = popen("kubectl delete -n default service nbp-app", "r");
    // pclose(fp);
}

int main() {

    for(int i = 0; i < 1; i++) {
        startProgram();
        sleep(2);
    }

    return 0;
}

    // if (fp == NULL) {
    //     printf("Błąd podczas uruchamiania polecenia.\n");
    //     return 1;
    // }