// MainObj, main_object_update_funcs[14]
// 8004CF24..8004D930
#include "common.h"
#include "func_tables.h"

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
    self->unk16 = 5;
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
    stop_sound(2, 0x40);
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
    func_8001540C(2, 0x40, self);

    self->ext.main_14.unk80 = 0x20;
    self->ext.main_14.unk84 = 1;
    self->x_speed = ice_bird_fly_speeds[(self->unk15 & 0x40) ? 1 : 0];
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
    stop_sound(2, 0x40);
    func_8001540C(2, 0x41, self);
    ice_bird_spawn_ice_shards(ANIMATED_OBJECT(self));
    self->unk6++;
}

void ice_bird_blast_finish(struct MainObj* self)
{
    self->ext.main_14.unk8C = 1;
    func_8001540C(5, 4, self);
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

    self->x_speed = ice_bird_fly_speeds[(self->unk15 & 0x40) != 0];
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
        self->unk15 = 0x40;
    }
}

// ice_bird_check_player_ahead
INCLUDE_ASM("main/nonmatchings/mains/main_14_ice_bird", func_8004D6FC);

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
        temp_v0->unk16 = 4;
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
            visual_obj->unk16 = 6;
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
    { 0x00010005 },
    { 0x01010004 },
    { 0x02010003 },
    { 0x03010004 },
    { 0x04010005 },
    { 0x03010004 },
    { 0x05010003 },
    { 0x01F90004 },
};

union AnimationStep ice_bird_anim_1[] = {
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010006 },
    { 0x0A010008 },
    { 0x0B010003 },
    { 0x0C010003 },
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F010003 },
    { 0x10010005 },
    { 0x0F010003 },
    { 0x0E000003 },
};

union AnimationStep ice_bird_anim_2[] = {
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x11010001 },
    { 0x12FD0001 },
};

union AnimationStep ice_bird_anim_3[] = {
    { 0x13010006 },
    { 0x14010006 },
    { 0x15010006 },
    { 0x16FD0006 },
};

union AnimationStep ice_bird_anim_4[] = {
    { 0x17010004 },
    { 0x18010004 },
    { 0x19010004 },
    { 0x1AFD0004 },
};

union AnimationStep ice_bird_anim_5[] = {
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1EFD0002 },
};

union AnimationStep ice_bird_anim_6[] = {
    { 0x1F010001 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x22FD0001 },
};

union AnimationStep ice_bird_anim_7[] = {
    { 0x28010003 },
    { 0x23010003 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x3A010002 },
    { 0x39010002 },
    { 0x3B000002 },
};

union AnimationStep ice_bird_anim_8[] = {
    { 0x29000001 },
};

union AnimationStep ice_bird_anim_9[] = {
    { 0x2A000001 },
};

union AnimationStep ice_bird_anim_10[] = {
    { 0x2B000001 },
};

union AnimationStep ice_bird_anim_11[] = {
    { 0x2C000001 },
};

union AnimationStep ice_bird_anim_12[] = {
    { 0x2D000001 },
};

union AnimationStep ice_bird_anim_13[] = {
    { 0x2E000001 },
};

union AnimationStep ice_bird_anim_14[] = {
    { 0x2F010005 },
    { 0x30010004 },
    { 0x31010003 },
    { 0x32FD0004 },
};

union AnimationStep ice_bird_anim_15[] = {
    { 0x33000001 },
};

union AnimationStep ice_bird_anim_16[] = {
    { 0x34000001 },
};

union AnimationStep ice_bird_anim_17[] = {
    { 0x35010005 },
    { 0x36010005 },
    { 0x37010005 },
    { 0x38FD0005 },
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
