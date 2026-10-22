// MainObj, main_object_update_funcs[45]
// 80065B8C..80066A48
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_45_train_boss.h"
#include "main/player_common.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/visuals/visual_03_small_effect.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/visuals/visual_03_small_effect.h"
#endif

extern s8 train_boss_terrain_box[4];

#ifdef MMX4_PC
#ifdef MMX4_PC
extern void train_boss_fight_idle(struct MainObj*);
#else
extern void train_boss_fight_idle(void);
#endif
#endif

// train_boss_state_funcs
void train_boss_init(struct MainObj*);

// train_boss_step_funcs
extern void (*train_boss_step_funcs[])(struct MainObj*);
void train_boss_arrive(struct MainObj*);
void train_boss_fight(struct MainObj*);

void train_boss_arrive_approach(struct MainObj*);
void train_boss_arrive_stop(struct MainObj*);
void train_boss_arrive_fill_hp(struct MainObj*);

// train_boss_fight_funcs
#ifdef MMX4_PC
void train_boss_fight_idle(struct MainObj*);
#else
void train_boss_fight_idle(void);
#endif

extern void (*train_boss_state_funcs[])(struct MainObj*);
extern void (*train_boss_arrive_funcs[])(struct MainObj*);
extern void (*train_boss_fight_funcs[])(struct MainObj*);

void train_boss_update(struct MainObj* self)
{
    train_boss_state_funcs[self->state](self);
}

void train_boss_init(struct MainObj* self)
{
    self->active |= 4;
    self->on_screen = 0;
    self->hp = 0;
    self->contact_damage = 2;
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
    self->unk16 = VISUAL_SATURN_LAYER(4);
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
            player_start_script_action(0x14, PLAYER_FACING_RIGHT);
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

    func_80066970(self);
    timer = --self->unk7C;
    if (timer == 0) {
        if (get_layout_screen(1, -0x20, 0x80) == 0x1C) {
            self->state = 3;
            self->unk5 = 0;
        } else {
            self->unk7C = 1;
        }
    }
    if (self->unk6 == 0) {
        if ((g_Player.x_pos.i.hi <= self->x_pos.i.hi + 0x69) || (g_Player.x_pos.i.hi >= 0x1B36)) {
            player_start_script_action(0x14, PLAYER_FACING_RIGHT);
            self->unk6 = 1;
        }
    }
    collide_with_players(PLAYER_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x100, 0x100);
}

// train_boss_leave

#if defined(MMX4_PC) || defined(MMX4_SATURN)
static void train_boss_move_player_past_exit(struct MainObj* self);
static void train_boss_exit_player_script(struct MainObj* self);
void func_80065EA4(struct MainObj* self);
void func_800661AC(struct MainObj* self);
void func_8006630C(struct MainObj* self);
void func_80066478(struct MainObj* self);
void func_800665BC(struct MainObj* self);
void func_80066970(struct MainObj* self);
void collide_with_players(struct PlayerObj*);
extern u8 D_800FF8B0[8];
static void train_boss_move_player_past_exit(struct MainObj* self)
{
    if (self->x_pos.i.hi + 0x69 < g_Player.x_pos.i.hi && (u8)(get_layout_screen(1, 0xA0, 0x80) - 0x23) < 2) {
        g_Player.x_pos.u.hi = background_objects[0].x_pos.u.hi + 0x12C;
        g_Player.y_pos.u.hi = background_objects[0].y_pos.u.hi + 0x64;
        g_Player.unk18 = g_Player.x_pos;
        g_Player.unk1C = g_Player.y_pos;
    }
}
static void train_boss_exit_player_script(struct MainObj* self)
{
    if (self->unk6 == 0 && (g_Player.x_pos.i.hi <= self->x_pos.i.hi + 0x69 || g_Player.x_pos.i.hi >= 0x1B36)) {
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
        self->unk6 = 1;
    }
    collide_with_players(PLAYER_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x100, 0x100);
}
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80065EA4(struct MainObj* self)
{
    train_boss_move_player_past_exit(self);
    func_80066970(self);
    switch ((s16)(get_layout_screen(1, -0x20, 0x80) - 0x20)) {
    case 9:
        if (self->unk5 == 0) {
            SP_BG_TILEMAP[layout_size + 2] = 0x20;
            self->unk5 = 1;
        }
        break;
    case 10:
        if (self->unk5 == 1) {
            SP_BG_TILEMAP[layout_size + 3] = 0x21;
            self->unk5 = 2;
        }
        break;
    case 0:
        if (self->unk5 == 2) {
            SP_BG_TILEMAP[layout_size + 4] = 0x22;
            self->unk5 = 3;
        }
        break;
    case 1:
        if (self->unk5 == 3) {
            SP_BG_TILEMAP[layout_size + 5] = 0x23;
            self->unk5 = 4;
        }
        break;
    case 2:
        if (self->unk5 == 4) {
            SP_BG_TILEMAP[layout_size + 6] = 0x24;
            self->unk5 = 5;
        }
        break;
    case 3:
        if (self->unk5 == 5) {
            SP_BG_TILEMAP[layout_size + 2] = 0x1D;
            SP_BG_TILEMAP[layout_size + 3] = 0x1D;
            SP_BG_TILEMAP[layout_size + 4] = 0x1D;
            SP_BG_TILEMAP[layout_size + 7] = 0x1D;
            self->unk7C = 0xC;
            self->state = 4;
        }
        break;
    }
    train_boss_exit_player_script(self);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_80065EA4);
