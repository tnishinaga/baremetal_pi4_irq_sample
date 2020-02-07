#pragma once

#ifndef __ASSEMBLER__
    #include <stdint.h>
    #include <stdbool.h>

    typedef volatile struct {
        volatile uint32_t IRQ_BASIC_PENDING;
        volatile uint32_t IRQ_PENDING[2];
        volatile uint32_t FIQ_CONTROL;
        volatile uint32_t ENABLE_IRQS[2];
        volatile uint32_t ENABLE_BASIC_IRQS;
        volatile uint32_t DISABLE_IRQS[2];
        volatile uint32_t DISABLE_BASIC_IRQS;
    } __attribute__ ((packed)) __attribute__ ((aligned (4))) BCM2835_INTERRUPT_Type;

    typedef enum {
        AUX_INT = 29,
        I2C_SPI_SLV_INT = 43,
        PWA0 = 45,
        PWA1 = 46,
        SMI = 48,
        GPIO_INT_0 = 49,
        GPIO_INT_1 = 50,
        GPIO_INT_2 = 51,
        GPIO_INT_3 = 52,
        I2C_INT = 53,
        SPI_INT = 54,
        PCM_INT = 55,
        UART_INT = 57,
        NOT_BCM2835_INTERRUPT_NUMBER = -1
    } BCM2835_INTERRUPT_NUMBER;

    extern int bcm2835_interrupt_enable(BCM2835_INTERRUPT_Type *interrupt, BCM2835_INTERRUPT_NUMBER number);
    extern int bcm2835_interrupt_disable(BCM2835_INTERRUPT_Type *interrupt, BCM2835_INTERRUPT_NUMBER number);
    extern int bcm2835_interrupt_basic_disable_all(BCM2835_INTERRUPT_Type *interrupt);
    extern int bcm2835_interrupt_disable_all(BCM2835_INTERRUPT_Type *interrupt);
    extern BCM2835_INTERRUPT_NUMBER bcm2835_pending_interrupt(BCM2835_INTERRUPT_Type *interrupt);
#endif