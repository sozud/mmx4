// EffectObj, effect_object_update_funcs[6]
// 800B6A0C..800B6B18
#include "common.h"

void func_800B6A0C(struct EffectObj* arg0)
{
    D_8010B45C[arg0->state](arg0);
}

void func_800B6A48(struct EffectObj* arg0)
{
    arg0->ext.unk_effect.unk14 = 0;
    arg0->state++;
    if ((arg0->unk2 & 0xF) == engine_obj.checkpoint) {
        func_8002B0C8(arg0);
    }
}

void func_800B6A90(struct EffectObj* arg0)
{
    if (func_8002B160(arg0) == 0) {
        if (arg0->unk2 & 0xF0) {
            if (arg0->y_pos.i.hi <= g_Player.base.y_pos.i.hi) {
                engine_obj.checkpoint = arg0->unk2 & 0xF;
                func_8002B0C8(arg0);
            }
        } else {
            if (arg0->x_pos.i.hi <= g_Player.base.x_pos.i.hi) {
                engine_obj.checkpoint = arg0->unk2 & 0xF;
                func_8002B0C8(arg0);
            }
        }
    } else {
        func_8002B0C8(arg0);
    }
}

void (*D_8010B45C[])(struct EffectObj*) = {
    func_800B6A48,
    func_800B6A90,
};
