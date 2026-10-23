
    .macro DIV_STEPS_R1 divisor, partial
    .rept 32
    rotcl r1
    div1 \divisor,\partial
    .endr
    .endm

    .section .text.shc_divlu,"ax",@progbits
    .align 2
    .global __divlu
    .type __divlu,@function
__divlu:
    tst r0,r0
    mov.l r2,@-r15
    bt .Ldivlu_zero
    mov #0,r2
    div0u
    DIV_STEPS_R1 r0,r2
    rotcl r1
    mov r1,r0
    rts
    mov.l @r15+,r2
.Ldivlu_zero:
    mov.l .Lerrno_divlu,r2
    mov.l .Lediv_divlu,r1
    mov #0,r0
    mov.l r1,@r2
    rts
    mov.l @r15+,r2
    .align 2
.Lerrno_divlu:
    .long 0x0606D474
.Lediv_divlu:
    .long 0x0000044E
    .size __divlu,.-__divlu

    .section .text.shc_divls,"ax",@progbits
    .align 2
    .global __divls
    .type __divls,@function
__divls:
    tst r0,r0
    mov.l r2,@-r15
    bt .Ldivls_zero
    mov.l r3,@-r15
    mov #0,r2
    div0s r2,r1
    subc r3,r3
    subc r2,r1
    div0s r0,r3
    DIV_STEPS_R1 r0,r3
    rotcl r1
    addc r2,r1
    mov r1,r0
    mov.l @r15+,r3
    rts
    mov.l @r15+,r2
.Ldivls_zero:
    mov.l .Lerrno_divls,r1
    mov.l .Lediv_divls,r2
    mov #0,r0
    mov.l r2,@r1
    rts
    mov.l @r15+,r2
    .align 2
.Lerrno_divls:
    .long 0x0606D474
.Lediv_divls:
    .long 0x0000044E
    .size __divls,.-__divls

    .section .text.shc_divbs,"ax",@progbits
    .align 2
    .global __divbs
    .type __divbs,@function
__divbs:
    tst #255,r0
    bt.s .Ldivbs_zero
    mov.l r2,@-r15
    exts.b r1,r1
    mov #0,r2
    div0s r2,r1
    subc r2,r1
    shll16 r0
    shll16 r1
    shll8 r0
    div0s r0,r1
    div1 r0,r1
    div1 r0,r1
    div1 r0,r1
    div1 r0,r1
    div1 r0,r1
    div1 r0,r1
    div1 r0,r1
    div1 r0,r1
    exts.b r1,r0
    rotcl r0
    addc r2,r0
    rts
    mov.l @r15+,r2
.Ldivbs_zero:
    mov.l .Lerrno_divbs,r2
    mov.l .Lediv_divbs,r1
    mov #0,r0
    mov.l r1,@r2
    rts
    mov.l @r15+,r2
    .align 2
.Lerrno_divbs:
    .long 0x0606D474
.Lediv_divbs:
    .long 0x0000044E
    .size __divbs,.-__divbs

    .section .text.shc_modls,"ax",@progbits
    .align 2
    .global __modls
    .type __modls,@function
__modls:
    tst r0,r0
    mov.l r2,@-r15
    bt .Lmodls_zero
    mov.l r3,@-r15
    mov #0,r2
    mov.l r4,@-r15
    div0s r2,r1
    movt r4
    subc r3,r3
    subc r2,r1
    div0s r0,r3
    DIV_STEPS_R1 r0,r3
    div0s r2,r3
    movt r2
    xor r4,r2
    rotcr r2
    bf .Lmodls_fixed
    div0s r0,r3
    shar r3
    div1 r0,r3
.Lmodls_fixed:
    add r4,r3
    mov r3,r0
    mov.l @r15+,r4
    mov.l @r15+,r3
    rts
    mov.l @r15+,r2
.Lmodls_zero:
    mov.l .Lerrno_modls,r1
    mov.l .Lediv_modls,r2
    mov #0,r0
    mov.l r2,@r1
    rts
    mov.l @r15+,r2
    .align 2
.Lerrno_modls:
    .long 0x0606D474
.Lediv_modls:
    .long 0x0000044E
    .size __modls,.-__modls

    .section .text.shc_modlu,"ax",@progbits
    .align 2
    .global __modlu
    .type __modlu,@function
__modlu:
    tst r0,r0
    bt .Lmodlu_zero
    mov.l r3,@-r15
    mov #0,r3
    mov.l r4,@-r15
    mov r0,r4
    div0u
    DIV_STEPS_R1 r4,r3
    bf .Lmodlu_fix
    mov r3,r0
    mov.l @r15+,r4
    rts
    mov.l @r15+,r3
