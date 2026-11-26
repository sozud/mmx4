#include "test_runtime.h"
#include "main/quads/quad_06_light_ray.h"
#include "main/object_motion.h"

void func_800D5934(struct QuadObj*);
void light_ray_main(struct QuadObj*);

static u32 ray_paths(u32 index)
{
    static const u8 scenarios[] = { 0, 1, 2, 3, 4, 5, 7, 8 };
    u32 row = scenarios[index];
    struct QuadObj obj;
    u32 seed, angle;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 1;
    obj.id = 6;
    obj.state = 1;
    if (row <= 3) {
        for (seed = 0;; seed++) {
            cur_random = seed;
            angle = get_random() & 0x1F;
            if (angle / 8 == row && angle % 8 != 0)
                break;
        }
        cur_random = seed;
        obj.state = 0;
        func_800D5934(&obj);
        assert(obj.state == 1 && obj.ext.ready_line.x_vel.bytes[0] == angle && obj.ext.ready_line.x_vel.bytes[1] == 4);
        assert((obj.ext.ready_line.y_vel.val > 0) == (row == 0 || row == 3));
        assert((obj.ext.ready_line.x_accel.val > 0) == (row >= 2));
        assert(obj.ext.ready_line.y_accel.val == obj.ext.ready_line.y_vel.val);
        return 1;
    }
    obj.ext.ready_line.x_vel.bytes[1] = row == 5 ? 2 : 0;
    obj.ext.ready_line.x_vel.bytes[2] = row == 4 ? 0xFF : row == 8 ? 30
                                                                   : 100;
    obj.x_pos.i.hi = row == 7 ? 100 : 0x400;
    obj.y_pos.i.hi = 100;
    light_ray_main(&obj);
    assert(obj.ext.ready_line.x_vel.bytes[2] == (row == 4 ? 0xFE : row == 8 ? 31
                                                                            : 101));
    assert(obj.ext.ready_line.x_vel.bytes[1] == (row == 5 ? 1 : 0));
    assert(obj.state == (row == 4 || row == 6 ? 2 : 1));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "ray_paths", 0, 0, 8, ray_paths },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 8;
