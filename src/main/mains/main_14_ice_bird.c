// MainObj, main_object_update_funcs[14]
// 8004CF24..8004D930
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_14_ice_bird.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"

extern struct Unk_unk68 ice_bird_charge_box;

extern u8 ice_bird_debris[];

void ice_bird_spawn_charge_ring(struct MainObj*, s8);

// ice_bird_state_funcs
void ice_bird_init(struct MainObj*);

// ice_bird_step_funcs
extern void (*ice_bird_step_funcs[6])();
void ice_bird_resume_step(struct MainObj* arg0);
void ice_bird_fly_in(struct MainObj* arg0);
void ice_bird_charge(struct MainObj* arg0);
void ice_bird_blast(struct MainObj* arg0);
void ice_bird_leave(struct MainObj* arg0);

void ice_bird_fly_in_move(struct MainObj*);

// ice_bird_charge_funcs
void ice_bird_charge_start(struct MainObj*);
void ice_bird_charge_wait(struct MainObj*);
void ice_bird_charge_ring(struct MainObj*);

// ice_bird_blast_funcs
void ice_bird_blast_start(struct MainObj* arg0);
void ice_bird_blast_wait(struct MainObj*);

void ice_bird_blast_finish(struct MainObj*);

void ice_bird_leave_fly(struct MainObj* arg0);

extern void (*ice_bird_state_funcs[])(struct MainObj*);
extern void (*ice_bird_fly_in_funcs[])(struct MainObj*);
extern void (*ice_bird_charge_funcs[])(struct MainObj*);
extern void (*ice_bird_blast_funcs[])(struct MainObj*);
extern void (*ice_bird_leave_funcs[])(struct MainObj*);

void ice_bird_update(struct MainObj* self)
{
    ice_bird_state_funcs[self->state](self);
}

void ice_bird_init(struct MainObj* self)
{
    self->active = 0x41;
    self->hp = 0xE;
    self->contact_damage = 3;
    self->invincibility_timer = 0;

    self->bg_offset = g_Player.bg_offset;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;

    self->collision_data = D_80106974;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->animation_table = (const u8* const*)ice_bird_animations;
    self->unk16 = VISUAL_SATURN_LAYER(5);
    self->terrain_box = 0;
    self->hurt_box = &ice_bird_body_box;
    self->attack_box = &ice_bird_body_box;
    ice_bird_face_player(ANIMATED_OBJECT(self));
    set_animation(self, 0);
    self->ext.main_14.unk80 = 0;
    self->ext.main_14.unk84 = 0;
    self->ext.main_14.visual_variant = 0;
    self->ext.main_14.unk8C = 0;
    self->ext.main_14.saved_unk5 = 0;
    self->ext.main_14.unk94 = 0;
    self->state++;
    self->unk5 = 2;
    self->unk6 = 0;
}

void ice_bird_main(struct MainObj* self)
{
    s32 collision;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    ice_bird_step_funcs[self->unk5](self);
    func_8004D6FC(self);
    func_8002D9BC(self);
    collision = func_8002DD04(self);
    if (self->unk5 != 0) {
        self->ext.main_14.saved_unk5 = self->unk5;
    }
    if (collision < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(6, ice_bird_debris, self);
        drop_item(BASE_OBJECT(self), 8);
    } else {
        if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
            update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
            return;
        }
        if (self->x_pos.val > g_Player.x_pos.val && self->ext.main_14.unk8C == 0) {
            self->ext.main_14.unk94 = 1;
        }
    }
    self->state = 2;
}

void ice_bird_despawn(struct MainObj* self)
{
    self->ext.main_14.unk80 = 0;
    self->ext.main_14.unk84 = 0;
    engine_obj.character_state.bytes[0] = 0;
    STOP_SOUND(2, 0x40, 0x6);
    if (self->ext.main_14.unk94 != 0) {
        despawn_object(OBJECT_HEADER(self));
        return;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void ice_bird_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_14.saved_unk5;
}

void ice_bird_fly_in(struct MainObj* self)
{
    ice_bird_fly_in_funcs[self->unk6](self);
}

void ice_bird_fly_in_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    ice_bird_spawn_charge_ring(self, 3);
    func_8001540C(2, SATURN_SOUND(0x40, 0x3E), self);

    self->ext.main_14.unk80 = 0x20;
    self->ext.main_14.unk84 = 1;
    self->x_speed = ice_bird_fly_speeds[(self->unk15 & PLAYER_FACING_RIGHT) ? 1 : 0];
    self->unk6++;
}

