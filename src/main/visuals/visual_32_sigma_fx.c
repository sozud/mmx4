// VisualObj, visual_object_update_funcs[32]
// 800B4E34..800B5570
#include "common.h"
#include "main/objects.h"
#include "main/visuals/visual_32_sigma_fx.h"
#include "main/55C4.h"
#include "main/object_motion.h"

// sigma_cloak_piece_funcs
extern void (*sigma_cloak_piece_funcs[])(struct VisualObj*);
void sigma_cloak_piece_wait(struct VisualObj*);
void sigma_cloak_piece_blink(struct VisualObj*);

// sigma_fx_subtype_funcs
extern void (*sigma_fx_subtype_funcs[])(struct VisualObj*);
void sigma_fx_glow(struct VisualObj*);
void sigma_fx_cloak_piece(struct VisualObj*);
void sigma_fx_oneshot(struct VisualObj*);
void sigma_fx_electric(struct VisualObj*);
void sigma_fx_electric(struct VisualObj*);
void sigma_fx_oneshot(struct VisualObj*);
void sigma_fx_hit_glow(struct VisualObj*);

// sigma_fx_state_funcs
extern void (*sigma_fx_state_funcs[])(struct VisualObj*);

void sigma_fx_run(struct VisualObj*);
void sigma_fx_despawn(struct VisualObj*);
#include "weapon_resources.h"
extern u8 sigma_fx_x_offsets[4];
extern u8 sigma_fx_y_offsets[4];
extern u8 sigma_fx_cloak_piece_animations[4];
extern s32 sigma_fx_cloak_piece_x_vels[8];
extern s32 sigma_fx_cloak_piece_y_vels[8];

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

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B4E34(struct VisualObj* self);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B4E34(struct VisualObj* self)
{
    struct PlayerObj* parent = self->unk50;

    self->state = 1;
    self->unk40 = parent->unk40;
    self->animation_table = parent->animation_table;
    self->unk3C = parent->unk3C;
    self->unk42 = parent->unk42;
    self->unk15 = parent->unk15;
    self->bg_offset = parent->bg_offset;
    self->x_pos.val = parent->x_pos.val;
    self->y_pos.val = parent->y_pos.val;
    self->unk16 = parent->unk16;

    switch (self->unk2) {
    case 0:
        self->unk16 = VISUAL_SATURN_LAYER(5);
        set_animation(self, 2);
        break;
    case 1:
        self->x_pos.i.hi += (parent->unk15 ? -1 : 1) * (s8)sigma_fx_x_offsets[get_random() & 3];
        self->y_pos.i.hi += (s8)sigma_fx_y_offsets[get_random() & 3];
        self->y_vel.val = sigma_fx_cloak_piece_y_vels[get_random() & 7];
        self->x_vel.val = sigma_fx_cloak_piece_x_vels[get_random() & 7];
        set_animation(self, sigma_fx_cloak_piece_animations[self->unk54]);
        self->unk54 = 0x14;
        break;
    case 2:
    case 5:
        self->unk16 = VISUAL_SATURN_LAYER(5);
        self->x_pos.i.hi += (parent->unk15 ? -1 : 1) * (s8)sigma_fx_x_offsets[get_random() & 3];
        self->y_pos.i.hi += (s8)sigma_fx_y_offsets[get_random() & 3];
        set_animation(self, 0xA);
        break;
    case 3:
        self->x_pos.val += self->unk15 ? 0x90000 : -0x90000;
        self->y_pos.val -= 0x160000;
        set_animation(self, 0x22);
        break;
    case 4:
        self->x_pos.val += self->unk15 ? -0x160000 : 0x160000;
        self->y_pos.val += 0x40000;
        set_animation(self, 0x24);
        break;
    case 6:
        self->unk16 = VISUAL_SATURN_LAYER(5);
        set_animation(self, 0x2A);
        self->unk42 &= 0x7FFF;
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/visuals/visual_32_sigma_fx", func_800B4E34);
#endif

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
                    shot->unk2 = self->unk2 + 1;
                    shot->timer = i;
                    shot->unk7C = WEAPON_OBJECT(self);
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
