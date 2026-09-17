// MainObj, main_object_update_funcs[15]
// 8004D930..8004E890
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004D930);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004D9CC);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004DB10);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004DCB0);

void func_8004DEA0(struct MainObj* arg0)
{
    s8 state;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    state = arg0->unk6;
    if (state == 0) {
        if (arg0->animation_step.fields.event != 0) {
            arg0->unk6 = state + 1;
        }
    } else {
        func_8002B694(ANIMATED_OBJECT(arg0));
        if (arg0->unk24 < 0) {
            arg0->unk6++;
            func_80015D60(arg0, 3);
            arg0->unk5 = 2;
            arg0->unk2C = FIXED(0.2578125);
            arg0->unk6 = 0;
            arg0->unk24 = 0;
            arg0->unk28 = 0;
            arg0->unk67 = -1;
        }
    }
}

void func_8004DF40(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk6 == 0) {
        arg0->collision_data = (const u16*)D_801069F4;
        func_8002B694(ANIMATED_OBJECT(arg0));
        if (arg0->unk70 & 8) {
            func_80015D60(arg0, 4);
            arg0->unk24 = 0;
            arg0->unk2C = 0;
            arg0->unk20 = 0;
            arg0->unk28 = 0;
            arg0->unk6++;
        }
    } else if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 1);
        arg0->unk5 = 1;
        arg0->unk6 = 0;
        arg0->unk67 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004DFEC);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004E128);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004E218);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004E300);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004E490);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004E55C);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004E6A4);

void func_8004E810(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8004E830(struct MainObj* arg0)
{
    D_800FBBA0[arg0->state](arg0);
    if (arg0->state != 5) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
}
