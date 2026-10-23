#include "common.h"
#include "saturn/platform.h"

#define SAVE_SLOT_BYTES 42
#define SAVE_BUTTON_MASKS 16
#define SAVE_LIVES_FLAG 4
#define SAVE_LIVES_DEFAULT 2
#define SAVE_CONFIRM 0x0700
#define SAVE_ANY 0x0770
#define SAVE_STATE_RESUME 1
#define SAVE_STATE_CONFIRM 2
#define SAVE_STATE_EXIT 3
#define SAVE_MODE_SLOTS 8
#define SAVE_MODE_LOAD 9
#define SAVE_SLOT_HIDDEN 0xFF
#define SAVE_SELECT_X 0xD0
#define SAVE_SELECT_Y 0x88
#define SAVE_SELECT_KIND 7
#define ENGINE_LIVES 0x44
#define ENGINE_HP_DISPLAY 0x5C

extern u8 saturn_engine_bytes[];
extern u8 saturn_main_bss_bytes[];
extern u8 saturn_save_slots[];
extern u8* saturn_save_box_objects;
extern u8* saturn_save_cursor;
extern u8 saturn_save_device;
extern s8 saturn_save_slot;
#define SAVE_LIVES_MASK save_armor_masks[3]
extern u8 saturn_save_slots_text[];
extern u8 saturn_save_load_text[];
extern u16 saturn_pad_pressed;
void reset_objects(void);
void saturn_save_menu_draw_slots(u8* menu, s32 mode);
void saturn_save_menu_draw_frame(void);
void saturn_save_menu_draw_box(s32 kind, s32 x, s32 y);
s16 saturn_menu_string_width(u8* text, s32 arg);

#define SAVE_PAD_UP 0x1000
#define SAVE_PAD_DOWN 0x2000
#define SAVE_PAD_CONFIRM 0x0600
#define SAVE_PAD_CANCEL 0x0100
#define SAVE_SE_CURSOR 13
#define SAVE_SE_EMPTY 14
#define SAVE_SE_CONFIRM 39
#define SAVE_STATE_DEVICE 1
#define SAVE_STATE_SLOT 2
#define SAVE_STATE_PROMPT 3
#define SAVE_STATE_SAVED 4
#define SAVE_STATE_FAILED 5
#define SAVE_STATE_LOADED 6
#define SAVE_DEVICE_INTERNAL 0
#define SAVE_DEVICE_CART 1
#define SAVE_DEVICE_NONE 2
#define SAVE_INTERNAL_ERROR 0x04
#define SAVE_INTERNAL_DATA 0x02
#define SAVE_CART_DATA 0x20
#define SAVE_SLOT_COUNT 3
#define SAVE_SLOT_BACK 3
#define SAVE_ALL_SLOT_BYTES (SAVE_SLOT_BYTES * SAVE_SLOT_COUNT)
#define SAVE_BOX_OBJECT_BYTES 0x60
#define SAVE_BOX_ROW 0
#define SAVE_SAVED_X 0xA0
#define SAVE_SAVED_Y 0x78
#define SAVE_SLOTS_IDLE 0
#define SAVE_SLOTS_LIST 1
#define SAVE_SLOTS_PROMPT 2
#define SAVE_SLOTS_SAVED 3
#define SAVE_SLOTS_FAILED 4
#define SAVE_SLOTS_LOAD_FAILED 5
#define SAVE_CURSOR_Y_OFFSET 8
#define SAVE_FADE 8
#define SAVE_DISPLAY_GAME 15
#define SAVE_GAME_STATE 1
#define SAVE_GAME_STEP 6
#define SAVE_SELECTION 7
#define SAVE_GAME_INFO_TITLE 7
#define SAVE_LOAD_MODE 8
#define ENGINE_CHARACTER 0x43
#define ENGINE_ALTERNATE 0x37

extern u8 saturn_save_selection;
extern u16 saturn_save_checksum;
extern u16 saturn_save_cursor_rows[];
extern u8 saturn_backup_cart_status;
extern u8 saturn_display_mode;
extern u8 D_800F22D0[];
extern u8 D_800F22E0[];
extern u8 D_800F2300[];
extern u8 D_800F2328[];
void func_8001E980(u8 arg0);
void func_8001FB50(void);
void func_800129F0(s32 frames);
void func_800127FC(void);
s32 saturn_archive_load_blocking(const char* path);
void saturn_sprite_reset_queues(void);
void saturn_sprite_draw_passes(void);
void update_misc_objects(void);

#define SAVE_LABEL_OBJECT 0x16
#define SAVE_LABEL_KIND 6
#define SAVE_CURSOR_KIND 4
#define SAVE_MARKER_KIND 7
#define SAVE_CURSOR_TEXTURE 0xE000
#define SAVE_CURSOR_LAYER 0x10
#define SAVE_CURSOR_CLUT 6
#define SAVE_CURSOR_X_OFFSET 8
#define SAVE_ROW_NONE 0xFF
#define SAVE_ROW_DISABLED 0xF0
#define SAVE_ROWS 4
#define SAVE_INTERNAL_FULL 0x01
#define SAVE_CART_FULL 0x10
#define SAVE_CART_ERROR 0x40
#define SAVE_DEVICE_ERRORS (SAVE_INTERNAL_ERROR | SAVE_CART_ERROR)
#define SAVE_MARKER_FRAME 42

extern u8 saturn_save_draw_mode;
extern u32 saturn_loading_resource[];
extern union AnimationStep* saturn_save_cursor_animations[];
void set_animation(void* object, s32 index);

#define SAVE_ICON_SLOTS 24
#define SAVE_ICON_UPGRADES 8
#define SAVE_ICON_TANKS 16
#define SAVE_ICON_NONE 0xFF
#define SAVE_ICON_TANK 22
#define SAVE_RECORD_UPGRADES 0x24
#define SAVE_RECORD_ITEMS 0x22

