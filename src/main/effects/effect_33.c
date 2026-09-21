// EffectObj, effect_object_update_funcs[33]
// 800BC748..800BCE48
#include "common.h"

void func_800BC748(struct EffectObj* arg0)
{
    D_8010BF98[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_33", func_800BC784);

INCLUDE_ASM("main/nonmatchings/effects/effect_33", func_800BC92C);

void func_800BCD84(struct EffectObj* self)
{
    switch (self->unk2 & 0xF0) {
    case 0:
        if (self->backref != NULL) {
            func_8002B108(OBJECT_HEADER(self));
        } else {
            ZeroObjectState(OBJECT_HEADER(self));
        }
        break;
    case 0x10:
        if (self->backref != NULL) {
            func_8002B108(OBJECT_HEADER(self));
        } else {
            ZeroObjectState(OBJECT_HEADER(self));
        }
        break;
    case 0x20:
        if (self->backref != NULL) {
            func_8002B0C8(OBJECT_HEADER(self));
        } else {
            ZeroObjectState(OBJECT_HEADER(self));
        }
        break;
    }
}

void func_800BCE40(struct EffectObj* arg0)
{
}

void (*D_8010BF98[])(struct EffectObj*) = {
    func_800BC784,
    func_800BC92C,
    func_800BCD84,
    func_800BCE40,
};
