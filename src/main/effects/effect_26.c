// EffectObj, effect_object_update_funcs[26]
// 800BB1F0..800BB9B8
#include "common.h"

INCLUDE_ASM("main/nonmatchings/effects/effect_26", func_800BB1F0);

void func_800BB314(struct EffectObj* arg0)
{
    s8 temp_v0;

    temp_v0 = arg0->ext.unk_effect.unk16 - 1;
    arg0->ext.unk_effect.unk16 = temp_v0;
    if (temp_v0 == 0) {
        arg0->ext.unk_effect.unk16 = 4;
        func_800AF95C(OBJECT_HEADER(arg0), 1, 0x60, 0x60, 2);
    }
}

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

void func_800BB5F4(struct EffectObj* arg0)
{
    struct QuadObj* quad;
    u16 timer;

    timer = arg0->ext.effect_26_timer;
    if (timer != 0) {
        arg0->ext.effect_26_timer = timer - 1;
        func_800BB314(arg0);
        func_800BB508(arg0);
        return;
    }
    arg0->state++;
    quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = 1;
        quad->id = 8;
        quad->x_pos.i.hi = arg0->x_pos.i.hi;
        quad->y_pos.i.hi = arg0->y_pos.i.hi;
    }
    arg0->ext.effect_26_timer = 10;
}

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
