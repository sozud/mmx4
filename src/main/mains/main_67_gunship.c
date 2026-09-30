// MainObj, main_object_update_funcs[67]
// 80082434..80083218
#include "common.h"
#include "func_tables.h"

void gunship_spawn_missiles(struct VisualObj* arg0);

void gunship_update(struct MainObj* self)
{
    gunship_state_funcs[self->state](self);
}

// gunship_init
void func_80082470(struct MainObj* obj)
{
    obj->active = 0x41;
    obj->hp = 0x1E;
    obj->contact_damage = 0;
    obj->invincibility_timer = 0;
    obj->bg_offset = g_Player.bg_offset;
    obj->collision_data = D_80107F04;
    obj->animation_table = (const u8* const*)gunship_animations;
    obj->unk16 = 6;
    obj->terrain_box = &gunship_terrain_box;
    obj->hurt_box = &gunship_hurt_box;
    obj->x_speed = 0;
    obj->y_speed = 0;
    obj->x_accel = 0;
    obj->gravity = 0;
    obj->air_state = 0;
    obj->attack_box = NULL;
    obj->unk15 = 0;
    obj->unk75 = 1;
    obj->unk18.val = obj->x_pos.val;
    obj->unk1C.val = obj->y_pos.val;
    set_animation(obj, 0);
    /* volatile: the clear and the real value are both stored to this word */
    *(volatile u32*)&obj->ext.main_67.vertical_speed = 0;
    obj->ext.main_67.vertical_speed = -0x5800;
    obj->unk5 = 2;
    obj->ext.raw[1] = 0;
    obj->ext.raw[2] = 0;
    obj->ext.raw[3] = 0;
    obj->ext.raw[4] = 0;
    obj->ext.raw[5] = 0;
    obj->ext.raw[1] = 0;
    obj->unk6 = 0;
    obj->unk7C = 0x28;
    obj->state++;
}

// gunship_main
INCLUDE_ASM("main/nonmatchings/mains/main_67_gunship", func_80082574);

void gunship_destroyed(struct MainObj* self)
{
    s32 y;

    self->unk18.val = self->x_pos.val;
    y = self->y_pos.val;
    self->unk1C.val = y;
    gunship_destroyed_funcs[self->unk5](self, y);
}

void gunship_destroyed_start(struct MainObj* self, s32 y)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 0x13);
    self->y_speed = FIXED(-0.5);
    self->x_speed = 0;
    self->x_accel = 0;
    self->gravity = FIXED(0.0078125);
    self->terrain_box = NULL;
    self->unk5++;
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
    collide_with_players(PLAYER_OBJECT(self));
}

void gunship_destroyed_sink(struct MainObj* self, s32 y)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        drop_item(BASE_OBJECT(self), 8);
        spawn_debris(6, gunship_debris, self);
        self->on_screen = 0;
        self->unk5++;
    } else {
        if (--self->unk7E == 0) {
            func_800AF878(BASE_OBJECT(self), 1, 0x40, 0x20);
            self->unk7E = 5;
        }
        update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
        collide_with_players(PLAYER_OBJECT(self));
    }
}

void gunship_destroyed_end(struct MainObj* self, s32 y)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void gunship_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_67.saved_unk5;
}

void gunship_choose(struct MainObj* self)
{
    gunship_choose_funcs[self->unk6](self);
}

// gunship_choose_attack
INCLUDE_ASM("main/nonmatchings/mains/main_67_gunship", func_800828B4);

void gunship_gun(struct MainObj* self)
{
    gunship_gun_funcs[self->unk6](self);
}

void gunship_gun_fire(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    self->ext.main_67.unk89 = 1;
    func_8001540C(2, 0xA1, self);
    gunship_spawn_bullet(self);
    self->ext.main_67.unk8A++;
    timer = 0xA;
    if (engine_obj.cur_character == 0) {
        timer = 0x14;
    }
    self->unk7C = timer;
    self->unk6++;
}

void gunship_gun_wait(struct MainObj* self)
{
    s16 reset_timer;

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk6 = 0;
        if (self->ext.main_67.unk8A >= 3) {
            self->unk5 = 2;
            self->ext.main_67.unk89 = 0;
            self->ext.main_67.unk8A = 0;
            reset_timer = 0x28;
            if (engine_obj.cur_character == 0) {
                reset_timer = 0x1E;
            }
            self->unk7C = reset_timer;
        }
    }
}

