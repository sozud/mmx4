#include "test_runtime.h"
#include "main/mains/main_11_wall_crawler.h"
#include "main/55C4.h"
#include "support/state_cases.h"
void func_8004B2BC(struct MainObj*);
void wall_crawler_drop(struct MainObj* arg0);
void wall_crawler_next_state(struct MainObj*);
void wall_crawler_resume_step(struct MainObj* arg0);
void func_8004AE20(struct MainObj* arg0);
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
static const u32 wall_crawler_corner_animation_cases_expected[] = { 0x280511u, 0x2010001u, 0x270400u, 0x10001u, 0x280513u, 0xA010001u };
static u32 wall_crawler_corner_animation_cases_row(u32 row)
{
    return corner_case(row / 2, row % 2);
}

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
static const u32 wall_crawler_turn_animation_cases_expected[] = { 0x10300u, 0x240u, 0x200u, 0x440u, 0x400u };

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
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.unk2 = -1;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    obj.y_pos.i.hi = c->obj_y_pos_hi;
    g_Player.y_pos.i.hi = c->g_Player_y_pos_hi;
    SP_CUR_MAIN_OBJ = &child_0;
    func_8004B0A0(&obj);
    observed_values[0] = (u32)((u8*)&child_0.ext)[4];
    observed_values[1] = (u32)g_Player.y_pos.i.hi;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

#define WC(step, kind) (state_reset(step, 0, 0), so.unk2 = kind, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x40, so.terrain_box = &state_hit_box, so.animation_table = (void*)state_table)
#define CRAWL(kind, mode, flags, facing, body)     \
    do {                                           \
        struct MainObj* current = SP_CUR_MAIN_OBJ; \
        WC(2, kind);                               \
        SP_CUR_MAIN_OBJ = &so;                     \
        so.ext.main_11.unk80 = mode;               \
        so.collision_flags = flags;                \
        so.unk15 = facing;                         \
        body;                                      \
        func_8004AE20(&so);                        \
        SP_CUR_MAIN_OBJ = current;                 \
        so.unk7E = so.ext.main_11.unk80;           \
    } while (0)
#define SPAWN(kind, px, x, awake)                          \
    do {                                                   \
        struct MainObj* current = SP_CUR_MAIN_OBJ;         \
        u8 was = engine_obj.character_state.fields.active; \
        WC(0, kind);                                       \
        SP_CUR_MAIN_OBJ = &so;                             \
        so.x_pos.i.hi = x;                                 \
        g_Player.x_pos.i.hi = px;                          \
        engine_obj.character_state.fields.active = awake;  \
        func_8004A78C(&so);                                \
        SP_CUR_MAIN_OBJ = current;                         \
        engine_obj.character_state.fields.active = was;    \
        so.unk7E = so.ext.main_11.unk80;                   \
    } while (0)
