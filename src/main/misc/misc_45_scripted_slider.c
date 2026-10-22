// MiscObj, misc_object_update_funcs[45]
// 800D0E48..800D1284
#include "common.h"
#include "main/misc/misc_45_scripted_slider.h"
#include "main/object_motion.h"
#include "main/objects.h"

// scripted_slider_step_funcs
extern void (*scripted_slider_step_funcs[])(struct MiscObj*);
void scripted_slider_slide(struct MiscObj*);
void scripted_slider_brake(struct MiscObj*);
void scripted_slider_idle(void);
void scripted_slider_follow_owner(struct MiscObj*);

// scripted_slider_state_funcs
extern void (*scripted_slider_state_funcs[])(struct MiscObj*);

void scripted_slider_main(struct MiscObj*);
void scripted_slider_despawn(struct MiscObj*);

u8 stage_cutscene_data[24] = {
    0,
    2,
    4,
    5,
    6,
    7,
    9,
    10,
    12,
    1,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    3,
    8,
    11,
#ifdef VERSION_JP
    0,
#else
    21,
#endif
    0,
    0,
};

#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/misc/misc_45_scripted_slider", func_800D0E7C_jp);
#endif

// scripted_slider_init
struct Misc45PositionData {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};

#ifdef MMX4_PC
void func_800D0E48(struct MiscObj* self);
void func_800D11B0(struct MiscObj* self);
void func_800D0D68(struct MiscObj* self, u8 kind);
extern struct Misc45PositionData scripted_slider_offsets[];
#endif

#ifdef MMX4_PC
void func_800D0E48(struct MiscObj* self)
{
    self->active = 0x41;
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[0];
    self->unk42 = 0x7848;
    self->bg_offset = -1;
    self->ext.misc_45.direction = 1;
    self->unk40 = D_801406A8[0] >> 7;
    self->unk16 = 0;
    self->state++;
    self->unk15 = 0;
    switch (self->unk2) {
    case 1:
        func_800D0D68(self, 0x12);
        break;
    case 5:
        func_800D0D68(self, 0x13);
        break;
    case 7:
        func_800D0D68(self, 0x14);
        break;
#ifndef VERSION_JP
    case 11:
        func_800D0D68(self, 0x15);
        break;
#endif
    default:
        if (self->unk2 >= 0x12) {
            self->x_pos.i.hi += scripted_slider_offsets[self->unk2].x;
            self->unk5 = 3;
            self->y_pos.i.hi += scripted_slider_offsets[self->unk2].y;
            break;
        }
        self->x_pos.i.hi = scripted_slider_offsets[self->unk2].x;
        self->y_pos.i.hi = scripted_slider_offsets[self->unk2].y;
        self->ext.misc_45.unk58 = scripted_slider_offsets[self->unk2].width;
        self->ext.misc_45.target_x = scripted_slider_offsets[self->unk2].height;
        if (self->unk2 == 0 || self->unk2 == 9) {
            self->x_vel.val = 0xE0000;
            self->ext.misc_45.direction = 0;
        } else {
            self->x_vel.val = 0xFFF20000;
        }
        self->unk28 = 0;
        break;
    }
    self->animation_step.fields.frame_index = stage_cutscene_data[self->unk2];
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_45_scripted_slider", func_800D0E48);
#endif

void scripted_slider_slide(struct MiscObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->ext.misc_45.direction == 0) {
        if (self->x_pos.i.hi > self->ext.misc_45.target_x) {
            self->unk28 = FIXED(1);
            self->unk5++;
        }
    } else if (self->x_pos.i.hi < self->ext.misc_45.target_x) {
        self->unk28 = -FIXED(1);
        self->unk5++;
    }
}

void scripted_slider_brake(struct MiscObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));

    if (self->ext.misc_45.direction == 0) {
        if (self->x_pos.i.hi < self->ext.misc_45.target_x) {
            self->x_pos.i.hi = self->ext.misc_45.target_x;
            self->unk28 = 0;
            self->x_vel.val = 0;
            self->unk5++;
        }
    } else if (self->x_pos.i.hi > self->ext.misc_45.target_x) {
        self->x_pos.i.hi = self->ext.misc_45.target_x;
        self->unk28 = 0;
        self->x_vel.val = 0;
        self->unk5++;
    }
}

void scripted_slider_idle(void)
{
}

extern struct Misc45PositionData scripted_slider_offsets[];

void scripted_slider_follow_owner(struct MiscObj* self)
{
    s32 index;
    struct MainObj* source;

    index = self->unk2;
    source = self->ext.misc_45.owner;
    self->x_pos.u.hi = source->x_pos.u.hi + scripted_slider_offsets[index].x;
    self->y_pos.u.hi = source->y_pos.u.hi + scripted_slider_offsets[self->unk2].y;
}

// scripted_slider_step_4
#ifdef MMX4_PC
void func_800D11B0(struct MiscObj* self)
{
    self->unk28 = 0;
    self->x_vel.val = 0;
    self->unk5 = 2;
    self->x_pos.i.hi = self->ext.misc_45.target_x;
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_45_scripted_slider", func_800D11B0);
#endif

void scripted_slider_main(struct MiscObj* self)
{
    if (engine_flags != 0) {
        scripted_slider_step_funcs[self->unk5](self);
        self->on_screen = 1;
    }
}

void scripted_slider_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void scripted_slider_update(struct MiscObj* self)
{
    scripted_slider_state_funcs[self->state](self);
}

struct Misc45PositionData scripted_slider_offsets[] = {
    { -120, 176, 184, 160 },
    { 424, 208, 99, 123 },
    { 448, 208, 136, 160 },
    { 432, 208, 136, 160 },
    { 432, 208, 136, 160 },
    { 400, 208, 65, 89 },
    { 448, 208, 136, 160 },
    { 400, 208, 65, 89 },
    { 464, 208, 136, 160 },
    { -120, 176, 184, 160 },
    { 440, 208, 136, 160 },
#ifdef VERSION_JP
    { 440, 208, 136, 160 },
#else
    { 440, 208, 136, 152 },
#endif
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 136, 0, 0, 0 },
    { 144, 0, 0, 0 },
    { 144, 0, 0, 0 },
#ifndef VERSION_JP
    { 136, 0, 0, 0 },
#endif
};

void (*scripted_slider_step_funcs[5])(struct MiscObj*) = {
    scripted_slider_slide,
    scripted_slider_brake,
    scripted_slider_idle,
    scripted_slider_follow_owner,
    func_800D11B0,
};

void (*scripted_slider_state_funcs[3])(struct MiscObj*) = {
    func_800D0E48,
    scripted_slider_main,
    scripted_slider_despawn,
};
