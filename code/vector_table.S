.macro infinit_loop label
    wfe
    b \label
.endm

.macro backup_register
    stp x0, x1, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x20, x21, [sp, #-16]!
    stp x22, x23, [sp, #-16]!
    stp x24, x25, [sp, #-16]!
    stp x26, x27, [sp, #-16]!
    stp x28, x29, [sp, #-16]!
    stp x30, xzr, [sp, #-16]!
.endm

.macro restore_register
    ldp x30, xzr, [sp], #16
    ldp x28, x29, [sp], #16
    ldp x26, x27, [sp], #16
    ldp x24, x25, [sp], #16
    ldp x22, x23, [sp], #16
    ldp x20, x21, [sp], #16
    ldp x18, x19, [sp], #16
    ldp x16, x17, [sp], #16
    ldp x14, x15, [sp], #16
    ldp x12, x13, [sp], #16
    ldp x10, x11, [sp], #16
    ldp x8, x9, [sp], #16
    ldp x6, x7, [sp], #16
    ldp x4, x5, [sp], #16
    ldp x2, x3, [sp], #16
    ldp x0, x1, [sp], #16
.endm


.balign 0x800
.global vector_table_el2
vector_table_el2:

// Current EL with SP0
current_el_sp0_sync_el2:
    b asm_current_el_sp0_sync_el2_handler
.balign 0x80
current_el_sp0_irq_el2:
    b asm_current_el_sp0_irq_el2_handler
.balign 0x80
current_el_sp0_fiq_el2:
    b asm_current_el_sp0_fiq_el2_handler
.balign 0x80
current_el_sp0_serror_el2:
    b asm_current_el_sp0_serror_el2_handler
.balign 0x80


// Current EL with SPx
current_el_spx_sync_el2:
    b asm_current_el_spx_sync_el2_handler
.balign 0x80
current_el_spx_irq_el2:
    b asm_current_el_spx_irq_el2_handler
.balign 0x80
current_el_spx_fiq_el2:
    b asm_current_el_spx_fiq_el2_handler
.balign 0x80
current_el_spx_serror_el2:
    b asm_current_el_spx_serror_el2_handler
.balign 0x80

// Lower EL using AArch64
lower_el_aarch64_sync_el2:
    infinit_loop lower_el_aarch64_sync_el2
.balign 0x80
lower_el_aarch64_irq_el2:
    infinit_loop lower_el_aarch64_irq_el2
.balign 0x80
lower_el_aarch64_fiq_el2:
    infinit_loop lower_el_aarch64_fiq_el2
.balign 0x80
lower_el_aarch64_serror_el2:
    infinit_loop lower_el_aarch64_serror_el2
.balign 0x80

// Lower EL using AArch32
lower_el_aarch32_sync_el2:
    infinit_loop lower_el_aarch32_sync_el2
.balign 0x80
lower_el_aarch32_irq_el2:
    infinit_loop lower_el_aarch32_irq_el2
.balign 0x80
lower_el_aarch32_fiq_el2:
    infinit_loop lower_el_aarch32_fiq_el2
.balign 0x80
lower_el_aarch32_serror_el2:
    infinit_loop lower_el_aarch32_serror_el2
.balign 0x80



asm_current_el_sp0_sync_el2_handler:
    backup_register
    bl current_el_sp0_sync_el2_handler
    restore_register
    eret
asm_current_el_sp0_irq_el2_handler:
    backup_register
    bl current_el_sp0_irq_el2_handler
    restore_register
    msr DAIFClr, #2
    eret
asm_current_el_sp0_fiq_el2_handler:
    backup_register
    bl current_el_sp0_fiq_el2_handler
    restore_register
    msr DAIFClr, #1
    eret
asm_current_el_sp0_serror_el2_handler:
    backup_register
    bl current_el_sp0_serror_el2_handler
    restore_register
    msr DAIFClr, #4
    eret


asm_current_el_spx_sync_el2_handler:
    backup_register
    bl current_el_spx_sync_el2_handler
    restore_register
    eret
asm_current_el_spx_irq_el2_handler:
    backup_register
    bl current_el_spx_irq_el2_handler
    restore_register
    msr DAIFClr, #2
    eret
asm_current_el_spx_fiq_el2_handler:
    backup_register
    bl current_el_spx_fiq_el2_handler
    restore_register
    msr DAIFClr, #1
    eret
asm_current_el_spx_serror_el2_handler:
    backup_register
    bl current_el_spx_serror_el2_handler
    restore_register
    msr DAIFClr, #4
    eret