// ShotObj, shot_object_update_funcs[2, 3, 4, 5]
// 80099D10..8009A984
#include "common.h"

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
INCLUDE_ASM("main/nonmatchings/shots/shot_02_gunner_shot", func_80099D54);

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
INCLUDE_ASM("main/nonmatchings/shots/shot_02_gunner_shot", func_80099F48);

// eregion_fireball_fly
INCLUDE_ASM("main/nonmatchings/shots/shot_02_gunner_shot", func_8009A10C);

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
INCLUDE_ASM("main/nonmatchings/shots/shot_02_gunner_shot", func_8009A448);

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
INCLUDE_ASM("main/nonmatchings/shots/shot_02_gunner_shot", func_8009A5F4);

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
