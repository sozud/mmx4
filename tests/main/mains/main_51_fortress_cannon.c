#include "test_runtime.h"
#include "main/mains/main_51_fortress_cannon.h"
#include "main/1A5BC.h"
#include "support/state_cases.h"
#include "main/55C4.h"
#include "main/objects.h"
extern u32* D_80137E08;
extern u8* D_80141EE8[6];
void fortress_cannon_fire_volley(struct MainObj*);
#ifdef MMX4_PC
extern u8 D_80141BE8[1536];
#endif
#ifndef MMX4_PC
extern u8 D_80141BE8[768];
#endif

static const u32 fortress_cannon_fire_double_shot_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_fortress_cannon_fire_double_shot(u32 row)
{
    u32 observed_values[8];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    FILL_ACTIVE(shot_objects, 32, 255 ? 1 : 0);
    fortress_cannon_fire_double_shot(&obj);
    observed_values[0] = (u32)shot_objects[0].active;
    observed_values[1] = (u32)shot_objects[0].bg_offset;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    return c_test_observe(0, row, observed_values, fortress_cannon_fire_double_shot_expected, 8);
}

struct fortress_cannon_fire_shot_case {
    u32 pool_0_full, unk84;
    u32 expected[8];
};
static const struct fortress_cannon_fire_shot_case fortress_cannon_fire_shot_cases[] = {
    { 0, 3, { 0x41u, 0u, 0x1Eu, 0u, 4u, 2u, 0u, 0u } },
    { 255, 0, { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_fortress_cannon_fire_shot(u32 row)
{
    const struct fortress_cannon_fire_shot_case* c = &fortress_cannon_fire_shot_cases[row];
    u32 observed_values[8];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    pool_0_full = c->pool_0_full;
    obj.ext.main_51.unk84 = c->unk84;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    fortress_cannon_fire_shot(&obj);
    observed_values[0] = (u32)shot_objects[0].active;
    observed_values[1] = (u32)shot_objects[0].bg_offset;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    return c_test_observe(0, row, observed_values, c->expected, 8);
}

static const u32 fortress_cannon_fire_volley_expected[] = { 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_fortress_cannon_fire_volley(u32 row)
{
    u32 observed_values[8];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    FILL_ACTIVE(shot_objects, 32, 255 ? 1 : 0);
    fortress_cannon_fire_volley(&obj);
    observed_values[0] = (u32)shot_objects[0].active;
    observed_values[1] = (u32)shot_objects[0].bg_offset;
    observed_values[2] = (u32)shot_objects[0].id;
    observed_values[3] = (u32)shot_objects[0].unk15;
    observed_values[4] = (u32)shot_objects[0].unk16;
    observed_values[5] = (u32)shot_objects[0].unk2;
    observed_values[6] = (u32)shot_objects[0].unk40;
    observed_values[7] = (u32)shot_objects[0].unk42;
    return c_test_observe(0, row, observed_values, fortress_cannon_fire_volley_expected, 8);
}

static const u32 func_80069BE4_expected[] = { 0u, 0u, 1u, 1u, 1u, 0x640000u, 0x500000u };
static u32 test_func_80069BE4(u32 row)
{
    u32 observed_values[7];
    struct MainObj obj;
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013B7D8, 0, sizeof(D_8013B7D8));
    memset(&D_8013B7DC, 0, sizeof(D_8013B7DC));
    memset(&D_8013B7E0, 0, sizeof(D_8013B7E0));
    memset(&D_8013B7E4, 0, sizeof(D_8013B7E4));
    memset(&D_8013B7E8, 0, sizeof(D_8013B7E8));
    memset(&D_8013B7EC, 0, sizeof(D_8013B7EC));
    memset(&D_8013B7F0, 0, sizeof(D_8013B7F0));
    memset(&D_8013B7F4, 0, sizeof(D_8013B7F4));
    memset(&D_8013B7F8, 0, sizeof(D_8013B7F8));
    memset(&D_8013B7FC, 0, sizeof(D_8013B7FC));
    memset(&D_8013B800, 0, sizeof(D_8013B800));
    memset(&D_8013B804, 0, sizeof(D_8013B804));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141BE8, 0, sizeof(D_80141BE8));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&D_80141F70, 0, sizeof(D_80141F70));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&cur_random, 0, sizeof(cur_random));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_FilterAmountG, 0, sizeof(g_FilterAmountG));
    memset(&layout_size, 0, sizeof(layout_size));
    memset(&layout_width, 0, sizeof(layout_width));
    memset(&misc_objects, 0, sizeof(misc_objects));

    memset(&qux_object, 0, sizeof(qux_object));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&visual_objects, 0, sizeof(visual_objects));
    memset(&weapon_objects, 0, sizeof(weapon_objects));
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.spike_immune = 1;
    obj.active = 0x41;
    obj.id = 51;
    obj.hp = 30;
    obj.state = 1;
    obj.unk5 = 1;
    obj.air_state = 1;
    obj.x_pos.val = 6553600;
    obj.y_pos.val = 5242880;
    func_80069BE4(&obj);
    assert(obj.terrain_box == NULL);
    observed_values[0] = (u32)(u8)obj.unk5;
    observed_values[1] = (u32)obj.ext.main_51.saved_unk5;
    observed_values[2] = (u32)(u8)obj.state;
    observed_values[3] = (u32)obj.on_screen;
    observed_values[4] = (u32)obj.air_state;
    observed_values[5] = (u32)obj.unk18.val;
    observed_values[6] = (u32)obj.unk1C.val;
    return c_test_observe(0, row, observed_values, func_80069BE4_expected, 7);
}

