#include "test_runtime.h"
#ifndef VERSION_DEMO
#include "main/visuals/visual_05_object_afterimage.h"

static struct PlayerObj ai_owner;
static struct VisualObj ai;
static u32 afterimage(u8 step, s8 flag, u8 part)
{
    memset(&ai_owner, 0, sizeof(ai_owner));
    memset(&ai, 0, sizeof(ai));
    ai_owner.x_pos.i.hi = 0x90;
    ai_owner.y_pos.i.hi = 0x70;
    ai_owner.pad4B[0] = flag;
    ai.active = 1;
    ai.id = 5;
    ai.state = 1;
    ai.unk5 = step;
    ai.unk2 = part;
    ai.on_screen = 1;
    ai.x_pos.i.hi = 0x80;
    ai.y_pos.i.hi = 0x60;
    ai.unk50 = &ai_owner;
    ai.unk5C.owner = &ai_owner;
    object_afterimage_update(&ai);
    return ai.state | (u32)ai.unk5 << 8 | (u32)(u8)ai_owner.pad4B[0] << 16 | (u32)(u8)ai.x_pos.i.hi << 24;
}
static u32 ai_restart(void)
{
    u32 seen = afterimage(1, 1, 1);
    assert(ai.unk54 == 3 && ai.unk56 == 8 && ai.unk58 == 8 && ai.y_pos.i.hi == 0x70);
    return seen;
}
static u32 ai_last_done(void) { return afterimage(2, -1, 2); }
static const CTestCase object_afterimage_steps_cases[] = {
    ai_restart,
    ai_last_done,
};
static const u32 object_afterimage_steps_cases_expected[] = { 0x90010002u, 0x80000200u };

const struct CTestGroup c_test_groups[] = {
    { "object_afterimage_steps", object_afterimage_steps_cases, object_afterimage_steps_cases_expected, COUNT(object_afterimage_steps_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(object_afterimage_steps_cases);
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
