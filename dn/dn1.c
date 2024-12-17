#include "dn1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>

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