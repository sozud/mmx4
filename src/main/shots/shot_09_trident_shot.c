// ShotObj, shot_object_update_funcs[9]
// 8009B07C..8009B3E8
#include "common.h"

u8 trident_shot_flash_box[4] = { 0xCB, 0xD0, 0x2C, 0x3A };
u8 trident_shot_hit_box[4] = { 0xFB, 0xFC, 0x0D, 0x06 };
s8 trident_shot_muzzle_offsets[6][2] = {
    { 0, 0x18 },
    { -0x14, 0x14 },
    { -0x20, 0 },
    { -9, -5 },
    { -0x0E, 0x0C },
    { 0, 0 },
};

void trident_shot_update(struct ShotObj* self)
{
    trident_shot_state_funcs[self->state](self);
}

// trident_shot_flash_init
INCLUDE_ASM("main/nonmatchings/shots/shot_09_trident_shot", func_8009B0B8);

void trident_shot_flash(struct ShotObj* self)
{
    s32 temp_v0;

    animate_object(ANIMATED_OBJECT(self));
    temp_v0 = self->unk84.value - 1;
    self->unk84.value = temp_v0;
    if (temp_v0 != 0) {
        if (*(u32*)self->unk7C != 0) {
            func_8002D9BC(self);
            func_8002DD04(MAIN_OBJECT(self));
            if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
                update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
                return;
            }
        }
    }
    self->state = 2;
}

void trident_shot_flash_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

// trident_shot_init
INCLUDE_ASM("main/nonmatchings/shots/shot_09_trident_shot", func_8009B1E8);

void trident_shot_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(self);
        self->state = 5;
    } else {
        self->unk42 &= 0x7FFF;
    }
    if (func_8002BB80(self, &g_Player) != 0) {
        self->state = 5;
    }
    if (engine_obj.character_state.bytes[0] != 0) {
        self->state = 5;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
        return;
    }
    self->state = 5;
}

void trident_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*trident_shot_state_funcs[])(struct ShotObj*) = {
    func_8009B0B8,
    trident_shot_flash,
    trident_shot_flash_despawn,
    func_8009B1E8,
    trident_shot_fly,
    trident_shot_despawn,
};
