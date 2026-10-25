// ShotObj, shot_object_update_funcs[2, 3, 4, 5]
// 80099D10..8009A984
#include "common.h"
#include "main/shots/eregion_fireball_data.h"
#include "main/shots/eregion_wing_slash_data.h"
#include "main/shots/gunner_shot_unused_data.h"
#include "main/shots/mech_boulder_data.h"
#include "main/shots/shot_02_gunner_shot.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/misc/misc_02_rubble.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/collision_bounds.h"

// gunner_shot_state_funcs
extern void (*gunner_shot_state_funcs[])(struct ShotObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

struct Shot2Hitbox {
    s8 x;
    s8 y;
    u8 width;
    u8 height;
};

extern void (*gunner_shot_unused_funcs[])(struct ShotObj*);

u8 gunner_shot_hit_box[4] = { 0xFC, 0xFC, 7, 8 };

s8 gunner_shot_spawn_offsets[2][2] = { { -0x12, -2 }, { 0x12, -2 } };

void (*gunner_shot_state_funcs[])(struct ShotObj*) = {
    func_80099D54,
    gunner_shot_fly,
    gunner_shot_despawn,
};

extern u8 eregion_fireball_hit_box[4];

extern u8 eregion_fireball_explode_box[4];

extern u8 eregion_fireball_terrain_box[4];

extern u8 eregion_fireball_debris[2][4];

extern void (*eregion_fireball_state_funcs[])(struct ShotObj*);

extern u8 eregion_wing_slash_hit_box[4];

extern void (*eregion_wing_slash_state_funcs[])(struct ShotObj*);

extern struct Shot2Hitbox mech_boulder_shockwave_boxes[1];
extern struct Shot2Hitbox mech_boulder_shockwave_boxes_tail[6];
extern u8 mech_boulder_debris[8];

void gunner_shot_unused(struct ShotObj* self)
{
}

void gunner_shot_update(struct ShotObj* self)
{
    gunner_shot_state_funcs[self->state](self);
}

// gunner_shot_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009A5F4(struct ShotObj* arg0);
void func_80099F48(struct ShotObj* arg0);
void func_8009A448(struct ShotObj* arg0);
void func_80099D54(struct ShotObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80099D54(struct ShotObj* arg0)
{
    u8 kind = (u8)arg0->unk2;

    arg0->unk58.animation_steps = D_80105FF0;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk42 &= 0x7FFF;
    arg0->x_pos.i.hi += gunner_shot_spawn_offsets[kind][0];
    arg0->x_vel.val *= 3;
    arg0->y_vel.val *= 3;
    arg0->unk54 = gunner_shot_hit_box;
    arg0->unk50.data = gunner_shot_hit_box;
    arg0->unk60 = 2;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk5C = 1;
    arg0->y_pos.i.hi += gunner_shot_spawn_offsets[kind][1];
    set_animation(arg0, 8);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_02_gunner_shot", func_80099D54);
#endif

void gunner_shot_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    if (engine_obj.stage == 0 && engine_obj.substage != 0 && self->x_pos.i.hi > 0xF40) {
        self->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }

    func_8002D9BC(self);
    if (func_8002BB80(self, &g_Player) == 0) {
        if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
            spawn_explosion(self);
            self->state = 2;
        }
        if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
            update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
            return;
        }
    }
    self->state = 2;
}

void gunner_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

