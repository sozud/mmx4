#include "test_runtime.h"
#include "main/2824.h"

void menu_text_update(struct UnkObj*);
extern u16 menu_button_bits_a[8], menu_button_bits_b[8];
extern u8 D_800F4508[32], D_800F4528[28], D_800F4544[28];
extern u8 D_800F4568[20], D_800F457C[20];
extern u32* option_toggle_animations[1];
extern union AnimationStep* menu_text_animations[1];

static struct UnkObj obj, expected;
static struct PlayerObj player_before;
static struct EngineObj engine_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static u16 bindings_expected[16];
static union {
    u32 words[0xC00];
    u8 bytes[0x3000];
} window_expected;
static const u16 binding_defaults[16] = {
    0x2000, 0x8000, 0x1000, 0x4000, 0x80, 0x10, 2, 0x40,
    0x20, 8, 4, 0, 0, 0, 0, 0
};
static const u16 source_buttons[8] = { 0x10, 0x80, 0x100, 0x40, 0x20, 0x200, 0x400, 0 };
static const u16 physical_buttons[8] = { 0x80, 0x10, 0x40, 0x20, 4, 1, 8, 2 };
static const u8 binding_slots[7] = { 4, 7, 8, 6, 5, 9, 10 };
static const u32 cursor_words[36] = {
    0x3101000F, 0x3201000D, 0x3301000A, 0x31010008, 0x32010007, 0x33010006, 0x31010006, 0x32010005,
    0x33010005, 0x31010004, 0x32010005, 0x33010005, 0x31010006, 0x32010006, 0x33010007, 0x31010008,
    0x3201000A, 0x3301000D, 0x3101000F, 0x3301000D, 0x3201000A, 0x31010008, 0x33010007, 0x32010006,
    0x31010006, 0x33010005, 0x32010005, 0x31010004, 0x33010005, 0x32010005, 0x31010006, 0x33010006,
    0x32010007, 0x31010008, 0x3301000A, 0x32DD000D
};
static const struct {
    s8 label;
    u8 y, category;
} label_rows[41] = {
    { 0x5E, 0x10, 0x00 },
    { 0x5F, 0x28, 0x00 },
    { 0x60, 0x38, 0x00 },
    { 0x61, 0x48, 0x01 },
    { 0x62, 0x58, 0x02 },
    { 0x63, 0x68, 0x03 },
    { 0x64, 0x78, 0x04 },
    { 0x65, 0x88, 0x04 },
    { 0x66, 0x98, 0x05 },
    { 0x67, 0xA8, 0x06 },
    { 0x70, 0xB8, 0x07 },
    { 0x5F, 0x30, 0x00 },
    { 0x61, 0x40, 0x01 },
    { 0x62, 0x50, 0x02 },
    { 0x63, 0x60, 0x03 },
    { 0x64, 0x70, 0x04 },
    { 0x66, 0x80, 0x05 },
    { 0x67, 0x90, 0x06 },
    { 0x70, 0xB0, 0x07 },
    { 0x60, 0x30, 0x00 },
    { 0x61, 0x40, 0x01 },
    { 0x62, 0x50, 0x02 },
    { 0x63, 0x60, 0x03 },
    { 0x65, 0x70, 0x04 },
    { 0x66, 0x80, 0x05 },
    { 0x67, 0x90, 0x06 },
    { 0x70, 0xB0, 0x07 },
    { 0x00, 0x30, 0x00 },
    { 0x01, 0x48, 0x00 },
    { 0x02, 0x58, 0x00 },
    { 0x03, 0x68, 0x00 },
    { 0x04, 0x80, 0x00 },
    { 0x05, 0x98, 0x00 },
    { 0x06, 0xA8, 0x00 },
    { 0x00, 0x30, 0x00 },
    { 0x01, 0x40, 0x00 },
    { 0x02, 0x50, 0x00 },
    { 0x03, 0x60, 0x00 },
    { 0x04, 0x70, 0x00 },
    { 0x05, 0x80, 0x00 },
    { 0x06, 0x90, 0x00 },
};
static const u8 expected_D_800F4508[] = { 0x5F, 0x28, 0x00, 0x60, 0x38, 0x00, 0x61, 0x48, 0x01, 0x62, 0x58, 0x02, 0x63, 0x68, 0x03, 0x64, 0x78, 0x04, 0x65, 0x88, 0x04, 0x66, 0x98, 0x05, 0x67, 0xA8, 0x06, 0x70, 0xB8, 0x07, 0xFF, 0x00 };
static const u8 expected_D_800F4528[] = { 0x5F, 0x30, 0x00, 0x61, 0x40, 0x01, 0x62, 0x50, 0x02, 0x63, 0x60, 0x03, 0x64, 0x70, 0x04, 0x66, 0x80, 0x05, 0x67, 0x90, 0x06, 0x70, 0xB0, 0x07, 0xFF, 0x00, 0x00, 0x00 };
static const u8 expected_D_800F4544[] = { 0x60, 0x30, 0x00, 0x61, 0x40, 0x01, 0x62, 0x50, 0x02, 0x63, 0x60, 0x03, 0x65, 0x70, 0x04, 0x66, 0x80, 0x05, 0x67, 0x90, 0x06, 0x70, 0xB0, 0x07, 0xFF, 0x00, 0x00, 0x00 };
static const u8 expected_D_800F4568[] = { 0x30, 0x00, 0x48, 0x01, 0x58, 0x02, 0x68, 0x03, 0x80, 0x04, 0x98, 0x05, 0xA8, 0x06, 0xB8, 0x07, 0xFF, 0x00, 0x00, 0x00 };
static const u8 expected_D_800F457C[] = { 0x30, 0x00, 0x40, 0x01, 0x50, 0x02, 0x60, 0x03, 0x70, 0x04, 0x80, 0x05, 0x90, 0x06, 0xB0, 0x07, 0xFF, 0x00, 0x00, 0x00 };

