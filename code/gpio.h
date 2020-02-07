#pragma once

#ifndef __ASSEMBLER__
    #include <stdint.h>
    #include <stdbool.h>

    typedef volatile struct {
        volatile uint32_t GPFSEL[6];
        volatile uint32_t REV0;
        volatile uint32_t GPSET[2];
        volatile uint32_t REV1;
        volatile uint32_t GPCLR[2];
        volatile uint32_t REV2;
        volatile uint32_t GPLEV[2];
        volatile uint32_t REV3;
        volatile uint32_t GPEDS[2];
        volatile uint32_t REV4;
        volatile uint32_t GPREN[2];
        volatile uint32_t REV5;
        volatile uint32_t GPFEN[2];
        volatile uint32_t REV6;
        volatile uint32_t GPHEN[2];
        volatile uint32_t REV7;
        volatile uint32_t GPLEN[2];
        volatile uint32_t REV8;
        volatile uint32_t GPAREN[2];
        volatile uint32_t REV9;
        volatile uint32_t GPAFEN[2];
        volatile uint32_t REV10;
        volatile uint32_t GPPUD;
        volatile uint32_t GPPUDCLK[2];
        volatile uint32_t REV11;
        volatile uint32_t TEST;
    }  __attribute__ ((packed)) __attribute__ ((aligned (4))) GPIO_Type;

    typedef enum {
        INPUT = 0b000,
        OUTPUT = 0b001,
        ALT0 = 0b100,
        ALT1 = 0b101,
        ALT2 = 0b110,
        ALT3 = 0b111,
        ALT4 = 0b011,
        ALT5 = 0b010
    } GPIO_FUNC;

    // functions
    extern int gpio_mode(GPIO_Type *gpio, uint32_t port, GPIO_FUNC func);
    extern int gpio_output(GPIO_Type *gpio, uint32_t port, bool out);
#endif