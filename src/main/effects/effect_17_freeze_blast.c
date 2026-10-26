// EffectObj, effect_object_update_funcs[17]
// 800B9100..800B9690
#include "common.h"
#include "main/effects/effect_17_freeze_blast.h"
#include "main/objects.h"
#include "main/1AC84.h"
#include "main/object_motion.h"

// freeze_blast_state_funcs
extern void (*freeze_blast_state_funcs[])(struct EffectObj*);

void freeze_blast_finish(struct EffectObj*);
#include "weapon_resources.h"
#ifdef MMX4_SATURN
#include "saturn/platform.h"
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1AC84.h"
#include "main/object_motion.h"
#endif

void freeze_blast_update(struct EffectObj* self)
{
    freeze_blast_state_funcs[self->state](self);
}

// freeze_blast_flash_init
struct Effect17SpawnGroup {
    struct Effect17SpawnRecord* records;
    u32 count;
};

extern u8 freeze_blast_tile_patches[4][6];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B913C(struct EffectObj* self);
void func_800B9354(struct EffectObj* self);
void func_800B94B8(struct EffectObj* self);
void func_800B91E0(struct EffectObj* self);
void func_800B9354(struct EffectObj*);
void func_800B94B8(struct EffectObj*);
struct Effect17SpawnRecordPC {
    u16 x;
    u16 y;
    u8 count;
    u8 unused;
};
struct Effect17SpawnGroupPC {
    struct Effect17SpawnRecordPC* records;
    u32 count;
};
extern struct Effect17SpawnGroup freeze_blast_spawn_groups[4];
extern ret_u8 func_8002938C(s32);
#endif

void func_800B913C(struct EffectObj* self)
{
    u8 i;

    engine_obj.unk10 = 1;
    engine_obj.unk12 = 1;
    engine_obj.unk11 = 1;
    engine_obj.unk13 = 1;
    self->ext.effect_17.phase = 1;
#ifdef MMX4_SATURN
    D_8013E188[0] = 0x4F;
#else
    for (i = 0; i < 4; i++)
        D_8013E188[i] = -1;
#endif
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    self->ext.effect_17.timer = 2;
    self->state++;
}

// freeze_blast_flash
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/effects/effect_17_freeze_blast", func_800B91E0);
#else
void func_800B91E0(struct EffectObj* self)
{
    struct Effect17Ext* ext = &self->ext.effect_17;
    u8 phase = ext->phase--;
    if (phase != 0)
        return;
    if ((u16)g_FilterAmountR >= 0x1E) {
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        engine_obj.character_state.fields.active = 1;
        need_palette_load |= 1;
        func_800B9354(self);
        engine_obj.unk10 = 0;
        engine_obj.unk12 = 0;
        engine_obj.unk11 = 0;
        engine_obj.unk13 = 0;
        func_800B94B8(self);
        ext->timer = 2;
        self->state++;
        return;
    }
    ext->phase = 1;
    if (--ext->timer != 0) {
        g_FilterAmountR += 2;
        g_FilterAmountG += 0x40;
        g_FilterAmountB += 0x800;
        return;
    }
    ext->timer = 2;
}
#endif

void freeze_blast_finish(struct EffectObj* self)
{
    if (--self->ext.effect_17.timer != 0) {
        engine_obj.character_state.fields.active = 0;
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

// freeze_blast_freeze_tiles
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/effects/effect_17_freeze_blast", func_800B9354);
#else
void func_800B9354(struct EffectObj* self)
{
    u8* tiles = freeze_blast_tile_patches[self->unk2];
    s8 i = 0;

    do {
        D_80141BE8[tiles[5] + i] = tiles[0] + i;
        D_80141BE8[layout_width + (tiles[5] + i)] = tiles[1] + i;
        if (tiles[2] != 0) {
            D_80141BE8[tiles[5] + i + layout_size] = tiles[2] + i;
        } else {
            D_80141BE8[tiles[5] + i + layout_size] = tiles[2];
        }
        D_80141BE8[layout_width + (tiles[5] + i) + layout_size] = tiles[3] + i;
        D_80141BE8[layout_size * 2 + (layout_width + (tiles[5] + i))] = tiles[4] + i;
        i++;
    } while (i < 2);
#ifdef MMX4_SATURN
    for (i = 0; i < 3; i++)
        saturn_background_redraw(i);
#else
    background_objects[0].unk4C = 1;
    background_objects[1].unk4C = 1;
    background_objects[2].unk4C = 1;
#endif
}
#endif

// freeze_blast_spawn_enemies
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B94B8(struct EffectObj* self)
{
    struct Effect17SpawnGroupPC* group = &((struct Effect17SpawnGroupPC*)freeze_blast_spawn_groups)[(s8)self->unk2];
    for (u32 i = 0; i < (u8)group->count; i++) {
        struct Effect17SpawnRecordPC* record = &group->records[i];
        u32 j;
        for (j = 0; j < record->count; j++) {
            struct MainObj* child = find_free_main_obj();
            s32 index;
            s32 column;
            s32 row;
            if (child == NULL)
                continue;
            child->active = 0x41;
            child->id = 0x15;
            child->unk2 = (get_random_nonzero() % 6) + 6;
            child->x_pos.u.hi = record->x + (j & 0xFF) * 0x10;
            child->y_pos.u.hi = record->y;
            index = func_8002938C(0x15);
            child->unk40 = OBJECT_STAGE_TEXTURE(index);
            column = func_8002938C(0x15) * 4 + 0x18;
            row = func_8002938C(0x15);
#ifdef MMX4_SATURN
            child->unk42 = column;
#else
            child->unk42 = (column % 16) | (((row + 6) / 4 + 0x1E0) << 6);
#endif
            child->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x15));
        }
    }
}
#else
INCLUDE_ASM("main/nonmatchings/effects/effect_17_freeze_blast", func_800B94B8);
#endif

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
