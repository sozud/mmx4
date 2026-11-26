// saturn-capability: sh2_dma
#ifdef MMX4_SATURN
#include "test_runtime.h"
#include "support/test_pad.h"
#include "main/pause_menu.h"
#include "saturn/platform.h"
#include "saturn/game_low.h"

#define PAUSE_OBSERVED 26

extern struct BarObj bar_object;
extern u16 saturn_vdp2_shadow[];
extern u16 saturn_color_ram_shadow[];
extern u16 saturn_pause_palette_save[];
extern u16 saturn_pause_shadow_save[];
extern u8 saturn_pause_sprite_counts_save[];
extern u32 saturn_pause_sprite_lists_save[];
extern u8 saturn_sprite_list_counts[];
extern u32 saturn_sprite_object_lists[];
extern u8 saturn_pause_weapon;

#define DEBUG_TEXT_BYTES 0x2000

struct PauseCase {
    u8 state, unk5, unk6, unk2;
    s8 unk14;
    u8 calls;
    u16 pad;
    u16 items;
    u8 player_unk2;
    s8 ride_state;
    u8 stage, checkpoint;
    u16 upgrades;
    u8 boss_flags, armor_parts, palette_flags;
    s8 weapon;
    s8 tanks[3];
    s8 hp, max_hp;
    s8 energy;
    s32 unk28, unk2C, unk30;
    u8 transition, latch, request;
    u32 frame;
};

static u8 sound_queue[0x800] __attribute__((aligned(4)));

static u32 hash(const void* data, u32 bytes)
{
    const u8* b = data;
    u32 h = 2166136261u, i;
    for (i = 0; i < bytes; i++)
        h = (h ^ b[i]) * 16777619u;
    return h;
}

static void seed(void* data, u32 bytes, u8 value)
{
    u8* b = data;
    u32 i;
    for (i = 0; i < bytes; i++)
        b[i] = (u8)(value + i * 7);
}

