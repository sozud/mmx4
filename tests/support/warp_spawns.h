#ifndef MMX4_TESTS_WARP_SPAWNS_H
#define MMX4_TESTS_WARP_SPAWNS_H

static void reset_pool(u32 full)
{
    u32 i;
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    if (full)
        for (i = 0; i < COUNT(misc_objects); i++)
            misc_objects[i].active = 1;
}
static void check_other_slots(u32 full)
{
    u32 i;
    for (i = 1; i < COUNT(misc_objects); i++) {
        assert(misc_objects[i].active == full);
        assert(misc_objects[i].id == 0 && misc_objects[i].unk2 == 0);
    }
}

#define WARP_TRIAL_CASE(name, enabled, subtype, stage, rank_value, full)         \
    static u32 name(void)                                                        \
    {                                                                            \
        struct EffectObj obj;                                                    \
        u32 actual;                                                              \
        memset(&obj, 0, sizeof(obj));                                            \
        reset_pool(full);                                                        \
        obj.ext.effect_38.active = enabled;                                      \
        obj.ext.effect_38.variant = rank_value;                                  \
        obj.unk2 = subtype;                                                      \
        engine_obj.substage = stage;                                             \
        cyberspace_trial_spawn_rank_warp(&obj);                                  \
        if (misc_objects[0].active == 0x41) {                                    \
            assert(misc_objects[0].id == 0x21);                                  \
            assert(misc_objects[0].ext.misc_7.position == &obj);                 \
        }                                                                        \
        assert(obj.ext.effect_38.active == enabled && obj.unk2 == subtype);      \
        check_other_slots(full);                                                 \
        actual = (u8)misc_objects[0].active | ((u32)(u8)misc_objects[0].id << 8) \
            | ((u32)(u8)misc_objects[0].unk2 << 16)                              \
            | ((u32)(misc_objects[0].ext.misc_7.position == &obj) << 24);        \
        return actual;                                                           \
    }

#define WARP_BOSS_CASE(name, uncleared, full)                                         \
    static u32 name(void)                                                             \
    {                                                                                 \
        struct ItemObj obj;                                                           \
        u32 frame = 0x04010302;                                                       \
        u32* table[2] = { &frame, &frame };                                           \
        u32 i, actual;                                                                \
        memset(&obj, 0, sizeof(obj));                                                 \
        reset_pool(full);                                                             \
        for (i = 8; i < 16; i++)                                                      \
            engine_obj.character_state.bytes[i] = 1;                                  \
        if (uncleared)                                                                \
            engine_obj.character_state.bytes[uncleared] = 0;                          \
        obj.unk5 = 7;                                                                 \
        obj.x_pos.i.hi = 101;                                                         \
        obj.y_pos.i.hi = -70;                                                         \
        obj.animation_table = table;                                                  \
        obj.animation_cursor = &frame;                                                \
        obj.animation_step.packed = frame;                                            \
        boss_teleporter_wait_bosses_cleared(&obj);                                    \
        assert(obj.animation_cursor == &frame && obj.animation_step.packed == frame); \
        if (misc_objects[0].active == 0x41) {                                         \
            assert(misc_objects[0].id == 0x33 && misc_objects[0].unk2 == 0);          \
            assert(misc_objects[0].x_pos.val == obj.x_pos.val);                       \
            assert(misc_objects[0].y_pos.val == obj.y_pos.val);                       \
            assert((void*)misc_objects[0].ext.misc_51.source == &obj);                \
            assert(obj.unk7C.misc == &misc_objects[0]);                               \
        }                                                                             \
        check_other_slots(full);                                                      \
        actual = (u8)obj.unk5 | ((u32)obj.unk17 << 8)                                 \
            | ((u32)(u8)misc_objects[0].active << 16)                                 \
            | ((u32)(obj.unk7C.misc == &misc_objects[0]) << 24);                      \
        return actual;                                                                \
    }

#define WARP_ENTRY(name) name,
#endif
