/* main.c - Cortex-M4 test X25519 */

#include "x25519-cortex-m4.h"

void output_hex(const unsigned char *data, int len) {
    for (int i = 0; i < len; i++) {
        // 例如：uart_send_hex(data[i]);
    }
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

    output_hex(my_public_key, 32);
    output_hex(shared_secret, 32);

    // 裸機程式通常不會退出，因此進入無窮迴圈
    while(1) {
        // 可在此加入進一步的處理或睡眠
    }

    return 0;
}
