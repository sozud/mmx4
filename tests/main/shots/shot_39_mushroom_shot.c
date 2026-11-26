#include "test_runtime.h"
#include "main/shots/shot_39_mushroom_shot.h"
#include "main/mains/main_61_split_mushroom.h"
#include "support/state_cases.h"
#include "main/55C4.h"

static u32 launch_case(u32 observation)
{
    struct ShotObj obj, before;
    struct PlayerObj player_before;
    u32 i, script_before, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 39;
    obj.state = 5;
    obj.unk5 = 5;
    obj.timer = 1;
    obj.x_pos.val = 100 * 65536 + 0x1357;
    obj.y_pos.val = 100 * 65536 + 0x2468;
    obj.x_vel.val = 0x1234;
    obj.y_vel.val = 0x5678;
    obj.unk2C = 0x2468;
    obj.animation_table = (u32**)split_mushroom_animations;
    obj.animation_cursor = split_mushroom_animations[16];
    obj.animation_step.packed = *(u32*)split_mushroom_animations[16];
    g_Player.x_pos.val = obj.x_pos.val;
    g_Player.y_pos.val = obj.y_pos.val + 400 * 65536;
    before = obj;
    player_before = g_Player;
    script_before = *(u32*)split_mushroom_animations[16];
    func_800A5194(&obj);
    before.unk5 = obj.unk5;
    before.timer = obj.timer;
    before.x_vel = obj.x_vel;
    before.y_vel = obj.y_vel;
    before.unk2C = obj.unk2C;
    before.animation_step = obj.animation_step;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    assert(obj.animation_table == (u32**)split_mushroom_animations && obj.animation_cursor == split_mushroom_animations[16]);
    assert(*(u32*)split_mushroom_animations[16] == script_before);
    if (observation == 0)
        actual = obj.x_vel.val;
    else if (observation == 1)
        actual = obj.y_vel.val;
    else if (observation == 2)
        actual = obj.unk2C;
    else if (observation == 3)
        actual = (u16)obj.timer | ((u32)(u8)obj.unk5 << 16);
    else
        actual = C_TEST_STEP(obj.animation_step.packed);
    return actual;
}
static const u32 mushroom_launch_context_cases_expected[] = { 0x0u, 0xFFFA23EDu, 0x1000u, 0x60000u, 0x3D010001u };

static struct WeaponObj sprout_owner;
#define ss state_room.shot
#define SPROUT(st, step, setup)                         \
    do {                                                \
        u8 stage = engine_obj.stage;                    \
        state_reset(step, 0, 0);                        \
        memset(&sprout_owner, 0, sizeof(sprout_owner)); \
        ss.active = 1;                                  \
        ss.state = st;                                  \
        ss.x_pos.i.hi = 0x80;                           \
        ss.y_pos.i.hi = 0x60;                           \
        ss.unk7C = &sprout_owner;                       \
        main_bss_state.frame_counter = 0;               \
        setup;                                          \
        mushroom_shot_update(&ss);                      \
        engine_obj.stage = stage;                       \
    } while (0)
static void msh_sprout_init(void)
{
    SPROUT(4, 0, 0);
}
static void msh_sprout_init_right(void) { SPROUT(4, 0, ss.unk15 = PLAYER_FACING_RIGHT); }
static void msh_grow_wait(void) { SPROUT(5, 0, 0); }
static void msh_grow_highway(void) { SPROUT(5, 0, (engine_obj.stage = 3, ss.animation_step.fields.event = 1)); }
static void msh_grow_rematch(void) { SPROUT(5, 0, (engine_obj.stage = 0xC, ss.animation_step.fields.event = 1)); }
static void msh_main_blink_highway(void) { SPROUT(5, 0, (engine_obj.stage = 3, ss.unk6 = 1, ss.unk7 = 3, main_bss_state.frame_counter = 1)); }
static void msh_main_blink(void) { SPROUT(5, 0, (engine_obj.stage = 0, ss.unk6 = 1, ss.unk7 = 1, main_bss_state.frame_counter = 1)); }
static void msh_main_steady(void) { SPROUT(5, 0, (ss.unk6 = 1, main_bss_state.frame_counter = 2)); }
static void msh_main_owner_gone(void) { SPROUT(5, 0, sprout_owner.state = 2); }
static void msh_main_away(void) { SPROUT(5, 0, ss.x_pos.i.hi = 0x1000); }
static void msh_main_hit(void) { SPROUT(5, 0, (so.hp = 1, state_hit(&so, 0, 0, 1))); }
static void msh_spray_init(void) { SPROUT(7, 0, ss.unk2 = 1); }
static void msh_spray_init_right(void) { SPROUT(7, 0, (ss.unk2 = 2, ss.unk15 = PLAYER_FACING_RIGHT)); }

