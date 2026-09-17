// ShotObj, shot_object_update_funcs[49]
// 800A9DF4..800AA2FC
#include "common.h"

void (*D_80109BD0[])(struct ShotObj*) = {
    func_800A9EC0,
    func_800A9F30,
    func_800A9FD0,
    func_800AA000,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_49", func_800A9DF4);

void func_800A9EC0(struct ShotObj* arg0)
{
    if (--arg0->timer == 0) {
        arg0->timer = 0x1D;
        arg0->unk5++;
        func_80015D60(arg0, 0xF);
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_49", func_800A9F30);

void func_800A9FD0(struct ShotObj* arg0)
{
    func_8002B694((struct AnimatedObj*)arg0);
    func_80015DC8(arg0);
}

void func_800AA000(struct ShotObj* arg0)
{
    func_8002B694((struct AnimatedObj*)arg0);
    func_80015DC8(arg0);
}

void func_800AA030(struct ShotObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80109BD0[arg0->unk5](arg0);
    if (arg0->unk7C->state == 2) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state = 2;
        arg0->on_screen = 0;
        return;
    }
    func_8002D9BC(arg0);
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state = 2;
        arg0->on_screen = 0;
        return;
    }
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->state = 2;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->on_screen = 0;
}

void func_800AA10C(struct ShotObj* arg0)
{
    D_80109BE0[arg0->state](arg0);
}

void func_800AA148(struct ShotObj* arg0)
{
    s32 x_vel;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 3;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk5C = 3;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->timer = 0;
    arg0->unk8A = 0;
    arg0->bg_offset = 0;
    arg0->unk84.value = 0;
    arg0->unk68 = 0;
    arg0->unk54 = 0;
    arg0->unk50.data = 0;
    arg0->unk60 = 4;
    arg0->unk61 = 0;
    arg0->y_pos.i.hi -= 0x10;
    func_80015D60(arg0, 0x11);

    x_vel = FIXED(-3);
    arg0->timer = 0x14;
    if (arg0->unk2 != 0) {
        x_vel = FIXED(3);
    }
    arg0->y_vel.val = FIXED(4.5);
    arg0->x_vel.val = x_vel;
    arg0->unk28 = 0;
    arg0->unk2C = FIXED(0.34375);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_49", func_800AA20C);

void (*D_80109BE0[])(struct ShotObj*) = {
    func_800A9DF4,
    func_800AA030,
    func_800A9D98,
};
