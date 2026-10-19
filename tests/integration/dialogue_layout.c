#include "test_runtime.h"
#include "main/14A60.h"
#include "main/128C4.h"
#include "main/195B4.h"
#include "main/13A8C.h"

void func_8002328C(struct AbcObj*);
extern struct DialogueGlyphData D_801396C8;
extern u32 D_800F2F38[2];

enum { WINDOW,
    TEXT,
    ARROW,
    PLAYER_FACE,
    RIVAL_FACE,
    PLAYER_FRAME,
    RIVAL_FRAME };
static struct MiscObj expected_pool[64];
static struct MiscObj* expected_handles[7];
static struct AbcObj expected_dialogue;
static struct DialogueGlyphData expected_glyphs;
static struct EngineObj engine_before;
static struct PlayerObj player_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static struct WeaponObj weapons_before[16];
static u32 frame_headers[64], pages[64];
static union {
    u16 colors[0x400];
    u32 words[0x200];
} palette;
static u16 script[4], script_before[4];
static u8 config_before[2][60];
static u8 portrait_before;
static s16 glyph_count_expected;
static struct Func80022730Config* config_pointer_before;

static void same_bytes(const void* actual, const void* wanted, u32 size)
{
    const u8* a = actual;
    const u8* b = wanted;
    u32 i;
    for (i = 0; i < size; i++)
        assert(a[i] == b[i]);
}

static void prepare(u8 portrait, u32 free_first, u32 free_count)
{
    u32 i;
    memset(&abc_object, 0x25, sizeof(abc_object));
    memset(&D_801396C8, 0x35, sizeof(D_801396C8));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0x45, sizeof(g_Player));
    memset(&main_bss_state, 0x55, sizeof(main_bss_state));
    memset(background_objects, 0x65, sizeof(background_objects));
    memset(weapon_objects, 0x75, sizeof(weapon_objects));
    memset(misc_objects, 0x35, sizeof(misc_objects));
    memset(frame_headers, 0x35, sizeof(frame_headers));
    memset(&palette, 0x22, sizeof(palette));
    memset(script, 0, sizeof(script));
    script[0] = 0x2041;
    for (i = 0; i < 16; i++)
        frame_headers[i] = 0x80 + i * 4;
    for (i = 0; i < COUNT(pages); i++)
        pages[i] = 0x2000 + i * 128;
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = i >= free_first && i < free_first + free_count ? 0 : 1;
    for (i = 0; i < 32; i++)
        D_801397E4[i] = 0x4141;
    TEST_MENU_FRAMES = (u8*)frame_headers;
    TEST_PALETTE = (u8*)palette.colors;
    D_801406A8 = pages;
    D_801397BC = D_801397C0 = D_801397C4 = NULL;
    D_801397C8 = D_801397CC = D_801397D0 = D_801397D4 = NULL;
    D_801397DC = (struct Func80022730Config*)D_800F2DD0[0];
    D_801397D8 = portrait;
    D_801397E0 = 0;
    D_801396C8.count = D_801396C8.active = 0;
    D_80139824 = 7;
    D_80139828 = 1;
    abc_object.unk0 = script;
    abc_object.unk6 = -120;
    abc_object.unk8 = 29;
    abc_object.unkA = 1;
    abc_object.unkC = abc_object.unkF = 1;
    abc_object.unkD = 0;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0;
    need_palette_load = 0x20;
    cur_random = 0x1234;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
}

