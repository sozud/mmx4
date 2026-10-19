#include "test_runtime.h"
#include "main/mains/main_53_wave_rider.h"
#include "main/55C4.h"
#include "support/state_cases.h"
void wave_rider_catch_up(struct MainObj* arg0);
void wave_rider_idle(struct MainObj* arg0);
extern union AnimationStep* wave_rider_animations[27];

static struct WaveInput {
    u8 tile, bob, air;
    s16 timer;
};
static const struct WaveInput inputs[] = {
    { 0, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 5, 0, 0, 0 },
    { 9, 0, 0, 0 },
    { 0, 1, 1, 0 },
};
static u8 tilemap[256];
static u16 pixels[512];
static u32 attributes[1];
static u32 wave_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct BackgroundObj bg_before[3];
    struct Unk_unk68 bounds = { 0, 0, 4, 4 };
    const struct WaveInput* input = &inputs[mode];
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = 53;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = input->bob;
    obj.air_state = input->air;
    obj.unk7C = input->timer;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 80 * 65536 + 0x5678;
    obj.x_speed = 0x10000;
    obj.y_speed = 0x1000;
    obj.terrain_box = &bounds;
    obj.ext.main_53.unk80 = input->tile;
    obj.ext.main_53.unk84 = 1;
    obj.animation_table = (const u8* const*)wave_rider_animations;
    set_animation(&obj, 0);
    obj.animation_step.fields.duration = 2;
    before = obj;
    player_before = g_Player;
    memcpy(bg_before, background_objects, sizeof(bg_before));
    memset(tilemap, 1, sizeof(tilemap));
    memset(pixels, 0, sizeof(pixels));
    attributes[0] = input->tile;
    SP_BG_TILEMAP = tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    func_8006B6B0(&obj);
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.air_state = obj.air_state;
    before.on_screen = obj.on_screen;
    before.unk7C = obj.unk7C;
    before.ext.main_53.unk80 = obj.ext.main_53.unk80;
    before.ext.main_53.unk81 = obj.ext.main_53.unk81;
    before.ext.main_53.unk84 = 0;
    before.x_pos = obj.x_pos;
    before.y_pos = obj.y_pos;
    before.x_speed = obj.x_speed;
    before.y_speed = obj.y_speed;
    before.x_accel = 0;
    before.gravity = obj.gravity;
    before.animation_step = obj.animation_step;
    if (obj.unk17 != before.unk17) {
        before.unk17 = obj.unk17;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)wave_rider_animations[obj.unk17];
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    assert(bounds.unk0 == 0 && bounds.unk1 == 0 && bounds.unk2 == 4 && bounds.unk3 == 4);
    for (i = 0; i < COUNT(tilemap); i++)
        assert(tilemap[i] == 1);
    for (i = 0; i < COUNT(pixels); i++)
        assert(pixels[i] == 0);
    assert(attributes[0] == input->tile && SP_BG_TILEMAP == tilemap
        && SP_BG_TILE_PIXELS == pixels && SP_BG_TILE_ATTRS == attributes);
    assert(layout_width == 16 && layout_size == 256);
    switch (observation) {
    case 0:
        actual = (u8)obj.unk5 | ((u32)(u8)obj.air_state << 8)
            | ((u32)(u8)obj.unk6 << 16) | ((u32)obj.ext.main_53.unk81 << 24);
        break;
    case 1:
        actual = (u16)obj.unk7C | ((u32)obj.ext.main_53.unk80 << 16)
            | ((u32)obj.ext.main_53.unk84 << 24);
        break;
    case 2:
        actual = obj.x_pos.val;
        break;
    case 3:
        actual = obj.y_pos.val;
        break;
    case 4:
        actual = obj.x_speed;
        break;
    case 5:
        actual = obj.y_speed;
        break;
    case 6:
        actual = obj.gravity;
        break;
    case 7:
        actual = obj.animation_step.packed;
        break;
    default:
        actual = obj.on_screen | ((u32)obj.unk17 << 8);
        break;
    }
    return actual;
}
static const u32 wave_rider_terrain_context_cases_expected[] = { 0x104u, 0x0u, 0x651234u, 0x504678u, 0x80000u, 0x1000u, 0x0u, 0x10002u, 0x301u, 0x1000104u, 0x10000u, 0x651234u, 0x504678u, 0x80000u, 0x1000u, 0x0u, 0x2010002u, 0x501u, 0x5000104u, 0x50000u, 0x651234u, 0x504678u, 0x80000u, 0x1000u, 0x0u, 0x1010002u, 0x401u, 0x9000104u, 0x90000u, 0x651234u, 0x504678u, 0x80000u, 0x1000u, 0x0u, 0x10002u, 0x301u, 0x10103u, 0x0u, 0x651234u, 0x504678u, 0x10000u, 0x1000u, 0x0u, 0x10001u, 0x1u };
static u32 wave_rider_terrain_context_cases_row(u32 row)
{
    return wave_case(row / 9, row % 9);
}

