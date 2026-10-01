// MainObj, main_object_update_funcs[13]
// 8004C734..8004CF24
#include "common.h"
#include "func_tables.h"

void heavy_mech_update(struct MainObj* self)
{
    heavy_mech_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_13_heavy_mech", heavy_mech_init);
#else
void heavy_mech_init(struct MainObj* self)
{
    self->hp = 0x10;
    self->contact_damage = 3;
    self->invincibility_timer = 0;
    self->collision_data = D_801068F0;
    self->bg_offset = g_Player.bg_offset;
    self->animation_table = (const u8* const*)heavy_mech_animations;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->unk16 = 6;
    self->terrain_box = &heavy_mech_terrain_box;
    self->hurt_box = &heavy_mech_hurt_box;
    self->attack_box = &heavy_mech_attack_box;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    heavy_mech_face_player(ANIMATED_OBJECT(self));
    set_animation(self, 0);
    self->ext.main_13.unk80 = 0x8000;
    self->state = 1;
    self->ext.main_13.unk84 = 0;
    self->unk5 = 2;
    self->unk6 = 0;
}
#endif

// heavy_mech_main
INCLUDE_ASM("main/nonmatchings/mains/main_13_heavy_mech", func_8004C860);

void heavy_mech_explode(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->state = 3;
    } else if (--self->unk7E == 0) {
        self->unk7E = 6;
        func_800AF878(self, 1, 24, 32);
    }
}

void heavy_mech_despawn(struct MainObj* self)
{
    self->ext.main_13.unk80 = 0;
    self->ext.main_13.unk84 = 0;
    self->ext.main_13.unk88 = 0;
    self->ext.main_13.saved_unk5 = 0;
    despawn_object(OBJECT_HEADER(self));
}

void heavy_mech_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_13.saved_unk5;
}

void heavy_mech_idle(struct MainObj* self)
{
    heavy_mech_idle_funcs[self->unk6](self);
}

void heavy_mech_idle_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->unk7C = 0x3C;
    self->unk6 = 1;
}

// heavy_mech_idle_wait
INCLUDE_ASM("main/nonmatchings/mains/main_13_heavy_mech", func_8004CA94);

void heavy_mech_fall(struct MainObj* self)
{
    if (self->collision_flags & 8) {
        if (self->ext.main_13.unk80 == 0x8000) {
            heavy_mech_face_player(ANIMATED_OBJECT(self));
        }
        set_animation(self, 0);
        self->unk5 = 2;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->x_speed = 0;
        self->x_accel = 0;
        self->air_state = 0;
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
}

void heavy_mech_throw(struct MainObj* self)
{
    heavy_mech_throw_funcs[self->unk6](self);
}

void heavy_mech_throw_anim(struct MainObj* self)
{
    struct ShotObj* shot;
    s8 event;

    animate_object(ANIMATED_OBJECT(self));
    event = self->animation_step.fields.event;
    switch (event) {
    case 1:
        set_animation(self, 0);
        self->ext.main_13.unk88 = 0;
        self->unk5 = 2;
        self->unk6 = 0;
        break;
    case 2:
        func_8001540C(2, 0x31, self);
        if (self->animation_step.fields.event != 0) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 5;
                shot->unk2 = 0;
                shot->unk40 = self->unk40;
                shot->unk42 = self->unk42;
                shot->animation_table = (u32**)self->animation_table;
                shot->unk3C = (void*)self->sprite_frames;
                shot->unk15 = self->unk15;
                shot->bg_offset = self->bg_offset;
                shot->x_pos.val = self->x_pos.val;
                shot->y_pos.val = self->y_pos.val;
                shot->unk84.collision_state = &self->ext.main_13.unk80;
                if (self->ext.main_13.unk88 == event) {
                    shot->state = 3;
                }
            }
        }
        break;
    }
}

void heavy_mech_stomp(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        start_screen_shake_x(8, 4, 1);
    }
    if (self->animation_step.fields.event == 1) {
        if (self->ext.main_13.unk80 == 0x8000) {
            set_animation(self, 0);
        }
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void heavy_mech_check_fall(struct MainObj* self)
{
    if (self->air_state == 0 && !(self->collision_flags & 8)) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->x_accel = 0;
        self->air_state = 1;
    }
}

