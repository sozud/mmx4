// MainObj, main_object_update_funcs[40]
// 80061DC0..800623C4
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_40_breakable_terrain.h"
#include "main/visuals/visual_08_ice_shard.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/misc/misc_02_rubble.h"
#include "main/objects.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#endif

void breakable_terrain_spawn_rubble(struct MainObj*);

void breakable_terrain_crumble(struct MainObj*);
void breakable_terrain_remove(struct MainObj*);

extern void (*breakable_terrain_state_funcs[])(struct MainObj*);

void breakable_terrain_update(struct MainObj* self)
{
    breakable_terrain_state_funcs[self->state](self);
}

// breakable_terrain_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

extern struct Unk_unk68 D_80108504[];
extern s8* D_800FEA24[7];
extern union AnimationStep** D_800FEA40[7];
extern struct Unk_unk68 D_800FEAA0;
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80061DFC(struct MainObj* arg0);
void func_80061F2C(struct MainObj* arg0);
extern u8 D_800FEA1C[8];
u8 func_80062338(struct MainObj*);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_40_breakable_terrain", func_80061DFC);
#else
void func_80061DFC(struct MainObj* arg0)
{
    s8** boxes = D_800FEA24;

    arg0->invincibility_timer = 0;
    arg0->ext.main_40.unk80 = arg0->unk2 >> 4;
    arg0->ext.main_40.unk81 = arg0->unk2 & 0xF;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->air_state = 0;
    arg0->hurt_box = boxes[arg0->ext.main_40.unk80];
    arg0->animation_table = (const u8* const*)D_800FEA40[arg0->ext.main_40.unk80];
    arg0->hp = 0;
    arg0->contact_damage = 0;
    arg0->attack_box = NULL;
    arg0->terrain_box = NULL;
    if (arg0->ext.main_40.unk80 == 1) {
        set_animation(arg0, 0);
        arg0->hp = 3;
        arg0->contact_damage = 2;
        arg0->attack_box = boxes[arg0->ext.main_40.unk80];
        arg0->terrain_box = &D_800FEAA0;
    }
    arg0->collision_data = D_80108504;
    arg0->unk15 = 0;
    arg0->state++;
}
#endif

