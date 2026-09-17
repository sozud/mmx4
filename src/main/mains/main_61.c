// MainObj, main_object_update_funcs[61]
// 8007872C..8007B90C
#include "common.h"

void func_8007872C(struct MainObj* arg0)
{
    D_80101FF8[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007877C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800788E4);

void func_80078DF0(struct MainObj* arg0)
{
    D_80102024[arg0->unk5](arg0);
}

void func_80078E2C(struct MainObj* arg0)
{
    g_Player.unkBA = 0;
    func_80036AE4(0x14, g_Player.unk15);
    arg0->unk5 = 1;
    arg0->unk42 &= 0x7FFF;
    func_80015D60(arg0, 0x15);
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->unk61 = 0x19;
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80078EB0);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80078FA4);

void func_800790AC(struct MainObj* arg0)
{
    D_80102030[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800790E8);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800791D4);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007927C);

void func_80079364(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60((struct Unk19*)arg0, 17);
        arg0->unk6 = 4;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800793AC);

void func_80079518(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        func_80015D60(arg0, 0);
        arg0->unk7E = 3;
        arg0->unk6 = 6;
        func_800921E8(2);
    }
}

void func_80079568(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (func_8009227C() != 0) {
        return;
    }
    if (--arg0->unk7E == 0) {
        func_8001540C(0, 0xE, NULL);
        arg0->unk7E = 3;
    }
    if (++arg0->unk5C == 0x30) {
        func_80015D60(arg0, 2);
        arg0->unk5 = 7;
        arg0->unk6 = 0;
        func_80036B18();
    }
}

void func_80079608(struct MainObj* arg0)
{
    D_8010204C[arg0->unk6](arg0);
}

void func_80079644(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->unk2 == 0) {
        if (--self->unk7E == 0) {
            self->unk7E = 0xC;
            func_8001540C(2, 0xAB, self);
        }
    }
    if (self->animation_step.fields.event != 0) {
        self->unk60 = 5;
        self->unk68 = &D_80101CA8;
        self->unk7C = 0x1E;
        self->unk6 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_800796DC);

void func_80079794(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk61 = 0;
        func_80015D60(arg0, 2);
        arg0->unk5 = 7;
        arg0->unk6 = 0;
    }
}

void func_800797E8(struct MainObj* arg0)
{
    if (arg0->ext.main_61.unk85 == 0) {
        arg0->ext.main_61.unk89 = 3;
        arg0->unk2C = FIXED(0.21875);
        arg0->ext.main_61.unk8A = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = 0;
        arg0->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079824);

void func_80079914(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk61 = 0;
        func_80015D60(arg0, 0);
        arg0->unk7C = 0x14;
        arg0->unk6 = 6;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007996C);

void func_80079A50(struct MainObj* arg0)
{
    D_80102068[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079A8C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079B50);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_80079DD8);

void func_80079FE4(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 0xA);
        func_8001540C(2, 0xA6, arg0);
        arg0->unk6 = 4;
    }
}

void func_8007A048(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->ext.main_61.unk86 = 0;
        func_80015D60(arg0, 0);
        arg0->unk7C = 0x1E;
        arg0->unk6 = 5;
    }
}

void func_8007A09C(struct MainObj* arg0)
{
    u16 timer;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if ((timer << 16) == 0) {
        arg0->unk24 = 0;
        if (arg0->unk2 == 0) {
            arg0->unk7C = 6;
            arg0->unk5 = 4;
            arg0->unk6 = 0;
        } else {
            arg0->unk7C = 6;
            func_80015D60(arg0, 2);
            arg0->unk5 = 4;
            arg0->unk6 = 2;
        }
    }
}

void func_8007A12C(struct MainObj* arg0)
{
    D_80102080[arg0->unk6](arg0);
}

void func_8007A168(struct MainObj* arg0)
{
    s32 x_vel;

    func_80015D60(arg0, 1);
    if (arg0->unk15 == 0) {
        x_vel = -D_80101CB8[arg0->ext.main_61.unk8C];
    } else {
        x_vel = D_80101CB8[arg0->ext.main_61.unk8C];
    }
    arg0->unk20 = x_vel;
    arg0->unk6 = 1;
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A1EC);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A2B4);

