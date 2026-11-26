#include "test_runtime.h"
#include "main/102FC.h"
#include "support/state_cases.h"
#ifdef MMX4_SATURN
#include "saturn/menu.h"
#include "saturn/player_resources.h"
#else
#include <unistd.h>
#include <stdlib.h>
#include <psyz/cd.h>
#include <psyz/spu.h>
#include "archive_memory.h"
#endif

#ifdef VERSION_DEMO
static const struct {
    s8 outcome, stage, substage, palette_flags, lives;
} demo_outcomes[] = {
    { 1, 3, 1, 4, 2 },
    { 1, 3, 1, 0, 2 },
    { 1, 3, 0, 0, 2 },
    { 1, 11, 0, 0, 2 },
    { 1, 0, 0, 0, 2 },
    { 1, 0, 1, 0, 2 },
    { 1, 12, 1, 0, 2 },
    { -1, 12, 1, 0, 2 },
    { 0, 12, 1, 0, 2 },
    { 0, 12, 1, 0, 0 },
};

static u32 outcome_case(u32 row)
{
    struct EngineObj expected;
    struct PlayerObj player_expected;
    u32 i;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    engine_obj.state = 3;
    engine_obj.unk1 = 9;
    engine_obj.unkF = demo_outcomes[row].outcome;
    engine_obj.stage = demo_outcomes[row].stage;
    engine_obj.substage = demo_outcomes[row].substage;
    engine_obj.palette_flags = demo_outcomes[row].palette_flags;
    engine_obj.player_lives = demo_outcomes[row].lives;
    engine_obj.unk1E = 4;
    engine_obj.unk42 = 0x22;
    engine_obj.unk5F = 0x66;
    engine_obj.checkpoint_hp = 0x33;
    g_Player.hp = 27;
    for (i = 0; i < 16; i++) {
        g_Player.weapon_energy[i] = 3 + i;
        engine_obj.player_initial_data[i] = 0x88 + i;
    }
    expected = engine_obj;
    player_expected = g_Player;
    expected.unk1 = 0;
    expected.unkF = 0;
    if (demo_outcomes[row].outcome > 0) {
        s8 stage = demo_outcomes[row].stage, substage = demo_outcomes[row].substage;
        expected.unk1E = 0;
        if (stage != 0 && stage < 9) {
            if (substage != 0) {
                expected.state = (demo_outcomes[row].palette_flags >> (stage - 1)) & 1 ? 3 : 7;
            } else {
                expected.substage = substage + 1;
                expected.state = 4;
            }
        } else if (substage == 0 && (stage == 11 || stage == 0)) {
            expected.substage = 1;
            expected.state = 4;
        } else {
            expected.state = 3;
            if (stage == 0)
                expected.sub_tanks[2] = 2;
        }
    } else if (demo_outcomes[row].outcome < 0) {
        expected.unk1E = -1;
        expected.checkpoint_hp = 27;
        for (i = 0; i < 16; i++)
            expected.player_initial_data[i] = 3 + i;
        expected.unk42 = 1;
        expected.state = 5;
    } else {
        expected.player_lives = demo_outcomes[row].lives - 1;
        if (expected.player_lives < 0) {
            expected.state = 8;
        } else {
            expected.unk1E = 0;
            expected.state = 5;
        }
    }
    func_800200D4(&engine_obj);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    return (u8)engine_obj.state | ((u32)(u8)engine_obj.unk1E << 8) | ((u32)(u8)engine_obj.unk42 << 16) | ((u32)(u8)engine_obj.unk5F << 24);
}
static const u32 engine_outcome_transition_context_cases_expected[] = {
    0x66220003u,
    0x66220007u,
    0x66220004u,
    0x66220004u,
    0x66220004u,
    0x66220003u,
    0x66220003u,
    0x6601FF05u,
    0x66220005u,
    0x66220408u,
};
#else
static u32 outcome_case(u32 mode)
{
    struct EngineObj expected;
    struct PlayerObj player_expected;
    struct EffectObj pool_expected[32];
    u32 i;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(effect_objects, 0, sizeof(effect_objects));
    engine_obj.state = 3;
    engine_obj.unk1 = 9;
    engine_obj.unkF = mode < 2 ? 1 : -1;
    engine_obj.stage = mode == 1 ? 10 : mode == 5 ? 11
                                                  : 12;
    engine_obj.substage = mode < 2 || mode >= 4 ? 1 : 0;
    engine_obj.checkpoint = mode == 3 ? 9 : 10;
    engine_obj.unk1E = 4;
    engine_obj.unk42 = 0x22;
    engine_obj.unk5F = 0x66;
    engine_obj.checkpoint_hp = 0x33;
    engine_obj.unk60 = 0x44;
    g_Player.hp = 27;
    g_Player.weapon = 5;
    for (i = 0; i < 16; i++) {
        g_Player.weapon_energy[i] = 3 + i;
        engine_obj.player_initial_data[i] = 0x88 + i;
        engine_obj.character_state.bytes[i] = 0xA0 + i;
    }
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = i == 2 ? 0 : 0x41;
        effect_objects[i].id = i == 1 ? 3 : 2;
        effect_objects[i].unk2 = i == 3 ? 15 : 14;
        effect_objects[i].on_screen = 9;
        effect_objects[i].state = 7;
        effect_objects[i].unk5 = 8;
        effect_objects[i].unk6 = 9;
        effect_objects[i].unk7 = 10;
    }
    expected = engine_obj;
    player_expected = g_Player;
    memcpy(pool_expected, effect_objects, sizeof(pool_expected));
    expected.unk1 = 0;
    expected.unkF = 0;
    if (mode < 2) {
        expected.unk1E = 0;
        expected.state = mode == 0 ? 11 : 9;
        if (mode == 1)
            expected.unk5F = 7;
    } else {
        expected.unk1E = -1;
        expected.state = 5;
        expected.checkpoint_hp = 27;
        expected.unk60 = 5;
        for (i = 0; i < 16; i++)
            expected.player_initial_data[i] = 3 + i;
        if (mode == 2 || mode == 5)
            expected.unk42 = 1;
        for (i = 0; i < 32; i++)
            if (i != 1 && i != 2 && i != 3) {
                ((u32*)&pool_expected[i])[0] = 0;
                ((u32*)&pool_expected[i])[1] = 0;
            }
    }
    func_800200D4(&engine_obj);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)pool_expected)[i]);
    i = (u8)engine_obj.state | ((u32)(u8)engine_obj.unk1E << 8) | ((u32)(u8)engine_obj.unk42 << 16) | ((u32)(u8)engine_obj.unk5F << 24);
    return i;
}
static const u32 engine_outcome_transition_context_cases_expected[] = { 0x6622000Bu, 0x7220009u, 0x6601FF05u, 0x6622FF05u, 0x6622FF05u, 0x6601FF05u };
#endif

