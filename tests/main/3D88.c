#include "test_runtime.h"
#ifndef MMX4_SATURN
#include "main/3D88.h"
#include "support/cd_disc.h"
#include "archive_memory.h"
#include "main/55C4.h"
#include <psyz/spu.h>
#include <stddef.h>
#include <stdlib.h>
void MyCdReadyCallback(u8, u8*);
void func_800142BC(void);
void func_80014514(void);
extern s32 D_80137CC8;
extern s32 D_80137CBC, D_80137CC0, D_80137CCC, D_80137CD8, D_80137CEC, D_80137DE4;
extern u8* D_80137CC4;
extern u8* D_80137DC4;
extern struct CdCompletionSlot D_80137D04[16];
extern s32 mmx4_pc_canonical_load;
extern u8* D_80137DCC;
extern u8* D_80137DE0;
extern u8 D_80137DD8;
static u32 sectors[2048], sectors_before[2048];
static u32 inactive(u32 row)
{
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 response = 0x03020101, i;
    s32 remaining = row ? 6144 : 8192, sector = row ? 31 : 27;
    for (i = 0; i < COUNT(sectors); i++)
        sectors[i] = sectors_before[i] = 0x13570000 + i;
    D_801406AC = 0;
    D_80137CD8 = 0;
    D_80137CCC = func_80013614(row, &D_80137CC8) - 1;
    D_80137CBC = D_80137CC8;
    D_80137CC4 = (u8*)sectors;
    D_80137CEC = 0;
    MyCdReadyCallback(CdlDataReady, (u8*)&response);
    assert(D_801406AC == 0 && D_80137CD8 == 0 && D_80137CBC == remaining && D_80137CC8 == remaining && D_80137CC4 == (u8*)sectors && D_80137CCC == sector && D_80137CC0 == (row ? 1 : 2) && D_80137CEC == 0 && response == 0x03020101);
    c_test_same_words(sectors, sectors_before, sizeof(sectors));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

static u8 raw_buffer[0x8000];
static u32 raw_file(s32* size)
{
    u32 index;
    for (index = 0; index < 0x50; index++) {
        func_80013614(index, size);
        if (*size % 0x800 == 0 && *size <= 0x6000 && *size > 0x1000)
            return index;
    }
    assert(!"no file of that shape");
    return 0;
}
enum { RAW_WRONG_LAST,
    RAW_UNREADABLE,
    RAW_RESTARTED };
static u32 raw_load(u32 row)
{
    s32 size, start, i, count;
    u32 index = raw_file(&size), copied;
    start = func_80013614(index, &size);
    count = (size + 0x7FF) / 0x800;
    cd_disc_insert(start);
    if (row == RAW_WRONG_LAST)
        cd_disc_wrong_header = start + count - 1;
    if (row == RAW_UNREADABLE)
        cd_disc_unreadable = start + 1;
    memset(raw_buffer, 0xA5, sizeof(raw_buffer));
    mmx4_pc_canonical_load = 0;
    D_801406AC = 0;
    D_80137DE4 = 99;
    D_80137DC4 = (u8*)0x1234;
    if (row == RAW_RESTARTED)
        func_80013890(index, raw_buffer);
    func_80013890(index, raw_buffer);
    func_80014C70();
    cd_disc_eject();
    copied = (size + 3) & ~3;
    for (i = 0; i < (s32)sizeof(raw_buffer); i++)
        assert(raw_buffer[i] == (i < (s32)copied ? cd_disc_byte(i / 0x800, i % 0x800) : 0xA5));
    assert(D_801406AC == 2 && D_80137CD8 == 0 && D_80137CBC == 0 && D_8013BD40 == 0);
    assert(D_8015D9C8 == (u8*)0x1234);
    for (i = 0; i < count; i++) {
        u32 again = (row == RAW_UNREADABLE || row == RAW_RESTARTED) && i == 0;
        again |= row == RAW_WRONG_LAST;
        assert(cd_disc_reads[i] == 1 + again);
    }
    switch (row) {
    case RAW_UNREADABLE:
        assert(D_80137DE4 == 1 + count);
        break;
    case RAW_WRONG_LAST:
        assert(D_80137DE4 == count - 1 + count);
        break;
    default:
        assert(D_80137DE4 == count);
    }
    return D_80137DE4;
}

#define ARCHIVE_FILE 0
static u8 archive_buffer[0x6000];
static u32 archive_word, archive_sector;
static s32 archive_start(void)
{
    s32 size;
    return func_80013614(ARCHIVE_FILE, &size);
}
static void archive_begin(u32 count)
{
    cd_disc_insert(archive_start());
    memset(cd_disc_data[0], 0, 0x800);
    cd_disc_put_word(0, 0, count);
    cd_disc_put_word(0, 1, 0x5A5A);
    archive_word = 2;
    archive_sector = 1;
    memset(archive_buffer, 0xA5, sizeof(archive_buffer));
}
static u32 archive_entry(u32 command, u32 size)
{
    u32 first = archive_sector;
    cd_disc_put_word(0, archive_word++, command);
    cd_disc_put_word(0, archive_word++, size);
    archive_sector += (size + 0x7FF) / 0x800;
    return first;
}
static void archive_bytes(u32 sector, const void* bytes, u32 size)
{
    memcpy(&cd_disc_data[sector][0], bytes, size);
}
static void archive_run(u32 mode, CdLoadAddress address)
{
    mmx4_pc_canonical_load = 0;
    D_801406AC = 0;
    D_80137DE4 = 99;
    func_80013AD8(ARCHIVE_FILE, mode, address);
    func_80014C70();
    cd_disc_eject();
    assert(D_801406AC == 2 && D_80137CD8 == 1 && D_8013BD40 == 0 && D_80137CC8 == 0x5A5A);
}
static void archive_check_slots(u32 count, const u32* places)
{
    u32 i;
    for (i = 0; i < count; i++) {
        u32 slot = i % 16, sector = 1 + i;
        if (i + 16 < count)
            continue;
        assert(D_80137D04[slot].pending == 0 && D_80137D04[slot].callback == 1);
        assert(D_80137D04[slot].callback_arg == places[i]);
        assert(memcmp(D_8012F4B4.sectors[slot], cd_disc_data[sector], 0x800) == 0);
    }
    assert(D_801374B8 == count % 16 && D_801374B4 == count % 16);
    assert(D_80137CF0 == count && D_80137CF4 == count);
    assert(D_80137CFC.x == places[count - 1] >> 16 && D_80137CFC.y == (places[count - 1] & 0xFFFF));
    assert(D_80137CFC.w == 0x40 && D_80137CFC.h == 0x10);
}
#define PLACE(x, y) ((u32)(x) << 16 | (y))
extern u32 D_8012F4A8, D_8012F4AC;
enum { ARCHIVE_DATA,
    ARCHIVE_COLUMN,
    ARCHIVE_SHORT_COLUMN,
    ARCHIVE_LOW_COLUMN };
static u32 archive_images(u32 row)
{
    static const u32 column[17] = { PLACE(0x140, 0x100), PLACE(0x140, 0x110), PLACE(0x140, 0x120), PLACE(0x140, 0x130),
        PLACE(0x140, 0x140), PLACE(0x140, 0x150), PLACE(0x140, 0x160), PLACE(0x140, 0x170), PLACE(0x140, 0x180),
        PLACE(0x140, 0x190), PLACE(0x140, 0x1A0), PLACE(0x140, 0x1B0), PLACE(0x140, 0x1C0), PLACE(0x140, 0x1D0),
        PLACE(0x140, 0x1E0), PLACE(0x140, 0x1F0), PLACE(0x180, 0x100) };
    static const u32 short_column[12] = { PLACE(0x340, 0x100), PLACE(0x340, 0x110), PLACE(0x340, 0x120),
        PLACE(0x340, 0x130), PLACE(0x340, 0x140), PLACE(0x340, 0x150), PLACE(0x340, 0x160), PLACE(0x340, 0x170),
        PLACE(0x340, 0x180), PLACE(0x340, 0x190), PLACE(0x340, 0x1A0), PLACE(0x380, 0x100) };
    static const u32 low_column[8] = { PLACE(0x140, 0xB0), PLACE(0x140, 0xC0), PLACE(0x140, 0xD0), PLACE(0x140, 0xE0),
        PLACE(0x140, 0xF0), PLACE(0x180, 0xB0), PLACE(0x180, 0x000), PLACE(0x180, 0x000) };
    u8* saved[2] = { pc_archive_slots[16], pc_archive_slots[17] };
    s32 start = archive_start(), i;
    u32 polls;
    switch (row) {
    case ARCHIVE_DATA:
        archive_begin(2);
        archive_entry(16, 0x900);
        archive_entry(17, 0x800);
        cd_disc_wrong_header = start + 2;
        archive_run(2, (CdLoadAddress)archive_buffer);
        for (i = 0; i < (s32)sizeof(archive_buffer); i++)
            assert(archive_buffer[i] == (i < 0x900 ? cd_disc_byte(1 + i / 0x800, i % 0x800) : i < 0x1100 ? cd_disc_byte(3, i - 0x900)
                                                                                                         : 0xA5));
        assert(pc_archive_slots[16] == archive_buffer && pc_archive_slots[17] == archive_buffer + 0x900);
        assert(D_8015D9C8 == archive_buffer + 0x1100);
        assert(cd_disc_reads[0] == 2 && cd_disc_reads[1] == 2 && cd_disc_reads[2] == 2 && cd_disc_reads[3] == 1);
        polls = 2 + 4;
        break;
    case ARCHIVE_COLUMN:
        archive_begin(1);
        archive_entry(0x00010000, 17 * 0x800);
        cd_disc_wrong_header = start + 6;
        archive_run(2, (CdLoadAddress)archive_buffer);
        archive_check_slots(17, column);
        assert(D_8012F4A8 == 0x180 && D_8012F4AC == 0x110);
        polls = 6 + 18;
        break;
    case ARCHIVE_SHORT_COLUMN:
        archive_begin(1);
        archive_entry(0x00010107, 12 * 0x800);
        cd_disc_wrong_header = start;
        archive_run(2, (CdLoadAddress)archive_buffer);
        archive_check_slots(12, short_column);
        assert(D_8012F4A8 == 0x380 && D_8012F4AC == 0x110);
        polls = 13;
        break;
    default:
        archive_begin(2);
        archive_entry(0x00010206, 6 * 0x800);
        archive_entry(0x00010302, 2 * 0x800);
        cd_disc_unreadable = start;
        archive_run(2, (CdLoadAddress)archive_buffer);
        archive_check_slots(8, low_column);
        assert(D_8012F4A8 == 0x180 && D_8012F4AC == 0);
        polls = 9;
        break;
    }
    assert(D_80137DE4 == polls);
    for (i = 0; i < (s32)sizeof(archive_buffer); i++)
        assert(row == ARCHIVE_DATA || archive_buffer[i] == 0xA5);
    pc_archive_slots[16] = saved[0];
    pc_archive_slots[17] = saved[1];
    return polls;
}

struct ArchiveSoundBank {
    u32 packed, body_size;
    u8 commands[16];
    VabHdr header;
    ProgAtr programs[128];
    VagAtr tones[16];
    u16 lengths[256];
};
#define ARCHIVE_BODY 0x8000
static struct ArchiveSoundBank archive_bank;
static const u8 archive_sep[] = {
    'p',
    'Q',
    'E',
    'S',
    0,
    0,
    0,
    0,
    0,
    48,
    0x07,
    0xA1,
    0x20,
    4,
    2,
    0,
    0,
    0,
    4,
    0,
    0xFF,
    0x2F,
    0,
    0,
    1,
    0,
    48,
    0x07,
    0xA1,
    0x20,
    4,
    2,
    0,
    0,
    0,
    4,
    0,
    0xFF,
    0x2F,
    0,
    0,
    2,
    0,
    48,
    0x07,
    0xA1,
    0x20,
    4,
    2,
    0,
    0,
    0,
    4,
    0,
    0xFF,
    0x2F,
    0,
};
static void archive_make_bank(u32 form)
{
    memset(&archive_bank, 0, sizeof(archive_bank));
    archive_bank.packed = 2u << 24 | offsetof(struct ArchiveSoundBank, header);
    archive_bank.body_size = ARCHIVE_BODY;
    archive_bank.header.form = form;
    archive_bank.header.ver = 7;
    archive_bank.header.id = 2;
    archive_bank.header.fsize = sizeof(archive_bank) - offsetof(struct ArchiveSoundBank, header) + ARCHIVE_BODY;
    archive_bank.header.ps = archive_bank.header.ts = archive_bank.header.vs = 1;
    archive_bank.header.mvol = 127;
    archive_bank.header.pan = 64;
    archive_bank.programs[0].tones = 1;
    archive_bank.programs[0].mvol = 127;
    archive_bank.programs[0].mpan = 64;
    archive_bank.tones[0].vol = 127;
    archive_bank.tones[0].pan = 64;
    archive_bank.tones[0].center = 60;
    archive_bank.tones[0].max = 127;
    archive_bank.tones[0].vag = 1;
    archive_bank.lengths[1] = ARCHIVE_BODY / 8;
}
static u32 archive_sound(u32 row)
{
    u8* saved_header = D_80141F00;
    u8* saved_entries = D_80141F50[2];
    u8* saved_bank = D_80141EE8[2];
    u32 saved_address = D_80141F30[2];
    s32 start = archive_start(), body, sep, other;
    u8* ram;
    int success = setenv("SDL_AUDIODRIVER", "dummy", 1);
    assert(success == 0);
    Psyz_SpuInit();
    func_80014DC4();
    archive_make_bank(0x56414270);
    archive_begin(4);
    archive_bytes(archive_entry(4, sizeof(archive_bank)), &archive_bank, sizeof(archive_bank));
    body = archive_entry(0x00020200, ARCHIVE_BODY);
    sep = archive_entry(0x00030200, sizeof(archive_sep));
    archive_bytes(sep, archive_sep, sizeof(archive_sep));
    archive_bytes(archive_entry(0x00030200, 0x900), archive_sep, sizeof(archive_sep));
    cd_disc_wrong_header = start + sep;
    ram = Psyz_SpuGetRam();
    memset(ram + 0x10000, 0xCC, ARCHIVE_BODY);
    D_8015D9C8 = archive_buffer;
    archive_run(4, 0x10000);
    assert(D_80141F00 == archive_buffer && memcmp(archive_buffer, &archive_bank, offsetof(struct ArchiveSoundBank, programs)) == 0);
    assert(memcmp(archive_buffer + sizeof(archive_bank), archive_sep, sizeof(archive_sep)) == 0);
    assert(D_8015D9C8 == archive_buffer + sizeof(archive_bank));
    assert(D_8013E198[2] == 2 && D_80141F30[2] == 0x10000);
    assert(D_80141EE8[2] == archive_buffer + offsetof(struct ArchiveSoundBank, header));
    assert(D_80141F50[2] == archive_buffer + 8);
    assert(memcmp(ram + 0x10000, cd_disc_data[body], ARCHIVE_BODY) == 0);
    assert(D_80137DD0 == 0x10000 + ARCHIVE_BODY && loaded_vab_address == 0x10000 + ARCHIVE_BODY);
    assert(D_8013E1C8[2] == 0);
    other = SsSepOpenJ((unsigned long*)archive_sep, 2, 3);
    assert(other == 1);
    SsSepClose(other);
    SsSepClose(D_8013E1C8[2]);
    SsVabClose(D_8013E198[2]);
    func_80014DC4();
    assert(D_80137DE4 == 19 + 22);
    D_80141F00 = saved_header;
    D_80141F50[2] = saved_entries;
    D_80141EE8[2] = saved_bank;
    D_80141F30[2] = saved_address;
    return D_80137DE4;
}

enum { GUARD_IMAGE_RING,
    GUARD_BANK_RING,
    GUARD_BAD_BANK,
    GUARD_STOPPED,
    GUARD_BANK_SECTOR };
static u32 handler_guard(u32 row)
{
    u8* saved_header = D_80141F00;
    u8* saved_entries = D_80141F50[3];
    u8* saved_bank = D_80141EE8[3];
    u32 saved_address = D_80141F30[3];
    if (row == GUARD_BANK_SECTOR) {
        CdlLOC position;
        u8 mode = 0xA0;
        s32 start = archive_start();
        cd_disc_insert(start);
        cd_disc_wrong_header = start + 1;
        CdControl(CdlSetmode, &mode, NULL);
        CdControl(CdlSetloc, (u8*)CdIntToPos(start + 1, &position), NULL);
        CdControl(CdlReadN, NULL, NULL);
        assert(CdReady(1, NULL) == CdlDataReady);
        D_80137CCC = start;
        D_80137CBC = 0x800;
    }
    D_801406AC = row == GUARD_STOPPED ? 0x80 : 1;
    D_80137CF0 = 0;
    D_80137CF4 = row == GUARD_BAD_BANK || row == GUARD_BANK_SECTOR ? 0 : 6;
    D_801374B8 = 6;
    D_80137CE8 = row == GUARD_BAD_BANK;
    D_80137CEC = 0;
    D_80137D04[6].pending = 0;
    D_80137D04[6].transfer_pending = 0x1234;
    D_80137CD4.word = 0x00020300;
    D_80137DD0 = 0x10000;
    D_8013E198[3] = 5;
    archive_make_bank(0);
    D_80141F00 = (u8*)&archive_bank;
    CdReadyCallback(func_80013E68);
    switch (row) {
    case GUARD_IMAGE_RING:
        func_800142BC();
        break;
    case GUARD_STOPPED:
        func_80013E68(CdlDataReady, NULL);
        break;
    default:
        func_80014514();
    }
    if (row == GUARD_STOPPED) {
        assert(CdReadyCallback(NULL) == func_80013E68);
        assert(D_80137CEC == 0 && D_8013E198[3] == 5);
    } else {
        assert(CdReadyCallback(NULL) == NULL);
        assert(D_80137CF4 == (row == GUARD_BAD_BANK || row == GUARD_BANK_SECTOR ? 1 : 7));
    }
    assert(D_801406AC == 0x80 && D_801374B8 == 6 && D_80137D04[6].pending == 0);
    assert(D_80137D04[6].transfer_pending == (row == GUARD_BAD_BANK || row == GUARD_BANK_SECTOR ? 0 : 0x1234));
    if (row == GUARD_BANK_SECTOR) {
        assert(D_8013E198[3] == 5 && D_80137CCC == archive_start() && D_80137CBC == 0x800);
        cd_disc_eject();
    }
    if (row == GUARD_BAD_BANK) {
        assert(D_8013E198[3] == -1 && D_80141F30[3] == 0x10000 && D_80137DD0 == 0x10000 && D_80137CE8 == 1);
        assert(D_80141EE8[3] == (u8*)&archive_bank.header && D_80141F50[3] == (u8*)&archive_bank + 8);
    }
    D_80141F00 = saved_header;
    D_80141F50[3] = saved_entries;
    D_80141EE8[3] = saved_bank;
    D_80141F30[3] = saved_address;
    D_8013E198[3] = -1;
    return D_80137CF4;
}

static u32 archive_destination(u32 row)
{
    static const u8 modes[] = { 0, 1, 3 };
    static const s8 banks[] = { 3, -1, 7, 4, -1, 2 };
    static const s8 kept[3][6] = { { -1, -1, 7, -1, -1, -1 }, { 3, -1, 7, 4, -1, 2 }, { 3, -1, -1, 4, -1, -1 } };
    u8* destinations[3] = { MAIN_ARCHIVE_ARENA, (u8*)0x4321, (u8*)0x5555 };
    static const s32 addresses[3] = { 0x1010, 0x1111, 0x2222 };
    s32 start = archive_start(), size;
    u32 i, mode = modes[row];
    CdlLOC position;
    cd_disc_insert(start);
    memcpy(D_8013E198, banks, sizeof(banks));
    for (i = 0; i < 16; i++)
        D_80137D04[i].pending = 1;
    D_80137DC4 = (u8*)0x4321;
    D_80173C80 = (u8*)0x5555;
    saved_vab_address = 0x2222;
    D_80137DD0 = 0x1111;
    D_801374B4 = D_801374B8 = D_80137CF0 = D_80137CF4 = 3;
    D_8013BD40 = 1;
    D_801406AC = 0;
    D_80137DE4 = 99;
    func_80013AD8(ARCHIVE_FILE, mode, 0x7777);
    if (mode == 1)
        func_80013AD8(ARCHIVE_FILE, mode, 0x7777);
    assert(CdReadyCallback(NULL) == func_80013E68);
    position = *CdLastPos();
    cd_disc_eject();
    assert(D_80137DCC == destinations[row] && D_80137DD0 == addresses[row]);
    assert(memcmp(D_8013E198, kept[row], sizeof(banks)) == 0);
    for (i = 0; i < 16; i++)
        assert(D_80137D04[i].pending == 0);
    assert(D_801374B4 == 0 && D_801374B8 == 0 && D_80137CF0 == 0 && D_80137CF4 == 0 && D_8013BD40 == 0);
    assert(D_801406AC == 1 && D_80137CD8 == 1 && D_80137DE4 == 0 && D_80137CEC == 0);
    assert(D_80137DD8 == ARCHIVE_FILE && D_80137DDC == mode && D_80137DE0 == (u8*)0x7777);
    assert(D_80137CCC == start && D_80137CBC == (func_80013614(ARCHIVE_FILE, &size), size));
    assert(CdPosToInt(&position) == start);
    assert(cd_disc_reads[0] == (mode == 1));
    memset(D_8013E198, -1, sizeof(banks));
    return mode;
}

static u32 completion_drain(u32 row)
{
    D_8013BD40 = 1;
    D_801374B4 = 15;
    D_80137CF0 = 0;
    D_80137CF4 = 2;
    D_80137D04[15].pending = 1;
    D_80137D04[15].callback = 0;
    D_80137D04[0].pending = 0;
    func_80014780();
    assert(D_80137D04[15].pending == 0 && D_801374B4 == 0 && D_80137CF0 == 1 && D_8013BD40 == 1);
    D_8013BD40 = 0;
    return D_80137CF0;
}

const struct CTestGroup c_test_groups[] = {
    { "normal_CD_ready_callback_registered_before_read_active_flag_ignores_notification", NULL, NULL, 1, inactive },
    { "raw_file_load", NULL, NULL, 3, raw_load },
    { "archive_data_and_images", NULL, NULL, 4, archive_images },
    { "archive_sound_bank_and_sequences", NULL, NULL, 1, archive_sound },
    { "archive_handler_guards", NULL, NULL, 5, handler_guard },
    { "archive_destinations", NULL, NULL, 3, archive_destination },
    { "completion_drain_short", NULL, NULL, 1, completion_drain },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1 + 3 + 4 + 1 + 5 + 3 + 1;
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
