#include "test_runtime.h"

#include "support/state_cases.h"
#include "main/misc/misc_22_dialogue_ui.h"

static struct MiscUnk50_2 ui_speaker[2];
#define sm state_room.misc
#define UI(kind, c, d, body)                                                                                                \
    do {                                                                                                                    \
        u8 dc = abc_object.unkC, dd = abc_object.unkD, de = abc_object.unkE;                                                \
        u16 pressed = controller_input.pressed;                                                                             \
        state_reset(0, 0, 0);                                                                                               \
        memset(ui_speaker, 0, sizeof(ui_speaker));                                                                          \
        ui_speaker[0].x_pos.val = 0x500000;                                                                                 \
        sm.active = 1;                                                                                                      \
        sm.unk2 = kind;                                                                                                     \
        sm.x_pos.i.hi = 0x80;                                                                                               \
        sm.y_pos.i.hi = 0x60;                                                                                               \
        sm.ext.unk.unk50 = ui_speaker;                                                                                      \
        sm.ext.unk.unk56.sht = 2;                                                                                           \
        abc_object.unkC = c;                                                                                                \
        abc_object.unkD = d;                                                                                                \
        abc_object.unkE = 0;                                                                                                \
        controller_input.pressed = 0;                                                                                       \
        body;                                                                                                               \
        dialogue_ui_update(&sm);                                                                                            \
        state_extra = sm.on_screen | sm.ext.unk.unk54 << 8 | sm.ext.unk.unk55 << 16 | (u32)(u8)sm.ext.unk.unk56.byte << 24; \
        abc_object.unkC = dc;                                                                                               \
        abc_object.unkD = dd;                                                                                               \
        abc_object.unkE = de;                                                                                               \
        controller_input.pressed = pressed;                                                                                 \
    } while (0)
static void ui_static(void)
{
    UI(0, 0, 0, );
}
static void ui_prompt(void) { UI(1, 0, 0, ); }
static void ui_prompt_blink(void) { UI(1, 0, 0, sm.ext.unk.unk56.sht = 1); }
static void ui_prompt_hidden(void) { UI(1, 0, 0, sm.ext.unk.unk54 = 1); }
static void ui_prompt_pressed(void) { UI(1, 0, 0, controller_input.pressed = 1); }
static void ui_frame_open(void) { UI(2, 1, 0, ); }
static void ui_frame_typing(void) { UI(2, 1, 2, ); }
static void ui_frame_closed(void) { UI(2, 0, 0, ); }
static void ui_mouth_start(void) { UI(3, 1, 0, ui_speaker[0].unk0 = 1); }
static void ui_mouth_move(void) { UI(3, 1, 0, (ui_speaker[0].unk0 = 1, sm.ext.unk.unk55 = 1)); }
static void ui_mouth_event(void) { UI(3, 1, 0, (ui_speaker[0].unk0 = 1, sm.ext.unk.unk55 = 1, sm.animation_step.fields.event = 1)); }
static void ui_mouth_close(void) { UI(3, 0, 0, sm.ext.unk.unk55 = 1); }
static void ui_mouth_closed(void) { UI(3, 0, 0, (sm.ext.unk.unk55 = 1, sm.animation_step.fields.event = 1)); }
static void ui_mouth_rest(void) { UI(3, 0, 0, ); }
static void ui_portrait(void) { UI(4, 0, 0, ); }
static void ui_eyes_start(void) { UI(5, 1, 0, sm.ext.unk.unk54 = 2); }
static void ui_eyes_move(void) { UI(5, 1, 0, sm.ext.unk.unk55 = 1); }
static void ui_eyes_event(void) { UI(5, 1, 0, (sm.ext.unk.unk55 = 1, sm.animation_step.fields.event = 1)); }
static void ui_eyes_close(void) { UI(5, 0, 0, sm.ext.unk.unk55 = 1); }
static void ui_eyes_closed(void) { UI(5, 0, 0, (sm.ext.unk.unk55 = 1, sm.animation_step.fields.event = 1)); }
static void ui_eyes_rest(void) { UI(5, 0, 0, ); }
static void ui_marker(void) { UI(8, 0, 0, sm.ext.unk.unk56.byte = 2); }
static void ui_marker_follow(void) { UI(8, 0, 0, (sm.ext.unk.unk56.byte = 1, sm.unk6 = 1)); }
static void ui_marker_done(void) { UI(8, 0, 0, sm.unk5 = 1); }
static void ui_other(void) { UI(6, 0, 0, ); }

static void (*const dialogue_ui_states_cases[])(void) = {
    ui_static,
    ui_prompt,
    ui_prompt_blink,
    ui_prompt_hidden,
    ui_prompt_pressed,
    ui_frame_open,
    ui_frame_typing,
    ui_frame_closed,
    ui_mouth_start,
    ui_mouth_move,
    ui_mouth_event,
    ui_mouth_close,
    ui_mouth_closed,
    ui_mouth_rest,
    ui_portrait,
    ui_eyes_start,
    ui_eyes_move,
    ui_eyes_event,
    ui_eyes_close,
    ui_eyes_closed,
    ui_eyes_rest,
    ui_marker,
    ui_marker_follow,
    ui_marker_done,
    ui_other,
};
static const u32 dialogue_ui_states_expected[] = { 0u, 1u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2000001u, 0u, 0u, 0x101u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x1000001u, 0u, 0u, 0x101u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x20000100u, 0u, 0u, 0x101u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x1000100u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2000000u, 0u, 0u, 0x201u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x2000001u, 0u, 0u, 0x201u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2000001u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2000000u, 0u, 0u, 0xFF000301u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2010001u, 0u, 0u, 0x301u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x2010001u, 0u, 0u, 0x301u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x2000001u, 0u, 0u, 0x301u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x2010001u, 0u, 0u, 0xFF000301u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2000001u, 0u, 0u, 0xFF000301u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2000001u, 0u, 0u, 0x401u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x2000001u, 0u, 0u, 0xFF000501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2010201u, 0u, 0u, 0x501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x2010001u, 0u, 0u, 0x501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x2000001u, 0u, 0u, 0x501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x2010001u, 0u, 0u, 0xFF000501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2000001u, 0u, 0u, 0xFF000501u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2000001u, 0u, 0u, 0x801u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x40000u, 0x1000001u, 0u, 0x10100u, 0x801u, 0x500000u, 0u, 0u, 0u, 0u, 0x40000u, 1u, 0u, 0u, 0u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2000000u, 0u, 0u, 0x601u, 0x800000u, 0x600000u, 0u, 0u, 0u, 0x50000u, 0x2000000u, 0u };

static u32 test_dialogue_ui_states(u32 row)
{
    return object_run(dialogue_ui_states_cases[row], row, &dialogue_ui_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "dialogue_ui_states", 0, 0, COUNT(dialogue_ui_states_cases), test_dialogue_ui_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(dialogue_ui_states_cases);
