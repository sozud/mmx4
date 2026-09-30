// ShotObj, shot_object_update_funcs[30]
// 8009FB60..8009FF10
#include "common.h"

void cannon_shot_update(struct ShotObj* self)
{
    cannon_shot_state_funcs[self->state](self);
}

// cannon_shot_init
INCLUDE_ASM("main/nonmatchings/shots/shot_30_cannon_shot", func_8009FB9C);

// cannon_shot_fly
INCLUDE_ASM("main/nonmatchings/shots/shot_30_cannon_shot", func_8009FD00);

void cannon_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void cannon_shot_idle(struct ShotObj* self)
{
}

void cannon_shot_spawn_flash(struct ShotObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x10;
        obj->unk2 = 1;
        obj->unk50 = (struct PlayerObj*)self;
        obj->unk42 = self->unk42;
        obj->animation_table = self->animation_table;
        obj->unk3C = self->unk3C;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = self->unk15;
        obj->x_pos.val = self->x_pos.val;
        obj->y_pos.val = self->y_pos.val;
    }
}

u8 cannon_shot_boxes[4][4] = {
    { 0xF3, 0xFA, 0x17, 0x0A },
    { 0xF5, 0xFD, 0x1B, 0x0A },
    { 0xFF, 0xFF, 0x0A, 0x04 },
    { 0x02, 0x02, 0x0D, 0x04 },
};

s32 cannon_shot_speeds[4] = { -0x22000, 0x22000, -0x10000, 0x10000 };

void (*cannon_shot_state_funcs[])(struct ShotObj*) = {
    func_8009FB9C,
    func_8009FD00,
    cannon_shot_despawn,
    cannon_shot_idle,
};
