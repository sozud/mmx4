#include "test_runtime.h"
#include "main/mains/main_67_gunship.h"
#include "main/55C4.h"
void gunship_boost(struct MainObj* arg0);
void gunship_missiles(struct MainObj* arg0);
void gunship_resume_step(struct MainObj* arg0);
void gunship_turn(struct MainObj* arg0);

static u32 wait_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    u32 script_before, i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 67;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 0x27;
    obj.unk72 = 8;
    obj.ext.main_67.unk8D = 1;
    obj.unk7C = mode ? 2 : 1;
    obj.x_pos.val = 100 * 65536 + 0x1357;
    obj.y_pos.val = 100 * 65536 + 0x2468;
    obj.animation_table = (u32**)gunship_animations;
    obj.animation_cursor = gunship_animations[1];
    obj.animation_step.packed = *(u32*)gunship_animations[1];
    g_Player.x_pos.i.hi = mode ? -93 : 100;
    g_Player.y_pos.i.hi = 51;
    before = obj;
    player_before = g_Player;
    script_before = *(u32*)gunship_animations[1];
    func_800828B4(&obj);
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.unk7C = obj.unk7C;
    before.ext.main_67.unk8D = obj.ext.main_67.unk8D;
    before.animation_step = obj.animation_step;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(obj.animation_table == (u32**)gunship_animations && obj.animation_cursor == gunship_animations[1]);
    assert(*(u32*)gunship_animations[1] == script_before);
    if (observation == 0)
        actual = (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)obj.ext.main_67.unk8D << 16);
    else if (observation == 1)
        actual = (u16)obj.unk7C;
    else
        actual = obj.animation_step.packed;
    return actual;
}
static const u32 gunship_wait_context_cases_expected[] = { 0x4u, 0x0u, 0x10001u, 0x12702u, 0x1u, 0x10001u };
static u32 gunship_wait_context_cases_row(u32 row)
{
    return wait_case(row / 3, row % 3);
}

