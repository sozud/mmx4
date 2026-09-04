// MainObj, main_object_update_funcs[75]
// 8008FB38..800919C4
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_8008FB38);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_8008FBCC);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_8008FD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_8008FDF8);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_8008FEE0);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_8008FF50);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_8009002C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_800900E0);

void func_80090148(struct MainObj* arg0)
{
    D_80105E98[arg0->base.unk5](arg0);
    if (arg0->base.unk5 >= 2) {
        func_8002B318(arg0, 0xA0, 0xA0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_800901B0);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_8009027C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090470);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090508);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_800905D4);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_800906E4);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090720);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090838);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_8009093C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_8009099C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090A28);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090AC0);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090B04);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090BD4);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090BE0);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090C54);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090CFC);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090D24);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090D6C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090F0C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80090FC0);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80091008);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_800910E0);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_8009114C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_800911DC);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80091218);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80091448);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_800914EC);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_800915C4);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80091754);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_800917AC);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_75", func_80091898);

void func_8009197C(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_80105F34[arg0->base.state](arg0);
}

void (*D_80105F34[])(struct MainObj*) = {
    func_80090148,
    func_80091218,
    func_80091898,
};
