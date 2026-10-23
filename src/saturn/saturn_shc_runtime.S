#include "runtime_arith.S"
#include "runtime_copy.S"

    .section .text.shc_unsigned_remainder,"ax",@progbits
    .align 2
    .global _saturn_shc_unsigned_remainder
    .type _saturn_shc_unsigned_remainder,@function
_saturn_shc_unsigned_remainder:
    mov.l .Lmodlu_entry,r2
    mov r4,r1
    jmp @r2
    mov r5,r0
    .align 2
.Lmodlu_entry:
    .long __modlu
    .size _saturn_shc_unsigned_remainder,.-_saturn_shc_unsigned_remainder
    .section .text.shc_abs,"ax",@progbits
    .align 1
    .global _abs
    .type _abs,@function
_abs:
    mov r4,r0
    cmp/pz r0
    bt .Labs_done
    neg r0,r0
.Labs_done:
    rts
    nop
    .size _abs,.-_abs

    .global __sta_sftra8
    .align 2
__sta_sftra8:
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    rts
    shar r0

    .global __sta_sftra10
    .align 2
__sta_sftra10:
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    rts
    shar r0

    .global __sta_sftra7
    .align 2
__sta_sftra7:
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    rts
    shar r0

    .global __sta_sftra12
    .align 2
__sta_sftra12:
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    shar r0
    rts
    shar r0
