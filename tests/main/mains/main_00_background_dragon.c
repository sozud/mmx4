#include "test_runtime.h"
#include "main/mains/main_00_background_dragon.h"
#include "main/55C4.h"
#include "main/tile_effects.h"
void background_dragon_attach_to_background(struct MainObj*);
void background_dragon_fireball(struct MainObj*);
void background_dragon_noop(struct MainObj*);
void background_dragon_reset(struct MainObj*);
extern u8 background_dragon_attack_map[128];
void background_dragon_spawn_trail(struct PlayerObj*, s8);
void background_dragon_multi_shot_update(struct MainObj*);

static struct DragonInput {
    s16 index;
    u16 seed;
    u8 raw_kind;
};
static const struct DragonInput inputs[] = {
    { -1, 0, 0 },
    { 32, 3, 0 },
    { 104, 3, 0 },
    { 0, 1, 9 },
    { 0, 2, 9 },
    { 0, 3, 9 },
};
static u32 dragon_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u8 map_before[128];
    u8* ext;
    const struct DragonInput* input = &inputs[mode];
    s32 choice;
    u32 i, hash = 2166136261U;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.state = 1;
    obj.unk2 = 0x27;
    obj.x_pos.val = (input->index < 0 ? 100 : (80 + input->index) * 16) * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.x_pos = obj.x_pos;
    cur_random = input->seed;
    memcpy(map_before, background_dragon_attack_map, sizeof(map_before));
    assert(map_before[32] == 0 && map_before[104] == 8);
    if (input->raw_kind)
        background_dragon_attack_map[input->index] = input->raw_kind;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    choice = func_80040ABC(&obj);
    ext = (u8*)&obj.ext;
    before.unk2 = obj.unk2;
    ((u8*)&before.ext)[1] = ext[1];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < COUNT(map_before); i++) {
        assert(background_dragon_attack_map[i] == (input->raw_kind && i == input->index ? input->raw_kind : map_before[i]));
        background_dragon_attack_map[i] = map_before[i];
        hash = (hash ^ background_dragon_attack_map[i]) * 16777619U;
    }
    if (observation == 0)
        return choice;
    if (observation == 1)
        return (u8)obj.unk2 | ((u32)ext[1] << 8);
    if (observation == 2)
        return cur_random;
    return hash;
}
static const u32 dragon_attack_context_cases_expected[] = { 0xCu, 0x0u, 0x0u, 0x13D3C53Eu, 0x5u, 0x1u, 0x3u, 0x13D3C53Eu, 0xCu, 0x1u, 0x3u, 0x13D3C53Eu, 0x3u, 0x301u, 0x1u, 0x13D3C53Eu, 0x5u, 0x0u, 0x2u, 0x13D3C53Eu, 0x2u, 0x1u, 0x3u, 0x13D3C53Eu };
static u32 dragon_attack_context_cases_row(u32 row)
{
    return dragon_case(row / 4, row % 4);
}

static const u32 background_dragon_spawn_trail_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_background_dragon_spawn_trail(u32 row)
{
    u32 observed_values[9];
    struct PlayerObj obj;
    u8 pool_0_full;
    s8 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&visual_objects, 0, sizeof(visual_objects));
    pool_0_full = 255;
    arg1 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            visual_objects[slot].active = pool_0_full ? 1 : 0;
    }
    background_dragon_spawn_trail(&obj, arg1);
    observed_values[0] = (u32)visual_objects[0].active;
    observed_values[1] = (u32)visual_objects[0].id;
    observed_values[2] = (u32)visual_objects[0].state;
    observed_values[3] = (u32)visual_objects[0].unk16;
    observed_values[4] = (u32)visual_objects[0].unk2;
    observed_values[5] = (u32)visual_objects[0].unk40;
    observed_values[6] = (u32)visual_objects[0].unk42;
    observed_values[7] = (u32)visual_objects[0].unk5;
    observed_values[8] = (u32)visual_objects[0].unk6;
    return c_test_observe(0, row, observed_values, background_dragon_spawn_trail_expected, 9);
}

#include "support/pool_full.h"

