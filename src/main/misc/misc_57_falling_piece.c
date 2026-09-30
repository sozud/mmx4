// MiscObj, misc_object_update_funcs[57]
// 800D3388..800D3928
#include "common.h"

// falling_piece_init
INCLUDE_ASM("main/nonmatchings/misc/misc_57_falling_piece", func_800D3388);

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

void menu_text_init_label(struct UnkObj* self)
{
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32 temp_v1;

    self->unk40 = 0x1F00;
    temp_v1 = *addr_801F3000;
    self->bg_offset = -1;
    self->unk15 = 0;
    self->unk3C = temp_v1 + (s32)addr_801F3000;
    if (self->y_pos.i.hi == 0x10) {
        self->unk42 = 0x7802;
    } else {
        self->unk42 = 0x7800;
    }
    self->x_pos.i.hi = 0xA0;
    self->unk16 = 0;
    self->animation_step.fields.frame_index = self->unk2;
    self->state++;
    if (self->unk2 < 9) {
        self->state++;
    }
}

void menu_text_init_cursor(struct UnkObj* self)
{
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32* addr_801F3008 = (s32*)0x801F3008;
    u32 temp_v1;

    self->unk40 = 0x1E00;
    self->animation_table = option_toggle_animations;
    temp_v1 = *addr_801F3008;
    self->unk3C = temp_v1 + (s32)addr_801F3000;
    self->unk15 = 0;
    self->bg_offset = -1;
    if (self->unk2 == -1) {
        self->unk42 = 0x7806;
        self->y_pos.i.hi = self->link.data[D_80141BDF[0] * 2] + 8;
        self->ext.unk_0.selection_index = D_80141BDF[0];
        set_animation(self, 0);
    } else {
        self->unk42 = 0x784B;
        self->x_pos.i.hi = 0x60;
        self->y_pos.i.hi = 0xD0;
        self->animation_step.fields.frame_index = 0x29;
    }
    self->unk16 = 0;
    self->state = 3;
}

void menu_text_init(struct UnkObj* self)
{
    if (self->unk2 < 0) {
        menu_text_init_cursor(self);
    } else {
        menu_text_init_label(self);
    }
    is_on_screen(self);
}

void menu_text_highlight(struct UnkObj* self)
{
    s8 temp_v1; // probably fake

    if (self->y_pos.i.hi != 0x10) {
        if (self->unk7 == D_80141BDF[0]) {
            self->unk42 = 0x7803;
        } else {
            self->unk42 = 0x7800;
        }
    }
    if ((D_80141BE0 == 0) && (engine_obj.cur_character != CHARACTER_X)) {
        temp_v1 = self->unk7;
        if ((self->unk7 < 7) && (temp_v1 >= 5)) {
            self->unk42 = 0x7804;
        }
    }
    is_on_screen(self);
}

// menu_text_blink
INCLUDE_ASM("main/nonmatchings/misc/misc_57_falling_piece", func_800D3798);

void menu_text_cursor(struct UnkObj* self)
{
    if (self->unk2 == -1) {
        if (self->ext.unk_0.selection_index != D_80141BDF[0]) {
            self->y_pos.i.hi = self->link.data[D_80141BDF[0] * 2] + 8;
            self->ext.unk_0.selection_index = D_80141BDF[0];
        }
        animate_object(self);
    }
    is_on_screen(self);
}

union AnimationStep menu_text_anim_0[6] = {
    { .packed = 0x00010001 },
    { .packed = 0x01010001 },
    { .packed = 0x02010001 },
    { .packed = 0x03010001 },
    { .packed = 0x04010001 },
    { .packed = 0x05000001 },
};
union AnimationStep* menu_text_animations[1] = { menu_text_anim_0 };

void (*falling_piece_state_funcs[3])(struct MiscObj*) = {
    func_800D3388,
    falling_piece_fall,
    falling_piece_despawn,
};

extern u16 menu_button_bits_a[8];
extern u16 menu_button_bits_b[8];
