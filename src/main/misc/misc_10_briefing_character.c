// MiscObj, misc_object_update_funcs[10]
// 800C9EAC..800CA0C8
#include "common.h"
#include "main/misc/misc_10_briefing_character.h"
#include "main/55C4.h"
#include "main/objects.h"

extern u32* briefing_x_partner_animations[];
extern u32* briefing_x_animations[];
extern u32* briefing_zero_animations[];
extern u32* briefing_zero_partner_animations[];

extern void (*g_MegamanInBriefingRoomUpdateFuncs[2])(struct MiscObj*);

// D_8010E578
void briefing_character_init(struct MiscObj* arg0);
void briefing_character_animate(struct MiscObj* arg0);
#include "weapon_resources.h"

// megaman standing in the briefing room. doesn't show
// up if nopped out
// asm(".rept 13 ; nop ; .endr");
void MegamanInBriefingRoomUpdate(struct MiscObj* self)
{
    g_MegamanInBriefingRoomUpdateFuncs[self->state](self);
}

// g_MegamanInBriefingRoomUpdateFuncs state 0
void briefing_character_init(struct MiscObj* self)
{
    if (self->unk2 == 0) {
        self->unk42 = OBJECT_CLUT(0x7883);
        self->unk40 = OBJECT_STAGE_TEXTURE(2);
        self->unk3C = (s8*)SP_MENU_FRAMES + SP_MENU_FRAMES[2];
        if (engine_obj.cur_character != CHARACTER_X) {
            self->animation_table = &briefing_zero_animations;
        } else {
            self->animation_table = &briefing_x_animations;
        }
        self->x_pos.val = FIXED(42);
        self->y_pos.val = FIXED(416);
    } else {
        self->unk42 = OBJECT_CLUT(0x7885);
        self->unk40 = OBJECT_STAGE_TEXTURE(3);
        self->unk3C = (s8*)SP_MENU_FRAMES + SP_MENU_FRAMES[3];
        if (engine_obj.cur_character != CHARACTER_X) {
            self->animation_table = &briefing_zero_partner_animations;
        } else {
            self->animation_table = &briefing_x_partner_animations;
        }
        self->x_pos.val = FIXED(282);
        self->y_pos.val = FIXED(432);
    }
    self->bg_offset = 0;
    self->unk15 = 0;
    self->unk16 = 3;
    self->state++;
    set_animation(self, 0);
    is_on_screen(self);
}

// g_MegamanInBriefingRoomUpdateFuncs state 1
// X doesn't appear in briefing room if nopped out
// asm(".rept 36 ; nop ; .endr");
void briefing_character_animate(struct MiscObj* self)
{
    if (self->unk2 == 0) {
        if (!(engine_obj.unk40 & 0x10)) {
            animate_object(self);
        } else {
            set_animation(self, engine_obj.unk40 & 0xF);
        }
    } else if (!(engine_obj.unk40 & 0x20)) {
        animate_object(self);
    } else {
        set_animation(self, engine_obj.unk40 & 0xF);
    }
    is_on_screen(self);
}

union AnimationStep D_8010E100[] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 90, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 89, 0, 1, 0x00 },
    { 1, 0, -13, 0x00 },
};
union AnimationStep D_8010E138[] = {
    { 6, 0, 1, 0x00 },
    { 5, 0, 1, 0x0F },
    { 1, 0, -2, 0x0F },
};

union AnimationStep D_8010E144[] = {
    { 6, 0, 1, 0x0F },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 90, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 89, 0, 1, 0x00 },
    { 1, 0, -13, 0x00 },
};

union AnimationStep D_8010E180[] = {
    { 3, 0, 1, 0x00 },
    { 6, 0, 1, 0x03 },
    { 6, 0, 1, 0x04 },
    { 6, 0, 1, 0x05 },
    { 5, 0, 1, 0x04 },
    { 1, 0, -2, 0x04 },
};

union AnimationStep D_8010E198[] = {
    { 6, 0, 1, 0x04 },
    { 6, 0, 1, 0x03 },
    { 4, 0, 1, 0x00 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 90, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 89, 0, 1, 0x00 },
    { 1, 0, -13, 0x00 },
};

union AnimationStep D_8010E1DC[] = {
    { 6, 0, 1, 0x10 },
    { 5, 0, 1, 0x11 },
    { 1, 0, -2, 0x11 },
};

union AnimationStep D_8010E1E8[] = {
    { 6, 0, 1, 0x10 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 90, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 89, 0, 1, 0x00 },
    { 1, 0, -13, 0x00 },
};

union AnimationStep D_8010E224[] = {
    { 6, 0, 0, 0x11 },
};

union AnimationStep D_8010E228[] = {
    { 3, 0, 1, 0x00 },
    { 4, 0, 1, 0x09 },
    { 8, 0, 0, 0x0A },
};

union AnimationStep D_8010E234[] = {
    { 6, 0, 1, 0x06 },
    { 6, 0, 1, 0x06 },
    { 5, 0, 1, 0x05 },
    { 4, 0, 1, 0x05 },
    { 1, 0, -3, 0x05 },
};

