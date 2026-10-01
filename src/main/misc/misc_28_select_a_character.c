// MiscObj, misc_object_update_funcs[28]
// 800CCA34..800CD78C
#include "common.h"

static inline void set_engine_flags(u8 flags)
{
    engine_flags = flags;
}

enum SubTypes {
    X_PORTRAIT,
    ZERO_PORTRAIT,
    PLAYER_SELECT_UPPER,
    PLAYER_SELECT_LOWER,
    SELECTOR = 6,
    X_CHARACTER,
    ZERO_CHARACTER,
};

// SelectACharacterUpdate state 0
void select_char_init(struct MiscObj* self)
{
    s8 temp_v0;
    s8 temp_v1_2;

    temp_v0 = self->unk2 - 7;
    switch (temp_v0) {
    case 0:
    case 2:
    case 3:
        self->unk40 = D_801406A8[2] >> 7;
        self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[2];
        self->unk42 = 0x7840;
        self->animation_table = select_char_x_animations;
        self->unk15 = 0x40;
        break;
    case 1:
    case 4:
        self->unk40 = D_801406A8[0] >> 7;
        self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[0];
        self->unk42 = 0x7800;
        self->animation_table = select_char_zero_animations;
        self->unk15 = 0;
        break;
    default:
        self->unk40 = D_801406A8[1] >> 7;
        self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[1];
        self->unk42 = (((select_char_palettes[self->unk2] * 4) + 4) % 16) | ((((select_char_palettes[self->unk2] + 1) / 4) + 0x1E0) << 6);
        self->animation_table = select_char_menu_animations;
        break;
    }
    temp_v1_2 = 2;
    if (self->unk2 < 9) {
        self->x_pos.val = FIXED(select_char_positions[self->unk2].x);
        self->y_pos.val = FIXED(select_char_positions[self->unk2].y);
    }
    if (self->unk2 > 0xB) {
        s32 temp = self->unk2 - 0xC;
        self->x_pos.val = FIXED(select_char_text_positions[temp].x);
        self->y_pos.val = FIXED(select_char_text_positions[(self->unk2 - 0xC)].y);
    }
    self->unk16 = select_char_priorities[self->unk2];
    set_animation(self, select_char_initial_animations[self->unk2]);
    self->bg_offset = -1;
    self->x_vel.val = 0;
    self->y_vel.val = 0;
    self->ext.title_logo.palette_shift_speed = 0;
    self->ext.title_logo.unk57 = 0;
    self->unk6 = 0;
    self->unk7 = 0;
    self->state++;
    self->unk5 = self->unk2;
}

// select_char_portrait_funcs state 0
void select_char_portrait_slide_in(struct MiscObj* self)
{
    // set speeds of portraits when "select a character"
    // screen first starts and portraits come in
    if (self->unk2 != X_PORTRAIT) {
        self->x_vel.val = FIXED(-16); // speed of Zero portrait
    } else {
        self->x_vel.val = FIXED(16); // speed of X portrait
    }
    if (((self->unk2 == X_PORTRAIT) && (self->x_pos.i.hi == 96)) || ((self->unk2 == ZERO_PORTRAIT) && (self->x_pos.i.hi == 224))) {
        engine_obj.character_state.bytes[2] |= 1 << self->unk2;
        self->unk6++;
        return;
    }
    move_object((struct MovingObj*)self);
}

// select_char_portrait_funcs state 1
void select_char_portrait_wait_select(struct MiscObj* self)
{
    if (engine_obj.character_state.bytes[1] & 0x80) {
        self->unk6++;
        // sets how fast the X and Zero portraits move
        // to the left and right after selecting a character
        if (self->unk2 != X_PORTRAIT) {
            self->x_vel.val = FIXED(16);
        } else {
            self->x_vel.val = FIXED(-16);
        }
    }
}

// select_char_portrait_funcs state 2
void select_char_portrait_slide_out(struct MiscObj* self)
{
    move_object((struct MovingObj*)self);
    if (self->on_screen == 0) {
        self->state++;
    }
}

// select_char_portrait_funcs state 3
void select_char_portrait_bounce(struct MiscObj* self)
{
    switch (self->unk7) {
    case 0:
        self->x_vel.val = FIXED(16);
        /* fallthrough */
    case 1:
        move_object((struct MovingObj*)self);
        if (self->on_screen == 0) {
            self->ext.sel_char.blast_timer = 20;
            self->unk7++;
            return;
        }
        return;
    case 2:
        if (--self->ext.sel_char.blast_timer == 0) {
            self->x_vel.val = FIXED(-16);
            self->unk7++;
            return;
        }
        break;
    case 3:
        move_object((struct MovingObj*)self);
        if (self->x_pos.i.hi == 0xE0) {
            self->unk6 = 1;
            self->unk7 = 0;
        }
        break;
    }
}

