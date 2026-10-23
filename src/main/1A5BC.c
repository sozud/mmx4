#include "common.h"
#ifdef MMX4_SATURN
#include "saturn/platform.h"
#include "saturn/game_low.h"
#endif
#include "main/1A5BC.h"
#include "main/14A60.h"
#include "main/2824.h"
#include "main/E47C.h"
#include "main/object_update.h"
#include "main/objects.h"

extern u8 D_800F4508[];
extern u8* D_800F4560[];
extern u8 D_800F4568[];
extern u8 D_800F457C[];

extern u16 D_800F44E8[8];
extern u16 D_800F44F8[8];
extern u8 D_800F4528[];
extern u8 D_800F4544[];

#ifndef MMX4_SATURN
// might also be inlined inside reset_objects
void func_80029DBC(void)
{
    u16 a1;
    u16 var_v1;
    u8* a0;
    u8 fill = 0;

    for (a1 = 0; a1 < COUNT(unk_objects); a1++) {
        a0 = (u8*)&unk_objects[a1];
        var_v1 = sizeof(unk_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }
}

void func_80029E1C(struct GameInfo* arg0)
{
    struct UnkObj* obj;
    u8* var_s1;

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->unk2 = 0x5E;
        obj->id = 0;
        obj->y_pos.i.hi = 0x10;
    }

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->id = 0;
        obj->unk2 = -1;
        if (main_bss_state.character_mode != 0) {
            obj->link.data = D_800F4568;
        } else {
            obj->link.data = D_800F457C;
        }
#ifdef VERSION_JP
        obj->x_pos.i.hi = 0x20;
#else
        obj->x_pos.i.hi = 0x38;
#endif
    }

    if (main_bss_state.character_mode != 0) {
        var_s1 = D_800F4508;
    } else {
        var_s1 = D_800F4560[engine_obj.cur_character];
    }
    while (var_s1[0] != 0xFF) {
        obj = find_free_unk_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0;
            obj->unk2 = var_s1[0];
            obj->y_pos.i.hi = var_s1[1];
            obj->unk7 = var_s1[2];
        }
        if (var_s1[2] == 7) {
            break;
        }
        var_s1 += 3;
    }

    var_s1 = main_bss_state.character_mode != 0 ? D_800F4568 : D_800F457C;
    if (var_s1[1] != 7) {
        do {
            obj = find_free_unk_obj();
            if (obj != NULL) {
                obj->active = 1;
                obj->id = 0;
                obj->unk2 = var_s1[1];
                obj->y_pos.i.hi = var_s1[0];
            }
            var_s1 += 2;
        } while (var_s1[1] != 7);
    }

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->unk2 = -2;
        obj->id = 0;
        obj->x_pos.i.hi = 0x20;
    }

    if (main_bss_state.character_mode == 0) {
        func_8001E980(0);
    }
    main_bss_state.transition.selection = 0;
    func_800129A4(8);
    D_8013B7D0++;
}

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002A098);

void func_8002A394(struct GameInfo* arg0)
{
    if (main_bss_state.transition.active == 0) {
        if (main_bss_state.character_mode != 0) {
            arg0->unk0 = 8;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
        } else {
            (*(s8*)&arg0->unk6)++;
        }
        func_80029DBC();
        if (main_bss_state.character_mode != 0) {
            func_8001E980(1);
        }
        D_8013B7D0 = 0;
    }
}

void func_8002A41C(struct GameInfo* arg0)
{
    func_8002B460(); // no-op
    D_800F4590[D_8013B7D0](arg0);
    update_unk_objects();
    func_80016124();
    func_80025CDC();
}

#else
#define OPTIONS_PAD_CONFIRM 0x0600
#define OPTIONS_PAD_START 0x0800
#define OPTIONS_PAD_UP 0x1000
#define OPTIONS_PAD_DOWN 0x2000
#define OPTIONS_ROW_EXIT 7
#define OPTIONS_ROW_LOCKED_A 5
#define OPTIONS_ROW_LOCKED_B 6
#define OPTIONS_ROW_UNLOCKED 4
#define OPTIONS_BUTTON_COUNT 8
#define OPTIONS_FIRST_ACTION_BIT 4
#define OPTIONS_ACTION_BITS 16
#define OPTIONS_NO_ACTION 0xFF
#define OPTIONS_SOUND_CONFIRM 0x27
#define OPTIONS_SOUND_MOVE 0x0D

