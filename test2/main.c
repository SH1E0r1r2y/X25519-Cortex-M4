

#include "x25519-cortex-m4.h"

static inline void semihosting_putchar(char ch) {
    register int r0 asm("r0") = 0x03;  // SYS_WRITEC
    register char r1 asm("r1") = ch;
    asm volatile ("bkpt 0xAB" : : "r" (r0), "r" (r1));
}

void semihosting_puts(const char *s) {
    while(*s) {
        semihosting_putchar(*s++);
    }
}

char nibble_to_hex(unsigned int nibble) {
    if(nibble < 10)
        return '0' + nibble;
    else
        return 'A' + (nibble - 10);
}


void output_hex_byte(unsigned char byte) {
    semihosting_putchar(nibble_to_hex((byte >> 4) & 0xF));
    semihosting_putchar(nibble_to_hex(byte & 0xF));
    semihosting_putchar(' ');
}

void output_hex(const unsigned char *data, int len) {
    for (int i = 0; i < len; i++) {
        output_hex_byte(data[i]);
    }
    semihosting_putchar('\n');
}

int main(void) {
    unsigned char my_secret_key[32] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20
    };

    unsigned char my_public_key[32];
    X25519_calc_public_key(my_public_key, my_secret_key);

    unsigned char shared_secret[32];
    X25519_calc_shared_secret(shared_secret, my_secret_key, my_public_key);

    semihosting_puts("Public Key:\n");
    output_hex(my_public_key, 32);

    semihosting_puts("Shared Secret:\n");
    output_hex(shared_secret, 32);


    return 0;
}
