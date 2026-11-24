.set noat
.set noreorder

 lui        $v0, (0x1F800124 >> 16)
 lw         $v0, (0x1F800124 & 0xFFFF)($v0)
 addiu      $sp, $sp, -0x70
 sw         $s5, 0x5C($sp)
 addu       $s5, $a0, $zero
 sw         $ra, 0x6C($sp)
 sw         $fp, 0x68($sp)
 sw         $s7, 0x64($sp)
 sw         $s6, 0x60($sp)
 sw         $s4, 0x58($sp)
 sw         $s3, 0x54($sp)
 sw         $s2, 0x50($sp)
 sw         $s1, 0x4C($sp)
 slti       $v0, $v0, 0x3E8
 beqz       $v0, .L800248EC
  sw        $s0, 0x48($sp)
 lb         $v1, 0x14($s5)
 nop
 bgez       $v1, .L8002439C
  sll       $v0, $v1, 2
 lhu        $t6, 0xA($s5)
 nop
 sh         $t6, 0x30($sp)
 lhu        $t6, 0xE($s5)
 j          .L800243DC
  sh        $t6, 0x38($sp)
.L8002439C:
 addu       $v0, $v0, $v1
 sll        $v0, $v0, 2
 addu       $v0, $v0, $v1
 sll        $v0, $v0, 2
 lhu        $a1, 0xA($s5)
 lui        $at, %hi(background_objects + 0xA)
 addu       $at, $at, $v0
 lhu        $v1, %lo(background_objects + 0xA)($at)
 lhu        $a0, 0xE($s5)
 lui        $at, %hi(background_objects + 0xE)
 addu       $at, $at, $v0
 lhu        $v0, %lo(background_objects + 0xE)($at)
 subu       $a1, $a1, $v1
 subu       $a0, $a0, $v0
 sh         $a1, 0x30($sp)
 sh         $a0, 0x38($sp)
.L800243DC:
 lui        $s4, (0x1F800100 >> 16)
 lw         $s4, (0x1F800100 & 0xFFFF)($s4)
 lui        $s6, (0x1F800104 >> 16)
 lw         $s6, (0x1F800104 & 0xFFFF)($s6)
 lbu        $v0, 0x47($s5)
 lw         $a0, 0x3C($s5)
 sll        $v0, $v0, 2
 addu       $v0, $a0, $v0
 lhu        $v1, 0x2($v0)
 lhu        $v0, 0x0($v0)
 sll        $v1, $v1, 2
 addu       $a0, $a0, $v1
 sw         $v0, 0x40($sp)
 sw         $a0, 0x10($sp)
 lbu        $t6, 0x15($s5)
 nop
 sb         $t6, 0x18($sp)
 lhu        $t6, 0x40($s5)
 nop
 sh         $t6, 0x20($sp)
 lhu        $t6, 0x42($s5)
 beqz       $v0, .L80024874
  sh        $t6, 0x28($sp)
 lui        $s7, (0xFFFFFF >> 16)
 ori        $s7, $s7, (0xFFFFFF & 0xFFFF)
 addiu      $fp, $a0, 0x1
 addiu      $s3, $s6, 0x8
 addiu      $s0, $s4, 0x25
.L8002444C:
 lui        $a0, (0x1F800124 >> 16)
 ori        $a0, $a0, (0x1F800124 & 0xFFFF)
 lw         $v1, 0x0($a0)
 nop
 slti       $v0, $v1, 0x3E8
 beqz       $v0, .L800248EC
  addiu     $v0, $v1, 0x1
 sw         $v0, 0x0($a0)
 lbu        $v0, 0x1($fp)
 lw         $t6, 0x10($sp)
 sll        $v0, $v0, 24
 lbu        $t4, 0x0($t6)
 lbu        $t6, 0x18($sp)
 nop
 bnez       $t6, .L80024494
  sra       $t1, $v0, 24
 j          .L800244A0
  addiu     $a3, $t1, 0x10
.L80024494:
 negu       $a3, $t1
 addiu      $v0, $t1, 0x10
 negu       $t1, $v0
