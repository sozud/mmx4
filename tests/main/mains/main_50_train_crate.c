#include "test_runtime.h"
#include "support/platform_fixture.h"
#include "main/mains/main_50_train_crate.h"
#include "main/195B4.h"
#include "main/collision_bounds.h"
extern u8 train_crate_hurt_box[4];

struct func_80069748_case {
    u32 substage, unk2, slot;
    u32 expected[12];
};
static const struct func_80069748_case func_80069748_cases[] = {
    { 0, 0x01, 5, { 9u, 0x788Cu, 1u, 0u, 3u, 1u, 1u, 6u, 0u, 0u, 0x640000u, 0x500000u } },
    { 0, 0x81, 5, { 9u, 0x788Cu, 1u, 8u, 3u, 1u, 1u, 6u, 0u, 1u, 0x640000u, 0x500000u } },
    { 1, 0x01, 7, { 0xDu, 0x78C4u, 1u, 0u, 3u, 1u, 1u, 6u, 0u, 0u, 0x640000u, 0x500000u } },
    { 1, 0x81, 7, { 0xDu, 0x78C4u, 1u, 8u, 3u, 1u, 1u, 6u, 0u, 1u, 0x640000u, 0x500000u } },
};
static u32 test_func_80069748(u32 row)
{
    const struct func_80069748_case* c = &func_80069748_cases[row];
    u32 observed_values[12];
    struct MainObj obj;
    struct EngineObj engine_before;
    struct PlayerObj player_before;
    u32 frames[64], metadata[32], frames_before[64], metadata_before[32];
    u8 slot;
    memset(&obj, 0, sizeof(obj));
    memset(&frames, 0, sizeof(frames));
    memset(&metadata, 0, sizeof(metadata));
    frames[5] = 128;
    frames[7] = 160;
    metadata[5] = 0x480;
    metadata[7] = 0x680;
    engine_obj.stage = 8;
    engine_obj.substage = c->substage;
    obj.active = 0x41;
    obj.id = 50;
    obj.unk2 = c->unk2;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    test_stage_graphics(metadata);
    TEST_MENU_FRAMES = (void*)frames;
    slot = c->slot;
    assert(s_StageMainIds[8][engine_obj.substage][slot] == 0x28);
    assert((u8)func_8002938C(0x28) == slot);
    engine_before = engine_obj;
    player_before = g_Player;
    memcpy(frames_before, frames, sizeof(frames_before));
    memcpy(metadata_before, metadata, sizeof(metadata_before));
    func_80069748(&obj);
    assert(obj.hurt_box == train_crate_hurt_box);
    assert(obj.animation_table == (const u8* const*)train_crate_animations);
    assert(obj.sprite_frames == (u8*)frames + frames[slot]);
    assert(obj.terrain_box == 0 && obj.attack_box == 0);
    assert(obj.unk18.val == obj.x_pos.val && obj.unk1C.val == obj.y_pos.val);
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(frames, frames_before, sizeof(frames));
    c_test_same_words(metadata, metadata_before, sizeof(metadata));
    observed_values[0] = (u32)obj.unk40;
    observed_values[1] = (u32)obj.unk42;
    observed_values[2] = (u32)obj.unk2;
    observed_values[3] = (u32)obj.ext.main_50.unk84;
    observed_values[4] = (u32)obj.hp;
    observed_values[5] = (u32)obj.state;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = TEST_PSX_LAYER(obj.unk16);
    observed_values[8] = (u32)obj.on_screen;
    observed_values[9] = (u32)(obj.collision_data == D_80108584);
    observed_values[10] = (u32)obj.x_pos.val;
    observed_values[11] = (u32)obj.y_pos.val;
#ifdef MMX4_SATURN
    {
        u32 expected[12];
        memcpy(expected, c->expected, sizeof(expected));
        expected[0] = (u16)OBJECT_STAGE_TEXTURE(slot);
        expected[1] = (u16)OBJECT_STAGE_CLUT(0x28);
        return c_test_observe(0, row, observed_values, expected, 12);
    }
#endif
    return c_test_observe(0, row, observed_values, c->expected, 12);
}

