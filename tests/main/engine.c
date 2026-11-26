#include "test_runtime.h"
#ifndef VERSION_DEMO
#include "main/engine.h"
#include "main/1AC84.h"
#include "support/test_pad.h"
#ifndef MMX4_SATURN
#include <unistd.h>
#include <stdlib.h>
#include <psyz/cd.h>
#include <psyz/spu.h>
#include "archive_memory.h"
#endif
extern struct MiscObj* D_801396C0;
extern struct MiscObj* D_801396C4;
s32 func_8001F8FC(struct GameInfo*);

static const u32 func_8001F6E8_expected[] = { 1u, 4u, 1u, 4u, 1u, 0u, 6u };
static u32 test_func_8001F6E8(u32 row)
{
    u32 observed_values[7];
    struct EngineObj obj;
    struct MiscObj child_0;
    struct MiscObj child_1;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&child_1, 0, sizeof(child_1));
    memset(&controller_input, 0, sizeof(controller_input));
    TEST_PAD_PRESSED = 255;
    D_801396C0 = &child_0;
    D_801396C4 = &child_1;
    func_8001F6E8(&obj);
    observed_values[0] = (u32)child_0.state;
    observed_values[1] = (u32)child_0.unk5;
    observed_values[2] = (u32)child_1.state;
    observed_values[3] = (u32)child_1.unk5;
    observed_values[4] = (u32)obj.unk2;
    observed_values[5] = (u32)obj.unk3;
    observed_values[6] = (u32)obj.unk4;
    return c_test_observe(0, row, observed_values, func_8001F6E8_expected, 7);
}
#undef controller_input

#ifndef MMX4_SATURN
struct func_8001F8FC_case {
    u32 unk6;
    u32 expected[2];
};
static const struct func_8001F8FC_case func_8001F8FC_cases[] = {
    { 0, { 1u, 0xFFFFFFFFu } },
    { 1, { 0u, 0u } },
};
static u32 test_func_8001F8FC(u32 row)
{
    const struct func_8001F8FC_case* c = &func_8001F8FC_cases[row];
    u32 observed_values[2];
    struct GameInfo obj;
    s32 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&D_80139520, 0, sizeof(D_80139520));
    memset(&D_80139524, 0, sizeof(D_80139524));
    memset(&D_80139528, 0, sizeof(D_80139528));
    memset(&D_80139530, 0, sizeof(D_80139530));
    memset(&D_8013955C, 0, sizeof(D_8013955C));
    memset(&D_80139564, 0, sizeof(D_80139564));
    memset(&D_80139568, 0, sizeof(D_80139568));
    memset(&D_80141BD4, 0, sizeof(D_80141BD4));
    memset(&D_80171EA9, 0, sizeof(D_80171EA9));
    memset(&D_80173C84, 0, sizeof(D_80173C84));
    obj.unk6 = c->unk6;
    return_value = func_8001F8FC(&obj);
    observed_values[0] = (u32)return_value;
    observed_values[1] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}
#endif

static u32 test_func_8001F798(u32 row)
{
    struct EngineObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk2 = 3;
    obj.unk3 = 7;
    obj.unk4 = 1;
    obj.cur_character = row;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 9;
    need_palette_load = 0x10;
    func_8001F798(&obj);
    assert(obj.unk2 == 4 && obj.unk3 == 0 && obj.unk4 == 0xF0);
    assert(*(s16*)&obj.unk6 == (row ? 0x46 : 0x3C));
    assert(g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0);
    assert(need_palette_load == 0x11);
    return 1;
}

