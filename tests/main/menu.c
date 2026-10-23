#include "test_runtime.h"
#include "main/55C4.h"
#include "main/memcard.h"
#include "main/E47C_menu_data.h"
#include "main/1AC84.h"
#include "main/144A4.h"
#include "main/E47C.h"
void func_800194C8(struct EngineObj* arg0);
void func_8001989C(struct EngineObj* arg0);
void func_80019D04(struct EngineObj* arg0);
void func_80019EF0(struct EngineObj* arg0);
void func_8001A178(struct EngineObj* arg0);
void func_8001A308(struct EngineObj* arg0);
void func_8001A8E8(struct EngineObj* arg0);
void func_8001AA98(struct EngineObj* arg0);
void func_8001ABDC(struct EngineObj* arg0);
void func_8001AE8C(struct EngineObj* arg0);
void func_8001B10C(struct EngineObj* arg0);
void func_8001B388(struct EngineObj* arg0);
void func_8001B558(struct EngineObj* arg0);
#include "main/menu.h"
#include "main/2824.h"
#ifdef MMX4_PC
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#endif
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern u16 D_800EE430[16];

static u32 list_case(u32 mode, u32 observation)
{
    struct MiscObj pool_before[64];
    struct EngineObj engine_before;
    struct PlayerObj player_before;
    u8 data[] = { 42, 7, 9, 80, 8, 10, 0xFF };
    u32 i, j, actual;
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x27;
        misc_objects[i].state = 0x28;
    }
    if (mode != 0) {
        misc_objects[17].active = 0;
        misc_objects[31].active = 0;
    }
    engine_obj.unk1 = mode == 2 ? 3 : 2;
    engine_obj.unk2 = 0x25;
    g_Player.hp = 0x26;
    engine_before = engine_obj;
    player_before = g_Player;
    memcpy(pool_before, misc_objects, sizeof(pool_before));
    func_8001B644(mode == 0 ? &data[6] : data);
    if (mode != 0) {
        for (j = 0; j < 2; j++) {
            struct MiscObj* expected = &pool_before[j == 0 ? 17 : 31];
            expected->active = 0x41;
            expected->id = 0x2A;
            expected->unk2 = 0;
            expected->x_pos.i.hi = 0xA0;
            expected->y_pos.i.hi = data[j * 3];
            expected->animation_step.fields.frame_index = data[j * 3 + 1];
            expected->ext.misc_42.unk54 = mode == 2 ? 0x25 : 2;
            expected->ext.misc_42.unk55 = mode == 2 ? 2 : 1;
            expected->ext.misc_42.unk56 = data[j * 3 + 2];
        }
    }
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(data[0] == 42 && data[1] == 7 && data[2] == 9 && data[3] == 80 && data[4] == 8 && data[5] == 10 && data[6] == 0xFF);
    actual = observation == 0 ? misc_objects[17].animation_step.packed : misc_objects[31].ext.misc_42.unk54 | ((u32)misc_objects[31].ext.misc_42.unk55 << 8) | ((u32)misc_objects[31].ext.misc_42.unk56 << 16);
    return actual;
}
static const u32 menu_text_list_context_cases_expected[] = { 0x0u, 0x0u, 0x7000000u, 0xA0102u, 0x7000000u, 0xA0225u };
static u32 menu_text_list_context_cases_row(u32 row)
{
    return list_case(row / 2, row % 2);
}

static struct NavigationInput {
    u16 pressed;
    u8 selection, card0, card1;
};
static const struct NavigationInput inputs[] = {
    { 20480, 0, 0, 0 },
    { 20480, 0, 1, 0 },
    { 20480, 2, 0, 0 },
    { 20480, 2, 0, 1 },
    { 20480, 2, 1, 1 },
    { 20480, 1, 1, 1 },
};
static u32 navigate(u32 mode)
{
    struct EngineObj engine, before;
    struct ControllerInput input_before;
    struct MainBssState main_before;
    struct MemcardMenuState menu_before;
    u32 i;
    memset(&engine, 0, sizeof(engine));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&memcard_menu, 0, sizeof(memcard_menu));
    controller_input.pressed = inputs[mode].pressed;
    main_bss_state.transition.selection = inputs[mode].selection;
    memcard_menu.card_status[0] = inputs[mode].card0;
    memcard_menu.card_status[1] = inputs[mode].card1;
    before = engine;
    input_before = controller_input;
    main_before = main_bss_state;
    menu_before = memcard_menu;
    assert((controller_input.pressed & PAD_SELECTION_BUTTONS) == 0);
    assert(main_bss_state.transition.selection <= 2);
    func_8001961C(&engine);
    main_before.transition.selection = main_bss_state.transition.selection;
    for (i = 0; i < sizeof(engine) / 4; i++)
        assert(((u32*)&engine)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(controller_input) / 4; i++)
        assert(((u32*)&controller_input)[i] == ((u32*)&input_before)[i]);
    for (i = 0; i < sizeof(main_bss_state) / 4; i++)
        assert(((u32*)&main_bss_state)[i] == ((u32*)&main_before)[i]);
    for (i = 0; i < sizeof(memcard_menu) / 4; i++)
        assert(((u32*)&memcard_menu)[i] == ((u32*)&menu_before)[i]);
    return main_bss_state.transition.selection;
}
static const u32 save_menu_navigation_cases_expected[] = { 0x0u, 0x1u, 0x2u, 0x2u, 0x2u, 0x2u };

static u32 same_words(const void* actual, const void* before, u32 size)
{
    const u32* a = actual;
    const u32* b = before;
    u32 i;
    assert((size & 3) == 0);
    for (i = 0; i < size / 4; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}
static void same_bytes(const void* actual, const void* before, u32 size)
{
    const u8* a = actual;
    const u8* b = before;
    u32 i;
    for (i = 0; i < size; i++) {
#ifdef MMX4_PC
        if (a[i] != b[i])
            fprintf(stderr, "byte mismatch at %u/%u: expected %02X, actual %02X\n", i, size, b[i], a[i]);
#endif
        assert(a[i] == b[i]);
    }
}

static u32 preview_case(u32 mode)
{
    struct MiscObj before[0x40];
    struct MemcardSaveSlot slot, slot_before;
    struct MemcardMenuState menu_before;
    struct EngineObj engine_before;
    struct MainBssState main_before;
    struct MiscObj* obj;
    u32 i, allocated = 0;
    u32 expected_count = mode == 16 ? 1 : (mode >= 12 && mode <= 14) ? 1
        : mode == 11                                                 ? 26
        : mode < 2                                                   ? 20
        : mode == 3                                                  ? 1
        : (mode == 4 || mode == 5)                                   ? 4
        : (mode == 6 || mode == 7)                                   ? 1
                                                                     : 0;
    u8 persistent = mode == 1 || mode == 5 || mode == 7 || mode == 11 || mode == 13;
    memset(&slot, 0, sizeof(slot));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&memcard_menu, 0, sizeof(memcard_menu));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(misc_objects, 0x5A, sizeof(misc_objects));
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 0x91;
    if (mode < 2 || mode == 4 || mode == 5 || mode == 6 || mode == 7 || mode == 11 || (mode >= 12 && mode <= 14) || mode == 16)
        for (i = 0; i < expected_count; i++)
            misc_objects[i].active = 0;
    if (mode == 3)
        misc_objects[63].active = 0;
    engine_obj.unk1 = 0x27;
    main_bss_state.transition.selection = 0x33;
    memcard_menu.slot = &slot;
    slot.character = mode == 14 ? 0xFF : (mode == 1 || mode == 12 || mode == 16) ? 1
                                                                                 : 0;
    slot.unk4 = 0xFF;
    slot.unk6 = 0xFFFF;
    slot.unk3 = mode == 10 ? 0 : 0xF;
    slot.unk2 = mode == 5 ? 0 : 2;
    slot.unk29 = (mode == 6 || mode == 7 || mode == 8 || mode == 10 || mode == 12 || mode == 13) ? 1 : 0;
    if (mode == 16) {
        slot.unk4 = D_800F1D90.button_lookup[0];
        slot.unk6 = 0;
        D_800F1D90.button_lookup[2] = 8;
    }
    slot_before = slot;
    menu_before = memcard_menu;
    engine_before = engine_obj;
    main_before = main_bss_state;
    memcpy(before, misc_objects, sizeof(before));
    if (mode >= 12 && mode <= 14)
        func_8001BCAC(120, 80, persistent);
    else if (mode == 11 || mode == 15)
        func_8001B7C0(120, 80, persistent);
    else if (mode < 4 || mode == 16)
        func_8001B8B0(120, 80, persistent);
    else
        func_8001BE10(120, 80, persistent);
    same_bytes(&slot, &slot_before, sizeof(slot));
    assert(same_words(&memcard_menu, &menu_before, sizeof(memcard_menu)));
    assert(same_words(&engine_obj, &engine_before, sizeof(engine_obj)));
    assert(same_words(&main_bss_state, &main_before, sizeof(main_bss_state)));
    for (i = 0; i < COUNT(misc_objects); i++) {
        if (before[i].active == 0 && misc_objects[i].active != 0) {
            allocated++;
            before[i].active = misc_objects[i].active;
            before[i].id = misc_objects[i].id;
            before[i].unk2 = misc_objects[i].unk2;
            before[i].animation_step.fields.frame_index = misc_objects[i].animation_step.fields.frame_index;
            before[i].unk42 = misc_objects[i].unk42;
            before[i].x_pos.i.hi = misc_objects[i].x_pos.i.hi;
            before[i].y_pos.i.hi = misc_objects[i].y_pos.i.hi;
            before[i].ext.misc_42.unk54 = misc_objects[i].ext.misc_42.unk54;
            before[i].ext.misc_42.unk55 = misc_objects[i].ext.misc_42.unk55;
            if (mode >= 4)
                before[i].unk16 = misc_objects[i].unk16;
            if (mode == 14)
                before[i].ext.misc_42.unk56 = misc_objects[i].ext.misc_42.unk56;
        }
    }
    assert(allocated == expected_count);
    assert(same_words(misc_objects, before, sizeof(before)));
    if (expected_count == 0)
        return allocated;
    for (i = 0; i < expected_count; i++) {
        obj = &misc_objects[i];
        allocated = allocated * 31 + (obj->active | ((u32)(u8)obj->id << 8) | ((u32)(u8)obj->unk2 << 16) | ((u32)(u8)obj->animation_step.fields.frame_index << 24));
        allocated = allocated * 31 + ((u16)obj->unk42 | ((u32)(u8)obj->unk16 << 16) | ((u32)(u8)obj->ext.misc_42.unk56 << 24));
        allocated = allocated * 31 + ((u16)obj->x_pos.i.hi | ((u32)(u16)obj->y_pos.i.hi << 16));
        allocated = allocated * 31 + ((u8)obj->ext.misc_42.unk54 | ((u32)(u8)obj->ext.misc_42.unk55 << 8));
    }
    return allocated;
}
#undef memcard_menu
#undef main_bss_state
#undef PREVIEW_CASE

#undef controller_input
#undef memcard_menu

static const u32 func_8001B718_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_8001B718(u32 row)
{
    u32 observed_values[9];
    u8 pool_0_full;
    s16 arg0;
    u8 arg1;
    u8 arg2;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&misc_objects, 0, sizeof(misc_objects));
    pool_0_full = 255;
    arg0 = 0;
    arg1 = 0;
    arg2 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 64; ++slot)
            misc_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_8001B718(arg0, arg1, arg2);
    observed_values[0] = (u32)misc_objects[0].active;
    observed_values[1] = (u32)misc_objects[0].animation_step.fields.frame_index;
    observed_values[2] = (u32)misc_objects[0].ext.misc_42.unk54;
    observed_values[3] = (u32)misc_objects[0].ext.misc_42.unk55;
    observed_values[4] = (u32)misc_objects[0].ext.misc_42.unk56;
    observed_values[5] = (u32)misc_objects[0].id;
    observed_values[6] = (u32)misc_objects[0].unk2;
    observed_values[7] = (u32)misc_objects[0].x_pos.i.hi;
    observed_values[8] = (u32)misc_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, func_8001B718_expected, 9);
}

