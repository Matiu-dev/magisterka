#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

#define BUFFER_SIZE 128

int containsExchangeValue(const char *buffer) {
    return strstr(buffer, "3.93") != NULL; 
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

    FILE *fp = popen("nomad job run -hcl1 nbpAppQuarkus.nomad.hcl", "r");
    if (fp == NULL) {
        printf("Błąd podczas uruchamiania polecenia.\n");
        return 1;
    }
    pclose(fp);

    char buffer[BUFFER_SIZE];
    FILE *curl_output;

    do {
        curl_output = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://localhost:8080/currency/currencyExchangeValue", "r");
        if (curl_output == NULL) {
            printf("Błąd podczas wykonania zapytania.\n");
            return 1;
        }
        
        fgets(buffer, BUFFER_SIZE, curl_output);
        pclose(curl_output);

    } while(!containsExchangeValue(buffer));

    memset(buffer, 0, sizeof(buffer));

    end_time = timeInMilliseconds();
    execution_time = (double)(end_time - start_time) / 1000; 
    printf("Czas wykonania: %.4f sekund.\n", execution_time);

    writeToFile(execution_time);

    fp = popen("nomad job stop -purge nbpapp", "r");
    if (fp == NULL) {
        printf("Błąd podczas uruchamiania polecenia.\n");
        return 1;
    }
    pclose(fp);
}

int main() {

    for(int i = 0; i < 1; i++) {
        startProgram();
        sleep(2);
    }

    return 0;
}