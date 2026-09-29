// VisualObj, visual_object_update_funcs[32]
// 800B4E34..800B5570
#include "common.h"

u8 sigma_fx_x_offsets[4] = { 0xF, 6, 0x16, 0xF0 };
u8 sigma_fx_y_offsets[4] = { 0xF8, 0x16, 2, 0xFF };
u8 sigma_fx_cloak_piece_animations[4] = { 0xD, 0xC, 0xD, 0xB };
s32 sigma_fx_cloak_piece_x_vels[8] = {
    -0x50000,
    -0x42000,
    0x45000,
    0x28000,
    -0x48000,
    -0x43000,
    0x50000,
    0x22000,
};
s32 sigma_fx_cloak_piece_y_vels[8] = {
    -0x10000,
    0x8000,
    0xC000,
    0x12000,
    0x10000,
    -0x8000,
    -0xC000,
    -0x12000,
};

// sigma_fx_init
INCLUDE_ASM("main/nonmatchings/visuals/visual_32", func_800B4E34);

void sigma_fx_glow(struct VisualObj* self)
{
    if (self->unk50->state >= 3) {
        self->state = 2;
    }
    animate_object(self);
    is_on_screen(self);
}

void sigma_cloak_piece_wait(struct VisualObj* self)
{
    if (--self->unk54 == 0) {
        self->unk54 = 30;
        self->unk5++;
    }
    is_on_screen(self);
}

void sigma_cloak_piece_blink(struct VisualObj* self)
{
    self->on_screen = 0;
    if (--self->unk54 == 0) {
        self->state = 2;
    }
    if (self->unk54 & 1) {
        is_on_screen(self);
    }
}

void sigma_fx_cloak_piece(struct VisualObj* self)
{
    sigma_cloak_piece_funcs[self->unk5](self);
    animate_object(self);
    move_object((struct MovingObj*)self);
}

void sigma_fx_oneshot(struct VisualObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->state = 2;
    }
    if (self->unk2 == 5) {
        self->on_screen = 0;
        if ((self->unk50->input.buttons.held & 1) != 0) {
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        is_on_screen(BASE_OBJECT(self));
    }
}

void sigma_fx_electric(struct VisualObj* self)
{
    u8 i;
    u8 shot_type;
    s8 state;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    state = self->unk5;
    if (state == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            self->unk5 = state + 1;
            i = 0;
            do {
                shot = find_free_shot_obj();
                if (shot != 0) {
                    shot->active = 0x41;
                    shot->id = 0x2E;
                    shot_type = self->unk2;
                    shot->timer = i;
                    shot->unk7C = WEAPON_OBJECT(self);
                    shot->unk2 = shot_type + 1;
                }
                i += 1;
            } while (i < 2);
            self->unk56 = 5;
        }
    } else if (--self->unk56 == 0) {
        self->state = 2;
    }
    is_on_screen(BASE_OBJECT(self));
    if (self->unk50->state == 2) {
        self->state = 2;
    }
}

void sigma_fx_hit_glow(struct VisualObj* self)
{
    struct PlayerObj* temp_s0 = self->unk50;
    animate_object(self);
    self->x_pos.val = temp_s0->x_pos.val;
    self->y_pos.val = temp_s0->y_pos.val;
    is_on_screen(self);
    if (MAIN_OBJECT(temp_s0)->ext.main_68.flash_timer == 0) {
        self->state = 2;
    }
}

void sigma_fx_run(struct VisualObj* self)
{
    sigma_fx_subtype_funcs[self->unk2](self);
}

void sigma_fx_despawn(struct VisualObj* self)
{
    if (self->unk2 == 1) {
        MAIN_OBJECT(self->unk50)->ext.main_68.count--;
    }
    ZeroObjectState(self);
}

void sigma_fx_update(struct VisualObj* self)
{
    sigma_fx_state_funcs[self->state](self);
}

void (*sigma_cloak_piece_funcs[])(struct VisualObj*) = {
    sigma_cloak_piece_wait,
    sigma_cloak_piece_blink,
};

void (*sigma_fx_subtype_funcs[])(struct VisualObj*) = {
    sigma_fx_glow,
    sigma_fx_cloak_piece,
    sigma_fx_oneshot,
    sigma_fx_electric,
    sigma_fx_electric,
    sigma_fx_oneshot,
    sigma_fx_hit_glow,
};

void (*sigma_fx_state_funcs[])(struct VisualObj*) = {
    func_800B4E34,
    sigma_fx_run,
    sigma_fx_despawn,
};
