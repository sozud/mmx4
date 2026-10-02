// VisualObj, visual_object_update_funcs[9]
// 800B1354..800B14E8
#include "common.h"

void dust_puff_update(struct VisualObj* arg0)
{
    if (arg0->state == 0) {
        dust_puff_init(arg0);
    } else {
        dust_puff_main(arg0);
    }
}

void dust_puff_init(struct VisualObj* self)
{
    s32* sprite_frames;
    s32 offset;

    self->on_screen = 1;
    self->unk38 = 0;
    sprite_frames = SP_SPRITE_FRAMES;
    offset = sprite_frames[2];
    self->unk3C = (u8*)sprite_frames + offset;
    self->animation_table = explosion_animations;
    self->bg_offset = g_Player.bg_offset;
    self->unk40 = 0;
    if (self->unk5C.value != 2) {
        self->unk42 = 0x7805;
    } else {
        self->unk42 = 0x7806;
    }
    if (self->unk7 == 0) {
        self->unk16 = 1;
    }
    set_animation(self, self->unk5C.value);
    self->state++;
    self->unk7 = get_random() & 1;
    is_on_screen(BASE_OBJECT(self));
}

void dust_puff_main(struct VisualObj* arg0)
{
    u8 temp_v1;

    move_object((struct MovingObj*)arg0);
    animate_object(arg0);
    if (0 == arg0->animation_step.fields.relative_step) {
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk5C.value = 0;
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    arg0->on_screen = 0;
    temp_v1 = (u8)arg0->unk5C.value;
    if (((temp_v1 & 3) && !(temp_v1 & 1)) || ((BLINK_CLOCK(main_bss_state.frame_counter) & 1) == arg0->unk7)) {
        is_on_screen((struct BaseObj*)arg0);
    }
}
