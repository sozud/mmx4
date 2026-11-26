#include "test_runtime.h"
#include "main/misc/misc_16_vent_puff.h"
#include "main/55C4.h"
#include "support/state_cases.h"

void vent_puff_init(struct MiscObj*);
void func_800CACF0(struct MiscObj*);

static u32 puff_paths(u32 row)
{
    struct MiscObj obj;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    for (i = 0; i < COUNT(state_table); i++)
        state_table[i] = state_step;
    obj.active = 0x41;
    obj.id = 16;
    obj.state = 1;
    obj.bg_offset = -1;
    obj.x_pos.i.hi = 100;
    obj.y_pos.i.hi = 100;
    obj.animation_table = (u32**)state_table;
    obj.animation_cursor = state_step;
    obj.animation_step.packed = state_step[0];
    if (row <= 2) {
        obj.state = 0;
        obj.unk2 = row == 2;
        obj.ext.misc_16.timer = row == 0 ? 3 : 0;
        vent_puff_init(&obj);
        assert(obj.state == (row != 0) && obj.ext.misc_16.timer == (row == 0 ? 2 : 0));
        if (row != 0) {
            assert(obj.unk17 == (row == 1 ? 0x19 : 0x1A) && obj.bg_offset == 0);
            assert(obj.y_vel.val == (row == 1 ? -0xA000 : -0x14000) && obj.x_vel.val == (row == 1 ? -0x4000 : -0x8000));
        }
        return 1;
    }
    if (row <= 4) {
        engine_obj.stage = row == 3 ? 3 : 0xC;
        obj.y_pos.i.hi = 0x5CF;
        obj.y_vel.val = -0x10000;
        obj.x_vel.val = 0x4000;
        obj.animation_step.fields.event = row == 3;
        func_800CACF0(&obj);
        assert(obj.y_pos.i.hi == 0x5D0 && obj.x_vel.val == (row == 3 ? -0x4000 : 0x4000));
        assert(obj.unk5 == (row == 3) && obj.ext.misc_16.timer == (row == 3 ? 0x14 : 0) && obj.y_vel.val == (row == 3 ? 0 : -0x10000));
        return 1;
    }
    obj.unk5 = 1;
    obj.on_screen = 1;
    obj.ext.misc_16.timer = row == 5 ? 1 : row == 6 ? 4
                                                    : 3;
    func_800CACF0(&obj);
    assert(obj.state == (row == 5 ? 2 : 1));
    assert(row == 5 || obj.on_screen == (row == 6));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "puff_paths", 0, 0, 8, puff_paths },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 8;
