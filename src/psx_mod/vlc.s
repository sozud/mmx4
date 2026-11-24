.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

glabel vlc_state
.word 0x00FFFFFF
.size vlc_state, . - vlc_state

glabel DecDCTvlcSize
 lui        $t0, %hi(vlc_state)
 addiu      $t0, $t0, %lo(vlc_state)
 addi       $at, $a0, -0x1
 blez       $at, .Lvlc_564
  lw        $v0, 0x0($t0)
 sll        $at, $a0, 1
 jr         $ra
  sw        $at, 0x0($t0)
.Lvlc_564:
 lui        $at, (0xFFFFFF >> 16)
 ori        $at, $at, (0xFFFFFF & 0xFFFF)
 jr         $ra
  sw        $at, 0x0($t0)
.size DecDCTvlcSize, . - DecDCTvlcSize

glabel DecDCTvlc
 lui        $t0, %hi(vlc_state)
 addiu      $t0, $t0, %lo(vlc_state)
 lui        $a2, %hi(CF_DVLC)
 addiu      $a2, $a2, %lo(CF_DVLC)
 lui        $a3, %hi(CF2_DVLC)
 addiu      $a3, $a3, %lo(CF2_DVLC)
 bnez       $a0, .Lvlc_5CC
  lw        $t1, 0x0($t0)
 lui        $t0, %hi(vlc_saved_registers)
 addiu      $t0, $t0, %lo(vlc_saved_registers)
 lw         $a0, 0x0($t0)
 lw         $a1, 0x4($t0)
 lw         $v0, 0x8($t0)
 lw         $v1, 0xC($t0)
 lw         $t4, 0x10($t0)
 lw         $t5, 0x14($t0)
 lw         $t7, 0x18($t0)
 lw         $t8, 0x1C($t0)
 lw         $t9, 0x20($t0)
 add        $t1, $t1, $t1
 bgez       $zero, .Lvlc_744
  add       $t6, $a1, $t1
.Lvlc_5CC:
 add        $t5, $zero, $zero
 add        $t7, $zero, $zero
 add        $t8, $zero, $zero
 add        $t9, $zero, $zero
 add        $t1, $t1, $t1
 add        $t6, $a1, $t1
 lhu        $t0, 0x0($a0)
 lhu        $t1, 0x2($a0)
 lhu        $t4, 0x4($a0)
 lhu        $t2, 0x6($a0)
 lhu        $v0, 0x8($a0)
 lhu        $v1, 0xA($a0)
 addi       $t2, $t2, -0x3
 bltz       $t2, .Lvlc_60C
  sll       $t4, $t4, 10
 addi       $t5, $zero, 0x1
.Lvlc_60C:
 addi       $a0, $a0, 0xC
 sll        $v0, $v0, 16
 or         $v0, $v0, $v1
 or         $v1, $zero, $zero
 sh         $t0, 0x0($a1)
 sh         $t1, 0x2($a1)
 addi       $a1, $a1, 0x2
.Lvlc_628:
 beqz       $t5, .Lvlc_700
  srl       $t0, $v0, 22
 xori       $at, $t0, 0x3FF
 beqz       $at, .Lvlc_84C
  addi      $a1, $a1, 0x2
 addi       $at, $t5, -0x3
 bltz       $at, .Lvlc_64C
  addi      $at, $a2, -0x400
 addi       $at, $at, -0x400
.Lvlc_64C:
 srl        $t0, $v0, 24
 sll        $t0, $t0, 2
 add        $t0, $t0, $at
 lhu        $t1, 0x0($t0)
 lhu        $t2, 0x2($t0)
 and        $t0, $zero, $zero
 beqz       $t2, .Lvlc_690
  sllv      $v0, $v0, $t1
 addi       $at, $zero, 0x20
 sub        $at, $at, $t2
 srlv       $t0, $v0, $at
 bltz       $v0, .Lvlc_68C
  sllv      $v0, $v0, $t2
 addi       $t3, $zero, -0x1
 srlv       $t3, $t3, $at
 sub        $t0, $t0, $t3
.Lvlc_68C:
 add        $v1, $v1, $t2
.Lvlc_690:
 add        $v1, $v1, $t1
 andi       $at, $v1, 0x10
 beqz       $at, .Lvlc_6B0
  andi      $v1, $v1, 0xF
 lhu        $t1, 0x0($a0)
 addi       $a0, $a0, 0x2
 sllv       $t1, $t1, $v1
 or         $v0, $v0, $t1
.Lvlc_6B0:
 addi       $at, $t5, -0x2
 bgtz       $at, .Lvlc_6D8
  add       $t1, $t9, $t0
 beqz       $at, .Lvlc_6D0
  add       $t1, $t8, $t0
 add        $t1, $t7, $t0
 bgez       $zero, .Lvlc_6DC
  add       $t7, $t7, $t0
.Lvlc_6D0:
 bgez       $zero, .Lvlc_6DC
  add       $t8, $t8, $t0
.Lvlc_6D8:
 add        $t9, $t9, $t0
.Lvlc_6DC:
 sll        $t1, $t1, 2
 andi       $t1, $t1, 0x3FF
 or         $t1, $t4, $t1
 addi       $t5, $t5, 0x1
 addi       $at, $t5, -0x7
 bnez       $at, .Lvlc_738
  sh        $t1, 0x0($a1)
 bgez       $zero, .Lvlc_738
  addi      $t5, $t5, -0x6