static void pause_setup(const struct PauseCase* c)
{
    u32 i;
    memset(&bar_object, 0, sizeof(bar_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    seed(saturn_vdp2_shadow, 0x100, 0x11);
    seed(saturn_color_ram_shadow, 0x400, 0x23);
    memset(saturn_pause_palette_save, 0, 0x400);
    memset(saturn_pause_shadow_save, 0, 0x120);
    memset(saturn_pause_sprite_counts_save, 0, 20);
    memset(saturn_pause_sprite_lists_save, 0, 0x280);
    memset((void*)saturn_sprite_list_counts, 0, 20);
    memset((void*)saturn_sprite_object_lists, 0, 0xC00);
    memset(sound_queue, 0, sizeof(sound_queue));
    memset(saturn_sound_requests, 0, sizeof(saturn_sound_requests));
    memset(saturn_sound_effect_requests, 0, sizeof(saturn_sound_effect_requests));
    memset(saturn_sound_channel_effects, 0, sizeof(saturn_sound_channel_effects));
    saturn_sound_request_read = saturn_sound_request_write = 0;
    saturn_sound_effect_request_read = saturn_sound_effect_request_write = 0;
    saturn_sound_last_group = -1;
    memset(saturn_debug_text, 0, DEBUG_TEXT_BYTES);
    saturn_sound_driver_area = NULL;
    saturn_sound_command_queue = sound_queue;
    saturn_sound_command_slot = sound_queue;
    saturn_debug_column = saturn_debug_row = saturn_debug_margin = saturn_debug_top = 0;
    saturn_text_dirty_b = 0;
    saturn_pause_weapon = 0;
    saturn_pause_latch = c->latch;
    saturn_pause_request = c->request;
    saturn_pad_pressed = c->pad;
    bar_object.state = c->state;
    bar_object.unk5 = c->unk5;
    bar_object.unk6 = c->unk6;
    bar_object.unk2 = c->unk2;
    bar_object.unk14 = c->unk14;
    bar_object.unk28 = c->unk28;
    bar_object.unk2C = c->unk2C;
    bar_object.unk30 = c->unk30;
    for (i = 0; i < 15; i++)
        bar_object.options.items[i] = (c->items >> i) & 1;
    g_Player.unk2 = c->player_unk2;
    g_Player.ride_state = c->ride_state;
    g_Player.boss_flags = c->boss_flags;
    g_Player.armor_parts = c->armor_parts;
    g_Player.weapon = c->weapon;
    g_Player.hp = c->hp;
    for (i = 0; i < 9; i++)
        g_Player.weapon_energy[i] = c->energy + (s8)i;
    engine_obj.stage = c->stage;
    engine_obj.checkpoint = c->checkpoint;
    engine_obj.collected_upgrades = c->upgrades;
    engine_obj.palette_flags = c->palette_flags;
    engine_obj.max_hp = c->max_hp;
    for (i = 0; i < 3; i++)
        engine_obj.sub_tanks[i] = c->tanks[i];
    main_bss_state.frame_counter = c->frame;
    main_bss_state.transition.active = c->transition;
}

static void pause_observe(u32* observed)
{
    u32 i;
    for (i = 0; i < 13; i++)
        observed[i] = ((u32*)&bar_object)[i];
    observed[13] = (u8)g_Player.weapon | (u32)(u8)g_Player.hp << 8 | (u32)(u8)g_Player.unk2 << 16 | (u32)(u8)engine_obj.max_hp << 24;
    observed[14] = (u8)engine_obj.sub_tanks[0] | (u32)(u8)engine_obj.sub_tanks[1] << 8 | (u32)(u8)engine_obj.sub_tanks[2] << 16;
    observed[15] = hash(g_Player.weapon_energy, sizeof(g_Player.weapon_energy));
    observed[16] = hash(&engine_obj, sizeof(engine_obj));
    observed[17] = hash(&g_Player, sizeof(g_Player));
    observed[18] = hash(saturn_vdp2_shadow, 0x100);
    observed[19] = hash(saturn_color_ram_shadow, 0x400);
    observed[20] = hash(saturn_pause_palette_save, 0x400) ^ hash(saturn_pause_shadow_save, 0x120)
        ^ hash(saturn_pause_sprite_counts_save, 20) ^ hash(saturn_pause_sprite_lists_save, 0x280);
    observed[21] = hash(sound_queue, sizeof(sound_queue)) ^ hash(saturn_sound_requests, sizeof(saturn_sound_requests))
        ^ hash(saturn_sound_effect_requests, sizeof(saturn_sound_effect_requests))
        ^ hash(saturn_sound_channel_effects, sizeof(saturn_sound_channel_effects))
        ^ (u32)saturn_sound_request_write << 8 ^ (u32)saturn_sound_effect_request_write << 16
        ^ (u32)(saturn_sound_command_slot - (volatile u8*)sound_queue);
    observed[22] = saturn_pause_weapon | (u32)(u8)saturn_pause_latch << 8 | (u32)saturn_text_dirty_b << 16 | (u32)(u8)saturn_pause_request << 24;
    observed[23] = hash(&main_bss_state, sizeof(main_bss_state));
    observed[24] = hash(saturn_debug_text, DEBUG_TEXT_BYTES);
    observed[25] = saturn_debug_column | saturn_debug_row << 8 | saturn_debug_margin << 16 | saturn_debug_top << 24;
}

static const struct PauseCase pause_cases[] = {
    { .state = 0, .unk5 = 0 },
    { .state = 0, .unk5 = 1, .transition = 1 },
    { .state = 0, .unk5 = 1, .stage = 3, .upgrades = 0x1000, .boss_flags = 0xA5, .armor_parts = 0x02, .palette_flags = 0x04, .weapon = 3 },
    { .state = 0, .unk5 = 2, .transition = 1 },
    { .state = 0, .unk5 = 2 },
    { .state = 0, .unk5 = 2, .latch = 1 },
    { .state = 1, .unk5 = 0, .unk14 = 5, .items = 0x7FFF },
    { .state = 1, .unk5 = 0, .unk14 = 4, .pad = 0x0800, .items = 0x7FFF },
    { .state = 1, .unk5 = 0, .unk14 = 6, .pad = 0x0200, .items = 0x7FFF },
    { .state = 1, .unk5 = 0, .unk14 = 6, .pad = 0x0400, .items = 0x7FFF },
    { .state = 1, .unk5 = 0, .unk14 = 7, .pad = 0x1000, .items = 0x7FFF },
    { .state = 1, .unk5 = 0, .unk14 = 2, .pad = 0x2000, .items = 0x7FFF },
    { .state = 1, .unk5 = 0, .unk14 = 2, .pad = 0x8000, .items = 0x7FFF },
    { .state = 1, .unk5 = 0, .unk14 = 3, .pad = 0x4000, .items = 0x7FFF },
    { .state = 1, .unk5 = 1, .unk14 = 10, .pad = 0x0800, .items = 0x7FFF },
    { .state = 1, .unk5 = 1, .unk14 = 10, .pad = 0x0200, .items = 0x7FFF, .tanks = { 32, 0, 0 } },
    { .state = 1, .unk5 = 1, .unk14 = 12, .pad = 0x0400, .items = 0x7FFF, .tanks = { 0, 0, 32 } },
    { .state = 1, .unk5 = 1, .unk14 = 11, .pad = 0x1000, .items = 0x7FFF },
    { .state = 1, .unk5 = 1, .unk14 = 10, .pad = 0x8000, .items = 0x7FFF },
    { .state = 1, .unk5 = 1, .unk14 = 11, .pad = 0x4000, .items = 0x7FFF },
    { .state = 1, .unk5 = 2, .unk14 = 13, .pad = 0x0800, .items = 0x7FFF },
    { .state = 1, .unk5 = 2, .unk14 = 13, .pad = 0x0200, .items = 0x7FFF },
    { .state = 1, .unk5 = 2, .unk14 = 14, .pad = 0x0400, .items = 0x7FFF },
    { .state = 1, .unk5 = 2, .unk14 = 14, .pad = 0x1000, .items = 0x7FFF },
    { .state = 1, .unk5 = 2, .unk14 = 13, .pad = 0x2000, .items = 0x7FFF },
    { .state = 1, .unk5 = 2, .unk14 = 13, .pad = 0x4000, .items = 0x7FFF },
    { .state = 1, .unk5 = 3, .unk14 = 10, .tanks = { 7, 0, 0 }, .hp = 12, .max_hp = 32, .frame = 0 },
    { .state = 1, .unk5 = 4, .tanks = { 0, 0, 9 }, .energy = 10, .frame = 0 },
    { .state = 1, .unk5 = 5, .unk6 = 0 },
    { .state = 1, .unk5 = 5, .unk6 = 1, .transition = 1 },
    { .state = 1, .unk5 = 5, .unk6 = 1 },
    { .state = 1, .unk5 = 5, .unk6 = 3 },
    { .state = 1, .unk5 = 5, .unk6 = 4, .transition = 1 },
    { .state = 1, .unk5 = 5, .unk6 = 4 },
    { .state = 1, .unk5 = 6, .unk6 = 0 },
    { .state = 1, .unk5 = 6, .unk6 = 1, .unk28 = 5 },
    { .state = 1, .unk5 = 6, .unk6 = 1, .unk28 = 1 },
    { .state = 1, .unk5 = 6, .unk6 = 2, .unk28 = 5 },
    { .state = 1, .unk5 = 6, .unk6 = 2, .unk28 = 1 },
    { .state = 1, .unk5 = 6, .unk6 = 3, .pad = 0x0800 },
    { .state = 1, .unk5 = 6, .unk6 = 3, .pad = 0x0800, .request = 1 },
    { .state = 1, .unk5 = 6, .unk6 = 3, .pad = 0x0200 },
    { .state = 1, .unk5 = 6, .unk6 = 4, .unk28 = 5 },
    { .state = 1, .unk5 = 6, .unk6 = 4, .unk28 = 1 },
    { .state = 1, .unk5 = 6, .unk6 = 5, .unk28 = 5 },
    { .state = 1, .unk5 = 6, .unk6 = 5, .unk28 = 1, .request = 1 },
    { .state = 1, .unk5 = 6, .unk6 = 6 },
    { .state = 1, .unk5 = 6, .unk6 = 0, .calls = 40 },
    { .state = 2, .unk5 = 0 },
    { .state = 2, .unk5 = 1, .transition = 1 },
    { .state = 2, .unk5 = 1 },
    { .state = 2, .unk5 = 2, .weapon = 3 },
    { .state = 2, .unk5 = 2, .weapon = 0 },
    { .state = 2, .unk5 = 2, .player_unk2 = 1, .weapon = 3 },
    { .state = 2, .unk5 = 2, .unk30 = 1 },
    { .state = 2, .unk5 = 3, .transition = 1 },
    { .state = 2, .unk5 = 3 },
    { .state = 2, .unk5 = 3, .unk30 = 1 },
    { .state = 2, .unk5 = 3, .ride_state = -1, .stage = 5, .checkpoint = 0 },
    { .state = 2, .unk5 = 3, .ride_state = 0, .stage = 5, .checkpoint = 0 },
    { .state = 1, .unk5 = 1, .unk14 = 10, .pad = TEST_PAD_UP, .items = 0x7C01 },
    { .state = 1, .unk5 = 1, .unk14 = 12, .pad = TEST_PAD_RIGHT, .items = 0x5FFF },
    { .state = 1, .unk5 = 2, .unk14 = 13, .items = 0x7FFF },
    { .state = 1, .unk5 = 2, .unk14 = 13, .pad = TEST_PAD_UP, .items = 0x7C01 },
    { .state = 1, .unk5 = 2, .unk14 = 13, .pad = TEST_PAD_UP, .items = 0x7FFE, .player_unk2 = 1 },
    { .state = 1, .unk5 = 2, .unk2 = 1, .unk14 = 14, .pad = TEST_PAD_UP, .items = 0x5FFF },
    { .state = 1, .unk5 = 2, .unk14 = 14, .pad = TEST_PAD_DOWN, .items = 0x7FFF },
    { .state = 1, .unk5 = 2, .unk14 = 13, .pad = TEST_PAD_LEFT, .items = 0x6FFF },
    { .state = 1, .unk5 = 2, .unk14 = 13, .pad = TEST_PAD_LEFT, .items = 0x6FFF, .player_unk2 = 1 },
    { .state = 1, .unk5 = 2, .unk2 = 1, .unk14 = 13, .pad = TEST_PAD_LEFT, .items = 0x6401 },
    { .state = 1, .unk5 = 2, .unk2 = 1, .unk14 = 13, .pad = TEST_PAD_LEFT, .items = 0x6001 },
    { .state = 1, .unk5 = 4, .unk2C = 1, .tanks = { 0, 0, 9 }, .energy = 10, .frame = 0 },
    { .state = 1, .unk5 = 4, .tanks = { 0, 0, 9 }, .energy = 47, .frame = 0 },
    { .state = 0, .unk5 = 1, .player_unk2 = 1, .boss_flags = 0x5A, .upgrades = 0xE000 },
    { .state = 0, .unk5 = 1, .stage = 5, .checkpoint = 0, .boss_flags = 0x01 },
    { .state = 0, .unk5 = 1, .ride_state = -1, .stage = 0, .upgrades = 0x1000 },
    { .state = 0, .unk5 = 2, .unk2 = 1, .unk14 = 10 },
    { .state = 1, .unk5 = 0, .unk14 = 1, .pad = 0x0200, .items = 0x7FFF, .weapon = 4 },
    { .state = 1, .unk5 = 0, .unk14 = 1, .pad = 0x1000, .items = 0x7FFF },
    { .state = 1, .unk5 = 0, .unk14 = 8, .pad = 0x2000, .items = 0x7FFF },
    { .state = 1, .unk5 = 0, .unk14 = 8, .pad = 0x2000, .items = 0x03FF },
    { .state = 1, .unk5 = 0, .unk14 = 3, .pad = 0x8000, .items = 0x7FFF },
    { .state = 1, .unk5 = 0, .unk14 = 2, .pad = 0x8000, .items = 0x7FF7 },
    { .state = 1, .unk5 = 0, .unk14 = 6, .pad = 0x8000, .items = 0x7D7F },
    { .state = 1, .unk5 = 0, .unk14 = 5, .pad = 0x4000, .items = 0x7FEF },
    { .state = 1, .unk5 = 0, .unk14 = 5, .pad = 0x4000, .items = 0x7FEA },
    { .state = 1, .unk5 = 1, .unk14 = 11, .pad = 0x0200, .items = 0x7FFF, .tanks = { 0, 32, 0 } },
    { .state = 1, .unk5 = 1, .unk14 = 10, .pad = 0x4000, .items = 0x7FFF },
    { .state = 1, .unk5 = 3, .unk14 = 10, .tanks = { 3, 0, 0 }, .hp = 32, .max_hp = 32, .frame = 0 },
    { .state = 1, .unk5 = 3, .unk14 = 10, .tanks = { 0, -123, 0 }, .hp = 12, .max_hp = 32 },
    { .state = 1, .unk5 = 3, .unk14 = 10, .unk28 = 1, .tanks = { 4, 0, 0 }, .hp = 32, .max_hp = 32, .frame = 2 },
    { .state = 1, .unk5 = 3, .unk14 = 10, .unk28 = 1, .tanks = { 0, 0, 0 }, .hp = 10, .max_hp = 32, .frame = 0 },
    { .state = 1, .unk5 = 3, .unk14 = 10, .unk28 = 1, .tanks = { 0, -123, 0 }, .hp = 32, .max_hp = 32, .frame = 2 },
    { .state = 1, .unk5 = 4, .unk2C = 1, .tanks = { 0, 0, 9 }, .energy = 48, .frame = 0 },
    { .state = 1, .unk5 = 4, .unk2C = 1, .tanks = { 0, 0, 0 }, .energy = 48, .frame = 0 },
};

static const u32 pause_expected[][PAUSE_OBSERVED] = {
#include "pause_menu_saturn_expected.inc"
};

static u32 test_pause(u32 row)
{
    const struct PauseCase* c = &pause_cases[row];
    u32 observed[PAUSE_OBSERVED];
    u32 i;
    pause_setup(c);
    for (i = 0; i < (c->calls ? c->calls : 1); i++)
        func_8002FCAC();
    pause_observe(observed);
    return c_test_observe(0, row, observed, row < COUNT(pause_expected) ? pause_expected[row] : pause_expected[0],
        PAUSE_OBSERVED);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_pause_states", 0, 0, COUNT(pause_cases), test_pause },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pause_cases);
#else
#include "test_runtime.h"
#include "main/pause_menu.h"
#include "main/144A4.h"
#include "main/55C4.h"
#include "main/player_animations.h"
#include "main/player_common.h"
void func_80030DF8(struct BarObj*);
void func_80030EC8(struct BarObj*);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern struct BgDrawRelated D_8015D9D0[2];
extern struct SecondaryPrimitiveBuffer temp2[2];
extern u8 D_8013B818[0x10];

static struct DrawInfo pause_action_selection_drawing;
static u16 pause_action_selection_tiles[512];
static u16 pause_action_selection_title_frames[0x400];

static u32 action_case(u32 mode, u32 observation)
{
    struct BarObj* obj = &bar_object;
    struct BarObj before;
    struct PlayerObj player_before;
    struct ControllerInput input_before;
    u8* bytes = (u8*)obj;
    u32 i, actual;
    memset(obj, 0, sizeof(*obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    obj->state = 1;
    obj->unk5 = 2;
    obj->unk6 = 9;
    obj->unk14 = 13;
    obj->unk28 = 0x12345678;
    obj->unk2C = 0x24681357;
    g_Player.hp = 16;
    g_Player.bg_offset = -1;
    g_Player.weapon = 5;
    engine_obj.cur_character = 1;
    switch (mode) {
    case 0:
        controller_input.pressed = 0x8800;
        break;
    case 1:
        controller_input.pressed = PAD_CONFIRM;
        break;
    case 2:
        controller_input.pressed = 0x2000;
        break;
    case 3:
        controller_input.pressed = 0x3000;
        break;
    case 4:
        controller_input.pressed = 0x5000;
        break;
    case 5:
        controller_input.pressed = 0x1000;
        g_Player.unk2 = 1;
        bytes[0x16 + 13] = 1;
        break;
    case 6:
        controller_input.pressed = 0x1000;
        g_Player.unk2 = 1;
        obj->unk14 = 14;
        break;
    case 7:
        controller_input.pressed = 0x1000;
        g_Player.unk2 = 1;
        obj->unk14 = 15;
        bytes[0x16 + 14] = 1;
        break;
    case 8:
        controller_input.pressed = 0x1000;
        obj->unk2 = 1;
        bytes[0x16 + 13] = 1;
        break;
    case 9:
        controller_input.pressed = 0x1000;
        obj->unk14 = 14;
        bytes[0x16 + 13] = 1;
        break;
    case 10:
        controller_input.pressed = 0x1000;
        obj->unk14 = 14;
        break;
    case 11:
        controller_input.pressed = 0x1000;
        obj->unk14 = 14;
        bytes[0x16 + 5] = 1;
        break;
    case 12:
        controller_input.pressed = 0x4000;
        bytes[0x16 + 14] = 1;
        break;
    case 13:
        controller_input.pressed = 0x4000;
        break;
    case 14:
        controller_input.pressed = 0x8000;
        g_Player.unk2 = 1;
        bytes[0x16 + 12] = 1;
        break;
    case 15:
        controller_input.pressed = 0x8000;
        g_Player.unk2 = 1;
        break;
    case 16:
        controller_input.pressed = 0x8000;
        obj->unk2 = 1;
        bytes[0x16 + 10] = 1;
        break;
    case 17:
        controller_input.pressed = 0x8000;
        bytes[0x16 + 8] = 1;
        break;
    case 18:
        controller_input.pressed = PAD_CONFIRM;
        obj->unk14 = 14;
        break;
    case 19:
        controller_input.pressed = 0x8000;
        bytes[0x16 + 12] = 1;
        break;
    default:
        controller_input.pressed = 0x8000;
        break;
    }
    before = *obj;
    player_before = g_Player;
    input_before = controller_input;
    D_8013E198[0] = -1;
    if (mode == 18) {
        memset(&pause_action_selection_drawing, 0, sizeof(pause_action_selection_drawing));
        memset(pause_action_selection_tiles, 0, sizeof(pause_action_selection_tiles));
        memset(pause_action_selection_title_frames, 0, sizeof(pause_action_selection_title_frames));
        memset(&temp1[0].data[0], 0, 4 * sizeof(temp1[0].data[0]));
        memset(&temp2[0].data[0], 0, 4 * sizeof(temp2[0].data[0]));
        memset(&D_8015D9D0[0].sprites[0], 0, 320 * sizeof(D_8015D9D0[0].sprites[0]));
        SP_DRAW_BUFFER = 0;
        TEST_ARC_34 = (u8*)pause_action_selection_tiles;
        TEST_TITLE_FRAMES = (u8*)pause_action_selection_title_frames;
        cur_draw_info = &pause_action_selection_drawing;
    }
    func_80030728(obj);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(controller_input); i++)
        assert(((u8*)&controller_input)[i] == ((u8*)&input_before)[i]);
    before.state = obj->state;
    before.unk5 = obj->unk5;
    before.unk6 = obj->unk6;
    before.unk14 = obj->unk14;
    before.unk30 = obj->unk30;
    for (i = 0; i < sizeof(*obj) / 4; i++)
        assert(((u32*)obj)[i] == ((u32*)&before)[i]);
    if (observation == 0)
        actual = (u8)obj->state | ((u32)(u8)obj->unk5 << 8) | ((u32)(u8)obj->unk6 << 16) | ((u32)(u8)obj->unk14 << 24);
    else
        actual = obj->unk30;
    return actual;
}
static const u32 pause_action_selection_cases_expected[] = { 0xD090002u, 0x0u, 0xD090002u, 0x1u, 0xD090201u, 0x0u, 0xD090201u, 0x0u, 0xD090201u, 0x0u, 0xD090201u, 0x0u, 0xE090201u, 0x0u, 0xE090201u, 0x0u, 0xD090201u, 0x0u, 0xD090201u, 0x0u, 0x90001u, 0x0u, 0x5090001u, 0x0u, 0xE090201u, 0x0u, 0xE090201u, 0x0u, 0xC090101u, 0x0u, 0xD090201u, 0x0u, 0xA090101u, 0x0u, 0x8090001u, 0x0u, 0xE000501u, 0x0u, 0xC090101u, 0x0u, 0x90001u, 0x0u };
static u32 pause_action_selection_cases_row(u32 row)
{
    return action_case(row / 2, row % 2);
}

static u32 image[256];

static u32 availability_case(u32 mode, u32 observation)
{
    struct BarObj obj;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 i, actual;
    memset(&obj, 0x5A, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    engine_obj.sub_tanks[0] = 0x11;
    engine_obj.sub_tanks[1] = 0x12;
    engine_obj.sub_tanks[2] = 0x13;
    g_Player.hp = 16;
    g_Player.bg_offset = -1;
    g_Player.boss_flags = mode & 1 ? 0xAA : 0x55;
    switch (mode) {
    case 0:
        engine_obj.stage = 0;
        break;
    case 1:
        engine_obj.stage = 5;
        engine_obj.checkpoint = 0;
        g_Player.armor_parts = 2;
        g_Player.weapon = 5;
        engine_obj.collected_upgrades = 0xF000;
        engine_obj.palette_flags = 0x10;
        break;
    case 2:
        g_Player.unk2 = 1;
        engine_obj.stage = 3;
        engine_obj.checkpoint = 1;
        engine_obj.collected_upgrades = 0x2000;
        break;
    case 3:
        engine_obj.stage = 8;
        engine_obj.checkpoint = 1;
        g_Player.ride_state = -1;
        engine_obj.collected_upgrades = 0x1000;
        break;
    case 4:
        engine_obj.stage = 3;
        engine_obj.checkpoint = 1;
        g_Player.weapon = 5;
        engine_obj.collected_upgrades = 0x4000;
        engine_obj.palette_flags = 4;
        break;
    case 5:
        g_Player.unk2 = 1;
        engine_obj.stage = 1;
        engine_obj.checkpoint = 1;
        break;
    case 6:
        engine_obj.stage = 5;
        engine_obj.checkpoint = 1;
        break;
    default:
        engine_obj.stage = 5;
        engine_obj.checkpoint = 0;
        break;
    }
    player_before = g_Player;
    engine_before = engine_obj;
    TEST_VRAM_IMAGE = (u8*)image;
    func_8002FD70(&obj);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    engine_before.sub_tanks[0] = engine_obj.sub_tanks[0];
    engine_before.sub_tanks[1] = engine_obj.sub_tanks[1];
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    assert(sizeof(struct BarObj) == 0x34);
    if (observation < 13)
        actual = ((u32*)&obj)[observation];
    else if (observation == 13)
        actual = (u8)engine_obj.sub_tanks[0] | ((u32)(u8)engine_obj.sub_tanks[1] << 8) | ((u32)(u8)engine_obj.sub_tanks[2] << 16) | ((u32)D_8013B818[0] << 24);
    else if (observation == 14)
        actual = (u8)main_bss_state.transition.active | ((u32)(u8)main_bss_state.transition.fade_amount << 8) | ((u32)(u8)main_bss_state.transition.selection << 16);
    else {
#ifdef MMX4_PC
        actual = mmx4_pc_thread_slot(2)->state;
#else
        actual = ((struct GameThread*)0x801F8200)->state;
#endif
    }
    return actual;
}
static const u32 pause_availability_cases_expected[] = { 0x5A005A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A00u, 0x10001u, 0x10001u, 0x5A000000u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x131211u, 0x801u, 0x2u, 0x5A015A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x1015A0Au, 0x1000100u, 0x1000100u, 0x1010101u, 0x5A5A0101u, 0x0u, 0x0u, 0x0u, 0x5139291u, 0x801u, 0x2u, 0x5A5A5A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x1005A0Bu, 0x1000101u, 0x5A0000u, 0x100u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x139211u, 0x801u, 0x2u, 0x5A015A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A0Au, 0x1000100u, 0x1000100u, 0x5A01u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x131291u, 0x801u, 0x2u, 0x5A005A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A06u, 0x10001u, 0x10001u, 0x1010000u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x5131211u, 0x801u, 0x2u, 0x5A5A5A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A0Eu, 0x10000u, 0x5A0101u, 0x0u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x131211u, 0x801u, 0x2u, 0x5A005A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A00u, 0x10001u, 0x10001u, 0x0u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x131211u, 0x801u, 0x2u, 0x5A015A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A0Eu, 0x1000100u, 0x1000100u, 0x0u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x131211u, 0x801u, 0x2u };
static u32 pause_availability_cases_row(u32 row)
{
    return availability_case(row / 16, row % 16);
}

static void assert_preserved(const void* actual, const void* before, u32 size)
{
    const u8* a = actual;
    const u8* b = before;
    u32 i;
    for (i = 0; i < size; i++)
        assert(a[i] == b[i]);
}

static u32 navigation_case(u32 mode, u32 observation)
{
    struct BarObj obj, before;
    struct PlayerObj player_before;
    struct ControllerInput input_before;
    u8* bytes = (u8*)&obj;
    u32 actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&controller_input, 0, sizeof(controller_input));
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk30 = 0x12345678;
    g_Player.hp = 16;
    g_Player.bg_offset = -1;
    g_Player.weapon = 5;
    controller_input.held = 0x55;
    switch (mode) {
    case 0:
        obj.unk14 = 4;
        controller_input.pressed = 0x3000;
        break;
    case 1:
        obj.unk14 = 4;
        controller_input.pressed = 0x5000;
        break;
    case 2:
        obj.unk14 = 8;
        controller_input.pressed = 0x4000;
        bytes[0x16 + 13] = 1;
        break;
    case 3:
        obj.unk14 = 0;
        controller_input.pressed = 0x2000;
        bytes[0x16 + 3] = 1;
        break;
    case 8:
        obj.unk14 = 11;
        controller_input.pressed = 0x3000;
        break;
    case 9:
        obj.unk14 = 11;
        controller_input.pressed = 0x5000;
        break;
    case 10:
        obj.unk14 = 9;
        controller_input.pressed = PAD_CONFIRM;
        break;
    default:
        obj.unk14 = 13;
        controller_input.pressed = PAD_CONFIRM;
        break;
    }
    if (mode >= 10) {
        obj.unk28 = 0x11223344;
        obj.unk2C = 0x55667788;
    }
    before = obj;
    player_before = g_Player;
    input_before = controller_input;
    D_8013E198[0] = -1;
    if (mode < 4)
        func_800301BC(&obj);
    else
        func_800304E4(&obj);
    assert_preserved(&g_Player, &player_before, sizeof(g_Player));
    assert_preserved(&controller_input, &input_before, sizeof(controller_input));
    before.state = obj.state;
    before.unk5 = obj.unk5;
    before.unk14 = obj.unk14;
    if (mode >= 10) {
        before.unk28 = obj.unk28;
        before.unk2C = obj.unk2C;
    }
    assert_preserved(&obj, &before, sizeof(obj));
    if (observation == 0)
        actual = (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.unk14 << 16);
    else if (observation == 1)
        actual = obj.unk28;
    else
        actual = obj.unk2C;
    return actual;
}
#define NAV_CASE(name, mode, observation)          \
    static u32 name(void)                          \
    {                                              \
        return navigation_case(mode, observation); \
    }
NAV_CASE(GRID_DEFAULT_MID_HEADER, 0, 0)
NAV_CASE(GRID_DEFAULT_HIGH_HEADER, 1, 0)
NAV_CASE(GRID_DOWN_ESCAPE_HEADER, 2, 0)
NAV_CASE(GRID_RIGHT_SPARSE_HEADER, 3, 0)
NAV_CASE(TANK_DEFAULT_MID_HEADER, 8, 0)
NAV_CASE(TANK_DEFAULT_HIGH_HEADER, 9, 0)
NAV_CASE(TANK_CONFIRM_LOW_DEFAULT_HEADER, 10, 0)
NAV_CASE(TANK_CONFIRM_LOW_DEFAULT_HEALTH_FLAG, 10, 1)
NAV_CASE(TANK_CONFIRM_LOW_DEFAULT_WEAPON_FLAG, 10, 2)
NAV_CASE(TANK_CONFIRM_HIGH_DEFAULT_HEADER, 11, 0)
NAV_CASE(TANK_CONFIRM_HIGH_DEFAULT_HEALTH_FLAG, 11, 1)
NAV_CASE(TANK_CONFIRM_HIGH_DEFAULT_WEAPON_FLAG, 11, 2)
static const CTestCase pause_navigation_edges_cases[] = {
    GRID_DEFAULT_MID_HEADER,
    GRID_DEFAULT_HIGH_HEADER,
    GRID_DOWN_ESCAPE_HEADER,
    GRID_RIGHT_SPARSE_HEADER,
    TANK_DEFAULT_MID_HEADER,
    TANK_DEFAULT_HIGH_HEADER,
    TANK_CONFIRM_LOW_DEFAULT_HEADER,
    TANK_CONFIRM_LOW_DEFAULT_HEALTH_FLAG,
    TANK_CONFIRM_LOW_DEFAULT_WEAPON_FLAG,
    TANK_CONFIRM_HIGH_DEFAULT_HEADER,
    TANK_CONFIRM_HIGH_DEFAULT_HEALTH_FLAG,
    TANK_CONFIRM_HIGH_DEFAULT_WEAPON_FLAG,
};
static const u32 pause_navigation_edges_cases_expected[] = { 0x40101u, 0x40101u, 0xD0201u, 0x30101u, 0xB0101u, 0xB0101u, 0x90101u, 0x0u, 0x0u, 0xD0101u, 0x0u, 0x0u };
#undef controller_input
#undef NAV_CASE

static struct DrawInfo pause_restricted_ready_drawing;
static u16 pause_restricted_ready_tiles[512];
static u16 pause_restricted_ready_title_frames[0x400];

static u32 pause_restricted(void)
{
    struct BarObj before;
    struct PlayerObj player_before;
    struct MainBssState main_before;
    u32 actual, i;
    memset(&bar_object, 0, sizeof(bar_object));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    bar_object.state = 0;
    bar_object.unk5 = 7;
    bar_object.unk6 = 0x35;
    bar_object.unk2 = 1;
    bar_object.unk14 = 13;
    g_Player.hp = 16;
    g_Player.bg_offset = -1;
    engine_obj.cur_character = 1;
    before = bar_object;
    player_before = g_Player;
    main_before = main_bss_state;
    memset(&pause_restricted_ready_drawing, 0, sizeof(pause_restricted_ready_drawing));
    memset(pause_restricted_ready_tiles, 0, sizeof(pause_restricted_ready_tiles));
    memset(pause_restricted_ready_title_frames, 0, sizeof(pause_restricted_ready_title_frames));
    memset(&temp1[0].data[0], 0, 4 * sizeof(temp1[0].data[0]));
    memset(&temp2[0].data[0], 0, 4 * sizeof(temp2[0].data[0]));
    memset(&D_8015D9D0[0].sprites[0], 0, 320 * sizeof(D_8015D9D0[0].sprites[0]));
    SP_DRAW_BUFFER = 0;
    TEST_ARC_34 = (u8*)pause_restricted_ready_tiles;
    TEST_TITLE_FRAMES = (u8*)pause_restricted_ready_title_frames;
    cur_draw_info = &pause_restricted_ready_drawing;
    func_800300AC(&bar_object);
    before.state = bar_object.state;
    before.unk5 = bar_object.unk5;
    for (i = 0; i < sizeof(before) / 4; i++)
        assert(((u32*)&bar_object)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(main_bss_state) / 4; i++)
        assert(((u32*)&main_bss_state)[i] == ((u32*)&main_before)[i]);
    actual = bar_object.state | ((u32)(u8)bar_object.unk5 << 8) | ((u32)(u8)bar_object.unk6 << 16) | ((u32)(u8)bar_object.unk14 << 24);
    return actual;
}
static const CTestCase pause_restricted_ready_cases[] = { pause_restricted };
static const u32 pause_restricted_ready_cases_expected[] = { 0xD350201u };
#undef controller_input
#undef main_bss_state

static u32 boundary(u32 observation)
{
    struct BarObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 i, actual = 0;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    obj.state = 1;
    obj.unk5 = 4;
    obj.unk14 = 12;
    obj.unk30 = 0x12345678;
    g_Player.hp = 16;
    g_Player.bg_offset = -1;
    for (i = 0; i < COUNT(g_Player.weapon_energy); i++)
        g_Player.weapon_energy[i] = i < 9 ? 47 : 0x55;
    engine_obj.sub_tanks[0] = 0x94;
    engine_obj.sub_tanks[1] = 0x83;
    engine_obj.sub_tanks[2] = 0x81;
    main_bss_state.frame_counter = 2;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    D_8013E198[0] = -1;
    func_80030C54(&obj);
    before.unk5 = obj.unk5;
    for (i = 0; i < 9; i++)
        player_before.weapon_energy[i] = g_Player.weapon_energy[i];
    for (i = 0; i < sizeof(obj); i++)
        assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj); i++)
        assert(((u8*)&engine_obj)[i] == ((u8*)&engine_before)[i]);
    assert(main_bss_state.frame_counter == 2);
    if (observation < 4) {
        for (i = 0; i < 4; i++)
            actual |= (u32)(u8)g_Player.weapon_energy[observation * 4 + i] << (i * 8);
    } else
        actual = (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)obj.unk14 << 16) | ((u32)(u8)engine_obj.sub_tanks[2] << 24);
    return actual;
}
static const u32 pause_weapon_boundary_cases_expected[] = { 0x30303030u, 0x30303030u, 0x55555530u, 0x55555555u, 0x810C0101u };

struct func_800301BC_case {
    u32 unk14, pressed;
    u32 expected[4];
};
static const struct func_800301BC_case func_800301BC_cases[] = {
    { 1, 8192, { 0u, 0u, 1u, 0u } },
    { 12, 64, { 0u, 0u, 0xCu, 0u } },
    { 6, 8192, { 0u, 0u, 6u, 0u } },
    { 3, 32768, { 0u, 0u, 3u, 0u } },
    { 10, 16384, { 0u, 0u, 0xEu, 0u } },
};
static u32 test_func_800301BC(u32 row)
{
    const struct func_800301BC_case* c = &func_800301BC_cases[row];
    u32 observed_values[4];
    struct BarObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk14 = c->unk14;
    controller_input.pressed = c->pressed;
    func_800301BC(&obj);
    observed_values[0] = (u32)g_Player.weapon;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk14;
    observed_values[3] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}
#undef controller_input

struct func_800304E4_case {
    u32 unk14, pressed, unk2;
    u32 expected[5];
};
static const struct func_800304E4_case func_800304E4_cases[] = {
    { 11, 64, 0, { 0u, 0xBu, 0u, 0u, 3u } },
    { 0, 4096, -1, { 0u, 0u, 0u, 0u, 0u } },
    { 12, 64, 0, { 0u, 0xCu, 0u, 0u, 4u } },
    { 11, 32768, 0, { 0u, 0xBu, 0u, 0u, 0u } },
    { -1, 4096, 0, { 0u, 0u, 0u, 0u, 0u } },
    { 11, 8192, 0, { 0u, 0xEu, 0u, 0u, 2u } },
};
static u32 test_func_800304E4(u32 row)
{
    const struct func_800304E4_case* c = &func_800304E4_cases[row];
    u32 observed_values[5];
    struct BarObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk14 = c->unk14;
    controller_input.pressed = c->pressed;
    obj.unk2 = c->unk2;
    func_800304E4(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk14;
    observed_values[2] = (u32)obj.unk28;
    observed_values[3] = (u32)obj.unk2C;
    observed_values[4] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 5);
}
#undef controller_input

struct func_80030A2C_case {
    u32 frame_counter, unk14, unk28, unk5C_1, hp, unk46;
    u32 expected[6];
};
static const struct func_80030A2C_case func_80030A2C_cases[] = {
    { 0, 0, 0, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 1u } },
    { 0, 10, 0, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 1u } },
    { 0, 0, -1032192, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 1u } },
    { 0, 10, 0, -128, 0, 0, { 0xFFFFFF80u, 0xFFFFFF80u, 0u, 0u, 0u, 1u } },
    { 0, 10, -1032192, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 1u } },
    { 2, -11, 0, 64, 127, 0, { 0u, 0xFFFFFFBFu, 0u, 0xFFFFFF80u, 0u, 0u } },
    { 0, -11, 0, 1, 0, 0, { 0u, 0xFFFFFF80u, 0u, 0u, 0u, 0u } },
    { 0, -11, -1032192, 0, 0, -128, { 0u, 0u, 0u, 0xFFFFFF80u, 0xFFF04000u, 0u } },
};
static u32 test_func_80030A2C(u32 row)
{
    const struct func_80030A2C_case* c = &func_80030A2C_cases[row];
    u32 observed_values[6];
    struct BarObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    main_bss_state.frame_counter = c->frame_counter;
    obj.unk14 = c->unk14;
    obj.unk28 = c->unk28;
    engine_obj.sub_tanks[1] = c->unk5C_1;
    engine_obj.sub_tanks[2] = 0;
    g_Player.hp = c->hp;
    engine_obj.max_hp = c->unk46;
    func_80030A2C(&obj);
    observed_values[0] = (u32)engine_obj.sub_tanks[0];
    observed_values[1] = (u32)engine_obj.sub_tanks[1];
    observed_values[2] = (u32)engine_obj.sub_tanks[2];
    observed_values[3] = (u32)g_Player.hp;
    observed_values[4] = (u32)obj.unk28;
    observed_values[5] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 6);
}
#undef main_bss_state

