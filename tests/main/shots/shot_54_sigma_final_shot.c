#include "test_runtime.h"
#include "main/shots/shot_54_sigma_final_shot.h"
#include "main/55C4.h"
void sigma_final_shot_ice(struct ShotObj*);
void sigma_final_shot_lightning(struct ShotObj*);
void sigma_final_shot_lightning_split(struct ShotObj*);
extern void* sigma_final_animations[39];

static u32 lightning_case(u32 mode)
{
    struct ShotObj obj, before, pool_before[32];
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    u32 i, free_count = mode == 2 || mode == 4 ? 2 : mode == 3 ? 1
                                                               : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x27;
        shot_objects[i].state = 0x28;
    }
    for (i = 0; i < free_count; i++)
        shot_objects[32 - free_count + i].active = 0;
    obj.active = 0x41;
    obj.id = 54;
    obj.state = 1;
    obj.unk6 = 2;
    obj.timer = 0x27;
    obj.unk70 = mode == 0 ? 0 : mode == 2 ? 4
                                          : 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -32768;
    obj.animation_table = (const u8* const*)sigma_final_animations;
    set_animation(&obj, 0);
    owner.active = 0x41;
    owner.id = 74;
    owner.state = 1;
    obj.unk7C = WEAPON_OBJECT(&owner);
    D_8013E198[2] = -1;
    before = obj;
    owner_before = owner;
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    sigma_lightning_fly(&obj);
    before.x_pos.val += 65536;
    before.y_pos.val += 32768;
    before.animation_step.fields.duration--;
    if (mode != 0) {
        before.timer = 10;
        before.unk6++;
    }
    for (i = 0; i < free_count; i++) {
        struct ShotObj* shot = &pool_before[32 - free_count + i];
        shot->active = 0x41;
        shot->id = 54;
        shot->unk2 = (mode == 2 ? 3 : 5) + i;
        shot->x_pos.val = 100 * 65536 + 0x1234;
        shot->y_pos.val = 200 * 65536 + 0x5678;
        shot->unk7C = WEAPON_OBJECT(&owner);
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(D_8013E198[2] == -1);
    return (u8)obj.unk6 | ((u32)(u16)obj.timer << 8) | ((u32)(u8)shot_objects[31].unk2 << 24);
}
static const u32 sigma_lightning_shot_pool_cases_expected[] = { 0x2702u, 0xA03u, 0x4000A03u, 0x5000A03u, 0x6000A03u };

#include "support/state_cases.h"