// eregion_fireball_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80099F48(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;
    s32 target;
    s32 offset;
    s32 subtype = arg0->unk2;
    s32 angle;

    arg0->unk40 = owner->unk40;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->animation_table = owner->animation_table;
    arg0->unk3C = owner->unk3C;
    arg0->unk15 = owner->unk15;
    arg0->bg_offset = owner->bg_offset;
    arg0->x_pos.val = owner->x_pos.val
        + (owner->unk15 != 0 ? 0x530000 : -0x530000);
    arg0->y_pos.val = owner->y_pos.val;
    arg0->state = 1;
    arg0->on_screen = 1;

    if (subtype == 0) {
        angle = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
        set_velocity_from_angle(MOVING_OBJECT(arg0), angle & 0xFF);
        arg0->x_vel.val *= 4;
        arg0->y_vel.val *= 4;
    } else {
        offset = ((subtype - 1) * 11 << 17) - 0x200000;
        target = arg0->x_pos.val
            + (owner->unk15 != 0 ? offset : -offset);
        angle = angle_to_point(OBJECT_HEADER(arg0), target, 0x1E00000);
        set_velocity_from_angle(MOVING_OBJECT(arg0), angle & 0xFF);
        arg0->x_vel.val *= 8;
        arg0->y_vel.val *= 8;
    }

    arg0->unk68 = (struct Unk_unk68*)eregion_fireball_terrain_box;
    arg0->unk50.data = eregion_fireball_hit_box;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->unk16 = 0;
    arg0->unk54 = NULL;
    set_animation(ANIMATED_OBJECT(arg0), 0x17);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_02_gunner_shot", func_80099F48);
#endif

// eregion_fireball_fly
void func_8009A10C(struct ShotObj* self)
{
    struct WeaponObj* owner = self->unk7C;
    s32 target;
    s32 angle;

    func_8002D9BC(self);
    if (self->unk2 != 0) {
        if (owner->unk15 == 0) {
            s32 offset = FIXED((self->unk2 - 1) * 19) - FIXED(32);
            target = self->x_pos.val - offset;
            angle = angle_to_point(OBJECT_HEADER(self), target, FIXED(0x1E0));
        } else {
            s32 offset = FIXED((self->unk2 - 1) * 19) - FIXED(32);
            target = self->x_pos.val + offset;
            angle = angle_to_point(OBJECT_HEADER(self), target, FIXED(0x1E0));
        }
        set_velocity_from_angle(MOVING_OBJECT(self), angle & 0xFF);
        self->x_vel.val *= 8;
        self->y_vel.val *= 8;
    }
    if (func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(&g_Player)) == 0) {
        if ((self->unk70 & 8) != 0) {
            self->unk68 = NULL;
            self->state = 3;
        }
        animate_object(ANIMATED_OBJECT(self));
        move_object(MOVING_OBJECT(self));
        if (func_8002B1E8(BASE_OBJECT(self), 0x19, 0x19) == 0) {
            update_on_screen(BASE_OBJECT(self), 0x19, 0x19);
            return;
        }
    }
    self->state = 2;
}

void eregion_fireball_explode(struct ShotObj* self)
{
    if (self->unk5 == 0) {
        self->unk50.data = eregion_fireball_explode_box;
        set_animation(self, 0x18);
        spawn_rubble(8, eregion_fireball_debris[0], self, -1);
        self->unk60 = 3;
        self->unk5 = (u8)self->unk5 + 1;
    } else {
        func_8002D9BC(self);
        animate_object((struct AnimatedObj*)self);
        if (self->animation_step.fields.relative_step < 0) {
            self->state = 2;
            self->unk5 = 0;
        }
    }

    if (func_8002B1E8((struct BaseObj*)self, 0x19, 0x19) == 0) {
        update_on_screen((struct BaseObj*)self, 0x19, 0x19);
        return;
    }
    self->state = 2;
}

void eregion_fireball_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void eregion_fireball_update(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    CollisionRelated(self);
    eregion_fireball_state_funcs[self->state](self);
}

void eregion_wing_slash_update(struct ShotObj* self)
{
    if (self->unk7C->unk15 == 0) {
        self->x_pos.val = self->unk7C->x_pos.val + FIXED(-75);
    } else {
        self->x_pos.val = self->unk7C->x_pos.val + FIXED(75);
    }
    self->y_pos.val = self->unk7C->y_pos.val + FIXED(2);
    self->unk42 = self->unk7C->unk42;
    self->on_screen = 0;
    eregion_wing_slash_state_funcs[self->state](self);
}

