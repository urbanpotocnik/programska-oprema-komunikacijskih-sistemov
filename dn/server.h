#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>

void *connection_handler(void *socket_desc);
void error(const char *msg);
void sanitize_input(char *input);

extern unsigned int serial_number;
extern pthread_mutex_t serial_mutex;

#endif 