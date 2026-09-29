// VisualObj, visual_object_update_funcs[1]
// 800AED18..800AEED8
#include "common.h"

void dash_dust_update(struct VisualObj* arg0)
{
    struct VisualObj* obj;
    s32 var_a0;
    struct PlayerObj* entity;

    obj = arg0;
    entity = &g_Entity;
    if (g_Player.controlling_clone == 0) {
        entity = &g_Player;
    }
    if (obj->state == 0) {
        obj->on_screen = 1;
        obj->unk38 = 0;
        obj->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
        obj->animation_table = D_8011BF40;
        obj->unk42 = 0x7802;
        obj->unk40 = 0;
        obj->unk16 = 3;

        dash_dust_attach(obj, entity);
        set_animation(obj, 2);
        obj->state = (u8)obj->state + 1;
    } else {
        animate_object(obj);
        dash_dust_attach(obj, entity);
        var_a0 = 0;
        if (entity->dash_momentum > 0) {
            if (entity->unk17 != 0x10) {
                var_a0 = entity->unk17 != 0x80;
            }
        } else if (entity->unk17 != 0x12) {
            var_a0 = 1;
        }
        if (obj->animation_step.fields.relative_step < 0) {
            var_a0 = 1;
        }
        if (var_a0 != 0) {
            ZeroObjectState(obj);
            return;
        }
    }
    is_on_screen(obj);
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
