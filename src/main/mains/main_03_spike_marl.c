// MainObj, main_object_update_funcs[3]
// 80043340..8004441C
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_03_spike_marl.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/objects.h"

extern struct Unk_unk68 spike_marl_curl_attack_box;
extern struct Unk_unk68 spike_marl_curl_hurt_box;

// spike_marl_state_funcs
extern u8 spike_marl_debris[8];

void spike_marl_run(struct MainObj* arg0);
void spike_marl_cleanup(struct MainObj* arg0);

// spike_marl_step_funcs
extern void (*spike_marl_step_funcs[9])(struct MainObj*);
void spike_marl_resume_step(struct MainObj* arg0);
void spike_marl_patrol(struct MainObj* arg0);
void spike_marl_turn(struct MainObj* arg0);
void spike_marl_curl(struct MainObj* arg0);
void spike_marl_roll(struct MainObj* arg0);
void spike_marl_fall(struct MainObj* arg0);
void spike_marl_uncurl(struct MainObj* arg0);
void spike_marl_roll_entry(struct MainObj* arg0);

void spike_marl_begin_fall(struct MainObj* arg0);
void spike_marl_detect_player(struct MainObj* arg0);
void spike_marl_track_player_side(struct MainObj* arg0);

// spike_marl_patrol_funcs
void spike_marl_patrol_begin(struct MainObj* arg0);
void spike_marl_patrol_update(struct MainObj* arg0);

// spike_marl_turn_funcs
void spike_marl_turn_start(struct MainObj* arg0);
void spike_marl_turn_flip(struct PlayerObj*);

// spike_marl_curl_funcs
void spike_marl_curl_begin(struct MainObj* arg0);

// spike_marl_roll_funcs
void spike_marl_roll_begin(struct MainObj* arg0);

// spike_marl_uncurl_funcs
void spike_marl_uncurl_begin(struct MainObj* arg0);

// spike_marl_roll_entry_funcs
void spike_marl_roll_entry_begin(struct MainObj*);

extern void (*spike_marl_state_funcs[])(struct MainObj*);
extern void (*spike_marl_patrol_funcs[])(struct MainObj*);
extern void (*spike_marl_turn_funcs[])(struct MainObj*);
extern void (*spike_marl_curl_funcs[])(struct MainObj*);
extern void (*spike_marl_roll_funcs[])(struct MainObj*);
extern void (*spike_marl_uncurl_funcs[])(struct MainObj*);
extern void (*spike_marl_roll_entry_funcs[])(struct MainObj*);

void spike_marl_noop(struct MainObj* self);

extern u8 item_carrier_debris[];
extern u8 item_carrier_capsule_debris[];

void spike_marl_update(struct MainObj* self)
{
    spike_marl_state_funcs[self->state](self);
    CollisionRelated(PLAYER_OBJECT(self));
}

// spike_marl_init

extern union AnimationStep* D_800F9E1C[];
extern struct Unk_unk68 spike_marl_terrain_box;
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80043390(struct MainObj* arg0);
void func_80043C0C(struct MainObj* arg0);
extern ret_u8 func_8002938C(s32);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_03_spike_marl", func_80043390);
#else
void func_80043390(struct MainObj* arg0)
{
    s32 column;
    s32 row;

    arg0->unk7C = 0;
    arg0->hp = 6;
    arg0->invincibility_timer = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (arg0->x_pos.val > g_Player.x_pos.val)
        arg0->unk15 = 0;
    else
        arg0->unk15 = PLAYER_FACING_RIGHT;
    arg0->animation_table = (const u8* const*)D_800F9E1C;
    arg0->unk16 = VISUAL_SATURN_LAYER(4);
    arg0->terrain_box = &spike_marl_terrain_box;
    arg0->hurt_box = (const u8*)&spike_marl_walk_hurt_box;
    arg0->attack_box = (const u8*)&spike_marl_walk_attack_box;
    arg0->unk40 = (u16)((u32)OBJECT_STAGE_TEXTURE(func_8002938C(3)));
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(3));
    column = func_8002938C(3);
    row = func_8002938C(3);
#ifdef MMX4_SATURN
    arg0->unk42 = column * 4 + 0x18;
#else
    arg0->unk42 = CLUT_FROM_XY(column, row);
