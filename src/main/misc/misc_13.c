// MiscObj, misc_object_update_funcs[13]
// 800CA52C..800CA754
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_13", func_800CA52C);

void func_800CA60C(struct MiscObj* self)
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
            animation = 9;
            if (engine_obj.unk5F < 7U) {
                animation = 8;
            }
        }
        func_80015D90(ANIMATED_OBJECT(self), 0,
            (s8)D_800F474C.stage_order[animation] - 1);
        stage = (s8)D_800F474C.stage_order[animation];
        temp_v0 = stage - 1;
        temp_v0 <<= 1;
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

void func_800CA6F8(struct MiscObj* arg0)
{
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800CA718(struct MiscObj* arg0)
{
    arg0->on_screen = 0;
    D_8010E640[arg0->state](arg0);
}

union AnimationStep D_8010E60C[12] = {
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

union AnimationStep* D_8010E63C[1] = { D_8010E60C };

void (*D_8010E640[3])(struct MiscObj*) = {
    func_800CA52C,
    func_800CA60C,
    func_800CA6F8,
};
