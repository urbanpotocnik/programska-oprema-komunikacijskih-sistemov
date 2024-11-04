#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long crc_polynomial = 0xEDB88320;
unsigned long crc32_table[256];    

// Function to seed the random number generator
void seed_the_random_number_generator() 
{
    srand(time(0));
}

int get_random_hex() 
{
    return rand() % 16;
}

// Initializing the crc32 table
void initialize_crc32_table() 
{
    for (unsigned long i = 0; i < 256; i++) {
        unsigned long crc = i;
        for (unsigned long j = 8; j > 0; j--) {
            if (crc & 1) {
                crc = (crc >> 1) ^ crc_polynomial;
            } else {
                crc >>= 1;
            }
        }
        crc32_table[i] = crc;
    }
}

// Calculate crc32 for an array
unsigned long calculate_crc32(int *data) 
{
    unsigned long crc = 0xFFFFFFFF; 
    for (int i = 0; i < 32; i++) 
    {
        int byte = data[i];
        crc = (crc >> 8) ^ crc32_table[(crc ^ byte) & 0xFF];
    }
    return ~crc; 
}


void generate_uuid() 
{
    int uuid[32];
    for (int i = 0; i < 32; i++) {
        uuid[i] = get_random_hex(); 
    }

    for (int i = 0; i < 32; i++) {
        if (i == 8 || i == 12 || i == 16 || i == 20) {
            printf("-");
        }
        printf("%x", uuid[i]);
    }

    unsigned long crc = calculate_crc32(uuid);
    printf(" %08lx\n", crc & 0xFFFFFFFF); 
}

void print_uuids() 
{
    seed_the_random_number_generator();
    initialize_crc32_table(); 

    for (int i = 1; i <= 100; i++) {
        printf("%08d-", i);
        generate_uuid(i);
    }
}

int main() 
{
    print_uuids(); 
    return 0;
}
