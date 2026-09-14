// WeaponObj, weapon_object_update_funcs[10]
// 80093564..80093CBC
#include "common.h"

INCLUDE_ASM("main/nonmatchings/weapons/weapon_10", func_80093564);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_10", func_80093610);

void func_8009372C(struct WeaponObj* arg0)
{
    D_8010882C[arg0->unk5](arg0);
    func_80093C54(arg0);
}

void func_8009377C(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_10.timer == 0) {
        func_80015D60(arg0, 6);
        arg0->unk15 = 0;
        arg0->unk5++;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->ext.weapon_10.timer--;
}

void func_800937EC(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 7);
        arg0->unk50 = (const u8*)D_801087CC;
        arg0->unk64 = 2;
        arg0->ext.weapon_10.timer = 0x3C;
        arg0->ext.weapon_10.unk90 = 0;
        arg0->unk5++;
    }
}

void func_80093858(struct WeaponObj* arg0)
{
    u8 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_800933A0(arg0, arg0->ext.raw);
    temp_v0 = arg0->ext.weapon_10.timer;
    if (temp_v0 == 0) {
        temp_v0 = 0x98;
        arg0->ext.weapon_10.timer = temp_v0;
        arg0->ext.weapon_10.unk8F = 1;
        arg0->unk5++;
    } else {
        arg0->ext.weapon_10.timer = temp_v0 - 1;
    }
}

void func_800938C0(struct WeaponObj* arg0)
{
    u8* timer_ptr;

    timer_ptr = &arg0->ext.weapon_10.timer;
    if (arg0->ext.weapon_10.timer == 0) {
        func_80015D60(arg0, 8);
        arg0->unk50 = 0;
        arg0->state = 4;
    } else {
        arg0->ext.weapon_10.timer--;
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_800933A0(arg0, timer_ptr);
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_10", func_80093930);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_10", func_800939F4);

void func_80093A5C(struct WeaponObj* arg0)
{
    D_8010883C[arg0->unk5](arg0);
    func_80093C54(arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_10", func_80093AAC);

void func_80093B4C(struct WeaponObj* arg0)
{
    u8 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    temp_v0 = arg0->ext.weapon_10.timer;
    if (temp_v0 == 0) {
        arg0->unk64 = 2;
        arg0->ext.weapon_10.timer = 0x10;
        arg0->unk5++;
        return;
    }
    arg0->ext.weapon_10.timer = temp_v0 - 1;
}

void func_80093BA8(struct WeaponObj* arg0)
{
    u8 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->ext.weapon_10.timer;
    if (timer == 0) {
        func_80015D60(arg0, 8);
        arg0->unk50 = 0;
        arg0->state = 4;
    } else {
        arg0->ext.weapon_10.timer = timer - 1;
        func_8002B718(MOVING_OBJECT(arg0));
    }
}

void func_80093C08(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->on_screen = 0;
        arg0->state = 3;
    } else {
        func_80093C54(arg0);
    }
}

void func_80093C54(struct WeaponObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x30);
    }
    if (arg0->unk2 == 1) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x40);
    }
    func_8002B318(BASE_OBJECT(arg0), 0x28, 0x28);
}
