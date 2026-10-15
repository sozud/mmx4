#include "test_runtime.h"
void wall_crawler_update_surface(struct MainObj*);
extern union AnimationStep* wall_crawler_animations[25];
extern struct Unk_unk68 D_800FB568;
extern struct Unk_unk68 D_800FB56C;
extern struct Unk_unk68 wall_crawler_terrain_box;

static u32 wall_turns_left(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_11.unk80 = 1;
    obj.collision_flags = 12;
    SP_CUR_MAIN_OBJ = &obj;
    wall_crawler_update_surface(&obj);
    return obj.ext.main_11.unk80;
}

static u32 wall_turns_right(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_11.unk80 = 1;
    obj.collision_flags = 14;
    SP_CUR_MAIN_OBJ = &obj;
    wall_crawler_update_surface(&obj);
    return obj.ext.main_11.unk80;
}

static u32 wall_stays_blocked(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_11.unk80 = 1;
    obj.collision_flags = 15;
    SP_CUR_MAIN_OBJ = &obj;
    wall_crawler_update_surface(&obj);
    return obj.ext.main_11.unk80;
}

static u32 floor_turns_down(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_11.unk80 = 4;
    obj.collision_flags = 3;
    SP_CUR_MAIN_OBJ = &obj;
    wall_crawler_update_surface(&obj);
    return obj.ext.main_11.unk80;
}

static u32 floor_turns_up(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_11.unk80 = 4;
    obj.collision_flags = 7;
    SP_CUR_MAIN_OBJ = &obj;
    wall_crawler_update_surface(&obj);
    return obj.ext.main_11.unk80;
}

static u32 floor_stays_blocked(void)
{
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.ext.main_11.unk80 = 4;
    obj.collision_flags = 15;
    SP_CUR_MAIN_OBJ = &obj;
    wall_crawler_update_surface(&obj);
    return obj.ext.main_11.unk80;
}
static const CTestCase wall_crawler_cases[] = {
    wall_turns_left,
    wall_turns_right,
    wall_stays_blocked,
    floor_turns_down,
    floor_turns_up,
    floor_stays_blocked,
};
static const u32 wall_crawler_cases_expected[] = { 0x1u, 0x2u, 0x1u, 0x4u, 0x8u, 0x4u };

static const u8 angles[] = { 0, 8, 8 };
static const s8 events[] = { 0, 0, 1 };
static u32 corner_case(u32 mode, u32 observation)
{
    struct MainObj obj, before, context, context_before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&context, 0, sizeof(context));
    obj.active = 0x41;
    obj.id = 11;
    obj.state = 1;
    obj.unk6 = 4;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)wall_crawler_animations;
    set_animation(&obj, 0);
    obj.animation_step.fields.event = events[mode];
    context.ext.main_11.angle = angles[mode];
    context.ext.main_11.unk85 = 0x27;
    before = obj;
    context_before = context;
    SP_CUR_MAIN_OBJ = &context;
    func_8004B418(&obj);
    assert(SP_CUR_MAIN_OBJ == &context);
    if (mode != 1) {
        before.unk17 = mode == 0 ? 0x11 : 0x13;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)wall_crawler_animations[before.unk17];
        before.animation_step = *wall_crawler_animations[before.unk17];
        before.unk6++;
        context_before.ext.main_11.unk85++;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(context) / 4; i++)
        assert(((u32*)&context)[i] == ((u32*)&context_before)[i]);
    actual = observation == 0 ? obj.unk17 | ((u32)(u8)obj.unk6 << 8) | ((u32)context.ext.main_11.unk85 << 16) : obj.animation_step.packed;
    return actual;
}
#define CASE(m, n)                                                  \
    static u32 wall_crawler_corner_animation_corner_##m##_##n(void) \
    {                                                               \
        return corner_case(m, n);                                   \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1)