#endif
    arg0->air_state = 0;
    switch (arg0->unk2) {
    case 0:
        arg0->collision_data = D_80106470;
        set_animation(arg0, 1);
        arg0->contact_damage = 3;
        arg0->ext.main_3.turn_timer = 0x78;
        arg0->ext.main_3.alerted = 0;
        arg0->ext.main_3.player_ahead = 0;
        arg0->unk5 = 2;
        break;
    case 1:
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->ext.main_3.turn_timer = 0x78;
        arg0->contact_damage = 4;
        arg0->ext.main_3.alerted = 1;
        arg0->ext.main_3.player_ahead = 0;
        arg0->unk5 = 5;
        break;
    default:
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->contact_damage = 4;
        arg0->ext.main_3.alerted = 1;
        arg0->ext.main_3.player_ahead = 0;
        arg0->ext.main_3.turn_timer = 0x78;
        set_animation(arg0, 5);
        arg0->unk5 = 8;
        break;
    }
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->state = 1;
    arg0->unk6 = 0;
}
#endif

void spike_marl_run(struct MainObj* self)
{
    s32 hit;

    if (self->unk5 != 8) {
        spike_marl_check_patrol_path(self);
        spike_marl_begin_fall(self);
        spike_marl_track_player_side(self);
        spike_marl_detect_player(self);
        spike_marl_noop(self);
    }
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    spike_marl_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    self->ext.main_3.saved_step = (u32)self->unk5;
    hit = func_8002DD04(self);
    if (hit < 0) {
        spawn_explosion((struct BaseObj*)self);
        spawn_debris(7, &spike_marl_debris, self);
        drop_item(BASE_OBJECT(self), 0x11);
    } else if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        update_on_screen((struct BaseObj*)self, 0x20, 0x20);
        return;
    }
    self->state = 2;
}

