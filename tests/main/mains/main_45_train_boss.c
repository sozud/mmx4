#include "test_runtime.h"
#include "main/mains/main_45_train_boss.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

enum { DEFEATED_WAIT,
    DEFEATED_OPEN,
    DEFEATED_CLOSED,
    DEFEATED_SCRIPT_NEAR,
    DEFEATED_SCRIPT_END,
    DEFEATED_NO_SCRIPT,
    LEAVE_TELEPORT,
    LEAVE_STAY,
    LEAVE_DONE,
    LEAVE_DEAD_PLAYER,
    LEAVE_DONE_FAR,
    PARTS_FULL,
    PARTS_SPAWN };
#define LAYER_SLOT 2
#define ITEM_SLOT 9
#define MAIN_SLOT 10
static u8 train_boss_exit_tilemap[8];
static u32 sprite_steps[1];
static u32* table[2];
static struct MainObj boss, expected;
static struct MainObj want_mains[0x30];
static struct ItemObj want_items[0x20];
static struct LayerObj want_layers[4];
static struct PlayerObj want_player;
static struct EngineObj want_engine;

static void same(const void* a, const void* b, u32 size)
{
    u32 i, difference = 0;
    for (i = 0; i < size / 4; i++)
        difference |= ((const u32*)a)[i] ^ ((const u32*)b)[i];
    for (i = size & ~3u; i < size; i++)
        difference |= ((const u8*)a)[i] ^ ((const u8*)b)[i];
    assert(difference == 0);
}

static void zero(void* target, u32 size)
{
    u32 i;
    for (i = 0; i < size / 4; i++)
        ((u32*)target)[i] = 0;
}

static void script(void)
{
    want_player.script_state = 1;
    want_player.script_action = 0x14;
    want_player.script_facing = 0x40;
    want_player.spike_immune = 1;
    want_engine.gameplay_locked = 1;
}

