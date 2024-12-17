#include "dn1.h"

// Global variables
unsigned long crc_polynomial = 0xEDB88320;
unsigned long crc32_table[256];    

// Function to seed the random number generator
void seed_the_random_number_generator() 
{
    srand(time(0));
}

// Function to get a random hex digit (0-15)
int get_random_hex() 
{
    return rand() % 16;
}

// Initialize the CRC32 table
void initialize_crc32_table() 
{
    for (unsigned long i = 0; i < 256; i++) {
        unsigned long crc = i;
        for (unsigned long j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ crc_polynomial;
            } else {
                crc >>= 1;
            }
        }
        crc32_table[i] = crc;
    }
}

// Calculate CRC32 for a data buffer
unsigned long calculate_crc32(const unsigned char *data, size_t length) 
{
    unsigned long crc = 0xFFFFFFFF; 
    for (size_t i = 0; i < length; i++) 
    {
        unsigned char byte = data[i];
        crc = (crc >> 8) ^ crc32_table[(crc ^ byte) & 0xFF];
    }
    return ~crc; 
}

// Generate a UUID string in the format xxxxxxxx-xxxx-Mxxx-Nxxx-xxxxxxxxxxxx
void generate_uuid(char *uuid_str) 
{
    const char *hex_chars = "0123456789abcdef";
    
    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            uuid_str[i] = '-';
        } else if (i == 14) { // Fix the 'M' position to specify UUID version 4
            uuid_str[i] = '4';
        } else if (i == 19) { // Fix the 'N' position to specify UUID variant
            uuid_str[i] = hex_chars[(rand() % 4) + 8];
        } else {
            uuid_str[i] = hex_chars[get_random_hex()];
        }
    }
    uuid_str[36] = '\0';
}

// Optional: Function to print 100 UUIDs (not used in dn2.c)
void print_uuids() 
{
    seed_the_random_number_generator();
    initialize_crc32_table(); 

    for (int i = 1; i <= 100; i++) {
        printf("%08d-", i);
        char uuid[37];
        generate_uuid(uuid);
        printf("%s\n", uuid);
    }
}