static const u32 func_8001C30C_expected[] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_func_8001C30C(u32 row)
{
    u32 observed_values[29];
    struct MemcardSaveSlot obj;
    memset(&obj, 0, sizeof(obj));
    memset(&D_800EE430, 0, sizeof(D_800EE430));
    memset(&D_800F1D90, 0, sizeof(D_800F1D90));
    memset(&engine_obj, 0, sizeof(engine_obj));
    func_8001C30C(&obj);
    observed_values[0] = (u32)D_800EE430[0];
    observed_values[1] = (u32)D_800EE430[10];
    observed_values[2] = (u32)D_800EE430[11];
    observed_values[3] = (u32)D_800EE430[12];
    observed_values[4] = (u32)D_800EE430[13];
    observed_values[5] = (u32)D_800EE430[14];
    observed_values[6] = (u32)D_800EE430[15];
    observed_values[7] = (u32)D_800EE430[1];
    observed_values[8] = (u32)D_800EE430[2];
    observed_values[9] = (u32)D_800EE430[3];
    observed_values[10] = (u32)D_800EE430[4];
    observed_values[11] = (u32)D_800EE430[5];
    observed_values[12] = (u32)D_800EE430[6];
    observed_values[13] = (u32)D_800EE430[7];
    observed_values[14] = (u32)D_800EE430[8];
    observed_values[15] = (u32)D_800EE430[9];
    observed_values[16] = (u32)engine_obj.cur_character;
    observed_values[17] = (u32)engine_obj.palette_flags;
    observed_values[18] = (u32)engine_obj.unk37;
    observed_values[19] = (u32)engine_obj.player_lives;
    observed_values[20] = (u32)engine_obj.checkpoint_hp;
    observed_values[21] = (u32)engine_obj.max_hp;
    observed_values[22] = (u32)engine_obj.armor_parts;
    observed_values[23] = (u32)engine_obj.arm_type;
    observed_values[24] = (u32)engine_obj.collected_upgrades;
    observed_values[25] = (u32)engine_obj.sub_tanks[0];
    observed_values[26] = (u32)engine_obj.sub_tanks[1];
    observed_values[27] = (u32)engine_obj.sub_tanks[2];
    observed_values[28] = (u32)engine_obj.unk5F;
    return c_test_observe(0, row, observed_values, func_8001C30C_expected, 29);
}

#include "support/pool_full.h"
static u32 pool_full_menu_spawn_marker(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    func_8001C008(0, 0);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_menu_spawn_marker,
};
static const u32 pool_full_cases_expected[] = { 0x50000u };

static u32 save_sign_bit(void)
{
    struct MemcardSaveSlot slot;
    u32 i, actual;
    memset(&slot, 0, sizeof(slot));
    memset(&engine_obj, 0, sizeof(engine_obj));
    slot.unk6 = D_800F1D90.sign_bit_mask;
    slot.character = 1;
    slot.unk1 = 5;
    slot.unk29 = 1;
    for (i = 0; i < COUNT(slot.unk8); i++)
        slot.unk8[i] = 0x1000 + i;
    func_8001C30C(&slot);
    assert(engine_obj.cur_character == 1);
    assert(engine_obj.max_hp == 5 && engine_obj.checkpoint_hp == 5);
    assert(engine_obj.unk37 == 1);
    assert(engine_obj.collected_upgrades == slot.unk6);
    for (i = 0; i < COUNT(slot.unk8); i++)
        assert(D_800EE430[i] == slot.unk8[i]);
    actual = engine_obj.player_lives;
    return actual;
}
static const CTestCase save_sign_bit_cases[] = {
    save_sign_bit,
};

static const u32 save_sign_bit_cases_expected[] = { 0x4u };
static struct MemcardSaveSlot menu_slots[4];

static void menu_reset(u8 step, u8 selection, u16 pressed)
{
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(menu_slots, 0, sizeof(menu_slots));
    memcard_menu.slot = &menu_slots[selection == 3 ? 3 : selection];
    memcard_menu.card_status[0] = 1;
    memcard_menu.card_status[1] = 1;
    main_bss_state.transition.selection = selection;
    controller_input.pressed = pressed;
    engine_obj.unk1 = step;
    engine_obj.unk2 = 0;
    engine_obj.state = 0;
}

static u32 menu_run(void (*run)(void), u32 row, const u32* expected)
{
    u32 seen[6], active = 0, i;
    run();
    for (i = 0; i < COUNT(misc_objects); i++)
        active += misc_objects[i].active != 0;
    seen[0] = (u8)engine_obj.unk1 | (u8)engine_obj.unk2 << 8 | (u8)engine_obj.state << 16 | (u32)main_bss_state.transition.selection << 24;
    seen[1] = memcard_menu.port | memcard_menu.selection << 8 | memcard_menu.result << 16 | (u32)memcard_menu.timer << 24;
    seen[2] = memcard_menu.slot - menu_slots;
    seen[3] = active;
    seen[4] = (u8)misc_objects[0].id | (u8)misc_objects[0].unk2 << 8 | (u32)misc_objects[0].animation_step.fields.frame_index << 16;
    seen[5] = (u16)misc_objects[0].y_pos.i.hi | (u32)(u8)misc_objects[0].ext.misc_42.unk54 << 16 | (u32)(u8)misc_objects[0].ext.misc_42.unk55 << 24;
    return c_test_observe(0, row, seen, expected, 6);
}

#define CONFIRM (PAD_SELECTION_BUTTONS & ~PAD_SELECTION_ALT)
static void m_port_up_top(void)
{
    menu_reset(1, 0, PADLup);
    func_8001961C(&engine_obj);
}
static void m_port_up_second(void)
{
    menu_reset(1, 1, PADLup);
    func_8001961C(&engine_obj);
}
static void m_port_up_second_empty(void)
{
    menu_reset(1, 1, PADLup);
    memcard_menu.card_status[0] = 0;
    func_8001961C(&engine_obj);
}
static void m_port_up_back_empty(void)
{
    menu_reset(1, 2, PADLup);
    memcard_menu.card_status[0] = 0;
    func_8001961C(&engine_obj);
}
static void m_port_up_back(void)
{
    menu_reset(1, 2, PADLup);
    func_8001961C(&engine_obj);
}
static void m_port_up_back_one(void)
{
    menu_reset(1, 2, PADLup);
    memcard_menu.card_status[1] = 0;
    func_8001961C(&engine_obj);
}
static void m_port_down_top(void)
{
    menu_reset(1, 0, PADLdown);
    func_8001961C(&engine_obj);
}
static void m_port_down_top_one(void)
{
    menu_reset(1, 0, PADLdown);
    memcard_menu.card_status[1] = 0;
    func_8001961C(&engine_obj);
}
static void m_port_down_back(void)
{
    menu_reset(1, 2, PADLdown);
    func_8001961C(&engine_obj);
}
static void m_port_down_back_one(void)
{
    menu_reset(1, 2, PADLdown);
    memcard_menu.card_status[1] = 0;
    func_8001961C(&engine_obj);
}
static void m_port_down_back_empty(void)
{
    menu_reset(1, 2, PADLdown);
    memcard_menu.card_status[0] = 0;
    func_8001961C(&engine_obj);
}
static void m_port_down_second(void)
{
    menu_reset(1, 1, PADLdown);
    func_8001961C(&engine_obj);
}
static void m_slot_up_wrap(void)
{
    menu_reset(4, 0, PADLup);
    func_80019EF0(&engine_obj);
}
static void m_slot_up(void)
{
    menu_reset(4, 2, PADLup);
    func_80019EF0(&engine_obj);
}
static void m_slot_down_wrap(void)
{
    menu_reset(4, 3, PADLdown);
    func_80019EF0(&engine_obj);
}
static void m_slot_down(void)
{
    menu_reset(4, 1, PADLdown);
    func_80019EF0(&engine_obj);
}
static void m_slot_cancel(void)
{
    menu_reset(4, 3, CONFIRM);
    func_80019EF0(&engine_obj);
}
static void m_slot_back(void)
{
    menu_reset(4, 1, PAD_SELECTION_ALT);
    func_80019EF0(&engine_obj);
}
static void m_label_list(void)
{
    menu_reset(5, 0, 0);
    func_8001B718(0x40, 0x36, 0xFF);
}
static void m_label_slot(void)
{
    menu_reset(3, 0, 0);
    engine_obj.unk2 = 2;
    func_8001B718(0x30, 0x1B, 1);
}
static void m_arrows(void)
{
    menu_reset(3, 0, 0);
    func_8001C008(3, 3);
}
static void m_arrows_full(void)
{
    u32 i;
    menu_reset(3, 0, 0);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = 1;
    func_8001C008(3, 3);
}

static void (*const menu_cases[])(void) = {
    m_port_up_top,
    m_port_up_second,
    m_port_up_second_empty,
    m_port_up_back_empty,
    m_port_up_back,
    m_port_up_back_one,
    m_port_down_top,
    m_port_down_top_one,
    m_port_down_back,
    m_port_down_back_one,
    m_port_down_back_empty,
    m_port_down_second,
    m_slot_up_wrap,
    m_slot_up,
    m_slot_down_wrap,
    m_slot_down,
    m_slot_cancel,
    m_slot_back,
    m_label_list,
    m_label_slot,
    m_arrows,
    m_arrows_full,
};
static const u32 menu_expected[] = { 0x2000001u, 0u, 0u, 0u, 0u, 0u, 0x2000001u, 0u, 1u, 0u, 0u, 0u, 1u, 0u, 1u, 0u, 0u, 0u, 1u, 0u, 2u, 0u, 0u, 0u, 0x2000001u, 0u, 2u, 0u, 0u, 0u, 0x1000001u, 0u, 2u, 0u, 0u, 0u, 0x2000001u, 0u, 0u, 0u, 0u, 0u, 0x1000001u, 0u, 0u, 0u, 0u, 0u, 0x2000001u, 0u, 2u, 0u, 0u, 0u, 0x1000001u, 0u, 2u, 0u, 0u, 0u, 1u, 0u, 2u, 0u, 0u, 0u, 0x2000001u, 0u, 1u, 0u, 0u, 0u, 0x3000004u, 0u, 3u, 0u, 0u, 0u, 0x1000004u, 0u, 1u, 2u, 0x2A012Au, 0x3010088u, 4u, 0u, 0u, 2u, 0x2A012Au, 0x3000088u, 0x2000004u, 0u, 2u, 2u, 0x2A012Au, 0x3020088u, 0u, 0u, 3u, 0u, 0u, 0u, 0u, 0u, 1u, 0u, 0u, 0u, 5u, 0u, 0u, 1u, 0x36002Au, 0x1050040u, 0x203u, 0u, 0u, 1u, 0x1B002Au, 0x2020030u, 3u, 0u, 0u, 1u, 0x42Au, 0x1030000u, 3u, 0u, 0u, 0x40u, 0u, 0u };

static u32 test_menu_screens(u32 row)
{
    return menu_run(menu_cases[row], row, &menu_expected[row * 6]);
}