extern u8 saturn_save_icons[SAVE_SLOT_COUNT][SAVE_ICON_SLOTS];

#define SAVE_BOX_COLUMNS 8
#define SAVE_BOX_ROWS 3
#define SAVE_BOX_STEP 16
#define SAVE_BOX_LEFT 48
#define SAVE_BOX_TOP 24
#define SAVE_PORTRAIT_LEFT 64
#define SAVE_BOX_PRIORITY 0x10
#define SAVE_PORTRAIT_LAYER 0x12
#define SAVE_PART_LAYER 0x11
#define SAVE_ICON_TEXTURE_BASE 0x25C7C000u
#define SAVE_ICON_TEXTURE_SHIFT 7
#define SAVE_PORTRAIT_TEXTURE 0xE000
#define SAVE_RECORD_ARMOR 0x26
#define SAVE_RECORD_ARMOR_COLOR 0x27
#define SAVE_RECORD_ULTIMATE 0x29
#define SAVE_FRAME_X 44
#define SAVE_FRAME_ZERO 43
#define SAVE_FRAME_PART 45
#define SAVE_FRAME_ULTIMATE 52
#define SAVE_CLUT_X 8
#define SAVE_CLUT_X_ULTIMATE 29
#define SAVE_CLUT_ZERO 7
#define SAVE_CLUT_ZERO_ULTIMATE 28
#define SAVE_CLUT_PART 9
#define SAVE_CLUT_PART_GOLD 25
#define SAVE_CLUT_ULTIMATE 28
#define SAVE_PART_GOLD 2
#define SAVE_PART_GOLD_INDEX 2
#define SAVE_ARMOR_PARTS 4

#define SMPC_SF (*(volatile u8*)0x20100063)
#define SMPC_COMREG (*(volatile u8*)0x2010001F)
#define SMPC_BUSY 1
#define SMPC_RESET_DISABLE 0x1A
#define SMPC_RESET_ENABLE 0x19
#define BUP_LIBRARY ((void*)0x06002000)
#define BUP_WORK ((void*)0x06006000)
#define BUP_INTERNAL 0
#define BUP_CARTRIDGE 1
#define BUP_NOT_FORMATTED 1
#define BUP_NOT_CONNECTED 2
#define BUP_SAVE_BYTES 0x80
#define BUP_MIN_BLOCKS 3
#define BUP_FAILED 0xFF
#define BACKUP_INTERNAL_MISSING 8
#define BACKUP_CARTRIDGE_MISSING 0x80
#define BACKUP_INTERNAL_UNFORMATTED 5
#define BACKUP_INTERNAL_NO_FILE 2
#define BACKUP_INTERNAL_FULL 4
#define BACKUP_CARTRIDGE_UNFORMATTED 0x50
#define BACKUP_CARTRIDGE_NO_FILE 0x20
#define BACKUP_CARTRIDGE_FULL 0x40
#define BUP_SEL_STAT 3
#define BUP_SEL_WRITE 4
#define BUP_SEL_READ 5
#define BUP_SEL_DIR 7
#define BUP_SEL_VERIFY 8
#define BUP_SEL_SET_DATE 10
#define RTC_YEAR_HIGH 6
#define RTC_YEAR_LOW 5
#define RTC_MONTH 4
#define RTC_DAY 3
#define RTC_HOUR 2
#define RTC_MINUTE 1

struct SaturnBackupStat {
    u32 total_size;
    u32 total_blocks;
    u32 block_size;
    u32 free_size;
    u32 free_blocks;
    u32 data_blocks;
};

struct SaturnBackupDir {
    char file_name[12];
    char comment[11];
    u8 language;
    u32 date;
    u32 data_size;
    u16 block_size;
    u16 padding;
};

struct SaturnBackupDate {
    u8 year;
    u8 month;
    u8 day;
    u8 hour;
    u8 minute;
    u8 week;
};

typedef void (*SaturnBupInit)(void* library, void* work, void* config);
typedef s32 (*SaturnBupFunction)();

extern SaturnBupInit saturn_bios_bup_init;
extern SaturnBupFunction* saturn_bios_bup_vector;
extern u8 saturn_save_slots[];
extern u8* saturn_rtc_time;
char* strcpy(char* destination, const char* source);

static void save_menu_device(u8* menu);
static void save_menu_slot(u8* menu);
static void save_menu_prompt(u8* menu);
static void save_menu_loaded(u8* menu);

char saturn_backup_file_name[] = "MEGAMAN_X4_";

char saturn_backup_comment[] = "MEGAMAN_X4";

u8 saturn_save_icon_frame[] = {
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
};

struct MemcardSaveSlot;

u8 saturn_save_options[42] = { 0xFF };

u8 saturn_save_cursor_columns[] = { 0x48, 0x20, 0x20 };

static const u8 save_upgrade_frames[2][SAVE_ICON_UPGRADES] = {
    { 0x08, 0x0D, 0x0E, 0x0B, 0x0C, 0x0A, 0x0F, 0x09 },
    { 0x02, 0x00, 0x05, 0x04, 0x03, 0x01, 0x07, 0x06 },
};

static const u8 save_armor_frames[4][2] = { { 0x12, 0x13 }, { 0x12, 0x13 }, { 0x10, 0x11 }, { 0x14, 0x15 } };

static const u8 save_icon_cluts[] = {
    0x13,
    0x13,
    0x14,
    0x15,
    0x16,
    0x15,
    0x16,
    0x14,
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x0F,
    0x10,
    0x11,
    0x12,
    0x17,
    0x17,
    0x17,
    0x17,
    0x18,
    0x18,
    0x19,
};

static const u8 save_upgrade_masks[SAVE_ICON_UPGRADES] = { 0x01, 0x20, 0x40, 0x08, 0x10, 0x04, 0x80, 0x02 };

