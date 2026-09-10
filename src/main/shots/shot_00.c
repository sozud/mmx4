// ShotObj, shot_object_update_funcs[0]
// 800994A0..80099B30
#include "common.h"

u8 D_80108C44[4] = { 0xB4, 0x1B, 0x52, 0x31 };
u8 D_80108C48[4] = { 0x9E, 0xAE, 0x2C, 0x72 };
u8 D_80108C4C[4] = { 0x24, 0xF4, 0x32, 0x52 };
u8 D_80108C50[4] = { 0x2B, 0x15, 0x29, 0x40 };
u8 D_80108C54[4] = { 0xF3, 0xF3, 0x1A, 0x18 };
u8 D_80108C58[4] = { 0xF3, 0xF3, 0x1A, 0x18 };
u8 D_80108C5C[4] = { 0x20, 0xA7, 0x20, 0x10 };
u8 D_80108C60[4] = { 0x00, 0x00, 0x00, 0x00 };
u8 D_80108C64[4] = { 0x01, 0xFE, 0x09, 0x09 };
u8 D_80108C68[4] = { 0xC1, 0x0B, 0x32, 0x40 };
u8 D_80108C6C[4] = { 0x25, 0x08, 0x32, 0x40 };
u8 D_80108C70[4] = { 0x1A, 0x95, 0x27, 0x23 };

void func_800994A0(struct ShotObj* arg0)
{
    D_80108C74[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_00", func_800994DC);

void func_80099784(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;

    weapon = arg0->unk7C;
    arg0->x_pos.val = weapon->x_pos.val;
    arg0->y_pos.val = weapon->y_pos.val;
    arg0->unk42 = weapon->unk42;
    func_80015DC8(arg0);
    func_8002B318((struct BaseObj*)arg0, 0x5A, 0x5A);
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->state = 4;
    }
    func_8002D9BC(arg0);
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk50.data = D_80108C48;
        func_8002D9BC(arg0);
        arg0->unk50.data = D_80108C44;
    }
}

void func_8009982C(struct ShotObj* arg0)
{
    struct WeaponObj* weapon;

    weapon = arg0->unk7C;
    arg0->x_pos.val = weapon->x_pos.val;
    arg0->y_pos.val = weapon->y_pos.val;
    arg0->unk42 = weapon->unk42;
    func_80015DC8(arg0);
    func_8002B318((struct BaseObj*)arg0, 0x5A, 0x5A);
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->state = 4;
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk50.data = D_80108C4C;
    } else {
        arg0->unk50.data = D_80108C50;
    }
    func_8002D9BC(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_00", func_800998D4);

void func_800999D0(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    func_8002D9BC(arg0);
    func_8002B318((struct BaseObj*)arg0, 0x19, 0x19);
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->state = 4;
        arg0->unk5 = 0;
    }
}

void func_80099A28(struct ShotObj* arg0)
{
    if (arg0->unk5 == 0) {
        func_800998D4(arg0);
    } else {
        func_800999D0(arg0);
    }

    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_00", func_80099A8C);

void func_80099B0C(struct ShotObj* arg0)
{
    arg0->unk7C->unk54 = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108C74[])(struct ShotObj*) = {
    func_800994DC,
    func_80099784,
    func_8009982C,
    func_80099A28,
    func_80099B0C,
    func_80099A8C,
};
