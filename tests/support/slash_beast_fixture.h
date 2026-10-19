#ifndef MMX4_TESTS_SLASH_BEAST_FIXTURE_H
#define MMX4_TESTS_SLASH_BEAST_FIXTURE_H
#include "test_runtime.h"
#include "main/mains/main_54_slash_beast.h"
#include "main/13A8C.h"
#include "main/collision_bounds.h"
#include "main/player_animations.h"
#include "main/player_animations_2.h"
#include "main/sprite_animations.h"
#include "main/weapons/weapon_24_zero_saber.h"
#include "main/55C4.h"
#include "main/14A60.h"
#include "main/misc/misc_26_slash_beast_afterimage.h"
#include "main/tile_effects.h"
#include "main/3D88.h"
void slash_beast_death(struct MainObj*);
extern struct Unk5 D_800F0E18[];
void slash_beast_decide(struct MainObj*);
void slash_beast_high_leap(struct MainObj*);
extern u8 slash_beast_pattern_weights[12];
extern u8** slash_beast_patterns[3];
void slash_beast_stagger(struct MainObj*);
extern struct Unk_unk68 D_80100204;
extern struct Unk_unk68 D_80100210;
extern struct Unk_unk68 D_80100214;
void slash_beast_crescent(struct MainObj*);
extern struct Unk_unk68 D_80100200;
extern struct Unk_unk68 D_80100220;
extern struct Unk_unk68 D_80100224;
extern struct Unk_unk68 ground_hunter_crawl_box[];
extern struct Unk_unk68 lemon_hit_box[];
void slash_beast_intro_land(struct MainObj*);
void slash_beast_dash(struct MainObj*);
void slash_beast_grab(struct MainObj*);
void slash_beast_high_leap_jump(struct MainObj*);
void slash_beast_intro(struct MainObj*);
void slash_beast_jump(struct MainObj*);
void slash_beast_start_pattern(struct MainObj*);

static const u32 slash_beast_death_blink_expected[] = { 1u, 0u, 0u, 0u, 0u, 0x8000u, 2u, 0u, 5u };
static u32 test_slash_beast_death_blink(u32 row)
{
    u32 observed_values[9];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = 1;
    pool_0_full = 255;
    obj.invincibility_timer = 31;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    slash_beast_death_blink(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)effect_objects[0].x_pos.i.hi;
    observed_values[3] = (u32)effect_objects[0].y_pos.i.hi;
    observed_values[4] = (u32)obj.invincibility_timer;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = (u32)obj.unk7C;
    observed_values[8] = (u32)obj.unk7E;
    return c_test_observe(0, row, observed_values, slash_beast_death_blink_expected, 9);
}

#include "support/boss_death_flash.h"
BOSS_DEATH_FLASH_TESTS(slash_beast_death_flash, slash_beast_death_blink, 0)

static const u32 slash_beast_death_flash_cases_expected[] = { 0x10501u, 0x10502u, 0x10502u, 0x50001u, 0xF0F01u, 0x5FB01u, 0x50001u };
#include "support/state_cases.h"

static struct Unk_unk68 beast_box = { 0, 8, 16, 24 };
#define BEAST(a, b) (state_reset(a, b, 0), so.terrain_box = &beast_box)
#define HIGH() (so.x_pos.i.hi = 0x100, so.y_pos.i.hi = -0x200)
static void sb_throw_left(void)
{
    BEAST(8, 3);
    so.x_pos.i.hi = 0x50;
    slash_beast_grab(&so);
}
static void sb_throw_right(void)
{
    BEAST(8, 3);
    so.unk15 = 0x40;
    slash_beast_grab(&so);
}
static void sb_check_miss(void)
{
    BEAST(8, 0);
    so.unk7C = 1;
    g_Player.stun_timer = 0;
    slash_beast_grab(&so);
}
static void sb_check_grab_left(void)
{
    BEAST(8, 0);
    so.unk7C = 2;
    g_Player.stun_timer = 1;
    so.x_pos.i.hi = 0xC0;
    slash_beast_grab(&so);
}
static void sb_check_grab_right(void)
{
    BEAST(8, 0);
    so.unk7C = 2;
    g_Player.stun_timer = 1;
    so.x_pos.i.hi = 0x40;
    slash_beast_grab(&so);
}
static void sb_windup(void)
{
    BEAST(8, 1);
    so.unk7C = 1;
    slash_beast_grab(&so);
}
static void sb_windup_wait(void)
{
    BEAST(8, 1);
    so.unk7C = 2;
    slash_beast_grab(&so);
}
static void sb_pounce_claw(void)
{
    BEAST(4, 1);
    so.animation_step.fields.event = 2;
    so.y_speed = 0x10000;
    slash_beast_jump(&so);
}
static void sb_pounce_catch_left(void)
{
    BEAST(4, 1);
    so.ext.main_54.grab = 1;
    g_Player.stun_timer = 1;
    so.x_pos.i.hi = 0x60;
    so.y_speed = 0x10000;
    slash_beast_jump(&so);
}
static void sb_pounce_catch_right(void)
{
    BEAST(4, 1);
    so.ext.main_54.grab = 1;
    g_Player.stun_timer = 1;
    so.unk15 = 0x40;
    so.y_speed = 0x10000;
    slash_beast_jump(&so);
}
static void sb_pounce_land_grab(void)
{
    BEAST(4, 1);
    so.ext.main_54.grab = 1;
    so.collision_flags = 8;
    slash_beast_jump(&so);
}
static void sb_pounce_land(void)
{
    BEAST(4, 1);
    so.collision_flags = 8;
    slash_beast_jump(&so);
}
static void sb_start_pattern(void)
{
    BEAST(1, 0);
    slash_beast_start_pattern(&so);
}
static void sb_intro_land_stop(void)
{
    BEAST(9, 4);
    so.x_pos.i.hi = 0x100;
    so.y_pos.i.hi = -0x100;
    so.y_speed = 0x10000;
    slash_beast_intro(&so);
}
static void sb_high_leap_right(void)
{
    BEAST(11, 0);
    so.unk15 = 0x40;
    so.animation_step.fields.event = 1;
    slash_beast_high_leap_jump(&so);
}
static void sb_dash_claw(void)
{
    BEAST(6, 3);
    so.animation_step.fields.event = 2;
    slash_beast_dash(&so);
}
static void sb_dash_turn_last(void)
{
    BEAST(6, 3);
    so.animation_step.fields.event = 1;
    so.unk7E = 1;
    slash_beast_dash(&so);
}
static void sb_dash_turn_left(void)
{
    BEAST(6, 3);
    so.animation_step.fields.event = 1;
    so.unk7E = 2;
    so.unk15 = 0x40;
    so.x_pos.i.hi = 0x80;
    slash_beast_dash(&so);
}
static void sb_dash_turn_right(void)
{
    BEAST(6, 3);
    so.animation_step.fields.event = 1;
    so.unk7E = 2;
    so.x_pos.i.hi = 0x80;
    slash_beast_dash(&so);
}

static void (*const slash_beast_states_cases[])(void) = {
    sb_throw_left,
    sb_throw_right,
    sb_check_miss,
    sb_check_grab_left,
    sb_check_grab_right,
    sb_windup,
    sb_windup_wait,
    sb_pounce_claw,
    sb_pounce_catch_left,
    sb_pounce_catch_right,
    sb_pounce_land_grab,
    sb_pounce_land,
    sb_start_pattern,
    sb_intro_land_stop,
    sb_high_leap_right,
    sb_dash_claw,
    sb_dash_turn_last,
    sb_dash_turn_left,
    sb_dash_turn_right,
};
static const u32 slash_beast_states_expected[] = { 0x104u, 0u, 0x533E80u, 0x33E80u, 0x65800u, 0x380000u, 2u, 3u, 0u, 0u, 0x104u, 0u, 0xFFFCC180u, 0xFFFCC180u, 0x65800u, 0x380000u, 0x4002u, 3u, 0u, 0u, 0x204u, 0u, 0u, 0u, 0u, 0u, 6u, 3u, 0u, 0u, 0x108u, 0x30u, 0xC00000u, 0xFFFA0000u, 0u, 0u, 5u, 0u, 0u, 0u, 0x108u, 0x30u, 0x400000u, 0x60000u, 0u, 0u, 0x4005u, 0u, 0u, 0u, 0x208u, 0u, 0u, 0u, 0u, 0u, 7u, 0u, 0u, 0u, 0x108u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x104u, 0u, 0u, 0u, 0x10000u, 0u, 0u, 3u, 0u, 0u, 0x104u, 0u, 0x600000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0x104u, 0u, 0u, 0u, 0x10000u, 0u, 0x4000u, 0u, 0u, 0u, 8u, 0xAu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x204u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x409u, 0u, 0x1000000u, 0u, 0x10000u, 0x1000000u, 0u, 0u, 0u, 0u, 0x10Bu, 0u, 0x1C000u, 0x1C000u, 0x73800u, 0x380000u, 0x4002u, 0u, 0u, 0u, 0x306u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0u, 0x104u, 0u, 0u, 0u, 0u, 0x380000u, 0x4025u, 0u, 0u, 0u, 0x406u, 0x10000u, 0x600000u, 0u, 0u, 0u, 0x10u, 0u, 0u, 0u, 0x406u, 0x10000u, 0xA00000u, 0u, 0u, 0u, 0x4010u, 0u, 0u, 0u };

static u32 test_slash_beast_states(u32 row)
{
    return state_run(slash_beast_states_cases[row], row, &slash_beast_states_expected[row * 10]);
}

static u8 beast_pattern[2];
static u32 beast_pages[8];
static u32 beast_attrs[0x400];
#define PICK(next, px, seed, hp_) (BEAST(1, 0), so.x_pos.i.hi = 0x100, so.y_pos.i.hi = 0x80, so.hp = hp_, g_Player.x_pos.i.hi = px, beast_pattern[0] = 0, beast_pattern[1] = next, so.ext.main_54.pattern = beast_pattern, cur_random = seed, func_8006C6AC(&so), so.unk7E ^= so.ext.main_54.grab << 8)
static void sbp_far_charge(void)
{
    PICK(0, 0x200, 0, 0x20);
}
static void sbp_near_claw(void) { PICK(1, 0x120, 1, 0x20); }
static void sbp_near_dash(void) { PICK(2, 0x120, 1, 0x20); }
static void sbp_grab(void) { PICK(6, 0x120, 1, 0x20); }
static void sbp_highway_land(void)
{
    u8 stage = engine_obj.stage;
    BEAST(9, 4);
    state_terrain(0x38);
    engine_obj.stage = 0xC;
    so.x_pos.i.hi = 0x40;
    so.y_pos.i.hi = 0x40;
    so.unk7E = 1;
    so.y_speed = -0x40000;
    slash_beast_intro_land(&so);
    engine_obj.stage = stage;
}

static void (*const slash_beast_patterns_cases[])(void) = {
    sbp_far_charge,
    sbp_near_claw,
    sbp_near_dash,
    sbp_grab,
    sbp_highway_land,
};
static const u32 slash_beast_patterns_expected[] = { 2u, 0u, 0x1000000u, 0u, 0u, 0u, 0x4008u, 0x200000u, 0u, 0u, 6u, 0x20024u, 0x1000000u, 0u, 0u, 0u, 0x400Cu, 0x200000u, 0u, 0u, 6u, 0x20024u, 0x1000000u, 0u, 0u, 0u, 0x400Cu, 0x200000u, 0u, 0u, 7u, 0x1000000u, 0x1000000u, 0u, 0u, 0u, 0x4026u, 0x200000u, 0u, 0u, 0x409u, 0x20000u, 0x400000u, 0u, 0xFFFC0000u, 0u, 3u, 0u, 0u, 0u };

static u32 test_slash_beast_patterns(u32 row)
{
    return state_run(slash_beast_patterns_cases[row], row, &slash_beast_patterns_expected[row * 10]);
}

