#ifndef SCRATCHPAD_H
#define SCRATCHPAD_H

struct Scratchpad1C {
    s8 unk0[1];
    s8 pad[0xf];
    s32 unk10;
    s8 pad14[0x24 - 0x14];
    s32 unk24;
};

#ifdef MMX4_PC
extern u8 mmx4_scratchpad[0x400];
extern void* mmx4_sp_primitive_cursor;
extern void* mmx4_sp_draw_mode_cursor;
extern u8* mmx4_sp_background_cursor;
extern void* mmx4_sp_background_primitive_cursor;
extern void* mmx4_sp_ordering_cursor;
extern void* mmx4_sp_auxiliary_cursor;
extern u8* pc_archive_slots[22];
#define MMX4_SP_PTR(offset, type) ((type*)(void*)&mmx4_scratchpad[(offset)])
#define SP_DRAW_BUFFER (*MMX4_SP_PTR(0x000, s32))
#define SP_BG_TILEMAP mmx4_sp_background_cursor
#define SP_BG_TILE_PIXELS ((u16*)pc_archive_slots[0])
#define SP_BG_TILE_ATTRS ((u32*)pc_archive_slots[1])
#define SP_PLAYER_GFX ((s32*)pc_archive_slots[2])
#define SP_SPRITE_FRAMES ((s32*)pc_archive_slots[3])
#define SP_SPRITE_FRAMES_HDR ((struct Scratchpad1C*)pc_archive_slots[3])
#define SP_MENU_FRAMES ((s32*)pc_archive_slots[10])
#define SP_PALETTE_BANK ((u16*)pc_archive_slots[9])
#define SP_PALETTE ((u16*)pc_archive_slots[5])
#define SP_PALETTES ((Palette*)pc_archive_slots[5])
#define SP_ARC_2C ((void*)pc_archive_slots[11])
#define SP_ARC_30 ((s32*)pc_archive_slots[13])
#define SP_ARC_34 ((void*)pc_archive_slots[16])
#define SP_VRAM_IMAGE ((void*)pc_archive_slots[17])
#define SP_TITLE_FRAMES ((void*)pc_archive_slots[18])
#define SP_ARC_40 ((void*)pc_archive_slots[19])
#define SP_ARC_44 ((void*)pc_archive_slots[20])
#define SP_ARC_48 ((void*)pc_archive_slots[21])
#define SP_CUR_MAIN_OBJ (*MMX4_SP_PTR(0x04C, struct Unk*))
#define SP_CUR_WEAPON_OBJ (*MMX4_SP_PTR(0x050, struct WeaponObj*))
#define SP_CUR_SHOT_OBJ (*MMX4_SP_PTR(0x050, struct ShotObj*))
#define SP_CUR_VISUAL_OBJ (*MMX4_SP_PTR(0x054, struct VisualObj*))
#define SP_CUR_EFFECT_OBJ (*MMX4_SP_PTR(0x05C, struct EffectObj*))
#define SP_CUR_ITEM_OBJ (*MMX4_SP_PTR(0x060, struct ItemObj*))
#define SP_CUR_MISC_OBJ (*MMX4_SP_PTR(0x064, struct MiscObj*))
#define SP_CUR_UNK_OBJ (*MMX4_SP_PTR(0x064, struct UnkObj*))
#define SP_CUR_QUAD_OBJ (*MMX4_SP_PTR(0x068, struct QuadObj*))
#define SP_CUR_LAYER_OBJ (*MMX4_SP_PTR(0x06C, struct LayerObj*))
#define SP_PRIM_CURSOR mmx4_sp_primitive_cursor
#define SP_DRAW_MODE_CURSOR mmx4_sp_draw_mode_cursor
#define SP_BG_PRIM_CURSOR mmx4_sp_background_primitive_cursor
#define SP_OT_CURSOR mmx4_sp_ordering_cursor
#define SP_AUX_CURSOR mmx4_sp_auxiliary_cursor
#define SP_AUX_POLY_F4_CURSOR ((POLY_F4*)mmx4_sp_auxiliary_cursor)
#define SP_BG_SPRITE_COUNT (*MMX4_SP_PTR(0x11C, s32))
#define SP_SPRITE_COUNT (*MMX4_SP_PTR(0x124, s32))
#else
#define SP_DRAW_BUFFER (*(s32*)0x1F800000)
#define SP_BG_TILEMAP (*(u8**)0x1F800004)
#define SP_BG_TILE_PIXELS (*(u16**)0x1F800008)
#define SP_BG_TILE_ATTRS (*(u32**)0x1F80000C)
#define SP_PLAYER_GFX (*(s32**)0x1F800014)
#define SP_SPRITE_FRAMES (*(s32**)0x1F80001C)
#define SP_SPRITE_FRAMES_HDR (*(struct Scratchpad1C**)0x1F80001C)
#define SP_MENU_FRAMES (*(s32**)0x1F800020)
#define SP_PALETTE_BANK (*(u16**)0x1F800024)
#define SP_PALETTE (*(u16**)0x1F800028)
#define SP_PALETTES (*(Palette**)0x1F800028)
#define SP_ARC_2C (*(void**)0x1F80002C)
#define SP_ARC_30 (*(s32**)0x1F800030)
#define SP_ARC_34 (*(void**)0x1F800034)
#define SP_VRAM_IMAGE (*(void**)0x1F800038)
#define SP_TITLE_FRAMES (*(void**)0x1F80003C)
#define SP_ARC_40 (*(void**)0x1F800040)
#define SP_ARC_44 (*(void**)0x1F800044)
#define SP_ARC_48 (*(void**)0x1F800048)
#define SP_CUR_MAIN_OBJ (*(struct Unk**)0x1F80004C)
#define SP_CUR_WEAPON_OBJ (*(struct WeaponObj**)0x1F800050)
#define SP_CUR_SHOT_OBJ (*(struct ShotObj**)0x1F800050)
#define SP_CUR_VISUAL_OBJ (*(struct VisualObj**)0x1F800054)
#define SP_CUR_EFFECT_OBJ (*(struct EffectObj**)0x1F80005C)
#define SP_CUR_ITEM_OBJ (*(struct ItemObj**)0x1F800060)
#define SP_CUR_MISC_OBJ (*(struct MiscObj**)0x1F800064)
#define SP_CUR_UNK_OBJ (*(struct UnkObj**)0x1F800064)
#define SP_CUR_QUAD_OBJ (*(struct QuadObj**)0x1F800068)
#define SP_CUR_LAYER_OBJ (*(struct LayerObj**)0x1F80006C)
#define SP_PRIM_CURSOR (*(void**)0x1F800100)
#define SP_DRAW_MODE_CURSOR (*(void**)0x1F800104)
#define SP_BG_PRIM_CURSOR (*(void**)0x1F800108)
#define SP_OT_CURSOR (*(void**)0x1F80010C)
#define SP_AUX_CURSOR (*(void**)0x1F800110)
#define SP_AUX_POLY_F4_CURSOR (*(POLY_F4**)0x1F800110)
#define SP_BG_SPRITE_COUNT (*(s32*)0x1F80011C)
#define SP_SPRITE_COUNT (*(s32*)0x1F800124)
#endif

#endif
