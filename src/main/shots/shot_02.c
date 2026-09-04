// ShotObj, shot_object_update_funcs[2, 3, 4, 5]
// 80099D10..8009A984
#include "common.h"

void func_80099D10(struct ShotObj* arg0)
{
}

void func_80099D18(struct ShotObj* arg0)
{
    D_80108CC4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_80099D54);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_80099E34);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_80099F28);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_80099F48);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A10C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A264);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A338);

void func_8009A358(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    CollisionRelated(arg0);
    D_80108CE4[arg0->base.state](arg0);
}

void func_8009A3B4(struct ShotObj* arg0)
{
    if (arg0->unk7C->base.unk15 == 0) {
        arg0->base.x_pos.val = arg0->unk7C->base.x_pos.val + FIXED(-75);
    } else {
        arg0->base.x_pos.val = arg0->unk7C->base.x_pos.val + FIXED(75);
    }
    arg0->base.y_pos.val = arg0->unk7C->base.y_pos.val + FIXED(2);
    arg0->unk42 = arg0->unk7C->unk42;
    arg0->base.on_screen = 0;
    D_80108CF8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A448);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A4F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A598);

void func_8009A5B8(struct ShotObj* arg0)
{
    D_80108D28[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A5F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A6B4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A7D8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A7F8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A87C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_02", func_8009A964);

void (*D_80108D28[])(struct ShotObj*) = {
    func_8009A5F4,
    func_8009A6B4,
    func_8009A7D8,
    func_8009A7F8,
    func_8009A87C,
    func_8009A964,
};
