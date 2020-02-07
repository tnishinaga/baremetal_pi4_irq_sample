#pragma once

// register's bit
#define PL011_FR_RI          (1 << 8)
#define PL011_FR_TXFE        (1 << 7)
#define PL011_FR_RXFF        (1 << 6)
#define PL011_FR_TXFF        (1 << 5)
#define PL011_FR_RXFE        (1 << 4)
#define PL011_FR_BUSY        (1 << 3)
#define PL011_FR_DCD         (1 << 2)
#define PL011_FR_DSR         (1 << 1)
#define PL011_FR_CTS         (1 << 0)

#define PL011_LCRH_SPS       (1 << 7)
#define PL011_LCRH_WLEN_8    (3 << 5)
#define PL011_LCRH_WLEN_7    (2 << 5)
#define PL011_LCRH_WLEN_6    (1 << 5)
#define PL011_LCRH_WLEN_5    (0 << 5)
#define PL011_LCRH_FEN       (1 << 4)
#define PL011_LCRH_STP2      (1 << 3)
#define PL011_LCRH_EPS       (1 << 2)
#define PL011_LCRH_PEN       (1 << 1)
#define PL011_LCRH_BRK       (1 << 0)

#define PL011_CR_CTSEN       (1 << 15)
#define PL011_CR_RTSEN       (1 << 14)
#define PL011_CR_RTS         (1 << 11)
#define PL011_CR_DTR         (1 << 10)
#define PL011_CR_RXE         (1 << 9)
#define PL011_CR_TXE         (1 << 8)
#define PL011_CR_LBE         (1 << 7)
#define PL011_CR_SIRLP       (1 << 2)
#define PL011_CR_SIREN       (1 << 1)
#define PL011_CR_UARTEN      (1 << 0)

#define PL011_IMSC_TXIM      (1 << 5)
#define PL011_IMSC_RXIM      (1 << 4)


#define PL011_INTERRUPT_OVERRUN_ERROR   (1 << 10)
#define PL011_INTERRUPT_BREAK_ERROR     (1 << 9)
#define PL011_INTERRUPT_PARITY_ERROR    (1 << 8)
#define PL011_INTERRUPT_FRAMING_ERROR   (1 << 7)
#define PL011_INTERRUPT_RECEIVE_TIMEOUT (1 << 6)
#define PL011_INTERRUPT_TRANSMIT        (1 << 5)
#define PL011_INTERRUPT_RECEIVE         (1 << 4)
#define PL011_INTERRUPT_nUARTCTS        (1 << 1)

#ifndef __ASSEMBLER__
    #include <stdint.h>
    #include <stddef.h>
    #include <stdbool.h>

    typedef volatile struct {
        volatile uint32_t DR; // 0x00
        volatile uint32_t RSRECR; // 0x04
        volatile uint8_t RESERVED0[0x18 - 0x08];
        volatile uint32_t FR; // 0x18
        volatile uint8_t RESERVED1[0x20 - 0x1c];
        volatile uint32_t ILPR; // 0x20
        volatile uint32_t IBRD; // 0x24
        volatile uint32_t FBRD; // 0x28
        volatile uint32_t LCRH; // 0x2c
        volatile uint32_t CR; // 0x30
        volatile uint32_t IFLS; // 0x34
        volatile uint32_t IMSC; // 0x38
        volatile uint32_t RIS; // 0x3c
        volatile uint32_t MIS; // 0x40
        volatile uint32_t ICR; // 0x44
        volatile uint32_t DMACR; // 0x48
        volatile uint8_t RESERVED2[0x80 - 0x4c];
        volatile uint32_t ITCR; // 0x80
        volatile uint32_t ITIP; // 0x84
        volatile uint32_t ITOP; // 0x88
        volatile uint32_t TDR; // 0x8c   
    } __attribute__ ((packed)) __attribute__ ((aligned (4))) PL011_UART_Type;

    // inline functions
    static inline bool pl011_is_fifo_tx_empty(PL011_UART_Type *uart)
    {
        if ((uart->FR & PL011_FR_TXFE) != 0) {
            return true;
        }
        return false;
    }

    static inline bool pl011_is_fifo_rx_empty(PL011_UART_Type *uart)
    {
        if ((uart->FR & PL011_FR_RXFE) != 0) {
            return true;
        }
        return false;
    }

    static inline bool pl011_is_fifo_tx_full(PL011_UART_Type *uart)
    {
        if ((uart->FR & PL011_FR_TXFF) != 0) {
            return true;
        }
        return false;
    }

    static inline bool pl011_is_fifo_rx_full(PL011_UART_Type *uart)
    {
        if ((uart->FR & PL011_FR_RXFF) != 0) {
            return true;
        }
        return false;
    }

    static inline bool pl011_is_busy(PL011_UART_Type *uart)
    {
        if ((uart->FR & PL011_FR_BUSY) != 0) {
            return true;
        }
        return false;
    }

    void pl011_uart_enable(PL011_UART_Type *uart, uint64_t uart_clock, uint64_t baudrate);
    void pl011_uart_disable(PL011_UART_Type *uart);
    int pl011_write(PL011_UART_Type *uart, uint8_t *buf, size_t size);
    int pl011_read(PL011_UART_Type *uart, uint8_t *buf, size_t size);
    int pl011_receive_interrupt_enable(PL011_UART_Type *uart);
    int pl011_receive_interrupt_disable(PL011_UART_Type *uart);
    
    // inline function
    extern inline bool pl011_is_fifo_tx_empty(PL011_UART_Type *uart);
    extern inline bool pl011_is_fifo_rx_empty(PL011_UART_Type *uart);
    extern inline bool pl011_is_fifo_tx_full(PL011_UART_Type *uart);
    extern inline bool pl011_is_fifo_rx_full(PL011_UART_Type *uart);
    extern inline bool pl011_is_busy(PL011_UART_Type *uart);

    typedef struct {
        bool OVERRUN_ERROR;
        bool BREAK_ERROR;
        bool PARITY_ERROR;
        bool FRAMING_ERROR;
        bool RECEIVE_TIMEOUT;
        bool TRANSMIT;
        bool RECEIVE;
        bool nUARTCTS;
    } PL011_INTERRUPT_MASK_CONFIG;
#endif