static const u32 wave_rider_wait_offscreen_expected[] = { 1u, 2u };
static u32 test_wave_rider_wait_offscreen(u32 row)
{
    u32 observed_values[2];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.x_pos.val = -1048575;
    background_objects[0].x_pos.val = 2;
    background_objects[1].x_pos.val = 256;
    wave_rider_wait_offscreen(&obj);
    observed_values[0] = (u32)obj.state;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, wave_rider_wait_offscreen_expected, 2);
}

#define WR(step, attr) (state_reset(step, 0, 0), state_terrain(attr), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x40, so.terrain_box = &state_hit_box)
#define RIDE(attr) (WR(3, attr), func_8006B6B0(&so), so.unk7E = so.ext.main_53.unk81)
static void wr_catch_up(void)
{
    WR(4, 0);
    background_objects[0].x_pos.i.hi = 0x80;
    wave_rider_catch_up(&so);
}
static void wr_catch_up_far(void)
{
    WR(4, 0);
    so.x_pos.i.hi = 0x200;
    wave_rider_catch_up(&so);
}
static void wr_ride_wait(void)
{
    WR(3, 0);
    so.unk7C = 2;
    func_8006B6B0(&so);
}
static void wr_ride_air(void)
{
    WR(3, 0);
    so.air_state = 1;
    func_8006B6B0(&so);
}
static void wr_ride_open(void) { RIDE(0); }
static void wr_ride_low(void) { RIDE(3); }
static void wr_ride_mid(void) { RIDE(6); }
static void wr_ride_high(void) { RIDE(0xA); }
static void wr_idle(void)
{
    WR(1, 0);
    wave_rider_idle(&so);
}

