#include <stdio.h>
#include <stdlib.h>

int main() {
    int bruto;
    printf("Vnesi bruto dohodek studentskega dela: \n");
    scanf("%d", &bruto);

    double neto = bruto * 0.78; 
    printf("Neto dohodek je %.2f \n", neto);

    int dohodninskiRazred = 0;

    if (neto < 8500) {
        dohodninskiRazred = 1;
    } else if (neto >= 8500 && neto < 25000) {
        dohodninskiRazred = 2;
    } else if (neto >= 25000 && neto < 50000) {
        dohodninskiRazred = 3;
    } else if (neto >= 50000 && neto < 72000) {
        dohodninskiRazred = 4;
    } else if (neto >= 72000) {
        dohodninskiRazred = 5;
    }

    switch (dohodninskiRazred) {
        case 1: {
            double dohodnina1 = neto * 0.16;
            printf("Dohodnina je %.2f! \n", dohodnina1);
            double razlika1 = 8500 - neto;
            printf("Razlika do naslednjega razreda je = %.2f \n", razlika1);
            break;
        }
        case 2: {
            double dohodnina2 = neto * 0.16;
            printf("Dohodnina je %.2f! \n", dohodnina2);
            double razlika2 = 25000 - neto;
            printf("Razlika do naslednjega razreda je = %.2f \n", razlika2);
            break;
        }
        case 3: {
            double dohodnina3 = (neto - 25000) * 0.33 + 5650;
            printf("Dohodnina je %.2f! \n", dohodnina3);
            double razlika3 = 50000 - neto;
            printf("Razlika do naslednjega razreda je = %.2f \n", razlika3);
            break;
        }
        case 4: {
            double dohodnina4 = (neto - 50000) * 0.39 + 13900;
            printf("Dohodnina je %.2f! \n", dohodnina4);
            double razlika4 = 72000 - neto;
            printf("Razlika do naslednjega razreda je = %.2f \n", razlika4);
            break;
        }
        case 5: {
            double dohodnina5 = (neto - 72000) * 0.50 + 22480;
            printf("Dohodnina je %.2f! \n", dohodnina5);
            break;
        }
        default:
            printf("Napaka pri izračunu! \n");
            break;
    }

    return 0;
}
