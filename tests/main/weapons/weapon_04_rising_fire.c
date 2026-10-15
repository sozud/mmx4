#include "test_runtime.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern s32 player_gfx_buf_0[1024];

static u32 disabled(void)
{
    struct WeaponObj obj, before;
    struct PlayerObj player_before;
    struct Unk_unk68 box = { 1, 2, 3, 4 };
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.capsule_state = -1;
    g_Player.weapon = 0;
    g_Player.shot_type = 13;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    obj.active = 0x21;
    obj.id = 4;
    obj.unk2 = 0x27;
    obj.on_screen = 1;
    obj.unk5 = 0x28;
    obj.unk6 = 0x29;
    obj.unk7 = 0x2A;
    obj.unk50 = &box;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk64 = 0x2B;
    before = obj;
    player_before = g_Player;
    rising_fire_update(&obj);
    before.active = 0;
    before.id = 0;
    before.unk2 = 0;
    before.on_screen = 0;
    before.state = 0;
    before.unk5 = 0;
    before.unk6 = 0;
    before.unk7 = 0;
    before.unk50 = NULL;
    player_before.shot_count = g_Player.shot_count;
    player_before.special_shot_count = g_Player.special_shot_count;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(box.unk0 == 1 && box.unk1 == 2 && box.unk2 == 3 && box.unk3 == 4);
    actual = (u8)g_Player.shot_count | ((u32)(u8)g_Player.special_shot_count << 8);
    return actual;
}
static const CTestCase rising_fire_disable_state_cases[] = { disabled };
static const u32 rising_fire_disable_state_cases_expected[] = { 0x102u };

static const u32 rising_fire_charged_update_expected[] = { 0x10200u };
static u32 test_rising_fire_charged_update(u32 row)
{
    u32 observed_values[1];
    struct WeaponObj obj, before;
    struct PlayerObj player_before;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));

    memset(&player_gfx_buf_0, 0, sizeof(player_gfx_buf_0));
    memset(&player_gfx_buf_1, 0, sizeof(player_gfx_buf_1));
    memset(&vram_rect_ptr, 0, sizeof(vram_rect_ptr));
    g_Player.input_locked = 0;
    g_Player.capsule_state = -1;
    g_Player.weapon = 0;
    obj.state = 0;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    obj.active = 0x41;
    obj.id = 13;
    obj.unk2 = 1;
    obj.on_screen = 1;
    obj.unk5 = 5;
    obj.unk6 = 6;
    obj.unk7 = 7;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.unk50 = &obj;
    before = obj;
    player_before = g_Player;
    rising_fire_charged_update(&obj);
    before.active = before.id = before.unk2 = before.on_screen = 0;
    before.state = before.unk5 = before.unk6 = before.unk7 = 0;
    before.unk50 = NULL;
    --player_before.shot_count;
    --player_before.special_shot_count;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u8)obj.state | ((u32)(u8)g_Player.shot_count << 8) | ((u32)(u8)g_Player.special_shot_count << 16) | ((u32)(u8)obj.active << 24);
    return c_test_observe(0, row, observed_values, rising_fire_charged_update_expected, 1);
}

static const u32 rising_fire_update_expected[] = { 0u };
static u32 test_rising_fire_update(u32 row)
{
    u32 observed_values[1];
    struct WeaponObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));

    memset(&player_gfx_buf_0, 0, sizeof(player_gfx_buf_0));
    memset(&player_gfx_buf_1, 0, sizeof(player_gfx_buf_1));
    memset(&vram_rect_ptr, 0, sizeof(vram_rect_ptr));
    g_Player.input_locked = 0;
    g_Player.capsule_state = -1;
    g_Player.weapon = 0;
    g_Player.shot_type = 13;
    obj.state = 0;
    rising_fire_update(&obj);
    observed_values[0] = (u32)obj.state;
    return c_test_observe(0, row, observed_values, rising_fire_update_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "rising_fire_disable_state", rising_fire_disable_state_cases, rising_fire_disable_state_cases_expected, COUNT(rising_fire_disable_state_cases), 0 },
    { "rising_fire_charged_update", 0, 0, 1, test_rising_fire_charged_update },
    { "rising_fire_update", 0, 0, 1, test_rising_fire_update },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(rising_fire_disable_state_cases) + 1 + 1;
