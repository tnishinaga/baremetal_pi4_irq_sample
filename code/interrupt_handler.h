#pragma once

#ifndef __ASSEMBLER__
    // variables
    extern uintptr_t vector_table_el2;

    // inline functions
    static inline void set_vbar_el2(uintptr_t *address)
    {
        __asm ("msr VBAR_EL2, %[addr]" : :[addr] "r" (address) :);
    }

    static inline uintptr_t* get_vbar_el2(void)
    {
        uintptr_t *address;
        __asm ("mrs %[addr], VBAR_EL2" : [addr] "=r" (address) ::);
        return address;
    }

    extern inline void set_vbar_el2(uintptr_t *address);
    extern inline uintptr_t* get_vbar_el2(void);
#endif