static const struct {
    u16 pressed;
    u8 selection, card0, card1, saved_character;
    u8 expected_selection, expected_step, expected_port, expected_timer, expected_mode;
} load_ports[] = {
    { PADLup, 0, 0, 0, 0, 2, 4, 0, 0, 0 },
    { PADLup, 1, 0, 0, 0, 0, 4, 0, 0, 0 },
    { PADLup, 1, 1, 0, 0, 2, 4, 0, 0, 0 },
    { PADLup, 2, 0, 0, 0, 1, 4, 0, 0, 0 },
    { PADLup, 2, 0, 1, 0, 0, 4, 0, 0, 0 },
    { PADLup, 2, 1, 1, 0, 2, 4, 0, 0, 0 },
    { PADLdown, 0, 0, 0, 0, 1, 4, 0, 0, 0 },
    { PADLdown, 0, 0, 1, 0, 2, 4, 0, 0, 0 },
    { PADLdown, 1, 0, 0, 0, 2, 4, 0, 0, 0 },
    { PADLdown, 2, 0, 0, 0, 0, 4, 0, 0, 0 },
    { PADLdown, 2, 1, 0, 0, 1, 4, 0, 0, 0 },
    { PADLdown, 2, 1, 1, 0, 2, 4, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 4, 0, 0, 0 },
    { PAD_CONFIRM, 0, 0, 0, 0, 0, 5, 0, 2, 0 },
    { PAD_CONFIRM, 1, 0, 0, 0, 0, 5, 1, 2, 0 },
    { PAD_CONFIRM, 2, 0, 0, 0, 1, 4, 0, 0, 1 },
    { PAD_CONFIRM, 2, 0, 0, 0xFF, 0, 4, 0, 0, 3 },
    { PAD_SELECTION_ALT, 0, 0, 0, 0, 1, 4, 0, 0, 1 },
};

static u32 test_load_ports(u32 row)
{
    menu_reset(4, load_ports[row].selection, load_ports[row].pressed);
    memset(&game_info, 0, sizeof(game_info));
    memcard_menu.port = memcard_menu.timer = 0;
    memcard_menu.card_status[0] = load_ports[row].card0;
    memcard_menu.card_status[1] = load_ports[row].card1;
    D_800F1D90.save.character = load_ports[row].saved_character;

    func_8001ABDC(&engine_obj);

    assert(main_bss_state.transition.selection == load_ports[row].expected_selection);
    assert(engine_obj.unk1 == load_ports[row].expected_step);
    assert(memcard_menu.port == load_ports[row].expected_port);
    assert(memcard_menu.timer == load_ports[row].expected_timer);
    assert(game_info.mode == load_ports[row].expected_mode);
    assert(game_info.unk0 == (load_ports[row].expected_mode ? 7 : 0));
    assert(game_info.unk2 == 0 && game_info.unk3 == 0);
    assert(memcard_menu.card_status[0] == load_ports[row].card0);
    assert(memcard_menu.card_status[1] == load_ports[row].card1);
    assert(controller_input.pressed == load_ports[row].pressed);
    return main_bss_state.transition.selection;
}

static const struct {
    u16 pressed;
    u8 selection, character, expected_selection, expected_slot, expected_step, expected_choice;
} load_slots[] = {
    { PADLup, 0, 0, 3, 3, 6, 0 },
    { PADLup, 1, 0, 0, 0, 6, 0 },
    { PADLup, 2, 0, 1, 1, 6, 0 },
    { PADLdown, 3, 0, 0, 0, 6, 0 },
    { PADLdown, 0, 0, 1, 1, 6, 0 },
    { PADLdown, 2, 0, 3, 3, 6, 0 },
    { 0, 1, 0, 1, 1, 6, 0 },
    { PAD_CONFIRM, 1, 0xFF, 1, 1, 6, 0 },
    { PAD_CONFIRM, 1, 0, 0, 1, 7, 1 },
    { PAD_CONFIRM, 2, 1, 0, 2, 7, 2 },
    { PAD_CONFIRM, 3, 0, 0, 3, 0, 0 },
    { PAD_SELECTION_ALT, 1, 0, 0, 1, 0, 0 },
};

static u32 test_load_slots(u32 row)
{
    struct MemcardSaveSlot before[4];
    menu_reset(6, load_slots[row].selection, load_slots[row].pressed);
    menu_slots[load_slots[row].selection].character = load_slots[row].character;
    memcpy(before, menu_slots, sizeof(before));
    memcard_menu.port = 1;
    memcard_menu.selection = 0;

    func_8001B10C(&engine_obj);

    assert(main_bss_state.transition.selection == load_slots[row].expected_selection);
    assert(memcard_menu.slot == &menu_slots[load_slots[row].expected_slot]);
    assert(engine_obj.unk1 == load_slots[row].expected_step);
    assert(memcard_menu.selection == load_slots[row].expected_choice);
    assert(memcard_menu.port == 1);
    c_test_same_words(menu_slots, before, sizeof(before));
    assert(controller_input.pressed == load_slots[row].pressed);
    return (u8)engine_obj.unk1;
}

static const struct {
    u16 pressed;
    u8 result, destination, expected_state, expected_step, expected_cursor;
} save_result_cases[] = {
    { 0, 0, 8, 3, 11, 2 },
    { PADstart, 0, 8, 8, 1, 2 },
    { PAD_CONFIRM, 1, 9, 9, 1, 0 },
    { PAD_CANCEL, 2, 8, 8, 1, 2 },
    { PADRup, 3, 9, 9, 1, 0 },
    { PADstart, 4, 8, 3, 0, 0 },
};

static u32 test_save_result(u32 row)
{
    menu_reset(11, 2, save_result_cases[row].pressed);
    engine_obj.state = 3;
    engine_obj.unk2 = 5;
    engine_obj.unk4 = save_result_cases[row].destination;
    memcard_menu.result = save_result_cases[row].result;
    func_8001A8E8(&engine_obj);
    assert(engine_obj.state == save_result_cases[row].expected_state);
    assert(engine_obj.unk1 == save_result_cases[row].expected_step);
    assert(engine_obj.unk2 == (save_result_cases[row].result == 4 ? 0 : 5));
    assert(main_bss_state.transition.selection == save_result_cases[row].expected_cursor);
    assert(memcard_menu.result == save_result_cases[row].result);
    assert(controller_input.pressed == save_result_cases[row].pressed);
    return engine_obj.state;
}

static const struct {
    u16 pressed;
    u8 result, saved_character, expected_mode, expected_cursor;
} load_result_cases[] = {
    { 0, 0, 0, 5, 2 },
    { PADstart, 0, 0, 1, 1 },
    { PAD_CONFIRM, 1, 1, 1, 1 },
    { PAD_CANCEL, 2, 0xFF, 3, 0 },
    { PADRup, 3, 0xFF, 3, 0 },
    { PADRleft, 4, 0, 1, 1 },
};

static u32 test_load_result(u32 row)
{
    menu_reset(6, 2, load_result_cases[row].pressed);
    memset(&game_info, 0, sizeof(game_info));
    game_info.mode = 5;
    game_info.unk0 = 4;
    game_info.unk2 = 3;
    game_info.unk3 = 2;
    D_800F1D90.save.character = load_result_cases[row].saved_character;
    memcard_menu.result = load_result_cases[row].result;
    func_8001B558(&engine_obj);
    assert(game_info.mode == load_result_cases[row].expected_mode);
    assert(main_bss_state.transition.selection == load_result_cases[row].expected_cursor);
    assert(game_info.unk0 == (load_result_cases[row].pressed ? 7 : 4));
    assert(game_info.unk2 == (load_result_cases[row].pressed ? 0 : 3));
    assert(game_info.unk3 == (load_result_cases[row].pressed ? 0 : 2));
    assert(engine_obj.unk1 == 6);
    assert(memcard_menu.result == load_result_cases[row].result);
    return game_info.mode;
}

static u8 save_confirmation_buffer[0x800];

static void check_save_slot(const struct MemcardSaveSlot* actual, const struct MemcardSaveSlot* expected)
{
    u32 i;
    for (i = 0; i < sizeof(*actual); i++)
        assert(((const u8*)actual)[i] == ((const u8*)expected)[i]);
}
static const struct {
    u16 pressed;
    u8 cursor, next_cursor, outcome;
} save_confirmations[] = {
    { 0, 0, 0, 0 },
    { PADLup, 0, 1, 0 },
    { PADLdown, 1, 0, 0 },
    { PAD_CONFIRM, 0, 0, 2 },
    { PAD_CONFIRM, 1, 0, 1 },
    { PAD_SELECTION_ALT, 0, 0, 1 },
    { PADLup | PAD_CONFIRM, 0, 0, 1 },
    { PADLdown | PAD_CONFIRM, 1, 0, 2 },
    { PAD_CONFIRM | PAD_SELECTION_ALT, 0, 0, 1 },
    { PADLleft, 0, 0, 0 },
};

static u32 test_save_confirmation(u32 row)
{
    u32 variant = row / COUNT(save_confirmations);
    u32 index = row % COUNT(save_confirmations);
    u8 step = variant ? 6 : 5;
    u8 outcome = save_confirmations[index].outcome;
    struct MemcardSaveSlot slot;
    menu_reset(step, save_confirmations[index].cursor, save_confirmations[index].pressed);
    memset(save_confirmation_buffer, 0, sizeof(save_confirmation_buffer));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memcard_menu.buffer = save_confirmation_buffer;
    memcard_menu.slot = &menu_slots[1];
    menu_slots[1].character = CHARACTER_ZERO;
    menu_slots[1].unk1 = 28;
    slot = menu_slots[1];
    memcard_menu.timer = 9;
    memcard_menu.port = 0;
    memcard_menu.result = 5;
    if (variant)
        func_8001A308(&engine_obj);
    else
        func_8001A178(&engine_obj);
    assert(engine_obj.unk1 == (outcome == 1 ? 4 : outcome == 2 ? 7
                                                               : step));
    assert(main_bss_state.transition.selection == save_confirmations[index].next_cursor);
    assert(memcard_menu.timer == (outcome == 2 ? 2 : 9));
    assert(memcard_menu.slot == (outcome == 1 ? (struct MemcardSaveSlot*)(save_confirmation_buffer + 0x200) : &menu_slots[1]));
    check_save_slot(&menu_slots[1], &slot);
    assert(memcard_menu.result == 5 && memcard_menu.port == 0);
    assert(controller_input.pressed == save_confirmations[index].pressed);
    return 1;
}

static const struct {
    u16 pressed;
    u8 timer, remaining, next_step;
} save_notices[] = {
    { PAD_CONFIRM, 140, 139, 9 },
    { PAD_CONFIRM, 122, 121, 9 },
    { PAD_CONFIRM, 121, 120, 10 },
    { 0, 121, 120, 9 },
    { 0, 2, 1, 9 },
    { 0, 1, 0, 10 },
    { PAD_CONFIRM, 0, 255, 9 },
    { PADstart, 2, 1, 9 },
};

