// MiscObj, misc_object_update_funcs[57]
// 800D3388..800D354C
#include "common.h"
#include "main/misc/misc_57_falling_piece.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#include "main/objects.h"
#include "main/2824.h"

// falling_piece_state_funcs
extern void (*falling_piece_state_funcs[])(struct MiscObj*);
void func_800D3388(struct MiscObj*);
void falling_piece_fall(struct MiscObj*);
void falling_piece_despawn(struct MiscObj*);
#include "weapon_resources.h"

extern union AnimationStep* falling_piece_animations[1];

// falling_piece_init
void func_800D3388(struct MiscObj* self)
{
    self->x_pos.u.hi = background_objects[0].x_pos.u.hi + ((get_random() & 0xFF) + 0x30);
    self->y_pos.u.hi = background_objects[0].y_pos.u.hi - 0x10;
    self->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0xA4));
    self->animation_table = (u32**)falling_piece_animations;
    self->unk42 = OBJECT_STAGE_CLUT(0xA4);
    self->bg_offset = 0;
    self->unk15 = 0;
    self->unk16 = 0x10;
    set_animation_frame(ANIMATED_OBJECT(self), 0, self->unk2);
    self->y_vel.val = 0xFFFE0000;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0x4200;
    self->state++;
}

void falling_piece_fall(struct MiscObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (func_8002B160(self) != 0) {
        self->state = 2;
    }
}

void falling_piece_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void falling_piece_update(struct MiscObj* self)
{
    falling_piece_state_funcs[self->state](self);
}

union AnimationStep falling_piece_anim_0[6] = {
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x01 },
    { 1, 0, 1, 0x02 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 0, 0x05 },
};
union AnimationStep* falling_piece_animations[1] = { falling_piece_anim_0 };

void (*falling_piece_state_funcs[3])(struct MiscObj*) = {
    func_800D3388,
    falling_piece_fall,
    falling_piece_despawn,
};
