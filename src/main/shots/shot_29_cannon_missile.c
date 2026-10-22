// ShotObj, shot_object_update_funcs[29]
// 8009F638..8009FB60
#include "common.h"
#include "main/objects.h"
#include "main/shots/shot_29_cannon_missile.h"
#include "main/object_motion.h"

#ifdef MMX4_PC
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#endif

// cannon_missile_state_funcs
extern void (*cannon_missile_state_funcs[])(struct ShotObj*);

void cannon_missile_despawn(struct ShotObj*);
void cannon_missile_idle(struct ShotObj*);

u8 cannon_missile_boxes[8] = { 0xF5, 0xFD, 0x1B, 0x0A, 2, 2, 0x0D, 4 };
s32 cannon_missile_speeds[2] = { 0x5000, -0x5000 };
s32 cannon_missile_accels[4] = { 0x10000, -0x10000, -0x10000, 0x10000 };

void cannon_missile_update(struct ShotObj* self)
{
    cannon_missile_state_funcs[self->state](self);
}

// cannon_missile_init
#ifdef MMX4_PC
void func_8009F674(struct ShotObj* arg0);
void func_8009F7C0(struct ShotObj* arg0);
void func_8009F89C(struct ShotObj* arg0);
extern void (*cannon_missile_step_funcs[])(struct ShotObj*);
#endif

#ifdef MMX4_PC
void func_8009F674(struct ShotObj* arg0)
{
    struct MainObj* owner;
    s32 dx;

    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 5;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk50.data = cannon_missile_boxes;
    arg0->unk54 = cannon_missile_boxes;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk68 = NULL;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    owner = (struct MainObj*)arg0->unk7C;
    dx = arg0->unk15 != 0 ? -0x1A : 0x1A;
    arg0->x_pos.i.hi = owner->x_pos.i.hi + dx;
    arg0->y_pos.i.hi = owner->y_pos.i.hi + (arg0->unk2 == 0 ? -0x23 : -0x10);
    set_animation(arg0, 7);
    arg0->unk8C.bytes[3] = 0x20;
    arg0->unk5 = 0;
    arg0->unk8C.bytes[1] = 0;
    arg0->unk8C.bytes[2] = 0;
    arg0->unk90.bytes[2] = 0;
    arg0->unk90.bytes[0] = 2;
    arg0->unk90.bytes[1] = 0;
    arg0->unk8C.bytes[0] = arg0->unk2 * 20 + 0x1E;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_29_cannon_missile", func_8009F674);
#endif

// cannon_missile_main
#ifdef MMX4_PC
void func_8009F7C0(struct ShotObj* arg0)
{
    s32 speed;

    cannon_missile_step_funcs[arg0->unk5](arg0);
    animate_object(ANIMATED_OBJECT(arg0));
    move_with_gravity(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (func_8002DD04((struct MainObj*)arg0) < 0) {
        spawn_explosion(BASE_OBJECT(arg0));
        arg0->state++;
        return;
    }
    speed = arg0->x_vel.val;
    if (speed < 0)
        speed = -speed;
    if (speed > 0x40000)
        arg0->unk28 = 0;
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x20) != 0) {
        arg0->state++;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_29_cannon_missile", func_8009F7C0);
#endif

// cannon_missile_launch
#ifdef MMX4_PC
void func_8009F89C(struct ShotObj* arg0)
{
    u8 timer = arg0->unk8C.bytes[3];
    u8 blink;

    if (timer == 0) {
        arg0->x_vel.val = cannon_missile_speeds[(arg0->unk15 & 0x40) ? 1 : 0];
        arg0->y_vel.val = cannon_missile_accels[arg0->unk2 != 0 ? 1 : 0];
        arg0->unk42 &= 0x7FFF;
        arg0->unk5++;
        return;
    }
    arg0->unk8C.bytes[3] = timer - 1;
    blink = arg0->unk90.bytes[0];
    arg0->unk90.bytes[0] = blink - 1;
    if (blink == 0) {
        arg0->unk90.bytes[0] = 2;
        arg0->unk42 &= 0x7FFF;
    } else {
        arg0->unk42 |= 0x8000;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_29_cannon_missile", func_8009F89C);
#endif

void cannon_missile_slow(struct ShotObj* self)
{
    self->unk8C.shot_29.timer -= 1;
    if (self->unk8C.shot_29.timer == 0) {
        if (self->unk90.bytes[1] == 0) {
            self->x_vel.val = 0;
            self->y_vel.val = 0;
            self->unk28 = FIXED(0.1875);
            self->unk90.bytes[1] = 1;
            self->unk8C.shot_29.unk8D = 0x28;
            self->unk5++;
        }
    }
    if ((self->unk2 != 0) && (self->unk8C.shot_29.timer <= 0x14) && (self->y_vel.val != 0)) {
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
    if (spawnTimer == 0) {
        if (shot->unk90.bytes[1] != 0) {
            effect = find_free_misc_obj();
            if (effect != 0) {
                effect->active = 0x21;
                effect->id = 0x17;
                effect->unk2 = 0;
                effect->unk15 = get_random() & 0x40;
                effect->ext.misc_5.animation = 0;
                if (shot->unk15 == 0) {
                    effect->x_pos.i.hi = (u16)shot->x_pos.i.hi + 0x10;
                } else {
                    effect->x_pos.i.hi = (u16)shot->x_pos.i.hi - 0x10;
                }
                effect->y_pos.i.hi = (u16)shot->y_pos.i.hi;
                effect->x_vel.val = 0;
                effect->y_vel.val = 0;
                effect->unk7 = 1;
                effect->unk16 = 7;
            }
            shot->unk8C.bytes[2] = 1;
        }
    } else {
        shot->unk8C.bytes[2] = spawnTimer - 1;
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

void (*cannon_missile_step_funcs[3])(struct ShotObj*) = {
    func_8009F89C,
    cannon_missile_slow,
    cannon_missile_track,
};
