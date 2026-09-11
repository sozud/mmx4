// MiscObj, misc_object_update_funcs[14]
// 800CA754..800CA86C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_14", func_800CA754);

void func_800CA7E4(struct MiscObj* self)
{
    if (--self->unk7 == 0) {
        ZeroObjectState(OBJECT_HEADER(self));
    } else {
        is_on_screen(BASE_OBJECT(self));
    }
}

void func_800CA830(struct MiscObj* arg0)
{
    D_8010E64C[arg0->state](arg0);
}

void (*D_8010E64C[2])(struct MiscObj*) = {
    func_800CA754,
    func_800CA7E4,
};