static void prepare(u32 fraction, u32 archive)
{
    u32 i;
    c_test_zero_words((u32*)&obj, sizeof(obj) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)&main_bss_state, sizeof(main_bss_state) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    for (i = 0; i < COUNT(window_expected.words); i += 4) {
        window_expected.words[i] = 0xA55A0000u ^ i;
        window_expected.words[i + 1] = 0x5AA50000u ^ i;
        window_expected.words[i + 2] = ~window_expected.words[i];
        window_expected.words[i + 3] = ~window_expected.words[i + 1];
    }
    window_expected.words[0] = archive ? 0x80 : 0x40;
    window_expected.words[1] = archive ? 0x180 : 0xA0;
    window_expected.words[2] = archive ? 0x280 : 0x140;
    c_test_copy_words((u32*)WINDOW_ARCHIVE_DATA, window_expected.words, COUNT(window_expected.words));
    for (i = 0; i < 16; i++)
        D_800EE430[i] = binding_defaults[i];
    obj.active = 1;
    obj.id = 0;
    obj.on_screen = 1;
    obj.bg_offset = 2;
    obj.x_pos.val = 96 * 65536 + (fraction ? 0xFEDC : 0);
    obj.y_pos.val = 80 * 65536 + (fraction ? 0xBA98 : 0);
    obj.unk15 = 0x40;
    obj.unk16 = 9;
    obj.unk40 = 0x1234;
    obj.unk42 = 0x5678;
    obj.animation_step.packed = 0x55123456;
    obj.previous_animation_index = 0x35;
    obj.animation_table = (u32**)menu_text_animations;
    obj.link.data = D_800F457C;
    obj.ext.unk_0.selection_index = 0;
    g_Player.input.history = 0x12345678;
    g_Player.hp = 24;
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    cur_random = 0x1234;
    need_palette_load = 0x20;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
}

static void capture(void)
{
    u32 i;
    expected = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before, (const u32*)background_objects, sizeof(backgrounds_before) / 4);
    for (i = 0; i < 16; i++)
        bindings_expected[i] = D_800EE430[i];
}

static void same_bytes(const u8* actual, const u8* wanted, u32 count)
{
    u32 i;
    for (i = 0; i < count; i++)
        assert(actual[i] == wanted[i]);
}

