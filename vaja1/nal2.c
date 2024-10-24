#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    printf("Ugani stevilo med 1 in 100\n");
    srand(time(NULL));
    int stevilo = rand() % 100 + 1; 
    int u;
    int poizkusi = 3;

    do {
        printf("Vnesi stevilo: ");
        scanf("%d", &u);

        if (u == stevilo) {
            printf("Zmaga!\n");
            return 0;  
        } 
        else if (u < stevilo) {
            printf("Stevilo je vecje!\n");
        } 
        else {
            printf("Stevilo je manjse!\n");
        }
        poizkusi--;
    } while (poizkusi > 0);

    printf("Nisi uganil stevila, stevilo je %d\n", stevilo);
    return 0;
}
