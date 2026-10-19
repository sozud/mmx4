#include "test_runtime.h"
void func_800D0E48(struct MiscObj*);
static u32 metadata[2], archive[4];
static const u8 kinds[3] = { 0, 9, 11 }, frames[3] = { 0, 1, 14 };
static struct MiscObj pool_expected[64];
static u32 enter(u32 row)
{
    struct MiscObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 index = row % 3, free_slot = row / 3 % 2, fraction = row / 6, i;
    metadata[0] = 0x1DA;
    metadata[1] = 0x12345678;
    archive[0] = 8;
    archive[1] = 12;
    archive[2] = 0x13572468;
    archive[3] = 0x24681357;
    D_801406A8 = metadata;
    TEST_MENU_FRAMES = (u8*)archive;
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = i == 63 && free_slot ? 0 : 1;
        misc_objects[i].id = 63;
    }
    memcpy(pool_expected, misc_objects, sizeof(pool_expected));
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 45;
    obj.unk2 = kinds[index];
    obj.x_pos.val = 99 * 65536 + fraction * 0x1234;
    obj.y_pos.val = 101 * 65536 + fraction * 0x5678;
    expected = obj;
    expected.unk3C = (u8*)archive + 8;
    expected.unk42 = 0x7848;
    expected.bg_offset = -1;
    expected.ext.misc_45.direction = index == 2;
    expected.unk40 = 3;
    expected.state = 1;
    expected.x_pos.i.hi = index == 2 ? 440 : -120;
    expected.y_pos.i.hi = index == 2 ? 208 : 176;
    expected.ext.misc_45.unk58 = index == 2 ? 136 : 184;
    expected.ext.misc_45.target_x = index == 2 ? 152 : 160;
    expected.x_vel.val = index == 2 ? -14 * 65536 : 14 * 65536;
    expected.animation_step.fields.frame_index = frames[index];
    if (index == 2 && free_slot) {
        struct MiscObj* child = &pool_expected[63];
        child->active = 0x41;
        child->id = 45;
        child->unk2 = 21;
        child->x_pos = expected.x_pos;
        child->y_pos = expected.y_pos;
        child->ext.misc_45.owner = (struct MainObj*)&obj;
    }
    func_800D0E48(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(c_test_word_difference((u32*)misc_objects, (u32*)pool_expected, sizeof(pool_expected) / 4) == 0);
    assert(D_801406A8 == metadata && TEST_MENU_FRAMES == (u8*)archive && metadata[0] == 0x1DA && metadata[1] == 0x12345678 && archive[0] == 8 && archive[1] == 12 && archive[2] == 0x13572468 && archive[3] == 0x24681357);
    return 1;
}

void scripted_slider_update(struct MiscObj*);

static struct MiscObj slider;

static u32 snap(u32 row)
{
    static const s16 targets[] = { 0, 0x123, -0x80 };
    u32 hash;

    c_test_zero_words((u32*)&slider, sizeof(slider) / 4);
    engine_flags = 1;
    slider.active = 1;
    slider.id = 45;
    slider.state = 1;
    slider.unk5 = 4;
    slider.x_pos.val = 0x00456789;
    slider.y_pos.val = 0x00654321;
    slider.x_vel.val = 0x00012345;
    slider.y_vel.val = 0x00054321;
    slider.unk28 = 0x1000;
    slider.ext.misc_45.target_x = targets[row];
    scripted_slider_update(&slider);
    assert(slider.state == 1 && slider.unk5 == 2 && slider.on_screen == 1);
    hash = slider.x_pos.val;
    hash = hash * 31 + slider.y_pos.val;
    hash = hash * 31 + slider.x_vel.val;
    hash = hash * 31 + slider.y_vel.val;
    return hash * 31 + slider.unk28;
}

static u32 run(u32 row)
{
    static const u32 expected[3] = { 3147921735u, 1933867335u, 4213274951u };
    u32 hash = snap(row);
    return c_test_observe(0, row, &hash, &expected[row], 1);
}

const struct CTestGroup c_test_groups[] = {
    { "opening_late_title_and_US_extra_title_full_free_child_pool", NULL, NULL, 12, enter },
    { "step4_snaps_to_target", NULL, NULL, 3, run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 12 + 3;
