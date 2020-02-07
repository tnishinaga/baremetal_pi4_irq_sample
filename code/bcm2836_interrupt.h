#pragma once

#ifndef __ASSEMBLER__
    #include <stdint.h>
    #include <stdbool.h>
    
    typedef struct {
        volatile uint32_t CONTROL;
        volatile uint32_t UNUSED0;
        volatile uint32_t CORE_TIME_PRESCALER;
        volatile uint32_t GPU_INTERRUPT_ROUTING;
        volatile uint32_t PM_INTERRUPT_ROUTING_SET;
        volatile uint32_t PM_INTERRUPT_ROUTING_CLR;
        volatile uint32_t UNUSED1;
        volatile uint32_t CORE_TIMER_ACCESS_LS;
        volatile uint32_t CORE_TIMER_ACCESS_MS;
        volatile uint32_t LOCAL_INTERRUPT0;
        volatile uint32_t LOCAL_INTERRUPT1_UNUSED;
        volatile uint32_t AXI_OUTSTANDING_COUNTERS;
        volatile uint32_t AXI_OUTSTANDING_IRQ;
        volatile uint32_t LOCAL_TIMER_CONTROL_STATUS;
        volatile uint32_t LOCAL_TIMER_WRITE_FLAGS;
        volatile uint32_t UNUSED2;
        volatile uint32_t CORE_TIMERS_INTERRUPT_CONTROL[4];
        volatile uint32_t CORE_MAILBOXES_INTERRUPT_CONTROL[4];
        volatile uint32_t CORE_IRQ_SOURCE[4];
        volatile uint32_t CORE_FIQ_SOURCE[4];
        volatile uint32_t CORE_MAILBOX_WRITE_SET[4][4];
        volatile uint32_t CORE_MAILBOX_READ_AND_WRITE_HIGH_TO_CLEAR[4][4];
    } BCM2836_INTERRUPT_Type;
#endif
