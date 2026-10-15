#include "test_runtime.h"
extern union AnimationStep* regen_turret_animations[];

static u32 turret_case(u32 mode)
{
    struct MainObj obj, expected;
    struct ShotObj shots[32];
    struct PlayerObj player_before;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    u32 i, facing = mode == 2 || mode == 3 || mode == 5;
    s16 player_x = mode == 4 ? 100 : mode == 2 || mode == 3 ? 99
                                                            : 101;
    memset(&obj, 0, sizeof(obj));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(&g_Player, 0, sizeof(g_Player));
    for (i = 0; i < 32; i++) {
        struct ShotObj* s = &shot_objects[i];
        s->active = 1;
        s->id = 39;
        s->state = 40;
        s->unk2 = 9;
        s->unk5 = 3;
        s->unk6 = 4;
        s->unk7 = 5;
        s->x_pos.val = 50 * 65536 + 0xBEEF;
        s->y_pos.val = 60 * 65536 + 0xCAFE;
        s->unk50.data = (const u8*)&box;
        s->unk54 = (const u8*)&box;
        s->unk68 = &box;
        s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = 7;
        s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = s->unk78 = 7;
        s->unk62 = s->unk63 = s->unk7A = s->unk75 = 7;
    }
    if (mode == 0 || mode == 2 || mode == 5)
        shot_objects[31].active = 0;
    g_Player.x_pos.val = player_x * 65536 + 0x4321;
    player_before = g_Player;
    obj.active = 0x41;
    obj.id = 30;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk15 = facing ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)regen_turret_animations;
    set_animation(&obj, 1);
    if (mode < 6) {
        obj.animation_cursor = (const u8*)&regen_turret_animations[1][5];
        obj.animation_step = regen_turret_animations[1][5];
        assert(obj.animation_step.packed == 0x06FB0001);
    } else if (mode == 7)
        obj.animation_step.fields.duration = 1;
    expected = obj;
    memcpy(shots, shot_objects, sizeof(shots));
    if (mode < 6) {
        expected.unk5 = 2;
        expected.unk17 = 10;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)regen_turret_animations[10];
        expected.animation_step = regen_turret_animations[10][0];
        if (mode == 0 || mode == 2) {
            struct ShotObj* s = &shots[31];
            s->active = 0x41;
            s->id = 0xF;
            s->unk7C = WEAPON_OBJECT(&obj);
            s->state = s->unk5 = s->unk6 = 0;
            s->unk50.data = NULL;
            s->unk54 = NULL;
            s->unk68 = NULL;
            s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = 0;
            s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = s->unk78 = 0;
            s->unk62 = s->unk63 = s->unk7A = s->unk75 = 0;
        }
    } else if (mode == 6)
        expected.animation_step.fields.duration = 4;
    else {
        expected.animation_cursor = (const u8*)&regen_turret_animations[1][1];
        expected.animation_step = regen_turret_animations[1][1];
    }
    regen_turret_fire(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(shots) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)shots)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return obj.unk17 | ((u32)(u8)obj.unk5 << 8) | ((u32)(u8)shot_objects[31].active << 16);
}
#define CASE(m)                                          \
    static u32 regen_turret_facing_pool_turret_##m(void) \
    {                                                    \
        return turret_case(m);                           \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
CASE(6)
CASE(7)
#define ENTRY(m) regen_turret_facing_pool_turret_##m,
static const CTestCase regen_turret_facing_pool_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) ENTRY(6) ENTRY(7) };
static const u32 regen_turret_facing_pool_cases_expected[] = { 0x41020Au, 0x1020Au, 0x41020Au, 0x1020Au, 0x1020Au, 0x20Au, 0x10301u, 0x10301u };
#undef CASE
#undef ENTRY

static const u32 regen_turret_rebuild_expected[] = { 0u, 0u, 0u, 0u, 0u, 0x70u, 0x76u, 0x3E80000u, 0x3E80000u, 6u };
static u32 test_regen_turret_rebuild(u32 row)
{
    u32 observed_values[10];
    struct MainObj obj, before;
    u32 spawn_record;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.active = 0x45;
    obj.id = 30;
    obj.x_pos.val = 65536000;
    obj.y_pos.val = 65536000;
    func_8005B438(&obj);
    obj.state = 2;
    obj.unk5 = 1;
    set_animation(&obj, 2);
    spawn_record = 0xF1;
    obj.backref = &spawn_record;
    before = obj;
    regen_turret_rebuild(&obj);
    before.active = 0;
    before.id = 0;
    before.unk2 = 0;
    before.on_screen = 0;
    before.state = 0;
    before.unk5 = 0;
    before.unk6 = 0;
    before.unk7 = 0;
    --before.animation_step.fields.duration;
    c_test_same_words(&obj, &before, sizeof(obj));
    observed_values[0] = (u32)obj.active;
    observed_values[1] = (u32)obj.id;
    observed_values[2] = (u32)obj.state;
    observed_values[3] = (u32)obj.unk5;
    observed_values[4] = (u32)obj.on_screen;
    observed_values[5] = spawn_record;
    observed_values[6] = (u32)obj.animation_step.fields.duration;
    observed_values[7] = (u32)obj.x_pos.val;
    observed_values[8] = (u32)obj.y_pos.val;
    observed_values[9] = (u32)(u8)obj.hp;
    return c_test_observe(0, row, observed_values, regen_turret_rebuild_expected, 10);
}

const struct CTestGroup c_test_groups[] = {
    { "regen_turret_facing_pool", regen_turret_facing_pool_cases, regen_turret_facing_pool_cases_expected, COUNT(regen_turret_facing_pool_cases), 0 },
    { "regen_turret_rebuild", 0, 0, 1, test_regen_turret_rebuild },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(regen_turret_facing_pool_cases) + 1;