struct func_8001FA24_case {
    u32 boss_flags;
    u32 expected[22];
};
static const struct func_8001FA24_case func_8001FA24_cases[] = {
    { -1, { 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 0u, 0u } },
    { 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 9u, 0u, 0u, 0u } },
};
static u32 test_func_8001FA24(u32 row)
{
    const struct func_8001FA24_case* c = &func_8001FA24_cases[row];
    u32 observed_values[22];
    struct EngineObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.character_state.bytes[0] = 17;
    g_Player.boss_flags = c->boss_flags;
    func_8001FA24(&obj);
    observed_values[0] = (u32)g_Player.boss_flags;
    observed_values[1] = (u32)obj.character_state.bytes[0];
    observed_values[2] = (u32)obj.character_state.bytes[10];
    observed_values[3] = (u32)obj.character_state.bytes[11];
    observed_values[4] = (u32)obj.character_state.bytes[12];
    observed_values[5] = (u32)obj.character_state.bytes[13];
    observed_values[6] = (u32)obj.character_state.bytes[14];
    observed_values[7] = (u32)obj.character_state.bytes[15];
    observed_values[8] = (u32)obj.character_state.bytes[1];
    observed_values[9] = (u32)obj.character_state.bytes[2];
    observed_values[10] = (u32)obj.character_state.bytes[3];
    observed_values[11] = (u32)obj.character_state.bytes[4];
    observed_values[12] = (u32)obj.character_state.bytes[5];
    observed_values[13] = (u32)obj.character_state.bytes[6];
    observed_values[14] = (u32)obj.character_state.bytes[7];
    observed_values[15] = (u32)obj.character_state.bytes[8];
    observed_values[16] = (u32)obj.character_state.bytes[9];
    observed_values[17] = (u32)obj.palette_flags;
    observed_values[18] = (u32)obj.state;
    observed_values[19] = (u32)obj.unk1;
    observed_values[20] = (u32)obj.unk2;
    observed_values[21] = (u32)obj.unk5F;
    return c_test_observe(0, row, observed_values, c->expected, 22);
}