static u32 train_boss_exit_run(u32 mode)
{
    u32 i, full = mode == PARTS_FULL, pools = mode >= PARTS_FULL;
    if (pools) {
        zero(main_objects, sizeof(main_objects));
        zero(item_objects, sizeof(item_objects));
        zero(layer_objects, sizeof(layer_objects));
        zero(want_mains, sizeof(want_mains));
        zero(want_items, sizeof(want_items));
        zero(want_layers, sizeof(want_layers));
        for (i = 0; i < 0x30; i++)
            main_objects[i].active = want_mains[i].active = full || i < MAIN_SLOT || i >= MAIN_SLOT + 4;
        for (i = 0; i < 0x20; i++)
            item_objects[i].active = want_items[i].active = full || i != ITEM_SLOT;
        for (i = 0; i < 4; i++)
            layer_objects[i].active = want_layers[i].active = full || i != LAYER_SLOT;
    }
    memset(train_boss_exit_tilemap, 0, sizeof(train_boss_exit_tilemap));
    train_boss_exit_tilemap[4] = mode == DEFEATED_OPEN ? 0x1C : 0x10;
    train_boss_exit_tilemap[5] = mode == LEAVE_TELEPORT ? 0x23 : 0x10;
    SP_BG_TILEMAP = train_boss_exit_tilemap;
    layout_size = 4;
    layout_width = 2;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    background_objects[1].x_pos.val = 0x01000000;
    background_objects[1].y_pos.val = 0;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.hp = mode == LEAVE_DEAD_PLAYER ? (s8)0x80 : 0x10;
    g_Player.x_pos.i.hi = mode == DEFEATED_SCRIPT_NEAR ? 0x250 : mode == DEFEATED_SCRIPT_END || mode == LEAVE_DONE_FAR ? 0x1B40
                                                                                                                       : 0x300;
    g_Player.y_pos.i.hi = 0x90;
    engine_obj.unkF = 0;
    engine_obj.gameplay_locked = 0;
    table[0] = &sprite_steps[0];
    memset(&boss, 0, sizeof(boss));
    boss.active = 0x41;
    boss.id = 0x2D;
    boss.state = 2;
    boss.unk5 = 1;
    boss.unk6 = mode == DEFEATED_SCRIPT_NEAR || mode == DEFEATED_SCRIPT_END || mode == DEFEATED_NO_SCRIPT ? 0 : 1;
    boss.unk7 = 1;
    boss.hp = 3;
    boss.unk40 = 0x0234;
    boss.unk42 = 0x0567;
    boss.x_pos.val = 0x02001111;
    boss.y_pos.val = 0x00802222;
    boss.unk7C = mode == DEFEATED_OPEN || mode == DEFEATED_CLOSED || mode == LEAVE_DONE || mode == LEAVE_DEAD_PLAYER || mode == LEAVE_DONE_FAR ? 1 : 5;
    boss.unk7E = 10;
    boss.animation_table = table;
    boss.sprite_frames = (const u8*)&sprite_steps[0];
    want_player = g_Player;
    want_engine = engine_obj;
    expected = boss;

    if (mode <= DEFEATED_NO_SCRIPT) {
        train_boss_defeated(&boss);
        expected.unk7E = 9;
        expected.unk7C--;
        if (mode == DEFEATED_OPEN) {
            expected.state = 3;
            expected.unk5 = 0;
        }
        if (mode == DEFEATED_CLOSED)
            expected.unk7C = 1;
        if (mode == DEFEATED_SCRIPT_NEAR || mode == DEFEATED_SCRIPT_END) {
            script();
            expected.unk6 = 1;
        }
        expected.on_screen = 1;
    } else if (mode <= LEAVE_DONE_FAR) {
        func_800661AC(&boss);
        if (mode == LEAVE_TELEPORT) {
            want_player.x_pos.u.hi = 0x12C;
            want_player.y_pos.u.hi = 0x64;
            want_player.unk18 = want_player.x_pos;
            want_player.unk1C = want_player.y_pos;
        }
        expected.unk7E = 9;
        expected.unk7C--;
        if (expected.unk7C == 0) {
            if (mode != LEAVE_DEAD_PLAYER)
                want_engine.unkF = 0x40;
            memset(&expected, 0, 8);
        }
        if (mode == LEAVE_DONE_FAR) {
            script();
            expected.unk6 = 1;
        }
        expected.on_screen = 1;
    } else {
        func_800665BC(&boss);
        expected.x_speed = 0x10000;
        expected.unk6 = 1;
        if (mode == PARTS_SPAWN) {
            struct LayerObj* layer = &want_layers[LAYER_SLOT];
            struct ItemObj* floor = &want_items[ITEM_SLOT];
            struct Main45LayerSignals* signals = (struct Main45LayerSignals*)&layer->unk16;

            layer->active = 1;
            layer->id = 3;
            layer->unk2 = 1;
            layer->bg_offset = 0;
            layer->unk16 = layer->unk17 = 0;
            signals->projectile_state[0] = signals->projectile_state[1] = signals->projectile_state[2] = 0;
            layer->state = 0;
            expected.ext.main_45.layer_bg_offset = (u8*)&layer_objects[LAYER_SLOT].bg_offset;
            expected.ext.main_45.layer_parameter = &layer_objects[LAYER_SLOT].unk15;
            expected.ext.main_45.layer_signals = (struct Main45LayerSignals*)&layer_objects[LAYER_SLOT].unk16;
            floor->active = 0x41;
            floor->id = 0x10;
            floor->unk2 = 0;
            floor->unk40 = boss.unk40;
            floor->unk42 = boss.unk42;
            floor->animation_table = boss.animation_table;
            floor->sprite_frames = boss.sprite_frames;
            floor->animation_step.fields.frame_index = 7;
            floor->bg_offset = boss.bg_offset;
            floor->x_pos = boss.x_pos;
            floor->y_pos = boss.y_pos;
            floor->unk7C.train_boss = &boss.ext.main_45;
            floor->ext.train_layer_parameter = &layer_objects[LAYER_SLOT].unk15;
            floor->unk15 = 0;
            floor->state = 0;
            for (i = 0; i < 4; i++) {
                struct MainObj* part = &want_mains[MAIN_SLOT + i];
                part->active = 0x45;
                part->id = i == 0 ? 0x2E : 0x2F;
                part->unk2 = i == 0 ? 0 : i - 1;
                part->unk40 = boss.unk40;
                part->unk42 = boss.unk42;
                part->animation_table = boss.animation_table;
                part->sprite_frames = boss.sprite_frames;
                part->animation_step.fields.frame_index = i == 0 ? 0x11 : 0x13 + i - 1;
                part->bg_offset = boss.bg_offset;
                part->x_pos = boss.x_pos;
                part->y_pos = boss.y_pos;
                if (i == 0) {
                    part->ext.main_46.owner = &boss.ext.main_45;
                } else {
                    ((void**)&part->ext)[0] = &boss.ext.main_45;
                    ((void**)&part->ext)[1] = &boss.hp;
                }
                part->unk15 = 0;
                part->state = 0;
            }
        }
    }
    same(&boss, &expected, sizeof(boss));
    if (pools) {
        same(main_objects, want_mains, sizeof(want_mains));
        same(item_objects, want_items, sizeof(want_items));
        same(layer_objects, want_layers, sizeof(want_layers));
    }
    same(&g_Player, &want_player, sizeof(want_player));
    same(&engine_obj, &want_engine, sizeof(want_engine));
    assert(train_boss_exit_tilemap[4] == (mode == DEFEATED_OPEN ? 0x1C : 0x10) && train_boss_exit_tilemap[5] == (mode == LEAVE_TELEPORT ? 0x23 : 0x10));
    i = (u8)boss.state | ((u32)(u8)boss.unk6 << 8) | ((u32)(u16)boss.unk7C << 16) | ((u32)(u8)boss.on_screen << 30) ^ ((u32)(u8)g_Player.script_state << 24) ^ ((u32)(u8)engine_obj.unkF << 12) ^ ((u32)(u16)g_Player.x_pos.i.hi << 4);
    return i;
}

