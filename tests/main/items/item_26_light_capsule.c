#include "test_runtime.h"
#include "main/items/item_26_light_capsule.h"
#include "main/195B4.h"
#include "archive_memory.h"
#include "main/collision.h"
#include "main/player_animations.h"
#include "main/player.h"
#include "main/player_special.h"
#include "main/player_enter.h"
#include "main/player_common.h"
#include "main/55C4.h"
#include "main/objects.h"
extern struct Item26AnimationStep* light_capsule_animations[14];
extern s32 player_gfx_buf_0[1024];
extern s32 D_80139538;
extern s32 D_80139540;
extern s32 D_80139544;
extern s16 D_80139560;
extern s32 D_80175EE8[2];

static u32 visual_case(u32 mode, u32 observation)
{
    struct VisualObj obj, before;
    struct PlayerObj owner, owner_before;
    u8 frames[] = { 0x27, 0x28, 0x29, 0x2A };
    u32 i, index = mode == 0 ? 2 : mode == 1 ? 7
        : mode == 2                          ? 8
                                             : 9;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    obj.active = 0x41;
    obj.id = mode == 0 ? 35 : mode == 1 ? 36
        : mode == 4                     ? 38
                                        : 37;
    obj.unk2 = mode == 0 ? 2 : mode == 3 ? 1
                                         : 0;
    obj.state = 2;
    obj.unk5 = 0x27;
    obj.unk15 = 0x40;
    obj.unk16 = 0x25;
    owner.x_pos.val = 100 * 65536 + 0x1234;
    owner.y_pos.val = 200 * 65536 + 0x5678;
    owner.unk3C = frames;
    owner.unk40 = 0x2468;
    owner.unk42 = 0x1357;
    owner.animation_table = (const u8* const*)light_capsule_animations;
    before = obj;
    owner_before = owner;
    capsule_visual_init(&obj, &owner);
    before.on_screen = 1;
    before.unk3C = frames;
    before.animation_table = owner.animation_table;
    before.unk40 = 0x2468;
    before.unk42 = 0x1357;
    before.unk15 = 0;
    before.x_pos = owner.x_pos;
    before.y_pos = owner.y_pos;
    before.unk5 = 0;
    before.state = 3;
    if (mode != 4) {
        before.unk16 = mode == 0 ? 3 : mode == 1 ? 1
                                                 : 0;
        before.unk17 = index;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)light_capsule_animations[index];
        memcpy(&before.animation_step, light_capsule_animations[index], sizeof(before.animation_step));
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    assert(frames[0] == 0x27 && frames[1] == 0x28 && frames[2] == 0x29 && frames[3] == 0x2A);
    if (observation == 0)
        return obj.animation_step.packed;
    if (observation == 1)
        return obj.unk40 | ((u32)obj.unk42 << 16);
    return (u8)obj.state | ((u32)obj.unk16 << 8) | ((u32)obj.unk17 << 16);
}
static const u32 capsule_visual_animation_context_cases_expected[] = { 0x1D010002u, 0x13572468u, 0x20303u, 0x1B010002u, 0x13572468u, 0x70103u, 0x1E010001u, 0x13572468u, 0x80003u, 0x2C010001u, 0x13572468u, 0x90003u, 0x0u, 0x13572468u, 0x2503u };
static u32 capsule_visual_animation_context_cases_row(u32 row)
{
    return visual_case(row / 3, row % 3);
}

