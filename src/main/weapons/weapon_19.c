// WeaponObj, weapon_object_update_funcs[19]
// 800927EC..800929A0
#include "common.h"

void func_800927EC(struct WeaponObj* arg0)
{
    D_80108748[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_19", func_80092828);

void func_80092918(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x1A, 0x12) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->unk98 == 0) {
            func_80092490(ANIMATED_OBJECT(arg0));
            func_8002B318(BASE_OBJECT(arg0), 0x1A, 0x12);
            return;
        }
        func_80092600(arg0);
        return;
    }
    arg0->on_screen = 0;
    arg0->state = 3;
}

void (*D_80108748[])(struct WeaponObj*) = {
    func_80092828,
    func_80092918,
    func_80092614,
    func_80092614,
};
