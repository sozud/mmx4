#include "test_runtime.h"
#include "main/misc/misc_28_select_a_character.h"
#include "main/misc/misc_52_npc_cutscene.h"
#include "main/misc/misc_31_option_toggle.h"
#include "main/55C4.h"
#include "main/menu.h"
#include "main/misc/misc_21_center_sprite.h"
void func_80019BF4(struct EngineObj* arg0);
extern union AnimationStep* npc_cutscene_animations[2];

static struct MiscObj obj, expected;
static struct {
    struct EngineObj engine;
    struct PlayerObj player;
    struct MainBssState main;
    struct ControllerInput input;
    struct AbcObj dialogue;
    struct BackgroundObj backgrounds[3];
    struct MiscObj pool[64];
} before;
static u32 backref[3];
#define COPY(dst, src) c_test_copy_words((u32*)&(dst), (u32*)&(src), sizeof(dst) / 4)
#define SAME(a, b) assert(c_test_word_difference((u32*)&(a), (u32*)&(b), sizeof(a) / 4) == 0)
static void setup(u8 id, u8 subtype)
{
    c_test_zero_words((u32*)&obj, sizeof(obj) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&main_bss_state, sizeof(main_bss_state) / 4);
    memset(&controller_input, 0, sizeof(controller_input));
    c_test_zero_words((u32*)&abc_object, sizeof(abc_object) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    memset(D_80141F50, 0, sizeof(D_80141F50));
    obj.active = 0x41;
    obj.id = id;
    obj.unk2 = subtype;
    obj.state = 1;
    obj.unk5 = subtype;
    obj.on_screen = 7;
    obj.bg_offset = -1;
    obj.x_pos.val = 96 * 65536 + 0x1357;
    obj.y_pos.val = 120 * 65536 + 0x2468;
    obj.unk42 = 0x7800;
    obj.previous_animation_index = 0x25;
    backref[0] = 0x12345678;
    backref[1] = 0x34567812;
    backref[2] = 0x56781234;
}
static void snapshot(void)
{
    COPY(expected, obj);
    COPY(before.engine, engine_obj);
    COPY(before.player, g_Player);
    COPY(before.main, main_bss_state);
    memcpy(&before.input, &controller_input, sizeof(controller_input));
    COPY(before.dialogue, abc_object);
    COPY(before.backgrounds, background_objects);
    COPY(before.pool, misc_objects);
}
static u32 check(void)
{
    SAME(obj, expected);
    SAME(engine_obj, before.engine);
    SAME(g_Player, before.player);
    SAME(main_bss_state, before.main);
    assert(controller_input.held == before.input.held && controller_input.previous == before.input.previous && controller_input.pressed == before.input.pressed);
    SAME(abc_object, before.dialogue);
    SAME(background_objects, before.backgrounds);
    SAME(misc_objects, before.pool);
    assert(backref[0] == 0x12345678 && backref[2] == 0x56781234);
    return 1;
}
static void animation(u32** table, u8 index, u32 first)
{
    obj.animation_table = table;
    obj.animation_cursor = table[index];
    obj.unk17 = index;
    assert(*table[index] == first);
    obj.animation_step.packed = first;
}
static void menu_visible(void)
{
    expected.on_screen = expected.x_pos.i.hi >= -128 && expected.x_pos.i.hi < 448
        && expected.y_pos.i.hi >= -48 && expected.y_pos.i.hi < 288;
}
static u32 portrait(u32 row)
{
    u32 kind = row % 2, selected = row / 2 % 2, departing = row / 4 % 2;
    static const s16 positions[3] = { -129, 96, 448 };
    setup(28, kind);
    obj.unk6 = departing ? 2 : 1;
    obj.x_pos.i.hi = positions[row / 8];
    obj.on_screen = row / 8 == 1;
    obj.x_vel.val = (kind ^ departing) ? -0x100000 : 0x100000;
    engine_obj.character_state.bytes[1] = selected ? 0x80 : 0;
    animation(select_char_menu_animations, kind, kind ? 0x01000001 : 1);
    snapshot();
    if (departing) {
        expected.x_pos.val += expected.x_vel.val;
        if (expected.on_screen == 0)
            expected.state = 2;
    } else if (selected) {
        expected.unk6 = 2;
        expected.x_vel.val = kind ? 0x100000 : -0x100000;
    }
    menu_visible();
    SelectACharacterUpdate(&obj);
    return check();
}
static const u32 selector_words[2][4] = {
    { 0x08010003, 0x09010003, 0x08010003, 0x0AFD0003 },
    { 0x0B010003, 0x0C010003, 0x0B010003, 0x0DFD0003 },
};
static u32 selector(u32 row)
{
    u32 character = row % 2, old = row / 2 % 2, selected = row / 4 % 2;
    u32 step = row / 8 % 2, ticks = row / 16 + 1, t, i;
    setup(28, 6);
    obj.unk6 = step;
    obj.ext.sel_char.cur_character_selected = old;
    animation(select_char_menu_animations, 8 + old, selector_words[old][0]);
    engine_obj.cur_character = character;
    engine_obj.character_state.bytes[1] = selected ? 0x80 : 0;
    for (i = 0; i < 4; i++)
        assert(select_char_menu_animations[8 + old][i] == selector_words[old][i]);
    snapshot();
    for (t = 0; t < ticks && expected.state == 1; t++) {
        if (expected.unk6 == 0) {
            expected.unk17 = 8 + character;
            expected.previous_animation_index = 0xFF;
            expected.animation_cursor = select_char_menu_animations[8 + character];
            expected.animation_step.packed = selector_words[character][0];
            expected.x_pos.i.hi = character ? 224 : 96;
            expected.y_pos.i.hi = 120;
            expected.unk6 = 1;
        } else {
            if (--expected.animation_step.fields.duration == 0) {
                expected.animation_cursor++;
                expected.animation_step.packed = selector_words[expected.unk17 - 8][1];
            }
            if (character != expected.ext.sel_char.cur_character_selected)
                expected.unk6 = 0;
            expected.ext.sel_char.cur_character_selected = character;
        }
        if (selected)
            expected.state = 2;
        menu_visible();
        SelectACharacterUpdate(&obj);
        check();
    }
    return 1;
}
static u32 charged_shot(u32 row)
{
    static const u32 words[3] = { 0x0F010103, 0x10010103, 0x11FE0103 };
    static const s16 start_x[3] = { 137, 147, 148 };
    u32 ticks = row / 3 + 1, t, index = 0, i;
    setup(28, 9);
    obj.x_pos.i.hi = start_x[row % 3];
    animation(select_char_x_animations, 6, words[0]);
    for (i = 0; i < 3; i++)
        assert(select_char_x_animations[6][i] == words[i]);
    snapshot();
    for (t = 0; t < ticks && expected.active; t++) {
        if (expected.state == 2) {
            memset(&expected, 0, 8);
        } else {
            if (t == 0) {
                expected.unk6 = 1;
                expected.x_vel.val = 0xA0000;
                expected.x_pos.i.hi += 3;
                expected.y_pos.i.hi -= 7;
            }
            if (--expected.animation_step.fields.duration == 0) {
                index++;
                expected.animation_cursor = select_char_x_animations[6] + index;
                expected.animation_step.packed = words[index];
            }
            expected.x_pos.val += 0xA0000;
            if (expected.x_pos.i.hi > 160)
                expected.state = 2;
            menu_visible();
        }
        SelectACharacterUpdate(&obj);
        check();
    }
    return 1;
}
static u32 option(u32 row)
{
    u32 setting = row % 2, cached = row / 2 % 2, outside = row / 4 % 2;
    u8 old_setting = D_80171EA9;
    setup(31, 2);
    obj.state = 2;
    obj.x_pos.i.hi = outside ? 352 : 96;
    obj.ext.misc_31.animation = cached;
    obj.animation_step.packed = 0x56000001;
    D_80171EA9 = setting;
    snapshot();
    if (setting != cached) {
        expected.animation_step.fields.frame_index = setting ? 0x56 : 0x57;
        expected.ext.misc_31.animation = setting;
    }
    expected.on_screen = !outside;
    option_toggle_update(&obj);
    check();
    assert(D_80171EA9 == setting);
    D_80171EA9 = old_setting;
    return 1;
}
static u32 npc_finish(u32 row)
{
    static const u8 timers[4] = { 0, 1, 2, 30 };
    u32 kind = row % 3, blink = row / 3 % 2, frame = row / 6 % 4;
    u32 timer = timers[row / 24 % 4], has_backref = row / 30;
    if (timer == 0 && (kind == 1 || !blink))
        timer = 29;
    setup(52, 0);
    obj.state = 2;
    obj.unk5 = kind;
    obj.unk6 = blink ? 0 : 1;
    obj.ext.misc_52.timer = timer;
    obj.backref = has_backref ? (void*)&backref[1] : NULL;
    main_bss_state.frame_counter = frame;
    g_Player.script_state = g_Player.spike_immune = engine_obj.gameplay_locked = 1;
    snapshot();
    if (kind != 1 && blink) {
        expected.ext.misc_52.timer = timer ? timer - 1 : 30;
        if (timer == 0)
            expected.unk6 = 1;
        expected.on_screen = frame & 1;
    } else {
        expected.ext.misc_52.timer = (u8)(timer - 1);
        expected.on_screen = kind == 1;
        if (timer == 1) {
            if (kind == 2) {
                before.player.script_state = before.player.spike_immune = before.engine.gameplay_locked = 0;
                memset(&expected, 0, 8);
            } else
                before.engine.unkF = 0x40;
        }
    }
    npc_cutscene_update(&obj);
    check();
    assert(backref[1] == (kind == 2 && !blink && timer == 1 && has_backref ? 0x34567880u : 0x34567812u));
    return 1;
}
static u32 npc_bob(u32 row)
{
    static const u8 frames[4] = { 9, 10, 11, 20 }, counts[3] = { 1, 2, 7 };
    u32 frame = frames[row % 4], count = counts[row / 4 % 3];
    s32 direction = row / 12 ? -1 : 1;
    setup(52, 0);
    obj.unk5 = 2;
    obj.unk6 = 0;
    obj.ext.misc_52.unk56 = count;
    obj.ext.misc_52.unk57 = direction;
    obj.animation_table = (u32**)npc_cutscene_animations;
    obj.animation_cursor = (u32*)npc_cutscene_animations[0];
    obj.animation_step.packed = 0x0001003A;
    assert(*obj.animation_cursor == 0x0001003A);
    abc_object.unkC = 1;
    main_bss_state.frame_counter = frame;
    snapshot();
    expected.on_screen = 1;
    expected.animation_step.fields.duration = 57;
    if (frame == 10 || frame == 20) {
        expected.y_pos.i.hi += direction;
        expected.ext.misc_52.unk56 = count == 1 ? 7 : count - 1;
        if (count == 1)
            expected.ext.misc_52.unk57 = -direction;
    }
    npc_cutscene_update(&obj);
    return check();
}
static u32 scroll_text(u32 row)
{
    static const u8 kinds[7] = { 2, 3, 4, 5, 12, 13, 14 };
    static const s32 speeds[7] = { -0x18000, 0x18000, 0, 0, 0x40000, -0x40000, 0x40000 };
    static const s16 starts[7] = { -111, 431, 85, 229, 122, 164, 274 };
    u32 kind = row % 7, moving = row / 7 % 2, exiting = row / 14;
    setup(28, kinds[kind]);
    obj.unk6 = moving;
    obj.x_pos.i.hi = starts[kind];
    obj.x_vel.val = moving ? speeds[kind] : 0;
    engine_obj.character_state.bytes[1] = exiting ? 0x80 : 0;
    snapshot();
    if (!moving) {
        expected.x_vel.val = speeds[kind];
        expected.unk6 = 1;
    } else {
        expected.x_pos.val += speeds[kind];
        if (kind == 0)
            expected.x_pos.i.hi = 432;
        if (kind >= 4)
            expected.x_vel.val = 0;
    }
    if (exiting)
        expected.state = 2;
    menu_visible();
    SelectACharacterUpdate(&obj);
    return check();
}
static const u32 burst_words[2][9] = {
    { 0x09010002, 0x0A010002, 0x0B010002, 0x0C010001, 0x0C010101, 0x0D010002, 0x0E000002 },
    { 0x04010001, 0x06010001, 0x08010002, 0x0A010002, 0x0C010002, 0x0E010002, 0x10010003, 0x12010003, 0x14000004 },
};
static u32 burst(u32 row)
{
    static const s8 free_slots[4] = { -1, 0, 31, 63 };
    u32 character = row % 2, layout = row / 2 % 4, ticks = row / 8 + 1, t, frame = 0, i;
    u32** table = character ? select_char_zero_animations : select_char_x_animations;
    setup(28, 10 + character);
    animation(table, 2, burst_words[character][0]);
    for (i = 0; i < (character ? 9 : 7); i++)
        assert(table[2][i] == burst_words[character][i]);
    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 21;
        misc_objects[i].x_pos.val = 0x34561234;
        misc_objects[i].y_pos.val = 0x56782468;
        misc_objects[i].unk7 = 0x35;
        misc_objects[i].state = 2;
    }
    if (free_slots[layout] >= 0)
        misc_objects[free_slots[layout]].active = 0;
    snapshot();
    for (t = 0; t < ticks && expected.active; t++) {
        if (expected.state == 2)
            memset(&expected, 0, 8);
        else {
            if (--expected.animation_step.fields.duration == 0) {
                frame++;
                expected.animation_cursor = table[2] + frame;
                expected.animation_step.packed = burst_words[character][frame];
            }
            if (!character && frame == 4) {
                expected.animation_step.fields.event = 0;
                if (layout != 0) {
                    struct MiscObj* child = &before.pool[free_slots[layout]];
                    child->active = 0x41;
                    child->id = 28;
                    child->unk2 = 9;
                    child->x_pos.i.hi = 96;
                    child->y_pos.i.hi = 120;
                }
            }
            if (frame == (character ? 8 : 6))
                expected.state = 2;
            menu_visible();
        }
        SelectACharacterUpdate(&obj);
    }
    return check();
}
static u32 option_highlight(u32 row)
{
    static const u16 buttons[3] = { 0, PAD_SELECTION_ALT, 0 };
    struct MenuRuntimeData runtime_before;
    struct GameInfo game_before;
    u32 cancel = row % 3, empty = row / 3 % 2, selected = row / 6;
    setup(31, cancel == 2 ? 0xFF : 3);
    obj.unk7 = 3;
    main_bss_state.transition.selection = selected ? 3 : 0;
    controller_input.pressed = buttons[cancel];
    obj.unk42 = 0x7825;
    D_800F1D90.save.character = empty ? 0xFF : CHARACTER_X;
    game_info.unk0 = 9;
    runtime_before = D_800F1D90;
    game_before = game_info;
    snapshot();
    expected.on_screen = 1;
    if (cancel)
        expected.unk2 = -1;
    else
        expected.unk42 = selected ? 0x7803 : empty ? 0x7804
                                                   : 0x7800;
    option_toggle_update(&obj);
    check();
    SAME(D_800F1D90, runtime_before);
    SAME(game_info, game_before);
    return 1;
}
static u32 center_sprite(u32 row)
{
    u32 frames[8] = { 0x12345678, 1, 2, 3, 4, 5, 6, 0x34567812 }, i;
    setup(21, 0);
    obj.state = row;
    obj.unk38 = frames + 7;
    obj.unk15 = 0x40;
    obj.unk16 = 9;
    obj.animation_step.packed = 0x25123456;
    TEST_SPRITE_FRAMES = (u8*)frames;
    snapshot();
    if (row == 0) {
        expected.on_screen = 1;
        expected.bg_offset = -1;
        expected.animation_step.fields.frame_index = 0;
        expected.unk38 = 0;
        expected.unk3C = (u8*)frames;
        expected.animation_table = NULL;
        expected.unk40 = 0x600;
        expected.unk42 = 0x7804;
        expected.unk15 = expected.unk16 = 0;
        expected.x_pos.i.hi = 160;
        expected.y_pos.i.hi = 120;
        expected.state = 1;
    }
    center_sprite_update(&obj);
    check();
    assert(TEST_SPRITE_FRAMES == (u8*)frames);
    for (i = 0; i < 8; i++)
        assert(frames[i] == (i == 0 ? 0x12345678 : i == 7 ? 0x34567812
                                                          : i));
    return 1;
}
static u32 format_navigation(u32 row)
{
    static const u16 buttons[6] = { 0, PADLup, PADLdown, PADLup | PADLdown, PADLleft, PADLright };
    struct MemcardMenuState menu_before;
    setup(21, 0);
    engine_obj.state = 10;
    engine_obj.unk1 = 2;
    engine_obj.unk2 = 1;
    main_bss_state.transition.selection = row % 2;
    controller_input.pressed = buttons[row / 2];
    menu_before = memcard_menu;
    snapshot();
    if (row / 2 >= 1 && row / 2 <= 3)
        before.main.transition.selection ^= 1;
    func_80019BF4(&engine_obj);
    check();
    SAME(memcard_menu, menu_before);
    return 1;
}
const struct CTestGroup c_test_groups[] = {
    { "portrait_selection_departure", NULL, NULL, 14, portrait },
    { "selector_choice_animation", NULL, NULL, 10, selector },
    { "charged_shot_departure", NULL, NULL, 6, charged_shot },
    { "option_setting_refresh", NULL, NULL, 6, option },
    { "npc_blink_fade_leave", NULL, NULL, 36, npc_finish },
    { "npc_talk_bob", NULL, NULL, 8, npc_bob },
    { "scroll_text_selection_exit", NULL, NULL, 21, scroll_text },
    { "burst_allocation_lifecycle", NULL, NULL, 74, burst },
    { "option_cancel_and_empty_highlight", NULL, NULL, 9, option_highlight },
    { "center_sprite_initialization", NULL, NULL, 2, center_sprite },
    { "format_confirmation_navigation", NULL, NULL, 4, format_navigation },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 14 + 10 + 6 + 6 + 36 + 8 + 21 + 74 + 9 + 2 + 4;
