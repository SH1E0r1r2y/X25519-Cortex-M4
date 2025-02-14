
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "x25519-cortex-m4.h"

// USART2 initial（ TX = PA2）
void USART2_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    GPIOA->MODER &= ~(3UL << (2 * 2));
    GPIOA->MODER |= (2UL << (2 * 2));
    GPIOA->AFR[0] &= ~(0xF << (2 * 4));
    GPIOA->AFR[0] |= (7UL << (2 * 4));

    USART2->BRR = 139;
    USART2->CR1 = USART_CR1_TE;
    USART2->CR1 |= USART_CR1_UE;
}

void USART2_SendChar(char c) {
    while (!(USART2->SR & USART_SR_TXE));
    USART2->DR = c;
}

void USART2_SendString(const char *str) {
    while (*str) {
        USART2_SendChar(*str++);
    }
}

void USART2_SendHexByte(uint8_t byte) {
    const char hex_digits[] = "0123456789ABCDEF";
    USART2_SendChar(hex_digits[byte >> 4]);
    USART2_SendChar(hex_digits[byte & 0x0F]);
}

void USART2_SendHex(const uint8_t *data, int len) {
    for (int i = 0; i < len; i++) {
        USART2_SendHexByte(data[i]);
        USART2_SendChar(' ');
    }
    USART2_SendChar('\n');
}

int main(void) {
    USART2_Init();

    uint8_t secret_key_alice[32] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20
    };

    uint8_t secret_key_bob[32] = {
        0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
        0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
        0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
        0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40
    };

    uint8_t public_key_alice[32];
    uint8_t public_key_bob[32];
    uint8_t shared_secret_alice[32];
    uint8_t shared_secret_bob[32];

    X25519_calc_public_key(public_key_alice, secret_key_alice);
    X25519_calc_public_key(public_key_bob, secret_key_bob);

    X25519_calc_shared_secret(shared_secret_alice, secret_key_alice, public_key_bob);
    X25519_calc_shared_secret(shared_secret_bob, secret_key_bob, public_key_alice);

    int equal = memcmp(shared_secret_alice, shared_secret_bob, 32) == 0;

    if (equal) {
        USART2_SendString("SUCCESS: Both Bob and Alice computed the same shared secret\n");
    } else {
        USART2_SendString("FAILED: Shared secrets do not match\n");
    }

    USART2_SendString("Shared Secret: ");
    USART2_SendHex(shared_secret_alice, 32);

    while (1) {
    }
    return 0;
}
