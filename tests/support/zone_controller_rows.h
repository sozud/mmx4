#ifndef MMX4_TESTS_ZONE_CONTROLLER_ROWS_H
#define MMX4_TESTS_ZONE_CONTROLLER_ROWS_H

struct ZoneRow {
    u8 state, zone, step, index;
    s16 x, y;
};

static u32 zone_row_run(void (*update)(struct EffectObj*), const struct ZoneRow* row, u32 index, const u32* expected)
{
    struct EffectObj obj;
    u32 seen[4];
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.state = row->state;
    obj.unk5 = row->zone;
    obj.unk6 = row->step;
    obj.ext.effect_15.unk14 = row->index;
    g_Player.x_pos.i.hi = row->x;
    g_Player.y_pos.i.hi = row->y;
    update(&obj);
    seen[0] = obj.state | obj.unk5 << 8 | obj.unk6 << 16 | (u32)(u8)obj.ext.effect_15.unk14 << 24;
    seen[1] = background_objects[0].unk2E;
    seen[2] = (u16)background_objects[0].unk24;
    seen[3] = (u8)background_objects[2].unk4A;
    return c_test_observe(0, index, seen, expected, 4);
}

#endif
