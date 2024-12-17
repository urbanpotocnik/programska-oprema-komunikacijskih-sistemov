#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <uuid/uuid.h>

#define PORT 5069
#define BUFFER_SIZE 1024

void initialize_crc32_table();
unsigned long calculate_crc32(const unsigned char *data, size_t length);
void generate_uuid(char *uuid_str);

unsigned long crc_polynomial = 0xEDB88320;
unsigned long crc32_table[256];

void initialize_crc32_table() {
    for (unsigned long i = 0; i < 256; i++) {
        unsigned long crc = i;
        for (unsigned long j = 0; j < 8; j++) {
            if (crc & 1)
                crc = (crc >> 1) ^ crc_polynomial;
            else
                crc >>= 1;
        }
        crc32_table[i] = crc;
    }
}

unsigned long calculate_crc32(const unsigned char *data, size_t length) {
    unsigned long crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        unsigned char byte = data[i];
        crc = (crc >> 8) ^ crc32_table[(crc ^ byte) & 0xFF];
    }
    return ~crc;
}

void generate_uuid(char *uuid_str) {
    uuid_t binuuid;
    uuid_generate(binuuid);
    uuid_unparse_lower(binuuid, uuid_str);
}

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_addr;
    char message[BUFFER_SIZE];
    char server_reply[BUFFER_SIZE];
    socklen_t server_len;
    int n;

    initialize_crc32_table();

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        printf("Neuspešno ustvarjanje socket-a\n");
        return 1;
    }
    printf("UDP Socket ustvarjen.\n");

    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_aton("127.0.0.1", &server_addr.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    server_len = sizeof(server_addr);

    while (1) {
        printf("Vnesi sporočilo (ali 'exit' za izhod): ");
        if (fgets(message, sizeof(message), stdin) == NULL) {
            printf("Napaka pri branju vhoda.\n");
            break;
        }

        message[strcspn(message, "\n")] = '\0';

        if (strcmp(message, "exit") == 0) {
            break;
        }

        n = sendto(sock, message, strlen(message), 0, (struct sockaddr *)&server_addr, server_len);
        if (n < 0) {
            printf("Pošiljanje neuspešno\n");
            continue;
        }
        printf("Poslano: %s\n", message);

        n = recvfrom(sock, server_reply, BUFFER_SIZE - 1, 0, NULL, NULL);
        if (n < 0) {
            printf("Prejemanje neuspešno\n");
            continue;
        }
        server_reply[n] = '\0';
        printf("Prejeto: %s\n", server_reply);
    }

    close(sock);
    return 0;
}