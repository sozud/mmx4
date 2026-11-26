#include "test_runtime.h"
#include "main/unks/unk_01_menu_label.h"
#include "archive_memory.h"

#undef main_bss_state

void menu_label_init(struct UnkObj*);

#ifdef MMX4_SATURN
#define LABEL_TEXTURE 0xC600
#define LABEL_FRAMES ((u8*)0x002C6400)
#define LABEL_NORMAL 0
#define LABEL_SELECTED 2
#define LABEL_LOCKED 4
#else
#define LABEL_TEXTURE 0x1F00
#define LABEL_FRAMES ((u8*)WINDOW_ARCHIVE_DATA + *(s32*)WINDOW_ARCHIVE_DATA)
#define LABEL_NORMAL 0x7800
#define LABEL_SELECTED 0x7803
#define LABEL_LOCKED 0x7804
#endif

static const s16 positions[] = { 16, 17, 120 };
static const u8 restricted[] = { 0, 1, 1, 0 };
static u32 highlight(u32 row)
{
    struct UnkObj obj, expected;
    struct EngineObj engine_before;
    struct MainBssState main_before;
    struct PlayerObj player_before = g_Player;
    u32 label = row % 4, y = row / 4 % 3, selected = row / 12 % 2, mode = row / 24 % 2, character = row / 48;
    engine_obj.cur_character = character;
    engine_before = engine_obj;
    main_bss_state.character_mode = mode;
    main_bss_state.transition.selection = selected ? label + 4 : 0;
    main_before = main_bss_state;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 1;
    obj.state = 1;
    obj.on_screen = 7;
    obj.unk7 = label + 4;
    obj.bg_offset = -1;
    obj.unk42 = 0x4567;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = positions[y] * 65536 + 0x5678;
    expected = obj;
    expected.on_screen = 1;
    if (y)
        expected.unk42 = selected ? LABEL_SELECTED : LABEL_NORMAL;
    if (character && !mode && restricted[label])
        expected.unk42 = LABEL_LOCKED;
    menu_label_highlight(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

static u32 init(u32 row)
{
    struct UnkObj obj, expected;
#ifndef MMX4_SATURN
    s32 frames_before = *(s32*)WINDOW_ARCHIVE_DATA;
    *(s32*)WINDOW_ARCHIVE_DATA = 0x40;
#endif
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 1;
    obj.unk2 = 5;
    obj.unk15 = 1;
    obj.unk16 = 3;
    obj.x_pos.val = 0x20 * 65536 + 0x1234;
    obj.y_pos.val = positions[2] * 65536;
    expected = obj;
    expected.state = 1;
    expected.on_screen = 1;
    expected.unk40 = LABEL_TEXTURE;
    expected.unk3C = LABEL_FRAMES;
    expected.bg_offset = -1;
    expected.unk15 = 0;
    expected.unk16 = 0;
    expected.unk42 = LABEL_NORMAL;
    expected.x_pos.i.hi = 0xA0;
    expected.animation_step.fields.frame_index = 5;
    menu_label_init(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
#ifndef MMX4_SATURN
    *(s32*)WINDOW_ARCHIVE_DATA = frames_before;
#endif
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "selection_special_row_and_character_restrictions", NULL, NULL, 96, highlight },
    { "init_row", NULL, NULL, 1, init },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 96 + 1;
