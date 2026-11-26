#include "test_runtime.h"
void destructible_core_main(struct ItemObj*);
extern struct Unk_unk68 D_80108504[];
static struct WeaponObj weapons_before[16];
static u32 completion(u32 row)
{
    struct ItemObj obj, expected;
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32 slot = row % 4, flags = row / 4, i;
    memset(&obj, 0, sizeof(obj));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memcpy(weapons_before, weapon_objects, sizeof(weapons_before));
    obj.active = 1;
    obj.id = 4;
    obj.state = 1;
    obj.unk2 = slot;
    obj.unk5 = 1;
    obj.unk42 = 0x9234;
    obj.unk5C = slot ? 32 : 80;
    obj.tail_ext.unk1.unk84.previous_value = obj.unk5C;
    obj.ext.timer = 2;
    obj.unk58 = (const u8*)D_80108504;
    obj.x_pos.val = 160 * 65536 + 0x1234;
    obj.y_pos.val = 120 * 65536 + 0x5678;
    for (i = 1; i < 4; i++)
        engine_obj.character_state.bytes[i] = (flags >> (i - 1)) & 1;
    engine_before = engine_obj;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    expected = obj;
    expected.unk42 = 0x1234;
    if (!slot)
        expected.ext.timer = 1;
    else if (flags & (1 << (slot - 1)))
        expected.state = 3;
    destructible_core_main(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    c_test_same_words(weapon_objects, weapons_before, sizeof(weapons_before));
    return 1;
}
#include "support/tile_writes.h"
#include "support/state_cases.h"
void func_800C0864(struct ItemObj*);
void destructible_core_update(struct ItemObj*);
#define it state_room.item
static s32 dc_palette[0x3F0];
static s32 dc_arc[0x2D8];
static u32 dc_meta[8];
static s32 dc_frames[8];
static void dc_reset(u8 state, u8 slot)
{
    state_reset(0, 0, 0);
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    tile_writes_begin();
    TEST_PALETTE = (u8*)dc_palette;
    TEST_ARC_30 = (u8*)dc_arc;
    D_801406A8 = dc_meta;
    TEST_MENU_FRAMES = (u8*)dc_frames;
    need_palette_load = 0;
    it.active = 1;
    it.id = 4;
    it.state = state;
    it.unk2 = slot;
    it.unk5 = 1;
}
#define DCX() (state_extra = tile_writes_end() ^ ((u8)it.unk5C | (u8)it.unk7C.timer << 8 | (u8)it.ext.timer << 16 | (u32)(need_palette_load | (u8)it.tail_ext.unk1.unk88 << 4) << 24))
static void dc_init_broken(void) { dc_reset(0, 0), engine_obj.checkpoint = 2, tile_writes_expect(0, 0, 0, 1), destructible_core_update(&it), DCX(); }
#define DCINIT() (func_800C0864(&it), assert(it.unk42 == OBJECT_CLUT(0x78C0) && it.unk58 == (const u8*)D_80108504), it.unk42 = 0, DCX())
static void dc_init_side(void) { dc_reset(0, 1), engine_obj.checkpoint = 2, DCINIT(); }
static void dc_init_main(void) { dc_reset(0, 0), DCINIT(); }
#define DCMAIN(slot, setup) (dc_reset(1, slot), it.unk5C = 0x50, it.tail_ext.unk1.unk84.previous_value = 0x50, it.ext.timer = 2, setup, destructible_core_main(&it), DCX())
static void dc_main_hurt_shards(void) { DCMAIN(0, (it.unk5C = 0x40, it.ext.timer = 1)); }
static void dc_main_flash_back(void) { DCMAIN(0, (it.unk5C = 0, it.tail_ext.unk1.unk88 = 1, it.ext.timer = 1)); }
static void dc_main_full(void) { DCMAIN(0, it.ext.timer = 1); }
#define DCKILL(slot) DCMAIN(slot, (it.unk5C = 1, it.tail_ext.unk1.unk84.previous_value = 1, it.x_pos.i.hi = 0x80, it.y_pos.i.hi = 0x60, state_hit(MAIN_OBJECT(&it), 0, 0, 1), tile_writes_expect(slot, 0, 0, 1))), assert(engine_obj.character_state.bytes[slot] == 1)
static void dc_kill_0(void) { DCKILL(0); }
static void dc_kill_1(void) { DCKILL(1); }
static void dc_kill_2(void) { DCKILL(2); }
static void dc_kill_3(void) { DCKILL(3); }
#define DCDONE(slot, count, frame) (dc_reset(2, slot), it.unk7C.timer = count, WEAPON_FRAME_COUNTER = frame, cur_random = 1, destructible_core_update(&it), DCX())
static void dc_destroyed_end(void) { DCDONE(0, 1, 0); }
static void dc_destroyed_main(void) { DCDONE(0, 5, 0); }
static void dc_destroyed_side(void) { DCDONE(1, 5, 4); }
static void dc_destroyed_quiet(void) { DCDONE(1, 5, 1); }
static void dc_finish_main(void)
{
#ifdef MMX4_SATURN
    const s32* source = (const s32*)0x060A59E0;
#else
    const s32* source = &dc_arc[0x268];
#endif
    dc_reset(3, 0), it.tail_ext.unk1.unk88 = 1, destructible_core_update(&it), DCX();
    assert(background_objects[0].unk1C == 0x11C0 && background_objects[0].unk24 == 0x11C0);
    c_test_same_words(&dc_palette[0x3B8], source, 0x38 * 4);
}
static void dc_finish_side(void) { dc_reset(3, 1), destructible_core_update(&it), DCX(); }

static void (*const destructible_core_states_cases[])(void) = {
    dc_init_broken,
    dc_init_side,
    dc_init_main,
    dc_main_hurt_shards,
    dc_main_flash_back,
    dc_main_full,
    dc_kill_0,
    dc_kill_1,
    dc_kill_2,
    dc_kill_3,
    dc_destroyed_end,
    dc_destroyed_main,
    dc_destroyed_side,
    dc_destroyed_quiet,
    dc_finish_main,
    dc_finish_side,
};
static const u32 destructible_core_states_expected[] = {
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x8615EDD8u, 0x0u,
    0x101u, 0x101u, 0x6C80000u, 0x1980000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x50020u, 0x0u,
    0x101u, 0x1u, 0xCC00000u, 0x1680000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x50050u, 0x0u,
    0x101u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x11050040u, 0x2100u,
    0x101u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x1050000u, 0x2100u,
    0x101u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x50050u, 0x0u,
    0x102u, 0x1u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x58000u, 0x8614BDD8u, 0x2100u,
    0x102u, 0x101u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x58000u, 0xE0DACFE1u, 0x2100u,
    0x102u, 0x201u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x58000u, 0xE0DACFE1u, 0x2100u,
    0x102u, 0x301u, 0x800000u, 0x600000u, 0x0u, 0x0u, 0x0u, 0x58000u, 0xE0DACFE1u, 0x2100u,
    0x103u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
    0x102u, 0x1u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x400u, 0x41002100u,
    0x102u, 0x101u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x400u, 0x41002100u,
    0x102u, 0x101u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x400u, 0x0u,
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x11000000u, 0x0u,
    0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x0u, 0x0u,
};
static u32 test_destructible_core_states(u32 row)
{
    return object_run(destructible_core_states_cases[row], row, &destructible_core_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "all_core_slots_and_shared_completion_flag_combinations", NULL, NULL, 32, completion },
    { "destructible_core_states", 0, 0, COUNT(destructible_core_states_cases), test_destructible_core_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 32 + COUNT(destructible_core_states_cases);
