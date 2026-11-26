#include "test_runtime.h"
#include "main/55C4.h"
#include "main/xa_sequence_data.h"
#include "main/3D88.h"
#ifdef MMX4_PC
#include <psyz/spu.h>
#include <stdlib.h>
void func_8001653C(void);
void func_8001663C(u8 selection, u8 volume);
void func_800168D8(void);
s32 func_800169D8(void);
void func_80016B58(void);
void func_80016D0C(void);
void func_80016FB4(s32 arg0);
extern s32 D_80139534, D_80139538, D_80139540, D_80139544, D_80139510, D_800F1AAC;
extern u32 D_8013953C;
extern s16 D_80139560;
extern u8 D_80139528;
extern u16 D_800F188C[];
extern u_char CD_com;
extern int CD_status;

static void music_begin(void)
{
    int success = setenv("SDL_AUDIODRIVER", "dummy", 1);
    assert(success == 0);
    Psyz_SpuInit();
    Psyz_CdShellOpen(0);
    D_80141BD4 = 0;
    D_80139530 = 0;
    D_80139564 = 0;
    D_80139568 = 0;
    D_8013955C = 0;
    D_8013952C = 0;
    D_801441B8 = 0;
    D_80173C84 = 0;
    D_80171EA9 = 1;
}

struct TrackRow {
    u8 selection, volume;
    s16 file;
    u8 channel, one_shot;
    u16 entry;
};
static const struct TrackRow track_rows[] = {
    { 0, 0x40, XA_ARCHIVE_BGM1, 0, 1, 0 },
    { 49, 0x50, XA_ARCHIVE_VOICE2, 1, 1, 92 },
    { 57, 0x60, XA_ARCHIVE_VOICE3, 1, 1, 108 },
    { 30, 0x70, XA_ARCHIVE_BGM4, 5, 0, 59 },
};
static u32 check_track(u8 volume, s16 file, u8 channel, u8 one_shot, u16 entry)
{
    s32 size, start = func_80013614(file, &size) + channel;
    CdlLOC position;
    CdIntToPos(start + (D_800F188C[entry] & 0x7FFF) * 8, &position);
    assert(D_80139560 == file && D_80139568 == one_shot);
    assert(((u8*)D_80175EE8)[0] == 1 && ((u8*)D_80175EE8)[1] == channel);
    assert(D_80139540 == start + (D_800F188C[entry] & 0x7FFF) * 8 && D_80139544 == start + (D_800F188C[entry + 1] & 0x7FFF) * 8);
    assert(memcmp(&D_80139514, &position, 3) == 0);
    assert(D_80139524 == volume && D_80141BD4 == 2 && D_80173C84 == 1 && D_80139530 == 7);
    return D_80139540;
}
static u32 test_track(u32 row)
{
    const struct TrackRow* in = &track_rows[row];
    music_begin();
    func_8001663C(in->selection, in->volume);
    return check_track(in->volume, in->file, in->channel, in->one_shot, in->entry);
}

static u32 test_late_stage_music(u32 row)
{
    s32 start, end;
    music_begin();
    func_8001663C(alternate_stage_music[13 * 2], alternate_stage_music[13 * 2 + 1]);
    start = D_80139540;
    end = D_80139544;
    music_begin();
    engine_obj.stage = 13;
    func_8001653C();
    assert(D_80139524 == alternate_stage_music[13 * 2 + 1] && D_80139540 == start && D_80139544 == end);
    return start;
}

struct PollRow {
    u8 driver, command, complete, one_shot;
    s8 from_end;
};
static const struct PollRow poll_rows[] = {
    { 2, CdlReadS, 1, 0, 0 },
    { 2, CdlGetlocP, 1, 0, -20 },
    { 2, CdlGetlocP, 1, 0, -4 },
    { 2, CdlGetlocP, 1, 1, -4 },
    { 2, CdlGetlocP, 0, 0, -4 },
    { 0, CdlGetlocP, 1, 0, -4 },
};
static u32 test_poll(u32 row)
{
    const struct PollRow* in = &poll_rows[row];
    u8 reply[8];
    u32 position = 0x1000 + in->from_end, stopped = in->driver == 2 && in->command == CdlGetlocP && in->complete && in->from_end > -8 && in->one_shot;
    music_begin();
    func_80016420(0x55);
    if (!in->complete)
        Psyz_CdShellOpen(1);
    CdControl(CdlNop, NULL, reply);
    Psyz_CdShellOpen(0);
    memset(D_80139554, 0, 8);
    CdIntToPos(position, (CdlLOC*)(D_80139554 + 5));
    CD_com = in->command;
    D_80141BD4 = in->driver;
    D_80139530 = 2;
    D_80139544 = 0x1000;
    D_80139568 = in->one_shot;
    D_80139564 = 2;
    D_8013953C = 0x12345678;
    func_800168D8();
    CD_com = 0;
    assert(D_8013955C == (in->driver == 2));
    assert(D_8013953C == (in->driver == 2 && in->command == CdlGetlocP && in->complete ? position : 0x12345678));
    assert(D_80139530 == (stopped ? 0 : in->driver == 2 && in->complete && in->from_end > -8 && in->command == CdlGetlocP ? 5
                                                                                                                          : 2));
    assert(D_80139524 == (stopped ? 0 : 0x55) && D_80139564 == (stopped ? 0 : 2));
    return D_80139530;
}

