#include "test_runtime.h"
#ifndef VERSION_DEMO
#include "main/mains/main_72_unused_ride_armor.h"
#include "main/collision_bounds.h"
#include "main/55C4.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static struct Fixture {
    struct MainObj obj;
    u32 frames[2];
    const u8* table[10];
};
static void initialize(struct Fixture* fixture, u32 mode)
{
    u32 i;
    memset(fixture, 0, sizeof(*fixture));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(D_80139234, 0, sizeof(D_80139234));
    memset(D_8013924C, 0, sizeof(D_8013924C));
    memset(D_8013E198, 0, sizeof(D_8013E198));
    memset(D_80141EE8, 0, sizeof(D_80141EE8));
    memset(D_80141F50, 0, sizeof(D_80141F50));
    memset(background_objects, 0, sizeof(background_objects));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    fixture->frames[0] = C_TEST_STEP(mode == 1 ? 0x04000302 : 0x04010302);
    fixture->frames[1] = C_TEST_STEP(0x06000103);
    if (mode == 2)
        fixture->frames[0] = C_TEST_STEP(0x04010301);
    for (i = 0; i < COUNT(fixture->table); i++)
        fixture->table[i] = (const u8*)fixture->frames;
    fixture->obj.animation_table = fixture->table;
    fixture->obj.animation_cursor = (const u8*)fixture->frames;
    fixture->obj.animation_step.packed = fixture->frames[0];
    fixture->obj.x_pos.i.hi = 50;
    fixture->obj.y_pos.i.hi = 100;
    fixture->obj.ext.main_72.unk84 = 1;
    fixture->obj.collision_flags = 8;
    fixture->obj.previous_animation_index = 9;
    if (mode >= 2)
        fixture->obj.unk6 = 1;
    if (mode >= 3) {
        fixture->obj.ext.main_72.lifetime = mode == 3 ? 1 : 2;
        fixture->obj.ext.main_72.spawn_timer = mode == 4 ? 1 : 2;
    }
    if (mode >= 6 && mode <= 8) {
        fixture->obj.collision_flags = 0;
        fixture->obj.y_pos.i.hi = mode == 6 ? 0 : -100;
        fixture->obj.y_speed = mode == 8 ? -0x60000 : -0x10000;
        fixture->obj.gravity = 0x4200;
    }
    if (mode == 9) {
        fixture->obj.ext.main_72.spawn_timer = 1;
        for (i = 0; i < COUNT(shot_objects); i++)
            shot_objects[i].active = 1;
    }
    if (mode == 10) {
        fixture->obj.collision_flags = 0;
        fixture->obj.y_pos.i.hi = -100;
        fixture->obj.ext.main_72.unk84 = -1;
        fixture->obj.y_speed = -0x10000;
        fixture->obj.gravity = 0x4200;
    }
    g_Player.x_pos.i.hi = 100;
}

static const struct {
    void (*function)(struct MainObj*);
    u8 finished;
} animations[] = {
    { unused_ride_armor_jump, 0 },
    { unused_ride_armor_fall, 0 },
    { unused_ride_armor_land, 0 },
    { unused_ride_armor_land, 1 },
    { unused_ride_armor_shoot, 0 },
    { unused_ride_armor_land, 2 },
    { unused_ride_armor_shoot, 3 },
    { unused_ride_armor_shoot, 4 },
    { unused_ride_armor_shoot, 5 },
    { unused_ride_armor_fall, 6 },
    { unused_ride_armor_fall, 7 },
    { unused_ride_armor_fall, 8 },
    { unused_ride_armor_shoot, 9 },
    { unused_ride_armor_fall, 10 },
    { unused_ride_armor_rapid_fire, 0 },
    { unused_ride_armor_rapid_fire, 3 },
    { unused_ride_armor_rapid_fire, 4 },
    { unused_ride_armor_rapid_fire, 5 },
};

