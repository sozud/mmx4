// ShotObj, shot_object_update_funcs[21]
// 8009D200..8009D74C
#include "common.h"

u8 cannon_shell_hit_box[4] = { 0xF7, 0xF8, 0x11, 0x11 };
u8 cannon_shell_flat_hit_box[4] = { 0xF3, 0xFC, 0x18, 0x0B };
u8 cannon_shell_steep_hit_box[4] = { 0xFC, 0xF4, 0x08, 0x18 };
u8 cannon_shell_terrain_box[4] = { 0, 0, 5, 5 };
u8 cannon_shell_flat_terrain_box[4] = { 0, 2, 0x0A, 4 };
u8 cannon_shell_steep_terrain_box[4] = { 0, 0, 4, 0x0A };

void cannon_shell_update(struct ShotObj* self)
{
    cannon_shell_state_funcs[self->state](self);
}

// cannon_shell_init
INCLUDE_ASM("main/nonmatchings/shots/shot_21", func_8009D23C);

void cannon_shell_fly(struct ShotObj* self)
{
    struct MiscObj* misc;
    s16 y;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state++;
        return;
    }
    func_8002D9BC(self);
    if (self->unk84.value != 0) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
    func_8009D588(self);
    if (self->y_pos.i.hi >= background_objects[0].y_pos.i.hi + 0xE0) {
        self->unk70 = 1;
    }
    if (self->unk70 != 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state++;
        return;
    }
    if (self->unk7 == 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x21;
            misc->id = 0x17;
            misc->unk2 = 0;
            misc->unk15 = get_random() & 0x40;
            misc->ext.unk.unk54 = 0;
            misc->x_pos.i.hi = self->x_pos.i.hi;
            y = self->y_pos.i.hi;
            misc->unk7 = 1;
            misc->x_vel.val = 0;
            misc->y_vel.val = 0;
            misc->unk16 = 7;
            misc->y_pos.i.hi = y;
        }
        self->unk7 = 1;
    } else {
        self->unk7--;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x120, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else {
        self->state++;
    }
}

void cannon_shell_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void cannon_shell_idle(struct ShotObj* self)
{
}

// cannon_shell_update_facing
INCLUDE_ASM("main/nonmatchings/shots/shot_21", func_8009D588);

void (*cannon_shell_state_funcs[])(struct ShotObj*) = {
    func_8009D23C,
    cannon_shell_fly,
    cannon_shell_despawn,
    cannon_shell_idle,
};