static void wc_seek_left(void)
{
    CRAWL(0, 1, 0, 0, );
}
static void wc_seek_left_wall(void) { CRAWL(0, 1, 2, 0, ); }
static void wc_seek_right_wall(void) { CRAWL(0, 2, 1, 0, ); }
static void wc_seek_right(void) { CRAWL(0, 2, 0, 0, ); }
static void wc_seek_down_wall(void) { CRAWL(0, 4, 4, 0, ); }
static void wc_seek_down(void) { CRAWL(0, 4, 0, 0, ); }
static void wc_seek_up_wall(void) { CRAWL(0, 8, 8, 0, ); }
static void wc_seek_up(void) { CRAWL(0, 8, 0, 0, ); }
static void wc_seek_other(void) { CRAWL(0, 3, 0, 0, ); }
static void wc_watch_right_near(void) { CRAWL(1, 0, 0, 0x40, g_Player.x_pos.i.hi = 0x70); }
static void wc_watch_right_far(void) { CRAWL(1, 0, 0, 0x40, g_Player.x_pos.i.hi = 0x40); }
static void wc_watch_left_near(void) { CRAWL(1, 0, 0, 0, g_Player.x_pos.i.hi = 0x90); }
static void wc_watch_left_far(void) { CRAWL(1, 0, 0, 0, g_Player.x_pos.i.hi = 0xC0); }
static void wc_surface_left(void) { CRAWL(0, 0x11, 0xC, 0, ); }
static void wc_surface_left_turn(void) { CRAWL(0, 0x11, 0xC, 0x40, ); }
static void wc_surface_right(void) { CRAWL(0, 0x12, 0xE, 0x40, ); }
static void wc_surface_right_turn(void) { CRAWL(0, 0x12, 0xE, 0, ); }
static void wc_surface_down(void) { CRAWL(0, 0x11, 0, 0, ); }
static void wc_surface_corner(void) { CRAWL(0, 0x11, 0xF, 0, ); }
static void wc_climb_left(void) { CRAWL(0, 0x14, 0, 0, ); }
static void wc_climb_right(void) { CRAWL(0, 0x14, 2, 0x40, ); }
static void wc_climb_down(void) { CRAWL(0, 0x14, 3, 0, ); }
static void wc_climb_up(void) { CRAWL(0, 0x14, 7, 0, ); }
static void wc_climb_corner(void) { CRAWL(0, 0x14, 0xF, 0, ); }
static void wc_surface_up(void) { CRAWL(0, 0x11, 4, 0, ); }
static void wc_resume(void)
{
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    WC(1, 0);
    SP_CUR_MAIN_OBJ = &so;
    so.ext.main_11.saved_unk5 = 4;
    wall_crawler_resume_step(&so);
    SP_CUR_MAIN_OBJ = current;
}
static void wc_next(void)
{
    WC(1, 0);
    wall_crawler_next_state(&so);
}
static void wc_drop(void)
{
    WC(5, 0);
    so.y_speed = 0x10000;
    wall_crawler_drop(&so);
}
static void wc_spawn_hanging(void) { SPAWN(2, 0, 0x85, 0); }
static void wc_spawn_left(void) { SPAWN(0, 0, 0x80, 0); }
static void wc_spawn_right(void) { SPAWN(1, 0x100, 0x80, 0); }
static void wc_spawn_dormant(void) { SPAWN(0, 0, 0xD00, 1); }
static void wc_spawn_dormant_b(void) { SPAWN(0, 0, 0x1100, 1); }
static void wc_spawn_dormant_c(void) { SPAWN(0, 0, 0x1400, 1); }
static void wc_spawn_dormant_d(void) { SPAWN(0, 0, 0x1700, 1); }
static void wc_spawn_awake(void) { SPAWN(0, 0, 0x80, 1); }