void func_8007A3B0(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if ((arg0->unk7 == 0) && (arg0->unk24 < 0)) {
        func_80015D60(arg0, 3);
        arg0->unk7 = 1;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 0xA);
        func_8001540C(2, 0xA6, arg0);
        arg0->unk6 = 4;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A444);

void func_8007A4B0(struct MainObj* arg0)
{
    D_80102094[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A4EC);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A63C);

void func_8007A7F0(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 0xA);
        func_8001540C(2, 0xA6, arg0);
        arg0->unk6 = 3;
    }
}

void func_8007A854(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk60 = 5;
        func_80015D60(arg0, 0);
        arg0->unk7C = 0x28;
        arg0->unk6 = 4;
    }
}

void func_8007A8AC(struct MainObj* arg0)
{
    s16 timer;

    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer != 0) {
        return;
    }
    if (arg0->unk2 == 0) {
        arg0->unk7C = 6;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    arg0->unk7C = 6;
    func_80015D60(arg0, 2);
    arg0->unk5 = 4;
    arg0->unk6 = 2;
}

void func_8007A930(struct MainObj* arg0)
{
    D_801020A8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007A96C);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007AB1C);

void func_8007ADB4(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        func_8001540C(2, 0xAC, arg0);
        func_80015D60(arg0, 8);
        arg0->unk2C = FIXED(0.21875);
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = 0;
        arg0->unk6 = 3;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007AE2C);

void func_8007AFB4(struct MainObj* arg0)
{
    s8 temp_v0_2;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        temp_v0_2 = arg0->ext.main_61.unk87 - 1;
        arg0->ext.main_61.unk87 = temp_v0_2;
        if (temp_v0_2 == 0) {
            func_80015D60(arg0, 0xF);
            arg0->unk6 = 6;
        } else {
            func_80015D60(arg0, 5);
            func_8001540C(2, 0xA7, arg0);
            arg0->unk7C = 0x28;
            arg0->unk6 = 0;
            arg0->unk7E = 1;
        }
    }
}

void func_8007B054(struct MainObj* arg0)
{
    arg0->unk7C--;
    if (arg0->unk7C == 0) {
        arg0->unk7C = 1;
        arg0->unk5 = 5;
        arg0->unk6 = 4;
        return;
    }

    if ((arg0->unk2 != 0) && ((*(u32*)&arg0->ext.main_61.unk94->state & 0xFFFF00) == 0x50600)) {
        arg0->unk7C = 1;
        arg0->unk5 = 5;
        arg0->unk6 = 4;
        arg0->ext.main_61.unk94->unk7C = 1;
        arg0->ext.main_61.unk94->unk5 = 5;
        arg0->ext.main_61.unk94->unk6 = 4;
    }
}

void func_8007B0F8(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60((struct Unk19*)arg0, 2);
        arg0->unk6 = 7;
    }
}

void func_8007B140(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk7C = 1;
        arg0->unk6 = 0;
    }
}

void func_8007B180(struct MainObj* arg0)
{
    D_801020C8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B1BC);

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B2FC);

void func_8007B3A8(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk68 = &D_80101CA8;
        func_80015D60(arg0, 7);
        arg0->unk7C = 0x28;
        arg0->unk6 = 3;
        arg0->unk7E = 6;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B418);

void func_8007B588(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.21875);
        arg0->unk15 ^= 0x40;
        func_80015D60(arg0, 3);
        arg0->unk6 = 5;
    }
}

void func_8007B5F0(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_8001540C(2, 0xA6, arg0);
        arg0->unk6 = 6;
    }
}

void func_8007B640(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 2);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_8007B68C(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B6BC);

void func_8007B7B4(void)
{
    s32 i;
    u16* source;
    u16* destination;

    source = SP_PALETTE_BANK[53];
    if (engine_obj.stage == 3) {
        destination = SP_PALETTES[60];
    } else {
        destination = SP_PALETTES[44];
    }
    i = 0;
    do {
        *destination++ = *source++;
        i++;
    } while (i < 0x40);
    need_palette_load |= 1;
}

INCLUDE_ASM("main/nonmatchings/mains/main_61", func_8007B834);