static void beast_fill_words(u32* dest, u32 value, u32 count)
{
    while (count >= 8) {
        dest[0] = dest[1] = dest[2] = dest[3] = dest[4] = dest[5] = dest[6] = dest[7] = value;
        dest += 8;
        count -= 8;
    }
    while (count) {
        *dest++ = value;
        count--;
    }
}
static void beast_same_words(const void* a, const void* b, u32 bytes)
{
    assert(c_test_word_difference((const u32*)a, (const u32*)b, bytes / 4) == 0);
}
extern union AnimationStep* slash_beast_animations[39];
extern struct Unk_unk68 D_801078F8[32], D_80100218, D_8010021C, D_8010023C, double_cyclone_hit_box[1], aiming_laser_charged_box[1];
extern u16 D_801005B8[8], D_801005C8[14];
struct BeastWeapon {
    u8 id, damage, visual, facing;
    s8 x, y, w, h;
    const void* box;
};
static const struct BeastWeapon beast_weapons[6] = {
    { 0, 1, 3, 1, -10, -6, 18, 11, lemon_hit_box },
    { 5, 4, 3, 1, -16, -8, 34, 14, ground_hunter_crawl_box },
    { 14, 5, 3, 1, -24, -24, 48, 48, aiming_laser_charged_box },
    { 24, 1, 7, 0, -23, -43, 31, 31, &zero_saber_hit_boxes[1] },
    { 25, 1, 6, 0, -23, -43, 31, 31, &zero_saber_hit_boxes[1] },
    { 7, 0, 0, 1, -16, -16, 32, 32, double_cyclone_hit_box },
};
static const u8 beast_animation_lengths[39] = { 1, 6, 12, 6, 2, 2, 6, 1, 6, 16, 5, 8, 5, 3, 3, 7, 2, 2, 12, 1, 4, 3, 2, 6, 1, 7, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 6 };
static const u16 beast_tiles[2][14] = {
    { 0x70, 0x72, 0x74, 0x76, 0x65, 0x67, 0x69, 0x6B },
    { 0x388, 0x38D, 0x3AC, 0x3AF, 0x3B2, 0x3B5, 0x3C3, 0x380, 0x383, 0x390, 0x392, 0x394, 0x396, 0x3A0 },
};
struct BeastScene {
    u8 active, flash, hp, weapon, hit, crash, pattern, fight, contact, grab, claw, outside;
};
static const struct BeastScene beast_scenes[] = {
    { 0, 0, 48, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 48, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
    { 1, 0, 48, 0, 0, 2, 1, 0, 0, 0, 0, 1 },
    { 1, 0, 16, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
    { 1, 0, 17, 0, 0, 0, 2, 1, 2, 0, 1, 0 },
    { 1, 0, 32, 0, 0, 0, 0, 1, 3, 0, 0, 0 },
    { 1, 0, 33, 0, 0, 0, 0, 1, 4, 128, 0, 0 },
    { 1, 1, 48, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
    { 1, 2, 48, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
    { 1, 3, 48, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
    { 1, 0, 48, 0, 1, 0, 0, 1, 1, 0, 0, 0 },
    { 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0 },
    { 1, 0, 48, 0, 2, 0, 0, 1, 0, 0, 0, 0 },
    { 1, 0, 48, 5, 1, 0, 0, 1, 0, 0, 0, 0 },
    { 1, 0, 48, 1, 1, 0, 0, 1, 1, 0, 0, 0 },
    { 1, 0, 48, 2, 1, 0, 0, 1, 1, 0, 0, 0 },
    { 1, 0, 48, 1, 1, 0, 0, 1, 1, 1, 0, 0 },
    { 1, 0, 48, 2, 1, 0, 0, 1, 2, 0, 1, 0 },
    { 1, 0, 48, 3, 1, 0, 0, 1, 3, 0, 0, 0 },
    { 1, 0, 48, 4, 1, 0, 0, 1, 4, 128, 0, 0 },
    { 1, 0, 48, 0, 0, 0, 0, 1, 5, 0, 0, 0 },
};
static struct {
    u32 before;
    struct MainObj value;
    u32 after;
} beast_guard;
#define boss beast_guard.value
static struct MainObj beast_want;
static u16 beast_random_want;
static u8 beast_palette_want;
static struct PlayerObj beast_player, beast_entity;
static struct EngineObj beast_engine;
static struct MainBssState beast_main;
static struct BackgroundObj beast_backgrounds[3];
static struct WeaponObj beast_weapon_pool[16];
static struct VisualObj beast_visual_pool[32];
static u32 beast_attrs_want[0x400], beast_animation_words[150], beast_collision_words[64];
static union AnimationStep* beast_animation_pointers[39];
static s32 beast_sprite_archive[3] = { 8, 8, 0x11223344 };
static u8 *beast_saved_attrs, *beast_saved_frames;
static void beast_prepare(u32 scene, u32 facing, u32 layer, u32 rematch, u32 available)
{
    const struct BeastScene* c = &beast_scenes[scene];
    const struct BeastWeapon* w = &beast_weapons[c->weapon];
    struct WeaponObj* weapon = &weapon_objects[7];
    u32 i, n = 0;
    beast_saved_attrs = TEST_BG_TILE_ATTRS;
    beast_saved_frames = TEST_SPRITE_FRAMES;
    TEST_BG_TILE_ATTRS = (u8*)beast_attrs;
    TEST_SPRITE_FRAMES = (u8*)beast_sprite_archive;
    beast_fill_words((u32*)&beast_guard, 0xA5A5A5A5, sizeof(beast_guard) / 4);
    beast_guard.before = 0x12345678;
    beast_guard.after = 0x87654321;
    boss.active = 0x41;
    boss.id = 54;
    boss.state = 1;
    boss.unk5 = 1;
    boss.unk6 = 7;
    boss.on_screen = 1;
    boss.bg_offset = layer == 0 ? -1 : layer - 1;
    boss.unk15 = facing * 0x40;
    boss.x_pos.val = (200 + (layer == 2 ? 1024 : 0) + (c->outside ? 216 : 0)) * 65536 + 0x1234;
    boss.y_pos.val = 120 * 65536 + 0x5678;
    boss.animation_table = (const u8* const*)slash_beast_animations;
    boss.unk17 = c->contact == 3 ? 9 : 0;
    boss.animation_cursor = (const u8*)(slash_beast_animations[boss.unk17] + (c->contact == 3 ? 5 : 0));
    boss.animation_step.packed = c->contact == 3 ? 0x25010301 : 0x00000101;
    assert(*(const u32*)boss.animation_cursor == boss.animation_step.packed);
    boss.attack_box = D_801001F8;
    boss.hurt_box = D_801001FC;
    boss.terrain_box = 0;
    boss.collision_data = c->flash ? D_801060F0 : D_801078F8;
    boss.hp = c->hp;
    boss.invincibility_timer = boss.unk7A = boss.unk62 = 0;
    boss.unk65 = c->hit == 2 ? 9 : 0x55;
    boss.unk63 = 0x22;
    boss.unk42 = 0x9234;
    boss.contact_damage = 9;
    boss.ext.main_54.active = c->active;
    boss.ext.main_54.flash_timer = c->flash;
    boss.ext.main_54.was_hit = 0x5A;
    boss.ext.main_54.crash_timer = c->crash;
    boss.ext.main_54.pattern_set = c->pattern;
    boss.ext.main_54.fight_started = c->fight;
    boss.ext.main_54.grab = c->grab;
    boss.ext.main_54.claw_hitbox = c->claw;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    engine_obj.stage = rematch ? 12 : 8;
    g_Player.hp = c->contact == 5 ? 9 : 24;
    g_Player.unk2 = c->weapon == 3 || c->weapon == 4;
    g_Player.unk54 = g_Player.unk2 ? &D_8011A230[1] : &D_801194F0[1];
    g_Player.unk15 = boss.unk15;
    g_Player.x_pos.val = boss.x_pos.val + (c->contact == 0 ? 512 : c->contact == 1 ? 0
                                                  : c->contact == 2                ? -55
                                                                                   : -25)
            * (facing ? -65536 : 65536);
    g_Player.y_pos.val = boss.y_pos.val - (c->contact == 3 ? 55 : 0) * 65536;
    g_Player.hurt_type = 7;
    g_Player.stun_timer = 9;
    g_Player.hit_facing = 0x33;
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    weapon->active = 0x21;
    weapon->id = w->id;
    weapon->state = 1;
    weapon->unk15 = boss.unk15;
    weapon->bg_offset = boss.bg_offset;
    weapon->unk50 = w->box;
    weapon->unk64 = 9;
    weapon->unk98 = 0x33;
    weapon->x_pos.val = boss.x_pos.val + (-27 - w->x) * (facing ? -65536 : 65536) + (c->hit ? 0 : 512 * 65536);
    weapon->y_pos.val = boss.y_pos.val + (-21 - w->y) * 65536;
    beast_fill_words((u32*)visual_objects, 0xA5A5A5A5, sizeof(visual_objects) / 4);
    for (i = 0; i < 32; i++)
        visual_objects[i].active = 1;
    if (available)
        visual_objects[31].active = 0;
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = i * 1024 * 65536;
        background_objects[i].y_pos.val = 0;
    }
    for (i = 0; i < 0x400; i += 8) {
        u32 value = 0x65430080 + i * 256;
        beast_attrs[i] = beast_attrs_want[i] = value;
        beast_attrs[i + 1] = beast_attrs_want[i + 1] = value + 256;
        beast_attrs[i + 2] = beast_attrs_want[i + 2] = value + 512;
        beast_attrs[i + 3] = beast_attrs_want[i + 3] = value + 768;
        beast_attrs[i + 4] = beast_attrs_want[i + 4] = value + 1024;
        beast_attrs[i + 5] = beast_attrs_want[i + 5] = value + 1280;
        beast_attrs[i + 6] = beast_attrs_want[i + 6] = value + 1536;
        beast_attrs[i + 7] = beast_attrs_want[i + 7] = value + 1792;
    }
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    cur_random = beast_random_want = 0x1234;
    need_palette_load = beast_palette_want = 0x20;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    c_test_copy_words((u32*)&beast_player, (u32*)&g_Player, sizeof(beast_player) / 4);
    c_test_copy_words((u32*)&beast_entity, (u32*)&g_Entity, sizeof(beast_entity) / 4);
    c_test_copy_words((u32*)&beast_engine, (u32*)&engine_obj, sizeof(beast_engine) / 4);
    c_test_copy_words((u32*)&beast_main, (u32*)&main_bss_state, sizeof(beast_main) / 4);
    c_test_copy_words((u32*)beast_backgrounds, (u32*)background_objects, sizeof(beast_backgrounds) / 4);
    c_test_copy_words((u32*)beast_weapon_pool, (u32*)weapon_objects, sizeof(beast_weapon_pool) / 4);
    c_test_copy_words((u32*)beast_visual_pool, (u32*)visual_objects, sizeof(beast_visual_pool) / 4);
    c_test_copy_words((u32*)beast_animation_pointers, (u32*)slash_beast_animations, sizeof(beast_animation_pointers) / 4);
    for (i = 0; i < 39; i++) {
        c_test_copy_words(beast_animation_words + n, (u32*)slash_beast_animations[i], beast_animation_lengths[i]);
        n += beast_animation_lengths[i];
    }
    assert(n == 150);
    c_test_copy_words(beast_collision_words, (u32*)D_801078F8, 32);
    c_test_copy_words(beast_collision_words + 32, (u32*)D_801060F0, 32);
}
static void beast_expect_tiles(u32 rematch)
{
    u32 i;
    for (i = 0; i < (rematch ? 14 : 8); i++)
        beast_attrs_want[beast_tiles[rematch][i]] = (beast_attrs_want[beast_tiles[rematch][i]] & 0xFFFFFF00) | 0x38;
}
static void beast_check(void)
{
    u32 i, n = 0;
    beast_same_words(&boss, &beast_want, sizeof(boss));
    beast_same_words(&g_Player, &beast_player, sizeof(g_Player));
    beast_same_words(&g_Entity, &beast_entity, sizeof(g_Entity));
    beast_same_words(&engine_obj, &beast_engine, sizeof(engine_obj));
    beast_same_words(&main_bss_state, &beast_main, sizeof(main_bss_state));
    beast_same_words(background_objects, beast_backgrounds, sizeof(beast_backgrounds));
    beast_same_words(weapon_objects, beast_weapon_pool, sizeof(beast_weapon_pool));
    beast_same_words(visual_objects, beast_visual_pool, sizeof(beast_visual_pool));
    assert(c_test_word_difference(beast_attrs, beast_attrs_want, sizeof(beast_attrs) / 4) == 0);
    beast_same_words(slash_beast_animations, beast_animation_pointers, sizeof(beast_animation_pointers));
    for (i = 0; i < 39; i++) {
        beast_same_words(slash_beast_animations[i], beast_animation_words + n, beast_animation_lengths[i] * 4);
        n += beast_animation_lengths[i];
    }
    beast_same_words(D_801078F8, beast_collision_words, 128);
    beast_same_words(D_801060F0, beast_collision_words + 32, 128);
    beast_same_words(D_801005B8, beast_tiles[0], 16);
    beast_same_words(D_801005C8, beast_tiles[1], 28);
    assert(D_801001F8[0].packed == 0x2225F1EF && D_801001FC[0].packed == 0x313AEBE5);
    assert(*(u32*)&D_80100218 == 0x1B21EDD6 && *(u32*)&D_8010021C == 0x061AF6BE && *(u32*)&D_8010023C == 0x3031B7D0);
    assert(D_801194F0[1] == 0x2613EFF6 && D_8011A230[1] == 0x2715EFF6);
    for (i = 0; i < 6; i++) {
        assert(D_8013E198[i] == -1);
        beast_same_words(beast_weapons[i].box, &beast_weapons[i].x, 4);
    }
    assert(beast_guard.before == 0x12345678 && beast_guard.after == 0x87654321 && cur_random == beast_random_want && need_palette_load == beast_palette_want);
    assert(TEST_BG_TILE_ATTRS == (u8*)beast_attrs && TEST_SPRITE_FRAMES == (u8*)beast_sprite_archive);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    assert(beast_sprite_archive[0] == 8 && beast_sprite_archive[1] == 8 && beast_sprite_archive[2] == 0x11223344);
    TEST_BG_TILE_ATTRS = beast_saved_attrs;
    TEST_SPRITE_FRAMES = beast_saved_frames;
}
static u32 test_slash_beast_run(u32 row)
{
    u32 scene = row % COUNT(beast_scenes), facing = (row / COUNT(beast_scenes)) % 2, rematch = row / (COUNT(beast_scenes) * 2);
    u32 layer = rematch, available = rematch;
    const struct BeastScene* c = &beast_scenes[scene];
    const struct BeastWeapon* w = &beast_weapons[c->weapon];
    s32 hit = 0, x = 0, y = 0;
    beast_prepare(scene, facing, layer, rematch, available);
    beast_want.unk18 = boss.x_pos;
    beast_want.unk1C = boss.y_pos;
    beast_want.unk5 = 3;
    beast_want.unk6 = 0;
    if (c->crash) {
        beast_want.ext.main_54.crash_timer--;
        if (c->crash == 1)
            beast_expect_tiles(rematch);
    }
    if (!rematch && c->pattern == 1 && c->fight)
        beast_engine.character_state.bytes[1] = 1;
    if (c->active) {
        beast_want.unk42 = 0x1234;
        beast_want.unk65 = c->hit ? 9 : 0;
        beast_want.ext.main_54.was_hit = 0;
        if (c->hit) {
            x = boss.x_pos.i.hi + (-27 + w->w / 2) * (facing ? -1 : 1);
            y = boss.y_pos.i.hi - 21 + w->h / 2;
            ((s16*)&beast_weapon_pool[7].unk80)[0] = x;
            ((s16*)&beast_weapon_pool[7].unk80)[1] = y;
            if (c->hit == 1) {
                beast_want.unk63 = c->flash || c->weapon == 5 ? -1 : 0;
                hit = c->flash || c->weapon == 5 ? 127 : c->hp <= w->damage ? -1
                                                                            : w->id + 1;
                if (hit != 127) {
                    beast_want.hp = c->hp > w->damage ? c->hp - w->damage : 0;
                    beast_want.unk42 = 0x9234;
                }
                if (w->facing)
                    beast_weapon_pool[7].unk98 = hit == 127 ? -1 : 1;
                if (available) {
                    struct VisualObj* v = &beast_visual_pool[31];
                    v->active = 0x21;
                    v->id = 3;
                    v->unk2 = hit == 127 ? 0 : w->visual;
                    v->bg_offset = boss.bg_offset;
                    v->animation_table = D_8011BF40;
                    v->unk40 = 0;
                    v->unk42 = 0x7802;
                    v->unk16 = 0;
                    v->unk3C = (u8*)&beast_sprite_archive[2];
                    v->x_pos.i.hi = x;
                    v->y_pos.i.hi = y;
                    v->unk15 = boss.unk15 ^ 0x40;
                }
            }
        }
        if (!c->flash && hit < 0) {
            beast_want.state = 2;
            beast_want.unk5 = 0;
            beast_player.spike_immune = 1;
            beast_expect_tiles(rematch);
        } else {
            if (c->flash) {
                beast_want.ext.main_54.flash_timer--;
                if (c->flash == 1)
                    beast_want.collision_data = D_801078F8;
                else if (c->flash & 1)
                    beast_want.unk42 |= 0x8000;
            } else if (hit && hit != 127) {
                beast_want.ext.main_54.was_hit = 1;
                beast_want.collision_data = D_801060F0;
                beast_want.unk42 |= 0x8000;
                beast_want.ext.main_54.flash_timer = c->weapon == 3 || c->weapon == 4 ? 4 : 64;
                if ((c->weapon == 1 || c->weapon == 2) && !c->grab && !c->claw) {
                    beast_want.contact_damage = 6;
                    beast_want.unk5 = 10;
                }
            }
            if (beast_want.hp < 17)
                beast_want.ext.main_54.pattern_set = 2;
            else if (beast_want.hp < 33)
                beast_want.ext.main_54.pattern_set = 1;
            if (c->grab & 128)
                beast_want.attack_box = &D_80100218;
            if (c->contact) {
                beast_player.hp = c->contact == 5 ? (s8)0x80 : (s8)((24 - beast_want.contact_damage) | 128);
                beast_player.hurt_type = 2;
                beast_player.stun_timer = 0;
                beast_player.hit_facing = c->contact != 1 && !facing ? 0x40 : 0;
            }
            beast_want.on_screen = !c->outside;
        }
    }
    beast_want.collision_flags = 0;
    ((u8*)&beast_want)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)] = 0;
    if (c->contact == 5)
        beast_expect_tiles(rematch);
    slash_beast_update(&boss);
    beast_check();
    return 1;
}

static u32 test_slash_beast_tile_masks(u32 row)
{
    u32 kind = row % 2, facing = (row / 2) % 2, rematch = row / 4, count = rematch ? 14 : 8, i;
    beast_prepare(0, facing, 0, rematch, 0);
    for (i = 0; i < count; i++)
        if (!kind || (facing ? i < count / 2 : i >= count / 2))
            beast_attrs_want[beast_tiles[rematch][i]] = (beast_attrs_want[beast_tiles[rematch][i]] & 0xFFFFFF00) | (0x38 + kind);
    func_8006E920(&boss, 0x38 + kind);
    beast_check();
    return 1;
}

extern union AnimationStep D_80100230[], D_80100234[], D_80100238[];
extern struct Unk_unk68 D_80100228, D_8010022C, D_80100240, D_80100244, D_80100248;
static const struct {
    const void* pointer;
    u32 word;
} beast_attack_boxes[16] = {
    { &D_80100220, 0x321AE3F1 },
    { &D_80100224, 0x4028DCEA },
    { D_80100230, 0x2244F5C4 },
    { D_80100234, 0x3959E8C2 },
    { D_80100238, 0x1F47D0B1 },
    { &D_80100240, 0x5A69BBB6 },
    { &D_80100228, 0x1B27F3F5 },
    { &D_8010022C, 0x2E39EAEC },
    { &D_80100244, 0x5020BCFA },
    { &D_80100248, 0x6030B9F1 },
    { &D_80100208, 0x391DE2F5 },
    { &D_8010020C, 0x422BE0EF },
    { &D_80100200, 0x2622F0E4 },
    { &D_80100204, 0x3040E8DB },
    { &D_80100210, 0x511FDAF0 },
    { &D_80100214, 0x5D2BD5EA },
};
struct BeastSlash {
    u8 frame, elapsed, event, next;
    s8 attack, hurt;
    u32 before, after;
};
static const struct BeastSlash beast_slashes[8] = {
    { 0, 0, 0, 0, -1, -1, 0x1F010002, 0x1F010001 },
    { 15, 0, 1, 15, -1, -1, 0x2B000101, 0x2B000101 },
    { 3, 1, 2, 4, 2, 3, 0x23010002, 0x24010201 },
    { 4, 0, 3, 5, 4, 5, 0x24010201, 0x25010301 },
    { 1, 1, 4, 2, 6, 7, 0x21010002, 0x22010402 },
    { 5, 0, 5, 6, 8, 9, 0x25010301, 0x26010501 },
    { 11, 1, 6, 12, 10, 11, 0x29010002, 0x2A010602 },
    { 12, 1, 7, 13, 10, 11, 0x2A010602, 0x2C010702 },
};
static struct ShotObj beast_shots[32];
static struct MiscObj beast_misc[64];
static const s8 beast_shot_slots[4] = { -1, 0, 15, 31 };
static void beast_install(u32 animation, u32 frame, u32 word, u32 elapsed)
{
    assert(((u32*)slash_beast_animations[animation])[frame] == word && (word & 255) > elapsed);
    boss.unk17 = animation;
    boss.animation_cursor = (u8*)(slash_beast_animations[animation] + frame);
    boss.animation_step.packed = word - elapsed;
}
static void beast_expect_frame(u32 animation, u32 frame, u32 word, u32 reset)
{
    beast_want.unk17 = animation;
    beast_want.animation_cursor = (u8*)(slash_beast_animations[animation] + frame);
    beast_want.animation_step.packed = word;
    if (reset)
        beast_want.previous_animation_index = 0xFF;
    assert((((u32*)slash_beast_animations[animation])[frame] & 0xFFFFFF00) == (word & 0xFFFFFF00));
}
static void beast_attack_prepare(u32 facing, u32 layer, u32 rematch, u32 shot_mode, u32 misc_count)
{
    u32 i;
    beast_prepare(1, facing, layer, rematch, 0);
    boss.unk40 = 0x4567;
    boss.sprite_frames = (u8*)&beast_sprite_archive[2];
    boss.x_speed = facing ? 0x30000 : -0x30000;
    boss.y_speed = 0x34567;
    boss.x_accel = -0x2000;
    boss.gravity = 0x2000;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < 32; i++) {
        struct ShotObj* s = &shot_objects[i];
        s->active = (s32)i != beast_shot_slots[shot_mode];
        s->id = 7;
        s->state = 7;
        s->unk5 = 6;
        s->unk6 = 5;
        s->x_pos.val = 0x12345678;
        s->y_pos.val = 0x23456789;
        s->x_vel.val = -0x76543;
        s->unk60 = 18;
        s->unk40 = 11;
        s->unk42 = 0x8002;
        s->unk50.data = (u8*)D_801001F8;
        s->unk54 = (u8*)D_801001FC;
        s->unk68 = &D_80100208;
        s->unk84.value = 0x12345678;
        s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = 1;
        s->unk78 = s->unk62 = s->unk63 = s->unk7A = s->unk75 = 1;
        s->animation_table = D_8011BF40;
        s->unk3C = &g_Entity;
    }
    for (i = 0; i < 64; i++) {
        struct MiscObj* m = &misc_objects[i];
        m->active = !(misc_count && (i == 3 || (misc_count == 2 && i == 61)));
        m->id = 7;
        m->state = 9;
        m->unk5 = 7;
        m->unk6 = 6;
        m->unk16 = 0x12;
        m->unk40 = 0x3456;
        m->unk42 = 0xC123;
        m->bg_offset = -1;
        m->animation_step.packed = 0xDEADBEEF;
        m->x_pos.val = 0x12345678;
        m->y_pos.val = 0x23456789;
        m->ext.misc_26.timer = 60;
        m->ext.misc_26.owner = (struct MainObj*)&g_Entity;
        m->animation_table = D_8011BF40;
        m->unk3C = &g_Entity;
    }
    c_test_copy_words((u32*)beast_shots, (u32*)shot_objects, sizeof(beast_shots) / 4);
    c_test_copy_words((u32*)beast_misc, (u32*)misc_objects, sizeof(beast_misc) / 4);
}
static void beast_expect_move(void)
{
    beast_want.x_pos.val += boss.x_speed;
    beast_want.y_pos.val -= boss.y_speed;
    beast_want.x_speed += boss.unk15 ? boss.x_accel : -boss.x_accel;
    beast_want.y_speed -= boss.gravity;
}
static void beast_attack_check(void)
{
    u32 i;
    assert(c_test_word_difference((u32*)shot_objects, (u32*)beast_shots, sizeof(beast_shots) / 4) == 0);
    assert(c_test_word_difference((u32*)misc_objects, (u32*)beast_misc, sizeof(beast_misc) / 4) == 0);
    for (i = 0; i < 16; i++)
        beast_same_words(beast_attack_boxes[i].pointer, &beast_attack_boxes[i].word, 4);
    beast_check();
}
static u32 test_slash_beast_crescent(u32 row)
{
    u32 scene = row % 15, stop = (row / 15) % 2, powered = (row / 30) % 2, facing = (scene + stop) % 2;
    u32 pool = (scene + powered) % 4, layer = 0, rematch = 0;
    u32 phase = scene < 8 ? 1 : scene < 11 ? 0
        : scene < 13                       ? 2
                                           : 3;
    beast_attack_prepare(facing, layer, rematch, pool, 0);
    boss.unk5 = 2;
    boss.unk6 = phase;
    boss.ext.main_54.powered_up = powered;
    if (stop)
        boss.x_speed = facing ? 0x2000 : -0x2000;
    if (scene < 8) {
        const struct BeastSlash* c = &beast_slashes[scene];
        beast_install(9, c->frame, c->before, c->elapsed);
    } else if (scene < 11)
        beast_install(8, scene == 8 ? 0 : scene == 9 ? 2
                                                     : 5,
            scene == 8 ? 0x01010002 : scene == 9 ? 0x01010002
                                                 : 0x20000101,
            scene == 9);
    else if (scene < 13) {
        beast_install(37, 0, 0x05010002, 0);
        boss.collision_flags = scene == 12 ? 8 : 0;
    } else
        beast_install(10, scene == 13 ? 0 : 4, scene == 13 ? 0x01010002 : 0x00000101, 0);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    if (phase == 1) {
        const struct BeastSlash* c = &beast_slashes[scene];
        beast_expect_move();
        beast_expect_frame(9, c->next, c->after, 0);
        if (stop)
            beast_want.x_accel = beast_want.gravity = 0;
        if (c->event == 1) {
            beast_expect_frame(37, 0, 0x05010002, 1);
            beast_want.gravity = 0x3800;
            beast_want.unk6 = 2;
        }
        if (c->attack >= 0) {
            beast_want.attack_box = beast_attack_boxes[c->attack].pointer;
            beast_want.hurt_box = beast_attack_boxes[c->hurt].pointer;
        }
        if ((c->event == 2 || (c->event == 3 && powered)) && pool) {
            struct ShotObj* s = &beast_shots[beast_shot_slots[pool]];
            s->unk50.data = 0;
            s->unk54 = 0;
            s->unk68 = 0;
            s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = 0;
            s->unk78 = s->unk62 = s->unk63 = s->unk7A = s->unk75 = 0;
            s->active = 0x41;
            s->id = 31;
            s->unk2 = c->event == 3;
            s->state = 0;
            s->unk15 = boss.unk15;
            s->bg_offset = boss.bg_offset;
            s->unk40 = boss.unk40;
            s->unk42 = boss.unk42;
            s->animation_table = (u32**)slash_beast_animations;
            s->unk3C = (void*)boss.sprite_frames;
            s->x_pos = beast_want.x_pos;
            s->y_pos = beast_want.y_pos;
            s->unk7C = (struct WeaponObj*)&boss;
        }
    } else if (phase == 0) {
        beast_expect_frame(8, scene == 8 ? 0 : scene == 9 ? 3
                                                          : 5,
            scene == 8 ? 0x01010001 : scene == 9 ? 0x1F010202
                                                 : 0x20000101,
            0);
        if (scene == 9) {
            beast_want.attack_box = &D_80100220;
            beast_want.hurt_box = &D_80100224;
        }
        if (scene == 10) {
            beast_expect_frame(9, 0, 0x1F010002, 1);
            beast_want.x_speed = facing ? 0x30000 : -0x30000;
            beast_want.x_accel = -0x2000;
            beast_want.y_speed = 0x30000;
            beast_want.gravity = 0x2000;
            beast_want.unk6 = 1;
        }
    } else if (phase == 2) {
        beast_expect_move();
        beast_expect_frame(37, 0, 0x05010001, 0);
        if (scene == 12) {
            beast_expect_frame(10, 0, 0x01010002, 1);
            beast_want.hurt_box = D_801001FC;
            beast_want.attack_box = D_801001F8;
            beast_want.y_speed = beast_want.gravity = 0;
            beast_want.unk6 = 3;
        }
    } else {
        beast_expect_frame(10, scene == 13 ? 0 : 4, scene == 13 ? 0x01010001 : 0x00000101, 0);
        if (scene == 14) {
            beast_expect_frame(0, 0, 0x00000101, 1);
            beast_want.unk15 ^= 0x40;
            beast_want.unk5 = 3;
            beast_want.unk6 = 0;
        }
    }
    slash_beast_crescent(&boss);
    beast_attack_check();
    return 1;
}
static u32 test_slash_beast_dash_run(u32 row)
{
    static const s32 deltas[3] = { -1, 0, 1 };
    u32 speed = row % 3, delay = (row / 3) % 2 + 1, powered = (row / 6) % 2, available = row / 12;
    u32 hit = row % 4, facing = (row / 4) % 2, layer = 0, rematch = 0, i;
    s32 threshold = powered ? 0x78000 : 0x60000;
    beast_attack_prepare(facing, layer, rematch, 0, available);
    boss.unk5 = 6;
    boss.unk6 = 2;
    boss.ext.main_54.powered_up = powered;
    boss.ext.main_54.afterimage_timer = delay;
    boss.collision_flags = hit;
    boss.x_speed = (threshold - 0x8000 + deltas[speed]) * (facing ? 1 : -1);
    boss.x_accel = 0x8000;
    beast_install(14, 0, 0x0F010001, 0);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    beast_expect_move();
    beast_want.ext.main_54.afterimage_timer = delay == 1 ? 10 : 1;
    beast_expect_frame(14, 2, 0x11FE0101, 0);
    if (speed != 0)
        beast_want.x_accel = 0;
    for (i = 0; delay == 1 && i < (powered ? 2 : 1) && i < available; i++) {
        struct MiscObj* m = &beast_misc[i ? 61 : 3];
        m->active = 0x41;
        m->id = 26;
        m->unk2 = 1;
        m->state = 0;
        m->unk16 = i ? 0x20 : 0x21;
        m->unk40 = boss.unk40;
        m->unk42 = 0x1234;
        m->animation_table = (u32**)slash_beast_animations;
        m->unk3C = (void*)boss.sprite_frames;
        m->bg_offset = boss.bg_offset;
        m->x_pos = beast_want.x_pos;
        m->y_pos = beast_want.y_pos;
        m->unk15 = boss.unk15;
        m->animation_step.fields.frame_index = i ? 76 : 16;
        m->ext.misc_26.timer = 30;
        m->ext.misc_26.owner = &boss;
    }
    if (hit & (facing ? 1 : 2)) {
        struct BackgroundObj* bg = &beast_backgrounds[0];
        u32 count = rematch ? 14 : 8;
        bg->unk36 = 30;
        bg->unk45 = bg->unk3E.bytes[0] = 8;
        bg->unk3C = bg->unk3A = 2;
        bg->unk34 |= 0x10;
        beast_want.contact_damage = 6;
        beast_want.unk6 = 3;
        beast_want.hurt_box = beast_want.attack_box = 0;
        beast_want.ext.main_54.crash_timer = 30;
        beast_expect_frame(15, 0, 0x12010002, 1);
        for (i = 0; i < count; i++)
            if (facing ? i < count / 2 : i >= count / 2)
                beast_attrs_want[beast_tiles[rematch][i]] = (beast_attrs_want[beast_tiles[rematch][i]] & 0xFFFFFF00) | 0x39;
    }
    slash_beast_dash(&boss);
    beast_attack_check();
    return 1;
}

extern u8 slash_beast_pattern_steps[9][4];
struct BeastRoll {
    u16 seed, state;
    u8 offsets[3];
};
static const struct BeastRoll beast_rolls[16] = {
    { 0x010D, 0x0310, { 0, 8, 16 } },
    { 0x010E, 0x0311, { 0, 8, 16 } },
    { 0x010F, 0x0312, { 0, 8, 16 } },
    { 0x0100, 0x0303, { 0, 8, 16 } },
    { 0x0101, 0x0304, { 0, 8, 16 } },
    { 0x0102, 0x0305, { 0, 8, 16 } },
    { 0x0103, 0x0306, { 0, 8, 16 } },
    { 0x0104, 0x0307, { 4, 8, 20 } },
    { 0x0105, 0x0308, { 4, 8, 20 } },
    { 0x0106, 0x0309, { 4, 12, 20 } },
    { 0x0107, 0x030A, { 4, 12, 24 } },
    { 0x0108, 0x030B, { 4, 12, 24 } },
    { 0x0109, 0x030C, { 4, 12, 24 } },
    { 0x010A, 0x030D, { 4, 12, 24 } },
    { 0x010B, 0x030E, { 4, 12, 24 } },
    { 0x010C, 0x030F, { 4, 12, 24 } },
};
struct BeastDecision {
    u16 seed, state;
    u8 cursor, set, hp, powered;
    u16 distance;
    u8 next, animation, phase, subphase, flags;
    s16 timer, counter;
};
static const struct BeastDecision beast_decisions[] = {
    { 0x0077, 0x0178, 0, 2, 15, 0, 161, 0, 38, 7, 0, 3, -1, -1 },
    { 0x0077, 0x0178, 0, 0, 16, 0, 161, 0, 8, 2, 0, 1, -1, -1 },
    { 0x0077, 0x0178, 0, 0, 48, 0, 160, 1, 8, 2, 0, 1, -1, -1 },
    { 0x1234, 0xA30D, 0, 0, 48, 0, 161, 1, 1, 4, 0, 9, -1, -1 },
    { 0x0077, 0x0178, 0, 0, 48, 0, 111, 1, 8, 2, 0, 1, -1, -1 },
    { 0x1234, 0x366A, 0, 0, 48, 1, 111, 1, 38, 11, 0, 0, -1, -1 },
    { 0x1234, 0x366A, 0, 0, 48, 0, 111, 1, 12, 6, 0, 1, 36, 2 },
    { 0x1234, 0x366A, 0, 0, 48, 0, 112, 1, 1, 4, 0, 9, -1, -1 },
    { 0x1234, 0x366A, 5, 0, 48, 0, 111, 6, 12, 6, 0, 1, 36, 2 },
    { 0x1234, 0x366A, 5, 0, 48, 1, 111, 6, 38, 11, 0, 0, -1, -1 },
    { 0x0077, 0x0178, 5, 0, 48, 1, 111, 6, 8, 2, 0, 1, -1, -1 },
    { 0x0077, 0x0077, 5, 0, 48, 0, 112, 6, 8, 2, 0, 1, -1, -1 },
    { 0x1234, 0x1234, 8, 0, 48, 0, 80, 9, 38, 7, 0, 1, -1, -1 },
    { 0x1234, 0x1234, 9, 0, 48, 0, 80, 10, 12, 6, 0, 1, 36, 2 },
    { 0x1234, 0x1234, 18, 2, 15, 0, 80, 19, 38, 7, 0, 3, -1, -1 },
    { 0x1234, 0x1234, 4, 0, 48, 0, 80, 5, 1, 4, 0, 5, -1, -1 },
    { 0x1234, 0x1234, 2, 0, 48, 0, 80, 3, 255, 3, 0, 0, -1, -1 },
    { 0x0153, 0x0A60, 3, 0, 48, 0, 80, 0, 8, 2, 0, 1, -1, -1 },
    { 0x0105, 0x0911, 3, 0, 48, 0, 80, 4, 11, 3, 1, 1, 60, -1 },
    { 0x0100, 0x090C, 3, 1, 24, 0, 80, 8, 11, 3, 1, 1, 60, -1 },
    { 0x010C, 0x0918, 3, 1, 24, 0, 80, 12, 8, 2, 0, 1, -1, -1 },
    { 0x0100, 0x0303, 3, 2, 15, 0, 80, 16, 20, 5, 0, 1, 90, -1 },
    { 0x0104, 0x0307, 3, 2, 15, 0, 80, 20, 255, 3, 0, 0, -1, -1 },
    { 0x0107, 0x0913, 3, 2, 15, 0, 80, 24, 11, 3, 1, 1, 60, -1 },
    { 0x0077, 0x0178, 255, 0, 48, 0, 80, 0, 8, 2, 0, 1, -1, -1 },
    { 0x1234, 0x366A, 255, 0, 48, 0, 80, 0, 11, 3, 1, 1, 60, -1 },
};
static u8** beast_pattern_tables[3];
static u8* beast_pattern_links[3][4];
static u32 beast_pattern_words[12];
static void beast_pattern_capture(void)
{
    u32 i;
    c_test_copy_words((u32*)beast_pattern_tables, (u32*)slash_beast_patterns, sizeof(beast_pattern_tables) / 4);
    for (i = 0; i < 3; i++)
        c_test_copy_words((u32*)beast_pattern_links[i], (u32*)slash_beast_patterns[i], sizeof(beast_pattern_links[i]) / 4);
    c_test_copy_words(beast_pattern_words, (u32*)slash_beast_pattern_steps, 9);
    c_test_copy_words(beast_pattern_words + 9, (u32*)slash_beast_pattern_weights, 3);
}
static void beast_pattern_check(void)
{
    u32 i;
    beast_same_words(slash_beast_patterns, beast_pattern_tables, sizeof(beast_pattern_tables));
    for (i = 0; i < 3; i++)
        beast_same_words(slash_beast_patterns[i], beast_pattern_links[i], sizeof(beast_pattern_links[i]));
    beast_same_words(slash_beast_pattern_steps, beast_pattern_words, 36);
    beast_same_words(slash_beast_pattern_weights, beast_pattern_words + 9, 12);
    assert(D_8010024C.unk0 == 0 && D_8010024C.unk1 == 0 && D_8010024C.unk2 == 28 && D_8010024C.unk3 == 26);
    beast_attack_check();
}
static u32 test_slash_beast_pick_patterns(u32 row)
{
    const struct BeastRoll* c = &beast_rolls[row % 16];
    u32 set = (row / 16) % 3, facing = (row / 48) % 2, layer = 0, rematch = 0;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.ext.main_54.pattern_set = set;
    boss.ext.main_54.pattern = slash_beast_pattern_steps[0];
    cur_random = c->seed;
    beast_random_want = c->state;
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    beast_pattern_capture();
    beast_want.ext.main_54.pattern = &slash_beast_pattern_steps[c->offsets[set] / 4][c->offsets[set] % 4];
    slash_beast_pick_pattern(&boss);
    beast_pattern_check();
    return 1;
}
static u32 test_slash_beast_decisions(u32 row)
{
    const struct BeastDecision* c = &beast_decisions[row % COUNT(beast_decisions)];
    u32 side = (row / COUNT(beast_decisions)) % 2;
    u32 facing = (row / (COUNT(beast_decisions) * 2)) % 2, layer = 0, rematch = 0;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 3;
    boss.unk6 = 0;
    boss.unk7C = 77;
    boss.unk7E = 55;
    boss.hp = c->hp;
    boss.ext.main_54.high_jump = facing;
    boss.ext.main_54.powered_up = c->powered;
    boss.ext.main_54.pattern_set = c->set;
    boss.ext.main_54.pattern = c->cursor == 255 ? (u8*)slash_beast_pattern_steps - 1 : &slash_beast_pattern_steps[c->cursor / 4][c->cursor % 4];
    g_Player.x_pos.val = boss.x_pos.val + c->distance * (side ? 65536 : -65536);
    c_test_copy_words((u32*)&beast_player, (u32*)&g_Player, sizeof(beast_player) / 4);
    cur_random = c->seed;
    beast_random_want = c->state;
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    beast_pattern_capture();
    beast_want.ext.main_54.pattern = &slash_beast_pattern_steps[c->next / 4][c->next % 4];
    beast_want.unk5 = c->phase;
    beast_want.unk6 = c->subphase;
    if (c->animation != 255)
        beast_expect_frame(c->animation, 0, c->animation == 8 ? 0x01010002 : c->animation == 38 ? 0x00010003
                : c->animation == 20                                                            ? 0x30010001
                                                                                                : 0x00010002,
            1);
    if (c->flags & 1)
        beast_want.unk15 = side ? 0x40 : 0;
    if (c->flags & 2)
        beast_want.ext.main_54.grab = 1;
    if (c->flags & 4)
        beast_want.ext.main_54.high_jump = 1;
    if (c->flags & 8)
        beast_want.ext.main_54.high_jump = 0;
    if (c->timer >= 0)
        beast_want.unk7C = c->timer;
    if (c->counter >= 0)
        beast_want.unk7E = c->counter;
    slash_beast_decide(&boss);
    beast_pattern_check();
    return 1;
}

static u32 test_slash_beast_dash_transitions(u32 row)
{
    u32 scene = row % 10, facing = (row / 10) % 2, layer = 0, rematch = 0;
    u32 phase = scene < 2 ? 0 : scene < 4 ? 1
        : scene < 8                       ? 3
                                          : 4;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 6;
    boss.unk6 = phase;
    boss.unk7C = scene == 0 ? 2 : 1;
    boss.unk7E = scene == 6 ? 2 : 1;
    boss.contact_damage = 6;
    boss.ext.main_54.claw_hitbox = scene == 5;
    if (phase == 4)
        boss.x_speed = facing ? -0x30000 : 0x30000;
    if (phase == 0)
        beast_install(12, 0, 0x00010002, 0);
    else if (phase == 1)
        beast_install(13, scene == 2 ? 0 : 1, scene == 2 ? 0x02010001 : 0x0E010001, 0);
    else if (phase == 3)
        beast_install(15, scene < 6 ? 0 : 5, scene < 6 ? 0x12010002 : 0x13010001, scene == 5);
    else
        beast_install(16, scene == 8 ? 0 : 1, scene == 8 ? 0x16010001 : 0x0A000101, 0);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    if (phase == 0) {
        beast_want.unk7C--;
        beast_expect_frame(12, 0, 0x00010001, 0);
        if (scene == 1) {
            beast_expect_frame(13, 0, 0x02010001, 1);
            beast_want.unk6 = 1;
        }
    } else if (phase == 1) {
        beast_expect_frame(13, scene == 2 ? 1 : 2, scene == 2 ? 0x0E010001 : 0x09000101, 0);
        if (scene == 3) {
            beast_expect_frame(14, 0, 0x0F010001, 1);
            beast_want.contact_damage = 9;
            beast_want.x_speed = facing ? 0x10000 : -0x10000;
            beast_want.x_accel = 0x8000;
            beast_want.ext.main_54.claw_hitbox = beast_want.ext.main_54.afterimage_timer = 1;
            beast_want.unk6 = 2;
        }
    } else if (phase == 3) {
        beast_expect_frame(15, scene == 4 ? 0 : scene == 5 ? 1
                                                           : 6,
            scene == 4 ? 0x12010001 : scene == 5 ? 0x13010202
                                                 : 0x13000101,
            0);
        if (scene == 5) {
            beast_want.hurt_box = D_801001FC;
            beast_want.attack_box = D_801001F8;
            beast_want.ext.main_54.claw_hitbox = 0;
        }
        if (scene >= 6) {
            beast_want.unk15 ^= 0x40;
            beast_want.unk7E--;
            if (scene == 7) {
                beast_expect_frame(37, 0, 0x05010002, 1);
                beast_want.gravity = 0x3800;
                beast_want.unk5 = 4;
                beast_want.unk6 = 1;
            } else {
                beast_expect_frame(16, 0, 0x16010001, 1);
                beast_want.x_pos.i.hi += facing ? -32 : 32;
                beast_want.unk6 = 4;
            }
        }
    } else {
        beast_expect_frame(14, 0, 0x0F010001, 1);
        beast_want.contact_damage = 9;
        beast_want.ext.main_54.claw_hitbox = 1;
        beast_want.x_speed = -boss.x_speed;
        beast_want.unk6 = 2;
    }
    slash_beast_dash(&boss);
    beast_attack_check();
    return 1;
}
static u32 test_slash_beast_jump_edges(u32 row)
{
    u32 scene = row % 5, high = (row / 5) % 2, facing = (row / 10) % 2, layer = 0, rematch = 0;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 4;
    boss.unk6 = scene < 3 ? 0 : 2;
    boss.ext.main_54.high_jump = high;
    if (scene < 3)
        beast_install(1, scene == 0 ? 0 : scene == 1 ? 4
                                                     : 5,
            scene == 0 ? 0x00010002 : scene == 1 ? 0x00010001
                                                 : 0x00000101,
            0);
    else
        beast_install(3, scene == 3 ? 0 : 5, scene == 3 ? 0x02010002 : 0x00000101, 0);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    if (scene < 2)
        beast_expect_frame(1, scene == 0 ? 0 : 5, scene == 0 ? 0x00010001 : 0x00000101, 0);
    else if (scene == 2) {
        beast_expect_frame(2, 0, 0x03010002, 1);
        beast_want.x_accel = 0;
        beast_want.gravity = 0x3800;
        beast_want.hurt_box = &D_8010020C;
        beast_want.attack_box = &D_80100208;
        beast_want.x_speed = (high ? 0x36000 : 0x24000) * (facing ? 1 : -1);
        beast_want.y_speed = high ? 0x7C000 : 0x5C000;
        beast_want.x_pos.val += beast_want.x_speed;
        beast_want.y_pos.val -= beast_want.y_speed;
        beast_want.y_speed -= 0x3800;
        beast_want.unk6 = 1;
    } else {
        beast_expect_frame(3, scene == 3 ? 0 : 5, scene == 3 ? 0x02010001 : 0x00000101, 0);
        if (scene == 4) {
            beast_expect_frame(0, 0, 0x00000101, 1);
            beast_want.unk15 ^= 0x40;
            beast_want.unk5 = 3;
            beast_want.unk6 = 0;
        }
    }
    slash_beast_jump(&boss);
    beast_attack_check();
    return 1;
}
static u32 test_slash_beast_crouch(u32 row)
{
    u32 event = row % 2, timer = (row / 2) % 2 + 1, facing = (row / 4) % 2, layer = 0, rematch = 0;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 3;
    boss.unk6 = 1;
    boss.unk7C = timer;
    beast_install(11, event ? 1 : 0, event ? 0x1A010002 : 0x00010002, event);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    beast_expect_frame(11, event ? 2 : 0, event ? 0x1B010201 : 0x00010001, 0);
    beast_want.unk7C--;
    if (event) {
        beast_want.hurt_box = &D_80100204;
        beast_want.attack_box = &D_80100200;
    }
    if (timer == 1) {
        beast_want.hurt_box = D_801001FC;
        beast_want.attack_box = D_801001F8;
        beast_want.unk6 = 0;
    }
    slash_beast_decide(&boss);
    beast_attack_check();
    return 1;
}

extern char D_801005B4[];
static const u8 beast_debris_slots[6] = { 3, 17, 31, 47, 61, 63 };
static const u8 beast_debris_random[6][3] = { { 106, 13, 246 }, { 179, 236, 153 }, { 161, 186, 7 }, { 238, 165, 203 }, { 63, 155, 176 }, { 241, 182, 7 } };
static const u16 beast_debris_states[7] = { 4660, 59894, 44441, 19719, 9931, 5552, 20743 };
static u32 test_slash_beast_stagger_start(u32 row)
{
    static const u8 counts[4] = { 0, 1, 3, 6 };
    u32 available = counts[row % 4], hits = (row / 4) % 2 + 1, side = (row / 8) % 3, facing = (row / 24) % 2, layer = 0, rematch = 0, i;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 10;
    boss.unk6 = 0;
    boss.ext.main_54.power_hits = hits;
    boss.ext.main_54.powered_up = 1;
    g_Player.x_pos.val = boss.x_pos.val + ((s32)side - 1) * 100 * 65536 + 0x111;
    c_test_copy_words((u32*)&beast_player, (u32*)&g_Player, sizeof(beast_player) / 4);
    for (i = 0; i < available; i++)
        misc_objects[beast_debris_slots[i]].active = beast_misc[beast_debris_slots[i]].active = 0;
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    beast_want.ext.main_54.power_hits--;
    for (i = 0; hits == 1 && i < available; i++) {
        struct MiscObj* m = &beast_misc[beast_debris_slots[i]];
        const u8* r = beast_debris_random[i];
        m->active = 0x41;
        m->id = 3;
        m->unk2 = m->state = m->unk5 = m->unk6 = 0;
        m->unk15 = r[0] & 0x40;
        m->x_pos.val = boss.x_pos.val + ((i < 3 ? 27 : 29) * (facing ? -1 : 1) + (r[1] & 3)) * 65536;
        m->y_pos.val = boss.y_pos.val + ((i < 3 ? -4 : 12) + (r[2] & 3)) * 65536;
        m->ext.misc_2.unk58 = 34 + i % 3;
        m->ext.misc_2.owner = &boss;
    }
    if (hits == 1) {
        beast_want.ext.main_54.powered_up = 0;
        beast_random_want = beast_debris_states[available];
    }
    beast_expect_frame(17, 0, 0x33010002, 1);
    beast_want.unk15 = side == 2 ? 0 : 0x40;
    beast_want.x_speed = side == 2 ? -65536 : 65536;
    beast_want.y_speed = 0x40000;
    beast_want.x_accel = 0;
    beast_want.gravity = 0x8000;
    beast_want.x_pos.val += beast_want.x_speed;
    beast_want.y_pos.val -= 0x40000;
    beast_want.unk6 = 1;
    slash_beast_stagger(&boss);
    assert(*(u32*)D_801005B4 == 0x00242322);
    beast_attack_check();
    return 1;
}
static u32 test_slash_beast_air_recovery(u32 row)
{
    u32 scene = row % 13, side = (row / 13) % 3, facing = (row / 39) % 2, layer = 0, rematch = 0;
    u32 phase = scene < 2 ? 1 : scene < 4 ? 2
        : scene < 6                       ? 0
        : scene < 9                       ? 1
                                          : 3;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = scene < 4 ? 10 : 11;
    boss.unk6 = phase;
    boss.contact_damage = 7;
    g_Player.x_pos.val = boss.x_pos.val + ((s32)side - 1) * 100 * 65536 + 0x111;
    c_test_copy_words((u32*)&beast_player, (u32*)&g_Player, sizeof(beast_player) / 4);
    boss.collision_flags = scene == 1 || scene == 10 || scene == 12 ? 8 : 0;
    if (scene < 2)
        beast_install(17, 0, 0x33010002, 0);
    else if (scene < 4)
        beast_install(18, scene == 2 ? 0 : 11, scene == 2 ? 0x35010002 : 0x00000101, 0);
    else if (scene < 6)
        beast_install(38, scene == 4 ? 0 : 5, scene == 4 ? 0x00010003 : 0x00000101, 0);
    else if (scene < 9) {
        beast_install(2, 0, 0x03010002, 0);
        boss.gravity = 0x3800;
        boss.y_speed = 0x3800 + (s32)scene - 7;
    } else
        beast_install(3, scene < 11 ? 0 : 5, scene < 11 ? 0x02010002 : 0x00000101, 0);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    if (scene < 2) {
        beast_expect_move();
        beast_expect_frame(17, 0, 0x33010001, 0);
        if (scene == 1) {
            beast_want.x_speed = beast_want.y_speed = beast_want.gravity = 0;
            beast_expect_frame(18, 0, 0x35010002, 1);
            beast_want.unk6 = 2;
        }
    } else if (scene < 4) {
        beast_expect_frame(18, scene == 2 ? 0 : 11, scene == 2 ? 0x35010001 : 0x00000101, 0);
        if (scene == 3) {
            beast_expect_frame(12, 0, 0x00010002, 1);
            beast_want.unk15 = side == 0 ? 0 : 0x40;
            beast_want.unk7C = 20;
            beast_want.unk7E = beast_want.ext.main_54.claw_hitbox = 1;
            beast_want.unk5 = 6;
            beast_want.unk6 = 0;
        }
    } else if (scene < 6) {
        beast_expect_frame(38, scene == 4 ? 0 : 5, scene == 4 ? 0x00010002 : 0x00000101, 0);
        if (scene == 5) {
            beast_want.x_speed = facing ? 0x1C000 : -0x1C000;
            beast_want.x_accel = 0;
            beast_want.y_speed = 0x73800;
            beast_want.gravity = 0x3800;
            beast_want.x_pos.val += beast_want.x_speed;
            beast_want.y_pos.val -= 0x77000;
            beast_expect_frame(2, 0, 0x03010002, 1);
            beast_want.unk6 = 1;
        }
    } else if (scene < 9) {
        beast_expect_move();
        beast_expect_frame(2, 0, 0x03010001, 0);
        if (scene == 7) {
            beast_want.gravity = 0x20000;
            beast_want.x_speed = 0;
            beast_want.unk6 = 2;
            beast_want.contact_damage = 7;
            beast_want.attack_box = &D_80100210;
            beast_want.hurt_box = &D_80100214;
            beast_expect_frame(23, 0, 0x05010002, 1);
        }
    } else {
        beast_expect_move();
        beast_expect_frame(3, scene < 11 ? 0 : 5, scene < 11 ? 0x02010001 : 0x00000101, 0);
        if (scene == 10 || scene == 12) {
            beast_want.contact_damage = 5;
            beast_want.y_speed = beast_want.gravity = 0;
        }
        if (scene >= 11) {
            beast_want.attack_box = D_801001F8;
            beast_want.hurt_box = D_801001FC;
            beast_expect_frame(0, 0, 0x00000101, 1);
            beast_want.unk15 = side == 0 || (side == 1 && facing) ? 0 : 0x40;
            beast_want.unk5 = 3;
            beast_want.unk6 = 0;
        }
    }
    if (scene < 4)
        slash_beast_stagger(&boss);
    else
        slash_beast_high_leap(&boss);
    beast_attack_check();
    return 1;
}

extern s32 D_80139538, D_80139540, D_80139544;
extern s16 D_80139560;
extern u16 D_800F188C[170];
extern const u16* D_800F19E0;
extern u8 alternate_stage_music[32];
static u16 beast_cd_control(void)
{
#ifdef MMX4_PC
    return Psyz_SpuRead(0x1AA);
#else
    return *(volatile u16*)0x1F801DAA;
#endif
}
extern const u16* D_800F19E4;
struct BeastMusic {
    u8 archive, channel, volume;
    u32 first, end, location, size, metadata;
};
static const struct BeastMusic beast_music[6] = {
    { 149, 7, 112, 0x246C9, 0x2A3F1, 0x27181133, 0x039D9E00, 0x01640001 },
    { 150, 7, 117, 0x2AC39, 0x2F4A9, 0x27365738, 0x03418300, 0x01640001 },
    { 150, 5, 127, 0x2AC37, 0x2FAF7, 0x27345738, 0x03418300, 0x01640001 },
    { 150, 3, 127, 0x2AC35, 0x30045, 0x27325738, 0x03418300, 0x01640001 },
    { 149, 2, 127, 0x246C4, 0x2A96C, 0x27131133, 0x039D9E00, 0x01640001 },
    { 149, 1, 117, 0x246C3, 0x2AC33, 0x27121133, 0x039D9E00, 0x01640001 },
};
static struct Unk5 beast_music_archives[2];
static u32 beast_music_durations[85], beast_stage_tracks[8];
static u16 beast_music_control;
static void beast_music_prepare(u32 mono, u32 playing)
{
    D_80173C84 = playing;
    D_80171EA9 = mono;
    D_80139538 = 123;
    D_80137CC0 = 3;
    D_80139540 = 44;
    D_80139544 = 99;
    D_80139560 = XA_ARCHIVE_VOICE1;
    D_80139568 = 5;
    D_80139530 = 6;
    D_80141BD4 = 4;
    D_80175EE8[0] = 0x35353535;
    D_80175EE8[1] = 0x24681357;
    D_80139514 = 0x27272727;
    D_80139524 = D_80139528 = 85;
    memset(&D_80139520, 85, sizeof(D_80139520));
    SsSetSerialAttr(0, 0, 0);
    beast_music_control = beast_cd_control();
    c_test_copy_words((u32*)beast_music_archives, (u32*)&D_800F0E18[XA_ARCHIVE_BGM1], sizeof(beast_music_archives) / 4);
    c_test_copy_words(beast_music_durations, (u32*)D_800F188C, 85);
    c_test_copy_words(beast_stage_tracks, (u32*)alternate_stage_music, 8);
}
static void beast_music_check(u32 started, u32 music, u32 mono, u32 playing)
{
    const struct BeastMusic* m = &beast_music[music];
    struct Unk5* archive = &D_800F0E18[m->archive];
    u32 i;
    assert(D_80139538 == (started ? m->size : 123) && D_80137CC0 == (started ? m->metadata : 3));
    assert(D_80139540 == (started ? m->first : 44) && D_80139544 == (started ? m->end : 99) && (u32)D_80139514 == (started ? m->location : 0x27272727u));
    assert(D_80139560 == (started ? m->archive : XA_ARCHIVE_VOICE1) && D_80139568 == (started ? 0 : 5) && D_80139530 == (started ? 7 : 6));
    assert(D_80141BD4 == (started ? 2 : 4) && D_80173C84 == (started ? 1 : playing) && D_80171EA9 == mono);
    assert((u32)D_80175EE8[0] == (started ? 0x35350001u | m->channel * 256 : 0x35353535u) && D_80175EE8[1] == 0x24681357);
    assert(D_80139524 == (started ? m->volume : 85) && D_80139528 == D_80139524 && beast_cd_control() == (beast_music_control | started));
    for (i = 0; i < 4; i++)
        assert(((u8*)&D_80139520)[i] == (started ? (mono ? (i & 1 ? 0 : m->volume) : m->volume / 2) : 85));
    beast_same_words(&D_800F0E18[XA_ARCHIVE_BGM1], beast_music_archives, sizeof(beast_music_archives));
    beast_same_words(D_800F188C, beast_music_durations, sizeof(beast_music_durations));
    beast_same_words(alternate_stage_music, beast_stage_tracks, sizeof(beast_stage_tracks));
    assert(archive->unk0 == m->first - m->channel && archive->unk4 == m->size && archive->unk8 == m->metadata && D_800F19E0 == D_800F188C && D_800F19E4 == D_800F188C + 16 && D_800F188C[14] == 0x8000 && D_800F188C[15] == 0xBA5);
    assert(alternate_stage_music[16] == 7 && alternate_stage_music[17] == 112);
}
static const struct {
    u8 stage, substage, character, final, music;
} beast_music_scenes[9] = {
    { 8, 0, 0, 0, 0 },
    { 11, 0, 0, 0, 1 },
    { 11, 0, 1, 1, 2 },
    { 11, 1, 0, 0, 3 },
    { 11, 1, 1, 1, 3 },
    { 12, 0, 0, 0, 0 },
    { 12, 0, 1, 1, 0 },
    { 12, 1, 0, 0, 4 },
    { 12, 1, 1, 1, 5 },
};
static u32 test_boss_music_selection(u32 row)
{
    u32 scene = row % 9, mono = (row / 9) % 2, playing = row / 18;
    beast_attack_prepare(0, 0, 0, 0, 0);
    engine_obj.stage = beast_music_scenes[scene].stage;
    engine_obj.substage = beast_music_scenes[scene].substage;
    engine_obj.cur_character = beast_music_scenes[scene].character;
    D_80171EA8 = beast_music_scenes[scene].final;
    c_test_copy_words((u32*)&beast_engine, (u32*)&engine_obj, sizeof(beast_engine) / 4);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(boss) / 4);
    beast_music_prepare(mono, playing);
    func_8001653C();
    beast_music_check(1, beast_music_scenes[scene].music, mono, playing);
    assert(D_80171EA8 == beast_music_scenes[scene].final);
    beast_attack_check();
    return 1;
}
static const struct {
    u8 timer, playing, next, start;
} beast_music_delays[5] = { { 0, 0, 0, 0 }, { 1, 0, 0, 1 }, { 2, 0, 1, 0 }, { 2, 1, 2, 0 }, { 0, 1, 0, 0 } };
static u32 test_slash_beast_fill_health(u32 row)
{
    static const u8 phases[][5] = { { 0, 1, 0, 0, 0 }, { 0, 1, 1, 0, 0 }, { 1, 1, 0, 1, 0 }, { 0, 2, 0, 0, 1 } };
    const u8* phase = phases[row / 5];
    u32 delay = row % 5, full = phase[0], timer = phase[1], scroll = phase[2], facing = (delay + full) % 2;
    u32 layer = 0, rematch = phase[3], mono = phase[4], roll = (timer + scroll) % 2, started = beast_music_delays[delay].start, fills = beast_music_delays[delay].next == 0;
    const struct BeastRoll* r = &beast_rolls[roll ? 7 : 0];
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 9;
    boss.unk6 = 7;
    boss.hp = full ? 47 : 46;
    boss.unk7E = timer;
    beast_install(25, 0, 0x00010002, 0);
    boss.ext.main_54.pattern_set = 2;
    boss.ext.main_54.fight_started = 0;
    boss.ext.main_54.pattern = slash_beast_pattern_steps[8];
    background_objects[0].unk26 = 0x24B0 + scroll;
    engine_obj.unk36.value = beast_music_delays[delay].timer;
    engine_obj.gameplay_locked = 1;
    g_Player.script_state = 1;
    g_Player.script_action = 0x14;
    g_Player.script_facing = 0x40;
    g_Player.spike_immune = 1;
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    c_test_copy_words((u32*)&beast_player, (u32*)&g_Player, sizeof(beast_player) / 4);
    c_test_copy_words((u32*)&beast_engine, (u32*)&engine_obj, sizeof(beast_engine) / 4);
    c_test_copy_words((u32*)&beast_backgrounds[0], (u32*)&background_objects[0], sizeof(beast_backgrounds[0]) / 4);
    beast_pattern_capture();
    beast_music_prepare(mono, beast_music_delays[delay].playing);
    cur_random = beast_random_want = r->seed;
    beast_engine.unk36.value = beast_music_delays[delay].next;
    if (fills) {
        if (!rematch && scroll)
            beast_backgrounds[0].unk26--;
        beast_want.unk7E = timer == 1 ? 3 : 1;
        beast_want.hp++;
        if (full) {
            beast_want.ext.main_54.pattern_set = 0;
            beast_want.ext.main_54.fight_started = 1;
            beast_want.ext.main_54.pattern = (u8*)slash_beast_pattern_steps + r->offsets[0] - 1;
            beast_random_want = r->state;
            beast_want.unk5 = 3;
            beast_want.unk6 = 0;
            beast_player.script_state = beast_player.spike_immune = beast_engine.gameplay_locked = 0;
        }
    }
    slash_beast_intro(&boss);
    beast_pattern_check();
    beast_music_check(started, 0, mono, beast_music_delays[delay].playing);
    return 1;
}
static u32 test_slash_beast_intro_dialogue(u32 row)
{
    u32 waiting = row % 2, facing = (row / 2) % 2, layer = 0, rematch = row / 4;
    struct AbcObj abc;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 9;
    boss.unk6 = 6;
    boss.unk7E = 9;
    beast_install(24, 0, 0x19000101, 0);
    memset(&abc_object, 0x5A, sizeof(abc_object));
    abc_object.unkC = waiting ? 0x80 : 0;
    abc = abc_object;
    engine_obj.unk36.value = 0x34;
    c_test_copy_words((u32*)&beast_engine, (u32*)&engine_obj, sizeof(beast_engine) / 4);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    if (!waiting) {
        beast_expect_frame(25, 0, 0x00010002, 1);
        beast_want.unk7E = 3;
        beast_want.unk6 = 7;
        beast_engine.unk36.value = 60;
    }
    slash_beast_intro(&boss);
    beast_same_words(&abc_object, &abc, sizeof(abc));
    beast_attack_check();
    return 1;
}
static u32 test_slash_beast_intro_leap(u32 row)
{
    u32 timer = row % 2 + 1, outside = (row / 2) % 2, layer = 0;
    beast_attack_prepare(1, layer, 0, 0, 0);
    boss.unk5 = 9;
    boss.unk6 = 3;
    boss.unk7C = timer;
    boss.unk7E = 0;
    boss.x_speed = 65536;
    boss.y_speed = boss.x_accel = boss.gravity = 0;
    boss.x_pos.i.hi += outside * 512;
    beast_install(21, 0, 0x2D010001, 0);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    beast_want.unk7C--;
    beast_want.on_screen = !outside;
    if (timer == 1) {
        beast_backgrounds[0].unk26 = 0x24C0;
        beast_backgrounds[0].unk24 = 0x24D0;
        beast_backgrounds[0].unk2A = beast_backgrounds[0].unk28 = 0xD0;
        beast_want.gravity = 0x2000;
        beast_want.y_speed = 0x78000;
        beast_want.x_speed = 0x1E000;
        beast_want.unk6 = 4;
        beast_expect_frame(22, 0, 0x03010001, 1);
    } else
        beast_expect_frame(21, 1, 0x2E010001, 0);
    beast_want.x_pos.val += beast_want.x_speed;
    beast_want.y_pos.val -= beast_want.y_speed;
    slash_beast_intro(&boss);
    beast_attack_check();
    return 1;
}
static union {
    u32 align;
    u8 bytes[160];
} beast_probe_map, beast_probe_map_want;
static union {
    u32 align;
    u16 cells[2][16][16];
} beast_probe_tiles, beast_probe_tiles_want;
static u32 test_slash_beast_high_leap_landing(u32 row)
{
    u32 attribute = row % 3 + 0x37, facing = (row / 3) % 2, layer = 0, rematch = row / 6;
    u8 *saved_map = SP_BG_TILEMAP, *saved_pixels = TEST_BG_TILE_PIXELS;
    u32 width = layout_width, height = layout_height, size = layout_size;
    beast_attack_prepare(facing, layer + 1, rematch, 0, 0);
    boss.unk5 = 11;
    boss.unk6 = 2;
    boss.terrain_box = &D_8010024C;
    boss.contact_damage = 7;
    boss.x_pos.i.hi = 255 + facing + layer * 1024;
    boss.y_pos.i.hi = 117;
    boss.x_speed = boss.x_accel = 0;
    boss.y_speed = -0x20000;
    boss.gravity = 0x20000;
    beast_install(23, 0, 0x05010002, 0);
    c_test_zero_words((u32*)&beast_probe_map, sizeof(beast_probe_map) / 4);
    c_test_zero_words((u32*)&beast_probe_tiles, sizeof(beast_probe_tiles) / 4);
    beast_probe_map.bytes[layer * 8 + layer * 4 + facing] = 1;
    beast_probe_tiles.cells[1][10][facing ? 0 : 15] = 1;
    c_test_copy_words((u32*)&beast_probe_map_want, (u32*)&beast_probe_map, sizeof(beast_probe_map) / 4);
    c_test_copy_words((u32*)&beast_probe_tiles_want, (u32*)&beast_probe_tiles, sizeof(beast_probe_tiles) / 4);
    SP_BG_TILEMAP = beast_probe_map.bytes;
    TEST_BG_TILE_PIXELS = (u8*)beast_probe_tiles.cells;
    layout_width = layout_size = 8;
    layout_height = 1;
    beast_attrs[1] = beast_attrs_want[1] = (beast_attrs[1] & 0xFFFFFF00) | attribute;
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    beast_expect_move();
    beast_expect_frame(23, 0, 0x05010001, 0);
    if (attribute == 0x38) {
        struct BackgroundObj* bg = &beast_backgrounds[0];
        bg->unk37 = 16;
        bg->unk46 = bg->unk3E.bytes[1] = 4;
        bg->unk3D = bg->unk3B = 2;
        bg->unk34 |= 1;
        beast_expect_frame(3, 0, 0x02010002, 1);
        beast_want.unk6 = 3;
    }
    slash_beast_high_leap(&boss);
    assert(c_test_word_difference((u32*)&beast_probe_map, (u32*)&beast_probe_map_want, sizeof(beast_probe_map) / 4) == 0);
    assert(c_test_word_difference((u32*)&beast_probe_tiles, (u32*)&beast_probe_tiles_want, sizeof(beast_probe_tiles) / 4) == 0);
    assert(SP_BG_TILEMAP == beast_probe_map.bytes && TEST_BG_TILE_PIXELS == (u8*)beast_probe_tiles.cells && layout_width == 8 && layout_size == 8 && layout_height == 1 && *(u32*)&D_8010024C == 0x1A1C0000);
    beast_attack_check();
    SP_BG_TILEMAP = saved_map;
    TEST_BG_TILE_PIXELS = saved_pixels;
    layout_width = width;
    layout_height = height;
    layout_size = size;
    return 1;
}

