// VisualObj, visual_object_update_funcs[4]
// 800AFB50..800AFC9C
#include "common.h"
#include "main/visuals/visual_04_blast.h"
#include "main/55C4.h"
#include "main/objects.h"

void blast_animate(struct VisualObj* arg0);

u8 blast_anim_0[19][4] = {
    { 1, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 2, 0, 1, 4 },
    { 2, 0, 1, 5 },
    { 2, 0, 1, 6 },
    { 2, 0, 1, 7 },
    { 2, 0, 1, 8 },
    { 2, 0, 1, 9 },
    { 2, 0, 1, 10 },
    { 2, 0, 1, 11 },
    { 2, 0, 1, 12 },
    { 3, 0, 1, 13 },
    { 3, 0, 1, 14 },
    { 4, 0, 1, 15 },
    { 5, 0, 1, 16 },
    { 6, 0, 1, 17 },
    { 0x60, 0, 0xFF, 17 },
};

u8* blast_animations[1] = { blast_anim_0 };

void blast_update(struct VisualObj* arg0)
{
    if (arg0->state == 0) {
        func_800AFB90(arg0);
    } else {
        blast_animate(arg0);
    }
}

// blast_init
#ifdef MMX4_PC
void func_800AFB90(struct VisualObj* arg0);
#endif

#ifdef MMX4_PC
void func_800AFB90(struct VisualObj* arg0)
{
    s32 index = arg0->unk2;
    s32 column = index + 4;
    s32 row = column < 0 ? index + 0x13 : column;

    arg0->on_screen = 1;
    arg0->unk38 = NULL;
    arg0->animation_table = (u32**)blast_animations;
    arg0->unk40 = 0;
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 2);
    row >>= 4;
    arg0->unk42 = (u16)((column - (row << 4)) | ((row + 0x1E0) << 6));
    set_animation(arg0, 0);
    if ((u8)arg0->unk5C.value != 0xFF) {
        func_8001540C(0, (u8)arg0->unk5C.value, arg0);
    }
    arg0->state = (u8)arg0->state + 1;
    is_on_screen(BASE_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/visuals/visual_04_blast", func_800AFB90);
#endif

void blast_animate(struct VisualObj* arg0)
{
    animate_object(arg0);
    if (arg0->animation_step.fields.relative_step < 0) {
        ZeroObjectState(arg0);
    } else {
        is_on_screen(arg0);
    }
}