static void capture(void)
{
    u32 i;
    expected_dialogue = abc_object;
    expected_glyphs = D_801396C8;
    engine_before = engine_obj;
    player_before = g_Player;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before, (const u32*)background_objects, sizeof(backgrounds_before) / 4);
    c_test_copy_words((u32*)weapons_before, (const u32*)weapon_objects, sizeof(weapons_before) / 4);
    c_test_copy_words((u32*)expected_pool, (const u32*)misc_objects, sizeof(expected_pool) / 4);
    memset(expected_handles, 0, sizeof(expected_handles));
    expected_handles[WINDOW] = D_801397BC;
    expected_handles[TEXT] = D_801397C0;
    expected_handles[ARROW] = D_801397C4;
    expected_handles[PLAYER_FACE] = D_801397C8;
    expected_handles[RIVAL_FACE] = D_801397CC;
    expected_handles[PLAYER_FRAME] = D_801397D0;
    expected_handles[RIVAL_FRAME] = D_801397D4;
    portrait_before = D_801397D8;
    config_pointer_before = D_801397DC;
    glyph_count_expected = D_801397E0;
    for (i = 0; i < 4; i++)
        script_before[i] = script[i];
    for (i = 0; i < 60; i++) {
        config_before[0][i] = D_800F2DD0[0][i];
        config_before[1][i] = D_800F2DD0[1][i];
    }
}

static void check(u16 input)
{
    struct MiscObj* handles[] = { D_801397BC, D_801397C0, D_801397C4,
        D_801397C8, D_801397CC, D_801397D0, D_801397D4 };
    u32 i;
    c_test_same_words(&abc_object, &expected_dialogue, sizeof(expected_dialogue));
    same_bytes(&D_801396C8, &expected_glyphs, sizeof(expected_glyphs));
    assert(D_801397E0 == glyph_count_expected);
    assert(D_801397D8 == portrait_before && D_801397DC == config_pointer_before);
    for (i = 0; i < COUNT(handles); i++)
        assert(handles[i] == expected_handles[i]);
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_before));
    c_test_same_words(&g_Player, &player_before, sizeof(player_before));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_before));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((const u32*)weapon_objects,
               (const u32*)weapons_before, sizeof(weapons_before) / 4)
        == 0);
    assert(c_test_word_difference((const u32*)misc_objects,
               (const u32*)expected_pool, sizeof(expected_pool) / 4)
        == 0);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678
        && controller_input.pressed == input);
    assert(need_palette_load == 0x20 && cur_random == 0x1234);
    assert(D_80139824 == 7 && D_80139828 == 1);
    assert(TEST_MENU_FRAMES == (u8*)frame_headers && D_801406A8 == pages);
    assert(TEST_PALETTE == (u8*)palette.colors);
    for (i = 0; i < 64; i++) {
        assert(frame_headers[i] == (i < 16 ? 0x80 + i * 4 : 0x35353535));
        assert(pages[i] == 0x2000 + i * 128);
    }
    for (i = 0; i < COUNT(palette.words); i++)
        assert(palette.words[i] == 0x22222222);
    for (i = 0; i < 32; i++)
        assert(D_801397E4[i] == 0x4141);
    for (i = 0; i < 4; i++)
        assert(script[i] == script_before[i]);
    same_bytes(D_800F2DD0[0], config_before[0], 60);
    same_bytes(D_800F2DD0[1], config_before[1], 60);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
}

static s32 allocate_expected(void)
{
    u32 i;
    for (i = 0; i < COUNT(expected_pool); i++)
        if (!expected_pool[i].active)
            return i;
    return -1;
}

static void choose_resources(u32 character, u32 single, u8 rival, u8 indices[3])
{
    u32 stage, substage, i;
    for (stage = 0; stage < 13; stage++) {
        for (substage = 0; substage < 2; substage++) {
            const u8* ids = s_StageMainIds[stage][substage];
            u32 found = single ? 4 : 0;
            if (ids == NULL)
                continue;
            for (i = 0; i < 16 && ids[i] != 0xFF; i++) {
                if (ids[i] == 0x91 + character) {
                    indices[0] = i;
                    found |= 1;
                }
                if (ids[i] == 0x97) {
                    indices[1] = i;
                    found |= 2;
                }
                if (!single && ids[i] == rival) {
                    indices[2] = i;
                    found |= 4;
                }
            }
            if (found == 7) {
                engine_obj.stage = stage;
                engine_obj.substage = substage;
                return;
            }
        }
    }
    assert(0);
}