static void (*const wave_rider_states_cases[])(void) = {
    wr_catch_up,
    wr_catch_up_far,
    wr_ride_wait,
    wr_ride_air,
    wr_ride_open,
    wr_ride_low,
    wr_ride_mid,
    wr_ride_high,
    wr_idle,
};
static const u32 wave_rider_states_expected[] = { 4u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x2050000u, 0x50000u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 1u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x1000004u, 0u, 0x800000u, 0x80000u, 0u, 0u, 3u, 0u, 0u, 0u, 0x1000004u, 0u, 0x800000u, 0x80000u, 0u, 0u, 3u, 0u, 0u, 0u, 0x1000004u, 0x30000u, 0x800000u, 0x80000u, 0u, 0u, 5u, 0u, 0u, 0u, 0x1000004u, 0x60000u, 0x800000u, 0x80000u, 0u, 0u, 4u, 0u, 0u, 0u, 0x1000004u, 0xA0000u, 0x800000u, 0x80000u, 0u, 0u, 3u, 0u, 0u, 0u, 1u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_wave_rider_states(u32 row)
{
    return state_run(wave_rider_states_cases[row], row, &wave_rider_states_expected[row * 10]);
}

extern union AnimationStep* wave_rider_animations[27];
extern struct Unk_unk68 wave_rider_terrain_box, wave_rider_attack_box;
extern struct Unk_unk68 D_80107878[];
void func_8006AF70(struct MainObj*);
void func_8006B5F8(struct MainObj*);

static struct MainObj obj, expected;
static struct PlayerObj player_before, entity_before;
static struct EngineObj engine_before;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds_before[3];
static struct ShotObj shots_expected[32];
static struct VisualObj visuals_expected[32];
static u8 tilemap_wave_rider_transitions[3 * 256];
static u16 tiles[4][16][16];
static u32 attributes_wave_rider_transitions[3];
static const u32 animation_words[3][7] = {
    { 0x00010002, 0x04010002, 0x05010006, 0x04010001, 0x00010001, 0x06010003, 0x00000101 },
    { 0x01010002, 0x07010002, 0x08010006, 0x07010001, 0x01010001, 0x09010003, 0x01000001 },
    { 0x02010002, 0x0A010002, 0x0B010006, 0x0A010001, 0x02010001, 0x0C010003, 0x02000101 },
};
static const s16 cameras[3][2] = { { 0, 0 }, { 512, 64 }, { 1024, 128 } };

static void prepare(u32 subtype, u32 layer)
{
    u32 i, b;
    c_test_zero_words((u32*)&obj, sizeof(obj) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&g_Entity, sizeof(g_Entity) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)&main_bss_state, sizeof(main_bss_state) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(tilemap_wave_rider_transitions); i++)
        tilemap_wave_rider_transitions[i] = i / 256 + 1;
    for (b = 0; b < 4; b++)
        for (i = 0; i < 256; i++)
            ((u16*)tiles[b])[i] = b ? b - 1 : 0;
    attributes_wave_rider_transitions[0] = 0x24;
    attributes_wave_rider_transitions[1] = 0x38;
    attributes_wave_rider_transitions[2] = 5;
    SP_BG_TILEMAP = tilemap_wave_rider_transitions;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes_wave_rider_transitions;
    layout_width = layout_height = 16;
    layout_size = 256;
    for (i = 0; i < 3; i++) {
        background_objects[i].x_pos.val = cameras[i][0] * 65536;
        background_objects[i].y_pos.val = cameras[i][1] * 65536;
    }
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 7;
        shot_objects[i].x_pos.val = (100 + i) * 65536 + 0x1234;
        shot_objects[i].unk50.data = (u8*)&wave_rider_terrain_box;
        shot_objects[i].unk54 = (u8*)&wave_rider_attack_box;
        shot_objects[i].unk68 = &wave_rider_terrain_box;
        shot_objects[i].unk98 = shot_objects[i].unk61 = shot_objects[i].unk64 = 1;
        shot_objects[i].unk65 = shot_objects[i].unk66 = shot_objects[i].unk72 = 1;
        shot_objects[i].unk73 = shot_objects[i].unk74 = shot_objects[i].unk76 = 1;
        shot_objects[i].unk77 = shot_objects[i].unk78 = shot_objects[i].unk62 = 1;
        shot_objects[i].unk63 = shot_objects[i].unk7A = shot_objects[i].unk75 = 1;
        visual_objects[i].active = 1;
        visual_objects[i].id = 8;
        visual_objects[i].x_pos.val = (200 + i) * 65536 + 0x5678;
        visual_objects[i].unk50 = &g_Entity;
    }
    g_Player.hp = 24;
    g_Player.bg_offset = layer;
    g_Entity.hp = 17;
    engine_obj.stage = 6;
    engine_obj.substage = 1;
    obj.active = 0x41;
    obj.id = 53;
    obj.unk2 = subtype;
    obj.on_screen = 1;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk15 = 0x40;
    obj.bg_offset = layer;
    obj.x_pos.val = (cameras[layer][0] + 100) * 65536 + 0x1234;
    obj.y_pos.val = (cameras[layer][1] + 160) * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)wave_rider_animations;
    obj.terrain_box = &wave_rider_terrain_box;
    obj.attack_box = &wave_rider_attack_box;
    obj.hp = 4;
    obj.contact_damage = 3;
    obj.invincibility_timer = 7;
    obj.unk62 = 5;
    obj.unk7C = 19;
    obj.unk7E = 9;
    obj.unk16 = 3;
    obj.x_speed = 0x50000;
    obj.x_accel = 0x1000;
    obj.y_speed = -0x10000;
    obj.gravity = 0x5000;
    set_animation(&obj, 0);
    controller_input.held = 0x1234;
    controller_input.previous = 0x5678;
    controller_input.pressed = 0x840;
    need_palette_load = 0x20;
    cur_random = 0x1234;
}

