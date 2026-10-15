#include "test_runtime.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern struct Unk_unk68 jet_stingray_ambush_drop_attack_box;

static struct DamageInput {
    u8 character, weapon, timer, hp;
};
static const struct DamageInput inputs[] = {
    { 1, 24, 0, 40 },
    { 1, 33, 0, 40 },
    { 1, 0, 0, 40 },
    { 1, 1, 0, 40 },
    { 0, 11, 0, 40 },
    { 0, 0, 0, 40 },
    { 1, 26, 2, 40 },
    { 1, 34, 0, 40 },
};
static u32 damage_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct WeaponObj weapon_before;
    struct EngineObj engine_before;
    struct Unk_unk68 attack = { 0, 0, 8, 8 }, hurt = { 0, 0, 8, 8 };
    struct WeaponObj* weapon = &weapon_objects[0];
    u32 i, actual, collision = ~0u;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    for (i = 0; i < COUNT(D_8013E198); i++)
        D_8013E198[i] = -1;
    obj.active = 0x41;
    obj.id = 56;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 0x27;
    obj.unk7 = 0x35;
    obj.hp = inputs[mode].hp;
    obj.unk42 = 0x1234;
    obj.bg_offset = 0;
    obj.x_pos.val = 100 * 65536 + 0x1357;
    obj.y_pos.val = 100 * 65536 + 0x2468;
    obj.hurt_box = &hurt;
    obj.collision_data = D_801079F8;
    obj.ext.main_56.flash_timer = inputs[mode].timer;
    weapon->active = 1;
    weapon->id = inputs[mode].weapon;
    weapon->unk64 = 2;
    weapon->bg_offset = 0;
    weapon->unk50 = &attack;
    weapon->x_pos.val = obj.x_pos.val;
    weapon->y_pos.val = obj.y_pos.val;
    weapon->unk98 = 0x27;
    g_Player.active = 0x41;
    g_Player.hp = 20;
    g_Player.spike_immune = 1;
    engine_obj.cur_character = inputs[mode].character;
    before = obj;
    player_before = g_Player;
    weapon_before = *weapon;
    engine_before = engine_obj;
    func_80071D30(&obj);
    before.state = obj.state;
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.unk7 = obj.unk7;
    before.hp = obj.hp;
    before.unk42 = obj.unk42;
    before.unk63 = obj.unk63;
    before.unk65 = obj.unk65;
    before.ext.main_56.flash_timer = obj.ext.main_56.flash_timer;
    before.collision_data = obj.collision_data;
    before.on_screen = obj.on_screen;
    weapon_before.unk80 = weapon->unk80;
    weapon_before.unk98 = weapon->unk98;
    player_before.update_delay_request = g_Player.update_delay_request;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(*weapon) / 4; i++)
        assert(((u32*)weapon)[i] == ((u32*)&weapon_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 1; i < COUNT(weapon_objects); i++)
        assert(weapon_objects[i].active == 0);
    for (i = 0; i < COUNT(visual_objects); i++)
        assert(visual_objects[i].active == 1);
    for (i = 0; i < COUNT(D_8013E198); i++)
        assert(D_8013E198[i] == -1);
    assert(obj.hurt_box == &hurt && weapon->unk50 == &attack);
    assert(hurt.unk2 == 8 && hurt.unk3 == 8 && attack.unk2 == 8 && attack.unk3 == 8);
    if (obj.collision_data == D_801079F8)
        collision = 0;
    if (obj.collision_data == D_801060F0)
        collision = 1;
    assert(collision != ~0u);
    switch (observation) {
    case 0:
        actual = (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.unk6 << 16) | ((u32)(u8)obj.unk7 << 24);
        break;
    case 1:
        actual = (u8)obj.hp | ((u32)(u8)obj.unk63 << 8) | ((u32)(u8)obj.unk65 << 16) | ((u32)obj.on_screen << 24);
        break;
    case 2:
        actual = obj.unk42 | ((u32)obj.ext.main_56.flash_timer << 16) | (collision << 24);
        break;
    case 3:
        actual = weapon->unk80.word;
        break;
    default:
        actual = (u8)weapon->unk98 | ((u32)g_Player.update_delay_request << 8) | ((u32)g_Player.spike_immune << 16);
        break;
    }
    return actual;
}
#define DAMAGE_CASE(m, n)                                      \
    static u32 stingray_damage_dispatch_damage_##m##_##n(void) \
    {                                                          \
        return damage_case(m, n);                              \
    }
