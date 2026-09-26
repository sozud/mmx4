// WeaponObj, weapon_object_update_funcs[60]
// 80098F4C..800992FC
#include "common.h"

void func_80098F4C(struct WeaponObj* arg0)
{
    D_80108C00[arg0->state](arg0);
}

void func_80098F88(struct WeaponObj* arg0)
{
    s8 temp_v1;
    s16* table;
    u16 var_a0;
    u32 var_a2;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk50 = D_80108BF0;
    var_a0 = (u16)*D_80108BF4[arg0->unk2];
    table = &D_80108BF4[0][0];
    if (arg0->unk15 != 0)
        var_a0 = -var_a0;
    arg0->x_pos.i.hi = (u16)arg0->x_pos.i.hi + var_a0;
    arg0->y_pos.i.hi = (u16)arg0->y_pos.i.hi
        + (u16) * ((u16*)((u32)table - -((u32)(s32)arg0->unk2 << 2) + 2));

    temp_v1 = arg0->unk2;
    switch (temp_v1) {
    case 0:
        var_a2 = (arg0->unk15 == 0) << 4;
        break;
    case 1:
        var_a2 = 0x1C;
        if (arg0->unk15 == 0)
            var_a2 = 0x14;
        break;
    case 2:
        var_a2 = 4;
        if (arg0->unk15 == 0)
            var_a2 = 0xC;
        break;
    }
    arg0->ext.weapon_60.direction = var_a2;
    func_8002B93C(MOVING_OBJECT(arg0), var_a2 & 0xFF);
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->unk88.half = 8;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    *(s16*)arg0->pad8A = 1;
    arg0->ext.target = NULL;
    arg0->unk84.word = 0;
    arg0->x_vel.val *= 6;
    arg0->y_vel.val *= 6;
    func_80015D60(arg0, 0x21);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_60", func_80099118);

void func_800992C4(struct WeaponObj* arg0)
{
    struct PlayerObj* temp_a2;

    temp_a2 = arg0->owner;
    temp_a2->input.bytes.previous_high ^= 1 << arg0->unk2;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 D_80108BF0[4] = { 0xFC, 0xFD, 6, 5 };

s16 D_80108BF4[3][2] = {
    { -0x28, 0 },
    { -0x28, 0 },
    { -0x28, 0 },
};

void (*D_80108C00[])(struct WeaponObj*) = {
    func_80098F88,
    func_80099118,
    func_800992C4,
};
