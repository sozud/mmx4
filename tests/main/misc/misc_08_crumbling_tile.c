#include "test_runtime.h"
#include "main/misc/misc_08_crumbling_tile.h"
#include "main/55C4.h"
extern struct Misc08EffectDescriptor crumbling_tile_first_effects[];
extern struct Misc08EffectTripletTable crumbling_tile_second_effects;

void crumbling_tile_update(struct MiscObj*);

static struct MiscObj tile;
static u16 pixels[13][256];
static u8 map[12];
static s32 frames[64];
static u32 metadata[32];

static u32 mix(u32 hash, u32 value)
{
    return hash * 31 + value;
}

static void prepare(u32 entry, u32 scene, u32 free)
{
    u32 i;
    c_test_zero_words((u32*)&tile, sizeof(tile) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)pixels, sizeof(pixels) / 4);
    c_test_zero_words((u32*)D_801441C8, sizeof(D_801441C8) / 4);
    for (i = 0; i < COUNT(map); i++)
        map[i] = i + 1;
    for (i = 0; i < COUNT(frames); i++)
        frames[i] = 0x40 + i * 4;
    for (i = 0; i < COUNT(metadata); i++)
        metadata[i] = 0x400 + i * 128;
    TEST_MENU_FRAMES = (u8*)frames;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    SP_BG_TILEMAP = map;
    D_801406A8 = metadata;
    layout_width = layout_height = 2;
    layout_size = 4;
    for (i = 0; i < 64; i++)
        misc_objects[i].active = !(i % 4 == 0 && i / 4 < free);
    for (i = 0; i < 3; i++)
        background_objects[i].x_pos.i.hi = scene == 2 ? 1024 : scene == 1 ? 224
                                                                          : 0;
    g_Player.bg_offset = scene % 2;
    engine_obj.stage = 2;
    tile.active = 0x41;
    tile.id = 8;
    tile.unk2 = entry >= 27 ? (entry - 27) | 0x80 : entry;
    tile.on_screen = 1;
    tile.x_pos.i.hi = scene ? 240 : 96;
    tile.y_pos.i.hi = scene ? 240 : 128;
    cur_random = scene ? 0x4321 : 0x1234;
    crumbling_tile_update(&tile);
    assert(tile.state == 1 && tile.animation_table == (u32**)D_8010DF48);
    tile.on_screen = scene != 2;
}

static u32 last_frame(u32 animation)
{
    u32 frame = 0;
    while (((union AnimationStep*)D_8010DF48[animation])[frame].fields.relative_step != 0)
        frame++;
    return frame;
}

static u32 observe(void)
{
    u32 hash = tile.state | tile.unk5 << 8 | tile.unk2 << 16 | tile.on_screen << 24, i;
    hash = mix(hash, tile.x_pos.val ^ tile.unk15);
    hash = mix(hash, tile.animation_step.packed ^ tile.unk17 << 24 ^ tile.ext.misc_8.timer);
    for (i = 0; i < 64; i++)
        if (misc_objects[i].active == 0x41)
            hash = mix(mix(hash, i ^ misc_objects[i].x_pos.val ^ misc_objects[i].unk15), misc_objects[i].y_pos.val ^ misc_objects[i].ext.misc_2.unk58);
    for (i = 0; i < sizeof(pixels) / 2; i++)
        hash = mix(hash, ((u16*)pixels)[i]);
    for (i = 0; i < sizeof(D_801441C8) / 2; i++)
        hash = mix(hash, ((u16*)D_801441C8)[i]);
    return mix(hash, cur_random);
}

static u32 init(u32 row)
{
    prepare(row, row % 2, 0);
    return observe();
}

static u32 crumble(u32 entry, u32 end, u32 free, u32 scene)
{
    u32 alternate = entry >= 27, kind = alternate ? entry - 27 : entry, animation, frame;
    prepare(entry, scene, free);
    animation = alternate && crumbling_tile_second_effects.entries[kind].second ? crumbling_tile_second_effects.entries[kind].second
        : alternate                                                             ? crumbling_tile_second_effects.entries[kind].first
                                                                                : crumbling_tile_first_effects[kind].effect_id;
    frame = last_frame(animation);
    set_animation_frame(ANIMATED_OBJECT(&tile), animation, end || frame == 0 ? frame : frame - 1);
    if (end)
        tile.animation_step.fields.duration = 1;
    tile.unk5 = alternate ? 2 : 0;
    crumbling_tile_update(&tile);
    assert(tile.state == (end || frame == 0 ? 2 : 1));
    return observe();
}

static u32 break_end(u32 row)
{
    return crumble(row, 1, 0, 0);
}

static u32 break_variant(u32 row)
{
    static const u8 variants[][4] = {
        { 0, 0, 0, 0 },
        { 27, 0, 0, 0 },
        { 13, 1, 16, 0 },
        { 26, 0, 0, 1 },
        { 0, 1, 0, 2 },
        { 27, 1, 0, 2 },
    };
    return crumble(variants[row][0], variants[row][1], variants[row][2], variants[row][3]);
}

static u32 settle(u32 row)
{
    static const u8 timers[] = { 0, 1, 15 };
    u32 kind = row % 26, phase = row / 26, animation = crumbling_tile_second_effects.entries[kind].first;
    prepare(kind + 27, 0, 0);
    set_animation_frame(ANIMATED_OBJECT(&tile), animation, phase == 0 ? 0 : last_frame(animation));
    if (phase >= 2) {
        tile.unk5 = 1;
        tile.ext.misc_8.timer = timers[phase - 2];
    }
    crumbling_tile_update(&tile);
    return observe();
}

static u32 despawn(u32 row)
{
    prepare(row, 0, 0);
    tile.state = 2;
    crumbling_tile_update(&tile);
    assert(tile.active == 0 && tile.state == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "initialize", NULL, NULL, 53, init },
    { "break", NULL, NULL, 53, break_end },
    { "break_variants", NULL, NULL, 6, break_variant },
    { "wait_and_delay", NULL, NULL, 104, settle },
    { "despawn", NULL, NULL, 2, despawn },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 53 + 53 + 6 + 104 + 2;
