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
extern struct MainObj* mmx4_sp_current_main;
extern struct WeaponObj* mmx4_sp_current_weapon;
extern struct ShotObj* mmx4_sp_current_shot;
extern struct VisualObj* mmx4_sp_current_visual;
extern struct EffectObj* mmx4_sp_current_effect;
extern struct ItemObj* mmx4_sp_current_item;
extern struct MiscObj* mmx4_sp_current_misc;
extern struct UnkObj* mmx4_sp_current_unk;
extern struct QuadObj* mmx4_sp_current_quad;
extern struct LayerObj* mmx4_sp_current_layer;
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
#define SP_PALETTE_BANK ((Palette*)pc_archive_slots[9])
#define SP_PALETTE ((u16*)pc_archive_slots[5])
#define SP_PALETTES ((Palette*)pc_archive_slots[5])
#define SP_PALETTE_WORDS ((s32*)pc_archive_slots[5])
#define SP_ARC_2C ((void*)pc_archive_slots[11])
#define SP_ARC_30 ((s32*)pc_archive_slots[13])
#define SP_ARC_34 ((void*)pc_archive_slots[16])
#define SP_VRAM_IMAGE ((void*)pc_archive_slots[17])
#define SP_TITLE_FRAMES ((void*)pc_archive_slots[18])
#define SP_ARC_40 ((void*)pc_archive_slots[19])
#define SP_ARC_44 ((void*)pc_archive_slots[20])
#define SP_ARC_48 ((void*)pc_archive_slots[21])
#define SP_CUR_MAIN_OBJ mmx4_sp_current_main
#define SP_CUR_WEAPON_OBJ mmx4_sp_current_weapon
#define SP_CUR_SHOT_OBJ mmx4_sp_current_shot
#define SP_CUR_VISUAL_OBJ mmx4_sp_current_visual
#define SP_CUR_EFFECT_OBJ mmx4_sp_current_effect
#define SP_CUR_ITEM_OBJ mmx4_sp_current_item
#define SP_CUR_MISC_OBJ mmx4_sp_current_misc
#define SP_CUR_UNK_OBJ mmx4_sp_current_unk
#define SP_CUR_QUAD_OBJ mmx4_sp_current_quad
#define SP_CUR_LAYER_OBJ mmx4_sp_current_layer
#define SP_PRIM_CURSOR mmx4_sp_primitive_cursor
#define SP_DRAW_MODE_CURSOR mmx4_sp_draw_mode_cursor
#define SP_BG_PRIM_CURSOR mmx4_sp_background_primitive_cursor
#define SP_OT_CURSOR mmx4_sp_ordering_cursor
#define SP_AUX_CURSOR mmx4_sp_auxiliary_cursor
#define SP_AUX_POLY_F4_CURSOR ((POLY_F4*)mmx4_sp_auxiliary_cursor)
#define SP_BG_BLOCK_WIDTH (*MMX4_SP_PTR(0x10C, u32))
#define SP_BG_BLOCK_HEIGHT (*MMX4_SP_PTR(0x110, u32))
#define SP_CUR_BG_INDEX (*MMX4_SP_PTR(0x114, s32))
#define SP_BG_BLOCK (*MMX4_SP_PTR(0x118, u8))
#define SP_BG_SPRITE_COUNT (*MMX4_SP_PTR(0x11C, s32))
#define SP_SPRITE_COUNT (*MMX4_SP_PTR(0x124, s32))
#define SP_ARCHIVE_ENTRY(archive, index) \
    ((s32*)((u8*)(archive) + (archive)[index]))
#else
#ifdef MMX4_WIN32
extern u8* scratchpad_base;
#define SP(offset) (scratchpad_base + (offset))
#else
#define SP(offset) (0x1F800000 + (offset))
#endif
#define SP_DRAW_BUFFER (*(s32*)SP(0x000))
#define SP_BG_TILEMAP (*(u8**)SP(0x004))
#define SP_BG_TILE_PIXELS (*(u16**)SP(0x008))
#define SP_BG_TILE_ATTRS (*(u32**)SP(0x00C))
#define SP_PLAYER_GFX (*(s32**)SP(0x014))
#define SP_SPRITE_FRAMES (*(s32**)SP(0x01C))
#define SP_SPRITE_FRAMES_HDR (*(struct Scratchpad1C**)SP(0x01C))
#define SP_MENU_FRAMES (*(s32**)SP(0x020))
#define SP_PALETTE_BANK (*(Palette**)SP(0x024))
#define SP_PALETTE (*(u16**)SP(0x028))
#define SP_PALETTES (*(Palette**)SP(0x028))
#define SP_PALETTE_WORDS (*(s32**)SP(0x028))
#define SP_ARC_2C (*(void**)SP(0x02C))
#define SP_ARC_30 (*(s32**)SP(0x030))
#define SP_ARC_34 (*(void**)SP(0x034))
#define SP_VRAM_IMAGE (*(void**)SP(0x038))
#define SP_TITLE_FRAMES (*(void**)SP(0x03C))
#define SP_ARC_40 (*(void**)SP(0x040))
#define SP_ARC_44 (*(void**)SP(0x044))
#define SP_ARC_48 (*(void**)SP(0x048))
#define SP_CUR_MAIN_OBJ (*(struct MainObj**)SP(0x04C))
#define SP_CUR_WEAPON_OBJ (*(struct WeaponObj**)SP(0x050))
#define SP_CUR_SHOT_OBJ (*(struct ShotObj**)SP(0x050))
#define SP_CUR_VISUAL_OBJ (*(struct VisualObj**)SP(0x054))
#define SP_CUR_EFFECT_OBJ (*(struct EffectObj**)SP(0x05C))
#define SP_CUR_ITEM_OBJ (*(struct ItemObj**)SP(0x060))
#define SP_CUR_MISC_OBJ (*(struct MiscObj**)SP(0x064))
#define SP_CUR_UNK_OBJ (*(struct UnkObj**)SP(0x064))
#define SP_CUR_QUAD_OBJ (*(struct QuadObj**)SP(0x068))
#define SP_CUR_LAYER_OBJ (*(struct LayerObj**)SP(0x06C))
#define SP_PRIM_CURSOR (*(void**)SP(0x100))
#define SP_DRAW_MODE_CURSOR (*(void**)SP(0x104))
#define SP_BG_PRIM_CURSOR (*(void**)SP(0x108))
#define SP_OT_CURSOR (*(void**)SP(0x10C))
#define SP_AUX_CURSOR (*(void**)SP(0x110))
#define SP_AUX_POLY_F4_CURSOR (*(POLY_F4**)SP(0x110))
#define SP_BG_BLOCK_WIDTH (*(u32*)SP(0x10C))
#define SP_BG_BLOCK_HEIGHT (*(u32*)SP(0x110))
#define SP_CUR_BG_INDEX (*(s32*)SP(0x114))
#define SP_BG_BLOCK (*(u8*)SP(0x118))
#define SP_BG_SPRITE_COUNT (*(s32*)SP(0x11C))
#define SP_SPRITE_COUNT (*(s32*)SP(0x124))
#define SP_ARCHIVE_ENTRY(archive, index) \
    ((s32*)((s32)(archive) + (archive)[index]))
#endif

#endif
