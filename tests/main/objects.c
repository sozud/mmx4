#include "test_runtime.h"
struct EffectObj* func_8002B468(s8, s8);

#define IDENTITY(prefix, type, pool)                               \
    static u32 allocators_##prefix##_identity(struct type* actual) \
    {                                                              \
        u32 i;                                                     \
        if (actual == NULL)                                        \
            return 0xFFFFFFFFu;                                    \
        for (i = 0; i < COUNT(pool); i++)                          \
            if (actual == &pool[i])                                \
                return i;                                          \
        return 0xFFFFFFFEu;                                        \
    }
#define ALLOC_CASE(prefix, suffix, type, pool, function, free1, free2) \
    static u32 allocators_##prefix##_##suffix(void)                    \
    {                                                                  \
        u32 i, identity;                                               \
        struct type* actual;                                           \
        for (i = 0; i < COUNT(pool); i++)                              \
            pool[i].active = 1;                                        \
        if (free1 >= 0)                                                \
            pool[free1].active = 0;                                    \
        if (free2 >= 0)                                                \
            pool[free2].active = 0;                                    \
        actual = function();                                           \
        identity = allocators_##prefix##_identity(actual);             \
        assert(identity != 0xFFFFFFFEu);                               \
        if (actual != NULL)                                            \
            assert(actual->active == 0);                               \
        return identity;                                               \
    }
#define ALLOCATOR(prefix, type, pool, function)                         \
    IDENTITY(prefix, type, pool)                                        \
    ALLOC_CASE(prefix, first, type, pool, function, 0, COUNT(pool) - 1) \
    ALLOC_CASE(prefix, last, type, pool, function, COUNT(pool) - 1, -1) \
    ALLOC_CASE(prefix, full, type, pool, function, -1, -1)

ALLOCATOR(MAIN, MainObj, main_objects, find_free_main_obj)
ALLOCATOR(WEAPON, WeaponObj, weapon_objects, find_free_weapon_obj)
ALLOCATOR(SHOT, ShotObj, shot_objects, find_free_shot_obj)
ALLOCATOR(VISUAL, VisualObj, visual_objects, find_free_visual_obj)
ALLOCATOR(EFFECT, EffectObj, effect_objects, find_free_effect_obj)
ALLOCATOR(ITEM, ItemObj, item_objects, find_free_item_obj)
ALLOCATOR(MISC, MiscObj, misc_objects, find_free_misc_obj)
ALLOCATOR(QUAD, QuadObj, g_QuadObjects, find_free_quad_obj)
ALLOCATOR(LAYER, LayerObj, layer_objects, find_free_layer_obj)
ALLOCATOR(UNK, UnkObj, unk_objects, find_free_unk_obj)

#define WALK_CASE(prefix, suffix, type, pool, function, previous, direction, free1, free2) \
    static u32 allocators_##prefix##_##suffix(void)                                        \
    {                                                                                      \
        u32 i, identity;                                                                   \
        struct type* actual;                                                               \
        struct type* start = previous < 0 ? NULL : &pool[previous];                        \
        for (i = 0; i < COUNT(pool); i++)                                                  \
            pool[i].active = 1;                                                            \
        if (free1 >= 0)                                                                    \
            pool[free1].active = 0;                                                        \
        if (free2 >= 0)                                                                    \
            pool[free2].active = 0;                                                        \
        actual = function(start, direction);                                               \
        identity = allocators_##prefix##_identity(actual);                                 \
        assert(identity != 0xFFFFFFFEu);                                                   \
        if (actual != NULL)                                                                \
            assert(actual->active == 0);                                                   \
        return identity;                                                                   \
    }
