#include "test_runtime.h"
#include "main/shots/shot_53_sigma_head.h"
#include "main/object_motion.h"
extern s16 sigma_head_formation_end[8][3][2];
extern u8 sigma_head_formation_next[8][3];

static u32 head_case(u32 raw, u32 observation)
{
    struct ShotObj obj, before;
    u8 next_before[8][3];
    u32 i, variant = raw ? 0 : 1;
    s16 x = sigma_head_formation_end[5][variant][0], y = sigma_head_formation_end[5][variant][1];
    memset(&obj, 0, sizeof(obj));
    memcpy(next_before, sigma_head_formation_next, sizeof(next_before));
    assert(next_before[5][0] == 1 && next_before[5][1] == 0);
    if (raw)
        sigma_head_formation_next[5][0] = 0;
    obj.active = 0x41;
    obj.id = 53;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.unk15 = 0x27;
    obj.unk8C.bytes[2] = 5;
    obj.unk2 = variant;
    obj.x_pos.val = (x - 50) * 65536 + 0x1234;
    obj.y_pos.val = y * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    before = obj;
    before.x_pos.val += 65536;
    obj.unk8C.bytes[1] = angle_to_point(OBJECT_HEADER(&before), x * 65536, y * 65536) ^ 0x10;
    before.unk8C.bytes[1] = obj.unk8C.bytes[1];
    sigma_head_move(&obj);
    before.x_pos.i.hi = x;
    before.y_pos.i.hi = y;
    before.unk6 = 0;
    before.unk5 = raw ? 3 : 8;
    if (!raw)
        before.unk15 = 0x40;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(next_before); i++)
        assert(((u8*)sigma_head_formation_next)[i] == (raw && i == 15 ? 0 : ((u8*)next_before)[i]));
    return observation == 0 ? (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u8)obj.unk15 << 16) : (u16)obj.x_pos.i.hi | ((u32)(u16)obj.y_pos.i.hi << 16);
}
#define CASE(m, n)                                               \
    static u32 sigma_head_formation_context_head_##m##_##n(void) \
    {                                                            \
        return head_case(m, n);                                  \
    }
CASE(0, 0)
CASE(0, 1)
CASE(1, 0)
CASE(1, 1)
#define ENTRY(m, n) sigma_head_formation_context_head_##m##_##n,
static const CTestCase sigma_head_formation_context_cases[]
    = { ENTRY(0, 0) ENTRY(0, 1) ENTRY(1, 0) ENTRY(1, 1) };
static const u32 sigma_head_formation_context_cases_expected[] = { 0x400008u, 0x2580408u, 0x270003u, 0x2B80578u };
#undef CASE
#undef ENTRY