extern struct TileEffectRecord** tile_effect_tables[26];
extern struct TileEffectRecord* D_80119090[14];
extern struct TileEffectRecord D_80116F70[6];
extern u16 D_80114C14[4], D_80114C1C[4], D_80114C24[4];
extern u8 D_801005B0[4];
static struct TileEffectRecord** beast_effect_tables[26];
static struct TileEffectRecord* beast_effect_links[14];
static struct TileEffectRecord beast_effect_records[6];
static union {
    u32 align;
    u16 cells[3][32][32];
} beast_cache_want;
static const u16 beast_floor_tiles[3][4] = { { 0, 0, 0, 0 }, { 356, 357, 358, 359 }, { 368, 369, 370, 371 } };
static void beast_intro_resources(u32 check)
{
    u32 i;
    if (!check) {
        c_test_copy_words((u32*)beast_effect_tables, (u32*)tile_effect_tables, sizeof(beast_effect_tables) / 4);
        c_test_copy_words((u32*)beast_effect_links, (u32*)D_80119090, sizeof(beast_effect_links) / 4);
        c_test_copy_words((u32*)beast_effect_records, (u32*)D_80116F70, sizeof(beast_effect_records) / 4);
    } else {
        beast_same_words(tile_effect_tables, beast_effect_tables, sizeof(beast_effect_tables));
        beast_same_words(D_80119090, beast_effect_links, sizeof(beast_effect_links));
        beast_same_words(D_80116F70, beast_effect_records, sizeof(beast_effect_records));
        beast_same_words(D_80114C14, beast_floor_tiles[0], 8);
        beast_same_words(D_80114C1C, beast_floor_tiles[1], 8);
        beast_same_words(D_80114C24, beast_floor_tiles[2], 8);
        assert(tile_effect_tables[16] == D_80119090 && D_80119090[8] == D_80116F70 && *(u32*)D_801005B0 == 0x201F1E1D && *(u32*)&D_8010024C == 0x1A1C0000);
        for (i = 0; i < 6; i++)
            assert(D_80116F70[i].layer == 0 && D_80116F70[i].packed_count == 9 && D_80116F70[i].x == 0 && D_80116F70[i].y == (i + 1) * 16 && D_80116F70[i].has_next == (i < 5) && D_80116F70[i].tiles == (i < 4 ? D_80114C14 : i == 4 ? D_80114C1C
                                                                                                                                                                                                                                      : D_80114C24));
    }
}
struct BeastIntroLand {
    s32 speed;
    u8 counter, attribute, animation;
};
static const struct BeastIntroLand beast_intro_lands[9] = {
    { 0x4000, 0, 55, 22 },
    { 0x2000, 0, 55, 22 },
    { -0x20000, 0, 55, 23 },
    { -0x20000, 0, 56, 23 },
    { -0x20000, 0, 57, 23 },
    { -0x20000, 1, 55, 23 },
    { -0x20000, 1, 56, 23 },
    { -0x20000, 1, 57, 23 },
    { -0x20000, 2, 56, 3 },
};
static const u8 beast_intro_free[4] = { 0, 1, 3, 4 };
static u32 test_slash_beast_intro_landing(u32 row)
{
    static const u8 phases[][4] = { { 0, 0, 0, 0 }, { 2, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 1, 1 } };
    const struct BeastIntroLand* c = &beast_intro_lands[row % 9];
    const u8* phase = phases[row / 9];
    u32 edge = phase[0], floor = phase[3] && row % 9 >= 2, available = beast_intro_free[(row % 9 + edge) % 4];
    u32 visible = phase[1], layer = 0, rematch = phase[2], effect = !rematch && c->speed < 0 && c->counter == 0 && c->attribute == 56, i, j;
    u8 *saved_map = SP_BG_TILEMAP, *saved_pixels = TEST_BG_TILE_PIXELS;
    u32 width = layout_width, height = layout_height, size = layout_size;
    beast_attack_prepare(!rematch, layer + 1, rematch, 0, 0);
    boss.unk5 = 9;
    boss.unk6 = 4;
    boss.unk7E = c->counter;
    boss.ext.main_54.active = 0;
    boss.on_screen = 0;
    boss.x_pos.val = (0x24A0 + 222 + edge) * 65536 + 0x1234;
    boss.y_pos.val = 224 * 65536 + 0x5678;
    boss.x_speed = 0x1E000;
    boss.x_accel = 0;
    boss.y_speed = c->speed;
    boss.gravity = 0x2000;
    boss.collision_flags = floor ? 8 : 0;
    boss.terrain_box = c->speed > 0 ? 0 : &D_8010024C;
    beast_install(c->animation, 0, c->animation == 22 ? 0x03010002 : c->animation == 23 ? 0x05010002
                                                                                        : 0x02010002,
        0);
    for (i = 0; i < 2; i++) {
        background_objects[i].x_pos.val = 0x24A0 * 65536;
        background_objects[i].y_pos.val = visible * 256 * 65536;
        c_test_copy_words((u32*)&beast_backgrounds[i], (u32*)&background_objects[i], sizeof(beast_backgrounds[i]) / 4);
    }
    for (i = 0; i < available; i++)
        misc_objects[beast_debris_slots[i]].active = beast_misc[beast_debris_slots[i]].active = 0;
    c_test_zero_words((u32*)&beast_probe_map, sizeof(beast_probe_map) / 4);
    beast_fill_words((u32*)&beast_probe_tiles, 0x02AA02AA, sizeof(beast_probe_tiles) / 4);
    beast_probe_map.bytes[77] = beast_probe_map.bytes[layer * 80 + 77] = 1;
    beast_probe_tiles.cells[1][c->counter == 0 ? 3 : 0][edge ? 8 : 7] = 1;
    beast_fill_words((u32*)D_801441C8, 0x05550555, sizeof(D_801441C8) / 4);
    c_test_copy_words((u32*)&beast_cache_want, (u32*)D_801441C8, sizeof(D_801441C8) / 4);
    c_test_copy_words((u32*)&beast_probe_map_want, (u32*)&beast_probe_map, sizeof(beast_probe_map) / 4);
    c_test_copy_words((u32*)&beast_probe_tiles_want, (u32*)&beast_probe_tiles, sizeof(beast_probe_tiles) / 4);
    SP_BG_TILEMAP = beast_probe_map.bytes;
    TEST_BG_TILE_PIXELS = (u8*)beast_probe_tiles.cells;
    layout_width = 40;
    layout_height = 2;
    layout_size = 80;
    beast_attrs[1] = beast_attrs_want[1] = (beast_attrs[1] & 0xFFFFFF00) | c->attribute;
    beast_intro_resources(0);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    beast_expect_move();
    beast_expect_frame(c->animation, 0, c->animation == 22 ? 0x03010001 : c->animation == 23 ? 0x05010001
                                                                                             : 0x02010001,
        0);
    beast_want.on_screen = 1;
    if (edge) {
        beast_want.x_speed = 0;
        beast_want.gravity = 65536;
    }
    if (c->speed == 0x2000) {
        beast_want.terrain_box = &D_8010024C;
        beast_expect_frame(23, 0, 0x05010002, 1);
    }
    if (c->speed < 0 && c->attribute == 56 && c->counter < 2) {
        beast_want.unk7E++;
        if (c->counter == 1)
            beast_expect_frame(3, 0, 0x02010002, 1);
    }
    if (effect) {
        for (i = 0; i < 6; i++)
            for (j = 0; j < 4; j++) {
                u16 tile = beast_floor_tiles[i < 4 ? 0 : i - 3][j];
                beast_probe_tiles_want.cells[1][i + 5][j + 8] = tile;
                if (visible)
                    beast_cache_want.cells[0][i + 21][j + 24] = tile;
            }
        for (i = 0; i < available; i++) {
            struct MiscObj* m = &beast_misc[beast_debris_slots[i]];
            const u8* r = beast_debris_random[i];
            m->active = 0x41;
            m->id = 3;
            m->unk2 = m->state = m->unk5 = m->unk6 = 0;
            m->unk15 = r[0] & 0x40;
            m->x_pos.val = beast_want.x_pos.val + (r[1] & 3) * 65536;
            m->y_pos.val = beast_want.y_pos.val + (r[2] & 3) * 65536;
            m->ext.misc_2.unk58 = 29 + i;
            m->ext.misc_2.owner = &boss;
        }
        beast_random_want = beast_debris_states[available];
    }
    if (floor) {
        struct BackgroundObj* bg = &beast_backgrounds[0];
        bg->unk37 = 16;
        bg->unk46 = bg->unk3E.bytes[1] = 4;
        bg->unk3D = bg->unk3B = 2;
        bg->unk34 |= 1;
        beast_want.ext.main_54.active = 1;
        beast_want.unk6 = 5;
    }
    slash_beast_intro(&boss);
    beast_same_words(&beast_probe_map, &beast_probe_map_want, sizeof(beast_probe_map));
    beast_same_words(&beast_probe_tiles, &beast_probe_tiles_want, sizeof(beast_probe_tiles));
    beast_same_words(D_801441C8, &beast_cache_want, sizeof(D_801441C8));
    beast_intro_resources(1);
    assert(SP_BG_TILEMAP == beast_probe_map.bytes && TEST_BG_TILE_PIXELS == (u8*)beast_probe_tiles.cells && layout_width == 40 && layout_height == 2 && layout_size == 80);
    beast_attack_check();
    SP_BG_TILEMAP = saved_map;
    TEST_BG_TILE_PIXELS = saved_pixels;
    layout_width = width;
    layout_height = height;
    layout_size = size;
    return 1;
}
static struct EffectObj beast_effects[32];
static struct ItemObj beast_items[32];
static u32 test_slash_beast_intro_wait(u32 row)
{
    u32 scene = row % 7, pool = (row / 7) % 4, facing = (row / 28) % 2, layer = 0, rematch = row / 56, i, slot = pool ? beast_shot_slots[pool] : 14;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 9;
    boss.unk6 = scene < 3 ? 0 : 1;
    boss.ext.main_54.effect = &effect_objects[14];
    beast_fill_words((u32*)effect_objects, 0xA5A5A5A5, sizeof(effect_objects) / 4);
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = 1;
        effect_objects[i].id = 7;
        item_objects[i].active = 1;
    }
    if (pool)
        effect_objects[slot].active = 0;
    if (scene < 3)
        g_Player.x_pos.i.hi = 0x24FF + scene;
    else {
        boss.ext.main_54.effect = &effect_objects[slot];
        effect_objects[slot].active = (scene - 3) & 1;
        background_objects[0].x_pos.i.hi = 0x24A0 + ((scene - 3) / 2);
    }
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(beast_want) / 4);
    c_test_copy_words((u32*)&beast_player, (u32*)&g_Player, sizeof(beast_player) / 4);
    c_test_copy_words((u32*)&beast_backgrounds[0], (u32*)&background_objects[0], sizeof(beast_backgrounds[0]) / 4);
    c_test_copy_words((u32*)beast_effects, (u32*)effect_objects, sizeof(beast_effects) / 4);
    c_test_copy_words((u32*)beast_items, (u32*)item_objects, sizeof(beast_items) / 4);
    if (scene < 3 && (scene != 0 || rematch)) {
        if (pool) {
            beast_effects[slot].active = 1;
            beast_effects[slot].id = 24;
            beast_want.ext.main_54.effect = &effect_objects[slot];
        }
        beast_player.script_state = beast_player.spike_immune = beast_engine.gameplay_locked = 1;
        beast_player.script_action = 0x14;
        beast_player.script_facing = 0x40;
        if (!rematch) {
            beast_backgrounds[0].unk26 = 0x24A0;
            beast_backgrounds[0].unk24 = 0x24E0;
            beast_backgrounds[0].unk2A = beast_backgrounds[0].unk28 = 0xF8;
        }
        beast_want.unk7C = 3;
        beast_want.unk7E = 1;
        beast_want.unk6 = 1;
    } else if (scene >= 3 && !((scene - 3) & 1) && (scene < 5 || rematch))
        beast_want.unk6 = 2;
    slash_beast_intro(&boss);
    beast_same_words(effect_objects, beast_effects, sizeof(beast_effects));
    beast_same_words(item_objects, beast_items, sizeof(beast_items));
    beast_attack_check();
    return 1;
}