static void expect_portrait(u32 slot, u32 part, const struct Func80022730Config* config,
    const u8 indices[3])
{
    struct MiscObj* obj = &expected_pool[slot];
    u32 character = engine_obj.cur_character, palette_column, animation = 0;
    u32 frame = part == PLAYER_FACE ? indices[0] : part == RIVAL_FACE ? indices[2]
                                                                      : indices[1];
    u32 texture = part == PLAYER_FACE ? config->unk0 + character + 2
        : part == RIVAL_FACE          ? config->unk1
                                      : config->unk0;
    obj->active = 0x41;
    obj->id = 0x16;
    obj->unk2 = part == PLAYER_FACE ? 5 : part == RIVAL_FACE ? 3
                                                             : 4;
    obj->bg_offset = -1;
    obj->unk15 = part == RIVAL_FRAME ? 0x40 : 0;
    obj->x_pos.i.hi = part == RIVAL_FACE || part == RIVAL_FRAME ? 240 : config->unk5 ? 160
                                                                                     : 80;
    obj->y_pos.i.hi = 72;
    obj->unk16 = part == PLAYER_FRAME || part == RIVAL_FRAME ? 17 : 16;
    obj->unk40 = (pages[texture] >> 7) + (config->unk4 ? 0xB0 : 0);
    palette_column = config->unk3 * 4 + (part == PLAYER_FACE ? character + 26 : part == RIVAL_FACE ? 25
                                                                                                   : 24);
    obj->unk42 = (palette_column % 16) | ((480 + palette_column / 16) << 6);
    obj->unk3C = (u8*)frame_headers + frame_headers[frame];
    obj->state = 0;
    obj->animation_table = (u32**)D_800F2EE8[part == PLAYER_FACE ? character
            : part == RIVAL_FACE                                 ? config->unk2 - 0x91
                                                                 : 6];
    if (part == PLAYER_FACE || part == RIVAL_FACE) {
        obj->ext.pointer.unk50 = D_800F2DD8[character][portrait_before];
        obj->ext.title_logo.palette_shift_value = 0;
        if (part == PLAYER_FACE) {
            animation = engine_obj.armor_parts * 2;
            obj->ext.title_logo.palette_shift_speed = animation;
        }
    }
    obj->unk17 = animation;
    obj->previous_animation_index = 0xFF;
    obj->animation_cursor = obj->animation_table[animation];
    obj->animation_step.packed = *obj->animation_cursor;
    expected_handles[part] = &misc_objects[slot];
}

static u32 test_portrait_allocation(u32 row)
{
    static const u8 counts[] = { 0, 1, 2, 3, 4, 5, 4, 64 }, plans[] = { 0, 4, 1, 2 };
    static const u8 parts[] = { PLAYER_FACE, PLAYER_FRAME, RIVAL_FACE, RIVAL_FRAME };
    u32 plan = plans[row / 31], variant = row % 31, character = variant >= 40;
    u32 portrait = character ? variant - 40 : variant % 10, part;
    u8 indices[3] = { 0, 0, 0 };
    const struct Func80022730Config* config;
    prepare(portrait, plan == 6 ? 60 : 0, counts[plan]);
    engine_obj.cur_character = character;
    engine_obj.armor_parts = character ? 0 : variant / 10;
    config = (const struct Func80022730Config*)(D_800F2DD0[character] + portrait * 6);
    D_801397DC = (struct Func80022730Config*)config;
    choose_resources(character, config->unk5, config->unk2, indices);
    capture();
    expected_dialogue.unkA = 0;
    expected_dialogue.unkC = expected_dialogue.unkD = 1;
    for (part = 0; part < (config->unk5 ? 2 : 4); part++) {
        s32 slot = allocate_expected();
        if (slot >= 0)
            expect_portrait(slot, parts[part], config, indices);
    }
    func_80022730(&abc_object);
    check(0);
    return 1;
}