static const u8 save_armor_part_masks[SAVE_ARMOR_PARTS] = { 0x01, 0x02, 0x04, 0x08 };

static const u16 save_armor_masks[4] = { 0x1000, 0x2000, 0x4000, 0x8000 };

static const u16 save_tank_masks[8] = { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080 };

static const u8 save_icon_layers[SAVE_BOX_ROWS] = { 0x10, 0x11, 0x12 };

static void (*const save_menu_states[])(u8*) = {
    saturn_save_menu_init,
    save_menu_device,
    save_menu_slot,
    save_menu_prompt,
    saturn_save_menu_message,
    saturn_save_menu_result,
    save_menu_loaded,
};

void func_8001A9EC(struct EngineObj* engine)
{
    u8* menu = (u8*)engine;

    saturn_sprite_reset_queues();
    save_menu_states[menu[1]](menu);
    if (saturn_save_cursor != NULL) {
        *(s16*)(saturn_save_cursor + 12) = saturn_save_cursor_rows[saturn_main_bss_bytes[SAVE_SELECTION]] + SAVE_CURSOR_Y_OFFSET;
    }
    update_misc_objects();
    saturn_sprite_draw_passes();
}

void saturn_save_menu_init(u8* menu)
{
    saturn_save_box_objects = NULL;
    saturn_save_cursor = NULL;
    saturn_save_device = 0;
    saturn_save_slot = 0;
    reset_objects();
    saturn_save_menu_draw_slots(menu, 0);
    menu[1] = SAVE_STATE_RESUME;
}

static void save_menu_leave(u8* menu)
{
    u8* selection = &saturn_main_bss_bytes[SAVE_SELECTION];

    saturn_save_cursor = NULL;
    reset_objects();
    if (saturn_main_bss_bytes[SAVE_LOAD_MODE] == 0) {
        if (*(s16*)(menu + 4) == SAVE_MODE_SLOTS) {
            *(s16*)(menu + 8) = saturn_menu_string_width(D_800F2328, 1);
            menu[0] = SAVE_MODE_SLOTS;
            *selection = 2;
        } else {
            *(s16*)(menu + 8) = saturn_menu_string_width(D_800F2300, 1);
            menu[0] = SAVE_MODE_LOAD;
            *selection = 0;
        }
        menu[1] = SAVE_STATE_DEVICE;
        return;
    }
    game_info.unk0 = SAVE_GAME_INFO_TITLE;
    game_info.unk2 = 0;
    game_info.unk3 = 0;
    if (saturn_save_options[0] != SAVE_SLOT_HIDDEN) {
        game_info.unk8 = saturn_menu_string_width(D_800F22D0, 0);
        game_info.mode = 1;
    } else {
        game_info.unk8 = saturn_menu_string_width(D_800F22E0, 0);
        game_info.mode = 3;
    }
    *selection = 0;
}

static void save_menu_show_slots(u8* menu)
{
    saturn_save_menu_draw_frame();
    saturn_save_menu_draw_slots(menu, SAVE_SLOTS_LIST);
    saturn_save_menu_draw_box(SAVE_SELECT_KIND, SAVE_SELECT_X, SAVE_SELECT_Y);
    menu[1] = SAVE_STATE_SLOT;
}

static u16 save_slots_sum(void)
{
    u32 i;
    u16 sum = 0;
    for (i = 0; i < SAVE_ALL_SLOT_BYTES; i++) {
        sum += saturn_save_slots[i];
    }
    return sum;
}

static s32 save_menu_device_chosen(u8* menu)
{
    u8* selection = &saturn_main_bss_bytes[SAVE_SELECTION];
    u8 device;

    func_8001540C(0, SAVE_SE_CONFIRM, NULL);
    reset_objects();
    saturn_save_selection = *selection;
    saturn_save_device = *selection;
    saturn_save_slot = 0;
    if (saturn_save_device == SAVE_DEVICE_INTERNAL) {
        saturn_save_device = (saturn_backup_cart_status & SAVE_INTERNAL_ERROR) ? SAVE_DEVICE_CART : SAVE_DEVICE_INTERNAL;
    } else if (menu[3] == 1) {
        saturn_save_device = SAVE_DEVICE_NONE;
    }
    device = saturn_save_device;
    if (device == SAVE_DEVICE_NONE) {
        return 0;
    }
    if ((device == SAVE_DEVICE_INTERNAL && (saturn_backup_cart_status & SAVE_INTERNAL_DATA)) || (device != SAVE_DEVICE_INTERNAL && (saturn_backup_cart_status & SAVE_CART_DATA))) {
        if ((saturn_backup_load(device) == 0 || saturn_backup_load(device) == 0) && (u16)(save_slots_sum() + saturn_save_checksum) == 0) {
            save_menu_show_slots(menu);
            return 0;
        }
        saturn_save_menu_draw_slots(menu, SAVE_SLOTS_LOAD_FAILED);
        menu[1] = SAVE_STATE_FAILED;
        return 1;
    }
    saturn_save_slots[0] = SAVE_SLOT_HIDDEN;
    saturn_save_slots[SAVE_SLOT_BYTES] = SAVE_SLOT_HIDDEN;
    saturn_save_slots[SAVE_SLOT_BYTES * 2] = SAVE_SLOT_HIDDEN;
    save_menu_show_slots(menu);
    return 0;
}

static void save_menu_device(u8* menu)
{
    u8* selection = &saturn_main_bss_bytes[SAVE_SELECTION];

    if (saturn_pad_pressed & SAVE_PAD_UP) {
        func_8001540C(0, SAVE_SE_CURSOR, NULL);
        *selection = *selection != 0 ? *selection - 1 : menu[3];
    }
    if (saturn_pad_pressed & SAVE_PAD_DOWN) {
        func_8001540C(0, SAVE_SE_CURSOR, NULL);
        *selection = *selection != menu[3] ? *selection + 1 : 0;
    }
    if ((saturn_pad_pressed & SAVE_PAD_CONFIRM) && save_menu_device_chosen(menu)) {
        return;
    }
    if ((saturn_pad_pressed & SAVE_PAD_CANCEL) || saturn_save_device == SAVE_DEVICE_NONE) {
        save_menu_leave(menu);
    }
}