// select_char_subtype_funcs state 0, 1
void select_char_portrait(struct MiscObj* self)
{
    select_char_portrait_funcs[self->unk6](self);
}

// select_char_scroll_text_funcs state 0
void select_char_scroll_text_init(struct MiscObj* self)
{
    switch (self->unk2) {
    case PLAYER_SELECT_UPPER:
        // set velocity of upper "PLAYER SELECT" text
        self->x_vel.val = FIXED(-2) | FIXED(.5);
        break;
    case PLAYER_SELECT_LOWER:
        // lower player select text
        self->x_vel.val = FIXED(1) | FIXED(.5);
        break;
    case 12:
    case 14:
        self->x_vel.val = FIXED(4);
        break;
    case 13:
        self->x_vel.val = FIXED(-4);
        break;
    default:
        self->x_vel.val = FIXED(0);
        break;
    }
    self->unk6++;
}

const u32 padding = 0;

// select_char_scroll_text_funcs state 1
void select_char_scroll_text_move(struct MiscObj* self)
{
    move_object((struct MovingObj*)self);
    switch (self->unk2) {
    case PLAYER_SELECT_UPPER:
        // when top "PLAYER SELECT" goes off to the left,
        // wrap it around
        if (self->x_pos.i.hi < -112) {
            self->x_pos.i.hi = 432;
        }
        break;
    case PLAYER_SELECT_LOWER:
        // when bottom "PLAYER SELECT" goes off to the right,
        // wrap it around
        if (self->x_pos.i.hi > 432) {
            self->x_pos.i.hi = -112;
            return;
        }
        break;
    case 12:
        if (self->x_pos.i.hi == 126) {
            self->x_vel.val = 0;
        }
        break;
    case 13:
        if (self->x_pos.i.hi == 160) {
            self->x_vel.val = 0;
        }
        break;
    case 14:
        if (self->x_pos.i.hi == 278) {
            self->x_vel.val = 0;
        }
        break;
    }
}

// scrolling text doesn't appear if nopped out
// asm(".rept 26 ; nop ; .endr");
// select_char_subtype_funcs state 2,3,4,5,12,13,14
void select_char_scroll_text(struct MiscObj* self)
{
    select_char_scroll_text_funcs[self->unk6](self);
    if (engine_obj.character_state.bytes[1] & 0x80) {
        self->state++;
    }
}

// select_char_selector_funcs state 0
void select_char_selector_move(struct MiscObj* self)
{
    if (engine_obj.cur_character != CHARACTER_X) {
        set_animation(self, 9);
        self->x_pos.i.hi = 224; // zero is selected, move selector graphic to right
    } else {
        set_animation(self, 8);
        self->x_pos.i.hi = 96; // X is selected, move selector graphic to left
    }
    self->y_pos.i.hi = 120; // set y pos of green selector
    do {
    } while (0);
    self->unk6++;
}

// select_char_selector_funcs state 1
void select_char_selector_animate(struct MiscObj* self)
{
    animate_object(self);
    if (engine_obj.cur_character != self->ext.sel_char.cur_character_selected) {
        self->unk6 = 0;
        func_8001540C(5, 0, NULL);
    }
    self->ext.sel_char.cur_character_selected = engine_obj.cur_character;
}

// select_char_subtype_funcs state 6
// green selector graphic around X doesn't animate if nopped out
// asm(".rept 26 ; nop ; .endr");
void select_char_selector(struct MiscObj* self)
{
    select_char_selector_funcs[self->unk6](self);
    if (engine_obj.character_state.bytes[1] & 0x80) {
        self->state++;
    }
}

// select_char_character_funcs state 0
void select_char_character_idle(struct MiscObj* self)
{
    struct MiscObj* obj;

    if (engine_obj.character_state.bytes[0] != 0) {
        self->unk5 = 0xF;
        self->unk6 = 0;
        return;
    }
    if (engine_obj.cur_character == (self->unk2 - 7)) {
        if (self->ext.sel_char.blast_timer == 0) {
            self->unk6++;
            set_animation(self, 1);
            if (self->unk2 == X_CHARACTER) {
                obj = find_free_misc_obj();
                // create "blast" right before charged shot comes out
                // still id 0x1C but different unk2
                if (obj != NULL) {
                    obj->active = 0x41;
                    obj->id = 0x1C;
                    obj->unk2 = 0xA;
                    obj->x_pos.i.hi = self->x_pos.i.hi;
                    obj->y_pos.i.hi = self->y_pos.i.hi;
                }
            }
        } else {
            self->ext.sel_char.blast_timer--;
        }
    }
}

