// ShotObj, shot_object_update_funcs[29]
// 8009F638..8009FB60
#include "common.h"

u8 D_801091D0[8] = { 0xF5, 0xFD, 0x1B, 0x0A, 2, 2, 0x0D, 4 };
s32 D_801091D8[2] = { 0x5000, -0x5000 };
s32 D_801091E0[4] = { 0x10000, -0x10000, -0x10000, 0x10000 };

void func_8009F638(struct ShotObj* arg0)
{
    D_801091F0[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_29", func_8009F674);

INCLUDE_ASM("main/nonmatchings/shots/shot_29", func_8009F7C0);

INCLUDE_ASM("main/nonmatchings/shots/shot_29", func_8009F89C);

void func_8009F94C(struct ShotObj* arg0)
{
    u8 temp_v0;

    temp_v0 = arg0->unk8C.shot_29.timer - 1;
    arg0->unk8C.shot_29.timer = temp_v0;
    if ((temp_v0 == 0) && (arg0->unk90.bytes[1] == 0)) {
        arg0->unk28 = FIXED(0.1875);
        arg0->unk90.bytes[1] = 1;
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk8C.shot_29.unk8D = 0x28;
        arg0->unk5++;
    }
    if ((arg0->unk2 != 0) && (arg0->unk8C.shot_29.timer < 0x15U) && (arg0->y_vel.val != 0)) {
        arg0->y_vel.val = 0;
    }
}

void func_8009F9E0(struct ShotObj* arg0)
{
    struct ShotObj* shot;
    u8 verticalTimer;
    u8 spawnTimer;
    s32 targetY;
    s32 delta;
    struct MiscObj* effect;
    s16 spawnX;

    shot = arg0;
    verticalTimer = shot->unk8C.bytes[1];
    if (verticalTimer != 0) {
        shot->unk8C.bytes[1] = verticalTimer - 1;
        targetY = shot->y_pos.i.hi + 8;
        delta = g_Player.y_pos.i.hi - targetY;
        if (delta >= 0) {
            if (delta < 3) {
                shot->y_vel.val = 0;
                goto vertical_done;
            }
        } else if (targetY - g_Player.y_pos.i.hi < 3) {
            goto vertical_zero;
        }
        if (g_Player.y_pos.i.hi - 8 >= shot->y_pos.i.hi) {
            shot->y_vel.val = -0x20000;
        } else {
            shot->y_vel.val = 0x20000;
        }
        goto vertical_done;
    }
vertical_zero:
    shot->y_vel.val = 0;
vertical_done:
    spawnTimer = shot->unk8C.bytes[2];
    if (spawnTimer != 0) {
        shot->unk8C.bytes[2] = spawnTimer - 1;
    } else if (shot->unk90.bytes[1] != 0) {
        effect = find_free_misc_obj();
        if (effect != 0) {
            effect->active = 0x21;
            effect->id = 0x17;
            effect->unk2 = 0;
            effect->unk15 = get_random() & 0x40;
            effect->ext.misc_5.animation = 0;
            if (shot->unk15 == 0) {
                spawnX = (u16)shot->x_pos.i.hi + 0x10;
            } else {
                spawnX = (u16)shot->x_pos.i.hi - 0x10;
            }
            effect->x_pos.i.hi = spawnX;
            effect->y_pos.i.hi = (u16)shot->y_pos.i.hi;
            effect->unk7 = 1;
            effect->x_vel.val = 0;
            effect->y_vel.val = 0;
            effect->unk16 = 7;
        }
        shot->unk8C.bytes[2] = 1;
    }
}

void func_8009FB38(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009FB58(struct ShotObj* arg0)
{
}

void (*D_801091F0[])(struct ShotObj*) = {
    func_8009F674,
    func_8009F7C0,
    func_8009FB38,
    func_8009FB58,
};
