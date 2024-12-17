#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include "dn1.h"  

void error(const char *msg) {
    perror(msg);
    exit(1);
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

    memmove(input, start, end - start + 2); 
}

int main() {
    int sock, length, n;
    struct sockaddr_in server, from;
    socklen_t fromlen;
    char buf[1024];
    int port = 5069;  
    int sequence_number = 1;  

    seed_the_random_number_generator();
    initialize_crc32_table();

    sock = socket(AF_INET, SOCK_DGRAM, 0); 
    if (sock < 0) error("Opening socket");

    length = sizeof(server);
    bzero((char *) &server, length);
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);  

    if (bind(sock, (struct sockaddr *)&server, length) < 0) 
        error("binding");

    fromlen = sizeof(struct sockaddr_in);

    while (1) {
        n = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)&from, &fromlen);
        if (n < 0) error("recvfrom");

        buf[n] = '\0';  
        sanitize_input(buf);  

        printf("Received message: '%s'\n", buf); 

        if (strcmp(buf, "GET") == 0) {
            char uuid[37];
            generate_uuid(uuid);  

            char response[128];
            char combined[100];
            snprintf(combined, sizeof(combined), "%08d-%s", sequence_number, uuid);
            unsigned long crc = calculate_crc32((unsigned char *)combined, strlen(combined));
            snprintf(response, sizeof(response), "%08d-%s %08lx", sequence_number, uuid, crc & 0xFFFFFFFF);

            printf("Sent: %s\n", response);
            n = sendto(sock, response, strlen(response), 0, (struct sockaddr *)&from, fromlen);
            if (n < 0) error("sendto");

            sequence_number++;  
        } 
        else if (strncmp(buf, "PREJETO ", 8) == 0) {
            char text[1024];
            unsigned long received_crc;
            int scanned = sscanf(buf + 8, "%s %lx", text, &received_crc);

            if (scanned != 2) {
                char unknown_command_response[] = "NEPREPOZNAVEN UKAZ";
                printf("Sent: %s\n", unknown_command_response);
                n = sendto(sock, unknown_command_response, strlen(unknown_command_response), 0, (struct sockaddr *)&from, fromlen);
                if (n < 0) error("sendto");
                continue;
            }

            unsigned long calculated_crc = calculate_crc32((unsigned char *)text, strlen(text));
            if (calculated_crc == received_crc) {
                sequence_number++;  
                printf("CRC32 is correct. Sequence number increased.\n");
            } else {
                char error_response[] = "NAPAKA 4900B4DB";
                printf("Sent: %s\n", error_response);
                n = sendto(sock, error_response, strlen(error_response), 0, (struct sockaddr *)&from, fromlen);
                if (n < 0) error("sendto");
            }
        } 
        else {
            char unknown_command_response[] = "NEPREPOZNAVEN UKAZ";
            printf("Sent: %s\n", unknown_command_response);
            n = sendto(sock, unknown_command_response, strlen(unknown_command_response), 0, (struct sockaddr *)&from, fromlen);
            if (n < 0) error("sendto");
        }
    }

    close(sock);
    return 0;
}