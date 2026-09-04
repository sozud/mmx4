// ShotObj, shot_object_update_funcs[53]
// 800AAC98..800ABE08
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AAC98);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AAD44);

void func_800AAD64(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AAD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AAE94);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AAFF8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB050);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB128);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB170);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB224);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB32C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB384);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB3A4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB4C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB518);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB564);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB5A4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB66C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB6C4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB710);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB768);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB814);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB868);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB8EC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB98C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800AB9C8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_53", func_800ABB50);

void func_800ABB70(struct ShotObj* arg0)
{
    struct WeaponObj* temp_s1 = arg0->unk7C;
    if (temp_s1->unk94 == 2) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi - 20, -1);
    }
    if (temp_s1->unk94 == 1) {
        arg0->unk8C = 0;
        arg0->base.state = 1;
        arg0->base.unk5 = 3;
        arg0->base.unk6 = 0;
        arg0->base.unk7 = 1;
        arg0->unk50 = 0;
        temp_s1->unk8C = 0;
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi - 20, -1);
        arg0->base.x_pos.i.hi = 0;
        arg0->base.y_pos.i.hi = 0;
        arg0->unk5C = 0x30;
        return;
    }
    arg0->base.on_screen = 0;
    D_80109D84[arg0->base.state](arg0);
}

void (*D_80109D84[])(struct ShotObj*) = {
    func_800AAC98,
    func_800AB9C8,
    func_800ABB50,
};
