#include "raspi_peripheral.h"

#ifdef TARGET_RASPI_3

// gpio
GPIO_Type *GPIO = (GPIO_Type *)GPIO_BASE;
// uart
PL011_UART_Type *UART0 = (PL011_UART_Type *)UART0_BASE;
// bcm2835 interrupt
BCM2835_INTERRUPT_Type *BCM2835_INTERRUPT = (BCM2835_INTERRUPT_Type *)BCM2835_INTERRUPT_BASE;
// bcm2836 interrupt
BCM2836_INTERRUPT_Type *BCM2836_INTERRUPT = (BCM2836_INTERRUPT_Type *)BCM2836_INTERRUPT_BASE;

#endif