// select_char_character_funcs state 1
void select_char_character_shoot(struct MiscObj* self)
{
    struct BaseObj* obj;

    animate_object(self);
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        obj = (struct BaseObj*)find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x1C;
            obj->unk2 = 0xB;
            obj->x_pos.i.hi = self->x_pos.i.hi;
            obj->y_pos.i.hi = self->y_pos.i.hi;
        }
    }

    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 0;
        self->ext.sel_char.blast_timer = (self->ext.sel_char.unk54 & 1) ? 0x96 : 0x5A;
        self->ext.sel_char.unk54++;
        if (engine_obj.character_state.bytes[0] != 0) {
            self->unk5 = 0xF;
        }
        set_animation(self, 0);
    }
}

// select_char_subtype_funcs state 7,8
void select_char_character(struct MiscObj* self)
{
    select_char_character_funcs[self->unk6](self);
    if ((engine_obj.cur_character != (self->unk2 - 7)) && (self->animation_step.fields.relative_step == 0)) {
        self->unk6 = 0;
        self->ext.sel_char.blast_timer = 0;
    }
}

// select_char_subtype_funcs state 9
void select_char_charged_shot_fly(struct MiscObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        // set speed and position of X's charged shot
        self->x_vel.val = FIXED(10);
        self->x_pos.i.hi += 3;
        self->y_pos.i.hi -= 7;
    }
    animate_object(self);
    move_object((struct MovingObj*)self);
    if (self->x_pos.i.hi > 160) {
        self->state++;
    }
}

// select_char_subtype_funcs state 10, 11
void select_char_shot_burst(struct MiscObj* self)
{
    struct MiscObj* temp_v0;

    animate_object(self);
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        temp_v0 = find_free_misc_obj();
        // create X charged shot object
        if (temp_v0 != NULL) {
            temp_v0->active = 0x41;
            temp_v0->id = 0x1C;
            temp_v0->unk2 = 9;
            temp_v0->x_pos.i.hi = self->x_pos.i.hi;
            temp_v0->y_pos.i.hi = self->y_pos.i.hi;
        }
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->state++;
    }
}

// select_char_subtype_funcs state 15
void select_char_character_exit(struct MiscObj* self)
{
    switch (self->unk6) {
    case 0:
        self->unk6++;
        if (engine_obj.cur_character == (self->unk2 - 7)) {
            set_animation(self, 3);
        } else {
            set_animation(self, 0);
        }
        break;
    case 1:
        animate_object(self);
        if (self->animation_step.fields.relative_step == 0) {
            set_engine_flags(engine_flags | (1 << (self->unk2 - 7)));
        }
        if ((s8)engine_flags & 0x80) {
            self->unk6 = (u8)self->unk6 + 1;
            set_animation(self, 4);
        }
        break;
    case 2:
        animate_object(self);
        if (self->animation_step.fields.relative_step == 0) {
            self->unk6 = (u8)self->unk6 + 1;
            set_animation(self, 5);
            self->y_vel.val = 0x80000;
        }
        break;
    case 3:
        animate_object(self);
        move_object((struct MovingObj*)self);
        if (self->on_screen == 0) {
            set_engine_flags(engine_flags & ~(1 << (self->unk2 - 7)));
            self->state = (u8)self->state + 1;
        }
        break;
    }
}

// SelectACharacterUpdate state 1
void select_char_main(struct MiscObj* self)
{
    select_char_subtype_funcs[self->unk5](self);
    update_on_screen(self, 0x80, 0x30);
}

// SelectACharacterUpdate state 2
void select_char_despawn(struct MiscObj* self)
{
    ZeroObjectState(self);
}

// select a character menu never appears if nopped out
void SelectACharacterUpdate(struct MiscObj* self)
{
    g_SelectACharacterUpdateFuncs[self->state](self);
}

u32 D_8010E968[1] = {
    0x00000008,
};

u32 D_8010E96C[8] = {
    0x01010001,
    0x02010001,
    0x03010002,
    0x04010002,
    0x0501000c,
    0x06010005,
    0x07010004,
    0x08000003,
};

u32 D_8010E98C[7] = {
    0x09010002,
    0x0a010002,
    0x0b010002,
    0x0c010001,
    0x0c010101,
    0x0d010002,
    0x0e000002,
};

u32 D_8010E9A8[3] = {
    0x0f010103,
    0x10010103,
    0x11fe0103,
};

u32 D_8010E9B4[2] = {
    0x1201010a,
    0x12000101,
};

u32 D_8010E9BC[5] = {
    0x13010103,
    0x14010103,
    0x15010103,
    0x16010103,
    0x17000103,
};

u32 D_8010E9D0[1] = {
    0x18000103,
};

u32 D_8010E9D4[1] = {
    0x00000001,
};

u32 D_8010E9D8[18] = {
    0x01010004,
    0x02010002,
    0x03010101,
    0x05010001,
    0x07010002,
    0x09010002,
    0x0b010002,
    0x0d010002,
    0x0f010003,
    0x11010003,
    0x13010004,
    0x15010002,
    0x16010002,
    0x17010002,
    0x18010004,
    0x19010006,
    0x1a010004,
    0x00000006,
};

