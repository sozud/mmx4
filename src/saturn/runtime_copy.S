
    .section .text.shc_quick_mvn,"ax",@progbits
    .align 2
    .global __quick_mvn
    .type __quick_mvn,@function
__quick_mvn:
    mov.l r3,@-r15
    mov #64,r3
    cmp/hs r0,r3
    bf .Lquick_forward
.Lquick_back:
    add #-4,r0
    cmp/pz r0
    bf .Lquick_done
    mov.l @(r0,r2),r3
    bra .Lquick_back
    mov.l r3,@(r0,r1)
.Lquick_done:
    rts
    mov.l @r15+,r3
.Lquick_forward:
    mov.l r2,@-r15
    mov r2,r3
    add r0,r3
.Lquick_loop:
    mov.l @r2+,r0
    cmp/hs r2,r3
    bf .Lquick_end
    mov.l r0,@r1
    mov.l @r2+,r0
    cmp/hs r2,r3
    bf .Lquick_end
    mov.l r0,@(4,r1)
    bra .Lquick_loop
    add #8,r1
.Lquick_end:
    mov.l @r15+,r2
    rts
    mov.l @r15+,r3
    .size __quick_mvn,.-__quick_mvn

    .section .text.shc_quick_parity_mvn,"ax",@progbits
    .align 2
    .global __quick_odd_mvn
    .global __quick_evn_mvn
    .type __quick_odd_mvn,@function
    .type __quick_evn_mvn,@function
__quick_evn_mvn:
    bra .Lparity_entry
    mov.l r3,@-r15
__quick_odd_mvn:
    mov.l r3,@-r15
.Lparity_entry:
    tst r0,r0
    bt .Lparity_empty
    mov.l r4,@-r15
    mov.l r5,@-r15
    mov r2,r5
    add r0,r5
    add #-4,r5
    mov r1,r4
    add r0,r4
    add #-4,r4
    mov.l @r5,r3
.Lparity_loop:
    cmp/eq r2,r5
    bt .Lparity_last
    add #-4,r5
    mov.l @r5,r0
    mov.l r3,@r4
    add #-4,r4
    bra .Lparity_loop
    mov r0,r3
.Lparity_last:
    mov.l r3,@r4
    mov.l @r15+,r5
    mov.l @r15+,r4
.Lparity_empty:
    rts
    mov.l @r15+,r3
    .size __quick_odd_mvn,.-__quick_odd_mvn

    .section .text.shc_slow_mvn,"ax",@progbits
    .align 2
    .global __slow_mvn
    .type __slow_mvn,@function
__slow_mvn:
    mov.l r2,@-r15
    mov.l r3,@-r15
    mov.l r4,@-r15
    cmp/eq #0,r0
    bt .Lslow_done
    mov r2,r4
    add r0,r4
.Lslow_loop:
    mov.b @r2+,r0
    mov.b r0,@r1
    cmp/hi r2,r4
    bf .Lslow_done
    mov.b @r2+,r0
    mov.b r0,@(1,r1)
    cmp/hi r2,r4
    bf .Lslow_done
    mov.b @r2+,r0
    mov.b r0,@(2,r1)
    cmp/hi r2,r4
    bf .Lslow_done
    mov.b @r2+,r0
    mov.b r0,@(3,r1)
    cmp/hi r2,r4
    add #4,r1
    bt .Lslow_loop
.Lslow_done:
    mov.l @r15+,r4
    mov.l @r15+,r3
    rts
    mov.l @r15+,r2
    .size __slow_mvn,.-__slow_mvn

    .section .text.shc_strcpy_r0,"ax",@progbits
    .align 2
    .global __strcpy_r0
    .type __strcpy_r0,@function
__strcpy_r0:
    mov.l r3,@-r15
    mov.l r4,@-r15
    mov r0,r4
    mov r0,r3
.Lstrcpy_loop:
    mov.b @r1+,r0
    mov.b r0,@r3
    cmp/eq #0,r0
    bf/s .Lstrcpy_loop
    add #1,r3
    mov r4,r0
    mov.l @r15+,r4
    rts
    mov.l @r15+,r3
    .size __strcpy_r0,.-__strcpy_r0