void gunship_missiles(struct MainObj* self)
{
    gunship_missiles_funcs[self->unk6](self);
}

void gunship_missiles_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->unk7C = 0x23;
    self->unk6++;
}

void gunship_missiles_open(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 1);
        self->unk7C = 4;
        self->unk6++;
    }
}

void gunship_missiles_launch(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_8001540C(2, 0xA2, self);
        gunship_spawn_missiles(VISUAL_OBJECT(self));
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void gunship_missiles_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7C = 0x78;
    }
}

void gunship_turn(struct MainObj* self)
{
    gunship_turn_funcs[self->unk6](self);
}

void gunship_turn_start(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    set_animation(self, 0x14);
    self->unk7C = 0x1A;
    self->unk6++;
}

void gunship_turn_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7C = 0x28;
    }
}

void gunship_boost(struct MainObj* self)
{
    gunship_boost_funcs[self->unk6](self);
}

void gunship_boost_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 0);
    gunship_spawn_exhaust(self);
    self->ext.main_67.unk89 = 1;
    self->unk7C = 0x78;
    self->unk6++;
}

void gunship_boost_wait(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 4;
        self->unk6 = 0;
        self->ext.main_67.unk89 = 0;
        self->unk7C = 0xA;
    }
}

void gunship_spawn_bullet(struct MainObj* self)
{
    struct ShotObj* shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x2B;
        shot->unk2 = (u8)engine_obj.cur_character;
        shot->unk7C = WEAPON_OBJECT(self);
        shot->unk42 = self->unk42;
        shot->animation_table = (u32**)gunship_animations;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk40 = self->unk40;
        shot->unk15 = self->unk15;
        shot->bg_offset = self->bg_offset;
        shot->unk16 = 4;
    }
}

void gunship_spawn_missiles(struct VisualObj* self)
{
    struct ShotObj* shot;
    u8 i;
    for (i = 0; i < 4; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x2B;
            shot->unk2 = i + 2;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)gunship_animations;
            shot->unk3C = self->unk3C;
            shot->unk40 = self->unk40;
            shot->unk15 = self->unk15;
            shot->bg_offset = self->bg_offset;
            shot->unk16 = (i < 2) ? 4 : 7;
        }
    }
}

void gunship_bob(struct MainObj* self)
{
    if (self->ext.main_67.direction == 0) {
        if (self->ext.main_67.vertical_speed < FIXED(0.375) + 1) {
            if (self->ext.main_67.vertical_speed > 0 && self->ext.main_67.delay != 0) {
                self->ext.main_67.delay--;
            } else {
                self->ext.main_67.vertical_speed += FIXED(0.015625);
                self->y_pos.val -= self->ext.main_67.vertical_speed / 2;
                self->y_pos.val -= self->ext.main_67.vertical_speed;
            }
        } else {
            self->ext.main_67.delay = 0xF;
            self->ext.main_67.direction = 1;
        }
    } else {
        if (self->ext.main_67.vertical_speed >= FIXED(-0.375)) {
            if (self->ext.main_67.vertical_speed < 0 && self->ext.main_67.delay != 0) {
                self->ext.main_67.delay--;
            } else {
                self->ext.main_67.vertical_speed -= FIXED(0.015625);
                self->y_pos.val -= self->ext.main_67.vertical_speed / 2;
                self->y_pos.val -= self->ext.main_67.vertical_speed;
            }
        } else {
            self->ext.main_67.delay = 0xF;
            self->ext.main_67.direction = 0;
        }
    }
}

void gunship_spawn_exhaust(struct MainObj* self)
{
    s32 var_s1;
    struct VisualObj* temp_v0;

    var_s1 = 0;
    do {
        temp_v0 = find_free_visual_obj();
        if (temp_v0 != 0) {
            temp_v0->active = 0x41;
            temp_v0->id = 0x1F;
            temp_v0->unk2 = var_s1;
            temp_v0->unk50 = PLAYER_OBJECT(self);
            temp_v0->unk42 = self->unk42;
            temp_v0->animation_table = (u32**)gunship_animations;
            temp_v0->unk3C = self->sprite_frames;
            temp_v0->unk40 = self->unk40;
            temp_v0->bg_offset = self->bg_offset;
            temp_v0->unk16 = 5;
            temp_v0->unk15 = self->unk15;
        }
        var_s1 += 1;
    } while ((var_s1 & 0xFF) < 4U);
}

