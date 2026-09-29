// QuadObj, quad_object_update_funcs[6]
// 800D5934..800D5C54
#include "common.h"

// light_ray_init
INCLUDE_ASM("main/nonmatchings/quads/quad_06", func_800D5934);

void light_ray_main(struct QuadObj* arg0)
{
    if (++arg0->ext.ready_line.x_vel.bytes[2] == 0) {
        arg0->ext.ready_line.x_vel.bytes[2] = 0xFE;
    }

    arg0->unk14.val += arg0->ext.ready_line.y_vel.val;
    arg0->unk18.val += arg0->ext.ready_line.x_accel.val;
    arg0->unk24.val += arg0->ext.ready_line.y_accel.val;
    arg0->unk28.val += arg0->runtime.quad_06.x_accumulator;
    arg0->ext.ready_line.y_vel.val += arg0->runtime.quad_06.y_accumulator;
    arg0->ext.ready_line.x_accel.val += arg0->runtime.quad_06.acceleration;
    arg0->ext.ready_line.y_accel.val += arg0->runtime.quad_06.base_speed;
    arg0->runtime.quad_06.x_accumulator += (s32)arg0->link.owner;
    arg0->unk1C.val = arg0->unk14.val + 0x10000;
    arg0->unk20.val = arg0->unk18.val + 0x10000;
    arg0->unk2C.val = arg0->unk24.val - 0x10000;
    arg0->unk30.val = arg0->unk28.val - 0x10000;

    if (arg0->ext.ready_line.x_vel.bytes[1] != 0) {
        arg0->ext.ready_line.x_vel.bytes[1]--;
    } else {
        quad_is_on_screen(arg0);
        if (arg0->on_screen == 0 && arg0->ext.ready_line.x_vel.bytes[2] > 60) {
            arg0->state++;
        }
    }
}

void light_ray_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void light_ray_update(struct QuadObj* arg0)
{
    light_ray_state_funcs[arg0->state](arg0);
}

void (*light_ray_state_funcs[])(struct QuadObj*) = {
    func_800D5934,
    light_ray_main,
    light_ray_despawn,
};
