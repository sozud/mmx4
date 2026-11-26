#include "test_runtime.h"
#include "main/items/item_02_pickup.h"
#include "weapon_resources.h"
#include "support/state_cases.h"
#include "main/55C4.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

#ifndef VERSION_DEMO
static u32 pickup_case(u32 mode)
{
    struct ItemObj obj, before;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 i, actual;
    u8 kind;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.id = 2;
    obj.state = 1;
    for (i = 0; i < COUNT(g_Player.weapon_energy); i++)
        g_Player.weapon_energy[i] = 24;
    g_Player.hp = 20;
    g_Player.boss_flags = 1;
    g_Player.weapon_energy[0] = mode == 0 ? 40 : 20;
    g_Player.weapon_energy[1] = mode == 0 ? 3 : 7;
    g_Player.weapon_energy[2] = 11;
    engine_obj.collected_upgrades = mode == 2 ? 0 : 0x4000;
    engine_obj.sub_tanks[2] = 32;
    if (mode == 2)
        g_Player.weapon = 2;
    kind = mode == 0 ? 3 : mode == 1 ? 2
                                     : 0;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    func_800BFCC0(&obj, kind);
    actual = (u8)g_Player.weapon_energy[0] | ((u32)(u8)g_Player.weapon_energy[1] << 8)
        | ((u32)(u8)engine_obj.sub_tanks[2] << 16);
    player_before.weapon_energy[0] = g_Player.weapon_energy[0];
    player_before.weapon_energy[1] = g_Player.weapon_energy[1];
    engine_before.sub_tanks[2] = engine_obj.sub_tanks[2];
    for (i = 0; i < sizeof(obj); i++)
        assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj); i++)
        assert(((u8*)&engine_obj)[i] == ((u8*)&engine_before)[i]);
    return actual;
}
static const u32 energy_selection_context_cases_expected[] = { 0x201330u, 0x200B18u, 0x200714u };

