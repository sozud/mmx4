// MiscObj, misc_object_update_funcs[12]
// 800CA228..800CA52C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_12", func_800CA228);

INCLUDE_ASM("main/nonmatchings/misc/misc_12", func_800CA3C0);

INCLUDE_ASM("main/nonmatchings/misc/misc_12", func_800CA40C);

INCLUDE_ASM("main/nonmatchings/misc/misc_12", func_800CA46C);

void func_800CA4B4(struct MiscObj* arg0)
{
    arg0->on_screen = 0;
    if (engine_obj.unk3 == arg0->unk2) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

void func_800CA4F0(struct MiscObj* arg0)
{
    D_8010E5F8[arg0->state](arg0);
}

union AnimationStep D_8010E58C[9] = {
    { .packed = 0x0001001E },
    { .packed = 0x0101001E },
    { .packed = 0x0201001E },
    { .packed = 0x0301001E },
    { .packed = 0x0401001E },
    { .packed = 0x0501001E },
    { .packed = 0x0601001E },
    { .packed = 0x0701001E },
    { .packed = 0x1000001E },
};

union AnimationStep D_8010E5B0[8] = {
    { .packed = 0x0801001E },
    { .packed = 0x0901001E },
    { .packed = 0x0A01001E },
    { .packed = 0x0B01001E },
    { .packed = 0x0C01001E },
    { .packed = 0x0D01001E },
    { .packed = 0x0E01001E },
    { .packed = 0x0FF9001E },
};

union AnimationStep* D_8010E5D0[2] = { D_8010E58C, D_8010E5B0 };

struct Misc12Position {
    s16 x;
    s16 y;
};

struct Misc12Position D_8010E5D8[8] = {
    { 8, 0x120 },
    { 0x55, 0x120 },
    { 0xA2, 0x120 },
    { 0xEF, 0x120 },
    { 0x21, 0x1B0 },
    { 0x61, 0x1B0 },
    { 0xA2, 0x1B0 },
    { 0xE2, 0x1B0 },
};

void (*D_8010E5F8[5])(struct MiscObj*) = {
    func_800CA228,
    func_800CA3C0,
    func_800CA40C,
    func_800CA46C,
    func_800CA4B4,
};