static const u16 beast_dialogue_colors[32] = { 0x0, 0x8000, 0x8421, 0x8c63, 0xa108, 0xa94a, 0xad6b, 0xb18c, 0xbdef, 0xc631, 0xd6b5, 0xe318, 0xeb5a, 0xf39c, 0xffff, 0x8c67, 0x0, 0xfbde, 0xc100, 0xbce0, 0xb8c0, 0xb4c0, 0xb0a0, 0xaca0, 0xa880, 0xa480, 0xa060, 0x9c60, 0x9840, 0x9840, 0xfb91, 0xcde6 };
extern union MainPaletteData D_800F1660;
extern const u32* D_800F2FD4[2];
extern u32 D_800F2F60[29];
extern struct DialogueGlyphData D_801396C8;
static union {
    u32 words[512];
    u16 colors[1024];
} beast_dialogue_palette, beast_dialogue_palette_want;
static u32 beast_dialogue_resource[128], beast_glyph_words[61];
static union {
    u32 words[18];
    u16 half[36];
} beast_messages;
static const s8 beast_window_slots[4] = { -1, 0, 31, 63 };
static const u8 beast_dialogue_slots[7] = { 9, 7, 13, 19, 29, 43, 57 };
static void beast_filled_words(const u32* words, u32 value, u32 count)
{
    u32 difference = 0;
    while (count >= 8) {
        difference |= (words[0] ^ value) | (words[1] ^ value) | (words[2] ^ value) | (words[3] ^ value) | (words[4] ^ value) | (words[5] ^ value) | (words[6] ^ value) | (words[7] ^ value);
        words += 8;
        count -= 8;
    }
    while (count) {
        difference |= *words++ ^ value;
        count--;
    }
    assert(difference == 0);
}
static const struct {
    u8 event, repeat, mode, flags, pool, rematch;
} beast_poses[] = {
    { 0, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 0 },
    { 1, 1, 0, 0, 0, 0 },
    { 1, 0, 1, 0, 0, 0 },
    { 1, 0, 2, 0, 0, 0 },
    { 1, 0, 0, 1, 1, 0 },
    { 1, 0, 0, 0, 2, 0 },
    { 1, 0, 0, 0, 0, 1 },
};
static u32 test_slash_beast_intro_pose(u32 row)
{
    u32 event = beast_poses[row].event, repeat = beast_poses[row].repeat, mode = beast_poses[row].mode;
    u32 flags = beast_poses[row].flags, pool = beast_poses[row].pool, rematch = beast_poses[row].rematch;
    u32 facing = row % 2, layer = 0, i;
    u8 *saved_palette = TEST_PALETTE, *saved_messages = TEST_ARC_48;
    struct AbcObj want;
    struct MiscObj** slots[7] = { &D_801397BC, &D_801397C0, &D_801397C4, &D_801397C8, &D_801397CC, &D_801397D0, &D_801397D4 };
    struct MiscObj* handles[7];
    u32 saved_colors[16], resource_animation[29], message_words[18];
    u8 portrait = 0x27, old_enable = 0x42, old_lock = 0x49;
    s16 glyph_count = 37;
    struct Func80022730Config* config;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 9;
    boss.unk6 = 5;
    beast_install(3, event ? 5 : 0, event ? 0x00000101 : 0x02010002, 0);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(boss) / 4);
    if (pool)
        misc_objects[beast_window_slots[pool]].active = 0;
    for (i = 0; i < 7; i++) {
        handles[i] = mode && i != 3 ? &misc_objects[beast_dialogue_slots[i]] : 0;
        *slots[i] = handles[i];
        if (handles[i]) {
            handles[i]->id = i & 1 ? 22 : 23;
            handles[i]->on_screen = 1;
        }
    }
    c_test_copy_words((u32*)beast_misc, (u32*)misc_objects, sizeof(beast_misc) / 4);
    beast_fill_words((u32*)&abc_object, 0x25252525, sizeof(abc_object) / 4);
    abc_object.unkC = mode == 0 ? 0 : mode == 1 ? 1
                                                : 0x80;
    c_test_copy_words((u32*)&want, (u32*)&abc_object, sizeof(want) / 4);
    engine_obj.character_state.bytes[8] = repeat;
    engine_obj.enable_boss = 1;
    engine_obj.unk1F = 7;
    c_test_copy_words((u32*)&beast_engine, (u32*)&engine_obj, sizeof(engine_obj) / 4);
    D_801397D8 = portrait;
    D_801397DC = (struct Func80022730Config*)D_800F2DD0[0];
    config = D_801397DC;
    D_801397E0 = glyph_count;
    D_80139828 = old_enable;
    D_80139824 = old_lock;
    beast_fill_words((u32*)&D_801396C8, 0x35353535, sizeof(D_801396C8) / 4);
    c_test_copy_words(beast_glyph_words, (u32*)&D_801396C8, sizeof(D_801396C8) / 4);
    beast_fill_words((u32*)D_801397E4, 0x41414141, 16);
    beast_fill_words(saved_colors, 0x41414141, 16);
    beast_fill_words(beast_dialogue_palette.words, 0x29292929, 512);
    c_test_copy_words(beast_dialogue_palette_want.words, beast_dialogue_palette.words, 512);
    TEST_PALETTE = (u8*)beast_dialogue_palette.colors;
    beast_fill_words((u32*)WINDOW_ARCHIVE_DATA, 0x47474747, 0xC00);
    ((u32*)WINDOW_ARCHIVE_DATA)[2] = 0x40;
    beast_fill_words(beast_messages.words, 0, 18);
    beast_messages.half[16] = 64;
    beast_messages.half[32] = flags ? 0x800 : 0;
    beast_messages.half[33] = 0xFFFF;
    c_test_copy_words(message_words, beast_messages.words, 18);
    TEST_ARC_48 = (u8*)beast_messages.half;
    c_test_copy_words(beast_dialogue_resource, (u32*)&D_800F1660, 128);
    c_test_copy_words(resource_animation, D_800F2F60, 29);
    if (event) {
        beast_want.unk6 = 6;
        if (!rematch) {
            beast_want.unk15 = 0;
            beast_expect_frame(24, 0, 0x19000101, 1);
            beast_engine.character_state.bytes[8] = 1;
        }
    } else
        beast_expect_frame(3, 0, 0x02010001, 0);
    if (event && !rematch) {
        if (mode) {
            want.unk10 = (s16)0x8010;
            if (mode == 1) {
                want.unkC = 0x80;
                want.unkA = 0x27;
                want.unkD = 4;
                for (i = 1; i < 7; i++)
                    if (handles[i] && (i & 1)) {
                        beast_misc[beast_dialogue_slots[i]].active = 0;
                        beast_misc[beast_dialogue_slots[i]].on_screen = 0;
                    }
            }
        } else {
            want.unkC = 0x80;
            want.unk10 = want.unkE = 0;
            portrait = 0xFF;
            for (i = 0; i < 7; i++)
                handles[i] = 0;
            if (repeat) {
                want.unkA = 60;
                want.unkD = 6;
            } else {
                old_enable = 1;
                old_lock = 7;
                beast_engine.enable_boss = beast_engine.unk1F = 0;
                beast_fill_words(saved_colors, 0x29292929, 16);
                c_test_copy_words((u32*)(beast_dialogue_palette_want.colors + 0x150), (u32*)beast_dialogue_colors, 16);
                beast_palette_want = 0x21;
                want.unk0 = beast_messages.half + 32;
                want.unk4 = flags ? 0x800 : 0;
                want.unk6 = -120;
                want.unk8 = 29;
                want.unkF = 1;
                want.unkA = 39;
                want.unkD = 0;
                glyph_count = 0;
                if (pool) {
                    struct MiscObj* m = &beast_misc[beast_window_slots[pool]];
                    handles[0] = &misc_objects[beast_window_slots[pool]];
                    m->active = 1;
                    m->id = 22;
                    m->unk2 = 2;
                    m->unk16 = 0x11;
                    m->animation_table = (u32**)D_800F2FD4;
                    m->unk40 = 0x1E00;
                    m->unk42 = 0x7846;
                    m->bg_offset = -1;
                    m->x_pos.i.hi = 160;
                    m->y_pos.i.hi = flags ? 180 : 60;
                    m->unk3C = WINDOW_ARCHIVE_DATA + 0x40;
                    m->unk15 = m->unk17 = 0;
                    m->previous_animation_index = 0xFF;
                    m->animation_cursor = D_800F2F60;
                    m->animation_step.packed = 0x28010004;
                }
            }
        }
    }
    slash_beast_intro(&boss);
    beast_same_words(&abc_object, &want, sizeof(want));
    for (i = 0; i < 7; i++)
        assert(*slots[i] == handles[i]);
    assert(D_801397D8 == portrait && D_801397DC == config && D_801397E0 == glyph_count && D_80139828 == old_enable && D_80139824 == old_lock);
    beast_same_words(D_801397E4, saved_colors, 64);
    beast_same_words(&D_801396C8, beast_glyph_words, sizeof(D_801396C8));
    beast_same_words(beast_dialogue_palette.words, beast_dialogue_palette_want.words, sizeof(beast_dialogue_palette));
    beast_filled_words((u32*)WINDOW_ARCHIVE_DATA, 0x47474747, 2);
    assert(((u32*)WINDOW_ARCHIVE_DATA)[2] == 0x40);
    beast_filled_words((u32*)WINDOW_ARCHIVE_DATA + 3, 0x47474747, 0xBFD);
    beast_same_words(&D_800F1660, beast_dialogue_resource, 512);
    beast_same_words(D_800F1660.raw + 0xA0, beast_dialogue_colors, 64);
    beast_same_words(D_800F2F60, resource_animation, sizeof(resource_animation));
    beast_same_words(beast_messages.words, message_words, sizeof(message_words));
    assert(TEST_PALETTE == (u8*)beast_dialogue_palette.colors && TEST_ARC_48 == (u8*)beast_messages.half && D_800F2FD4[0] == D_800F2F60 && D_800F2FD4[1] == 0 && D_800F2F60[0] == 0x28010004 && sizeof(D_801396C8) == sizeof(beast_glyph_words));
    beast_attack_check();
    TEST_PALETTE = saved_palette;
    TEST_ARC_48 = saved_messages;
    return 1;
}
static const s16 beast_afterimage_x[4] = { -33, -32, 351, 352 };
static u32 test_slash_beast_afterimages(u32 row)
{
    u32 scene = row % 8, position = (row / 8) % 4, facing = (row / 32) % 2, layer = 0, rematch = row / 64;
    struct MiscObj *m, *w;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.state = scene == 1 || scene == 6 ? 2 : 1;
    boss.ext.main_54.powered_up = scene != 2;
    boss.x_pos.val = (beast_afterimage_x[position] + (layer == 2 ? 1024 : 0)) * 65536 + 0x1234;
    beast_install(9, 0, 0x1F010002, 0);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(boss) / 4);
    m = &misc_objects[13];
    m->active = 0x41;
    m->id = 26;
    m->state = scene == 7;
    m->unk2 = scene >= 3;
    m->on_screen = 1;
    m->ext.misc_26.owner = &boss;
    m->ext.misc_26.timer = scene == 3 ? 2 : scene == 5 ? 1
                                                       : 5;
    m->bg_offset = boss.bg_offset;
    m->unk15 = boss.unk15 ^ 0x40;
    m->unk42 = 0x4567;
    m->x_pos.val = boss.x_pos.val + 65536;
    m->y_pos.val = boss.y_pos.val + 65536 + 0x111;
    m->animation_step.fields.frame_index = 31;
    c_test_copy_words((u32*)beast_misc, (u32*)misc_objects, sizeof(beast_misc) / 4);
    w = &beast_misc[13];
    if (scene < 3) {
        w->x_pos = boss.x_pos;
        w->y_pos = boss.y_pos;
        w->unk15 = boss.unk15;
        w->unk42 = boss.unk42;
        w->animation_step.fields.frame_index = 91;
        if (scene)
            w->state = 1;
        else
            w->on_screen = position == 1 || position == 2;
    } else if (scene < 7) {
        w->ext.misc_26.timer--;
        if (scene >= 5)
            w->state = 1;
        else
            w->on_screen = scene == 4 && position < 2;
    } else
        w->active = w->id = w->unk2 = w->on_screen = w->state = w->unk5 = w->unk6 = w->unk7 = 0;
    slash_beast_afterimage_update(m);
    beast_attack_check();
    return 1;
}

