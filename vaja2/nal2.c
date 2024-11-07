#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Start moj PID = %d\n", getpid());

    int PIDotroka = fork();
    
    if(PIDotroka != 0)
    {
        printf("PID starsa = %d\n", getpid());
    } else {
        printf("PID otroka = %d\n", getpid());
    }
    return 0;
}
