#include "test_runtime.h"
void stock_charge_meter_update(struct MiscObj*);
static u32 archive[32];
static const u8 meter_rows[] = { 0, 1, 2, 6 };
static u32 meter(u32 row)
{
    struct MiscObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 start, enabled, charge, i;
    row = meter_rows[row];
    start = row % 2, enabled = row / 2 % 2, charge = row / 4;
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
    obj.unk16 = VISUAL_SATURN_LAYER(3);
    obj.x_pos.val = 99 * 65536 + 0x1234;
    obj.y_pos.val = 101 * 65536 + 0x5678;
    obj.animation_step.packed = C_TEST_STEP(0x09010004);
    expected = obj;
    if (start) {
        expected.bg_offset = -1;
        expected.unk3C = (u8*)archive + 112;
        expected.unk40 = WEAPON_TEXTURE_BASE;
        expected.unk42 = WEAPON_PALETTE_10;
        expected.unk16 = VISUAL_SATURN_LAYER(16);
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
#include "support/state_cases.h"
#include "main/visuals/visual_33_hover_jet.h"
static u32 jet_frames[16];
static struct PlayerObj jet_player;
#define jv state_room.visual
#define JET(st, frame, shown, timer) (jet_player = g_Player, state_reset(0, 0, 0), TEST_SPRITE_FRAMES = (u8*)jet_frames, g_Player.animation_step.fields.frame_index = frame, g_Player.unk15 = PLAYER_FACING_RIGHT, g_Player.x_pos.i.hi = 0x100, g_Player.y_pos.i.hi = 0x80, jv.active = 1, jv.state = st, jv.unk2 = shown, jv.unk5C.value = timer, hover_jet_update(&jv), state_extra = jv.unk17 | (u32)(u8)jv.unk5C.value << 8, g_Player = jet_player)
static void jet_init(void)
{
    JET(0, 0xE5, 0, 0);
}
static void jet_same_flame(void) { JET(1, 0xE6, 0, 3); }
static void jet_flame_dd(void) { JET(1, 0xDD, 0, 3); }
static void jet_flame_de(void) { JET(1, 0xDE, 0, 3); }
static void jet_flame_df(void) { JET(1, 0xDF, 0, 3); }
static void jet_flame_e0(void) { JET(1, 0xE0, 0, 3); }
static void jet_flame_e1(void) { JET(1, 0xE1, 0, 3); }
static void jet_flame_e2(void) { JET(1, 0xE2, 0, 3); }
static void jet_flame_e3(void) { JET(1, 0xE3, 0, 3); }
static void jet_flame_e4(void) { JET(1, 0xE4, 0, 3); }
static void jet_landed(void) { JET(1, 0x10, 0, 3); }
static void (*const jet_cases[])(void) = {
    jet_init,
    jet_same_flame,
    jet_flame_dd,
    jet_flame_de,
    jet_flame_df,
    jet_flame_e0,
    jet_flame_e1,
    jet_flame_e2,
    jet_flame_e3,
    jet_flame_e4,
    jet_landed,
};
static const u32 jet_expected[] = {
    0x1u,
    0xFF400001u,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x10000u | WEAPON_PALETTE_2,
    0x820u,
    0x0u,
    0x1u,
    0x400001u,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x40000u,
    0x200u,
    0x0u,
    0x1u,
    0xFF400101u,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x221u,
    0x0u,
    0x1u,
    0xFF400101u,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x221u,
    0x0u,
    0x1u,
    0xFF400201u,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x222u,
    0x0u,
    0x1u,
    0xFF400201u,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x222u,
    0x0u,
    0x1u,
    0xFF400301u,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x223u,
    0x0u,
    0x1u,
    0xFF400301u,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x223u,
    0x0u,
    0x1u,
    0xFF400401u,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x224u,
    0x0u,
    0x1u,
    0xFF400401u,
    0x1000000u,
    0x800000u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x224u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x0u,
    0x50000u,
    0x300u,
    0x0u,
};
static u32 test_jet(u32 row)
{
    return object_run(jet_cases[row], row, &jet_expected[row * 10]);
}
const struct CTestGroup c_test_groups[] = {
    { "HUD_frame_archive_initialization_and_visible_stock_counts", NULL, NULL, COUNT(meter_rows), meter },
    { "hover_jet_flames", 0, 0, COUNT(jet_cases), test_jet },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(meter_rows) + COUNT(jet_cases);
