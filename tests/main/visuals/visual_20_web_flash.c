#include "test_runtime.h"
#include "main/visuals/visual_20_web_flash.h"
#include "main/55C4.h"
#include "main/mains/main_43_web_spider.h"

static u32 flash_case(u32 mode)
{
    struct VisualObj obj, before;
    struct ShotObj shot, shot_before;
    struct WeaponObj weapon, weapon_before;
    struct PlayerObj player_before = g_Player;
    u32 i, animation = mode < 2 ? 17 : 21, frame = mode == 6 ? 6 : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&shot, 0, sizeof(shot));
    memset(&weapon, 0, sizeof(weapon));
    obj.active = 0x41;
    obj.id = 20;
    obj.state = 1;
    obj.unk5 = 0x27;
    obj.unk6 = 0x28;
    obj.unk7 = 0x29;
    obj.unk2 = mode < 2 ? 0 : 1;
    obj.bg_offset = -1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)web_spider_animations;
    set_animation_frame(&obj, animation, frame);
    weapon.active = 0x41;
    weapon.id = 0x27;
    weapon.state = mode == 5 ? 2 : 1;
    weapon.unk5 = mode == 3 ? 5 : mode == 4 ? 4
                                            : 3;
    weapon.x_pos.val = 116 * 65536 + 0x2345;
    weapon.y_pos.val = 72 * 65536 + 0x6789;
    shot.active = 0x41;
    shot.id = 22;
    shot.unk2 = mode == 0 ? 1 : 0;
    shot.unk7C = &weapon;
    obj.unk50 = mode < 2 ? (struct PlayerObj*)&shot : (struct PlayerObj*)&weapon;
    before = obj;
    shot_before = shot;
    weapon_before = weapon;
    web_flash_main(&obj);
    if (mode < 2) {
        before.animation_cursor = (const u8*)&web_spider_animations[17][1];
        before.animation_step = web_spider_animations[17][1];
        before.x_pos.val = weapon.x_pos.val;
        before.y_pos.val = weapon.y_pos.val;
    } else if (mode == 6) {
        before.animation_cursor = (const u8*)&web_spider_animations[21][7];
        before.animation_step = web_spider_animations[21][7];
    } else
        before.animation_step.fields.duration--;
    if (mode == 1 || mode >= 4)
        memset(&before, 0, 8);
    else
        before.on_screen = 1;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(shot) / 4; i++)
        assert(((u32*)&shot)[i] == ((u32*)&shot_before)[i]);
    for (i = 0; i < sizeof(weapon) / 4; i++)
        assert(((u32*)&weapon)[i] == ((u32*)&weapon_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.active | ((u32)(u8)obj.on_screen << 8) | ((u32)(u8)obj.state << 16);
}
#define CASE(m)                \
    static u32 flash_##m(void) \
    {                          \
        return flash_case(m);  \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
#define ENTRY(m) flash_##m,
static const CTestCase web_flash_pointer_views_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) };
static const u32 web_flash_pointer_views_cases_expected[] = { 0x10141u, 0x0u, 0x10141u, 0x10141u, 0x0u, 0x0u, 0x0u };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "web_flash_pointer_views", web_flash_pointer_views_cases, web_flash_pointer_views_cases_expected, COUNT(web_flash_pointer_views_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(web_flash_pointer_views_cases);
