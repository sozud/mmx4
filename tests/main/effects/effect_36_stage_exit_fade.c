#include "test_runtime.h"
#include "main/effects/effect_36_stage_exit_fade.h"
#include "support/state_cases.h"

#include "support/pool_full.h"
#include "main/14A60.h"
#include "main/1A5BC.h"
static u32 pool_full_stage_exit_fade_init(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    stage_exit_fade_init(&pf_effect);
    pf_effect_expected.ext.effect_36.timer = 0x1E;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_stage_exit_fade_init,
};

static const u32 pool_full_cases_expected[] = { 0x50000u };
#define se state_room.effect
#define FADE(st) (state_reset(0, 0, 0), se.active = 1, se.state = st, se.ext.effect_36.spawned_effect = &effect_objects[0])
#define KEEP(body)                                                                                                                         \
    do {                                                                                                                                   \
        s16 invincible = g_Player.invincibility_timer;                                                                                     \
        u8 flags = engine_obj.unkF;                                                                                                        \
        g_Player.invincibility_timer = 0;                                                                                                  \
        engine_obj.unkF = 0;                                                                                                               \
        body;                                                                                                                              \
        state_extra = g_Player.invincibility_timer | engine_obj.unkF << 8 | (se.ext.effect_36.spawned_effect == &effect_objects[0]) << 16; \
        g_Player.invincibility_timer = invincible;                                                                                         \
        engine_obj.unkF = flags;                                                                                                           \
    } while (0)
static void ef_init(void)
{
    KEEP((FADE(0), stage_exit_fade_update(&se)));
}
static void ef_wait(void) { KEEP((FADE(1), effect_objects[0].active = 1, effect_objects[0].id = 2, stage_exit_fade_update(&se))); }
static void ef_wait_gone(void) { KEEP((FADE(1), stage_exit_fade_update(&se))); }
static void ef_wait_reused(void) { KEEP((FADE(1), effect_objects[0].active = 1, effect_objects[0].id = 3, stage_exit_fade_update(&se))); }
static void ef_whiteout(void) { KEEP((FADE(2), se.ext.effect_36.timer = 2, stage_exit_fade_update(&se))); }
static s32 fade_saved[4];
static u8 fade_modes[3];
static void ef_whiteout_done(void)
{
    memcpy(fade_saved, D_8013E188, sizeof(fade_saved));
    fade_modes[0] = g_FilterModeR, fade_modes[1] = g_FilterModeG, fade_modes[2] = g_FilterModeB;
    KEEP((FADE(2), se.ext.effect_36.timer = 1, stage_exit_fade_update(&se)));
    state_extra ^= g_FilterModeR | g_FilterModeG << 4 | g_FilterModeB << 8 | (u32)D_8013E188[3] << 24;
    memcpy(D_8013E188, fade_saved, sizeof(fade_saved));
    g_FilterModeR = fade_modes[0], g_FilterModeG = fade_modes[1], g_FilterModeB = fade_modes[2];
}
static void ef_finish(void) { KEEP((FADE(3), stage_exit_fade_update(&se))); }

static void (*const stage_exit_fade_states_cases[])(void) = {
    ef_init,
    ef_wait,
    ef_wait_gone,
    ef_wait_reused,
    ef_whiteout,
    ef_whiteout_done,
    ef_finish,
};
static const u32 stage_exit_fade_states_expected[] = { 0x1E0101u, 0xC0201u, 0x10000u, 0u, 0x101u, 0x201u, 0x10000u, 0u, 0x201u, 0u, 0x10078u, 0u, 0x201u, 0x301u, 0x10078u, 0u, 0x10201u, 0u, 0x10078u, 0u, 0x301u, 0u, 0xFF010459u, 0u, 0u, 0u, 0x14000u, 0u };