#include "support/state_cases.h"
#include "support/tile_writes.h"
void train_crate_explode(struct MainObj*);
#define TCR(st, ss, kind, below, x, y) (state_reset(1, 0, 0), memset(weapon_objects, 0, sizeof(weapon_objects)), memset(&engine_obj, 0, sizeof(engine_obj)), engine_obj.stage = st, engine_obj.substage = ss, g_Player.unk68 = NULL, so.active = 0x41, so.id = 0x32, so.state = 1, so.unk2 = kind, so.ext.main_50.unk84 = below, so.x_pos.i.hi = x, so.y_pos.i.hi = y, background_objects[0].x_pos.i.hi = x - 0x80, background_objects[0].y_pos.i.hi = 0, tile_writes_begin_wide())
#define TCRX() (state_extra = so.ext.main_50.timer | (u32)so.ext.main_50.unk84 << 8, state_extra ^= tile_writes_end(), engine_obj.stage = engine_obj.substage = 0)
#define TCR_HIT() (so.hp = 1, state_hit(&so, 0, 0, 1))
static void tcr_metal_broken(void) { TCR(8, 0, 1, 8, 0xED0, 0x160), TCR_HIT(), tile_writes_expect(9, 0xED0 - 0x20, 0x160 - 0x40, 1), func_800698D8(&so), TCRX(); }
static void tcr_stacked_broken(void)
{
    TCR(5, 1, 6, 4, 0x34E0, 0xB0), TCR_HIT();
    tile_writes_expect(6, 0x34E0 - 0x20, 0xB0 - 0x30, 1), tile_writes_expect(4, 0x34E0 - 0x20, 0xB0, 1), func_800698D8(&so), TCRX();
}
static void tcr_single_broken(void) { TCR(5, 1, 0, 0, 0x31E0, 0x50), TCR_HIT(), tile_writes_expect(0, 0x31E0 - 0x20, 0x50 - 0x30, 1), func_800698D8(&so), TCRX(); }
static void tcr_on_screen(void) { TCR(8, 0, 0, 0, 0x3A0, 0x180), background_objects[0].y_pos.i.hi = 0x100, func_800698D8(&so), TCRX(); }
static void tcr_off_screen(void) { TCR(8, 0, 0, 0, 0x3A0, 0x180), background_objects[0].x_pos.i.hi = 0x100, func_800698D8(&so), TCRX(); }
#define BOOM(count, frame) (TCR(8, 0, 0, 0, 0x3A0, 0x180), so.state = 2, so.ext.main_50.timer = count, WEAPON_FRAME_COUNTER = frame, train_crate_explode(&so), TCRX())
static void tcr_explode_sparks(void) { BOOM(0, 0); }
static void tcr_explode(void) { BOOM(0, 1); }
static void tcr_explode_end(void) { BOOM(0x2F, 1); }
static void (*const train_crate_states_cases[])(void) = {
    tcr_metal_broken,
    tcr_stacked_broken,
    tcr_single_broken,
    tcr_on_screen,
    tcr_off_screen,
    tcr_explode_sparks,
    tcr_explode,
    tcr_explode_end,
};
static const u32 train_crate_states_expected[] = {
    0x0u, 0x0u, 0xED00000u, 0x0u, 0x0u, 0x0u, 0x80000000u, 0x1u, 0x576FADE4u, 0x41002100u,
    0x0u, 0x0u, 0x34E00000u, 0x0u, 0x0u, 0x0u, 0x80000000u, 0x1u, 0x3B79DAF2u, 0x41002100u,
    0x0u, 0x0u, 0x31E00000u, 0x0u, 0x0u, 0x0u, 0x80000000u, 0x1u, 0x7246710Cu, 0x41002100u,
    0x1u, 0x0u, 0x3A00000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x41000000u,
    0x0u, 0x0u, 0x3A00000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u,
    0x1u, 0x0u, 0x3A00000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x1u, 0x41002100u,
    0x1u, 0x0u, 0x3A00000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x1u, 0x41000000u,
    0x1u, 0x0u, 0x3A00000u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x30u, 0x41000000u,
};
static u32 test_train_crate_states(u32 row)
{
    return state_run(train_crate_states_cases[row], row, &train_crate_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "func_80069748", 0, 0, 4, test_func_80069748 },
    { "train_crate_states", 0, 0, COUNT(train_crate_states_cases), test_train_crate_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4 + COUNT(train_crate_states_cases);
