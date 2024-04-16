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

void startProgram(char *buffer1, char *buffer2, char *buffer3, char *buffer4, char *buffer5, 
                FILE *curl_output1, FILE *curl_output2, FILE *curl_output3,
                 FILE *curl_output4, FILE *curl_output5) {
    long long start_time, end_time;
    double execution_time;

    start_time = timeInMilliseconds();

    //tworzenie deploymentu
    FILE *fp = popen("kubectl apply -f quarkusDeployment8090.yml", "r");
    pclose(fp);

    fp = popen("kubectl apply -f quarkusDeployment8091.yml", "r");
    pclose(fp);

    fp = popen("kubectl apply -f quarkusDeployment8092.yml", "r");
    pclose(fp);

    fp = popen("kubectl apply -f quarkusDeployment8093.yml", "r");
    pclose(fp);

    fp = popen("kubectl apply -f quarkusDeployment8094.yml", "r");
    pclose(fp);
    //koniec tworzenie deploymentu

    // fp = popen("kubectl wait --for=condition=Ready pods --all ", "r");
    // pclose(fp);

    do {
        curl_output1 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://127.0.0.1:8090/currency/currencyExchangeValue", "r");
        fgets(buffer1, BUFFER_SIZE, curl_output1);

        curl_output2 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://127.0.0.1:8091/currency/currencyExchangeValue", "r");
        fgets(buffer2, BUFFER_SIZE, curl_output2);

        curl_output3 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://127.0.0.1:8092/currency/currencyExchangeValue", "r");
        fgets(buffer3, BUFFER_SIZE, curl_output3);

        curl_output4 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://127.0.0.1:8093/currency/currencyExchangeValue", "r");
        fgets(buffer4, BUFFER_SIZE, curl_output4);

        curl_output5 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://127.0.0.1:8094/currency/currencyExchangeValue", "r");
        fgets(buffer5, BUFFER_SIZE, curl_output5);

    } while(!containsExchangeValue(buffer1) && 
    !containsExchangeValue(buffer2) && 
    !containsExchangeValue(buffer3) && 
    !containsExchangeValue(buffer4) && 
    !containsExchangeValue(buffer5));

    pclose(curl_output1);
    pclose(curl_output2);
    pclose(curl_output3);
    pclose(curl_output4);
    pclose(curl_output5);

    memset(buffer1, 0, sizeof(buffer1));
    memset(buffer1, 0, sizeof(buffer2));
    memset(buffer1, 0, sizeof(buffer3));
    memset(buffer1, 0, sizeof(buffer4));
    memset(buffer1, 0, sizeof(buffer5));

    end_time = timeInMilliseconds();
    execution_time = (double)(end_time - start_time) / 1000; 
    printf("Czas wykonania: %.4f sekund.\n", execution_time);

    writeToFile(execution_time);

    fp = popen("kubectl delete -n default deployment nbp-app8090", "r");
    pclose(fp);

    fp = popen("kubectl delete -n default deployment nbp-app8091", "r");
    pclose(fp);

    fp = popen("kubectl delete -n default deployment nbp-app8092", "r");
    pclose(fp);

    fp = popen("kubectl delete -n default deployment nbp-app8093", "r");
    pclose(fp);

    fp = popen("kubectl delete -n default deployment nbp-app8094", "r");
    pclose(fp);
}

int main() {

    char buffer1[BUFFER_SIZE];
    FILE *curl_output1;

    char buffer2[BUFFER_SIZE];
    FILE *curl_output2;

    char buffer3[BUFFER_SIZE];
    FILE *curl_output3;

    char buffer4[BUFFER_SIZE];
    FILE *curl_output4;

    char buffer5[BUFFER_SIZE];
    FILE *curl_output5;

    for(int i = 0; i < 1; i++) {
        startProgram(buffer1, buffer2, buffer3, buffer4, buffer5, 
        curl_output1, curl_output2, curl_output3, curl_output4, curl_output5);
        sleep(2);
    }

    return 0;
}

    // if (fp == NULL) {
    //     printf("Błąd podczas uruchamiania polecenia.\n");
    //     return 1;
    // }