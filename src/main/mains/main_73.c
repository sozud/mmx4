// MainObj, main_object_update_funcs[73]
// 8008BA38..8008D460
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BA38);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BB6C);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BCB0);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BD10);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BD5C);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BDAC);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BE74);

void func_8008BEC4(struct MainObj* arg0)
{
    D_801052BC[arg0->unk5](arg0);
}

void func_8008BF00(struct MainObj* arg0)
{
    if (arg0->unk70 & 3) {
        if (arg0->unk70 & 1) {
            arg0->unk15 = 0;
        } else {
            arg0->unk15 = 0x40;
        }
    } else if ((arg0->x_pos.i.hi - g_Player.x_pos.i.hi) < 0) {
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008BF54);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C014);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C0C0);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C10C);

void func_8008C204(struct MainObj* arg0)
{
    D_801052C8[arg0->unk6](arg0);
}

void func_8008C240(struct MainObj* arg0)
{
    arg0->unk6++;
    func_80015D60(arg0, 3);
    func_8001540C(2, 0xF4, NULL);
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C27C);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C30C);

void func_8008C360(struct MainObj* arg0)
{
    D_801052D0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C39C);

void func_8008C3F4(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C43C);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C4B4);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C5A8);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C664);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C7E4);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C888);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C8E0);

void func_8008C95C(struct MainObj* arg0)
{
    D_801052DC[arg0->unk6](arg0);
}

void func_8008C998(struct MainObj* arg0)
{
    arg0->unk24 = FIXED(5);
    arg0->unk28 = 0;
    arg0->unk20 = 0;
    arg0->unk2C = 0x4200;
    arg0->ext.main_73.unk89 = 0;
    arg0->unk6++;
    func_80015D60(arg0, 2);
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008C9E0);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CA60);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CB2C);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CBF8);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CC7C);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CCD4);

void func_8008CD44(struct MainObj* arg0)
{
    D_80105300[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CD80);

void func_8008CF68(struct MainObj* arg0)
{
    s16 timer = arg0->unk7C, next_timer = timer;
    u16 flags;
    if (timer == 0) {
        next_timer = 0x10;
        arg0->unk7C = next_timer;
        flags = arg0->unk42 | 0x8000;
    } else {
        next_timer--;
        arg0->unk7C = next_timer;
        flags = arg0->unk42 & 0x7FFF;
    }
    arg0->unk42 = flags;
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008CFAC);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008D050);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008D0D0);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008D138);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008D19C);

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008D278);

void func_8008D2FC(struct MainObj* arg0)
{
    s16 temp_v0;

    temp_v0 = arg0->unk7C - 1;
    arg0->unk7C = temp_v0;
    if (temp_v0 == 0) {
        engine_obj.unkF = 1;
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008D340);

void func_8008D37C(struct MainObj* arg0)
{
    D_80105350[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_73", func_8008D3B8);

void func_8008D410(struct MainObj* arg0)
{
    if (--arg0->ext.main_74.unk97 == 0) {
        arg0->ext.main_74.unk97 = 4;
        func_800AF95C(OBJECT_HEADER(arg0), 1, 0x60, 0x60, 2);
    }
}
