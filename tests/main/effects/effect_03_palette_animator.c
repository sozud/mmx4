#include "test_runtime.h"
#include "main/effects/effect_03_palette_animator.h"
#ifdef MMX4_SATURN
#include "saturn/game_low.h"
#define ANIMATION_SOURCE SATURN_PALETTE_ANIMATION_SOURCE
#else
#define ANIMATION_SOURCE ((s32*)animation_source)
#endif

extern s8** palette_animator_stage_scripts[27];
extern s8 D_800F493C[];
static s32 palette[0x80 * 8], animation_source[0x20 * 8];
static struct EffectObj pa;
static void pa_reset(u8 state)
{
    u32 i;
    memset(&pa, 0, sizeof(pa));
    memset(palette, 0, sizeof(palette));
    memset(&engine_obj, 0, sizeof(engine_obj));
    for (i = 0; i < COUNT(animation_source); i++)
        animation_source[i] = 0x5A000000 + i;
    TEST_PALETTE = (u8*)palette;
    TEST_ARC_30 = (u8*)animation_source;
    need_palette_load = 0;
    pa.active = 1;
    pa.id = 3;
    pa.state = state;
    pa.unk2 = 1;
    pa.ext.palette_animation.destination = &palette[0x6B * 8];
    pa.ext.palette_animation.palette_count = 1;
}
static u32 copied(s32 entry)
{
    u32 i;
    for (i = 0; i < COUNT(palette); i++)
        assert(palette[i] == (entry >= 0 && i / 8 == 0x6B ? ANIMATION_SOURCE[entry * 8 + i % 8] : 0));
    return need_palette_load;
}
#define PA_SEEN() ((u32)(pa.ext.palette_animation.cursor - D_800F493C) | (u32)(u8)pa.ext.palette_animation.timer << 8 | (u32)pa.state << 16)
static u32 pa_start(void)
{
    pa_reset(0);
    palette_animator_update(&pa);
    assert(pa.ext.palette_animation.cursor == palette_animator_stage_scripts[0][1] && pa.ext.palette_animation.palette_count == 1);
    assert(pa.ext.palette_animation.destination == &palette[0x6B * 8] && pa.ext.palette_animation.source == ANIMATION_SOURCE + 12 * 8);
    return PA_SEEN() | copied(12) << 24;
}
static u32 pa_hold(void)
{
    pa_reset(1);
    pa.ext.palette_animation.cursor = D_800F493C;
    pa.ext.palette_animation.timer = 5;
    palette_animator_update(&pa);
    return PA_SEEN() | copied(-1) << 24;
}
static u32 pa_next(void)
{
    pa_reset(1);
    pa.ext.palette_animation.cursor = D_800F493C;
    palette_animator_update(&pa);
    return PA_SEEN() | copied(13) << 24;
}
static u32 pa_loop(void)
{
    pa_reset(1);
    pa.ext.palette_animation.cursor = D_800F493C + 10;
    palette_animator_update(&pa);
    return PA_SEEN() | copied(12) << 24;
}
static const CTestCase palette_animator_steps_cases[] = {
    pa_start,
    pa_hold,
    pa_next,
    pa_loop,
};
static const u32 palette_animator_steps_cases_expected[] = { 0x1011000u, 0x10400u, 0x1011002u, 0x1011000u };

const struct CTestGroup c_test_groups[] = {
    { "palette_animator_steps", palette_animator_steps_cases, palette_animator_steps_cases_expected, COUNT(palette_animator_steps_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(palette_animator_steps_cases);