struct func_8001FDBC_case {
    u32 stage, checkpoint, substage, cur_character, pool_1_full, pool_0_full;
    u32 expected[6];
};
static const struct func_8001FDBC_case func_8001FDBC_cases[] = {
    { 5, -1, 0, 0, 0, 255, { 1u, 0u, 1u, 0u, 0u, 0u } },
    { 12, -1, -1, 0, 0, 255, { 1u, 0u, 1u, 0u, 0u, 0u } },
    { 12, 0, -1, -1, 255, 0, { 0u, 0u, 0xFFFFFFFEu, 1u, 0u, 0u } },
};
static u32 test_func_8001FDBC(u32 row)
{
    const struct func_8001FDBC_case* c = &func_8001FDBC_cases[row];
    u32 observed_values[6];
    u8 pool_1_full;
    u8 pool_0_full;
    memset(&effect_objects, 0, sizeof(effect_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&misc_objects, 0, sizeof(misc_objects));
    engine_obj.stage = c->stage;
    engine_obj.checkpoint = c->checkpoint;
    engine_obj.substage = c->substage;
    engine_obj.cur_character = c->cur_character;
    pool_1_full = c->pool_1_full;
    pool_0_full = c->pool_0_full;
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_1_full ? 1 : 0;
    }
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            effect_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8001FDBC();
    observed_values[0] = (u32)effect_objects[0].active;
    observed_values[1] = (u32)effect_objects[0].id;
    observed_values[2] = (u32)engine_obj.unk1E;
    observed_values[3] = (u32)misc_objects[0].active;
    observed_values[4] = (u32)misc_objects[0].id;
    observed_values[5] = (u32)misc_objects[0].unk2;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}

