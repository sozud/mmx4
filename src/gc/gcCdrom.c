#include "common.h"
#include "archive_memory.h"
#include "main/2824.h"
#include "main/3D88.h"
#include "gc/collection.h"
#include "gc/dolphin.h"

extern char cd_file_names[][64];

static unsigned long cd_size;
static u8* cd_cursor;
static unsigned long cd_remaining;
static unsigned long cd_partial;
static u8* cd_dest;
static u8 cd_index;
static volatile s8 cd_done;
static DVDFileInfo cd_file;
static u8* cd_buffer;

extern u8 cd_sync_status;

static void callback(long result, DVDFileInfo* fileInfo);
static void callback_arc(long result, DVDFileInfo* fileInfo);

extern struct CdCompletionSlot D_80137D04[16];
extern u8* D_80137DCC;
extern s32 D_80137DC8;
extern s32 D_80137CEC;
extern u8** D_800F15BC[];
extern struct CdImageOrigin D_800F1614[];

#define SWAP32(x) ((((x)&0xFF) << 24) | (((x)&0xFF00) << 8) | (((x) >> 8) & 0xFF00) | ((x) >> 24))
#define LE24(p) (((p)[0] | ((p)[1] << 8) | ((p)[2] << 16) | ((p)[3] << 24)) & 0xFFFFFF)

static u32 gc_sound_data_size;
static u32 gc_vab_body_size;
static u32 gc_vab_slot;
static u8 gc_vab_head_buffer[0x800];
static u8* gc_vab_head;
void func_80013404(u8 arg0);
void func_80013530(void);
void func_800127C8(s32 arg0);

void fn_4_9E6BC(void);

void gc_init_dvd_buffer(void)
{
    cd_buffer = gc_get_dvd_buffer();
    fn_4_9E6BC();
}

#line 333
void func_80013890(u32 index, u8* dest)
{
    cd_index = index;
    cd_dest = (u8*)dest;
    cd_cursor = dest;
    cd_partial = 0;
    if (!DVDOpen(cd_file_names[index], &cd_file)) {
        OSPanic(__FILE__, __LINE__, "open error\n");
    }
    cd_done = 0;
    cd_size = cd_file.length;
    cd_remaining = cd_file.length;
#line 355
    if (!DVDReadAsyncPrio(&cd_file, cd_buffer, OSRoundUp32B(cd_file.length), 0, callback, 2)) {
        OSPanic(__FILE__, __LINE__, "load start error\n");
    }
}

#line 380
void func_80013AD8(s32 index, u8 arg1, CdLoadAddress dest)
{
    u8 i;

    cd_index = index;
    D_80137DDC = arg1;
    cd_dest = (u8*)dest;
    for (i = 0; i < 16; i++) {
        D_80137D04[i].pending = 0;
    }
    switch (arg1) {
    case 0:
        D_80137DCC = MAIN_ARCHIVE_ARENA;
        D_80137DD0 = 0x1010;
        for (i = 0; i < 6; i++) {
            if (i != 2 && D_8013E198[i] != -1) {
                SsVabClose(D_8013E198[i]);
                D_8013E198[i] = -1;
            }
        }
        break;
    case 1:
        D_80137DCC = D_80137DC4;
        break;
    case 2:
        D_80137DCC = (u8*)dest;
        break;
    case 3:
        D_80137DCC = D_80173C80;
        D_80137DD0 = saved_vab_address;
        for (i = 2; i < 6; i++) {
            if (i != 3 && D_8013E198[i] != -1) {
                SsVabClose(D_8013E198[i]);
                D_8013E198[i] = -1;
            }
        }
        break;
    case 4:
        D_80137DD0 = dest;
        D_80137DCC = D_8015D9C8;
        if (D_8013E198[2] != -1) {
            SsVabClose(D_8013E198[2]);
            D_8013E198[2] = -1;
        }
        break;
    }

    cd_partial = 1;
    cd_done = 0;
    if (!DVDOpen(cd_file_names[index], &cd_file)) {
        OSPanic(__FILE__, __LINE__, "open error\n");
    }
    cd_remaining = cd_file.length;
#line 442
    if (!DVDReadAsyncPrio(&cd_file, cd_buffer, OSRoundUp32B(cd_file.length), 0, callback_arc, 2)) {
        OSPanic(__FILE__, __LINE__, "load start error\n");
    }
}

s32 fn_4_12B4(s32 index)
{
    return 1;
}

s32 fn_4_1290(s32 index, u8 arg1, CdLoadAddress dest)
{
    func_80013AD8(index, arg1, dest);
    return 1;
}

s32 fn_4_1288(void)
{
    return 1;
}

void fn_4_1284(void)
{
}

void func_80014A90(s32 arg0, s32 arg1)
{
    int state;

    cd_fade_requested = 0;
    D_8013BD44 = 0;
    while (cd_done != 1) {
        if (cd_fade_requested == 0 && !(arg1 & 0xFF) && main_bss_state.transition.active == 0) {
            func_800129A4(8);
            cd_fade_requested += 1;
        }
        func_80013404(arg0 & 0xFF);
        if (cd_done == -1) {
            OSReport("DVD retry!\n");
            if (cd_partial == 0) {
                func_80013890(cd_index, cd_dest);
            } else {
                func_80013AD8(cd_index, D_80137DDC, (CdLoadAddress)cd_dest);
            }
        }
        state = gc_get_disc_state();
        if (state != 2 && state != 3) {
            gc_disc_error_screen();
        }
        func_800127C8(1);
    }
    gc_set_main_flag(1);
    D_8013BD44 = 1;
    D_80141BD2 = 0x78;
    if (arg1 & 0xFF) {
        func_80013530();
    }
}

