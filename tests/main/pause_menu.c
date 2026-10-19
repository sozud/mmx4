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
    engine_obj.unk16 = 16;
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
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4 * COUNT(submenu_phases) + COUNT(pause_action_selection_cases_expected) + COUNT(pause_availability_cases_expected) + COUNT(pause_navigation_edges_cases) + COUNT(pause_restricted_ready_cases) + COUNT(pause_weapon_boundary_cases_expected) + 5 + 6 + 8 + COUNT(cases) + 4 + 44 + 2;
