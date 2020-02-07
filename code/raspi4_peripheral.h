#pragma once

#include "gpio.h"
#include "pl011_serial.h"
#include "gicv2.h"

#if 1
    // share with .S files
    #define PERI_BASE 0xFE000000
    #define GPIO_BASE (PERI_BASE + 0x00200000)
    #define UART0_BASE (PERI_BASE + 0x00201000)

    #define INTC_BASE   0xff800000
    #define GIC_V2_DISTRIBUTOR_BASE     (INTC_BASE + 0x00041000)
    #define GIC_V2_CPU_INTERFACE_BASE   (INTC_BASE + 0x00042000)
    #define GIC_V2_HYPERVISOR_BASE      (INTC_BASE + 0x00044000)
    #define GIC_V2_VIRTUAL_CPU_BASE     (INTC_BASE + 0x00046000)

    #define UART_REFERENCE_CLOCK 48000000
#endif


#ifndef __ASSEMBLER__
    // only C sources
    extern GPIO_Type *GPIO;
    extern PL011_UART_Type *UART0;
    extern GIC_V2_Type GIC_V2;
#endif