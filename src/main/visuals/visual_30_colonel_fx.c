// VisualObj, visual_object_update_funcs[30]
// 800B4610..800B4B64
#include "common.h"

void colonel_fx_update(struct VisualObj* arg0)
{
    colonel_fx_state_funcs[arg0->state](arg0);
}

void colonel_fx_init(struct VisualObj* arg0)
{
    struct PlayerObj* player = arg0->unk50;

    arg0->state++;
    arg0->unk3C = player->unk3C;
    arg0->unk40 = player->unk40;
    arg0->unk42 = player->unk42 & 0x7FFF;
    arg0->bg_offset = player->bg_offset;
    arg0->animation_table = player->animation_table;
    arg0->unk15 = player->unk15;
    arg0->unk5 = (s8)((s32)((u8)arg0->unk2 << 24) >> 28);
    arg0->unk6 = 0;
    arg0->unk5C.value = 0;
    arg0->unk2 &= 0xF;
}

void colonel_fx_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void colonel_fx_main(struct VisualObj* arg0)
{
    colonel_fx_mode_funcs[arg0->unk5](arg0);
    if (arg0->unk50->state == 2) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
}

void colonel_fx_beam_in(struct VisualObj* arg0)
{
    colonel_fx_beam_in_funcs[arg0->unk6](arg0);
}

void colonel_fx_beam_in_start(struct VisualObj* arg0)
{
    struct PlayerObj* player = arg0->unk50;

    arg0->unk16 = 4;
    arg0->x_pos.val = player->x_pos.val + ((arg0->unk15 == 0) ? FIXED(-5) : FIXED(5));
    arg0->y_pos.val = player->y_pos.val + FIXED(-224);
    set_animation(arg0, 0x12);
    arg0->unk6++;
}

void colonel_fx_beam_in_animate(struct VisualObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    update_on_screen(BASE_OBJECT(arg0), 0x100, 0x100);
    if (arg0->unk5C.value != 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void colonel_fx_flash(struct VisualObj* arg0)
{
    colonel_fx_flash_funcs[arg0->unk6](arg0);
}

void colonel_fx_flash_start(struct VisualObj* arg0)
{
    struct PlayerObj* player;

    player = arg0->unk50;
    arg0->unk16 = 4;
    arg0->x_pos.val = player->x_pos.val + (arg0->unk15 != 0 ? FIXED(-5) : FIXED(5));
    arg0->y_pos.val = player->y_pos.val + FIXED(-16);
    set_animation(arg0, 0x14);
    arg0->unk6++;
}

void colonel_fx_flash_animate(struct VisualObj* arg0)
{
    animate_object(arg0);
    is_on_screen(BASE_OBJECT(arg0));
    if (--arg0->unk54 == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void colonel_fx_slash(struct VisualObj* arg0)
{
    colonel_fx_slash_funcs[arg0->unk6](arg0);
}

void colonel_fx_slash_start(struct VisualObj* arg0)
{
    struct PlayerObj* player;

    player = arg0->unk50;
    arg0->unk16 = 4;
    arg0->x_pos.val = player->x_pos.val + (arg0->unk15 == 0 ? FIXED(-7) : FIXED(7));
    arg0->y_pos.val = player->y_pos.val + FIXED(-93);
    set_animation(arg0, 0x11);
    arg0->unk54 = 0x30;
    arg0->unk6++;
}

void colonel_fx_slash_animate(struct VisualObj* arg0)
{
    animate_object(arg0);
    is_on_screen(arg0);
    if (--arg0->unk54 == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void colonel_fx_ground(struct VisualObj* arg0)
{
    colonel_fx_ground_funcs[arg0->unk6](arg0);
}

void colonel_fx_ground_start(struct VisualObj* arg0)
{
    struct PlayerObj* entity = arg0->unk50;

    arg0->unk16 = 4;
    arg0->x_pos.val = entity->x_pos.val;
    arg0->y_pos.val = entity->y_pos.val + FIXED(32);
    set_animation(arg0, 0x15);
    arg0->unk54 = 0x20;
    arg0->unk6++;
}

void colonel_fx_ground_animate(struct VisualObj* arg0)
{
    animate_object(arg0);
    if (--arg0->unk54 == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    } else {
        is_on_screen(arg0);
    }
}

void (*colonel_fx_state_funcs[])(struct VisualObj*) = {
    colonel_fx_init,
    colonel_fx_main,
    colonel_fx_despawn,
};

void (*colonel_fx_mode_funcs[])(struct VisualObj*) = {
    colonel_fx_beam_in,
    colonel_fx_flash,
    colonel_fx_slash,
    colonel_fx_ground,
};

void (*colonel_fx_beam_in_funcs[])(struct VisualObj*) = {
    colonel_fx_beam_in_start,
    colonel_fx_beam_in_animate,
};

void (*colonel_fx_flash_funcs[])(struct VisualObj*) = {
    colonel_fx_flash_start,
    colonel_fx_flash_animate,
};

void (*colonel_fx_slash_funcs[])(struct VisualObj*) = {
    colonel_fx_slash_start,
    colonel_fx_slash_animate,
};

void (*colonel_fx_ground_funcs[])(struct VisualObj*) = {
    colonel_fx_ground_start,
    colonel_fx_ground_animate,
};
