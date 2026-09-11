// MiscObj, misc_object_update_funcs[51]
// 800D1DC4..800D2190
#include "common.h"

void func_800D1DC4(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010F4BC[arg0->state](arg0);
}

void func_800D1E0C(struct MiscObj* arg0)
{
    struct MainObj* source;
    const u8* const* animation_table;

    source = arg0->ext.misc_51.source;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = source->unk15;
    arg0->unk40 = source->unk40;
    arg0->unk42 = source->unk42;
    arg0->unk3C = (void*)source->sprite_frames;
    animation_table = source->animation_table;
    arg0->unk6 = 0;
    arg0->state++;
    arg0->unk5 = arg0->unk2 >> 4;
    arg0->animation_table = (u32**)animation_table;
    arg0->unk2 &= 0xF;
    func_800D1E9C(arg0);
}

void func_800D1E9C(struct MiscObj* arg0)
{
    struct MainObj* source;

    source = arg0->ext.misc_51.source;
    D_8010F4C8[arg0->unk5](arg0);
    if (source->active != 0x41) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void func_800D1F04(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_51", func_800D1F24);

INCLUDE_ASM("main/nonmatchings/misc/misc_51", func_800D1F74);

void func_800D1FB8(struct MiscObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 5);
        arg0->unk6++;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}

void func_800D2010(struct MiscObj* arg0)
{
    func_80015DC8(arg0);
}

void func_800D2030(struct MiscObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk16 = 6;
        func_80015D60(arg0, 3);
        arg0->unk6++;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_51", func_800D2094);

void func_800D212C(struct MiscObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk16 = 1;
        func_80015D60(arg0, 9);
        arg0->unk6++;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void (*D_8010F4BC[3])(struct MiscObj*) = {
    func_800D1E0C,
    func_800D1E9C,
    func_800D1F04,
};

void (*D_8010F4C8[4])(struct MiscObj*) = {
    func_800D1F24,
    func_800D2030,
    func_800D2094,
    func_800D212C,
};

void (*D_8010F4D8[3])(struct MiscObj*) = {
    func_800D1F74,
    func_800D1FB8,
    func_800D2010,
};