static void save_menu_clear_box(void)
{
    u8* object = saturn_save_box_objects;
    if (object == NULL) {
        return;
    }
    for (; object < (u8*)layer_objects; object += SAVE_BOX_OBJECT_BYTES) {
        object[0] = 0;
        object[3] = 0;
    }
    saturn_save_box_objects = NULL;
}

static void save_menu_slot_moved(void)
{
    saturn_save_slot = saturn_main_bss_bytes[SAVE_SELECTION];
    save_menu_clear_box();
    saturn_save_menu_draw_box(SAVE_SELECT_KIND, SAVE_SELECT_X, SAVE_SELECT_Y);
}

static void save_menu_back_to_device(u8* menu)
{
    reset_objects();
    saturn_save_menu_draw_slots(menu, SAVE_SLOTS_IDLE);
    saturn_main_bss_bytes[SAVE_SELECTION] = saturn_save_selection;
    menu[1] = SAVE_STATE_DEVICE;
}

static void save_menu_slot(u8* menu)
{
    u8* selection = &saturn_main_bss_bytes[SAVE_SELECTION];

    if (saturn_pad_pressed & SAVE_PAD_UP) {
        func_8001540C(0, SAVE_SE_CURSOR, NULL);
        *selection = *selection != 0 ? *selection - 1 : SAVE_SLOT_BACK;
        save_menu_slot_moved();
    }
    if (saturn_pad_pressed & SAVE_PAD_DOWN) {
        func_8001540C(0, SAVE_SE_CURSOR, NULL);
        *selection = *selection != SAVE_SLOT_BACK ? *selection + 1 : 0;
        save_menu_slot_moved();
    }
    if (saturn_pad_pressed & SAVE_PAD_CONFIRM) {
        if (saturn_main_bss_bytes[SAVE_LOAD_MODE] != 0 && *selection != SAVE_SLOT_BACK && saturn_save_slots[(s8)(*selection * SAVE_SLOT_BYTES)] == SAVE_SLOT_HIDDEN) {
            func_8001540C(0, SAVE_SE_EMPTY, NULL);
        } else {
            func_8001540C(0, SAVE_SE_CONFIRM, NULL);
            reset_objects();
            if (*selection != SAVE_SLOT_BACK) {
                saturn_save_slot = *selection;
                saturn_save_menu_draw_slots(menu, SAVE_SLOTS_PROMPT);
                saturn_save_menu_draw_box(SAVE_BOX_ROW, SAVE_SELECT_X, SAVE_SELECT_Y);
                menu[1] = SAVE_STATE_PROMPT;
            } else {
                save_menu_back_to_device(menu);
            }
        }
    }
    if (saturn_pad_pressed & SAVE_PAD_CANCEL) {
        save_menu_back_to_device(menu);
    }
}

static void save_menu_back_to_slot(u8* menu)
{
    reset_objects();
    saturn_save_menu_draw_slots(menu, SAVE_SLOTS_LIST);
    saturn_save_menu_draw_box(SAVE_SELECT_KIND, SAVE_SELECT_X, SAVE_SELECT_Y);
    menu[1] = SAVE_STATE_SLOT;
}

static void save_menu_prompt(u8* menu)
{
    u8* selection = &saturn_main_bss_bytes[SAVE_SELECTION];

    if (saturn_pad_pressed & SAVE_PAD_UP) {
        func_8001540C(0, SAVE_SE_CURSOR, NULL);
        *selection = *selection != 0 ? *selection - 1 : 1;
    }
    if (saturn_pad_pressed & SAVE_PAD_DOWN) {
        func_8001540C(0, SAVE_SE_CURSOR, NULL);
        *selection = *selection != 1 ? *selection + 1 : 0;
    }
    if (saturn_pad_pressed & SAVE_PAD_CONFIRM) {
        func_8001540C(0, SAVE_SE_CONFIRM, NULL);
        if (*selection != 0) {
            save_menu_back_to_slot(menu);
        } else if (saturn_main_bss_bytes[SAVE_LOAD_MODE] == 0) {
            reset_objects();
            saturn_save_capture_slot();
            saturn_save_checksum = -save_slots_sum();
            if (saturn_backup_save(saturn_save_device) != 0 && saturn_backup_save(saturn_save_device) != 0) {
                saturn_save_menu_draw_slots(menu, SAVE_SLOTS_FAILED);
                menu[1] = SAVE_STATE_FAILED;
                return;
            }
            saturn_backup_cart_status |= saturn_save_device == SAVE_DEVICE_INTERNAL ? SAVE_INTERNAL_DATA : SAVE_CART_DATA;
            saturn_save_menu_draw_slots(menu, SAVE_SLOTS_SAVED);
            saturn_save_menu_draw_frame();
            saturn_save_menu_draw_box(SAVE_BOX_ROW, SAVE_SAVED_X, SAVE_SAVED_Y);
            menu[1] = SAVE_STATE_SAVED;
        } else {
            saturn_save_load((struct MemcardSaveSlot*)(saturn_save_slots + (s8)(saturn_save_slot * SAVE_SLOT_BYTES)), 1);
            func_800129F0(SAVE_FADE);
            menu[1] = SAVE_STATE_LOADED;
            return;
        }
    }
    if (saturn_pad_pressed & SAVE_PAD_CANCEL) {
        save_menu_back_to_slot(menu);
    }
}

