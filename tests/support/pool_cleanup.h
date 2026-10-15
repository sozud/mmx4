#ifndef MMX4_TESTS_POOL_CLEANUP_H
#define MMX4_TESTS_POOL_CLEANUP_H

static u32 zero_words(const void* data, u32 size)
{
    const u32* words = data;
    u32 i;
    for (i = 0; i < size / 4; i++)
        if (words[i] != 0)
            return 0;
    return 1;
}

static u32 same_words(const void* data, const void* before, u32 size)
{
    const u32* a = data;
    const u32* b = before;
    u32 i;
    for (i = 0; i < size / 4; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

#define CLEANUP_DELETE_CASE(name, match_lane, expected)                                                   \
    static u32 name(void)                                                                                 \
    {                                                                                                     \
        struct ItemObj before[0x20];                                                                      \
        u32 i, actual = 1;                                                                                \
        memset(item_objects, 0x5A, sizeof(item_objects));                                                 \
        for (i = 0; i < COUNT(item_objects); i++) {                                                       \
            item_objects[i].id = (i % 3 == 1) ? 0x12 : 0x11;                                              \
            item_objects[i].unk2 = (i % 3 == 2) ? 8 : 7;                                                  \
        }                                                                                                 \
        item_objects[COUNT(item_objects) - 1].id = 0x11;                                                  \
        item_objects[COUNT(item_objects) - 1].unk2 = 7;                                                   \
        memcpy(before, item_objects, sizeof(before));                                                     \
        delete_items(0x111, 0x107);                                                                       \
        for (i = 0; i < COUNT(item_objects); i++) {                                                       \
            u32 matches = (before[i].id == 0x11 && before[i].unk2 == 7);                                  \
            if (matches == match_lane) {                                                                  \
                u32 result = matches ? zero_words(&item_objects[i], sizeof(item_objects[i]))              \
                                     : same_words(&item_objects[i], &before[i], sizeof(item_objects[i])); \
                assert(result == expected);                                                               \
                actual &= result;                                                                         \
            }                                                                                             \
        }                                                                                                 \
        assert(actual == expected);                                                                       \
        return actual;                                                                                    \
    }

#define CLEANUP_OWL_CASE(name, match_lane, expected)                                                      \
    static u32 name(void)                                                                                 \
    {                                                                                                     \
        struct ShotObj before[0x20];                                                                      \
        u32 i, actual = 1;                                                                                \
        memset(shot_objects, 0x5A, sizeof(shot_objects));                                                 \
        for (i = 0; i < COUNT(shot_objects); i++) {                                                       \
            shot_objects[i].id = i % 6 == 0 ? 0x25 : 1;                                                   \
            shot_objects[i].unk2 = i % 6 == 5 ? -1 : i % 6;                                               \
        }                                                                                                 \
        shot_objects[COUNT(shot_objects) - 1].id = 0x25;                                                  \
        memcpy(before, shot_objects, sizeof(before));                                                     \
        storm_owl_clear_shots();                                                                          \
        for (i = 0; i < COUNT(shot_objects); i++) {                                                       \
            u32 matches = before[i].id == 0x25 || (before[i].unk2 != 0 && before[i].unk2 <= 4);           \
            if (matches == match_lane) {                                                                  \
                u32 result = matches ? zero_words(&shot_objects[i], sizeof(shot_objects[i]))              \
                                     : same_words(&shot_objects[i], &before[i], sizeof(shot_objects[i])); \
                assert(result == expected);                                                               \
                actual &= result;                                                                         \
            }                                                                                             \
        }                                                                                                 \
        assert(actual == expected);                                                                       \
        return actual;                                                                                    \
    }
#endif
