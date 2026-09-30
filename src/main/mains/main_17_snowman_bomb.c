// MainObj, main_object_update_funcs[17]
// 8004FF90..80050708
#include "common.h"
#include "func_tables.h"

void snowman_bomb_update(struct MainObj* self)
{
    snowman_bomb_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

void snowman_bomb_init(struct MainObj* self)
{
    self->hp = 6;
    self->contact_damage = 2;
    self->invincibility_timer = 0;
    self->collision_data = D_80106AF4;
    self->bg_offset = (u8)g_Player.bg_offset;
    self->unk16 = 6;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->animation_table = (const u8* const*)snowman_bomb_animations;
    self->terrain_box = &snowman_bomb_terrain_box;
    self->hurt_box = &snowman_bomb_hurt_box;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->attack_box = &snowman_bomb_attack_box;
    snowman_bomb_face_player(ANIMATED_OBJECT(self));
    set_animation(self, 0);
    self->ext.main_17.unk80 = 4;
    self->ext.main_17.unk84 = 3;
    self->ext.main_17.unk88 = 0xC;
    self->ext.main_17.unk8C = 0;
    self->state = 1;
    self->unk5 = 2;
    self->unk6 = 0;
    self->ext.main_17.saved_unk5 = self->y_pos.val;
}

void snowman_bomb_main(struct MainObj* self)
{
    s32 collision;

    snowman_bomb_check_fall(self);
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    snowman_bomb_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    self->ext.main_17.unk90 = self->unk5;
    collision = func_8002DD04(self);
    if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi + self->terrain_box->unk0,
            self->terrain_box->unk3 + (self->y_pos.i.hi + self->terrain_box->unk1))
        == 0x3E) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, snowman_bomb_debris, self);
    } else if (collision < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, snowman_bomb_debris, self);
        drop_item(BASE_OBJECT(self), 0);
    } else if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }
    self->state = 2;
}

void snowman_bomb_despawn(struct MainObj* self)
{
    self->ext.main_17.unk80 = 0;
    self->ext.main_17.unk84 = 0;
    self->ext.main_17.unk88 = 0;
    self->ext.main_17.unk8C = 0;
    self->ext.main_17.unk90 = 0;
    self->ext.main_17.saved_unk5 = 0;
    despawn_object(OBJECT_HEADER(self));
}

void snowman_bomb_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.raw[4];
}

// snowman_bomb_hop
INCLUDE_ASM("main/nonmatchings/mains/main_17_snowman_bomb", func_80050278);

void snowman_bomb_turn(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        snowman_bomb_face_player(ANIMATED_OBJECT(self));
        self->unk5 = 2;
        self->unk6 = 0;
        self->ext.main_17.unk80 = 4;
        self->ext.main_17.unk84 = 3;
        set_animation(self, 0);
    }
}

void snowman_bomb_detonate(struct MainObj* self)
{
    if (self->x_speed != 0) {
        move_with_gravity(ANIMATED_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->terrain_box = &snowman_bomb_blast_terrain_box;
        self->hurt_box = &snowman_bomb_blast_hurt_box;
        self->attack_box = &snowman_bomb_blast_attack_box;
    }
    if (self->animation_step.fields.event == 1) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, snowman_bomb_debris, self);
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
        set_animation(self, 0);
    }
}

void snowman_bomb_fall(struct MainObj* self)
{
    s32 distance;
    s32 target_y;
    s32 current_y;

    if (self->collision_flags & 8) {
        if (self->ext.main_17.unk8C != 0) {
            self->unk5 = 4;
            self->unk6 = 0;
            self->air_state = 0;
        } else {
            set_animation(self, 0);
            target_y = self->ext.main_17.saved_unk5;
            current_y = self->y_pos.val;
            distance = target_y - current_y;
            self->unk5 = 2;
            self->unk6 = 0;
            self->y_speed = 0;
            self->gravity = 0;
            self->x_speed = 0;
            self->x_accel = 0;
            self->air_state = 0;
            if (distance >= 0 ? distance > 0x7FFFF : current_y - target_y >= 0x80000) {
                self->ext.main_17.unk80 = 4;
                self->ext.main_17.unk84 = 3;
                self->ext.main_17.unk88 = 0xC;
            }
        }
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->x_speed == 0) {
            self->x_accel = 0;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void snowman_bomb_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->ext.main_17.unk80 = 4;
        set_animation(self, 0);
    }
}

void snowman_bomb_check_fall(struct MainObj* self)
{
    if (self->air_state == 0 && !(self->collision_flags & 8)) {
        self->unk5 = 5;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = 0x4200;
        self->air_state = 1;
    }
}

void snowman_bomb_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

struct Unk_unk68 snowman_bomb_hurt_box = { -8, -13, 15, 26 };

struct Unk_unk68 snowman_bomb_attack_box = { -7, -11, 12, 22 };

struct Unk_unk68 snowman_bomb_terrain_box = { 0, 0, 5, 13 };

struct Unk_unk68 snowman_bomb_blast_hurt_box = { -12, -1, 25, 13 };

struct Unk_unk68 snowman_bomb_blast_attack_box = { -10, 1, 21, 10 };

struct Unk_unk68 snowman_bomb_blast_terrain_box = { 0, 5, 13, 8 };

union AnimationStep snowman_bomb_anim_0[] = {
    { 0x00010008 },
    { 0x03010003 },
    { 0x04010004 },
    { 0x05010006 },
    { 0x04010004 },
    { 0x03010002 },
    { 0x03000101 },
};

union AnimationStep snowman_bomb_anim_1[] = {
    { 0x0001000C },
    { 0x01010006 },
    { 0x0201000C },
    { 0x01010006 },
    { 0x0001000C },
    { 0x01010006 },
    { 0x0201000C },
    { 0x01010006 },
    { 0x0001000B },
    { 0x0000010C },
};

union AnimationStep snowman_bomb_anim_2[] = {
    { 0x06010005 },
    { 0x07010004 },
    { 0x08010004 },
    { 0x07010204 },
    { 0x0901003C },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0901001D },
    { 0x09000101 },
};

union AnimationStep snowman_bomb_anim_3[] = {
    { 0x0B000101 },
};

union AnimationStep snowman_bomb_anim_4[] = {
    { 0x0C000101 },
};

union AnimationStep snowman_bomb_anim_5[] = {
    { 0x0D000101 },
};

union AnimationStep snowman_bomb_anim_6[] = {
    { 0x0E000101 },
};

union AnimationStep* snowman_bomb_animations[7] = {
    snowman_bomb_anim_0,
    snowman_bomb_anim_1,
    snowman_bomb_anim_2,
    snowman_bomb_anim_3,
    snowman_bomb_anim_4,
    snowman_bomb_anim_5,
    snowman_bomb_anim_6,
};

u8 snowman_bomb_debris[4] = { 3, 4, 5, 6 };

void (*snowman_bomb_state_funcs[3])() = {
    snowman_bomb_init,
    snowman_bomb_main,
    snowman_bomb_despawn,
};

void (*snowman_bomb_step_funcs[7])(struct MainObj*) = {
    enemy_hit_reaction,
    snowman_bomb_resume_step,
    func_80050278,
    snowman_bomb_turn,
    snowman_bomb_detonate,
    snowman_bomb_fall,
    snowman_bomb_wait,
};