void saturn_save_menu_message(u8* menu)
{
    if ((saturn_pad_pressed & SAVE_CONFIRM) == 0) {
        return;
    }
    saturn_save_cursor = NULL;
    reset_objects();
    menu[1] = SAVE_STATE_EXIT;
    menu[2] = 0;
    menu[3] = 0;
    if (*(s16*)(menu + 4) == SAVE_MODE_SLOTS) {
        *(s16*)(menu + 8) = saturn_menu_string_width(saturn_save_slots_text, 1);
        menu[0] = SAVE_MODE_SLOTS;
    } else {
        *(s16*)(menu + 8) = saturn_menu_string_width(saturn_save_load_text, 1);
        menu[0] = SAVE_MODE_LOAD;
    }
    saturn_main_bss_bytes[7] = 0;
}

void saturn_save_menu_result(u8* menu)
{
    if ((saturn_pad_pressed & SAVE_ANY) == 0) {
        return;
    }
    if (saturn_main_bss_bytes[8] == 0) {
        saturn_save_slots[0] = SAVE_SLOT_HIDDEN;
        saturn_save_slots[SAVE_SLOT_BYTES] = SAVE_SLOT_HIDDEN;
        saturn_save_slots[SAVE_SLOT_BYTES * 2] = SAVE_SLOT_HIDDEN;
        saturn_save_menu_draw_frame();
        reset_objects();
        saturn_save_menu_draw_slots(menu, 1);
        saturn_save_menu_draw_box(SAVE_SELECT_KIND, SAVE_SELECT_X, SAVE_SELECT_Y);
        menu[1] = SAVE_STATE_CONFIRM;
    } else {
        reset_objects();
        saturn_save_menu_draw_slots(menu, 0);
        menu[1] = SAVE_STATE_RESUME;
    }
}

static void save_menu_loaded(u8* menu)
{
    if (main_bss_state.transition.active != 0) {
        return;
    }
    reset_objects();
    saturn_save_cursor = NULL;
    saturn_display_mode = SAVE_DISPLAY_GAME;
    func_8001E980(1);
    if (menu[ENGINE_CHARACTER] != 0) {
        saturn_archive_load_blocking("PL01.ARC");
    } else if (menu[ENGINE_ALTERNATE] != 0) {
        saturn_archive_load_blocking("PL02.ARC");
    } else {
        saturn_archive_load_blocking("PL00.ARC");
    }
    saturn_engine_bytes[0] = SAVE_GAME_STATE;
    saturn_engine_bytes[1] = SAVE_GAME_STEP;
    saturn_engine_bytes[2] = 0;
    saturn_engine_bytes[3] = 0;
    func_80012740(1, func_8001FB50);
    func_800127FC();
}

static void smpc_command(u8 command)
{
    while ((SMPC_SF & SMPC_BUSY) == SMPC_BUSY) {
    }
    SMPC_SF = SMPC_BUSY;
    SMPC_COMREG = command;
    while (SMPC_SF & SMPC_BUSY) {
    }
}

u32 saturn_backup_status(void)
{
    u8 config[12];
    struct SaturnBackupStat stat;
    struct SaturnBackupDir dir;
    u32 free_blocks[2];
    s32 internal;
    s32 cartridge;
    u32 flags;
    smpc_command(SMPC_RESET_DISABLE);
    saturn_bios_bup_init(BUP_LIBRARY, BUP_WORK, config);
    smpc_command(SMPC_RESET_ENABLE);
    internal = saturn_bios_bup_vector[BUP_SEL_STAT](BUP_INTERNAL, BUP_SAVE_BYTES, &stat);
    free_blocks[0] = stat.free_blocks;
    cartridge = saturn_bios_bup_vector[BUP_SEL_STAT](BUP_CARTRIDGE, BUP_SAVE_BYTES, &stat);
    free_blocks[1] = stat.free_blocks;
    flags = internal == BUP_NOT_CONNECTED ? BACKUP_INTERNAL_MISSING : 0;
    if (cartridge == BUP_NOT_CONNECTED) {
        flags |= BACKUP_CARTRIDGE_MISSING;
    }
    if ((u8)flags) {
        return flags;
    }
    flags = 0;
    if (internal == BUP_NOT_FORMATTED) {
        flags = BACKUP_INTERNAL_UNFORMATTED;
    } else if (saturn_bios_bup_vector[BUP_SEL_DIR](BUP_INTERNAL, saturn_backup_file_name, 1, &dir) != 0) {
        flags = BACKUP_INTERNAL_NO_FILE;
    } else if (free_blocks[0] < BUP_MIN_BLOCKS) {
        flags = BACKUP_INTERNAL_FULL;
    }
    if (cartridge == BUP_NOT_FORMATTED) {
        flags |= BACKUP_CARTRIDGE_UNFORMATTED;
    } else if (saturn_bios_bup_vector[BUP_SEL_DIR](BUP_CARTRIDGE, saturn_backup_file_name, 1, &dir) != 0) {
        flags |= BACKUP_CARTRIDGE_NO_FILE;
    } else if (free_blocks[1] < BUP_MIN_BLOCKS) {
        flags |= BACKUP_CARTRIDGE_FULL;
    }
    return flags;
}

static u8 bcd(u8 value)
{
    return (u8)((value >> 4) * 10 + (value & 15));
}

