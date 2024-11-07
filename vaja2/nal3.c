#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Start moj PID = %d\n", getpid());
    int otrok = 0;
    otrok = fork();
    if(otrok != 0)
    {
        otrok = fork();
        if(otrok)
        {
            otrok = fork();
        }
    }

    printf("Konec moj PID = %d\nmoj PPID = %d\nin otrok %d\n", getpid(), getppid(), otrok);
    sleep(1);

    return 0;
}