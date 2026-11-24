.set noat
.set noreorder

.text
.globl _patch_gte
.ent _patch_gte
_patch_gte:
    lui     $at, %hi(D_8012F41C)
    sw      $ra, %lo(D_8012F41C)($at)
    jal     EnterCriticalSection
    nop
    addiu   $t2, $zero, 0xB0
    jalr    $t2
    addiu   $t1, $zero, 0x56
    lui     $t2, %hi(patch_start)
    lui     $t1, %hi(patch_end)
    lw      $v0, 0x18($v0)
    addiu   $t2, $t2, %lo(patch_start)
    addiu   $t1, $t1, %lo(patch_end)
1:  lw      $v1, 0x0($t2)
    addiu   $t2, $t2, 0x4
    addiu   $v0, $v0, 0x4
    bne     $t2, $t1, 1b
    sw      $v1, -0x4($v0)
    jal     FlushCache
    nop
    jal     ExitCriticalSection
    nop
    lui     $ra, %hi(D_8012F41C)
    lw      $ra, %lo(D_8012F41C)($ra)
    nop
    jr      $ra
    nop

patch_start:
    nop
    nop
    addiu   $k0, $zero, 0x100
    lw      $k0, 0x8($k0)
    nop
    lw      $k0, 0x0($k0)
    nop
    addi    $k0, $k0, 0x8
    sw      $at, 0x4($k0)
    sw      $v0, 0x8($k0)
    sw      $v1, 0xC($k0)
    sw      $ra, 0x7C($k0)
    mfc0    $v0, $13
    nop
patch_end:
    .end _patch_gte