u32 saturn_backup_save(u32 device)
{
    u8 config[12];
    struct SaturnBackupStat stat;
    struct SaturnBackupDir dir;
    struct SaturnBackupDate date;
    u8* rtc;
    s32 result;
    smpc_command(SMPC_RESET_DISABLE);
    saturn_bios_bup_init(BUP_LIBRARY, BUP_WORK, config);
    smpc_command(SMPC_RESET_ENABLE);
    saturn_bios_bup_vector[BUP_SEL_STAT](device, BUP_SAVE_BYTES, &stat);
    strcpy(dir.file_name, saturn_backup_file_name);
    strcpy(dir.comment, saturn_backup_comment);
    dir.language = 0;
    rtc = saturn_rtc_time;
    date.year = (u8)((rtc[RTC_YEAR_HIGH] >> 4) * 1000 + (rtc[RTC_YEAR_HIGH] & 15) * 100 + (rtc[RTC_YEAR_LOW] >> 4) * 10 + (rtc[RTC_YEAR_LOW] & 15) + 68);
    date.month = (u8)(rtc[RTC_MONTH] & 15);
    date.day = bcd(rtc[RTC_DAY]);
    date.hour = bcd(rtc[RTC_HOUR]);
    date.minute = bcd(rtc[RTC_MINUTE]);
    dir.date = (u32)saturn_bios_bup_vector[BUP_SEL_SET_DATE](&date);
    dir.data_size = BUP_SAVE_BYTES;
    smpc_command(SMPC_RESET_DISABLE);
    result = saturn_bios_bup_vector[BUP_SEL_WRITE](device, &dir, saturn_save_slots, 0);
    smpc_command(SMPC_RESET_ENABLE);
    if (result == 0) {
        result = saturn_bios_bup_vector[BUP_SEL_VERIFY](device, saturn_backup_file_name, saturn_save_slots);
        if (result == 0) {
            return 0;
        }
    }
    return BUP_FAILED;
}

u32 saturn_backup_load(u32 device)
{
    u8 config[12];
    s32 result;
    smpc_command(SMPC_RESET_DISABLE);
    saturn_bios_bup_init(BUP_LIBRARY, BUP_WORK, config);
    result = saturn_bios_bup_vector[BUP_SEL_READ](device, saturn_backup_file_name, saturn_save_slots);
    smpc_command(SMPC_RESET_ENABLE);
    return result ? BUP_FAILED : 0;
}

static void save_menu_label(u8 frame, u8 y, u8 row)
{
    struct MiscObj* obj;

    if (row == 0) {
        obj = find_free_misc_obj();
        if (obj != NULL) {
            saturn_save_cursor = (u8*)obj;
            obj->active = 1;
            obj->id = SAVE_LABEL_OBJECT;
            obj->unk2 = SAVE_CURSOR_KIND;
            obj->unk40 = SAVE_CURSOR_TEXTURE;
            obj->unk3C = (u8*)saturn_loading_resource + saturn_loading_resource[0];
            obj->bg_offset = -1;
            obj->x_pos.i.hi = saturn_save_cursor_columns[saturn_save_draw_mode] + SAVE_CURSOR_X_OFFSET;
            obj->y_pos.i.hi = saturn_save_cursor_rows[0] + SAVE_CURSOR_Y_OFFSET;
            obj->unk15 = 0;
            obj->unk16 = SAVE_CURSOR_LAYER;
            obj->unk42 = SAVE_CURSOR_CLUT;
            obj->animation_table = (u32**)saturn_save_cursor_animations;
            set_animation(obj, 0);
            obj->unk6 = SAVE_CURSOR_LAYER;
        }
    }
    if (row < SAVE_ROWS) {
        saturn_save_cursor_rows[row] = y;
    }
    obj = find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->id = SAVE_LABEL_OBJECT;
        obj->unk2 = SAVE_LABEL_KIND;
        obj->unk6 = 0;
        obj->unk7 = row;
        obj->y_pos.i.hi = y;
        obj->animation_step.fields.frame_index = frame;
    }
}

static void save_box_portrait_frame(struct MiscObj* obj, u8 frame, u8 clut)
{
    obj->unk40 = SAVE_PORTRAIT_TEXTURE;
    obj->unk3C = (u8*)saturn_loading_resource + saturn_loading_resource[0];
    obj->unk15 = SAVE_BOX_PRIORITY;
    obj->unk42 = clut;
    obj->animation_step.fields.frame_index = frame;
}

static struct MiscObj* save_box_object(u8 kind, s16 x, s16 y, u8 layer)
{
    struct MiscObj* obj = find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->id = SAVE_LABEL_OBJECT;
        obj->unk2 = kind;
        obj->bg_offset = -1;
        obj->x_pos.i.hi = x;
        obj->y_pos.i.hi = y;
        obj->unk16 = layer;
        obj->unk6 = SAVE_BOX_PRIORITY;
    }
    return obj;
}