static struct MainObj sigma_parent;
#define ss state_room.shot
#define SIGMA_SHOT(step, phase) (state_reset(step, phase, 0), memset(&sigma_parent, 0, sizeof(sigma_parent)), sigma_parent.animation_table = (void*)state_table, sigma_parent.unk42 = 0x100, sigma_parent.bg_offset = 1, ss.unk7C = (struct WeaponObj*)&sigma_parent, ss.x_pos.i.hi = 0x80, ss.y_pos.i.hi = 0x60)
#define SHOT_TIMER() (state_extra = (u16)ss.timer | (u32)(u8)ss.unk60 << 16 | (u32)(u8)ss.bg_offset << 24)
static void sf_init(u8 kind)
{
    SIGMA_SHOT(0, 0);
    ss.unk2 = kind;
    ss.unk7 = 1;
    func_800ABE08(&ss);
    SHOT_TIMER();
}
static void sf_init_fireball(void) { sf_init(0); }
static void sf_init_lightning(void) { sf_init(1); }
static void sf_init_ice(void) { sf_init(2); }
static void sf_init_wide_left(void) { sf_init(3); }
static void sf_init_wide_right(void) { sf_init(4); }
static void sf_init_tall_up(void) { sf_init(5); }
static void sf_init_tall_down(void) { sf_init(6); }
static void sf_init_spike(void) { sf_init(7); }
static void sf_ice_land_a(void)
{
    SIGMA_SHOT(4, 0);
    ss.unk70 = 8;
    cur_random = 1;
    sigma_final_shot_ice(&ss);
    SHOT_TIMER();
}
static void sf_ice_land_b(void)
{
    SIGMA_SHOT(4, 0);
    ss.unk70 = 8;
    cur_random = 2;
    sigma_final_shot_ice(&ss);
    SHOT_TIMER();
}
static void sf_ice_fall(void)
{
    SIGMA_SHOT(4, 0);
    ss.y_vel.val = -0x10000;
    sigma_final_shot_ice(&ss);
}
static void sf_ice_slide(void)
{
    SIGMA_SHOT(4, 1);
    ss.timer = 3;
    ss.x_vel.val = 0x20000;
    sigma_final_shot_ice(&ss);
    SHOT_TIMER();
}
static void sf_ice_slide_stop(void)
{
    SIGMA_SHOT(4, 1);
    ss.timer = 1;
    sigma_final_shot_ice(&ss);
    SHOT_TIMER();
}
static void sf_ice_melt(void)
{
    SIGMA_SHOT(4, 2);
    sigma_final_shot_ice(&ss);
}
static void sf_ice_melting(void)
{
    SIGMA_SHOT(4, 2);
    ss.animation_step.fields.relative_step = 1;
    ss.x_vel.val = 0x20000;
    sigma_final_shot_ice(&ss);
}
static void sf_bolt_aim(void)
{
    SIGMA_SHOT(3, 0);
    ss.timer = 1;
    g_Player.x_pos.i.hi = 0x100;
    sigma_final_shot_lightning(&ss);
    SHOT_TIMER();
}
static void sf_bolt_wait(void)
{
    SIGMA_SHOT(3, 0);
    ss.timer = 3;
    sigma_final_shot_lightning(&ss);
    SHOT_TIMER();
}
static void sf_bolt_fade(void)
{
    SIGMA_SHOT(3, 2);
    ss.timer = 1;
    sigma_final_shot_lightning(&ss);
    SHOT_TIMER();
}
static void sf_bolt_fading(void)
{
    SIGMA_SHOT(3, 2);
    ss.timer = 3;
    sigma_final_shot_lightning(&ss);
    SHOT_TIMER();
}
static void sf_split(void)
{
    SIGMA_SHOT(6, 0);
    ss.x_vel.val = 0x40000;
    sigma_final_shot_lightning_split(&ss);
}

static void (*const sigma_final_shot_states_cases[])(void) = {
    sf_init_fireball,
    sf_init_lightning,
    sf_init_ice,
    sf_init_wide_left,
    sf_init_wide_right,
    sf_init_tall_up,
    sf_init_tall_down,
    sf_init_spike,
    sf_ice_land_a,
    sf_ice_land_b,
    sf_ice_fall,
    sf_ice_slide,
    sf_ice_slide_stop,
    sf_ice_melt,
    sf_ice_melting,
    sf_bolt_aim,
    sf_bolt_wait,
    sf_bolt_fade,
    sf_bolt_fading,
    sf_split,
};
static const u32 sigma_final_shot_states_expected[] = { 0x1000201u, 0xFF400000u, 0x980000u, 0x700000u, 0x40000u, 0x10000u, 0u, 0x50107u, 0x1060019u, 0u, 0x1000301u, 0xFF000100u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50102u, 0x1060014u, 0u, 0x1000401u, 0xFF000200u, 0x680000u, 0x700000u, 0xFFFD0000u, 0x10000u, 0x800000u, 0x50103u, 0x1090000u, 0u, 0x1000601u, 0xFF000300u, 0x800000u, 0x600000u, 0x40000u, 0u, 0u, 0x50102u, 0x1060000u, 0u, 0x1000601u, 0xFF400400u, 0x800000u, 0x600000u, 0xFFFC0000u, 0u, 0u, 0x50102u, 0x1060000u, 0u, 0x1000601u, 0xFF000500u, 0x800000u, 0x600000u, 0u, 0x40000u, 0u, 0x50102u, 0x1060000u, 0u, 0x1000601u, 0xFF400600u, 0x800000u, 0x600000u, 0u, 0xFFFC0000u, 0u, 0x50102u, 0x1060000u, 0u, 0x1000501u, 0xFF400700u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50104u, 0x118003Cu, 0u, 0x10400u, 0u, 0x820000u, 0x600000u, 0x20000u, 0u, 0u, 0x40000u, 0x20u, 0u, 0x10400u, 0u, 0x7E0000u, 0x600000u, 0xFFFE0000u, 0u, 0u, 0x40000u, 0x20u, 0u, 0x400u, 0u, 0x800000u, 0x610000u, 0u, 0xFFFF0000u, 0u, 0x40000u, 0u, 0u, 0x10400u, 0u, 0x820000u, 0x600000u, 0x20000u, 0u, 0u, 0x40000u, 2u, 0u, 0x20400u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20400u, 0u, 0x820000u, 0x600000u, 0x20000u, 0u, 0u, 0x40000u, 0u, 0u, 0x10300u, 0u, 0x800000u, 0x600000u, 0x3536Cu, 0x238E4u, 0u, 0x40000u, 0u, 0u, 0x300u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 2u, 0u, 2u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20300u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 2u, 0u, 0x600u, 0u, 0x840000u, 0x600000u, 0x40000u, 0u, 0u, 0x40000u, 0u, 0u };