MODE(0)
MODE(1)
MODE(2)
#define ENTRY(m, n) wall_crawler_corner_animation_corner_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1)
static const CTestCase wall_crawler_corner_animation_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) };
static const u32 wall_crawler_corner_animation_cases_expected[] = { 0x280511u, 0x2010001u, 0x270400u, 0x10001u, 0x280513u, 0xA010001u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static u32 pursuit_case(u32 mode)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    u8* context;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 11;
    obj.state = 1;
    obj.unk5 = 0x27;
    obj.unk6 = 0x28;
    obj.unk2 = mode;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = (mode ? 200 : 344) * 65536 + 0x5678;
    g_Player.x_pos.val = (mode ? 132 : 100) * 65536 + 0x1234;
    g_Player.y_pos.val = 200 * 65536 + 0x5678;
    context = (u8*)&obj.ext;
    *(u16*)(context + 2) = 1;
    context[4] = 0x29;
    before = obj;
    player_before = g_Player;
    SP_CUR_MAIN_OBJ = &obj;
    func_8004B0A0(&obj);
    before.unk5 = obj.unk5;
    before.unk6 = mode ? 0 : 0x28;
    ((u8*)&before.ext)[2] = context[2];
    ((u8*)&before.ext)[3] = context[3];
    ((u8*)&before.ext)[4] = context[4];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(SP_CUR_MAIN_OBJ == &obj);
    actual = *(u16*)(context + 2) | ((u32)context[4] << 16) | ((u32)(u8)obj.unk5 << 24);
    return actual;
}
static u32 vertical_boundary(void)
{
    return pursuit_case(0);
}
static u32 timer_expiry(void)
{
    return pursuit_case(1);
}
static const CTestCase wall_crawler_pursuit_context_cases[] = {
    vertical_boundary,
    timer_expiry,
};
static const u32 wall_crawler_pursuit_context_cases_expected[] = { 0x229003Cu, 0x5000000u };

static u32 turn_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 11;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 9;
    obj.unk2 = mode < 3 ? 0 : mode == 3 ? 1
                                        : -1;
    obj.unk15 = mode == 2 || mode == 4 ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 12345;
    obj.y_speed = -54321;
    obj.animation_table = (const u8* const*)wall_crawler_animations;
    set_animation(&obj, 1);
    obj.animation_step.fields.event = mode == 0 ? 0 : 1;
    expected = obj;
    if (mode) {
        expected.unk15 ^= 0x40;
        expected.unk5 = mode < 3 ? 2 : 4;
        expected.unk17 = 0;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)wall_crawler_animations[0];
        expected.animation_step = wall_crawler_animations[0][0];
    }
    wall_crawler_turn(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return obj.unk15 | ((u32)(u8)obj.unk5 << 8) | ((u32)obj.unk17 << 16);
}
#define CASE(m)                                           \
    static u32 wall_crawler_turn_animation_turn_##m(void) \
    {                                                     \
        return turn_case(m);                              \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
#define ENTRY(m) wall_crawler_turn_animation_turn_##m,
static const CTestCase wall_crawler_turn_animation_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) };
static const u32 wall_crawler_turn_animation_cases_expected[] = { 0x10300u, 0x240u, 0x200u, 0x440u, 0x400u };
#undef CASE
#undef ENTRY

