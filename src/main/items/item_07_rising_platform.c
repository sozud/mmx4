// ItemObj, item_object_update_funcs[7]
// 800C16F0..800C1994
#include "common.h"

struct Item06AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

u16 rising_platform_start_y[2] = { 0x1028, 0x1028 };

extern struct Item06AnimationStep rising_platform_anim_steps[5];

extern struct Item06AnimationStep* rising_platform_animations[5];

extern u8 rising_platform_debris[2][4];

// rising_platform_init
void func_800C16F0(struct ItemObj* self)
{
    s32 resource;

    self->active = 0x41;
    self->animation_table = (const u8* const*)rising_platform_animations;
    self->state++;
    self->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0x87);
    self->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    self->unk40 = D_801406A8[func_8002938C(0x87)] >> 7;
    self->unk42 = CLUT_FROM_ID(0x87);
    self->unk16 = 6;
    self->unk15 = 0;
    self->unk68 = (struct Unk_unk68*)rising_platform_start_y;
    set_animation(ANIMATED_OBJECT(self), 0);
    self->unk76 = 0;
    self->x_vel.val = 0;
    self->y_vel.val = 0x8000;
    self->unk7C.value = 0;
}

void rising_platform_rise(struct ItemObj* self)
{
    struct ItemObj* item;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    move_object(MOVING_OBJECT(self));
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->unk70 & 4) {
        if (self->on_screen != 0) {
            func_8001540C(5, 2, self);
            spawn_debris_offset(8, rising_platform_debris[0], MISC_OBJECT(self), FIXED(40), FIXED(8));
        }
        self->state++;
        return;
    }

    collide_with_players(self);
    if (self->unk7C.value == 0 && self->y_pos.i.hi <= 0x5B0) {
        item = find_free_item_obj();
        if (item != NULL) {
            item->active = 0x41;
            item->id = 7;
            item->x_pos.val = self->x_pos.val;
            item->y_pos.val = FIXED(2320);
            self->unk7C.value = 1;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x60, 0x30);
}

void rising_platform_despawn(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void rising_platform_update(struct ItemObj* arg0)
{
    rising_platform_state_funcs[arg0->state](arg0);
}

extern void (*rising_platform_state_funcs[])(struct ItemObj*);
