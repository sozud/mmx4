// VisualObj, visual_object_update_funcs[17]
// 800B2090..800B2544
#include "common.h"
#include "main/visuals/visual_17_web_piece.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

// web_piece_state_funcs
extern void (*web_piece_state_funcs[])(struct VisualObj*);

void web_piece_main(struct VisualObj*);
void web_piece_fall(struct VisualObj*);

// web_piece_step_funcs
extern void (*web_piece_step_funcs[])(struct VisualObj*);

void web_piece_hang(struct VisualObj*);

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
#ifdef MMX4_PC
static const s16* visual_17_target(struct VisualObj* arg0);
void func_800B20CC(struct VisualObj* arg0);
void func_800B22B4(struct VisualObj* arg0);
u8 angle_from_delta(s32 arg0, s32 arg1);
static const s16* visual_17_target(struct VisualObj* arg0)
{
    return engine_obj.stage != 0xC ? web_piece_positions_a[arg0->unk2 - 1] : web_piece_positions_b[arg0->unk2 - 1];
}
#endif

#ifdef MMX4_PC
void func_800B20CC(struct VisualObj* arg0)
{
    const s16* target;
    u8 direction;
    struct QuadObj* quad;

    arg0->state = 1;
    arg0->on_screen = 1;
    if (arg0->unk2 == 0) {
        arg0->unk16 = 3;
        set_animation(arg0, 0x18);
        return;
    }
    arg0->unk16 = 5;
    set_animation(arg0, 0x17);
    target = visual_17_target(arg0);
    direction = angle_from_delta(arg0->x_pos.val - (target[0] << 16), arg0->y_pos.val - (target[1] << 16));
    set_velocity_from_angle(MOVING_OBJECT(arg0), direction);
    arg0->unk54 = direction;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->x_vel.val *= 2;
    arg0->y_vel.val *= 2;
    quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = -0x7F;
        quad->id = 5;
        arg0->unk5C.owner = (struct PlayerObj*)quad;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/visuals/visual_17_web_piece", func_800B20CC);
#endif

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
#ifdef MMX4_PC
void func_800B22B4(struct VisualObj* arg0)
{
    const s16* target = visual_17_target(arg0);
    s32 target_x = target[0] << 16;
    s32 target_y = target[1] << 16;
    u8 direction = angle_from_delta(arg0->x_pos.val - target_x, arg0->y_pos.val - target_y);
    struct BaseObj* quad = (struct BaseObj*)arg0->unk5C.owner;

    if ((arg0->unk54 >> 3) != (direction >> 3)) {
        arg0->unk5 = 1;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->y_vel.val = 0;
        arg0->unk2C = 0;
        arg0->x_pos.val = target_x;
        arg0->y_pos.val = target_y;
        quad->state = 2;
        update_on_screen(BASE_OBJECT(arg0), 0x10, 0x10);
    } else {
        move_with_gravity(ANIMATED_OBJECT(arg0));
    }
    quad->x_pos.val = arg0->x_pos.val;
    quad->y_pos.val = arg0->y_pos.val;
}
#else
INCLUDE_ASM("main/nonmatchings/visuals/visual_17_web_piece", func_800B22B4);
#endif

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
