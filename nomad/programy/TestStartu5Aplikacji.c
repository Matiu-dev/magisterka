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

    FILE *fp1 = popen("nomad job run -hcl1 nbpAppQuarkus8090.nomad.hcl", "r");
    pclose(fp1);

    FILE *fp2 = popen("nomad job run -hcl1 nbpAppQuarkus8091.nomad.hcl", "r");
    pclose(fp2);

    FILE *fp3 = popen("nomad job run -hcl1 nbpAppQuarkus8092.nomad.hcl", "r");
    pclose(fp3);

    FILE *fp4 = popen("nomad job run -hcl1 nbpAppQuarkus8093.nomad.hcl", "r");
    pclose(fp4);

    FILE *fp5 = popen("nomad job run -hcl1 nbpAppQuarkus8094.nomad.hcl", "r");
    pclose(fp5);

    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    char buffer3[BUFFER_SIZE];
    char buffer4[BUFFER_SIZE];
    char buffer5[BUFFER_SIZE];

    FILE *curl_output1;
    FILE *curl_output2;
    FILE *curl_output3;
    FILE *curl_output4;
    FILE *curl_output5;

    do {
        curl_output1 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://localhost:8090/currency/currencyExchangeValue", "r");
        curl_output2 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://localhost:8091/currency/currencyExchangeValue", "r");
        curl_output3 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://localhost:8092/currency/currencyExchangeValue", "r");
        curl_output4 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://localhost:8093/currency/currencyExchangeValue", "r");
        curl_output5 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://localhost:8094/currency/currencyExchangeValue", "r");
        
        fgets(buffer1, BUFFER_SIZE, curl_output1);
        pclose(curl_output1);

        fgets(buffer2, BUFFER_SIZE, curl_output2);
        pclose(curl_output2);

        fgets(buffer3, BUFFER_SIZE, curl_output3);
        pclose(curl_output3);

        fgets(buffer4, BUFFER_SIZE, curl_output4);
        pclose(curl_output4);

        fgets(buffer5, BUFFER_SIZE, curl_output5);
        pclose(curl_output5);
        

    } while(!containsExchangeValue(buffer1) &&
    !containsExchangeValue(buffer2) &&
    !containsExchangeValue(buffer3) &&
    !containsExchangeValue(buffer4) &&
    !containsExchangeValue(buffer5) );

    memset(buffer1, 0, sizeof(buffer1));
    memset(buffer2, 0, sizeof(buffer1));
    memset(buffer3, 0, sizeof(buffer1));
    memset(buffer4, 0, sizeof(buffer1));
    memset(buffer5, 0, sizeof(buffer1));

    end_time = timeInMilliseconds();
    execution_time = (double)(end_time - start_time) / 1000; 
    printf("Czas wykonania: %.4f sekund.\n", execution_time);

    writeToFile(execution_time);

    fp1 = popen("nomad job stop -purge nbpapp8090", "r");
    pclose(fp1);

    fp2 = popen("nomad job stop -purge nbpapp8091", "r");
    pclose(fp2);

    fp3 = popen("nomad job stop -purge nbpapp8092", "r");
    pclose(fp3);

    fp4 = popen("nomad job stop -purge nbpapp8093", "r");
    pclose(fp4);

    fp5 = popen("nomad job stop -purge nbpapp8094", "r");
    pclose(fp5);
}

int main() {

    for(int i = 0; i < 50; i++) {
        startProgram();
        sleep(2);
    }

    return 0;
}

    // if (fp == NULL) {
    //     printf("Błąd podczas uruchamiania polecenia.\n");
    //     return 1;
    // }

            // if (curl_output == NULL) {
        //     printf("Błąd podczas wykonania zapytania.\n");
        //     return 1;
        // }