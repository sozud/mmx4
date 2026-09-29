// MainObj, main_object_update_funcs[45]
// 80065B8C..80066A48
#include "common.h"
#include "func_tables.h"

void train_boss_update(struct MainObj* self)
{
    train_boss_state_funcs[self->state](self);
}

void train_boss_init(struct MainObj* self)
{
    self->active |= 4;
    self->contact_damage = 2;
    self->on_screen = 0;
    self->hp = 0;
    self->invincibility_timer = 1;
    self->collision_data = D_80107678;
    self->bg_offset = g_Player.bg_offset;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->unk75 = 1;
    self->unk76 = 0;
    self->hurt_box = NULL;
    self->attack_box = NULL;
    self->unk15 = 0;
    self->ext.main_45.attack_flags = 0;
    self->ext.main_45.unk81 = 0;
    self->ext.main_45.unk82 = 0;
    self->ext.main_45.unk83 = 0;
    self->animation_table = (const u8* const*)train_boss_animations;
    self->unk16 = 4;
    self->terrain_box = (struct Unk_unk68*)train_boss_terrain_box;
    self->ext.main_45.unk84 = 0x320;
    self->ext.main_45.projectile_command = 0x80;
    self->ext.main_45.unk89 = 0;
    self->ext.main_45.unk86 = train_boss_attack_timers[0];
    self->ext.main_45.unk87 = 0;
    set_animation(self, 0);
    self->state = 1;
    self->unk5 = 0;
    self->unk6 = 0;
}

void train_boss_main(struct MainObj* self)
{
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    self->ext.main_45.unk8A = self->x_pos.i.hi;
    func_8006630C(self);
    train_boss_step_funcs[self->unk5](self);
    func_80066478(self);
    if ((self->ext.main_45.attack_flags & 7) == 7) {
        spawn_explosion(BASE_OBJECT(self));
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        *self->ext.main_45.layer_bg_offset = 0;
        self->unk7C = 0x78;
        self->unk7E = 1;
        self->state = 2;
        if (g_Player.unk5 == 2) {
            player_start_script_action(0x14, 0x40);
            self->unk6 = 1;
        } else {
            self->unk6 = 0;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x100, 0x100);
}

void train_boss_defeated(struct MainObj* self)
{
    s16 timer;

    func_80066970();
    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        if (get_layout_screen(1, -0x20, 0x80) == 0x1C) {
            self->state = 3;
            self->unk5 = 0;
        } else {
            self->unk7C = 1;
        }
    }
    if ((self->unk6 == 0) && ((self->x_pos.i.hi + 0x69 >= g_Player.x_pos.i.hi) || (g_Player.x_pos.i.hi >= 0x1B36))) {
        player_start_script_action(0x14, 0x40);
        self->unk6 = 1;
    }
    collide_with_players(PLAYER_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x100, 0x100);
}

// train_boss_leave
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_80065EA4);

// train_boss_despawn
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_800661AC);

// train_boss_update_parts
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_8006630C);

// train_boss_update_projectiles
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_80066478);

void train_boss_arrive(struct MainObj* self)
{
    train_boss_arrive_funcs[self->unk6](self);
}

// train_boss_arrive_start
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_800665BC);

void train_boss_arrive_approach(struct MainObj* self)
{
    if (self->x_pos.i.hi >= 0x19A1) {
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 2;
        engine_obj.boss_ptr = self;
        self->unk6 = 2;
    }
    move_object(MOVING_OBJECT(self));
}

void train_boss_arrive_stop(struct MainObj* self)
{
    if (self->x_pos.i.hi >= 0x1AA1) {
        self->unk7E = 3;
        self->unk6 = 3;
    } else {
        move_object(MOVING_OBJECT(self));
    }
}

void train_boss_arrive_fill_hp(struct MainObj* self)
{
    s16 timer;

    if (self->hp < 0x30) {
        timer = (u16)self->unk7E - 1;
        self->unk7E = timer;
        if (timer == 0) {
            func_8001540C(0, 0xE, NULL);
            self->unk7E = 3;
        }
        self->hp = (u8)self->hp + 1;
        return;
    }
    self->ext.main_45.projectile_command = 0xFF;
    self->unk5 = 1;
    self->unk6 = 0;
    player_end_script_action();
}

void train_boss_fight(struct MainObj* self)
{
    train_boss_fight_funcs[self->unk6](self);
}

void train_boss_fight_idle(void)
{
}

// train_boss_spawn_smoke
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_80066970);

s8 train_boss_terrain_box[4] = { -56, 12, 39, 86 };

u8 train_boss_attack_timers[20] = {
    0,
    1,
    2,
    1,
    2,
    0,
    3,
    3,
    2,
    1,
    0,
    1,
    0,
    2,
    4,
    3,
    3,
    0xFF,
    0,
    0,
};

u8 D_800FF8B0[8] = { 0x11, 0x22, 0x44, 0x08, 0, 0, 0, 0 };

union AnimationStep train_boss_anim_0[] = { { 0x00000101 } };

union AnimationStep train_boss_anim_1[] = { { 0x01000101 } };

union AnimationStep train_boss_anim_2[] = { { 0x02000101 } };

union AnimationStep train_boss_anim_3[] = {
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x06FD0101 },
};

union AnimationStep train_boss_anim_4[] = {
    { 0x03010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x06FD0101 },
};

union AnimationStep train_boss_anim_5[] = { { 0x07000101 } };

union AnimationStep train_boss_anim_6[] = { { 0x0A000101 } };

union AnimationStep train_boss_anim_7[] = { { 0x0B000101 } };

union AnimationStep train_boss_anim_8[] = { { 0x0C000101 } };

union AnimationStep train_boss_anim_9[] = { { 0x0D000101 } };

union AnimationStep train_boss_anim_10[] = { { 0x0E000101 } };

union AnimationStep train_boss_anim_11[] = { { 0x0F000101 } };

union AnimationStep train_boss_anim_12[] = { { 0x10000101 } };

union AnimationStep train_boss_anim_13[] = { { 0x11000101 } };

union AnimationStep train_boss_anim_14[] = { { 0x12000101 } };

union AnimationStep train_boss_anim_15[] = { { 0x13000101 } };

union AnimationStep train_boss_anim_16[] = { { 0x14000101 } };

union AnimationStep train_boss_anim_17[] = { { 0x15000101 } };

union AnimationStep* train_boss_animations[19] = {
    train_boss_anim_0,
    train_boss_anim_1,
    train_boss_anim_2,
    train_boss_anim_3,
    train_boss_anim_4,
    train_boss_anim_5,
    train_boss_anim_6,
    train_boss_anim_7,
    train_boss_anim_8,
    train_boss_anim_9,
    train_boss_anim_10,
    train_boss_anim_11,
    train_boss_anim_12,
    train_boss_anim_13,
    train_boss_anim_14,
    train_boss_anim_15,
    train_boss_anim_16,
    train_boss_anim_17,
    NULL,
};

void (*train_boss_state_funcs[])(struct MainObj*) = {
    train_boss_init,
    train_boss_main,
    train_boss_defeated,
    func_80065EA4,
    func_800661AC,
};

void (*train_boss_step_funcs[2])(struct MainObj*) = { train_boss_arrive, train_boss_fight };

void (*train_boss_arrive_funcs[4])(struct MainObj*) = {
    func_800665BC,
    train_boss_arrive_approach,
    train_boss_arrive_stop,
    train_boss_arrive_fill_hp,
};

void (*train_boss_fight_funcs[1])(struct MainObj*) = { train_boss_fight_idle };
