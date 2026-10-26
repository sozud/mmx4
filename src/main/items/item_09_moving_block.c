// ItemObj, item_object_update_funcs[9]
// 800C20AC..800C24E0
#include "common.h"
#include "main/items/item_09_moving_block.h"
#include "main/objects.h"
#include "main/object_motion.h"

// moving_block_state_funcs
extern void (*moving_block_state_funcs[])(struct ItemObj*);

void moving_block_despawn(struct ItemObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/object_motion.h"
#endif

extern u8 moving_block_terrain_box[4];

void moving_block_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    moving_block_state_funcs[arg0->state](arg0);
}

// moving_block_init
void func_800C20F4(struct ItemObj* self)
{
    self->active = 0x41;
    self->state++;
    self->bg_offset = g_Player.bg_offset;
    self->unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(0xA1));
    self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0xA1));
    self->unk42 = OBJECT_STAGE_CLUT(0xA1);
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->animation_step.fields.frame_index = 0;
    self->unk5C = 0;
    self->unk61 = 0;
    self->unk54 = NULL;
    self->unk68 = (struct Unk_unk68*)(moving_block_terrain_box + 4 * self->unk2);
    self->x_vel.val = moving_block_motion[self->unk2].x_velocity;
    self->y_vel.val = moving_block_motion[self->unk2].y_velocity;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk7C.saved_pos.x = self->x_pos.u.hi;
    self->unk7C.saved_pos.y = self->y_pos.u.hi;
    if (g_Player.x_pos.val < self->x_pos.val) {
        self->x_vel.val = -self->x_vel.val;
    }
    self->unk75 = 0;
    self->unk76 = 0;
}

// moving_block_move

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800C229C(struct ItemObj* self);
void collide_with_players(struct PlayerObj*);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/items/item_09_moving_block", func_800C229C);
#else
void func_800C229C(struct ItemObj* self)
{
    s32 velocity;

    if ((u8)self->ext.item_2.unk80 == 0)
        move_object(MOVING_OBJECT(self));
    else
        self->ext.item_2.unk80--;
    if (moving_block_motion[self->unk2].vertical == 0) {
        velocity = self->x_vel.val;
        if (velocity > 0) {
            if (self->x_pos.i.hi >= (s16)self->unk7C.saved_pos.x + moving_block_motion[self->unk2].range)
                self->x_vel.val = -velocity;
        } else if (self->x_pos.i.hi <= (s16)self->unk7C.saved_pos.x - moving_block_motion[self->unk2].range) {
            self->x_vel.val = -velocity;
        }
        if (func_8002B1E8(BASE_OBJECT(self), moving_block_motion[self->unk2].range + 0xA0, 0x30) == 0)
            update_on_screen(BASE_OBJECT(self), 0x30, 0x20);
        else
            self->state++;
        if (self->x_vel.val != velocity)
            self->ext.item_2.unk80 = 0xA;
    } else {
        velocity = self->y_vel.val;
        if (velocity > 0) {
            if (self->y_pos.i.hi <= (s16)self->unk7C.saved_pos.y - moving_block_motion[self->unk2].range)
                self->y_vel.val = -velocity;
        } else if (self->y_pos.i.hi >= (s16)self->unk7C.saved_pos.y + moving_block_motion[self->unk2].range) {
            self->y_vel.val = -velocity;
        }
        if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x30) == 0)
            update_on_screen(BASE_OBJECT(self), 0x30, moving_block_motion[self->unk2].range + 0x78);
        else
            self->state++;
        if (self->y_vel.val != velocity)
            self->ext.item_2.unk80 = 0xA;
    }
    collide_with_players(PLAYER_OBJECT(self));
}
#endif

void moving_block_despawn(struct ItemObj* arg0)
{
    arg0->on_screen = 0;
    despawn_object(OBJECT_HEADER(arg0));
}

u8 moving_block_terrain_box[4] = { 0, 0, 0x18, 0x10 };

struct MovingBlockMotion moving_block_motion[1] = { { 0x10000, 0, 0x90, 0 } };

void (*moving_block_state_funcs[])(struct ItemObj*) = {
    func_800C20F4,
    func_800C229C,
    moving_block_despawn,
};