static void capture(void)
{
    expected = obj;
    player_before = g_Player;
    entity_before = g_Entity;
    engine_before = engine_obj;
    main_before = main_bss_state;
    c_test_copy_words((u32*)backgrounds_before, (u32*)background_objects, sizeof(backgrounds_before) / 4);
    c_test_copy_words((u32*)shots_expected, (u32*)shot_objects, sizeof(shots_expected) / 4);
    c_test_copy_words((u32*)visuals_expected, (u32*)visual_objects, sizeof(visuals_expected) / 4);
}

#define SAME(a, b) assert(c_test_word_difference((const u32*)(a), (const u32*)(b), sizeof(*(b)) / 4) == 0)
static void check(void)
{
    u32 i, b;
    SAME(&obj, &expected);
    SAME(&g_Player, &player_before);
    SAME(&g_Entity, &entity_before);
    SAME(&engine_obj, &engine_before);
    SAME(&main_bss_state, &main_before);
    SAME(&background_objects, &backgrounds_before);
    SAME(&shot_objects, &shots_expected);
    SAME(&visual_objects, &visuals_expected);
    assert(controller_input.held == 0x1234 && controller_input.previous == 0x5678 && controller_input.pressed == 0x840);
    assert(cur_random == 0x1234 && need_palette_load == 0x20);
    assert(SP_BG_TILEMAP == tilemap_wave_rider_transitions && TEST_BG_TILE_PIXELS == (u8*)tiles && TEST_BG_TILE_ATTRS == (u8*)attributes_wave_rider_transitions);
    assert(layout_width == 16 && layout_height == 16 && layout_size == 256);
    for (i = 0; i < COUNT(tilemap_wave_rider_transitions); i++)
        assert(tilemap_wave_rider_transitions[i] == i / 256 + 1);
    for (b = 0; b < 4; b++)
        for (i = 0; i < 256; i++)
            assert(((u16*)tiles[b])[i] == (b ? b - 1 : 0));
    assert(wave_rider_terrain_box.unk0 == -7 && wave_rider_terrain_box.unk1 == 15);
    assert(wave_rider_terrain_box.unk2 == 33 && wave_rider_terrain_box.unk3 == 11);
    assert(wave_rider_attack_box.unk0 == -30 && wave_rider_attack_box.unk1 == -10);
    assert(wave_rider_attack_box.unk2 == 49 && wave_rider_attack_box.unk3 == 30);
    for (b = 0; b < 3; b++)
        for (i = 0; i < 7; i++)
            assert(wave_rider_animations[b][i].packed == animation_words[b][i]);
}

static void expect_animation(u32 animation)
{
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (const u8*)wave_rider_animations[animation];
    expected.animation_step.packed = animation_words[animation][0];
}

static u32 test_initialization(u32 row)
{
    static const s8 slots[] = { -1, 0, 15, 31 };
    u32 subtype = row % 5, old_layer = row % 3, new_layer = row / 3 % 3;
    s32 shot = slots[row / 5], visual = slots[(row / 5 + 1) % 4];
    prepare(subtype, old_layer);
    g_Player.bg_offset = new_layer;
    obj.state = 0;
    obj.unk15 = row % 2 ? 0 : 0x40;
    obj.ext.main_53.unk84 = 1;
    if (shot >= 0)
        shot_objects[shot].active = 0;
    if (visual >= 0)
        visual_objects[visual].active = 0;
    capture();
    expected.ext.main_53.unk84 = 0;
    expected.x_speed = subtype < 3 ? 0x80000 : 0x54000;
    expected.unk5 = subtype < 3 ? 1 : subtype == 3 ? 2
                                                   : 5;
    expected.state = subtype >= 3;
    expected.unk15 = subtype == 4 ? 0 : 0x40;
    expected.ext.main_53.unk80 = attributes_wave_rider_transitions[old_layer];
    expected.unk7C = 0x3C;
    expected.collision_data = D_80107878;
    expected.unk16 = 5;
    expected.invincibility_timer = expected.unk62 = 0;
    expected.x_accel = expected.y_speed = expected.gravity = 0;
    expected.hp = 6;
    expected.contact_damage = 5;
    expected.air_state = 0;
    expected.bg_offset = new_layer;
    expect_animation(0);
    if (subtype == 0 && shot >= 0) {
        struct ShotObj* s = &shots_expected[shot];
        s->active = 0x41;
        s->id = 0x1C;
        s->unk2 = 0;
        s->unk7C = WEAPON_OBJECT(&obj);
        s->unk50.data = s->unk54 = NULL;
        s->unk68 = NULL;
        s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = 0;
        s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = s->unk78 = 0;
        s->unk62 = s->unk63 = s->unk7A = s->unk75 = 0;
    }
    if (visual >= 0) {
        visuals_expected[visual].active = 0x41;
        visuals_expected[visual].id = 0x15;
        visuals_expected[visual].unk50 = PLAYER_OBJECT(&obj);
    }
    func_8006AF70(&obj);
    check();
    assert(attributes_wave_rider_transitions[0] == 0x24 && attributes_wave_rider_transitions[1] == 0x38 && attributes_wave_rider_transitions[2] == 5);
    return 1;
}

