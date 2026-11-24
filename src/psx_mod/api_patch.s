.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

glabel EnablePAD
 lui        $t1, %hi(jtbl_8012F454)
 lw         $t1, %lo(jtbl_8012F454)($t1)
 nop
 jr         $t1
  nop
.size EnablePAD, . - EnablePAD

glabel DesablePAD
 lui        $t1, %hi(jtbl_8012F458)
 lw         $t1, %lo(jtbl_8012F458)($t1)
 nop
 jr         $t1
  nop
.size DesablePAD, . - DesablePAD

glabel _patch_pad
 lui        $at, %hi(D_8012F44C)
 sw         $ra, %lo(D_8012F44C)($at)
 jal        EnterCriticalSection
  nop
 addiu      $t2, $zero, 0xB0
 jalr       $t2
  addiu     $t1, $zero, 0x57
 lw         $v0, 0x16C($v0)
 lui        $at, %hi(jtbl_8012F454)
 addi       $v1, $v0, 0x884
 sw         $v1, %lo(jtbl_8012F454)($at)
 lui        $at, %hi(jtbl_8012F458)
 addi       $v1, $v0, 0x894
 addiu      $t1, $zero, 0xB
 sw         $v1, %lo(jtbl_8012F458)($at)
.Lpad_3E0:
 addiu      $t1, $t1, -0x1
 sw         $zero, 0x594($v0)
 bnez       $t1, .Lpad_3E0
  addiu     $v0, $v0, 0x4
 jal        FlushCache
  nop
 lui        $ra, %hi(D_8012F44C)
 lw         $ra, %lo(D_8012F44C)($ra)
 nop
 jr         $ra
  nop
.size _patch_pad, . - _patch_pad