#undef main_bss_state

static const struct {
    s8 phase, active, next_phase, next_active;
} submenu_phases[] = {
    { 0, 0, 1, -1 },
    { 0, 1, 1, 1 },
    { 1, 0, 2, 0 },
    { 1, -1, 1, -1 },
    { 2, 0, 2, 0 },
    { 3, 0, 4, 1 },
    { 3, -1, 4, -1 },
    { 4, 0, 0, 0 },
    { 4, 1, 4, 1 },
};

static u32 test_pause_submenu_phases(u32 row)
{
    struct BarObj expected;
    struct EngineObj engine_before;
    struct PlayerObj player_before;
    u32 variant = row / (2 * COUNT(submenu_phases));
    u32 character = row / COUNT(submenu_phases) % 2;
    u32 index = row % COUNT(submenu_phases);
    memset(&bar_object, 0, sizeof(bar_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(unk_objects, 0, sizeof(unk_objects));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&pause_action_selection_drawing, 0, sizeof(pause_action_selection_drawing));
    memset(pause_action_selection_tiles, 0, sizeof(pause_action_selection_tiles));
    memset(pause_action_selection_title_frames, 0, sizeof(pause_action_selection_title_frames));
    TEST_ARC_34 = (u8*)pause_action_selection_tiles;
    TEST_TITLE_FRAMES = (u8*)pause_action_selection_title_frames;
    SP_DRAW_BUFFER = 0;
    cur_draw_info = &pause_action_selection_drawing;
    func_80023D30();
    engine_obj.cur_character = character;
    engine_obj.stage = 9;
    bar_object.state = 1;
    bar_object.unk5 = variant ? 5 : 4;
    bar_object.unk6 = submenu_phases[index].phase;
    bar_object.pad7 = 1;
    bar_object.unk28 = 3;
    D_8013B7D0 = 1;
    D_8013E198[0] = -1;
    main_bss_state.transition.active = submenu_phases[index].active;
    main_bss_state.transition.fade_amount = 3;
    expected = bar_object;
    engine_before = engine_obj;
    player_before = g_Player;
    expected.unk6 = submenu_phases[index].next_phase;
    if (submenu_phases[index].phase == 4 && submenu_phases[index].active == 0)
        expected.unk5 = variant ? 3 : 2;
    if (variant)
        func_80030EC8(&bar_object);
    else
        func_80030DF8(&bar_object);
    c_test_same_words(&bar_object, &expected, sizeof(expected));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_before));
    c_test_same_words(&g_Player, &player_before, sizeof(player_before));
    assert(main_bss_state.transition.active == submenu_phases[index].next_active);
    assert(main_bss_state.transition.fade_amount == ((submenu_phases[index].phase == 0 || submenu_phases[index].phase == 3) && submenu_phases[index].active == 0 ? 8 : 3));
    assert(D_8013B7D0 == 1);
    assert(controller_input.pressed == 0);
    return 1;
}