void ice_bird_fly_in_move(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (--self->ext.main_14.unk80 == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void ice_bird_charge(struct MainObj* self)
{
    ice_bird_charge_funcs[self->unk6](self);
}

void ice_bird_charge_start(struct MainObj* self)
{
    set_animation(self, 1);
    self->x_speed = 0;
    self->ext.main_14.unk80 = 0x2E;
    self->hurt_box = (const u8*)&ice_bird_charge_box;
    self->attack_box = (const u8*)&ice_bird_charge_box;
    self->unk6++;
}

void ice_bird_charge_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_14.unk80 == 0) {
        set_animation(self, 2);
        self->unk6++;
    }
}

void ice_bird_charge_ring(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->ext.main_14.visual_variant == 7) {
        self->unk5 = 4;
        self->unk6 = 0;
    }
}

void ice_bird_blast(struct MainObj* self)
{
    ice_bird_blast_funcs[self->unk6](self);
}

void ice_bird_blast_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->ext.main_14.unk80 = 0xC;
    self->unk6++;
}

void ice_bird_blast_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_14.unk80 == 0) {
        self->ext.main_14.visual_variant = 0xFF;
        self->unk6++;
    }
}

void ice_bird_blast_release(struct MainObj* self)
{
    struct EffectObj* effect;

    effect = find_free_effect_obj();
    if (effect != 0) {
        effect->active = 1;
        effect->id = 0x11;
        effect->unk2 = self->unk2;
        effect->on_screen = 0;
        effect->state = 0;
        effect->unk5 = 0;
        effect->unk6 = 0;
        effect->unk7 = 0;
        effect->x_pos.val = self->x_pos.val;
        effect->y_pos.val = self->y_pos.val;
        effect->ext.effect_17.source = ANIMATED_OBJECT(self);
    }

    animate_object(ANIMATED_OBJECT(self));
    STOP_SOUND(2, 0x40, 0x6);
    func_8001540C(2, SATURN_SOUND(0x41, 0x3F), self);
    ice_bird_spawn_ice_shards(ANIMATED_OBJECT(self));
    self->unk6++;
}

void ice_bird_blast_finish(struct MainObj* self)
{
    self->ext.main_14.unk8C = 1;
    func_8001540C(5, SATURN_SOUND(4, 0x25), self);
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 0);
    self->unk6 = 0;
    self->unk5++;
}

void ice_bird_leave(struct MainObj* self)
{
    ice_bird_leave_funcs[self->unk6](self);
}

void ice_bird_leave_start(struct MainObj* self)
{
    set_animation(self, 0);
    animate_object(ANIMATED_OBJECT(self));

    self->x_speed = ice_bird_fly_speeds[(self->unk15 & PLAYER_FACING_RIGHT) != 0];
    self->hurt_box = (const u8*)&ice_bird_body_box;
    self->attack_box = (const u8*)&ice_bird_body_box;
    engine_obj.character_state.bytes[0] = 0;
    self->unk6++;
}

void ice_bird_leave_fly(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void ice_bird_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
}