static u32 test_slash_beast_intro_crates(u32 row)
{
    u32 scene = row % 4, items = row / 4 == 1, misc = row / 4 == 2, facing = 0, layer = 0, rematch = row / 4 == 2, i;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 9;
    boss.unk6 = 2;
    boss.unk7C = scene ? 4 - scene : 3;
    boss.unk7E = scene ? 1 : 2;
    beast_install(3, 0, 0x02010002, 0);
    beast_fill_words((u32*)item_objects, 0xA5A5A5A5, sizeof(item_objects) / 4);
    for (i = 0; i < 32; i++)
        item_objects[i].active = 1;
    if (items)
        item_objects[beast_shot_slots[items]].active = 0;
    if (misc)
        misc_objects[beast_window_slots[misc]].active = 0;
    c_test_copy_words((u32*)beast_items, (u32*)item_objects, sizeof(beast_items) / 4);
    c_test_copy_words((u32*)beast_misc, (u32*)misc_objects, sizeof(beast_misc) / 4);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(boss) / 4);
    beast_want.unk7E--;
    if (scene) {
        beast_want.unk7C--;
        if (!rematch && items) {
            struct ItemObj* item = &beast_items[beast_shot_slots[items]];
            item->unk50 = 0;
            item->unk54 = 0;
            item->unk68 = 0;
            item->unk61 = item->unk64 = item->unk65 = item->unk66 = item->unk72 = item->unk73 = item->unk74 = item->unk76 = item->unk77 = item->unk78 = item->unk62 = item->unk63 = item->unk7A = item->unk75 = 0;
            item->active = 0x41;
            item->id = 18;
            item->unk16 = 5;
            item->unk2 = 3 - boss.unk7C;
            item->unk40 = boss.unk40;
            item->unk42 = boss.unk42 & 0x7FFF;
            item->animation_table = (const u8* const*)slash_beast_animations;
            item->sprite_frames = boss.sprite_frames;
            item->animation_step.fields.frame_index = 121;
            item->state = 0;
            item->bg_offset = boss.bg_offset;
        }
        if (!rematch && scene < 3)
            beast_want.unk7E = 30;
        else {
            beast_engine.enable_boss = beast_engine.unk25 = 1;
            beast_engine.boss_ptr = &boss;
            beast_want.unk7C = 200;
            if (misc) {
                struct MiscObj* m = &beast_misc[beast_window_slots[misc]];
                m->active = 0x41;
                m->id = 26;
                m->unk2 = m->state = 0;
                m->unk16 = 5;
                m->unk40 = boss.unk40;
                m->unk42 = boss.unk42 & 0x7FFF;
                m->animation_table = (u32**)slash_beast_animations;
                m->unk3C = (void*)boss.sprite_frames;
                m->bg_offset = boss.bg_offset;
                m->x_pos = boss.x_pos;
                m->y_pos = boss.y_pos;
                m->unk15 = boss.unk15;
                m->ext.misc_26.owner = &boss;
                m->animation_step.fields.frame_index = 62;
            }
            beast_want.unk15 = rematch ? 0 : 0x40;
            beast_expect_frame(rematch ? 23 : 21, 0, rematch ? 0x05010002 : 0x2D010001, 1);
            beast_want.unk6 = rematch ? 4 : 3;
            if (rematch)
                beast_want.unk7E = 1;
            else
                beast_want.x_speed = 65536;
        }
    }
    slash_beast_intro(&boss);
    beast_same_words(item_objects, beast_items, sizeof(beast_items));
    beast_attack_check();
    return 1;
}
static u32 test_slash_beast_grab_trails(u32 row)
{
    u32 available = row % 3, powered = (row / 3) % 2, timer = (row / 6) % 2 + 1, attribute = (row / 12) % 3 + 55, facing = (row / 36) % 2, layer = 0, i, created = timer == 1 ? (available < 1 + powered ? available : 1 + powered) : 0;
    u8 *saved_map = SP_BG_TILEMAP, *saved_pixels = TEST_BG_TILE_PIXELS;
    u32 width = layout_width, height = layout_height, size = layout_size;
    beast_attack_prepare(facing, layer + 1, 0, 0, available);
    boss.unk5 = 7;
    boss.unk6 = 2;
    boss.ext.main_54.powered_up = powered;
    boss.ext.main_54.afterimage_timer = timer;
    boss.terrain_box = &D_8010024C;
    boss.x_pos.val = (facing ? 253 : 258) * 65536 + layer * 1024 * 65536 + 0x1234;
    boss.y_pos.val = 129 * 65536 + 0x5678;
    beast_install(3, 0, 0x02010002, 0);
    c_test_zero_words((u32*)&beast_probe_map, sizeof(beast_probe_map) / 4);
    beast_fill_words((u32*)&beast_probe_tiles, 0x02AA02AA, sizeof(beast_probe_tiles) / 4);
    beast_probe_map.bytes[layer * 12 + facing] = 1;
    beast_probe_tiles.cells[1][7][facing ? 3 : 12] = 1;
    c_test_copy_words((u32*)&beast_probe_map_want, (u32*)&beast_probe_map, sizeof(beast_probe_map) / 4);
    c_test_copy_words((u32*)&beast_probe_tiles_want, (u32*)&beast_probe_tiles, sizeof(beast_probe_tiles) / 4);
    SP_BG_TILEMAP = beast_probe_map.bytes;
    TEST_BG_TILE_PIXELS = (u8*)beast_probe_tiles.cells;
    layout_width = layout_size = 8;
    layout_height = 1;
    beast_attrs[1] = beast_attrs_want[1] = (beast_attrs[1] & 0xFFFFFF00) | attribute;
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(boss) / 4);
    beast_want.x_pos.val += boss.x_speed;
    beast_want.y_pos.val -= boss.y_speed;
    beast_want.ext.main_54.afterimage_timer = timer == 1 ? 10 : 1;
    beast_player.x_pos.i.hi = beast_want.x_pos.i.hi + (facing ? 35 : -35);
    if (attribute == 56)
        beast_want.unk6 = 3;
    for (i = 0; i < created; i++) {
        struct MiscObj* m = &beast_misc[i ? 61 : 3];
        m->active = 0x41;
        m->id = 26;
        m->unk2 = 1;
        m->unk16 = 0x21 - i;
        m->unk40 = boss.unk40;
        m->unk42 = boss.unk42 & 0x7FFF;
        m->animation_table = (u32**)slash_beast_animations;
        m->unk3C = (void*)boss.sprite_frames;
        m->bg_offset = boss.bg_offset;
        m->x_pos = beast_want.x_pos;
        m->y_pos = beast_want.y_pos;
        m->unk15 = boss.unk15;
        m->animation_step.fields.frame_index = i ? 62 : 2;
        m->ext.misc_26.timer = 30;
        m->ext.misc_26.owner = &boss;
        m->state = 0;
    }
    slash_beast_grab(&boss);
    beast_same_words(&beast_probe_map, &beast_probe_map_want, sizeof(beast_probe_map));
    beast_same_words(&beast_probe_tiles, &beast_probe_tiles_want, sizeof(beast_probe_tiles));
    assert(SP_BG_TILEMAP == beast_probe_map.bytes && TEST_BG_TILE_PIXELS == (u8*)beast_probe_tiles.cells && layout_width == 8 && layout_size == 8 && layout_height == 1 && *(u32*)&D_8010024C == 0x1A1C0000);
    beast_attack_check();
    SP_BG_TILEMAP = saved_map;
    TEST_BG_TILE_PIXELS = saved_pixels;
    layout_width = width;
    layout_height = height;
    layout_size = size;
    return 1;
}