void func_80030128(struct BarObj*);
static struct DrawInfo drawing;
static u32 tiles[256], title_frames[512];
static const struct {
    u8 phase, substep, select, transition, next_phase, next_substep;
} cases[] = {
    { 0, 1, 1, 1, 6, 1 },
    { 1, 3, 1, 1, 6, 1 },
    { 2, 4, 1, 1, 6, 1 },
    { 3, 1, 1, 1, 3, 1 },
    { 4, 1, 1, 1, 4, 1 },
    { 6, 1, 0, 1, 6, 1 },
    { 6, 4, 0, 0, 2, 0 },
    { 5, 4, 1, 0, 2, 0 },
};
static u32 help_dispatch(u32 row)
{
    struct BarObj expected;
    struct EngineObj engine_before;
    struct PlayerObj player_before;
    struct MainBssState main_before;
    struct ControllerInput input;
    u32 i;
    memset(&bar_object, 0, sizeof(bar_object));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&drawing, 0, sizeof(drawing));
    memset(tiles, 0, sizeof(tiles));
    memset(title_frames, 0, sizeof(title_frames));
    memset(unk_objects, 0, sizeof(unk_objects));
    for (i = 0; i < 320; i++) {
        memset(&D_8015D9D0[0].sprites[i], 0, sizeof(SPRT_16));
        setSprt16(&D_8015D9D0[0].sprites[i]);
        setRGB0(&D_8015D9D0[0].sprites[i], 128, 128, 128);
    }
    TEST_ARC_34 = (u8*)tiles;
    TEST_TITLE_FRAMES = (u8*)title_frames;
    SP_DRAW_BUFFER = 0;
    cur_draw_info = &drawing;
    func_80023D30();
    engine_obj.stage = 9;
    engine_obj.cur_character = 1;
    g_Player.unk2 = 1;
    g_Player.hp = 30;
    engine_before = engine_obj;
    player_before = g_Player;
    main_bss_state.frame_counter = 1;
    main_bss_state.transition.active = cases[row].transition;
    main_bss_state.transition.fade_amount = 3;
    main_before = main_bss_state;
    bar_object.state = 1;
    bar_object.unk5 = cases[row].phase;
    bar_object.unk6 = cases[row].substep;
    bar_object.unk28 = 2;
    bar_object.unk14 = 10;
    expected = bar_object;
    controller_input.held = 0x1357;
    controller_input.previous = 0x2468;
    controller_input.pressed = cases[row].select ? PADselect : 0;
    input = controller_input;
    expected.unk5 = cases[row].next_phase;
    expected.unk6 = cases[row].next_substep;
    if (cases[row].select && cases[row].phase < 3)
        expected.unk28 = cases[row].phase;
    func_80030128(&bar_object);
    c_test_same_words(&bar_object, &expected, sizeof(expected));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(cur_draw_info == &drawing && SP_DRAW_BUFFER == 0 && TEST_ARC_34 == (u8*)tiles && TEST_TITLE_FRAMES == (u8*)title_frames);
    for (i = 0; i < 320; i++) {
        SPRT_16* sprite = &D_8015D9D0[0].sprites[i];
        assert(sprite->x0 == (i < 256 ? i % 16 * 16 : 256 + (i - 256) % 4 * 16));
        assert(sprite->y0 == (i < 256 ? i / 16 * 16 : (i - 256) / 4 * 16));
        assert(sprite->clut == 0x7900 && sprite->u0 == 0 && sprite->v0 == 0 && sprite->code == 0x7C && getlen(sprite) == 3);
        assert(sprite->r0 == 128 && sprite->g0 == 128 && sprite->b0 == 128);
    }
    for (i = 0; i < COUNT(tiles); i++)
        assert(tiles[i] == 0);
    for (i = 0; i < COUNT(title_frames); i++)
        assert(title_frames[i] == 0);
    return 1;
}

