// MainObj, main_object_update_funcs[47]
// 80066DAC..80067350
#include "common.h"

extern u16 train_boss_armor_smoke_offsets[3][2];
#include "func_tables.h"

void train_boss_armor_update(struct MainObj* self)
{
    train_boss_armor_state_funcs[self->state](self);
}

// train_boss_armor_init
INCLUDE_ASM("main/nonmatchings/mains/main_47_train_boss_armor", func_80066DE8);

// train_boss_armor_main
INCLUDE_ASM("main/nonmatchings/mains/main_47_train_boss_armor", func_80066F1C);

void train_boss_armor_smoke(struct MainObj* self)
{
    s32 tableIndex;
    s32 x;
    s32 y;
    s32 frameArea[2];

    if (--self->unk7C == 0) {
        self->state = 3;
        return;
    }

    if (--self->unk7E == 0) {
        tableIndex = self->unk2;
        y = (u16)self->ext.main_47.unk80->x_pos.i.hi + train_boss_armor_smoke_offsets[tableIndex][0];
        x = (u16)self->y_pos.i.hi + train_boss_armor_smoke_offsets[tableIndex][1];
        func_800B10E4(0x11, (s16)(y - 6), (s16)(x - 6),
            (s16)(y + 6), (s16)(x + 6), 1);
        self->unk7E = 10;
    }
}

void train_boss_armor_clear(struct MainObj* self)
{
    self->ext.main_47.unk80 = 0;
    self->ext.main_47.unk84 = 0;
    self->ext.main_47.unk88 = 0;
    self->ext.main_47.unk8C = 0;
    self->ext.main_47.unk90 = 0;
    self->ext.main_47.unk94 = 0;
}

void train_boss_armor_start_idle(struct MainObj* self)
{
    self->unk5 = 2;
    self->unk6 = 1;
}

void train_boss_armor_arrive(struct MainObj* self)
{
    if (self->unk6 == 0) {
        if (self->x_pos.i.hi >= 0x1AA1) {
            self->unk6 = 1;
            return;
        }
        move_object(MOVING_OBJECT(self));
        return;
    }
    self->unk42 &= 0x7FFF;
}

s8 train_boss_armor_hurt_boxes[3][16] = {
    { -47, -72, 29, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { -31, -39, 17, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { -31, -6, 17, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

u16 train_boss_armor_smoke_offsets[3][2] = { { -30, -61 }, { -24, -26 }, { -23, 8 } };

u8 D_800FF9FC[4] = { 1, 2, 4, 0 };

u8 D_800FFA00[4] = { 0x10, 0x20, 0x40, 0 };

u8 D_800FFA04[8] = { 11, 12, 11, 12, 11, 12, 0, 0 };

void (*train_boss_armor_state_funcs[])(struct MainObj*) = {
    func_80066DE8,
    func_80066F1C,
    train_boss_armor_smoke,
    train_boss_armor_clear,
};

void (*train_boss_armor_step_funcs[3])() = { enemy_hit_reaction, train_boss_armor_start_idle, train_boss_armor_arrive };
