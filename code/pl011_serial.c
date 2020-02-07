#include "pl011_serial.h"
#include <stdbool.h>

void pl011_uart_disable(PL011_UART_Type *uart)
{
    // Clear UART setting
    uart->CR = 0;

    // disable FIFO
    uart->LCRH = 0;
}

void pl011_baudrate_setup(PL011_UART_Type *uart, uint64_t uart_clock, uint64_t baudrate)
{
    // set baudrate
    uint32_t bauddiv = (1000 * uart_clock) / (16 * baudrate);
    uint32_t ibrd = bauddiv / 1000;
    uint32_t fbrd = ((bauddiv - ibrd * 1000) * 64 + 500) / 1000;
    uart->IBRD = ibrd;
    uart->FBRD = fbrd;
}

void pl011_uart_enable(PL011_UART_Type *uart, uint64_t uart_clock, uint64_t baudrate)
{
    pl011_uart_disable(uart);
    pl011_baudrate_setup(uart, uart_clock, baudrate);
    // 8bit, FIFO
    uart->LCRH = PL011_LCRH_WLEN_8;
    // uart enable, TX/RX enable
    uart->CR = PL011_CR_UARTEN | PL011_CR_TXE | PL011_CR_RXE;
}

int pl011_write(PL011_UART_Type *uart, uint8_t *buf, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++) {
        while (pl011_is_fifo_tx_full(uart));
        uart->DR = (uint8_t)buf[i];
    }
    return i;
}

int pl011_read(PL011_UART_Type *uart, uint8_t *buf, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++) {
        while (pl011_is_fifo_rx_empty(uart));
        buf[i] = (uint8_t)uart->DR;
    }
    return i;
}

int pl011_receive_interrupt_enable(PL011_UART_Type *uart)
{
    uart->IMSC |= PL011_IMSC_RXIM;
    return 0;
}

int pl011_receive_interrupt_disable(PL011_UART_Type *uart)
{
    uart->IMSC &= ~((uint32_t)PL011_IMSC_RXIM);
    return 0;
}

// TODO: add interrupt clear function