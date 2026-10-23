    .section .text.saturn_draw_normal_sprite,"ax"
    .align 2
    .global _saturn_draw_normal_sprite
    .type _saturn_draw_normal_sprite,@function
_saturn_draw_normal_sprite:
    sts.l macl,@-r15
    sts.l pr,@-r15
    mov.l .Lsprite_body,r0
    jsr @r0
    nop
    lds.l @r15+,pr
    lds.l @r15+,macl
    rts
    nop
    .align 2
.Lsprite_body:
    .long _saturn_draw_normal_sprite_body
    .size _saturn_draw_normal_sprite,.-_saturn_draw_normal_sprite