s32 gunship_is_within(struct MainObj* self, s32 arg1, s32 arg2)
{
    POS_BOUNDS_CHECK_FAIL_RET0(self->x_pos.val, arg1)
    POS_BOUNDS_CHECK_FAIL_RET0(self->y_pos.val, arg2)
    return 1;
}

struct Unk_unk68 gunship_hurt_box = { -77, -41, -105, 68 };

struct Unk_unk68 gunship_terrain_box = { -1, -3, 78, 29 };

union AnimationStep gunship_anim_0[] = {
    { 0x00000001 },
};

union AnimationStep gunship_anim_1[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02000002 },
};

struct Unk_unk68 gunship_anim_2[5] = {
    { 5, 0, 1, 3 },
    { 5, 0, 1, 4 },
    { 5, 0, 1, 5 },
    { 5, 0, 1, 6 },
    { 5, 0, -4, 7 },
};

struct Unk_unk68 gunship_anim_3[3] = {
    { 1, 0, 1, 8 },
    { 1, 0, 1, 9 },
    { 1, 0, -2, 10 },
};

struct Unk_unk68 gunship_anim_4[3] = {
    { 1, 0, 1, 11 },
    { 1, 0, 1, 12 },
    { 1, 0, -2, 13 },
};

struct Unk_unk68 gunship_anim_5[3] = {
    { 1, 0, 1, 14 },
    { 1, 0, 1, 15 },
    { 1, 0, -2, 16 },
};

struct Unk_unk68 gunship_anim_6[3] = {
    { 1, 0, 1, 17 },
    { 1, 0, 1, 18 },
    { 1, 0, -2, 19 },
};

struct Unk_unk68 gunship_anim_7[3] = {
    { 1, 0, 1, 20 },
    { 1, 0, 1, 21 },
    { 1, 0, -2, 22 },
};

struct Unk_unk68 gunship_anim_8[3] = {
    { 1, 0, 1, 23 },
    { 1, 0, 1, 24 },
    { 1, 0, -2, 25 },
};

struct Unk_unk68 gunship_anim_9[3] = {
    { 1, 0, 1, 26 },
    { 1, 0, 1, 27 },
    { 1, 0, -2, 28 },
};

struct Unk_unk68 gunship_anim_10[3] = {
    { 1, 0, 1, 29 },
    { 1, 0, 1, 30 },
    { 1, 0, -2, 31 },
};

struct Unk_unk68 gunship_anim_11[3] = {
    { 1, 0, 1, 32 },
    { 1, 0, 1, 33 },
    { 1, 0, -2, 34 },
};

struct Unk_unk68 gunship_anim_12[3] = {
    { 1, 0, 1, 35 },
    { 1, 0, 1, 36 },
    { 1, 0, -2, 37 },
};

struct Unk_unk68 gunship_anim_13[3] = {
    { 1, 0, 1, 38 },
    { 1, 0, 1, 39 },
    { 1, 0, -2, 40 },
};

struct Unk_unk68 gunship_anim_14[3] = {
    { 1, 0, 1, 41 },
    { 1, 0, 1, 42 },
    { 1, 0, -2, 43 },
};

struct Unk_unk68 gunship_anim_15[3] = {
    { 1, 0, 1, 44 },
    { 1, 0, 1, 45 },
    { 1, 0, -2, 46 },
};

struct Unk_unk68 gunship_anim_16[3] = {
    { 1, 0, 1, 47 },
    { 1, 0, 1, 48 },
    { 1, 0, -2, 49 },
};

struct Unk_unk68 gunship_anim_17[3] = {
    { 1, 0, 1, 50 },
    { 1, 0, 1, 51 },
    { 1, 0, -2, 52 },
};

