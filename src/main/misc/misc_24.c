// MiscObj, misc_object_update_funcs[24]
// 800CBECC..800CC460
#include "common.h"

void func_800CBECC(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    D_8010E90C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_24", func_800CBF14);

void func_800CC040(struct MiscObj* arg0)
{
    D_8010E918[arg0->base.unk5](arg0);
    if (func_8002B160(arg0) == 0) {
        is_on_screen(arg0);
    } else {
        arg0->base.state = 2;
    }
}

void func_800CC0AC(struct MiscObj* arg0)
{
    D_8010E924[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_24", func_800CC0E8);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_24", func_800CC114);

void func_800CC1F8(struct MiscObj* arg0)
{
    D_8010E92C[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_24", func_800CC234);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_24", func_800CC304);

void func_800CC350(struct MiscObj* arg0)
{
    D_8010E934[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_24", func_800CC38C);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_24", func_800CC3D4);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_24", func_800CC418);

void (*D_8010E90C[])(struct MiscObj*) = {
    func_800CBF14,
    func_800CC040,
    func_800CC418,
};

void (*D_8010E918[])(struct MiscObj*) = {
    func_800CC0AC,
    func_800CC1F8,
    func_800CC350,
};

void (*D_8010E924[])(struct MiscObj*) = {
    func_800CC0E8,
    func_800CC114,
};

void (*D_8010E92C[])(struct MiscObj*) = {
    func_800CC234,
    func_800CC304,
};

void (*D_8010E934[])(struct MiscObj*) = {
    func_800CC38C,
    func_800CC3D4,
};
