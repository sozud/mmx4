#include "test_runtime.h"

#include "main/object_update.h"
void update_main_objects(void);
void update_weapon_objects(void);
void update_shot_objects(void);
void update_visual_objects(void);
void update_item_objects(void);
void update_layer_objects(void);
void func_80021C14(void);
void func_80021CC8(void);

static u8 dispatch_backref[4];
static struct ObjectHeader dispatch_quad_owner;
static u16 dispatch_messages[] = { 2, 0x800 };
static s8 dispatch_cursor[4] = { 0, 5, 0, 5 };

#define DISPATCH_WORD(o) \
    ((u8)(o).active | (u32)(u8)(o).state << 8 | (u32)(u8)(o).on_screen << 16 | (u32)(u8)(o).id << 24)

static void dispatch_place(void* object, u8 active, u8 id, u8 state, u8 shown)
{
    struct BaseObj* o = object;
    o->active = active;
    o->id = id;
    o->state = state;
    o->on_screen = shown;
    o->x_pos.i.hi = 0x1000;
    o->y_pos.i.hi = 0x1000;
}

static const u32 dispatch_expected[][12] = {
#include "object_dispatch_expected.inc"
};

static u32 test_object_dispatch(u32 row)
{
    static const u8 frozen[] = { 0, 1, 1, 1, 1 }, active[] = { 1, 1, 1, 9, 0 }, shown[] = { 0, 1, 0, 0, 1 };
    u32 seen[12];
    struct EffectObj* effect = &effect_objects[0];
    u8 f = frozen[row];
    memset(main_objects, 0, sizeof(main_objects));
    memset(weapon_objects, 0, sizeof(weapon_objects));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(effect_objects, 0, sizeof(effect_objects));
    memset(item_objects, 0, sizeof(item_objects));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(unk_objects, 0, sizeof(unk_objects));
    memset(g_QuadObjects, 0, sizeof(g_QuadObjects));
    memset(layer_objects, 0, sizeof(layer_objects));
    memset(foo_objects, 0, sizeof(foo_objects));
    memset(background_objects, 0, sizeof(background_objects));
    memset(&qux_object, 0, sizeof(qux_object));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&dispatch_quad_owner, 0, sizeof(dispatch_quad_owner));
    memset(dispatch_backref, 0, sizeof(dispatch_backref));
    engine_obj.unk10 = engine_obj.unk11 = engine_obj.unk12 = engine_obj.unk13 = engine_obj.unk14 = f;
    engine_obj.unk15 = engine_obj.unk16 = engine_obj.unk17 = engine_obj.unk18 = engine_obj.unk19 = f;
    dispatch_place(&main_objects[0], active[row], 2, 4, shown[row]);
    dispatch_place(&weapon_objects[0], active[row], 0, 3, shown[row]);
    weapon_objects[0].owner = &g_Player;
    g_Player.shot_count = 2;
    dispatch_place(&shot_objects[0], active[row], 1, 2, shown[row]);
    dispatch_place(&visual_objects[0], active[row], 3, 2, shown[row]);
    dispatch_place(effect, active[row], 3, 1, shown[row]);
    effect->ext.palette_animation.cursor = dispatch_cursor;
    effect->ext.palette_animation.timer = 4;
    dispatch_place(&item_objects[0], active[row], 0, 2, shown[row]);
    item_objects[0].backref = &dispatch_backref[1];
    dispatch_place(&misc_objects[0], active[row], 0, 2, shown[row]);
    misc_objects[0].backref = &dispatch_backref[2];
    dispatch_backref[2] = 0xFF;
    dispatch_place(&unk_objects[0], active[row], 1, 1, shown[row]);
    unk_objects[0].y_pos.i.hi = 0x10;
    unk_objects[0].bg_offset = -1;
    unk_objects[0].unk42 = 0x55;
    dispatch_place(&g_QuadObjects[0], active[row], 0, 2, shown[row]);
    g_QuadObjects[0].backref = &dispatch_quad_owner;
    dispatch_quad_owner.active = 1;
    dispatch_place(&layer_objects[0], active[row], 0, 2, shown[row]);
    layer_objects[0].backref = &dispatch_backref[3];
    dispatch_place(&qux_object, row == 0 ? 0 : active[row], 1, 2, shown[row]);
    foo_objects[0].x_pos.i.hi = 0x41;
    if (row == 1) {
        abc_object.unkC = 1;
        abc_object.unkA = 0x13;
    }
    update_main_objects();
    update_weapon_objects();
    update_shot_objects();
    update_visual_objects();
    update_effect_objects();
    update_item_objects();
    update_misc_objects();