static struct EngineObj exit_saved;
#define exit_engine engine_obj
#define EXIT(flag, stage_id, sub, setup) (exit_saved = engine_obj, state_reset(0, 0, 0), memset(&exit_engine, 0, sizeof(exit_engine)), exit_engine.unkF = flag, exit_engine.stage = stage_id, exit_engine.substage = sub, exit_engine.player_lives = 2, exit_engine.unk1 = 3, setup, func_800200D4(&exit_engine), state_extra = exit_engine.state | (u8)exit_engine.unk1E << 8 | exit_engine.substage << 16 | (u32)exit_engine.unk5F << 24, so.unk7E = (u8)exit_engine.player_lives | exit_engine.checkpoint << 8, so.unk7C = exit_engine.unk42 | exit_engine.character_state.bytes[3] << 8, engine_obj = exit_saved)
static void ex_clear_first(void)
{
    EXIT(1, 3, 0, 0);
}
static void ex_clear_revisit(void) { EXIT(1, 3, 1, exit_engine.palette_flags = 4); }
static void ex_clear_new(void) { EXIT(1, 3, 1, 0); }
static void ex_clear_intro(void) { EXIT(1, 0, 0, 0); }
static void ex_clear_fortress(void) { EXIT(1, 0xC, 0, 0); }
static void ex_clear_final(void) { EXIT(1, 0xC, 1, 0); }
static void ex_clear_intro_done(void) { EXIT(1, 0, 1, 0); }
static void ex_clear_nine(void) { EXIT(1, 9, 0, 0); }
static void ex_clear_ten(void) { EXIT(1, 0xA, 0, 0); }
static void ex_clear_eleven(void) { EXIT(1, 0xB, 1, 0); }
static void ex_clear_other(void) { EXIT(1, 0xD, 1, 0); }
static void ex_checkpoint(void) { EXIT(-1, 3, 0, 0); }
static void ex_checkpoint_fortress(void) { EXIT(-1, 0xC, 0, exit_engine.checkpoint = 0xA); }
static void ex_checkpoint_fortress_mid(void) { EXIT(-1, 0xC, 0, exit_engine.checkpoint = 3); }
static void ex_death(void) { EXIT(0, 3, 0, 0); }
static void ex_game_over(void) { EXIT(0, 3, 0, exit_engine.player_lives = 0); }
static void ex_game_over_fortress(void) { EXIT(0, 0xC, 0, (exit_engine.player_lives = 0, exit_engine.character_state.bytes[3] = 1)); }
static void ex_death_final(void)
{
    u8 seen = D_80171EA8;
    EXIT(0, 0xC, 1, D_80171EA8 = 1);
    D_80171EA8 = seen;
}

static void (*const stage_exit_states_cases[])(void) = {
    ex_clear_first,
    ex_clear_revisit,
    ex_clear_new,
    ex_clear_intro,
    ex_clear_fortress,
    ex_clear_final,
    ex_clear_intro_done,
    ex_clear_nine,
    ex_clear_ten,
    ex_clear_eleven,
    ex_clear_other,
    ex_checkpoint,
    ex_checkpoint_fortress,
    ex_checkpoint_fortress_mid,
    ex_death,
    ex_game_over,
    ex_game_over_fortress,
    ex_death_final,
};
static const u32 stage_exit_states_expected[] = { 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10004u, 0u, 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10009u, 0u, 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10007u, 0u, 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10004u, 0u, 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 0xAu, 0u, 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000Bu, 0u, 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x2010009u, 0u, 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x4000009u, 0u, 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x7000009u, 0u, 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 0xA010009u, 0u, 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10009u, 0u, 0u, 0x20001u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFF05u, 0u, 0u, 0xA020001u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFF05u, 0u, 0u, 0x3020000u, 0u, 0u, 0u, 0u, 0u, 0u, 0xFF05u, 0u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 5u, 0u, 0u, 0xFF0000u, 0u, 0u, 0u, 0u, 0u, 0u, 8u, 0u, 0u, 0xFF0000u, 0u, 0u, 0u, 0u, 0u, 0u, 8u, 0u, 0u, 0x10000u, 0u, 0u, 0u, 0u, 0u, 0u, 0x10004u, 0u };

