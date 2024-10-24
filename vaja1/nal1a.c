#include <stdio.h>
#include <string.h>

int main() {
    char ime[20];
    char primek[20];

    printf("Prosim vnesi svoje ime: ");
    fgets(ime, sizeof(ime), stdin);
    ime[strcspn(ime, "\n")] = '\0'; 
    
    printf("Prosim vnesi svoj priimek: ");
    fgets(primek, sizeof(primek), stdin);
    primek[strcspn(primek, "\n")] = '\0'; 

    printf("Tvoje ime je %s in tvoj priimek je %s\n", ime, primek);

    return 0;
}