static void check(void)
{
    u32 i;
    c_test_same_words(&obj, &expected, sizeof(expected));
    c_test_same_words(&g_Player, &player_before, sizeof(player_before));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_before));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_before));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(c_test_word_difference((const u32*)WINDOW_ARCHIVE_DATA, window_expected.words, COUNT(window_expected.words)) == 0);
    for (i = 0; i < 16; i++)
        assert(D_800EE430[i] == bindings_expected[i]);
    for (i = 0; i < 8; i++) {
        assert(menu_button_bits_a[i] == source_buttons[i]);
        assert(menu_button_bits_b[i] == physical_buttons[i]);
    }
    for (i = 0; i < 36; i++)
        assert(option_toggle_animations[0][i] == cursor_words[i]);
    same_bytes(D_800F4508, expected_D_800F4508, sizeof(expected_D_800F4508));
    same_bytes(D_800F4528, expected_D_800F4528, sizeof(expected_D_800F4528));
    same_bytes(D_800F4544, expected_D_800F4544, sizeof(expected_D_800F4544));
    same_bytes(D_800F4568, expected_D_800F4568, sizeof(expected_D_800F4568));
    same_bytes(D_800F457C, expected_D_800F457C, sizeof(expected_D_800F457C));
    assert(cur_random == 0x1234 && need_palette_load == 0x20);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
}

static void expect_visibility(void)
{
    s32 x = expected.x_pos.i.hi, y = expected.y_pos.i.hi;
    expected.on_screen = x >= -32 && x < 352 && y >= -32 && y < 272;
}

static void expect_label_init(void)
{
    expected.unk40 = 0x1F00;
    expected.bg_offset = -1;
    expected.unk15 = 0;
    expected.unk3C = WINDOW_ARCHIVE_DATA + window_expected.words[0];
    expected.unk42 = expected.y_pos.i.hi == 16 ? 0x7802 : 0x7800;
    expected.x_pos.i.hi = 160;
    expected.unk16 = 0;
    expected.animation_step.fields.frame_index = expected.unk2;
    expected.state = expected.unk2 < 9 ? 2 : 1;
    expect_visibility();
}

static u32 test_labels(u32 row)
{
    u32 index = row % 41, fraction = (row / 41) % 2, archive = row / 82;
    prepare(fraction, archive);
    obj.unk2 = label_rows[index].label;
    obj.y_pos.i.hi = label_rows[index].y;
    obj.unk7 = label_rows[index].category;
    capture();
    expect_label_init();
    menu_text_update(&obj);
    check();
    return 1;
}

static void expect_cursor_init(void)
{
    expected.unk40 = 0x1E00;
    expected.animation_table = option_toggle_animations;
    expected.unk3C = WINDOW_ARCHIVE_DATA + window_expected.words[2];
    expected.unk15 = 0;
    expected.bg_offset = -1;
    expected.unk16 = 0;
    expected.state = 3;
    if (expected.unk2 == -1) {
        expected.unk42 = 0x7806;
        expected.y_pos.i.hi = (expected.link.data == D_800F4568 ? expected_D_800F4568 : expected_D_800F457C)[main_bss_state.transition.selection * 2] + 8;
        expected.ext.unk_0.selection_index = main_bss_state.transition.selection;
        expected.unk17 = 0;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (u32*)option_toggle_animations[0];
        expected.animation_step.packed = cursor_words[0];
    } else {
        expected.unk42 = 0x784B;
        expected.x_pos.i.hi = 96;
        expected.y_pos.i.hi = 208;
        expected.animation_step.fields.frame_index = 0x29;
    }
    expect_visibility();
}

static u32 test_cursor_init(u32 row)
{
    u32 selection = row % 8, table = (row / 8) % 2, type = (row / 16) % 2;
    prepare((row / 32) % 2, row / 64);
    obj.unk2 = type ? -2 : -1;
    obj.link.data = table ? D_800F4568 : D_800F457C;
    main_bss_state.transition.selection = selection;
    capture();
    expect_cursor_init();
    menu_text_update(&obj);
    check();
    return 1;
}

static u32 test_highlight(u32 row)
{
    u32 index = row % 27, second = row / 27, equal = second ? 0 : index % 2;
    prepare(row % 2, 0);
    obj.unk2 = label_rows[index].label;
    obj.y_pos.i.hi = label_rows[index].y;
    obj.unk7 = label_rows[index].category;
    menu_text_update(&obj);
    main_bss_state.transition.selection = (label_rows[index].category + (equal ? 0 : 1)) % 8;
    main_bss_state.character_mode = second ? 0 : index % 2;
    engine_obj.cur_character = second;
    capture();
    if (expected.y_pos.i.hi != 16)
        expected.unk42 = equal ? 0x7803 : 0x7800;
    if (!main_bss_state.character_mode && engine_obj.cur_character == 1 && expected.unk7 >= 5 && expected.unk7 < 7)
        expected.unk42 = 0x7804;
    expect_visibility();
    menu_text_update(&obj);
    check();
    return 1;
}

