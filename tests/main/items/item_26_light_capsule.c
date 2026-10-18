#include "test_runtime.h"
#include "main/items/item_26_light_capsule.h"
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
#define CASE(m, n)                                                     \
    static u32 capsule_visual_animation_context_visual_##m##_##n(void) \
    {                                                                  \
        return visual_case(m, n);                                      \
    }
#define MODE(m) CASE(m, 0) CASE(m, 1) CASE(m, 2)
MODE(0)
MODE(1)
MODE(2)
MODE(3)
MODE(4)
#define ENTRY(m, n) capsule_visual_animation_context_visual_##m##_##n,
#define ENTRIES(m) ENTRY(m, 0) ENTRY(m, 1) ENTRY(m, 2)
static const CTestCase capsule_visual_animation_context_cases[]
    = { ENTRIES(0) ENTRIES(1) ENTRIES(2) ENTRIES(3) ENTRIES(4) };
static const u32 capsule_visual_animation_context_cases_expected[] = { 0x1D010002u, 0x13572468u, 0x20303u, 0x1B010002u, 0x13572468u, 0x70103u, 0x1E010001u, 0x13572468u, 0x80003u, 0x2C010001u, 0x13572468u, 0x90003u, 0x0u, 0x13572468u, 0x2503u };
#undef CASE
#undef MODE
#undef ENTRY
#undef ENTRIES

static const u32 capsule_visual_init_expected[] = { 1u, 1u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };
static u32 test_capsule_visual_init(u32 row)
{
    u32 observed_values[9];
    struct VisualObj obj;
    struct PlayerObj argument_obj_1;
    memset(&obj, 0, sizeof(obj));
    memset(&argument_obj_1, 0, sizeof(argument_obj_1));
    capsule_visual_init(&obj, &argument_obj_1);
    observed_values[0] = (u32)obj.on_screen;
    observed_values[1] = (u32)obj.state;
    observed_values[2] = (u32)obj.unk15;
    observed_values[3] = (u32)obj.unk16;
    observed_values[4] = (u32)obj.unk40;
    observed_values[5] = (u32)obj.unk42;
    observed_values[6] = (u32)obj.unk5;
    observed_values[7] = (u32)obj.x_pos.val;
    observed_values[8] = (u32)obj.y_pos.val;
    return c_test_observe(0, row, observed_values, capsule_visual_init_expected, 9);
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
const struct CTestGroup c_test_groups[] = {
    { "capsule_visual_animation_context", capsule_visual_animation_context_cases, capsule_visual_animation_context_cases_expected, COUNT(capsule_visual_animation_context_cases), 0 },
    { "capsule_visual_init", 0, 0, 1, test_capsule_visual_init },
    { "func_800C6EDC", 0, 0, 3, test_func_800C6EDC },
    { "light_capsule_wait_player", 0, 0, 1, test_light_capsule_wait_player },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(capsule_visual_animation_context_cases) + 1 + 3 + 1 + COUNT(pool_full_cases);
