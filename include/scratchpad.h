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
extern void* mmx4_sp_background_cursor;
extern void* mmx4_sp_background_primitive_cursor;
extern void* mmx4_sp_ordering_cursor;
extern void* mmx4_sp_auxiliary_cursor;
extern u8* pc_archive_slots[22];
#define MMX4_SP_PTR(offset, type) ((type*)(void*)&mmx4_scratchpad[(offset)])
#define SP_DRAW_INFO_POS (*MMX4_SP_PTR(0x000, s32))
#define SP_LAYOUT_DATA ((u8*)mmx4_sp_background_cursor)
#define SP_TABLE_08 ((u16*)pc_archive_slots[0])
#define SP_TABLE_0C ((u16*)pc_archive_slots[1])
#define SP_1C ((struct Scratchpad1C*)pc_archive_slots[3])
#define SP_TABLE_14 ((s32*)pc_archive_slots[2])
#define SP_TABLE_1C ((s32*)pc_archive_slots[3])
#define SP_TABLE_20 ((s32*)pc_archive_slots[10])
#define SP_TABLE_24 ((u16*)pc_archive_slots[9])
#define SP_TABLE_28 ((u16*)pc_archive_slots[5])
#define SP_TABLE_30 ((s32*)pc_archive_slots[13])
#define SP_TABLE_3C ((void*)pc_archive_slots[18])
#define SP_DRAW_COUNT (*MMX4_SP_PTR(0x124, s32))
#else
#define SP_DRAW_INFO_POS (*(s32*)0x1F800000)
#define SP_LAYOUT_DATA (*(u8**)0x1F800004)
#define SP_TABLE_08 (*(u16**)0x1F800008)
#define SP_TABLE_0C (*(u16**)0x1F80000C)
#define SP_1C (*(struct Scratchpad1C**)0x1F80001C)
#define SP_TABLE_14 (*(s32**)0x1F800014)
#define SP_TABLE_1C (*(s32**)0x1F80001C)
#define SP_TABLE_20 (*(s32**)0x1F800020)
#define SP_TABLE_24 (*(u16**)0x1F800024)
#define SP_TABLE_28 (*(u16**)0x1F800028)
#define SP_TABLE_30 (*(s32**)0x1F800030)
#define SP_TABLE_3C (*(void**)0x1F80003C)
#define SP_DRAW_COUNT (*(s32*)0x1F800124)
#endif
#define SP_PALETTE ((volatile u32*)SP_TABLE_28)

#endif
