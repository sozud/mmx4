#include "test_runtime.h"
#include "main/128C4.h"
#include "saturn/game_low.h"
#include "saturn/menu.h"

void func_8002328C(struct AbcObj* arg0);

#define TEXT_OFFSET 0x60

static u16 text[4];

static void reset(u8 character, u8 stage, u8 portrait)
{
    u32 i;
    u16* messages = SATURN_DIALOGUE_MESSAGES;
    c_test_zero_words((u32*)&abc_object, sizeof(abc_object) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)text, sizeof(text) / 4);
    D_801397BC = D_801397C0 = D_801397C4 = D_801397C8 = NULL;
    D_801397CC = D_801397D0 = D_801397D4 = NULL;
    D_801397D8 = portrait;
    D_801397E0 = 0;
    engine_obj.cur_character = character;
    engine_obj.stage = stage;
    engine_obj.enable_boss = 1;
    engine_obj.unk1F = 7;
    saturn_pad_pressed = 0;
    saturn_dialogue_flags = 0;
    need_palette_load = 0;
    for (i = 0; i < 40; i++)
        messages[i] = TEXT_OFFSET;
    saturn_color_ram[SATURN_DIALOGUE_PALETTE] = 0x1357;
    saturn_color_ram[SATURN_DIALOGUE_FORTRESS_PALETTE] = 0x2468;
    D_801397E4[0] = 0;
}

static void start(u16 message, u16 flags)
{
    SATURN_DIALOGUE_MESSAGES[TEXT_OFFSET / 2] = flags | 0x41;
    func_8002217C(message, D_801397D8, 0);
}

static void all_misc_busy(void)
{
    u32 i;
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
}

static void start_x_portrait(void)
{
    reset(0, 2, 0);
    start(5, 0);
}
static void start_x_stop(void)
{
    reset(0, 2, 0xFF);
    start(34, 0x800);
}
static void start_zero_capsule(void)
{
    reset(1, 2, 1);
    start(SATURN_DIALOGUE_CAPSULE_MESSAGE, 0x800);
}
static void start_zero_track(void)
{
    reset(1, 2, 1);
    start(26, 0);
}
static void start_delay(void)
{
    reset(0, 2, 0);
    func_8002217C(5, 0, 1);
}

static void update(u16 a, u16 b, u8 more)
{
    text[0] = a;
    text[1] = b;
    abc_object.unk0 = text;
    abc_object.unk6 = -0x78;
    abc_object.unk8 = 0x1D;
    abc_object.unkF = more;
    func_8002328C(&abc_object);
}

static void update_bottom_speakerless(void)
{
    reset(0, 2, 0xFF);
    update(0x0841, 0x2842, 1);
}
static void update_bottom_portrait(void)
{
    reset(0, 2, 1);
    update(0x0841, 0x2842, 1);
}
static void update_pause_pressed(void)
{
    reset(0, 2, 0);
    saturn_pad_pressed = 0x0400;
    update(0x1041, 0x8042, 1);
}
static void update_banner_arrow(void)
{
    reset(0, 2, 0x80);
    update(0x0041, 0x2042, 1);
}

static void (*const start_cases[])(void) = {
    start_x_portrait,
    start_x_stop,
    start_zero_capsule,
    start_zero_track,
    start_delay,
};
static void (*const update_cases[])(void) = {
    update_bottom_speakerless,
    update_bottom_portrait,
    update_pause_pressed,
    update_banner_arrow,
};

#define WORDS 5
static const u32 start_expected[][WORDS] = {
#include "game_dialogue_start_expected.inc"
};
static const u32 update_expected[][WORDS] = {
#include "game_dialogue_update_expected.inc"
};

static u32 object_word(const struct MiscObj* obj)
{
    return obj == NULL ? 0xFFFFFFFF : (u16)obj->y_pos.i.hi | (u32)(u16)obj->unk42 << 16;
}

static void common_words(u32* observed)
{
    observed[0] = abc_object.unkA | (u32)abc_object.unkC << 16 | (u32)abc_object.unkD << 24;
    observed[1] = abc_object.unkF | (u32)(u8)D_801397E0 << 8 | (u32)(u16)abc_object.unk6 << 16;
    observed[2] = (u16)abc_object.unk8 | (u32)saturn_dialogue_flags << 16 | (u32)(u8)need_palette_load << 24;
}

static u32 start_run(u32 row)
{
    u32 observed[WORDS];
    start_cases[row]();
    common_words(observed);
    observed[3] = object_word(D_801397BC);
    observed[4] = (u16)abc_object.unk10 | (u32)D_801397E4[0] << 16;
    return c_test_observe(0, row, observed, start_expected[row], WORDS);
}

static u32 update_run(u32 row)
{
    u32 observed[WORDS];
    update_cases[row]();
    common_words(observed);
    observed[3] = object_word(D_801397C0);
    observed[4] = object_word(D_801397C4);
    return c_test_observe(1, row, observed, update_expected[row], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_dialogue_start", 0, 0, COUNT(start_cases), start_run },
    { "saturn_dialogue_update", 0, 0, COUNT(update_cases), update_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(start_cases) + COUNT(update_cases);
