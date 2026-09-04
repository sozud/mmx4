// EffectObj, effect_object_update_funcs[27]
// 800BB9B8..800BBC14
#include "common.h"

// megaman never teleports in if nopped out
// asm(".rept 13 ; nop ; .endr");
void TeleportRelatedObjectUpdate(struct EffectObj* arg0)
{
    D_8010BEC8[arg0->state]();
}

// D_8010BEC8 state 0
void func_800BB9F4(struct EffectObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->ext.unk_effect.unk14 = 0;
        arg0->ext.unk_effect.unk15 = 0;
        arg0->ext.unk_effect.unk16 = 0;
        arg0->state = 1;
        arg0->unk5 = 0;
    }
}

// D_8010BEC8 state 1
void func_800BBA24(struct EffectObj* arg0)
{
    struct QuadObj* quad;
    u32 var_i;

    switch (arg0->unk5) {
    case 0:
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 0x81;
            quad->id = 7;
            quad->unk2 = 0;
            quad->link.owner = arg0;
        }
        arg0->unk5 = 1;
        arg0->ext.unk_effect.unk14++;
        return;
    case 1:
        var_i = 0;
        // spawn blue quads behind "READY"
        if (arg0->ext.unk_effect.unk14 == 0) {
            arg0->ext.unk_effect.unk14 = 0;
            do {
                quad = find_free_quad_obj();
                if (quad != NULL) {
                    quad->active = 0x81;
                    quad->id = 7;
                    quad->unk2 = 1;
                    quad->unk7 = var_i;
                    quad->link.owner = arg0;
                    arg0->ext.unk_effect.unk14++;
                }
                var_i += 1;
            } while (var_i < 0xA);
            arg0->unk5 = 2;
            return;
        }
        return;
    case 2:
        var_i = 0;
        if (arg0->ext.unk_effect.unk14 == 0) {
            arg0->ext.unk_effect.unk14 = 0;
            do {
                quad = find_free_quad_obj();
                if (quad != NULL) {
                    quad->active = 0x81;
                    quad->id = 7;
                    quad->unk2 = 2;
                    quad->unk7 = get_random() & 3;
                    quad->link.owner = arg0;
                    arg0->ext.unk_effect.unk14++;
                }
                var_i += 1;
            } while (var_i < 8);
            arg0->unk5 = 3;
            return;
        }
        break;
    case 3:
        if (arg0->ext.unk_effect.unk14 == 0) {
            arg0->ext.unk_effect.unk14 = 0;
            arg0->ext.unk_effect.unk16 = 1;
        }
        break;
    }
}

// D_8010BEC8 state 2
INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_27", func_800BBBF4);

void (*D_8010BEC8[])(struct EffectObj*) = {
    func_800BB9F4,
    func_800BBA24,
    func_800BBBF4,
};