#ifndef VERSION_DEMO
    update_unk_objects();
#endif
    update_quad_objects();
    update_layer_objects();
    func_80021C14();
    func_80021D20();
    func_80021CC8();
    seen[0] = DISPATCH_WORD(main_objects[0]);
    seen[1] = DISPATCH_WORD(weapon_objects[0]) ^ (u32)(u8)g_Player.shot_count << 28;
    seen[2] = DISPATCH_WORD(shot_objects[0]);
    seen[3] = DISPATCH_WORD(visual_objects[0]);
    seen[4] = DISPATCH_WORD(*effect) ^ (u32)(u8)effect->ext.palette_animation.timer << 28;
    seen[5] = DISPATCH_WORD(item_objects[0]) ^ (u32)dispatch_backref[1] << 24;
    seen[6] = DISPATCH_WORD(misc_objects[0]) ^ (u32)dispatch_backref[2] << 24;
    seen[7] = DISPATCH_WORD(unk_objects[0]) ^ (u32)(u8)unk_objects[0].unk42 << 24;
    seen[8] = DISPATCH_WORD(g_QuadObjects[0]) ^ (u32)dispatch_quad_owner.active << 28;
    seen[9] = DISPATCH_WORD(layer_objects[0]) ^ (u32)dispatch_backref[3] << 24;
    seen[10] = DISPATCH_WORD(qux_object);
    seen[11] = (u32)abc_object.unkC << 24 | (u32)(u16)abc_object.unkA | (u32)(u16)foo_objects[0].unk18.i.hi << 16;
#ifdef VERSION_DEMO
    {
        u32 expected[12];
        memcpy(expected, dispatch_expected[row], sizeof(expected));
        if (row == 1)
            expected[7] = 0x54010101u;
        return c_test_observe(0, row, seen, expected, 12);
    }
#else
    return c_test_observe(0, row, seen, dispatch_expected[row], 12);
#endif
}

static u32 test_dialogue_queue(u32 row)
{
    static u16 palette[0x400];
    u32 seen[3], i;
#ifdef VERSION_DEMO
    static const u32 expected[3] = { 0x00808000u, 0x00002700u, 0x00000100u };
#else
    static const u32 expected[3] = { 0x00800000u, 0x0000FF01u, 0x00000001u };
#endif
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = 1;
        misc_objects[i].id = 0x17;
    }
    TEST_PALETTE = (u8*)palette;
    TEST_ARC_48 = (u8*)dispatch_messages;
    engine_obj.stage = 2;
    abc_object.unk10 = (s16)0x8000;
    D_801397D8 = 0x27;
    need_palette_load = 0x20;
    D_801397BC = (struct MiscObj*)&misc_objects[3];
    func_80021D20();
    seen[0] = (u32)abc_object.unkC << 16 | (u16)abc_object.unk10;
    seen[1] = (u32)D_801397D8 << 8 | (u8)abc_object.unkF;
    seen[2] = (u32)(D_801397BC != NULL) << 8 | (need_palette_load & 1);
    return c_test_observe(0, row, seen, expected, 3);
}

static u32 test_mech_update_delay(u32 row)
{
    u32 seen[2];
    static const u32 expected[2] = { 0x01000201u, DEMO_ALT(0x00000000u, 0x00400000u) };
    memset(&qux_object, 0, sizeof(qux_object));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    dispatch_place(&qux_object, 1, 1, 2, 1);
    qux_object.collision_flags = 0x1234;
    qux_object.unk8A = 0x5678;
    g_Player.input.buttons.held = 0x40;
    g_Player.script_state = 3;
    g_Player.update_delay = 2;
    func_80021C14();
    seen[0] = DISPATCH_WORD(qux_object);
    seen[1] = (u32)qux_object.collision_flags << 16 | qux_object.unk8A;
    return c_test_observe(0, row, seen, expected, 2);
}

const struct CTestGroup c_test_groups[] = {
    { "object_dispatch", 0, 0, 5, test_object_dispatch },
    { "dialogue_queue", 0, 0, 1, test_dialogue_queue },
    { "mech_update_delay", 0, 0, 1, test_mech_update_delay },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 5 + 1 + 1;