struct Unk_unk68 gunship_anim_18[3] = {
    { 1, 0, 1, 53 },
    { 1, 0, 1, 54 },
    { 1, 0, -2, 55 },
};

union AnimationStep gunship_anim_19[] = {
    { 0x00010019 },
    { 0x38010019 },
    { 0x39010019 },
    { 0x3A000019 },
};

union AnimationStep gunship_anim_20[] = {
    { 0x02010001 },
    { 0x51010001 },
    { 0x3B010001 },
    { 0x51010001 },
    { 0x00000001 },
};

struct Unk_unk68 gunship_anim_21[12] = {
    { 4, 0, 1, 79 },
    { 4, 0, 1, 80 },
    { 4, 0, 1, 60 },
    { 4, 0, 1, 61 },
    { 4, 0, 1, 62 },
    { 14, 0, 1, 63 },
    { 4, 0, 1, 64 },
    { 4, 0, 1, 65 },
    { 4, 0, 1, 66 },
    { 4, 0, 1, 67 },
    { 4, 0, 1, 68 },
    { 14, 0, -11, 63 },
};

struct Unk_unk68 gunship_anim_22[11] = {
    { 1, 0, 1, 69 },
    { 2, 0, 1, 70 },
    { 4, 0, 1, 71 },
    { 4, 0, 1, 72 },
    { 4, 0, 1, 73 },
    { 4, 0, 1, 74 },
    { 4, 0, 1, 75 },
    { 4, 0, 1, 76 },
    { 4, 0, 1, 77 },
    { 4, 0, 1, 78 },
    { 24, 0, -10, 63 },
};

union AnimationStep gunship_anim_23[] = {
    { 0x52000001 },
};

union AnimationStep gunship_anim_24[] = {
    { 0x53000001 },
};

union AnimationStep gunship_anim_25[] = {
    { 0x54000001 },
};

union AnimationStep gunship_anim_26[] = {
    { 0x55000001 },
};

union AnimationStep gunship_anim_27[] = {
    { 0x56000001 },
};

union AnimationStep gunship_anim_28[] = {
    { 0x57000001 },
};

void* gunship_animations[29] = {
    gunship_anim_0,
    gunship_anim_1,
    gunship_anim_2,
    gunship_anim_3,
    gunship_anim_4,
    gunship_anim_5,
    gunship_anim_6,
    gunship_anim_7,
    gunship_anim_8,
    gunship_anim_9,
    gunship_anim_10,
    gunship_anim_11,
    gunship_anim_12,
    gunship_anim_13,
    gunship_anim_14,
    gunship_anim_15,
    gunship_anim_16,
    gunship_anim_17,
    gunship_anim_18,
    gunship_anim_19,
    gunship_anim_20,
    gunship_anim_21,
    gunship_anim_22,
    gunship_anim_23,
    gunship_anim_24,
    gunship_anim_25,
    gunship_anim_26,
    gunship_anim_27,
    gunship_anim_28,
};

struct Unk_unk68 gunship_debris[2] = {
    { 23, 24, 25, 26 },
    { 27, 28, 0, 0 },
};

void (*gunship_state_funcs[3])() = {
    func_80082470,
    func_80082574,
    gunship_destroyed,
};

void (*gunship_step_funcs[7])() = {
    enemy_hit_reaction,
    gunship_resume_step,
    gunship_choose,
    gunship_gun,
    gunship_missiles,
    gunship_turn,
    gunship_boost,
};

void (*gunship_destroyed_funcs[3])(struct MainObj*, s32) = {
    gunship_destroyed_start,
    gunship_destroyed_sink,
    gunship_destroyed_end,
};

void (*gunship_choose_funcs[1])() = {
    func_800828B4,
};

void (*gunship_gun_funcs[2])() = {
    gunship_gun_fire,
    gunship_gun_wait,
};

void (*gunship_missiles_funcs[4])() = {
    gunship_missiles_start,
    gunship_missiles_open,
    gunship_missiles_launch,
    gunship_missiles_end,
};

void (*gunship_turn_funcs[2])() = {
    gunship_turn_start,
    gunship_turn_wait,
};

void (*gunship_boost_funcs[2])() = {
    gunship_boost_start,
    gunship_boost_wait,
};