u32 D_8010EA20[9] = {
    0x04010001,
    0x06010001,
    0x08010002,
    0x0a010002,
    0x0c010002,
    0x0e010002,
    0x10010003,
    0x12010003,
    0x14000004,
};

u32 D_8010EA44[9] = {
    0x00010001,
    0x1b010001,
    0x1c010001,
    0x1d010001,
    0x1e010001,
    0x1f010003,
    0x20010006,
    0x21010011,
    0x21000001,
};

u32 D_8010EA68[6] = {
    0x1e010004,
    0x22010003,
    0x23010002,
    0x24010002,
    0x25010002,
    0x26000002,
};

u32 D_8010EA80[2] = {
    0x27010002,
    0x28ff0002,
};

u32 D_8010EA88[1] = {
    0x00000001,
};

u32 D_8010EA8C[1] = {
    0x01000001,
};

u32 D_8010EA90[1] = {
    0x02000001,
};

u32 D_8010EA94[1] = {
    0x03000001,
};

u32 D_8010EA98[1] = {
    0x04000001,
};

u32 D_8010EA9C[1] = {
    0x05000001,
};

u32 D_8010EAA0[1] = {
    0x06000001,
};

u32 D_8010EAA4[1] = {
    0x07000001,
};

u32 D_8010EAA8[4] = {
    0x08010003,
    0x09010003,
    0x08010003,
    0x0afd0003,
};

u32 D_8010EAB8[4] = {
    0x0b010003,
    0x0c010003,
    0x0b010003,
    0x0dfd0003,
};

u32* select_char_x_animations[7] = {
    D_8010E968,
    D_8010E96C,
    D_8010E98C,
    D_8010E9B4,
    D_8010E9BC,
    D_8010E9D0,
    D_8010E9A8,
};
u32* select_char_zero_animations[6] = {
    D_8010E9D4,
    D_8010E9D8,
    D_8010EA20,
    D_8010EA44,
    D_8010EA68,
    D_8010EA80,
};
u32* select_char_menu_animations[10] = {
    D_8010EA88,
    D_8010EA8C,
    D_8010EA90,
    D_8010EA94,
    D_8010EA98,
    D_8010EA9C,
    D_8010EAA0,
    D_8010EAA4,
    D_8010EAA8,
    D_8010EAB8,
};

u8 select_char_initial_animations[16] = { 0, 1, 2, 2, 3, 4, 8, 0, 0, 6, 2, 2, 5, 7, 6, 0 };
u8 select_char_palettes[16] = { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 0 };
u8 select_char_priorities[16] = { 5, 5, 5, 5, 2, 2, 4, 3, 3, 3, 3, 3, 0, 0, 0, 0 };
struct CharacterSelectPosition select_char_positions[9] = {
    { -112, 120 },
    { 432, 120 },
    { 432, 21 },
    { -112, 208 },
    { 85, 120 },
    { 229, 120 },
    { 96, 120 },
    { 32, 160 },
    { 288, 160 },
};
struct CharacterSelectPosition select_char_text_positions[3] = {
    { -192, 56 },
    { -40, 56 },
    { 432, 56 },
};

void (*select_char_portrait_funcs[])(struct MiscObj*) = {
    select_char_portrait_slide_in,
    select_char_portrait_wait_select,
    select_char_portrait_slide_out,
    select_char_portrait_bounce,
};

// unreferenced
u32 select_char_unused_0 = 0x0000A07E;

void (*select_char_scroll_text_funcs[])(struct MiscObj*) = {
    select_char_scroll_text_init,
    select_char_scroll_text_move,
};

void (*select_char_selector_funcs[])(struct MiscObj*) = {
    select_char_selector_move,
    select_char_selector_animate,
};

void (*select_char_character_funcs[])(struct MiscObj*) = {
    select_char_character_idle,
    select_char_character_shoot,
};

// unreferenced
u32 select_char_unused_1 = 0xFFFE0002;

void (*select_char_subtype_funcs[])(struct MiscObj*) = {
    select_char_portrait,
    select_char_portrait,
    select_char_scroll_text,
    select_char_scroll_text,
    select_char_scroll_text,
    select_char_scroll_text,
    select_char_selector,
    select_char_character,
    select_char_character,
    select_char_charged_shot_fly,
    select_char_shot_burst,
    select_char_shot_burst,
    select_char_scroll_text,
    select_char_scroll_text,
    select_char_scroll_text,
    select_char_character_exit,
};

void (*g_SelectACharacterUpdateFuncs[])(struct MiscObj*) = {
    select_char_init,
    select_char_main,
    select_char_despawn,
};