.L800244A0:
 andi       $v0, $t4, 0x3
 sll        $v0, $v0, 8
 lhu        $t6, 0x30($sp)
 lbu        $a0, 0x2($fp)
 lbu        $v1, 0x0($fp)
 lbu        $a2, 0x0($s5)
 addu       $t1, $t1, $t6
 addu       $a3, $a3, $t6
 sll        $a0, $a0, 24
 sra        $a0, $a0, 24
 or         $v1, $v1, $v0
 lhu        $t6, 0x38($sp)
 andi       $v0, $a2, 0x40
 addu       $a0, $t6, $a0
 addiu      $t3, $a0, 0x10
 lhu        $t6, 0x20($sp)
 addu       $t5, $a0, $zero
 beqz       $v0, .L8002452C
  addu      $s2, $t6, $v1
 andi       $a1, $s2, 0xFFFF
 lui        $v0, (0xBA2E8BA3 >> 16)
 ori        $v0, $v0, (0xBA2E8BA3 & 0xFFFF)
 multu      $a1, $v0
 mfhi       $t6
 srl        $v1, $t6, 7
 andi       $a0, $v1, 0xFFFF
 sll        $a0, $a0, 8
 sll        $v0, $v1, 1
 addu       $v0, $v0, $v1
 sll        $v0, $v0, 2
 subu       $v0, $v0, $v1
 sll        $v0, $v0, 4
 subu       $a1, $a1, $v0
 addu       $a0, $a0, $a1
 addiu      $s2, $a0, 0x600
.L8002452C:
 andi       $v0, $a2, 0x20
 beqz       $v0, .L8002456C
  andi      $a1, $s2, 0xFFFF
 lui        $v0, (0xCCCCCCCD >> 16)
 ori        $v0, $v0, (0xCCCCCCCD & 0xFFFF)
 multu      $a1, $v0
 mfhi       $t6
 srl        $v1, $t6, 6
 andi       $a0, $v1, 0xFFFF
 sll        $a0, $a0, 8
 sll        $v0, $v1, 2
 addu       $v0, $v0, $v1
 sll        $v0, $v0, 4
 subu       $a1, $a1, $v0
 addu       $a0, $a0, $a1
 addiu      $s2, $a0, 0x5B0
.L8002456C:
 lhu        $t6, 0x28($sp)
 nop
 andi       $v0, $t6, 0x8000
 beqz       $v0, .L80024588
  andi      $v0, $t4, 0xC
 j          .L800245A0
  addiu     $t2, $zero, 0x7840
.L80024588:
 srl        $v0, $v0, 2
 addu       $v1, $t6, $v0
 andi       $v0, $v1, 0x30
 beqz       $v0, .L800245A0
  addu      $t2, $v1, $zero
 addiu      $t2, $v1, 0x30
.L800245A0:
 andi       $v0, $t4, 0x80
 bnez       $v0, .L800246F4
  addiu     $v0, $zero, 0x9
 lbu        $t6, 0x18($sp)
 andi       $v0, $t4, 0x40
 xor        $v0, $v0, $t6
 bnez       $v0, .L80024674
  andi      $t0, $s2, 0xF0
 addiu      $v0, $zero, 0x3
 sb         $v0, -0x22($s0)
 addiu      $v0, $zero, 0x7D
 sb         $v0, -0x1E($s0)
 lbu        $v0, 0x0($s5)
 nop
 andi       $v0, $v0, 0x10
 beqz       $v0, .L800245EC
  addu      $s1, $s4, $zero
 j          .L800245F0
  addiu     $v0, $zero, 0x7F
.L800245EC:
 addiu      $v0, $zero, 0x7D
.L800245F0:
 sb         $v0, -0x1E($s0)
 sll        $a1, $s2, 4
 sh         $t2, 0xE($s1)
 sh         $t1, 0x8($s1)
 sh         $t5, 0xA($s1)
 sb         $a1, 0xC($s1)
 sb         $t0, 0xD($s1)
 addiu      $t6, $zero, 0x1
 jal        GetGraphType
  sb        $t6, -0x5($s3)
 addiu      $t6, $zero, 0x1
 beq        $v0, $t6, .L80024630
  lui       $v1, (0xE1000020 >> 16)
 jal        GetGraphType
  nop
 lui        $v1, (0xE1000020 >> 16)