struct BeastLaunch {
    s16 distance;
    s8 fraction;
    s32 motion[3][2];
};
static const struct BeastLaunch beast_launches[18] = {
    { 111, -1, { { 0x29c80, 0x4b400 }, { 0x36700, 0x5b000 }, { 0x3f700, 0x6b400 } } },
    { 111, 0, { { 0x29c80, 0x4b400 }, { 0x36b80, 0x5b000 }, { 0x3fb80, 0x68000 } } },
    { 111, 1, { { 0x29c80, 0x4b400 }, { 0x36b80, 0x5b000 }, { 0x3fb80, 0x68000 } } },
    { 112, -1, { { 0x29c80, 0x4b400 }, { 0x36b80, 0x5e400 }, { 0x3fb80, 0x6b400 } } },
    { 112, 0, { { 0x29c80, 0x4b400 }, { 0x37000, 0x5b000 }, { 0x40000, 0x6b400 } } },
    { 112, 1, { { 0x29c80, 0x4b400 }, { 0x37000, 0x5b000 }, { 0x40000, 0x6b400 } } },
    { 113, -1, { { 0x2a100, 0x4b400 }, { 0x37000, 0x5e400 }, { 0x40000, 0x6b400 } } },
    { 113, 0, { { 0x2a100, 0x4b400 }, { 0x37480, 0x5e400 }, { 0x40480, 0x6b400 } } },
    { 113, 1, { { 0x2a100, 0x4b400 }, { 0x37480, 0x5e400 }, { 0x40480, 0x6b400 } } },
    { 117, -1, { { 0x2a580, 0x4ec00 }, { 0x38200, 0x5e400 }, { 0x41200, 0x6b400 } } },
    { 117, 0, { { 0x2aa00, 0x4d000 }, { 0x38680, 0x5e400 }, { 0x41680, 0x6b400 } } },
    { 117, 1, { { 0x2aa00, 0x4d000 }, { 0x38680, 0x5e400 }, { 0x41680, 0x6b400 } } },
    { 161, -1, { { 0x2ff80, 0x5e800 }, { 0x44800, 0x6e800 }, { 0x4d800, 0x78400 } } },
    { 161, 0, { { 0x2ff80, 0x5e800 }, { 0x44c80, 0x6e800 }, { 0x4dc80, 0x78400 } } },
    { 161, 1, { { 0x2ff80, 0x5e800 }, { 0x44c80, 0x6e800 }, { 0x4dc80, 0x78400 } } },
    { 162, -1, { { 0x2ff80, 0x60400 }, { 0x44c80, 0x6e800 }, { 0x4dc80, 0x78400 } } },
    { 162, 0, { { 0x30400, 0x5e800 }, { 0x45100, 0x6e800 }, { 0x4e100, 0x78400 } } },
    { 162, 1, { { 0x30400, 0x5e800 }, { 0x45100, 0x6e800 }, { 0x4e100, 0x78400 } } },
};
static u32 test_slash_beast_leap_launch(u32 row)
{
    const struct BeastLaunch* c = &beast_launches[row / 8];
    u32 event = row % 2, grab = (row / 2) % 2, side = (row / 4) % 2, facing = (row / 8 + side) % 2, layer = 0, rematch = 0;
    const s32* motion = c->motion[grab ? (side == facing ? 1 : 2) : 0];
    s32 delta = c->distance * 65536 + c->fraction;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 7;
    boss.unk6 = 0;
    boss.ext.main_54.grab = grab;
    g_Player.x_pos.val = boss.x_pos.val + (side ? delta : -delta);
    beast_install(38, event ? 5 : 0, event ? 0x00000101 : 0x00010003, 0);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(boss) / 4);
    c_test_copy_words((u32*)&beast_player, (u32*)&g_Player, sizeof(g_Player) / 4);
    if (c->distance < 112) {
        beast_want.unk5 = 3;
        beast_want.unk6 = 0;
    } else if (!event)
        beast_expect_frame(38, 0, 0x00010002, 0);
    else {
        beast_want.x_accel = 0;
        beast_want.gravity = grab ? 0x6800 : 0x3800;
        beast_want.x_speed = facing ? motion[0] : -motion[0];
        beast_want.y_speed = motion[1] - beast_want.gravity;
        beast_want.x_pos.val += beast_want.x_speed;
        beast_want.y_pos.val -= motion[1];
        beast_want.unk5 = 4;
        beast_want.unk6 = 1;
        beast_expect_frame(grab ? 4 : 2, 0, grab ? 0x07010002 : 0x03010002, 1);
        if (grab) {
            beast_want.ext.main_54.grab = 0x81;
            beast_want.contact_damage = 0;
            beast_want.unk62 = 3;
        } else {
            beast_want.hurt_box = &D_8010020C;
            beast_want.attack_box = &D_80100208;
        }
    }
    func_8006D3DC(&boss);
    beast_attack_check();
    return 1;
}
static u32 test_slash_beast_init_full(u32 row)
{
    u32 page = row % 2, facing = (row / 2) % 2, layer = 0, rematch = row / 4, words[8];
    u32* saved_pages = D_801406A8;
    u8* saved_menu = TEST_MENU_FRAMES;
    beast_attack_prepare(facing, 0, rematch, 0, 0);
    boss.state = 0;
    boss.x_pos.i.hi += layer * 1024;
    boss.collision_data = D_801060F0;
    g_Player.bg_offset = layer;
    beast_install(3, 0, 0x02010002, 0);
    background_objects[layer].y_pos.val = 512 * 65536 + 0x1122;
    c_test_copy_words((u32*)beast_backgrounds, (u32*)background_objects, sizeof(beast_backgrounds) / 4);
    c_test_copy_words((u32*)&beast_player, (u32*)&g_Player, sizeof(g_Player) / 4);
    beast_fill_words(beast_pages, 0x45454545, 8);
    beast_pages[0] = 0x80 + page * 0x80;
    beast_pages[4] = 20;
    c_test_copy_words(words, beast_pages, 8);
    D_801406A8 = beast_pages;
    TEST_MENU_FRAMES = (u8*)beast_pages;
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(boss) / 4);
    beast_want.contact_damage = 6;
    beast_want.hp = beast_want.invincibility_timer = 0;
    beast_want.collision_data = D_801078F8;
    beast_want.unk40 = (rematch ? 0x161 : 0xB1) + page;
    if (rematch) {
        beast_want.unk42 = 0x7888;
        beast_want.sprite_frames = (u8*)beast_pages + 20;
        beast_want.y_pos.val = 464 * 65536 + 0x1122;
    }
    beast_want.animation_table = (const u8* const*)slash_beast_animations;
    beast_want.unk16 = 6;
    beast_want.hurt_box = D_801001FC;
    beast_want.attack_box = D_801001F8;
    beast_want.unk15 = 0x40;
    beast_want.x_speed = beast_want.y_speed = beast_want.x_accel = beast_want.gravity = beast_want.air_state = 0;
    beast_want.terrain_box = 0;
    beast_want.ext.main_54.flash_timer = beast_want.ext.main_54.was_hit = beast_want.ext.main_54.grab = beast_want.ext.main_54.active = beast_want.ext.main_54.claw_hitbox = beast_want.ext.main_54.pattern_set = beast_want.ext.main_54.fight_started = beast_want.ext.main_54.high_jump = 0;
    beast_want.ext.main_54.powered_up = beast_want.ext.main_54.power_hits = 1;
    beast_want.bg_offset = layer;
    beast_want.unk18 = beast_want.x_pos;
    beast_want.unk1C = beast_want.y_pos;
    beast_expect_tiles(rematch);
    beast_expect_frame(0, 0, 0x00000101, 1);
    beast_want.state = 1;
    beast_want.unk5 = 9;
    beast_want.unk6 = 0;
    func_8006BB70(&boss);
    beast_same_words(beast_pages, words, sizeof(words));
    assert(D_801406A8 == beast_pages && TEST_MENU_FRAMES == (u8*)beast_pages);
    beast_attack_check();
    D_801406A8 = saved_pages;
    TEST_MENU_FRAMES = saved_menu;
    return 1;
}
static const s16 beast_death_x[4] = { -97, -96, 415, 416 };
static u32 test_slash_beast_death_full(u32 row)
{
    u32 scene = row % 6, slot = beast_shot_slots[1], edge = row / 6 == 1, facing = 0, layer = 0, rematch = row / 6 == 2, i;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.state = 2;
    boss.unk5 = scene ? 2 : 0;
    boss.ext.main_54.effect = &effect_objects[slot];
    boss.x_pos.val = (beast_death_x[edge] + (layer == 2 ? 1024 : 0)) * 65536 + 0x1234;
    boss.unk7E = scene > 0 && scene < 4 ? scene - 1 : 9;
    beast_install(3, 0, 0x02010002, 0);
    beast_fill_words((u32*)effect_objects, 0xA5A5A5A5, sizeof(effect_objects) / 4);
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = 1;
        effect_objects[i].id = 26;
    }
    effect_objects[slot].active = scene != 5;
    effect_objects[slot].unk7 = scene == 4;
    engine_obj.checkpoint = 2;
    engine_obj.enable_boss = 1;
    engine_obj.boss_ptr = &boss;
    c_test_copy_words((u32*)beast_effects, (u32*)effect_objects, sizeof(beast_effects) / 4);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(boss) / 4);
    c_test_copy_words((u32*)&beast_engine, (u32*)&engine_obj, sizeof(beast_engine) / 4);
    beast_want.on_screen = scene < 4 && (edge == 1 || edge == 2);
    if (!scene) {
        beast_player.stun_timer = 0;
        beast_player.script_state = beast_player.spike_immune = beast_engine.gameplay_locked = 1;
        beast_player.script_action = 20;
        beast_player.script_facing = g_Player.unk15;
        beast_want.unk5 = 1;
        beast_want.unk42 &= 0x7FFF;
        beast_expect_frame(19, 0, 0x37000101, 1);
        beast_want.unk7C = 127;
        beast_want.unk7E = beast_want.invincibility_timer = 25;
    } else if (scene < 4) {
        beast_want.unk7E = scene == 1 ? 5 : scene - 2;
        if (scene == 1)
            beast_want.unk42 ^= 0x8000;
    } else if (scene == 5) {
        for (i = 0; i < 6; i++)
            beast_want.ext.raw[i] = 0;
        beast_engine.enable_boss = 0;
        beast_engine.boss_ptr = 0;
        beast_engine.unkF = rematch ? -128 : 16;
        if (rematch) {
            beast_engine.character_state.bytes[8] = 1;
            beast_engine.checkpoint = 11;
        }
        beast_want.active = beast_want.id = beast_want.unk2 = beast_want.on_screen = beast_want.state = beast_want.unk5 = beast_want.unk6 = beast_want.unk7 = 0;
    }
    slash_beast_death(&boss);
    beast_same_words(effect_objects, beast_effects, sizeof(beast_effects));
    beast_attack_check();
    return 1;
}