static u32 test_stage_exit_states(u32 row)
{
    return state_run(stage_exit_states_cases[row], row, &stage_exit_states_expected[row * 10]);
}

void func_800200D4(struct EngineObj*);
static u32 handoff(u32 row)
{
    struct EngineObj expected;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    struct GameInfo game_before = game_info;
    u32 i, stage = row % 2 ? 12 : 11, finish = row / 2;
#ifdef MMX4_PC
    ResetGraph(0);
#endif
    engine_obj.state = 6;
    engine_obj.unk1 = 1;
    engine_obj.stage = stage;
    engine_obj.substage = 0;
    engine_obj.cur_character = 0;
    engine_obj.unkF = 1;
    engine_obj.unk1E = 7;
    expected = engine_obj;
    expected.state = 10;
    expected.unk1 = expected.unkF = expected.unk1E = 0;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    func_800200D4(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(engine_obj));
#ifdef MMX4_SATURN
    c_test_skip();
#endif
    expected.unk1 = 1;
    func_80020464(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(engine_obj));
    if (finish) {
        expected.state = 4;
        expected.unk1 = 0;
        expected.substage = 1;
        func_80020464(&engine_obj);
    }
    c_test_same_words(&engine_obj, &expected, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    for (i = 0; i < sizeof(game_info); i++)
        assert(((const u8*)&game_info)[i] == ((const u8*)&game_before)[i]);
    return 1;
}

static u32 fortress_outcomes_row(u32 row)
{
    static const s8 flags[] = { 1, -1, 0, 0, 0, 0 };
    static const u8 substages[] = { 2, 1, 0, 1, 0, 1 }, states[] = { 9, 5, 5, 5, 0, 8 };
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(effect_objects, 0, sizeof(effect_objects));
    engine_obj.stage = 12;
#ifndef VERSION_DEMO
    if (row == 4) {
        engine_obj.checkpoint = 1;
        assert(func_8001FD7C(&engine_obj) == 0);
        return 0;
    }
#endif
    engine_obj.unkF = flags[row];
    engine_obj.substage = substages[row];
    engine_obj.checkpoint = row == 2 ? 5 : 3;
    engine_obj.player_lives = row == 5 ? 0 : 2;
    engine_obj.character_state.bytes[3] = 7;
    D_80171EA8 = 0;
    func_800200D4(&engine_obj);
    assert(engine_obj.state == states[row] && engine_obj.unk42 == 0 && engine_obj.unkF == 0);
    assert(engine_obj.character_state.bytes[3] == 7);
    assert(engine_obj.checkpoint == (row == 2 ? 1 : 3));
    return engine_obj.state;
}
#ifdef VERSION_DEMO
#define FORTRESS_CASES 4
#else
#define FORTRESS_CASES 5
#endif
static u32 fortress_outcomes(u32 row)
{
#ifdef VERSION_DEMO
    static const u8 kept[] = { 0, 2, 3, 5 };
#else
    static const u8 kept[] = { 0, 2, 3, 4, 5 };
#endif
    return fortress_outcomes_row(kept[row]);
}

static u32 stage_intro_marks(u32 row)
{
    u32 i;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    engine_obj.stage = row ? 12 : 5;
    engine_obj.substage = row == 2;
    engine_obj.unk1E = row == 1 ? 3 : 0;
    func_8001FDBC();
    assert(engine_obj.unk1E == (row == 0 ? 1 : row == 1 ? 3
                                                        : -2));
    for (i = 0; i < COUNT(effect_objects); i++)
        assert(effect_objects[i].active == 0);
    for (i = 0; i < COUNT(misc_objects); i++)
        assert(misc_objects[i].active == 0);
    return 1;
}

#ifndef MMX4_SATURN
void func_8001FEC0(void);
static u32 stage_music_row(u32 row)
{
    static const u8 stages[] = { 12, 12, 12, 12, 9 }, substages[] = { 1, 1, 0, 0, 0 }, checkpoints[] = { 0, 0, 5, 1, 0 };
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.stage = stages[row];
    engine_obj.substage = substages[row];
    engine_obj.checkpoint = checkpoints[row];
    engine_obj.character_state.bytes[8] = row == 0;
    D_80173C84 = 0;
    func_8001FEC0();
    assert(D_80173C84 == (row == 2 || row == 4 ? 0 : 1));
    D_80173C84 = 0;
    return 1;
}

#endif

#ifndef MMX4_SATURN
extern u8 pad_port1_packet[];
#endif
void func_80012854(s32);
static u8 frame_map[3 * 256];
static u16 frame_tiles[2][256], frame_palette[0x800];
static u32 frame_attrs[2];
static u32 stage_pause_row(u32 row)
{
    u32 pauses = row == 0 || row == 3;
    u16 random;
#ifndef MMX4_SATURN
    static struct DrawInfo draw;
    memset(&draw, 0, sizeof(draw));
    cur_draw_info = &draw;
    memset(&controller_input, 0, sizeof(controller_input));
#endif
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(background_objects, 0, sizeof(background_objects));
    SP_BG_TILEMAP = frame_map;
    TEST_BG_TILE_PIXELS = (u8*)frame_tiles;
    TEST_BG_TILE_ATTRS = (u8*)frame_attrs;
    TEST_PALETTE = (u8*)frame_palette;
    layout_width = layout_height = 16;
    layout_size = 256;
    engine_obj.state = 6;
    engine_obj.unk1 = 0;
    engine_obj.stage = 1;
    engine_obj.gameplay_locked = row == 1 || row == 7;
    main_bss_state.transition.active = row == 2;
#ifdef MMX4_SATURN
    saturn_pad_pressed = row == 3 || row == 4 ? 0 : SATURN_PAD_START;
    saturn_pause_request = row == 3;
    saturn_pause_latch = 0;
#else
    controller_input.pressed = row == 3 || row == 4 ? 0 : PADstart;
    pad_port1_packet[0] = row == 3 ? 0xFF : 0;
#endif
    engine_obj.unk10 = row == 5;
    engine_obj.unkF = row == 6;
    g_Player.state = row == 7 ? 3 : 0;
    cur_random = 0x1234;
    random = cur_random;
    func_8001FF8C(&engine_obj);
#ifdef MMX4_SATURN
    assert(saturn_pause_latch == (row == 3));
    saturn_pause_request = saturn_pad_pressed = 0;
#else
    pad_port1_packet[0] = 0;
#endif
    assert(engine_obj.unk1 == (pauses ? 2 : row == 7 ? 1
                                                     : 0));
    assert(pauses ? cur_random == random : cur_random != random);
#ifdef MMX4_SATURN
    assert(main_bss_state.transition.active == (row == 7 ? 2 : row == 2));
#else
    assert(main_bss_state.transition.active == (row == 7 ? -1 : row == 2));
    if (row == 7) {
        assert(main_bss_state.transition.fade_amount == 8);
        func_80012854(2);
    }
#endif
    main_bss_state.transition.active = 0;
    return engine_obj.unk1;
}

#ifndef MMX4_SATURN
extern s32 D_80141BD4, D_80139564;
void func_80020060(struct EngineObj*);
static u32 outcome_music(u32 row)
{
    static struct DrawInfo draw;
    memset(&draw, 0, sizeof(draw));
    cur_draw_info = &draw;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(background_objects, 0, sizeof(background_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    SP_BG_TILEMAP = frame_map;
    TEST_BG_TILE_PIXELS = (u8*)frame_tiles;
    TEST_BG_TILE_ATTRS = (u8*)frame_attrs;
    TEST_PALETTE = (u8*)frame_palette;
    layout_width = layout_height = 16;
    layout_size = 256;
    engine_obj.state = 6;
    engine_obj.unk1 = 1;
    engine_obj.unkF = -1;
    engine_obj.stage = row == 2 ? 12 : 3;
    engine_obj.checkpoint = 3;
    main_bss_state.transition.active = row == 0;
    D_80141BD4 = 2;
    D_80139564 = 0;
    D_80173C84 = 1;
    SP_SPRITE_COUNT = 77;
    func_80020060(&engine_obj);
    if (row == 0) {
        assert(engine_obj.state == 6 && engine_obj.unk1 == 1 && SP_SPRITE_COUNT == 0 && D_80173C84 == 1);
    } else {
        assert(engine_obj.state == 5 && engine_obj.unk1 == 0 && engine_obj.unk42 == (row == 1));
        assert(D_80173C84 == (row == 1));
    }
    main_bss_state.transition.active = 0;
    D_80141BD4 = 0;
    D_80173C84 = 0;
    return engine_obj.state;
}
void func_80014DC4(void);
void func_80013588(void);
void func_80012E38(void);
void func_8001FC20(struct EngineObj*);
void func_80012EB8(void);
static u32 stage_start_row(u32 row)
{
    static struct DrawInfo draw;
    char cue[sizeof(__FILE__) + 32];
    char* suffix;
    strcpy(cue, __FILE__);
    suffix = strstr(cue, "/tests/main/102FC.c");
    assert(suffix != NULL);
    strcpy(suffix, "/disks/mmx4.us.cue");
    if (access(cue, R_OK) != 0)
        c_test_skip();
    assert(setenv("SDL_AUDIODRIVER", "dummy", 1) == 0);
    assert(Psyz_CdSetDiskPath(cue) == 0);
    Psyz_SpuInit();
    ResetGraph(0);
    func_80014DC4();
    func_80013588();
    func_80012E38();
    D_80173C80 = MAIN_ARCHIVE_ARENA;
    memset(&draw, 0, sizeof(draw));
    cur_draw_info = &draw;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.state = 4;
    engine_obj.stage = row < 2 ? 3 : 12;
    engine_obj.player_lives = 2;
    engine_obj.max_hp = 0x20;
    func_80012EB8();
    engine_state_4(&engine_obj);
    assert(engine_obj.state == 5);
    engine_obj.checkpoint = row < 2 ? 0 : 5;
    engine_obj.unk42 = row == 0;
    D_80171EA8 = row == 3 ? 5 : 0;
    D_80173C84 = 0;
    SP_PALETTE_WORDS[0x500 / 4] = 0x12345678;
    func_8001FC20(&engine_obj);
    assert(engine_obj.state == 6 && engine_obj.unk42 == 0 && engine_obj.gameplay_locked == 1);
    assert(D_80173C84 == (row == 1));
    assert(D_80171EA8 == (row < 2 ? 0 : 5));
    if (row == 2)
        assert(SP_PALETTE_WORDS[0x500 / 4] == SP_ARC_30[(5 << 5) + 0x280 / 4]);
    if (row == 3)
        assert(SP_PALETTE_WORDS[0x500 / 4] == 0x12345678);
    main_bss_state.transition.active = 0;
    func_80012854(2);
    D_80173C84 = 0;
    return 1;
}
static u32 stage_music(u32 row)
{
    static const u8 kept[] = { 0, 1, 4 };
    return stage_music_row(kept[row]);
}
static u32 stage_pause(u32 row)
{
    static const u8 kept[] = { 2, 3, 4, 5, 6, 7 };
    return stage_pause_row(kept[row]);
}
static u32 stage_start(u32 row)
{
    static const u8 kept[] = { 0, 2, 3 };
    return stage_start_row(kept[row]);
}
#define STAGE_CASES (3 + 6 + 3 + 3)
#else
#define STAGE_CASES 8
#endif

const struct CTestGroup c_test_groups[] = {
    { "stage_exit_states", 0, 0, COUNT(stage_exit_states_cases), test_stage_exit_states },
    { "engine_outcome_transition_context", NULL, engine_outcome_transition_context_cases_expected, COUNT(engine_outcome_transition_context_cases_expected), outcome_case },
    { "func_8001FDBC", 0, 0, 3, test_func_8001FDBC },
    { "real_stage_clear_entry_X_fortress_11_12_initial_and_completion_ticks", NULL, NULL, 4, handoff },
    { "stage_intro_marks", NULL, NULL, 3, stage_intro_marks },
    { "fortress_outcomes", NULL, NULL, FORTRESS_CASES, fortress_outcomes },
#ifndef MMX4_SATURN
    { "stage_music", NULL, NULL, 3, stage_music },
    { "stage_pause", NULL, NULL, 6, stage_pause },
    { "outcome_music", NULL, NULL, 3, outcome_music },
    { "stage_start_on_the_disc", NULL, NULL, 3, stage_start },
#else
    { "stage_pause", NULL, NULL, 8, stage_pause_row },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(stage_exit_states_cases) + COUNT(engine_outcome_transition_context_cases_expected) + 3 + 4 + 3 + FORTRESS_CASES + STAGE_CASES;
