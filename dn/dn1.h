#ifndef DN1_H
#define DN1_H

#include <stddef.h>

void initialize_crc32_table();
unsigned long calculate_crc32(const unsigned char *data, size_t length);
void generate_uuid(char *uuid_str);

#endif 