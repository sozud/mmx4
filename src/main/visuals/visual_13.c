// VisualObj, visual_object_update_funcs[13]
// 800B1AF8..800B1C5C
#include "common.h"

void func_800B1AF8(struct VisualObj* arg0)
{
    D_8010A520[arg0->state](arg0);
}

void func_800B1B34(struct VisualObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk54 = 0xFF;
    arg0->unk56 = 0xFF;
    arg0->unk16 = 6;
    func_80015D60(arg0, 0x15);
}

void func_800B1B74(struct VisualObj* arg0)
{
    struct PlayerObj* player;
    s32 animation;
    s16 previous_frame;
    u8 frame;
    u8 next_animation;

    player = arg0->unk50;
    if (player->state != 2) {
        frame = player->animation_step.fields.frame_index;
        previous_frame = arg0->unk56;
        next_animation = D_8010A510[frame];
        if (frame != previous_frame && (animation = next_animation & 0xFF) != arg0->unk54) {
            func_80015D90(ANIMATED_OBJECT(arg0), animation,
                arg0->animation_step.fields.event);
            frame = player->animation_step.fields.frame_index;
            arg0->unk54 = next_animation;
            arg0->unk56 = frame;
        }
        arg0->x_pos.i.hi = player->x_pos.i.hi;
        arg0->y_pos.i.hi = player->y_pos.i.hi;
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }
    arg0->state = 2;
}

void func_800B1C3C(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A520[])(struct VisualObj*) = {
    func_800B1B34,
    func_800B1B74,
    func_800B1C3C,
};