struct func_800828B4_case {
    u32 g_Player_x_pos_hi, obj_x_pos_hi, unk7C, unk8D;
    u32 expected[4];
};
static const struct func_800828B4_case func_800828B4_cases[] = {
    { 194, 0, 0, 255, { 0xFFu, 0u, 0u, 0xFFFFFFFFu } },
    { 194, 0, 1, 0, { 0u, 4u, 0u, 0u } },
    { 0, 0, 0, 255, { 1u, 4u, 0u, 0xFFFFFFFFu } },
    { -28704, -28528, 0, 255, { 1u, 4u, 0u, 0xFFFFFFFFu } },
    { 0, 0, 1, 0, { 0u, 3u, 0u, 0u } },
};
static u32 test_func_800828B4(u32 row)
{
    const struct func_800828B4_case* c = &func_800828B4_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    obj.unk7C = c->unk7C;
    obj.unk72 = 8;
    obj.ext.main_67.unk8D = c->unk8D;
    func_800828B4(&obj);
    observed_values[0] = (u32)obj.ext.main_67.unk8D;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

#include "support/pool_full.h"
static u32 pool_full_gunship_spawn_bullet(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    gunship_spawn_bullet(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_gunship_spawn_missiles(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    gunship_spawn_missiles(VISUAL_OBJECT(&pf_self));
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_gunship_spawn_exhaust(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    gunship_spawn_exhaust(&pf_self);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_gunship_spawn_bullet,
    pool_full_gunship_spawn_missiles,
    pool_full_gunship_spawn_exhaust,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u, 0x50000u };
#include "support/state_cases.h"

void gunship_bob(struct MainObj*);
#define BOB() (state_extra = (u16)so.ext.main_67.vertical_speed | (u32)so.ext.main_67.delay << 16 | (u32)so.ext.main_67.direction << 24)
static void gp_missiles_start(void)
{
    state_reset(4, 0, 0);
    gunship_missiles(&so);
}
static void gp_missiles_open(void)
{
    state_reset(4, 1, 0);
    so.unk7C = 1;
    gunship_missiles(&so);
}
static void gp_missiles_opening(void)
{
    state_reset(4, 1, 0);
    so.unk7C = 2;
    gunship_missiles(&so);
}
static void gp_missiles_launch(void)
{
    state_reset(4, 2, 0);
    so.unk7C = 1;
    gunship_missiles(&so);
    state_extra = shot_objects[3].active | shot_objects[3].unk16 << 8;
}
static void gp_missiles_aim(void)
{
    state_reset(4, 2, 0);
    so.unk7C = 2;
    gunship_missiles(&so);
}
static void gp_missiles_end(void)
{
    state_reset(4, 3, 0);
    so.unk7C = 1;
    gunship_missiles(&so);
}
static void gp_missiles_hold(void)
{
    state_reset(4, 3, 0);
    so.unk7C = 2;
    gunship_missiles(&so);
}
static void gp_turn_start(void)
{
    state_reset(5, 0, 0);
    gunship_turn(&so);
}
static void gp_turn_done(void)
{
    state_reset(5, 1, 0);
    so.unk7C = 1;
    gunship_turn(&so);
}
static void gp_turn_wait(void)
{
    state_reset(5, 1, 0);
    so.unk7C = 2;
    gunship_turn(&so);
}
static void gp_boost_start(void)
{
    state_reset(6, 0, 0);
    gunship_boost(&so);
    state_extra = so.ext.main_67.unk89 | visual_objects[3].active << 8;
}
static void gp_boost_done(void)
{
    state_reset(6, 1, 0);
    so.unk7C = 1;
    so.ext.main_67.unk89 = 1;
    gunship_boost(&so);
    state_extra = so.ext.main_67.unk89;
}
static void gp_boost_wait(void)
{
    state_reset(6, 1, 0);
    so.unk7C = 2;
    gunship_boost(&so);
}
static void gp_resume(void)
{
    state_reset(1, 0, 0);
    so.ext.main_67.saved_unk5 = 5;
    gunship_resume_step(&so);
}
static void gp_bob_rise(void)
{
    state_reset(2, 0, 0);
    gunship_bob(&so);
    BOB();
}
static void gp_bob_hold_up(void)
{
    state_reset(2, 0, 0);
    so.ext.main_67.vertical_speed = 0x100;
    so.ext.main_67.delay = 2;
    gunship_bob(&so);
    BOB();
}
static void gp_bob_top(void)
{
    state_reset(2, 0, 0);
    so.ext.main_67.vertical_speed = 0x7000;
    gunship_bob(&so);
    BOB();
}
static void gp_bob_fall(void)
{
    state_reset(2, 0, 0);
    so.ext.main_67.direction = 1;
    gunship_bob(&so);
    BOB();
}
static void gp_bob_hold_down(void)
{
    state_reset(2, 0, 0);
    so.ext.main_67.direction = 1;
    so.ext.main_67.vertical_speed = -0x100;
    so.ext.main_67.delay = 2;
    gunship_bob(&so);
    BOB();
}
static void gp_bob_bottom(void)
{
    state_reset(2, 0, 0);
    so.ext.main_67.direction = 1;
    so.ext.main_67.vertical_speed = -0x7000;
    gunship_bob(&so);
    BOB();
}

static void (*const gunship_states_cases[])(void) = {
    gp_missiles_start,
    gp_missiles_open,
    gp_missiles_opening,
    gp_missiles_launch,
    gp_missiles_aim,
    gp_missiles_end,
    gp_missiles_hold,
    gp_turn_start,
    gp_turn_done,
    gp_turn_wait,
    gp_boost_start,
    gp_boost_done,
    gp_boost_wait,
    gp_resume,
    gp_bob_rise,
    gp_bob_hold_up,
    gp_bob_top,
    gp_bob_fall,
    gp_bob_hold_down,
    gp_bob_bottom,
};
static const u32 gunship_states_expected[] = { 0x10400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20400u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x10400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x30400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0x741u, 0x410000u, 0x20400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x30400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10500u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10600u, 0xFF000000u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x4101u, 0x4100u, 0x400u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10600u, 0u, 0u, 0u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x500u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x200u, 0u, 0u, 0xFFFFFA00u, 0u, 0u, 0u, 0x50000u, 0x400u, 0u, 0x200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x10100u, 0u, 0x200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x10F7000u, 0u, 0x200u, 0u, 0u, 0x600u, 0u, 0u, 0u, 0x50000u, 0x100FC00u, 0u, 0x200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0x101FF00u, 0u, 0x200u, 0u, 0u, 0u, 0u, 0u, 0u, 0x50000u, 0xF9000u, 0u };

static u32 test_gunship_states(u32 row)
{
    return object_run(gunship_states_cases[row], row, &gunship_states_expected[row * 10]);
}

void gunship_gun_fire(struct MainObj*);
void gunship_gun_wait(struct MainObj*);
static struct ShotObj shots_expected[32];
static u32 gun(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 mode = row % 2, character = row / 2 % 2, available = row / 4 % 2, face = row / 8, i;
    memset(&obj, 0, sizeof(obj));
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < 32; i++)
        shot_objects[i].active = 1;
    if (available)
        shot_objects[31].active = 0;
    c_test_copy_words((u32*)shots_expected, (u32*)shot_objects, sizeof(shots_expected) / 4);
    engine_obj.cur_character = character;
    engine_before = engine_obj;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    obj.active = 0x41;
    obj.id = 67;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = mode;
    obj.unk15 = face ? 0x40 : 0;
    obj.unk7C = 1;
    obj.unk40 = 8;
    obj.unk42 = 0x9234;
    obj.ext.main_67.unk89 = 1;
    obj.ext.main_67.unk8A = mode ? 3 : 2;
    obj.animation_table = (const u8* const*)gunship_animations;
    set_animation(&obj, 0);
    assert(obj.animation_step.packed == 0x00000001);
    expected = obj;
    if (!mode) {
        expected.ext.main_67.unk8A++;
        expected.unk7C = character ? 10 : 20;
        expected.unk6 = 1;
        if (available) {
            shots_expected[31].active = 0x41;
            shots_expected[31].id = 43;
            shots_expected[31].unk2 = character;
            shots_expected[31].unk7C = WEAPON_OBJECT(&obj);
            shots_expected[31].unk42 = obj.unk42;
            shots_expected[31].animation_table = (u32**)gunship_animations;
            shots_expected[31].unk40 = 8;
            shots_expected[31].unk15 = obj.unk15;
            shots_expected[31].unk16 = 4;
        }
    } else {
        expected.unk6 = 0;
        expected.unk5 = 2;
        expected.ext.main_67.unk89 = expected.ext.main_67.unk8A = 0;
        expected.unk7C = character ? 40 : 30;
    }
    D_8013E198[2] = -1;
    if (!mode)
        gunship_gun_fire(&obj);
    else
        gunship_gun_wait(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((u32*)shot_objects, (u32*)shots_expected, sizeof(shots_expected) / 4) == 0);
    return 1;
}

extern struct Unk_unk68 gunship_hurt_box, gunship_terrain_box, D_80107F04[];
static const struct {
    s8 weapon;
    u8 damage, lethal, flag;
} hits[] = {
    { -1, 0, 0, 0 },
    { 0, 3, 0, 1 },
    { 1, 4, 0, 0 },
    { 10, 4, 0, 0 },
    { 32, 3, 0, 0 },
    { 0, 3, 1, 1 },
};
static struct WeaponObj weapons_expected[16];
static struct VisualObj visuals_before[32];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 interrupt(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before, entity_before;
    struct RideArmorObj ride_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 hit = row % COUNT(hits), character = row / COUNT(hits) % 2, boost = row / COUNT(hits) / 2 % 2;
    u32 facing = row / COUNT(hits) / 4 % 2, outside = row / COUNT(hits) / 8, i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 24;
    g_Player.spike_immune = 1;
    player_before = g_Player;
    if (hits[hit].weapon == 32)
        player_before.update_delay_request = 1;
    memset(&g_Entity, 0, sizeof(g_Entity));
    entity_before = g_Entity;
    memset(&qux_object, 0, sizeof(qux_object));
    ride_before = qux_object;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    engine_obj.cur_character = character;
    engine_before = engine_obj;
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    memcpy(visuals_before, visual_objects, sizeof(visuals_before));
    obj.active = 0x41;
    obj.id = 67;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 9;
    obj.bg_offset = 0;
    obj.on_screen = 7;
    obj.unk15 = facing ? 0x40 : 0;
    obj.unk42 = 0x9234;
    obj.hp = hits[hit].lethal ? 1 : 30;
    obj.unk75 = 1;
    obj.x_pos.val = (outside ? 417 : 160) * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk18.val = 0x1234;
    obj.unk1C.val = 0x5678;
    obj.hurt_box = &gunship_hurt_box;
    obj.terrain_box = &gunship_terrain_box;
    obj.collision_data = D_80107F04;
    obj.ext.main_67.saved_unk5 = boost ? 6 : 2;
    obj.ext.main_67.unk89 = boost;
    obj.animation_table = (const u8* const*)gunship_animations;
    set_animation(&obj, 0);
    obj.previous_animation_index = 37;
    if (hits[hit].weapon >= 0) {
        weapon_objects[0].active = 0x21;
        weapon_objects[0].id = hits[hit].weapon;
        weapon_objects[0].unk15 = obj.unk15;
        weapon_objects[0].x_pos = obj.x_pos;
        weapon_objects[0].y_pos = obj.y_pos;
        weapon_objects[0].unk50 = (const u8*)&gunship_hurt_box;
    }
    memcpy(weapons_expected, weapon_objects, sizeof(weapons_expected));
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk5 = boost ? 6 : 2;
    expected.unk42 = 0x1234;
    if (!boost) {
        expected.ext.main_67.vertical_speed = 1024;
        expected.y_pos.val -= 1536;
    }
    if (hits[hit].weapon >= 0) {
        expected.hp = hits[hit].lethal ? 0 : 30 - hits[hit].damage;
        expected.unk42 |= 0x8000;
        ((s16*)&weapons_expected[0].unk80)[0] = obj.x_pos.i.hi + (facing ? 2 : -2);
        ((s16*)&weapons_expected[0].unk80)[1] = 113;
        weapons_expected[0].unk98 = hits[hit].flag;
    }
    if (hits[hit].lethal) {
        expected.unk7C = 100;
        expected.unk7E = 5;
        expected.unk5 = 0;
        expected.unk42 &= 0x7FFF;
        expected.state = 2;
    } else {
        if (!boost && (character == 0 ? hits[hit].weapon == 1 || hits[hit].weapon == 10 : hits[hit].weapon == 32)) {
            expected.unk5 = 6;
            expected.unk6 = 0;
        }
        if (outside)
            memset(&expected, 0, 8);
        else
            expected.on_screen = 1;
    }
    D_8013E198[1] = D_8013E198[5] = -1;
    cur_random = 0x1234;
    func_80082574(&obj);
    SAME(obj, expected);
    SAME(g_Player, player_before);
    SAME(g_Entity, entity_before);
    SAME(qux_object, ride_before);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(weapon_objects, weapons_expected);
    SAME(visual_objects, visuals_before);
    assert(cur_random == 0x1234 && D_8013E198[1] == -1 && D_8013E198[5] == -1);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "gunship_states", 0, 0, COUNT(gunship_states_cases), test_gunship_states },
    { "gunship_wait_context", NULL, gunship_wait_context_cases_expected, COUNT(gunship_wait_context_cases_expected), gunship_wait_context_cases_row },
    { "func_800828B4", 0, 0, 5, test_func_800828B4 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "character_specific_gun_burst_delays_and_real_pool_capacity", NULL, NULL, 16, gun },
    { "weapon_character_boost_and_bounds", NULL, NULL, COUNT(hits) * 16, interrupt },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(gunship_states_cases) + COUNT(gunship_wait_context_cases_expected) + 5 + COUNT(pool_full_cases) + 16 + COUNT(hits) * 16;
