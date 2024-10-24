#include <stdio.h>

int main()
{
    char ime[50];
    char primek[50];
    int starost;
    
    printf("Prosim, napiši svoje ime (do 49 znakov): ");
    scanf("%s", ime);  
    printf("Prosim, napiši svoj priimek (do 49 znakov): ");
    scanf("%s", primek);  
    printf("Prosim, vnesi svojo starost: ");
    scanf("%d", &starost);

    printf("Tvoje ime je %s,\npriimek %s,\nstarost pa %d.\n", ime, primek, starost);

    return 0;
}
