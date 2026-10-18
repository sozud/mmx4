#include "test_runtime.h"
#include "main/items/item_01_stage_block.h"
#include "main/player.h"
#include "main/objects.h"
#include "main/tile_effects.h"

struct func_800BF638_case {
    u32 stage, pool_0_full, arg1;
    u32 expected[7];
};
static const struct func_800BF638_case func_800BF638_cases[] = {
    { 5, 0, 0, { 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { 0, 255, 46, { 1u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800BF638(u32 row)
{
    const struct func_800BF638_case* c = &func_800BF638_cases[row];
    u32 observed_values[7];
    struct BaseObj obj;
    u8 pool_0_full;
    s8 arg1;
    s16 arg2;
    s16 arg3;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&item_objects, 0, sizeof(item_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    engine_obj.stage = c->stage;
    pool_0_full = c->pool_0_full;
    arg1 = c->arg1;
    arg2 = 0;
    arg3 = 0;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            item_objects[slot].active = pool_0_full ? 1 : 0;
    }
    func_800BF638(&obj, arg1, arg2, arg3);
    observed_values[0] = (u32)item_objects[0].active;
    observed_values[1] = (u32)item_objects[0].bg_offset;
    observed_values[2] = (u32)item_objects[0].id;
    observed_values[3] = (u32)item_objects[0].unk2;
    observed_values[4] = (u32)item_objects[0].unk7C.value;
    observed_values[5] = (u32)item_objects[0].x_pos.i.hi;
    observed_values[6] = (u32)item_objects[0].y_pos.i.hi;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

void stage_block_wait_trigger(struct ItemObj*);
extern struct TileEffectRecord** tile_effect_tables[26];
static struct ItemObj items[32];
static struct MainObj mains[48];
static struct VisualObj visuals[32];
static struct MiscObj misc[64];
static struct EffectObj effects[32];
static struct ShotObj shots[32];
static struct WeaponObj weapons[16];
static struct LayerObj layers[4];
static struct PlayerObj player, entity;
static struct EngineObj engine;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds[3];
static struct ControllerInput input;
static u32 archive[64], map[192];
static u16 pixels[256], expected_pixels[256], expected_cache[3][32][32];
static u32 landing(u32 row)
{
    struct ItemObj* object;
    struct TileEffectRecord* record;
    u32 i, kind = row == 0 ? 1 : 3, ticks = 0;
    u8 *old_archive = TEST_MENU_FRAMES, *old_map = SP_BG_TILEMAP, *old_pixels = TEST_BG_TILE_PIXELS;
    s32 old_width = layout_width, old_height = layout_height, old_size = layout_size;
    u16 rng;
    u8 dirty;
    void* current[8];
    c_test_zero_words((u32*)item_objects, sizeof(item_objects) / 4);
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words(archive, COUNT(archive));
    archive[8] = 128;
    TEST_MENU_FRAMES = (u8*)archive;
    c_test_zero_words(map, COUNT(map));
    c_test_zero_words((u32*)pixels, sizeof(pixels) / 4);
    c_test_zero_words((u32*)D_801441C8, sizeof(D_801441C8) / 4);
    c_test_zero_words((u32*)expected_cache, sizeof(expected_cache) / 4);
    c_test_zero_words((u32*)expected_pixels, sizeof(expected_pixels) / 4);
    SP_BG_TILEMAP = (u8*)map;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    layout_width = 16;
    layout_height = 16;
    layout_size = 256;
    engine_obj.stage = 0;
    engine_obj.substage = 1;
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = stage_block_entries[kind].left;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    for (i = 0; i < COUNT(main_objects); i++)
        main_objects[i].active = 1;
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = 1;
    object = find_free_item_obj();
    assert(object == &item_objects[0]);
    object->active = 1;
    object->id = 1;
    object->unk2 = kind;
    stage_block_update(object);
    assert(object->state == 1 && object->unk5 == 0 && object->sprite_frames == (u8*)archive + 128);
    stage_block_wait_trigger(object);
    assert(object->unk5 == 1 && object->ext.timer == 1);
    while (object->unk5 == 1 && ticks < 100) {
        func_800BEFCC(object);
        ticks++;
    }
    assert(ticks > 0 && ticks < 100 && object->unk5 == 2 && object->y_pos.i.hi == stage_block_entries[kind].right && object->y_pos.i.hi == stage_block_entries[kind].trigger_x);
    c_test_copy_words((u32*)items, (u32*)item_objects, sizeof(items) / 4);
    c_test_copy_words((u32*)mains, (u32*)main_objects, sizeof(mains) / 4);
    c_test_copy_words((u32*)visuals, (u32*)visual_objects, sizeof(visuals) / 4);
    c_test_copy_words((u32*)misc, (u32*)misc_objects, sizeof(misc) / 4);
    c_test_copy_words((u32*)effects, (u32*)effect_objects, sizeof(effects) / 4);
    c_test_copy_words((u32*)shots, (u32*)shot_objects, sizeof(shots) / 4);
    c_test_copy_words((u32*)weapons, (u32*)weapon_objects, sizeof(weapons) / 4);
    c_test_copy_words((u32*)layers, (u32*)layer_objects, sizeof(layers) / 4);
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)backgrounds, (u32*)background_objects, sizeof(backgrounds) / 4);
    rng = cur_random;
    dirty = need_palette_load;
    current[0] = SP_CUR_MAIN_OBJ;
    current[1] = SP_CUR_ITEM_OBJ;
    current[2] = SP_CUR_VISUAL_OBJ;
    current[3] = SP_CUR_EFFECT_OBJ;
    current[4] = SP_CUR_MISC_OBJ;
    current[5] = SP_CUR_LAYER_OBJ;
    current[6] = SP_CUR_SHOT_OBJ;
    current[7] = SP_CUR_WEAPON_OBJ;
    items[0].unk5 = 3;
    if (kind == 1)
        items[0].state = 3;
    else {
        backgrounds[0].unk37 = 32;
        backgrounds[0].unk46 = 4;
        backgrounds[0].unk3E.bytes[1] = 4;
        backgrounds[0].unk3D = backgrounds[0].unk3B = 1;
        backgrounds[0].unk34 |= 1;
    }
    record = tile_effect_tables[1][(u8)stage_block_entries[kind].sound_id];
    do {
        u32 j, x = (u16)record->x / 16, y = (u16)record->y / 16;
        for (j = 0; j < (record->packed_count >> 1); j++) {
            s32 px = x * 16, py = y * 16, bx = backgrounds[record->layer].x_pos.i.hi, by = backgrounds[record->layer].y_pos.i.hi;
            assert(x < 256 && y < 256 && record->layer < 3);
            expected_pixels[(y & 15) * 16 + (x & 15)] = record->tiles[j];
            if (px >= bx - 32 && px < bx + 352 && py >= by - 32 && py < by + 272)
                expected_cache[record->layer][y & 31][x & 31] = record->tiles[j];
            if (record->packed_count & 1)
                x++;
            else
                y++;
        }
        if (!record->has_next)
            break;
        record++;
    } while (1);
    func_800BF1FC(object);
    assert(c_test_word_difference((u32*)item_objects, (u32*)items, sizeof(items) / 4) == 0 && c_test_word_difference((u32*)main_objects, (u32*)mains, sizeof(mains) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0 && c_test_word_difference((u32*)misc_objects, (u32*)misc, sizeof(misc) / 4) == 0 && c_test_word_difference((u32*)effect_objects, (u32*)effects, sizeof(effects) / 4) == 0 && c_test_word_difference((u32*)shot_objects, (u32*)shots, sizeof(shots) / 4) == 0 && c_test_word_difference((u32*)weapon_objects, (u32*)weapons, sizeof(weapons) / 4) == 0 && c_test_word_difference((u32*)layer_objects, (u32*)layers, sizeof(layers) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0 && c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)backgrounds, sizeof(backgrounds) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && need_palette_load == dirty);
    assert(SP_CUR_MAIN_OBJ == current[0] && SP_CUR_ITEM_OBJ == current[1] && SP_CUR_VISUAL_OBJ == current[2] && SP_CUR_EFFECT_OBJ == current[3] && SP_CUR_MISC_OBJ == current[4] && SP_CUR_LAYER_OBJ == current[5] && SP_CUR_SHOT_OBJ == current[6] && SP_CUR_WEAPON_OBJ == current[7]);
    assert(c_test_word_difference((u32*)pixels, (u32*)expected_pixels, sizeof(pixels) / 4) == 0 && c_test_word_difference((u32*)D_801441C8, (u32*)expected_cache, sizeof(expected_cache) / 4) == 0);
    for (i = 0; i < COUNT(map); i++)
        assert(map[i] == 0);
    for (i = 0; i < COUNT(archive); i++)
        assert(archive[i] == (i == 8 ? 128 : 0));
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    assert(TEST_MENU_FRAMES == (u8*)archive && SP_BG_TILEMAP == (u8*)map && TEST_BG_TILE_PIXELS == (u8*)pixels && layout_width == 16 && layout_height == 16 && layout_size == 256);
    TEST_MENU_FRAMES = old_archive;
    SP_BG_TILEMAP = old_map;
    TEST_BG_TILE_PIXELS = old_pixels;
    layout_width = old_width;
    layout_height = old_height;
    layout_size = old_size;
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "func_800BF638", 0, 0, 2, test_func_800BF638 },
    { "actual_block_fall_capacity_and_variant3", NULL, NULL, 2, landing },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 2 + 2;