static u32 fade_run(void (*run)(void), u32 row, const u32* expected)
{
    u32 seen[4];
    run();
    seen[0] = (u8)se.active | (u8)se.state << 8 | (u32)se.ext.effect_36.timer << 16;
    seen[1] = effect_objects[0].active | effect_objects[0].id << 8 | (u32)effect_objects[0].unk2 << 16;
    seen[2] = state_extra;
    seen[3] = (u8)se.id | (u8)se.unk2 << 8;
    return c_test_observe(0, row, seen, expected, 4);
}

static u32 test_stage_exit_fade_states(u32 row)
{
    return fade_run(stage_exit_fade_states_cases[row], row, &stage_exit_fade_states_expected[row * 4]);
}

void stage_exit_fade_whiteout(struct EffectObj*);
static POLY_F4 primitives[4], expected_primitives[4];
static struct DrawInfo draw, expected_draw;
static u32 gauge(u32 row)
{
    struct EffectObj fade, expected_fade;
    struct PlayerObj expected_player;
    struct EngineObj engine_before;
    struct MainBssState main_before = main_bss_state;
    u32 i, hp = row ? 20 : 2;
    engine_obj.stage = 4;
    engine_obj.substage = 0;
    engine_obj.max_hp = 32;
    engine_before = engine_obj;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.hp = hp;
    g_Player.hud_hp = 24;
    g_Player.drain_hold_timer = 1;
    expected_player = g_Player;
    expected_player.invincibility_timer = 120;
    expected_player.drain_hold_timer = 0;
    memset(&fade, 0, sizeof(fade));
    fade.active = 1;
    fade.id = 36;
    fade.state = 2;
    fade.ext.effect_36.timer = 1;
    expected_fade = fade;
    expected_fade.state = 3;
    expected_fade.ext.effect_36.timer = 0;
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 7;
    stage_exit_fade_whiteout(&fade);
    memset(primitives, 0xA5, sizeof(primitives));
    memset(&draw, 0, sizeof(draw));
    setaddr(&draw.ordering_table.unk3, 0x543210);
    expected_draw = draw;
    cur_draw_info = &draw;
    SP_AUX_CURSOR = &primitives[1];
    memcpy(expected_primitives, primitives, sizeof(primitives));
    for (i = 1; i <= 2; i++) {
        POLY_F4* p = &expected_primitives[i];
        setPolyF4(p);
        p->r0 = p->g0 = p->b0 = 0;
        p->x0 = p->x2 = 22;
        p->x1 = p->x3 = 27;
        p->y0 = p->y1 = i == 1 ? 79 - hp : 55;
        p->y2 = p->y3 = i == 1 ? 79 : 79 - hp;
        setaddr(p, i == 1 ? (void*)0x543210 : &primitives[1]);
    }
    setaddr(&expected_draw.ordering_table.unk3, &primitives[2]);
    func_800253F0(MAIN_OBJECT(&g_Player), 0);
    c_test_same_words(primitives, expected_primitives, sizeof(primitives));
    c_test_same_words(&draw, &expected_draw, sizeof(draw));
    c_test_same_words(&g_Player, &expected_player, sizeof(g_Player));
    c_test_same_words(&fade, &expected_fade, sizeof(fade));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    assert(cur_draw_info == &draw && SP_AUX_POLY_F4_CURSOR == &primitives[3]);
    for (i = 0; i < 4; i++)
        assert(D_8013E188[i] == -1);
    assert(g_FilterModeR == 1 && g_FilterModeG == 2 && g_FilterModeB == 4 && g_FilterAmountR == 31 && g_FilterAmountG == 0x3E0 && g_FilterAmountB == 0x7C00);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "stage_exit_fade_states", 0, 0, COUNT(stage_exit_fade_states_cases), test_stage_exit_fade_states },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "real_stage_exit_filter_clamps_normal_low_and_damage_HP_bars", NULL, NULL, 2, gauge },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(stage_exit_fade_states_cases) + COUNT(pool_full_cases) + 2;
