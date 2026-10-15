#include "test_runtime.h"
void train_scroll_update_section(struct LayerObj*);

static u32 event_case(u32 section, u32 mode)
{
    struct LayerObj obj, before;
    struct MainObj pool_before[48];
    struct BackgroundObj background_before[3];
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(main_objects, 0, sizeof(main_objects));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < 48; i++) {
        main_objects[i].active = 1;
        main_objects[i].id = 0x27;
        main_objects[i].state = 0x28;
    }
    if (mode == 2)
        main_objects[17].active = 0;
    obj.active = 0x41;
    obj.id = 0;
    obj.state = 1;
    obj.bg_offset = section;
    obj.unk6 = 0x25;
    obj.unk7 = 0;
    background_objects[0].x_pos.i.hi = mode == 0 ? 99 : 100;
    background_objects[0].unk26 = 100;
    before = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(pool_before, main_objects, sizeof(pool_before));
    memcpy(background_before, background_objects, sizeof(background_before));
    if (section == 3)
        train_scroll_section_3_event(&obj);
    else
        train_scroll_section_4_event(&obj);
    if (mode != 0)
        before.unk7 = 1;
    if (mode == 2) {
        pool_before[17].active = 0x41;
        pool_before[17].id = 0x22;
        pool_before[17].unk2 = section - 1;
        pool_before[17].backref = &obj;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)main_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(background_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)background_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    return (u8)obj.unk7 | ((u32)main_objects[17].id << 8) | ((u32)main_objects[17].unk2 << 16);
}
#define CASE(s, m)                                              \
    static u32 train_scroll_event_context_event_##s##_##m(void) \
    {                                                           \
        return event_case(s, m);                                \
    }
CASE(3, 0)
CASE(3, 1)
CASE(3, 2)
CASE(4, 0)
CASE(4, 1)
CASE(4, 2)
#define ENTRY(s, m) train_scroll_event_context_event_##s##_##m,
static const CTestCase train_scroll_event_context_cases[]
    = { ENTRY(3, 0) ENTRY(3, 1) ENTRY(3, 2) ENTRY(4, 0) ENTRY(4, 1) ENTRY(4, 2) };
static const u32 train_scroll_event_context_cases_expected[] = { 0x2700u, 0x2701u, 0x22201u, 0x2700u, 0x2701u, 0x32201u };
#undef CASE
#undef ENTRY

static const u32 train_scroll_player_at_lock_expected[] = { 0u };
static u32 test_train_scroll_player_at_lock(u32 row)
{
    u32 observed_values[1];
    struct LayerObj obj;
    u8 return_value;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.bg_offset = 4;
    return_value = train_scroll_player_at_lock(&obj);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, train_scroll_player_at_lock_expected, 1);
}

static const u32 train_scroll_spawn_trooper_expected[] = { 1u, 0u, 0u, 1u };
static u32 test_train_scroll_spawn_trooper(u32 row)
{
    u32 observed_values[4];
    struct LayerObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&main_objects, 0, sizeof(main_objects));
    pool_0_full = 255;
    {
        u32 slot;
        for (slot = 0; slot < 48; ++slot)
            main_objects[slot].active = pool_0_full ? 1 : 0;
    }
    train_scroll_spawn_trooper(&obj);
    observed_values[0] = (u32)main_objects[0].active;
    observed_values[1] = (u32)main_objects[0].id;
    observed_values[2] = (u32)main_objects[0].unk2;
    observed_values[3] = (u32)obj.unk7;
    return c_test_observe(0, row, observed_values, train_scroll_spawn_trooper_expected, 4);
}

static const u32 train_scroll_update_section_expected[] = { 4u, 4u, 0u };
static u32 test_train_scroll_update_section(u32 row)
{
    u32 observed_values[3];
    struct LayerObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.i.hi = 7168;
    train_scroll_update_section(&obj);
    observed_values[0] = (u32)obj.bg_offset;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    return c_test_observe(0, row, observed_values, train_scroll_update_section_expected, 3);
}

#include "support/train_sections.h"
SECTION_CASE(0)
SECTION_CASE(1)
SECTION_CASE(2)
SECTION_CASE(3)
SECTION_CASE(4)
SECTION_CASE(5)
SECTION_CASE(6)
static const CTestCase train_scroll_sections_cases[] = { SECTION_ENTRY(0) SECTION_ENTRY(1) SECTION_ENTRY(2) SECTION_ENTRY(3) SECTION_ENTRY(4) SECTION_ENTRY(5) SECTION_ENTRY(6) };

static const u32 train_scroll_sections_cases_expected[] = { 0x4u, 0x104u, 0x4u, 0x10104u, 0x104u, 0x10104u, 0x4u };
const struct CTestGroup c_test_groups[] = {
    { "train_scroll_event_context", train_scroll_event_context_cases, train_scroll_event_context_cases_expected, COUNT(train_scroll_event_context_cases), 0 },
    { "train_scroll_player_at_lock", 0, 0, 1, test_train_scroll_player_at_lock },
    { "train_scroll_spawn_trooper", 0, 0, 1, test_train_scroll_spawn_trooper },
    { "train_scroll_update_section", 0, 0, 1, test_train_scroll_update_section },
    { "train_scroll_sections", train_scroll_sections_cases, train_scroll_sections_cases_expected, COUNT(train_scroll_sections_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(train_scroll_event_context_cases) + 1 + 1 + 1 + COUNT(train_scroll_sections_cases);
