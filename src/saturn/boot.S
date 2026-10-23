    .section .text
    .align 2
    .global _saturn_boot
    .global _saturn_boot_tail
    .global _saturn_boot_tail_second
    .global _saturn_boot_module_first
    .global _saturn_boot_module_second
    .global _saturn_boot_erased
    .global _saturn_boot_end
_saturn_boot:
    mov.l .Lsource,r1
    mov.l .Ldestination,r2
#ifdef MODULE_COMPRESSED
    mov.l .Ldecoded_end,r4
.Lgroup:
    mov.b @r1+,r5
    shll16 r5
    shll8 r5
    mov #8,r6
.Litem:
    cmp/hs r4,r2
    bt .Lcopy_tail
    shll r5
    bf .Lmatch
    mov.b @r1+,r0
    mov.b r0,@r2
    bra .Lnext
    add #1,r2
.Lmatch:
    mov.b @r1+,r7
    extu.b r7,r7
    mov.b @r1+,r3
    extu.b r3,r3
    shll8 r7
    or r7,r3
    shlr8 r7
    shlr2 r7
    shlr2 r7
    add #3,r7
    mov.w .Ldistance_mask,r0
    and r0,r3
    add #1,r3
    mov r2,r0
    sub r3,r0
.Lmatch_copy:
    mov.b @r0+,r3
    dt r7
    mov.b r3,@r2
    bf/s .Lmatch_copy
    add #1,r2
.Lnext:
    dt r6
    bf .Litem
    bra .Lgroup
    nop
#else
    mov.l .Linitialized_words,r3
.Lcopy:
    mov.l @r1+,r0
    mov.l r0,@r2
    dt r3
    bf/s .Lcopy
    add #4,r2
#endif
.Lcopy_tail:
    mov.l .Ltail_destination,r2
    mov.l .Ltail_source,r1
    mov.l .Ltail_words,r3
.Ltail_copy:
    mov.l @r1+,r0
    mov.l r0,@r2
    dt r3
    bf/s .Ltail_copy
    add #4,r2
    mov.l .Lccr,r1
    mov.b @r1,r0
    or #0x10,r0
    mov.b r0,@r1
    mov.l .Ltail_destination,r0
    jmp @r0
    nop
#ifdef MODULE_COMPRESSED
.Ldistance_mask:     .word 0x0FFF
#endif
    .align 2
.Lsource:            .long MODULE_SOURCE
.Ldestination:       .long MODULE_DESTINATION
.Linitialized_words: .long MODULE_COPY_WORDS
.Ldecoded_end:       .long MODULE_DESTINATION+MODULE_INITIALIZED_WORDS*4
.Ltail_source:       .long _saturn_boot_tail
.Ltail_words:        .long (_saturn_boot_end-_saturn_boot_tail)/4
.Ltail_destination:  .long MODULE_END
.Lccr:               .long 0xFFFFFE92

    .align 2
_saturn_boot_tail:
    stc sr,r7
    mov r7,r0
    or #0xF0,r0
    ldc r0,sr
    mov.l .Lbss_start,r1
    mov.l .Lbss_words,r3
    tst r3,r3
    bt .Lbss_done
    mov #0,r0
.Lclear_bss:
    mov.l r0,@r1
    dt r3
    bf/s .Lclear_bss
    add #4,r1
.Lbss_done:
_saturn_boot_module_first:
    mov.l .Lentry_target,r1
_saturn_boot_module_second:
    mov.l @r1,r0
    mov.l .Lself,r3
    cmp/eq r3,r0
    bt .Lsource_ready
    mov.l .Lerase_source,r1
_saturn_boot_tail_second:
    mov.l .Lerase_words,r3
    mov #0,r0
.Lerase:
    mov.l r0,@r1
    dt r3
    bf/s .Lerase
    add #4,r1
.Lsource_ready:
    mov.l .Lentry_target,r1
    mov.l .Lself,r0
    mov.l r0,@r1
    mov.l .Ltail_ccr,r1
    mov.b @r1,r0
    or #0x10,r0
    mov.b r0,@r1
    ldc r7,sr
_saturn_boot_erased:
    mov.l .Lmain,r0
    jmp @r0
    nop
    .align 2
.Lerase_source: .long APPENDED_SOURCE
.Lerase_words:  .long APPENDED_WORDS
.Lmain:         .long 0x06010330
.Lbss_start:    .long MODULE_DESTINATION+MODULE_INITIALIZED_WORDS*4
.Lbss_words:    .long MODULE_ZERO_WORDS
.Lentry_target: .long 0x06010010
.Lself:         .long MODULE_END
.Ltail_ccr:     .long 0xFFFFFE92
_saturn_boot_end:
