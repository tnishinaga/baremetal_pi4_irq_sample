#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "raspi_peripheral.h"
#include "my_stdio.h"
#include "interrupt_handler.h"
#include "armv8_misc.h"

void show_current_el(void)
{
    volatile int64_t el = current_el();
    char num[] = "0";
    num[0] += el;
    my_puts("Current EL");
    my_puts(num);
    my_puts("\n");
}

void hexprint32(uint32_t value)
{
    const char *hextable = "0123456789abcdef";
    char buffer[10];
    for (int8_t i = 7; 0 <= i; i--) {
        buffer[i] = hextable[value & 0x0f];
        value >>= 4;
    }
    buffer[8] = '\n';
    buffer[9] = '\0';
    my_puts(buffer);
}

void hexprint64(uint64_t value)
{
    const char *hextable = "0123456789abcdef";
    char buffer[18];
    for (int8_t i = 15; 0 <= i; i--) {
        buffer[i] = hextable[value & 0x0f];
        value >>= 4;
    }
    buffer[16] = '\n';
    buffer[17] = '\0';
    my_puts(buffer);
}

#ifdef TARGET_RASPI_3
void setup_interrupt_controller(void)
{
    // disable all irq source
    my_puts("bcm2835_interrupt_basic_disable_all\n");
    bcm2835_interrupt_basic_disable_all(BCM2835_INTERRUPT);
    my_puts("bcm2835_interrupt_disable_all\n");
    bcm2835_interrupt_disable_all(BCM2835_INTERRUPT);
    __asm ("isb");
    __asm ("dsb sy");

    // enable serial interrupt
    my_puts(" bcm2835_interrupt_enable\n");
    bcm2835_interrupt_enable(BCM2835_INTERRUPT, UART_INT);
    my_puts("pl011_receive_interrupt_enable\n");
    pl011_receive_interrupt_enable(UART0);
    // setup core interrupt routing
    my_puts("set GPU_INTERRUPT_ROUTING to Core0\n");
    BCM2836_INTERRUPT->GPU_INTERRUPT_ROUTING = 0;
}
#elif defined(TARGET_RASPI_4)
void setup_interrupt_controller()
{
    // disable distribute
    GIC_V2.D->GICD_CTLR = 0;

    // number of implemented GICD_ISENABLER
    uint32_t IT_LINES_NUMBER = GIC_V2.D->GICD_TYPER;
    IT_LINES_NUMBER &= GICD_TYPER_IT_LINES_NUMBER_MASK;
    uint32_t max_interrupt_id = (IT_LINES_NUMBER + 1) * 32;

    uint32_t uart0_id = 121 + 32;

    // enable uart0 interrupt
    GIC_V2.D->GICD_ISENABLER[uart0_id / 32] |= 1 << (uart0_id % 32);

    // set uart0 priority to highest(lower numbers have higher priority)
    uint32_t priority_mask = ~((uint32_t)0xff << ((uart0_id % 4) * 8));
    GIC_V2.D->GICD_IPRIORITYR[uart0_id / 4] &= priority_mask;

    // set uart0 target processor to 0
    uint32_t target_processor = 0;
    uint32_t itargetsr_shift = ((uart0_id % 4) * 8);
    uint32_t itargetsr_tmp = GIC_V2.D->GICD_ITARGETSR[uart0_id / 4];
    itargetsr_tmp &= ~((uint32_t)0xff << itargetsr_shift);
    itargetsr_tmp |= ((uint32_t)0x01 << target_processor) << itargetsr_shift;
    GIC_V2.D->GICD_ITARGETSR[uart0_id / 4] = itargetsr_tmp;

    // enable CPU interface
    GIC_V2.C->GICC_CTLR = GICC_CTLR_NON_SECURE_ENABLE_GRP1;

    // enable distribute
    GIC_V2.D->GICD_CTLR = GICD_CTLR_NON_SECURE_ENABLE;
}
#endif


int main(void)
{
    // setup vector table EL2
    set_vbar_el2(&vector_table_el2);
    __asm ("isb");

    // set GPIO14 to ALT0(TXD0)
    // set GPIO15 to ALT0(RXD0)
    gpio_mode(GPIO, 14, ALT0);
    gpio_mode(GPIO, 15, ALT0);
    
    pl011_uart_enable(UART0, UART_REFERENCE_CLOCK, 115200);

    // setup interrupt controller
    setup_interrupt_controller();

    my_puts("pl011_receive_interrupt_enable\n");
    pl011_receive_interrupt_enable(UART0);

    // route irq to EL2
    uint64_t hcl_el2 = read_hcr_el2();
    hcl_el2 |= (1 << 4);
    write_hcr_el2(hcl_el2);
    __asm ("isb");
    __asm ("dsb sy");

    // enable irq
    enable_irq();

    my_puts("Start LED Blink and echo\n");

    gpio_mode(GPIO, 17, OUTPUT);
    while (1) {
        // set GPIO17 to HIGH
        gpio_output(GPIO, 17, true);
        // loop delay
        for (volatile uint32_t i = 0; i < 1000000; i++);
        // GPIO17 to LOW
        gpio_output(GPIO, 17, false);
        // // loop delay
        for (volatile uint32_t i = 0; i < 1000000; i++);
    }

    return 0;
}