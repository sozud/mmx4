#include "test_runtime.h"
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
#define ACTION_CASE(name, mode, observation)   \
    static u32 name(void)                      \
    {                                          \
        return action_case(mode, observation); \
    }
ACTION_CASE(PAUSE_CANCEL_HEADER, 0, 0)
ACTION_CASE(PAUSE_CANCEL_EXIT_FLAG, 0, 1)
ACTION_CASE(PAUSE_CONFIRM_EXIT_HEADER, 1, 0)
ACTION_CASE(PAUSE_CONFIRM_EXIT_EXIT_FLAG, 1, 1)
ACTION_CASE(PAUSE_DEFAULT_RIGHT_HEADER, 2, 0)
ACTION_CASE(PAUSE_DEFAULT_RIGHT_EXIT_FLAG, 2, 1)
ACTION_CASE(PAUSE_DEFAULT_MID_HEADER, 3, 0)
ACTION_CASE(PAUSE_DEFAULT_MID_EXIT_FLAG, 3, 1)
ACTION_CASE(PAUSE_DEFAULT_HIGH_HEADER, 4, 0)
ACTION_CASE(PAUSE_DEFAULT_HIGH_EXIT_FLAG, 4, 1)
ACTION_CASE(PAUSE_ZERO_UP_CLAMP_HEADER, 5, 0)
ACTION_CASE(PAUSE_ZERO_UP_CLAMP_EXIT_FLAG, 5, 1)
ACTION_CASE(PAUSE_ZERO_UP_UNAVAILABLE_HEADER, 6, 0)
ACTION_CASE(PAUSE_ZERO_UP_UNAVAILABLE_EXIT_FLAG, 6, 1)
ACTION_CASE(PAUSE_ZERO_UP_ABOVE_HEADER, 7, 0)
ACTION_CASE(PAUSE_ZERO_UP_ABOVE_EXIT_FLAG, 7, 1)
ACTION_CASE(PAUSE_OBJECT_UP_CLAMP_HEADER, 8, 0)
ACTION_CASE(PAUSE_OBJECT_UP_CLAMP_EXIT_FLAG, 8, 1)
ACTION_CASE(PAUSE_UP_AVAILABLE_HEADER, 9, 0)
ACTION_CASE(PAUSE_UP_AVAILABLE_EXIT_FLAG, 9, 1)
ACTION_CASE(PAUSE_UP_EMPTY_HEADER, 10, 0)
ACTION_CASE(PAUSE_UP_EMPTY_EXIT_FLAG, 10, 1)
ACTION_CASE(PAUSE_UP_SPARSE_HEADER, 11, 0)
ACTION_CASE(PAUSE_UP_SPARSE_EXIT_FLAG, 11, 1)
ACTION_CASE(PAUSE_DOWN_AVAILABLE_HEADER, 12, 0)
ACTION_CASE(PAUSE_DOWN_AVAILABLE_EXIT_FLAG, 12, 1)
ACTION_CASE(PAUSE_DOWN_BOUNDARY_HEADER, 13, 0)
ACTION_CASE(PAUSE_DOWN_BOUNDARY_EXIT_FLAG, 13, 1)
ACTION_CASE(PAUSE_ZERO_LEFT_AVAILABLE_HEADER, 14, 0)
ACTION_CASE(PAUSE_ZERO_LEFT_AVAILABLE_EXIT_FLAG, 14, 1)
ACTION_CASE(PAUSE_ZERO_LEFT_EMPTY_HEADER, 15, 0)
ACTION_CASE(PAUSE_ZERO_LEFT_EMPTY_EXIT_FLAG, 15, 1)
ACTION_CASE(PAUSE_OBJECT_LEFT_SPARSE_HEADER, 16, 0)
ACTION_CASE(PAUSE_OBJECT_LEFT_SPARSE_EXIT_FLAG, 16, 1)
ACTION_CASE(PAUSE_LEFT_WEAPON_HEADER, 17, 0)
ACTION_CASE(PAUSE_LEFT_WEAPON_EXIT_FLAG, 17, 1)
ACTION_CASE(PAUSE_CONFIRM_SAVE_HEADER, 18, 0)
ACTION_CASE(PAUSE_CONFIRM_SAVE_EXIT_FLAG, 18, 1)
ACTION_CASE(PAUSE_LEFT_TANK_HEADER, 19, 0)
ACTION_CASE(PAUSE_LEFT_TANK_EXIT_FLAG, 19, 1)
ACTION_CASE(PAUSE_LEFT_EMPTY_HEADER, 20, 0)
ACTION_CASE(PAUSE_LEFT_EMPTY_EXIT_FLAG, 20, 1)
static const CTestCase pause_action_selection_cases[] = {
    PAUSE_CANCEL_HEADER,
    PAUSE_CANCEL_EXIT_FLAG,
    PAUSE_CONFIRM_EXIT_HEADER,
    PAUSE_CONFIRM_EXIT_EXIT_FLAG,
    PAUSE_DEFAULT_RIGHT_HEADER,
    PAUSE_DEFAULT_RIGHT_EXIT_FLAG,
    PAUSE_DEFAULT_MID_HEADER,
    PAUSE_DEFAULT_MID_EXIT_FLAG,
    PAUSE_DEFAULT_HIGH_HEADER,
    PAUSE_DEFAULT_HIGH_EXIT_FLAG,
    PAUSE_ZERO_UP_CLAMP_HEADER,
    PAUSE_ZERO_UP_CLAMP_EXIT_FLAG,
    PAUSE_ZERO_UP_UNAVAILABLE_HEADER,
    PAUSE_ZERO_UP_UNAVAILABLE_EXIT_FLAG,
    PAUSE_ZERO_UP_ABOVE_HEADER,
    PAUSE_ZERO_UP_ABOVE_EXIT_FLAG,
    PAUSE_OBJECT_UP_CLAMP_HEADER,
    PAUSE_OBJECT_UP_CLAMP_EXIT_FLAG,
    PAUSE_UP_AVAILABLE_HEADER,
    PAUSE_UP_AVAILABLE_EXIT_FLAG,
    PAUSE_UP_EMPTY_HEADER,
    PAUSE_UP_EMPTY_EXIT_FLAG,
    PAUSE_UP_SPARSE_HEADER,
    PAUSE_UP_SPARSE_EXIT_FLAG,
    PAUSE_DOWN_AVAILABLE_HEADER,
    PAUSE_DOWN_AVAILABLE_EXIT_FLAG,
    PAUSE_DOWN_BOUNDARY_HEADER,
    PAUSE_DOWN_BOUNDARY_EXIT_FLAG,
    PAUSE_ZERO_LEFT_AVAILABLE_HEADER,
    PAUSE_ZERO_LEFT_AVAILABLE_EXIT_FLAG,
    PAUSE_ZERO_LEFT_EMPTY_HEADER,
    PAUSE_ZERO_LEFT_EMPTY_EXIT_FLAG,
    PAUSE_OBJECT_LEFT_SPARSE_HEADER,
    PAUSE_OBJECT_LEFT_SPARSE_EXIT_FLAG,
    PAUSE_LEFT_WEAPON_HEADER,
    PAUSE_LEFT_WEAPON_EXIT_FLAG,
    PAUSE_CONFIRM_SAVE_HEADER,
    PAUSE_CONFIRM_SAVE_EXIT_FLAG,
    PAUSE_LEFT_TANK_HEADER,
    PAUSE_LEFT_TANK_EXIT_FLAG,
    PAUSE_LEFT_EMPTY_HEADER,
    PAUSE_LEFT_EMPTY_EXIT_FLAG,
};
static const u32 pause_action_selection_cases_expected[] = { 0xD090002u, 0x0u, 0xD090002u, 0x1u, 0xD090201u, 0x0u, 0xD090201u, 0x0u, 0xD090201u, 0x0u, 0xD090201u, 0x0u, 0xE090201u, 0x0u, 0xE090201u, 0x0u, 0xD090201u, 0x0u, 0xD090201u, 0x0u, 0x90001u, 0x0u, 0x5090001u, 0x0u, 0xE090201u, 0x0u, 0xE090201u, 0x0u, 0xC090101u, 0x0u, 0xD090201u, 0x0u, 0xA090101u, 0x0u, 0x8090001u, 0x0u, 0xE000501u, 0x0u, 0xC090101u, 0x0u, 0x90001u, 0x0u };
#undef controller_input
#undef main_bss_state
#undef ACTION_CASE

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
#define AVAILABILITY_CASE(name, mode, observation)   \
    static u32 name(void)                            \
    {                                                \
        return availability_case(mode, observation); \
    }
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_0, 0, 0)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_1, 0, 1)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_2, 0, 2)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_3, 0, 3)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_4, 0, 4)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_5, 0, 5)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_6, 0, 6)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_7, 0, 7)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_8, 0, 8)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_9, 0, 9)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_10, 0, 10)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_11, 0, 11)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_12, 0, 12)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_13, 0, 13)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_14, 0, 14)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_0_15, 0, 15)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_0, 1, 0)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_1, 1, 1)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_2, 1, 2)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_3, 1, 3)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_4, 1, 4)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_5, 1, 5)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_6, 1, 6)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_7, 1, 7)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_8, 1, 8)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_9, 1, 9)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_10, 1, 10)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_11, 1, 11)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_12, 1, 12)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_13, 1, 13)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_14, 1, 14)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_1_15, 1, 15)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_0, 2, 0)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_1, 2, 1)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_2, 2, 2)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_3, 2, 3)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_4, 2, 4)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_5, 2, 5)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_6, 2, 6)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_7, 2, 7)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_8, 2, 8)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_9, 2, 9)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_10, 2, 10)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_11, 2, 11)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_12, 2, 12)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_13, 2, 13)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_14, 2, 14)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_2_15, 2, 15)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_0, 3, 0)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_1, 3, 1)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_2, 3, 2)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_3, 3, 3)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_4, 3, 4)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_5, 3, 5)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_6, 3, 6)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_7, 3, 7)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_8, 3, 8)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_9, 3, 9)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_10, 3, 10)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_11, 3, 11)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_12, 3, 12)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_13, 3, 13)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_14, 3, 14)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_3_15, 3, 15)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_0, 4, 0)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_1, 4, 1)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_2, 4, 2)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_3, 4, 3)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_4, 4, 4)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_5, 4, 5)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_6, 4, 6)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_7, 4, 7)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_8, 4, 8)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_9, 4, 9)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_10, 4, 10)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_11, 4, 11)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_12, 4, 12)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_13, 4, 13)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_14, 4, 14)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_4_15, 4, 15)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_0, 5, 0)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_1, 5, 1)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_2, 5, 2)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_3, 5, 3)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_4, 5, 4)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_5, 5, 5)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_6, 5, 6)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_7, 5, 7)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_8, 5, 8)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_9, 5, 9)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_10, 5, 10)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_11, 5, 11)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_12, 5, 12)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_13, 5, 13)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_14, 5, 14)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_5_15, 5, 15)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_0, 6, 0)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_1, 6, 1)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_2, 6, 2)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_3, 6, 3)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_4, 6, 4)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_5, 6, 5)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_6, 6, 6)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_7, 6, 7)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_8, 6, 8)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_9, 6, 9)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_10, 6, 10)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_11, 6, 11)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_12, 6, 12)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_13, 6, 13)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_14, 6, 14)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_6_15, 6, 15)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_0, 7, 0)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_1, 7, 1)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_2, 7, 2)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_3, 7, 3)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_4, 7, 4)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_5, 7, 5)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_6, 7, 6)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_7, 7, 7)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_8, 7, 8)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_9, 7, 9)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_10, 7, 10)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_11, 7, 11)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_12, 7, 12)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_13, 7, 13)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_14, 7, 14)
AVAILABILITY_CASE(PAUSE_AVAILABILITY_7_15, 7, 15)
static const CTestCase pause_availability_cases[] = {
    PAUSE_AVAILABILITY_0_0,
    PAUSE_AVAILABILITY_0_1,
    PAUSE_AVAILABILITY_0_2,
    PAUSE_AVAILABILITY_0_3,
    PAUSE_AVAILABILITY_0_4,
    PAUSE_AVAILABILITY_0_5,
    PAUSE_AVAILABILITY_0_6,
    PAUSE_AVAILABILITY_0_7,
    PAUSE_AVAILABILITY_0_8,
    PAUSE_AVAILABILITY_0_9,
    PAUSE_AVAILABILITY_0_10,
    PAUSE_AVAILABILITY_0_11,
    PAUSE_AVAILABILITY_0_12,
    PAUSE_AVAILABILITY_0_13,
    PAUSE_AVAILABILITY_0_14,
    PAUSE_AVAILABILITY_0_15,
    PAUSE_AVAILABILITY_1_0,
    PAUSE_AVAILABILITY_1_1,
    PAUSE_AVAILABILITY_1_2,
    PAUSE_AVAILABILITY_1_3,
    PAUSE_AVAILABILITY_1_4,
    PAUSE_AVAILABILITY_1_5,
    PAUSE_AVAILABILITY_1_6,
    PAUSE_AVAILABILITY_1_7,
    PAUSE_AVAILABILITY_1_8,
    PAUSE_AVAILABILITY_1_9,
    PAUSE_AVAILABILITY_1_10,
    PAUSE_AVAILABILITY_1_11,
    PAUSE_AVAILABILITY_1_12,
    PAUSE_AVAILABILITY_1_13,
    PAUSE_AVAILABILITY_1_14,
    PAUSE_AVAILABILITY_1_15,
    PAUSE_AVAILABILITY_2_0,
    PAUSE_AVAILABILITY_2_1,
    PAUSE_AVAILABILITY_2_2,
    PAUSE_AVAILABILITY_2_3,
    PAUSE_AVAILABILITY_2_4,
    PAUSE_AVAILABILITY_2_5,
    PAUSE_AVAILABILITY_2_6,
    PAUSE_AVAILABILITY_2_7,
    PAUSE_AVAILABILITY_2_8,
    PAUSE_AVAILABILITY_2_9,
    PAUSE_AVAILABILITY_2_10,
    PAUSE_AVAILABILITY_2_11,
    PAUSE_AVAILABILITY_2_12,
    PAUSE_AVAILABILITY_2_13,
    PAUSE_AVAILABILITY_2_14,
    PAUSE_AVAILABILITY_2_15,
    PAUSE_AVAILABILITY_3_0,
    PAUSE_AVAILABILITY_3_1,
    PAUSE_AVAILABILITY_3_2,
    PAUSE_AVAILABILITY_3_3,
    PAUSE_AVAILABILITY_3_4,
    PAUSE_AVAILABILITY_3_5,
    PAUSE_AVAILABILITY_3_6,
    PAUSE_AVAILABILITY_3_7,
    PAUSE_AVAILABILITY_3_8,
    PAUSE_AVAILABILITY_3_9,
    PAUSE_AVAILABILITY_3_10,
    PAUSE_AVAILABILITY_3_11,
    PAUSE_AVAILABILITY_3_12,
    PAUSE_AVAILABILITY_3_13,
    PAUSE_AVAILABILITY_3_14,
    PAUSE_AVAILABILITY_3_15,
    PAUSE_AVAILABILITY_4_0,
    PAUSE_AVAILABILITY_4_1,
    PAUSE_AVAILABILITY_4_2,
    PAUSE_AVAILABILITY_4_3,
    PAUSE_AVAILABILITY_4_4,
    PAUSE_AVAILABILITY_4_5,
    PAUSE_AVAILABILITY_4_6,
    PAUSE_AVAILABILITY_4_7,
    PAUSE_AVAILABILITY_4_8,
    PAUSE_AVAILABILITY_4_9,
    PAUSE_AVAILABILITY_4_10,
    PAUSE_AVAILABILITY_4_11,
    PAUSE_AVAILABILITY_4_12,
    PAUSE_AVAILABILITY_4_13,
    PAUSE_AVAILABILITY_4_14,
    PAUSE_AVAILABILITY_4_15,
    PAUSE_AVAILABILITY_5_0,
    PAUSE_AVAILABILITY_5_1,
    PAUSE_AVAILABILITY_5_2,
    PAUSE_AVAILABILITY_5_3,
    PAUSE_AVAILABILITY_5_4,
    PAUSE_AVAILABILITY_5_5,
    PAUSE_AVAILABILITY_5_6,
    PAUSE_AVAILABILITY_5_7,
    PAUSE_AVAILABILITY_5_8,
    PAUSE_AVAILABILITY_5_9,
    PAUSE_AVAILABILITY_5_10,
    PAUSE_AVAILABILITY_5_11,
    PAUSE_AVAILABILITY_5_12,
    PAUSE_AVAILABILITY_5_13,
    PAUSE_AVAILABILITY_5_14,
    PAUSE_AVAILABILITY_5_15,
    PAUSE_AVAILABILITY_6_0,
    PAUSE_AVAILABILITY_6_1,
    PAUSE_AVAILABILITY_6_2,
    PAUSE_AVAILABILITY_6_3,
    PAUSE_AVAILABILITY_6_4,
    PAUSE_AVAILABILITY_6_5,
    PAUSE_AVAILABILITY_6_6,
    PAUSE_AVAILABILITY_6_7,
    PAUSE_AVAILABILITY_6_8,
    PAUSE_AVAILABILITY_6_9,
    PAUSE_AVAILABILITY_6_10,
    PAUSE_AVAILABILITY_6_11,
    PAUSE_AVAILABILITY_6_12,
    PAUSE_AVAILABILITY_6_13,
    PAUSE_AVAILABILITY_6_14,
    PAUSE_AVAILABILITY_6_15,
    PAUSE_AVAILABILITY_7_0,
    PAUSE_AVAILABILITY_7_1,
    PAUSE_AVAILABILITY_7_2,
    PAUSE_AVAILABILITY_7_3,
    PAUSE_AVAILABILITY_7_4,
    PAUSE_AVAILABILITY_7_5,
    PAUSE_AVAILABILITY_7_6,
    PAUSE_AVAILABILITY_7_7,
    PAUSE_AVAILABILITY_7_8,
    PAUSE_AVAILABILITY_7_9,
    PAUSE_AVAILABILITY_7_10,
    PAUSE_AVAILABILITY_7_11,
    PAUSE_AVAILABILITY_7_12,
    PAUSE_AVAILABILITY_7_13,
    PAUSE_AVAILABILITY_7_14,
    PAUSE_AVAILABILITY_7_15,
};
static const u32 pause_availability_cases_expected[] = { 0x5A005A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A00u, 0x10001u, 0x10001u, 0x5A000000u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x131211u, 0x801u, 0x2u, 0x5A015A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x1015A0Au, 0x1000100u, 0x1000100u, 0x1010101u, 0x5A5A0101u, 0x0u, 0x0u, 0x0u, 0x5139291u, 0x801u, 0x2u, 0x5A5A5A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x1005A0Bu, 0x1000101u, 0x5A0000u, 0x100u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x139211u, 0x801u, 0x2u, 0x5A015A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A0Au, 0x1000100u, 0x1000100u, 0x5A01u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x131291u, 0x801u, 0x2u, 0x5A005A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A06u, 0x10001u, 0x10001u, 0x1010000u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x5131211u, 0x801u, 0x2u, 0x5A5A5A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A0Eu, 0x10000u, 0x5A0101u, 0x0u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x131211u, 0x801u, 0x2u, 0x5A005A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A00u, 0x10001u, 0x10001u, 0x0u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x131211u, 0x801u, 0x2u, 0x5A015A5Au, 0x5A5A025Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x5A5A5A5Au, 0x15A0Eu, 0x1000100u, 0x1000100u, 0x0u, 0x5A5A0001u, 0x0u, 0x0u, 0x0u, 0x131211u, 0x801u, 0x2u };
#undef controller_input
#undef main_bss_state
#undef AVAILABILITY_CASE

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
#define BOUNDARY_CASE(name, observation) \
    static u32 name(void)                \
    {                                    \
        return boundary(observation);    \
    }
