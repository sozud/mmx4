// MainObj, main_object_update_funcs[3]
// 80043340..8004441C
#include "common.h"
#include "func_tables.h"

extern struct Unk_unk68 item_carrier_hitboxes[];
extern u8 item_carrier_debris[];
extern u8 item_carrier_capsule_debris[];

void spike_marl_update(struct MainObj* self)
{
    spike_marl_state_funcs[self->state](self);
    CollisionRelated(PLAYER_OBJECT(self));
}

// spike_marl_init
INCLUDE_ASM("main/nonmatchings/mains/main_03_spike_marl", func_80043390);

void spike_marl_run(struct MainObj* self)
{
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
    if (func_8002DD04(self) < 0) {
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
    u8 subtype;

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
    s32 velocity = FIXED(-0.8);
    self->unk6 = 1;
    if (self->unk15 & 0x40) {
        velocity = FIXED(0.8);
    }
    self->x_speed = velocity;
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
        self->unk15 ^= 0x40;
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
        func_8001540C(2, 0, self);
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
    s32 value;

    if (self->unk7C == 0) {
        func_8001540C(2, 1, self);
        set_animation(self, 5);
        value = FIXED(-4);
        if (self->unk15 & 0x40) {
            value = FIXED(4);
        }
        self->x_speed = value;
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
INCLUDE_ASM("main/nonmatchings/mains/main_03_spike_marl", func_80043C0C);

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
    s32 x_vel;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (--self->unk7C == 0) {
        x_vel = FIXED(-2);
        if (self->unk15 & 0x40) {
            x_vel = FIXED(2);
        }
        self->x_speed = x_vel;
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

        if (((s32(*)(void*, s16, s16))func_8002D724)(
                self, var_v1,
                self->terrain_box->unk3 + (self->y_pos.u.hi + self->terrain_box->unk1))
            == 0) {
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
    s16 temp_v1;
    s32 temp_v0;

    if (self->unk5 < 5 || self->unk5 > 6) {
        temp_v1 = self->y_pos.i.hi;
        temp_v0 = g_Player.y_pos.i.hi - temp_v1;
        if (temp_v0 >= 0) {
            if (temp_v0 < 0x20) {
                goto check_x_distance;
            }
        } else if (temp_v1 - g_Player.y_pos.i.hi < 0x20) {
        check_x_distance:
            temp_v1 = self->x_pos.i.hi;
            temp_v0 = g_Player.x_pos.i.hi - temp_v1;
            if (temp_v0 >= 0) {
                if (temp_v0 < 0x60) {
                    goto check_facing;
                }
            } else if (temp_v1 - g_Player.x_pos.i.hi < 0x60) {
            check_facing:
                if (!(self->collision_flags & 3) && ((self->unk15 == 0 && g_Player.x_pos.val < self->x_pos.val) || (self->unk15 != 0 && g_Player.x_pos.val > self->x_pos.val))) {
                    self->ext.main_3.alerted = 1;
                }
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
    s32 temp_v0;

    if (self->unk5 == 2) {
        if (self->ext.main_3.player_ahead == 0) {
            temp_v0 = g_Player.y_pos.i.hi - self->y_pos.i.hi;
            if (temp_v0 >= 0) {
                if (temp_v0 < 0x20) {
                    goto block_6;
                }
            } else if (self->y_pos.i.hi - g_Player.y_pos.i.hi < 0x20) {
            block_6:
                if ((self->unk15 == 0 && g_Player.x_pos.val < self->x_pos.val) || (self->unk15 != 0 && g_Player.x_pos.val > self->x_pos.val)) {
                    self->ext.main_3.player_ahead = 1;
                }
            }
        } else {
            temp_v0 = g_Player.y_pos.i.hi - self->y_pos.i.hi;
            if (temp_v0 >= 0) {
                if (temp_v0 >= 0x21) {
                    goto block_15;
                }
            } else if (self->y_pos.i.hi - g_Player.y_pos.i.hi >= 0x21) {
            block_15:
                self->ext.main_3.player_ahead = 0;
                self->ext.main_3.turn_timer = 0x78;
            }
        }
    }
}

struct Unk_unk68 spike_marl_terrain_box = { 0, -1, 11, 18 };

struct Unk_unk68 spike_marl_walk_attack_box = { -7, -16, 18, 33 };

struct Unk_unk68 spike_marl_walk_hurt_box = { -14, -20, 32, 37 };

struct Unk_unk68 spike_marl_curl_attack_box = { -7, -10, 15, 25 };

struct Unk_unk68 spike_marl_curl_hurt_box = { -13, -19, 26, 36 };

union AnimationStep D_800F9CE0[] = {
    { 0x00000001 },
};

union AnimationStep D_800F9CE4[] = {
    { 0x01010006 },
    { 0x02010004 },
    { 0x01010006 },
    { 0x03010006 },
    { 0x04010004 },
    { 0x03010006 },
    { 0x0501000E },
    { 0x06010006 },
    { 0x07010004 },
    { 0x06010006 },
    { 0x08010006 },
    { 0x09010004 },
    { 0x08010006 },
    { 0x0AF3000E },
};

union AnimationStep D_800F9D1C[] = {
    { 0x0B01000E },
    { 0x0C010006 },
    { 0x0D010004 },
    { 0x0C010008 },
    { 0x0E01000D },
    { 0x0E000101 },
};

union AnimationStep D_800F9D34[] = {
    { 0x0F010002 },
    { 0x10010002 },
    { 0x00010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x00010002 },
    { 0x11010004 },
    { 0x12010002 },
    { 0x14010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x12010006 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x16010301 },
    { 0x16010001 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x1B010002 },
    { 0x1A010002 },
    { 0x1B010406 },
    { 0x1C010002 },
    { 0x1D010005 },
    { 0x1D010201 },
    { 0x1D010004 },
    { 0x1E010006 },
    { 0x1F010002 },
    { 0x1D01000E },
    { 0x1D000101 },
};

union AnimationStep D_800F9DB0[] = {
    { 0x1D010002 },
    { 0x1C010002 },
    { 0x1B010006 },
    { 0x1A010302 },
    { 0x19010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x18010002 },
    { 0x16010002 },
    { 0x15010202 },
    { 0x12010006 },
    { 0x13010002 },
    { 0x12010002 },
    { 0x14010002 },
    { 0x12010002 },
    { 0x11010001 },
    { 0x11000101 },
};

union AnimationStep D_800F9DF4[] = {
    { 0x1D010003 },
    { 0x20010003 },
    { 0x21FE0003 },
};

union AnimationStep D_800F9E00[] = {
    { 0x22000002 },
};

union AnimationStep D_800F9E04[] = {
    { 0x23000001 },
};

union AnimationStep D_800F9E08[] = {
    { 0x24000001 },
};

union AnimationStep D_800F9E0C[] = {
    { 0x25000001 },
};

union AnimationStep D_800F9E10[] = {
    { 0x26000001 },
};

union AnimationStep D_800F9E14[] = {
    { 0x27000001 },
};

union AnimationStep D_800F9E18[] = {
    { 0x28000001 },
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