struct FrameRow {
    u8 driver, failed, fade;
    s32 level;
    s32 toggle;
    s8 shown_mode, mode;
};
static const struct FrameRow frame_rows[] = {
    { 0, 0, 0, 0, 1, 1, 1 },
    { 2, 1, 0, 0, 1, 1, 1 },
    { 2, 0, 1, 2, 1, 1, 1 },
    { 2, 0, 1, 9, 1, 1, 1 },
    { 2, 0, 1, -1, 0, 1, 1 },
    { 2, 0, 0, 0, 1, 0, 1 },
    { 2, 0, 0, 0, 1, 1, 0 },
};
static u32 test_frame(u32 row)
{
    const struct FrameRow* in = &frame_rows[row];
    s32 result;
    music_begin();
    D_80171EA9 = in->shown_mode;
    func_80016420(0x60);
    D_80141BD4 = in->driver;
    D_8013952C = in->failed;
    D_80139530 = 2;
    D_80141BD0 = in->fade;
    D_80139510 = in->level;
    D_800F1AAC = in->toggle;
    D_80139534 = 0x10;
    D_8013956C = in->shown_mode;
    D_80171EA9 = in->mode;
    result = func_800169D8();
    assert(result == (in->driver == 2 && !in->failed ? 0 : -1));
    if (row < 2) {
        assert(D_80141BD0 == in->fade && D_80139528 == 0x60 && D_80139530 == 2);
    } else if (row == 2) {
        assert(D_80139510 == 0 && D_800F1AAC == 1 && D_80141BD0 == 0 && D_80139530 == 0 && D_80139528 == 0 && D_80139524 == 0);
    } else if (row == 3) {
        assert(D_800F1AAC == 0 && D_80139510 == 0x60 - 0x10 && D_80139528 == 0x50 && D_80141BD0 == 1);
    } else if (row == 4) {
        assert(D_800F1AAC == 1 && D_80139510 == -1 && D_80139528 == 0xFF && D_80141BD0 == 1);
    } else {
        u8 half = row == 5 ? 0x60 : 0x30;
        assert(D_8013956C == in->mode && D_80171EA9 == in->mode && D_80139528 == 0x60);
        assert(D_80139520.val0 == half && D_80139520.val2 == half);
        assert(D_80139520.val1 == (row == 5 ? 0 : half) && D_80139520.val3 == D_80139520.val1);
    }
    return result;
}

static const u8 fade_rows[][3] = { { 12, 1, 0 }, { 12, 0, 0 }, { 3, 0, 2 } };
static u32 test_fade_request(u32 row)
{
    music_begin();
    engine_obj.stage = fade_rows[row][0];
    engine_obj.substage = fade_rows[row][1];
    D_80173C84 = fade_rows[row][2];
    D_80141BD0 = 0;
    D_80139534 = 0x11;
    func_80016FB4(0x22);
    assert(D_80139534 == (row == 1 ? 0x11 : 0x22) && D_80141BD0 == (row != 1));
    return D_80139534;
}

static u32 test_start_waits_for_seek(u32 row)
{
    u8 reply[8];
    music_begin();
    CD_status |= CdlStatSeek;
    CdControl(CdlNop, NULL, reply);
    CD_status &= ~CdlStatSeek;
    D_80141BD4 = 2;
    D_80173C84 = 7;
    D_80139530 = 1;
    func_80016B58();
    assert(D_80139530 == 1 && D_80173C84 == 7);
    return D_80139530;
}
#define MUSIC_CASES (COUNT(track_rows) + 1 + COUNT(poll_rows) + COUNT(frame_rows) + COUNT(fade_rows) + 1)
#else
#define MUSIC_CASES 0
#endif

const struct CTestGroup c_test_groups[] = {
#ifdef MMX4_PC
    { "xa_track_selection", 0, 0, COUNT(track_rows), test_track },
    { "late_stage_music", 0, 0, 1, test_late_stage_music },
    { "xa_position_poll", 0, 0, COUNT(poll_rows), test_poll },
    { "xa_frame_update", 0, 0, COUNT(frame_rows), test_frame },
    { "music_fade_request", 0, 0, COUNT(fade_rows), test_fade_request },
    { "xa_start_waits_for_seek", 0, 0, 1, test_start_waits_for_seek },
#endif
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = MUSIC_CASES;
