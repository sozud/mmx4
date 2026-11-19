// MiscObj, misc_object_update_funcs[2]
// 800C7DA4..800C813C
#include "common.h"
#include "main/misc/misc_02_rubble.h"
#include "main/objects.h"
#include "main/object_motion.h"

extern s32 rubble_x_offsets[8];
extern s32 rubble_y_offsets[8];

void rubble_fall(struct MiscObj*);
#include "weapon_resources.h"

void spawn_rubble(arg_u8 count, u8* variants, void* source, s32 x_velocity)
{
    struct BaseObj* source_obj;
    struct MiscObj* obj;
    s32 remaining;

    remaining = count;
    source_obj = source;
    while (remaining & 0xFF) {
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 2;
            obj->unk15 = get_random() & PLAYER_FACING_RIGHT;
            obj->state = 0;
            obj->unk5 = 0;
            obj->unk6 = 0;
            if (x_velocity != -1) {
                obj->x_vel.val = x_velocity;
                obj->unk2 = 0;
            } else {
                obj->x_vel.val = 0;
                obj->unk2 = 1;
            }
            obj->x_pos.val = source_obj->x_pos.val + rubble_x_offsets[get_random() & 7];
            obj->y_pos.val = source_obj->y_pos.val + rubble_y_offsets[get_random() & 7];
            obj->ext.unk.unk54 = *variants++;
        }
        remaining--;
    }
}

void rubble_update(struct MiscObj* self)
{
    if (self->state == 0) {
        func_800C7F1C(self);
    } else {
        rubble_fall(self);
    }
}

// rubble_init

extern s32 rubble_x_speeds[8];
extern s32 rubble_y_speeds[8];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800C7F1C(struct MiscObj* arg0);
extern ret_u8 func_8002938C(s32);
#endif

void func_800C7F1C(struct MiscObj* arg0)
{
    arg0->on_screen = 1;
    arg0->animation_step.fields.frame_index = arg0->ext.unk.unk54;
    if (engine_obj.stage == 3) {
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x8A));
        arg0->unk40 = (u16)((u32)OBJECT_STAGE_TEXTURE(func_8002938C(0x8A)));
        arg0->unk42 = OBJECT_CLUT(0x7987);
    } else {
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x83));
        arg0->unk40 = (u16)((u32)OBJECT_STAGE_TEXTURE(func_8002938C(0x83)));
        if (arg0->unk2 == 0)
            arg0->unk42 = OBJECT_CLUT(0x7983);
        else
            arg0->unk42 = VISUAL_STAGE_PALETTE(func_8002938C(0x83));
    }
    arg0->unk16 = 1;
    arg0->unk2C = 0x5000;
    arg0->x_vel.val += rubble_x_speeds[get_random() & 7];
    arg0->y_vel.val = rubble_y_speeds[get_random() & 7];
    arg0->state++;
    is_on_screen(BASE_OBJECT(arg0));
}

void rubble_fall(struct MiscObj* self)
{
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        move_with_gravity(ANIMATED_OBJECT(self));
        if (FLICKER_ENABLED) {
            self->on_screen ^= 1;
        }
        if (self->on_screen != 0) {
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

s32 rubble_x_speeds[8] = { -0x30000, -0x20000, 0x18000, 0x28000, -0x38000, -0x28000, 0x20000, 0x30000 };
s32 rubble_y_speeds[8] = { 0x38000, 0x48000, 0x60000, 0x30000, 0x40000, 0x50000, 0x58000, 0x28000 };

s32 rubble_x_offsets[8] = {
    0x1F0000,
    0x190000,
    0x150000,
    0x120000,
    -0x1F0000,
    -0x190000,
    -0x150000,
    -0x120000,
};

s32 rubble_y_offsets[8] = {
    0x1F0000,
    0x190000,
    0x150000,
    0x120000,
    -0x1F0000,
    -0x190000,
    -0x150000,
    -0x120000,
};