void saturn_save_menu_draw_box(s32 kind, s32 x, s32 y)
{
    u8* record = saturn_save_slots + (s8)(saturn_save_slot * SAVE_SLOT_BYTES);
    u8* icons = saturn_save_icons[(s8)saturn_save_slot];
    struct MiscObj* obj;
    u8 first = 0;
    s32 row;
    s32 column;
    s32 i;

    if ((u8)kind == 0 && record[0] == SAVE_SLOT_HIDDEN) {
        saturn_save_box_objects = NULL;
        return;
    }
    for (row = 0; row < SAVE_BOX_ROWS; row++) {
        for (column = 0; column < SAVE_BOX_COLUMNS; column++) {
            u8 icon = *icons++;
            if (icon == SAVE_ICON_NONE) {
                continue;
            }
            obj = save_box_object(kind, x - SAVE_BOX_LEFT + column * SAVE_BOX_STEP, y - SAVE_BOX_TOP + row * SAVE_BOX_STEP,
                save_icon_layers[row]);
            if (obj == NULL) {
                continue;
            }
            if (!first) {
                saturn_save_box_objects = (u8*)obj;
                first = 1;
            }
            obj->unk40 = (u16)(((icon << SAVE_ICON_TEXTURE_SHIFT) + SAVE_ICON_TEXTURE_BASE) >> 3);
            obj->unk42 = save_icon_cluts[icon];
            obj->unk3C = saturn_save_icon_frame;
            obj->animation_step.fields.frame_index = 0;
            obj->unk15 = 0;
        }
    }
    obj = save_box_object(kind, x - SAVE_PORTRAIT_LEFT, y, SAVE_PORTRAIT_LAYER);
    if (obj != NULL) {
        if (!first) {
            saturn_save_box_objects = (u8*)obj;
        }
        if (record[0] == 0) {
            save_box_portrait_frame(obj, SAVE_FRAME_X, record[SAVE_RECORD_ULTIMATE] ? SAVE_CLUT_X_ULTIMATE : SAVE_CLUT_X);
        } else {
            save_box_portrait_frame(obj, SAVE_FRAME_ZERO, record[SAVE_RECORD_ULTIMATE] ? SAVE_CLUT_ZERO_ULTIMATE : SAVE_CLUT_ZERO);
        }
    }
    if (record[0] != 0) {
        return;
    }
    if (record[SAVE_RECORD_ULTIMATE] != 0) {
        if (record[SAVE_RECORD_ARMOR] != 0) {
            obj = save_box_object(kind, x - SAVE_PORTRAIT_LEFT, y, SAVE_PART_LAYER);
            if (obj != NULL) {
                save_box_portrait_frame(obj, SAVE_FRAME_ULTIMATE, SAVE_CLUT_ULTIMATE);
            }
        }
        return;
    }
    for (i = 0; i < SAVE_ARMOR_PARTS; i++) {
        if (!(record[SAVE_RECORD_ARMOR] & save_armor_part_masks[i])) {
            continue;
        }
        obj = save_box_object(kind, x - SAVE_PORTRAIT_LEFT, y, SAVE_PART_LAYER);
        if (obj != NULL) {
            save_box_portrait_frame(obj, SAVE_FRAME_PART + i,
                (i == SAVE_PART_GOLD_INDEX && record[SAVE_RECORD_ARMOR_COLOR] == SAVE_PART_GOLD) ? SAVE_CLUT_PART_GOLD
                                                                                                 : SAVE_CLUT_PART);
        }
    }
}

void saturn_save_menu_draw_frame(void)
{
    u32 slot;
    u32 i;

    for (slot = 0; slot < SAVE_SLOT_COUNT; slot++) {
        u8* record = saturn_save_slots + (s8)(slot * SAVE_SLOT_BYTES);
        u8* icons = saturn_save_icons[slot];
        const u8* frames = save_upgrade_frames[record[0] != 0];
        u16 items = *(u16*)(record + SAVE_RECORD_ITEMS);
        s32 count = 0;

        for (i = 0; i < SAVE_ICON_UPGRADES; i++) {
            if (record[SAVE_RECORD_UPGRADES] & save_upgrade_masks[i]) {
                icons[count++] = frames[i];
            }
        }
        while (count < SAVE_ICON_UPGRADES) {
            icons[count++] = SAVE_ICON_NONE;
        }
        for (i = 0; i < 8; i++) {
            if (items & save_tank_masks[i]) {
                icons[count++] = SAVE_ICON_TANK;
            }
        }
        while (count < SAVE_ICON_TANKS) {
            icons[count++] = SAVE_ICON_NONE;
        }
        for (i = 0; i < 4; i++) {
            if (items & save_armor_masks[i]) {
                icons[count++] = save_armor_frames[i][0];
                icons[count++] = save_armor_frames[i][1];
            }
        }
        while (count < SAVE_ICON_SLOTS) {
            icons[count++] = SAVE_ICON_NONE;
        }
    }
}

static void save_menu_draw_failure(u8 frame)
{
    save_menu_label(62, 16, SAVE_ROW_NONE);
    save_menu_label(77, 64, SAVE_ROW_NONE);
    save_menu_label(frame, 80, SAVE_ROW_NONE);
    save_menu_label(63, 0xD0, SAVE_ROW_NONE);
}

static u8 save_menu_device_label(void)
{
    return saturn_save_device * 3 + saturn_save_slot + 35;
}

static struct MiscObj* save_menu_marker(s16 x, s16 y)
{
    struct MiscObj* obj = find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->id = SAVE_LABEL_OBJECT;
        obj->unk2 = SAVE_MARKER_KIND;
        obj->x_pos.i.hi = x;
        obj->y_pos.i.hi = y;
    }
    return obj;
}

static void save_menu_draw_prompt(u8 load)
{
    save_menu_label(load ? 8 : 50, 16, SAVE_ROW_NONE);
    save_menu_label(save_menu_device_label(), 48, SAVE_ROW_NONE);
    if (saturn_save_slots[(s8)(saturn_main_bss_bytes[SAVE_SELECTION] * SAVE_SLOT_BYTES)] != SAVE_SLOT_HIDDEN) {
        save_menu_label(load ? 32 : 55, 64, SAVE_ROW_NONE);
    } else {
        save_menu_label(93, 0x80, SAVE_ROW_NONE);
        save_menu_label(55, 64, SAVE_ROW_NONE);
    }
    save_menu_label(33, 112, 0);
    save_menu_label(34, 0x90, 1);
    save_menu_label(7, 0xD0, SAVE_ROW_NONE);
    save_menu_marker(SAVE_SELECT_X, SAVE_SELECT_Y);
    saturn_main_bss_bytes[SAVE_SELECTION] = 0;
}

static void save_menu_draw_list(u8 load)
{
    struct MiscObj* marker;

    if (!load) {
        save_menu_label(50, 16, SAVE_ROW_NONE);
        save_menu_label(52, 64, SAVE_ROW_NONE);
        save_menu_label(116, 80, SAVE_ROW_NONE);
    } else {
        save_menu_label(8, 16, SAVE_ROW_NONE);
        save_menu_label(19, 64, SAVE_ROW_NONE);
    }
    save_menu_label(23, 0xB0, SAVE_SLOT_BACK);
    save_menu_label(saturn_save_device + 24, 48, SAVE_ROW_NONE);
    save_menu_label(20, 112, 0);
    save_menu_label(21, 128, 1);
    save_menu_label(22, 0x90, 2);
    save_menu_label(7, 0xD0, SAVE_ROW_NONE);
    save_menu_label(93, 0x80, 0x80);
    marker = save_menu_marker(SAVE_SELECT_X, SAVE_SELECT_Y);
    if (marker != NULL) {
        marker->animation_step.fields.frame_index = SAVE_MARKER_FRAME;
    }
    saturn_main_bss_bytes[SAVE_SELECTION] = saturn_save_slot;
}

