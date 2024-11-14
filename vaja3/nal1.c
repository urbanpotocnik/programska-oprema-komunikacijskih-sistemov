#include <stdio.h>
#include <pthread.h>

void *sum1();
void *sum2();
void *sum3();

int a = 10;
int b = 15;
int c = 21;
int d = 20;
int e = 40;
int f = 5;

int ab = 0;
int cd = 0;
int ef = 0;

int main()
{
    pthread_t nit1, nit2, nit3;
    int R = 0;

    pthread_create(&nit1, NULL, &sum1, NULL);
    pthread_create(&nit2, NULL, &sum2, NULL);
    pthread_create(&nit3, NULL, &sum3, NULL);

    pthread_join(nit1, NULL);
    pthread_join(nit2, NULL);
    pthread_join(nit3, NULL);

    R = ab * cd * ef;
    printf("Rezultat je: %d\n", R);

    return 0;
}

void *sum1()
{
    pthread_t nit1 = pthread_self();
    ab = a + b;
    printf("ID niti = %lu in rezultat je %d\n", nit1, ab);
}

void *sum2()
{
    pthread_t nit2 = pthread_self();
    cd = c - d;
    printf("ID niti = %lu in rezultat je %d\n", nit2, cd);
}

void *sum3()
{
    pthread_t nit3 = pthread_self();
    ef = e + f;
    printf("ID niti = %lu in rezultat je %d\n", nit3, ef);
}