static u32 pool_full_background_dragon_visual(void)
{
    u32 actual;
    pf_prepare();
    pf_event(1, 1);
    pf_snapshot();
    background_dragon_multi_shot_update(&pf_self);
    pf_expected.animation_step.fields.event = 0;
    pf_animated();
    pf_expected.on_screen = 1;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_background_dragon_shot(void)
{
    u32 actual;
    pf_prepare();
    pf_event(2, 1);
    pf_snapshot();
    background_dragon_multi_shot_update(&pf_self);
    pf_expected.animation_step.fields.event = 0;
    pf_animated();
    pf_expected.on_screen = 1;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_background_dragon_visual,
    pool_full_background_dragon_shot,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u };
#include "support/state_cases.h"

void background_dragon_projectile_attack_update(struct MainObj*);
s32 func_80040ABC(struct MainObj*);
void func_80040838(struct MainObj*);
void func_80041060(struct MainObj*);
void func_800415B0(struct MainObj*);
#define DRAGON(step) (state_reset(step, 0, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60)
#define DRAGON_EXT() (state_extra = ((u8*)&so.ext)[1] | ((u8*)&so.ext)[2] << 8 | ((u8*)&so.ext)[5] << 16 | (u32)((u8*)&so.ext)[6] << 24)
static s32 dragon_pick(s32 index, u16 seed)
{
    DRAGON(0);
    so.x_pos.i.hi = (index + 0x50) << 4;
    g_Player.x_pos.i.hi = so.x_pos.i.hi;
    cur_random = seed;
    return func_80040ABC(&so);
}
static void bd_main_calm(void)
{
    DRAGON(11);
    so.hp = 0x20;
    cur_random = 1;
    func_80040838(&so);
    DRAGON_EXT();
}
static void bd_main_flag(void)
{
    DRAGON(11);
    so.hp = 0x20;
    engine_obj.character_state.bytes[0] = 1;
    cur_random = 1;
    func_80040838(&so);
    DRAGON_EXT();
}
static void bd_main_hit(void)
{
    DRAGON(11);
    so.hp = 0x30;
    state_hit(&so, 0, 0, 1);
    cur_random = 1;
    func_80040838(&so);
    DRAGON_EXT();
}
static void bd_main_defeated(void)
{
    DRAGON(11);
    so.hp = 1;
    state_hit(&so, 0, 0, 1);
    func_80040838(&so);
    DRAGON_EXT();
}
static void bd_main_flash_on(void)
{
    DRAGON(11);
    so.hp = 0x20;
    so.invincibility_timer = 3;
    cur_random = 1;
    func_80040838(&so);
}
static void bd_main_flash_end(void)
{
    DRAGON(11);
    so.hp = 0x20;
    so.invincibility_timer = 1;
    so.unk42 = 0x8000;
    cur_random = 1;
    func_80040838(&so);
}
static void bd_main_burning_a(void)
{
    DRAGON(11);
    so.hp = 0x20;
    ((u8*)&so.ext)[5] = 2;
    cur_random = 1;
    func_80040838(&so);
    DRAGON_EXT();
}
static void bd_main_burning_b(void)
{
    DRAGON(11);
    so.hp = 0x20;
    ((u8*)&so.ext)[5] = 2;
    so.unk15 = 0x40;
    cur_random = 2;
    func_80040838(&so);
    DRAGON_EXT();
}
static void bd_main_burning_flip(void)
{
    DRAGON(11);
    so.hp = 0x20;
    ((u8*)&so.ext)[5] = 2;
    cur_random = 3;
    func_80040838(&so);
    DRAGON_EXT();
}
static void bd_main_weak_blink(void)
{
    DRAGON(11);
    so.hp = 0x10;
    cur_random = 2;
    func_80040838(&so);
    DRAGON_EXT();
}
static void bd_main_weak_wait(void)
{
    DRAGON(11);
    so.hp = 0x10;
    ((u8*)&so.ext)[6] = 3;
    cur_random = 2;
    func_80040838(&so);
    DRAGON_EXT();
}
static void bd_fire_begin_late(void)
{
    DRAGON(2);
    so.x_pos.i.hi = 0xCA0;
    background_dragon_fireball(&so);
}
static void bd_fire_begin_turn(void)
{
    DRAGON(2);
    so.x_pos.i.hi = 0xC50;
    background_dragon_fireball(&so);
}
static void bd_fire_begin(void)
{
    DRAGON(2);
    so.x_pos.i.hi = 0xC00;
    background_dragon_fireball(&so);
}
static void bd_fire_breath(void)
{
    DRAGON(2);
    so.unk6 = 1;
    so.animation_step.fields.event = 1;
    background_dragon_fireball(&so);
}
static void bd_fire_breath_right(void)
{
    DRAGON(2);
    so.unk6 = 1;
    so.unk15 = 0x40;
    so.animation_step.fields.event = 1;
    background_dragon_fireball(&so);
}
static void bd_fire_done(void)
{
    DRAGON(2);
    so.unk6 = 1;
    so.animation_step.fields.relative_step = -1;
    background_dragon_fireball(&so);
}
static void bd_spit(void)
{
    DRAGON(3);
    so.animation_step.fields.event = 1;
    background_dragon_projectile_attack_update(&so);
}
static void bd_spit_right(void)
{
    DRAGON(3);
    so.unk15 = 0x40;
    so.animation_step.fields.event = 1;
    background_dragon_projectile_attack_update(&so);
}
static void bd_spit_hold(void)
{
    DRAGON(3);
    so.animation_step.fields.event = 3;
    so.x_speed = 0x10000;
    background_dragon_projectile_attack_update(&so);
}
static void bd_spit_wall_done(void)
{
    DRAGON(3);
    so.animation_step.fields.event = 2;
    so.ext.main_0.index = 3;
    background_dragon_projectile_attack_update(&so);
}
static void bd_spit_done(void)
{
    DRAGON(3);
    so.animation_step.fields.relative_step = -1;
    background_dragon_projectile_attack_update(&so);
}
static void bd_pick_hurt(void)
{
    DRAGON(0);
    ((u8*)&so.ext)[5] = 1;
    state_extra = func_80040ABC(&so);
}
static void bd_pick_far(void)
{
    DRAGON(0);
    so.x_pos.i.hi = 0x400;
    state_extra = func_80040ABC(&so);
}
static void bd_pick_early(void)
{
    DRAGON(0);
    so.x_pos.i.hi = 0x100;
    g_Player.x_pos.i.hi = 0x100;
    state_extra = func_80040ABC(&so);
}
static void bd_pick_open_a(void)
{
    state_extra = dragon_pick(32, 1);
    DRAGON_EXT();
}
static void bd_pick_open_b(void) { state_extra = dragon_pick(32, 2) | ((u8*)&so.ext)[1] << 8; }
static void bd_pick_open_c(void) { state_extra = dragon_pick(32, 3) | ((u8*)&so.ext)[1] << 8; }
static void bd_pick_open_d(void) { state_extra = dragon_pick(33, 4) | ((u8*)&so.ext)[1] << 8; }
static void bd_pick_wall_one(void) { state_extra = dragon_pick(23, 1) | ((u8*)&so.ext)[1] << 8; }
static void bd_pick_wall_two(void)
{
    DRAGON(0);
    so.x_pos.i.hi = (55 + 0x50) << 4;
    g_Player.x_pos.i.hi = so.x_pos.i.hi;
    ((u8*)&so.ext)[3] = 1;
    state_extra = func_80040ABC(&so) | ((u8*)&so.ext)[1] << 8;
}
static void bd_pick_wall_three(void) { state_extra = dragon_pick(87, 1) | ((u8*)&so.ext)[1] << 8; }
static void bd_pick_spit(void) { state_extra = dragon_pick(34, 1); }
static void bd_pick_burst(void) { state_extra = dragon_pick(0, 1); }
static void bd_pick_mixed_a(void) { state_extra = dragon_pick(97, 1) | ((u8*)&so.ext)[1] << 8; }
static void bd_pick_mixed_b(void) { state_extra = dragon_pick(98, 2) | ((u8*)&so.ext)[1] << 8; }
static void bd_pick_mixed_c(void) { state_extra = dragon_pick(99, 3) | ((u8*)&so.ext)[1] << 8; }
static void bd_pick_end_a(void) { state_extra = dragon_pick(104, 1); }
static void bd_pick_end_b(void) { state_extra = dragon_pick(105, 2); }
static void bd_pick_end_c(void) { state_extra = dragon_pick(106, 3); }
static void bd_pick_end_d(void) { state_extra = dragon_pick(107, 4); }
static void bd_attach(void)
{
    DRAGON(10);
    so.unk2 = 1;
    background_dragon_attach_to_background(&so);
}
static void bd_reset(void)
{
    DRAGON(0);
    background_dragon_reset(&so);
}
static void bd_noop(void)
{
    DRAGON(11);
    background_dragon_noop(&so);
}

static void (*const background_dragon_states_cases[])(void) = {
    bd_main_calm,
    bd_main_flag,
    bd_main_hit,
    bd_main_defeated,
    bd_main_flash_on,
    bd_main_flash_end,
    bd_main_burning_a,
    bd_main_burning_b,
    bd_main_burning_flip,
    bd_main_weak_blink,
    bd_main_weak_wait,
    bd_fire_begin_late,
    bd_fire_begin_turn,
    bd_fire_begin,
    bd_fire_breath,
    bd_fire_breath_right,
    bd_fire_done,
    bd_spit,
    bd_spit_right,
    bd_spit_hold,
    bd_spit_wall_done,
    bd_spit_done,
    bd_pick_hurt,
    bd_pick_far,
    bd_pick_early,
    bd_pick_open_a,
    bd_pick_open_b,
    bd_pick_open_c,
    bd_pick_open_d,
    bd_pick_wall_one,
    bd_pick_wall_two,
    bd_pick_wall_three,
    bd_pick_spit,
    bd_pick_burst,
    bd_pick_mixed_a,
    bd_pick_mixed_b,
    bd_pick_mixed_c,
    bd_pick_end_a,
    bd_pick_end_b,
    bd_pick_end_c,
    bd_pick_end_d,
    bd_attach,
    bd_reset,
    bd_noop,
};
static const u32 background_dragon_states_expected[] = { 0xB00u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xB00u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x10000u, 0u, 0xB00u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0x2100u, 0xB00u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x20000u, 0x2100u, 0xB00u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 0xB00u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xB00u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x4020000u, 0u, 0xB00u, 0x400000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x4020000u, 0x2100u, 0xB00u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x4020000u, 0u, 0xB00u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x58000u, 0x1E000000u, 0u, 0xB00u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2000000u, 0u, 0xC00u, 0xFF000000u, 0xCA00000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10200u, 0xFF400000u, 0xC500000u, 0x1700000u, 0x10000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10200u, 0xFF000000u, 0xC000000u, 0x1700000u, 0xFFFF0000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10200u, 0u, 0x800000u, 0x600000u, 0u, 0xFFFFC000u, 0u, 0x40000u, 0u, 0x41410000u, 0x10200u, 0x400000u, 0x800000u, 0x600000u, 0u, 0xFFFFC000u, 0u, 0x40000u, 0u, 0x41410000u, 0xC00u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x300u, 0u, 0x800000u, 0x600000u, 0x3C000u, 0xFFFF0000u, 0u, 0x40000u, 0u, 0x410000u, 0x300u, 0x400000u, 0x800000u, 0x600000u, 0xFFFC4000u, 0xFFFF0000u, 0u, 0x40000u, 0u, 0x410000u, 0x300u, 0u, 0x800000u, 0x600000u, 0x10000u, 0u, 0u, 0x40000u, 0u, 0u, 0x300u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0xC00u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 8u, 0u, 0u, 0u, 0x4000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 6u, 0u, 0u, 0u, 0x1000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0xCu, 0u, 0u, 0x100u, 0x7000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 3u, 0u, 0u, 0u, 0x7000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 0u, 0x100u, 0x7000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 5u, 0u, 0u, 0u, 0x7100000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0xCu, 0u, 0u, 0x100u, 0x6700000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 3u, 0u, 0u, 0u, 0x8700000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 0u, 0x100u, 0xA700000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x203u, 0u, 0u, 0x100u, 0x7200000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 0u, 0x100u, 0x5000000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 5u, 0u, 0u, 0x100u, 0xB100000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x303u, 0u, 0u, 0u, 0xB200000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 5u, 0u, 0u, 0x100u, 0xB300000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 0u, 0x100u, 0xB800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 0u, 0u, 0xB900000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 2u, 0u, 0u, 0x100u, 0xBA00000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0xCu, 0u, 0u, 0u, 0xBB00000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 8u, 0u, 0x600u, 0xFF000100u, 0xFF800000u, 0x1700000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xC00u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0xB00u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u };

static u32 test_background_dragon_states(u32 row)
{
    return object_run(background_dragon_states_cases[row], row, &background_dragon_states_expected[row * 10]);
}

#define SPIT(ev, rel) (DRAGON(5), so.animation_step.fields.event = ev, so.animation_step.fields.relative_step = rel, so.x_speed = 0x10000, background_dragon_projectile_attack_update(&so), so.unk7E = shot_objects[0].id | shot_objects[0].unk2 << 8)
#define GLIDE(idx, x, y, facing) (DRAGON(6), so.ext.main_0.index = idx, so.x_pos.i.hi = x, so.y_pos.i.hi = y, so.unk15 = facing, func_80041060(&so))
#define SWOOP(character, facing, x, y, rage)                                                       \
    do {                                                                                           \
        u8 who = engine_obj.cur_character;                                                         \
        DRAGON(7);                                                                                 \
        engine_obj.cur_character = character;                                                      \
        so.unk15 = facing;                                                                         \
        so.unk7E = rage;                                                                           \
        g_Player.x_pos.i.hi = 0x400;                                                               \
        so.x_pos.i.hi = x;                                                                         \
        so.y_pos.i.hi = y;                                                                         \
        func_800415B0(&so);                                                                        \
        state_extra = misc_objects[0].unk2 | misc_objects[1].unk2 << 8 | misc_objects[1].id << 16; \
        engine_obj.cur_character = who;                                                            \
    } while (0)
static void dg_spit_glide(void)
{
    SPIT(0, 1);
}
static void dg_spit_hold(void) { SPIT(3, 1); }
static void dg_spit_fire(void) { SPIT(1, 1); }
static void dg_spit_fire_left(void)
{
    DRAGON(5);
    so.unk15 = 0x40;
    so.animation_step.fields.event = 1;
    so.animation_step.fields.relative_step = 1;
    background_dragon_projectile_attack_update(&so);
}
static void dg_spit_crash_done(void)
{
    u8 seen = engine_obj.character_state.bytes[1];
    DRAGON(5);
    engine_obj.character_state.bytes[1] = 1;
    so.animation_step.fields.event = 2;
    so.animation_step.fields.relative_step = 1;
    background_dragon_projectile_attack_update(&so);
    engine_obj.character_state.bytes[1] = seen;
}
static void dg_spit_crash_last(void)
{
    DRAGON(5);
    so.ext.main_0.index = 3;
    so.animation_step.fields.event = 2;
    so.animation_step.fields.relative_step = 1;
    background_dragon_projectile_attack_update(&so);
}
static void dg_spit_end(void) { SPIT(0, -1); }
static void dg_glide_center(void) { GLIDE(3, 0x400, 0x100, 0); }
static void dg_glide_center_right(void) { GLIDE(3, 0x400, 0x100, 0x40); }
static void dg_glide_arrive(void) { GLIDE(0, 0x6A1, 0x171, 0); }
static void dg_glide_arrive_right(void) { GLIDE(0, 0x6A0, 0x170, 0x40); }
static void dg_glide_low(void) { GLIDE(0, 0x6A0, 0x100, 0); }
static void dg_glide_far(void) { GLIDE(1, 0x600, 0x170, 0); }
static void dg_swoop_x(void) { SWOOP(0, 0, 0x300, 0x200, 0); }
static void dg_swoop_zero(void) { SWOOP(1, 0x40, 0x300, 0x200, 0); }
static void dg_swoop_land(void) { SWOOP(0, 0, 0x3B8, 0x214, 0); }
static void dg_swoop_land_rage(void) { SWOOP(1, 0x40, 0x44A, 0x214, 1); }
static void dg_swoop_high(void) { SWOOP(0, 0, 0x3B8, 0x100, 0); }

static void (*const background_dragon_attacks_cases[])(void) = {
    dg_spit_glide,
    dg_spit_hold,
    dg_spit_fire,
    dg_spit_fire_left,
    dg_spit_crash_done,
    dg_spit_crash_last,
    dg_spit_end,
    dg_glide_center,
    dg_glide_center_right,
    dg_glide_arrive,
    dg_glide_arrive_right,
    dg_glide_low,
    dg_glide_far,
    dg_swoop_x,
    dg_swoop_zero,
    dg_swoop_land,
    dg_swoop_land_rage,
    dg_swoop_high,
};
static const u32 background_dragon_attacks_expected[] = { 0x500u, 0u, 0x810000u, 0x600000u, 0x10000u, 0u, 0u, 0x40000u, 0u, 0u, 0x500u, 0u, 0x800000u, 0x600000u, 0x10000u, 0u, 0u, 0x40000u, 0u, 0u, 0x500u, 0u, 0x810000u, 0x600000u, 0x3C000u, 0xFFFF0000u, 0u, 0x40000u, 0u, 0x410000u, 0x500u, 0x400000u, 0x800000u, 0x600000u, 0xFFFC4000u, 0xFFFF0000u, 0u, 0x40000u, 0u, 0x410000u, 0x500u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x500u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0xC00u, 0xFF000000u, 0x810000u, 0x600000u, 0x10000u, 0u, 0u, 0x50000u, 0u, 0u, 0x10600u, 0xFF000000u, 0x4000000u, 0x1700000u, 0xFFFF4000u, 0x8000u, 0u, 0x50000u, 0u, 0u, 0x10600u, 0xFF400000u, 0x4000000u, 0x1700000u, 0xC000u, 0x8000u, 0u, 0x50000u, 0u, 0u, 0x10600u, 0xFF000000u, 0x6A10000u, 0x1700000u, 0xFFFF4000u, 0x8000u, 0u, 0x50000u, 0u, 0u, 0x10600u, 0xFF000000u, 0x6A00000u, 0x1700000u, 0xFFFF4000u, 0x8000u, 0u, 0x50000u, 0u, 0u, 0x600u, 0u, 0x6A00000u, 0x1020000u, 0u, 0xFFFE0000u, 0u, 0x40000u, 0u, 0u, 0x600u, 0u, 0x6020000u, 0x1700000u, 0x20000u, 0u, 0u, 0x40000u, 0u, 0u, 0x700u, 0u, 0x303EC50u, 0x200C7C4u, 0x3EC50u, 0xFFFF383Cu, 0u, 0x40000u, 0u, 0u, 0x700u, 0x400000u, 0x3040000u, 0x2000000u, 0x40000u, 0u, 0u, 0x40000u, 0u, 0u, 0x10700u, 0xFF000000u, 0x3B80000u, 0x2140000u, 0u, 0u, 0u, 0x50000u, 0x40100u, 0x41410000u, 0x10700u, 0xFF400000u, 0x44A0000u, 0x2140000u, 0u, 0u, 0u, 0x50000u, 0x40100u, 0x41410000u, 0x700u, 0u, 0x3B80000u, 0x1040000u, 0u, 0xFFFC0000u, 0u, 0x40000u, 0u, 0u };

static u32 test_background_dragon_attacks(u32 row)
{
    return object_run(background_dragon_attacks_cases[row], row, &background_dragon_attacks_expected[row * 10]);
}

extern s32 background_dragon_perch_points[][2];
extern struct FixedPointPosition background_dragon_route_starts[];
void background_dragon_fly_offscreen(struct MainObj*);
void background_dragon_fly_to_route_start(struct MainObj*);
void background_dragon_fly_to_staging_position(struct MainObj*);
extern union AnimationStep* D_800F9934[16];
static const struct {
    s32 dx, dy, vx, vy;
} paths[] = {
    { 0x10000, 0, -65536, 0 },
    { -0x10000, 0, 65536, 0 },
    { 0x20000, 0, -65536, 0 },
    { -0x20000, 0, 65536, 0 },
    { 0x40000, 0, -65536, 0 },
    { -0x40000, 0, 65536, 0 },
    { 0, 0x10000, 0, 65536 },
    { 0, -0x10000, 0, -65536 },
    { 0, 0x40000, 0, 65536 },
    { 0, -0x40000, 0, -65536 },
    { 0x10000, 0x10000, -0xB505, 0xB505 },
    { -0x10000, 0x10000, 0xB505, 0xB505 },
    { 0x10000, -0x10000, -0xB505, -0xB505 },
    { -0x10000, -0x10000, 0xB505, -0xB505 },
    { 0, 0, -65536, 0 },
    { 0x3FFFF, 0, -65536, 0 },
    { 0x40001, 0, -65536, 0 },
    { 0, -0x3FFFF, 0, -65536 },
    { 0, -0x40001, 0, -65536 },
};
static const s32 perch[2][2] = { { 40 * 65536, 179 * 65536 }, { 280 * 65536, 179 * 65536 } };
static const s32 starts[2][2] = { { -128 * 65536, 179 * 65536 }, { -128 * 65536, 368 * 65536 } };
static struct MainObj obj, expected;
static struct BackgroundObj backgrounds_before[3];
static struct PlayerObj player_before;
static struct EngineObj engine_before;
static void prepare(u32 path, u32 kind, s32 target_x, s32 target_y, s32 camera_x, s32 camera_y, u32 last_tick)
{
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.val = camera_x;
    background_objects[0].y_pos.val = camera_y;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    player_before = g_Player;
    engine_before = engine_obj;
    for (i = 0; i < 2; i++) {
        assert(background_dragon_perch_points[i][0] == perch[i][0] && background_dragon_perch_points[i][1] == perch[i][1]);
        assert(background_dragon_route_starts[i].x == starts[i][0] && background_dragon_route_starts[i].y == starts[i][1]);
    }
    obj.active = 0x41;
    obj.state = 1;
    obj.unk2 = kind;
    obj.on_screen = 1;
    obj.bg_offset = 0;
    obj.unk15 = kind & 1 ? 0x40 : 0;
    obj.unk16 = 9;
    obj.x_pos.val = target_x + paths[path].dx;
    obj.y_pos.val = target_y + paths[path].dy;
    obj.unk18.val = 0x12345678;
    obj.unk1C.val = 0x23456789;
    obj.x_speed = 0x13579;
    obj.y_speed = -0x2468;
    obj.ext.main_0.background_relative = 1;
    obj.animation_table = (const u8* const*)D_800F9934;
    set_animation(&obj, 6);
    assert(obj.animation_step.packed == 0x19010008);
    if (last_tick)
        obj.animation_step.fields.duration = 1;
    obj.previous_animation_index = 0x35;
}
static void expect_motion(u32 path, u32 scale, u32 last_tick)
{
    expected = obj;
    expected.x_speed = paths[path].vx * scale;
    expected.y_speed = paths[path].vy * scale;
    expected.x_pos.val += expected.x_speed;
    expected.y_pos.val -= expected.y_speed;
    if (last_tick) {
        expected.animation_cursor = (const u8*)(D_800F9934[6] + 1);
        expected.animation_step.packed = 0x1A010008;
    } else
        expected.animation_step.fields.duration = 7;
}
static u32 check(void)
{
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}
static u32 approach(u32 row)
{
    u32 path = row % COUNT(paths), kind = path % 4, tick = row / COUNT(paths);
    s32 x = perch[kind / 2][0], y = perch[kind / 2][1], dx, dy;
    prepare(path, kind, x, y, x - 160 * 65536, y - 120 * 65536, tick);
    obj.unk5 = 7;
    expect_motion(path, 2, tick);
    dx = expected.x_pos.val - x;
    dy = expected.y_pos.val - y;
    if (dx > -131072 && dx < 131072 && dy > -131072 && dy < 131072)
        expected.unk5 = 1;
    expected.on_screen = 1;
    background_dragon_fly_to_route_start(&obj);
    return check();
}
static u32 depart(u32 row, u32 staging)
{
    u32 path = row % COUNT(paths), tick = row / COUNT(paths), visible = (path + tick) % 2, exit_mode = (path + tick) % 3;
    u32 kind = (path + exit_mode + tick) % 2;
    s32 x = staging ? starts[kind][0] : -256 * 65536, y = staging ? starts[kind][1] : (kind ? 496 : -256) * 65536;
    prepare(path, kind, x, y, staging ? x - 160 * 65536 : 0, staging ? y - 120 * 65536 : 0, tick);
    obj.unk5 = staging ? 9 : 8;
    obj.on_screen = visible;
    obj.ext.main_0.exit_mode = exit_mode;
    expect_motion(path, staging ? 1 : exit_mode == 2 ? 2
                                                     : 4,
        tick);
    if (!visible && exit_mode)
        expected.state = 2;
    else {
        expected.on_screen = staging ? 1 : 0;
        if (!visible) {
            expected.unk15 = 0;
            expected.unk16 = staging ? 0x22 : 0x12;
            expected.unk5 = staging ? 10 : 7;
            if (!staging) {
                expected.bg_offset = -1;
                expected.x_pos.val = starts[kind][0];
                expected.y_pos.val = starts[kind][1];
                expected.ext.main_0.background_relative = 0;
                expected.on_screen = 1;
                expected.unk17 = 6;
                expected.previous_animation_index = 0xFF;
                expected.animation_cursor = (const u8*)D_800F9934[6];
                expected.animation_step.packed = 0x19010008;
            }
        }
    }
    if (staging)
        background_dragon_fly_to_staging_position(&obj);
    else
        background_dragon_fly_offscreen(&obj);
    return check();
}
static u32 offscreen(u32 row) { return depart(row, 0); }
static u32 staging(u32 row) { return depart(row, 1); }

void background_dragon_fireball(struct MainObj*);
void background_dragon_projectile_attack(struct MainObj*);
extern union AnimationStep* D_800F9934[16];
static struct ShotObj shots_expected[32];
static struct MiscObj misc_expected[64];
static u32 attack(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 fireball = row % 2, free_shot = row / 2 % 2, free_misc = row / 4 % 2, face = row / 8, i, anim = fireball ? 3 : 1, step = fireball ? 4 : 5;
    memset(&obj, 0, sizeof(obj));
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = i == 31 && free_shot ? 0 : 1;
        shot_objects[i].id = 63;
        shot_objects[i].unk2 = 9;
        shot_objects[i].state = 5;
        shot_objects[i].unk5 = 3;
        shot_objects[i].unk6 = 2;
        shot_objects[i].x_pos.val = 0x12345678;
    }
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i == 63 && free_misc ? 0 : 1;
        misc_objects[i].id = 63;
        misc_objects[i].unk2 = 9;
        misc_objects[i].state = 5;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 2;
        misc_objects[i].x_pos.val = 0x23456789;
    }
    c_test_copy_words((u32*)shots_expected, (u32*)shot_objects, sizeof(shots_expected) / 4);
    c_test_copy_words((u32*)misc_expected, (u32*)misc_objects, sizeof(misc_expected) / 4);
    obj.active = 0x41;
    obj.id = 0;
    obj.state = 1;
    obj.unk5 = fireball ? 2 : 3;
    obj.unk6 = 1;
    obj.unk15 = face ? 0x40 : 0;
    obj.bg_offset = 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_speed = face ? 65536 : -65536;
    obj.y_speed = -0x8000;
    obj.animation_table = (const u8* const*)D_800F9934;
    set_animation_frame(ANIMATED_OBJECT(&obj), anim, step);
    assert(obj.animation_step.packed == (fireball ? 0x0E010019 : 0x0601030F));
    obj.animation_step.fields.duration = 1;
    expected = obj;
    expected.animation_cursor += 4;
    expected.animation_step.packed = fireball ? 0x0F010002 : 0x07010102;
    expected.animation_step.fields.event = 0;
    expected.x_pos.val += obj.x_speed;
    expected.y_pos.val -= obj.y_speed;
    if (fireball) {
        expected.x_speed = 0;
        expected.y_speed = -0x4000;
    } else {
        expected.x_speed = face ? -0x3C000 : 0x3C000;
        expected.y_speed = -65536;
    }
    expected.on_screen = 1;
    if (free_shot) {
        struct ShotObj* s = &shots_expected[31];
        s->active = 0x41;
        s->id = 0;
        s->unk7C = (struct WeaponObj*)&obj;
        s->state = s->unk5 = s->unk6 = 0;
        s->unk2 = fireball;
    }
    if (fireball && free_misc) {
        struct MiscObj* m = &misc_expected[63];
        m->active = 0x41;
        m->id = 4;
        m->unk2 = 3;
        m->ext.ready_text.owner = (struct EffectObj*)&obj;
        m->state = 0;
        m->x_pos.val = expected.x_pos.val + (face ? -60 : 60) * 65536;
        m->y_pos.val = expected.y_pos.val + 68 * 65536;
    }
    D_8013E198[2] = -1;
    cur_random = 0x1234;
    if (fireball)
        background_dragon_fireball(&obj);
    else
        background_dragon_projectile_attack(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((u32*)shot_objects, (u32*)shots_expected, sizeof(shots_expected) / 4) == 0 && c_test_word_difference((u32*)misc_objects, (u32*)misc_expected, sizeof(misc_expected) / 4) == 0 && cur_random == 0x1234);
    return 1;
}