void heavy_mech_check_catch(struct MainObj* self)
{
    if (self->unk5 != 5 && self->ext.main_13.unk80 == 0x8001) {
        set_animation(self, 3);
        self->ext.main_13.unk80 = 0x8000;
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void heavy_mech_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

struct Unk_unk68 heavy_mech_hurt_box = { -21, -23, 39, 50 };

struct Unk_unk68 heavy_mech_attack_box = { -18, -21, 33, 46 };

struct Unk_unk68 heavy_mech_terrain_box = { 0, 27, 26, 3 };

union AnimationStep heavy_mech_anim_0[] = {
    { 0x0001000C },
    { 0x0101000C },
    { 0x0201000C },
    { 0x0301000C },
    { 0x0001000C },
    { 0x0101000C },
    { 0x0201000C },
    { 0x0301000C },
    { 0x0401000C },
    { 0x0501000C },
    { 0x0201000C },
    { 0x0301000C },
    { 0x0401000C },
    { 0x0501000C },
    { 0x0201000C },
    { 0x03F1010C },
};

union AnimationStep heavy_mech_anim_1[] = {
    { 0x0601000A },
    { 0x07010006 },
    { 0x0801000E },
    { 0x0901000D },
    { 0x0D010201 },
    { 0x0D010004 },
    { 0x0A01000E },
    { 0x0B010009 },
    { 0x0B000101 },
};

union AnimationStep heavy_mech_anim_2[] = {
    { 0x0601000A },
    { 0x0E010008 },
    { 0x0F010010 },
    { 0x10010008 },
    { 0x11010201 },
    { 0x11010001 },
    { 0x1201000E },
    { 0x13010009 },
    { 0x13000101 },
};

union AnimationStep heavy_mech_anim_3[] = {
    { 0x1B010010 },
    { 0x1C010212 },
    { 0x1B01000C },
    { 0x1A010212 },
    { 0x1B01000C },
    { 0x1C010212 },
    { 0x1B01000C },
    { 0x1A010211 },
    { 0x1A000101 },
};

union AnimationStep heavy_mech_anim_4[] = {
    { 0x14010003 },
    { 0x15010010 },
    { 0x16010004 },
    { 0x17010005 },
    { 0x18010006 },
    { 0x19010006 },
    { 0x19000101 },
};

union AnimationStep heavy_mech_anim_5[] = {
    { 0x0C000101 },
};

union AnimationStep heavy_mech_anim_6[] = {
    { 0x1D000101 },
};

union AnimationStep heavy_mech_anim_7[] = {
    { 0x1E000101 },
};

union AnimationStep heavy_mech_anim_8[] = {
    { 0x1F000101 },
};

union AnimationStep heavy_mech_anim_9[] = {
    { 0x20000101 },
};

union AnimationStep heavy_mech_anim_10[] = {
    { 0x21000101 },
};

union AnimationStep heavy_mech_anim_11[] = {
    { 0x22000101 },
};

union AnimationStep heavy_mech_anim_12[] = {
    { 0x24000101 },
};

union AnimationStep heavy_mech_anim_13[] = {
    { 0x25000101 },
};

union AnimationStep heavy_mech_anim_14[] = {
    { 0x26000101 },
};

union AnimationStep heavy_mech_anim_15[] = {
    { 0x23000101 },
};

union AnimationStep heavy_mech_anim_16[] = {
    { 0x27000101 },
};

union AnimationStep heavy_mech_anim_17[] = {
    { 0x28000101 },
};

union AnimationStep* heavy_mech_animations[] = {
    heavy_mech_anim_0,
    heavy_mech_anim_1,
    heavy_mech_anim_2,
    heavy_mech_anim_3,
    heavy_mech_anim_4,
    heavy_mech_anim_5,
    heavy_mech_anim_6,
    heavy_mech_anim_7,
    heavy_mech_anim_8,
    heavy_mech_anim_9,
    heavy_mech_anim_10,
    heavy_mech_anim_11,
    heavy_mech_anim_12,
    heavy_mech_anim_13,
    heavy_mech_anim_14,
    heavy_mech_anim_15,
    heavy_mech_anim_16,
    heavy_mech_anim_17,
};

u8 heavy_mech_debris[] = {
    0x06,
    0x07,
    0x08,
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x00,
    0x00,
    0x00,
};

void (*heavy_mech_state_funcs[])() = {
    heavy_mech_init,
    func_8004C860,
    heavy_mech_explode,
    heavy_mech_despawn,
};

void (*heavy_mech_step_funcs[])() = {
    enemy_hit_reaction,
    heavy_mech_resume_step,
    heavy_mech_idle,
    heavy_mech_fall,
    heavy_mech_throw,
    heavy_mech_stomp,
};

void (*heavy_mech_idle_funcs[])() = {
    heavy_mech_idle_start,
    func_8004CA94,
};

void (*heavy_mech_throw_funcs[])() = {
    heavy_mech_throw_anim,
};