void func_8001F488(struct EngineObj*);
void func_8001F3D4(struct MainObj*);
extern struct MiscObj *D_801396C0, *D_801396C4;
extern s32 D_801396B8;
static const u16 presses[] = { 0, 0x40, 0x800, 0x1000 };
static const s32 edges[] = { -1, 0, 1 };
static u32 scroll_case(u32 row, u32 direct)
{
    struct EngineObj expected;
    struct PlayerObj player_before = g_Player;
    struct MainBssState main_before = main_bss_state;
    struct MiscObj children[2], children_expected[2];
    struct BackgroundObj backgrounds_expected[3];
    struct ControllerInput input_before;
    u32 character = direct ? row : row % 2, edge = direct ? 1 : row / 2 % 3, press = direct ? 0 : row / 6, i;
    s32 velocity = character ? -65536 : 65536, target = character ? 0xFFFFFF : 0x2000000;
    u32 confirmed = (presses[press] & 0x8FF) != 0, finished = direct || confirmed || (character ? edges[edge] <= 0 : edges[edge] > 0);
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.state = 1;
    engine_obj.unk1 = 3;
    engine_obj.unk2 = 7;
    engine_obj.unk3 = 8;
    engine_obj.unk4 = 9;
    engine_obj.cur_character = character;
    memset(children, 0, sizeof(children));
    children[0].active = 0x41;
    children[0].id = 45;
    children[0].state = 2;
    children[0].unk5 = 1;
    children[1] = children[0];
    children[1].unk2 = 3;
    memcpy(children_expected, children, sizeof(children_expected));
    D_801396C0 = &children[0];
    D_801396C4 = &children[1];
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = (10 + i) * 65536 + 0x1234;
        background_objects[i].y_pos.val = (20 + i) * 65536 + 0x5678;
        background_objects[i].unk4C = 7;
    }
    background_objects[character].x_pos.val = target + edges[edge] - velocity;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    controller_input.held = 0x1357;
    controller_input.previous = 0x2468;
    TEST_PAD_PRESSED = presses[press];
    input_before = controller_input;
    D_801396B8 = velocity;
    g_FilterModeR = 1;
    g_FilterModeG = 2;
    g_FilterModeB = 3;
    g_FilterAmountR = 4;
    g_FilterAmountG = 5;
    g_FilterAmountB = 6;
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 10 + i;
    expected = engine_obj;
    if (!direct && !confirmed)
        backgrounds_expected[character].x_pos.val += velocity;
    if (finished) {
        expected.unk4 = 6;
        expected.unk3 = 0;
        expected.unk2 = 8;
        backgrounds_expected[character].x_pos.val = character ? 0x1000000 : 0x2000000;
        if (!direct && confirmed) {
            backgrounds_expected[character].unk4C = 1;
            expected.character_state.bytes[1] = expected.character_state.bytes[2] = 1;
            for (i = 0; i < 2; i++) {
                children_expected[i].state = 1;
                children_expected[i].unk5 = 4;
            }
        }
    }
    if (direct)
        func_8001F3D4((struct MainObj*)&engine_obj);
    else
        func_8001F488(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    c_test_same_words(children, children_expected, sizeof(children_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    assert(controller_input.held == input_before.held && controller_input.previous == input_before.previous && controller_input.pressed == input_before.pressed);
    assert(D_801396C0 == &children[0] && D_801396C4 == &children[1] && D_801396B8 == velocity);
    for (i = 0; i < 4; i++)
#ifdef MMX4_SATURN
        assert(D_8013E188[i] == (finished && i == 0 ? 0x7F : (s32)(10 + i)));
#else
        assert(D_8013E188[i] == (finished ? -1 : (s32)(10 + i)));
#endif
    assert(g_FilterModeR == (finished ? 0 : 1) && g_FilterModeG == (finished ? 0 : 2) && g_FilterModeB == (finished ? 0 : 3));
    assert(g_FilterAmountR == (finished ? 0 : 4) && g_FilterAmountG == (finished ? 0 : 5) && g_FilterAmountB == (finished ? 0 : 6));
    return 1;
}
static u32 scroll(u32 row) { return scroll_case(row, 0); }
static u32 complete(u32 row) { return scroll_case(row, 1); }

extern void func_8001F2BC(struct EngineObj*);
extern struct MiscObj* func_8001F150(struct EngineObj*, u8);
extern struct MiscObj *D_801396C0, *D_801396C4;
extern s32 D_801396B8, D_80139530, D_80141BD4;
extern u8 D_80139524, D_80139528;
static struct MiscObj expected_pool[64];
#ifndef MMX4_SATURN
static u32 enter(u32 row)
{
    struct EngineObj expected;
    struct PlayerObj player_before = g_Player;
    struct MainBssState main_expected;
    struct BackgroundObj backgrounds_expected[3];
    u32 character = row % 2, boss = row / 2 % 8 + 1, available = 2, i;
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.state = 1;
    engine_obj.unk1 = 2;
    engine_obj.unk2 = 1;
    engine_obj.stage = 15;
    engine_obj.cur_character = character;
    engine_obj.character_state.bytes[0] = boss;
    expected = engine_obj;
    expected.unk1 = 3;
    expected.unk2 = 0;
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    main_expected = main_bss_state;
    main_expected.transition.active = 1;
    main_expected.transition.fade_amount = 8;
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 3; i++)
        background_objects[i].x_pos.val = (10 + i) * 65536 + 0x1234;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    backgrounds_expected[character].x_pos.val = character ? 0x3000000 : 0;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 0;
    memcpy(expected_pool, misc_objects, sizeof(expected_pool));
    for (i = 0; i < available; i++) {
        struct MiscObj* m = &expected_pool[i];
        m->active = 0x41;
        m->id = 45;
        m->unk2 = i == 0 ? (character ? 9 : 0) : boss + (character ? 9 : 0);
    }
    func_8001F2BC(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    c_test_same_words(misc_objects, expected_pool, sizeof(expected_pool));
    assert(D_801396B8 == (character ? -0x100000 : 0x100000));
    assert(D_801396C0 == (available ? &misc_objects[0] : NULL));
    assert(D_801396C4 == (available == 2 ? &misc_objects[1] : NULL));
    assert(D_80139524 == 0x70 && D_80139528 == 0x70 && D_80141BD4 == 2 && D_80173C84 == 1 && D_80139530 == 7);
    return 1;
}
#endif
static u32 label_capacity(u32 row)
{
    struct EngineObj engine_before = engine_obj;
    struct PlayerObj player_before = g_Player;
    struct MiscObj* result;
    u32 full = row % 2, variant = row / 2 ? 9 : 0, i;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = i == 63 && !full ? 0 : 1;
    memcpy(expected_pool, misc_objects, sizeof(expected_pool));
    if (!full) {
        expected_pool[63].active = 0x41;
        expected_pool[63].id = 45;
        expected_pool[63].unk2 = variant;
    }
    result = func_8001F150(&engine_obj, variant);
    assert(result == (full ? NULL : &misc_objects[63]));
    c_test_same_words(misc_objects, expected_pool, sizeof(expected_pool));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

static u32 flash_countdown_row(u32 row)
{
    static const u8 timers[] = { 1, 1, 3, 4 };
    struct EngineObj obj;
    u16 white = row == 2;
    memset(&obj, 0, sizeof(obj));
    obj.unk2 = 2;
    obj.unk3 = 5;
    obj.unk4 = timers[row];
    obj.character_state.bytes[2] = row == 1;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 9;
    need_palette_load = 0x10;
    func_8001F634(&obj);
    assert(need_palette_load == 0x11);
    if (row < 2) {
        assert(g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0 && obj.unk3 == 0);
        assert(obj.unk2 == (row ? 4 : 3) && obj.unk4 == (row ? 0x78 : 0x1E) && obj.character_state.bytes[1] == !row);
    } else {
        assert(obj.unk2 == 2 && obj.unk3 == 5 && obj.unk4 == timers[row] - 1);
        assert(g_FilterAmountR == (white ? 0x1F : 0) && g_FilterAmountG == (white ? 0x3E0 : 0) && g_FilterAmountB == (white ? 0x7C00 : 0));
    }
    return obj.unk2;
}
static u32 flash_countdown(u32 row)
{
    static const u8 kept[] = { 0, 1, 3 };
    return flash_countdown_row(kept[row]);
}

static u32 labels_wait(u32 row)
{
    struct EngineObj obj;
    struct MiscObj first, second;
    memset(&obj, 0, sizeof(obj));
    memset(&first, 0, sizeof(first));
    memset(&second, 0, sizeof(second));
    memset(&controller_input, 0, sizeof(controller_input));
    first.unk5 = 2;
    second.unk5 = row ? 1 : 2;
    D_801396C0 = &first;
    D_801396C4 = &second;
    obj.unk2 = 3;
    obj.unk3 = 7;
    func_8001F6E8(&obj);
    assert(obj.unk2 == (row ? 3 : 4) && obj.unk3 == (row ? 7 : 0) && obj.unk4 == (row ? 0 : 6));
    assert(first.state == 0 && second.state == 0 && first.unk5 == 2 && second.unk5 == (row ? 1 : 2));
    return obj.unk2;
}

static u32 slide_flash(u32 row)
{
    struct EngineObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk2 = 3;
    obj.unk4 = 3;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 9;
    need_palette_load = 0x10;
    func_8001F798(&obj);
    assert(obj.unk2 == 3 && obj.unk4 == 2 && need_palette_load == 0x11);
    assert(g_FilterAmountR == 0x1F && g_FilterAmountG == 0x3E0 && g_FilterAmountB == 0x7C00);
    return 1;
}

extern u32* D_80137E08;
static u16 weapon_messages[0x20];
static u32 voice_table[8], message_pages[0x40];
static s32 message_frames[0x200];
static u16 message_palette[0x400];
static struct Func80022730Config message_config;
static u32 weapon_message(u32 row)
{
    struct EngineObj obj;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(&message_config, 0, sizeof(message_config));
    D_801397BC = D_801397C0 = D_801397C4 = D_801397C8 = NULL;
    D_801397CC = D_801397D0 = D_801397D4 = NULL;
    D_801397DC = &message_config;
    D_801406A8 = message_pages;
    TEST_MENU_FRAMES = (u8*)message_frames;
    TEST_PALETTE = (u8*)message_palette;
    for (i = 0; i < 0x14; i++)
        weapon_messages[i] = 0x28;
    weapon_messages[0x14] = 0x800;
    TEST_ARC_48 = (u8*)weapon_messages;
    obj.unk2 = 5;
    obj.character_state.bytes[0] = 3;
    *(s16*)&obj.unk6 = 0x3C;
    obj.unk4 = row == 0 ? 1 : row == 1 ? 0xF0 - 0x3C + 1 : 0x50;
#ifndef MMX4_SATURN
    for (i = 0; i < 8; i++)
        voice_table[i] = 0;
    D_8013E198[5] = 0;
    D_80141F50[5] = (u8*)voice_table;
    D_80141EE8[5] = (u8*)&voice_table[8];
    D_80137E08 = NULL;
#endif
    func_8001F850(&obj);
    assert(obj.unk2 == (row == 0 ? 6 : 5));
    if (row == 0) {
        assert(D_801397BC == &misc_objects[0] && D_801397D8 == 0x80);
#ifndef MMX4_SATURN
        assert(abc_object.unk0 == &weapon_messages[0x14]);
#endif
    } else
        assert(obj.unk4 == (row == 1 ? 0xF0 - 0x3C : 0x4F) && D_801397BC == NULL);
#ifndef MMX4_SATURN
    assert(D_80137E08 == (row == 1 ? &voice_table[3] : NULL));
    D_8013E198[5] = -1;
#endif
    return obj.unk2;
}

static u32 waits(u32 row)
{
    struct EngineObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk2 = 7;
    if (row < 2) {
        abc_object.unkC = row;
        func_8001F93C(&obj);
        assert(obj.unk2 == (row ? 7 : 8) && obj.unk4 == (row ? 0 : 0x3C));
    } else {
#ifdef MMX4_SATURN
        if (row == 2)
            c_test_skip();
#endif
        main_bss_state.transition.active = row == 3;
        func_8001F9DC(&obj);
        assert(obj.unk2 == (row == 3 ? 7 : 8));
        main_bss_state.transition.active = 0;
    }
    return obj.unk2;
}

static u32 last_weapon(u32 row)
{
    struct EngineObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.palette_flags = 0x7F;
    obj.character_state.bytes[0] = 8;
    g_Player.boss_flags = 0x7F;
    func_8001FA24(&obj);
    assert((u8)obj.palette_flags == 0xFF && obj.unk5F == 5 && (u8)g_Player.boss_flags == 0xFF && obj.state == 9);
    return obj.unk5F;
}

#ifndef MMX4_SATURN
void func_8001F198(struct EngineObj*);
void func_80014DC4(void);
void func_80013588(void);
void func_80012E38(void);
static u32 weapon_screen(u32 row)
{
    static struct DrawInfo draw;
    char cue[sizeof(__FILE__) + 32];
    char* suffix;
    u32 i, same = 0;
    strcpy(cue, __FILE__);
    suffix = strstr(cue, "/tests/main/engine.c");
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
    engine_obj.stage = 3;
    engine_obj.substage = 1;
    engine_obj.checkpoint = 2;
    engine_obj.enable_boss = engine_obj.unk1F = 1;
    engine_obj.cur_character = row;
    engine_obj.character_state.bytes[5] = 9;
    need_palette_load = 0x10;
    func_8001F198(&engine_obj);
    assert(engine_obj.stage == 0xF && engine_obj.substage == 0 && engine_obj.checkpoint == 0);
    assert(engine_obj.unk1F == 0 && engine_obj.enable_boss == 0 && engine_obj.unkE == 0);
    assert(engine_obj.unk2 == 1 && engine_obj.unk3 == 0 && engine_obj.cur_character == row);
    for (i = 0; i < 0x10; i++)
        assert(engine_obj.character_state.bytes[i] == (i == 0 ? 3 : 0));
    for (i = 0; i < 0x30; i++)
        same += SP_PALETTE_WORDS[0xAE0 / 4 + i] == SP_ARC_30[2 * 0x30 + i];
    assert(same == (row ? same : 0x30) && (row == 0 || same < 0x30));
    if (row == 0)
        assert(need_palette_load & 1);
    return same;
}
#define WEAPON_SCREEN_CASES 2
#else
#define weapon_screen NULL
#define WEAPON_SCREEN_CASES 0
#endif

const struct CTestGroup c_test_groups[] = {
    { "func_8001F6E8", 0, 0, 1, test_func_8001F6E8 },
#ifndef MMX4_SATURN
    { "func_8001F8FC", 0, 0, 2, test_func_8001F8FC },
#endif
    { "func_8001F798", 0, 0, 2, test_func_8001F798 },
    { "func_8001FA24", 0, 0, 2, test_func_8001FA24 },
    { "scroll_confirmation_and_exact_fixed_point_thresholds", NULL, NULL, 24, scroll },
    { "completion_uses_selected_character_background", NULL, NULL, 2, complete },
#ifndef MMX4_SATURN
    { "both_characters_eight_boss_rewards_normal_screen_setup", NULL, NULL, 16, enter },
#endif
    { "public_label_allocation_API_full_and_last_slot_X_Zero_headers", NULL, NULL, 4, label_capacity },
    { "flash_countdown", NULL, NULL, 3, flash_countdown },
    { "labels_wait", NULL, NULL, 2, labels_wait },
    { "slide_flash", NULL, NULL, 1, slide_flash },
    { "weapon_message", NULL, NULL, 3, weapon_message },
    { "message_and_fade_waits", NULL, NULL, 4, waits },
    { "last_weapon", NULL, NULL, 1, last_weapon },
    { "weapon_screen_setup", NULL, NULL, WEAPON_SCREEN_CASES, weapon_screen },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 2 + 2 + 2 + 24 + 2 + 16 + 4 + 3 + 2 + 1 + 3 + 4 + 1 + WEAPON_SCREEN_CASES
#ifdef MMX4_SATURN
    - 2 - 16
#endif
    ;
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
