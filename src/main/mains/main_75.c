// MainObj, main_object_update_funcs[75]
// 8008FB38..800919C4
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8008FB38);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8008FBCC);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8008FD6C);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8008FDF8);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8008FEE0);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8008FF50);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8009002C);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800900E0);

void func_80090148(struct MainObj* arg0)
{
    D_80105E98[arg0->unk5](arg0);
    if (arg0->unk5 >= 2) {
        func_8002B318(arg0, 0xA0, 0xA0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800901B0);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8009027C);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090470);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090508);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800905D4);

void func_800906E4(struct MainObj* arg0)
{
    D_80105EB8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090720);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090838);

void func_8009093C(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 0xC);
        arg0->unk7C = 0x46;
        arg0->unk7E = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8009099C);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090A28);

void func_80090AC0(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090B04);

void func_80090BD4(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_75.saved_unk5;
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090BE0);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090C54);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090CFC);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090D24);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090D6C);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090E2C);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80090F0C);

void func_80090FC0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk7C = 0x28;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80091008);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800910E0);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_8009114C);

void func_800911DC(struct MainObj* arg0)
{
    D_80105EEC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80091218);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80091448);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800914EC);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800915C4);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80091754);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_800917AC);

INCLUDE_ASM("main/nonmatchings/mains/main_75", func_80091898);

void func_8009197C(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80105F34[arg0->state](arg0);
}

void (*D_80105F34[])(struct MainObj*) = {
    func_80090148,
    func_80091218,
    func_80091898,
};