BOUNDARY_CASE(WEAPON_BOUNDARY_ENERGY_0, 0)
BOUNDARY_CASE(WEAPON_BOUNDARY_ENERGY_1, 1)
BOUNDARY_CASE(WEAPON_BOUNDARY_ENERGY_2, 2)
BOUNDARY_CASE(WEAPON_BOUNDARY_ENERGY_3, 3)
BOUNDARY_CASE(WEAPON_BOUNDARY_STATE, 4)
static const CTestCase pause_weapon_boundary_cases[] = {
    WEAPON_BOUNDARY_ENERGY_0,
    WEAPON_BOUNDARY_ENERGY_1,
    WEAPON_BOUNDARY_ENERGY_2,
    WEAPON_BOUNDARY_ENERGY_3,
    WEAPON_BOUNDARY_STATE,
};
static const u32 pause_weapon_boundary_cases_expected[] = { 0x30303030u, 0x30303030u, 0x55555530u, 0x55555555u, 0x810C0101u };
#undef main_bss_state
#undef BOUNDARY_CASE

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

struct func_80030C54_case {
    u32 frame_counter, unk2C, weapon_energy_0, weapon_energy_1, weapon_energy_2, weapon_energy_3;
    u32 weapon_energy_4, weapon_energy_5, weapon_energy_6, weapon_energy_7, weapon_energy_8, unk5C_2;
    u32 expected[19];
};
static const struct func_80030C54_case func_80030C54_cases[] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 1u } },
    { 0, 0, 48, 48, 48, 48, 48, 48, 48, 48, 48, 127, { 0x7Fu, 0x30u, 0u, 0u, 0u, 0u, 0u, 0u, 0x30u, 0x30u, 0x30u, 0x30u, 0x30u, 0x30u, 0x30u, 0x30u, 0u, 0u, 1u } },
    { 2, 1048576, 48, 0, 0, 48, 48, 0, 0, 48, 0, 0, { 0u, 0x30u, 0u, 0u, 0u, 0u, 0u, 0u, 1u, 1u, 0x30u, 0x30u, 1u, 1u, 0x30u, 1u, 0u, 0x100000u, 0u } },
    { 0, 0, 48, 48, 48, 48, 48, 48, 48, 48, 0, 127, { 0x7Eu, 0x30u, 0u, 0u, 0u, 0u, 0u, 0u, 0x30u, 0x30u, 0x30u, 0x30u, 0x30u, 0x30u, 0x30u, 1u, 0u, 0u, 0u } },
};
static u32 test_func_80030C54(u32 row)
{
    const struct func_80030C54_case* c = &func_80030C54_cases[row];
    u32 observed_values[19];
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
    obj.unk2C = c->unk2C;
    g_Player.weapon_energy[0] = c->weapon_energy_0;
    g_Player.weapon_energy[1] = c->weapon_energy_1;
    g_Player.weapon_energy[2] = c->weapon_energy_2;
    g_Player.weapon_energy[3] = c->weapon_energy_3;
    g_Player.weapon_energy[4] = c->weapon_energy_4;
    g_Player.weapon_energy[5] = c->weapon_energy_5;
    g_Player.weapon_energy[6] = c->weapon_energy_6;
    g_Player.weapon_energy[7] = c->weapon_energy_7;
    g_Player.weapon_energy[8] = c->weapon_energy_8;
    g_Player.weapon_energy[9] = 0;
    g_Player.weapon_energy[10] = 0;
    g_Player.weapon_energy[11] = 0;
    g_Player.weapon_energy[12] = 0;
    g_Player.weapon_energy[13] = 0;
    g_Player.weapon_energy[14] = 0;
    g_Player.weapon_energy[15] = 0;
    engine_obj.sub_tanks[2] = c->unk5C_2;
    func_80030C54(&obj);
    observed_values[0] = (u32)engine_obj.sub_tanks[2];
    observed_values[1] = (u32)g_Player.weapon_energy[0];
    observed_values[2] = (u32)g_Player.weapon_energy[10];
    observed_values[3] = (u32)g_Player.weapon_energy[11];
    observed_values[4] = (u32)g_Player.weapon_energy[12];
    observed_values[5] = (u32)g_Player.weapon_energy[13];
    observed_values[6] = (u32)g_Player.weapon_energy[14];
    observed_values[7] = (u32)g_Player.weapon_energy[15];
    observed_values[8] = (u32)g_Player.weapon_energy[1];
    observed_values[9] = (u32)g_Player.weapon_energy[2];
    observed_values[10] = (u32)g_Player.weapon_energy[3];
    observed_values[11] = (u32)g_Player.weapon_energy[4];
    observed_values[12] = (u32)g_Player.weapon_energy[5];
    observed_values[13] = (u32)g_Player.weapon_energy[6];
    observed_values[14] = (u32)g_Player.weapon_energy[7];
    observed_values[15] = (u32)g_Player.weapon_energy[8];
    observed_values[16] = (u32)g_Player.weapon_energy[9];
    observed_values[17] = (u32)obj.unk2C;
    observed_values[18] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, c->expected, 19);
}
#undef main_bss_state