static u32 test_camera_handoff(u32 row)
{
    static const s32 offsets[] = { -0x20000, -0x1FFFF, 0, 0x1FFFF, 0x20000, 0x30000 };
    u32 subtype = row % 3, layer = row / 3 % 3, path = row / 9 % 3;
    s32 offset = offsets[row / 27];
    u32 i, hit = path != 2 && offset > -0x20000 && offset < 0x20000;
    prepare(subtype, layer);
    obj.unk6 = path != 0;
    obj.air_state = path != 0;
    obj.unk7E = path == 2 ? 1 : 0;
    obj.x_pos.val = (cameras[layer][0] + 64) * 65536 + offset - (path == 1 ? 0x80000 : 0x50000);
    obj.ext.main_53.unk80 = path == 0 ? 0x38 : 0;
    for (i = 0; i < 3; i++)
        attributes_wave_rider_transitions[i] = path == 0 ? 0x38 : path == 1 ? 0x24
                                                                            : 0;
    obj.x_accel = 0;
    if (path == 0)
        obj.y_speed = obj.gravity = 0;
    else if (path == 2)
        obj.y_speed = 0x60000;
    capture();
    expected.ext.main_53.unk84 = 1;
    expected.ext.main_53.unk81 = attributes_wave_rider_transitions[layer];
    if (path == 1) {
        expected.x_speed = 0x80000;
        expected.air_state = expected.unk6 = 0;
        expect_animation(0);
    } else {
        expected.animation_step.fields.duration--;
        if (path == 2)
            expected.unk7E = 0;
    }
    expected.x_pos.val += expected.x_speed;
    expected.y_pos.val -= expected.y_speed;
    expected.y_speed -= expected.gravity;
    if (hit && subtype == 0) {
        expected.x_speed = 0x60000;
        expected.unk5 = 3;
        expected.unk7C = 0x28;
    } else if (hit && subtype == 1) {
        expect_animation(2);
        expected.x_speed = 0x90000;
        expected.y_speed = 0x80000;
        expected.gravity = 0x5000;
        expected.unk5 = 2;
        expected.air_state = expected.unk6 = 1;
        expected.unk7E = 2;
    }
    expected.on_screen = 1;
    func_8006B5F8(&obj);
    check();
    for (i = 0; i < 3; i++)
        assert(attributes_wave_rider_transitions[i] == (path == 0 ? 0x38 : path == 1 ? 0x24
                                                                                     : 0));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "wave_rider_states", 0, 0, COUNT(wave_rider_states_cases), test_wave_rider_states },
    { "wave_rider_terrain_context", NULL, wave_rider_terrain_context_cases_expected, COUNT(wave_rider_terrain_context_cases_expected), wave_rider_terrain_context_cases_row },
    { "wave_rider_wait_offscreen", 0, 0, 1, test_wave_rider_wait_offscreen },
    { "initialization", 0, 0, 20, test_initialization },
    { "camera_handoff", 0, 0, 57, test_camera_handoff },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(wave_rider_states_cases) + COUNT(wave_rider_terrain_context_cases_expected) + 1 + 20 + 57;