extern u8 D_8013B818[16];
static u32 confirm(u32 row)
{
    struct BarObj obj, expected;
    struct PlayerObj player;
    struct EngineObj engine;
    struct MainBssState main;
    struct ControllerInput input;
    u32 i;
    engine_obj.state = 6;
    engine_obj.unk5F = 3;
    engine_obj.unk1 = 1;
    engine_obj.stage = 1;
    engine_obj.substage = 0;
    engine_obj.cur_character = CHARACTER_X;
    engine_obj.collected_upgrades = 0x7000;
    engine_obj.palette_flags = 1;
    engine_obj.sub_tanks[0] = 0x9F;
    engine_obj.sub_tanks[1] = 0xA0;
    engine_obj.sub_tanks[2] = 0xA0;
    main_bss_state.transition.active = 0;
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 16;
    g_Player.boss_flags = 1;
    g_Player.animation_table = (u32**)D_80119DF0;
    set_animation(&g_Player, 5);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    memset(&obj, 0, sizeof(obj));
    obj.state = 1;
    obj.options.fields.player[0] = 1;
    obj.options.items[2] = 1;
    for (i = 10; i <= 14; i++)
        obj.options.items[i] = 1;
    D_8013B818[0] = 0;
    D_8013E198[0] = -1;
    memset(&controller_input, 0, sizeof(controller_input));
    controller_input.pressed = PADLdown;
    func_800301BC(&obj);
    assert(obj.unk14 == 2 && obj.unk5 == 0);
    func_800301BC(&obj);
    assert(obj.unk14 == 10 && obj.unk5 == 1);
    controller_input.pressed = PADLright;
    for (i = 0; i < (row < 3 ? row : 2); i++)
        func_800304E4(&obj);
    assert(obj.unk14 == (row < 3 ? 10 + row : 12));
    controller_input.pressed = row == 3 ? PADLright : PAD_CONFIRM;
    input = controller_input;
    expected = obj;
    if (row == 3) {
        expected.unk14 = 13;
        expected.unk5 = 2;
    } else {
        expected.unk5 = row == 2 ? 4 : 3;
        expected.unk28 = row == 1;
        expected.unk2C = row == 2;
    }
    player = g_Player;
    engine = engine_obj;
    main = main_bss_state;
    cur_random = 0x1234;
    func_800304E4(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&main_bss_state, &main, sizeof(main));
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(D_8013B818[0] == 0 && D_8013E198[0] == -1 && cur_random == 0x1234);
    return 1;
}