// ice_bird_check_player_ahead

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004D6FC(struct MainObj* self);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004D6FC(struct MainObj* self)
{
    struct Main14Ext* ext = &self->ext.main_14;

    if (self->unk5 == 2 || self->unk5 == 5)
        return;
    if (--ext->unk84 != 0)
        return;
    if (ext->visual_variant >= 7)
        return;
    switch (++ext->visual_variant) {
    case 4:
        ext->unk84 = 0x1E;
        break;
    case 5:
        ext->unk84 = 0x14;
        break;
    case 6:
        ext->unk84 = 0x32;
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_14_ice_bird", func_8004D6FC);
#endif

void ice_bird_spawn_charge_ring(struct MainObj* self, s8 arg1)
{
    struct VisualObj* temp_v0;

    temp_v0 = find_free_visual_obj();
    if (temp_v0 != 0) {
        temp_v0->unk50 = PLAYER_OBJECT(self);
        temp_v0->active = 0x41;
        temp_v0->unk2 = arg1;
        temp_v0->id = 0xB;
        self->ext.main_14.visual_variant = arg1;
        temp_v0->state = 0;
        temp_v0->unk5 = 0;
        temp_v0->unk6 = 0;
        temp_v0->unk38 = 0;
        temp_v0->unk3C = ANIMATED_OBJECT(self)->unk3C;
        temp_v0->animation_table = ANIMATED_OBJECT(self)->animation_table;
        temp_v0->unk40 = self->unk40;
        temp_v0->unk42 = self->unk42;
        temp_v0->unk16 = VISUAL_SATURN_LAYER(4);
        temp_v0->x_pos.val = self->x_pos.val;
        temp_v0->y_pos.val = self->y_pos.val;
    }
}

void ice_bird_spawn_ice_shards(struct AnimatedObj* self)
{
    struct VisualObj* visual_obj;
    u32 i;
    u32 j;

    for (j = 0; j < 3; j++) {
        for (i = 0; i < 4; i++) {
            visual_obj = find_free_visual_obj();
            if (visual_obj == NULL) {
                return;
            }

            visual_obj->unk50 = PLAYER_OBJECT(self);
            visual_obj->active = 0x41;
            visual_obj->id = 8;
            visual_obj->unk2 = i;
            visual_obj->state = 0;
            visual_obj->unk5 = 0;
            visual_obj->unk6 = 0;
            visual_obj->bg_offset = self->bg_offset;
            visual_obj->unk38 = 0;
            visual_obj->unk3C = self->unk3C;
            visual_obj->animation_table = self->animation_table;
            visual_obj->unk40 = self->unk40;
            visual_obj->unk42 = self->unk42;
            visual_obj->unk16 = VISUAL_SATURN_LAYER(6);
            visual_obj->x_pos.val = self->x_pos.val;
            visual_obj->y_pos.val = self->y_pos.val;
        }
    }
}

struct Unk_unk68 ice_bird_body_box = { -10, -15, 32, 25 };

struct Unk_unk68 ice_bird_charge_box = { -9, -25, 28, 48 };

struct Unk_unk68 D_800FB894 = { -27, -25, 33, 52 };

struct Unk_unk68 D_800FB898 = { -10, 27, 26, 3 };

s32 ice_bird_fly_speeds[] = {
    (s32)0xFFFE0000,
    (s32)0x00020000,
};

union AnimationStep ice_bird_anim_0[] = {
    { 5, 0, 1, 0x00 },
    { 4, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 4, 0, 1, 0x03 },
    { 5, 0, 1, 0x04 },
    { 4, 0, 1, 0x03 },
    { 3, 0, 1, 0x05 },
    { 4, 0, -7, 0x01 },
};

union AnimationStep ice_bird_anim_1[] = {
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x08 },
    { 6, 0, 1, 0x09 },
    { 8, 0, 1, 0x0A },
    { 3, 0, 1, 0x0B },
    { 3, 0, 1, 0x0C },
    { 3, 0, 1, 0x0D },
    { 3, 0, 1, 0x0E },
    { 3, 0, 1, 0x0F },
    { 5, 0, 1, 0x10 },
    { 3, 0, 1, 0x0F },
    { 3, 0, 0, 0x0E },
};

union AnimationStep ice_bird_anim_2[] = {
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x11 },
    { 1, 0, -3, 0x12 },
};

union AnimationStep ice_bird_anim_3[] = {
    { 6, 0, 1, 0x13 },
    { 6, 0, 1, 0x14 },
    { 6, 0, 1, 0x15 },
    { 6, 0, -3, 0x16 },
};

