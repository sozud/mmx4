// MiscObj, misc_object_update_funcs[13]
// 800CA52C..800CA754
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_13", func_800CA52C);

INCLUDE_ASM("main/nonmatchings/misc/misc_13", func_800CA60C);

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