static void (*const wall_crawler_states_cases[])(void) = {
    wc_seek_left,
    wc_seek_left_wall,
    wc_seek_right_wall,
    wc_seek_right,
    wc_seek_down_wall,
    wc_seek_down,
    wc_seek_up_wall,
    wc_seek_up,
    wc_seek_other,
    wc_watch_right_near,
    wc_watch_right_far,
    wc_watch_left_near,
    wc_watch_left_far,
    wc_surface_left,
    wc_surface_left_turn,
    wc_surface_right,
    wc_surface_right_turn,
    wc_surface_down,
    wc_surface_corner,
    wc_climb_left,
    wc_climb_right,
    wc_climb_down,
    wc_climb_up,
    wc_climb_corner,
    wc_surface_up,
    wc_resume,
    wc_next,
    wc_drop,
    wc_spawn_hanging,
    wc_spawn_left,
    wc_spawn_right,
    wc_spawn_dormant,
    wc_spawn_dormant_b,
    wc_spawn_dormant_c,
    wc_spawn_dormant_d,
    wc_spawn_awake,
};
static const u32 wall_crawler_states_expected[] = { 2u, 0x10000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x110000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x120000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x20000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x140000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x40000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x180000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x80000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x30000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 3u, 0u, 0x800000u, 0u, 0u, 0u, 0x4002u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0x800000u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 2u, 0x10000u, 0x7E8000u, 0xFFFE8000u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0x10000u, 0x7E8000u, 0xFFFE8000u, 0u, 0u, 0x4002u, 0u, 0u, 0u, 2u, 0x20000u, 0x818000u, 0x18000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 3u, 0x20000u, 0x818000u, 0x18000u, 0u, 0u, 2u, 0u, 0u, 0u, 2u, 0x40000u, 0x800000u, 0u, 0x18000u, 0u, 1u, 0u, 0u, 0u, 2u, 0x110000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x10000u, 0x7E8000u, 0xFFFE8000u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x20000u, 0x818000u, 0x18000u, 0u, 0u, 0x4000u, 0u, 0u, 0u, 2u, 0x40000u, 0x800000u, 0u, 0x18000u, 0u, 1u, 0u, 0u, 0u, 2u, 0x80000u, 0x800000u, 0u, 0xFFFE8000u, 0u, 1u, 0u, 0u, 0u, 2u, 0x140000u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0x80000u, 0x800000u, 0u, 0xFFFE8000u, 0u, 1u, 0u, 0u, 0u, 4u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 5u, 0u, 0x800000u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 7u, 0u, 0x880000u, 0u, 0u, 0u, 0x17u, 0x50002u, 0u, 0u, 2u, 0x10000u, 0x7E8000u, 0xFFFE8000u, 0u, 0u, 0u, 0x50003u, 0u, 0u, 2u, 0x20000u, 0x818000u, 0x18000u, 0u, 0u, 0x4000u, 0x50003u, 0u, 0u, 0u, 0x10000u, 0xCFE8000u, 0u, 0u, 0x800000u, 0x16u, 0x10003u, 0u, 0u, 0u, 0x10000u, 0x10FE8000u, 0u, 0u, 0x800000u, 0x16u, 0x10003u, 0u, 0u, 0u, 0x10000u, 0x13FE8000u, 0u, 0u, 0x800000u, 0x16u, 0x10003u, 0u, 0u, 0u, 0x10000u, 0x16FE8000u, 0u, 0u, 0x800000u, 0x16u, 0x10003u, 0u, 0u, 2u, 0x10000u, 0x7E8000u, 0xFFFE8000u, 0u, 0u, 0u, 3u, 0u, 0u };

static u32 test_wall_crawler_states(u32 row)
{
    return state_run(wall_crawler_states_cases[row], row, &wall_crawler_states_expected[row * 10]);
}

static u32 test_corner_aim_angles(u32 row)
{
    static const s16 targets[32][2] = {
        { 128, 0 },
        { 126, -25 },
        { 118, -49 },
        { 106, -71 },
        { 91, -91 },
        { 71, -106 },
        { 49, -118 },
        { 25, -126 },
        { 0, -128 },
        { -25, -126 },
        { -49, -118 },
        { -71, -106 },
        { -91, -91 },
        { -106, -71 },
        { -118, -49 },
        { -126, -25 },
        { -128, 0 },
        { -126, 25 },
        { -118, 49 },
        { -106, 71 },
        { -91, 91 },
        { -71, 106 },
        { -49, 118 },
        { -25, 126 },
        { 0, 128 },
        { 25, 126 },
        { 49, 118 },
        { 71, 106 },
        { 91, 91 },
        { 106, 71 },
        { 118, 49 },
        { 126, 25 },
    };
    static const s8 animations[16] = {
        -1,
        7,
        7,
        7,
        3,
        7,
        7,
        7,
        -1,
        9,
        9,
        9,
        5,
        9,
        9,
        9,
    };
    static const u8 facing[16] = {
        0x40,
        0x40,
        0x40,
        0x40,
        0x2A,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0x2A,
        0x40,
        0x40,
        0x40,
    };
    struct MainObj obj, expected, context, context_expected;
    struct PlayerObj player_before;
    s32 animation = animations[row / 2];
    memset(&obj, 0, sizeof(obj));
    memset(&context, 0, sizeof(context));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 11;
    obj.state = 1;
    obj.unk6 = 0;
    obj.unk15 = 0x2A;
    obj.x_pos.val = 200 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)wall_crawler_animations;
    set_animation(&obj, 0);
    g_Player.x_pos.val = (200 + targets[row][0]) * 65536 + 0x1234;
    g_Player.y_pos.val = (200 + targets[row][1]) * 65536 + 0x5678;
    g_Player.hp = 20;
    context.active = 0x41;
    context.id = 11;
    context.ext.main_11.angle = 0x17;
    context.ext.main_11.unk85 = 0x27;
    context.ext.main_11.unk86 = 0x31;
    expected = obj;
    context_expected = context;
    player_before = g_Player;
    context_expected.ext.main_11.angle = row;
    context_expected.ext.main_11.unk85 = 0;
    context_expected.ext.main_11.unk86 = 20;
    expected.unk15 = facing[row / 2];
    expected.unk6 = 1;
    if (animation >= 0) {
        expected.unk17 = animation;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)wall_crawler_animations[animation];
        expected.animation_step = *wall_crawler_animations[animation];
    }
    SP_CUR_MAIN_OBJ = &context;
    func_8004B2BC(&obj);
    assert(SP_CUR_MAIN_OBJ == &context);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&context, &context_expected, sizeof(context));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

