.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

glabel _SsInitSoundSep
 addiu      $sp, $sp, -0x20
 addu       $t4, $a0, $zero
 addu       $t3, $a1, $zero
 sw         $s1, 0x14($sp)
 addu       $s1, $zero, $zero
 addu       $t0, $zero, $zero
 addiu      $t2, $zero, 0x40
 addiu      $t1, $zero, 0x7F
 sll        $a0, $a0, 16
 sra        $a0, $a0, 14
 sll        $a1, $a1, 16
 sra        $a1, $a1, 16
 sll        $v0, $a1, 1
 addu       $v0, $v0, $a1
 sll        $v0, $v0, 2
 subu       $v0, $v0, $a1
 sll        $v0, $v0, 2
 subu       $v0, $v0, $a1
 sw         $ra, 0x1C($sp)
 sw         $s2, 0x18($sp)
 sw         $s0, 0x10($sp)
 lui        $at, %hi(_ss_score)
 addu       $at, $at, $a0
 lw         $v1, %lo(_ss_score)($at)
 sll        $v0, $v0, 2
 addu       $s0, $v1, $v0
 addu       $v1, $s0, $zero
 addiu      $v0, $zero, 0x1
 sb         $zero, 0x10($s0)
 sb         $zero, 0x11($s0)
 sb         $zero, 0x12($s0)
 sb         $zero, 0x13($s0)
 sb         $zero, 0x14($s0)
 sb         $zero, 0x15($s0)
 sb         $zero, 0x16($s0)
 sb         $zero, 0x27($s0)
 sb         $zero, 0x28($s0)
 sb         $zero, 0x29($s0)
 sb         $zero, 0x2A($s0)
 sb         $zero, 0x2B($s0)
 sh         $zero, 0x48($s0)
 sh         $v0, 0x6E($s0)
 sh         $zero, 0x4A($s0)
 sh         $a2, 0x4C($s0)
 sh         $zero, 0x72($s0)
 sw         $zero, 0x7C($s0)
 sw         $zero, 0x80($s0)
 sw         $zero, 0x84($s0)
 sw         $zero, 0x88($s0)
 sh         $zero, 0xA8($s0)
.Lsep_BE8:
 addu       $v0, $s0, $t0
 sb         $t2, 0x17($v0)
 sb         $t0, 0x2C($v0)
 sh         $t1, 0x4E($v1)
 addiu      $t0, $t0, 0x1
 slti       $v0, $t0, 0x10
 bnez       $v0, .Lsep_BE8
  addiu     $v1, $v1, 0x2
 sll        $v0, $t3, 16
 bnez       $v0, .Lsep_C68
  sw        $a3, 0x4($s0)
 lbu        $v1, 0x0($a3)
 addiu      $v0, $zero, 0x53
 beq        $v1, $v0, .Lsep_C2C
  addiu     $v0, $zero, 0x70
 bne        $v1, $v0, .Lsep_C78
  lui       $a1, (0x3938700 >> 16)
.Lsep_C2C:
 addiu      $v0, $a3, 0x6
 sw         $v0, 0x4($s0)
 lbu        $v0, 0x5($a3)
 nop
 beqz       $v0, .Lsep_C5C
  addiu     $v0, $a3, 0x8
 lui        $a0, %hi(sep_not_sep_data)
 addiu      $a0, $a0, %lo(sep_not_sep_data)
 jal        printf
  nop
 j          .Lsep_EB4
  addiu     $v0, $zero, -0x1
.Lsep_C5C:
 sw         $v0, 0x4($s0)
 j          .Lsep_C74
  addiu     $s1, $s1, 0x8
.Lsep_C68:
 addiu      $v0, $a3, 0x2
 sw         $v0, 0x4($s0)
 addiu      $s1, $s1, 0x2
.Lsep_C74:
 lui        $a1, (0x3938700 >> 16)
.Lsep_C78:
 lw         $v1, 0x4($s0)
 ori        $a1, $a1, (0x3938700 & 0xFFFF)
 addiu      $v0, $v1, 0x1
 sw         $v0, 0x4($s0)
 lbu        $a2, 0x0($v1)
 addiu      $v0, $v1, 0x2
 sw         $v0, 0x4($s0)
 lbu        $v0, 0x1($v1)
 lw         $v1, 0x4($s0)
 sll        $a0, $a2, 8
 or         $v0, $v0, $a0
 sh         $v0, 0x4A($s0)
 addiu      $v0, $v1, 0x1
 sw         $v0, 0x4($s0)
 lbu        $a3, 0x0($v1)
 addiu      $v0, $v1, 0x2
 sw         $v0, 0x4($s0)
 lbu        $a0, 0x1($v1)
 addiu      $v0, $v1, 0x3
 sw         $v0, 0x4($s0)
 lbu        $v1, 0x2($v1)
 sll        $v0, $a3, 16
 sll        $a0, $a0, 8
 or         $v0, $v0, $a0
 or         $v0, $v0, $v1
 div        $zero, $a1, $v0
 bnez       $v0, .Lsep_CEC
  nop
 break      7