// eregion_wing_slash_init
void func_8009A448(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;

    arg0->unk40 = owner->unk40;
    arg0->animation_table = owner->animation_table;
    arg0->unk3C = owner->unk3C;
    arg0->unk15 = owner->unk15;
    arg0->bg_offset = owner->bg_offset;
    arg0->state++;
    arg0->unk16 = VISUAL_SATURN_LAYER(5);
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk50.data = eregion_wing_slash_hit_box;
    arg0->unk5C = 0x7F;
    arg0->unk60 = 5;
    set_animation(ANIMATED_OBJECT(arg0), 0x14);
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}

void eregion_wing_slash_active(struct ShotObj* self)
{
    if (0 > self->animation_step.fields.event) {
        if (func_8002D9BC(self) == 1) {
            MAIN_OBJECT(self->unk7C)->ext.main_8.queued_sound = 0x1C;
        }
    }

    update_on_screen(BASE_OBJECT(self), 0x19, 0x19);

    if (self->unk7C->state == 1 && self->unk7C->unk5 == 5) {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 1) {
            return;
        }
    }

    self->state++;
}

void eregion_wing_slash_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void mech_boulder_update(struct ShotObj* self)
{
    mech_boulder_state_funcs[self->state](self);
}

// mech_boulder_init
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_02_gunner_shot", func_8009A5F4);
#else
void func_8009A5F4(struct ShotObj* arg0)
{
    arg0->unk42 &= 0x7FFF;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->x_pos.i.hi += arg0->unk15 != 0 ? 0x20 : -0x20;
    arg0->y_pos.i.hi += 0x18;
    arg0->y_vel.val = 0x70000;
    arg0->unk2C = 0x4200;
    arg0->unk16 = 0;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -0x2C000;
    else
        arg0->x_vel.val = 0x2C000;
    arg0->unk68 = NULL;
    arg0->unk54 = mech_boulder_shockwave_boxes;
    arg0->unk50.data = mech_boulder_shockwave_boxes;
    arg0->unk5C = 6;
    arg0->unk60 = 2;
    set_animation(arg0, 5);
}
#endif

void mech_boulder_fall(struct ShotObj* self)
{
    s8 previous_state;
    u32* collision_state;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    previous_state = g_Player.hp;
    func_8002D9BC(self);
    if (previous_state != g_Player.hp) {
        collision_state = self->unk84.collision_state;
        if (*collision_state == 0x8000) {
            *collision_state = 0x8001;
        }
    }

    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_debris(6, mech_boulder_debris, self);
        self->state = 2;
    } else {
        self->unk42 &= 0x7FFF;
    }

    if (func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(&g_Player)) != 0) {
        spawn_debris(6, mech_boulder_debris, self);
        self->state = 2;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
    } else {
        self->state = 2;
    }
}

void mech_boulder_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void mech_boulder_shockwave_start(struct ShotObj* self)
{
    self->state = 4;
    self->on_screen = 1;
    self->unk16 = 0;
    self->unk68 = NULL;
    self->unk42 &= 0x7FFF;
    if (self->unk15 == 0) {
        self->x_pos.i.hi = (u16)self->x_pos.i.hi - 0x19;
    } else {
        self->x_pos.i.hi = (u16)self->x_pos.i.hi + 0x19;
    }
    self->unk5C = 1;
    self->unk60 = 2;
    self->y_pos.i.hi = (u16)self->y_pos.i.hi + 0x21;
    set_animation(self, 4);
}

void mech_boulder_shockwave(struct ShotObj* self)
{
    s32* collision_state;
    s8 player_active;

    animate_object(ANIMATED_OBJECT(self));
    self->unk54 = (u8*)&mech_boulder_shockwave_boxes_tail[self->animation_step.fields.frame_index - 20];
    self->unk50.data = (u8*)&mech_boulder_shockwave_boxes_tail[self->animation_step.fields.frame_index - 20];
    player_active = g_Player.hp;
    func_8002D9BC(self);
    if (player_active != g_Player.hp) {
        collision_state = (s32*)self->unk84.collision_state;
        if (*collision_state == 0x8000) {
            *collision_state = 0x8001;
        }
    }
    if ((func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) && (self->animation_step.fields.event == 0)) {
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
        return;
    }
    self->state = 5;
}

void mech_boulder_shockwave_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

extern void (*mech_boulder_state_funcs[])(struct ShotObj*);
