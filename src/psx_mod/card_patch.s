.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

glabel func_800EDA4C
 lui        $v0, %hi(D_800EDA60)
 addiu      $v0, $v0, %lo(D_800EDA60)
 jr         $v0
  nop
 nop
glabel D_800EDA60
 lw         $v0, 0x1074($v1)
 nop
 andi       $v0, $v0, 0x80
 beqz       $v0, .Lcard_A9C
  nop
.Lcard_A74:
 lw         $v0, 0x1044($v1)
 nop
 andi       $v0, $v0, 0x80
 bnez       $v0, .Lcard_A74
  nop
 lui        $v0, %hi(jtbl_8012F430)
 lw         $v0, %lo(jtbl_8012F430)($v0)
 nop
 jr         $v0
  nop
.Lcard_A9C:
 jr         $ra
  nop
.size func_800EDA4C, . - func_800EDA4C

glabel _patch_card
 lui        $at, %hi(D_8012F42C)
 sw         $ra, %lo(D_8012F42C)($at)
 jal        EnterCriticalSection
  nop
 addiu      $t2, $zero, 0xB0
 jalr       $t2
  addiu     $t1, $zero, 0x56
 lw         $v0, 0x18($v0)
 nop
 lw         $v1, 0x70($v0)
 nop
 andi       $t1, $v1, 0xFFFF
 lw         $v1, 0x74($v0)
 sll        $t1, $t1, 16
 andi       $t2, $v1, 0xFFFF
 addu       $v1, $t1, $t2
 lui        $t2, %hi(func_800EDA4C)
 lui        $t1, %hi(D_800EDA60)
 addiu      $v0, $v1, 0x28
 addiu      $t2, $t2, %lo(func_800EDA4C)
 addiu      $t1, $t1, %lo(D_800EDA60)
.Lcard_AF8:
 lw         $v1, 0x0($t2)
 addiu      $t2, $t2, 0x4
 addiu      $v0, $v0, 0x4
 bne        $t2, $t1, .Lcard_AF8
  sw        $v1, -0x4($v0)
 lui        $at, %hi(jtbl_8012F430)
 jal        FlushCache
  sw        $v0, %lo(jtbl_8012F430)($at)
 lui        $ra, %hi(D_8012F42C)
 lw         $ra, %lo(D_8012F42C)($ra)
 nop
 jr         $ra
  nop
.size _patch_card, . - _patch_card

glabel func_800EDB2C
 lui        $t0, %hi(func_800EDB2C)
 addiu      $t0, $t0, %lo(func_800EDB2C)
 jalr       $t0
  nop
 nop
 nop
 addiu      $t0, $zero, 0xC8
.Lcard_B48:
 addiu      $t0, $t0, -0x1
 bnez       $t0, .Lcard_B48
  nop
 jr         $ra
  nop
.size func_800EDB2C, . - func_800EDB2C

glabel _patch_card2
 lui        $at, %hi(D_8012F42C)
 sw         $ra, %lo(D_8012F42C)($at)
 jal        EnterCriticalSection
  nop
 addiu      $t2, $zero, 0xB0
 jalr       $t2
  addiu     $t1, $zero, 0x57
 lw         $v0, 0x16C($v0)
 lui        $t2, %hi(func_800EDB2C)
 lui        $t1, %hi(func_800EDB2C + 0x14)
 lw         $v1, 0x9C8($v0)
 addiu      $t2, $t2, %lo(func_800EDB2C)
 addiu      $t1, $t1, %lo(func_800EDB2C + 0x14)
.Lcard_B90:
 lw         $v1, 0x9C8($v0)
 lw         $t0, 0x0($t2)
 addiu      $t2, $t2, 0x4
 sw         $v1, -0x4($t2)
 addiu      $v0, $v0, 0x4
 bne        $t2, $t1, .Lcard_B90
  sw        $t0, 0x9C4($v0)
 jal        FlushCache
  nop
 lui        $ra, %hi(D_8012F42C)
 lw         $ra, %lo(D_8012F42C)($ra)
 nop
 jr         $ra
  nop
.size _patch_card2, . - _patch_card2

glabel func_800EDBC8
 lui        $t6, %hi(0x31FFFF)
 addiu      $t6, $t6, %lo(0x31FFFF)
.Lcard_BD0:
 bnez       $t6, .Lcard_BD0
  addiu     $t6, $t6, -0x1
 jr         $ra
  nop
 nop
 nop
 nop
.size func_800EDBC8, . - func_800EDBC8