void background_dragon_sequence_begin(struct MainObj*);
extern union AnimationStep* D_800F9934[16];
static struct ShotObj shots_expected_dragon_swoop_capacity[32];
static struct MiscObj misc_expected_dragon_swoop_capacity[64];
static u32 swoop(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    u32 available = row % 3, shot_free = row / 3 % 2, character = row / 6 % 2, cycle = row / 12, i, animation = cycle ? 13 : 15;
    engine_obj.stage = engine_obj.substage = 0;
    engine_obj.cur_character = character;
    engine_before = engine_obj;
    g_Player.x_pos.i.hi = 1765;
    g_Player.x_pos.u.lo = 0;
    player_before = g_Player;
    background_objects[0].x_pos.val = 1605 << 16;
    background_objects[0].y_pos.val = 400 << 16;
    background_before = background_objects[0];
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = i == 31 && shot_free ? 0 : 1;
    memcpy(shots_expected_dragon_swoop_capacity, shot_objects, sizeof(shots_expected_dragon_swoop_capacity));
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = i >= 64 - available ? 0 : 1;
    memcpy(misc_expected_dragon_swoop_capacity, misc_objects, sizeof(misc_expected_dragon_swoop_capacity));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 0;
    obj.state = 1;
    obj.hp = 48;
    obj.unk5 = 5;
    obj.unk7E = cycle;
    obj.x_pos.val = g_Player.x_pos.val - (character ? 0x4A0000 : 0x480000);
    obj.y_pos.i.hi = 532;
    obj.animation_table = (const u8* const*)D_800F9934;
    background_dragon_sequence_begin(&obj);
    assert(obj.unk6 == 1 && obj.unk15 == 0 && obj.animation_step.packed == 0x0001FF10);
    expected = obj;
    expected.unk6 = 2;
    expected.unk17 = animation;
    expected.previous_animation_index = 255;
    expected.animation_cursor = (const u8*)D_800F9934[animation];
    expected.animation_step.packed = 0x30010103;
    if (shot_free) {
        struct ShotObj* s = &shots_expected_dragon_swoop_capacity[31];
        s->active = 0x41;
        s->id = 0;
        s->unk2 = 4;
        s->unk7C = WEAPON_OBJECT(&obj);
    }
    for (i = 0; i < available; i++) {
        struct MiscObj* m = &misc_expected_dragon_swoop_capacity[64 - available + i];
        m->active = 0x41;
        m->id = 4;
        m->unk2 = i;
        m->ext.pointer.unk50 = &obj;
        m->state = 2;
    }
    D_8013E198[2] = -1;
    func_800415B0(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, shots_expected_dragon_swoop_capacity, sizeof(shots_expected_dragon_swoop_capacity));
    c_test_same_words(misc_objects, misc_expected_dragon_swoop_capacity, sizeof(misc_expected_dragon_swoop_capacity));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&background_objects[0], &background_before, sizeof(background_before));
    assert(D_8013E198[2] == -1);
    return 1;
}