static u32 test_save_notice(u32 row)
{
    struct EngineObj expected;
    menu_reset(9, 1, save_notices[row].pressed);
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memcard_menu.timer = save_notices[row].timer;
    expected = engine_obj;
    expected.unk1 = save_notices[row].next_step;
    func_8001A7D4(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    assert(memcard_menu.timer == save_notices[row].remaining);
    assert(controller_input.pressed == save_notices[row].pressed);
    return 1;
}

#ifdef MMX4_PC
enum TestCardKind { CARD_MISSING,
    CARD_BLANK,
    CARD_UNFORMATTED,
    CARD_READ_ERROR,
    CARD_WRITE_ERROR,
    CARD_SAVED,
    CARD_FULL,
    CARD_FULL_SAVED };
static u8 card_image[0x20000], menu_buffer[0x2000];

static void create_test_card(const char* directory, u8 port, u8 kind)
{
    char path[160];
    FILE* file;
    size_t written;
    int closed;
    u32 block;
    if (kind == CARD_MISSING)
        return;
    memset(card_image, 0, sizeof(card_image));
    if (kind != CARD_UNFORMATTED) {
        card_image[0] = 'M';
        card_image[1] = 'C';
        card_image[0x7F] = 0x0E;
        for (block = 1; block < 16; block++) {
            u8* entry = &card_image[block * 0x80];
            u32 byte;
            entry[0] = 0xA0;
            entry[8] = entry[9] = 0xFF;
            if (kind == CARD_FULL || kind == CARD_FULL_SAVED
                || ((kind == CARD_SAVED) && block == 1)) {
                entry[0] = 0x51;
                entry[5] = 0x20;
                snprintf((char*)entry + 10, 21, "OTHER%02u", block);
                if (block == 1 && kind != CARD_FULL)
                    memcpy(entry + 10, "BASLUS-00561", 12);
            }
            for (byte = 0; byte < 0x7F; byte++)
                entry[0x7F] ^= entry[byte];
        }
        if (kind == CARD_SAVED || kind == CARD_FULL_SAVED) {
            card_image[0x2000] = 'S';
            card_image[0x2001] = 'C';
            card_image[0x2002] = 0x11;
            card_image[0x2003] = 1;
            card_image[0x2700] = 0x5A;
        }
    }
    snprintf(path, sizeof(path), "%s/card%u.mcr", directory, port);
    file = fopen(path, "wb");
    assert(file != NULL);
    written = fwrite(card_image, 1, sizeof(card_image), file);
    closed = fclose(file);
    assert(written == sizeof(card_image) && closed == 0);
}

static void remove_test_cards(const char* directory)
{
    char path[160];
    u32 port;
    int removed;
    for (port = 0; port < 2; port++) {
        snprintf(path, sizeof(path), "%s/card%u.mcr", directory, port);
        unlink(path);
    }
    removed = rmdir(directory);
    assert(removed == 0);
}

static const struct {
    u8 load, card, timer, step, result, cursor, remaining, empty;
} card_scan_cases[] = {
    { 0, CARD_MISSING, 2, 3, 5, 2, 1, 0 },
    { 0, CARD_MISSING, 1, 11, 1, 0, 0, 0 },
    { 0, CARD_UNFORMATTED, 1, 4, 5, 0, 0, 0 },
    { 0, CARD_READ_ERROR, 1, 11, 2, 0, 0, 0 },
    { 0, CARD_BLANK, 1, 5, 5, 0, 0, 1 },
    { 1, CARD_MISSING, 2, 3, 5, 2, 1, 0 },
    { 1, CARD_MISSING, 1, 6, 0, 0, 0, 0 },
    { 1, CARD_UNFORMATTED, 1, 6, 1, 0, 0, 0 },
    { 1, CARD_READ_ERROR, 1, 6, 1, 0, 0, 0 },
    { 1, CARD_BLANK, 1, 4, 5, 0, 0, 1 },
    { 0, CARD_SAVED, 1, 5, 5, 0, 0, 0 },
    { 1, CARD_SAVED, 1, 4, 5, 0, 0, 0 },
    { 0, CARD_FULL, 1, 11, 3, 0, 0, 0 },
    { 1, CARD_FULL, 1, 4, 5, 0, 0, 1 },
    { 0, CARD_FULL_SAVED, 1, 5, 5, 0, 0, 0 },
    { 1, CARD_FULL_SAVED, 1, 4, 5, 0, 0, 0 },
};

static void card_menu_reset(char* directory, u8 kind, u8 timer)
{
    char* created = mkdtemp(directory);
    int configured;
    assert(created != NULL);
    create_test_card(directory, 0, kind);
    configured = setenv("MMX4_MEMCARD_DIR", directory, 1);
    assert(configured == 0);
    unsetenv("MMX4_MEMCARD_FAULT_0");
    unsetenv("MMX4_MEMCARD_FAULT_1");
    if (kind == CARD_READ_ERROR || kind == CARD_WRITE_ERROR) {
        configured = setenv("MMX4_MEMCARD_FAULT_0", kind == CARD_READ_ERROR ? "read" : "write", 1);
        assert(configured == 0);
    }
    menu_reset(3, 2, 0);
    memset(&memcard_files, 0, sizeof(memcard_files));
    memset(menu_buffer, 0, sizeof(menu_buffer));
    memcard_menu.buffer = menu_buffer;
    memcard_menu.slot = (struct MemcardSaveSlot*)(menu_buffer + 0x200);
    memcard_menu.port = 0;
    memcard_menu.timer = timer;
    memcard_menu.result = 5;
}

static u32 test_card_scan(u32 row)
{
    char directory[] = "/tmp/mmx4-menu-card-XXXXXX";
    u32 i;
    card_menu_reset(directory, card_scan_cases[row].card, card_scan_cases[row].timer);
    if (card_scan_cases[row].load)
        func_8001AE8C(&engine_obj);
    else
        func_8001989C(&engine_obj);
    remove_test_cards(directory);
    assert(engine_obj.unk1 == card_scan_cases[row].step);
    assert(memcard_menu.result == card_scan_cases[row].result);
    assert(main_bss_state.transition.selection == card_scan_cases[row].cursor);
    assert(memcard_menu.timer == card_scan_cases[row].remaining);
    assert(memcard_menu.port == 0);
    if (card_scan_cases[row].card == CARD_SAVED || card_scan_cases[row].card == CARD_FULL_SAVED) {
        assert(menu_buffer[0] == 'S' && menu_buffer[1] == 'C');
        assert(menu_buffer[0x700] == 0x5A);
    }
    for (i = 0; i < 3; i++)
        assert(memcard_menu.slot[i].character == (card_scan_cases[row].empty ? 0xFF : 0));
    return (u8)engine_obj.unk1;
}

static const struct {
    u8 card, operation, timer, step, result, remaining, empty, cursor;
} card_format_cases[] = {
    { CARD_MISSING, 0, 1, 3, 5, 0, 0, 2 },
    { CARD_MISSING, 0, 0, 11, 0, 0, 0, 0 },
    { CARD_READ_ERROR, 0, 0, 11, 4, 0, 0, 0 },
    { CARD_UNFORMATTED, 0, 0, 4, 5, 2, 1, 2 },
    { CARD_UNFORMATTED, 1, 0, 4, 5, 2, 1, 2 },
    { CARD_BLANK, 0, 0, 4, 5, 2, 1, 2 },
    { CARD_WRITE_ERROR, 0, 0, 6, 4, 0, 0, 2 },
    { CARD_WRITE_ERROR, 1, 0, 11, 4, 0, 0, 2 },
};

static u32 test_card_format(u32 row)
{
    char directory[] = "/tmp/mmx4-menu-card-XXXXXX";
    u32 i;
    card_menu_reset(directory, card_format_cases[row].card, card_format_cases[row].timer);
    engine_obj.unk2 = 2;
    memcard_menu.operation = card_format_cases[row].operation;
    func_80019D04(&engine_obj);
    remove_test_cards(directory);
    assert(engine_obj.unk1 == card_format_cases[row].step);
    assert(engine_obj.unk2 == (card_format_cases[row].timer ? 2 : 0));
    assert(memcard_menu.result == card_format_cases[row].result);
    assert(memcard_menu.timer == card_format_cases[row].remaining);
    assert(main_bss_state.transition.selection == card_format_cases[row].cursor);
    for (i = 0; i < 3; i++)
        assert(memcard_menu.slot[i].character == (card_format_cases[row].empty ? 0xFF : 0));
    return (u8)engine_obj.unk1;
}
static const u8 transfer_cards[] = { CARD_BLANK, CARD_SAVED, CARD_MISSING,
    CARD_READ_ERROR, CARD_WRITE_ERROR, CARD_FULL };

static u32 test_card_transfer(u32 row)
{
    char directory[] = "/tmp/mmx4-menu-card-XXXXXX", path[160];
    u8 expected[0x2000];
    u32 i;
    s32 written, received = -1;
    FILE* file;
    size_t size;
    int positioned, closed;
    card_menu_reset(directory, transfer_cards[row], 0);
    for (i = 0; i < sizeof(menu_buffer); i++)
        menu_buffer[i] = (u8)(i * 17 + 5);
    written = func_8001C8F4(menu_buffer, 0, sizeof(menu_buffer));
    if (written == 0) {
        memcpy(expected, menu_buffer, sizeof(expected));
        memset(menu_buffer, 0xA5, sizeof(menu_buffer));
        received = func_8001CB24(menu_buffer, 0, sizeof(menu_buffer));
        snprintf(path, sizeof(path), "%s/card0.mcr", directory);
        file = fopen(path, "rb");
        assert(file != NULL);
        positioned = fseek(file, 0x2000, SEEK_SET);
        size = fread(card_image, 1, sizeof(expected), file);
        closed = fclose(file);
    } else {
        positioned = closed = 0;
        size = 0;
    }
    remove_test_cards(directory);
    if (transfer_cards[row] == CARD_BLANK || transfer_cards[row] == CARD_SAVED) {
        assert(written == 0 && received == 0);
        assert(expected[3] == 1 && expected[4] == 0x82 && expected[5] == 0x6C);
        assert(positioned == 0 && closed == 0 && size == sizeof(expected));
        for (i = 0; i < sizeof(expected); i++) {
            assert(card_image[i] == expected[i]);
            assert(menu_buffer[i] == (i < 0x800 ? expected[i] : 0xA5));
        }
    } else {
        assert(written != 0);
    }
    return written == 0;
}
static const struct {
    u8 card, timer, step, result, remaining, cursor;
} card_prewrite_cases[] = {
    { CARD_MISSING, 2, 7, 5, 1, 2 },
    { CARD_MISSING, 0, 7, 5, 255, 2 },
    { CARD_MISSING, 1, 11, 1, 0, 0 },
    { CARD_UNFORMATTED, 1, 3, 5, 0, 2 },
    { CARD_READ_ERROR, 1, 11, 1, 0, 0 },
    { CARD_BLANK, 1, 8, 5, 5, 2 },
    { CARD_WRITE_ERROR, 1, 8, 5, 5, 2 },
    { CARD_SAVED, 1, 8, 5, 5, 2 },
    { CARD_FULL, 1, 11, 3, 0, 0 },
    { CARD_FULL_SAVED, 1, 8, 5, 5, 2 },
};

static u32 test_card_prewrite(u32 row)
{
    char directory[] = "/tmp/mmx4-menu-card-XXXXXX";
    u32 port = row / COUNT(card_prewrite_cases);
    u32 index = row % COUNT(card_prewrite_cases);
    u8 kind = card_prewrite_cases[index].card;
    card_menu_reset(directory, kind, card_prewrite_cases[index].timer);
    if (port) {
        create_test_card(directory, 1, kind);
        if (kind == CARD_READ_ERROR || kind == CARD_WRITE_ERROR) {
            int configured = setenv("MMX4_MEMCARD_FAULT_1", kind == CARD_READ_ERROR ? "read" : "write", 1);
            assert(configured == 0);
        }
    }
    memcard_menu.port = port;
    memcard_menu.selection = 1;
    engine_obj.unk1 = 7;
    engine_obj.unk2 = 2;
    func_8001A498(&engine_obj);
    remove_test_cards(directory);
    assert(engine_obj.unk1 == card_prewrite_cases[index].step);
    assert(engine_obj.unk2 == (kind == CARD_UNFORMATTED ? 0 : 2));
    assert(memcard_menu.result == card_prewrite_cases[index].result);
    assert(memcard_menu.timer == card_prewrite_cases[index].remaining);
    assert(main_bss_state.transition.selection == card_prewrite_cases[index].cursor);
    assert(memcard_menu.port == port && memcard_menu.selection == 1);
    assert(memcard_menu.slot == (struct MemcardSaveSlot*)(menu_buffer + 0x200));
    if (engine_obj.unk1 == 8) {
        assert(misc_objects[0].id == 0x2A);
        assert(misc_objects[0].unk2 == 0);
        assert(misc_objects[0].animation_step.fields.frame_index == 0x1B + port * 3);
        assert(misc_objects[0].x_pos.i.hi == 0xA0 && misc_objects[0].y_pos.i.hi == 0x30);
        assert(misc_objects[0].ext.misc_42.unk54 == 8 && misc_objects[0].ext.misc_42.unk55 == 1);
    }
    return 1;
}

static const struct {
    u8 card, timer, step, result, remaining;
} card_write_cases[] = {
    { CARD_BLANK, 2, 8, 5, 1 },
    { CARD_BLANK, 0, 8, 5, 255 },
    { CARD_BLANK, 1, 9, 0, 140 },
    { CARD_SAVED, 1, 9, 0, 140 },
    { CARD_FULL_SAVED, 1, 9, 0, 140 },
    { CARD_MISSING, 1, 11, 1, 0 },
    { CARD_READ_ERROR, 1, 11, 2, 0 },
    { CARD_WRITE_ERROR, 1, 11, 2, 0 },
    { CARD_FULL, 1, 11, 1, 0 },
};

static u32 test_card_write(u32 row)
{
    char directory[] = "/tmp/mmx4-menu-card-XXXXXX", path[160];
    struct MemcardSaveSlot expected;
    u32 i;
    int positioned = -1, closed = -1;
    size_t received = 0;
    FILE* file;
    card_menu_reset(directory, card_write_cases[row].card, card_write_cases[row].timer);
    memset(&expected, 0, sizeof(expected));
    engine_obj.unk1 = 8;
    engine_obj.cur_character = expected.character = CHARACTER_ZERO;
    engine_obj.max_hp = expected.unk1 = 28;
    engine_obj.arm_type = expected.unk2 = 2;
    engine_obj.armor_parts = expected.unk3 = 3;
    engine_obj.palette_flags = expected.unk4 = 0;
    engine_obj.unk5F = expected.unk5 = 5;
    engine_obj.collected_upgrades = expected.unk6 = 0x155;
    engine_obj.unk37 = expected.unk29 = 1;
    D_80171EA9 = expected.unk28 = 1;
    for (i = 0; i < 16; i++)
        D_800EE430[i] = expected.unk8[i] = i * 3 + 1;
    func_8001A710(&engine_obj);
    if (card_write_cases[row].step == 9) {
        snprintf(path, sizeof(path), "%s/card0.mcr", directory);
        file = fopen(path, "rb");
        assert(file != NULL);
        positioned = fseek(file, 0x2000, SEEK_SET);
        received = fread(card_image, 1, sizeof(menu_buffer), file);
        closed = fclose(file);
    }
    remove_test_cards(directory);
    assert(engine_obj.unk1 == card_write_cases[row].step);
    assert(memcard_menu.result == card_write_cases[row].result);
    assert(memcard_menu.timer == card_write_cases[row].remaining);
    if (card_write_cases[row].timer == 1) {
        check_save_slot(memcard_menu.slot, &expected);
        check_save_slot(&D_800F1D90.save, &expected);
        assert(menu_buffer[0] == 's' && menu_buffer[1] == 'c' && menu_buffer[2] == 0x13);
    } else {
        for (i = 0; i < sizeof(menu_buffer); i++)
            assert(menu_buffer[i] == 0);
    }
    if (card_write_cases[row].step == 9) {
        assert(positioned == 0 && closed == 0 && received == sizeof(menu_buffer));
        c_test_same_words(card_image, menu_buffer, sizeof(menu_buffer));
        assert(menu_buffer[3] == 1 && menu_buffer[4] == 0x82 && menu_buffer[5] == 0x6C);
    }
    return 1;
}
static struct MiscObj port_confirm_expected_misc[64];

static void check_filled(const void* memory, u32 size, u8 value)
{
    const u8* bytes = memory;
    u32 i;
    for (i = 0; i < size; i++)
        assert(bytes[i] == value);
}

static void prime_menu_objects(void)
{
    memset(&g_Player, 0x25, sizeof(g_Player));
    memset(&g_Entity, 0x25, sizeof(g_Entity));
#define PRIME_POOL(pool) memset(pool, 0x25, sizeof(pool))
    PRIME_POOL(foo_objects);
    PRIME_POOL(baz_objects);
    PRIME_POOL(weapon_objects);
    PRIME_POOL(main_objects);
    PRIME_POOL(shot_objects);
    PRIME_POOL(visual_objects);
    PRIME_POOL(effect_objects);
    PRIME_POOL(item_objects);
    PRIME_POOL(unk_objects);
    PRIME_POOL(layer_objects);
    PRIME_POOL(g_QuadObjects);
#undef PRIME_POOL
    memset(misc_objects, 0, sizeof(misc_objects));
    misc_objects[0].active = 1;
    misc_objects[0].id = 1;
    memset(&qux_object, 0x25, sizeof(qux_object));
    memset(&bar_object, 0x25, sizeof(bar_object));
    memset(&abc_object, 0x25, sizeof(abc_object));
}

static void check_menu_objects_value(u8 value)
{
#define CHECK_POOL(pool) check_filled(pool, sizeof(pool), value)
    CHECK_POOL(foo_objects);
    CHECK_POOL(baz_objects);
    CHECK_POOL(weapon_objects);
    CHECK_POOL(main_objects);
    CHECK_POOL(shot_objects);
    CHECK_POOL(visual_objects);
    CHECK_POOL(effect_objects);
    CHECK_POOL(item_objects);
    CHECK_POOL(unk_objects);
    CHECK_POOL(layer_objects);
    CHECK_POOL(g_QuadObjects);
#undef CHECK_POOL
    check_filled(&g_Player, sizeof(g_Player), value);
    check_filled(&g_Entity, sizeof(g_Entity), value);
    check_filled(&qux_object, sizeof(qux_object), value);
    check_filled(&bar_object, sizeof(bar_object), value);
    check_filled(&abc_object, sizeof(abc_object), value);
}

static void check_menu_objects_reset(void)
{
    check_menu_objects_value(0);
}

static u32 test_port_confirmation(u32 row)
{
    struct EngineObj expected_engine;
    struct MainBssState expected_main;
    struct MemcardMenuState expected_menu;
    struct ControllerInput input_before;
    u32 i, selection = row / 4, save = (row / 2) & 1;
    u32 cancel = (row & 1) || selection == 2;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&memcard_menu, 0, sizeof(memcard_menu));
    memset(&controller_input, 0, sizeof(controller_input));
    prime_menu_objects();
    memset(port_confirm_expected_misc, 0, sizeof(port_confirm_expected_misc));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    engine_obj.state = 10;
    engine_obj.unk1 = 1;
    engine_obj.unk2 = 2;
    engine_obj.unk4 = save ? 8 : 9;
    engine_obj.unk8 = 77;
    main_bss_state.transition.selection = selection;
    memcard_menu.port = 1;
    memcard_menu.timer = 9;
    memcard_menu.operation = 1;
    controller_input.pressed = row & 1 ? PAD_SELECTION_ALT : CONFIRM;
    controller_input.held = controller_input.pressed;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 5;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 1;
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 9;
    expected_engine = engine_obj;
    expected_main = main_bss_state;
    expected_menu = memcard_menu;
    input_before = controller_input;
    if (cancel) {
        u8* script = save ? D_800F2328 : D_800F2300;
        u32 count = save ? 6 : 5;
        struct MiscObj* logo = &port_confirm_expected_misc[0];
        expected_engine.state = save ? 8 : 9;
        expected_engine.unk1 = 1;
        expected_engine.unk8 = save ? 3 : 2;
        expected_main.transition.selection = save ? 2 : 0;
        logo->active = 1;
        logo->id = 32;
        logo->ext.pointer.unk50 = script;
        logo->x_pos.i.hi = script[0];
        logo->ext.title_logo.palette_shift_value = 1;
        assert(script[count * 2 + 1] == 0xFF);
        for (i = 0; i < count; i++) {
            struct MiscObj* letter = &port_confirm_expected_misc[i + 1];
            letter->active = 1;
            letter->id = 31;
            letter->unk2 = script[i * 2 + 1];
            letter->unk7 = i;
            letter->y_pos.i.hi = script[i * 2 + 2] & 0xF0;
            letter->ext.title_logo.palette_shift_value = 1;
        }
    } else {
        static const u8 ys[] = { 64, 16, 112 };
        static const u8 frames[] = { 0, 60, 61 };
        expected_engine.unk1 = 2;
        expected_menu.port = selection;
        expected_menu.timer = 2;
        for (i = 0; i < 3; i++) {
            struct MiscObj* label = &port_confirm_expected_misc[i];
            label->active = 0x41;
            label->id = 42;
            label->x_pos.i.hi = 160;
            label->y_pos.i.hi = ys[i];
            label->animation_step.fields.frame_index = i == 0 ? selection + 11 : frames[i];
            label->ext.misc_42.unk54 = 2;
            label->ext.misc_42.unk55 = 1;
            label->ext.misc_42.unk56 = 0xFF;
        }
    }
    func_8001961C(&engine_obj);
    c_test_same_words(&engine_obj, &expected_engine, sizeof(expected_engine));
    c_test_same_words(&main_bss_state, &expected_main, sizeof(expected_main));
    c_test_same_words(&memcard_menu, &expected_menu, sizeof(expected_menu));
    assert(controller_input.held == input_before.held);
    assert(controller_input.previous == input_before.previous);
    assert(controller_input.pressed == input_before.pressed);
    c_test_same_words(misc_objects, port_confirm_expected_misc, sizeof(misc_objects));
    if (cancel)
        assert(misc_objects[0].ext.pointer.unk50 == (save ? D_800F2328 : D_800F2300));
    check_menu_objects_reset();
    assert(g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0);
    assert(g_FilterModeR == 0 && g_FilterModeG == 0 && g_FilterModeB == 0);
    for (i = 0; i < 4; i++)
        assert(D_8013E188[i] == 0);
    return 1;
}

