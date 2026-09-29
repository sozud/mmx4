// QuadObj, quad_object_update_funcs[16]
// 800D802C..800D8648
#include "common.h"

// sigma_laser_init
INCLUDE_ASM("main/nonmatchings/quads/quad_16", func_800D802C);

void sigma_laser_wait(struct QuadObj* arg0)
{
    if (--arg0->ext.unk38 == 0) {
        arg0->ext.unk38 = 8;
        arg0->unk5++;
    }
}

// sigma_laser_charge
INCLUDE_ASM("main/nonmatchings/quads/quad_16", func_800D8180);

void sigma_laser_flash(struct QuadObj* arg0)
{
    struct PlayerObj* obj = arg0->unk5C;
    arg0->ext.unk38--;
    if (arg0->ext.unk38 == 0) {
        arg0->unk34 = 0x12;
        arg0->ext.unk38 = 0x10;
        arg0->unk5 = (u8)arg0->unk5 + 1;
        obj->shot_types[1] = 0;
    } else {
        arg0->unk34 = sigma_laser_flash_colors[arg0->ext.unk38 & 3];
    }
}

// sigma_laser_fire
INCLUDE_ASM("main/nonmatchings/quads/quad_16", func_800D82E8);

void sigma_laser_main(struct QuadObj* arg0)
{
    sigma_laser_step_funcs[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
}

void sigma_laser_cancel_wait(struct QuadObj* arg0)
{
    if (--arg0->ext.unk38 == 0) {
        arg0->ext.unk38 = 0x10;
        arg0->unk5++;
    }
}

// sigma_laser_cancel_shrink
INCLUDE_ASM("main/nonmatchings/quads/quad_16", func_800D845C);

void sigma_laser_cancel(struct QuadObj* arg0)
{
    sigma_laser_cancel_funcs[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
}

void sigma_laser_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void sigma_laser_update(struct QuadObj* arg0)
{
    struct PlayerObj* temp_v1;

    temp_v1 = arg0->unk5C;
    if ((u8)temp_v1->shot_types[0] != 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        temp_v1->shot_types[1] = 0;
    }
    sigma_laser_state_funcs[arg0->state](arg0);
}

s16 sigma_laser_origin_offsets[2][2] = {
    { 0x50E, 0x29C },
    { 0x50D, 0x29B },
};

s16 sigma_laser_sweep_offsets[14][2] = {
    { 0x492, 0x2F0 },
    { 0x493, 0x2F0 },
    { 0x4FF, 0x279 },
    { 0x4FE, 0x278 },
    { 0x410, 0x2D0 },
    { 0x410, 0x2D1 },
    { 0x4FD, 0x259 },
    { 0x4FC, 0x258 },
    { 0x410, 0x28B },
    { 0x410, 0x28C },
    { 0x4FB, 0x231 },
    { 0x4FA, 0x230 },
    { 0x410, 0x230 },
    { 0x410, 0x231 },
};

s16 sigma_laser_start_offsets[8][2] = {
    { 0x4FF, 0x279 },
    { 0x4FD, 0x278 },
    { 0x410, 0x2D0 },
    { 0x410, 0x2D4 },
    { 0x4FD, 0x259 },
    { 0x4FC, 0x258 },
    { 0x2C0, 0x2F0 },
    { 0x2C4, 0x2F0 },
};

s16 sigma_laser_end_offsets[8][2] = {
    { 0x453, 0x2F0 },
    { 0x4D5, 0x2F0 },
    { 0x410, 0x2AF },
    { 0x410, 0x300 },
    { 0x410, 0x273 },
    { 0x410, 0x2C3 },
    { 0x410, 0x20B },
    { 0x410, 0x263 },
};

u8 sigma_laser_flash_colors[4] = { 0x12, 0x13, 0x14, 0x13 };

void (*sigma_laser_step_funcs[])(struct QuadObj*) = {
    sigma_laser_wait,
    func_800D8180,
    sigma_laser_flash,
    func_800D82E8,
};

void (*sigma_laser_cancel_funcs[])(struct QuadObj*) = {
    sigma_laser_cancel_wait,
    func_800D845C,
};

void (*sigma_laser_state_funcs[])(struct QuadObj*) = {
    func_800D802C,
    sigma_laser_main,
    sigma_laser_despawn,
    sigma_laser_cancel,
};
