#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "my_stdio.h"
#include "raspi_peripheral.h"

void current_el_sp0_sync_el2_handler(void)
{
    my_puts("enter current_el_sp0_sync_el2_handler\n");
}

void current_el_sp0_irq_el2_handler(void)
{
    my_puts("enter current_el_sp0_irq_el2_handler\n");
}
void current_el_sp0_fiq_el2_handler(void)
{
    my_puts("enter current_el_sp0_fiq_el2_handler\n");
}
void current_el_sp0_serror_el2_handler(void)
{
    my_puts("enter current_el_sp0_serror_el2_handler\n");
}
void current_el_spx_sync_el2_handler(void)
{
    my_puts("enter current_el_spx_sync_el2_handler\n");
}
void current_el_spx_irq_el2_handler(void)
{
#ifdef TARGET_RASPI_3
    // check reason of irq
    BCM2835_INTERRUPT_NUMBER pending = bcm2835_pending_interrupt(BCM2835_INTERRUPT);
    if (pending == UART_INT) {
        // echo back reveice charactor
        if (UART0->MIS & PL011_INTERRUPT_RECEIVE) {
            while(pl011_is_busy(UART0) == true);
            while(pl011_is_fifo_rx_empty(UART0) == false) {
                uint8_t c = 0;
                pl011_read(UART0, &c, 1);
                pl011_write(UART0, &c, 1);
            }
        }
        // clear interrupt flag
        UART0->ICR = PL011_INTERRUPT_RECEIVE;
    } else {
        my_puts("another irq pending\n");
    }
#elif defined (TARGET_RASPI_4)
    #warning "RASPI4 not supported"
    uint32_t iar = GIC_V2.C->GICC_IAR & 0x0fff;
    uint32_t cpu_id = iar >> 10;
    uint32_t interrupt_id = iar & 0x3ff;

    if (interrupt_id == (121 + 32)) {
        // uart0 interrupt
        // echo back reveice charactor
        if (UART0->MIS & PL011_INTERRUPT_RECEIVE) {
            while(pl011_is_busy(UART0) == true);
            while(pl011_is_fifo_rx_empty(UART0) == false) {
                uint8_t c = 0;
                pl011_read(UART0, &c, 1);
                pl011_write(UART0, &c, 1);
            }
        }
        // clear interrupt flag
        UART0->ICR = PL011_INTERRUPT_RECEIVE;
    } else {
        my_puts("another irq pending\n");
    }

    // finish
    GIC_V2.C->GICC_EOIR = iar;
#endif
}
void current_el_spx_fiq_el2_handler(void)
{
    my_puts("enter current_el_spx_fiq_el2_handler\n");
}
void current_el_spx_serror_el2_handler(void)
{
    my_puts("enter current_el_spx_serror_el2_handler\n");
}