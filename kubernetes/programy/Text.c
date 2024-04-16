#include <stdio.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *fp;
    char buffer[BUFFER_SIZE];

    // Uruchomienie polecenia i odczytanie pierwszej linii
    fp = popen("minikube service nbp-app --url", "r");
    if (fp == NULL) {
        printf("Błąd podczas uruchamiania polecenia.\n");
        return 1;
    }

    // Odczytanie pierwszej linii z wyniku polecenia
    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        printf("Błąd odczytu pierwszej linii z wyniku polecenia.\n");
        pclose(fp);
        return 1;
    }

    // Zamknięcie potoku
    pclose(fp);

    // Wyświetlenie pierwszej linii
    printf("Pierwsza linia: %s\n", buffer);

    return 0;
}
