// EffectObj, effect_object_update_funcs[5]
// 800B60BC..800B6A0C
#include "common.h"

// tile_scanner_update
INCLUDE_ASM("main/nonmatchings/effects/effect_05_tile_scanner", func_800B60BC);

void tile_scanner_init(struct EffectObj* self)
{
    self->state++;
    self->ext.effect_5.unk1C = 0;
    self->ext.effect_5.unk1E = 0;
    self->ext.effect_5.unk14 = 0;
    self->ext.effect_5.unk18 = 0;
}

// tile_scanner_scan
INCLUDE_ASM("main/nonmatchings/effects/effect_05_tile_scanner", func_800B64BC);

// tile_scanner_flood_fill
INCLUDE_ASM("main/nonmatchings/effects/effect_05_tile_scanner", func_800B6660);
