.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

glabel __main
    jr      $ra
    nop
.size __main, . - __main

glabel __start
    lui     $v0, %hi(__bss_start)
    addiu   $v0, $v0, %lo(__bss_start)
    lui     $v1, %hi(__bss_end)
    addiu   $v1, $v1, %lo(__bss_end)
1:  sw      $zero, 0x0($v0)
    addiu   $v0, $v0, 0x4
    sltu    $at, $v0, $v1
    bnez    $at, 1b
    nop
    addiu   $v0, $zero, 0x4
    nop
    nop
    nop
    nop
    lui     $a0, %hi(sn_ram_sizes)
    addiu   $a0, $a0, %lo(sn_ram_sizes)
    addu    $a0, $a0, $v0
    lw      $v0, 0x0($a0)
    lui     $t0, 0x8000
    or      $sp, $v0, $t0
    lui     $a0, %hi(__bss_end)
    addiu   $a0, $a0, %lo(__bss_end)
    sll     $a0, $a0, 3
    srl     $a0, $a0, 3
    lui     $v1, %hi(sn_stack_size)
    lw      $v1, %lo(sn_stack_size)($v1)
    nop
    subu    $a1, $v0, $v1
    subu    $a1, $a1, $a0
    or      $a0, $a0, $t0
    lui     $at, %hi(D_8012F418)
    sw      $ra, %lo(D_8012F418)($at)
    lui     $gp, %hi(__bss_start)
    addiu   $gp, $gp, %lo(__bss_start)
    addu    $fp, $sp, $zero
    jal     InitHeap
    addi    $a0, $a0, 4
    lui     $ra, %hi(D_8012F418)
    lw      $ra, %lo(D_8012F418)($ra)
    nop
    jal     func_80012024
    nop
.size __start, . - __start

glabel sn_version
    .word 0x0000004D
glabel sn_ram_sizes
    .word 0x00200000
    .word 0x00200000
    .word 0x00200000
    .word 0x00200000
