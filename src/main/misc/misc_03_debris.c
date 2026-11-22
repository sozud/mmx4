// MiscObj, misc_object_update_funcs[3]
// 800C813C..800C8774
#include "common.h"
#include "main/misc/misc_03_debris.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "weapon_resources.h"

void func_800C8610(struct MiscObj* arg0);
void debris_fall(struct MiscObj* arg0);

void spawn_debris(arg_u8 arg0, void* arg1, void* arg2)
{
    struct MiscObj* misc;
    struct MainObj* var_s2;
    u8* var_s3;
    s32 var_s1;

    var_s3 = arg1;
    var_s1 = arg0;
    var_s2 = arg2;
    while (var_s1 & 0xFF) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 3;
            misc->unk2 = 0;
            misc->unk15 = get_random() & PLAYER_FACING_RIGHT;
            misc->state = 0;
            misc->unk5 = 0;
            misc->unk6 = 0;
            misc->x_pos.val = var_s2->x_pos.val + ((get_random() & 3) << 16);
            misc->y_pos.val = var_s2->y_pos.val + ((get_random() & 3) << 16);
            misc->ext.misc_2.unk58 = *var_s3;
            var_s3 += 1;
            misc->ext.misc_2.owner = var_s2;
        }
        var_s1 -= 1;
    }
}

#ifndef VERSION_DEMO
void spawn_owner_debris(s32 arg0, u8* arg1, struct MainObj* arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 var_s1;
    u8* var_s3;
    s16 var_s4;
    struct MainObj* var_s2;
    struct MiscObj* misc;
    struct MiscObj* obj;

    var_s3 = arg1;
    var_s1 = arg0;
    var_s4 = arg3;
    var_s2 = arg2;
    while (var_s1 & 0xFF) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            obj = misc;
            obj->active = 0x41;
            obj->id = 3;
            obj->unk2 = 1;
            obj->unk15 = get_random() & PLAYER_FACING_RIGHT;
            obj->state = 0;
            obj->unk5 = 0;
            obj->unk6 = 0;
            obj->x_pos.val = var_s2->x_pos.val + (get_random() & 3) + arg4;
            obj->y_pos.val = var_s2->y_pos.val + (get_random() & 3) + arg5;
            obj->ext.misc_2.unk58 = (*var_s3);
            obj->ext.misc_2.owner = var_s2;
            obj->unk42 = var_s4;
            obj->unk3C = ANIMATED_OBJECT(obj->ext.misc_2.owner)->unk3C;
            obj->animation_table = ANIMATED_OBJECT(obj->ext.misc_2.owner)->animation_table;
            var_s3 += 1;
            obj->unk40 = obj->ext.misc_2.owner->unk40;
        }
        var_s1 -= 1;
    }
}
#endif

void spawn_debris_offset(u8 count, u8* variants, struct MainObj* owner, s32 x_offset, s32 y_offset)
{
    struct MiscObj* misc;
    struct MainObj* obj = owner;

    for (; count > 0; count--) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 3;
            misc->unk2 = 0;
            misc->unk15 = get_random() & PLAYER_FACING_RIGHT;
            misc->state = 0;
            misc->unk5 = 0;
            misc->unk6 = 0;
            misc->x_pos.val = obj->x_pos.val + (get_random() & 3) + x_offset;
            misc->y_pos.val = obj->y_pos.val + (get_random() & 3) + y_offset;
            misc->ext.misc_2.unk58 = *variants++;
            misc->ext.misc_2.owner = obj;
        }
    }
}

// spawn_animated_debris
void func_800C842C(u8 count, u8* variants, void* owner, s32 id, void* animation_table)
{
    struct MainObj* parent = owner;
    struct MiscObj* obj;
    s32 clut_x;
    u8 variant;

    for (; count != 0; count--) {
        obj = find_free_misc_obj();
        if (obj == NULL)
            continue;
        obj->active = 0x41;
        obj->id = 3;
        obj->unk2 = 1;
        obj->unk15 = get_random() & PLAYER_FACING_RIGHT;
        obj->state = 0;
        obj->unk5 = 0;
        obj->unk6 = 0;
        obj->x_pos.val = parent->x_pos.val + ((get_random() & 3) << 16);
        obj->y_pos.val = parent->y_pos.val + ((get_random() & 3) << 16);
        variant = *variants++;
        obj->ext.misc_2.unk58 = variant;
        obj->ext.misc_2.owner = parent;
        obj->animation_table = animation_table;
        clut_x = func_8002938C(id);
        obj->unk42 = OBJECT_CLUT(((clut_x * 4 + 0x18) % 16) | (((func_8002938C(id) + 6) / 4 + 0x1E0) << 6));
        obj->unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(id));
        obj->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(id)];
    }
}

void debris_update(struct MiscObj* self)
{
    if (self->state == 0) {
        func_800C8610(self);
    } else {
        debris_fall(self);
    }
}

// debris_init

extern s32 debris_x_speeds[8];
extern s32 debris_y_speeds[8];

void func_800C8610(struct MiscObj* arg0)
{
    arg0->on_screen = 1;
    if (arg0->unk2 == 0) {
        arg0->unk3C = (void*)arg0->ext.misc_2.owner->sprite_frames;
        arg0->animation_table = (u32**)arg0->ext.misc_2.owner->animation_table;
        arg0->unk40 = arg0->ext.misc_2.owner->unk40;
        arg0->unk42 = arg0->ext.misc_2.owner->unk42 & 0x7FFF;
    }
    arg0->unk16 = 1;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk2C = 0x5000;
    arg0->x_vel.val = debris_x_speeds[get_random() & 7] + arg0->ext.misc_2.owner->x_speed / 2;
    arg0->y_vel.val = debris_y_speeds[get_random() & 7];
    set_animation(arg0, arg0->ext.misc_2.unk58);
    arg0->state++;
    is_on_screen(BASE_OBJECT(arg0));
}

void debris_fall(struct MiscObj* self)
{
    u8 temp_v0;

    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        move_with_gravity((struct AnimatedObj*)self);
        animate_object(self);
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

s32 debris_x_speeds[8] = { -0x30000, -0x20000, 0x18000, 0x28000, -0x38000, -0x28000, 0x20000, 0x30000 };
s32 debris_y_speeds[8] = { 0x38000, 0x48000, 0x60000, 0x30000, 0x40000, 0x50000, 0x58000, 0x28000 };