struct func_8004A78C_case {
    u32 g_Player_x_pos, obj_x_pos;
    u32 expected[17];
};
static const struct func_8004A78C_case func_8004A78C_cases[] = {
    { 220605556, 220605556, { 2u, 0u, 0u, 3u, 0x8000u, 1u, 0u, 2u, 0x40u, 6u, 0u, 0u, 0u, 0xD27u, 0u, 0u, 0u } },
    { -1, 0, { 1u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 6u, 2u, 0u, 0u, 0xFFFEu, 0xFFFE8000u, 0u, 0u } },
    { -2, 294879232, { 1u, 0u, 0u, 3u, 0x8000u, 1u, 0u, 2u, 0u, 6u, 0u, 0u, 0u, 0x1192u, 0u, 0u, 0u } },
    { 349110272, 349110272, { 2u, 0u, 0u, 3u, 0x8000u, 1u, 0u, 2u, 0x40u, 6u, 0u, 0u, 0u, 0x14D0u, 0u, 0u, 0u } },
    { 393062584, 393062584, { 2u, 0u, 0u, 3u, 0x8000u, 1u, 0u, 2u, 0x40u, 6u, 0u, 0u, 0u, 0x176Fu, 0u, 0u, 0u } },
};
static u32 test_func_8004A78C(u32 row)
{
    const struct func_8004A78C_case* c = &func_8004A78C_cases[row];
    u32 observed_values[17];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_800FB568, 0, sizeof(D_800FB568));
    memset(&D_800FB56C, 0, sizeof(D_800FB56C));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&wall_crawler_terrain_box, 0, sizeof(wall_crawler_terrain_box));
    g_Player.x_pos.val = c->g_Player_x_pos;
    obj.x_pos.val = c->obj_x_pos;
    child_0_present = 255;
    engine_obj.character_state.fields.active = -1;
    SP_CUR_MAIN_OBJ = child_0_present ? &child_0 : NULL;
    func_8004A78C(&obj);
    observed_values[0] = (u32)child_0.ext.main_11.unk80;
    observed_values[1] = (u32)obj.air_state;
    observed_values[2] = (u32)obj.bg_offset;
    observed_values[3] = (u32)obj.contact_damage;
    observed_values[4] = (u32)obj.gravity;
    observed_values[5] = (u32)obj.hp;
    observed_values[6] = (u32)obj.invincibility_timer;
    observed_values[7] = (u32)obj.state;
    observed_values[8] = (u32)obj.unk15;
    observed_values[9] = (u32)obj.unk16;
    observed_values[10] = (u32)obj.unk5;
    observed_values[11] = (u32)obj.unk6;
    observed_values[12] = (u32)obj.x_accel;
    observed_values[13] = (u32)obj.x_pos.u.hi;
    observed_values[14] = (u32)obj.x_speed;
    observed_values[15] = (u32)obj.y_pos.u.hi;
    observed_values[16] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 17);
}

struct func_8004B0A0_case {
    u32 obj_x_pos_hi, g_Player_x_pos_hi, obj_y_pos_hi, g_Player_y_pos_hi;
    u32 expected[4];
};
static const struct func_8004B0A0_case func_8004B0A0_cases[] = {
    { 32761, -32768, 14704, 16455, { 0x18u, 0x4047u, 0u, 0u } },
    { 0, 0, 0, 0, { 0x10u, 0u, 5u, 0u } },
    { 0, 16386, -48, 0, { 0u, 0u, 0u, 0u } },
};
static u32 test_func_8004B0A0(u32 row)
{
    const struct func_8004B0A0_case* c = &func_8004B0A0_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&g_Player, 0, sizeof(g_Player));
    child_0_present = 255;
    obj.unk2 = -1;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    obj.y_pos.i.hi = c->obj_y_pos_hi;
    g_Player.y_pos.i.hi = c->g_Player_y_pos_hi;
    SP_CUR_MAIN_OBJ = child_0_present ? &child_0 : NULL;
    func_8004B0A0(&obj);
    observed_values[0] = (u32)((u8*)&child_0.ext)[4];
    observed_values[1] = (u32)g_Player.y_pos.i.hi;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

const struct CTestGroup c_test_groups[] = {
    { "wall_crawler", wall_crawler_cases, wall_crawler_cases_expected, COUNT(wall_crawler_cases), 0 },
    { "wall_crawler_corner_animation", wall_crawler_corner_animation_cases, wall_crawler_corner_animation_cases_expected, COUNT(wall_crawler_corner_animation_cases), 0 },
    { "wall_crawler_pursuit_context", wall_crawler_pursuit_context_cases, wall_crawler_pursuit_context_cases_expected, COUNT(wall_crawler_pursuit_context_cases), 0 },
    { "wall_crawler_turn_animation", wall_crawler_turn_animation_cases, wall_crawler_turn_animation_cases_expected, COUNT(wall_crawler_turn_animation_cases), 0 },
    { "func_8004A78C", 0, 0, 5, test_func_8004A78C },
    { "func_8004B0A0", 0, 0, 3, test_func_8004B0A0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(wall_crawler_cases) + COUNT(wall_crawler_corner_animation_cases) + COUNT(wall_crawler_pursuit_context_cases) + COUNT(wall_crawler_turn_animation_cases) + 5 + 3;