static u32 animation_run(u32 row)
{
    struct Fixture fixture;
    struct MainObj* obj = &fixture.obj;
    struct ShotObj* shot = &shot_objects[0];
    u32 hash;
    initialize(&fixture, animations[row].finished);
    animations[row].function(obj);
    assert(obj->animation_table == fixture.table);
    assert(obj->animation_cursor == (const u8*)(fixture.frames + (animations[row].finished == 2)));
    hash = (u8)obj->unk5 | ((u32)(u8)obj->unk6 << 8) | ((u32)C_TEST_PSX_FACING(obj->unk15) << 16) | ((u32)(u8)obj->air_state << 24);
    hash = hash * 31 + C_TEST_PSX_WORD(obj->animation_step.packed);
    hash = hash * 31 + obj->x_speed;
    hash = hash * 31 + obj->y_speed;
    hash = hash * 31 + obj->gravity;
    hash = hash * 31 + (obj->collision_flags | ((u32)obj->unk17 << 8) | ((u32)obj->previous_animation_index << 16));
    hash = hash * 31 + (obj->ext.main_72.lifetime | ((u32)obj->ext.main_72.spawn_timer << 8));
    hash = hash * 31 + obj->x_pos.val;
    hash = hash * 31 + obj->y_pos.val;
    hash = hash * 31 + ((u8)shot->active | ((u32)(u8)shot->id << 8) | ((u32)(u8)shot->unk2 << 16));
    hash = hash * 31 + ((shot->unk7C == obj) | ((u32)(shot->animation_table == obj->animation_table) << 1));
    return hash * 31 + (shot->x_pos.u.hi | ((u32)shot->y_pos.u.hi << 16));
}

struct unused_ride_armor_jump_case {
    u32 collision_flags, y_speed, obj_y_pos_hi, g_Player_y_pos_hi;
    u32 expected[7];
};
static const struct unused_ride_armor_jump_case unused_ride_armor_jump_cases[] = {
    { 4, 0, 0, 0, { 0u, 4u, 0u, 0u, 0u, 0u, 0u } },
    { 0, -1, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0xFFFFFFFFu } },
    { 0, 0, -28704, -28528, { 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, 0, 0, 0, { 0u, 0u, 0u, 0xFFFFFFFFu, 0u, 0u, 0u } },
};
static u32 test_unused_ride_armor_jump(u32 row)
{
    const struct unused_ride_armor_jump_case* c = &unused_ride_armor_jump_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk6 = -1;
    obj.collision_flags = c->collision_flags;
    obj.y_speed = c->y_speed;
    obj.y_pos.i.hi = c->obj_y_pos_hi;
    g_Player.y_pos.i.hi = c->g_Player_y_pos_hi;
    unused_ride_armor_jump(&obj);
    observed_values[0] = (u32)obj.air_state;
    observed_values[1] = (u32)obj.collision_flags;
    observed_values[2] = (u32)obj.gravity;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.x_accel;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

extern void* unused_ride_armor_animations[];
extern struct Unk_unk68 unused_ride_armor_hit_box;
extern struct Unk_unk68 unused_ride_armor_terrain_box;
void unused_ride_armor_main(struct MainObj*);
static const s16 screen_positions[][2] = { { 160, 120 }, { -65, 120 }, { 384, 120 }, { 160, -65 }, { 160, 304 } };
static u8 tilemap[256];
static u16 pixels[2][16][16];
static u32 attributes[1];
static struct WeaponObj weapons_expected[16];
static struct MiscObj misc_before[64];
static struct VisualObj visuals_before[32];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 root(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 hit = row % 3, edge = row / 3 % 5, facing = row / 15, i;
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = 0;
    SP_BG_TILEMAP = tilemap;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    memset(&g_Player, 0, sizeof(g_Player));
    SPIKE_IMMUNE_SET(g_Player, 1);
    player_before = g_Player;
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.val = background_objects[0].y_pos.val = 512 * 65536;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 39;
    }
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 72;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 9;
    obj.bg_offset = 0;
    obj.on_screen = 7;
    obj.unk15 = facing ? PLAYER_FACING_RIGHT : 0;
    obj.hp = hit == 2 ? 2 : 10;
    obj.x_pos.val = (screen_positions[edge][0] + 512) * 65536 + 0x1234;
    obj.y_pos.val = (screen_positions[edge][1] + 512) * 65536 + 0x5678;
    obj.unk18.val = 0x1234;
    obj.unk1C.val = 0x5678;
    obj.collision_flags = 15;
#ifndef VERSION_SATURN_PROTO
    obj.unk79 = 1;
#endif
    obj.hurt_box = &unused_ride_armor_hit_box;
    obj.attack_box = &unused_ride_armor_hit_box;
    obj.terrain_box = &unused_ride_armor_terrain_box;
    obj.collision_data = (const u16*)D_80108184;
    obj.animation_table = (const u8* const*)unused_ride_armor_animations;
    set_animation(&obj, 0);
    obj.unk42 = 0x9234;
    cur_random = 0x1234;
    D_8013E198[1] = -1;
    if (hit) {
        weapon_objects[15].active = 0x21;
        weapon_objects[15].id = 0;
        weapon_objects[15].unk15 = obj.unk15;
        weapon_objects[15].x_pos = obj.x_pos;
        weapon_objects[15].y_pos = obj.y_pos;
        weapon_objects[15].unk50 = (const u8*)&unused_ride_armor_hit_box;
    }
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk5 = 2;
    expected.unk6 = 0;
    expected.collision_flags = 0;
#ifndef VERSION_SATURN_PROTO
    expected.unk79 = 0;
#endif
    expected.unk6C = obj.x_pos.i.hi & 15;
    expected.unk6E = (obj.y_pos.i.hi + 48) & 15;
    expected.unk42 = 0x1234;
    if (hit) {
        expected.hp = hit == 2 ? 0 : 7;
        expected.unk42 = 0x9234;
        ((s16*)&weapons_expected[15].unk80)[0] = obj.x_pos.i.hi;
        ((s16*)&weapons_expected[15].unk80)[1] = obj.y_pos.i.hi + 8;
        weapons_expected[15].unk98 = 1;
        if (hit == 2) {
            expected.state = 2;
            expected.unk5 = 0;
        }
    }
    if (edge) {
        expected.state = 2;
        expected.unk5 = 0;
    } else
        expected.on_screen = 1;
    unused_ride_armor_main(&obj);
    SAME(obj, expected);
    SAME(g_Player, player_before);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(weapon_objects, weapons_expected);
    SAME(visual_objects, visuals_before);
    SAME(misc_objects, misc_before);
    assert(cur_random == 0x1234 && D_8013E198[1] == -1);
    return 1;
}

