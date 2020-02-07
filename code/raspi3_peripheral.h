#pragma once


#include "gpio.h"
#include "pl011_serial.h"
#include "bcm2835_interrupt.h"
#include "bcm2836_interrupt.h"

#if 1
    // share with .S files
    #define PERI_BASE 0x3F000000
    #define GPIO_BASE (PERI_BASE + 0x00200000)
    #define UART0_BASE (PERI_BASE + 0x00201000)
    #define BCM2835_INTERRUPT_BASE  (PERI_BASE + 0x0000B000 + 0x200)

    #define BCM2836_INTERRUPT_BASE 0x40000000
    #define UART_REFERENCE_CLOCK 48000000
#endif


#ifndef __ASSEMBLER__
    // only C sources
    extern GPIO_Type *GPIO;
    extern PL011_UART_Type *UART0;
    extern BCM2835_INTERRUPT_Type *BCM2835_INTERRUPT;
    extern BCM2836_INTERRUPT_Type *BCM2836_INTERRUPT;
#endif