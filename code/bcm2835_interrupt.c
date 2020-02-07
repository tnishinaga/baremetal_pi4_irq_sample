#include <stdint.h>
#include <stddef.h>

#include "bcm2835_interrupt.h"


int bcm2835_interrupt_enable(BCM2835_INTERRUPT_Type *interrupt, BCM2835_INTERRUPT_NUMBER number)
{
    if (interrupt == NULL) {
        return -1;
    }
    uint32_t regnum = number / 32;
    interrupt->ENABLE_IRQS[regnum] = 1 << (number % 32);
    return 0;
}

int bcm2835_interrupt_disable(BCM2835_INTERRUPT_Type *interrupt, BCM2835_INTERRUPT_NUMBER number)
{
    if (interrupt == NULL) {
        return -1;
    }
    uint32_t regnum = number / 32;
    interrupt->DISABLE_IRQS[regnum] = 1 << (number % 32);
    return 0;
}

int bcm2835_interrupt_basic_disable_all(BCM2835_INTERRUPT_Type *interrupt)
{
    if (interrupt == NULL) {
        return -1;
    }
    interrupt->DISABLE_BASIC_IRQS = 0xffffffff;
    return 0;
}

int bcm2835_interrupt_disable_all(BCM2835_INTERRUPT_Type *interrupt)
{
    if (interrupt == NULL) {
        return -1;
    }
    interrupt->DISABLE_IRQS[0] = 0xffffffff;
    interrupt->DISABLE_IRQS[1] = 0xffffffff;
    return 0;
}

BCM2835_INTERRUPT_NUMBER bcm2835_pending_interrupt(BCM2835_INTERRUPT_Type *interrupt)
{
    uint64_t irq_pending = interrupt->IRQ_PENDING[1];
    irq_pending <<= 32;
    irq_pending |= interrupt->IRQ_PENDING[0];
    
    switch (irq_pending) {
        case ((uint64_t)1 << AUX_INT):
            return AUX_INT;
        case ((uint64_t)1 << I2C_SPI_SLV_INT):
            return I2C_SPI_SLV_INT;
        case ((uint64_t)1 << PWA0):
            return PWA0;
        case ((uint64_t)1 << PWA1):
            return PWA1;
        case ((uint64_t)1 << SMI):
            return SMI;
        case ((uint64_t)1 << GPIO_INT_0):
            return GPIO_INT_0;
        case ((uint64_t)1 << GPIO_INT_1):
            return GPIO_INT_1;
        case ((uint64_t)1 << GPIO_INT_2):
            return GPIO_INT_2;
        case ((uint64_t)1 << GPIO_INT_3):
            return GPIO_INT_3;
        case ((uint64_t)1 << I2C_INT):
            return I2C_INT;
        case ((uint64_t)1 << SPI_INT):
            return SPI_INT;
        case ((uint64_t)1 << PCM_INT):
            return PCM_INT;
        case ((uint64_t)1 << UART_INT):
            return UART_INT;
        default:
            break;
    }
    return NOT_BCM2835_INTERRUPT_NUMBER;
}