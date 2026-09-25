// MainObj, main_object_update_funcs[3]
// 80043340..8004441C
#include "common.h"
#include "func_tables.h"

extern struct Unk_unk68 D_800F9B24[];
extern u8 D_800F9C44[];
extern u8 D_800F9C48[];

void spike_marl_update(struct MainObj* arg0)
{
    spike_marl_state_funcs[arg0->state](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_03", func_80043390);

void spike_marl_run(struct MainObj* arg0)
{
    if (arg0->unk5 != 8) {
        spike_marl_check_patrol_path(arg0);
        spike_marl_begin_fall(arg0);
        spike_marl_track_player_side(arg0);
        spike_marl_detect_player(arg0);
        spike_marl_noop(arg0);
    }
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    spike_marl_step_funcs[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    arg0->ext.main_3.saved_step = (u32)arg0->unk5;
    if (func_8002DD04(arg0) < 0) {
        func_800AF808((struct BaseObj*)arg0);
        func_800C813C(7, &D_800F9E50, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0x11);
    } else if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) == 0) {
        func_8002B318((struct BaseObj*)arg0, 0x20, 0x20);
        return;
    }
    arg0->state = 2;
}

void spike_marl_cleanup(struct MainObj* arg0)
{
    u8 subtype;

    subtype = (u8)arg0->unk2;
    arg0->ext.main_3.alerted = 0;
    arg0->ext.main_3.roll_timer = 0;
    arg0->ext.main_3.player_ahead = 0;
    arg0->ext.main_3.turn_timer = 0;
    arg0->ext.main_3.saved_step = 0;
    if (subtype < 2U) {
        func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void spike_marl_resume_step(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_3.saved_step;
}

void spike_marl_patrol(struct MainObj* arg0)
{
    spike_marl_patrol_funcs[arg0->unk6](arg0);
}

void spike_marl_patrol_begin(struct MainObj* arg0)
{
    s32 velocity = FIXED(-0.8);
    arg0->unk6 = 1;
    if (arg0->unk15 & 0x40) {
        velocity = FIXED(0.8);
    }
    arg0->unk20 = velocity;
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void spike_marl_patrol_update(struct MainObj* arg0)
{
    struct MainObj* temp_s0;
    s32 temp_v0;

    temp_s0 = arg0;
    if (temp_s0->ext.main_3.player_ahead == 0) {
        temp_v0 = temp_s0->ext.main_3.turn_timer - 1;
        temp_s0->ext.main_3.turn_timer = temp_v0;
        if (temp_v0 == 0) {
            func_80015D60(temp_s0, 2);
            temp_s0->unk5 = 3;
            temp_s0->unk6 = 0;
            temp_s0->ext.main_3.turn_timer = 0x78;
        }
    }
    func_8002B718((struct MovingObj*)temp_s0);
    func_80015DC8(ANIMATED_OBJECT(temp_s0));
}

void spike_marl_turn(struct MainObj* arg0)
{
    spike_marl_turn_funcs[arg0->unk6](arg0);
}

void func_80043858(struct MainObj* arg0)
{
    func_80015D60(arg0, 2);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->unk20 = 0;
    arg0->unk6 = 1;
}

void func_80043898(struct PlayerObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk28 = 0;
        arg0->unk15 ^= 0x40;
        func_80015D60(arg0, 1);
        arg0->unk5 = 2;
        arg0->x_vel.val = 0;
        arg0->unk6 = 0;
        arg0->input.buttons.held = 0x14;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void spike_marl_curl(struct MainObj* arg0)
{
    spike_marl_curl_funcs[arg0->unk6](arg0);
}

void spike_marl_curl_begin(struct MainObj* arg0)
{
    func_80015D60(arg0, 3);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 1;
}

void spike_marl_curl_update(struct MainObj* self)
{
    switch (self->animation_step.fields.event) {
    case 1:
        self->unk60 = 4;
        self->unk7C = 0xF;
        self->unk20 = 0;
        self->unk5 = 5;
        self->unk6 = 0;
        break;
    case 2:
        func_8001540C(2, 0, self);
        break;
    case 3:
        self->unk54 = (const u8*)&D_800F9CDC;
        self->unk50 = (const u8*)&D_800F9CD8;
        break;
    case 4:
        self->collision_data = (const u16*)D_801060F0;
        break;
    }

    func_80015DC8(ANIMATED_OBJECT(self));
}

void spike_marl_roll(struct MainObj* arg0)
{
    spike_marl_roll_funcs[arg0->unk6](arg0);
}

void spike_marl_roll_begin(struct MainObj* self)
{
    s32 value;

    if (self->unk7C == 0) {
        func_8001540C(2, 1, self);
        func_80015D60(self, 5);
        value = FIXED(-4);
        if (self->unk15 & 0x40) {
            value = FIXED(4);
        }
        self->unk20 = value;
        self->unk6 = 1;
    } else {
        self->unk7C--;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void spike_marl_roll_update(struct MainObj* self)
{
    s32 timer;
    u8 flags;

    timer = self->ext.main_3.roll_timer + 4;
    self->ext.main_3.roll_timer = timer;
    if (timer < 0 || (self->unk15 == 0 ? g_Player.x_pos.val > self->x_pos.val : g_Player.x_pos.val < self->x_pos.val)) {
        self->unk28 = FIXED(-0.09375);
        self->unk6 = 2;
    }

    flags = self->unk70;
    if (((flags & 2) && self->unk15 == 0) || ((flags & 1) && self->unk15 != 0)) {
        self->unk60 = 3;
        self->unk28 = 0;
        self->unk20 = 0;
        self->unk5 = 7;
        self->unk6 = 0;
    }

    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

INCLUDE_ASM("main/nonmatchings/mains/main_03", func_80043C0C);

void spike_marl_fall(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        if (arg0->ext.main_3.alerted != 0) {
            arg0->collision_data = D_80106470;
            arg0->unk60 = 3;
            arg0->unk5 = 7;
        } else {
            func_80015D60(arg0, 1);
            arg0->unk5 = 2;
        }
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 0;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void spike_marl_uncurl(struct MainObj* arg0)
{
    spike_marl_uncurl_funcs[arg0->unk6](arg0);
}

void spike_marl_uncurl_begin(struct MainObj* arg0)
{
    func_80015D60(arg0, 4);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->ext.main_3.player_ahead = 1;
    arg0->ext.main_3.alerted = 0;
    arg0->ext.main_3.roll_timer = 0;
    arg0->ext.main_3.turn_timer = 0;
    arg0->unk6 = 1;
}

void spike_marl_uncurl_update(struct MainObj* arg0)
{
    switch (arg0->animation_step.fields.event) {
    case 1:
        arg0->unk20 = 0;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        func_80015D60(arg0, 1);
        break;
    case 2:
        arg0->unk54 = (const u8*)&D_800F9CD4;
        arg0->unk50 = (const u8*)&D_800F9CD0;
        break;
    case 3:
        arg0->collision_data = D_80106470;
        break;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void spike_marl_roll_entry(struct MainObj* arg0)
{
    spike_marl_roll_entry_funcs[arg0->unk6](arg0);
}

void spike_marl_roll_entry_begin(struct MainObj* arg0)
{
    arg0->unk6 = 1;
    if (arg0->unk15 == 0) {
        arg0->unk20 = FIXED(-0.5);
    } else {
        arg0->unk20 = FIXED(0.5);
    }
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk7C = 0x30;
}

void spike_marl_roll_entry_update(struct MainObj* arg0)
{
    s32 x_vel;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        x_vel = FIXED(-2);
        if (arg0->unk15 & 0x40) {
            x_vel = FIXED(2);
        }
        arg0->unk20 = x_vel;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void spike_marl_check_patrol_path(struct MainObj* arg0)
{
    s16 temp_v0;
    s16 var_v1;
    s32 temp_v0_2;

    if (arg0->unk5 == 2) {
        temp_v0 = arg0->unk7C;
        if (temp_v0 != 0) {
            arg0->unk7C = temp_v0 - 1;
            return;
        }

        if (arg0->unk15 != 0) {
            var_v1 = arg0->x_pos.u.hi + arg0->unk68->unk0 + 0x10;
        } else {
            var_v1 = arg0->x_pos.u.hi - arg0->unk68->unk0 - 0x10;
        }

        if (((s32(*)(void*, s16, s16))func_8002D724)(
                arg0, var_v1,
                arg0->unk68->unk3 + (arg0->y_pos.u.hi + arg0->unk68->unk1))
            == 0) {
            arg0->ext.main_3.turn_timer = 0x78;
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            func_80015D60(arg0, 2);
        }

        if (arg0->ext.main_3.player_ahead == 0) {
            if (arg0->unk15 != 0) {
                if ((arg0->unk70 & 1) != 0) {
                    arg0->unk5 = 3;
                    arg0->unk6 = 0;
                    arg0->ext.main_3.turn_timer = 0x78;
                    func_80015D60(arg0, 2);
                }
            } else if ((arg0->unk70 & 2) != 0) {
                arg0->unk5 = 3;
                arg0->unk6 = 0;
                arg0->ext.main_3.turn_timer = 0x78;
                func_80015D60(arg0, 2);
            }
        } else {
            temp_v0_2 = arg0->x_pos.val - g_Player.x_pos.val;
            if (arg0->unk15 != 0) {
                if (temp_v0_2 <= 0) {
                    if ((arg0->unk70 & 1) == 0) {
                        return;
                    }
                }
            } else if (temp_v0_2 >= 0) {
                if ((arg0->unk70 & 2) == 0) {
                    return;
                }
            }

            arg0->unk5 = 3;
            arg0->unk6 = 0;
            arg0->ext.main_3.player_ahead = 0;
            arg0->ext.main_3.turn_timer = 0x3C;
            func_80015D60(arg0, 2);
        }
    }
}

void spike_marl_begin_fall(struct MainObj* arg0)
{
    if (arg0->unk67 == 0 && !(arg0->unk70 & 8)) {
        if (arg0->unk5 != 5) {
            func_80015D60(arg0, 0);
            arg0->unk20 = 0;
        }
        arg0->unk5 = 6;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 1;
    }
}

void spike_marl_detect_player(struct MainObj* arg0)
{
    s16 temp_v1;
    s32 temp_v0;

    if (arg0->unk5 < 5 || arg0->unk5 > 6) {
        temp_v1 = arg0->y_pos.i.hi;
        temp_v0 = g_Player.y_pos.i.hi - temp_v1;
        if (temp_v0 >= 0) {
            if (temp_v0 < 0x20) {
                goto check_x_distance;
            }
        } else if (temp_v1 - g_Player.y_pos.i.hi < 0x20) {
        check_x_distance:
            temp_v1 = arg0->x_pos.i.hi;
            temp_v0 = g_Player.x_pos.i.hi - temp_v1;
            if (temp_v0 >= 0) {
                if (temp_v0 < 0x60) {
                    goto check_facing;
                }
            } else if (temp_v1 - g_Player.x_pos.i.hi < 0x60) {
            check_facing:
                if (!(arg0->unk70 & 3) && ((arg0->unk15 == 0 && g_Player.x_pos.val < arg0->x_pos.val) || (arg0->unk15 != 0 && g_Player.x_pos.val > arg0->x_pos.val))) {
                    arg0->ext.main_3.alerted = 1;
                }
            }
        }

        if ((arg0->unk5 == 2) && (arg0->ext.main_3.alerted != 0)) {
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            arg0->unk20 = 0;
            arg0->unk28 = 0;
        }
    }
}

void spike_marl_noop(struct MainObj* arg0)
{
}

void spike_marl_track_player_side(struct MainObj* arg0)
{
    s32 temp_v0;

    if (arg0->unk5 == 2) {
        if (arg0->ext.main_3.player_ahead == 0) {
            temp_v0 = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
            if (temp_v0 >= 0) {
                if (temp_v0 < 0x20) {
                    goto block_6;
                }
            } else if (arg0->y_pos.i.hi - g_Player.y_pos.i.hi < 0x20) {
            block_6:
                if ((arg0->unk15 == 0 && g_Player.x_pos.val < arg0->x_pos.val) || (arg0->unk15 != 0 && g_Player.x_pos.val > arg0->x_pos.val)) {
                    arg0->ext.main_3.player_ahead = 1;
                }
            }
        } else {
            temp_v0 = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
            if (temp_v0 >= 0) {
                if (temp_v0 >= 0x21) {
                    goto block_15;
                }
            } else if (arg0->y_pos.i.hi - g_Player.y_pos.i.hi >= 0x21) {
            block_15:
                arg0->ext.main_3.player_ahead = 0;
                arg0->ext.main_3.turn_timer = 0x78;
            }
        }
    }
}

struct Unk_unk68 D_800F9CCC = { 0, -1, 11, 18 };

struct Unk_unk68 D_800F9CD0 = { -7, -16, 18, 33 };

struct Unk_unk68 D_800F9CD4 = { -14, -20, 32, 37 };

struct Unk_unk68 D_800F9CD8 = { -7, -10, 15, 25 };

struct Unk_unk68 D_800F9CDC = { -13, -19, 26, 36 };

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

#ifdef VERSION_JP
u8 D_800F9F8C_jp[] = { 6, 7, 8, 9, 10, 11, 12, 0 };
#endif

#ifndef VERSION_JP
u8 D_800F9E50[] = { 6, 7, 8, 9, 10, 11, 12, 0 };
#endif

void (*spike_marl_state_funcs[])(struct MainObj*) = {
    func_80043390,
    spike_marl_run,
    spike_marl_cleanup,
};

void (*spike_marl_step_funcs[])(struct MainObj*) = {
    (void (*)(struct MainObj*))func_8009216C,
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
    func_80043858,
    func_80043898,
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
