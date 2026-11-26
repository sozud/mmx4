#include "test_runtime.h"
#include "support/sound_probe.h"

void func_800B7EE8(struct EffectObj*);

static u32 zone_rows(u32 row)
{
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    sound_probe_begin_group(5);
    obj.active = 1;
    obj.id = 10;
    obj.state = row != 0;
    obj.ext.unk_effect.unk14 = row == 0 ? 0x55 : row == 2 ? 1 : 0;
    engine_obj.substage = row == 3;
    g_Player.x_pos.i.hi = row == 3 ? 0x300 : 0x100;
    g_Player.y_pos.i.hi = row == 3 ? 0x300 : 0x100;
    func_800B7EE8(&obj);
    assert(obj.state == 1);
    assert(obj.ext.unk_effect.unk14 == (row == 0 ? 0 : row == 3 ? 6 : 1));
    SOUND_CHECK(sound_probe_id() == (row == 1 ? 0 : row == 3 ? 1 : -1));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "zone_rows", 0, 0, 4, zone_rows },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4;