#define DAMAGE_MODE(m) DAMAGE_CASE(m, 0) DAMAGE_CASE(m, 1) DAMAGE_CASE(m, 2) DAMAGE_CASE(m, 3) DAMAGE_CASE(m, 4)
DAMAGE_MODE(0)
DAMAGE_MODE(1)
DAMAGE_MODE(2)
DAMAGE_MODE(3)
DAMAGE_MODE(4)
DAMAGE_MODE(5)
DAMAGE_MODE(6)
DAMAGE_MODE(7)
#define DAMAGE_ENTRY(m, n) stingray_damage_dispatch_damage_##m##_##n,
#define DAMAGE_ENTRIES(m) DAMAGE_ENTRY(m, 0) DAMAGE_ENTRY(m, 1) DAMAGE_ENTRY(m, 2) DAMAGE_ENTRY(m, 3) DAMAGE_ENTRY(m, 4)
static const CTestCase stingray_damage_dispatch_cases[]
    = { DAMAGE_ENTRIES(0) DAMAGE_ENTRIES(1) DAMAGE_ENTRIES(2) DAMAGE_ENTRIES(3) DAMAGE_ENTRIES(4) DAMAGE_ENTRIES(5) DAMAGE_ENTRIES(6) DAMAGE_ENTRIES(7) };
static const u32 stingray_damage_dispatch_cases_expected[] = { 0x201u, 0x1020027u, 0x9234u, 0x680068u, 0x10027u, 0x103u, 0x20024u, 0x9234u, 0x680068u, 0x10127u, 0x201u, 0x1020027u, 0x1409234u, 0x680068u, 0x10001u, 0x201u, 0x102FF28u, 0x1234u, 0x680068u, 0x10027u, 0x103u, 0x20023u, 0x9234u, 0x680068u, 0x10027u, 0x201u, 0x1020027u, 0x1409234u, 0x680068u, 0x10001u, 0x201u, 0x1020026u, 0x19234u, 0x680068u, 0x10127u, 0x201u, 0x1020026u, 0x1409234u, 0x680068u, 0x10127u };
#undef DAMAGE_CASE
#undef DAMAGE_MODE
#undef DAMAGE_ENTRY
#undef DAMAGE_ENTRIES

static const u32 frames[] = { 0x11223344, 0x55667788 };
static u32 vortex_case(u32 mode)
{
    struct MainObj obj, expected;
    struct VisualObj pool[32];
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds[3];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(visual_objects, 0, sizeof(visual_objects));
    memcpy(backgrounds, background_objects, sizeof(backgrounds));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
        visual_objects[i].state = 40;
        visual_objects[i].unk2 = 9;
        visual_objects[i].unk5 = 3;
        visual_objects[i].unk6 = 4;
        visual_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        visual_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    if (mode == 2)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 56;
    obj.state = 1;
    obj.unk5 = 7;
    obj.unk6 = 0;
    obj.unk7C = mode == 0 ? 2 : 1;
    obj.unk15 = 0x40;
    obj.bg_offset = 2;
    obj.unk40 = 0x1234;
    obj.unk42 = 0x5678;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.sprite_frames = (const u8*)frames;
    obj.animation_table = (const u8* const*)jet_stingray_animations;
    set_animation(&obj, 0);
    expected = obj;
    memcpy(pool, visual_objects, sizeof(pool));
    expected.unk7C--;
    if (mode) {
        expected.unk6 = 1;
        expected.unk7C = 240;
        expected.unk17 = 3;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)jet_stingray_animations[3];
        expected.animation_step = *(union AnimationStep*)jet_stingray_animations[3];
        if (mode == 2) {
            struct VisualObj* child = &pool[31];
            child->active = 0x41;
            child->id = 0x17;
            child->unk40 = obj.unk40;
            child->animation_table = ANIMATED_OBJECT(&obj)->animation_table;
            child->unk3C = (void*)obj.sprite_frames;
            child->unk42 = obj.unk42;
            child->unk15 = obj.unk15;
            child->bg_offset = obj.bg_offset;
            child->x_pos = obj.x_pos;
            child->y_pos = obj.y_pos;
            child->unk50 = PLAYER_OBJECT(&obj);
            child->unk2 = 0;
            expected.ext.main_56.object.visual = &visual_objects[31];
        }
    }
    jet_stingray_vortex_spawn(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)pool)[i]);
    for (i = 0; i < sizeof(backgrounds) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    assert(frames[0] == 0x11223344);
    assert(frames[1] == 0x55667788);
    return (u16)obj.unk7C | ((u32)obj.unk17 << 16) | ((u32)(u8)visual_objects[31].active << 24);
}
#define CASE(m)                                             \
    static u32 stingray_vortex_visual_pool_vortex_##m(void) \
    {                                                       \
        return vortex_case(m);                              \
    }
