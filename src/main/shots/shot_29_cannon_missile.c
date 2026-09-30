// ShotObj, shot_object_update_funcs[29]
// 8009F638..8009FB60
#include "common.h"

u8 cannon_missile_boxes[8] = { 0xF5, 0xFD, 0x1B, 0x0A, 2, 2, 0x0D, 4 };
s32 cannon_missile_speeds[2] = { 0x5000, -0x5000 };
s32 cannon_missile_accels[4] = { 0x10000, -0x10000, -0x10000, 0x10000 };

void cannon_missile_update(struct ShotObj* self)
{
    cannon_missile_state_funcs[self->state](self);
}

// cannon_missile_init
INCLUDE_ASM("main/nonmatchings/shots/shot_29_cannon_missile", func_8009F674);

// cannon_missile_main
INCLUDE_ASM("main/nonmatchings/shots/shot_29_cannon_missile", func_8009F7C0);

// cannon_missile_launch
INCLUDE_ASM("main/nonmatchings/shots/shot_29_cannon_missile", func_8009F89C);

void cannon_missile_slow(struct ShotObj* self)
{
    u8 temp_v0;

    temp_v0 = self->unk8C.shot_29.timer - 1;
    self->unk8C.shot_29.timer = temp_v0;
    if ((temp_v0 == 0) && (self->unk90.bytes[1] == 0)) {
        self->x_vel.val = 0;
        self->unk28 = FIXED(0.1875);
        self->unk90.bytes[1] = 1;
        self->y_vel.val = 0;
        self->unk8C.shot_29.unk8D = 0x28;
        self->unk5++;
    }
    if ((self->unk2 != 0) && (self->unk8C.shot_29.timer < 0x15U) && (self->y_vel.val != 0)) {
        self->y_vel.val = 0;
    }
}

void cannon_missile_track(struct ShotObj* self)
{
    struct ShotObj* shot;
    u8 verticalTimer;
    u8 spawnTimer;
    s32 targetY;
    s32 delta;
    struct MiscObj* effect;
    s16 spawnX;

    shot = self;
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

void cannon_missile_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void cannon_missile_idle(struct ShotObj* self)
{
}

void (*cannon_missile_state_funcs[])(struct ShotObj*) = {
    func_8009F674,
    func_8009F7C0,
    cannon_missile_despawn,
    cannon_missile_idle,
};