static u32 test_corner_resume_angles(u32 row)
{
    static const s8 animations[16] = {
        -1,
        18,
        18,
        18,
        19,
        18,
        18,
        18,
        -1,
        20,
        20,
        20,
        21,
        20,
        20,
        20,
    };
    struct MainObj obj, expected, context, context_expected;
    struct PlayerObj player_before = g_Player;
    u32 angle = row / 2, timer = row % 2 + 1;
    s32 animation = animations[angle / 2];
    memset(&obj, 0, sizeof(obj));
    memset(&context, 0, sizeof(context));
    obj.active = 0x41;
    obj.id = 11;
    obj.state = 1;
    obj.unk6 = 4;
    obj.unk15 = 0x40;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)wall_crawler_animations;
    set_animation(&obj, 0);
    context.active = 0x41;
    context.id = 11;
    context.ext.main_11.angle = angle;
    context.ext.main_11.unk85 = 0x27;
    context.ext.main_11.unk86 = timer;
    expected = obj;
    context_expected = context;
    context_expected.ext.main_11.unk86 = timer - 1;
    if (timer == 1) {
        expected.unk6 = 5;
        context_expected.ext.main_11.unk85 = 0;
        if (animation >= 0) {
            expected.unk17 = animation;
            expected.previous_animation_index = 0xFF;
            expected.animation_cursor = (const u8*)wall_crawler_animations[animation];
            expected.animation_step = *wall_crawler_animations[animation];
        }
    }
    SP_CUR_MAIN_OBJ = &context;
    func_8004B668(&obj);
    assert(SP_CUR_MAIN_OBJ == &context);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&context, &context_expected, sizeof(context));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

extern union AnimationStep* wall_crawler_animations[25];
static const u8 animations[16] = { 17, 18, 18, 18, 19, 18, 18, 18, 17, 20, 20, 20, 21, 20, 20, 20 };
static const u32 first_words[] = { 0x02010001, 0x04010001, 0x0A010001, 0x0C010001, 0x0E010001 };
static u32 aim_animation(u32 row)
{
    struct MainObj obj, expected, context, context_expected;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 angle = row % 32, event = row / 32 % 3, counter = row / 96, animation = animations[angle / 2];
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(&obj, 0, sizeof(obj));
    memset(&context, 0, sizeof(context));
    obj.active = 0x41;
    obj.id = 11;
    obj.state = 2;
    obj.unk5 = 5;
    obj.unk6 = counter ? 0x7E : 0;
    obj.x_pos.val = 0x641234;
    obj.y_pos.val = 0x785678;
    obj.x_speed = 0x12345;
    obj.y_speed = -0x2468;
    obj.animation_table = (const u8* const*)wall_crawler_animations;
    set_animation(&obj, 0);
    obj.animation_step.fields.event = event;
    obj.previous_animation_index = 0x35;
    context.active = 0x41;
    context.ext.main_11.angle = angle;
    context.ext.main_11.unk85 = counter ? 255 : 0;
    expected = obj;
    context_expected = context;
    if (animation == 17 || event == 1) {
        expected.unk17 = animation;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)wall_crawler_animations[animation];
        expected.animation_step.packed = first_words[animation - 17];
        expected.unk6++;
        context_expected.ext.main_11.unk85 = counter ? 0 : 1;
    }
    SP_CUR_MAIN_OBJ = &context;
    func_8004B418(&obj);
    assert(SP_CUR_MAIN_OBJ == &context);
    SP_CUR_MAIN_OBJ = current;
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&context, &context_expected, sizeof(context));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}