static u32 test_binding(u32 row)
{
    u32 label = row % 7, button = row % 9, mode = row / 9;
    u32 character = (label + mode) % 2, edge = row % 3;
    prepare(row % 2, 0);
    obj.unk2 = label;
    obj.y_pos.i.hi = 48 + label * 16;
    menu_text_update(&obj);
    obj.animation_step.fields.frame_index = 0x6F;
    obj.x_pos.i.hi = edge == 0 ? 160 : edge == 1 ? -32
                                                 : -33;
    main_bss_state.character_mode = mode;
    engine_obj.cur_character = character;
    D_800EE430[binding_slots[label]] = button < 8 ? physical_buttons[button] : 0;
    capture();
    if (button < 8)
        expected.animation_step.fields.frame_index = 0x68 + button;
    expected.unk42 = !mode && character && label >= 5 ? 0x7804 : 0x7800;
    expect_visibility();
    menu_text_update(&obj);
    check();
    return 1;
}

static u32 test_cursor_tick(u32 row)
{
    u32 frame = row % 36, selection = (row / 36) % 8;
    u32 changed = (row / 288) % 2, table = row / 576;
    prepare(row % 2, 0);
    obj.unk2 = -1;
    obj.link.data = table ? D_800F4568 : D_800F457C;
    main_bss_state.transition.selection = changed ? (selection + 1) % 8 : selection;
    menu_text_update(&obj);
    main_bss_state.transition.selection = selection;
    obj.animation_cursor = option_toggle_animations[0] + frame;
    obj.animation_step.packed = cursor_words[frame];
    obj.animation_step.fields.duration = 1;
    capture();
    if (changed) {
        expected.y_pos.i.hi = (table ? expected_D_800F4568 : expected_D_800F457C)[selection * 2] + 8;
        expected.ext.unk_0.selection_index = selection;
    }
    expected.animation_cursor = option_toggle_animations[0] + (frame == 35 ? 0 : frame + 1);
    expected.animation_step.packed = cursor_words[frame == 35 ? 0 : frame + 1];
    expect_visibility();
    menu_text_update(&obj);
    check();
    return 1;
}

static u32 test_cursor_delay(u32 row)
{
    u32 selection = row % 8, changed = (row / 8) % 2, table = row / 16;
    prepare(row % 2, 1);
    obj.unk2 = -1;
    obj.link.data = table ? D_800F4568 : D_800F457C;
    main_bss_state.transition.selection = changed ? (selection + 1) % 8 : selection;
    menu_text_update(&obj);
    main_bss_state.transition.selection = selection;
    capture();
    if (changed) {
        expected.y_pos.i.hi = (table ? expected_D_800F4568 : expected_D_800F457C)[selection * 2] + 8;
        expected.ext.unk_0.selection_index = selection;
    }
    expected.animation_step.fields.duration = 14;
    expect_visibility();
    menu_text_update(&obj);
    check();
    return 1;
}

static u32 test_static_cursor(u32 row)
{
    prepare(row % 2, 1);
    obj.unk2 = -2;
    obj.link.data = row / 8 ? D_800F4568 : D_800F457C;
    main_bss_state.transition.selection = row % 8;
    menu_text_update(&obj);
    main_bss_state.transition.selection = (row + 1) % 8;
    capture();
    expect_visibility();
    menu_text_update(&obj);
    check();
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "menu_label_initialization", 0, 0, 41, test_labels },
    { "menu_cursor_initialization", 0, 0, 8, test_cursor_init },
    { "menu_label_highlight", 0, 0, 54, test_highlight },
    { "menu_binding_icons", 0, 0, 18, test_binding },
    { "menu_cursor_animation", 0, 0, 36, test_cursor_tick },
    { "menu_cursor_delay", 0, 0, 16, test_cursor_delay },
    { "menu_static_cursor", 0, 0, 8, test_static_cursor },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 41 + 8 + 54 + 18 + 36 + 16 + 8;
