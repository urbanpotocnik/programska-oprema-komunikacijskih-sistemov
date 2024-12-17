#include "server.h"
#include "dn1.h"  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 5069
#define BUFFER_SIZE 1024

unsigned int serial_number = 1;
pthread_mutex_t serial_mutex = PTHREAD_MUTEX_INITIALIZER;

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void sanitize_input(char *input) {
    char *start = input;
    char *end = input + strlen(input) - 1;
    while (*start == ' ' || *start == '\t' || *start == '\n') start++;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n')) end--;
    if (*start == '"' && *end == '"') {
        start++;
        end--;
    }
    *(end + 1) = '\0';
}

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[BUFFER_SIZE];
    int n;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        error("Could not create socket");
    }
    printf("UDP Socket created.\n");

    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        close(sock);
        error("Bind failed");
    }
    printf("Bind successful. Listening on port %d...\n", PORT);

    initialize_crc32_table();

    while (1) {
        client_len = sizeof(client_addr);
        memset(buffer, 0, BUFFER_SIZE);
        n = recvfrom(sock, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *)&client_addr, &client_len);
        if (n < 0) {
            error("recvfrom failed");
        }
        buffer[n] = '\0';
        sanitize_input(buffer);
        printf("Received message: '%s'\n", buffer);

        if (strcmp(buffer, "GET") == 0) {
            pthread_mutex_lock(&serial_mutex);

            char uuid_str[37];
            generate_uuid(uuid_str);

            char combined[100];
            snprintf(combined, sizeof(combined), "%08u-%s", serial_number, uuid_str);
            unsigned long crc = calculate_crc32((unsigned char *)combined, strlen(combined));
            char response[128];
            snprintf(response, sizeof(response), "%s %08lx", combined, crc & 0xFFFFFFFF);

            n = sendto(sock, response, strlen(response), 0, (struct sockaddr *)&client_addr, client_len);
            if (n < 0) {
                pthread_mutex_unlock(&serial_mutex);
                error("sendto failed");
            }
            printf("Sent: %s\n", response);

            serial_number++;

            pthread_mutex_unlock(&serial_mutex);
        }
        else {
            char unknown_command_response[] = "NEPREPOZNAVEN UKAZ";
            n = sendto(sock, unknown_command_response, strlen(unknown_command_response), 0, (struct sockaddr *)&client_addr, client_len);
            if (n < 0) {
                error("sendto failed");
            }
            printf("Sent: %s\n", unknown_command_response);
        }
    }

    close(sock);
    return 0;
}