void func_80031130(struct BarObj*);
static const u8 amounts[] = { 0, 1, 48, 128, 129, 176 };
static u32 refill(u32 row)
{
    struct BarObj bar, expected;
    struct PlayerObj player_expected = g_Player;
    struct EngineObj engine_expected;
    struct MainBssState main_expected;
    u32 frame = row % 4, mode = row / 4 % 2, level = row / 8 % 3, tank = row / 24, i;
    memset(&bar, 0x35, sizeof(bar));
    bar.unk2C = mode;
    bar.unk5 = 0;
    expected = bar;
    for (i = 0; i < 9; i++)
        g_Player.weapon_energy[i] = player_expected.weapon_energy[i] = level == 0 ? 48 : level == 1 ? 47
                                                                                                    : i * 6;
    engine_obj.sub_tanks[2] = amounts[tank];
    engine_expected = engine_obj;
    main_bss_state.frame_counter = frame;
    main_expected = main_bss_state;
    D_8013E198[0] = -1;
    if (!(frame & 1)) {
        if (mode) {
            if (level != 0) {
                for (i = 0; i < 9; i++)
                    player_expected.weapon_energy[i] = level == 1 ? 48 : i < 8 ? i * 6 + 1
                                                                               : 48;
                engine_expected.sub_tanks[2] = amounts[tank] & 127 ? (amounts[tank] & 127) - 1 : 0;
            } else if (amounts[tank] & 127)
                engine_expected.sub_tanks[2] = (amounts[tank] & 127) - 1;
            else {
                expected.unk5 = 1;
                expected.unk2C = 0;
            }
        } else if (!(amounts[tank] & 127))
            expected.unk5 = 1;
        else {
            for (i = 0; i < 9; i++)
                player_expected.weapon_energy[i] = level == 2 && i < 8 ? i * 6 + 1 : 48;
            if (level == 2)
                engine_expected.sub_tanks[2] = (amounts[tank] & 127) - 1;
            else
                expected.unk5 = 1;
        }
    }
    func_80030C54(&bar);
    c_test_same_words(&bar, &expected, sizeof(bar));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    assert(D_8013E198[0] == -1);
    return 1;
}
static u32 exit_pause(u32 row)
{
    struct BarObj bar, expected;
    struct EngineObj engine_expected;
    struct PlayerObj player_before = g_Player;
    struct MainBssState main_expected;
    memset(&bar, 0x35, sizeof(bar));
    bar.unk30 = 1;
    bar.state = 2;
    bar.unk5 = 3;
    expected = bar;
    engine_obj.state = 8;
    engine_obj.unk1 = 3;
    engine_obj.unk2 = 4;
    engine_obj.unk10 = 10;
    engine_obj.unk11 = 11;
    engine_obj.unk12 = 12;
    engine_obj.unk13 = 13;
    engine_obj.unk14 = 14;
    engine_obj.unk15 = 15;
    engine_obj.unk16 = VISUAL_SATURN_LAYER(16);
    engine_obj.unk17 = 17;
    engine_expected = engine_obj;
    main_bss_state.transition.active = row;
    main_expected = main_bss_state;
    if (!row) {
        expected.state = expected.unk5 = 0;
        engine_expected.state = 9;
        engine_expected.unk1 = engine_expected.unk2 = 0;
        engine_expected.unk10 = engine_expected.unk11 = engine_expected.unk12 = engine_expected.unk13 = 0;
        engine_expected.unk14 = engine_expected.unk15 = engine_expected.unk16 = engine_expected.unk17 = 0;
    }
    func_80031130(&bar);
    c_test_same_words(&bar, &expected, sizeof(bar));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    return 1;
}

