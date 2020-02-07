.align 4

.section ".text.start"
.global _start
_start:
    // disable all interrupt(daif at bits 9..6)
    msr DAIFSet, #0x0f
//#if defined(DEBUG)
//    bl debug_spin
//#endif
    ldr x0, =__stack_start
    mov sp, x0
    bl bss_clear
    bl main
    b finish

#if defined(DEBUG)
debug_spin:
    mov x0, xzr
1:
    cbz x0, 1b
    ret
#endif

.section ".text"
bss_clear:
    ldr x1, =__bss_start
    ldr x2, =__bss_end
1:
    cmp x1, x2
    beq 2f
    str wzr, [x1]
    add x1, x1, #4
    b 1b
2:
    ret

finish:
    wfe
    b finish