static void save_menu_draw_devices(u8* menu, u8 load)
{
    u8 row = 0;
    u8 status;

    save_menu_label(load ? 8 : 50, 16, SAVE_ROW_NONE);
    save_menu_label(14, 48, SAVE_ROW_NONE);
    save_menu_label(10, 64, SAVE_ROW_NONE);
    status = saturn_backup_cart_status;
    if (!(status & SAVE_INTERNAL_ERROR)) {
        save_menu_label(15, 112, row++);
    } else if (!(status & SAVE_INTERNAL_FULL)) {
        save_menu_label(15, 112, load ? row++ : SAVE_ROW_DISABLED);
    }
    status = saturn_backup_cart_status;
    if (!(status & SAVE_CART_ERROR)) {
        save_menu_label(16, 0x90, row++);
    } else if (!(status & SAVE_CART_FULL)) {
        save_menu_label(16, 0x90, load ? row++ : SAVE_ROW_DISABLED);
    }
    menu[3] = row;
    save_menu_label(13, 0xB0, row);
    save_menu_label(7, 0xD0, SAVE_ROW_NONE);
    saturn_main_bss_bytes[SAVE_SELECTION] = 0;
    if (saturn_save_device != SAVE_DEVICE_INTERNAL && !(saturn_backup_cart_status & SAVE_DEVICE_ERRORS)) {
        saturn_main_bss_bytes[SAVE_SELECTION] = 1;
    }
}

void saturn_save_menu_draw_slots(u8* menu, s32 mode)
{
    u8 load = saturn_main_bss_bytes[SAVE_LOAD_MODE];

    saturn_save_draw_mode = mode;
    saturn_save_cursor = NULL;
    switch ((u8)mode) {
    case SAVE_SLOTS_IDLE:
        save_menu_draw_devices(menu, load);
        break;
    case SAVE_SLOTS_LIST:
        save_menu_draw_list(load);
        break;
    case SAVE_SLOTS_PROMPT:
        save_menu_draw_prompt(load);
        break;
    case SAVE_SLOTS_SAVED:
        save_menu_label(50, 16, SAVE_ROW_NONE);
        save_menu_label(save_menu_device_label(), 48, SAVE_ROW_NONE);
        save_menu_label(57, 0xA0, SAVE_ROW_NONE);
        save_menu_marker(0xA0, 0x78);
        break;
    case SAVE_SLOTS_FAILED:
        save_menu_draw_failure(75);
        break;
    case SAVE_SLOTS_LOAD_FAILED:
        save_menu_draw_failure(74);
        break;
    }
}

void saturn_save_capture_slot(void)
{
    u32 i;
    u8* record = saturn_save_slots + (s8)(saturn_save_slot * SAVE_SLOT_BYTES);
    record[0] = saturn_engine_bytes[0x43];
    record[0x24] = saturn_engine_bytes[0x59];
    record[0x25] = saturn_engine_bytes[0x5F];
    *(u16*)(record + 0x22) = *(u16*)(saturn_engine_bytes + 0x5A);
    record[0x26] = saturn_engine_bytes[0x47];
    record[0x27] = saturn_engine_bytes[0x48];
    record[0x28] = saturn_engine_bytes[0x46];
    record[0x29] = saturn_engine_bytes[0x37];
    record[1] = saturn_sound_output;
    for (i = 0; i < SAVE_BUTTON_MASKS; i++) {
        ((u16*)(record + 2))[i] = saturn_button_masks[i];
    }
    saturn_save_capture_options();
}

static void save_restore(u8* record, u8* engine)
{
    u32 i;
    engine[0x43] = record[0];
    engine[0x59] = record[0x24];
    engine[0x5F] = record[0x25];
    *(u16*)(engine + 0x5A) = *(u16*)(record + 0x22);
    engine[0x47] = record[0x26];
    engine[0x48] = record[0x27];
    engine[0x46] = record[0x28];
    engine[0x37] = record[0x29];
    for (i = 0; i < SAVE_BUTTON_MASKS; i++) {
        saturn_button_masks[i] = ((u16*)(record + 2))[i];
    }
}

void saturn_save_load(struct MemcardSaveSlot* save, s32 mode)
{
    u8* record = (u8*)save;
    u8* options;
    u32 i;
    save_restore(record, saturn_engine_bytes);
    if ((u8)mode != 0) {
        options = saturn_save_options;
        options[0] = record[0];
        options[0x24] = record[0x24];
        options[0x25] = record[0x25];
        *(u16*)(options + 0x22) = *(u16*)(record + 0x22);
        options[0x26] = record[0x26];
        options[0x27] = record[0x27];
        options[0x28] = record[0x28];
        options[0x29] = record[0x29];
        options[1] = record[1];
        for (i = 0; i < SAVE_BUTTON_MASKS; i++) {
            ((u16*)(options + 2))[i] = ((u16*)(record + 2))[i];
        }
    }
    saturn_engine_bytes[ENGINE_LIVES] = (*(u16*)(record + 0x22) & SAVE_LIVES_MASK) ? SAVE_LIVES_FLAG : SAVE_LIVES_DEFAULT;
    saturn_engine_bytes[ENGINE_HP_DISPLAY] = 0;
    saturn_engine_bytes[ENGINE_HP_DISPLAY + 1] = 0;
    saturn_engine_bytes[ENGINE_HP_DISPLAY + 2] = 0;
}