static const u8 entry_cards[][2] = {
    { CARD_MISSING, CARD_MISSING },
    { CARD_BLANK, CARD_MISSING },
    { CARD_MISSING, CARD_BLANK },
    { CARD_BLANK, CARD_BLANK },
    { CARD_UNFORMATTED, CARD_MISSING },
    { CARD_MISSING, CARD_UNFORMATTED },
    { CARD_SAVED, CARD_FULL },
    { CARD_READ_ERROR, CARD_WRITE_ERROR },
};
static u32 entry_buffer_words[0x2008 / 4];
static u8 entry_card_before[2][0x20000];

static void entry_label(u32 index, u8 step, s16 y, u8 frame, u8 selection)
{
    struct MiscObj* obj = &port_confirm_expected_misc[index];
    obj->active = 0x41;
    obj->id = 42;
    obj->x_pos.i.hi = 160;
    obj->y_pos.i.hi = y;
    obj->animation_step.fields.frame_index = frame;
    obj->ext.misc_42.unk54 = step;
    obj->ext.misc_42.unk55 = 1;
    obj->ext.misc_42.unk56 = selection;
}

static u32 test_card_menu_entry(u32 row)
{
    static const u8 prompt_y[5] = { 16, 48, 64, 176, 208 };
    static const u8 prompt_frame[5] = { 8, 9, 10, 13, 5 };
    static const u8 missing_y[5] = { 16, 64, 96, 112, 208 };
    static const u8 missing_frame[5] = { 62, 64, 65, 66, 63 };
    struct EngineObj expected_engine;
    struct MainBssState expected_main;
    struct MemcardMenuState expected_menu;
    struct ControllerInput input_before;
    char directory[] = "/tmp/mmx4-menu-entry-XXXXXX";
    u32 index = row / 2, load = row % 2, i, port, count = 0;
    u32 available = entry_cards[index][0] != CARD_MISSING || entry_cards[index][1] != CARD_MISSING;
    u8 step = available ? 1 : load ? 6
                                   : 11;
    u8* buffer = (u8*)entry_buffer_words + 4;
    char* created = mkdtemp(directory);
    int configured;
    assert(created != NULL);
    unsetenv("MMX4_MEMCARD_FAULT_0");
    unsetenv("MMX4_MEMCARD_FAULT_1");
    configured = setenv("MMX4_MEMCARD_DIR", directory, 1);
    assert(configured == 0);
    for (port = 0; port < 2; port++) {
        u8 kind = entry_cards[index][port];
        create_test_card(directory, port, kind);
        if (kind != CARD_MISSING)
            memcpy(entry_card_before[port], card_image, sizeof(card_image));
        if (kind == CARD_READ_ERROR || kind == CARD_WRITE_ERROR) {
            configured = setenv(port ? "MMX4_MEMCARD_FAULT_1" : "MMX4_MEMCARD_FAULT_0",
                kind == CARD_READ_ERROR ? "read" : "write", 1);
            assert(configured == 0);
        }
    }
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&memcard_menu, 0, sizeof(memcard_menu));
    memset(&controller_input, 0, sizeof(controller_input));
    prime_menu_objects();
    memset(port_confirm_expected_misc, 0, sizeof(port_confirm_expected_misc));
    memset(entry_buffer_words, 0xA5, sizeof(entry_buffer_words));
    memset(WINDOW_ARCHIVE_DATA, 0x7C, 0x3000);
    ((s32*)WINDOW_ARCHIVE_DATA)[1] = 8;
    D_8015D9C8 = buffer;
    engine_obj.state = load ? 11 : 10;
    engine_obj.unk1 = 0;
    engine_obj.unk2 = 0x2A;
    engine_obj.unk4 = 0x1234;
    engine_obj.cur_character = index & 1;
    main_bss_state.frame_counter = 0x13572468;
    main_bss_state.transition.active = -1;
    main_bss_state.transition.fade_amount = 3;
    main_bss_state.transition.selection = 2;
    memcard_menu.buffer = menu_buffer;
    memcard_menu.slot = &menu_slots[1];
    memcard_menu.card_status[0] = memcard_menu.card_status[1] = 0x24;
    memcard_menu.port = 1;
    memcard_menu.selection = 2;
    memcard_menu.result = 5;
    memcard_menu.operation = 0x25;
    memcard_menu.timer = 9;
    controller_input.held = PADLdown;
    controller_input.pressed = PAD_CONFIRM;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 5;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 1;
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 9;
    need_palette_load = 0x80;
    expected_engine = engine_obj;
    expected_engine.unk1 = step;
    if (load || available)
        expected_engine.unk2 = 0;
    expected_main = main_bss_state;
    expected_main.transition.selection = 0;
    expected_menu = memcard_menu;
    expected_menu.buffer = buffer;
    expected_menu.slot = (struct MemcardSaveSlot*)(buffer + 0x200);
    expected_menu.operation = load ? 0 : 1;
    expected_menu.card_status[0] = entry_cards[index][0] == CARD_MISSING;
    expected_menu.card_status[1] = entry_cards[index][1] == CARD_MISSING;
    if (!available)
        expected_menu.result = 0;
    input_before = controller_input;
    if (load && available) {
        for (port = 0; port < 2; port++)
            if (entry_cards[index][port] != CARD_MISSING)
                entry_label(count++, step, port ? 144 : 112, 11 + port, port);
    }
    for (i = 0; i < 5; i++) {
        u8 frame = available ? prompt_frame[i] : missing_frame[i];
        if (available && !load && i == 0)
            frame = 50;
        entry_label(count++, step, available ? prompt_y[i] : missing_y[i], frame,
            available && i == 3 ? 2 : 0xFF);
    }
    if (available) {
        struct MiscObj* cursor;
        if (!load) {
            for (port = 0; port < 2; port++)
                if (entry_cards[index][port] != CARD_MISSING)
                    entry_label(count++, step, port ? 144 : 112, 11 + port, port);
        }
        cursor = &port_confirm_expected_misc[count];
        cursor->active = 1;
        cursor->id = 42;
        cursor->unk2 = 4;
        cursor->unk42 = 0x7806;
        cursor->ext.misc_42.unk54 = 1;
        cursor->ext.misc_42.unk55 = 1;
        cursor->ext.misc_42.unk56 = 2;
    }
    if (load)
        func_8001AA98(&engine_obj);
    else
        func_800194C8(&engine_obj);
    c_test_same_words(&engine_obj, &expected_engine, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &expected_main, sizeof(main_bss_state));
    c_test_same_words(&memcard_menu, &expected_menu, sizeof(memcard_menu));
    assert(controller_input.held == input_before.held);
    assert(controller_input.previous == input_before.previous);
    assert(controller_input.pressed == input_before.pressed);
    c_test_same_words(misc_objects, port_confirm_expected_misc, sizeof(misc_objects));
    check_menu_objects_reset();
    assert(D_8015D9C8 == buffer && need_palette_load == 0x80);
    assert(g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0);
    assert(g_FilterModeR == 0 && g_FilterModeG == 0 && g_FilterModeB == 0);
    for (i = 0; i < 4; i++)
        assert(D_8013E188[i] == 0);
    for (i = 0; i < COUNT(entry_buffer_words); i++)
        assert(entry_buffer_words[i] == (i > 0 && i < 0x800 ? 0 : 0xA5A5A5A5u));
    for (port = 0; port < 2; port++) {
        char path[160];
        FILE* file;
        size_t received;
        int closed;
        if (entry_cards[index][port] == CARD_MISSING)
            continue;
        snprintf(path, sizeof(path), "%s/card%u.mcr", directory, port);
        file = fopen(path, "rb");
        assert(file != NULL);
        received = fread(card_image, 1, sizeof(card_image), file);
        closed = fclose(file);
        assert(received == sizeof(card_image) && closed == 0);
        c_test_same_words(card_image, entry_card_before[port], 0x1F80);
        c_test_same_words(card_image + 0x2000, entry_card_before[port] + 0x2000, sizeof(card_image) - 0x2000);
    }
    remove_test_cards(directory);
    return 1;
}

