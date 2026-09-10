// MiscObj, misc_object_update_funcs[35]
// 800CF144..800CF2B8
#include "common.h"

void func_800CF144(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_800CF184(arg0);
    } else {
        func_800CF268(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_35", func_800CF184);

void func_800CF268(struct MiscObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    } else {
        is_on_screen(BASE_OBJECT(arg0));
    }
}
