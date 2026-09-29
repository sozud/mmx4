// EffectObj, effect_object_update_funcs[17]
// 800B9100..800B9690
#include "common.h"

void freeze_blast_update(struct EffectObj* self)
{
    freeze_blast_state_funcs[self->state](self);
}

// freeze_blast_flash_init
INCLUDE_ASM("main/nonmatchings/effects/effect_17_freeze_blast", func_800B913C);

// freeze_blast_flash
INCLUDE_ASM("main/nonmatchings/effects/effect_17_freeze_blast", func_800B91E0);

void freeze_blast_finish(struct EffectObj* self)
{
    if (--self->ext.effect_17.timer != 0) {
        engine_obj.character_state.fields.active = 0;
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

// freeze_blast_freeze_tiles
INCLUDE_ASM("main/nonmatchings/effects/effect_17_freeze_blast", func_800B9354);

// freeze_blast_spawn_enemies
INCLUDE_ASM("main/nonmatchings/effects/effect_17_freeze_blast", func_800B94B8);

u8 freeze_blast_tile_patches[4][6] = {
    { 0x62, 0x72, 0x60, 0x70, 0x57, 0x0C },
    { 0x38, 0x48, 0x00, 0x95, 0x59, 0x10 },
    { 0x36, 0x46, 0x34, 0x44, 0x8C, 0x13 },
    { 0x32, 0x42, 0x30, 0x40, 0x8E, 0x16 },
};

struct Effect17SpawnRecord {
    u16 x;
    u16 y;
    u8 count;
    u8 unused;
};

struct Effect17SpawnRecord freeze_blast_spawns_0[4] = {
    { 0x0C08, 0x0190, 2, 0 },
    { 0x0C28, 0x0160, 2, 0 },
    { 0x0C48, 0x0140, 3, 0 },
    { 0x0D18, 0x0130, 5, 0 },
};

struct Effect17SpawnRecord freeze_blast_spawns_1[2] = {
    { 0x1098, 0x01A0, 3, 0 },
    { 0x1138, 0x0170, 4, 0 },
};

struct Effect17SpawnRecord freeze_blast_spawns_2[4] = {
    { 0x1318, 0x0150, 3, 0 },
    { 0x13F8, 0x0130, 3, 0 },
    { 0x1448, 0x0140, 3, 0 },
    { 0x1478, 0x0120, 2, 0 },
};

struct Effect17SpawnRecord freeze_blast_spawns_3[5] = {
    { 0x1658, 0x0150, 3, 0 },
    { 0x16C8, 0x0140, 4, 0 },
    { 0x1738, 0x0160, 2, 0 },
    { 0x1758, 0x0170, 2, 0 },
    { 0x1798, 0x0180, 3, 0 },
};

u16 freeze_blast_padding = 0;

struct Effect17SpawnGroup {
    struct Effect17SpawnRecord* records;
    u32 count;
};

struct Effect17SpawnGroup freeze_blast_spawn_groups[4] = {
    { freeze_blast_spawns_0, 4 },
    { freeze_blast_spawns_1, 2 },
    { freeze_blast_spawns_2, 4 },
    { freeze_blast_spawns_3, 5 },
};

void (*freeze_blast_state_funcs[])(struct EffectObj*) = {
    func_800B913C,
    func_800B91E0,
    freeze_blast_finish,
};
