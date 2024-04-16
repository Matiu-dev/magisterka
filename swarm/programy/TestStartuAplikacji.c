#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>

#define BUFFER_SIZE 128

int containsExchangeValue(const char *buffer) {
    return strstr(buffer, "3.95") != NULL; 
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

void startProgram(char *buffer1, char *buffer2, char *buffer3, 
                char *buffer4, char *buffer5, 
                FILE *curl_output1, FILE *curl_output2, FILE *curl_output3,
                FILE *curl_output4, FILE *curl_output5) {

    long long start_time, end_time;
    double execution_time;

    start_time = timeInMilliseconds();

    //tworzenie deploymentu
    FILE *fp = popen("docker service create --name NBP-APP8090 -p 8090:8090 --network=NBP-APP matiuw/nbp-app8090:latest", "r");
    pclose(fp);

    fp = popen("docker service create --name NBP-APP8091 -p 8091:8091 --network=NBP-APP matiuw/nbp-app8091:latest", "r");
    pclose(fp);

    fp = popen("docker service create --name NBP-APP8092 -p 8092:8092 --network=NBP-APP matiuw/nbp-app8092:latest", "r");
    pclose(fp);

    fp = popen("docker service create --name NBP-APP8093 -p 8093:8093 --network=NBP-APP matiuw/nbp-app8093:latest", "r");
    pclose(fp);

    fp = popen("docker service create --name NBP-APP8094 -p 8094:8094 --network=NBP-APP matiuw/nbp-app8094:latest", "r");
    pclose(fp);

    // fp = popen("kubectl wait --for=condition=Ready pods --all ", "r");
    // pclose(fp);


    do {
        curl_output1 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://localhost:8090/currency/currencyExchangeValue", "r");
        curl_output2 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://localhost:8091/currency/currencyExchangeValue", "r");
        curl_output3 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://localhost:8092/currency/currencyExchangeValue", "r");
        curl_output4 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://localhost:8093/currency/currencyExchangeValue", "r");
        curl_output5 = popen("curl -X GET -H \"Content-Type: application/json\" -d '{\"amount\": 1, \"myCurrency\": \"USD\", \"targetCurrency\": \"PLN\"}' http://localhost:8094/currency/currencyExchangeValue", "r");
        // if (curl_output == NULL) {
        //     printf("Błąd podczas wykonania zapytania.\n");
        //     return 1;
        // }
        
        fgets(buffer1, BUFFER_SIZE, curl_output1);
        fgets(buffer2, BUFFER_SIZE, curl_output2);
        fgets(buffer3, BUFFER_SIZE, curl_output3);
        fgets(buffer4, BUFFER_SIZE, curl_output4);
        fgets(buffer5, BUFFER_SIZE, curl_output5);

    } while(!containsExchangeValue(buffer1) &&
    !containsExchangeValue(buffer2) &&
    !containsExchangeValue(buffer3) &&
    !containsExchangeValue(buffer4) &&
    !containsExchangeValue(buffer5) );

    pclose(curl_output1);
    pclose(curl_output2);
    pclose(curl_output3);
    pclose(curl_output4);
    pclose(curl_output5);

    memset(buffer1, 0, sizeof(buffer1));
    memset(buffer2, 0, sizeof(buffer2));
    memset(buffer3, 0, sizeof(buffer3));
    memset(buffer4, 0, sizeof(buffer4));
    memset(buffer5, 0, sizeof(buffer5));

    end_time = timeInMilliseconds();
    execution_time = (double)(end_time - start_time) / 1000; 
    printf("Czas wykonania: %.4f sekund.\n", execution_time);

    writeToFile(execution_time);

    fp = popen("docker service rm NBP-APP8090", "r");
    pclose(fp);
    
    fp = popen("docker service rm NBP-APP8091", "r");
    pclose(fp);

    fp = popen("docker service rm NBP-APP8092", "r");
    pclose(fp);

    fp = popen("docker service rm NBP-APP8093", "r");
    pclose(fp);

    fp = popen("docker service rm NBP-APP8094", "r");
    pclose(fp);


    // fp = popen("kubectl delete -n default service nbp-app", "r");
    // pclose(fp);
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
        sleep(15);
    }

    return 0;
}

    // if (fp == NULL) {
    //     printf("Błąd podczas uruchamiania polecenia.\n");
    //     return 1;
    // }