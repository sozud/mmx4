// ShotObj, shot_object_update_funcs[30]
// 8009FB60..8009FF10
#include "common.h"
#include "main/objects.h"
#include "main/shots/shot_30_cannon_shot.h"
#include "main/55C4.h"
#include "main/1E1BC.h"
#include "main/object_motion.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#endif

// cannon_shot_state_funcs
extern void (*cannon_shot_state_funcs[])(struct ShotObj*);

void cannon_shot_despawn(struct ShotObj*);
void cannon_shot_idle(struct ShotObj*);

extern struct Unk_unk68 D_80106170[32];
extern u8 cannon_shot_boxes[4][4];
extern s32 cannon_shot_speeds[4];

void cannon_shot_update(struct ShotObj* self)
{
    cannon_shot_state_funcs[self->state](self);
}

// cannon_shot_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009FB9C(struct ShotObj* arg0);
void func_8009FD00(struct ShotObj* arg0);
extern struct Unk_unk68 D_80106170[32];
extern u8 cannon_shot_boxes[4][4];
extern s32 cannon_shot_speeds[4];
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/shots/shot_30_cannon_shot", func_8009FB9C);
#else
void func_8009FB9C(struct ShotObj* arg0)
{
    struct WeaponObj* owner;

    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 6;
    arg0->unk50.data = (const u8*)cannon_shot_boxes;
    arg0->unk58.collision_bounds = D_80106170;
    arg0->unk54 = (const u8*)cannon_shot_boxes;
    arg0->unk68 = NULL;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    owner = arg0->unk7C;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk2 == 0) {
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi = owner->x_pos.i.hi - 0x20;
        else
            arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x20;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 8;
    } else if (arg0->unk2 == 1) {
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi = owner->x_pos.i.hi - 0x1D;
        else
            arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x1D;
        arg0->y_pos.i.hi = owner->y_pos.i.hi + 0xE;
    } else {
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi = owner->x_pos.i.hi - 0xC;
        else
            arg0->x_pos.i.hi = owner->x_pos.i.hi + 0xC;
        arg0->y_pos.i.hi = owner->y_pos.i.hi + 0x12;
    }
    set_animation(arg0, 3);
    cannon_shot_spawn_flash(arg0);
    arg0->unk84.value = 0x10;
    arg0->unk8C.word = 0;
}
#endif

// cannon_shot_fly
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/shots/shot_30_cannon_shot", func_8009FD00);
#else
void func_8009FD00(struct ShotObj* arg0)
{
    s32 speed;

    animate_object(ANIMATED_OBJECT(arg0));
    move_with_gravity(ANIMATED_OBJECT(arg0));
    speed = arg0->x_vel.val >= 0 ? arg0->x_vel.val : -arg0->x_vel.val;
    if (speed > 0x30000)
        arg0->unk28 = 0;
    if (func_8002DD04((struct MainObj*)arg0) < 0) {
        spawn_explosion(BASE_OBJECT(arg0));
    } else {
        func_8002D9BC(arg0);
        if (--arg0->unk84.value == 0 && arg0->unk17 != 4) {
            arg0->x_vel.val = cannon_shot_speeds[(arg0->unk15 & PLAYER_FACING_RIGHT) ? 1 : 0];
            arg0->unk28 = 0x600;
            arg0->x_pos.i.hi += (arg0->unk15 & PLAYER_FACING_RIGHT) ? 0x10 : -0x10;
            set_animation(arg0, 4);
        }
        if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
            update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
            return;
        }
    }
    arg0->unk8C.word = 1;
    arg0->state++;
}
#endif

void cannon_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void cannon_shot_idle(struct ShotObj* self)
{
}

void cannon_shot_spawn_flash(struct ShotObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x10;
        obj->unk2 = 1;
        obj->unk50 = (struct PlayerObj*)self;
        obj->unk42 = self->unk42;
        obj->animation_table = self->animation_table;
        obj->unk3C = self->unk3C;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = self->unk15;
        obj->x_pos.val = self->x_pos.val;
        obj->y_pos.val = self->y_pos.val;
    }
}

u8 cannon_shot_boxes[4][4] = {
    { 0xF3, 0xFA, 0x17, 0x0A },
    { 0xF5, 0xFD, 0x1B, 0x0A },
    { 0xFF, 0xFF, 0x0A, 0x04 },
    { 0x02, 0x02, 0x0D, 0x04 },
};

s32 cannon_shot_speeds[4] = { -0x22000, 0x22000, -0x10000, 0x10000 };

void (*cannon_shot_state_funcs[])(struct ShotObj*) = {
    func_8009FB9C,
    func_8009FD00,
    cannon_shot_despawn,
    cannon_shot_idle,
};
