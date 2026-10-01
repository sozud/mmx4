// 8002B694..8002BB80
#include "common.h"

extern s32 D_800F459C[];
extern s32 D_800F45C0[];
extern u32 D_800F45E4[10];

void reset_game_engine();

void reset_entity(struct PlayerObj* arg0);

void reset_main_and_shots();

// some kind of reset?
void reset_objects(void);

void func_8002AB20();

struct MainObj* find_free_main_obj(void);

struct WeaponObj* find_free_weapon_obj();

struct ShotObj* find_free_shot_obj(void);

struct VisualObj* find_free_visual_obj();

struct EffectObj* find_free_effect_obj(void);

struct ItemObj* find_free_item_obj();

struct MiscObj* find_free_misc_obj(void);

struct MiscObj* func_8002AE90(struct MiscObj* arg0, s32 arg1);

struct VisualObj* func_8002AF4C(struct VisualObj* arg0, s32 arg1);

struct QuadObj* find_free_quad_obj();

struct LayerObj* find_free_layer_obj();

struct UnkObj* find_free_unk_obj();

void despawn_object(struct ObjectHeader* arg0);

void despawn_object_permanently(struct ObjectHeader* arg0);

void ZeroObjectState(struct ObjectHeader* arg0);

// is_far_off_screen

// is_off_screen

void is_on_screen(struct BaseObj* arg0);

void update_on_screen(struct BaseObj* arg0, s32 arg1, s32 arg2);

void func_8002B3C0(struct BaseObj* arg0);

void func_8002B450(void);

void func_8002B458(struct QuadObj* arg0);

void func_8002B460(void);

struct EffectObj* func_8002B468(s8 id, s8 arg1);

// delete_effects

s32 D_800F459C[] = {
    0,
    0x31F1,
    0x61F7,
    0x8E39,
    0xB505,
    0xD4DB,
    0xEC83,
    0xFB14,
    0x10000,
};

s32 D_800F45C0[] = {
    0x10000,
    0xFB14,
    0xEC83,
    0xD4DB,
    0xB505,
    0x8E39,
    0x61F7,
    0x31F1,
    0,
};

u32 D_800F45E4[10] = {
    0,
    0x1936,
    0x4DA8,
    0x88D5,
    0xD218,
    0x137EF,
    0x1DEF1,
    0x34BEB,
    0xA2736,
    0xFFFFFFFF,
};

void move_with_gravity(struct AnimatedObj* arg0)
{
    arg0->x_pos.val += arg0->x_vel.val;
    arg0->y_pos.val -= arg0->y_vel.val;

    if (arg0->unk15) {
        arg0->x_vel.val += arg0->unk28;
    } else {
        arg0->x_vel.val -= arg0->unk28;
    }

    arg0->y_vel.val -= arg0->unk2C;
    if (arg0->y_vel.val < FIXED(-6.5)) {
        arg0->y_vel.val = FIXED(-6.5);
    }
}

void move_object(struct MovingObj* arg0)
{
    arg0->x_pos.val += arg0->x_vel.val;
    arg0->y_pos.val -= arg0->y_vel.val;
}

u8 get_random()
{
    u16 temp = cur_random * 3;
    u32 temp_v1;
    u8 pad[2];

    temp_v1 = temp >> 8;
    cur_random += temp_v1;
    cur_random &= 0xFF;
    cur_random |= temp_v1 << 8;

    return cur_random;
}

ret_u8 get_random_nonzero(void)
{
    u8 random_value;
    s32 result;

    random_value = get_random() & 0xFF;
    if (random_value != 0) {
        result = random_value;
    } else {
        result = 1;
    }
    return result;
}

ret_u8 angle_to_point(struct ObjectHeader* arg0, s32 arg1, s32 arg2)
{
    return angle_from_delta(arg0->x_pos.val - arg1, arg0->y_pos.val - arg2) & 0xFF;
}

ret_u8 angle_to_object(struct ObjectHeader* arg0, struct ObjectHeader* arg1)
{
    return angle_from_delta(arg0->x_pos.val - arg1->x_pos.val,
               arg0->y_pos.val - arg1->y_pos.val)
        & 0xFF;
}

