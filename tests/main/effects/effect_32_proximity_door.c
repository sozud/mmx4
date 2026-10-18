#include "test_runtime.h"
#include "main/effects/effect_32_proximity_door.h"

static u32 door_case(u32 mode)
{
    struct EffectObj obj, expected;
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 1;
    obj.id = 32;
    obj.state = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.effect_32.unk15 = mode == 2 || mode == 4 || mode == 5 ? 1 : -1;
    obj.ext.effect_32.palette_source.bytes = tile_anim_trigger_scripts[1];
    obj.ext.effect_32.palette.fields.timer = 17;
    obj.ext.effect_32.palette.fields.unk1 = 0xA5;
    obj.ext.effect_32.palette.fields.step = mode == 3 || mode == 5 ? 1 : 0;
    obj.ext.effect_32.palette.fields.id = 6;
    g_Player.x_pos.i.hi = mode == 0 ? 53 : mode == 1 ? 147
        : mode == 4 || mode == 5                     ? 148
        : mode == 6                                  ? 52
                                                     : 100;
    expected = obj;
    player_before = g_Player;
    if (mode == 0 || mode == 1 || mode == 4) {
        u32 close = mode == 4;
        expected.ext.effect_32.palette_source.bytes = tile_anim_trigger_scripts[close];
        expected.ext.effect_32.palette.fields.timer = 2;
        expected.ext.effect_32.palette.fields.unk1 = 0;
        expected.ext.effect_32.palette.fields.step = 1;
        expected.ext.effect_32.palette.fields.id = close ? 8 : 0;
        expected.ext.effect_32.unk15 = close ? -1 : 1;
    }
    proximity_door_check_player(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.ext.effect_32.unk15 | ((u32)obj.ext.effect_32.palette.fields.id << 8) | ((u32)obj.ext.effect_32.palette.fields.timer << 16);
}
static const u32 proximity_door_real_scripts_cases_expected[] = { 0x20001u, 0x20001u, 0x110601u, 0x1106FFu, 0x208FFu, 0x110601u, 0x1106FFu };

const struct CTestGroup c_test_groups[] = {
    { "proximity_door_real_scripts", NULL, proximity_door_real_scripts_cases_expected, COUNT(proximity_door_real_scripts_cases_expected), door_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(proximity_door_real_scripts_cases_expected);
