#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int otrok = fork();
    
    if(otrok == 0)
    {
        printf("Otrok PID = %d, spi 5 sekund...\n", getpid());
        sleep(5);
        printf("Otrok PID = %d, se koncuje\n", getpid());
        exit(0);
    } else {
        printf("Stars PID = %d se nadaljuje\n", getpid());
        sleep(10);
        printf("Stars PID = %d se koncuje\n", getpid());
    }
    return 0;
}