static const s32 beast_stance_deltas[5] = { -65536, -1, 0, 1, 65536 };
static u32 test_slash_beast_stance(u32 row)
{
    u32 side = row % 5, hit = (row / 5) % 2, timer = (row / 10) % 2 + 1, cycle = 0, facing = (side + hit) % 2, layer = 0, rematch = 0;
    beast_attack_prepare(facing, layer, rematch, 0, 0);
    boss.unk5 = 5;
    boss.unk6 = 0;
    boss.unk7C = timer;
    boss.ext.main_54.was_hit = hit;
    g_Player.x_pos.val = boss.x_pos.val + beast_stance_deltas[side];
    beast_install(20, cycle ? 3 : 0, cycle ? 0x1BFD0101 : 0x30010001, 0);
    c_test_copy_words((u32*)&beast_want, (u32*)&boss, sizeof(boss) / 4);
    c_test_copy_words((u32*)&beast_player, (u32*)&g_Player, sizeof(g_Player) / 4);
    beast_expect_frame(20, cycle ? 0 : 1, cycle ? 0x30010001 : 0x31010001, 0);
    if (hit && (facing ? side == 4 : side == 0)) {
        beast_want.unk5 = 2;
        beast_want.unk6 = 0;
    } else if (timer == 1) {
        beast_want.unk7C = 30;
        beast_expect_frame(0, 0, 0x00000101, 1);
        beast_want.unk15 = side < 2 ? 0 : 0x40;
        beast_want.unk5 = 3;
        beast_want.unk6 = 1;
    } else
        beast_want.unk7C = 1;
    func_8006CDD4(&boss);
    beast_attack_check();
    return 1;
}

#endif
