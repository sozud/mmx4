#include "common.h"

extern s32 mmx4_pc_canonical_load;
extern u8 D_80137DD8;
extern u8* D_80137DE0;
extern s32 D_80137DE4;

static void advance_cd_load(void)
{
    if (D_801406AC == 1) {
        if (D_80137CD8 == 0)
            MyCdReadyCallback(CdlDataReady, NULL);
        else
            func_80013E68(CdlDataReady, NULL);
    }
    if (!mmx4_pc_canonical_load)
        func_80014780();
}

void func_80013530(void)
{
    if (!mmx4_pc_canonical_load) {
        SetDispMask(0);
        return;
    }
    func_800129F0(0x10);
    if (D_80141BDC[0] != 0) {
        do {
            func_80013404(0);
            func_800127C8(1);
        } while (D_80141BDC[0] != 0);
    }
}

void func_80014A90(s32 arg0, s32 arg1)
{
    u8 mode = 0xA0;
    u32 state = D_801406AC;

    D_80137DD4 = 0;
    D_8013BD44 = 0;
    while (state != 2 || D_8013BD40 != 0) {
        advance_cd_load();
        if (mmx4_pc_canonical_load) {
            if (D_80137DD4 == 0 && !(arg1 & 0xff) && D_80141BDC[0] == 0) {
                func_800129A4(8);
                D_80137DD4++;
            }
            func_80013404(arg0 & 0xff);
        }
        if (D_801406AC & 0xc0) {
            if (D_80137CD8 == 0)
                func_80013890(D_80137DD8, D_80137DE0);
            else
                func_80013AD8(D_80137DD8, D_80137DDC, (CdLoadAddress)D_80137DE0);
        } else if (++D_80137DE4 >= 0x259U) {
            CdReadyCallback(NULL);
            while (CdReset(0) == 0)
                ;
            while (CdControlB(0xE, &mode, NULL) == 0)
                ;
            VSync(3);
            D_801406AC = 0xc0;
        }
        if (mmx4_pc_canonical_load)
            func_800127C8(1);
        state = D_801406AC;
    }
    D_8013BD44 = 1;
    D_80141BD2 = 0x78;
    if (arg1 & 0xff)
        func_80013530();
}

void func_80014C70(void)
{
    u8 mode = 0xA0;
    s32 state = D_801406AC;

    D_8013BD44 = 0;
    while (state != 2 || D_8013BD40 != 0) {
        advance_cd_load();
        if (D_801406AC & 0xc0) {
            if (D_80137CD8 == 0)
                func_80013890(D_80137DD8, D_80137DE0);
            else
                func_80013AD8(D_80137DD8, D_80137DDC, (CdLoadAddress)D_80137DE0);
        } else if (++D_80137DE4 >= 0x259U) {
            CdReadyCallback(NULL);
            while (CdReset(0) == 0)
                ;
            while (CdControlB(0xE, &mode, NULL) == 0)
                ;
            VSync(3);
            D_801406AC = 0xc0;
        }
        if (mmx4_pc_canonical_load)
            func_800127C8(1);
        state = D_801406AC;
    }
    D_8013BD44 = 1;
    D_80141BD2 = 0x78;
}

extern struct ArchiveSelectionData D_800EE480;
extern u8* pc_archive_slots[22];
extern u8 D_80110064[64];

void func_80013014(void)
{
    u8* archive_ids = D_800EE480.archive_ids;
    u32 table_index;
    u32 count;
    u16* source;
    u16* destination;
    u8 first_asset;
    u8 second_asset;

    archive_ids[0x1e] = archive_ids[0x24 + engine_obj.cur_character];
    archive_ids[0x16] = archive_ids[0x28 + engine_obj.cur_character];
    if (engine_obj.stage == 0x0d && engine_obj.substage != 0) {
        archive_ids[0x1b] = archive_ids[0x2b + engine_obj.unk40];
        archive_ids[0x4f] = archive_ids[0x4f + engine_obj.unk40];
        archive_ids[0x6f] = archive_ids[0x73 + engine_obj.unk40];
    } else {
        archive_ids[0x1a] = archive_ids[0x20 + engine_obj.cur_character];
    }
    table_index = engine_obj.stage * 2 + engine_obj.substage;
    if (engine_obj.stage == 0x0e)
        first_asset = archive_ids[0x1c + engine_obj.substage];
    else
        first_asset = archive_ids[table_index];
    func_80013AD8(first_asset, engine_obj.stage == 0x0e ? 0 : 3, 0);
    func_80014A90(engine_obj.stage < 0x0d, 0);
    second_asset = archive_ids[
        (engine_obj.cur_character == CHARACTER_X ? 0x34 : 0x54) + table_index];
    func_80013AD8(second_asset, 1, 0);
    func_80014A90(engine_obj.stage < 0x0d, 1);
    source = (u16*)pc_archive_slots[0];
    destination = (u16*)D_8015D9C8;
    count = (pc_archive_slots[1] - pc_archive_slots[0]) / sizeof(*source);
    D_801441B4 = destination;
    while (count--)
        *destination++ = *source++;
    D_8015D9C8 += pc_archive_slots[1] - pc_archive_slots[0];
    table_index = engine_obj.stage * 4 + engine_obj.substage * 2;
    layout_width = D_80110064[table_index];
    layout_height = D_80110064[table_index + 1];
    layout_size = layout_width * layout_height;
    func_80016074();
    need_palette_load |= 1;
}