struct func_80069F28_case {
    u32 unk84;
    u32 expected[4];
};
static const struct func_80069F28_case func_80069F28_cases[] = {
    { 0, { 1u, 0u, 0u, 0u } },
    { 3, { 0u, 4u, 0u, 0x14u } },
};
static u32 test_func_80069F28(u32 row)
{
    const struct func_80069F28_case* c = &func_80069F28_cases[row];
    u32 observed_values[4];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.unk7C = 1;
    obj.ext.main_51.unk84 = c->unk84;
    obj.unk2 = -1;
    func_80069F28(&obj);
    observed_values[0] = (u32)obj.ext.main_51.unk84;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

#define FCN(step, sub) (state_reset(step, sub, 0), so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60)
#define FIRE(kind, mode, character)                                       \
    do {                                                                  \
        u8 who = engine_obj.cur_character;                                \
        FCN(3, 0);                                                        \
        so.unk2 = kind;                                                   \
        so.ext.main_51.unk84 = mode;                                      \
        engine_obj.cur_character = character;                             \
        fortress_cannon_fire_start(&so);                                  \
        state_extra = shot_objects[0].unk2 | shot_objects[1].active << 8; \
        engine_obj.cur_character = who;                                   \
    } while (0)
static void fcn_fall(void)
{
    FCN(4, 0);
    so.gravity = 0x4000;
    fortress_cannon_fall(&so);
}
static void fcn_land(void)
{
    FCN(4, 0);
    so.collision_flags = 8;
    so.air_state = 1;
    so.x_speed = 0x10000;
    fortress_cannon_fall(&so);
}
static void fcn_fire_x(void) { FIRE(1, 0, 0); }
static void fcn_fire_zero(void) { FIRE(1, 0, 1); }
static void fcn_fire_double(void) { FIRE(0, 2, 0); }
static void fcn_fire_split(void) { FIRE(1, 3, 0); }

static void (*const fortress_cannon_states_cases[])(void) = {
    fcn_fall,
    fcn_land,
    fcn_fire_x,
    fcn_fire_zero,
    fcn_fire_double,
    fcn_fire_split,
};
static const u32 fortress_cannon_states_expected[] = { 4u, 0u, 0x800000u, 0u, 0xFFFFC000u, 0x400000u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x103u, 0x4Bu, 0x800000u, 0u, 0u, 0u, 1u, 0u, 0u, 0x410000u, 0x103u, 0x4Bu, 0x800000u, 0u, 0u, 0u, 2u, 0u, 1u, 0x410000u, 0x103u, 0x4Bu, 0x800000u, 0u, 0u, 0u, 1u, 0u, 0x4100u, 0x410000u, 0x103u, 0x4Bu, 0x800000u, 0u, 0u, 0u, 2u, 0u, 2u, 0x410000u };

static u32 test_fortress_cannon_states(u32 row)
{
    return state_run(fortress_cannon_states_cases[row], row, &fortress_cannon_states_expected[row * 10]);
}

void fortress_cannon_update(struct MainObj*);
void fortress_cannon_wait(struct MainObj*);
void fortress_cannon_fire(struct MainObj*);
extern union AnimationStep* fortress_cannon_animations[];
static struct MainObj expected[48];
static struct ShotObj shots[32];
static u32 frames[64];
static u32 zero_difference(const u32* p, u32 count)
{
    u32 different = 0;
    while (count >= 8) {
        different |= p[0] | p[1] | p[2] | p[3] | p[4] | p[5] | p[6] | p[7];
        p += 8;
        count -= 8;
    }
    while (count--)
        different |= *p++;
    return different;
}
static u32 four_zero_shots(u32 row)
{
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct MainObj* cannon;
    u32 burst, i;
    u16 rng;
    u8 dirty;
    (void)row;
    c_test_zero_words((u32*)main_objects, sizeof(main_objects) / 4);
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    for (i = 0; i < 8; i++)
        frames[i] = 64;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    engine_obj.cur_character = CHARACTER_ZERO;
    g_Player.active = 0x41;
    g_Player.unk2 = CHARACTER_ZERO;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = 80;
    cur_random = 0x1234;
    cannon = find_free_main_obj();
    assert(cannon == &main_objects[0]);
    cannon->active = 1;
    cannon->id = 51;
    cannon->x_pos.i.hi = 160;
    cannon->y_pos.i.hi = 100;
    cannon->sprite_frames = (u8*)frames;
    cannon->unk40 = 0xB0;
    cannon->unk42 = 0x7804;
    SP_CUR_MAIN_OBJ = cannon;
    fortress_cannon_update(cannon);
    assert(cannon->state == 1 && cannon->unk5 == 2 && cannon->unk6 == 0 && cannon->unk7C == 40 && cannon->ext.main_51.unk84 == 0);
    for (i = 0; i < 40; i++)
        fortress_cannon_wait(cannon);
    assert(cannon->unk5 == 3 && cannon->unk6 == 0 && cannon->unk7C == 0);
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    rng = cur_random;
    dirty = need_palette_load;
    for (burst = 0; burst < 4; burst++) {
        assert(cannon->ext.main_51.unk84 == burst && cannon->unk5 == 3 && cannon->unk6 == 0);
        if (burst >= 2) {
            c_test_copy_words((u32*)expected, (u32*)main_objects, sizeof(expected) / 4);
            c_test_copy_words((u32*)shots, (u32*)shot_objects, sizeof(shots) / 4);
            expected[0].unk17 = (burst & 1) ? 1 : 2;
            expected[0].previous_animation_index = 255;
            expected[0].animation_cursor = (const u8*)fortress_cannon_animations[expected[0].unk17];
            expected[0].animation_step.packed = 0x00010001;
            expected[0].unk7C = 75;
            expected[0].unk6 = 1;
            shots[burst].active = 0x41;
            shots[burst].id = 30;
            shots[burst].unk2 = 1 ^ (burst & 1);
            shots[burst].unk7C = WEAPON_OBJECT(cannon);
            shots[burst].unk42 = 0x7804;
            shots[burst].animation_table = (u32**)fortress_cannon_animations;
            shots[burst].unk3C = (u8*)frames;
            shots[burst].unk40 = 0xB0;
            shots[burst].unk16 = 4;
            fortress_cannon_fire(cannon);
            assert(c_test_word_difference((u32*)main_objects, (u32*)expected, sizeof(expected) / 4) == 0 && c_test_word_difference((u32*)shot_objects, (u32*)shots, sizeof(shots) / 4) == 0);
        } else {
            fortress_cannon_fire(cannon);
            assert(cannon->unk7C == 75 && cannon->unk6 == 1 && shot_objects[burst].active == 0x41 && shot_objects[burst].id == 30 && shot_objects[burst].unk2 == (1 ^ (burst & 1)) && shot_objects[burst].unk7C == WEAPON_OBJECT(cannon));
        }
        if (burst < 3) {
            for (i = 0; i < 75; i++)
                fortress_cannon_fire(cannon);
            assert(cannon->unk6 == 0 && cannon->ext.main_51.unk84 == burst + 1);
        }
    }
    assert(zero_difference((u32*)weapon_objects, sizeof(weapon_objects) / 4) == 0 && zero_difference((u32*)visual_objects, sizeof(visual_objects) / 4) == 0 && zero_difference((u32*)misc_objects, sizeof(misc_objects) / 4) == 0);
    assert(c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0 && c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && need_palette_load == dirty && SP_CUR_MAIN_OBJ == cannon);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i < 8 ? 64u : 0));
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    SP_CUR_MAIN_OBJ = current;
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "fortress_cannon_states", 0, 0, COUNT(fortress_cannon_states_cases), test_fortress_cannon_states },
    { "fortress_cannon_fire_double_shot", 0, 0, 1, test_fortress_cannon_fire_double_shot },
    { "fortress_cannon_fire_shot", 0, 0, 2, test_fortress_cannon_fire_shot },
    { "fortress_cannon_fire_volley", 0, 0, 1, test_fortress_cannon_fire_volley },
    { "func_80069BE4", 0, 0, 1, test_func_80069BE4 },
    { "func_80069F28", 0, 0, 2, test_func_80069F28 },
    { "original_constructor_wait40_three_wait75_then_fourth_Zero_shot", NULL, NULL, 1, four_zero_shots },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(fortress_cannon_states_cases) + 1 + 2 + 1 + 1 + 2 + 1;
