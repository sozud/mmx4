// VisualObj, visual_object_update_funcs[5]
// 800AFC9C..800AFF78
#include "common.h"

void (*object_afterimage_state_funcs[])(struct VisualObj*) = {
    object_afterimage_wait,
    object_afterimage_main,
};

void (*object_afterimage_step_funcs[])(struct VisualObj*) = {
    object_afterimage_trail,
    object_afterimage_linger,
    object_afterimage_catch_up,
};

void object_afterimage_update(struct VisualObj* arg0)
{
    u8 temp_a1;
    struct PlayerObj* owner;

    owner = arg0->unk5C.owner;
    arg0->animation_step.fields.frame_index = owner->animation_step.fields.frame_index;
    temp_a1 = owner->unk15;
    arg0->unk15 = temp_a1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (owner->pad4B[0] == 0) {
        arg0->on_screen = 0;
        arg0->state = 0;
        return;
    }
    object_afterimage_state_funcs[arg0->state](arg0);
}

void object_afterimage_wait(struct VisualObj* arg0)
{
    s8 temp_v0;
    struct PlayerObj* owner;

    owner = arg0->unk5C.owner;
    temp_v0 = owner->pad4B[0];
    if (temp_v0 != 0) {
        if (temp_v0 > 0) {
            arg0->on_screen = 1;
            object_afterimage_start(arg0);
            return;
        }
        owner->pad4B[0] = 0;
    }
}

void object_afterimage_main(struct VisualObj* arg0)
{
    object_afterimage_step_funcs[arg0->unk5](arg0);
}

void object_afterimage_trail(struct VisualObj* arg0)
{
    s16 temp_v0;
    struct PlayerObj* owner;

    temp_v0 = arg0->unk54;
    owner = arg0->unk5C.owner;
    if (temp_v0 != 0) {
        arg0->unk54 = temp_v0 - 1;
    } else {
        arg0->unk54 = 3;
        object_afterimage_follow(arg0);
    }
    if (owner->pad4B[0] < 0) {
        arg0->unk5++;
    }
}

void object_afterimage_linger(struct VisualObj* arg0)
{
    s16 temp_v0;
    s16 temp_v0_2;

    if (arg0->unk5C.owner->pad4B[0] > 0) {
        object_afterimage_start(arg0);
        return;
    }

    temp_v0 = arg0->unk56;
    if (temp_v0 != 0) {
        temp_v0_2 = temp_v0 - 1;
        arg0->unk56 = temp_v0_2;
        if (temp_v0_2 & 1) {
            object_afterimage_follow(arg0);
        }
    } else {
        arg0->unk5++;
    }
}

void object_afterimage_catch_up(struct VisualObj* arg0)
{
    struct PlayerObj* owner;

    owner = arg0->unk5C.owner;
    if (arg0->unk58 != 0) {
        object_afterimage_follow(arg0);
        arg0->unk58--;
        return;
    }

    arg0->on_screen = 0;
    arg0->state = 0;
    if (arg0->unk2 == 2) {
        owner->pad4B[0] = 0;
    }
}

void object_afterimage_follow(struct VisualObj* arg0)
{
    struct PlayerObj* parent;

    parent = arg0->unk50;
    arg0->x_pos.val = parent->unk18.val;
    arg0->y_pos.val = parent->unk1C.val;
}

void object_afterimage_start(struct VisualObj* arg0)
{
    struct ObjectHeader* parent;

    arg0->unk54 = 3;
    arg0->unk56 = 8;
    parent = *(struct ObjectHeader**)&arg0->unk5C;
    arg0->unk58 = (5 - arg0->unk2) * 2;
    arg0->x_pos.val = parent->x_pos.val;
    arg0->y_pos.val = parent->y_pos.val;
    arg0->unk5 = 0;
    arg0->state++;
}
