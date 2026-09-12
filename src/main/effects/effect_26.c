// EffectObj, effect_object_update_funcs[26]
// 800BB1F0..800BB9B8
#include "common.h"

INCLUDE_ASM("main/nonmatchings/effects/effect_26", func_800BB1F0);

INCLUDE_ASM("main/nonmatchings/effects/effect_26", func_800BB314);

INCLUDE_ASM("main/nonmatchings/effects/effect_26", func_800BB364);

void func_800BB508(struct EffectObj* arg0)
{
    struct QuadObj* quad;

    if (!(func_8002B780() & 1)) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 4;
            quad->unk2 = get_random() & 0x1F;
            quad->x_pos.u.hi = arg0->x_pos.u.hi;
            quad->y_pos.u.hi = arg0->y_pos.u.hi;
        }
    }
}

void func_800BB588(struct EffectObj* arg0)
{
    struct QuadObj* quad;

    if (!(get_random() & 3)) {
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 1;
            quad->id = 6;
            quad->x_pos.i.hi = arg0->x_pos.i.hi;
            quad->y_pos.i.hi = arg0->y_pos.i.hi;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_26", func_800BB5F4);

INCLUDE_ASM("main/nonmatchings/effects/effect_26", func_800BB68C);

INCLUDE_ASM("main/nonmatchings/effects/effect_26", func_800BB750);

void func_800BB85C(struct EffectObj* arg0)
{
    u16 timer;

    timer = arg0->ext.effect_26_timer;
    arg0->ext.effect_26_timer = timer - 1;
    if (timer == 0) {
        arg0->state = (u8)arg0->state + 1;
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_26", func_800BB888);

void func_800BB928(struct EffectObj* arg0)
{
    if (!(arg0->active & 0x80)) {
        func_80036B18();
    }
    engine_obj.unk1C = 1;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800BB97C(struct EffectObj* arg0)
{
    D_8010BEA8[arg0->state](arg0);
}

void (*D_8010BEA8[])(struct EffectObj*) = {
    func_800BB1F0,
    func_800BB364,
    func_800BB5F4,
    func_800BB68C,
    func_800BB750,
    func_800BB85C,
    func_800BB888,
    func_800BB928,
};