#endif

// train_boss_despawn
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800661AC(struct MainObj* self)
{
    if ((u8)g_Player.hp != 0x80)
        train_boss_move_player_past_exit(self);
    func_80066970(self);
    self->unk7C = (u16)self->unk7C - 1;
    if (self->unk7C == 0) {
        if ((u8)g_Player.hp != 0x80)
            engine_obj.unkF = 0x40;
        ZeroObjectState(OBJECT_HEADER(self));
    }

    train_boss_exit_player_script(self);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_800661AC);
#endif

// train_boss_update_parts
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006630C(struct MainObj* self)
{
    struct Main45Ext* parts = &self->ext.main_45;
    u8 flags = parts->attack_flags;
    u8 command = parts->projectile_command;

    if ((flags & 7) == 7 || command == 0x80)
        return;
    if (command == 0xFF) {
        parts->projectile_command = parts->unk86;
        do {
            parts->unk89++;
            if (train_boss_attack_timers[parts->unk89] == 0xFF)
                parts->unk89 = 0;
            parts->unk86 = train_boss_attack_timers[parts->unk89];
        } while (D_800FF8B0[parts->unk86] & parts->attack_flags);
        return;
    }
    if (command == 5) {
        unsigned slot, finished = 0;
        for (slot = 0; slot < 3; slot++) {
            if ((s8)shot_objects[slot].state < 3 || shot_objects[slot].unk28 == 0)
                finished++;
        }
        if (finished == 3)
            parts->projectile_command = 0xFF;
    } else if (command == 4) {
        if ((flags & 0x70) == 0x70)
            parts->projectile_command = 0xFF;
    } else if (D_800FF8B0[command] & flags) {
        parts->projectile_command = 0xFF;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_8006630C);
#endif

// train_boss_update_projectiles
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80066478(struct MainObj* self)
{
    struct Main45Ext* parts = &self->ext.main_45;

    parts->unk84 = (u16)parts->unk84 - 1;
    if (parts->unk84 == 0) {
        if (parts->unk82 == 0) {
            parts->unk81 = 1;
            parts->unk82 = 1;
            parts->unk83 = 0x20;
            parts->unk84 = 0xF0;
        } else {
            parts->unk81 = 0xFF;
            parts->unk82 = 0;
            parts->unk83 = 0x20;
            parts->unk84 = 0x12C;
        }
    }
    collide_with_players(PLAYER_OBJECT(self));
    if (parts->unk83 != 0) {
        parts->unk83--;
        if (parts->unk83 == 0) {
            parts->unk81 = 0;
            *parts->layer_bg_offset = 0;
        } else if ((parts->unk83 & 1) == 0) {
            if (g_Player.wall_climbable != 0 || self->unk76 != 0)
                *parts->layer_parameter = 1;
            *parts->layer_bg_offset = parts->unk81;
        }
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_80066478);
#endif

void train_boss_arrive(struct MainObj* self)
{
    train_boss_arrive_funcs[self->unk6](self);
}

// train_boss_arrive_start
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800665BC(struct MainObj* self)
{
    struct LayerObj* layer = find_free_layer_obj();
    struct ItemObj* floor;
    struct MainObj* part;
    unsigned index;

    if (layer != NULL) {
        struct Main45LayerSignals* signals = (struct Main45LayerSignals*)&layer->unk16;

        layer->active = 1;
        layer->id = 3;
        layer->unk2 = 1;
        layer->bg_offset = 0;
        layer->unk16 = layer->unk17 = 0;
        signals->projectile_state[0] = 0;
        signals->projectile_state[1] = 0;
        signals->projectile_state[2] = 0;
        self->ext.main_45.layer_bg_offset = (u8*)&layer->bg_offset;
        self->ext.main_45.layer_parameter = &layer->unk15;
        self->ext.main_45.layer_signals = signals;
        layer->state = 0;
    }
    floor = find_free_item_obj();
    if (floor != NULL) {
        floor->active = 0x41;
        floor->id = 0x10;
        floor->unk2 = 0;
        floor->unk40 = self->unk40;
        floor->unk42 = self->unk42;
        floor->animation_table = self->animation_table;
        floor->sprite_frames = self->sprite_frames;
        floor->animation_step.fields.frame_index = 7;
        floor->bg_offset = self->bg_offset;
        floor->x_pos = self->x_pos;
        floor->y_pos = self->y_pos;
        floor->unk7C.train_boss = &self->ext.main_45;

        assert(layer != NULL);
        floor->ext.train_layer_parameter = &layer->unk15;
        floor->unk15 = 0;
        floor->state = 0;
    }
    part = find_free_main_obj();
    if (part != NULL) {
        part->active = 0x45;
        part->id = 0x2E;
        part->unk2 = 0;
        part->unk40 = self->unk40;
        part->unk42 = self->unk42;
        part->animation_table = self->animation_table;
        part->sprite_frames = self->sprite_frames;
        part->animation_step.fields.frame_index = 0x11;
        part->bg_offset = self->bg_offset;
        part->x_pos = self->x_pos;
        part->y_pos = self->y_pos;
        part->ext.main_46.owner = &self->ext.main_45;
        part->unk15 = 0;
        part->state = 0;
    }
    for (index = 0; index < 3; index++) {
        part = find_free_main_obj();
        if (part == NULL)
            continue;
        part->active = 0x45;
        part->id = 0x2F;
        part->unk2 = index;
        part->unk40 = self->unk40;
        part->unk42 = self->unk42;
        part->animation_table = self->animation_table;
        part->sprite_frames = self->sprite_frames;
        part->animation_step.fields.frame_index = index + 0x13;
        part->bg_offset = self->bg_offset;
        part->x_pos = self->x_pos;
        part->y_pos = self->y_pos;
        part->ext.main_47.train_boss = &self->ext.main_45;
        part->ext.main_47.boss_hp = &self->hp;
        part->unk15 = 0;
        part->state = 0;
    }
    self->x_speed = 0x10000;
    self->unk6 = 1;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_800665BC);
#endif

void train_boss_arrive_approach(struct MainObj* self)
{
    if (self->x_pos.i.hi > 0x19A0) {
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 2;
        engine_obj.boss_ptr = self;
        self->unk6 = 2;
    }
    move_object(MOVING_OBJECT(self));
}

void train_boss_arrive_stop(struct MainObj* self)
{
    if (self->x_pos.i.hi > 0x1AA0) {
        self->unk7E = 3;
        self->unk6 = 3;
    } else {
        move_object(MOVING_OBJECT(self));
    }
}

void train_boss_arrive_fill_hp(struct MainObj* self)
{
    if (self->hp < 0x30) {
        if (--self->unk7E == 0) {
            func_8001540C(0, SATURN_SOUND(0xE, 0x14), NULL);
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

#ifdef MMX4_PC
void train_boss_fight_idle(struct MainObj* self)
#else
void train_boss_fight_idle(void)
#endif
{
#ifdef MMX4_PC
    (void)self;
#endif
}

// train_boss_spawn_smoke
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80066970(struct MainObj* self)
{
    u16 x = self->x_pos.u.hi;
    u16 y = self->y_pos.u.hi;

    self->unk7E = (u16)self->unk7E - 1;
    if (self->unk7E == 3) {
        self->x_pos.u.hi = x - 0x37;
        self->y_pos.u.hi = y + 0xB;
        func_800AF95C(OBJECT_HEADER(self), 1, 0x29, 0x59, 4);
        self->x_pos.u.hi = x;
        self->y_pos.u.hi = y;
    }
    if (self->unk7E == 0) {
        self->x_pos.u.hi = x + 0x27;
        self->y_pos.u.hi = y + 0x34;
        func_800AF95C(OBJECT_HEADER(self), 1, 0x37, 0x28, 2);
        self->x_pos.u.hi = x;
        self->y_pos.u.hi = y;
        self->unk7E = 6;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_45_train_boss", func_80066970);
#endif

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

union AnimationStep train_boss_anim_0[] = { { 1, 1, 0, 0x00 } };

union AnimationStep train_boss_anim_1[] = { { 1, 1, 0, 0x01 } };

union AnimationStep train_boss_anim_2[] = { { 1, 1, 0, 0x02 } };

union AnimationStep train_boss_anim_3[] = {
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x05 },
    { 1, 1, -3, 0x06 },
};

union AnimationStep train_boss_anim_4[] = {
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x08 },
    { 1, 0, 1, 0x09 },
    { 1, 1, -3, 0x06 },
};

union AnimationStep train_boss_anim_5[] = { { 1, 1, 0, 0x07 } };

union AnimationStep train_boss_anim_6[] = { { 1, 1, 0, 0x0A } };

union AnimationStep train_boss_anim_7[] = { { 1, 1, 0, 0x0B } };

union AnimationStep train_boss_anim_8[] = { { 1, 1, 0, 0x0C } };

union AnimationStep train_boss_anim_9[] = { { 1, 1, 0, 0x0D } };

union AnimationStep train_boss_anim_10[] = { { 1, 1, 0, 0x0E } };

union AnimationStep train_boss_anim_11[] = { { 1, 1, 0, 0x0F } };

union AnimationStep train_boss_anim_12[] = { { 1, 1, 0, 0x10 } };

union AnimationStep train_boss_anim_13[] = { { 1, 1, 0, 0x11 } };

union AnimationStep train_boss_anim_14[] = { { 1, 1, 0, 0x12 } };

union AnimationStep train_boss_anim_15[] = { { 1, 1, 0, 0x13 } };

union AnimationStep train_boss_anim_16[] = { { 1, 1, 0, 0x14 } };

union AnimationStep train_boss_anim_17[] = { { 1, 1, 0, 0x15 } };

union AnimationStep* train_boss_animations[] = {
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
#ifndef MMX4_WIN32
    NULL,
#endif
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
