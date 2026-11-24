.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

glabel _ExitCard
 lui        $at, %hi(D_8012F43C)
 sw         $ra, %lo(D_8012F43C)($at)
 jal        EnterCriticalSection
  nop
 addiu      $t2, $zero, 0xB0
 jalr       $t2
  addiu     $t1, $zero, 0x56
 lui        $t2, %hi(D_800EDC54)
 lui        $t1, %hi(D_800EDC60)
 lw         $v0, 0x18($v0)
 addiu      $t2, $t2, %lo(D_800EDC54)
 addiu      $t1, $t1, %lo(D_800EDC60)
.Lcardend_C1C:
 lw         $v1, 0x0($t2)
 addiu      $t2, $t2, 0x4
 addiu      $v0, $v0, 0x4
 bne        $t2, $t1, .Lcardend_C1C
  sw        $v1, 0x6C($v0)
 jal        FlushCache
  nop
 jal        ExitCriticalSection
  nop
 lui        $ra, %hi(D_8012F43C)
 lw         $ra, %lo(D_8012F43C)($ra)
 nop
 jr         $ra
  nop
glabel D_800EDC54
 nop
 nop
 nop
glabel D_800EDC60
 nop
 nop
 nop
.size _ExitCard, . - _ExitCard
