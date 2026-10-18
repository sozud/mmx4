#include "test_runtime.h"
#include "main/weapons/weapon_01_lightning_web.h"
#include "main/weapons/weapon_02_frost_tower.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"
#include "main/weapons/weapon_07_double_cyclone.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
extern s32 player_gfx_buf_0[1024];

static const u32 double_cyclone_update_expected[] = { 0x10200u };
static u32 test_double_cyclone_update(u32 row)
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
    g_Player.shot_type = 16;
    obj.state = 0;
    g_Player.shot_count = 3;
    g_Player.special_shot_count = 2;
    obj.active = 0x41;
    obj.id = 7;
    obj.unk2 = 1;
    obj.on_screen = 1;
    obj.unk5 = 5;
    obj.unk6 = 6;
    obj.unk7 = 7;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.unk50 = &obj;
    before = obj;
    player_before = g_Player;
    double_cyclone_update(&obj);
    before.active = before.id = before.unk2 = before.on_screen = 0;
    before.state = before.unk5 = before.unk6 = before.unk7 = 0;
    before.unk50 = NULL;
    --player_before.shot_count;
    --player_before.special_shot_count;
    c_test_same_words(&obj, &before, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    observed_values[0] = (u8)obj.state | ((u32)(u8)g_Player.shot_count << 8) | ((u32)(u8)g_Player.special_shot_count << 16) | ((u32)(u8)obj.active << 24);
    return c_test_observe(0, row, observed_values, double_cyclone_update_expected, 1);
}

#include "support/charged_dispatch.h"
CHARGED_BASIC(3)
CHARGED_CASE(3, 4)
CHARGED_CASE(3, 5)
CHARGED_CASE(3, 6)
static const CTestCase double_cyclone_charged_dispatch_cases[] = { CHARGED_BASIC_ENTRIES(3) CHARGED_ENTRIES(3, 4) CHARGED_ENTRIES(3, 5) CHARGED_ENTRIES(3, 6) };

static const u32 double_cyclone_charged_dispatch_cases_expected[] = { 0x10391u, 0x605u, 0x0u, 0x605u, 0x0u, 0x605u, 0x0u, 0x605u, 0x0u, 0x605u, 0x0u, 0x605u, 0x0u, 0x504u };
const struct CTestGroup c_test_groups[] = {
    { "double_cyclone_update", 0, 0, 1, test_double_cyclone_update },
    { "double_cyclone_charged_dispatch", double_cyclone_charged_dispatch_cases, double_cyclone_charged_dispatch_cases_expected, COUNT(double_cyclone_charged_dispatch_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + COUNT(double_cyclone_charged_dispatch_cases);