static u8 load_confirmation_before[sizeof(menu_buffer)];

static u32 test_load_confirmation(u32 row)
{
    static const u8 ys[7] = { 16, 64, 112, 128, 144, 176, 208 };
    static const u8 frames[7] = { 8, 19, 20, 21, 22, 23, 5 };
    static const u8 selections[7] = { 0xFF, 0xFF, 0, 1, 2, 3, 0xFF };
    struct EngineObj expected_engine;
    struct MainBssState expected_main;
    struct MemcardMenuState expected_menu;
    struct ControllerInput input_before;
    struct MenuRuntimeData expected_runtime;
    struct GameThread expected_threads[4];
    struct MemcardSaveSlot* first = (struct MemcardSaveSlot*)(menu_buffer + 0x200);
    struct MemcardSaveSlot* slot;
    u16 expected_buttons[16];
    u32 variant = row / COUNT(save_confirmations), index = row % COUNT(save_confirmations);
    u32 port = (variant >> 1) & 1, bonus = variant >> 2;
    u32 outcome = save_confirmations[index].outcome, i;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&memcard_menu, 0, sizeof(memcard_menu));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(menu_buffer, 0, sizeof(menu_buffer));
    memset(expected_threads, 0, sizeof(expected_threads));
    prime_menu_objects();
    first->character = CHARACTER_ZERO;
    first->unk1 = 16;
    slot = &first[port + 1];
    slot->character = variant & 1;
    slot->unk1 = 24 + variant;
    slot->unk2 = 2;
    slot->unk3 = 5;
    slot->unk4 = 0xA5;
    slot->unk5 = 0x36;
    slot->unk6 = 0x125 | (bonus ? D_800F1D90.sign_bit_mask : 0);
    slot->unk28 = 5;
    slot->unk29 = variant & 1;
    for (i = 0; i < 16; i++)
        slot->unk8[i] = 0x1000 + i * 17;
    memcpy(load_confirmation_before, menu_buffer, sizeof(menu_buffer));
    memcard_menu.buffer = menu_buffer;
    memcard_menu.slot = slot;
    memcard_menu.port = port;
    memcard_menu.selection = port + 1;
    memcard_menu.result = 5;
    memcard_menu.timer = 9;
    memcard_menu.card_status[0] = 0;
    memcard_menu.card_status[1] = 1;
    engine_obj.state = 11;
    engine_obj.unk1 = 4;
    engine_obj.unk2 = 2;
    engine_obj.unk4 = 0x1234;
    engine_obj.cur_character = slot->character ^ 1;
    engine_obj.max_hp = 12;
    engine_obj.checkpoint_hp = 7;
    engine_obj.player_lives = 1;
    engine_obj.sub_tanks[0] = 10;
    engine_obj.sub_tanks[1] = 11;
    engine_obj.sub_tanks[2] = 12;
    main_bss_state.frame_counter = 0x13572468;
    main_bss_state.transition.selection = save_confirmations[index].cursor;
    controller_input.pressed = save_confirmations[index].pressed;
    controller_input.held = controller_input.pressed;
    memset(&D_800F1D90.save, 0, sizeof(D_800F1D90.save));
    D_800F1D90.save.character = CHARACTER_ZERO;
    D_800F1D90.save.unk1 = 16;
    D_800F1D90.save.unk29 = 1;
    D_80171EA9 = 0x17;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 5;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 1;
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 9;
    mmx4_pc_threads_init();
    if (bonus) {
        func_800129F0(3);
        expected_threads[2].state = 2;
    }
    expected_engine = engine_obj;
    expected_main = main_bss_state;
    expected_main.transition.selection = save_confirmations[index].next_cursor;
    expected_menu = memcard_menu;
    expected_runtime = D_800F1D90;
    memcpy(expected_buttons, D_800EE430, sizeof(expected_buttons));
    input_before = controller_input;
    memcpy(port_confirm_expected_misc, misc_objects, sizeof(misc_objects));
    if (outcome != 0)
        memset(port_confirm_expected_misc, 0, sizeof(port_confirm_expected_misc));
    if (outcome == 1) {
        struct MiscObj* preview = &port_confirm_expected_misc[8];
        struct MiscObj* portrait = &port_confirm_expected_misc[9];
        struct MiscObj* cursor = &port_confirm_expected_misc[10];
        expected_engine.unk1 = 3;
        expected_menu.slot = first;
        entry_label(0, 2, 48, port + 17, 0xFF);
        for (i = 0; i < 7; i++)
            entry_label(i + 1, 2, ys[i], frames[i], selections[i]);
        for (i = 0; i < 8; i++)
            port_confirm_expected_misc[i].ext.misc_42.unk55 = 2;
        preview->active = 0x41;
        preview->id = 42;
        preview->unk2 = 1;
        preview->animation_step.fields.frame_index = 42;
        preview->x_pos.i.hi = 208;
        preview->y_pos.i.hi = 136;
        preview->ext.misc_42.unk55 = 3;
        portrait->active = 1;
        portrait->id = 42;
        portrait->unk2 = 2;
        portrait->unk16 = 4;
        portrait->animation_step.fields.frame_index = 43;
        portrait->unk42 = 0x7808;
        portrait->x_pos.i.hi = 144;
        portrait->y_pos.i.hi = 136;
        portrait->ext.misc_42.unk55 = 3;
        cursor->active = 1;
        cursor->id = 42;
        cursor->unk2 = 4;
        cursor->unk42 = 0x7806;
        cursor->ext.misc_42.unk54 = 3;
        cursor->ext.misc_42.unk55 = 1;
        cursor->ext.misc_42.unk56 = 3;
        cursor->ext.misc_42.unk58 = 1;
    } else if (outcome == 2) {
        struct MemcardSaveSlot* cached = &expected_runtime.save;
        expected_engine.unk1 = 5;
        expected_engine.cur_character = slot->character;
        expected_engine.max_hp = expected_engine.checkpoint_hp = slot->unk1;
        expected_engine.arm_type = slot->unk2;
        expected_engine.armor_parts = slot->unk3;
        expected_engine.palette_flags = slot->unk4;
        expected_engine.unk5F = slot->unk5;
        expected_engine.collected_upgrades = slot->unk6;
        expected_engine.unk37 = slot->unk29;
        expected_engine.player_lives = bonus ? 4 : 2;
        expected_engine.sub_tanks[0] = expected_engine.sub_tanks[1] = expected_engine.sub_tanks[2] = 0;
        memcpy(expected_buttons, slot->unk8, sizeof(expected_buttons));
        cached->character = slot->character;
        cached->unk1 = slot->unk1;
        cached->unk2 = slot->unk2;
        cached->unk3 = slot->unk3;
        cached->unk4 = slot->unk4;
        cached->unk5 = slot->unk5;
        cached->unk6 = slot->unk6;
        cached->unk29 = slot->unk29;
        memcpy(cached->unk8, slot->unk8, sizeof(cached->unk8));
        cached->unk28 = 0x17;
        if (!bonus) {
            expected_main.transition.active = -1;
            expected_main.transition.fade_amount = 8;
            expected_threads[2].state = 2;
        }
    }
    func_8001B388(&engine_obj);
    c_test_same_words(&engine_obj, &expected_engine, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &expected_main, sizeof(main_bss_state));
    c_test_same_words(&memcard_menu, &expected_menu, sizeof(memcard_menu));
    same_bytes(&controller_input, &input_before, sizeof(controller_input));
    same_bytes(&D_800F1D90, &expected_runtime, sizeof(expected_runtime));
    same_bytes(D_800EE430, expected_buttons, sizeof(expected_buttons));
    same_bytes(menu_buffer, load_confirmation_before, sizeof(menu_buffer));
    c_test_same_words(misc_objects, port_confirm_expected_misc, sizeof(misc_objects));
    check_menu_objects_value(outcome ? 0 : 0x25);
    assert(D_80171EA9 == 0x17);
    assert(D_801F8300 == mmx4_pc_thread_slot(0));
    for (i = 0; i < 4; i++) {
        c_test_same_words(mmx4_pc_thread_slot(i), &expected_threads[i], sizeof(expected_threads[i]));
        assert(D_8013E188[i] == (outcome ? 0 : 9));
    }
    assert(g_FilterAmountR == (outcome ? 0 : 5));
    assert(g_FilterAmountG == (outcome ? 0 : 5));
    assert(g_FilterAmountB == (outcome ? 0 : 5));
    assert(g_FilterModeR == (outcome ? 0 : 1));
    assert(g_FilterModeG == (outcome ? 0 : 1));
    assert(g_FilterModeB == (outcome ? 0 : 1));
    return 1;
}