static u32 test_sigma_final_shot_states(u32 row)
{
    return object_run(sigma_final_shot_states_cases[row], row, &sigma_final_shot_states_expected[row * 10]);
}

extern u8 sigma_spike_box[4];
void sigma_final_shot_spike(struct ShotObj*);
extern void* sigma_final_animations[39];
static u32 lifetime(u32 row)
{
    struct MainObj owner, owner_expected;
    struct ShotObj obj, expected;
    struct EngineObj engine_before;
    struct BackgroundObj background_before;
    struct PlayerObj player_before = g_Player;
    u32 i, layer = row % 3, spike = row / 3;
    engine_obj.stage = 12;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    background_objects[layer].x_pos.val = 1280 << 16;
    background_objects[layer].y_pos.val = (552 + spike * 16 - 120) << 16;
    background_before = background_objects[layer];
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 74;
    owner.state = 1;
    owner.hp = 48;
    owner.x_pos.i.hi = 1473;
    owner.y_pos.i.hi = 707;
    owner.bg_offset = layer;
    owner.animation_table = (const u8* const*)sigma_final_animations;
    owner_expected = owner;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 54;
    obj.unk2 = 7;
    obj.x_pos.i.hi = 1440;
    obj.y_pos.i.hi = 552 + spike * 16;
    obj.unk7C = WEAPON_OBJECT(&owner);
    func_800ABE08(&obj);
    assert(obj.state == 1 && obj.unk5 == 5 && obj.unk6 == 0 && obj.timer == 60 && obj.animation_step.packed == 0x35000001 && obj.unk50.data == NULL && obj.on_screen == 1);
    expected = obj;
    for (i = 0; i < 60; i++)
        sigma_final_shot_spike(&obj);
    expected.timer = 210;
    expected.unk6 = 1;
    expected.unk50.data = sigma_spike_box;
    c_test_same_words(&obj, &expected, sizeof(obj));
    for (i = 0; i < 210; i++)
        sigma_final_shot_spike(&obj);
    expected.timer = 60;
    expected.unk6 = 2;
    expected.unk50.data = NULL;
    c_test_same_words(&obj, &expected, sizeof(obj));
    for (i = 0; i < 59; i++)
        sigma_final_shot_spike(&obj);
    expected.timer = 1;
    c_test_same_words(&obj, &expected, sizeof(obj));
    sigma_final_shot_spike(&obj);
    expected.timer = 0;
    expected.state = 2;
    expected.unk5 = expected.unk6 = 0;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&background_objects[layer], &background_before, sizeof(background_before));
    c_test_same_words(&owner, &owner_expected, sizeof(owner));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_final_shot_states", 0, 0, COUNT(sigma_final_shot_states_cases), test_sigma_final_shot_states },
    { "sigma_lightning_shot_pool", NULL, sigma_lightning_shot_pool_cases_expected, COUNT(sigma_lightning_shot_pool_cases_expected), lightning_case },
    { "own_Sigma_spike_constructor_extend_active_retract_entire_330_tick_lifetime", NULL, NULL, 36, lifetime },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_final_shot_states_cases) + COUNT(sigma_lightning_shot_pool_cases_expected) + 36;