u8 angle_from_delta(s32 arg0, s32 arg1)
{
    extern u32 D_800F45E4[];
    s32 temp_lo;
    s32 angle;
    s16 var_a3, var_a2;
    u32* ptr;

    if (arg0 < 0) {
        var_a2 = 1;
        arg0 = -arg0;
    } else {
        var_a2 = -1;
    }
    if (arg1 < 0) {
        var_a3 = -1;
        arg1 = -arg1;
    } else {
        var_a3 = 1;
    }

    if (arg1 >> 0x10 != 0) {
        temp_lo = arg0 / (arg1 >> 0x10);
        if (temp_lo < 0x10000) {
            ptr = &D_800F45E4[4];
            while (*ptr > temp_lo) {
                ptr--;
            }
#ifdef MMX4_PC
            arg0 = ptr - D_800F45E4;
#else
            arg0 = ((u32)ptr - (u32)D_800F45E4) >> 2;
#endif
        } else {
            ptr = &D_800F45E4[5];
            while (*ptr < temp_lo) {
                ptr++;
            }
            arg0 = ptr - D_800F45E4 - 1;
        }
    } else {
        arg0 = 8;
    }

    if (var_a3 << 0x10 < 0) {
        if (var_a2 << 0x10 > 0) {
            if ((s16)arg0 == 8) {
                return 0;
            }
            angle = 0x18 + arg0;
        } else {
            angle = 0x18 - arg0;
        }
    } else {
        angle = (var_a2 << 0x10) <= 0 ? arg0 + 8 : 8 - arg0;
    }

    return angle & 0xFF;
}

extern s32 D_800F459C[];

extern s32 D_800F45C0[];

void set_velocity_from_angle(struct MovingObj* arg0, arg_u8 arg1)
{
    u8 angle;
    s16 var_a2, var_v0;
    s16 var_v1;

    angle = arg1;
    if (angle < 0x10) {
        var_a2 = 1;
        if (angle < 8) {
            var_v1 = 8 - angle;
            var_v0 = 1;
        } else {
            var_v1 = angle - 8;
            var_v0 = -1;
        }
    } else {
        var_a2 = -1;
        if (angle < 0x18) {
            var_v1 = 0x18 - angle;
            var_v0 = -1;
        } else {
            var_v1 = angle - 0x18;
            var_v0 = 1;
        }
    }
    arg0->x_vel.val = D_800F459C[var_v1] * var_v0;
    arg0->y_vel.val = D_800F45C0[var_v1] * var_a2;
}

void func_8002B9F0(s32* arg0, s32* arg1, u8 arg2)
{
    s16 var_a3, var_v0;
    s16 var_v1;

    if (arg2 < 0x10) {
        var_a3 = 1;
        if (arg2 < 8) {
            var_v1 = 8 - arg2;
            var_v0 = 1;
        } else {
            var_v1 = arg2 - 8;
            var_v0 = -1;
        }
    } else {
        var_a3 = -1;
        if (arg2 < 0x18) {
            var_v1 = 0x18 - arg2;
            var_v0 = -1;
        } else {
            var_v1 = arg2 - 0x18;
            var_v0 = 1;
        }
    }
    *arg0 = D_800F459C[var_v1] * var_v0;
    *arg1 = D_800F45C0[var_v1] * var_a3;
}

s16 func_8002BAA4(void)
{
    u16 flags = g_Player.pressed_input;
    s16 count = (flags & 0xF) != 0;
    if (flags & 0x1B0) {
        count++;
    }
    return count;
}

s16 get_layout_screen(s16 arg0, s16 arg1, s16 arg2)
{
    struct BackgroundObj* temp_v1 = &background_objects[arg0];
    s16 var_x, var_y;
    s16 temp;

    var_x = (temp_v1->x_pos.i.hi + arg1) / 256;
    var_y = (temp_v1->y_pos.i.hi + arg2) / 256;
    temp = var_x + (arg0 * layout_size + layout_width * var_y);

    return SP_BG_TILEMAP[temp];
}