static u32 volley_case(u32 mode)
{
    struct ShotObj obj, expected, pool_before[32];
    struct MainObj owner, owner_before;
    struct PlayerObj player_before = g_Player;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    u32 i, free_count = mode == 2 || mode == 4 ? 1 : mode == 3 || mode == 5 ? 4
                                                                            : 0;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = i >= 32 - free_count ? 0 : 1;
        shot_objects[i].id = 39;
        shot_objects[i].state = 40;
        shot_objects[i].unk2 = 9;
        shot_objects[i].unk5 = 3;
        shot_objects[i].unk6 = 4;
        shot_objects[i].unk7 = 5;
        shot_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        shot_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
        shot_objects[i].unk50.data = (const u8*)&box;
        shot_objects[i].unk54 = (const u8*)&box;
        shot_objects[i].unk68 = &box;
        shot_objects[i].unk98 = shot_objects[i].unk61 = shot_objects[i].unk64 = shot_objects[i].unk65 = shot_objects[i].unk66 = 7;
        shot_objects[i].unk72 = shot_objects[i].unk73 = shot_objects[i].unk74 = shot_objects[i].unk76 = shot_objects[i].unk77 = shot_objects[i].unk78 = 7;
        shot_objects[i].unk62 = shot_objects[i].unk63 = shot_objects[i].unk7A = shot_objects[i].unk75 = 7;
    }
    owner.active = 0x41;
    owner.id = 74;
    owner.state = 1;
    obj.active = 0x41;
    obj.id = 53;
    obj.state = 1;
    obj.unk5 = 2;
    obj.unk6 = 4;
    obj.timer = mode ? 1 : 2;
    obj.unk8A = mode >= 4 ? 1 : 2;
    obj.unk7C = WEAPON_OBJECT(&owner);
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    expected = obj;
    owner_before = owner;
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    expected.timer = mode ? 40 : 1;
    if (mode) {
        expected.unk8A--;
        if (mode >= 4) {
            expected.unk5 = 3;
            expected.unk6 = 0;
            owner_before.ext.main_74.unk8E = 1;
        } else
            expected.unk6 = 3;
        for (i = 0; i < free_count; i++) {
            struct ShotObj* child = &pool_before[32 - free_count + i];
            child->active = 0x41;
            child->id = 54;
            child->unk2 = 0;
            child->unk7 = i;
            child->x_pos = obj.x_pos;
            child->y_pos = obj.y_pos;
            child->unk7C = WEAPON_OBJECT(&owner);
            child->unk50.data = NULL;
            child->unk54 = NULL;
            child->unk68 = NULL;
            child->unk98 = child->unk61 = child->unk64 = child->unk65 = child->unk66 = 0;
            child->unk72 = child->unk73 = child->unk74 = child->unk76 = child->unk77 = child->unk78 = 0;
            child->unk62 = child->unk63 = child->unk7A = child->unk75 = 0;
        }
    }
    sigma_head_fire_wall_shoot(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    return (u16)obj.timer | ((u32)(u8)obj.unk6 << 16) | ((u32)owner.ext.main_74.unk8E << 24);
}
#define CASE(m)                                              \
    static u32 sigma_head_wall_volley_pools_volley_##m(void) \
    {                                                        \
        return volley_case(m);                               \
    }
CASE(0)
CASE(1)
CASE(2)
CASE(3)
CASE(4)
CASE(5)
#define ENTRY(m) sigma_head_wall_volley_pools_volley_##m,
static const CTestCase sigma_head_wall_volley_pools_cases[]
    = { ENTRY(0) ENTRY(1) ENTRY(2) ENTRY(3) ENTRY(4) ENTRY(5) };
static const u32 sigma_head_wall_volley_pools_cases_expected[] = { 0x40001u, 0x30028u, 0x30028u, 0x30028u, 0x1000028u, 0x1000028u };
#undef CASE
#undef ENTRY

static const u32 func_800AB050_expected[] = { 0u, 0xFFFFFFFEu };
static u32 test_func_800AB050(u32 row)
{
    u32 observed_values[2];
    struct ShotObj obj;
    struct MainObj child_0;
    u8 child_0_present;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&background_objects, 0, sizeof(background_objects));
    child_0_present = 255;
    obj.unk7 = -1;
    obj.unk7C = child_0_present ? &child_0 : NULL;
    func_800AB050(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk7;
    return c_test_observe(0, row, observed_values, func_800AB050_expected, 2);
}

static const u32 sigma_head_move_expected[] = { 0x40u, 9u, 0u, 0x498u, 0x2A8u };
static u32 test_sigma_head_move(u32 row)
{
    u32 observed_values[5];
    struct ShotObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk8C.bytes[2] = 4;
    obj.unk2 = 2;
    obj.unk8C.bytes[1] = 0;
    sigma_head_move(&obj);
    observed_values[0] = (u32)obj.unk15;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.x_pos.i.hi;
    observed_values[4] = (u32)obj.y_pos.i.hi;
    return c_test_observe(0, row, observed_values, sigma_head_move_expected, 5);
}

const struct CTestGroup c_test_groups[] = {
    { "sigma_head_formation_context", sigma_head_formation_context_cases, sigma_head_formation_context_cases_expected, COUNT(sigma_head_formation_context_cases), 0 },
    { "sigma_head_wall_volley_pools", sigma_head_wall_volley_pools_cases, sigma_head_wall_volley_pools_cases_expected, COUNT(sigma_head_wall_volley_pools_cases), 0 },
    { "func_800AB050", 0, 0, 1, test_func_800AB050 },
    { "sigma_head_move", 0, 0, 1, test_sigma_head_move },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sigma_head_formation_context_cases) + COUNT(sigma_head_wall_volley_pools_cases) + 1 + 1;
