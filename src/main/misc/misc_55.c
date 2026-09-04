// MiscObj, misc_object_update_funcs[55]
// 800D3084..800D3388
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_55", func_800D3084);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_55", func_800D31F8);

void func_800D323C(struct Unk* arg0)
{
    func_8002B694();
    func_80015DC8(arg0);
    is_on_screen(arg0);
    if (func_8002B160(arg0) != 0) {
        arg0->base.state = 2;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_55", func_800D3288);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_55", func_800D330C);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_55", func_800D332C);