#include "support/state_cases.h"
void func_8008B020(struct MainObj*);
void func_8008B188(struct MainObj*);
void func_8008B4B8(struct MainObj*);
void func_8008B69C(struct MainObj*);
#define RA2(step, sub) (state_reset(step, sub, 0), so.active = 0x41, so.state = 1, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, g_Player.x_pos.i.hi = 0x200, g_Player.y_pos.i.hi = 0x60, cur_random = 0)
#define RA2X() (state_extra = so.ext.main_72.lifetime | so.ext.main_72.spawn_timer << 8 | (u32)(u16)so.ext.main_72.unk84 << 16)
#define IDLE(px, py, seed) (RA2(2, 1), g_Player.x_pos.i.hi = px, g_Player.y_pos.i.hi = py, cur_random = seed, func_8008B020(&so), RA2X())
static void ra2_idle_start(void)
{
    RA2(2, 0), cur_random = 5, func_8008B020(&so), RA2X();
}
static void ra2_idle_below_odd(void) { IDLE(0x70, 0xA0, 1); }
static void ra2_idle_below_even(void) { IDLE(0x90, 0xA0, 0); }
static void ra2_idle_near_odd(void) { IDLE(0x90, 0x60, 1); }
static void ra2_idle_near_even(void) { IDLE(0x70, 0x60, 0); }
static void ra2_idle_far_odd(void) { IDLE(0x200, 0x60, 1); }
static void ra2_idle_far_even(void) { IDLE(0x200, 0x60, 0); }
static void ra2_walk_start(void) { RA2(3, 0), so.animation_step.fields.event = 1, func_8008B188(&so), RA2X(); }
static void ra2_walk_left(void) { RA2(3, 1), so.ext.main_72.lifetime = 5, so.animation_step.fields.event = 1, func_8008B188(&so), RA2X(); }
static void ra2_walk_end_ground(void) { RA2(3, 1), so.ext.main_72.lifetime = 1, so.collision_flags = 8, func_8008B188(&so), RA2X(); }
static void ra2_walk_end_air(void) { RA2(3, 1), so.ext.main_72.lifetime = 1, func_8008B188(&so), RA2X(); }
static void ra2_dash_right(void) { RA2(6, 0), g_Player.x_pos.i.hi = 0xC0, func_8008B4B8(&so), RA2X(); }
static void ra2_dash_left(void) { RA2(6, 0), g_Player.x_pos.i.hi = 0x40, func_8008B4B8(&so), RA2X(); }
static void ra2_dash_end(void) { RA2(6, 1), so.ext.main_72.lifetime = 1, func_8008B4B8(&so), RA2X(); }
static void ra2_jump_shoot_land(void) { RA2(9, 0), so.collision_flags = 8, func_8008B69C(&so), RA2X(); }
static void ra2_jump_shoot_high(void) { RA2(9, 1), g_Player.y_pos.i.hi = 0x40, func_8008B69C(&so), RA2X(); }
#define DROP(speed, left, spawn) (RA2(9, 1), g_Player.y_pos.i.hi = 0xA0, so.y_speed = speed, so.gravity = 0x4200, so.air_state = 1, so.ext.main_72.lifetime = left, so.ext.main_72.spawn_timer = spawn, func_8008B69C(&so), RA2X(), state_extra ^= (u32)shot_objects[0].active << 4)
static void ra2_jump_shoot_fast(void)
{
    DROP(-0x70000, 5, 2);
}
static void ra2_jump_shoot_fall(void) { DROP(0, 5, 0x11); }
static void ra2_jump_shoot_done(void) { DROP(0, 1, 2); }
static void (*const ra2_cases[])(void) = {
    ra2_idle_start,
    ra2_idle_below_odd,
    ra2_idle_below_even,
    ra2_idle_near_odd,
    ra2_idle_near_even,
    ra2_idle_far_odd,
    ra2_idle_far_even,
    ra2_walk_start,
    ra2_walk_left,
    ra2_walk_end_ground,
    ra2_walk_end_air,
    ra2_dash_right,
    ra2_dash_left,
    ra2_dash_end,
    ra2_jump_shoot_land,
    ra2_jump_shoot_high,
    ra2_jump_shoot_fast,
    ra2_jump_shoot_fall,
    ra2_jump_shoot_done,
};
static const u32 ra2_expected[] = {
    0x1000102u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x4008u,
    0x0u,
    0x4u,
    0x41000000u,
    0x9u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0xAu,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x8u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x6u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x8u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x3u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x103u,
    0x0u,
    0x816000u,
    0x16000u,
    0x0u,
    0x0u,
    0x4008u,
    0x0u,
    0x160003Fu,
    0x41000000u,
    0x103u,
    0x0u,
    0x7EA000u,
    0xFFFEA000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x4u,
    0x41000000u,
    0x5u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x106u,
    0x0u,
    0x842000u,
    0x42000u,
    0x0u,
    0x0u,
    0x4007u,
    0x0u,
    0x420000Fu,
    0x41000000u,
    0x106u,
    0x0u,
    0x7BE000u,
    0xFFFBE000u,
    0x0u,
    0x0u,
    0x7u,
    0x0u,
    0x420000Fu,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x1000005u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x420000u,
    0x4003u,
    0x0u,
    0x0u,
    0x41000000u,
    0x2u,
    0x0u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x41000000u,
    0x1000109u,
    0x0u,
    0x800000u,
    0x0u,
    0xFFF9DE00u,
    0x420000u,
    0x0u,
    0x0u,
    0x514u,
    0x41410000u,
    0x1000109u,
    0x0u,
    0x800000u,
    0x0u,
    0xFFFFBE00u,
    0x420000u,
    0x0u,
    0x0u,
    0x1004u,
    0x41000000u,
    0x1000002u,
    0x0u,
    0x800000u,
    0x0u,
    0xFFFFBE00u,
    0x420000u,
    0x0u,
    0x0u,
    0x200u,
    0x41000000u,
};
static u32 ra2_run(u32 row)
{
    return state_run(ra2_cases[row], row, &ra2_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "unused_ride_armor_branch_steps", 0, 0, COUNT(ra2_cases), ra2_run },
    { "ride_armor_animation", NULL, NULL, COUNT(animations), animation_run },
    { "unused_ride_armor_jump", 0, 0, 4, test_unused_ride_armor_jump },
    { "root_real_weapon_hits_and_bounds", NULL, NULL, 30, root },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ra2_cases) + COUNT(animations) + 4 + 30;
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
