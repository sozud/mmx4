#include "common.h"

s32 D_8010EC00[4] = { 0x1E, 0x3C, 0x5A, 0x78 };
void (*g_TitleLogoUpdateFuncs[8])(struct MiscObj*) = {
    func_800CD78C,
    func_800CD90C,
    func_800CD974,
    func_800CDA90,
    func_800CDAD0,
    func_800CDB10,
    func_800CDB84,
    func_800CDC34,
};
