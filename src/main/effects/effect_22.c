// EffectObj, effect_object_update_funcs[22]
// 800BA57C..800BAA30
#include "common.h"

void func_800BA57C(struct EffectObj* arg0)
{
    D_8010BE24[arg0->state](arg0);
}

void func_800BA5B8(struct EffectObj* arg0)
{
    arg0->unk5 = 2;
    arg0->ext.effect_22.unk14 = 5;
    arg0->state++;
    func_800BA5F0(arg0);
}

void func_800BA5F0(struct EffectObj* arg0)
{
    arg0->ext.effect_22.unk15 = arg0->ext.effect_22.unk14;
    func_800BA9C0(arg0);
    D_8010BE2C[arg0->unk5](arg0);
}

void func_800BA644(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BA684(arg0);
    } else {
        func_800BA6AC(arg0);
    }
}

void func_800BA684(struct EffectObj* arg0)
{
    arg0->unk6++;
    background_objects[0].unk4 = 2;
    arg0->ext.effect_22.unk16 = 0;
    arg0->ext.effect_22.unk18 = 0;
}

void func_800BA6AC(struct EffectObj* arg0)
{
    s16 diff;
    s8 sum;
    s32 t;

    if (background_objects[0].unk14.val != background_objects[0].x_pos.val) {
        diff = background_objects[0].x_pos.i.hi - background_objects[0].unk14.i.hi;
        arg0->ext.effect_22.unk18 = diff;
        if (diff >= 0) {
            if (diff >= 8) {
                arg0->ext.effect_22.unk18 = 8;
            }
        } else {
            if (diff < -8) {
                arg0->ext.effect_22.unk18 = -8;
            }
        }

        sum = arg0->ext.effect_22.unk17 + arg0->ext.effect_22.unk18;
        arg0->ext.effect_22.unk17 = sum;
        if ((s8)sum >= 0) {
            if ((s8)sum < 8) {
                return;
            }
            if (++arg0->ext.effect_22.unk16 >= 3) {
                arg0->ext.effect_22.unk16 = 0;
            }
        } else {
            if ((s8)sum >= -7) {
                return;
            }
            if (--arg0->ext.effect_22.unk16 < 0) {
                arg0->ext.effect_22.unk16 = 2;
            }
        }
        t = arg0->ext.effect_22.unk16;
        background_objects[1].unk4C = 1;
        background_objects[1].x_pos.i.hi = t << 9;
        arg0->ext.effect_22.unk17 = 0;
    }
}

void func_800BA7C8(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BA808(arg0);
    } else {
        func_800BA81C(arg0);
    }
}

void func_800BA808(struct EffectObj* arg0)
{
    arg0->unk6++;
}

void func_800BA81C(struct EffectObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void func_800BA82C(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BA86C(arg0);
    } else {
        func_800BA898(arg0);
    }
}

void func_800BA86C(struct EffectObj* arg0)
{
    background_objects[1].unk4 = 1;
    background_objects[2].unk4 = 3;
    arg0->unk6++;
}

void func_800BA898(struct EffectObj* arg0)
{
    if (g_Player.x_pos.i.hi >= 0xFE0) {
        engine_obj.checkpoint = 2;
        engine_obj.unkF = -0x40;
    }
}

void func_800BA8CC(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BA90C(arg0);
    } else {
        func_800BA938(arg0);
    }
}

void func_800BA90C(struct EffectObj* arg0)
{
    background_objects[1].unk4 = 1;
    background_objects[2].unk4 = 3;
    arg0->unk6++;
}

void func_800BA938(struct EffectObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void func_800BA948(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BA988(arg0);
    } else {
        func_800BA9A8(arg0);
    }
}

void func_800BA988(struct EffectObj* arg0)
{
    background_objects[1].unk4 = 1;
    arg0->unk6++;
}

void func_800BA9A8(struct EffectObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void func_800BA9B8(struct EffectObj* arg0)
{
}

void func_800BA9C0(struct EffectObj* arg0)
{
    s16 player_x = g_Player.x_pos.i.hi;
    s8 offset = 0;
    while (1) {
        if (player_x - D_8010BE1C[offset] < 0) {
            break;
        }
        offset++;
        if (offset >= 3) {
            break;
        }
    }
    arg0->ext.effect_22.unk14 = offset;
    if (offset != arg0->ext.effect_22.unk15) {
        arg0->unk5 = offset;
        arg0->unk6 = 0;
    }
}

s16 D_8010BE1C[4] = { 0x0960, 0x0A08, 0x1700, 0 };

void (*D_8010BE24[])(struct EffectObj*) = {
    func_800BA5B8,
    func_800BA5F0,
};

void (*D_8010BE2C[6])(struct EffectObj*) = {
    func_800BA644,
    func_800BA7C8,
    func_800BA82C,
    func_800BA8CC,
    func_800BA948,
    func_800BA9B8,
};

u8 D_8010BE44[3][4] = {
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 0xFE, 3 },
};

u8 D_8010BE50[3][4] = {
    { 2, 0, 1, 4 },
    { 2, 0, 1, 5 },
    { 2, 0, 0xFE, 6 },
};

u8* D_8010BE5C[2] = { D_8010BE44[0], D_8010BE50[0] };
