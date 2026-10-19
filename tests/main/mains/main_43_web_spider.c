#include "test_runtime.h"
#include "main/mains/main_43_web_spider.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/visuals/visual_17_web_piece.h"
#include "main/object_motion.h"
void web_spider_fall(struct MainObj* arg0);
void web_spider_fall_slow(struct MainObj*);
void func_80065168(struct MainObj*, s16, s16);
void func_800643B0(struct MainObj*);
void web_spider_attack_web(struct MainObj*);
void web_spider_check_big_web(struct MainObj*);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 interpolate(u32 observation)
{
    struct MainObj obj, before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 43;
    obj.state = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    obj.unk7C = -1;
    obj.ext.main_43.move_direction = 0;
    before = obj;
    func_80065168(&obj, 10, 20);
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.ext.main_43.move_direction = obj.ext.main_43.move_direction;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    if (observation == 0)
        actual = obj.x_pos.val;
    else if (observation == 1)
        actual = obj.y_pos.val;
    else
        actual = (u8)obj.ext.main_43.move_direction;
    return actual;
}
static const u32 spider_interpolation_context_cases_expected[] = { 0xBE2468u, 0x8CACF0u, 0xDu };

static const s8 phases[] = { -1, 2, 3, 3, 3, 4 };
static u32 sweep_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct MiscObj pool_before[64];
    u16 arena_before, random_before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x27;
    }
    obj.active = 0x41;
    obj.id = 43;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = phases[mode];
    obj.unk7C = mode == 4 ? 7 : 6;
    obj.unk7E = mode == 2 ? 2 : 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    web_spider_arena_x = 0x400;
    cur_random = 0xACE1;
    before = obj;
    arena_before = web_spider_arena_x;
    random_before = cur_random;
    memcpy(pool_before, misc_objects, sizeof(pool_before));
    func_8006346C(&obj);
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.unk7C = obj.unk7C;
    before.unk7E = obj.unk7E;
    before.x_pos = obj.x_pos;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)pool_before)[i]);
    assert(web_spider_arena_x == arena_before && cur_random == random_before);
    if (observation == 0)
        actual = (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u16)obj.unk7E << 16);
    else if (observation == 1)
        actual = obj.x_pos.val;
    else
        actual = (u16)obj.unk7C;
    return actual;
}
static const u32 spider_sweep_context_cases_expected[] = { 0x1FF01u, 0x641234u, 0x6u, 0x140301u, 0x4F01234u, 0x7u, 0x10301u, 0x641234u, 0x6u, 0x201u, 0x641234u, 0x6u, 0x3u, 0x641234u, 0x0u, 0x10401u, 0x641234u, 0x6u };
static u32 spider_sweep_context_cases_row(u32 row)
{
    return sweep_case(row / 3, row % 3);
}

enum { SPIN,
    CENTER,
    CLIMB,
    RISE };
static u32 web_spider_big_web_steps_steps[2];
static u32* web_spider_big_web_steps_table[0x40];
static struct MainObj web_spider_big_web_steps_spider, web_spider_big_web_steps_expected;
static struct MainObj pool_before[0x30];

static void web_spider_big_web_steps_step(u32 index, s8 duration, s8 event, s8 relative)
{
    union AnimationStep value;
    value.fields.duration = duration;
    value.fields.event = event;
    value.fields.relative_step = relative;
    value.fields.frame_index = 6;
    web_spider_big_web_steps_steps[index] = value.packed;
}

static void enter(s8 sub_state, s8 event, s8 relative)
{
    u32 i;
    memcpy(pool_before, main_objects, sizeof(pool_before));
    g_Player.stun_timer = 1;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    D_8013E198[2] = -1;
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    for (i = 0; i < COUNT(web_spider_big_web_steps_table); i++)
        web_spider_big_web_steps_table[i] = &web_spider_big_web_steps_steps[1];
    web_spider_big_web_steps_step(0, 3, event, relative);
    web_spider_big_web_steps_step(1, 5, 0, 1);
    memset(&web_spider_big_web_steps_spider, 0, sizeof(web_spider_big_web_steps_spider));
    web_spider_big_web_steps_spider.active = 0x41;
    web_spider_big_web_steps_spider.id = 0x2B;
    web_spider_big_web_steps_spider.state = 1;
    web_spider_big_web_steps_spider.unk5 = 3;
    web_spider_big_web_steps_spider.unk6 = 1;
    web_spider_big_web_steps_spider.unk7 = sub_state;
    web_spider_big_web_steps_spider.hp = 0x20;
    web_spider_big_web_steps_spider.x_pos.val = 0x00A01234;
    web_spider_big_web_steps_spider.y_pos.val = 0x00400000;
    web_spider_big_web_steps_spider.animation_table = web_spider_big_web_steps_table;
    web_spider_big_web_steps_spider.animation_cursor = &web_spider_big_web_steps_steps[0];
    web_spider_big_web_steps_spider.animation_step.packed = web_spider_big_web_steps_steps[0];
    web_spider_big_web_steps_spider.ext.main_43.attack_cooldown = 5;
    web_spider_big_web_steps_spider.ext.main_43.animation_id = 3;
}

static void leave(void)
{
    u32 i, j;
    for (i = 0; i < sizeof(web_spider_big_web_steps_spider) / 4; i++)
        assert(((u32*)&web_spider_big_web_steps_spider)[i] == ((u32*)&web_spider_big_web_steps_expected)[i]);
    for (i = 0; i < COUNT(main_objects); i++) {
        struct MainObj want = pool_before[i];
        want.active = 1;
        for (j = 0; j < sizeof(want) / 4; j++)
            assert(((u32*)&main_objects[i])[j] == ((u32*)&want)[j]);
    }
    assert(g_Player.stun_timer == 1 && D_8013E198[2] == -1);
    assert(background_objects[0].x_pos.val == 0 && background_objects[0].y_pos.val == 0);
}

static void call(u32 which)
{
    web_spider_big_web_steps_expected = web_spider_big_web_steps_spider;
    if (which == SPIN)
        web_spider_big_web_spin(&web_spider_big_web_steps_spider);
    if (which == CENTER)
        web_spider_big_web_center(&web_spider_big_web_steps_spider);
    if (which == CLIMB)
        func_80063B20(&web_spider_big_web_steps_spider);
    if (which == RISE)
        func_800646EC(&web_spider_big_web_steps_spider);
}

static u32 summary(void)
{
    return (u8)web_spider_big_web_steps_spider.unk7 | ((u32)(u16)web_spider_big_web_steps_spider.unk7C << 8) | ((u32)(u8)web_spider_big_web_steps_spider.y_pos.i.hi << 24);
}

