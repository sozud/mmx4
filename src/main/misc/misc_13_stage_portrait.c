// MiscObj, misc_object_update_funcs[13]
// 800CA52C..800CA754
#include "common.h"

// stage_portrait_init
INCLUDE_ASM("main/nonmatchings/misc/misc_13_stage_portrait", func_800CA52C);

void stage_portrait_select(struct MiscObj* self)
{
    s32 temp_a0;
    s32 temp_v0;
    s32 var_a2;
    s32 var_v1;
    s8 stage;
    s8 engine_state;
    s8 animation;

    engine_state = engine_obj.unk3;
    if (engine_state != self->unk7) {
        animation = engine_state;
        self->unk7 = animation;
        if (engine_state >= 8) {
            animation = engine_obj.unk5F < 7U ? 8 : 9;
        }
        set_animation_frame(ANIMATED_OBJECT(self), 0,
            (s8)mission_stage_order[animation] - 1);
        stage = (s8)mission_stage_order[animation];
        temp_v0 = (stage - 1) << 1;
        temp_a0 = temp_v0 + 0xB;
        var_a2 = temp_a0;
        if (temp_a0 < 0) {
            var_a2 = temp_v0 + 0x1A;
        }
        var_v1 = stage + 4;
        temp_a0 -= (var_a2 >> 4) * 0x10;
        if (var_v1 < 0) {
            var_v1 = stage + 0xB;
        }
        self->unk42 = temp_a0 | (((var_v1 >> 3) + 0x1E0) << 6);
    }
    is_on_screen(BASE_OBJECT(self));
}

void stage_portrait_show(struct MiscObj* self)
{
    is_on_screen(BASE_OBJECT(self));
}

void stage_portrait_update(struct MiscObj* self)
{
    self->on_screen = 0;
    stage_portrait_state_funcs[self->state](self);
}

union AnimationStep stage_portrait_anim_0[12] = {
    { .packed = 0x0001001E },
    { .packed = 0x0101001E },
    { .packed = 0x0201001E },
    { .packed = 0x0301001E },
    { .packed = 0x0401001E },
    { .packed = 0x0501001E },
    { .packed = 0x0601001E },
    { .packed = 0x0701001E },
    { .packed = 0x0801001E },
    { .packed = 0x0901001E },
    { .packed = 0x0A01001E },
    { .packed = 0x1001001E },
};

union AnimationStep* stage_portrait_animations[1] = { stage_portrait_anim_0 };

void (*stage_portrait_state_funcs[3])(struct MiscObj*) = {
    func_800CA52C,
    stage_portrait_select,
    stage_portrait_show,
};
