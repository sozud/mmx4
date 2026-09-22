// EffectObj, effect_object_update_funcs[13]
// 800B84DC..800B89B4
#include "common.h"

void func_800B84DC(struct EffectObj* arg0)
{
    D_8010B638[arg0->state](arg0);
}

void func_800B8518(struct EffectObj* arg0)
{
    arg0->ext.unk_effect.unk14 = 0;
    func_800B8630(arg0);
    arg0->ext.unk_effect.unk15 = 0;
    arg0->state++;
}

void func_800B8554(struct EffectObj* self)
{
    s16 pos;

    pos = self->x_pos.i.hi - 0x10;
    if (background_objects[0].x_pos.i.hi - 0x10 <= pos && background_objects[0].x_pos.i.hi + 0x150 >= pos) {
        pos = self->y_pos.i.hi;
        if (background_objects[0].y_pos.i.hi - 0x10 <= pos && background_objects[0].y_pos.i.hi + 0x100 >= pos) {
            func_800B875C(self, background_objects[0].x_pos.i.hi);
            self->ext.unk_effect.unk15++;
        }
    }

    if (self->ext.unk_effect.unk15 >= 0x1F) {
        self->state++;
    }
}

void func_800B8610(struct EffectObj* arg0)
{
    func_8002B108(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/effects/effect_13", func_800B8630);

INCLUDE_ASM("main/nonmatchings/effects/effect_13", func_800B875C);

INCLUDE_ASM("main/nonmatchings/effects/effect_13", func_800B887C);

void (*D_8010B638[])(struct EffectObj*) = {
    func_800B8518,
    func_800B8554,
    func_800B8610,
};

struct Effect14ItemSpawn D_8010B644[19] = {
    { 0, 0x1, 0x1550, 0x5b0 },
    { 0, 0x1, 0x1510, 0x5d0 },
    { 0, 0x1, 0x15a0, 0x600 },
    { 0, 0x1, 0x1560, 0x620 },
    { 0, 0x1, 0x14e0, 0x630 },
    { 0, 0x1, 0x15a0, 0x640 },
    { 0, 0x1, 0x1510, 0x680 },
    { 0, 0x1, 0x1580, 0x6b0 },
    { 0, 0x1, 0x14e0, 0x6e0 },
    { 0, 0x1, 0x15a0, 0x710 },
    { 0, 0x1, 0x1530, 0x730 },
    { 0, 0x1, 0x14e0, 0x780 },
    { 0, 0x1, 0x1510, 0x7a0 },
    { 0, 0x1, 0x1540, 0x7c0 },
    { 0, 0x1, 0x15a0, 0x820 },
    { 0, 0x1, 0x1520, 0x820 },
    { 0, 0x1, 0x14e0, 0x870 },
    { 0, 0x1, 0x1550, 0x8c0 },
    { 0, 0xff, 0x0, 0x0 },
};

u16 D_8010B6B6 = 0;
