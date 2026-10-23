    .section .text.saturn_thread_context_prepare,"ax"
    .align 2
    .global _saturn_thread_context_prepare
_saturn_thread_context_prepare:
    add #-60,r5
    mov.l r4,@-r5
    mov.l r5,@(16,r6)
    rts
    mov r6,r0

    .section .text.saturn_thread_context_resume,"ax"
    .align 2
    .global _saturn_thread_context_resume
    .global _saturn_context_saved
    .global _saturn_context_restore
    .global _saturn_context_return
_saturn_thread_context_resume:
    mov.l r14,@-r15
    mov.l r13,@-r15
    mov.l r12,@-r15
    mov.l r11,@-r15
    mov.l r10,@-r15
    mov.l r9,@-r15
    mov.l r8,@-r15
    mov.l r7,@-r15
    mov.l r6,@-r15
    mov.l r5,@-r15
    mov.l r4,@-r15
    mov.l r3,@-r15
    mov.l r2,@-r15
    mov.l r1,@-r15
    mov.l r0,@-r15
    sts.l pr,@-r15
_saturn_context_saved:
    mov.l .Lscheduler_sp,r1
    mov.l .Lyield,r2
    cmp/eq r2,r4
    bt/s .Lyield_context
    nop
    mov.l r15,@r1
    mov.l @(16,r4),r15
    bra _saturn_context_restore
    nop
.Lyield_context:
    mov.l .Lcurrent_thread,r2
    mov.l @r2,r2
    mov.l @r2,r0
    mov.l .Ldiscard_saved_sp,r3
    and r3,r0
    cmp/eq r0,r3
    bt/s .Lrestore_scheduler
    nop
    mov.l r15,@(16,r2)
.Lrestore_scheduler:
    mov.l @r1,r15
_saturn_context_restore:
    lds.l @r15+,pr
    mov.l @r15+,r0
    mov.l @r15+,r1
    mov.l @r15+,r2
    mov.l @r15+,r3
    mov.l @r15+,r4
    mov.l @r15+,r5
    mov.l @r15+,r6
    mov.l @r15+,r7
    mov.l @r15+,r8
    mov.l @r15+,r9
    mov.l @r15+,r10
    mov.l @r15+,r11
    mov.l @r15+,r12
    mov.l @r15+,r13
_saturn_context_return:
    rts
    mov.l @r15+,r14
    .align 2
.Lscheduler_sp:
    .long _saturn_scheduler_stack_pointer
.Lcurrent_thread:
    .long _saturn_current_thread
.Lyield:
    .long 0xFF000000
.Ldiscard_saved_sp:
    .long 0x00040000

    .section .text.saturn_exception_vectors,"ax"
    .align 2
    .global _saturn_exception_vector_4
    .global _saturn_exception_vector_6
    .global _saturn_exception_vector_9
    .global _saturn_exception_vector_10
_saturn_exception_vector_4:
    mov.l r0,@-r15
    bra .Lexception_frame
    mov #0,r0
_saturn_exception_vector_6:
    mov.l r0,@-r15
    bra .Lexception_frame
    mov #1,r0
_saturn_exception_vector_9:
    mov.l r0,@-r15
    bra .Lexception_frame
    mov #2,r0
_saturn_exception_vector_10:
    mov.l r0,@-r15
    mov #3,r0
.Lexception_frame:
    mov.l r1,@-r15
    mov.l r2,@-r15
    mov.l r3,@-r15
    mov.l r4,@-r15
    mov.l r5,@-r15
    mov.l r6,@-r15
    mov.l r7,@-r15
    mov.l r8,@-r15
    mov.l r9,@-r15
    mov.l r10,@-r15
    mov.l r11,@-r15
    mov.l r12,@-r15
    mov.l r13,@-r15
    mov.l r14,@-r15
    mov r15,r1
    add #72,r1
    mov.l r1,@-r15
    sts.l macl,@-r15
    sts.l mach,@-r15
    stc.l vbr,@-r15
    stc.l gbr,@-r15
    sts.l pr,@-r15
    mov.l .Lerror_code,r7
    mov.l r0,@r7
    mov.l .Lerror_context,r7
    mov.l r15,@r7
    mov.l .Lfatal_error,r3
    jsr @r3
    nop
.Lexception_halt:
    bra .Lexception_halt
    nop
    .align 2
.Lerror_code:
    .long _saturn_error_code
.Lerror_context:
    .long _saturn_error_context
.Lfatal_error:
    .long _saturn_fatal_error

    .section .text.saturn_entry,"ax"
    .align 2
    .global _saturn_entry
_saturn_entry:
    mov.l .Lentry_stack,r0
    mov r0,r15
    mov.l .Lentry_main,r0
    jmp @r0
    nop
    .align 2
.Lentry_stack:
    .long 0x06009800
.Lentry_main:
    .long _saturn_main
