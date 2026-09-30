// VisualObj, visual_object_update_funcs[17]
// 800B2090..800B2544
#include "common.h"

s16 web_piece_positions_a[4][2] = {
    { 0x12C0, 0x538 },
    { 0x12F8, 0x568 },
    { 0x1288, 0x568 },
    { 0x12C0, 0x598 },
};

s16 web_piece_positions_b[4][2] = {
    { 0x10C0, 0x638 },
    { 0x10F8, 0x668 },
    { 0x1088, 0x668 },
    { 0x10C0, 0x698 },
};

void web_piece_update(struct VisualObj* arg0)
{
    web_piece_state_funcs[arg0->state](arg0);
}

// web_piece_init
INCLUDE_ASM("main/nonmatchings/visuals/visual_17_web_piece", func_800B20CC);

void web_piece_main(struct VisualObj* arg0)
{
    struct MainObj* owner;

    if (arg0->unk2 == 0) {
        owner = MAIN_OBJECT(arg0->unk50);
        arg0->x_pos.val = owner->x_pos.val;
        arg0->y_pos.val = owner->y_pos.val;
        animate_object(arg0);
        if (owner->ext.main_43.flash_timer == 0) {
            ZeroObjectState(arg0);
        } else {
            update_on_screen(arg0, 0x10, 0x10);
        }
    } else {
        web_piece_step_funcs[arg0->unk5](arg0);
    }
}

// web_piece_attach
INCLUDE_ASM("main/nonmatchings/visuals/visual_17_web_piece", func_800B22B4);

void web_piece_hang(struct VisualObj* arg0)
{
    if (arg0->unk50->state >= 2) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    } else {
        animate_object(arg0);
    }
    update_on_screen(arg0, 0x10, 0x10);
}

void web_piece_fall(struct VisualObj* arg0)
{
    switch (arg0->unk5) {
    case 0:
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->y_vel.val = -0x8000;
        arg0->unk2C = 0;
        arg0->unk54 = 0x78;
        arg0->unk5 = 1;
        animate_object(arg0);
        update_on_screen(arg0, 0x10, 0x10);
        break;
    case 1:
        if (--arg0->unk54 == 0) {
            arg0->unk5 = 2;
        }
        if (!(arg0->unk54 & 7)) {
            func_800AF878(arg0, 0, 0xF, 0xF);
        }
        move_with_gravity(arg0);
        animate_object(arg0);
        update_on_screen(arg0, 0x10, 0x10);
        break;
    case 2:
        ZeroObjectState(arg0);
        break;
    }
}

void (*web_piece_state_funcs[])(struct VisualObj*) = {
    func_800B20CC,
    web_piece_main,
    web_piece_fall,
};

void (*web_piece_step_funcs[])(struct VisualObj*) = {
    func_800B22B4,
    web_piece_hang,
};