#include "support/sound_probe.h"
void func_80030DF8(struct BarObj*);
void func_80031014(struct BarObj*);
void func_80031064(struct BarObj*);
enum { PP_FD70_FADING,
    PP_READY_FADING,
    PP_READY_PLAYER2,
    PP_READY_PLAIN,
    PP_W_START,
    PP_W_BUSTER,
    PP_W_WEAPON,
    PP_W_UP_TOP,
    PP_W_UP_SKIP,
    PP_W_UP_ZERO,
    PP_W_RIGHT,
    PP_W_LEFT_ODD,
    PP_W_LEFT,
    PP_W_LEFT_SKIP,
    PP_T_START,
    PP_T_TANK_FULL,
    PP_T_UP_PLAYER2,
    PP_T_UP_WEAPON,
    PP_T_DOWN,
    PP_T_LEFT,
    PP_H_TANK_CLAMP,
    PP_H_TANK_STEP,
    PP_H_EMPTY_STEP,
    PP_H_MERGE,
    PP_DF8_DEFAULT,
    PP_EC8_DEFAULT,
    PP_LEAVE_FADING,
    PP_LEAVE,
    PP_RESUME_EXIT,
    PP_RESUME_PLAYER2,
    PP_RESUME_SAME,
    PP_RESUME_CHANGED,
    PP_EXIT_RESUME,
    PP_COUNT };