#define WALKER(prefix, type, pool, function)                                                                    \
    WALK_CASE(prefix, fwd_first, type, pool, function, -1, 0, 0, COUNT(pool) - 1)                               \
    WALK_CASE(prefix, fwd_last, type, pool, function, -1, 0, COUNT(pool) - 1, -1)                               \
    WALK_CASE(prefix, fwd_full, type, pool, function, -1, 0, -1, -1)                                            \
    WALK_CASE(prefix, fwd_next, type, pool, function, 0, 0, 0, 1)                                               \
    WALK_CASE(prefix, fwd_end, type, pool, function, COUNT(pool) - 1, 0, 0, -1)                                 \
    WALK_CASE(prefix, rev_last, type, pool, function, -1, 1, 0, COUNT(pool) - 1)                                \
    WALK_CASE(prefix, rev_first, type, pool, function, -1, 1, 0, -1)                                            \
    WALK_CASE(prefix, rev_full, type, pool, function, -1, 1, -1, -1)                                            \
    WALK_CASE(prefix, rev_previous, type, pool, function, COUNT(pool) - 1, 1, COUNT(pool) - 1, COUNT(pool) - 2) \
    WALK_CASE(prefix, rev_begin, type, pool, function, 0, 1, COUNT(pool) - 1, -1)
WALKER(MISC, MiscObj, misc_objects, func_8002AE90)
WALKER(VISUAL, VisualObj, visual_objects, func_8002AF4C)

#define ALLOC_ENTRY(prefix)         \
    allocators_##prefix##_first,    \
        allocators_##prefix##_last, \
        allocators_##prefix##_full,
#define WALK_ENTRY(prefix)                  \
    allocators_##prefix##_fwd_first,        \
        allocators_##prefix##_fwd_last,     \
        allocators_##prefix##_fwd_full,     \
        allocators_##prefix##_fwd_next,     \
        allocators_##prefix##_fwd_end,      \
        allocators_##prefix##_rev_last,     \
        allocators_##prefix##_rev_first,    \
        allocators_##prefix##_rev_full,     \
        allocators_##prefix##_rev_previous, \
        allocators_##prefix##_rev_begin,
static const CTestCase allocators_cases[] = {
    ALLOC_ENTRY(MAIN) ALLOC_ENTRY(WEAPON) ALLOC_ENTRY(SHOT)
        ALLOC_ENTRY(VISUAL) ALLOC_ENTRY(EFFECT) ALLOC_ENTRY(ITEM)
            ALLOC_ENTRY(MISC) ALLOC_ENTRY(QUAD) ALLOC_ENTRY(LAYER) ALLOC_ENTRY(UNK)
                WALK_ENTRY(MISC) WALK_ENTRY(VISUAL)
};
static const u32 allocators_cases_expected[] = { 0x0u, 0x2Fu, 0xFFFFFFFFu, 0x0u, 0xFu, 0xFFFFFFFFu, 0x0u, 0x1Fu, 0xFFFFFFFFu, 0x0u, 0x1Fu, 0xFFFFFFFFu, 0x0u, 0x1Fu, 0xFFFFFFFFu, 0x0u, 0x1Fu, 0xFFFFFFFFu, 0x0u, 0x3Fu, 0xFFFFFFFFu, 0x0u, 0x1Fu, 0xFFFFFFFFu, 0x0u, 0x3u, 0xFFFFFFFFu, 0x0u, 0x13u, 0xFFFFFFFFu, 0x0u, 0x3Fu, 0xFFFFFFFFu, 0x1u, 0xFFFFFFFFu, 0x3Fu, 0x0u, 0xFFFFFFFFu, 0x3Eu, 0xFFFFFFFFu, 0x0u, 0x1Fu, 0xFFFFFFFFu, 0x1u, 0xFFFFFFFFu, 0x1Fu, 0x0u, 0xFFFFFFFFu, 0x1Eu, 0xFFFFFFFFu };
#undef IDENTITY
#undef ALLOC_CASE
#undef ALLOCATOR
#undef WALK_CASE
#undef WALKER
#undef ALLOC_ENTRY
#undef WALK_ENTRY