static const u32 train_boss_exit_cases_expected[] = { 0x40043102u, 0x40003103u, 0x40013102u, 0x41042502u, 0x4105B502u, 0x40043002u, 0x400413C2u, 0x40043102u, 0x40043000u, 0x40003000u, 0x4105B500u, 0x53102u, 0x53102u };

static u8 train_exit_layout_tilemap[64];
static u32 exit_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj bg_before[3];
    u8 map_before[64], selectors[6] = { 0x29, 0x2A, 0x20, 0x21, 0x22, 0x23 };
    u32 i, actual, phase = mode / 2;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x45;
    obj.id = 45;
    obj.state = 3;
    obj.unk5 = mode & 1 ? 6 : phase;
    obj.unk6 = 0;
    obj.unk7 = 0x35;
    obj.unk7C = 0x2468;
    obj.unk7E = 2;
    obj.bg_offset = 0;
    obj.x_pos.val = 0x500 * 65536 + 0x1357;
    obj.y_pos.val = 0x200 * 65536 + 0x2468;
    g_Player.active = 0x41;
    g_Player.hp = 20;
    g_Player.state = 1;
    g_Player.x_pos.val = (mode == 1 ? 0x1B36 : mode == 3 || !(mode & 1) ? 0x500 + 200
                                                                        : 0x500 + 80)
            * 65536
        + 0x1234;
    g_Player.y_pos.val = 0x200 * 65536 + 0x2345;
    g_Player.unk18.val = 0x24681357;
    g_Player.unk1C.val = 0x13572468;
    background_objects[0].x_pos.i.hi = 0x400;
    background_objects[0].y_pos.i.hi = 0x180;
    background_objects[1].x_pos.i.hi = 0x200;
    engine_obj.gameplay_locked = 0x27;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(bg_before, background_objects, sizeof(bg_before));
    SP_BG_TILEMAP = train_exit_layout_tilemap;
    layout_width = 16;
    layout_size = 16;
    memset(train_exit_layout_tilemap, 0xA5, sizeof(train_exit_layout_tilemap));
    train_exit_layout_tilemap[17] = selectors[phase];
    train_exit_layout_tilemap[18] = mode == 0 ? 0x23 : 0x22;
    memcpy(map_before, train_exit_layout_tilemap, sizeof(map_before));
    func_80065EA4(&obj);
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.state = obj.state;
    before.unk7C = obj.unk7C;
    before.unk7E = obj.unk7E;
    before.on_screen = obj.on_screen;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    player_before.x_pos = g_Player.x_pos;
    player_before.y_pos = g_Player.y_pos;
    player_before.unk18 = g_Player.unk18;
    player_before.unk1C = g_Player.unk1C;
    player_before.script_state = g_Player.script_state;
    player_before.script_action = g_Player.script_action;
    player_before.script_facing = g_Player.script_facing;
    player_before.spike_immune = g_Player.spike_immune;
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    engine_before.gameplay_locked = engine_obj.gameplay_locked;
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    for (i = 0; i < sizeof(train_exit_layout_tilemap); i++)
        if (i < 18 || i > 23)
            assert(train_exit_layout_tilemap[i] == map_before[i]);
    switch (observation) {
    case 0:
        actual = ((u32*)&obj)[1];
        break;
    case 1:
        actual = (u16)obj.unk7C | ((u32)(u16)obj.unk7E << 16);
        break;
    case 2:
        actual = g_Player.x_pos.val;
        break;
    case 3:
        actual = g_Player.y_pos.val;
        break;
    case 4:
        actual = g_Player.unk18.val;
        break;
    case 5:
        actual = g_Player.unk1C.val;
        break;
    case 6:
        actual = g_Player.script_state | ((u32)(u8)g_Player.script_action << 8) | ((u32)(u8)g_Player.script_facing << 16) | ((u32)g_Player.spike_immune << 24);
        break;
    case 7:
        actual = engine_obj.gameplay_locked | ((u32)obj.on_screen << 8);
        break;
    case 8:
        actual = train_exit_layout_tilemap[18] | ((u32)train_exit_layout_tilemap[19] << 8) | ((u32)train_exit_layout_tilemap[20] << 16) | ((u32)train_exit_layout_tilemap[21] << 24);
        break;
    default:
        actual = train_exit_layout_tilemap[22] | ((u32)train_exit_layout_tilemap[23] << 8);
        break;
    }
    return actual;
}
static const u32 train_exit_layout_cases_expected[] = { 0x35010103u, 0x12468u, 0x52C1234u, 0x1E42345u, 0x52C1234u, 0x1E42345u, 0x1401401u, 0x101u, 0xA5A5A520u, 0xA5A5u, 0x35010603u, 0x12468u, 0x1B361234u, 0x2002345u, 0x24681357u, 0x13572468u, 0x1401401u, 0x101u, 0xA5A5A522u, 0xA5A5u, 0x35000203u, 0x12468u, 0x5C81234u, 0x2002345u, 0x24681357u, 0x13572468u, 0x0u, 0x127u, 0xA5A52122u, 0xA5A5u, 0x35000603u, 0x12468u, 0x5C81234u, 0x2002345u, 0x24681357u, 0x13572468u, 0x0u, 0x127u, 0xA5A5A522u, 0xA5A5u, 0x35000303u, 0x12468u, 0x5C81234u, 0x2002345u, 0x24681357u, 0x13572468u, 0x0u, 0x127u, 0xA522A522u, 0xA5A5u, 0x35010603u, 0x12468u, 0x5501234u, 0x2002345u, 0x24681357u, 0x13572468u, 0x1401401u, 0x101u, 0xA5A5A522u, 0xA5A5u, 0x35000403u, 0x12468u, 0x5C81234u, 0x2002345u, 0x24681357u, 0x13572468u, 0x0u, 0x127u, 0x23A5A522u, 0xA5A5u, 0x35010603u, 0x12468u, 0x5501234u, 0x2002345u, 0x24681357u, 0x13572468u, 0x1401401u, 0x101u, 0xA5A5A522u, 0xA5A5u, 0x35000503u, 0x12468u, 0x5C81234u, 0x2002345u, 0x24681357u, 0x13572468u, 0x0u, 0x127u, 0xA5A5A522u, 0xA524u, 0x35010603u, 0x12468u, 0x5501234u, 0x2002345u, 0x24681357u, 0x13572468u, 0x1401401u, 0x101u, 0xA5A5A522u, 0xA5A5u, 0x35000504u, 0x1000Cu, 0x5C81234u, 0x2002345u, 0x24681357u, 0x13572468u, 0x0u, 0x127u, 0xA51D1D1Du, 0x1DA5u, 0x35010603u, 0x12468u, 0x5501234u, 0x2002345u, 0x24681357u, 0x13572468u, 0x1401401u, 0x101u, 0xA5A5A522u, 0xA5A5u };
static u32 train_exit_layout_cases_row(u32 row)
{
    return exit_case(row / 10, row % 10);
}