extern union AnimationStep* wall_crawler_animations[25];
extern struct Unk_unk68 wall_crawler_terrain_box;
extern struct Unk_unk68 D_801067F0[];
static const u8 available_slots[] = { 0, 1, 15, 16, 32 };
static const s32 vectors[16][2] = {
    { 65536, 0 },
    { 0xEC83, 0x61F7 },
    { 0xB505, 0xB505 },
    { 0x61F7, 0xEC83 },
    { 0, 65536 },
    { -0x61F7, 0xEC83 },
    { -0xB505, 0xB505 },
    { -0xEC83, 0x61F7 },
    { -65536, 0 },
    { -0xEC83, -0x61F7 },
    { -0xB505, -0xB505 },
    { -0x61F7, -0xEC83 },
    { 0, -65536 },
    { 0x61F7, -0xEC83 },
    { 0xB505, -0xB505 },
    { 0xEC83, -0x61F7 },
};
static struct ShotObj shots_expected[32];
static struct VisualObj visuals_expected[32];
static struct WeaponObj weapons_before[16];
#define SAME(a, b) assert(c_test_word_difference((const u32*)&(a), (const u32*)&(b), sizeof(a) / 4) == 0)
static u32 contact_death(u32 row)
{
    struct MainObj obj, expected;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct PlayerObj player_before;
    struct EngineObj engine_before = engine_obj;
    struct BackgroundObj backgrounds_before[3];
    u32 available = available_slots[row % 5], visual_free = row / 5 % 2, facing = row / 10 % 2, absolute = row / 20, i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        struct ShotObj* s = &shot_objects[i];
        s->active = i < 32 - available;
        s->id = 39;
        s->state = 40;
        s->unk2 = 9;
        s->unk50.data = s->unk54 = (const u8*)&wall_crawler_terrain_box;
        s->unk68 = &wall_crawler_terrain_box;
        s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = s->unk72 = s->unk73 = s->unk74 = 7;
        s->unk76 = s->unk77 = s->unk78 = s->unk62 = s->unk63 = s->unk7A = s->unk75 = 7;
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
    }
    if (visual_free)
        visual_objects[31].active = 0;
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    memcpy(visuals_expected, visual_objects, sizeof(visuals_expected));
    obj.active = 0x41;
    obj.id = 11;
    obj.state = 2;
    obj.unk5 = 2;
    obj.unk6 = 9;
    obj.unk15 = facing ? 0x40 : 0;
    obj.bg_offset = absolute ? -1 : 0;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    obj.unk18.val = 0x1234;
    obj.unk1C.val = 0x5678;
    obj.unk42 = 0x9234;
    obj.unk65 = 7;
    obj.attack_box = obj.hurt_box = &wall_crawler_terrain_box;
    obj.collision_data = D_801067F0;
    obj.animation_table = (const u8* const*)wall_crawler_animations;
    set_animation(&obj, 0);
    g_Player.x_pos = obj.x_pos;
    g_Player.y_pos = obj.y_pos;
    g_Player.unk15 = obj.unk15;
    g_Player.unk54 = (const u32*)&wall_crawler_terrain_box;
    g_Player.spike_immune = 1;
    player_before = g_Player;
    expected = obj;
    expected.unk18 = obj.x_pos;
    expected.unk1C = obj.y_pos;
    expected.unk42 = 0x1234;
    expected.unk65 = 0;
    expected.ext.main_11.saved_unk5 = 2;
    expected.ext.main_11.unk86 = 16;
    expected.state = 3;
    for (i = 0; i < available && i < 16; i++) {
        struct ShotObj* s = &shots_expected[32 - available + i];
        s->active = 0x41;
        s->id = 10;
        s->bg_offset = obj.bg_offset;
        s->x_pos = obj.x_pos;
        s->y_pos = obj.y_pos;
        s->unk2 = i * 2;
        s->x_vel.val = vectors[i][0];
        s->y_vel.val = vectors[i][1];
        s->unk50.data = s->unk54 = NULL;
        s->unk68 = NULL;
        s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = s->unk72 = s->unk73 = s->unk74 = 0;
        s->unk76 = s->unk77 = s->unk78 = s->unk62 = s->unk63 = s->unk7A = s->unk75 = 0;
    }
    if (visual_free) {
        struct VisualObj* v = &visuals_expected[31];
        v->active = 0x21;
        v->id = 4;
        v->unk2 = 0;
        v->unk5C.value = 1;
        v->x_pos.val = 160 * 65536;
        v->y_pos.val = 120 * 65536;
        v->unk16 = 1;
    }
    cur_random = 0x1234;
    SP_CUR_MAIN_OBJ = &obj;
    func_8004AB6C(&obj);
    assert(SP_CUR_MAIN_OBJ == &obj && cur_random == 0x366A);
    SP_CUR_MAIN_OBJ = current;
    SAME(obj, expected);
    SAME(g_Player, player_before);
    SAME(engine_obj, engine_before);
    SAME(background_objects, backgrounds_before);
    SAME(shot_objects, shots_expected);
    SAME(visual_objects, visuals_expected);
    SAME(weapon_objects, weapons_before);
    return 1;
}

