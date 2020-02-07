#pragma once

#ifndef __ASSEMBLER__
    #include <stdint.h>
    #include <stdbool.h>

    static inline uint32_t read_daif(void)
    {
        volatile uint32_t daif;
        __asm ("mrs %[result], DAIF" : [result] "=r" (daif) : :);
        return daif;
    }

    static inline uint64_t read_hcr_el2(void)
    {
        volatile uint32_t hcr_el2;
        __asm ("mrs %[result], HCR_EL2" : [result] "=r" (hcr_el2) : :);
        return hcr_el2;
    }

    static inline void write_hcr_el2(uint64_t hcr_el2)
    {
        __asm ("msr HCR_EL2, %[reg]" : : [reg] "r" (hcr_el2) :);
    }

    static inline int64_t current_el(void)
    {
        volatile int64_t el;
        __asm ("mrs %[result], CurrentEL" : [result] "=r" (el) : :);
        return (el >> 2) & 0x03;
    }

    static inline void enable_irq(void)
    {
        __asm ("msr DAIFClr, #0x02");
    }

    static inline void disable_irq(void)
    {
        __asm ("msr DAIFSet, #0x02");
    }


    extern inline uint32_t read_daif(void);
    extern inline uint64_t read_hcr_el2(void);
    extern inline void write_hcr_el2(uint64_t hcr_el2);
    extern inline int64_t current_el(void);
    extern inline void enable_irq(void);
    extern inline void disable_irq(void);
#endif