static u32 layer_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    u8 bg = 7, parameter = 0xA5;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 45;
    obj.state = 1;
    obj.ext.main_45.unk81 = 0xFF;
    obj.ext.main_45.unk82 = mode == 4;
    obj.ext.main_45.unk83 = mode == 5 ? 1 : 3;
    obj.ext.main_45.unk84 = mode == 3 || mode == 4 ? 1 : 20;
    obj.ext.main_45.layer_bg_offset = &bg;
    obj.ext.main_45.layer_parameter = &parameter;
    obj.unk76 = mode == 2;
    g_Player.wall_climbable = mode == 1;
    expected = obj;
    player_before = g_Player;
    expected.ext.main_45.unk84--;
    if (mode == 3 || mode == 4) {
        expected.ext.main_45.unk81 = mode == 3 ? 1 : 0xFF;
        expected.ext.main_45.unk82 = mode == 3;
        expected.ext.main_45.unk83 = 31;
        expected.ext.main_45.unk84 = mode == 3 ? 240 : 300;
    } else {
        expected.ext.main_45.unk83 = mode == 5 ? 0 : 2;
        if (mode == 5)
            expected.ext.main_45.unk81 = 0;
    }
    func_80066478(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(bg == (mode == 5 ? 0 : mode < 3 ? 0xFF
                                           : 7));
    assert(parameter == (mode == 1 || mode == 2 ? 1 : 0xA5));
    return (u16)obj.ext.main_45.unk84 | ((u32)bg << 16) | ((u32)parameter << 24);
}
static const u32 train_projectile_layer_signals_cases_expected[] = { 0xA5FF0013u, 0x1FF0013u, 0x1FF0013u, 0xA50700F0u, 0xA507012Cu, 0xA5000013u };