// breakable_terrain_main
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80061F2C(struct MainObj* arg0)
{
    struct Main40Ext* ext = &arg0->ext.main_40;
    s32 collision;
    s32 dy;

    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk18.val = arg0->x_pos.val;
    if (ext->unk80 == 1) {
        func_8002D9BC(arg0);
        collision = func_8002DD04(arg0);
        if (collision >= 0) {
            if (collision > 0)
                arg0->unk42 |= 0x8000;
            else
                arg0->unk42 &= 0x7FFF;
            if (!func_80062338(arg0))
                goto check;
        }
        ext->timer = 0x30;
        ext->trigger_time = 0x2F;
        arg0->on_screen = 0;
        spawn_debris(7, D_800FEA1C, arg0);
        arg0->state++;
        return;
    }
    if (ext->unk80 != 0 && ext->unk80 < 7) {
        dy = (s32)((u32)breakable_terrain_effect_offsets[(ext->unk80 - 2) * 2 + 1] << 16);
        if (arg0->y_pos.val - dy - background_objects[arg0->bg_offset].y_pos.val > 0xA80000) {
            ext->timer = 0x10;
            ext->trigger_time = 8;
            arg0->state++;
        }
    }
check:
    if (func_8002B160(BASE_OBJECT(arg0)) != 0) {
        despawn_object(OBJECT_HEADER(arg0));
        return;
    }
    if (ext->unk80 == 1)
        is_on_screen(BASE_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_40_breakable_terrain", func_80061F2C);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_40_breakable_terrain", breakable_terrain_crumble);
#else
void breakable_terrain_crumble(struct MainObj* self)
{
    s32 index;

    self->ext.main_40.timer--;
    if (self->ext.main_40.timer != 0) {
        if (!(WEAPON_FRAME_COUNTER & 7)) {
            if (self->ext.main_40.unk80 < 2U) {
                func_800AF878(BASE_OBJECT(self), 1, 0x10, 0x30);
            }
        }
        if (self->ext.main_40.unk80 >= 2U && self->ext.main_40.timer == self->ext.main_40.trigger_time) {
            index = (self->ext.main_40.unk80 - 2) * 2;
            ((void (*)(s32, s32, s32))apply_tile_effect)(self->ext.main_40.unk81 + 6,
                self->x_pos.i.hi + breakable_terrain_effect_offsets[index],
                self->y_pos.i.hi + breakable_terrain_effect_offsets[index + 1]);
        }
    } else {
        self->state++;
    }
}
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_40_breakable_terrain", breakable_terrain_remove);
#else
void breakable_terrain_remove(struct MainObj* self)
{
    u8 state = self->ext.main_40.unk80;
    s32 offset;

    if (state >= 2U) {
        offset = (state - 2) * 2;
        ((void (*)(s32, s32, s32))apply_tile_effect)(self->ext.main_40.unk81 + 0xB,
            self->x_pos.i.hi + breakable_terrain_effect_offsets[offset],
            self->y_pos.i.hi + breakable_terrain_effect_offsets[offset + 1]);
        breakable_terrain_spawn_rubble(self);
    }
    despawn_object_permanently(OBJECT_HEADER(self));
}
#endif

extern u8 breakable_terrain_rubble_sizes[];
extern u8 breakable_terrain_rubble_variants[];

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_40_breakable_terrain", breakable_terrain_spawn_rubble);
#else
void breakable_terrain_spawn_rubble(struct MainObj* self)
{
    s32 temp_v0;
    u16 temp_s0;
    u16 temp_s1;
    u8 temp_s2;
    u8 temp_s3;
    u8 temp_s5;

    temp_s1 = (u16)self->x_pos.i.hi;
    temp_s0 = (u16)self->y_pos.i.hi;
    temp_v0 = self->ext.main_0.index * 3;
    temp_s5 = breakable_terrain_rubble_sizes[2 + temp_v0];
    temp_s2 = breakable_terrain_rubble_sizes[temp_v0];
    temp_s3 = breakable_terrain_rubble_sizes[1 + temp_v0];
    spawn_rubble(temp_s5 * 2, breakable_terrain_rubble_variants, self, 0);
    func_800B10E4(0x21,
        (s16)temp_s1 - (temp_s2 >> 1),
        (s16)temp_s0 - (temp_s3 >> 1) + 0x10,
        (s16)temp_s1 + (temp_s2 >> 1),
        (s16)temp_s0 + (temp_s3 >> 1) + 0x10,
        temp_s5);
    func_8001540C(0, (get_random() & 1) ^ 1, self);
}
#endif

// breakable_terrain_check_hit
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_40_breakable_terrain", func_80062338);
#else
#ifdef MMX4_PC
static const struct Unk_unk68* relative_bounds_or_zero(const struct Unk_unk68* bounds)
{
    static const struct Unk_unk68 zero;

    return bounds != NULL ? bounds : &zero;
}
#define BOUNDS(bounds) relative_bounds_or_zero(bounds)
#else
#define BOUNDS(bounds) (bounds)
#endif

u8 func_80062338(struct MainObj* self)
{
    struct PlayerObj* player = &g_Player;
    s16 edge = self->x_pos.u.hi + (s8)BOUNDS(self->terrain_box)->unk0;
    s16 player_edge = player->x_pos.u.hi + (s8)BOUNDS(player->unk68)->unk0;
    s16 distance = edge - player_edge >= 0 ? (s16)(edge - player_edge) : (s16)(player_edge - edge);

    return distance <= BOUNDS(self->terrain_box)->unk2 + BOUNDS(player->unk68)->unk2;
}
#undef BOUNDS
#endif

s8 D_800FE9C8[4] = { -32, -32, 64, 80 };

s8 D_800FE9CC[4] = { -16, -48, 32, 96 };

s8 D_800FE9D0[4] = { -16, -32, 32, 64 };

s8 D_800FE9D4[4] = { -40, -48, 80, 96 };

s8 D_800FE9D8[4] = { -104, -24, -48, 48 };

s8 D_800FE9DC[4] = { -40, -48, 80, 96 };

s8 D_800FE9E0[4] = { -32, -24, 64, 48 };

union AnimationStep breakable_terrain_anim_0[] = { { 1, 0, 0, 0x00 } };

union AnimationStep breakable_terrain_anim_1[] = { { 1, 0, 0, 0x01 } };

union AnimationStep breakable_terrain_anim_2[] = { { 1, 0, 0, 0x02 } };

union AnimationStep breakable_terrain_anim_3[] = { { 1, 0, 0, 0x03 } };

union AnimationStep breakable_terrain_anim_4[] = { { 1, 0, 0, 0x04 } };

union AnimationStep breakable_terrain_anim_5[] = { { 1, 0, 0, 0x05 } };

union AnimationStep* breakable_terrain_animations[6] = {
    breakable_terrain_anim_0,
    breakable_terrain_anim_1,
    breakable_terrain_anim_2,
    breakable_terrain_anim_3,
    breakable_terrain_anim_4,
    breakable_terrain_anim_5,
};

u8 D_800FEA14[8] = { 0, 1, 2, 1, 0, 2, 0, 0 };

u8 D_800FEA1C[8] = { 1, 2, 3, 4, 5, 2, 4, 0 };

s8* D_800FEA24[7] = {
    D_800FE9C8,
    D_800FE9CC,
    D_800FE9D0,
    D_800FE9D4,
    D_800FE9D8,
    D_800FE9DC,
    D_800FE9E0,
};

union AnimationStep** D_800FEA40[7] = {
    NULL,
    breakable_terrain_animations,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

s8 breakable_terrain_effect_offsets[12] = { -16, -32, -40, -48, -104, -24, -40, -48, -32, -24, 0, 0 };

u8 breakable_terrain_rubble_sizes[16] = { 32, 48, 3, 80, 80, 6, 208, 32, 8, 64, 32, 5, 64, 32, 5, 0 };

void (*breakable_terrain_state_funcs[])(struct MainObj*) = {
    func_80061DFC,
    func_80061F2C,
    breakable_terrain_crumble,
    breakable_terrain_remove,
};

u8 breakable_terrain_rubble_variants[24] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    0,
    0,
    0,
};

struct Unk_unk68 D_800FEAA0 = { 0, 0, 16, 48 };
