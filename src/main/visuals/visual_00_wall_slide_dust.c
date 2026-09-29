// VisualObj, visual_object_update_funcs[0]
// 800AEAC0..800AED18
#include "common.h"

void wall_slide_dust_update(struct VisualObj* arg0)
{
    struct PlayerObj* var_a1;
    if (g_Player.controlling_clone == 0) {
        var_a1 = &g_Player;
    } else {
        var_a1 = &g_Entity;
    }
    wall_slide_dust_state_funcs[arg0->state](arg0, var_a1);
}

void wall_slide_dust_init(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    arg0->on_screen = 1;
    arg0->unk38 = 0;
    arg0->unk3C = (void*)((s8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[1]);
    arg0->animation_table = &D_8011BF40;
    arg0->unk40 = 0;
    arg0->unk42 = 0x7804;
    arg0->unk16 = 1;
    wall_slide_dust_attach(arg0, arg1);
    set_animation(arg0, 3);
    arg0->state++;
    update_on_screen(arg0, 0x20, 0x20);
}

void wall_slide_dust_main(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    s32 var_a0 = 0;

    animate_object(arg0);
    if ((*(s32*)&arg1->state & 0xFFFF00) == 0xB00) {
        var_a0 = 1;
    }
    if (arg1->unk5 == 0x34) {
        var_a0 = 1;
    }
    if (var_a0 != 0) {
        wall_slide_dust_attach(arg0, arg1);
    } else {
        set_animation(arg0, 4);
        arg0->state++;
    }
    update_on_screen(arg0, 0x20, 0x20);
}

void wall_slide_dust_fade(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    animate_object(arg0);
    if (arg0->animation_step.fields.relative_step < 0) {
        ZeroObjectState(arg0);
        return;
    }
    update_on_screen(arg0, 0x20, 0x20);
}

void wall_slide_dust_attach(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    arg0->unk15 = arg1->unk15;
    if (arg0->unk15 == 0) {
        arg0->x_pos.i.hi = arg1->x_pos.i.hi + wall_slide_dust_offsets[arg1->unk2].x;
    } else {
        arg0->x_pos.i.hi = arg1->x_pos.i.hi - wall_slide_dust_offsets[arg1->unk2].x;
    }
    arg0->y_pos.i.hi = arg1->y_pos.i.hi + wall_slide_dust_offsets[arg1->unk2].y;
}

void (*wall_slide_dust_state_funcs[])(struct VisualObj*, struct PlayerObj*) = {
    wall_slide_dust_init,
    wall_slide_dust_main,
    wall_slide_dust_fade,
};

struct VisualAttachmentOffset wall_slide_dust_offsets[2] = {
    { 0x0A, 0x11 },
    { 0x0A, 0x19 },
};
