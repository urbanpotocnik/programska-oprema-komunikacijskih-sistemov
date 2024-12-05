#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include "common.h"
#include <unistd.h>

#define STOP_STR "MMMMM\0"

int main()
{
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];
    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MSGS;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    sleep(5);
    while(1)
    {
        ssize_t bytes_read;
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL); /* receive message */
        printf("%s\n", buffer);
        int timer;

        /*
        if(buffer[1] != MSG_STOP[1])
        {
            timer++;
        }

        if (timer == 3)
        {
            printf("Blocked \n");
            sleep(10);
            break;
        }
        */

        mq_getattr(mq, &attr);
        printf("Atributi: mq_flags: %ld, mq_curmsgs: %ld\n", attr.mq_flags, attr.mq_curmsgs);

        if(buffer[1] == MSG_STOP[1])
        {
            printf("Receiver ended \n");
            break;
        }
    }
    mq_close(mq); /* cleanup */
    mq_unlink(QUEUE_NAME);
    return 0;
}