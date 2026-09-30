// ShotObj, shot_object_update_funcs[25]
// 8009EB6C..8009EE68
#include "common.h"

void grenade_update(struct ShotObj* self)
{
    grenade_state_funcs[self->state](self);
}

// grenade_init
INCLUDE_ASM("main/nonmatchings/shots/shot_25_grenade", func_8009EBA8);

void grenade_fly(struct ShotObj* self)
{
    animate_object(self);
    move_with_gravity(self);
    func_8002D9BC(self);

    if (func_8002BB80(self, &g_Player) != 0) {
        if (self->unk2 & 0x40) {
        label:
            spawn_explosion(self);
        }
    } else if (!(self->unk2 & 0x40) || (CollisionRelated(self), self->unk70 == 0)) {
        if (func_8002B160(self) == 0) {
            is_on_screen(self);
            return;
        }
    } else {
        goto label; // unfortunately seems to be necessary for a match
    }

    self->state++;
}

void grenade_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void grenade_idle(struct ShotObj* self)
{
}

extern void (*train_boss_arm_step_funcs[11])(struct ShotObj*);

u8 grenade_hit_box[4] = { 0xF9, 0xF9, 0x0C, 0x0C };

u8 grenade_terrain_box[4] = { 0, 0, 4, 4 };

s8 grenade_spawn_offsets[8] = { 0x21, -0x2A, 0x30, -0x15, 0x28, 7, 0, 0 };

void (*grenade_state_funcs[])(struct ShotObj*) = {
    func_8009EBA8,
    grenade_fly,
    grenade_despawn,
    grenade_idle,
};