void func_80014C70(void)
{
    int state;

    D_8013BD44 = 0;
    while (cd_done != 1) {
        if (cd_done == -1) {
            OSReport("DVD retry!\n");
            if (cd_partial == 0) {
                func_80013890(cd_index, cd_dest);
            } else {
                func_80013AD8(cd_index, D_80137DDC, (CdLoadAddress)cd_dest);
            }
        }
        state = gc_get_disc_state();
        if (state != 2 && state != 3) {
            gc_disc_error_screen();
        }
        func_800127C8(1);
    }
    gc_set_main_flag(1);
    D_8013BD44 = 1;
    D_80141BD2 = 0x78;
}

#line 711
static void callback(long result, DVDFileInfo* fileInfo)
{
    gc_memcpy(cd_dest, cd_buffer, cd_remaining);
    if (!DVDClose(fileInfo)) {
        OSPanic(__FILE__, __LINE__, "fatal error in callback\n");
    }

    if (result == -1) {
        cd_done = -1;
        OSPanic(__FILE__, __LINE__, "load error\n");
    } else {
        cd_done = 1;
    }
    cd_sync_status = 2;
    gc_set_main_flag(1);
}

void func_800148E4(void)
{
}

#line 777
static void callback_arc(long result, DVDFileInfo* fileInfo)
{
    u8* p = cd_buffer;
    u32* entry;
    u32 count;

    if (!DVDClose(fileInfo)) {
        OSPanic(__FILE__, __LINE__, "fatal error in callback_arc\n");
    }
    count = SWAP32(((u32*)p)[0]);
    __stwbrx(((u32*)p)[1], &cd_size, 0);
    D_80137DC4 = D_80137DCC;
    entry = (u32*)p + 2;
    p += 0x800;
    for (D_80137CEC = 0; D_80137CEC != count; D_80137CEC++) {
        u32 raw = entry[0];
        u32 word;
        u32 size;

        __stwbrx(raw, &D_80137CD4.word, 0);
        word = SWAP32(raw);
        size = entry[1];
        entry += 2;
        __stwbrx(size, &cd_remaining, 0);
        if ((word >> 16) == 0) {
            D_80137DC8 = SWAP32(size);
        }
        switch ((word >> 16) & 3) {
        case 0:
            gc_convert_entry(p, D_80137DC4, word, D_80137DC8);
            p += cd_remaining;
            if (((D_80137CD4.word >> 16) & 3) == 0) {
                u8 kind = D_80137CD4.word;

                if (kind == 4 || (kind >= 6 && kind <= 8)) {
                    gc_sound_data_size = cd_remaining;
                }
            }
            *D_800F15BC[D_80137CD4.word] = D_80137DC4;
            D_80137DC4 += D_80137DC8;
            if (cd_remaining & 0x7FF) {
                p += 0x800 - (cd_remaining & 0x7FF);
            }
            break;
        case 1: {
            struct CdImageOrigin* origin = &D_800F1614[(u8)word];
            u16 x = origin->x;
            u16 y = origin->y;
            u16 top = y & 0x100;

            while (cd_remaining != 0) {
                D_80137CFC.x = x;
                D_80137CFC.y = y;
                D_80137CFC.w = 64;
                D_80137CFC.h = 16;
                LoadImage(&D_80137CFC, (u_long*)p);
                p += 0x800;
                switch ((u8)(D_80137CD4.word >> 8)) {
                case 0:
                    if (y == top + 0xF0) {
                        y = top;
                        x += 0x40;
                    } else {
                        y += 0x10;
                    }
                    break;
                case 1:
                    if (y == top + 0xA0) {
                        y = top;
                        x += 0x40;
                    } else {
                        y += 0x10;
                    }
                    break;
                case 2:
                    if (y == 0xF0) {
                        y = 0xB0;
                        x += 0x40;
                    } else {
                        y += 0x10;
                    }
                    break;
                }
                cd_remaining -= 0x800;
            }
            break;
        }
        case 2: {
            u8 slot = word >> 8;
            struct SoundArchive* archive = (struct SoundArchive*)D_80141F00;

            D_80141F30[slot] = D_80137DD0;
            D_80141F50[slot] = (u8*)archive + 8;
            D_80141EE8[slot] = (u8*)archive + (LE24((u8*)archive));
            if (((word >> 16) & 3) == 2) {
                gc_vab_body_size = cd_remaining;
                gc_vab_slot = slot;
                gc_vab_head = gc_vab_head_buffer;
            }
            if (cd_remaining <= 0x800) {
                gc_memcpy(gc_vab_head_buffer, p, cd_remaining);
            }
            p += cd_remaining;
            if (cd_remaining & 0x7FF) {
                p += 0x800 - (cd_remaining & 0x7FF);
            }
            gc_vab_open(D_80141EE8[gc_vab_slot], gc_vab_slot, gc_sound_data_size);
            D_8013E198[gc_vab_slot] = gc_vab_transfer(gc_vab_head_buffer, gc_vab_slot, gc_vab_body_size);
            break;
        }
        case 3:
            p += cd_remaining;
            if (cd_remaining & 0x7FF) {
                p += 0x800 - (cd_remaining & 0x7FF);
            }
            break;
        }
    }
    D_8015D9C8 = D_80137DC4;
    loaded_vab_address = D_80137DD0;
    if (result == -1) {
        cd_done = -1;
        OSReport("load error\n");
    } else {
        cd_done = 1;
    }
    gc_set_main_flag(1);
    cd_sync_status = 2;
}
