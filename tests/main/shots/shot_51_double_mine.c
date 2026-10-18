#include "test_runtime.h"
#include "main/shots/shot_51_double_mine.h"

static u32 mine_case(u32 observation)
{
    struct ShotObj obj, before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 51;
    obj.state = 1;
    obj.unk5 = 0x27;
    obj.timer = -1;
    obj.unk8C.halves[1] = 1;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 3 * 65536;
    obj.animation_step.fields.duration = 2;
    before = obj;
    func_800AA68C(&obj);
    before.timer = -2;
    before.y_pos.val = 5 * 65536;
    before.animation_step.fields.duration = 1;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    return observation == 0 ? obj.y_pos.val : (u16)obj.timer | ((u32)obj.animation_step.fields.duration << 16);
}
#define CASE(n)               \
    static u32 mine_##n(void) \
    {                         \
        return mine_case(n);  \
    }
CASE(0)
CASE(1)
#define ENTRY(n) mine_##n,
static const CTestCase double_mine_negative_timer_cases[]
    = { ENTRY(0) ENTRY(1) };
static const u32 double_mine_negative_timer_cases_expected[] = { 0x50000u, 0x1FFFEu };
#undef CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "double_mine_negative_timer", double_mine_negative_timer_cases, double_mine_negative_timer_cases_expected, COUNT(double_mine_negative_timer_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(double_mine_negative_timer_cases);