static const u32 inputs_0[3][10] = {
    { -1, 0, 0, 0, 0, -1, -1, -1, 0, 0 },
    { -1, 2, 0, 0, 0, 0, -1, -1, 0, 0 },
    { -1, 3, 0, 0, 0, 0, -1, -1, 0, 0 },
};
struct func_800C6EDC_case {
    u32 expected[15];
};
static const struct func_800C6EDC_case func_800C6EDC_cases[] = {
    { { 0xFu, 2u, 2u, 0xFu, 0u, 0u, 0u, 1u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 4u, 1u, 1u, 4u, 0u, 0u, 0u, 1u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 4u, 2u, 2u, 4u, 0u, 0u, 0u, 1u, 0xFFFFFFFFu, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800C6EDC(u32 row)
{
    const struct func_800C6EDC_case* c = &func_800C6EDC_cases[row];
    u32 observed_values[15];
    struct VisualObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&player_gfx_buf_0, 0, sizeof(player_gfx_buf_0));
    memset(&player_gfx_buf_1, 0, sizeof(player_gfx_buf_1));
    memset(&vram_rect_ptr, 0, sizeof(vram_rect_ptr));
    obj.state = inputs_0[row][0];
    obj.unk2 = inputs_0[row][1];
    g_Player.unk15 = inputs_0[row][2];
    g_Player.x_pos.val = inputs_0[row][3];
    g_Player.y_pos.val = inputs_0[row][4];
    engine_obj.unk37 = inputs_0[row][5];
    obj.animation_step.fields.relative_step = inputs_0[row][6];
    obj.animation_step.fields.event = inputs_0[row][7];
    g_Player.armor_parts = inputs_0[row][8];
    g_Player.arm_type = inputs_0[row][9];
    func_800C6EDC(&obj);
    observed_values[0] = (u32)engine_obj.armor_parts;
    observed_values[1] = (u32)engine_obj.arm_type;
    observed_values[2] = (u32)g_Player.arm_type;
    observed_values[3] = (u32)g_Player.armor_parts;
    observed_values[4] = (u32)g_Player.item_step;
    observed_values[5] = (u32)obj.active;
    observed_values[6] = (u32)obj.animation_step.fields.event;
    observed_values[7] = (u32)obj.on_screen;
    observed_values[8] = (u32)obj.state;
    observed_values[9] = (u32)obj.unk15;
    observed_values[10] = (u32)obj.unk16;
    observed_values[11] = (u32)obj.unk40;
    observed_values[12] = (u32)obj.unk42;
    observed_values[13] = (u32)obj.x_pos.val;
    observed_values[14] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, c->expected, 15);
}

static const u32 light_capsule_wait_player_expected[] = { 0u, 0u };
static u32 test_light_capsule_wait_player(u32 row)
{
    u32 observed_values[2];
    struct ItemObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137CC0, 0, sizeof(D_80137CC0));
    memset(&D_80139514, 0, sizeof(D_80139514));
    memset(&D_80139520, 0, sizeof(D_80139520));
    memset(&D_80139524, 0, sizeof(D_80139524));
    memset(&D_80139528, 0, sizeof(D_80139528));
    memset(&D_80139530, 0, sizeof(D_80139530));
    memset(&D_80139538, 0, sizeof(D_80139538));
    memset(&D_80139540, 0, sizeof(D_80139540));
    memset(&D_80139544, 0, sizeof(D_80139544));
    memset(&D_8013955C, 0, sizeof(D_8013955C));
    memset(&D_80139560, 0, sizeof(D_80139560));
    memset(&D_80139564, 0, sizeof(D_80139564));
    memset(&D_80139568, 0, sizeof(D_80139568));
    memset(&D_80141BD4, 0, sizeof(D_80141BD4));
    memset(&D_80171EA9, 0, sizeof(D_80171EA9));
    memset(&D_80173C84, 0, sizeof(D_80173C84));
    memset(&D_80175EE8, 0, sizeof(D_80175EE8));
    memset(&engine_obj, 0, sizeof(engine_obj));
    g_Player.y_pos.i.hi = 4096;
    light_capsule_wait_player(&obj);
    observed_values[0] = (u32)obj.unk15;
    observed_values[1] = (u32)obj.unk5;
    return c_test_observe(0, row, observed_values, light_capsule_wait_player_expected, 2);
}

#include "support/pool_full.h"
static u32 pool_full_light_capsule_spawn_visual(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    light_capsule_spawn_visual(&pf_item, 0, 0);
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_light_capsule_spawn_visual,
};

static const u32 pool_full_cases_expected[] = { 0x50000u };

extern u8 light_capsule_terrain_box[4];
static u8 capsule_tilemap[128];
static u16 capsule_tiles[2][16][16];
static u32 capsule_attributes[2] = { 0, 0x38 };
static s32 capsule_frames[16];
static u32 capsule_metadata[16];

static const struct {
    u8 character, special, armor, subtype, arm, keep;
} capsule_eligibility[] = {
    { 0, 0, 0, 0, 0, 1 },
    { 0, 0, 1, 0, 0, 0 },
    { 0, 0, 2, 0, 0, 1 },
    { 0, 1, 0, 0, 0, 1 },
    { 0, 1, 1, 0, 0, 0 },
    { 0, 1, 4, 2, 2, 0 },
    { 0, 0, 4, 2, 0, 0 },
    { 0, 0, 4, 2, 1, 0 },
    { 0, 0, 4, 2, 2, 1 },
    { 0, 0, 4, 3, 0, 0 },
    { 0, 0, 4, 3, 1, 1 },
    { 0, 0, 4, 3, 2, 0 },
    { 0, 0, 0, 2, 0, 1 },
    { 0, 0, 0, 3, 0, 1 },
    { 1, 0, 0, 0, 0, 0 },
    { 1, 1, 0, 0, 0, 0 },
    { 0, 0, 8, 4, 0, 0 },
    { 0, 0, 0, 4, 0, 1 },
    { 0, 0, 2, 1, 0, 0 },
    { 0, 0, 0, 1, 0, 1 },
};