#define CARD_MENU_CASE_COUNT (COUNT(card_scan_cases) + COUNT(card_format_cases) + COUNT(transfer_cards) + 2 * COUNT(card_prewrite_cases) + COUNT(card_write_cases) + 12 + COUNT(entry_cards) * 2 + COUNT(save_confirmations) * 8)
#else
#define CARD_MENU_CASE_COUNT 0
#endif

static u32 dispatch_timer(u32 row)
{
    struct EngineObj expected;
    struct MemcardMenuState menu_expected;
    struct MainBssState main_before = main_bss_state;
    struct PlayerObj player_before = g_Player;
    struct ControllerInput input;
    engine_obj.state = 8;
    engine_obj.unk1 = 9;
    engine_obj.unk2 = 0;
    engine_obj.unk4 = 8;
    expected = engine_obj;
    expected.unk1 = 10;
    memcard_menu.timer = 1;
    menu_expected = memcard_menu;
    menu_expected.timer = 0;
    controller_input.held = 0x1357;
    controller_input.previous = 0x2468;
    controller_input.pressed = row ? PAD_CONFIRM : 0;
    input = controller_input;
    D_8013E198[0] = -1;
    func_800193D8(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(engine_obj));
    c_test_same_words(&memcard_menu, &menu_expected, sizeof(memcard_menu));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(D_8013E198[0] == -1);
    return 1;
}

extern SPRT D_80139268[2][17];
extern DR_MODE D_80139250[2];
static const u16 buttons[] = { 0, PADLup, PADLdown, PADLup | PADLdown };
static const u8 up[4][3] = { { 2, 0, 1 }, { 2, 2, 1 }, { 2, 0, 0 }, { 2, 2, 2 } };
static const u8 down[4][3] = { { 1, 2, 0 }, { 1, 2, 1 }, { 2, 2, 0 }, { 2, 2, 2 } };
static const s16 layout[17][4] = {
    { 0, 0, 112, 0 },
    { 112, 0, 96, 112 },
    { 208, 0, 112, 0 },
    { 0, 48, 96, 112 },
    { 96, 48, 112, 0 },
    { 208, 48, 96, 112 },
    { 304, 48, 16, 0 },
    { 0, 96, 112, 0 },
    { 112, 96, 96, 112 },
    { 208, 96, 112, 0 },
    { 0, 144, 96, 112 },
    { 96, 144, 112, 0 },
    { 208, 144, 96, 112 },
    { 304, 144, 16, 0 },
    { 0, 192, 112, 0 },
    { 112, 192, 96, 112 },
    { 208, 192, 112, 0 },
};
static struct DrawInfo drawing, drawing_expected;
static SPRT sprites_expected[2][17];
static DR_MODE modes_expected[2];
static P_TAG sentinel;
static u32 zero_pool[sizeof(main_objects) / 4];
#define POOLS(X)       \
    X(g_Player);       \
    X(g_Entity);       \
    X(baz_objects);    \
    X(foo_objects);    \
    X(main_objects);   \
    X(weapon_objects); \
    X(shot_objects);   \
    X(visual_objects); \
    X(item_objects);   \
    X(misc_objects);   \
    X(unk_objects);    \
    X(qux_object);     \
    X(g_QuadObjects)
#define ZERO(p) c_test_zero_words((u32*)&(p), sizeof(p) / 4)
#define SAME_ZERO(p) assert(sizeof(p) <= sizeof(zero_pool) && c_test_word_difference((u32*)&(p), zero_pool, sizeof(p) / 4) == 0)
static u32 navigate_menu_navigation_dispatch(u32 row)
{
    struct EngineObj engine_before;
    struct MemcardMenuState menu_before;
    struct MainBssState main_expected;
    struct ControllerInput input;
    u32 load = row % 2, selected = row / 2 % 3, cards = row / 6 % 4, press = row / 24 % 4, buffer = row / 96, next = selected, i, b, g, p;
    POOLS(ZERO);
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&memcard_menu, 0, sizeof(memcard_menu));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&drawing, 0, sizeof(drawing));
    memset(&sentinel, 0, sizeof(sentinel));
    memset(D_80139268, 0xA5, sizeof(sprites_expected));
    memset(D_80139250, 0x5A, sizeof(modes_expected));
    memcpy(sprites_expected, D_80139268, sizeof(sprites_expected));
    memcpy(modes_expected, D_80139250, sizeof(modes_expected));
    drawing_expected = drawing;
    engine_obj.state = load ? 11 : 10;
    engine_obj.unk1 = 1;
    engine_obj.unk4 = 8;
    engine_before = engine_obj;
    memcard_menu.card_status[0] = cards & 1;
    memcard_menu.card_status[1] = (cards >> 1) & 1;
    memcard_menu.timer = 9;
    memcard_menu.port = 1;
    menu_before = memcard_menu;
    main_bss_state.frame_counter = 7;
    main_bss_state.transition.active = 1;
    main_bss_state.transition.fade_amount = 3;
    main_bss_state.transition.selection = selected;
    main_expected = main_bss_state;
    if (buttons[press] & PADLup)
        next = up[cards][next];
    if (buttons[press] & PADLdown)
        next = down[cards][next];
    main_expected.transition.selection = next;
    controller_input.held = 0x1357;
    controller_input.previous = 0x2468;
    controller_input.pressed = buttons[press];
    input = controller_input;
    D_8013E198[0] = -1;
    for (b = 0; b < 2; b++)
        for (g = 0; g < 4; g++)
            for (p = 0; p < 8; p++)
                D_8013BC40[b][g][p] = D_8013E1E8[b][g][p] = &sentinel;
    SP_DRAW_BUFFER = buffer;
    SP_SPRITE_COUNT = 17;
    cur_draw_info = &drawing;
    func_80023D30();
    for (i = 0; i < 17; i++) {
        SPRT* sprite = &sprites_expected[buffer][i];
        setlen(sprite, 4);
        sprite->code = 0x65;
        sprite->u0 = layout[i][3];
        sprite->v0 = 0xD0;
        sprite->clut = 0x784C;
        sprite->x0 = layout[i][0];
        sprite->y0 = layout[i][1];
        sprite->w = layout[i][2];
        sprite->h = 48;
        setaddr(sprite, i ? (void*)&D_80139268[buffer][i - 1] : NULL);
    }
    setlen(&modes_expected[buffer], 2);
    modes_expected[buffer].code[0] = 0xE100001E;
    modes_expected[buffer].code[1] = 0;
    setaddr(&modes_expected[buffer], &D_80139268[buffer][16]);
    setaddr(&drawing_expected.ordering_table.ui, &D_80139250[buffer]);
    if (load)
        func_8001A9EC(&engine_obj);
    else
        func_800193D8(&engine_obj);
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&memcard_menu, &menu_before, sizeof(memcard_menu));
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    POOLS(SAME_ZERO);
    c_test_same_words(D_80139268, sprites_expected, sizeof(sprites_expected));
    c_test_same_words(D_80139250, modes_expected, sizeof(modes_expected));
    c_test_same_words(&drawing, &drawing_expected, sizeof(drawing));
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && D_8013E198[0] == -1);
    assert(SP_SPRITE_COUNT == 0 && SP_DRAW_BUFFER == buffer && cur_draw_info == &drawing && SP_CUR_MISC_OBJ == misc_objects + COUNT(misc_objects));
    assert(SP_PRIM_CURSOR == temp1[buffer].data && SP_DRAW_MODE_CURSOR == temp2[buffer].data && SP_BG_PRIM_CURSOR == temp3[buffer].data && SP_OT_CURSOR == temp4[buffer].data && SP_AUX_CURSOR == temp5[buffer].data);
    for (b = 0; b < 2; b++)
        for (g = 0; g < 4; g++)
            for (p = 0; p < 8; p++) {
                assert(D_8013E1E8[b][g][p] == (b == buffer ? NULL : &sentinel));
                assert(D_8013BC40[b][g][p] == (b == buffer ? (P_TAG*)&D_8013E1E8[b][g][p] : &sentinel));
            }
    return 1;
}

extern u8 D_800F22D0[16], D_800F22E0[16], D_800F22F0[16], D_800F2310[12];
void func_80019BF4(struct EngineObj* arg0);
void func_8001A860(struct EngineObj* arg0);
static struct MiscObj expected_misc[64];
static u32 window_before[0xC00], window_words[0xC00];
static const struct {
    u16 pressed;
    u8 selection, accept;
} confirmations[] = {
    { PAD_CONFIRM, 0, 1 },
    { PAD_CONFIRM, 1, 0 },
    { PAD_SELECTION_ALT, 0, 0 },
    { PAD_SELECTION_ALT, 1, 0 },
    { PADLup | PAD_CONFIRM, 0, 0 },
    { PADLup | PAD_CONFIRM, 1, 1 },
    { PADLdown | PAD_CONFIRM, 0, 0 },
    { PADLdown | PAD_CONFIRM, 1, 1 },
    { PADLup | PADLdown | PAD_CONFIRM, 0, 0 },
    { PADLup | PADLdown | PAD_CONFIRM, 1, 1 },
    { PAD_CONFIRM | PAD_SELECTION_ALT, 0, 0 },
    { PAD_CONFIRM | PAD_SELECTION_ALT, 1, 0 },
};
static void fill(void* address, u32 size, u32 value)
{
    u32* words = address;
    u32 i;
    for (i = 0; i < size / 4; i++)
        words[i] = value;
}
static void zero_check(const void* address, u32 size)
{
    const u32* words = address;
    u32 i;
    for (i = 0; i < size / 4; i++)
        assert(words[i] == 0);
}
#define RESET_POOLS(X) \
    X(g_Player);       \
    X(g_Entity);       \
    X(foo_objects);    \
    X(baz_objects);    \
    X(weapon_objects); \
    X(main_objects);   \
    X(shot_objects);   \
    X(visual_objects); \
    X(effect_objects); \
    X(item_objects);   \
    X(unk_objects);    \
    X(layer_objects);  \
    X(g_QuadObjects);  \
    X(qux_object);     \
    X(bar_object);     \
    X(abc_object)