static u32 health_case(u32 mode)
{
    struct ItemObj item, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 i, actual;
    s8 energy = mode == 2 ? 0 : 4;
    s32 tank_gain = mode == 1 ? 20 : mode == 3 ? 2
                                               : 4;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    memset(&item, 0, sizeof(item));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    item.active = 1;
    item.id = 2;
    item.state = 1;
    item.unk5 = 3;
    item.unk6 = 4;
    item.x_pos.val = 100 * 65536 + 0x1234;
    item.y_pos.val = 200 * 65536 + 0x5678;
    g_Player.hp = mode == 0 ? 10 : mode == 2 ? 0x92
                                             : 16;
    g_Player.weapon_energy[0] = mode == 0 ? 47 : mode == 2 ? 49
                                                           : 10;
    engine_obj.max_hp = 16;
    engine_obj.collected_upgrades = 0x3000;
    engine_obj.sub_tanks[0] = mode == 0 ? 0 : mode == 1 ? 16
                                                        : 32;
    engine_obj.sub_tanks[1] = mode == 3 ? 30 : 32;
    expected = item;
    player_before = g_Player;
    engine_before = engine_obj;
    if (mode == 0) {
        expected.active = 9;
        expected.state = 2;
        expected.unk5 = expected.unk6 = 0;
        expected.ext.item_2.unk80 = energy;
        expected.ext.item_2.unk81 = 2;
        engine_before.unk10 = engine_before.unk11 = engine_before.unk12 = engine_before.unk13 = 1;
        engine_before.unk14 = engine_before.unk15 = engine_before.unk16 = engine_before.unk17 = 1;
    } else {
        expected.state = 3;
        player_before.hp = mode == 2 ? 0x90 : 16;
    }
    player_before.weapon_energy[0] = mode == 0 || mode == 2 ? 48 : 14;
    if (mode == 0)
        engine_before.sub_tanks[0] = 0x84;
    if (mode == 1)
        engine_before.sub_tanks[0] = 0xA0;
    if (mode == 3)
        engine_before.sub_tanks[1] = 0xA0;
    pickup_collect_health(&item, energy, tank_gain);
    for (i = 0; i < sizeof(item) / 4; i++)
        assert(((u32*)&item)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    actual = (u8)item.state | ((u32)g_Player.weapon_energy[0] << 8) | ((u32)engine_obj.sub_tanks[0] << 16) | ((u32)engine_obj.sub_tanks[1] << 24);
    return actual;
}
static const u32 pickup_health_tank_limits_cases_expected[] = { 0xFF843002u, 0xFFA00E03u, 0x20203003u, 0xA0200E03u };

static const u32 inputs_0[3][22] = {
    { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16448, 0, 2 },
    { -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16448, 32, 2 },
    { -1, 15, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 46, 16448, 32, 2 },
};
struct func_800BFCC0_case {
    u32 expected[17];
};
static const struct func_800BFCC0_case func_800BFCC0_cases[] = {
    { { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0x20u, 4u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
    { { 0x20u, 0u, 0u, 0u, 0u, 0u, 0u, 0x30u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800BFCC0(u32 row)
{
    const struct func_800BFCC0_case* c = &func_800BFCC0_cases[row];
    u32 observed_values[17];
    struct ItemObj obj;
    u8 arg1;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    engine_obj.cur_character = inputs_0[row][0];
    g_Player.weapon = inputs_0[row][1];
    g_Player.boss_flags = inputs_0[row][2];
    g_Player.weapon_energy[0] = inputs_0[row][3];
    g_Player.weapon_energy[1] = inputs_0[row][4];
    g_Player.weapon_energy[2] = inputs_0[row][5];
    g_Player.weapon_energy[3] = inputs_0[row][6];
    g_Player.weapon_energy[4] = inputs_0[row][7];
    g_Player.weapon_energy[5] = inputs_0[row][8];
    g_Player.weapon_energy[6] = inputs_0[row][9];
    g_Player.weapon_energy[7] = inputs_0[row][10];
    g_Player.weapon_energy[8] = inputs_0[row][11];
    g_Player.weapon_energy[9] = inputs_0[row][12];
    g_Player.weapon_energy[10] = inputs_0[row][13];
    g_Player.weapon_energy[11] = inputs_0[row][14];
    g_Player.weapon_energy[12] = inputs_0[row][15];
    g_Player.weapon_energy[13] = inputs_0[row][16];
    g_Player.weapon_energy[14] = inputs_0[row][17];
    g_Player.weapon_energy[15] = inputs_0[row][18];
    engine_obj.collected_upgrades = inputs_0[row][19];
    engine_obj.sub_tanks[2] = inputs_0[row][20];
    arg1 = inputs_0[row][21];
    func_800BFCC0(&obj, arg1);
    observed_values[0] = (u32)engine_obj.sub_tanks[2];
    observed_values[1] = (u32)g_Player.weapon_energy[0];
    observed_values[2] = (u32)g_Player.weapon_energy[10];
    observed_values[3] = (u32)g_Player.weapon_energy[11];
    observed_values[4] = (u32)g_Player.weapon_energy[12];
    observed_values[5] = (u32)g_Player.weapon_energy[13];
    observed_values[6] = (u32)g_Player.weapon_energy[14];
    observed_values[7] = (u32)g_Player.weapon_energy[15];
    observed_values[8] = (u32)g_Player.weapon_energy[1];
    observed_values[9] = (u32)g_Player.weapon_energy[2];
    observed_values[10] = (u32)g_Player.weapon_energy[3];
    observed_values[11] = (u32)g_Player.weapon_energy[4];
    observed_values[12] = (u32)g_Player.weapon_energy[5];
    observed_values[13] = (u32)g_Player.weapon_energy[6];
    observed_values[14] = (u32)g_Player.weapon_energy[7];
    observed_values[15] = (u32)g_Player.weapon_energy[8];
    observed_values[16] = (u32)g_Player.weapon_energy[9];
    return c_test_observe(0, row, observed_values, c->expected, 17);
}

static const u32 pickup_collect_health_expected[] = { 0u, 0xFFFFFFA0u, 0u, 0u, 0u, 0u, 0u, 0u, 3u, 0u, 0u };
static u32 test_pickup_collect_health(u32 row)
{
    u32 observed_values[11];
    struct ItemObj obj;
    s8 arg1;
    s32 arg2;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    engine_obj.collected_upgrades = 8224;
    engine_obj.sub_tanks[1] = 28;
    engine_obj.sub_tanks[2] = 0;
    arg1 = 0;
    arg2 = 28;
    pickup_collect_health(&obj, arg1, arg2);
    observed_values[0] = (u32)engine_obj.sub_tanks[0];
    observed_values[1] = (u32)engine_obj.sub_tanks[1];
    observed_values[2] = (u32)engine_obj.sub_tanks[2];
    observed_values[3] = (u32)g_Player.hp;
    observed_values[4] = (u32)g_Player.weapon_energy[0];
    observed_values[5] = (u32)obj.active;
    observed_values[6] = (u32)obj.ext.item_2.unk80;
    observed_values[7] = (u32)obj.ext.item_2.unk81;
    observed_values[8] = (u32)obj.state;
    observed_values[9] = (u32)obj.unk5;
    observed_values[10] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, pickup_collect_health_expected, 11);
}
#define COLLECT_STEP_CASES (COUNT(energy_selection_context_cases_expected) + COUNT(pickup_health_tank_limits_cases_expected) + 3 + 1)
#else
#define COLLECT_STEP_CASES 0
#endif

static struct Unk_unk68 pickup_box = { 0, 0, 8, 8 };
static struct PlayerObj pickup_player;
static struct EngineObj pickup_engine;
static u8 pickup_qux_hp;
static u8* pickup_frames;
#define sp state_room.item
#define PICKUP_AT(kind, upgrades, lives) (pickup_player = g_Player, pickup_engine = engine_obj, pickup_qux_hp = qux_object.hp, pickup_frames = TEST_SPRITE_FRAMES, TEST_SPRITE_FRAMES = (u8*)state_sprite_frames, state_reset(0, 0, 0), engine_obj.collected_upgrades = upgrades, engine_obj.player_lives = lives, sp.active = 1, sp.state = 1, sp.unk2 = kind, sp.x_pos.i.hi = 0x80, sp.y_pos.i.hi = 0x80, SP_CUR_ITEM_OBJ = &sp)
#define PICKUP(kind, upgrades) PICKUP_AT(kind, upgrades, 2)
#define DONE() (state_extra = sp.unk7C.value | engine_obj.collected_upgrades << 8 | (u32)(u8)engine_obj.player_lives << 24, g_Player = pickup_player, engine_obj = pickup_engine, qux_object.hp = pickup_qux_hp, TEST_SPRITE_FRAMES = pickup_frames)
#define INIT(kind, upgrades) (PICKUP(kind, upgrades), func_800BF76C(&sp), DONE())
#define GRAB_AT(kind, type, upgrades, ride, health, lives) (PICKUP_AT(kind, upgrades, lives), sp.unk7C.value = type, sp.unk68 = &pickup_box, g_Player.ride_state = ride, g_Player.hp = health, g_Player.unk68 = &pickup_box, g_Player.x_pos.i.hi = 0x80, g_Player.y_pos.i.hi = 0x80, qux_object.hp = 0, func_800C00BC(&sp), DONE())
#define GRAB(kind, type, upgrades, ride, health) GRAB_AT(kind, type, upgrades, ride, health, 2)
static void pk_init_life(void)
{
    INIT(4, 0);
}
static void pk_init_heart(void) { INIT(9, 0); }
static void pk_init_heart_taken(void) { INIT(9, 4); }
static void pk_init_hearts_full(void) { INIT(9, 0xFF); }
static void pk_init_tank(void) { INIT(0x10, 0); }
static void pk_init_tank_taken(void) { INIT(0x10, 0x2000); }
static void pk_init_weapon_tank(void) { INIT(0x11, 0); }
static void pk_init_weapon_tank_taken(void) { INIT(0x11, 0x4000); }
static void pk_init_extra_tank(void) { INIT(0x12, 0); }
static void pk_init_extra_tank_taken(void) { INIT(0x12, 0x8000); }
static void pk_init_carried(void)
{
    PICKUP(1, 0);
    sp.backref = (void*)&pickup_box;
    func_800BF76C(&sp);
    DONE();
}
static void pk_grab_dead(void) { GRAB(4, 4, 0, 0, 0); }
static void pk_grab_ride_dead(void) { GRAB(4, 4, 0, 1, 8); }
static void pk_grab_miss(void)
{
    PICKUP(4, 0);
    sp.unk7C.value = 4;
    sp.unk68 = &pickup_box;
    g_Player.ride_state = 0;
    g_Player.hp = 8;
    g_Player.unk68 = &pickup_box;
    g_Player.x_pos.i.hi = 0x200;
    func_800C00BC(&sp);
    DONE();
}
static void pk_grab_life(void) { GRAB(4, 4, 0, 0, 8); }
static void pk_grab_life_full(void) { GRAB_AT(4, 4, 0, 0, 8, 9); }
static void pk_grab_heart(void) { GRAB(9, 7, 0, 0, 8); }
static void pk_grab_heart_taken(void) { GRAB(9, 7, 4, 0, 8); }
static void pk_grab_hearts_full(void) { GRAB(9, 7, 0xFF, 0, 8); }
static void pk_grab_tank(void) { GRAB(0xF, 8, 0, 0, 8); }
static void pk_grab_tank_taken(void) { GRAB(0xF, 8, 0x1000, 0, 8); }
static void pk_grab_tanks_full(void) { GRAB(0xF, 8, 0x3000, 0, 8); }
static void pk_grab_weapon_tank(void) { GRAB(0x11, 9, 0, 0, 8); }
static void pk_grab_weapon_tank_taken(void) { GRAB(0x11, 9, 0x4000, 0, 8); }
static void pk_grab_extra_tank(void) { GRAB(0x12, 10, 0, 0, 8); }
static void pk_grab_extra_tank_taken(void) { GRAB(0x12, 10, 0x8000, 0, 8); }
static void pk_grab_other(void) { GRAB(0x13, 11, 0, 0, 8); }

static void (*const pickup_states_cases[])(void) = {
    pk_init_life,
    pk_init_heart,
    pk_init_heart_taken,
    pk_init_hearts_full,
    pk_init_tank,
    pk_init_tank_taken,
    pk_init_weapon_tank,
    pk_init_weapon_tank_taken,
    pk_init_extra_tank,
    pk_init_extra_tank_taken,
    pk_init_carried,
    pk_grab_dead,
    pk_grab_ride_dead,
    pk_grab_miss,
    pk_grab_life,
    pk_grab_life_full,
    pk_grab_heart,
    pk_grab_heart_taken,
    pk_grab_hearts_full,
    pk_grab_tank,
    pk_grab_tank_taken,
    pk_grab_tanks_full,
    pk_grab_weapon_tank,
    pk_grab_weapon_tank_taken,
    pk_grab_extra_tank,
    pk_grab_extra_tank_taken,
    pk_grab_other,
};
#ifdef VERSION_SATURN_PROTO
#define PK_KIND12_CLUT OBJECT_CLUT(0x7807)
#else
#define PK_KIND12_CLUT OBJECT_CLUT(0x780B)
#endif
static const u32 pickup_states_expected[] = { 1u, 0xFF000421u, 0x800000u, 0x800000u, 0u, 0x80000u, 0x800000u, (0x60000u | OBJECT_CLUT(0x780B)), 0x2000004u, 0u, 1u, 0xFF000921u, 0x800000u, 0x800000u, 0u, 0x80000u, 0x800000u, (0x60000u | OBJECT_CLUT(0x7807)), 0x2000007u, 0u, 3u, 0x921u, 0x800000u, 0x800000u, 0u, 0x80000u, 0x800000u, (0x50000u | OBJECT_CLUT(0x7807)), 0x2000407u, 0u, 3u, 0x921u, 0x800000u, 0x800000u, 0u, 0x80000u, 0x800000u, (0x50000u | OBJECT_CLUT(0x7807)), 0x200FF07u, 0u, 1u, 0xFF001021u, 0x800000u, 0x800000u, 0u, 0x80000u, 0x800000u, (0x30000u | OBJECT_CLUT(0x7807)), 0x2000008u, 0u, 3u, 0x1021u, 0x800000u, 0x800000u, 0u, 0x80000u, 0x800000u, (0x50000u | OBJECT_CLUT(0x7807)), 0x2200008u, 0u, 1u, 0xFF001121u, 0x800000u, 0x800000u, 0u, 0x80000u, 0x800000u, (0x30000u | OBJECT_CLUT(0x7807)), 0x2000009u, 0u, 3u, 0x1121u, 0x800000u, 0x800000u, 0u, 0x80000u, 0x800000u, (0x50000u | OBJECT_CLUT(0x7807)), 0x2400009u, 0u, 1u, 0xFF001221u, 0x800000u, 0x800000u, 0u, 0x80000u, 0x800000u, (0x50000u | PK_KIND12_CLUT), 0x200000Au, 0u, 3u, 0x1221u, 0x800000u, 0x800000u, 0u, 0x80000u, 0x800000u, (0x50000u | PK_KIND12_CLUT), 0x280000Au, 0u, 1u, 0xFF000121u, 0x800000u, 0x800000u, 0u, 0u, 0x800000u, (0x30000u | OBJECT_CLUT(0x7807)), 0x2000001u, 0u, 1u, 0x401u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x2000004u, 0u, 1u, 0x401u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x2000004u, 0u, 1u, 0x401u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x2000004u, 0u, 3u, 0x401u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x3000004u, 0u, 3u, 0x401u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x9000004u, 0u, 3u, 0x901u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x2000407u, 0u, 3u, 0x901u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x2000407u, 0u, 3u, 0x901u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x200FF07u, 0u, 3u, 0xF01u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x2100008u, 0u, 1u, 0xF01u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x2100008u, 0u, 1u, 0xF01u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x2300008u, 0u, 3u, 0x1101u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x2400009u, 0u, 1u, 0x1101u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x2400009u, 0u, 3u, 0x1201u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x280000Au, 0u, 1u, 0x1201u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x280000Au, 0u, 3u, 0x1301u, 0x800000u, 0x800000u, 0u, 0u, 0u, 0x50000u, 0x200000Bu, 0u };

static u32 test_pickup_states(u32 row)
{
    return object_run(pickup_states_cases[row], row, &pickup_states_expected[row * 10]);
}

extern union AnimationStep* D_800F8FC4[38];
extern u8 D_800F9068[4], D_800F906C[4];
extern s8* pickup_hit_boxes[11];
static u32 frames[16];
static u32 collect(u32 row)
{
    struct ItemObj obj, expected;
    struct EngineObj engine;
    struct PlayerObj player;
    struct RideArmorObj bike;
    struct MainBssState main = main_bss_state;
    s8 bank = D_8013E198[0];
    u16 rng = cur_random;
    u32 i;
    (void)row;
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.state = 6;
    engine_obj.stage = 5;
    engine_obj.substage = 1;
    engine_obj.max_hp = 32;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.active = 0x41;
    g_Player.hp = 24;
    g_Player.ride_state = 1;
    g_Player.ride_animation = 0x41;
    g_Player.x_pos.i.hi = 15520;
    g_Player.y_pos.i.hi = 50;
    memset(&qux_object, 0, sizeof(qux_object));
    qux_object.active = 0x41;
    qux_object.id = 2;
    qux_object.state = 1;
    qux_object.hp = 24;
    qux_object.unk68 = (void*)D_800F9068;
    qux_object.unk54 = D_800F906C;
    qux_object.animation_table = (u32**)D_800F8FC4;
    qux_object.x_pos = g_Player.x_pos;
    qux_object.y_pos = g_Player.y_pos;
    ((u8*)&qux_object.unk7C)[0x9B - 0x7C] = 1;
    set_animation(&qux_object, 0);
    bike = qux_object;
    player = g_Player;
    memset(frames, 0, sizeof(frames));
    frames[3] = 32;
    TEST_SPRITE_FRAMES = (u8*)frames;
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 2;
    obj.unk2 = 16;
    obj.x_pos = g_Player.x_pos;
    obj.y_pos = g_Player.y_pos;
    func_800BF76C(&obj);
    assert(obj.unk7C.value == 8 && obj.state == 1 && obj.unk68 == (struct Unk_unk68*)pickup_hit_boxes[8]);
    expected = obj;
    expected.state = 3;
    engine = engine_obj;
    engine.collected_upgrades = 0x2000;
    engine.sub_tanks[1] = -128;
    D_8013E198[0] = -1;
    func_800C00BC(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&qux_object, &bike, sizeof(bike));
    c_test_same_words(&main_bss_state, &main, sizeof(main));
    assert(cur_random == rng && D_8013E198[0] == -1 && TEST_SPRITE_FRAMES == (u8*)frames);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i == 3 ? 32u : 0));
    D_8013E198[0] = bank;
    return 1;
}

void pickup_main(struct ItemObj*);
void func_800BFBD0(struct ItemObj*);
static u32 pk_seen;
#define PMX() (pk_seen = sp.unk67 | (u8)sp.unk70 << 8 | (u32)sp.ext.item_2.unk82 << 16 | (u32)sp.on_screen << 24, DONE(), state_extra = pk_seen)
#define PMAIN(setup) (PICKUP(0, 0), sp.unk68 = &pickup_box, sp.ext.item_2.unk82 = 0x40, sp.unk2C = 0x8000, g_Player.x_pos.i.hi = 0x200, setup, pickup_main(&sp), PMX())
static void pk_main_bounce(void) { PMAIN((state_terrain(0x38), sp.unk67 = 1, sp.y_vel.val = 0x20000)); }
static void pk_main_bounce_back(void) { PMAIN((state_terrain(0x38), sp.unk67 = 1, sp.y_vel.val = -0x20000)); }
static void pk_main_settle(void) { PMAIN((state_terrain(0x38), sp.unk67 = 1, sp.unk6 = 1)); }
static void pk_main_fall(void) { PMAIN((state_terrain(0), sp.unk67 = 1, sp.y_vel.val = -0x10000)); }
static void pk_main_drop(void) { PMAIN((state_terrain(0), sp.y_vel.val = -0x10000)); }
static void pk_main_rest(void) { PMAIN((state_terrain(0x38), sp.ext.item_2.unk82 = 0x3B, WEAPON_FRAME_COUNTER = 0)); }
static void pk_main_blink(void) { PMAIN((state_terrain(0x38), sp.ext.item_2.unk82 = 0x3B, WEAPON_FRAME_COUNTER = 0xFF)); }
static void pk_main_expire(void) { PMAIN((state_terrain(0x38), sp.ext.item_2.unk82 = 1)); }
static void pk_main_carried_away(void) { PMAIN((state_terrain(0x38), sp.backref = (void*)&pickup_box, sp.x_pos.i.hi = 0x400)); }
static void pk_main_away(void) { PMAIN((state_terrain(0x38), sp.x_pos.i.hi = 0x400)); }
#define REFILL(sub, delay, count, health) (PICKUP(1, 0), sp.unk6 = sub, sp.ext.item_2.unk81 = delay, sp.ext.item_2.unk80 = count, engine_obj.max_hp = 0x10, g_Player.hp = health, func_800BFBD0(&sp), pk_seen = sp.ext.item_2.unk80 | sp.ext.item_2.unk81 << 8 | (u32)g_Player.hp << 16, DONE(), state_extra = pk_seen)
static void pk_refill_delay(void) { REFILL(0, 2, 2, 8); }
static void pk_refill_step(void) { REFILL(0, 1, 2, 8); }
static void pk_refill_full(void) { REFILL(0, 1, 1, 0x10); }
static void pk_refill_end(void) { REFILL(1, 1, 1, 8); }
static void pk_grab_small(void) { GRAB(0, 0, 0, 0, 8); }
static void pk_grab_large(void) { GRAB(1, 1, 0, 0, 8); }
static void pk_grab_energy_small(void) { GRAB(2, 2, 0, 0, 8); }
static void pk_grab_energy_large(void) { GRAB(3, 3, 0, 0, 8); }
static void pk_grab_full(void) { GRAB(5, 5, 0, 0, 8); }
static void pk_grab_energy_full(void) { GRAB(6, 6, 0, 0, 8); }
static void pk_init_tanks_full(void) { INIT(0x10, 0x3000); }
#ifndef VERSION_DEMO
#define ENERGY(kind, who, held, owned, e0, e1, e2, setup) (PICKUP(kind, 0), engine_obj.cur_character = who, g_Player.weapon = held, g_Player.boss_flags = owned, g_Player.weapon_energy[0] = e0, g_Player.weapon_energy[1] = e1, g_Player.weapon_energy[2] = e2, setup, func_800BFCC0(&sp, kind), pk_seen = (u8)g_Player.weapon_energy[0] | (u8)g_Player.weapon_energy[1] << 8 | (u32)(u8)g_Player.weapon_energy[2] << 16, DONE(), state_extra = pk_seen)
static void pk_energy_no_weapons(void) { ENERGY(6, 0, 0, 0, 0x2F, 0x10, 0x10, 0); }
static void pk_energy_lowest_first(void) { ENERGY(2, 0, 0, 3, 0x30, 0x10, 0x20, 0); }
static void pk_energy_current_over(void) { ENERGY(6, 0, 2, 2, 0x30, 0x30, 0x20, 0); }
static void pk_energy_current_fill(void) { ENERGY(2, 0, 2, 2, 0x30, 0x30, 0x2C, 0); }
static void pk_energy_current_full(void) { ENERGY(2, 0, 2, 2, 0x30, 0x30, 0x31, 0); }
static void pk_energy_zero_full(void) { ENERGY(2, 1, 1, 1, 0x30, 0x31, 0x30, 0); }
#endif
static void (*const pickup_more_cases[])(void) = {
    pk_main_bounce,
    pk_main_bounce_back,
    pk_main_settle,
    pk_main_fall,
    pk_main_drop,
    pk_main_rest,
    pk_main_blink,
    pk_main_expire,
    pk_main_carried_away,
    pk_main_away,
    pk_refill_delay,
    pk_refill_step,
    pk_refill_full,
    pk_refill_end,
    pk_grab_small,
    pk_grab_large,
    pk_grab_energy_small,
    pk_grab_energy_large,
    pk_grab_full,
    pk_grab_energy_full,
    pk_init_tanks_full,
#ifndef VERSION_DEMO
    pk_energy_no_weapons,
    pk_energy_lowest_first,
    pk_energy_current_over,
    pk_energy_current_fill,
    pk_energy_current_full,
    pk_energy_zero_full,
#endif
};
static const u32 pickup_more_expected[] = {
    0x10001u, 0x1u, 0x800000u, 0x7E0000u, 0x0u, 0xC000u, 0x800000u, 0x50000u, 0x13F0F01u, 0x0u,
    0x10001u, 0x1u, 0x800000u, 0x820000u, 0x0u, 0x14000u, 0x800000u, 0x50000u, 0x13F0F01u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x800000u, 0x0u, 0xFFFF8000u, 0x800000u, 0x50000u, 0x13F0F00u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x810000u, 0x0u, 0xFFFE8000u, 0x800000u, 0x50000u, 0x13F0001u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x800000u, 0x40000u, 0x13F0001u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x800000u, 0x40000u, 0x13A0F00u, 0x0u,
    0x1u, 0x1u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x800000u, 0x40000u, 0x3A0F00u, 0x0u,
    0x3u, 0x1u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x800000u, 0x40000u, 0xF00u, 0x0u,
    0x0u, 0x0u, 0x4000000u, 0x800000u, 0x0u, 0x0u, 0x800000u, 0x40000u, 0x400F00u, 0x0u,
    0x3u, 0x1u, 0x4000000u, 0x800000u, 0x0u, 0x0u, 0x800000u, 0x40000u, 0x3F0F00u, 0x0u,
    0x1u, 0x101u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x80102u, 0x0u,
    0x1u, 0x101u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x90201u, 0x0u,
    0x10001u, 0x101u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x100200u, 0x0u,
    0x10003u, 0x101u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x80101u, 0x0u,
    0x3u, 0x1u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x2000000u, 0x0u,
    0x3u, 0x101u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x2000001u, 0x0u,
    0x3u, 0x201u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x2000002u, 0x0u,
    0x3u, 0x301u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x2000003u, 0x0u,
    0x3u, 0x501u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x2000005u, 0x0u,
    0x3u, 0x601u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x2000006u, 0x0u,
    0x3u, 0x1021u, 0x800000u, 0x800000u, 0x0u, 0x80000u, 0x800000u, (0x50000u | OBJECT_CLUT(0x7807)), 0x2300008u, 0x0u,
#ifndef VERSION_DEMO
    0x1u, 0x601u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x101030u, 0x0u,
    0x1u, 0x201u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x201430u, 0x0u,
    0x1u, 0x601u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x303030u, 0x0u,
    0x1u, 0x201u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x303030u, 0x0u,
    0x1u, 0x201u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x303030u, 0x0u,
    0x1u, 0x201u, 0x800000u, 0x800000u, 0x0u, 0x0u, 0x0u, 0x50000u, 0x303030u, 0x0u,
#endif
};
static u32 test_pickup_more(u32 row)
{
    return object_run(pickup_more_cases[row], row, &pickup_more_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "pickup_more_states", 0, 0, COUNT(pickup_more_cases), test_pickup_more },
    { "pickup_states", 0, 0, COUNT(pickup_states_cases), test_pickup_states },
#ifndef VERSION_DEMO
    { "energy_selection_context", NULL, energy_selection_context_cases_expected, COUNT(energy_selection_context_cases_expected), pickup_case },
    { "pickup_health_tank_limits", NULL, pickup_health_tank_limits_cases_expected, COUNT(pickup_health_tank_limits_cases_expected), health_case },
    { "func_800BFCC0", 0, 0, 3, test_func_800BFCC0 },
    { "pickup_collect_health", 0, 0, 1, test_pickup_collect_health },
#endif
    { "original_Jet_stage_second_health_tank_collects_from_real_ride_chaser", NULL, NULL, 1, collect },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(pickup_more_cases) + COUNT(pickup_states_cases) + COLLECT_STEP_CASES + 1;
