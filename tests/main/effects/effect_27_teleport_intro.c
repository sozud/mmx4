#include "test_runtime.h"
#include "main/effects/effect_27_teleport_intro.h"

static u32 teleport_case(u32 mode)
{
    static const u8 phase[] = { 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 2, 255 };
    static const u8 free_slots[] = { 0, 1, 0, 0, 1, 5, 10, 0, 1, 8, 0, 0, 0, 0, 0 };
    struct EffectObj obj, expected;
    struct QuadObj pool[32];
    struct PlayerObj player_before = g_Player;
    u16 expected_random = 119;
    u32 i, available = free_slots[mode], count = 0;
    memset(&obj, 0, sizeof(obj));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    for (i = 0; i < 32; i++) {
        g_QuadObjects[i].active = i >= 32 - available ? 0 : 1;
        g_QuadObjects[i].id = 39;
        g_QuadObjects[i].state = 40;
        g_QuadObjects[i].unk2 = 9;
        g_QuadObjects[i].unk5 = 3;
        g_QuadObjects[i].unk6 = 4;
        g_QuadObjects[i].unk7 = 5;
        g_QuadObjects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        g_QuadObjects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    obj.active = 1;
    obj.id = 27;
    obj.state = 1;
    obj.unk5 = phase[mode];
    obj.ext.effect_27.unk14 = mode == 2 || mode == 10 || mode == 13 ? 1 : 0;
    obj.ext.effect_27.unk15 = 7;
    obj.ext.effect_27.unk16 = 0;
    expected = obj;
    memcpy(pool, g_QuadObjects, sizeof(pool));
    cur_random = 119;
    if (phase[mode] == 0) {
        expected.unk5 = 1;
        expected.ext.effect_27.unk14 = 1;
        count = available;
    } else if (phase[mode] < 3 && obj.ext.effect_27.unk14 == 0) {
        count = available;
        expected.unk5++;
        expected.ext.effect_27.unk14 = count;
    } else if (phase[mode] == 3 && obj.ext.effect_27.unk14 == 0)
        expected.ext.effect_27.unk16 = 1;
    for (i = 0; i < count; i++) {
        struct QuadObj* child = &pool[32 - available + i];
        child->active = -127;
        child->id = 7;
        child->unk2 = phase[mode];
        child->link.owner = &obj;
        if (phase[mode] == 1)
            child->unk7 = i;
        if (phase[mode] == 2) {
            u16 temp = expected_random * 3;
            u32 high = temp >> 8;
            expected_random = ((expected_random + high) & 0xFF) | (high << 8);
            child->unk7 = (u8)expected_random & 3;
        }
    }
    teleport_intro_spawn_quads(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool) / 4; i++)
        assert(((u32*)g_QuadObjects)[i] == ((u32*)pool)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(cur_random == expected_random);
    return (u8)obj.unk5 | ((u32)(u8)obj.ext.effect_27.unk14 << 8) | ((u32)(u8)obj.ext.effect_27.unk16 << 16) | ((u32)pool[31].unk7 << 24);
}
static const u32 teleport_intro_quad_prefixes_cases_expected[] = { 0x5000101u, 0x5000101u, 0x5000101u, 0x5000002u, 0x102u, 0x4000502u, 0x9000A02u, 0x5000003u, 0x103u, 0x3000803u, 0x5000103u, 0x5010003u, 0x5000004u, 0x5000102u, 0x50000FFu };

const struct CTestGroup c_test_groups[] = {
    { "teleport_intro_quad_prefixes", NULL, teleport_intro_quad_prefixes_cases_expected, COUNT(teleport_intro_quad_prefixes_cases_expected), teleport_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(teleport_intro_quad_prefixes_cases_expected);
