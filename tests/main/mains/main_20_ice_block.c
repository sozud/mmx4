#include "test_runtime.h"
#include "main/mains/main_20_ice_block.h"
#include "support/state_cases.h"
void ice_block_start_idle(struct MainObj* arg0);
extern struct Unk_unk68 D_800FC850;
extern struct Unk_unk68 D_800FC854;
extern struct Unk_unk68 D_800FC858;
extern struct Unk_unk68 D_800FC85C;

static struct ShatterInput {
    u8 carried, top, bottom, weapon_free;
};
enum { TOP_BREAK,
    TOP_OTHER,
    TOP_SHATTER,
    BOTTOM_BREAK,
    BOTTOM_SHATTER,
    BOTTOM_OTHER,
    BOTH_SHATTER,
    POOL_FULL,
    CARRIED };
static const struct ShatterInput inputs[] = {
    { 0, 0x30, 0, 1 },
    { 0, 0x33, 0, 1 },
    { 0, 0x38, 0, 1 },
    { 0, 0, 0x31, 1 },
    { 0, 0, 0x38, 1 },
    { 0, 0, 0x34, 1 },
    { 0, 0x38, 0x38, 1 },
    { 0, 0, 0, 0 },
    { 1, 0x38, 0x38, 1 },
};
#define WEAPON_SLOT 3
static u8 tilemap[256];
static u16 tiles[2][16][16];
static u32 attributes[3];
static u32 steps[2];
static u32* table[0x10];
static struct MainObj block, expected;
static struct WeaponObj want_weapons[0x10];
static struct BackgroundObj cameras[3];

static void zero(void* target, u32 size)
{
    u32 i;
    for (i = 0; i < size / 4; i++)
        ((u32*)target)[i] = 0;
}

static u32 run(u32 mode)
{
    const struct ShatterInput* input = &inputs[mode];
    u8 flags = 0;
    union AnimationStep value;
    u32 i, difference = 0;
    for (i = 0; i < 3; i++)
        cameras[i] = background_objects[i];
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = 0;
        background_objects[i].y_pos.val = 0;
    }
    engine_obj.stage = 2;
    engine_obj.substage = 0;
    cur_random = 0x0420;
    memset(tilemap, 0, sizeof(tilemap));
    memset(tiles, 0, sizeof(tiles));
    tilemap[0] = 1;
    for (i = 0; i < 16; i++) {
        tiles[1][5][i] = 1;
        tiles[1][11][i] = 2;
    }
    attributes[0] = 0;
    attributes[1] = input->top;
    attributes[2] = input->bottom;
    SP_BG_TILEMAP = tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    zero(weapon_objects, sizeof(weapon_objects));
    zero(visual_objects, sizeof(visual_objects));
    zero(misc_objects, sizeof(misc_objects));
    for (i = 0; i < 0x10; i++)
        weapon_objects[i].active = !input->weapon_free || i != WEAPON_SLOT;
    for (i = 0; i < 0x20; i++)
        visual_objects[i].active = 1;
    for (i = 0; i < 0x40; i++)
        misc_objects[i].active = 1;
    memcpy(want_weapons, weapon_objects, sizeof(want_weapons));
    value.fields.duration = 5;
    value.fields.event = 0;
    value.fields.relative_step = 1;
    value.fields.frame_index = 3;
    steps[0] = value.packed;
    value.fields.duration = 9;
    steps[1] = value.packed;
    for (i = 0; i < COUNT(table); i++)
        table[i] = &steps[1];
    memset(&block, 0, sizeof(block));
    block.active = 0x41;
    block.id = 0x14;
    block.unk2 = input->carried;
    block.state = 1;
    block.unk5 = 2;
    block.x_pos.val = 0x00881234;
    block.y_pos.val = 0x00805678;
    block.animation_table = table;
    block.animation_cursor = &steps[0];
    block.animation_step.packed = steps[0];
    expected = block;
    func_800548B8(&block);

    if (!input->carried) {
        if (input->top == 0x38)
            flags = 1;
        if (input->bottom == 0x38)
            flags += 2;
    }
    if (flags == 3) {
        expected.unk7C = 1;
        expected.attack_box = &D_800FC858;
    } else {
        expected.unk17 = flags == 1 ? 7 : flags == 2 ? 6
                                                     : 8;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = &steps[1];
        expected.animation_step.packed = steps[1];
        expected.attack_box = flags == 1 ? &D_800FC850 : flags == 2 ? &D_800FC854
                                                                    : &D_800FC85C;
    }
    expected.unk5 = 3;
    if (input->weapon_free) {
        struct WeaponObj* weapon = &want_weapons[WEAPON_SLOT];
        weapon->active = 1;
        weapon->id = 0x3A;
        weapon->owner = PLAYER_OBJECT(&block);
        weapon->state = 0;
        weapon->unk5 = 0;
        weapon->unk6 = 0;
        weapon->unk2 = flags;
    }
    for (i = 0; i < sizeof(block) / 4; i++)
        difference |= ((u32*)&block)[i] ^ ((u32*)&expected)[i];
    for (i = 0; i < sizeof(want_weapons) / 4; i++)
        difference |= ((u32*)weapon_objects)[i] ^ ((u32*)want_weapons)[i];
    for (i = 0; i < 0x20; i++)
        difference |= visual_objects[i].active ^ 1;
    for (i = 0; i < 0x40; i++)
        difference |= misc_objects[i].active ^ 1;
    assert(difference == 0);
    assert(attributes[1] == input->top && attributes[2] == input->bottom && engine_obj.stage == 2);
    for (i = 0; i < 3; i++)
        background_objects[i] = cameras[i];
    return flags | ((u32)(u8)block.unk5 << 8) | ((u32)block.unk17 << 16) | ((u32)(u8)weapon_objects[WEAPON_SLOT].id << 24);
}

static const u32 ice_block_shatter_cases_expected[] = { 0x3A080300u, 0x3A080300u, 0x3A070301u, 0x3A080300u, 0x3A060302u, 0x3A080300u, 0x3A000303u, 0x80300u, 0x3A080300u };

static void ib_idle(void)
{
    state_reset(1, 0, 0);
    ice_block_start_idle(&so);
}

static void (*const ice_block_misc_cases[])(void) = {
    ib_idle,
};
static const u32 ice_block_misc_expected[] = { 2u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_ice_block_misc(u32 row)
{
    return state_run(ice_block_misc_cases[row], row, &ice_block_misc_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "ice_block_misc", 0, 0, COUNT(ice_block_misc_cases), test_ice_block_misc },
    { "ice_block_shatter", NULL, ice_block_shatter_cases_expected, COUNT(ice_block_shatter_cases_expected), run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ice_block_misc_cases) + COUNT(ice_block_shatter_cases_expected);
