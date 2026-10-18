#include "test_runtime.h"
#include "main/movie_hud_data.h"
extern void func_80018FD0(u32 arg0);
extern void func_80019058(s8 arg0);
extern void func_80019228(void);
void func_800192F8(void);
#include "main/55C4.h"
#ifdef MMX4_PC
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#endif
void func_80012D68(u32*, u32*, s32);

static u32 same_bytes(const void* lhs, const void* rhs, u32 size)
{
    const u8* a = lhs;
    const u8* b = rhs;
    u32 i;
    for (i = 0; i < size; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

static u32 copy_words(void)
{
    u32 source[3] = { 0x01234567, 0x89ABCDEF, 0xFEDCBA98 };
    u32 before[3];
    u32 destination[5] = { 0xCAFEBABE, 0, 0, 0, 0xDEADBEEF };
    u32 actual;
    memcpy(before, source, sizeof(before));
    func_80012D68(source, destination + 1, COUNT(source));
    assert(destination[0] == 0xCAFEBABE && destination[4] == 0xDEADBEEF);
    assert(same_bytes(source, before, sizeof(source)));
    actual = same_bytes(destination + 1, source, sizeof(source));
    return actual;
}

static u32 decode_pair(u32 pair)
{
    u16 source[23], before[23], destination[22];
    u32 i;
    source[0] = 0x4000;
    source[1] = 0xABCD;
    source[2] = 0x0801;
    for (i = 2; i < 16; i++)
        source[i + 1] = 0x1000 + i;
    source[17] = 0xE000;
    source[18] = 0x1000;
    source[19] = 1;
    source[20] = 2;
    source[21] = 0;
    source[22] = 0;
    memcpy(before, source, sizeof(before));
    for (i = 0; i < COUNT(destination); i++)
        destination[i] = 0xCCCC;
    destination[0] = 0xBEEF;
    destination[21] = 0xC0DE;
    decompress_gfx(source, destination + 1);
    assert(destination[0] == 0xBEEF && destination[21] == 0xC0DE);
    assert(same_bytes(source, before, sizeof(source)));
    return destination[1 + pair * 2] | ((u32)destination[2 + pair * 2] << 16);
}
#define DECODE_CASE(index)          \
    static u32 decode_##index(void) \
    {                               \
        return decode_pair(index);  \
    }
DECODE_CASE(0)
DECODE_CASE(1)
DECODE_CASE(2)
DECODE_CASE(3)
DECODE_CASE(4)
DECODE_CASE(5)
DECODE_CASE(6)
DECODE_CASE(7)
DECODE_CASE(8)
DECODE_CASE(9)
static const CTestCase buffer_primitives_cases[] = {
    copy_words,
    decode_0,
    decode_1,
    decode_2,
    decode_3,
    decode_4,
    decode_5,
    decode_6,
    decode_7,
    decode_8,
    decode_9,
};
static const u32 buffer_primitives_cases_expected[] = { 0x1u, 0xABCDABCDu, 0x10031002u, 0x10051004u, 0x10071006u, 0x10091008u, 0x100B100Au, 0x100D100Cu, 0x100F100Eu, 0x0u, 0x0u };
#undef DECODE_CASE

static u16 cd_input_enabled(void)
{
#ifdef MMX4_PC
    return Psyz_SpuRead(0x1AA) & 1;
#else
    return *(volatile u16*)0x1F801DAA & 1;
#endif
}

static u32 test_cd_mixer(u32 row)
{
    static const u8 volumes[] = { 0, 1, 2, 3, 126, 127, 128, 255 };
    u32 operation = row / 16, mono = (row / 8) & 1;
    u32 volume = volumes[row % 8], final_volume = volume;
    CdlATV expected;
#ifdef MMX4_PC
    Psyz_SpuInit();
#endif
    memset(&D_80139644, 0xA5, sizeof(D_80139644));
    D_800F1D8C = volume;
    D_80171EA9 = operation == 1 ? !mono : mono;
    SsSetSerialAttr(0, 0, operation == 3);
    if (operation == 0) {
        D_800F1D8C = 99;
        func_80018FD0(volume);
    } else if (operation == 1) {
        func_80019058(mono);
    } else if (operation == 2) {
        func_80019228();
        final_volume = volume & ~1u;
    } else {
        func_800192F8();
        final_volume = volume & 1;
    }
    expected.val0 = mono ? final_volume : final_volume / 2;
    expected.val1 = mono ? 0 : final_volume / 2;
    expected.val2 = expected.val0;
    expected.val3 = expected.val1;
    assert(same_bytes(&D_80139644, &expected, sizeof(expected)));
    assert(D_80171EA9 == mono && D_800F1D8C == volume);
    assert(cd_input_enabled() == (operation == 2));
    return 1;
}

static u32 test_cd_fade_signed_boundary(u32 row)
{
    static const u32 volumes[] = { 0x80000000u, 0xFFFFFFFFu };
    CdlATV before;
    u32 mono = row & 1, volume = volumes[row / 2];
#ifdef MMX4_PC
    Psyz_SpuInit();
#endif
    D_80171EA9 = mono;
    func_80018FD0(volume);
    before = D_80139644;
    SsSetSerialAttr(0, 0, 1);
    func_800192F8();
    assert(same_bytes(&D_80139644, &before, sizeof(before)));
    assert(D_800F1D8C == volume && D_80171EA9 == mono);
    assert(cd_input_enabled() == 0);
    return 1;
}

#ifdef MMX4_PC
static const struct {
    u8 operation, drive_reply, stream, ready, hold, phase;
    u8 next_phase, next_stream, next_ready, fault;
    u8 inactive;
} cd_commands[] = {
    { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 2, 2, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 2, 2, 0, 1, 0 },
    { 1, 0, 0, 0, 0, 9, 2, 0, 0, 0 },
    { 1, 1, 0, 0, 0, 9, 9, 0, 0, 0 },
    { 2, 0, 2, 0, 1, 2, 2, 2, 0, 0 },
    { 2, 0, 2, 1, 0, 2, 2, 2, 1, 0 },
    { 2, 0, 2, 1, 1, 2, 3, 2, 1, 0 },
    { 2, 1, 2, 1, 1, 2, 3, 2, 1, 1 },
    { 3, 1, 2, 1, 0, 3, 3, 2, 1, 0 },
    { 3, 0, 0, 1, 0, 3, 3, 0, 1, 0 },
    { 3, 0, 2, 1, 1, 3, 3, 2, 1, 0 },
    { 3, 0, 2, 1, 0, 3, 2, 2, 0, 0 },
    { 4, 1, 2, 1, 0, 9, 9, 2, 1, 0 },
    { 4, 0, 0, 1, 0, 9, 0, 0, 1, 0 },
    { 4, 0, 2, 1, 0, 9, 0, 0, 1, 0 },
    { 5, 1, 0, 0, 0, 9, 9, 0, 0, 0 },
    { 5, 0, 0, 0, 0, 9, 1, 2, 0, 0 },
    { 5, 0, 0, 1, 0, 9, 1, 2, 1, 0 },
    { 6, 1, 0, 0, 0, 9, 9, 0, 0, 0 },
    { 6, 0, 0, 0, 0, 9, 5, 0, 0, 0 },
    { 7, 1, 0, 0, 0, 9, 9, 0, 0, 0 },
    { 7, 0, 0, 0, 0, 9, 6, 0, 0, 0 },
    { 8, 0, 0, 0, 0, 2, 0, 0, 0, 0 },
    { 8, 0, 2, 0, 0, 2, 0, 0, 0, 0 },
    { 8, 0, 2, 1, 0, 2, 0, 0, 1, 0 },
    { 3, 2, 2, 1, 0, 3, 2, 2, 0, 1 },
    { 7, 2, 0, 0, 0, 9, 6, 0, 0, 1 },
    { 8, 0, 2, 1, 0, 2, 2, 2, 1, 0, 1 },
};

static void stop_cd_command(void)
{
    func_80016F0C();
}

static u32 test_cd_commands(u32 row)
{
    static void (*const handlers[])(void) = {
        func_800168D8,
        func_80016B58,
        func_80016BDC,
        func_80016C5C,
        func_80016D0C,
        func_80016DAC,
        func_80016E34,
        func_80016E84,
        stop_cd_command,
    };
    u8 response[8] = { 0 };
    u32 operation = cd_commands[row].operation;
    u32 complete = cd_commands[row].drive_reply != 1;
    u32 stopped = operation == 8 && !cd_commands[row].inactive;
    u32 muted = stopped || (operation == 4 && complete);
    int success;
    success = setenv("SDL_AUDIODRIVER", "dummy", 1);
    assert(success == 0);
    Psyz_SpuInit();
    if (operation == 7)
        ResetGraph(0);
    Psyz_CdShellOpen(cd_commands[row].drive_reply != 0);
    success = CdControl(cd_commands[row].drive_reply == 2 ? CdlGetlocL : CdlNop, NULL, response);
    assert(success == complete);
    assert(CdSync(1, response) == (complete ? CdlComplete : CdlDiskError));
    memcpy(D_80139554, response, sizeof(response));
    D_80141BD4 = cd_commands[row].inactive ? 0 : 2;
    D_80139530 = cd_commands[row].phase;
    D_80139564 = cd_commands[row].stream;
    D_8013955C = cd_commands[row].ready;
    D_801441B8 = cd_commands[row].hold;
    D_801441B0 = cd_commands[row].ready;
    D_8013952C = 0;
    D_80139568 = 1;
    D_80173C84 = 7;
    D_80171EA9 = 0;
    func_80016420(85);
    SsSetSerialAttr(0, 0, 1);
    handlers[operation]();
    assert(D_80139530 == cd_commands[row].next_phase);
    assert(D_80139564 == cd_commands[row].next_stream);
    assert(D_8013955C == cd_commands[row].next_ready);
    assert(D_8013952C == cd_commands[row].fault);
    assert(D_80141BD4 == (cd_commands[row].inactive ? 0 : 2));
    assert(D_80139524 == (muted ? 0 : 85));
    assert(D_80139528 == (muted ? 0 : 85));
    assert(D_80139520.val0 == (muted ? 0 : 42));
    assert(D_80139520.val1 == D_80139520.val0);
    assert(D_80139520.val2 == D_80139520.val0);
    assert(D_80139520.val3 == D_80139520.val0);
    assert(cd_input_enabled() == !muted);
    assert(D_80173C84 == (stopped ? 0 : operation == 1 && complete ? 2
                                                                   : 7));
    assert(D_80139568 == (stopped ? 0 : 1));
    return 1;
}

extern u32 mmx4_pc_xa_stops, mmx4_pc_xa_stop_sample;

s32 func_80015A50(u8);
void func_80015178(void);
s16 SsVabTransCompleted(s16);
struct TestSoundBank {
    u32 packed, body_size;
    u8 commands[16];
    VabHdr header;
    ProgAtr programs[128];
    VagAtr tones[16];
    u16 lengths[256];
};
static struct TestSoundBank test_sound_bank, test_sound_bank_storage[6];
static u8 test_sound_body[0x2040];
static u8 test_sound_body_before[0x2040];
static union {
    u32 align;
    u8 bytes[24];
} test_sound_sequence;

static void prepare_sound_bank(u32 size, u32 id)
{
    u32 i, offset;
    static const u8 sequence[] = {
        'p',
        'Q',
        'E',
        'S',
        0,
        0,
        0,
        1,
        0,
        48,
        7,
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
    memset(&test_sound_bank, 0, sizeof(test_sound_bank));
    memset(&test_sound_sequence, 0, sizeof(test_sound_sequence));
    memcpy(test_sound_sequence.bytes, sequence, sizeof(sequence));
    offset = (u8*)&test_sound_bank.header - (u8*)&test_sound_bank;
    test_sound_bank.packed = (id << 24) | offset;
    test_sound_bank.body_size = size;
    test_sound_bank.header.form = 0x56414270;
    test_sound_bank.header.ver = 7;
    test_sound_bank.header.id = id;
    test_sound_bank.header.fsize = sizeof(test_sound_bank) - offset + size;
    test_sound_bank.header.ps = 1;
    test_sound_bank.header.ts = 1;
    test_sound_bank.header.vs = 1;
    test_sound_bank.header.mvol = 127;
    test_sound_bank.header.pan = 64;
    test_sound_bank.programs[0].tones = 1;
    test_sound_bank.programs[0].mvol = 127;
    test_sound_bank.programs[0].mpan = 64;
    test_sound_bank.tones[0].vol = 127;
    test_sound_bank.tones[0].pan = 64;
    test_sound_bank.tones[0].center = 60;
    test_sound_bank.tones[0].max = 127;
    test_sound_bank.tones[0].vag = 1;
    test_sound_bank.lengths[1] = size / 8;
    for (i = 0; i < sizeof(test_sound_body); i++)
        test_sound_body[i] = i % 16 < 2 ? 0 : (i * 37 + 11) & 0xFF;
    test_sound_body[size - 15] = 1;
    memcpy(test_sound_body_before, test_sound_body, sizeof(test_sound_body));
    cur_draw_info_drawenv = (u8*)&test_sound_bank;
    cur_draw_info_dispenv_screen_w = test_sound_body;
}

static void close_sound_resources(u32 shutdown, u32 poisoned)
{
    u32 i;
    if (shutdown)
        func_80015178();
    else
        func_80015284();
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    for (i = 0; i < 4; i++) {
        assert(D_8013E1C8[i] == -1);
        assert(D_8013924C[i] == (shutdown && poisoned ? 0x12 : 0xFF));
    }
    for (i = 0; i < 24; i++)
        assert(D_80139234[i] == (shutdown && poisoned ? 0x34 : -1));
    if (shutdown) {
        assert(Psyz_SpuRead(0x184) == 0 && Psyz_SpuRead(0x186) == 0);
        assert((Psyz_SpuRead(0x1AA) & 0x80) == 0);
    }
}

static u32 sound_bank_case(u32 row, u32 shutdown)
{
    static const u32 sizes[] = { 0x40, 0x800, 0x1000, 0x1040, 0x1800, 0x2000 };
    u32 size = row < COUNT(sizes) ? sizes[row] : row == 8 ? 0x2000
                                                          : 0x800;
    u32 banks = row == 11 ? 6 : 1, slot, i, copied, step, amount;
    s32 result, handle;
    u8* ram;
    int success = setenv("SDL_AUDIODRIVER", "dummy", 1);
    assert(success == 0);
    Psyz_SpuInit();
    func_80014DC4();
    if (row == 10) {
        close_sound_resources(shutdown, 0);
        return 1;
    }
    ram = Psyz_SpuGetRam();
    for (slot = 0; slot < banks; slot++) {
        u32 id = row == 7 ? 16 : slot;
        u32 address = 0x10000 + slot * 0x4000;
        prepare_sound_bank(size, id);
        if (row == 6)
            test_sound_bank.header.form = 0;
        test_sound_bank_storage[slot] = test_sound_bank;
        cur_draw_info_drawenv = (u8*)&test_sound_bank_storage[slot];
        D_80141F30[slot] = address;
        memset(ram + address - 16, 0xCC, size + 32);
        D_80137DFC = 0;
        copied = 0;
        for (step = 0; step < 2 && copied < size; step++) {
            amount = size - copied;
            if (amount > 0x1000)
                amount = 0x1000;
            result = func_80015A50(slot);
            if (row == 6 || row == 7) {
                assert(result == -1 && D_80137DFC == 0);
                assert(D_80137E00.offset == 0 && D_80137E00.remaining == size);
                assert(D_8013E198[slot] == -1);
                for (i = 0; i < size + 32; i++)
                    assert(ram[address - 16 + i] == 0xCC);
                return 1;
            }
            copied += amount;
            assert(result == (copied == size ? id : -2));
            assert(D_80137DFC == (copied != size));
            assert(D_80137DFD == id && D_8013E198[slot] == id);
            assert(D_80137E00.offset == copied && D_80137E00.remaining == size - copied);
            assert(D_80141EE8[slot] == (u8*)&test_sound_bank_storage[slot].header);
            assert(D_80141F50[slot] == test_sound_bank_storage[slot].commands);
            assert(same_bytes(test_sound_body, test_sound_body_before, sizeof(test_sound_body)));
            assert(same_bytes(ram + address, test_sound_body_before, copied));
            for (i = copied; i < size; i++)
                assert(ram[address + i] == 0xCC);
            for (i = 0; i < 16; i++) {
                assert(ram[address - 16 + i] == 0xCC);
                assert(ram[address + size + i] == 0xCC);
            }
            if (row == 8 && step == 0) {
                SsInit();
                result = func_80015A50(slot);
                assert(result == -1 && D_80137DFC == 1);
                assert(D_80137E00.offset == 0x1000 && D_80137E00.remaining == 0x1000);
                return 1;
            }
        }
        assert(copied == size);
    }
    if (row == 9 || row == 11) {
        for (i = 0; i < 3; i++) {
            handle = SsSepOpen((u_long*)test_sound_sequence.bytes, 0, 1);
            assert(handle == i);
            D_8013E1C8[i] = handle;
        }
    }
    memset(D_8013924C, 0x12, sizeof(D_8013924C));
    memset(D_80139234, 0x34, sizeof(D_80139234));
    close_sound_resources(shutdown, 1);
    for (slot = 0; slot < banks; slot++) {
        result = SsVabOpenHeadSticky((u8*)&test_sound_bank_storage[slot].header, slot, D_80141F30[slot]);
        assert(result == slot);
        if (slot == 0 && (row == 9 || row == 11)) {
            for (i = 0; i < 3; i++) {
                handle = SsSepOpen((u_long*)test_sound_sequence.bytes, 0, 1);
                assert(handle == i);
            }
            for (i = 0; i < 3; i++)
                SsSepClose(i);
        }
        result = SsVabTransBodyPartly(test_sound_body, size, slot);
        assert(result == slot);
        SsVabTransCompleted(1);
        assert(same_bytes(test_sound_body, test_sound_body_before, sizeof(test_sound_body)));
        assert(same_bytes(ram + D_80141F30[slot], test_sound_body_before, size));
        SsVabClose(slot);
    }
    close_sound_resources(shutdown, 1);
    return 1;
}

static u32 test_sound_bank_transfer(u32 row)
{
    return sound_bank_case(row, 0);
}

static u32 test_sound_shutdown(u32 row)
{
    return sound_bank_case(row == 0 ? 10 : 11, 1);
}

static u32 test_replay_xa_stop(u32 row)
{
    static const u8 replay[] = {
        'M',
        'M',
        'X',
        '4',
        'R',
        'P',
        'L',
        '2',
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };
    static const char sync[] = "{\"format\":\"MMX4SYNC1\",\"clock\":\"pad-read\",\"samples\":2,"
                               "\"sync_points\":[{\"sample\":2,\"kind\":\"xa-complete\"}]}";
    char directory[] = "/tmp/mmx4-xa-stop-XXXXXX";
    char movie_path[96], sync_path[96];
    const char* previous_path = mmx4_pc_replay_path;
    FILE* file;
    u8 pad[4];
    u32 i;
    int success;
    char* created = mkdtemp(directory);
    assert(created != NULL);
    success = snprintf(movie_path, sizeof(movie_path), "%s/movie.mmx4r", directory);
    assert(success > 0 && success < sizeof(movie_path));
    success = snprintf(sync_path, sizeof(sync_path), "%s/movie.mmx4r.sync.json", directory);
    assert(success > 0 && success < sizeof(sync_path));
    file = fopen(movie_path, "wb");
    assert(file != NULL);
    i = fwrite(replay, 1, sizeof(replay), file);
    assert(i == sizeof(replay));
    success = fclose(file);
    assert(success == 0);
    file = fopen(sync_path, "wb");
    assert(file != NULL);
    i = fwrite(sync, 1, sizeof(sync) - 1, file);
    assert(i == sizeof(sync) - 1);
    success = fclose(file);
    assert(success == 0);
    success = setenv("MMX4_REPLAY_SYNC", sync_path, 1);
    assert(success == 0);
    success = unsetenv("MMX4_MAX_FRAMES");
    assert(success == 0);
    Psyz_SpuInit();
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.state = 6;
    D_801406AC = 0;
    mmx4_pc_replay_path = movie_path;
    D_80141BD4 = 2;
    D_80139530 = row == 3 ? 3 : 2;
    D_80139564 = row == 1 ? 0 : 2;
    D_8013955C = 0;
    D_80139568 = row != 0;
    D_80173C84 = 2;
    D_80171EA9 = 0;
    mmx4_pc_xa_stops = 13;
    mmx4_pc_xa_stop_sample = 123;
    func_80016420(85);
    SsSetSerialAttr(0, 0, 1);

    mmx4_pc_input_update(pad);
    assert(mmx4_pc_replay_consumed() == 1 && !mmx4_pc_replay_xa_stop_due());
    assert(pad[0] == 0 && pad[1] == 0x41 && pad[2] == 0xFF && pad[3] == 0xFF);
    func_800168D8();
    assert(D_80139530 == (row == 3 ? 3 : 2));
    assert(D_8013955C == (row != 3));
    assert(D_80139524 == 85 && D_80173C84 == 2);
    assert(mmx4_pc_xa_stops == 13 && mmx4_pc_xa_stop_sample == 123);

    mmx4_pc_input_update(pad);
    assert(mmx4_pc_replay_consumed() == 2 && mmx4_pc_replay_complete());
    assert(mmx4_pc_replay_xa_stop_due());
    for (i = 0; i < 2; i++) {
        func_800168D8();
        assert(!mmx4_pc_replay_xa_stop_due());
        assert(D_80139530 == (row == 0 ? 5 : 0));
        assert(D_80139564 == (row == 0 ? 2 : 0));
        assert(D_80139568 == 0 && D_8013955C == (row != 3));
        assert(D_80173C84 == (row == 0 ? 2 : 0));
        assert(D_80139524 == (row == 0 ? 85 : 0));
        assert(D_80139528 == (row == 0 ? 85 : 0));
        assert(cd_input_enabled() == (row == 0));
        assert(mmx4_pc_xa_stops == (row == 0 ? 13 : 14));
        assert(mmx4_pc_xa_stop_sample == (row == 0 ? 123 : 2));
    }
    mmx4_pc_replay_path = previous_path;
    success = unsetenv("MMX4_REPLAY_SYNC");
    assert(success == 0);
    success = unlink(movie_path);
    assert(success == 0);
    success = unlink(sync_path);
    assert(success == 0);
    success = rmdir(directory);
    assert(success == 0);
    return 1;
}
#endif

extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static u32 table[300];

static u32 lookup(u32 row)
{
    static const struct {
        s8 bank;
        u16 entries, index;
    } cases[] = {
        { -1, 4, 2 },
        { 0, 4, 2 },
        { 0, 4, 4 },
        { 0, 260, 5 },
        { 0, 0, 0 },
        { 0, 4, 3 },
    };
    static const u32 expected[COUNT(cases)] = { 76799u, 763u, 76798u, 76798u, 76798u, 1019u };
    u8 *start = D_80141F50[1], *end = D_80141EE8[1];
    u32* command = D_80137E08;
    s8 bank = D_8013E198[1];
    u32 observed;
    s32 result;

    c_test_zero_words(table, COUNT(table));
    D_8013E198[1] = cases[row].bank;
    D_80141F50[1] = (u8*)table;
    D_80141EE8[1] = (u8*)(table + cases[row].entries);
    D_80137E08 = &table[299];
    result = func_8001540C(1, cases[row].index, NULL);
    observed = (u8)result | (u32)(D_80137E08 - table) << 8;
    D_80141F50[1] = start;
    D_80141EE8[1] = end;
    D_80137E08 = command;
    D_8013E198[1] = bank;
    return c_test_observe(0, row, &observed, &expected[row], 1);
}

const struct CTestGroup c_test_groups[] = {
    { "cd_mixer", 0, 0, 64, test_cd_mixer },
    { "cd_fade_signed_boundary", 0, 0, 4, test_cd_fade_signed_boundary },
    { "buffer_primitives", buffer_primitives_cases, buffer_primitives_cases_expected, COUNT(buffer_primitives_cases), 0 },
    { "mute_range_and_empty_command_returns", NULL, NULL, 6, lookup },
#ifdef MMX4_PC
    { "cd_commands", 0, 0, COUNT(cd_commands), test_cd_commands },
    { "replay_xa_stop", 0, 0, 4, test_replay_xa_stop },
    { "sound_bank_transfer", 0, 0, 12, test_sound_bank_transfer },
    { "sound_shutdown", 0, 0, 2, test_sound_shutdown },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 64 + 4 + COUNT(buffer_primitives_cases) + 6
#ifdef MMX4_PC
    + COUNT(cd_commands)
    + 4
    + 12
    + 2
#endif
    ;
