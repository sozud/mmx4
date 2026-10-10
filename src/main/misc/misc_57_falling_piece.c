// MiscObj, misc_object_update_funcs[57]
// 800D3388..800D3928
#include "common.h"

extern union AnimationStep* menu_text_animations[1];

// falling_piece_init
void func_800D3388(struct MiscObj* self)
{
    self->x_pos.u.hi = background_objects[0].x_pos.u.hi + ((get_random() & 0xFF) + 0x30);
    self->y_pos.u.hi = background_objects[0].y_pos.u.hi - 0x10;
    self->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0xA4));
    self->animation_table = (u32**)menu_text_animations;
    self->unk42 = CLUT_FROM_ID(0xA4);
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
    s32* addr_801F3008;

    self->unk40 = 0x1E00;
    self->animation_table = option_toggle_animations;
    self->unk3C = (*((s32*)0x801F3008)) + (s32)addr_801F3000;
    self->unk15 = 0;
    self->bg_offset = -1;
    if (self->unk2 == -1) {
        self->unk42 = 0x7806;
        self->y_pos.i.hi = self->link.data[main_bss_state.transition.selection * 2] + 8;
        self->ext.unk_0.selection_index = main_bss_state.transition.selection;
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

#ifdef MMX4_WIN32
    if (self->y_pos.i.hi != 0x10 && self->y_pos.i.hi != 1) {
#else
    if (0x10 != self->y_pos.i.hi) {
#endif
        if (self->unk7 == main_bss_state.transition.selection) {
            self->unk42 = 0x7803;
        } else {
            self->unk42 = 0x7800;
        }
    }
    if ((main_bss_state.character_mode == 0) && (engine_obj.cur_character != CHARACTER_X)) {
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
        if (self->ext.unk_0.selection_index != main_bss_state.transition.selection) {
            self->y_pos.i.hi = self->link.data[main_bss_state.transition.selection * 2] + 8;
            self->ext.unk_0.selection_index = main_bss_state.transition.selection;
        }
        animate_object(self);
    }
    is_on_screen(self);
}

union AnimationStep menu_text_anim_0[6] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05000001 },
};
union AnimationStep* menu_text_animations[1] = { menu_text_anim_0 };

void (*falling_piece_state_funcs[3])(struct MiscObj*) = {
    func_800D3388,
    falling_piece_fall,
    falling_piece_despawn,
};

extern u16 menu_button_bits_a[8];
extern u16 menu_button_bits_b[8];