u8 saturn_options_rows_mode[] = {
    0x5F,
    0x28,
    0x00,
    0x60,
    0x38,
    0x00,
    0x61,
    0x48,
    0x01,
    0x62,
    0x58,
    0x02,
    0x63,
    0x68,
    0x03,
    0x64,
    0x78,
    0x04,
    0x65,
    0x88,
    0x04,
    0x66,
    0x98,
    0x05,
    0x67,
    0xA8,
    0x06,
    0x70,
    0xB8,
    0x07,
    0xFF,
};
static u8 saturn_options_rows_x[] = {
    0x5F,
    0x30,
    0x00,
    0x61,
    0x40,
    0x01,
    0x62,
    0x50,
    0x02,
    0x63,
    0x60,
    0x03,
    0x64,
    0x70,
    0x04,
    0x66,
    0x80,
    0x05,
    0x67,
    0x90,
    0x06,
    0x70,
    0xB0,
    0x07,
    0xFF,
};
static u8 saturn_options_rows_zero[] = {
    0x60,
    0x30,
    0x00,
    0x61,
    0x40,
    0x01,
    0x62,
    0x50,
    0x02,
    0x63,
    0x60,
    0x03,
    0x65,
    0x70,
    0x04,
    0x66,
    0x80,
    0x05,
    0x67,
    0x90,
    0x06,
    0x70,
    0xB0,
    0x07,
    0xFF,
};
u8* saturn_options_rows[] = { saturn_options_rows_x, saturn_options_rows_zero };
u8 saturn_options_labels_mode[] = {
    0x30,
    0x00,
    0x48,
    0x01,
    0x58,
    0x02,
    0x68,
    0x03,
    0x80,
    0x04,
    0x98,
    0x05,
    0xA8,
    0x06,
    0xB8,
    0x07,
    0xFF,
};
u8 saturn_options_labels[] = {
    0x30,
    0x00,
    0x40,
    0x01,
    0x50,
    0x02,
    0x60,
    0x03,
    0x70,
    0x04,
    0x80,
    0x05,
    0x90,
    0x06,
    0xB0,
    0x07,
    0xFF,
};
const u16 saturn_options_actions[OPTIONS_BUTTON_COUNT] = {
    0x0010,
    0x0080,
    0x0100,
    0x0040,
    0x0020,
    0x0200,
    0x0400,
    0xFFFF,
};
const u16 saturn_options_buttons[OPTIONS_BUTTON_COUNT] = {
    0x0400,
    0x0100,
    0x0200,
    0x0040,
    0x0020,
    0x0010,
    0x0080,
    0x0008,
};
extern u16 saturn_button_masks[];
void saturn_sprite_reset_queues(void);
void saturn_sprite_draw_passes(void);
void saturn_title_upload_window(void);
void saturn_fade_start_in(void);
void saturn_fade_start_out(void);

void func_80029DBC(void)
{
    u16 a1;
    u16 var_v1;
    u8* a0;
    u8 fill = 0;

    for (a1 = 0; a1 < COUNT(unk_objects); a1++) {
        a0 = (u8*)&unk_objects[a1];
        var_v1 = sizeof(unk_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }
}

void func_80029E1C(struct GameInfo* arg0)
{
    struct UnkObj* obj;
    u8* var_s1;

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->id = 0;
        obj->unk2 = 0x5E;
        obj->y_pos.i.hi = 0x10;
    }
    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->id = 0;
        obj->unk2 = -1;
        obj->link.data = main_bss_state.character_mode != 0 ? saturn_options_labels_mode : saturn_options_labels;
        obj->x_pos.i.hi = 0x38;
    }
    var_s1 = main_bss_state.character_mode != 0 ? saturn_options_rows_mode : saturn_options_rows[engine_obj.cur_character];
    while (var_s1[0] != 0xFF) {
        obj = find_free_unk_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0;
            obj->unk2 = var_s1[0];
            obj->y_pos.i.hi = var_s1[1];
            obj->unk7 = var_s1[2];
        }
        if (var_s1[2] == 7) {
            break;
        }
        var_s1 += 3;
    }
    var_s1 = main_bss_state.character_mode != 0 ? saturn_options_labels_mode : saturn_options_labels;
    while (var_s1[1] != 7) {
        obj = find_free_unk_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0;
            obj->unk2 = var_s1[1];
            obj->y_pos.i.hi = var_s1[0];
        }
        var_s1 += 2;
    }
    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->id = 0;
        obj->unk2 = -2;
        obj->x_pos.i.hi = 0x20;
    }
    if (main_bss_state.character_mode == 0) {
        func_8001E980(0);
        saturn_title_upload_window();
    }
    main_bss_state.transition.selection = 0;
    saturn_fade_start_in();
    D_8013B7D0++;
}