static void expect_text(u16 word)
{
    s32 slot = allocate_expected();
    expected_glyphs.active = 1;
    if (slot >= 0) {
        struct MiscObj* obj = &expected_pool[slot];
        obj->active = 1;
        obj->id = 0x16;
        obj->unk16 = 16;
        obj->unk40 = 0x1F00;
        obj->unk2 = 0;
        obj->unk3C = &D_801396C8.count;
        obj->unk42 = engine_obj.stage == 13 ? 0x78CE : 0x7845;
        obj->bg_offset = -1;
        obj->x_pos.val = 160 * 65536;
        obj->y_pos.val = ((word & 0x800)                   ? portrait_before == 0xFF ? 120 : 112
                                 : portrait_before == 0x80 ? 56
                                                           : 0)
            * 65536;
        obj->animation_step.fields.frame_index = 0;
        obj->unk15 = 0;
        expected_handles[TEXT] = &misc_objects[slot];
    }
}

static void expect_arrow(u16 word)
{
    s32 slot = allocate_expected();
    if (slot >= 0) {
        struct MiscObj* obj = &expected_pool[slot];
        obj->active = 1;
        obj->id = 0x16;
        obj->unk16 = 16;
        obj->unk40 = 0x1FFF;
        obj->unk2 = 1;
        obj->unk3C = D_800F2F38;
        obj->unk42 = engine_obj.stage == 13 ? 0x78CE : 0x7845;
        obj->bg_offset = -1;
        obj->x_pos.i.hi = 152;
        obj->y_pos.i.hi = word & 0x800 ? portrait_before == 0xFF ? 197 : 189
            : portrait_before == 0x80  ? 133
                                       : 77;
        obj->animation_step.fields.frame_index = 0;
        obj->unk15 = 0;
        obj->ext.title_logo.palette_shift_speed = 0;
        obj->ext.ready_text.stay_up_timer = 32;
        expected_handles[ARROW] = &misc_objects[slot];
    }
}

static void expect_decode(u16 input)
{
    u32 index = 0;
    u16 word;
    do {
        assert(index < COUNT(script));
        word = script[index++];
        if ((word & 0x1FF) != 0x1FF) {
            struct DialogueGlyph* glyph;
            if (glyph_count_expected == 0 && expected_handles[TEXT] == NULL)
                expect_text(word);
            assert(glyph_count_expected < 60);
            glyph = &expected_glyphs.glyphs[glyph_count_expected++];
            glyph->frame = 0;
            glyph->character = word;
            glyph->x = expected_dialogue.unk6;
            glyph->y = expected_dialogue.unk8;
            expected_glyphs.count = glyph_count_expected;
        }
        if (word & 0x4000) {
            expected_dialogue.unk6 = -120;
            expected_dialogue.unk8 += 18;
        } else {
            expected_dialogue.unk6 += 12;
        }
        if (expected_dialogue.unkF == 0)
            word &= ~0x1000;
    } while (!(word & 0xB000));
    expected_dialogue.unk0 = script + index;
    expected_dialogue.unk4 = word;
    if ((word & 0xB000) == 0x1000) {
        assert(expected_dialogue.unkF > 0);
        if (input & 0xFF)
            expected_dialogue.unkF--;
        expected_dialogue.unkA = 4;
        expected_dialogue.unkD = 2;
    } else {
        expected_dialogue.unkF = 2;
        if (word & 0x2000)
            expect_arrow(word);
        expected_dialogue.unkC = 0xFF;
        expected_dialogue.unkD = 3;
    }
}

static const u16 layout_scripts[][4] = {
    { 0x2041 },
    { 0x2841 },
    { 0x8041 },
    { 0x8841 },
    { 0x4041, 0x2042 },
    { 0x01FF, 0x2041 },
    { 0x4841, 0x2842 },
    { 0x21FF },
    { 0x89FF },
};
static const u8 portraits[] = { 0, 0x80, 0xFF };

