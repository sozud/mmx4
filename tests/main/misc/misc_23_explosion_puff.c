#include "test_runtime.h"
#include "main/misc/misc_23_explosion_puff.h"
#include "weapon_resources.h"

static s32 sprite_frames[8] = { 16, 20, 24, 28, 1, 2, 3, 4 };
static u32 puff_case(u32 mode)
{
    struct MiscObj obj, expected;
    struct BackgroundObj background_before[3];
    struct PlayerObj player_before = g_Player;
    u32 i, animation = mode & 1 ? 2 : 0;
    memset(&obj, 0, sizeof(obj));
    memcpy(background_before, background_objects, sizeof(background_before));
    obj.active = 0x41;
    obj.id = 23;
    obj.state = 0;
    obj.unk5 = 3;
    obj.unk6 = 4;
    obj.unk7 = mode >> 1;
    obj.bg_offset = -1;
    obj.unk16 = VISUAL_SATURN_LAYER(7);
    obj.unk17 = 5;
    obj.previous_animation_index = 6;
    obj.unk40 = 0x1234;
    obj.unk42 = 0x5678;
    obj.ext.unk.unk54 = animation;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    expected = obj;
    expected.on_screen = 1;
    expected.unk38 = NULL;
    expected.unk3C = (u8*)sprite_frames + 24;
    expected.animation_table = explosion_animations;
    expected.unk40 = WEAPON_TEXTURE_BASE;
    expected.unk42 = animation == 2 ? OBJECT_CLUT(0x7806) : OBJECT_CLUT(0x7805);
    if (obj.unk7 == 0)
        expected.unk16 = VISUAL_SATURN_LAYER(1);
    expected.unk17 = animation;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = explosion_animations[animation];
    expected.animation_step = *(union AnimationStep*)expected.animation_cursor;
    expected.state = 1;
    expected.unk7 = mode >> 1 ? 1 : 0;
    cur_random = mode >> 1 ? 1 : 119;
    TEST_SPRITE_FRAMES = (u8*)sprite_frames;
    explosion_puff_init(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(background_objects, background_before, sizeof(background_before));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    for (i = 0; i < 4; i++) {
        assert(sprite_frames[i] == 16 + i * 4);
        assert(sprite_frames[i + 4] == i + 1);
    }
    assert(SP_SPRITE_FRAMES == sprite_frames && cur_random == (mode >> 1 ? 1 : 376));
    return obj.unk42 | ((u32)(u8)obj.unk16 << 16) | ((u32)(u8)obj.unk7 << 24);
}
static const u32 explosion_puff_animation_start_cases_expected[] = {
    OBJECT_CLUT(0x7805) | 1u << 16,
    OBJECT_CLUT(0x7806) | 1u << 16,
    OBJECT_CLUT(0x7805) | (u32)(u8)VISUAL_SATURN_LAYER(7) << 16 | 1u << 24,
    OBJECT_CLUT(0x7806) | (u32)(u8)VISUAL_SATURN_LAYER(7) << 16 | 1u << 24,
};

struct explosion_puff_animate_case {
    u32 unk54;
    u32 expected[4];
};
static const struct explosion_puff_animate_case explosion_puff_animate_cases[] = {
    { 2, { 2u, 1u, 0u, 0u } },
    { 3, { 3u, 1u, 0u, 0u } },
};
static u32 test_explosion_puff_animate(u32 row)
{
    const struct explosion_puff_animate_case* c = &explosion_puff_animate_cases[row];
    u32 observed_values[4];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.animation_step.fields.relative_step = -1;
    obj.ext.unk.unk54 = c->unk54;
    explosion_puff_animate(&obj);
    observed_values[0] = (u32)obj.ext.unk.unk54;
    observed_values[1] = (u32)obj.on_screen;
    observed_values[2] = (u32)obj.x_vel.val;
    observed_values[3] = (u32)obj.y_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}
#undef main_bss_state


static u32 ep_step = C_TEST_STEP(5);
static u32 puff(u8 state, u8 rel, u8 size, u8 parity)
{
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    TEST_SPRITE_FRAMES = (u8*)sprite_frames;
    obj.active = 0x41;
    obj.state = state;
    obj.unk7 = parity;
    obj.x_pos.i.hi = 0x80;
    obj.y_pos.i.hi = 0x60;
    obj.x_vel.val = 0x10000;
    obj.ext.unk.unk54 = size;
    obj.animation_table = explosion_animations;
    obj.animation_cursor = (const u8*)&ep_step;
    obj.animation_step.packed = ep_step;
    obj.animation_step.fields.relative_step = rel;
    WEAPON_FRAME_COUNTER = 0;
    explosion_puff_update(&obj);
    return (u8)obj.active | (u32)obj.state << 8 | (u32)(u8)obj.on_screen << 16 | (u32)(u16)obj.x_pos.i.hi << 20;
}
static u32 ep_start(void) { return puff(0, 0, 0, 0); }
static u32 ep_done(void) { return puff(1, 0, 0, 0); }
static u32 ep_blink_hidden(void) { return puff(1, 1, 0, 1); }
static const CTestCase explosion_puff_steps_cases[] = {
    ep_start,
    ep_done,
    ep_blink_hidden,
};
static const u32 explosion_puff_steps_cases_expected[] = { 0x08010141u, 0x08100000u, 0x08100141u };

const struct CTestGroup c_test_groups[] = {
    { "explosion_puff_animation_start", NULL, explosion_puff_animation_start_cases_expected, COUNT(explosion_puff_animation_start_cases_expected), puff_case },
    { "explosion_puff_animate", 0, 0, 2, test_explosion_puff_animate },
    { "explosion_puff_steps", explosion_puff_steps_cases, explosion_puff_steps_cases_expected, COUNT(explosion_puff_steps_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(explosion_puff_animation_start_cases_expected) + 2 + COUNT(explosion_puff_steps_cases);