.Lmodlu_fix:
    add r3,r0
    mov.l @r15+,r4
    rts
    mov.l @r15+,r3
.Lmodlu_zero:
    mov.l r2,@-r15
    mov.l .Lerrno_modlu,r1
    mov.l .Lediv_modlu,r2
    mov #0,r0
    mov.l r2,@r1
    rts
    mov.l @r15+,r2
    .align 2
.Lerrno_modlu:
    .long 0x0606D474
.Lediv_modlu:
    .long 0x0000044E
    .size __modlu,.-__modlu

    .section .text.shc_shifts,"ax",@progbits
    .align 2
    .global __sftl
    .type __sftl,@function
__sftl:
    mov.l r2,@-r15
    cmp/pz r1
    bf .Lsftl_done
    mov #32,r2
    cmp/ge r2,r1
    bt .Lsftl_zero
    tst r1,r1
    bt .Lsftl_done
.Lsftl_loop:
    dt r1
    bf/s .Lsftl_loop
    shll r0
.Lsftl_done:
    rts
    mov.l @r15+,r2
.Lsftl_zero:
    mov #0,r0
    rts
    mov.l @r15+,r2
    .size __sftl,.-__sftl

    .align 2
    .global __sftrl
    .type __sftrl,@function
__sftrl:
    mov.l r2,@-r15
    cmp/pz r1
    bf .Lsftrl_done
    mov #32,r2
    cmp/ge r2,r1
    bt .Lsftrl_zero
    tst r1,r1
    bt .Lsftrl_done
.Lsftrl_loop:
    dt r1
    bf/s .Lsftrl_loop
    shlr r0
.Lsftrl_done:
    rts
    mov.l @r15+,r2
.Lsftrl_zero:
    mov #0,r0
    rts
    mov.l @r15+,r2
    .size __sftrl,.-__sftrl

    .align 2
    .global __sftra
    .type __sftra,@function
__sftra:
    mov.l r2,@-r15
    cmp/pz r1
    bf .Lsftra_done
    mov #32,r2
    cmp/ge r2,r1
    bt .Lsftra_sign
    tst r1,r1
    bt .Lsftra_done
.Lsftra_loop:
    dt r1
    bf/s .Lsftra_loop
    shar r0
.Lsftra_done:
    rts
    mov.l @r15+,r2
.Lsftra_sign:
    shll r0
    subc r0,r0
    rts
    mov.l @r15+,r2
    .size __sftra,.-__sftra

    .section .text.shc_divider,"ax",@progbits
    .align 2
    .global __divlsp
    .type __divlsp,@function
__divlsp:
    mov.l r2,@-r15
    mov.l r3,@-r15
    mov.l r4,@-r15
    mov r0,r4
    stc sr,r0
    and #240,r0
    mov r0,r2
    stc sr,r0
    or #240,r0
    ldc r0,sr
    mov.w .Ldivider_dvsr,r3
    mov.l r4,@r3
    mov #0,r0
    add #8,r3
    mov.l r0,@r3
    mov.l r1,@-r3
    add #16,r3
    mov.l @r3,r4
    stc sr,r0
    mov.w .Ldivider_mask,r1
    and r1,r0
    or r2,r0
    ldc r0,sr
    mov r4,r0
    mov.l @r15+,r4
    mov.l @r15+,r3
    rts
    mov.l @r15+,r2
    .size __divlsp,.-__divlsp

    .align 2
    .global __modlsp
    .type __modlsp,@function
__modlsp:
    mov.l r2,@-r15
    mov.l r3,@-r15
    mov.l r4,@-r15
    mov r0,r4
    stc sr,r0
    and #240,r0
    mov r0,r2
    stc sr,r0
    or #240,r0
    ldc r0,sr
    mov.w .Ldivider_dvsr,r3
    mov.l r4,@r3
    mov #0,r0
    add #8,r3
    mov.l r0,@r3
    mov.l r1,@-r3
    add #12,r3
    mov.l @r3,r4
    stc sr,r0
    mov.w .Ldivider_mask,r1
    and r1,r0
    or r2,r0
    ldc r0,sr
    mov r4,r0
    mov.l @r15+,r4
    mov.l @r15+,r3
    rts
    mov.l @r15+,r2
    .align 1
.Ldivider_dvsr:
    .short 0xFF00
.Ldivider_mask:
    .short 0xFF0F
    .size __modlsp,.-__modlsp