static void decoder_prepare(u32 portrait, u32 stage, u32 plan)
{
    static const u8 counts[] = { 0, 1, 2, 64, 2 };
    prepare(portraits[portrait], plan == 4 ? 62 : 0, counts[plan]);
    engine_obj.stage = stage ? 13 : 0;
    abc_object.unkD = 1;
}

static u32 test_decoder_layout(u32 row)
{
    u32 message = row % COUNT(layout_scripts), portrait = row / COUNT(layout_scripts) % 3;
    u32 stage = row / (3 * COUNT(layout_scripts)) % 2, plan = row / (6 * COUNT(layout_scripts)), i;
    decoder_prepare(portrait, stage, plan);
    for (i = 0; i < 4; i++)
        script[i] = layout_scripts[message][i];
    capture();
    expect_decode(0);
    func_8002328C(&abc_object);
    check(0);
    return 1;
}

static u32 test_decoder_delay(u32 row)
{
    static const u16 inputs[] = { 0, 0x40, 0x800 };
    static const u8 plans[] = { 0, 1, 4 };
    u32 skip = row % 3, input = row / 3 % 3, portrait = row / 9 % 3;
    u32 plan = row / 27 % 3, stage = row / 81;
    decoder_prepare(portrait, stage, plans[plan]);
    abc_object.unkF = skip;
    controller_input.pressed = inputs[input];
    script[0] = 0x1041;
    script[1] = 0x2042;
    capture();
    expect_decode(inputs[input]);
    func_80022730(&abc_object);
    check(inputs[input]);
    return 1;
}

static u32 test_decoder_continuation(u32 row)
{
    u32 message = row % 2, stage = row / 2 % 2, portrait = row / 4 % 3;
    u32 existing = row / 12 % 2, count = row / 24 ? 58 : 1;
    decoder_prepare(portrait, stage, 1);
    D_801397E0 = D_801396C8.count = count;
    D_801396C8.active = 1;
    if (existing) {
        D_801397C0 = &misc_objects[5];
        misc_objects[5].id = 0x16;
        misc_objects[5].unk2 = 0;
    }
    script[0] = message ? 0x01FF : 0x0041;
    script[1] = 0x2042;
    capture();
    expect_decode(0);
    func_8002328C(&abc_object);
    check(0);
    return 1;
}

static u32 test_close_handle(u32 row)
{
    static const u16 inputs[] = { 0, 0x40, 0x800 };
    u32 handle = row % 3, active = row / 3 % 2, input = row / 6;
    prepare(0, 0, 0);
    abc_object.unkD = 3;
    abc_object.unk4 = 0x81FF;
    abc_object.unkC = 0xFF;
    abc_object.unkF = 2;
    if (handle) {
        D_801397C4 = &misc_objects[3];
        misc_objects[3].id = handle == 1 ? 0x16 : 0x17;
        misc_objects[3].active = misc_objects[3].on_screen = active;
    }
    controller_input.pressed = inputs[input];
    capture();
    if (inputs[input] & 0xFF) {
        if (handle == 1)
            expected_pool[3].active = expected_pool[3].on_screen = 0;
        expected_dialogue.unkA = 39;
        expected_dialogue.unkD = 4;
        expected_dialogue.unkC = 0x80;
    }
    func_80022730(&abc_object);
    check(inputs[input]);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "dialogue_portrait_allocation", 0, 0, 124, test_portrait_allocation },
    { "dialogue_decoder_layout", 0, 0, 129, test_decoder_layout },
    { "dialogue_decoder_delay", 0, 0, 6, test_decoder_delay },
    { "dialogue_decoder_continuation", 0, 0, 2, test_decoder_continuation },
    { "dialogue_close_handle", 0, 0, 9, test_close_handle },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 124 + 129 + 6 + 2 + 9;
