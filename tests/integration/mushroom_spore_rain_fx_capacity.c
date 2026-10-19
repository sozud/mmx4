#include "test_runtime.h"
#include "main/mains/main_61_split_mushroom.h"
#include "main/55C4.h"
void split_mushroom_fx_main(struct VisualObj*);
extern void* split_mushroom_animations[26];
extern void spore_rain_fx_update(struct MiscObj*);
static struct VisualObj visuals_expected[32];
static struct MiscObj misc_expected[64];
static u32 rain(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct BackgroundObj backgrounds_before[3];
    u32 visual = row % 2, misc = row / 2 % 2, layer = row / 4, i;
    engine_obj.stage = 3;
    engine_obj.substage = 1;
    engine_before = engine_obj;
    g_Player.bg_offset = layer;
    player_before = g_Player;
    memset(background_objects, 0, sizeof(background_objects));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < COUNT(visual_objects); i++)
        visual_objects[i].active = i == 31 && visual ? 0 : 1;
    memcpy(visuals_expected, visual_objects, sizeof(visuals_expected));
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++)
        misc_objects[i].active = i == 63 && misc ? 0 : 1;
    memcpy(misc_expected, misc_objects, sizeof(misc_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 61;
    obj.state = 1;
    obj.hp = 48;
    obj.ext.main_61.stunned = 1;
    obj.unk5 = 3;
    obj.unk6 = 1;
    obj.bg_offset = layer;
    obj.animation_table = (const u8* const*)split_mushroom_animations;
    obj.x_pos.i.hi = 160;
    obj.y_pos.val = 360 * 65536 - 47 * 0x85C00 + 0x3800 * 47 * 46 / 2;
    obj.y_speed = 0x85C00 - 47 * 0x3800;
    obj.gravity = 0x3800;
    obj.unk7C = 1;
    obj.unk40 = 7;
    obj.unk42 = 0x78C0;
    set_animation(&obj, 3);
    expected = obj;
    expected.y_pos.val -= obj.y_speed;
    expected.y_speed -= 0x3800;
    expected.unk7C = 240;
    expected.unk6 = 2;
    expected.unk17 = 4;
    expected.animation_cursor = split_mushroom_animations[4];
    expected.animation_step.packed = 0x0F010003;
    if (visual) {
        struct VisualObj* v = &visuals_expected[31];
        v->active = 0x41;
        v->id = 34;
        v->x_pos.i.hi = -16;
        v->y_pos.i.hi = -32;
        v->bg_offset = layer;
        v->animation_table = (u32**)obj.animation_table;
        v->unk40 = 7;
        v->unk42 = 0x78C0;
        v->unk16 = 0x13;
        v->unk50 = PLAYER_OBJECT(&obj);
        v->unk5C.fields.unk5E = 260;
        v->unk17 = 14;
        v->previous_animation_index = 255;
        v->animation_cursor = split_mushroom_animations[14];
        v->animation_step.packed = 0x38010004;
    }
    if (misc) {
        struct MiscObj* m = &misc_expected[63];
        m->active = 0x41;
        m->id = 30;
        m->x_pos.i.hi = 48;
        m->y_pos.i.hi = -32;
        m->bg_offset = layer;
        m->animation_table = (u32**)obj.animation_table;
        m->unk40 = 7;
        m->unk42 = 0x78C0;
        m->unk16 = 0x13;
        m->ext.misc_30.owner = &obj;
        m->ext.misc_30.unk56 = 260;
        m->unk17 = 14;
        m->previous_animation_index = 255;
        m->animation_cursor = split_mushroom_animations[14];
        m->animation_step.packed = 0x38010004;
    }
    func_80079B50(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(visual_objects, visuals_expected, sizeof(visuals_expected));
    c_test_same_words(misc_objects, misc_expected, sizeof(misc_expected));
    obj.state = expected.state = 2;
    if (visual) {
        visuals_expected[31].active = visuals_expected[31].id = 0;
        split_mushroom_fx_main(&visual_objects[31]);
    }
    if (misc) {
        misc_expected[63].active = misc_expected[63].id = 0;
        spore_rain_fx_update(&misc_objects[63]);
    }
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(visual_objects, visuals_expected, sizeof(visuals_expected));
    c_test_same_words(misc_objects, misc_expected, sizeof(misc_expected));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(background_objects, backgrounds_before, sizeof(backgrounds_before));
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "own_spore_rain_jump_full_last_child_slots_and_real_owner_death", NULL, NULL, 12, rain } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 12;