.L80024630:
 ori        $v1, $v1, (0xE1000020 & 0xFFFF)
 andi       $v0, $s2, 0xFFFF
 srl        $v0, $v0, 8
 or         $v0, $v0, $v1
 lui        $t6, (0xFF000000 >> 16)
 sw         $v0, -0x4($s3)
 lw         $v0, 0x0($s6)
 and        $v1, $s1, $s7
 and        $v0, $v0, $t6
 or         $v0, $v0, $v1
 sw         $v0, 0x0($s6)
 lw         $v0, 0x0($s1)
 and        $v1, $s3, $s7
 and        $v0, $v0, $t6
 or         $v0, $v0, $v1
 j          .L80024844
  sw        $v0, 0x0($s1)
.L80024674:
 addiu      $v0, $zero, 0x9
 sb         $v0, -0x22($s0)
 addiu      $v0, $zero, 0x2D
 sb         $v0, -0x1E($s0)
 lbu        $v0, 0x0($s5)
 nop
 andi       $v0, $v0, 0x10
 bnez       $v0, .L8002469C
  addiu     $v0, $zero, 0x2F
 addiu      $v0, $zero, 0x2D
.L8002469C:
 sb         $v0, -0x1E($s0)
 sll        $v0, $s2, 4
 addiu      $a0, $v0, -0x1
 ori        $a1, $v0, 0xF
 andi       $v1, $s2, 0xFFFF
 srl        $v1, $v1, 8
 ori        $v1, $v1, 0x20
 sh         $v1, -0xF($s0)
 addu       $v1, $v0, $zero
 andi       $v0, $a0, 0xFF
 addiu      $t6, $zero, 0xFF
 bne        $v0, $t6, .L800246D8
  sh        $t2, -0x17($s0)
 addu       $a0, $v1, $zero
 addiu      $a3, $a3, -0x1
.L800246D8:
 addiu      $a2, $t0, 0x10
 andi       $v0, $a2, 0xFF
 bnez       $v0, .L800247B0
  addiu     $v0, $zero, 0x1
 addiu      $a2, $t0, 0xF
 j          .L800247B0
  addiu     $t3, $t3, -0x1
.L800246F4:
 sb         $v0, -0x22($s0)
 addiu      $v0, $zero, 0x2D
 sb         $v0, -0x1E($s0)
 lbu        $v0, 0x0($s5)
 nop
 andi       $v0, $v0, 0x10
 bnez       $v0, .L80024718
  addiu     $v0, $zero, 0x2F
 addiu      $v0, $zero, 0x2D
.L80024718:
 sb         $v0, -0x1E($s0)
 addu       $a0, $s2, $zero
 andi       $v0, $a0, 0xF0
 addiu      $a2, $v0, -0x1
 ori        $t0, $v0, 0xF
 andi       $v1, $s2, 0xFFFF
 srl        $v1, $v1, 8
 ori        $v1, $v1, 0x20
 sh         $v1, -0xF($s0)
 addu       $v1, $v0, $zero
 andi       $v0, $a2, 0xFF
 addiu      $t6, $zero, 0xFF
 bne        $v0, $t6, .L80024758
  sh        $t2, -0x17($s0)
 addu       $a2, $v1, $zero
 addiu      $t3, $t3, -0x1
.L80024758:
 lbu        $t6, 0x18($sp)
 andi       $v0, $t4, 0x40
 xor        $v0, $v0, $t6
 bnez       $v0, .L80024788
  sll       $v0, $a0, 4
 sll        $v1, $a0, 4
 addiu      $a0, $v1, 0x10
 andi       $v0, $a0, 0xFF
 bnez       $v0, .L800247AC
  addu      $a1, $v1, $zero
 j          .L800247A8
  ori       $a0, $v1, 0xF
.L80024788:
 addiu      $a0, $v0, -0x1
 ori        $a1, $v0, 0xF
 addu       $v1, $v0, $zero
 andi       $v0, $a0, 0xFF
 addiu      $t6, $zero, 0xFF
 bne        $v0, $t6, .L800247B0
  addiu     $v0, $zero, 0x1
 addu       $a0, $v1, $zero
.L800247A8:
 addiu      $a3, $a3, -0x1
.L800247AC:
 addiu      $v0, $zero, 0x1
