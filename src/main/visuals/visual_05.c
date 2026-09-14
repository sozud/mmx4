// VisualObj, visual_object_update_funcs[5]
// 800AFC9C..800AFF78
#include "common.h"

void (*D_8010A2A4[])(struct VisualObj*) = {
    func_800AFD20,
    func_800AFD6C,
};

void (*D_8010A2AC[])(struct VisualObj*) = {
    func_800AFDA8,
    func_800AFE20,
    func_800AFEA4,
};

void func_800AFC9C(struct VisualObj* arg0)
{
    u8 temp_a1;
    struct PlayerObj* owner;

    owner = arg0->unk5C.owner;
    arg0->animation_step.fields.frame_index = owner->animation_step.fields.frame_index;
    temp_a1 = owner->unk15;
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    arg0->unk15 = temp_a1;
    if (owner->pad4B[0] == 0) {
        arg0->on_screen = 0;
        arg0->state = 0;
        return;
    }
    D_8010A2A4[arg0->state](arg0);
}

void func_800AFD20(struct VisualObj* arg0)
{
    s8 temp_v0;
    struct PlayerObj* owner;

    owner = arg0->unk5C.owner;
    temp_v0 = owner->pad4B[0];
    if (temp_v0 != 0) {
        if (temp_v0 > 0) {
            arg0->on_screen = 1;
            func_800AFF28(arg0);
            return;
        }
        owner->pad4B[0] = 0;
    }
}

void func_800AFD6C(struct VisualObj* arg0)
{
    D_8010A2AC[arg0->unk5](arg0);
}

void func_800AFDA8(struct VisualObj* arg0)
{
    s16 temp_v0;
    struct PlayerObj* owner;

    temp_v0 = arg0->unk54;
    owner = arg0->unk5C.owner;
    if (temp_v0 != 0) {
        arg0->unk54 = temp_v0 - 1;
    } else {
        arg0->unk54 = 3;
        func_800AFF08(arg0);
    }
    if (owner->pad4B[0] < 0) {
        arg0->unk5++;
    }
}

void func_800AFE20(struct VisualObj* arg0)
{
    s16 temp_v0;
    s16 temp_v0_2;

    if (arg0->unk5C.owner->pad4B[0] > 0) {
        func_800AFF28(arg0);
        return;
    }

    temp_v0 = arg0->unk56;
    if (temp_v0 != 0) {
        temp_v0_2 = temp_v0 - 1;
        arg0->unk56 = temp_v0_2;
        if (temp_v0_2 & 1) {
            func_800AFF08(arg0);
        }
    } else {
        arg0->unk5++;
    }
}

void func_800AFEA4(struct VisualObj* arg0)
{
    struct PlayerObj* owner;

    owner = arg0->unk5C.owner;
    if (arg0->unk58 != 0) {
        func_800AFF08(arg0);
        arg0->unk58--;
        return;
    }

    arg0->on_screen = 0;
    arg0->state = 0;
    if (arg0->unk2 == 2) {
        owner->pad4B[0] = 0;
    }
}

void func_800AFF08(struct VisualObj* arg0)
{
    struct PlayerObj* parent;

    parent = arg0->unk50;
    arg0->x_pos.val = parent->unk18;
    arg0->y_pos.val = parent->unk1C;
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_05", func_800AFF28);