.Lsep_CEC:
 addiu      $at, $zero, -0x1
 bne        $v0, $at, .Lsep_D04
  lui       $at, (0x80000000 >> 16)
 bne        $a1, $at, .Lsep_D04
  nop
 break      6
.Lsep_D04:
 mflo       $a1
 mfhi       $v1
 sw         $v0, 0x84($s0)
 srl        $v0, $v0, 1
 slt        $v0, $v0, $v1
 beqz       $v0, .Lsep_D2C
  addiu     $s1, $s1, 0x5
 addiu      $v0, $a1, 0x1
 j          .Lsep_D30
  sw        $v0, 0x84($s0)
.Lsep_D2C:
 sw         $a1, 0x84($s0)
.Lsep_D30:
 sll        $a0, $t4, 16
 lw         $v0, 0x84($s0)
 lw         $a1, 0x4($s0)
 sra        $a0, $a0, 16
 sw         $v0, 0x8C($s0)
 addiu      $v0, $a1, 0x3
 sw         $v0, 0x4($s0)
 lbu        $a2, 0x2($a1)
 addiu      $v0, $a1, 0x4
 sw         $v0, 0x4($s0)
 lbu        $v1, 0x3($a1)
 addiu      $v0, $a1, 0x5
 sw         $v0, 0x4($s0)
 lbu        $a3, 0x4($a1)
 addiu      $v0, $a1, 0x6
 sw         $v0, 0x4($s0)
 lbu        $a1, 0x5($a1)
 sll        $v0, $a2, 24
 sll        $v1, $v1, 16
 addu       $v0, $v0, $v1
 sll        $v1, $a3, 8
 addu       $v0, $v0, $v1
 addu       $s2, $v0, $a1
 sll        $a1, $t3, 16
 jal        _SsReadDeltaValue
  sra       $a1, $a1, 16
 lh         $a0, 0x4A($s0)
 lw         $v1, 0x84($s0)
 nop
 mult       $a0, $v1
 lw         $a0, 0x4($s0)
 lw         $v1, 0x4($s0)
 sw         $a0, 0xC($s0)
 lui        $a0, %hi(VBLANK_MINUS)
 lw         $a0, %lo(VBLANK_MINUS)($a0)
 sw         $v0, 0x7C($s0)
 sw         $v0, 0x88($s0)
 sw         $v1, 0x8($s0)
 sll        $v1, $a0, 4
 subu       $a3, $v1, $a0
 sll        $a1, $a3, 2
 mflo       $a2
 sll        $v0, $a2, 2
 addu       $v0, $v0, $a2
 sll        $v0, $v0, 1
 sltu       $v0, $v0, $a1
 beqz       $v0, .Lsep_E20
  addiu     $s1, $s1, 0x6
 sll        $v1, $a0, 2
 addu       $v1, $v1, $a0
 sll        $v0, $v1, 4
 subu       $v0, $v0, $v1
 sll        $v0, $v0, 3
 divu       $zero, $v0, $a2
 bnez       $a2, .Lsep_E14
  nop
 break      7
.Lsep_E14:
 mflo       $v0
 j          .Lsep_EA4
  sh        $v0, 0x6E($s0)
.Lsep_E20:
 lh         $v1, 0x4A($s0)
 lw         $v0, 0x84($s0)
 nop
 mult       $v1, $v0
 mflo       $v1
 sll        $v0, $v1, 2
 addu       $v0, $v0, $v1
 sll        $v0, $v0, 1
 divu       $zero, $v0, $a1
 bnez       $a1, .Lsep_E50
  nop
 break      7
.Lsep_E50:
 mflo       $a0
 lh         $v1, 0x4A($s0)
 lw         $v0, 0x84($s0)
 nop
 mult       $v1, $v0
 mflo       $v1
 sll        $v0, $v1, 2
 addu       $v0, $v0, $v1
 sll        $v0, $v0, 1
 divu       $zero, $v0, $a1
 bnez       $a1, .Lsep_E84
  nop
 break      7
.Lsep_E84:
 mfhi       $v1
 addiu      $v0, $zero, -0x1
 sh         $v0, 0x6E($s0)
 sll        $v0, $a3, 1
 sltu       $v0, $v0, $v1
 beqz       $v0, .Lsep_EA8
  sh        $a0, 0x70($s0)
 addiu      $v0, $a0, 0x1
.Lsep_EA4:
 sh         $v0, 0x70($s0)
.Lsep_EA8:
 lhu        $v1, 0x70($s0)
 addu       $v0, $s1, $s2
 sh         $v1, 0x72($s0)
.Lsep_EB4:
 lw         $ra, 0x1C($sp)
 lw         $s2, 0x18($sp)
 lw         $s1, 0x14($sp)
 lw         $s0, 0x10($sp)
 addiu      $sp, $sp, 0x20
 jr         $ra
  nop
.size _SsInitSoundSep, . - _SsInitSoundSep

.section .rodata

.align 2
glabel sep_not_sep_data
.asciz "This is not SEP Data.\n"
.align 2
.size sep_not_sep_data, . - sep_not_sep_data
