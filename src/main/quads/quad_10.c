// QuadObj, quad_object_update_funcs[10]
// 800D6AD8..800D6F94
#include "common.h"

void func_800D6AD8(struct QuadObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    void* temp_a2 = arg0->unk5C;
    s32 var_a1 = 0;
    if (g_Player.unkC3 != 0) {
        var_a1 = 1;
    }
    if (g_Player.unkC4 != 0) {
        var_a1 = 1;
    }
    if (g_Player.unk93 != 6) {
        var_a1 = 1;
    }
    if (g_Player.unk5C == 0) {
        var_a1 = 1;
    }
    if (g_Player.unkBF != 0) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        ZeroObjectState(arg0);
        return;
    }
    D_8010FCB8[arg0->state](arg0, ptr, temp_a2);
}

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_10", func_800D6B9C);

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_10", func_800D6C48);

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_10", func_800D6CA0);

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_10", func_800D6D48);

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_10", func_800D6DC4);
