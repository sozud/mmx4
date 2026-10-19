#include "test_runtime.h"
void stock_charge_meter_update(struct MiscObj*);
static u32 archive[32];
static u32 meter(u32 row)
{
    struct MiscObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 start = row % 2, enabled = row / 2 % 2, charge = row / 4, i;
    for (i = 0; i < 16; i++) {
        archive[i] = 64 + 4 * i;
        archive[16 + i] = 0x13570000 + i;
    }
    TEST_SPRITE_FRAMES = (u8*)archive;
    engine_obj.unk1F = enabled;
    engine_before = engine_obj;
    g_Player.stock_charge = charge;
    player_before = g_Player;
    memset(&obj, 0, sizeof(obj));
    obj.state = !start;
    obj.unk42 = 0x1234;
    obj.unk40 = 0x5678;
    obj.unk16 = 3;
    obj.x_pos.val = 99 * 65536 + 0x1234;
    obj.y_pos.val = 101 * 65536 + 0x5678;
    obj.animation_step.packed = 0x09010004;
    expected = obj;
    if (start) {
        expected.bg_offset = -1;
        expected.unk3C = (u8*)archive + 112;
        expected.unk40 = 0;
        expected.unk42 = 0x780A;
        expected.unk16 = 16;
        expected.x_pos.i.hi = 32;
        expected.y_pos.i.hi = 52;
        expected.state = 1;
    } else if (enabled && charge) {
        expected.on_screen = 1;
        expected.x_pos.i.hi = 32;
        expected.y_pos.i.hi = 52;
        expected.animation_step.fields.frame_index = 31 - charge;
    }
    stock_charge_meter_update(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    for (i = 0; i < 16; i++)
        assert(archive[i] == 64 + 4 * i && archive[16 + i] == 0x13570000 + i);
    assert(TEST_SPRITE_FRAMES == (u8*)archive);
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "HUD_frame_archive_initialization_and_visible_stock_counts", NULL, NULL, 12, meter } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 12;