static u32 invalid_state(u32 which, s8 sub_state)
{
    u32 actual;
    enter(sub_state, 0, 1);
    call(which);
    actual = summary();
    leave();
    return actual;
}

static u32 rise_clamp(u32 which)
{
    u32 actual;
    enter(1, 0, 1);
    web_spider_big_web_steps_spider.y_speed = -0x90000;
    web_spider_big_web_steps_spider.gravity = 0x4000;
    call(which);
    web_spider_big_web_steps_expected.y_pos.val += 0x80000;
    web_spider_big_web_steps_expected.y_speed = FIXED(-6.5);
    web_spider_big_web_steps_expected.gravity = 0;
    actual = summary() ^ (u32)web_spider_big_web_steps_spider.y_speed;
    leave();
    return actual;
}

static u32 timer_nudge(u32 which)
{
    u32 actual;
    enter(2, 0, 1);
    web_spider_big_web_steps_spider.unk7C = 0x10;
    web_spider_big_web_steps_spider.y_speed = 0x10000;
    call(which);
    web_spider_big_web_steps_expected.y_pos.val -= 0x10000;
    web_spider_big_web_steps_expected.unk7C = 0xF;
    web_spider_big_web_steps_expected.y_speed = -0x10000;
    web_spider_big_web_steps_expected.animation_step.fields.duration = 2;
    actual = summary() ^ (u32)web_spider_big_web_steps_spider.y_speed;
    leave();
    return actual;
}

static u32 spawn_pool_full(void)
{
    u32 actual;
    enter(0, 1, 1);
    web_spider_big_web_steps_expected = web_spider_big_web_steps_spider;
    func_800643B0(&web_spider_big_web_steps_spider);
    web_spider_big_web_steps_expected.animation_step.fields.event = 0;
    web_spider_big_web_steps_expected.animation_step.fields.duration = 2;
    actual = (u8)web_spider_big_web_steps_spider.unk6 | ((u32)(u8)web_spider_big_web_steps_spider.animation_step.fields.event << 8);
    leave();
    return actual;
}

static u32 spawn_invalid(s8 sub_state)
{
    u32 actual;
    enter(0, 1, 1);
    web_spider_big_web_steps_spider.unk6 = sub_state;
    web_spider_big_web_steps_expected = web_spider_big_web_steps_spider;
    func_800643B0(&web_spider_big_web_steps_spider);
    web_spider_big_web_steps_expected.animation_step.fields.duration = 2;
    actual = (u8)web_spider_big_web_steps_spider.unk6 | ((u32)(u8)web_spider_big_web_steps_spider.animation_step.fields.event << 8);
    leave();
    return actual;
}

static u32 attack_wrap(void)
{
    u32 actual;
    enter(0, 0, 0);
    web_spider_big_web_steps_spider.unk6 = 2;
    web_spider_big_web_steps_spider.ext.main_43.attack_count = 2;
    web_spider_big_web_steps_expected = web_spider_big_web_steps_spider;
    func_800643B0(&web_spider_big_web_steps_spider);
    web_spider_big_web_steps_expected.unk5 = 4;
    web_spider_big_web_steps_expected.unk6 = 1;
    web_spider_big_web_steps_expected.unk7 = 0;
    web_spider_big_web_steps_expected.unk17 = 3;
    web_spider_big_web_steps_expected.previous_animation_index = 0xFF;
    web_spider_big_web_steps_expected.animation_cursor = &web_spider_big_web_steps_steps[1];
    web_spider_big_web_steps_expected.animation_step.packed = web_spider_big_web_steps_steps[1];
    web_spider_big_web_steps_expected.animation_step.fields.duration = 4;
    web_spider_big_web_steps_expected.ext.main_43.attack_count = 0;
    actual = (u8)web_spider_big_web_steps_spider.unk5 | ((u32)(u8)web_spider_big_web_steps_spider.unk6 << 8) | ((u32)web_spider_big_web_steps_spider.ext.main_43.attack_count << 16)
        | ((u32)web_spider_big_web_steps_spider.ext.main_43.attack_cooldown << 24);
    leave();
    return actual;
}

#define CASE(name, call)  \
    static u32 name(void) \
    {                     \
        return call;      \
    }
CASE(SPIN_NEGATIVE, invalid_state(SPIN, -1))
CASE(SPIN_HIGH, invalid_state(SPIN, 3))
CASE(CENTER_NEGATIVE, invalid_state(CENTER, -1))
CASE(CENTER_HIGH, invalid_state(CENTER, 3))
CASE(CLIMB_NEGATIVE, invalid_state(CLIMB, -1))
CASE(CLIMB_HIGH, invalid_state(CLIMB, 3))
CASE(CLIMB_CLAMP, rise_clamp(CLIMB))
CASE(CLIMB_TIMER, timer_nudge(CLIMB))
CASE(RISE_NEGATIVE, invalid_state(RISE, -1))
CASE(RISE_HIGH, invalid_state(RISE, 3))
CASE(RISE_CLAMP, rise_clamp(RISE))
CASE(RISE_TIMER, timer_nudge(RISE))
CASE(SPAWN_POOL_FULL, spawn_pool_full())
CASE(SPAWN_NEGATIVE, spawn_invalid(-1))
CASE(SPAWN_HIGH, spawn_invalid(3))
CASE(ATTACK_WRAP, attack_wrap())
#define ENTRY(name) name,
static const CTestCase web_spider_big_web_steps_cases[] = {
    ENTRY(SPIN_NEGATIVE) ENTRY(SPIN_HIGH) ENTRY(CENTER_NEGATIVE) ENTRY(CENTER_HIGH)
        ENTRY(CLIMB_NEGATIVE) ENTRY(CLIMB_HIGH) ENTRY(CLIMB_CLAMP) ENTRY(CLIMB_TIMER)
            ENTRY(RISE_NEGATIVE) ENTRY(RISE_HIGH) ENTRY(RISE_CLAMP) ENTRY(RISE_TIMER)
                ENTRY(SPAWN_POOL_FULL) ENTRY(SPAWN_NEGATIVE) ENTRY(SPAWN_HIGH) ENTRY(ATTACK_WRAP)
};
static const u32 web_spider_big_web_steps_cases_expected[] = { 0x400000FFu, 0x40000003u, 0x400000FFu, 0x40000003u, 0x400000FFu, 0x40000003u, 0xB7F98001u, 0xC0FF0F02u, 0x400000FFu, 0x40000003u, 0xB7F98001u, 0xC0FF0F02u, 0x1u, 0x1FFu, 0x103u, 0x5000104u };
#undef CASE
#undef ENTRY