const struct CTestGroup c_test_groups[] = {
    { "pause_action_selection", pause_action_selection_cases, pause_action_selection_cases_expected, COUNT(pause_action_selection_cases), 0 },
    { "pause_availability", pause_availability_cases, pause_availability_cases_expected, COUNT(pause_availability_cases), 0 },
    { "pause_navigation_edges", pause_navigation_edges_cases, pause_navigation_edges_cases_expected, COUNT(pause_navigation_edges_cases), 0 },
    { "pause_restricted_ready", pause_restricted_ready_cases, pause_restricted_ready_cases_expected, COUNT(pause_restricted_ready_cases), 0 },
    { "pause_weapon_boundary", pause_weapon_boundary_cases, pause_weapon_boundary_cases_expected, COUNT(pause_weapon_boundary_cases), 0 },
    { "func_800301BC", 0, 0, 5, test_func_800301BC },
    { "func_800304E4", 0, 0, 6, test_func_800304E4 },
    { "func_80030A2C", 0, 0, 8, test_func_80030A2C },
    { "func_80030C54", 0, 0, 4, test_func_80030C54 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pause_action_selection_cases) + COUNT(pause_availability_cases) + COUNT(pause_navigation_edges_cases) + COUNT(pause_restricted_ready_cases) + COUNT(pause_weapon_boundary_cases) + 5 + 6 + 8 + 4;