struct func_8006630C_case {
    u32 attack_flags, projectile_command, unk89, v_0_state, v_2_state, unk28;
    u32 expected[3];
};
static const struct func_8006630C_case func_8006630C_cases[] = {
    { 7, 0, 0, 0, 0, 0, { 0u, 0u, 0u } },
    { 112, 4, 0, 0, 0, 0, { 0xFFu, 0u, 0u } },
    { 0, 4, 0, 0, 0, 0, { 4u, 0u, 0u } },
    { 0, 5, 0, 0, 3, 65280, { 5u, 0u, 0u } },
    { 0, 5, 0, 3, 0, 0, { 0xFFu, 0u, 0u } },
    { 126, 255, 16, 0, 0, 0, { 0u, 4u, 0xEu } },
};
static u32 test_func_8006630C(u32 row)
{
    const struct func_8006630C_case* c = &func_8006630C_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    obj.ext.main_45.attack_flags = c->attack_flags;
    obj.ext.main_45.projectile_command = c->projectile_command;
    obj.ext.main_45.unk86 = 0;
    obj.ext.main_45.unk89 = c->unk89;
    shot_objects[0].state = c->v_0_state;
    shot_objects[2].state = c->v_2_state;
    shot_objects[0].unk28 = 0;
    shot_objects[2].unk28 = c->unk28;
    func_8006630C(&obj);
    observed_values[0] = (u32)obj.ext.main_45.projectile_command;
    observed_values[1] = (u32)obj.ext.main_45.unk86;
    observed_values[2] = (u32)obj.ext.main_45.unk89;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

#include "support/state_cases.h"

static u8 train_layer;
#define TB(step, phase) (state_reset(step, phase, 0), so.state = 1, so.x_pos.i.hi = 0x1900, so.y_pos.i.hi = 0x80, so.ext.main_45.unk84 = 5, so.ext.main_45.projectile_command = 0x80, so.ext.main_45.layer_bg_offset = &train_layer)
#define PARTS() (state_extra = so.ext.main_45.projectile_command | so.ext.main_45.unk86 << 8 | so.ext.main_45.unk89 << 16 | (u32)so.ext.main_45.attack_flags << 24)
static void tr_init(void)
{
    TB(0, 0);
    so.state = 0;
    train_boss_update(&so);
    PARTS();
}
static void tr_approach(void)
{
    TB(0, 1);
    so.x_speed = 0x10000;
    train_boss_update(&so);
}
static void tr_approach_arrive(void)
{
    TB(0, 1);
    so.x_pos.i.hi = 0x19B0;
    train_boss_update(&so);
}
static void tr_stop(void)
{
    TB(0, 2);
    so.x_pos.i.hi = 0x1AB0;
    train_boss_update(&so);
}
static void tr_stop_roll(void)
{
    TB(0, 2);
    so.x_speed = 0x10000;
    train_boss_update(&so);
}
static void tr_fill(void)
{
    TB(0, 3);
    so.unk7E = 1;
    so.hp = 5;
    train_boss_update(&so);
}
static void tr_fill_count(void)
{
    TB(0, 3);
    so.unk7E = 2;
    so.hp = 5;
    train_boss_update(&so);
}
static void tr_fill_done(void)
{
    TB(0, 3);
    so.hp = 0x30;
    train_boss_update(&so);
    PARTS();
}
static void tr_fight(void)
{
    TB(1, 0);
    train_boss_update(&so);
}
static void tr_defeated(void)
{
    TB(1, 0);
    so.ext.main_45.attack_flags = 7;
    g_Player.unk5 = 0;
    train_boss_update(&so);
    state_extra = train_layer | so.unk6 << 8;
}
static void tr_defeated_mounted(void)
{
    TB(1, 0);
    so.ext.main_45.attack_flags = 7;
    g_Player.unk5 = 2;
    train_layer = 3;
    train_boss_update(&so);
    state_extra = train_layer | so.unk6 << 8;
}
static void tr_smoke_front(void)
{
    TB(1, 0);
    so.unk7E = 4;
    func_80066970(&so);
}
static void tr_smoke_back(void)
{
    TB(1, 0);
    so.unk7E = 1;
    func_80066970(&so);
}
static void tr_smoke_wait(void)
{
    TB(1, 0);
    so.unk7E = 2;
    func_80066970(&so);
}
static void tr_command_broken(void)
{
    TB(1, 0);
    so.ext.main_45.attack_flags = 7;
    so.ext.main_45.projectile_command = 1;
    func_8006630C(&so);
    PARTS();
}
static void tr_command_idle(void)
{
    TB(1, 0);
    func_8006630C(&so);
    PARTS();
}
static void tr_command_next(void)
{
    TB(1, 0);
    so.ext.main_45.projectile_command = 0xFF;
    so.ext.main_45.unk86 = 2;
    func_8006630C(&so);
    PARTS();
}
static void tr_command_next_skip(void)
{
    TB(1, 0);
    so.ext.main_45.projectile_command = 0xFF;
    so.ext.main_45.attack_flags = 1;
    func_8006630C(&so);
    PARTS();
}
static void tr_command_shots_done(void)
{
    TB(1, 0);
    so.ext.main_45.projectile_command = 5;
    func_8006630C(&so);
    PARTS();
}
static void tr_command_shots_live(void)
{
    TB(1, 0);
    so.ext.main_45.projectile_command = 5;
    shot_objects[1].state = 4;
    shot_objects[1].unk28 = 1;
    func_8006630C(&so);
    PARTS();
}
static void tr_command_arms_done(void)
{
    TB(1, 0);
    so.ext.main_45.projectile_command = 4;
    so.ext.main_45.attack_flags = 0x70;
    func_8006630C(&so);
    PARTS();
}
static void tr_command_arms(void)
{
    TB(1, 0);
    so.ext.main_45.projectile_command = 4;
    so.ext.main_45.attack_flags = 0x30;
    func_8006630C(&so);
    PARTS();
}
static void tr_command_part_gone(void)
{
    TB(1, 0);
    so.ext.main_45.projectile_command = 1;
    so.ext.main_45.attack_flags = 2;
    func_8006630C(&so);
    PARTS();
}

static void (*const train_boss_states_cases[])(void) = {
    tr_init,
    tr_approach,
    tr_approach_arrive,
    tr_stop,
    tr_stop_roll,
    tr_fill,
    tr_fill_count,
    tr_fill_done,
    tr_fight,
    tr_defeated,
    tr_defeated_mounted,
    tr_smoke_front,
    tr_smoke_back,
    tr_smoke_wait,
    tr_command_broken,
    tr_command_idle,
    tr_command_next,
    tr_command_next_skip,
    tr_command_shots_done,
    tr_command_shots_live,
    tr_command_arms_done,
    tr_command_arms,
    tr_command_part_gone,
};
static const u32 train_boss_states_expected[] = { 1u, 0xFF000004u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x10000u, 0x80u, 0u, 0x10001u, 0u, 0x19010000u, 0x800000u, 0x10000u, 0u, 0u, 0x50000u, 0u, 0u, 0x20001u, 0u, 0x19B00000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x30001u, 0u, 0x1AB00000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x20001u, 0u, 0x19010000u, 0x800000u, 0x10000u, 0u, 0u, 0x50000u, 0u, 0u, 0x30001u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x30001u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0xFFu, 0u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x102u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0u, 0x2100u, 0x10102u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x100u, 0x2100u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0u, 0x2100u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0u, 0x2100u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x7000001u, 0u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x80u, 0u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x10102u, 0u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x1010100u, 0u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0xFFu, 0u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 5u, 0u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x700000FFu, 0u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x30000004u, 0u, 0x101u, 0u, 0x19000000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x20000FFu, 0u };

static u32 test_train_boss_states(u32 row)
{
    return object_run(train_boss_states_cases[row], row, &train_boss_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "train_boss_states", 0, 0, COUNT(train_boss_states_cases), test_train_boss_states },
    { "train_boss_exit", NULL, train_boss_exit_cases_expected, COUNT(train_boss_exit_cases_expected), train_boss_exit_run },
    { "train_exit_layout", NULL, train_exit_layout_cases_expected, COUNT(train_exit_layout_cases_expected), train_exit_layout_cases_row },
    { "train_projectile_layer_signals", NULL, train_projectile_layer_signals_cases_expected, COUNT(train_projectile_layer_signals_cases_expected), layer_case },
    { "func_8006630C", 0, 0, 6, test_func_8006630C },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_boss_states_cases) + COUNT(train_boss_exit_cases_expected) + COUNT(train_exit_layout_cases_expected) + COUNT(train_projectile_layer_signals_cases_expected) + 6;