union AnimationStep D_8010E248[] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 90, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 89, 0, 1, 0x00 },
    { 1, 0, -13, 0x00 },
};

union AnimationStep D_8010E280[] = {
    { 3, 0, 1, 0x00 },
    { 6, 0, 1, 0x03 },
    { 6, 0, 1, 0x04 },
    { 6, 0, 1, 0x05 },
    { 5, 0, 1, 0x04 },
    { 1, 0, -2, 0x04 },
};

union AnimationStep D_8010E298[] = {
    { 6, 0, 1, 0x04 },
    { 6, 0, 1, 0x03 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 90, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 89, 0, 1, 0x00 },
    { 1, 0, -13, 0x00 },
};

union AnimationStep D_8010E2DC[] = {
    { 2, 0, 1, 0x06 },
    { 3, 0, 1, 0x07 },
    { 6, 0, 1, 0x06 },
    { 6, 0, 1, 0x08 },
    { 5, 0, 1, 0x06 },
    { 1, 0, -2, 0x06 },
};

union AnimationStep D_8010E2F4[] = {
    { 6, 0, 1, 0x06 },
    { 6, 0, 1, 0x07 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 90, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 89, 0, 1, 0x00 },
    { 1, 0, -13, 0x00 },
};

union AnimationStep D_8010E334[] = {
    { 6, 0, 0, 0x06 },
};

union AnimationStep D_8010E338[] = {
    { 3, 0, 1, 0x00 },
    { 4, 0, 1, 0x0A },
    { 8, 0, 0, 0x09 },
};

union AnimationStep D_8010E344[] = {
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 90, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 89, 0, 1, 0x00 },
    { 1, 0, -18, 0x00 },
};

union AnimationStep D_8010E390[] = {
    { 5, 0, 1, 0x06 },
    { 5, 0, 1, 0x07 },
    { 5, 0, 1, 0x08 },
    { 4, 0, 1, 0x09 },
    { 1, 0, -2, 0x09 },
};

union AnimationStep D_8010E3A4[] = {
    { 5, 0, 1, 0x07 },
    { 5, 0, 1, 0x06 },
    { 5, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 90, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 89, 0, 1, 0x00 },
    { 1, 0, -18, 0x00 },
};

union AnimationStep D_8010E3FC[] = {
    { 3, 0, 1, 0x06 },
    { 3, 0, 1, 0x0B },
    { 5, 0, 1, 0x0A },
    { 5, 0, 1, 0x0C },
    { 4, 0, 1, 0x0B },
    { 1, 0, -2, 0x0B },
};

union AnimationStep D_8010E414[] = {
    { 5, 0, 1, 0x0B },
    { 5, 0, 1, 0x06 },
    { 5, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 90, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x01 },
    { 89, 0, 1, 0x00 },
    { 1, 0, -18, 0x00 },
};

union AnimationStep D_8010E46C[] = {
    { 5, 0, 0, 0x0B },
};

union AnimationStep D_8010E470[] = {
    { 5, 0, 1, 0x06 },
    { 8, 0, 0, 0x0D },
};

union AnimationStep D_8010E478[] = {
    { 5, 0, 1, 0x04 },
    { 4, 0, 1, 0x05 },
    { 1, 0, -2, 0x05 },
};

union AnimationStep D_8010E484[] = {
    { 33, 0, 1, 0x00 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 5, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 90, 0, 1, 0x00 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 5, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 5, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 1, 0, -18, 0x00 },
};

union AnimationStep D_8010E4D0[] = {
    { 6, 0, 1, 0x00 },
    { 5, 0, 1, 0x01 },
    { 1, 0, -2, 0x01 },
};

union AnimationStep D_8010E4DC[] = {
    { 6, 0, 1, 0x05 },
    { 5, 0, 1, 0x06 },
    { 1, 0, -2, 0x06 },
};

union AnimationStep D_8010E4E8[] = {
    { 1, 0, 0, 0x05 },
};

u32* briefing_x_partner_animations[] = {
    D_8010E100,
    D_8010E228,
    D_8010E138,
    D_8010E144,
    D_8010E180,
    D_8010E198,
    D_8010E1DC,
    D_8010E1E8,
    D_8010E224,
    D_8010E234,
};

u32* briefing_x_animations[] = {
    D_8010E248,
    D_8010E338,
    D_8010E280,
    D_8010E298,
    D_8010E280,
    D_8010E298,
    D_8010E2DC,
    D_8010E2F4,
    D_8010E334,
};

u32* briefing_zero_animations[] = {
    D_8010E344,
    D_8010E470,
    D_8010E478,
    D_8010E344,
    D_8010E390,
    D_8010E3A4,
    D_8010E3FC,
    D_8010E414,
    D_8010E46C,
};

u32* briefing_zero_partner_animations[] = {
    D_8010E484,
    D_8010E484,
    D_8010E4D0,
    D_8010E484,
    D_8010E4DC,
    D_8010E484,
    D_8010E4E8,
};

void (*g_MegamanInBriefingRoomUpdateFuncs[])(struct MiscObj*) = {
    briefing_character_init,
    briefing_character_animate,
};