void spike_marl_cleanup(struct MainObj* self)
{
    u32 subtype;

    subtype = (u8)self->unk2;
    self->ext.main_3.alerted = 0;
    self->ext.main_3.roll_timer = 0;
    self->ext.main_3.player_ahead = 0;
    self->ext.main_3.turn_timer = 0;
    self->ext.main_3.saved_step = 0;
    if (subtype < 2U) {
        despawn_object(OBJECT_HEADER(self));
        return;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void spike_marl_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_3.saved_step;
}

void spike_marl_patrol(struct MainObj* self)
{
    spike_marl_patrol_funcs[self->unk6](self);
}

void spike_marl_patrol_begin(struct MainObj* self)
{
    self->unk6 = 1;
    self->x_speed = self->unk15 & PLAYER_FACING_RIGHT ? FIXED(0.8) : FIXED(-0.8);
    animate_object(ANIMATED_OBJECT(self));
}

void spike_marl_patrol_update(struct MainObj* self)
{
    struct MainObj* temp_s0;
    s32 temp_v0;

    temp_s0 = self;
    if (temp_s0->ext.main_3.player_ahead == 0) {
        temp_v0 = temp_s0->ext.main_3.turn_timer - 1;
        temp_s0->ext.main_3.turn_timer = temp_v0;
        if (temp_v0 == 0) {
            set_animation(temp_s0, 2);
            temp_s0->unk5 = 3;
            temp_s0->unk6 = 0;
            temp_s0->ext.main_3.turn_timer = 0x78;
        }
    }
    move_object((struct MovingObj*)temp_s0);
    animate_object(ANIMATED_OBJECT(temp_s0));
}

void spike_marl_turn(struct MainObj* self)
{
    spike_marl_turn_funcs[self->unk6](self);
}

void spike_marl_turn_start(struct MainObj* self)
{
    set_animation(self, 2);
    animate_object(ANIMATED_OBJECT(self));
    self->x_speed = 0;
    self->unk6 = 1;
}

void spike_marl_turn_flip(struct PlayerObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->unk28 = 0;
        self->unk15 ^= PLAYER_FACING_RIGHT;
        set_animation(self, 1);
        self->x_vel.val = 0;
        self->unk5 = 2;
        self->unk6 = 0;
        self->input.buttons.held = 0x14;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void spike_marl_curl(struct MainObj* self)
{
    spike_marl_curl_funcs[self->unk6](self);
}

void spike_marl_curl_begin(struct MainObj* self)
{
    set_animation(self, 3);
    animate_object(ANIMATED_OBJECT(self));
    self->unk6 = 1;
}

void spike_marl_curl_update(struct MainObj* self)
{
    switch (self->animation_step.fields.event) {
    case 1:
        self->contact_damage = 4;
        self->x_speed = 0;
        self->unk7C = 0xF;
        self->unk5 = 5;
        self->unk6 = 0;
        break;
    case 2:
        func_8001540C(2, SATURN_SOUND(0, 0x0E), self);
        break;
    case 3:
        self->hurt_box = (const u8*)&spike_marl_curl_hurt_box;
        self->attack_box = (const u8*)&spike_marl_curl_attack_box;
        break;
    case 4:
        self->collision_data = (const u16*)D_801060F0;
        break;
    }

    animate_object(ANIMATED_OBJECT(self));
}

void spike_marl_roll(struct MainObj* self)
{
    spike_marl_roll_funcs[self->unk6](self);
}

void spike_marl_roll_begin(struct MainObj* self)
{
    if (self->unk7C == 0) {
        func_8001540C(2, SATURN_SOUND(1, 0x0F), self);
        set_animation(self, 5);
        self->x_speed = self->unk15 & PLAYER_FACING_RIGHT ? FIXED(4) : FIXED(-4);
        self->unk6 = 1;
    } else {
        self->unk7C--;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void spike_marl_roll_update(struct MainObj* self)
{
    s32 timer;
    u8 flags;

    timer = self->ext.main_3.roll_timer + 4;
    self->ext.main_3.roll_timer = timer;
    if (timer < 0 || (self->unk15 == 0 ? g_Player.x_pos.val > self->x_pos.val : g_Player.x_pos.val < self->x_pos.val)) {
        self->x_accel = FIXED(-0.09375);
        self->unk6 = 2;
    }

    flags = self->collision_flags;
    if (((flags & 2) && self->unk15 == 0) || ((flags & 1) && self->unk15 != 0)) {
        self->contact_damage = 3;
        self->x_accel = 0;
        self->x_speed = 0;
        self->unk5 = 7;
        self->unk6 = 0;
    }

    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

// spike_marl_roll_slow
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80043C0C(struct MainObj* arg0)
{
    s32 magnitude = arg0->x_speed;

    if (magnitude < 0) {
        magnitude = -magnitude;
    }
    if (magnitude <= 0xFFFF
        || ((arg0->collision_flags & 2) && arg0->unk15 == 0)
        || ((arg0->collision_flags & 1) && arg0->unk15 != 0)) {
        arg0->contact_damage = 3;
        arg0->x_speed = 0;
        arg0->x_accel = 0;
        arg0->unk5 = 7;
        arg0->unk6 = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_03_spike_marl", func_80043C0C);
#endif

void spike_marl_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        if (self->ext.main_3.alerted != 0) {
            self->collision_data = D_80106470;
            self->contact_damage = 3;
            self->unk5 = 7;
        } else {
            set_animation(self, 1);
            self->unk5 = 2;
        }
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->x_speed = 0;
        self->x_accel = 0;
        self->air_state = 0;
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void spike_marl_uncurl(struct MainObj* self)
{
    spike_marl_uncurl_funcs[self->unk6](self);
}

void spike_marl_uncurl_begin(struct MainObj* self)
{
    set_animation(self, 4);
    animate_object(ANIMATED_OBJECT(self));
    self->ext.main_3.alerted = 0;
    self->ext.main_3.roll_timer = 0;
    self->ext.main_3.player_ahead = 1;
    self->ext.main_3.turn_timer = 0;
    self->unk6 = 1;
}

void spike_marl_uncurl_update(struct MainObj* self)
{
    switch (self->animation_step.fields.event) {
    case 1:
        self->x_speed = 0;
        self->unk5 = 2;
        self->unk6 = 0;
        set_animation(self, 1);
        break;
    case 2:
        self->hurt_box = (const u8*)&spike_marl_walk_hurt_box;
        self->attack_box = (const u8*)&spike_marl_walk_attack_box;
        break;
    case 3:
        self->collision_data = D_80106470;
        break;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void spike_marl_roll_entry(struct MainObj* self)
{
    spike_marl_roll_entry_funcs[self->unk6](self);
}

void spike_marl_roll_entry_begin(struct MainObj* self)
{
    self->unk6 = 1;
    if (self->unk15 == 0) {
        self->x_speed = FIXED(-0.5);
    } else {
        self->x_speed = FIXED(0.5);
    }
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    self->unk7C = 0x30;
}

void spike_marl_roll_entry_update(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (--self->unk7C == 0) {
        self->x_speed = self->unk15 & PLAYER_FACING_RIGHT ? FIXED(2) : FIXED(-2);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void spike_marl_check_patrol_path(struct MainObj* self)
{
    s16 temp_v0;
    s16 var_v1;
    s32 temp_v0_2;

    if (self->unk5 == 2) {
        temp_v0 = self->unk7C;
        if (temp_v0 != 0) {
            self->unk7C = temp_v0 - 1;
            return;
        }

        if (self->unk15 != 0) {
            var_v1 = self->x_pos.u.hi + self->terrain_box->unk0 + 0x10;
        } else {
            var_v1 = self->x_pos.u.hi - self->terrain_box->unk0 - 0x10;
        }

#ifdef MMX4_PC
        if (func_8002D724(
                PLAYER_OBJECT(self), var_v1,
                self->terrain_box->unk3 + (self->y_pos.u.hi + self->terrain_box->unk1))
            == 0) {
#else
        if (((s32(*)(void*, s16, s16))func_8002D724)(
                self, var_v1,
                self->terrain_box->unk3 + (self->y_pos.u.hi + self->terrain_box->unk1))
            == 0) {
#endif
            self->ext.main_3.turn_timer = 0x78;
            self->unk5 = 3;
            self->unk6 = 0;
            set_animation(self, 2);
        }

        if (self->ext.main_3.player_ahead == 0) {
            if (self->unk15 != 0) {
                if ((self->collision_flags & 1) != 0) {
                    self->unk5 = 3;
                    self->unk6 = 0;
                    self->ext.main_3.turn_timer = 0x78;
                    set_animation(self, 2);
                }
            } else if ((self->collision_flags & 2) != 0) {
                self->unk5 = 3;
                self->unk6 = 0;
                self->ext.main_3.turn_timer = 0x78;
                set_animation(self, 2);
            }
        } else {
            temp_v0_2 = self->x_pos.val - g_Player.x_pos.val;
            if (self->unk15 != 0) {
                if (temp_v0_2 <= 0) {
                    if ((self->collision_flags & 1) == 0) {
                        return;
                    }
                }
            } else if (temp_v0_2 >= 0) {
                if ((self->collision_flags & 2) == 0) {
                    return;
                }
            }

            self->unk5 = 3;
            self->unk6 = 0;
            self->ext.main_3.player_ahead = 0;
            self->ext.main_3.turn_timer = 0x3C;
            set_animation(self, 2);
        }
    }
}

void spike_marl_begin_fall(struct MainObj* self)
{
    if (self->air_state == 0 && !(self->collision_flags & 8)) {
        if (self->unk5 != 5) {
            set_animation(self, 0);
            self->x_speed = 0;
        }
        self->unk5 = 6;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->x_accel = 0;
        self->air_state = 1;
    }
}

void spike_marl_detect_player(struct MainObj* self)
{
    if ((self->unk5 != 5 && self->unk5 != 6)) {
        if (ABS(g_Player.y_pos.i.hi, self->y_pos.i.hi) < 0x20 && ABS(g_Player.x_pos.i.hi, self->x_pos.i.hi) < 0x60) {
            if (!(self->collision_flags & 3) && ((self->unk15 == 0 && g_Player.x_pos.val < self->x_pos.val) || (self->unk15 != 0 && g_Player.x_pos.val > self->x_pos.val))) {
                self->ext.main_3.alerted = 1;
            }
        }

        if ((self->unk5 == 2) && (self->ext.main_3.alerted != 0)) {
            self->unk5 = 4;
            self->unk6 = 0;
            self->x_speed = 0;
            self->x_accel = 0;
        }
    }
}

void spike_marl_noop(struct MainObj* self)
{
}

void spike_marl_track_player_side(struct MainObj* self)
{
    if (self->unk5 == 2) {
        if (self->ext.main_3.player_ahead == 0) {
            if (ABS(g_Player.y_pos.i.hi, self->y_pos.i.hi) < 0x20) {
                if ((self->unk15 == 0 && g_Player.x_pos.val < self->x_pos.val) || (self->unk15 != 0 && g_Player.x_pos.val > self->x_pos.val)) {
                    self->ext.main_3.player_ahead = 1;
                }
            }
        } else if (ABS(g_Player.y_pos.i.hi, self->y_pos.i.hi) > 0x20) {
            self->ext.main_3.player_ahead = 0;
            self->ext.main_3.turn_timer = 0x78;
        }
    }
}

struct Unk_unk68 spike_marl_terrain_box = { 0, -1, 11, 18 };

struct Unk_unk68 spike_marl_walk_attack_box = { -7, -16, 18, 33 };

struct Unk_unk68 spike_marl_walk_hurt_box = { -14, -20, 32, 37 };

struct Unk_unk68 spike_marl_curl_attack_box = { -7, -10, 15, 25 };

struct Unk_unk68 spike_marl_curl_hurt_box = { -13, -19, 26, 36 };

union AnimationStep D_800F9CE0[] = {
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_800F9CE4[] = {
    { 6, 0, 1, 0x01 },
    { 4, 0, 1, 0x02 },
    { 6, 0, 1, 0x01 },
    { 6, 0, 1, 0x03 },
    { 4, 0, 1, 0x04 },
    { 6, 0, 1, 0x03 },
    { 14, 0, 1, 0x05 },
    { 6, 0, 1, 0x06 },
    { 4, 0, 1, 0x07 },
    { 6, 0, 1, 0x06 },
    { 6, 0, 1, 0x08 },
    { 4, 0, 1, 0x09 },
    { 6, 0, 1, 0x08 },
    { 14, 0, -13, 0x0A },
};

union AnimationStep D_800F9D1C[] = {
    { 14, 0, 1, 0x0B },
    { 6, 0, 1, 0x0C },
    { 4, 0, 1, 0x0D },
    { 8, 0, 1, 0x0C },
    { 13, 0, 1, 0x0E },
    { 1, 1, 0, 0x0E },
};

union AnimationStep D_800F9D34[] = {
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x00 },
    { 4, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x14 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x13 },
    { 6, 0, 1, 0x12 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 1, 3, 1, 0x16 },
    { 1, 0, 1, 0x16 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x1A },
    { 6, 4, 1, 0x1B },
    { 2, 0, 1, 0x1C },
    { 5, 0, 1, 0x1D },
    { 1, 2, 1, 0x1D },
    { 4, 0, 1, 0x1D },
    { 6, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 14, 0, 1, 0x1D },
    { 1, 1, 0, 0x1D },
};

union AnimationStep D_800F9DB0[] = {
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1C },
    { 6, 0, 1, 0x1B },
    { 2, 3, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x16 },
    { 2, 2, 1, 0x15 },
    { 6, 0, 1, 0x12 },
    { 2, 0, 1, 0x13 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x14 },
    { 2, 0, 1, 0x12 },
    { 1, 0, 1, 0x11 },
    { 1, 1, 0, 0x11 },
};

union AnimationStep D_800F9DF4[] = {
    { 3, 0, 1, 0x1D },
    { 3, 0, 1, 0x20 },
    { 3, 0, -2, 0x21 },
};

union AnimationStep D_800F9E00[] = {
    { 2, 0, 0, 0x22 },
};

union AnimationStep D_800F9E04[] = {
    { 1, 0, 0, 0x23 },
};

union AnimationStep D_800F9E08[] = {
    { 1, 0, 0, 0x24 },
};

union AnimationStep D_800F9E0C[] = {
    { 1, 0, 0, 0x25 },
};

union AnimationStep D_800F9E10[] = {
    { 1, 0, 0, 0x26 },
};

union AnimationStep D_800F9E14[] = {
    { 1, 0, 0, 0x27 },
};

union AnimationStep D_800F9E18[] = {
    { 1, 0, 0, 0x28 },
};

union AnimationStep* D_800F9E1C[] = {
    D_800F9CE0,
    D_800F9CE4,
    D_800F9D1C,
    D_800F9D34,
    D_800F9DB0,
    D_800F9DF4,
    D_800F9E00,
    D_800F9E04,
    D_800F9E08,
    D_800F9E0C,
    D_800F9E10,
    D_800F9E14,
    D_800F9E18,
};

u8 spike_marl_debris[] = { 6, 7, 8, 9, 10, 11, 12, 0 };

void (*spike_marl_state_funcs[])(struct MainObj*) = {
    func_80043390,
    spike_marl_run,
    spike_marl_cleanup,
};

void (*spike_marl_step_funcs[])(struct MainObj*) = {
    (void (*)(struct MainObj*))enemy_hit_reaction,
    spike_marl_resume_step,
    spike_marl_patrol,
    spike_marl_turn,
    spike_marl_curl,
    spike_marl_roll,
    spike_marl_fall,
    spike_marl_uncurl,
    spike_marl_roll_entry,
};

void (*spike_marl_patrol_funcs[])(struct MainObj*) = {
    spike_marl_patrol_begin,
    spike_marl_patrol_update,
};

void (*spike_marl_turn_funcs[])(struct MainObj*) = {
    spike_marl_turn_start,
    spike_marl_turn_flip,
};

void (*spike_marl_curl_funcs[])(struct MainObj*) = {
    spike_marl_curl_begin,
    spike_marl_curl_update,
};

void (*spike_marl_roll_funcs[])(struct MainObj*) = {
    spike_marl_roll_begin,
    spike_marl_roll_update,
    func_80043C0C,
};

void (*spike_marl_uncurl_funcs[])(struct MainObj*) = {
    spike_marl_uncurl_begin,
    spike_marl_uncurl_update,
};

void (*spike_marl_roll_entry_funcs[])(struct MainObj*) = {
    spike_marl_roll_entry_begin,
    spike_marl_roll_entry_update,
};
