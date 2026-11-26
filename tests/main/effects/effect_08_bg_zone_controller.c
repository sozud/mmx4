#include "test_runtime.h"
#include "main/effects/effect_08_bg_zone_controller.h"

struct ZoneStep {
    s16 player_x, player_y;
    u8 zone, unk6;
    s8 camera_dx, unk16, unk17;
    u8 out_unk5, out_unk6;
    s8 out_unk16, out_unk17;
    u8 checkpoint, bg1_unk4, bg2_unk4;
};
static const struct ZoneStep zone_steps[] = {
    { 0x100, 0, 5, 0, 0, 0, 0, 0, 1, 0, 0, 0xFF, 0, 0 },
    { 0x100, 0, 0, 1, 3, 1, 0, 0, 1, 1, 3, 0xFF, 0, 0 },
    { 0x100, 0, 0, 1, -3, 1, 0, 0, 1, 1, -3, 0xFF, 0, 0 },
    { 0x100, 0, 0, 1, 10, 2, 0, 0, 1, 0, 0, 0xFF, 0, 0 },
    { 0x100, 0, 0, 1, -10, 0, 0, 0, 1, 2, 0, 0xFF, 0, 0 },
    { 0x100, 0, 0, 1, 8, 0, 0, 0, 1, 1, 0, 0xFF, 0, 0 },
    { 0x100, 0, 0, 1, -8, 2, 0, 0, 1, 1, 0, 0xFF, 0, 0 },
    { 0x100, 0, 0, 1, 0, 1, 5, 0, 1, 1, 5, 0xFF, 0, 0 },
    { 0x780, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0xFF, 0, 0 },
    { 0x780, 0, 1, 1, 0, 0, 0, 5, 0, 0, 0, 0xFF, 0, 0 },
    { 0x900, 0x100, 2, 0, 0, 0, 0, 2, 1, 0, 0, 0xFF, 1, 3 },
    { 0xDCF, 0x100, 2, 1, 0, 0, 0, 2, 1, 0, 0, 0xFF, 0, 0 },
    { 0xDD0, 0x100, 2, 1, 0, 0, 0, 5, 0, 0, 0, 2, 0, 0 },
    { 0x1800, 0, 3, 0, 0, 0, 0, 3, 1, 0, 0, 0xFF, 6, 1 },
    { 0x1709, 0, 3, 1, 0, 0, 0, 3, 1, 0, 0, 0xFF, 0, 0 },
    { 0x1708, 0, 3, 1, 0, 0, 0, 5, 0, 0, 0, 3, 0, 0 },
    { 0x900, 0x128, 4, 0, 0, 0, 0, 4, 1, 0, 0, 0xFF, 1, 3 },
    { 0x112D, 0x128, 4, 1, 0, 0, 0, 4, 1, 0, 0, 0xFF, 0, 0 },
    { 0x112C, 0x128, 4, 1, 0, 0, 0, 5, 0, 0, 0, 0xFF, 0, 0 },
};
static u32 zone_step(u32 row)
{
    const struct ZoneStep* c = &zone_steps[row];
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(background_objects));
    engine_obj.checkpoint = 0xFF;
    g_Player.x_pos.i.hi = c->player_x;
    g_Player.y_pos.i.hi = c->player_y;
    background_objects[0].unk14.i.hi = 0x200;
    background_objects[0].x_pos.i.hi = 0x200 + c->camera_dx;
    obj.active = 1;
    obj.id = 8;
    obj.state = row == 0 ? 0 : 1;
    obj.unk5 = c->zone;
    obj.unk6 = c->unk6;
    obj.ext.unk_effect.unk14 = c->zone;
    obj.ext.effect_8.unk16 = c->unk16;
    obj.ext.effect_8.unk17 = c->unk17;
    bg_zone_controller_update(&obj);
    assert(obj.state == 1 && obj.unk5 == c->out_unk5 && obj.unk6 == c->out_unk6);
    assert(obj.ext.unk_effect.unk14 == (row == 0 ? 0 : c->zone));
    assert(obj.ext.effect_8.unk16 == c->out_unk16 && obj.ext.effect_8.unk17 == c->out_unk17);
    assert((u8)engine_obj.checkpoint == c->checkpoint);
    assert(engine_obj.unkF == (c->checkpoint != 0xFF ? -0x40 : row == 18 ? 0x40 : 0));
    assert(background_objects[1].unk4 == c->bg1_unk4 && background_objects[2].unk4 == c->bg2_unk4);
    assert(background_objects[0].unk4 == (row == 0 ? 2 : 0));
    if (row >= 3 && row <= 6) {
        assert(background_objects[1].unk4C == 1);
#ifdef MMX4_SATURN
        assert(background_objects[1].x_pos.val == (c->out_unk16 == 1 ? 0x2000000 : 0));
        assert(background_objects[1].y_pos.val == (c->out_unk16 == 2 ? 0x3000000 : 0x2000000));
#else
        assert(background_objects[1].x_pos.i.hi == c->out_unk16 << 9);
#endif
    } else {
        assert(background_objects[1].unk4C == 0 && background_objects[1].x_pos.val == 0);
    }
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "zone_step", 0, 0, COUNT(zone_steps), zone_step },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(zone_steps);