.L800247B0:
 sh         $t1, -0x1D($s0)
 sh         $t5, -0x1B($s0)
 sh         $a3, -0x15($s0)
 sh         $t5, -0x13($s0)
 sh         $t1, -0xD($s0)
 sh         $t3, -0xB($s0)
 sh         $a3, -0x5($s0)
 sh         $t3, -0x3($s0)
 sb         $a1, -0x19($s0)
 sb         $t0, -0x18($s0)
 sb         $a0, -0x11($s0)
 sb         $t0, -0x10($s0)
 sb         $a1, -0x9($s0)
 sb         $a2, -0x8($s0)
 sb         $a0, -0x1($s0)
 sb         $a2, 0x0($s0)
 jal        GetGraphType
  sb        $v0, -0x5($s3)
 addiu      $t6, $zero, 0x1
 beq        $v0, $t6, .L80024810
  lui       $v0, (0xE1000020 >> 16)
 jal        GetGraphType
  nop
 lui        $v0, (0xE1000020 >> 16)
.L80024810:
 ori        $v0, $v0, (0xE1000020 & 0xFFFF)
 lui        $t6, (0xFF000000 >> 16)
 sw         $v0, -0x4($s3)
 lw         $v0, 0x0($s6)
 and        $v1, $s4, $s7
 and        $v0, $v0, $t6
 or         $v0, $v0, $v1
 sw         $v0, 0x0($s6)
 lw         $v0, 0x0($s4)
 and        $v1, $s3, $s7
 and        $v0, $v0, $t6
 or         $v0, $v0, $v1
 sw         $v0, 0x0($s4)
.L80024844:
 addiu      $s0, $s0, 0x28
 addiu      $s4, $s4, 0x28
 addiu      $s3, $s3, 0x8
 lw         $t6, 0x10($sp)
 addiu      $s6, $s6, 0x8
 addiu      $t6, $t6, 0x4
 sw         $t6, 0x10($sp)
 lw         $t6, 0x40($sp)
 addiu      $fp, $fp, 0x4
 addiu      $t6, $t6, -0x1
 bnez       $t6, .L8002444C
  sw        $t6, 0x40($sp)
.L80024874:
 lui        $a3, (0x1F800104 >> 16)
 ori        $a3, $a3, (0x1F800104 & 0xFFFF)
 lui        $t0, (0xFFFFFF >> 16)
 lui        $v0, %hi(D_8013BC40)
 addiu      $v0, $v0, %lo(D_8013BC40)
 ori        $t0, $t0, (0xFFFFFF & 0xFFFF)
 lui        $v1, (0x1F800000 >> 16)
 lw         $v1, (0x1F800000 & 0xFFFF)($v1)
 lbu        $a0, 0x16($s5)
 lui        $a1, (0xFF000000 >> 16)
 lui        $at, (0x1F800100 >> 16)
 sw         $s4, (0x1F800100 & 0xFFFF)($at)
 sll        $v1, $v1, 7
 addu       $v1, $v1, $v0
 srl        $v0, $a0, 4
 sll        $v0, $v0, 5
 addu       $v0, $v0, $v1
 andi       $a0, $a0, 0xF
 sll        $a0, $a0, 2
 addu       $a0, $a0, $v0
 lw         $a2, 0x0($a0)
 lw         $v0, 0x0($a3)
 lw         $v1, 0x0($a2)
 and        $v0, $v0, $t0
 and        $v1, $v1, $a1
 or         $v1, $v1, $v0
 addiu      $v0, $s4, -0x28
 sw         $v1, 0x0($a2)
 sw         $v0, 0x0($a0)
 sw         $s6, 0x0($a3)
.L800248EC:
 lw         $ra, 0x6C($sp)
 lw         $fp, 0x68($sp)
 lw         $s7, 0x64($sp)
 lw         $s6, 0x60($sp)
 lw         $s5, 0x5C($sp)
 lw         $s4, 0x58($sp)
 lw         $s3, 0x54($sp)
 lw         $s2, 0x50($sp)
 lw         $s1, 0x4C($sp)
 lw         $s0, 0x48($sp)
 addiu      $sp, $sp, 0x70
 jr         $ra
  nop
