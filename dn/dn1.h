#ifndef DN1_H
#define DN1_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Global variables
extern unsigned long crc_polynomial;
extern unsigned long crc32_table[256];

// Function declarations
void seed_the_random_number_generator();
int get_random_hex();
void initialize_crc32_table();
unsigned long calculate_crc32(const unsigned char *data, size_t length);
void generate_uuid(char *uuid_str);
void print_uuids();

#endif // DN1_H