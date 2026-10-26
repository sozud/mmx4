// MiscObj, misc_object_update_funcs[2]
// 800C7DA4..800C85D0
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
    u8* variant;
    s32 velocity;

    remaining = count;
    velocity = x_velocity;
    source_obj = source;
    if (remaining & 0xFF) {
        do {
            obj = find_free_misc_obj();
            if (obj != NULL) {
                obj->active = 0x41;
                obj->id = 2;
                obj->unk15 = get_random() & PLAYER_FACING_RIGHT;
                obj->state = 0;
                obj->unk5 = 0;
                obj->unk6 = 0;
                if (velocity != -1) {
                    obj->x_vel.val = velocity;
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
        } while (remaining & 0xFF);
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
void func_800C842C(s32 count, u8* variants, void* owner, s32 id, void* animation_table);
extern ret_u8 func_8002938C(s32);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/misc/misc_02_rubble", func_800C7F1C);
#else
void func_800C7F1C(struct MiscObj* arg0)
{
    s32 index;

    arg0->on_screen = 1;
    arg0->animation_step.fields.frame_index = arg0->ext.unk.unk54;
    if (engine_obj.stage == 3) {
        index = func_8002938C(0x8A);
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
        index = func_8002938C(0x8A);
        arg0->unk40 = (u16)((u32)OBJECT_STAGE_TEXTURE(index));
        arg0->unk42 = OBJECT_CLUT(0x7987);
    } else {
        index = func_8002938C(0x83);
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
        index = func_8002938C(0x83);
        arg0->unk40 = (u16)((u32)OBJECT_STAGE_TEXTURE(index));
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
#endif

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

void spawn_debris(arg_u8 arg0, void* arg1, void* arg2)
{
    s32 var_s1;
    u8* var_s3;
    struct MainObj* var_s2;
    struct MiscObj* temp_v0;

    var_s3 = arg1;
    var_s1 = arg0;
    var_s2 = arg2;
    if (var_s1 & 0xFF) {
        do {
            temp_v0 = find_free_misc_obj();
            if (temp_v0 != NULL) {
                temp_v0->active = 0x41;
                temp_v0->id = 3;
                temp_v0->unk2 = 0;
                temp_v0->unk15 = get_random() & PLAYER_FACING_RIGHT;
                temp_v0->state = 0;
                temp_v0->unk5 = 0;
                temp_v0->unk6 = 0;
                temp_v0->x_pos.val = var_s2->x_pos.val + ((get_random() & 3) << 16);
                temp_v0->y_pos.val = var_s2->y_pos.val + ((get_random() & 3) << 16);
                temp_v0->ext.misc_2.unk58 = *var_s3;
                var_s3 += 1;
                temp_v0->ext.misc_2.owner = var_s2;
            }
            var_s1 -= 1;
        } while (var_s1 & 0xFF);
    }
}

void spawn_owner_debris(s32 arg0, u8* arg1, struct MainObj* arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 var_s1;
    u8* var_s3;
    s16 var_s4;
    struct MainObj* var_s2;
    struct MiscObj* temp_v0;
    struct MiscObj* obj;

    var_s3 = arg1;
    var_s1 = arg0;
    var_s4 = arg3;
    var_s2 = arg2;
    if (var_s1 & 0xFF) {
        do {
            temp_v0 = find_free_misc_obj();
            if (temp_v0 != NULL) {
                obj = temp_v0;
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
        } while (var_s1 & 0xFF);
    }
}

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/misc/misc_02_rubble", spawn_debris_offset);
#else
void spawn_debris_offset(u8 count, u8* variants, struct MainObj* owner, s32 x_offset, s32 y_offset)
{
    u8 i;
    u8* vars = variants;
    s32 xoff = x_offset;
    struct MainObj* obj = owner;

    for (i = count; i; i--) {
        struct MiscObj* misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 3;
            misc->unk2 = 0;
            misc->unk15 = get_random() & PLAYER_FACING_RIGHT;
            misc->state = 0;
            misc->unk5 = 0;
            misc->unk6 = 0;
            misc->x_pos.val = obj->x_pos.val + (get_random() & 3) + xoff;
            misc->y_pos.val = obj->y_pos.val + (get_random() & 3) + y_offset;
            misc->ext.misc_2.unk58 = *vars++;
            misc->ext.misc_2.owner = obj;
        }
    }
}
#endif

// spawn_animated_debris
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800C842C(s32 count, u8* variants, void* owner, s32 id, void* animation_table)
{
    struct MiscObj* obj;
    s32 clut_x;
    s32 clut_y;
    s32 resource;

    for (; count & 0xFF; count--) {
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
        obj->x_pos.val = ((struct MainObj*)owner)->x_pos.val + ((get_random() & 3) << 16);
        obj->y_pos.val = ((struct MainObj*)owner)->y_pos.val + ((get_random() & 3) << 16);
        obj->ext.misc_2.owner = owner;
        obj->animation_table = animation_table;
        obj->ext.misc_2.unk58 = *variants++;
        clut_x = func_8002938C(id);
        clut_y = func_8002938C(id);
        obj->unk42 = OBJECT_CLUT(((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6));
        resource = func_8002938C(id);
        obj->unk40 = OBJECT_STAGE_TEXTURE(resource);
        resource = func_8002938C(id);
        obj->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    }
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_02_rubble", func_800C842C);
#endif

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