static u32 test_capsule_eligibility(u32 row)
{
    static const u8 visual_kinds[] = { 3, 4, 5, 5, 6 };
    struct ItemObj obj, before;
    struct PlayerObj expected_player;
    struct StageObjectRecord record;
    u32 i, y, x, mode = row < COUNT(capsule_eligibility) ? row : 0;
    u32 pools = row < COUNT(capsule_eligibility) ? 0 : row - COUNT(capsule_eligibility) + 1;
    union AnimationStep first_frame;
    memset(&obj, 0, sizeof(obj));
    memset(&record, 0, sizeof(record));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_Entity, 0, sizeof(g_Entity));
    memset(&qux_object, 0, sizeof(qux_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(item_objects, 0, sizeof(item_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < COUNT(item_objects); i++)
        item_objects[i].active = (pools & 1) != 0;
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = (pools & 2) != 0;
    memset(capsule_tilemap, 1, sizeof(capsule_tilemap));
    memset(capsule_tiles, 0, sizeof(capsule_tiles));
    for (y = 6; y < 16; y++)
        for (x = 0; x < 16; x++)
            capsule_tiles[1][y][x] = 1;
    SP_BG_TILEMAP = capsule_tilemap;
    TEST_BG_TILE_PIXELS = (u8*)capsule_tiles;
    TEST_BG_TILE_ATTRS = (u8*)capsule_attributes;
    layout_width = 16;
    layout_size = 128;
    engine_obj.stage = 7;
    engine_obj.substage = 1;
    engine_obj.unk37 = capsule_eligibility[mode].special;
    g_Player.unk2 = capsule_eligibility[mode].character;
    g_Player.armor_parts = capsule_eligibility[mode].armor;
    g_Player.arm_type = capsule_eligibility[mode].arm;
    g_Player.item_step = 9;
    obj.active = 0x41;
    obj.id = 26;
    obj.unk2 = capsule_eligibility[mode].subtype;
    obj.unk5 = 9;
    obj.unk6 = 2;
    obj.unk7 = 3;
    obj.unk15 = 0x40;
    obj.x_pos.val = 64 * 65536;
    obj.y_pos.val = (mode == 0 ? 84 : 48) * 65536;
    obj.unk18 = obj.x_pos;
    obj.unk1C = obj.y_pos;
    record.flags = 0x81;
    obj.backref = &record;
    before = obj;
    expected_player = g_Player;
    assert(s_StageMainIds[7][1][9] == 0xA2);
    for (i = 0; i < 16; i++) {
        capsule_frames[i] = 0;
        capsule_metadata[i] = 0;
    }
    capsule_frames[9] = 64;
    capsule_metadata[9] = 0x2000;
    TEST_MENU_FRAMES = (u8*)capsule_frames;
    D_801406A8 = capsule_metadata;
    light_capsule_update(&obj);
    if (!capsule_eligibility[mode].keep) {
        before.active = before.id = before.unk2 = before.on_screen = 0;
        before.state = before.unk5 = before.unk6 = before.unk7 = 0;
        c_test_same_words(&obj, &before, sizeof(obj));
        assert(record.flags == 0);
    } else {
        assert(obj.active == 0x41 && obj.id == 26);
        assert(obj.state == 1 && obj.unk5 == 0);
        assert(obj.unk6 == 2 && obj.unk7 == 3);
        assert(obj.on_screen == 1 && obj.bg_offset == 0);
        assert(obj.unk68 == (struct Unk_unk68*)light_capsule_terrain_box);
        assert(obj.animation_table == (const u8* const*)light_capsule_animations);
        assert(obj.animation_cursor == (const u8*)light_capsule_animations[0]);
        memcpy(&first_frame, light_capsule_animations[0], sizeof(first_frame));
        assert(obj.animation_step.packed == first_frame.packed);
        assert(obj.previous_animation_index == 0xFF && obj.unk17 == 0);
        assert(obj.sprite_frames == (const u8*)capsule_frames + 64);
        assert(obj.unk40 == 64 && obj.unk42 == 0x78CC);
        assert(obj.unk16 == 4 && obj.unk15 == 0 && obj.unk75 == 1);
        assert(obj.x_pos.val == 64 * 65536 && obj.y_pos.val == 84 * 65536);
        assert(obj.unk18.val == before.unk18.val && obj.unk1C.val == before.unk1C.val);
        assert((obj.unk70 & 8) != 0 && record.flags == 0x81);
        expected_player.item_step = 0;
    }
    c_test_same_words(&g_Player, &expected_player, sizeof(g_Player));
    for (i = 0; i < COUNT(item_objects); i++) {
        struct ItemObj* child = &item_objects[i];
        u32 spawn = capsule_eligibility[mode].keep && !(pools & 1) && i == 0;
        assert(child->active == (spawn || (pools & 1)));
        if (spawn) {
            assert(child->id == 26 && child->unk2 == 6 && child->bg_offset == 0);
            assert(child->unk7C.object == (void*)&obj);
        } else {
            assert(child->id == 0);
        }
    }
    for (i = 0; i < COUNT(visual_objects); i++) {
        struct VisualObj* visual = &visual_objects[i];
        u32 spawn = capsule_eligibility[mode].keep && !(pools & 2) && i == 0;
        assert(visual->active == (spawn ? 0x41 : (pools & 2) != 0));
        if (spawn) {
            assert(visual->id == 35 && visual->unk2 == visual_kinds[obj.unk2]);
            assert(visual->unk50 == PLAYER_OBJECT(&obj) && visual->bg_offset == 0);
        } else {
            assert(visual->id == 0);
        }
    }
    return 1;
}

void light_capsule_main(struct ItemObj*);
void func_80029A48(void);
extern struct Item26AnimationStep* light_capsule_animations[14];
extern const u32* D_800F2FD4[2];
extern union MainPaletteData D_800F1660;
extern s32 D_80139538, D_80139540, D_80139544;
extern s16 D_80139560;
static u32 gfx[64], frames[64], menu[64], resources[64], map_words[192], attributes[2], messages_words[228], window_before[4];
#define map ((u8*)map_words)
#define messages ((u16*)messages_words)
static u16 tiles[512], tiles_before[512], palette[0x202], palette_expected[0x202];
static Palette bank[3];
static struct ItemObj capsule, capsule_expected, items[32];
static struct StageObjectRecord record;
static struct VisualObj visuals[32];
static struct MiscObj misc[64];
static struct PlayerObj player, entity;
static struct RideArmorObj ride;
static struct EngineObj engine;
static struct MainBssState main_before;
static struct BackgroundObj backgrounds[3];
static struct AbcObj dialogue;
static struct ControllerInput input;
static struct MiscObj* parts[7];
static struct Func80022730Config* portrait;
static u16 dialogue_palette[32];
static u32 audio_expected[15], resource, secret_mode, portrait_id, dialogue_clock, saved_boss, saved_hud;
static u16 rng;
static u8 dirty;
static const u32 secret_text_words[200] = {
    0x005B004D, 0x01FF0086, 0x00520055, 0x00510050, 0x1086505D, 0x10861086, 0x10851061, 0x107C11FF,
    0x10781072, 0x1079108B, 0x11FF1068, 0x106C1069, 0x10641071, 0x106F106F, 0x1064507C, 0x10751075,
    0x1079106C, 0x10671068, 0x10861086, 0x004D2086, 0x0086005B, 0x005501FF, 0x00500052, 0x505D0051,
    0x106B105D, 0x1076106C, 0x106611FF, 0x10731064, 0x10781076, 0x5068106F, 0x10721066, 0x10771071,
    0x106C1064, 0x10761071, 0x107711FF, 0x1068106B, 0x107611FF, 0x10641068, 0x1068106F, 0x004D2067,
    0x0086005B, 0x005501FF, 0x00500052, 0x505D0051, 0x10681076, 0x10751066, 0x10771068, 0x107311FF,
    0x10751064, 0x10761077, 0x106911FF, 0x50751072, 0x106B1077, 0x11FF1068, 0x106F105E, 0x106C1077,
    0x10641070, 0x10681077, 0x104A11FF, 0x10701075, 0x10751072, 0x004D2086, 0x0086005B, 0x005501FF,
    0x00500052, 0x505D0051, 0x106B1060, 0x10711068, 0x107C11FF, 0x10781072, 0x106811FF, 0x1068107B,
    0x10781066, 0x50681077, 0x106B1077, 0x11FF1068, 0x10721057, 0x10641079, 0x105C11FF, 0x10751077,
    0x106E106C, 0x10851068, 0x107711FF, 0x2068106B, 0x005B004D, 0x01FF0086, 0x00520055, 0x00510050,
    0x107A505D, 0x1071106C, 0x1076106A, 0x107A11FF, 0x106F106C, 0x11FF106F, 0x10731072, 0x10711068,
    0x106411FF, 0x50671071, 0x1072107C, 0x11FF1078, 0x10641066, 0x11FF1071, 0x107B1068, 0x10661068,
    0x10771078, 0x11FF1068, 0x106B1077, 0x004D2068, 0x0086005B, 0x005501FF, 0x00500052, 0x505D0051,
    0x1071106C, 0x106C1079, 0x10661071, 0x1065106C, 0x1068106F, 0x106511FF, 0x10671072, 0x1066507C,
    0x10641075, 0x106B1076, 0x106411FF, 0x10771077, 0x10661064, 0x2086106E, 0x005B004D, 0x01FF0086,
    0x00520055, 0x00510050, 0x1086505D, 0x10861086, 0x10721051, 0x1068107A, 0x10681079, 0x10851075,
    0x107711FF, 0x106C106B, 0x10645076, 0x10701075, 0x10751072, 0x106C11FF, 0x11FF1076, 0x10721071,
    0x004D2077, 0x0086005B, 0x005501FF, 0x00500052, 0x505D0051, 0x10721066, 0x10731070, 0x1068106F,
    0x10681077, 0x11FF1067, 0x1068107C, 0x11FF1077, 0x10711064, 0x107C5067, 0x10781072, 0x11FF1075,
    0x10641076, 0x10681069, 0x107C1077, 0x106C11FF, 0x11FF1076, 0x10721071, 0x004D2077, 0x0086005B,
    0x005501FF, 0x00500052, 0x505D0051, 0x10761064, 0x10781076, 0x10681075, 0x10861067, 0x105211FF,
    0x11FF1069, 0x106B1077, 0x5076106C, 0x1076106C, 0x106411FF, 0x10661066, 0x10731068, 0x10641077,
    0x106F1065, 0x11FF1068, 0x20721077, 0x005B004D, 0x01FF0086, 0x00520055, 0x00510050, 0x107C505D,
    0x10781072, 0x11FF1085, 0x10711068, 0x10681077, 0x11FF1075, 0x10721071, 0x1086107A, 0xA0861086
};
static void audio_state(u32* v)
{
    v[0] = D_80139538;
    v[1] = D_80139540;
    v[2] = D_80139544;
    v[3] = D_80139560;
    v[4] = D_80139568;
    v[5] = D_80139530;
    v[6] = D_80141BD4;
    v[7] = D_80137CC0;
    v[8] = D_80173C84;
    v[9] = D_80175EE8[0];
    v[10] = D_80139514;
    v[11] = D_80139524;
    v[12] = D_80139528;
    memcpy(&v[13], &D_80139520, 4);
    v[14] = D_8013955C;
}
static void code_input(u16 held)
{
    controller_input.previous = controller_input.held;
    controller_input.held = held;
    controller_input.pressed = held & ~controller_input.previous;
    func_80029A48();
}
static void prepare(u32 secret, u32 right)
{
    u32 i;
    secret_mode = secret;
    memset(&misc[0], 0, sizeof(misc[0]));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&g_Entity, 0, sizeof(g_Entity));
    memset(&qux_object, 0, sizeof(qux_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&abc_object, 0, sizeof(abc_object));
    c_test_zero_words((u32*)item_objects, sizeof(item_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    memset(gfx, 0, sizeof(gfx));
    memset(frames, 0, sizeof(frames));
    gfx[0] = frames[0] = 64;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    memset(menu, 0, sizeof(menu));
    memset(resources, 0, sizeof(resources));
    memset(map_words, 1, sizeof(map_words));
    for (i = 0; i < COUNT(tiles); i++)
        tiles[i] = i >= 256 && (i & 255) / 16 >= 9;
    c_test_copy_words((u32*)tiles_before, (u32*)tiles, sizeof(tiles) / 4);
    attributes[0] = 0;
    attributes[1] = 0x38;
    SP_BG_TILEMAP = map;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    memset(bank, 0, sizeof(bank));
    memset(palette, 0, sizeof(palette));
    palette[0] = palette[0x201] = 0xBEEF;
    TEST_PALETTE = (u8*)&palette[1];
    TEST_PALETTE_BANK = (u8*)bank;
    engine_obj.cur_character = 0;
    engine_obj.stage = 7;
    engine_obj.substage = 1;
    engine_obj.max_hp = 32;
    engine_obj.state = 6;
    if (secret) {
        for (i = 0; i < 8; i++) {
            code_input(0);
            code_input(D_800F44C4[i]);
        }
        code_input(0);
        code_input(D_800F44C4[8]);
        code_input(D_800F44C4[8] | PADstart);
        assert(engine_obj.unk37 == 1);
    }
    memset(&controller_input, 0, sizeof(controller_input));
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.voice_timer = 1;
    g_Player.animation_table = (u32**)D_80119DF0;
    g_Player.unk38 = (u8*)gfx + 64;
    g_Player.x_pos.i.hi = right ? 1544 : 1448;
    g_Player.y_pos.i.hi = 635;
    player_enter_idle(&g_Player);
    player_update_frame_hitbox(&g_Player);
    player_set_collision_bounds(&g_Player);
    CollisionRelated(&g_Player);
    assert(g_Player.unk70 == PLAYER_COLLIDE_GROUND);
    background_objects[0].x_pos.i.hi = 1392;
    background_objects[0].y_pos.i.hi = 500;
    resource = (u8)func_8002938C(0xA2);
    assert(resource < 64);
    menu[resource] = 128;
    TEST_MENU_FRAMES = (u8*)menu;
    D_801406A8 = resources;
    cur_random = 0x1234;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    D_80141BD4 = 0;
    D_80171EA9 = 0;
    memset(&record, 0, sizeof(record));
    record.id = 26;
    record.subtype = 3;
    record.flags = 1;
    record.object_type = 4;
    record.x = 1512;
    record.y = 632;
    memset(&capsule, 0, sizeof(capsule));
    capsule.active = 0x41;
    capsule.id = 26;
    capsule.unk2 = 3;
    capsule.x_pos.i.hi = 1512;
    capsule.y_pos.i.hi = 632;
    capsule.backref = &record;
    light_capsule_update(&capsule);
    assert(capsule.state == 1 && capsule.unk5 == 0 && capsule.y_pos.i.hi == 644 && capsule.unk70 == PLAYER_COLLIDE_GROUND && visual_objects[0].id == 35 && visual_objects[0].unk50 == PLAYER_OBJECT(&capsule) && item_objects[0].unk7C.object == &capsule);
}
static void capture(void)
{
    capsule_expected = capsule;
    player = g_Player;
    entity = g_Entity;
    ride = qux_object;
    engine = engine_obj;
    main_before = main_bss_state;
    dialogue = abc_object;
    c_test_copy_words((u32*)&items[0], (u32*)&item_objects[0], sizeof(items[0]) / 4);
    c_test_copy_words((u32*)&visuals[0], (u32*)&visual_objects[0], sizeof(visuals[0]) / 4);
    c_test_copy_words((u32*)backgrounds, (u32*)background_objects, sizeof(backgrounds) / 4);
    c_test_copy_words((u32*)palette_expected, (u32*)palette, sizeof(palette) / 4);
    c_test_copy_words((u32*)dialogue_palette, (u32*)D_801397E4, sizeof(dialogue_palette) / 4);
    parts[0] = D_801397BC;
    parts[1] = D_801397C0;
    parts[2] = D_801397C4;
    parts[3] = D_801397C8;
    parts[4] = D_801397CC;
    parts[5] = D_801397D0;
    parts[6] = D_801397D4;
    portrait = D_801397DC;
    portrait_id = D_801397D8;
    dialogue_clock = D_801397E0;
    saved_boss = D_80139828;
    saved_hud = D_80139824;
    input = controller_input;
    dirty = need_palette_load;
    rng = cur_random;
    audio_state(audio_expected);
}
static void check(void)
{
    u32 i, audio[15];
    assert(record.flags == (capsule_expected.active ? 1 : 0) && record.id == 26 && record.subtype == 3 && record.object_type == 4 && record.x == 1512 && record.y == 632);
    assert(c_test_word_difference((u32*)&capsule, (u32*)&capsule_expected, sizeof(capsule) / 4) == 0 && c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0 && c_test_word_difference((u32*)&qux_object, (u32*)&ride, sizeof(ride) / 4) == 0 && c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0);
    assert(c_test_word_difference((u32*)item_objects, (u32*)items, sizeof(items) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0 && c_test_word_difference((u32*)misc_objects, (u32*)misc, sizeof(misc) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)backgrounds, sizeof(backgrounds) / 4) == 0);
    assert(c_test_word_difference((u32*)&abc_object, (u32*)&dialogue, sizeof(dialogue) / 4) == 0 && c_test_word_difference((u32*)D_801397E4, (u32*)dialogue_palette, sizeof(dialogue_palette) / 4) == 0);
    assert(D_801397BC == parts[0] && D_801397C0 == parts[1] && D_801397C4 == parts[2] && D_801397C8 == parts[3] && D_801397CC == parts[4] && D_801397D0 == parts[5] && D_801397D4 == parts[6] && D_801397DC == portrait && D_801397D8 == portrait_id && D_801397E0 == (s16)dialogue_clock && D_80139828 == saved_boss && D_80139824 == saved_hud);
    audio_state(audio);
    assert(c_test_word_difference(audio, audio_expected, sizeof(audio) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && need_palette_load == dirty && cur_random == rng);
    assert(c_test_word_difference((u32*)palette, (u32*)palette_expected, sizeof(palette) / 4) == 0);
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames && TEST_MENU_FRAMES == (u8*)menu && D_801406A8 == resources && TEST_PALETTE == (u8*)&palette[1] && TEST_PALETTE_BANK == (u8*)bank && TEST_BG_TILE_PIXELS == (u8*)tiles && TEST_BG_TILE_ATTRS == (u8*)attributes && SP_BG_TILEMAP == map && layout_width == 16 && layout_height == 16 && layout_size == 256 && attributes[0] == 0 && attributes[1] == 0x38);
    for (i = 0; i < COUNT(map_words); i += 8)
        assert(((map_words[i] ^ 0x01010101) | (map_words[i + 1] ^ 0x01010101) | (map_words[i + 2] ^ 0x01010101) | (map_words[i + 3] ^ 0x01010101) | (map_words[i + 4] ^ 0x01010101) | (map_words[i + 5] ^ 0x01010101) | (map_words[i + 6] ^ 0x01010101) | (map_words[i + 7] ^ 0x01010101)) == 0);
    assert(c_test_word_difference((u32*)tiles, (u32*)tiles_before, sizeof(tiles) / 4) == 0);
    for (i = 0; i < 64; i++)
        assert(gfx[i] == (i == 0 ? 64u : 0) && frames[i] == (i == 0 ? 64u : 0) && menu[i] == (i == resource ? 128u : 0) && resources[i] == 0);
    for (i = 0; i < 48; i++)
        assert(((u16*)bank)[i] == 0);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
}
static void approach(void)
{
    light_capsule_main(&capsule);
    assert(capsule.unk5 == 1 && capsule.unk17 == 10 && g_Player.script_action == PLAYER_SCRIPT_WAIT && g_Player.script_state == 1 && engine_obj.gameplay_locked == 1);
}
static u32 right_approach(u32 row)
{
    (void)row;
    prepare(0, 1);
    capture();
    capsule_expected.unk5 = 1;
    capsule_expected.unk15 = 0x40;
    capsule_expected.unk17 = 10;
    capsule_expected.previous_animation_index = 255;
    capsule_expected.animation_cursor = (const u8*)light_capsule_animations[10];
    capsule_expected.animation_step.packed = 0x01010002;
    player.script_state = 1;
    player.script_action = PLAYER_SCRIPT_WAIT;
    player.script_facing = 0;
    player.spike_immune = 1;
    engine.gameplay_locked = 1;
    audio_expected[0] = 24107520;
    audio_expected[1] = 216253;
    audio_expected[2] = 225405;
    audio_expected[3] = XA_ARCHIVE_BGM4;
    audio_expected[4] = 0;
    audio_expected[5] = 7;
    audio_expected[6] = 2;
    audio_expected[7] = 23330817;
    audio_expected[8] = 1;
    audio_expected[9] = (audio_expected[9] & 0xFFFF0000) | 0x301;
    audio_expected[10] = (audio_expected[10] & 0xFF000000) | 0x280548;
    audio_expected[11] = audio_expected[12] = 0x7F;
    audio_expected[13] = 0x3F3F3F3F;
    approach();
    check();
    assert(record.flags == 1);
    return 1;
}
static u32 secret_dialogue(u32 row)
{
    u32 i;
    struct MiscObj* window;
    (void)row;
    prepare(1, 0);
    approach();
    for (i = 0; i < 67; i++)
        light_capsule_main(&capsule);
    assert(capsule.unk5 == 1 && capsule.animation_cursor == (const u8*)light_capsule_animations[10] + 33 * 4 && capsule.animation_step.packed == 0x00010001 && abc_object.unkC == 0);
    memset(messages_words, 0, sizeof(messages_words));
    messages[0x35] = 112;
    c_test_copy_words(&messages_words[28], secret_text_words, COUNT(secret_text_words));
    TEST_ARC_48 = (u8*)messages_words;
    c_test_copy_words(window_before, (u32*)WINDOW_ARCHIVE_DATA, COUNT(window_before));
    ((u32*)WINDOW_ARCHIVE_DATA)[2] = 128;
    capture();
    capsule_expected.unk5 = 2;
    capsule_expected.animation_cursor = (const u8*)light_capsule_animations[10] + 34 * 4;
    capsule_expected.animation_step.packed = 0x06010002;
    dialogue.unkC = 0x80;
    dialogue.unk0 = &messages[56];
    dialogue.unk4 = 77;
    dialogue.unk6 = -120;
    dialogue.unk8 = 29;
    dialogue.unkA = 39;
    dialogue.unkD = dialogue.unkE = 0;
    dialogue.unkF = 1;
    dialogue.unk10 = 0;
    saved_boss = engine.enable_boss;
    saved_hud = engine.unk1F;
    engine.enable_boss = engine.unk1F = 0;
    portrait_id = 255;
    dialogue_clock = 0;
    memset(parts, 0, sizeof(parts));
    parts[0] = &misc_objects[0];
    memcpy(dialogue_palette, &palette[1 + 0x150], sizeof(dialogue_palette));
    memcpy(&palette_expected[1 + 0x150], &D_800F1660.raw[0xA0], sizeof(dialogue_palette));
    dirty |= 1;
    window = &misc[0];
    window->active = 1;
    window->id = 22;
    window->unk2 = 2;
    window->unk16 = 17;
    window->animation_table = (u32**)D_800F2FD4;
    window->unk40 = 0x1E00;
    window->unk42 = 0x7846;
    window->bg_offset = -1;
    window->x_pos.i.hi = 160;
    window->y_pos.i.hi = 60;
    window->unk3C = WINDOW_ARCHIVE_DATA + 128;
    window->unk15 = 0;
    window->unk17 = 0;
    window->previous_animation_index = 255;
    window->animation_cursor = (u32*)D_800F2FD4[0];
    window->animation_step.packed = 0x28010004;
    light_capsule_main(&capsule);
    check();
    assert(record.flags == 1 && TEST_ARC_48 == (u8*)messages_words && ((u32*)WINDOW_ARCHIVE_DATA)[2] == 128);
    for (i = 0; i < 56; i++)
        assert(messages[i] == (i == 53 ? 112 : 0));
    assert(c_test_word_difference(&messages_words[28], secret_text_words, COUNT(secret_text_words)) == 0);
    for (i = 0; i < 4; i++)
        if (i != 2)
            assert(((u32*)WINDOW_ARCHIVE_DATA)[i] == window_before[i]);
    c_test_copy_words((u32*)WINDOW_ARCHIVE_DATA, window_before, COUNT(window_before));
    return 1;
}
static u32 offscreen_glass(u32 row)
{
    (void)row;
    prepare(0, 0);
    capsule_glass_update(&visual_objects[0]);
    assert(visual_objects[0].state != 0 && capsule.active == 0x41);
    g_Player.x_pos.i.hi = 1216;
    g_Player.unk18 = g_Player.x_pos;
    background_objects[0].x_pos.i.hi = 1056;
    assert(func_8002B1E8(BASE_OBJECT(&capsule), 136, 136) == 1);
    light_capsule_main(&capsule);
    assert(capsule.active == 0 && record.flags == 0);
    capture();
    memset(&visuals[0], 0, 8);
    capsule_glass_update(&visual_objects[0]);
    check();
    assert(record.flags == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "capsule_eligibility", 0, 0, COUNT(capsule_eligibility) + 3, test_capsule_eligibility },
    { "capsule_visual_animation_context", NULL, capsule_visual_animation_context_cases_expected, COUNT(capsule_visual_animation_context_cases_expected), capsule_visual_animation_context_cases_row },
    { "func_800C6EDC", 0, 0, 3, test_func_800C6EDC },
    { "light_capsule_wait_player", 0, 0, 1, test_light_capsule_wait_player },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "Original_capsule_right_approach_script_and_exact_XA_music", NULL, NULL, 1, right_approach },
    { "Actual_X_secret_code_capsule_own_event_starts_original_dialogue35", NULL, NULL, 1, secret_dialogue },
    { "Actual_offscreen_capsule_despawn_clears_its_existing_glass", NULL, NULL, 1, offscreen_glass },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(capsule_eligibility) + 3 + COUNT(capsule_visual_animation_context_cases_expected) + 3 + 1 + COUNT(pool_full_cases) + 1 + 1 + 1;