void background_dragon_projectile_attack(struct MainObj*);
extern union AnimationStep* D_800F9934[16];
extern struct TileEffectRecord** tile_effect_tables[26];
static struct MiscObj misc_expected_dragon_tile_destruction[64];
static u32 map_words[48];
static u16 pixels[256], pixels_expected[256], cache_expected[3][32][32];
static u32 destroy(u32 row)
{
    struct MainObj obj, expected;
    struct EngineObj engine_expected;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_expected[3];
    struct TileEffectRecord* records;
    u32 index = row % 3, free_slot = row / 3 % 2, done = row / 6 % 2, face = row / 12, i, y, x;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words(map_words, COUNT(map_words));
    layout_width = 16;
    layout_size = 64;
    SP_BG_TILEMAP = (u8*)map_words;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    memset(pixels, 0xA5, sizeof(pixels));
    memcpy(pixels_expected, pixels, sizeof(pixels));
    memset(D_801441C8, 0xB6, sizeof(D_801441C8));
    memcpy(cache_expected, D_801441C8, sizeof(cache_expected));
    engine_obj.stage = 1;
    engine_obj.character_state.bytes[index + 1] = done;
    engine_expected = engine_obj;
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i == 63 && free_slot ? 0 : 1;
        misc_objects[i].id = 63;
        misc_objects[i].state = 5;
        misc_objects[i].unk2 = 9;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 2;
    }
    c_test_copy_words((u32*)misc_expected_dragon_tile_destruction, (u32*)misc_objects, sizeof(misc_expected_dragon_tile_destruction) / 4);
    obj.active = 0x41;
    obj.id = 0;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.bg_offset = 0;
    obj.unk15 = face ? 0x40 : 0;
    obj.x_pos.val = (0x680 + index * 512) * 65536 + 0x1234;
    obj.y_pos.val = 0x170 * 65536 + 0x5678;
    obj.ext.main_0.index = index;
    background_objects[0].x_pos.i.hi = obj.x_pos.i.hi - 160;
    background_objects[0].y_pos.i.hi = obj.y_pos.i.hi - 120;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    obj.animation_table = (const u8* const*)D_800F9934;
    set_animation_frame(ANIMATED_OBJECT(&obj), 1, 6);
    assert(obj.animation_step.packed == 0x07010102);
    obj.animation_step.fields.duration = 1;
    expected = obj;
    expected.animation_cursor += 4;
    expected.animation_step.packed = 0x08010213;
    expected.on_screen = 1;
    records = tile_effect_tables[2][index + 1];
    for (y = 0; y < 9; y++) {
        assert(records[y].layer == 0 && records[y].packed_count == 13 && records[y].x == 0x680 + index * 512 && records[y].y == 0x130 + y * 16 && records[y].has_next == (y != 8));
        if (!done)
            for (x = 0; x < 6; x++) {
                pixels_expected[(y + 3) * 16 + 8 + x] = records[y].tiles[x];
                cache_expected[0][y + 19][8 + x] = records[y].tiles[x];
            }
    }
    if (!done) {
        expected.animation_step.fields.event = 0;
        expected.ext.main_0.flags[index] = 1;
        engine_expected.character_state.bytes[index + 1] = 1;
        backgrounds_expected[0].unk37 = 24;
        backgrounds_expected[0].unk46 = backgrounds_expected[0].unk3E.bytes[1] = 3;
        backgrounds_expected[0].unk3D = backgrounds_expected[0].unk3B = 1;
        backgrounds_expected[0].unk34 |= 1;
        if (free_slot) {
            struct MiscObj* m = &misc_expected_dragon_tile_destruction[63];
            m->active = 1;
            m->id = 4;
            m->ext.ready_text.owner = (struct EffectObj*)&obj;
            m->state = 4;
            m->unk5 = m->unk6 = 0;
            m->unk2 = index;
        }
    }
    background_dragon_projectile_attack(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    assert(c_test_word_difference((u32*)misc_objects, (u32*)misc_expected_dragon_tile_destruction, sizeof(misc_expected_dragon_tile_destruction) / 4) == 0 && c_test_word_difference((u32*)pixels, (u32*)pixels_expected, sizeof(pixels) / 4) == 0 && c_test_word_difference((u32*)D_801441C8, (u32*)cache_expected, sizeof(cache_expected) / 4) == 0);
    for (i = 0; i < COUNT(map_words); i++)
        assert(map_words[i] == 0);
    assert(SP_BG_TILEMAP == (u8*)map_words && TEST_BG_TILE_PIXELS == (u8*)pixels && layout_width == 16 && layout_size == 64);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "background_dragon_attacks", 0, 0, COUNT(background_dragon_attacks_cases), test_background_dragon_attacks },
    { "background_dragon_states", 0, 0, COUNT(background_dragon_states_cases), test_background_dragon_states },
    { "dragon_attack_context", NULL, dragon_attack_context_cases_expected, COUNT(dragon_attack_context_cases_expected), dragon_attack_context_cases_row },
    { "background_dragon_spawn_trail", 0, 0, 1, test_background_dragon_spawn_trail },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "perch_arrival_boundaries", NULL, NULL, COUNT(paths) * 2, approach },
    { "offscreen_departure", NULL, NULL, COUNT(paths) * 2, offscreen },
    { "staging_departure", NULL, NULL, COUNT(paths) * 2, staging },
    { "shipped_attack_event_with_full_or_one_free_independent_pools", NULL, NULL, 16, attack },
    { "own_Dragon_sequence_swoop_three_cycles_both_characters_full_partial_pools", NULL, NULL, 36, swoop },
    { "all_three_shipped_destruction_regions_full_free_pool_and_once_only_latch", NULL, NULL, 24, destroy },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(background_dragon_attacks_cases) + COUNT(background_dragon_states_cases) + COUNT(dragon_attack_context_cases_expected) + 1 + COUNT(pool_full_cases) + COUNT(paths) * 2 + COUNT(paths) * 2 + COUNT(paths) * 2 + 16 + 36 + 24;