static void options_sound(s32 id)
{
    func_8001540C(0, id, NULL);
}

void func_8002A098(struct GameInfo* arg0)
{
    u16 pressed;
    u16 button;
    u16 previous;
    u8 action;
    u8 bit;
    u8 i;

    if (main_bss_state.transition.active != 0) {
        return;
    }
    pressed = saturn_pad_pressed;
    if ((pressed & OPTIONS_PAD_START) || ((pressed & OPTIONS_PAD_CONFIRM) && main_bss_state.transition.selection == OPTIONS_ROW_EXIT)) {
        options_sound(OPTIONS_SOUND_CONFIRM);
        saturn_fade_start_out();
        D_8013B7D0++;
        return;
    }
    if (pressed & OPTIONS_PAD_UP) {
        options_sound(OPTIONS_SOUND_MOVE);
        main_bss_state.transition.selection = main_bss_state.transition.selection == 0 ? OPTIONS_ROW_EXIT
                                                                                       : main_bss_state.transition.selection - 1;
        if (main_bss_state.character_mode == 0 && engine_obj.cur_character != 0 && main_bss_state.transition.selection == OPTIONS_ROW_LOCKED_B) {
            main_bss_state.transition.selection = OPTIONS_ROW_UNLOCKED;
        }
    }
    if (saturn_pad_pressed & OPTIONS_PAD_DOWN) {
        options_sound(OPTIONS_SOUND_MOVE);
        main_bss_state.transition.selection = main_bss_state.transition.selection == OPTIONS_ROW_EXIT ? 0
                                                                                                      : main_bss_state.transition.selection + 1;
        if (main_bss_state.character_mode == 0 && engine_obj.cur_character != 0 && main_bss_state.transition.selection == OPTIONS_ROW_LOCKED_A) {
            main_bss_state.transition.selection = OPTIONS_ROW_EXIT;
        }
    }
    action = OPTIONS_NO_ACTION;
    for (bit = OPTIONS_FIRST_ACTION_BIT; bit < OPTIONS_ACTION_BITS; bit++) {
        if ((u16)(1 << bit) == saturn_options_actions[main_bss_state.transition.selection]) {
            action = bit;
            break;
        }
    }
    if (action == OPTIONS_NO_ACTION) {
        return;
    }
    pressed = saturn_pad_pressed;
    for (i = 0; i < OPTIONS_BUTTON_COUNT; i++) {
        button = saturn_options_buttons[i];
        if (pressed != button) {
            continue;
        }
        options_sound(OPTIONS_SOUND_CONFIRM);
        previous = saturn_button_masks[action];
        saturn_button_masks[action] = button;
        for (bit = 0; saturn_button_masks[bit] != 0; bit++) {
            if (bit != action && saturn_button_masks[bit] == button) {
                saturn_button_masks[bit] = previous;
            }
        }
        return;
    }
}

void func_8002A394(struct GameInfo* arg0)
{
    if (main_bss_state.transition.active == 0) {
        if (main_bss_state.character_mode != 0) {
            arg0->unk0 = 8;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
        } else {
            (*(s8*)&arg0->unk6)++;
        }
        func_80029DBC();
        func_8001E980(1);
        D_8013B7D0 = 0;
    }
}

static void (*const saturn_options_states[])(struct GameInfo*) = {
    func_80029E1C,
    func_8002A098,
    func_8002A394,
};

void func_8002A41C(struct GameInfo* arg0)
{
    saturn_sprite_reset_queues();
    saturn_options_states[D_8013B7D0](arg0);
    update_unk_objects();
    saturn_sprite_draw_passes();
}
#endif

u16 D_800F44E8[8] = { 0x10, 0x80, 0x100, 0x40, 0x20, 0x200, 0x400, 0xFFFF };

u16 D_800F44F8[8] = { 0x80, 0x10, 0x40, 0x20, 4, 1, 8, 2 };

