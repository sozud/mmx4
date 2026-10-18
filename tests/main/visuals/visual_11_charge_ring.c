#include "test_runtime.h"
#include "main/visuals/visual_11_charge_ring.h"
#include "main/mains/main_14_ice_bird.h"

static u32 ring_case(u32 mode)
{
    struct VisualObj obj, expected;
    struct MainObj parent, parent_expected;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    u32 i, start = mode == 9 ? 6 : 3;
    s32 variant = mode == 5 || mode == 7 ? 0xFF : mode == 4 ? 7
        : mode >= 1 && mode <= 3 || mode == 9               ? 6
                                                            : 3;
    memset(&obj, 0, sizeof(obj));
    memset(&parent, 0, sizeof(parent));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    parent.active = mode == 7 || mode == 8 ? 0 : 0x41;
    parent.id = 43;
    parent.state = mode == 6 ? 2 : 1;
    parent.unk5 = mode == 1 ? 1 : mode == 2 ? 2
        : mode == 3 || mode == 4            ? 3
                                            : 0;
    parent.ext.main_14.visual_variant = variant;
    parent.x_pos.val = 100 * 65536 + 0x1234;
    parent.y_pos.val = 100 * 65536 + 0x5678;
    obj.active = 0x41;
    obj.id = 11;
    obj.state = 1;
    obj.unk2 = start;
    obj.bg_offset = -1;
    obj.on_screen = 0;
    obj.unk50 = PLAYER_OBJECT(&parent);
    obj.x_pos.val = 50 * 65536 + 0xABCD;
    obj.y_pos.val = 60 * 65536 + 0xFEDC;
    obj.animation_table = (u32**)ice_bird_animations;
    ANIMATED_OBJECT(&obj)->animation_cursor = (u32*)ice_bird_animations[start];
    obj.animation_step = ice_bird_animations[start][0];
    obj.unk17 = start;
    obj.previous_animation_index = 0x27;
    expected = obj;
    parent_expected = parent;
    if (parent.active)
        parent_expected.id = 14;
    else
        expected.state++;
    if (mode == 5 || mode == 6 || mode == 7) {
        expected.state++;
    } else {
        if (mode == 3 || mode == 4) {
            expected.unk2 = variant;
            expected.unk17 = variant;
            expected.previous_animation_index = 0xFF;
            ANIMATED_OBJECT(&expected)->animation_cursor = (u32*)ice_bird_animations[variant];
            expected.animation_step = ice_bird_animations[variant][0];
        }
        if (mode == 3 || mode == 9) {
            ANIMATED_OBJECT(&expected)->animation_cursor = (u32*)(ice_bird_animations[6] + 1);
            expected.animation_step = ice_bird_animations[6][1];
        } else
            expected.animation_step.fields.duration--;
        expected.x_pos.i.hi = 100;
        expected.y_pos.i.hi = 100;
        if (mode == 1)
            expected.y_pos.i.hi = 95;
        else if (mode == 2 || mode == 3 || mode == 4) {
            expected.x_pos.i.hi = 98;
            expected.y_pos.i.hi = 90;
        }
        expected.on_screen = 1;
    }
    func_800B1864(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(parent) / 4; i++)
        assert(((u32*)&parent)[i] == ((u32*)&parent_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    return obj.state | ((u32)(u8)obj.unk2 << 8) | ((u32)obj.animation_step.fields.duration << 16);
}
static const u32 charge_ring_parent_animation_context_cases_expected[] = { 0x50301u, 0x50301u, 0x50301u, 0x10601u, 0x20701u, 0x60302u, 0x60302u, 0x60303u, 0x50302u, 0x10601u };

const struct CTestGroup c_test_groups[] = {
    { "charge_ring_parent_animation_context", NULL, charge_ring_parent_animation_context_cases_expected, COUNT(charge_ring_parent_animation_context_cases_expected), ring_case },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(charge_ring_parent_animation_context_cases_expected);
