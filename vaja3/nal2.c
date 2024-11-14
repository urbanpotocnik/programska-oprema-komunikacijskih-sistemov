#include <stdio.h>
#include <pthread.h>

void *sum1();
void *sum2();
void *sum3();

struct arg_struct
{
    int arg1;
    int arg2;
};

int main()
{
    pthread_t nit1, nit2, nit3;
    struct arg_struct args1, args2, args3;

    args1.arg1 = 10;
    args1.arg2 = 20;
    args2.arg1 = 40;
    args2.arg2 = 20;
    args3.arg1 = 30;
    args3.arg2 = 10;

    int R = 0;
    int ab = 0;
    int cd = 0;
    int ef = 0;

    pthread_create(&nit1, NULL, &sum1, (void*)&args1);
    pthread_create(&nit2, NULL, &sum2, (void*)&args2);
    pthread_create(&nit3, NULL, &sum3, (void*)&args3);

    pthread_join(nit1, (void **)&ab);
    pthread_join(nit2, (void **)&cd);
    pthread_join(nit3, (void **)&ef);

    R = ab * cd * ef;
    printf("Rezultat je: %d\n", R);
    
    return 0;
}

void *sum1(void *arguments)
{
    pthread_t nit1 = pthread_self();
    struct arg_struct *args = arguments;
    int ab = (args -> arg1) + (args -> arg2);
    printf("Nit ID = %lu\n", nit1);
    //pthread_exit((void*)ab);
    return 0;
}

void *sum2(void *arguments)
{
    pthread_t nit2 = pthread_self();
    struct arg_struct *args = arguments;
    int cd = (args -> arg1) - (args -> arg2);
    printf("Nit ID = %lu\n", nit2);
    //pthread_exit((void*)cd);
    return 0;
}

void *sum3(void *arguments)
{
    pthread_t nit3 = pthread_self();
    struct arg_struct *args = arguments;
    int ef = (args -> arg1) + (args -> arg2);
    printf("Nit ID = %lu\n", nit3);
    //pthread_exit((void*)ef);
    return 0;
}