.Lvlc_700:
 xori       $at, $t0, 0x1FF
 beqz       $at, .Lvlc_84C
  addi      $a1, $a1, 0x2
 sll        $v0, $v0, 10
 addi       $v1, $v1, 0xA
 andi       $at, $v1, 0x10
 beqz       $at, .Lvlc_730
  andi      $v1, $v1, 0xF
 lhu        $t1, 0x0($a0)
 addi       $a0, $a0, 0x2
 sllv       $t1, $t1, $v1
 or         $v0, $v0, $t1
.Lvlc_730:
 or         $t0, $t4, $t0
 sh         $t0, 0x0($a1)
.Lvlc_738:
 subu       $at, $a1, $t6
 bgez       $at, .Lvlc_880
  addi      $a1, $a1, 0x2
.Lvlc_744:
 srl        $t0, $v0, 19
 sll        $t0, $t0, 3
 add        $t0, $t0, $a2
 lw         $t1, 0x0($t0)
 nop
 bnez       $t1, .Lvlc_7A0
  andi      $at, $t1, 0xFF
 sll        $v0, $v0, 8
 addi       $v1, $v1, 0x8
 andi       $at, $v1, 0x10
 beqz       $at, .Lvlc_784
  andi      $v1, $v1, 0xF
 lhu        $t0, 0x0($a0)
 addi       $a0, $a0, 0x2
 sllv       $t0, $t0, $v1
 or         $v0, $v0, $t0
.Lvlc_784:
 srl        $t0, $v0, 23
 sll        $t0, $t0, 2
 add        $t0, $t0, $a3
 lw         $t1, 0x0($t0)
 add        $t3, $zero, $zero
 bgez       $zero, .Lvlc_7A4
  andi      $at, $t1, 0xFF
.Lvlc_7A0:
 lw         $t3, 0x4($t0)
.Lvlc_7A4:
 sllv       $v0, $v0, $at
 add        $v1, $v1, $at
 andi       $at, $v1, 0x10
 beqz       $at, .Lvlc_7C8
  andi      $v1, $v1, 0xF
 lhu        $t0, 0x0($a0)
 addi       $a0, $a0, 0x2
 sllv       $t0, $t0, $v1
 or         $v0, $v0, $t0
.Lvlc_7C8:
 srl        $t1, $t1, 16
 xori       $at, $t1, 0x7C1F
 beqz       $at, .Lvlc_828
  xori      $at, $t1, 0xFE00
 beqz       $at, .Lvlc_628
  sh        $t1, 0x0($a1)
 beqz       $t3, .Lvlc_744
  addi      $a1, $a1, 0x2
 andi       $t2, $t3, 0xFFFF
 xori       $at, $t2, 0x7C1F
 beqz       $at, .Lvlc_828
  xori      $at, $t2, 0xFE00
 beqz       $at, .Lvlc_628
  sh        $t2, 0x0($a1)
 srl        $t2, $t3, 16
 beqz       $t2, .Lvlc_744
  addi      $a1, $a1, 0x2
 xori       $at, $t2, 0x7C1F
 beqz       $at, .Lvlc_828
  xori      $at, $t2, 0xFE00
 beqz       $at, .Lvlc_628
  sh        $t2, 0x0($a1)
 bgez       $zero, .Lvlc_744
  addi      $a1, $a1, 0x2
.Lvlc_828:
 srl        $t0, $v0, 16
 sh         $t0, 0x0($a1)
 addi       $a1, $a1, 0x2
 lhu        $t0, 0x0($a0)
 addi       $a0, $a0, 0x2
 sll        $v0, $v0, 16
 sllv       $t0, $t0, $v1
 bgez       $zero, .Lvlc_744
  or        $v0, $v0, $t0
.Lvlc_84C:
 ori        $t0, $zero, 0xFE00
 addi       $v0, $zero, 0x40
.Lvlc_854:
 sh         $t0, 0x0($a1)
 addi       $a1, $a1, 0x2
 bnez       $v0, .Lvlc_854
  addi      $v0, $v0, -0x1
 mfc0       $t1, $12
 nop
 lui        $at, (0x20000 >> 16)
 or         $t1, $t1, $at
 mtc0       $t1, $12
 jr         $ra
  add       $v0, $zero, $zero
.Lvlc_880:
 lui        $t0, %hi(vlc_saved_registers)
 addiu      $t0, $t0, %lo(vlc_saved_registers)
 sw         $a0, 0x0($t0)
 sw         $a1, 0x4($t0)
 sw         $v0, 0x8($t0)
 sw         $v1, 0xC($t0)
 sw         $t4, 0x10($t0)
 sw         $t5, 0x14($t0)
 sw         $t7, 0x18($t0)
 sw         $t8, 0x1C($t0)
 sw         $t9, 0x20($t0)
 jr         $ra
  addi      $v0, $zero, 0x1
glabel vlc_saved_registers
 nop
 nop
 nop
 nop
 nop
 nop
 nop
 nop
 nop
.size DecDCTvlc, . - DecDCTvlc