static u32 identity(struct EffectObj* value)
{
    u32 i;
    if (value == NULL)
        return 0;
    for (i = 0; i < COUNT(effect_objects); i++)
        if (value == &effect_objects[i])
            return i + 1;
    assert(0);
    return ~0u;
}
static u32 unchanged(const void* after, const void* before, u32 size)
{
    const u32* a = after;
    const u32* b = before;
    u32 i;
    for (i = 0; i < size / 4; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}
#define SEARCH_CASE(name, query, active_value, object_id, subtype, slot)                         \
    static u32 name(void)                                                                        \
    {                                                                                            \
        u32 i, actual;                                                                           \
        struct EffectObj* found;                                                                 \
        struct EffectObj before[0x20];                                                           \
        memset(effect_objects, 0, sizeof(effect_objects));                                       \
        for (i = 0; i < COUNT(effect_objects); i++) {                                            \
            effect_objects[i].active = active_value;                                             \
            effect_objects[i].id = object_id;                                                    \
            effect_objects[i].unk2 = subtype;                                                    \
        }                                                                                        \
        if (slot >= 0) {                                                                         \
            effect_objects[slot].active = 1;                                                     \
            effect_objects[slot].id = 7;                                                         \
        }                                                                                        \
        memcpy(before, effect_objects, sizeof(before));                                          \
        if (slot < 0) {                                                                          \
            (void)func_8002B468(query, 3);                                                       \
            found = NULL;                                                                        \
        } else {                                                                                 \
            found = func_8002B468(query, 3);                                                     \
        }                                                                                        \
        assert(sizeof(before) % 4 == 0);                                                         \
        assert(unchanged(effect_objects, before, sizeof(before)));                               \
        for (i = 0; i < COUNT(effect_objects); i++) {                                            \
            assert(effect_objects[i].active == ((s32)i == slot ? 1 : active_value));             \
            assert(effect_objects[i].id == ((s32)i == slot ? 7 : object_id));                    \
            assert(effect_objects[i].unk2 == subtype);                                           \
        }                                                                                        \
        actual = slot < 0 ? unchanged(effect_objects, before, sizeof(before)) : identity(found); \
        return actual;                                                                           \
    }
SEARCH_CASE(first_exact, 7, 0, 0, 3, 0)
SEARCH_CASE(last_exact, 7, 0, 0, 3, 31)
SEARCH_CASE(last_ignore_subtype, -121, 0, 0, 4, 31)
SEARCH_CASE(inactive, 7, 0, 7, 3, -1)
SEARCH_CASE(wrong_id, 7, 1, 8, 3, -1)
SEARCH_CASE(wrong_subtype, 7, 1, 7, 4, -1)
SEARCH_CASE(negative_inactive, -121, 0, 7, 3, -1)
SEARCH_CASE(negative_wrong_id, -121, 1, 8, 3, -1)

#define ENTRY(name) name,
static const CTestCase effect_search_cases[] = {
    ENTRY(first_exact)
        ENTRY(last_exact)
            ENTRY(last_ignore_subtype)
                ENTRY(inactive)
                    ENTRY(wrong_id)
                        ENTRY(wrong_subtype)
                            ENTRY(negative_inactive)
                                ENTRY(negative_wrong_id)
};
static const u32 effect_search_cases_expected[] = { 0x1u, 0x20u, 0x20u, 0x1u, 0x1u, 0x1u, 0x1u, 0x1u };
#undef SEARCH_CASE
#undef ENTRY

static const u32 func_8002B1E8_expected[] = { 1u };
static u32 test_func_8002B1E8(u32 row)
{
    u32 observed_values[1];
    struct BaseObj obj;
    s32 return_value;
    s32 x_offset;
    s32 y_offset;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.bg_offset = -128;
    obj.x_pos.u.hi = 32924;
    x_offset = 32608;
    y_offset = 0;
    return_value = func_8002B1E8(&obj, x_offset, y_offset);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, func_8002B1E8_expected, 1);
}

static const u32 func_8002B3C0_expected[] = { 0u };
static u32 test_func_8002B3C0(u32 row)
{
    u32 observed_values[1];
    struct BaseObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.bg_offset = -128;
    obj.x_pos.i.hi = 32672;
    func_8002B3C0(&obj);
    observed_values[0] = (u32)obj.on_screen;
    return c_test_observe(0, row, observed_values, func_8002B3C0_expected, 1);
}

const struct CTestGroup c_test_groups[] = {
    { "allocators", allocators_cases, allocators_cases_expected, COUNT(allocators_cases), 0 },
    { "effect_search", effect_search_cases, effect_search_cases_expected, COUNT(effect_search_cases), 0 },
    { "func_8002B1E8", 0, 0, 1, test_func_8002B1E8 },
    { "func_8002B3C0", 0, 0, 1, test_func_8002B3C0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(allocators_cases) + COUNT(effect_search_cases) + 1 + 1;