static void (*const mushroom_sprout_states_cases[])(void) = {
    msh_sprout_init,
    msh_sprout_init_right,
    msh_grow_wait,
    msh_grow_highway,
    msh_grow_rematch,
    msh_main_blink_highway,
    msh_main_blink,
    msh_main_steady,
    msh_main_owner_gone,
    msh_main_away,
    msh_main_hit,
    msh_spray_init,
    msh_spray_init_right,
};
static const u32 mushroom_sprout_states_expected[] = { 5u, 0xFF000001u, 0x600000u, 0x600000u, 0u, 0xFFFD0000u, 0u, 0x50000u, 0u, 0u, 5u, 0xFF400001u, 0xA00000u, 0x600000u, 0u, 0xFFFD0000u, 0u, 0x50000u, 0u, 0u, 5u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10105u, 0xFF000001u, 0x800000u, 0x600000u, 0u, 0u, 0x380000u, 0x50000u | OBJECT_CLUT(0x78CC), 0u, 0u, 0x10105u, 0xFF000001u, 0x800000u, 0x600000u, 0u, 0u, 0x380000u, 0x50000u | OBJECT_CLUT(0x788C), 0u, 0u, 0x10005u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u | OBJECT_CLUT(0x78CC), 0u, 0u, 0x2010005u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u | OBJECT_CLUT(0x788E), 0u, 0u, 0x10005u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 6u, 1u, 0x10000000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 6u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x48000u, 0u, 0x2100u, 8u, 0xFF000101u, 0x740000u, 0x500000u, 0u, 0x18000u, 0x1000u, 0x50000u, 0u, 0u, 8u, 0xFF400201u, 0x7C0000u, 0x500000u, 0u, 0x18000u, 0xFFFFF000u, 0x50000u, 0u, 0u };

static u32 test_mushroom_sprout_states(u32 row)
{
    return object_run(mushroom_sprout_states_cases[row], row, &mushroom_sprout_states_expected[row * 10]);
}

