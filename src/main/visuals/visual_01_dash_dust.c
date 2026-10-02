// VisualObj, visual_object_update_funcs[1]
// 800AED18..800AEED8
#include "common.h"

void dash_dust_update(struct VisualObj* arg0)
{
    s32 var_a0;
    struct PlayerObj* entity;

    entity = g_Player.controlling_clone == 0 ? &g_Player : &g_Entity;
    if (arg0->state == 0) {
        arg0->on_screen = 1;
        arg0->unk38 = 0;
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
        arg0->animation_table = D_8011BF40;
        arg0->unk40 = 0;
        arg0->unk42 = 0x7802;
        arg0->unk16 = 3;

        dash_dust_attach(arg0, entity);
        set_animation(arg0, 2);
        arg0->state = (u8)arg0->state + 1;
    } else {
        animate_object(arg0);
        dash_dust_attach(arg0, entity);
        var_a0 = 0;
        if (entity->dash_momentum > 0) {
            if (entity->unk17 != 0x10) {
                var_a0 = entity->unk17 != 0x80;
            }
        } else if (entity->unk17 != 0x12) {
            var_a0 = 1;
        }
        if (arg0->animation_step.fields.relative_step < 0) {
            var_a0 = 1;
        }
        if (var_a0 != 0) {
            ZeroObjectState(arg0);
            return;
        }
    }
    is_on_screen(arg0);
}

void dash_dust_attach(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    arg0->unk15 = arg1->unk15;
    if (arg0->unk15 == 0) {
        arg0->x_pos.i.hi = arg1->x_pos.i.hi + dash_dust_offsets[arg1->unk2].x;
    } else {
        arg0->x_pos.i.hi = arg1->x_pos.i.hi - dash_dust_offsets[arg1->unk2].x;
    }
    arg0->y_pos.i.hi = arg1->y_pos.i.hi + dash_dust_offsets[arg1->unk2].y;
}

struct VisualAttachmentOffset dash_dust_offsets[2] = {
    { 0x20, 0x0C },
    { 0x24, 0x0E },
};