static u32 climb_case(u32 raw_default)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 43;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 2;
    obj.unk7 = raw_default ? 3 : 0;
    obj.unk7C = 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = -32768;
    obj.gravity = 0x1000;
    obj.animation_table = (const u8* const*)web_spider_animations;
    set_animation(&obj, 0);
    g_Player.stun_timer = 1;
    g_Player.x_pos.i.hi = 50;
    g_Player.hp = 0x27;
    cur_random = 0x1234;
    D_8013E198[2] = -1;
    before = obj;
    player_before = g_Player;
    web_spider_drop_climb(&obj);
    if (!raw_default) {
        before.unk7 = 1;
        before.y_speed = 0x38000;
        before.gravity = 0;
        before.unk17 = 31;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)web_spider_animations[31];
        before.animation_step = *web_spider_animations[31];
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(cur_random == (raw_default ? 0x1234 : 0x366A));
    assert(D_8013E198[2] == -1);
    return (u8)obj.unk7 | ((u32)obj.unk17 << 8) | ((u32)(u8)g_Player.stun_timer << 16);
}
static const u32 web_spider_climb_stun_default_cases_expected[] = { 0x11F01u, 0x10003u };

enum { DEFEATED,
    FLASHING,
    FLASH_ENDS };
static u32 web_spider_defeat_check_steps[1];
static u32* web_spider_defeat_check_table[8];
static struct MainObj web_spider_defeat_check_spider, web_spider_defeat_check_expected;