#define PRIME(pool) fill(&(pool), sizeof(pool), 0x25252525)
#define ZERO_menu_reset_transitions(pool) zero_check(&(pool), sizeof(pool))
static void setup(void)
{
    u32 i;
    RESET_POOLS(PRIME);
    PRIME(misc_objects);
    memset(expected_misc, 0, sizeof(expected_misc));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&memcard_menu, 0, sizeof(memcard_menu));
    memset(&controller_input, 0, sizeof(controller_input));
    engine_obj.state = 8;
    engine_obj.unk1 = 3;
    engine_obj.unk2 = 1;
    engine_obj.unk3 = 7;
    engine_obj.unk8 = 77;
    engine_obj.stage = 5;
    main_bss_state.transition.active = 1;
    main_bss_state.transition.fade_amount = 3;
    for (i = 0; i < 3; i++) {
        memset(&background_objects[i], 0, sizeof(background_objects[i]));
        background_objects[i].unk3 = i + 1;
        background_objects[i].x_pos.val = i * 0x12345;
    }
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 17;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 3;
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 7;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
}
static void check_reset(void)
{
    u32 i;
    RESET_POOLS(ZERO_menu_reset_transitions);
    c_test_same_words(misc_objects, expected_misc, sizeof(expected_misc));
    assert(g_FilterAmountR == 0 && g_FilterAmountG == 0 && g_FilterAmountB == 0);
    assert(g_FilterModeR == 0 && g_FilterModeG == 0 && g_FilterModeB == 0);
    for (i = 0; i < 4; i++)
        assert(D_8013E188[i] == 0);
}
static void expected_label(u32 index, s16 y, u8 frame)
{
    struct MiscObj* obj = &expected_misc[index];
    obj->active = 0x41;
    obj->id = 42;
    obj->x_pos.i.hi = 160;
    obj->y_pos.i.hi = y;
    obj->animation_step.fields.frame_index = frame;
    obj->ext.misc_42.unk54 = 2;
    obj->ext.misc_42.unk55 = 2;
    obj->ext.misc_42.unk56 = 255;
}
static u32 format_confirmation(u32 row)
{
    struct EngineObj engine_expected;
    struct MainBssState main_expected;
    struct MemcardMenuState menu_expected;
    struct BackgroundObj backgrounds_before[3];
    struct ControllerInput input;
    u32 c = row % COUNT(confirmations), port = row / COUNT(confirmations);
    setup();
    controller_input.pressed = confirmations[c].pressed;
    controller_input.held = 0x1357;
    main_bss_state.transition.selection = confirmations[c].selection;
    memcard_menu.port = port;
    memcard_menu.timer = 9;
    memcard_menu.operation = 1;
    engine_expected = engine_obj;
    main_expected = main_bss_state;
    menu_expected = memcard_menu;
    input = controller_input;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    main_expected.transition.selection = 0;
    if (confirmations[c].accept) {
        engine_expected.unk2 = 2;
        menu_expected.timer = 2;
        expected_label(0, 16, 58);
        expected_label(1, 112, 59);
        expected_label(2, 64, port + 11);
    } else {
        engine_expected.unk1 = 0;
        engine_expected.unk2 = 0;
    }
    func_80019BF4(&engine_obj);
    check_reset();
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    c_test_same_words(&memcard_menu, &menu_expected, sizeof(memcard_menu));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    assert(controller_input.held == input.held && controller_input.pressed == input.pressed && controller_input.previous == input.previous);
    return 1;
}
static const u8 menu_rows[5][6][2] = {
    { { 0x54, 0x40 }, { 0x55, 0x70 }, { 0x58, 0xB0 }, { 0x53, 0x10 }, { 5, 0xD0 } },
    { { 3, 0x70 }, { 0x73, 0x90 }, { 0, 0x10 }, { 1, 0x30 }, { 2, 0x40 }, { 5, 0xD0 } },
    { { 0x73, 0x90 }, { 3, 0x70 }, { 0, 0x10 }, { 1, 0x30 }, { 2, 0x40 }, { 5, 0xD0 } },
    { { 0x2E, 0x40 }, { 0x31, 0x60 }, { 0x2C, 0x90 }, { 0x2F, 0x10 }, { 0x72, 0xD0 } },
    { { 0x2E, 0x40 }, { 0x2C, 0x70 }, { 0x29, 0x10 }, { 0x72, 0xD0 } },
};
static const u8 row_counts[] = { 5, 6, 6, 5, 4 };
static u32 menu_rebuild(u32 row)
{
    struct EngineObj engine_expected;
    struct GameInfo info, info_expected;
    struct MainBssState main_expected;
    struct MemcardMenuState menu_before;
    struct MenuRuntimeData runtime_before;
    struct BackgroundObj backgrounds_expected[3];
    u32 kind = row % 4, empty = row / 4, bank = kind == 0 ? 0 : kind == 1 ? 1 + empty
                                                                          : kind + 1;
    u32 i, start = kind == 0 ? 1 : 0;
    u8* scripts[5];
    struct MiscObj* cursor;
    scripts[0] = D_800F22F0;
    scripts[1] = D_800F22D0;
    scripts[2] = D_800F22E0;
    scripts[3] = D_800F2338;
    scripts[4] = D_800F2310;
    setup();
    memset(&info, 0x25, sizeof(info));
    info.mode = 0;
    engine_obj.unk4 = kind == 2 ? 8 : 9;
    D_800F1D90.save.character = empty ? 255 : 0;
    runtime_before = D_800F1D90;
    c_test_copy_words(window_before, (u32*)WINDOW_ARCHIVE_DATA, COUNT(window_before));
    for (i = 0; i < COUNT(window_words); i++)
        window_words[i] = 0xA55A0000u + i;
    window_words[1] = 0x100;
    c_test_copy_words((u32*)WINDOW_ARCHIVE_DATA, window_words, COUNT(window_words));
    engine_expected = engine_obj;
    main_expected = main_bss_state;
    menu_before = memcard_menu;
    info_expected = info;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    if (kind < 2) {
        for (i = 0; i < 3; i++)
            backgrounds_expected[i].unk3 = 0;
        info_expected.unk8 = kind == 0 ? 2 : !empty;
        info_expected.mode = kind == 0 || !empty ? 1 : 3;
    } else {
        engine_expected.unk1 = 3;
        engine_expected.unk2 = engine_expected.unk3 = 0;
        engine_expected.unk8 = kind == 2 ? 2 : 1;
        engine_expected.state = kind == 2 ? 8 : 9;
    }
    if (kind == 0) {
        expected_misc[0].active = 1;
        expected_misc[0].id = 31;
        expected_misc[0].unk2 = 0x56;
        expected_misc[0].y_pos.i.hi = 128;
    }
    cursor = &expected_misc[start];
    cursor->active = 1;
    cursor->id = 32;
    cursor->ext.pointer.unk50 = scripts[bank];
    cursor->x_pos.i.hi = kind == 0 ? 88 : 64;
    cursor->ext.title_logo.palette_shift_value = kind >= 2;
    for (i = 0; i < row_counts[bank]; i++) {
        struct MiscObj* label = &expected_misc[start + i + 1];
        label->active = 1;
        label->id = 31;
        label->unk2 = menu_rows[bank][i][0];
        label->unk7 = i;
        label->y_pos.i.hi = menu_rows[bank][i][1];
        label->ext.title_logo.palette_shift_value = kind >= 2;
    }
    if (kind == 0)
        func_8001E9E0(&info);
    else if (kind == 1)
        func_8001EC90(&info);
    else
        func_8001A860(&engine_obj);
    check_reset();
    c_test_same_words(&info, &info_expected, sizeof(info));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_expected, sizeof(main_bss_state));
    c_test_same_words(&memcard_menu, &menu_before, sizeof(memcard_menu));
    c_test_same_words(&D_800F1D90, &runtime_before, sizeof(runtime_before));
    c_test_same_words(background_objects, backgrounds_expected, sizeof(backgrounds_expected));
    c_test_same_words(WINDOW_ARCHIVE_DATA, window_words, sizeof(window_words));
    c_test_copy_words((u32*)WINDOW_ARCHIVE_DATA, window_before, COUNT(window_before));
    return 1;
}
#ifdef MMX4_PC
#else
#endif

const struct CTestGroup c_test_groups[] = {
    { "menu_dispatches_timeout_or_confirm_to_return_phase", NULL, NULL, 2, dispatch_timer },
    { "load_save_navigation_runs_real_ui_and_empty_object_pools", NULL, NULL, 96, navigate_menu_navigation_dispatch },
    { "save_notice", 0, 0, COUNT(save_notices), test_save_notice },
    { "save_result", 0, 0, COUNT(save_result_cases), test_save_result },
    { "load_result", 0, 0, COUNT(load_result_cases), test_load_result },
    { "load_menu_ports", 0, 0, COUNT(load_ports), test_load_ports },
    { "load_menu_slots", 0, 0, COUNT(load_slots), test_load_slots },
    { "menu_screens", 0, 0, COUNT(menu_cases), test_menu_screens },
    { "menu_text_list_context", NULL, menu_text_list_context_cases_expected, COUNT(menu_text_list_context_cases_expected), menu_text_list_context_cases_row },
    { "save_menu_navigation", NULL, save_menu_navigation_cases_expected, COUNT(save_menu_navigation_cases_expected), navigate },
    { "save_preview_icons", 0, 0, 17, preview_case },
    { "func_8001B718", 0, 0, 1, test_func_8001B718 },
    { "func_8001C30C", 0, 0, 1, test_func_8001C30C },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "save_sign_bit", save_sign_bit_cases, save_sign_bit_cases_expected, COUNT(save_sign_bit_cases), 0 },
    { "save_confirmation", 0, 0, 2 * COUNT(save_confirmations), test_save_confirmation },
#ifdef MMX4_PC
    { "card_scan", 0, 0, COUNT(card_scan_cases), test_card_scan },
    { "card_format", 0, 0, COUNT(card_format_cases), test_card_format },
    { "card_transfer", 0, 0, COUNT(transfer_cards), test_card_transfer },
    { "card_prewrite", 0, 0, 2 * COUNT(card_prewrite_cases), test_card_prewrite },
    { "card_write", 0, 0, COUNT(card_write_cases), test_card_write },
    { "port_confirmation", 0, 0, 6, test_port_confirmation },
    { "card_menu_entry", 0, 0, COUNT(entry_cards) * 2, test_card_menu_entry },
    { "load_confirmation", 0, 0, COUNT(save_confirmations) * 8, test_load_confirmation },
#endif
#ifdef MMX4_PC
    { "format_accept_cancel", NULL, NULL, 24, format_confirmation },
    { "menu_rebuild", NULL, NULL, 8, menu_rebuild },
#else
    { "native_only_reset_budget", NULL, NULL, 0, NULL },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 96 + COUNT(save_notices) + COUNT(save_result_cases) + COUNT(load_result_cases) + COUNT(load_ports) + COUNT(load_slots) + COUNT(menu_cases) + COUNT(menu_text_list_context_cases_expected) + COUNT(save_menu_navigation_cases_expected) + 17 + 1 + 1 + COUNT(pool_full_cases) + COUNT(save_sign_bit_cases) + 2 * COUNT(save_confirmations)
#ifdef MMX4_PC
    + COUNT(card_scan_cases)
    + COUNT(card_format_cases)
    + COUNT(transfer_cards)
    + 2 * COUNT(card_prewrite_cases)
    + COUNT(card_write_cases)
    + 6
    + COUNT(entry_cards) * 2
    + COUNT(save_confirmations) * 8
#endif
#ifdef MMX4_PC
    + 24
    + 8
#else
    + 0
#endif
    ;
