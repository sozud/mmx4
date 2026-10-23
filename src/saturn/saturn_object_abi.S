.macro OBJECT_BOUNDARY name
    .section .text.\name,"ax"
    .align 2
    .global _\name
    .type _\name,@function
_\name:
    sts.l macl,@-r15
    sts.l pr,@-r15
    mov.l 1f,r0
    jsr @r0
    nop
    lds.l @r15+,pr
    lds.l @r15+,macl
    rts
    nop
    .align 2
1:  .long _saturn_shared_\name
    .size _\name,.-_\name
.endm
OBJECT_BOUNDARY func_8002AB20
OBJECT_BOUNDARY func_8002B160
OBJECT_BOUNDARY func_8002B1E8
OBJECT_BOUNDARY is_on_screen
OBJECT_BOUNDARY update_on_screen
OBJECT_BOUNDARY func_8002B3C0