static u16 pause_paths_palette[0x400], pause_paths_palette_bank[0x400];
static u32 pause_paths(u32 row)
{
    struct BarObj expected;
    struct PlayerObj player_expected;
    u32 i;
    s32 sound = -1;
    memset(&bar_object, 0x35, sizeof(bar_object));
    memset(bar_object.options.items, 0, sizeof(bar_object.options.items));
    bar_object.unk2 = 0;
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(unk_objects, 0, sizeof(unk_objects));
    memset(&pause_action_selection_drawing, 0, sizeof(pause_action_selection_drawing));
    memset(pause_action_selection_tiles, 0, sizeof(pause_action_selection_tiles));
    memset(pause_action_selection_title_frames, 0, sizeof(pause_action_selection_title_frames));
    TEST_ARC_34 = (u8*)pause_action_selection_tiles;
    TEST_TITLE_FRAMES = (u8*)pause_action_selection_title_frames;
    SP_DRAW_BUFFER = 0;
    cur_draw_info = &pause_action_selection_drawing;
    func_80023D30();
    sound_probe_begin_group(0);
    for (i = 1; i < 6; i++)
        D_80141F50[i] = (u8*)sound_probe_rows;
    TEST_PALETTE = (u8*)pause_paths_palette;
    TEST_PALETTE_BANK = (u8*)pause_paths_palette_bank;
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 3; i++)
        background_objects[i].x_pos.i.hi = background_objects[i].y_pos.i.hi = -0x200;
    g_Player.hp = 16;
    g_Player.weapon = 5;
    engine_obj.max_hp = 16;
    switch (row) {
    case PP_FD70_FADING:
    case PP_READY_FADING:
    case PP_LEAVE_FADING:
        main_bss_state.transition.active = 1;
        break;
    case PP_READY_PLAYER2:
        g_Player.unk2 = 1;
        bar_object.unk14 = 12;
        break;
    case PP_READY_PLAIN:
        bar_object.unk14 = 13;
        break;
    case PP_W_START:
    case PP_T_START:
        controller_input.pressed = PADstart;
        break;
    case PP_W_BUSTER:
        bar_object.unk14 = 1;
        controller_input.pressed = PAD_CONFIRM;
        break;
    case PP_W_WEAPON:
        bar_object.unk14 = 5;
        controller_input.pressed = PAD_CONFIRM;
        break;
    case PP_W_UP_TOP:
        bar_object.unk14 = 1;
        controller_input.pressed = PADLup;
        break;
    case PP_W_UP_SKIP:
        bar_object.unk14 = 6;
        bar_object.options.items[2] = 1;
        controller_input.pressed = PADLup;
        break;
    case PP_W_UP_ZERO:
        bar_object.unk14 = 4;
        controller_input.pressed = PADLup;
        break;
    case PP_W_RIGHT:
        bar_object.unk14 = 2;
        bar_object.options.items[3] = 1;
        controller_input.pressed = PADLright;
        break;
    case PP_W_LEFT_ODD:
        bar_object.unk14 = 2;
        controller_input.pressed = PADLleft;
        break;
    case PP_W_LEFT:
        bar_object.unk14 = 3;
        bar_object.options.items[2] = 1;
        controller_input.pressed = PADLleft;
        break;
    case PP_W_LEFT_SKIP:
        bar_object.unk14 = 5;
        bar_object.options.items[2] = 1;
        controller_input.pressed = PADLleft;
        break;
    case PP_T_TANK_FULL:
        bar_object.unk14 = 10;
        engine_obj.sub_tanks[0] = 0xA0;
        controller_input.pressed = PAD_CONFIRM;
        break;
    case PP_T_UP_PLAYER2:
        g_Player.unk2 = 1;
        bar_object.unk14 = 11;
        controller_input.pressed = PADLup;
        break;
    case PP_T_UP_WEAPON:
        bar_object.unk14 = 11;
        bar_object.options.items[7] = 1;
        controller_input.pressed = PADLup;
        break;
    case PP_T_DOWN:
        bar_object.unk14 = 11;
        controller_input.pressed = PADLdown;
        break;
    case PP_T_LEFT:
        bar_object.unk14 = 12;
        bar_object.options.items[11] = 1;
        controller_input.pressed = PADLleft;
        break;
    case PP_H_TANK_CLAMP:
    case PP_H_TANK_STEP:
        bar_object.unk14 = 10;
        bar_object.unk28 = 1;
        engine_obj.sub_tanks[0] = 0x85;
        if (row == PP_H_TANK_STEP) {
            g_Player.hp = 5;
            main_bss_state.frame_counter = 2;
        }
        break;
    case PP_H_EMPTY_STEP:
        bar_object.unk14 = 10;
        bar_object.unk28 = 1;
        engine_obj.sub_tanks[0] = 0x80;
        g_Player.hp = 5;
        main_bss_state.frame_counter = 2;
        break;
    case PP_H_MERGE:
        bar_object.unk14 = 10;
        bar_object.unk28 = 1;
        engine_obj.sub_tanks[0] = 0x80;
        engine_obj.sub_tanks[1] = 0x85;
        break;
    case PP_DF8_DEFAULT:
    case PP_EC8_DEFAULT:
        bar_object.unk6 = 5;
        break;
    case PP_RESUME_EXIT:
        bar_object.unk30 = 1;
        break;
    case PP_RESUME_PLAYER2:
        g_Player.unk2 = 1;
        bar_object.unk30 = 0;
        break;
    case PP_RESUME_SAME:
    case PP_RESUME_CHANGED:
        bar_object.unk30 = 0;
        g_Player.stock_charge = 3;
        D_8013B818[0] = row == PP_RESUME_SAME ? 5 : 2;
        if (row == PP_RESUME_CHANGED)
            g_Player.weapon = 3;
        break;
    case PP_EXIT_RESUME:
        bar_object.unk30 = 0;
        engine_obj.unk1 = 4;
        bar_object.state = 2;
        break;
    }
    expected = bar_object;
    player_expected = g_Player;
    switch (row) {
    case PP_FD70_FADING:
        func_8002FD70(&bar_object);
        break;
    case PP_READY_FADING:
    case PP_READY_PLAYER2:
    case PP_READY_PLAIN:
        func_800300AC(&bar_object);
        if (row != PP_READY_FADING) {
            expected.state = 1;
            expected.unk5 = row == PP_READY_PLAYER2;
        }
        break;
    case PP_W_START:
    case PP_W_BUSTER:
    case PP_W_WEAPON:
    case PP_W_UP_TOP:
    case PP_W_UP_SKIP:
    case PP_W_UP_ZERO:
    case PP_W_RIGHT:
    case PP_W_LEFT_ODD:
    case PP_W_LEFT:
    case PP_W_LEFT_SKIP:
        func_800301BC(&bar_object);
        if (row == PP_W_START) {
            expected.state = 2;
            expected.unk5 = 0;
        } else if (row == PP_W_BUSTER || row == PP_W_WEAPON) {
            player_expected.weapon = row == PP_W_BUSTER ? 0 : 4;
            sound = 0x22;
        } else if (row != PP_W_UP_TOP && row != PP_W_LEFT_ODD) {
            expected.unk14 = row == PP_W_UP_ZERO ? 0 : row == PP_W_RIGHT ? 3
                                                                         : 2;
            sound = 0xC;
        }
        break;
    case PP_T_START:
    case PP_T_TANK_FULL:
    case PP_T_UP_PLAYER2:
    case PP_T_UP_WEAPON:
    case PP_T_DOWN:
    case PP_T_LEFT:
        func_800304E4(&bar_object);
        if (row == PP_T_START) {
            expected.state = 2;
            expected.unk5 = 0;
        } else if (row == PP_T_TANK_FULL) {
            expected.unk5 = 3;
            expected.unk28 = 1;
            expected.unk2C = 0;
        } else if (row == PP_T_UP_WEAPON) {
            expected.unk5 = 0;
            expected.unk14 = 7;
            sound = 0xC;
        } else if (row == PP_T_LEFT) {
            expected.unk14 = 11;
            sound = 0xC;
        }
        break;
    case PP_H_TANK_CLAMP:
    case PP_H_TANK_STEP:
    case PP_H_EMPTY_STEP:
    case PP_H_MERGE:
        func_80030A2C(&bar_object);
        if (row == PP_H_MERGE) {
            expected.unk5 = 1;
            expected.unk28 = 0;
            assert(engine_obj.sub_tanks[0] == (s8)0x85 && engine_obj.sub_tanks[1] == (s8)0x80);
        } else {
            player_expected.hp = row == PP_H_TANK_CLAMP ? 16 : 6;
            assert(engine_obj.sub_tanks[0] == (s8)(row == PP_H_EMPTY_STEP ? 0x80 : 0x84));
            if (row == PP_H_TANK_CLAMP)
                sound = 0x17;
        }
        break;
    case PP_DF8_DEFAULT:
        func_80030DF8(&bar_object);
        break;
    case PP_EC8_DEFAULT:
        func_80030EC8(&bar_object);
        break;
    case PP_LEAVE_FADING:
    case PP_LEAVE:
        func_80031014(&bar_object);
        if (row == PP_LEAVE) {
            expected.unk5 = 2;
            assert(need_palette_load & 1);
        }
        break;
    case PP_RESUME_EXIT:
    case PP_RESUME_PLAYER2:
    case PP_RESUME_SAME:
    case PP_RESUME_CHANGED:
        need_palette_load = 0;
        func_80031064(&bar_object);
        expected.unk5 = 3;
        assert(main_bss_state.transition.active == (row == PP_RESUME_EXIT ? 0 : 1));
        if (row == PP_RESUME_SAME || row == PP_RESUME_CHANGED)
            assert(g_Player.stock_charge == (row == PP_RESUME_SAME ? 3 : 0));
        if (row == PP_RESUME_EXIT)
            c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
        break;
    case PP_EXIT_RESUME:
        func_80031130(&bar_object);
        expected.state = 0;
        expected.unk5 = 0;
        assert(engine_obj.unk1 == 0);
        break;
    }
    c_test_same_words(&bar_object, &expected, sizeof(expected));
    if (row < PP_RESUME_EXIT || row > PP_RESUME_CHANGED)
        c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    SOUND_CHECK(sound_probe_id() == sound);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "pause_submenu_phases", 0, 0, 4 * COUNT(submenu_phases), test_pause_submenu_phases },
    { "pause_action_selection", NULL, pause_action_selection_cases_expected, COUNT(pause_action_selection_cases_expected), pause_action_selection_cases_row },
    { "pause_availability", NULL, pause_availability_cases_expected, COUNT(pause_availability_cases_expected), pause_availability_cases_row },
    { "pause_navigation_edges", pause_navigation_edges_cases, pause_navigation_edges_cases_expected, COUNT(pause_navigation_edges_cases), 0 },
    { "pause_restricted_ready", pause_restricted_ready_cases, pause_restricted_ready_cases_expected, COUNT(pause_restricted_ready_cases), 0 },
    { "pause_weapon_boundary", NULL, pause_weapon_boundary_cases_expected, COUNT(pause_weapon_boundary_cases_expected), boundary },
    { "func_800301BC", 0, 0, 5, test_func_800301BC },
    { "func_800304E4", 0, 0, 6, test_func_800304E4 },
    { "func_80030A2C", 0, 0, 8, test_func_80030A2C },
    { "select_opens_help_preserves_refill_and_restores_saved_phase", NULL, NULL, COUNT(cases), help_dispatch },
    { "actual_X_pause_navigation_partial_first_health_full_second_health_full_weapon_and_available_escape", NULL, NULL, 4, confirm },
    { "weapon_tank_frame_mode_capacity_and_completion", NULL, NULL, 44, refill },
    { "pause_exit_waits_then_resets_stage_state", NULL, NULL, 2, exit_pause },
    { "pause_paths", NULL, NULL, PP_COUNT, pause_paths },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4 * COUNT(submenu_phases) + COUNT(pause_action_selection_cases_expected) + COUNT(pause_availability_cases_expected) + COUNT(pause_navigation_edges_cases) + COUNT(pause_restricted_ready_cases) + COUNT(pause_weapon_boundary_cases_expected) + 5 + 6 + 8 + COUNT(cases) + 4 + 44 + 2 + PP_COUNT;
#endif