CASE(0)
CASE(1)
CASE(2)
#define ENTRY(m) stingray_vortex_visual_pool_vortex_##m,
static const CTestCase stingray_vortex_visual_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) };
static const u32 stingray_vortex_visual_pool_cases_expected[] = { 0x1000001u, 0x10300F0u, 0x410300F0u };
#undef CASE
#undef ENTRY

static const u32 jet_stingray_ambush_drop_expected[] = { 0u, 0u, 0xFFFFFFFFu, 0u, 0u };
static u32 test_jet_stingray_ambush_drop(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&jet_stingray_ambush_drop_attack_box, 0, sizeof(jet_stingray_ambush_drop_attack_box));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7 = -1;
    jet_stingray_ambush_drop(&obj);
    observed_values[0] = (u32)obj.ext.main_56.flags;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7;
    observed_values[3] = (u32)obj.unk7C;
    observed_values[4] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, jet_stingray_ambush_drop_expected, 5);
}

static const u32 jet_stingray_ambush_return_expected[] = { 2u, 0u, 0u, 0u, 0x120u, 0xFFFFFFB0u };
static u32 test_jet_stingray_ambush_return(u32 row)
{
    u32 observed_values[6];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = 1;
    obj.x_pos.i.hi = 8192;
    jet_stingray_ambush_return(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7;
    observed_values[3] = (u32)obj.unk7C;
    observed_values[4] = (u32)obj.x_pos.i.hi;
    observed_values[5] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, jet_stingray_ambush_return_expected, 6);
}

struct jet_stingray_ambush_rise_case {
    u32 unk7;
    u32 expected[7];
};
static const struct jet_stingray_ambush_rise_case jet_stingray_ambush_rise_cases[] = {
    { -1, { 0u, 0u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u } },
    { 1, { 0u, 0u, 1u, 0u, 0u, 0u, 0u } },
};
static u32 test_jet_stingray_ambush_rise(u32 row)
{
    const struct jet_stingray_ambush_rise_case* c = &jet_stingray_ambush_rise_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&jet_stingray_ambush_attack_box, 0, sizeof(jet_stingray_ambush_attack_box));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    obj.unk7 = c->unk7;
    jet_stingray_ambush_rise(&obj);
    observed_values[0] = (u32)obj.ext.main_56.flags;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7;
    observed_values[3] = (u32)obj.unk7C;
    observed_values[4] = (u32)obj.x_pos.val;
    observed_values[5] = (u32)obj.y_pos.val;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