#ifdef MMX4_WIN32
u8 D_800F4508[] = { 0x5F, 0x11, 0x00, 0x60, 0x1F, 0x00, 0x61, 0x2D, 0x01, 0x62, 0x3B, 0x02, 0x63, 0x49, 0x03, 0x64, 0x57, 0x04, 0x65, 0x65, 0x04, 0x66, 0x73, 0x05, 0x67, 0x82, 0x06, 0x76, 0x91, 0x07, 0x77, 0x9F, 0x08, 0x78, 0xAD, 0x09, 0x79, 0xBB, 0x0A, 0x70, 0xCB, 0x0B, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00 };
#else
u8 D_800F4508[0x20] = {
    0x5F,
    0x28,
    0x00,
    0x60,
    0x38,
    0x00,
    0x61,
    0x48,
    0x01,
    0x62,
    0x58,
    0x02,
    0x63,
    0x68,
    0x03,
    0x64,
    0x78,
    0x04,
    0x65,
    0x88,
    0x04,
    0x66,
    0x98,
    0x05,
    0x67,
    0xA8,
    0x06,
    0x70,
    0xB8,
    0x07,
    0xFF,
    0x00,
};
#endif

#ifdef MMX4_WIN32
u8 D_800F4528[] = { 0x5F, 0x14, 0x00, 0x61, 0x24, 0x01, 0x62, 0x34, 0x02, 0x63, 0x44, 0x03, 0x64, 0x54, 0x04, 0x66, 0x64, 0x05, 0x67, 0x74, 0x06, 0x76, 0x86, 0x07, 0x77, 0x96, 0x08, 0x78, 0xA6, 0x09, 0x79, 0xB6, 0x0A, 0x70, 0xCA, 0x0B, 0xFF, 0x00, 0x00, 0x00 };
#else
u8 D_800F4528[0x1C] = {
    0x5F,
    0x30,
    0x00,
    0x61,
    0x40,
    0x01,
    0x62,
    0x50,
    0x02,
    0x63,
    0x60,
    0x03,
    0x64,
    0x70,
    0x04,
    0x66,
    0x80,
    0x05,
    0x67,
    0x90,
    0x06,
    0x70,
    0xB0,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};
#endif

#ifdef MMX4_WIN32
u8 D_800F4544[] = { 0x60, 0x14, 0x00, 0x61, 0x24, 0x01, 0x62, 0x34, 0x02, 0x63, 0x44, 0x03, 0x65, 0x54, 0x04, 0x66, 0x64, 0x05, 0x67, 0x74, 0x06, 0x76, 0x86, 0x07, 0x77, 0x96, 0x08, 0x78, 0xA6, 0x09, 0x79, 0xB6, 0x0A, 0x70, 0xCA, 0x0B, 0xFF, 0x00, 0x00, 0x00 };
#else
u8 D_800F4544[0x1C] = {
    0x60,
    0x30,
    0x00,
    0x61,
    0x40,
    0x01,
    0x62,
    0x50,
    0x02,
    0x63,
    0x60,
    0x03,
    0x65,
    0x70,
    0x04,
    0x66,
    0x80,
    0x05,
    0x67,
    0x90,
    0x06,
    0x70,
    0xB0,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};
#endif

u8* D_800F4560[2] = { D_800F4528, D_800F4544 };

#ifdef MMX4_WIN32
u8 D_800F4568[] = { 0x17, 0x00, 0x2D, 0x01, 0x3B, 0x02, 0x49, 0x03, 0x5D, 0x04, 0x73, 0x05, 0x82, 0x06, 0x91, 0x07, 0x9F, 0x08, 0xAD, 0x09, 0xBB, 0x0A, 0xCB, 0x0B, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
#else
u8 D_800F4568[0x14] = {
    0x30,
    0x00,
    0x48,
    0x01,
    0x58,
    0x02,
    0x68,
    0x03,
    0x80,
    0x04,
    0x98,
    0x05,
    0xA8,
    0x06,
    0xB8,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};
#endif

#ifdef MMX4_WIN32
u8 D_800F457C[] = { 0x14, 0x00, 0x24, 0x01, 0x34, 0x02, 0x44, 0x03, 0x54, 0x04, 0x64, 0x05, 0x74, 0x06, 0x86, 0x07, 0x96, 0x08, 0xA6, 0x09, 0xB6, 0x0A, 0xCA, 0x0B, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
#else
u8 D_800F457C[0x14] = {
    0x30,
    0x00,
    0x40,
    0x01,
    0x50,
    0x02,
    0x60,
    0x03,
    0x70,
    0x04,
    0x80,
    0x05,
    0x90,
    0x06,
    0xB0,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};
#endif

void (*D_800F4590[])(struct GameInfo* arg0) = {
    func_80029E1C,
    func_8002A098,
    func_8002A394,
};
