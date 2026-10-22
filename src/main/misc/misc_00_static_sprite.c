// MiscObj, misc_object_update_funcs[0]
// 800C7A68..800C7BF4
#include "common.h"
#include "main/misc/misc_00_static_sprite.h"
#include "main/objects.h"

// static_sprite_state_funcs
void static_sprite_init(struct MiscObj* arg0);
void static_sprite_main(struct MiscObj* arg0);
void static_sprite_despawn(struct MiscObj* arg0);
#include "weapon_resources.h"

extern void (*static_sprite_state_funcs[])(struct MiscObj*);

void static_sprite_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    static_sprite_state_funcs[self->state](self);
}
void static_sprite_init(struct MiscObj* self)
{
    self->active = 1;
    self->unk16 = SATURN_ALT(0x11, 0);
    self->unk40 = SATURN_ALT(0x1511, OBJECT_STAGE_TEXTURE(9));
    self->animation_step.fields.frame_index = (u8)self->unk2;

    self->bg_offset = (u8)g_Player.bg_offset;
    self->unk15 = 0;

    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[0x24 / 4];

    self->unk42 = OBJECT_CLUT(0x7904);
    self->state++;
}
void static_sprite_main(struct MiscObj* self)
{
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x30, 0x10);
    } else {
        self->state++;
    }
}
void static_sprite_despawn(struct MiscObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void spawn_common_effect(struct MainObj* self, s8 arg1)
{
    struct MiscObj* misc;

    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 1;
        misc->unk2 = arg1;
        misc->unk15 = self->unk15;
        misc->x_pos = self->x_pos;
        misc->y_pos = self->y_pos;
    }
}

void (*static_sprite_state_funcs[])(struct MiscObj*) = {
    static_sprite_init,
    static_sprite_main,
    static_sprite_despawn,
};
