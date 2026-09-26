// VisualObj, visual_object_update_funcs[1]
// 800AED18..800AEED8
#include "common.h"

void func_800AED18(struct VisualObj* arg0)
{
    struct VisualObj* obj;
    s32 var_a0;
    struct PlayerObj* entity;

    obj = arg0;
    entity = &g_Entity;
    if (g_Player.unkDE == 0) {
        entity = &g_Player;
    }
    if (obj->state == 0) {
        obj->on_screen = 1;
        obj->unk38 = 0;
        obj->unk3C = *(s8**)0x1F80001C + (*(s32**)0x1F80001C)[1];
        obj->animation_table = D_8011BF40;
        obj->unk42 = 0x7802;
        obj->unk40 = 0;
        obj->unk16 = 3;

        func_800AEE5C(obj, entity);
        func_80015D60(obj, 2);
        obj->state = (u8)obj->state + 1;
    } else {
        func_80015DC8(obj);
        func_800AEE5C(obj, entity);
        var_a0 = 0;
        if (entity->unk84 > 0) {
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

void func_800AEE5C(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    arg0->unk15 = arg1->unk15;
    if (arg0->unk15 == 0) {
        arg0->x_pos.i.hi = arg1->x_pos.i.hi + D_8010A1B4[arg1->unk2].x;
    } else {
        arg0->x_pos.i.hi = arg1->x_pos.i.hi - D_8010A1B4[arg1->unk2].x;
    }
    arg0->y_pos.i.hi = arg1->y_pos.i.hi + D_8010A1B4[arg1->unk2].y;
}
