#include "test_runtime.h"
#include "main/layers/layer_03.h"

static struct LayerObj train_layer;
static struct MainObj saved_mains[5];
static struct ShotObj saved_shots[5];
static struct ItemObj saved_items[2];
static struct WeaponObj saved_weapon;
static u32 train_pages[0x100];
static s32 train_frames[0x100];
static u8 train_records[0x10];

static void layer_reset(u8 kind, s8 shift, u8 flash, u8 hits)
{
    u32 i;
    memset(&train_layer, 0, sizeof(train_layer));
    train_layer.active = 1;
    train_layer.unk2 = kind;
    train_layer.bg_offset = shift;
    train_layer.unk16 = flash;
    train_layer.unk17 = hits;
    train_layer.backref = (void*)train_records;
    for (i = 0; i < 5; i++) {
        main_objects[i].id = 0;
        main_objects[i].unk42 = 0x1000;
        main_objects[i].x_pos.i.hi = 0x100;
        shot_objects[i].state = 0;
        shot_objects[i].unk2 = 0;
        shot_objects[i].unk42 = 0x1000;
        shot_objects[i].x_pos.i.hi = 0x100;
    }
    for (i = 0; i < 2; i++) {
        item_objects[i].unk42 = 0x1000;
        item_objects[i].x_pos.i.hi = 0x100;
    }
    weapon_objects[0].x_pos.i.hi = 0x100;
    g_Player.x_pos.i.hi = 0x100;
}

static u32 layer_run(void (*run)(void), u32 row, const u32* expected)
{
    u32 seen[6], i;
    memcpy(saved_mains, main_objects, sizeof(saved_mains));
    memcpy(saved_shots, shot_objects, sizeof(saved_shots));
    memcpy(saved_items, item_objects, sizeof(saved_items));
    saved_weapon = weapon_objects[0];
    run();
    seen[0] = (u8)train_layer.bg_offset | (u8)train_layer.unk15 << 8 | (u8)train_layer.unk16 << 16 | (u32)(u8)train_layer.unk17 << 24;
    seen[1] = (u16)main_objects[0].x_pos.i.hi | (u32)(u16)main_objects[1].x_pos.i.hi << 16;
    seen[2] = 0;
    for (i = 0; i < 5; i++)
        seen[2] |= (main_objects[i].unk42 >> 15) << i | (shot_objects[i].unk42 >> 15) << (i + 8);
    seen[2] |= (item_objects[0].unk42 >> 15) << 16 | (item_objects[1].unk42 >> 15) << 17;
    seen[3] = (u16)shot_objects[0].x_pos.i.hi | (u32)(u16)item_objects[1].x_pos.i.hi << 16;
    seen[4] = (u16)g_Player.x_pos.i.hi | (u32)(u16)weapon_objects[0].x_pos.i.hi << 16;
    seen[5] = (u8)train_layer.active | (u32)(u8)g_Player.script_state << 8 | (u32)((u8*)&train_layer.unk18)[0] << 16;
    memcpy(main_objects, saved_mains, sizeof(saved_mains));
    memcpy(shot_objects, saved_shots, sizeof(saved_shots));
    memcpy(item_objects, saved_items, sizeof(saved_items));
    weapon_objects[0] = saved_weapon;
    return c_test_observe(0, row, seen, expected, 6);
}

static void l_wait_player(void)
{
    layer_reset(0, 0, 0, 0);
    g_Player.x_pos.i.hi = 0x1B00;
    func_800D9C84(&train_layer);
}
static void l_spawn_boss(void)
{
    layer_reset(0, 0, 0, 0);
    g_Player.x_pos.i.hi = 0x1B70;
    main_objects[0x2F].active = 0;
    D_801406A8 = train_pages;
    TEST_MENU_FRAMES = (u8*)train_frames;
    func_800D9C84(&train_layer);
}
static void l_flash_all(void)
{
    layer_reset(1, 3, 1, 0);
    func_800D9C84(&train_layer);
}
static void l_settle(void)
{
    layer_reset(1, -2, 0, 0);
    main_objects[2].unk42 = 0x9000;
    func_800D9C84(&train_layer);
}
static void l_armor_hit(void)
{
    layer_reset(1, 0, 0, 2);
    main_objects[1].id = 0x2E;
    func_800D9C84(&train_layer);
}
static void l_shot_hit(void)
{
    layer_reset(1, 0, 0, 0);
    shot_objects[0].state = 3;
    ((u8*)&train_layer.unk18)[0] = 2;
    func_800D9C84(&train_layer);
}
static void l_shot_calm(void)
{
    layer_reset(1, 0, 0, 0);
    shot_objects[0].state = 4;
    func_800D9C84(&train_layer);
}
static void l_carry_player(void)
{
    layer_reset(1, 4, 0, 0);
    train_layer.unk15 = 1;
    func_800D9C84(&train_layer);
}

static void (*const layer_cases[])(void) = {
    l_wait_player,
    l_spawn_boss,
    l_flash_all,
    l_settle,
    l_armor_hit,
    l_shot_hit,
    l_shot_calm,
    l_carry_player,
};
static const u32 layer_expected[] = { 0u, 0x1000100u, 0u, 0x1000100u, 0x1001B00u, 1u, 0u, 0x1001960u, 0u, 0x1000100u, 0x1001B70u, 0x100u, 0u, 0x1030103u, 0x31F1Fu, 0x1030103u, 0x1000100u, 1u, 0u, 0xFE00FEu, 0u, 0xFE00FEu, 0x1000100u, 1u, 0x1000000u, 0x1000100u, 2u, 0x1000100u, 0x1000100u, 1u, 0u, 0x1000100u, 0x100u, 0x1000100u, 0x1000100u, 0x10001u, 0u, 0x1000100u, 0u, 0x1000100u, 0x1000100u, 1u, 0u, 0x1040104u, 0u, 0x1040104u, 0x1040104u, 1u };

static u32 test_train_layer_states(u32 row)
{
    return layer_run(layer_cases[row], row, &layer_expected[row * 6]);
}

const struct CTestGroup c_test_groups[] = {
    { "train_layer_states", 0, 0, COUNT(layer_cases), test_train_layer_states },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(layer_cases);