struct jet_stingray_intro_warning_case {
    u32 unk6, pool_0_full;
    u32 expected[6];
};
static const struct jet_stingray_intro_warning_case jet_stingray_intro_warning_cases[] = {
    { -1, 0, { 0u, 0u, 0u, 0u, 0xFFFFFFFFu, 0u } },
    { 0, 255, { 1u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_jet_stingray_intro_warning(u32 row)
{
    const struct jet_stingray_intro_warning_case* c = &jet_stingray_intro_warning_cases[row];
    u32 observed_values[6];
    struct MainObj obj;
    struct EffectObj child_0;
    u8 child_0_present;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&effect_objects, 0, sizeof(effect_objects));
    obj.unk6 = c->unk6;
    pool_0_full = c->pool_0_full;
    child_0_present = 0;
    obj.ext.main_56.object.effect = child_0_present ? &child_0 : NULL;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    jet_stingray_intro_warning(&obj);
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)obj.on_screen;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.unk6;
    observed_values[5] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

#include "support/pool_full.h"
static u32 pool_full_jet_stingray_death_explode(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_self.unk7E = 1;
    pf_snapshot();
    pf_expected.unk7C = 0;
    pf_expected.unk7E = 0;
    pf_expected.on_screen = 1;
    jet_stingray_death_explode(&pf_self);
    pf_expected.unk5++;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_jet_stingray_death_explode,
};
static const u32 pool_full_cases_expected[] = { 0x1u };

static u32 jet_stingray_ambush_drop_case(u32 mode)
{
    struct MainObj boss, boss_before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&boss, 0, sizeof(boss));
    boss.active = 0x41;
    boss.id = 56;
    boss.state = 1;
    boss.unk6 = 1;
    boss.unk7 = mode == 3 ? 0 : mode == 4 ? 3
                                          : 2;
    boss.unk7C = 1;
    boss.ext.main_56.flags = 0xFF;
    boss.animation_table = (const u8* const*)jet_stingray_animations;
    set_animation(&boss, 0);
    boss_before = boss;
    if (mode == 3) {
        boss_before.unk7 = 1;
        boss_before.unk7C = 0;
        boss_before.x_pos = g_Player.x_pos;
        boss_before.y_speed = -9 * 65536;
        boss_before.ext.main_56.flags = 0xFE;
        boss_before.attack_box = (const u8*)&jet_stingray_ambush_drop_attack_box;
        boss_before.unk17 = 8;
        boss_before.previous_animation_index = 0xFF;
        boss_before.animation_cursor = jet_stingray_animations[8];
        boss_before.animation_step = *(union AnimationStep*)jet_stingray_animations[8];
    } else if (mode == 5) {
        boss_before.unk7 = 0;
        boss_before.unk7C = 40;
        boss_before.unk6 = 2;
    }
    jet_stingray_ambush_drop(&boss);
    for (i = 0; i < sizeof(boss) / 4; i++)
        assert(((u32*)&boss)[i] == ((u32*)&boss_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)boss.unk6 | ((u32)(u8)boss.unk7 << 8) | ((u32)boss.unk17 << 16);
}
#define CASE(m)                                   \
    static u32 jet_stingray_ambush_drop_##m(void) \
    {                                             \
        return jet_stingray_ambush_drop_case(m);  \
    }
CASE(3)
CASE(4)
CASE(5)
#undef CASE
static const CTestCase jet_stingray_ambush_drop_start_cases[]
    = {
          jet_stingray_ambush_drop_3,
          jet_stingray_ambush_drop_4,
          jet_stingray_ambush_drop_5,
      };
static const u32 jet_stingray_ambush_drop_start_cases_expected[] = { 0x80101u, 0x301u, 0x2u };

#include "support/ambush_rise_and_hopper_blink.h"
RESET_CASE(0)
RESET_CASE(3)
static const CTestCase jet_stingray_ambush_rise_start_cases[] = { RESET_ENTRY(0) RESET_ENTRY(3) };
static const u32 jet_stingray_ambush_rise_start_cases_expected[] = { 0x7010103u, 0x30103u };

#include "support/jet_stingray_animation_wait.h"
JET_WAIT_CASE(0, 0)
JET_WAIT_CASE(0, 1)
JET_WAIT_CASE(2, 0)
JET_WAIT_CASE(2, 1)
static const CTestCase jet_stingray_intro_warning_wait_cases[] = { JET_WAIT_ENTRY(0, 0) JET_WAIT_ENTRY(0, 1) JET_WAIT_ENTRY(2, 0) JET_WAIT_ENTRY(2, 1) };

static const u32 jet_stingray_intro_warning_wait_cases_expected[] = { 0x5F010003u, 0x2u, 0x10009u, 0x301u };
const struct CTestGroup c_test_groups[] = {
    { "stingray_damage_dispatch", stingray_damage_dispatch_cases, stingray_damage_dispatch_cases_expected, COUNT(stingray_damage_dispatch_cases), 0 },
    { "stingray_vortex_visual_pool", stingray_vortex_visual_pool_cases, stingray_vortex_visual_pool_cases_expected, COUNT(stingray_vortex_visual_pool_cases), 0 },
    { "jet_stingray_ambush_drop", 0, 0, 1, test_jet_stingray_ambush_drop },
    { "jet_stingray_ambush_return", 0, 0, 1, test_jet_stingray_ambush_return },
    { "jet_stingray_ambush_rise", 0, 0, 2, test_jet_stingray_ambush_rise },
    { "jet_stingray_intro_warning", 0, 0, 2, test_jet_stingray_intro_warning },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "jet_stingray_ambush_drop_start", jet_stingray_ambush_drop_start_cases, jet_stingray_ambush_drop_start_cases_expected, COUNT(jet_stingray_ambush_drop_start_cases), 0 },
    { "jet_stingray_ambush_rise_start", jet_stingray_ambush_rise_start_cases, jet_stingray_ambush_rise_start_cases_expected, COUNT(jet_stingray_ambush_rise_start_cases), 0 },
    { "jet_stingray_intro_warning_wait", jet_stingray_intro_warning_wait_cases, jet_stingray_intro_warning_wait_cases_expected, COUNT(jet_stingray_intro_warning_wait_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(stingray_damage_dispatch_cases) + COUNT(stingray_vortex_visual_pool_cases) + 1 + 1 + 2 + 2 + COUNT(pool_full_cases) + COUNT(jet_stingray_ambush_drop_start_cases) + COUNT(jet_stingray_ambush_rise_start_cases) + COUNT(jet_stingray_intro_warning_wait_cases);