static u32 web_spider_defeat_check_run(u32 mode)
{
    union AnimationStep value;
    u32 i, actual;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    memset(&g_Player, 0, sizeof(g_Player));
    value.fields.duration = 3;
    value.fields.event = 0;
    value.fields.relative_step = 1;
    value.fields.frame_index = 6;
    web_spider_defeat_check_steps[0] = value.packed;
    for (i = 0; i < COUNT(web_spider_defeat_check_table); i++)
        web_spider_defeat_check_table[i] = &web_spider_defeat_check_steps[0];
    memset(&web_spider_defeat_check_spider, 0, sizeof(web_spider_defeat_check_spider));
    web_spider_defeat_check_spider.active = 0x41;
    web_spider_defeat_check_spider.id = 0x2B;
    web_spider_defeat_check_spider.state = 1;
    web_spider_defeat_check_spider.unk5 = 6;
    web_spider_defeat_check_spider.unk6 = 1;
    web_spider_defeat_check_spider.unk7 = 3;
    web_spider_defeat_check_spider.hp = 0;
    web_spider_defeat_check_spider.unk42 = 0x8123;
    web_spider_defeat_check_spider.x_pos.val = 0x00A01234;
    web_spider_defeat_check_spider.y_pos.val = 0x00405678;
    web_spider_defeat_check_spider.animation_table = web_spider_defeat_check_table;
    web_spider_defeat_check_spider.animation_cursor = &web_spider_defeat_check_steps[0];
    web_spider_defeat_check_spider.animation_step.packed = web_spider_defeat_check_steps[0];
    web_spider_defeat_check_spider.ext.main_43.flash_timer = mode == FLASHING ? 3 : mode == FLASH_ENDS ? 1
                                                                                                       : 0;
    web_spider_defeat_check_spider.ext.main_43.hurt_collision = mode != DEFEATED;
    web_spider_defeat_check_expected = web_spider_defeat_check_spider;
    func_8006398C(&web_spider_defeat_check_spider);

    web_spider_defeat_check_expected.unk18.val = web_spider_defeat_check_expected.x_pos.val;
    web_spider_defeat_check_expected.unk1C.val = web_spider_defeat_check_expected.y_pos.val;
    web_spider_defeat_check_expected.on_screen = 1;
    if (mode == DEFEATED) {
        web_spider_defeat_check_expected.state = 2;
        web_spider_defeat_check_expected.unk5 = 0;
        web_spider_defeat_check_expected.unk6 = 0;
        web_spider_defeat_check_expected.unk42 = 0x0123;
        assert(g_Player.spike_immune == 1);
        g_Player.spike_immune = 0;
    } else {
        web_spider_defeat_check_expected.unk42 = 0x0123;
        web_spider_defeat_check_expected.ext.main_43.flash_timer--;
        if (mode == FLASH_ENDS) {
            web_spider_defeat_check_expected.collision_data = D_801075F4;
            web_spider_defeat_check_expected.ext.main_43.hurt_collision = 0;
        }
    }
    for (i = 0; i < sizeof(web_spider_defeat_check_spider) / 4; i++)
        assert(((u32*)&web_spider_defeat_check_spider)[i] == ((u32*)&web_spider_defeat_check_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == 0);
    assert(background_objects[0].x_pos.val == 0 && background_objects[0].y_pos.val == 0);
    actual = (u8)web_spider_defeat_check_spider.state | ((u32)(u8)web_spider_defeat_check_spider.unk5 << 8) | ((u32)web_spider_defeat_check_spider.unk42 << 16);
    return actual;
}

static const u32 web_spider_defeat_check_cases_expected[] = { 0x1230002u, 0x1230601u, 0x1230601u };

enum { EXPLODE_WAIT,
    EXPLODE_FULL,
    EXPLODE_SPAWN,
    FINISH_BLINK,
    FINISH_PHASE,
    FINISH_STAGE1,
    FINISH_OTHER,
    SWING_STUNNED,
    SWING_FAR,
    CRAWL_WALL_LEFT,
    CRAWL_WALL_RIGHT,
    CRAWL_START,
    WEB_START_LEFT,
    WEB_START_RIGHT,
    WEB_SHOT,
    WEB_FLASH,
    WEB_END };
#define FREE_SLOT 6
static u32 web_spider_late_steps_steps[2];
static u32* web_spider_late_steps_table[0x20];
static struct MainObj web_spider_late_steps_spider, web_spider_late_steps_expected;
static struct EffectObj effect;
static struct ShotObj web_spider_late_steps_want_shots[0x20];
static struct VisualObj web_spider_late_steps_want_visuals[0x20];
static struct EffectObj web_spider_late_steps_want_effects[0x20];
static struct EngineObj web_spider_late_steps_want_engine;

static void web_spider_late_steps_same(const void* a, const void* b, u32 size)
{
    u32 i, difference = 0;
    for (i = 0; i < size / 4; i++)
        difference |= ((const u32*)a)[i] ^ ((const u32*)b)[i];
    for (i = size & ~3u; i < size; i++)
        difference |= ((const u8*)a)[i] ^ ((const u8*)b)[i];
    assert(difference == 0);
}

static void web_spider_late_steps_step(u32 index, s8 duration, s8 event, s8 relative)
{
    union AnimationStep value;
    value.fields.duration = duration;
    value.fields.event = event;
    value.fields.relative_step = relative;
    value.fields.frame_index = 4;
    web_spider_late_steps_steps[index] = value.packed;
}

static void animated(void)
{
    web_spider_late_steps_expected.animation_step.fields.duration--;
}

static u32 web_spider_late_steps_run(u32 mode)
{
    u32 i, result;
    D_8013E198[2] = -1;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    for (i = 0; i < 0x20; i++) {
        shot_objects[i].active = 1;
        visual_objects[i].active = 1;
        effect_objects[i].active = mode != EXPLODE_SPAWN || i != FREE_SLOT;
    }
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.i.hi = mode == SWING_FAR || mode == WEB_START_LEFT ? 0x20 : 0x100;
    g_Player.y_pos.i.hi = mode == SWING_FAR ? 0x10 : 0x60;
    g_Player.stun_timer = mode == SWING_STUNNED;
    engine_obj.stage = mode == FINISH_STAGE1 ? 1 : 3;
    engine_obj.checkpoint = 2;
    engine_obj.unkF = 0;
    engine_obj.character_state.bytes[8] = 0;
    for (i = 0; i < COUNT(web_spider_late_steps_table); i++)
        web_spider_late_steps_table[i] = &web_spider_late_steps_steps[1];
    web_spider_late_steps_step(0, 3, mode == WEB_SHOT ? 1 : mode == WEB_FLASH ? 2
                                                                              : 0,
        mode == CRAWL_START || mode == WEB_END ? 0 : 1);
    web_spider_late_steps_step(1, 6, 0, 1);
    memset(&effect, 0, sizeof(effect));
    effect.active = mode == FINISH_BLINK || mode == FINISH_PHASE;
    effect.unk7 = mode == FINISH_PHASE;
    memset(&web_spider_late_steps_spider, 0, sizeof(web_spider_late_steps_spider));
    web_spider_late_steps_spider.active = 0x41;
    web_spider_late_steps_spider.id = 0x2B;
    web_spider_late_steps_spider.state = 1;
    web_spider_late_steps_spider.unk5 = 3;
    web_spider_late_steps_spider.unk6 = mode == CRAWL_START || mode == WEB_START_LEFT || mode == WEB_START_RIGHT ? 0 : mode == WEB_END ? 2
                                                                                                                                       : 1;
    web_spider_late_steps_spider.unk7 = 1;
    web_spider_late_steps_spider.unk15 = 0x40;
    web_spider_late_steps_spider.x_pos.val = (mode == WEB_START_RIGHT || mode == CRAWL_START ? 0x00800000 : 0x00A00000) | 0x1234;
    web_spider_late_steps_spider.y_pos.val = 0x00B00000;
    web_spider_late_steps_spider.x_speed = 0x2000;
    web_spider_late_steps_spider.unk42 = 0x0321;
    web_spider_late_steps_spider.unk7C = mode == EXPLODE_WAIT ? 3 : 1;
    web_spider_late_steps_spider.unk7E = mode == EXPLODE_WAIT ? 4 : 0;
    web_spider_late_steps_spider.collision_flags = mode == CRAWL_WALL_LEFT ? 2 : mode == CRAWL_WALL_RIGHT ? 1
                                                                                                          : 0;
    web_spider_late_steps_spider.animation_table = web_spider_late_steps_table;
    web_spider_late_steps_spider.animation_cursor = &web_spider_late_steps_steps[0];
    web_spider_late_steps_spider.animation_step.packed = web_spider_late_steps_steps[0];
    web_spider_late_steps_spider.ext.main_43.effect = &effect;
    web_spider_late_steps_spider.ext.main_43.flash_timer = mode == EXPLODE_FULL ? 20 : 3;
    web_spider_late_steps_spider.ext.main_43.attack_cooldown = mode == SWING_STUNNED || mode == SWING_FAR ? 0 : 5;
    web_spider_late_steps_spider.ext.main_43.attack_count = 2;
    web_spider_late_steps_spider.ext.main_43.animation_id = 3;
    memcpy(web_spider_late_steps_want_shots, shot_objects, sizeof(web_spider_late_steps_want_shots));
    memcpy(web_spider_late_steps_want_visuals, visual_objects, sizeof(web_spider_late_steps_want_visuals));
    memcpy(web_spider_late_steps_want_effects, effect_objects, sizeof(web_spider_late_steps_want_effects));
    web_spider_late_steps_want_engine = engine_obj;
    web_spider_late_steps_expected = web_spider_late_steps_spider;

    if (mode <= EXPLODE_SPAWN) {
        web_spider_death_explode(&web_spider_late_steps_spider);
        web_spider_late_steps_expected.on_screen = 1;
        web_spider_late_steps_expected.unk7C--;
        if (mode == EXPLODE_WAIT) {
            web_spider_late_steps_expected.unk7E = 3;
        } else {
            web_spider_late_steps_expected.unk5 = 2;
            web_spider_late_steps_expected.unk42 ^= 0x8000;
            web_spider_late_steps_expected.ext.main_43.flash_timer = mode == EXPLODE_FULL ? 15 : 0;
            web_spider_late_steps_expected.unk7E = mode == EXPLODE_FULL ? 15 : 5;
            if (mode == EXPLODE_SPAWN) {
                web_spider_late_steps_want_effects[FREE_SLOT].active = 1;
                web_spider_late_steps_want_effects[FREE_SLOT].id = 0x1A;
                web_spider_late_steps_want_effects[FREE_SLOT].x_pos.u.hi = web_spider_late_steps_spider.x_pos.u.hi;
                web_spider_late_steps_want_effects[FREE_SLOT].y_pos.u.hi = web_spider_late_steps_spider.y_pos.u.hi;
                web_spider_late_steps_expected.ext.main_43.effect = &effect_objects[FREE_SLOT];
            }
        }
    } else if (mode <= FINISH_OTHER) {
        web_spider_death_finish(&web_spider_late_steps_spider);
        if (mode == FINISH_BLINK) {
            web_spider_late_steps_expected.unk7E = 5;
            web_spider_late_steps_expected.unk42 ^= 0x8000;
            web_spider_late_steps_expected.on_screen = 1;
        } else if (mode != FINISH_PHASE) {
            memset(&web_spider_late_steps_expected, 0, 8);
            if (mode == FINISH_STAGE1) {
                web_spider_late_steps_want_engine.unkF = 0x10;
            } else {
                web_spider_late_steps_want_engine.unkF = -0x80;
                web_spider_late_steps_want_engine.character_state.bytes[8] = 1;
                web_spider_late_steps_want_engine.checkpoint = 11;
            }
        }
    } else if (mode <= SWING_FAR) {
        func_80064154(&web_spider_late_steps_spider);
        web_spider_late_steps_expected.unk5 = 5;
        web_spider_late_steps_expected.unk6 = 0;
        web_spider_late_steps_expected.unk7 = 0;
        web_spider_late_steps_expected.ext.main_43.unk94 = mode == SWING_STUNNED;
    } else if (mode <= CRAWL_START) {
        spiderling_crawl(&web_spider_late_steps_spider);
        if (mode == CRAWL_START) {
            web_spider_late_steps_expected.x_speed = FIXED(1.5);
            web_spider_late_steps_expected.unk15 = 0x40;
            web_spider_late_steps_expected.unk6 = 1;
            web_spider_late_steps_expected.unk17 = 0x1D;
            web_spider_late_steps_expected.previous_animation_index = 0xFF;
            web_spider_late_steps_expected.animation_cursor = &web_spider_late_steps_steps[1];
            web_spider_late_steps_expected.animation_step.packed = web_spider_late_steps_steps[1];
            animated();
        } else {
            web_spider_late_steps_expected.unk5 = 4;
            web_spider_late_steps_expected.unk6 = 0;
            web_spider_late_steps_expected.unk7 = 0;
            web_spider_late_steps_expected.x_speed = 0;
            web_spider_late_steps_expected.unk15 = mode == CRAWL_WALL_RIGHT ? 0x40 : 0;
        }
    } else {
        web_spider_attack_web(&web_spider_late_steps_spider);
        if (mode == WEB_START_LEFT || mode == WEB_START_RIGHT) {
            web_spider_late_steps_expected.unk6 = 1;
            web_spider_late_steps_expected.unk17 = 0xA;
            web_spider_late_steps_expected.previous_animation_index = 0xFF;
            web_spider_late_steps_expected.animation_cursor = &web_spider_late_steps_steps[1];
            web_spider_late_steps_expected.animation_step.packed = web_spider_late_steps_steps[1];
            web_spider_late_steps_expected.unk15 = mode == WEB_START_RIGHT ? 0x40 : 0;
        } else if (mode == WEB_END) {
            web_spider_late_steps_expected.unk5 = 4;
            web_spider_late_steps_expected.unk6 = 1;
            web_spider_late_steps_expected.unk7 = 0;
            web_spider_late_steps_expected.unk17 = 3;
            web_spider_late_steps_expected.previous_animation_index = 0xFF;
            web_spider_late_steps_expected.animation_cursor = &web_spider_late_steps_steps[1];
            web_spider_late_steps_expected.animation_step.packed = web_spider_late_steps_steps[1];
            web_spider_late_steps_expected.ext.main_43.attack_count = 0;
            animated();
        } else {
            web_spider_late_steps_expected.animation_step.fields.event = 0;
            animated();
        }
    }
    web_spider_late_steps_same(&web_spider_late_steps_spider, &web_spider_late_steps_expected, sizeof(web_spider_late_steps_spider));
    web_spider_late_steps_same(shot_objects, web_spider_late_steps_want_shots, sizeof(web_spider_late_steps_want_shots));
    web_spider_late_steps_same(visual_objects, web_spider_late_steps_want_visuals, sizeof(web_spider_late_steps_want_visuals));
    web_spider_late_steps_same(effect_objects, web_spider_late_steps_want_effects, sizeof(web_spider_late_steps_want_effects));
    web_spider_late_steps_same(&engine_obj, &web_spider_late_steps_want_engine, sizeof(web_spider_late_steps_want_engine));
    assert(D_8013E198[2] == -1 && background_objects[0].x_pos.val == 0 && background_objects[0].y_pos.val == 0);
    result = (u8)web_spider_late_steps_spider.unk5 | ((u32)(u8)web_spider_late_steps_spider.unk6 << 8) | ((u32)web_spider_late_steps_spider.unk42 << 16);
    result ^= (u32)(u8)web_spider_late_steps_spider.unk7E << 4 ^ (u32)(u8)engine_obj.unkF << 12 ^ (u32)(u8)web_spider_late_steps_spider.unk15 << 20;
    return result;
}

static const u32 web_spider_late_steps_cases_expected[] = { 0x7210133u, 0x872101F2u, 0x87210152u, 0x87210153u, 0x7210103u, 0x7200000u, 0x7290000u, 0x7210005u, 0x7210005u, 0x3210004u, 0x7210004u, 0x7210103u, 0x3210103u, 0x7210103u, 0x7210103u, 0x7210103u, 0x7210104u };

enum { THREAD_EXISTS,
    THREAD_FULL,
    THREAD_SPAWN,
    PIECE_FULL,
    PIECE_SPAWN,
    FLASH_FULL,
    FLASH_SPAWN,
    SHOT_FULL,
    SHOT_LEFT,
    SHOT_RIGHT,
    WARNING_CAPSULE,
    WARNING_FULL,
    WARNING_SPAWN };
#define FREE_SLOT_B 5
static u32 table_storage[2];
static u32* web_spider_spawns_table[4];
static struct MainObj web_spider_spawns_spider, web_spider_spawns_expected;
static struct ShotObj web_spider_spawns_want_shots[0x20];
static struct VisualObj web_spider_spawns_want_visuals[0x20];
static struct EffectObj web_spider_spawns_want_effects[0x20];
static struct PlayerObj want_player;
static struct EngineObj web_spider_spawns_want_engine;

static void web_spider_spawns_same(const void* a, const void* b, u32 size)
{
    u32 i, difference = 0;
    for (i = 0; i < size / 4; i++)
        difference |= ((const u32*)a)[i] ^ ((const u32*)b)[i];
    for (i = size & ~3u; i < size; i++)
        difference |= ((const u8*)a)[i] ^ ((const u8*)b)[i];
    assert(difference == 0);
}

static u32 web_spider_spawns_run(u32 mode)
{
    u32 i, slot = 0xFF, result = 0;
    u32 full = mode == THREAD_FULL || mode == PIECE_FULL || mode == FLASH_FULL || mode == SHOT_FULL || mode == WARNING_FULL;
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    for (i = 0; i < 0x20; i++) {
        shot_objects[i].active = full || i != FREE_SLOT_B;
        visual_objects[i].active = full || i != FREE_SLOT_B;
        effect_objects[i].active = full || i != FREE_SLOT_B;
    }
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.capsule_state = mode == WARNING_CAPSULE ? 2 : 0;
    engine_obj.gameplay_locked = 0;
    background_objects[0].unk26 = 0x0340;
    background_objects[0].unk2A = 0x0120;
    web_spider_spawns_table[0] = &table_storage[0];
    memset(&web_spider_spawns_spider, 0, sizeof(web_spider_spawns_spider));
    web_spider_spawns_spider.active = 0x41;
    web_spider_spawns_spider.id = 0x2B;
    web_spider_spawns_spider.unk5 = 3;
    web_spider_spawns_spider.unk6 = 2;
    web_spider_spawns_spider.unk7 = 1;
    web_spider_spawns_spider.unk15 = mode == SHOT_RIGHT ? 0x40 : 0;
    web_spider_spawns_spider.unk16 = 0x12;
    web_spider_spawns_spider.unk40 = 0x0456;
    web_spider_spawns_spider.unk42 = 0x8789;
    web_spider_spawns_spider.x_pos.val = 0x01802345;
    web_spider_spawns_spider.y_pos.val = 0x00903456;
    web_spider_spawns_spider.animation_table = web_spider_spawns_table;
    ANIMATED_OBJECT(&web_spider_spawns_spider)->unk3C = (void*)&table_storage[1];
    if (mode == THREAD_EXISTS)
        web_spider_spawns_spider.ext.main_43.shot = &shot_objects[3];
    memcpy(web_spider_spawns_want_shots, shot_objects, sizeof(web_spider_spawns_want_shots));
    memcpy(web_spider_spawns_want_visuals, visual_objects, sizeof(web_spider_spawns_want_visuals));
    memcpy(web_spider_spawns_want_effects, effect_objects, sizeof(web_spider_spawns_want_effects));
    want_player = g_Player;
    web_spider_spawns_want_engine = engine_obj;
    web_spider_spawns_expected = web_spider_spawns_spider;

    if (mode <= THREAD_SPAWN) {
        struct ShotObj* shot = web_spider_spawn_thread(&web_spider_spawns_spider, 7);
        if (mode == THREAD_EXISTS)
            assert(shot == &shot_objects[3]);
        if (mode == THREAD_FULL)
            assert(shot == NULL);
        if (mode == THREAD_SPAWN) {
            struct ShotObj* s = &web_spider_spawns_want_shots[FREE_SLOT_B];
            assert(shot == &shot_objects[FREE_SLOT_B]);
            s->active = 0x41;
            s->id = 0x17;
            s->unk2 = 7;
            s->x_pos.val = web_spider_spawns_spider.x_pos.val;
            s->y_pos.val = web_spider_spawns_spider.y_pos.val;
            s->animation_table = web_spider_spawns_spider.animation_table;
            s->unk40 = web_spider_spawns_spider.unk40;
            s->unk3C = ANIMATED_OBJECT(&web_spider_spawns_spider)->unk3C;
            s->unk42 = web_spider_spawns_spider.unk42 & 0x7FFF;
            s->unk16 = web_spider_spawns_spider.unk16;
            s->unk7C = WEAPON_OBJECT(&web_spider_spawns_spider);
            s->unk15 = web_spider_spawns_spider.unk15;
            web_spider_spawns_expected.ext.main_43.shot = shot;
            slot = FREE_SLOT_B;
        }
    } else if (mode <= PIECE_SPAWN) {
        web_spider_spawn_web_piece(VISUAL_OBJECT(&web_spider_spawns_spider), 3);
        if (mode == PIECE_SPAWN) {
            struct VisualObj* v = &web_spider_spawns_want_visuals[FREE_SLOT_B];
            v->active = 0x41;
            v->id = 0x11;
            v->unk2 = 3;
            v->x_pos.val = web_spider_spawns_spider.x_pos.val;
            v->y_pos.val = web_spider_spawns_spider.y_pos.val;
            v->animation_table = web_spider_spawns_spider.animation_table;
            v->unk40 = web_spider_spawns_spider.unk40;
            v->unk3C = ANIMATED_OBJECT(&web_spider_spawns_spider)->unk3C;
            v->unk42 = web_spider_spawns_spider.unk42 & 0x7FFF;
            v->unk16 = web_spider_spawns_spider.unk16;
            v->unk50 = (struct PlayerObj*)&web_spider_spawns_spider;
            v->unk15 = web_spider_spawns_spider.unk15;
            slot = FREE_SLOT_B;
        }
    } else if (mode <= FLASH_SPAWN) {
        web_spider_spawn_web_flash(ANIMATED_OBJECT(&web_spider_spawns_spider));
        if (mode == FLASH_SPAWN) {
            struct VisualObj* v = &web_spider_spawns_want_visuals[FREE_SLOT_B];
            v->active = 0x41;
            v->id = 0x14;
            v->unk2 = 1;
            v->x_pos.val = web_spider_spawns_spider.x_pos.val;
            v->y_pos.val = web_spider_spawns_spider.y_pos.val + FIXED(28);
            v->animation_table = web_spider_spawns_spider.animation_table;
            v->unk40 = web_spider_spawns_spider.unk40;
            v->unk3C = ANIMATED_OBJECT(&web_spider_spawns_spider)->unk3C;
            v->unk42 = web_spider_spawns_spider.unk42 & 0x7FFF;
            v->unk16 = web_spider_spawns_spider.unk16;
            v->unk50 = (struct PlayerObj*)&web_spider_spawns_spider;
            v->unk15 = web_spider_spawns_spider.unk15;
            slot = FREE_SLOT_B;
        }
    } else if (mode <= SHOT_RIGHT) {
        web_spider_spawn_web_shot(ANIMATED_OBJECT(&web_spider_spawns_spider), 2);
        if (mode != SHOT_FULL) {
            struct ShotObj* s = &web_spider_spawns_want_shots[FREE_SLOT_B];
            s->active = 0x41;
            s->id = 0x16;
            s->unk2 = 2;
            s->x_pos.val = web_spider_spawns_spider.x_pos.val;
            s->y_pos.val = web_spider_spawns_spider.y_pos.val;
            s->x_pos.i.hi += mode == SHOT_RIGHT ? 0x12 : -0x12;
            s->y_pos.i.hi += 0x26;
            s->animation_table = web_spider_spawns_spider.animation_table;
            s->unk40 = web_spider_spawns_spider.unk40;
            s->unk3C = ANIMATED_OBJECT(&web_spider_spawns_spider)->unk3C;
            s->unk42 = web_spider_spawns_spider.unk42 & 0x7FFF;
            s->unk16 = web_spider_spawns_spider.unk16;
            s->unk7C = WEAPON_OBJECT(&web_spider_spawns_spider);
            s->unk15 = web_spider_spawns_spider.unk15;
            slot = FREE_SLOT_B;
        }
    } else {
        web_spider_intro_warning(&web_spider_spawns_spider);
        if (mode != WARNING_CAPSULE) {
            if (mode == WARNING_SPAWN) {
                web_spider_spawns_want_effects[FREE_SLOT_B].active = 1;
                web_spider_spawns_want_effects[FREE_SLOT_B].id = 0x18;
                web_spider_spawns_expected.ext.main_43.effect = &effect_objects[FREE_SLOT_B];
                slot = FREE_SLOT_B;
            }
            want_player.script_state = 1;
            want_player.script_action = 0x14;
            want_player.script_facing = 0x40;
            want_player.spike_immune = 1;
            web_spider_spawns_want_engine.gameplay_locked = 1;
            web_spider_spawns_expected.unk5 = 1;
            web_spider_spawns_expected.unk6 = 0;
            web_spider_spawns_expected.unk7 = 0;
            assert(web_spider_arena_x == 0x0340 && web_spider_arena_y == 0x0120);
        }
        result = (u8)g_Player.script_state | ((u32)(u8)g_Player.script_action << 8) | ((u32)(u8)web_spider_spawns_spider.unk5 << 16);
    }
    web_spider_spawns_same(&web_spider_spawns_spider, &web_spider_spawns_expected, sizeof(web_spider_spawns_spider));
    web_spider_spawns_same(shot_objects, web_spider_spawns_want_shots, sizeof(web_spider_spawns_want_shots));
    web_spider_spawns_same(visual_objects, web_spider_spawns_want_visuals, sizeof(web_spider_spawns_want_visuals));
    web_spider_spawns_same(effect_objects, web_spider_spawns_want_effects, sizeof(web_spider_spawns_want_effects));
    web_spider_spawns_same(&g_Player, &want_player, sizeof(want_player));
    web_spider_spawns_same(&engine_obj, &web_spider_spawns_want_engine, sizeof(web_spider_spawns_want_engine));
    result ^= slot << 24;
    if (slot != 0xFF && mode <= SHOT_RIGHT)
        result ^= (u8)(mode <= THREAD_SPAWN || mode >= SHOT_FULL ? shot_objects[slot].id : visual_objects[slot].id)
            | ((u32)(u16)(mode <= THREAD_SPAWN || mode >= SHOT_FULL ? shot_objects[slot].x_pos.i.hi : visual_objects[slot].y_pos.i.hi) << 8);
    return result;
}

static const u32 web_spider_spawns_cases_expected[] = { 0xFF000000u, 0xFF000000u, 0x5018017u, 0xFF000000u, 0x5009011u, 0xFF000000u, 0x500AC14u, 0xFF000000u, 0x5016E16u, 0x5019216u, 0xFF030000u, 0xFF011401u, 0x5011401u };

static const u32 web_spider_check_big_web_expected[] = { 0u, 0u, 0u, 0u, 0u };
static u32 test_web_spider_check_big_web(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.state = 64;
    web_spider_check_big_web(&obj);
    observed_values[0] = (u32)obj.ext.main_43.big_web_done;
    observed_values[1] = (u32)obj.ext.main_43.hurt_collision;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7;
    return c_test_observe(0, row, observed_values, web_spider_check_big_web_expected, 5);
}

#include "support/state_cases.h"

static struct ShotObj spider_thread;
#define SPIDER(phase) (state_reset(1, phase, 0), memset(&spider_thread, 0, sizeof(spider_thread)), so.ext.main_43.shot = &spider_thread, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60)
#define THREAD() (state_extra = spider_thread.unk84.value ^ (u32)so.ext.main_43.hurt_collision << 24)
static void ws_fall_start(void)
{
    SPIDER(0);
    web_spider_fall(&so);
    THREAD();
}
static void ws_fall_slow(void)
{
    SPIDER(1);
    so.y_speed = 0x10000;
    web_spider_fall(&so);
}
static void ws_fall_slow_done(void)
{
    SPIDER(1);
    so.animation_step.fields.relative_step = 0;
    web_spider_fall(&so);
}
static void ws_fall_land(void)
{
    SPIDER(2);
    so.collision_flags = 8;
    web_spider_fall(&so);
}
static void ws_fall_drop(void)
{
    SPIDER(2);
    so.y_speed = -0x10000;
    web_spider_fall(&so);
}
static void ws_crash_hurt(void)
{
    SPIDER(3);
    so.hp = 0x20;
    so.animation_step.fields.relative_step = 1;
    so.animation_step.fields.event = 1;
    web_spider_fall(&so);
}
static void ws_crash_wait(void)
{
    SPIDER(3);
    so.animation_step.fields.relative_step = 1;
    web_spider_fall(&so);
}
static void ws_crash_done(void)
{
    SPIDER(3);
    web_spider_fall(&so);
}
static void ws_rethread_left(void)
{
    SPIDER(4);
    so.animation_step.fields.relative_step = 1;
    so.animation_step.fields.event = 1;
    web_spider_fall(&so);
    state_extra = shot_objects[0].unk84.value;
}
static void ws_rethread_right(void)
{
    SPIDER(4);
    so.unk15 = 0x40;
    so.animation_step.fields.relative_step = 1;
    so.animation_step.fields.event = 1;
    web_spider_fall(&so);
    state_extra = shot_objects[0].unk84.value;
}
static void ws_rethread_wait(void)
{
    SPIDER(4);
    so.animation_step.fields.relative_step = 1;
    web_spider_fall(&so);
}
static void ws_rethread_climb(void)
{
    SPIDER(4);
    spider_thread.unk84.value = 5;
    web_spider_fall(&so);
    THREAD();
}
static void ws_rethread_pull(void)
{
    SPIDER(4);
    spider_thread.unk5 = 1;
    spider_thread.unk84.value = 5;
    web_spider_fall(&so);
    THREAD();
}

static void (*const web_spider_fall_states_cases[])(void) = {
    ws_fall_start,
    ws_fall_slow,
    ws_fall_slow_done,
    ws_fall_land,
    ws_fall_drop,
    ws_crash_hurt,
    ws_crash_wait,
    ws_crash_done,
    ws_rethread_left,
    ws_rethread_right,
    ws_rethread_wait,
    ws_rethread_climb,
    ws_rethread_pull,
};
static const u32 web_spider_fall_states_expected[] = { 0x10100u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0x40000u, 0x400000u, 0x50000u, 0x1000000u, 0u, 0x20100u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0xFFFF8000u, 0x800000u, 0x50000u, 0u, 0u, 0x20100u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0xFFFF8000u, 0x800000u, 0x50000u, 0u, 0u, 0x30100u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x20100u, 0u, 0x800000u, 0x610000u, 0u, 0xFFFF0000u, 0u, 0x40000u, 0u, 0u, 0x30100u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x30100u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x40100u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x40100u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x40100u, 0x400000u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x40100u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x1010200u, 0xFF000000u, 0x800000u, 0x600000u, 0u, 0x38000u, 0u, 0x40000u, 0u, 0u, 0x40100u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 5u, 0u };

static u32 test_web_spider_fall_states(u32 row)
{
    return object_run(web_spider_fall_states_cases[row], row, &web_spider_fall_states_expected[row * 10]);
}

static void ws_slow_descent(void)
{
    state_reset(3, 1, 0);
    so.animation_step.fields.relative_step = 1;
    so.gravity = 0x1000;
    web_spider_fall_slow(&so);
}
static void ws_slow_done(void)
{
    state_reset(3, 1, 0);
    web_spider_fall_slow(&so);
}

static void (*const web_spider_misc_cases[])(void) = {
    ws_slow_descent,
    ws_slow_done,
};
static const u32 web_spider_misc_expected[] = { 0x103u, 0u, 0u, 0u, 0xFFFFF000u, 0x100000u, 0u, 0u, 0u, 0u, 0x203u, 0u, 0u, 0u, 0xFFFF8000u, 0x800000u, 0xEu, 0u, 0u, 0u };

static u32 test_web_spider_misc(u32 row)
{
    return state_run(web_spider_misc_cases[row], row, &web_spider_misc_expected[row * 10]);
}

extern union AnimationStep* web_spider_animations[40];
extern u16 web_spider_arena_x;
static struct QuadObj quads_before[32];
static struct MiscObj misc_before[64];
static struct VisualObj visuals_expected[32];
static u32 full(u32 row)
{
    struct MainObj spider, parent_before;
    struct PlayerObj player;
    struct EngineObj engine;
    struct VisualObj* piece = &visual_objects[0];
    u32 i;
    (void)row;
    engine_obj.stage = 12;
    engine_obj.substage = 0;
    engine_obj.checkpoint = 2;
    background_objects[0].x_pos.i.hi = 4096;
    background_objects[0].y_pos.i.hi = 1536;
    background_objects[0].unk26 = 4096;
    web_spider_arena_x = 4096;
    D_8013E198[2] = -1;
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)g_QuadObjects, sizeof(g_QuadObjects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    for (i = 0; i < COUNT(g_QuadObjects); i++)
        g_QuadObjects[i].active = 1;
    memset(&spider, 0, sizeof(spider));
    spider.active = 0x41;
    spider.id = 43;
    spider.state = 1;
    spider.unk5 = 6;
    spider.y_pos.i.hi = 1624;
    spider.animation_table = (const u8* const*)web_spider_animations;
    func_800646EC(&spider);
    for (i = 0; i < 256 && spider.unk6 == 0; i++)
        func_800646EC(&spider);
    assert(spider.unk6 == 1 && spider.unk7 == 0 && spider.x_pos.i.hi == 4272);
    web_spider_big_web_spin(&spider);
    for (i = 0; i < 28; i++)
        web_spider_big_web_spin(&spider);
    assert(piece->active == 0x41 && piece->id == 17 && piece->unk2 == 1 && piece->unk50 == (struct PlayerObj*)&spider);
    memcpy(visuals_expected, visual_objects, sizeof(visuals_expected));
    visuals_expected[0].state = 1;
    visuals_expected[0].on_screen = 1;
    visuals_expected[0].unk16 = 5;
    set_animation(&visuals_expected[0], 23);
    visuals_expected[0].unk54 = angle_from_delta(piece->x_pos.val - 4288 * 65536, piece->y_pos.val - 1592 * 65536);
    set_velocity_from_angle(MOVING_OBJECT(&visuals_expected[0]), visuals_expected[0].unk54);
    visuals_expected[0].x_vel.val *= 2;
    visuals_expected[0].y_vel.val *= 2;
    visuals_expected[0].unk28 = 0;
    visuals_expected[0].unk2C = 0;
    memcpy(quads_before, g_QuadObjects, sizeof(quads_before));
    memcpy(misc_before, misc_objects, sizeof(misc_before));
    parent_before = spider;
    player = g_Player;
    engine = engine_obj;
    cur_random = 0x1234;
    func_800B20CC(piece);
    assert(c_test_word_difference((u32*)visual_objects, (u32*)visuals_expected, sizeof(visuals_expected) / 4) == 0);
    assert(c_test_word_difference((u32*)g_QuadObjects, (u32*)quads_before, sizeof(quads_before) / 4) == 0);
    assert(c_test_word_difference((u32*)misc_objects, (u32*)misc_before, sizeof(misc_before) / 4) == 0);
    c_test_same_words(&spider, &parent_before, sizeof(spider));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "web_spider_misc", 0, 0, COUNT(web_spider_misc_cases), test_web_spider_misc },
    { "web_spider_fall_states", 0, 0, COUNT(web_spider_fall_states_cases), test_web_spider_fall_states },
    { "spider_interpolation_context", NULL, spider_interpolation_context_cases_expected, COUNT(spider_interpolation_context_cases_expected), interpolate },
    { "spider_sweep_context", NULL, spider_sweep_context_cases_expected, COUNT(spider_sweep_context_cases_expected), spider_sweep_context_cases_row },
    { "web_spider_big_web_steps", web_spider_big_web_steps_cases, web_spider_big_web_steps_cases_expected, COUNT(web_spider_big_web_steps_cases), 0 },
    { "web_spider_climb_stun_default", NULL, web_spider_climb_stun_default_cases_expected, COUNT(web_spider_climb_stun_default_cases_expected), climb_case },
    { "web_spider_defeat_check", NULL, web_spider_defeat_check_cases_expected, COUNT(web_spider_defeat_check_cases_expected), web_spider_defeat_check_run },
    { "web_spider_late_steps", NULL, web_spider_late_steps_cases_expected, COUNT(web_spider_late_steps_cases_expected), web_spider_late_steps_run },
    { "web_spider_spawns", NULL, web_spider_spawns_cases_expected, COUNT(web_spider_spawns_cases_expected), web_spider_spawns_run },
    { "web_spider_check_big_web", 0, 0, 1, test_web_spider_check_big_web },
    { "stage12_actual_big_web_start_spin_and_piece_factory_full_quad_pool", NULL, NULL, 1, full },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(web_spider_misc_cases) + COUNT(web_spider_fall_states_cases) + COUNT(spider_interpolation_context_cases_expected) + COUNT(spider_sweep_context_cases_expected) + COUNT(web_spider_big_web_steps_cases) + COUNT(web_spider_climb_stun_default_cases_expected) + COUNT(web_spider_defeat_check_cases_expected) + COUNT(web_spider_late_steps_cases_expected) + COUNT(web_spider_spawns_cases_expected) + 1 + 1;
