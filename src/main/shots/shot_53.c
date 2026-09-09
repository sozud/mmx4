// ShotObj, shot_object_update_funcs[53]
// 800AAC98..800ABE08
#include "common.h"

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AAC98);

void func_800AAD44(struct ShotObj* arg0)
{
    func_8009216C(arg0);
}

void func_800AAD64(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AAD6C);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AAE94);

void func_800AAFF8(struct ShotObj* arg0)
{
    D_80109D1C[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x80, 0x80);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB050);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB128);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB170);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB224);

void func_800AB32C(struct ShotObj* arg0)
{
    D_80109D24[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB384);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB3A4);

void func_800AB4C0(struct ShotObj* arg0)
{
    D_80109D30[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB518);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB564);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB5A4);

void func_800AB66C(struct ShotObj* arg0)
{
    D_80109D38[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB6C4);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB710);

void func_800AB768(struct ShotObj* arg0)
{
    D_80109D44[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB7C0);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB814);

void func_800AB868(struct ShotObj* arg0)
{
    D_80109D4C[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB8C0);

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB8EC);

void func_800AB98C(struct ShotObj* arg0)
{
    D_80109D54[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB9C8);

void func_800ABB50(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800ABB70(struct ShotObj* arg0)
{
    struct WeaponObj* temp_s1 = arg0->unk7C;
    if (temp_s1->unk94 == 2) {
        arg0->state = 2;
        arg0->unk5 = 0;
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi - 20, -1);
    }
    if (temp_s1->unk94 == 1) {
        arg0->unk8C = 0;
        arg0->state = 1;
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk7 = 1;
        arg0->unk50 = 0;
        temp_s1->unk8C = 0;
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi - 20, -1);
        arg0->x_pos.i.hi = 0;
        arg0->y_pos.i.hi = 0;
        arg0->unk5C = 0x30;
        return;
    }
    arg0->on_screen = 0;
    D_80109D84[arg0->state](arg0);
}

void (*D_80109D84[])(struct ShotObj*) = {
    func_800AAC98,
    func_800AB9C8,
    func_800ABB50,
};