void mushroom_shot_spore_fly(struct ShotObj*);
void mushroom_shot_spray_fly(struct ShotObj*);
extern void* split_mushroom_animations[];
extern u8 mushroom_shot_spore_hit_box[], mushroom_shot_sprout_hit_box[];
static const s16 screen_x[] = { -65, -64, 160, 383, 384 };
static u32 owner_cleanup(u32 row)
{
    struct ShotObj obj, expected;
    struct MainObj owner, owner_before;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 position = row % COUNT(screen_x), dead = row / COUNT(screen_x) % 2, spray = row / COUNT(screen_x) / 2 % 2, facing = row / COUNT(screen_x) / 4;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = 24;
    player_before = g_Player;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    owner.active = 0x41;
    owner.id = 61;
    owner.state = dead ? 2 : 1;
    owner_before = owner;
    obj.active = 0x41;
    obj.id = 39;
    obj.state = spray ? 8 : 1;
    obj.on_screen = 7;
    obj.unk15 = facing ? PLAYER_FACING_RIGHT : 0;
    obj.unk7C = WEAPON_OBJECT(&owner);
    obj.unk61 = 1;
    obj.timer = 20;
    obj.unk5C = 1;
    obj.unk60 = 6;
    obj.x_pos.val = screen_x[position] * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.x_vel.val = 0;
    obj.y_vel.val = spray ? 0x18000 : 0x48000;
    obj.unk2C = spray ? 0 : 0x2000;
    obj.unk50.data = spray ? mushroom_shot_sprout_hit_box : mushroom_shot_spore_hit_box;
    obj.animation_table = (u32**)split_mushroom_animations;
    set_animation(&obj, spray ? 18 : 11);
    assert(obj.animation_step.packed == (spray ? C_TEST_STEP(0x51010002) : C_TEST_STEP(0x2C010003)));
    expected = obj;
    expected.animation_step.fields.duration--;
    expected.y_pos.val -= obj.y_vel.val;
    expected.y_vel.val -= obj.unk2C;
    if (!spray)
        expected.timer--;
    if (dead)
        expected.active = expected.id = expected.unk2 = expected.on_screen = expected.state = expected.unk5 = expected.unk6 = expected.unk7 = 0;
    else if (position == 0 || position == 4)
        expected.state = spray ? 9 : 2;
    else
        expected.on_screen = position == 2;
    if (spray)
        mushroom_shot_spray_fly(&obj);
    else
        mushroom_shot_spore_fly(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

static u32 mushroom_steps(u32 row);
const struct CTestGroup c_test_groups[] = {
    { "mushroom_steps", 0, 0, 20, mushroom_steps },
    { "mushroom_sprout_states", 0, 0, COUNT(mushroom_sprout_states_cases), test_mushroom_sprout_states },
    { "mushroom_launch_context", NULL, mushroom_launch_context_cases_expected, COUNT(mushroom_launch_context_cases_expected), launch_case },
    { "spore_spray_owner_death_and_margin_boundaries", NULL, NULL, COUNT(screen_x) * 8, owner_cleanup },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(mushroom_sprout_states_cases) + COUNT(mushroom_launch_context_cases_expected) + COUNT(screen_x) * 8 + 20;

void mushroom_shot_spore_init(struct ShotObj*);
void mushroom_shot_spore_burst(struct ShotObj*);
void mushroom_shot_sprout_main(struct ShotObj*);
void mushroom_shot_sprout_hop(struct ShotObj*);
void mushroom_shot_sprout_land(struct ShotObj*);
void mushroom_shot_sprout_wait(struct ShotObj*);
void mushroom_shot_sprout_jump(struct ShotObj*);
void func_800A5194(struct ShotObj*);
extern s32 mushroom_shot_spore_x_speeds[];
static u32 mushroom_steps(u32 row)
{
    struct ShotObj obj;
    struct MainObj owner;
    u32 hurt;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    owner.state = 1;
    obj.active = 0x41;
    obj.id = 39;
    obj.state = 1;
    obj.unk7C = (struct WeaponObj*)&owner;
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 100;
    obj.unk60 = 6;
    obj.timer = 5;
    obj.animation_table = (u32**)split_mushroom_animations;
    set_animation(&obj, 0xB);
    obj.animation_step.fields.duration = 2;
    g_Player.hp = 16;
    g_Player.x_pos = obj.x_pos;
    g_Player.y_pos = obj.y_pos;
    MAIN_OBJECT(&g_Player)->hurt_box = (const u8*)&state_hit_box;
    obj.unk50.data = (const u8*)&state_hit_box;
    if (row == 2 || row == 3 || row == 5)
        obj.animation_step.fields.event = 1;
    if (row == 4 || row == 6)
        obj.animation_step.fields.event = 2;
    switch (row) {
    case 0:
    case 1:
        obj.state = 0;
        obj.unk2 = 1;
        obj.unk15 = row == 1 ? PLAYER_FACING_RIGHT : 0;
        mushroom_shot_spore_init(&obj);
        assert(obj.state == 1 && obj.timer == 0x28 && obj.unk17 == 0xB);
        assert(obj.x_vel.val == (row == 0 ? mushroom_shot_spore_x_speeds[1] : -mushroom_shot_spore_x_speeds[1]));
        break;
    case 2:
        obj.timer = 1;
        obj.y_vel.val = 0x2000;
        obj.unk2C = 0x2000;
        mushroom_shot_spore_fly(&obj);
        assert(obj.unk2C == 0x1000 && obj.state == 2 && obj.unk17 == 0xD);
        break;
    case 3:
    case 4:
        obj.state = 2;
        mushroom_shot_spore_burst(&obj);
        assert(obj.state == (row == 4 ? 3 : 2));
        break;
    case 5:
    case 6:
        obj.state = 8;
        mushroom_shot_spray_fly(&obj);
        assert(obj.state == (row == 6 ? 9 : 8));
        break;
    case 7:
        obj.state = 5;
        obj.unk5 = 6;
        obj.unk70 = 8;
        obj.unk68 = (struct Unk_unk68*)&state_hit_box;
        obj.unk50.data = NULL;
        mushroom_shot_sprout_main(&obj);
        assert(obj.unk70 == 8 && obj.state == 5);
        break;
    case 8:
    case 9:
    case 10:
        obj.unk5 = 1;
        obj.unk84.bytes[0] = row == 9;
        obj.y_vel.val = row == 10 ? 0x20000 : -0x10000;
        obj.unk70 = row == 8 ? 8 : 0;
        set_animation(&obj, 2);
        mushroom_shot_sprout_hop(&obj);
        assert(obj.unk84.bytes[0] == (row != 10) && obj.unk5 == (row == 8 ? 2 : 1));
        assert(obj.unk17 == (row == 8 ? 0xA : 2));
        break;
    case 11:
    case 12:
    case 13:
        obj.unk5 = 2;
        obj.unk8A = row == 11 ? 1 : 3;
        obj.animation_step.fields.event = row != 13;
        mushroom_shot_sprout_land(&obj);
        assert(obj.unk5 == (row == 11 ? 3 : row == 12 ? 4
                                                      : 2)
            && obj.unk17 == (row == 11 ? 0 : row == 12 ? 2
                                                       : 0xB));
        assert(obj.timer == (row == 11 ? 0x28 : 5));
        break;
    case 14:
    case 15:
        obj.unk5 = 3;
        obj.timer = row == 14 ? 1 : 2;
        mushroom_shot_sprout_wait(&obj);
        assert(obj.unk5 == (row == 14 ? 5 : 3) && obj.timer == (row == 14 ? 0x28 : 1));
        break;
    case 16:
    case 17:
        obj.unk5 = 4;
        obj.animation_step.fields.event = row == 16;
        obj.unk84.bytes[0] = 1;
        mushroom_shot_sprout_jump(&obj);
        assert(obj.unk5 == (row == 16 ? 1 : 4) && obj.unk84.bytes[0] == (row == 17));
        assert(obj.y_pos.val == (row == 16 ? (100 << 16) - 0x40000 : 100 << 16));
        break;
    case 19:
        obj.unk5 = 5;
        obj.timer = 2;
        func_800A5194(&obj);
        assert(obj.unk5 == 5 && obj.timer == 1 && obj.x_vel.val == 0);
        break;
    default:
        obj.unk5 = 5;
        obj.timer = 1;
        g_Player.x_pos.i.hi = 60;
        g_Player.y_pos.i.hi = 80;
        func_800A5194(&obj);
        assert(obj.unk5 == 6 && obj.unk2C == 0x1000);
        assert(obj.x_vel.val < 0 && obj.x_vel.val >= -0x60000 && obj.y_vel.val > 0 && obj.y_vel.val <= 0x60000);
        break;
    }
    hurt = HP_DAMAGE_FLAG(g_Player.hp) != 0;
    assert(hurt == (row == 2 || row == 3 || row == 5));
    return 1;
}
