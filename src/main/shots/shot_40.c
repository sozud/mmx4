// ShotObj, shot_object_update_funcs[40]
// 800A5348..800A56E4
#include "common.h"

void func_800A5348(struct ShotObj* arg0)
{
    D_801098B8[arg0->state](arg0);
}

void func_800A5384(struct ShotObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 2;
    arg0->unk68 = &D_80109894;
    arg0->unk5C = 3;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk8A = 0;
    arg0->unk84.value = 0;
    arg0->unk54 = NULL;
    arg0->unk50.data = NULL;
    arg0->unk58.data = NULL;
    arg0->unk60 = 6;
    arg0->unk61 = 0;
    arg0->y_pos.i.hi = (u16)arg0->y_pos.i.hi + 0x7E;
    func_80015D60(arg0, 2);
}

void func_800A5404(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 1;
        arg0->timer = 0xF0;
        arg0->unk6 = 0;
        arg0->unk50.data = D_80109890;
        func_80015D60(arg0, 4);
        return;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800A5460(struct ShotObj* arg0)
{
    struct ShotObj* shot = arg0;

    if (shot->timer == 0) {
        shot->unk5 = 2;
        shot->unk6 = 0;
        shot->unk50.data = 0;
        func_80015D60(shot, 3);
        return;
    }
    if ((engine_obj.stage == 7) && (shot->unk70 & 0xB) && (shot->unk7 == 0)) {
        shot->unk8A = 0x14;
        shot->unk7 = 1;
    }
    shot->timer = (u16)shot->timer - 1;
    func_80015DC8(ANIMATED_OBJECT(shot));
}

void func_800A5500(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        return;
    }
    func_80015DC8(arg0);
}

void func_800A5540(struct ShotObj* arg0)
{
    s32 x_offset;

    if (arg0->unk7C->active != 0 && arg0->unk7C->id == 0x3F) {
        arg0->unk18.val = arg0->x_pos.val;
        arg0->unk1C.val = arg0->y_pos.val;
        D_801098C4[arg0->unk5](arg0);
        func_8002D9BC(arg0);
        func_8002C808(PLAYER_OBJECT(arg0));
        if (arg0->unk8A != 0) {
            if (!(D_80141BD8.unk0 & 3)) {
                func_800AF878(BASE_OBJECT(arg0), 1, 0x60, 0x60);
                func_800AF878(BASE_OBJECT(arg0), 1, 0x30, 0x30);
                x_offset = get_random() & 0x30;
                func_800C833C(7, D_801098A0, (struct MiscObj*)arg0, x_offset, get_random() & 0x30);
            }
            if (--arg0->unk8A == 0) {
                func_800DABE4(0, D_80109898[arg0->unk2], 0x150);
                func_800C813C(0xE, D_801098A8, arg0);
            }
        }
        func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
        return;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A56C0(struct ShotObj* arg0)
{
    arg0->unk7C->unk7 = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 D_80109890[4] = { 0xCF, 0x82, 0x60, 0xFF };

struct Unk_unk68 D_80109894 = { 0, 8, 0x2E, 0x78 };

s16 D_80109898[4] = { 0x0AE0, 0x14E0, 0x1710, 0 };

u8 D_801098A0[8] = { 6, 7, 8, 9, 0x0A, 0x0B, 0x0C, 0 };

u8 D_801098A8[16] = { 6, 7, 8, 9, 0x0A, 0x0B, 0x0C, 6, 7, 8, 9, 0x0A, 0x0B, 0x0C, 0, 0 };

void (*D_801098B8[])(struct ShotObj*) = {
    func_800A5384,
    func_800A5540,
    func_800A56C0,
};

void (*D_801098C4[3])(struct ShotObj*) = {
    func_800A5404,
    func_800A5460,
    func_800A5500,
};