void func_8004B2BC(struct MainObj*);
void func_8004B514(struct MainObj*);
extern union AnimationStep* wall_crawler_animations[25];
static struct ShotObj expected_pool[32];
static u32 full(u32 row)
{
    struct MainObj obj, expected;
    struct MainObj* previous = SP_CUR_MAIN_OBJ;
    struct PlayerObj player;
    struct EngineObj engine;
    u32 i;
    (void)row;
    engine_obj.stage = 2;
    engine_obj.substage = 1;
    engine = engine_obj;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = 1;
    memcpy(expected_pool, shot_objects, sizeof(expected_pool));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 11;
    obj.state = 2;
    obj.unk5 = 5;
    obj.x_pos.i.hi = 2224;
    obj.y_pos.i.hi = 432;
    obj.animation_table = (const u8* const*)wall_crawler_animations;
    SP_CUR_MAIN_OBJ = &obj;
    g_Player.x_pos.val = obj.x_pos.val + 96 * 65536;
    g_Player.y_pos = obj.y_pos;
    player = g_Player;
    func_8004B2BC(&obj);
    func_8004B418(&obj);
    assert(obj.unk6 == 2 && obj.unk17 == 17 && obj.ext.main_11.angle == 0);
    for (i = 0; i < 6; i++)
        animate_object(ANIMATED_OBJECT(&obj));
    assert(obj.animation_step.packed == 0x24010201);
    expected = obj;
    cur_random = 0x1234;
    func_8004B514(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234 && SP_CUR_MAIN_OBJ == &obj);
    SP_CUR_MAIN_OBJ = previous;
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "corner_aim_angles", 0, 0, 32, test_corner_aim_angles },
    { "corner_resume_angles", 0, 0, 62, test_corner_resume_angles },
    { "wall_crawler_states", 0, 0, COUNT(wall_crawler_states_cases), test_wall_crawler_states },
    { "wall_crawler", wall_crawler_cases, wall_crawler_cases_expected, COUNT(wall_crawler_cases), 0 },
    { "wall_crawler_corner_animation", NULL, wall_crawler_corner_animation_cases_expected, COUNT(wall_crawler_corner_animation_cases_expected), wall_crawler_corner_animation_cases_row },
    { "wall_crawler_pursuit_context", wall_crawler_pursuit_context_cases, wall_crawler_pursuit_context_cases_expected, COUNT(wall_crawler_pursuit_context_cases), 0 },
    { "wall_crawler_turn_animation", NULL, wall_crawler_turn_animation_cases_expected, COUNT(wall_crawler_turn_animation_cases_expected), turn_case },
    { "func_8004B0A0", 0, 0, 3, test_func_8004B0A0 },
    { "aim_event_and_context_counter", NULL, NULL, 96, aim_animation },
    { "contact_death_radial_shots", NULL, NULL, 40, contact_death },
    { "own_corner_animation_event_two_full_32_shot_slots", NULL, NULL, 1, full },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 32 + 62 + COUNT(wall_crawler_states_cases) + COUNT(wall_crawler_cases) + COUNT(wall_crawler_corner_animation_cases_expected) + COUNT(wall_crawler_pursuit_context_cases) + COUNT(wall_crawler_turn_animation_cases_expected) + 3 + 96 + 40 + 1;