union AnimationStep ice_bird_anim_4[] = {
    { 4, 0, 1, 0x17 },
    { 4, 0, 1, 0x18 },
    { 4, 0, 1, 0x19 },
    { 4, 0, -3, 0x1A },
};

union AnimationStep ice_bird_anim_5[] = {
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x1D },
    { 2, 0, -3, 0x1E },
};

union AnimationStep ice_bird_anim_6[] = {
    { 1, 0, 1, 0x1F },
    { 1, 0, 1, 0x20 },
    { 1, 0, 1, 0x21 },
    { 1, 0, -3, 0x22 },
};

union AnimationStep ice_bird_anim_7[] = {
    { 3, 0, 1, 0x28 },
    { 3, 0, 1, 0x23 },
    { 2, 0, 1, 0x24 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x3A },
    { 2, 0, 1, 0x39 },
    { 2, 0, 0, 0x3B },
};

union AnimationStep ice_bird_anim_8[] = {
    { 1, 0, 0, 0x29 },
};

union AnimationStep ice_bird_anim_9[] = {
    { 1, 0, 0, 0x2A },
};

union AnimationStep ice_bird_anim_10[] = {
    { 1, 0, 0, 0x2B },
};

union AnimationStep ice_bird_anim_11[] = {
    { 1, 0, 0, 0x2C },
};

union AnimationStep ice_bird_anim_12[] = {
    { 1, 0, 0, 0x2D },
};

union AnimationStep ice_bird_anim_13[] = {
    { 1, 0, 0, 0x2E },
};

union AnimationStep ice_bird_anim_14[] = {
    { 5, 0, 1, 0x2F },
    { 4, 0, 1, 0x30 },
    { 3, 0, 1, 0x31 },
    { 4, 0, -3, 0x32 },
};

union AnimationStep ice_bird_anim_15[] = {
    { 1, 0, 0, 0x33 },
};

union AnimationStep ice_bird_anim_16[] = {
    { 1, 0, 0, 0x34 },
};

union AnimationStep ice_bird_anim_17[] = {
    { 5, 0, 1, 0x35 },
    { 5, 0, 1, 0x36 },
    { 5, 0, 1, 0x37 },
    { 5, 0, -3, 0x38 },
};

union AnimationStep* ice_bird_animations[] = {
    ice_bird_anim_0,
    ice_bird_anim_1,
    ice_bird_anim_2,
    ice_bird_anim_3,
    ice_bird_anim_4,
    ice_bird_anim_5,
    ice_bird_anim_6,
    ice_bird_anim_7,
    ice_bird_anim_8,
    ice_bird_anim_9,
    ice_bird_anim_10,
    ice_bird_anim_11,
    ice_bird_anim_12,
    ice_bird_anim_13,
    ice_bird_anim_14,
    ice_bird_anim_15,
    ice_bird_anim_16,
    ice_bird_anim_17,
};

u8 ice_bird_debris[] = {
    0x08,
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x00,
    0x00,
};

void (*ice_bird_state_funcs[])(struct MainObj*) = {
    ice_bird_init,
    ice_bird_main,
    ice_bird_despawn,
};

void (*ice_bird_step_funcs[6])() = {
    enemy_hit_reaction,
    ice_bird_resume_step,
    ice_bird_fly_in,
    ice_bird_charge,
    ice_bird_blast,
    ice_bird_leave,
};

void (*ice_bird_fly_in_funcs[2])() = {
    ice_bird_fly_in_start,
    ice_bird_fly_in_move,
};

void (*ice_bird_charge_funcs[3])() = {
    ice_bird_charge_start,
    ice_bird_charge_wait,
    ice_bird_charge_ring,
};

void (*ice_bird_blast_funcs[4])(struct MainObj*) = {
    ice_bird_blast_start,
    ice_bird_blast_wait,
    ice_bird_blast_release,
    ice_bird_blast_finish,
};

void (*ice_bird_leave_funcs[2])() = {
    ice_bird_leave_start,
    ice_bird_leave_fly,
};
