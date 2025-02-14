#ifndef STM32F4XX_H
#define STM32F4XX_H

#include <stdint.h>

// 簡單定義 GPIO 結構（僅定義我們用到的部分）
typedef struct {
    volatile uint32_t MODER;    // 模式設定
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];     // AFR[0] for pins 0..7, AFR[1] for pins 8..15
} GPIO_TypeDef;

// 簡單定義 USART 結構（僅定義我們用到的部分）
typedef struct {
    volatile uint32_t SR;    // 狀態暫存器
    volatile uint32_t DR;    // 資料暫存器
    volatile uint32_t BRR;   // 波特率暫存器
    volatile uint32_t CR1;   // 控制暫存器1
    volatile uint32_t CR2;   // 控制暫存器2
    volatile uint32_t CR3;   // 控制暫存器3
    volatile uint32_t GTPR;  // 逾時預分頻暫存器
} USART_TypeDef;

// 簡單定義 RCC 結構（僅定義我們用到的部分）
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    // 之後的成員在此範例中不需要
} RCC_TypeDef;

// 定義外設基底位址（以 STM32F407 為例）
#define RCC                 ((RCC_TypeDef *)0x40023800)
#define GPIOA               ((GPIO_TypeDef *)0x40020000)
#define USART2              ((USART_TypeDef *)0x40004400)

// 定義需要用到的位元旗標
#define RCC_AHB1ENR_GPIOAEN   (1U << 0)
#define RCC_APB1ENR_USART2EN  (1U << 17)

#define USART_CR1_TE        (1U << 3)
#define USART_CR1_UE        (1U << 13)
#define USART_SR_TXE        (1U << 7)

#endif // STM32F4XX_H
