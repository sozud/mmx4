#include "common.h"

extern s32 mmx4_pc_canonical_load;
extern u8 D_80137DD8;
extern u8* D_80137DE0;
extern s32 D_80137DE4;

u32 mmx4_pc_cd_reads;
u32 mmx4_pc_cd_read_sample;
u32 mmx4_pc_cd_read_pending;
u32 mmx4_pc_xa_stops;
u32 mmx4_pc_xa_stop_sample;
static s32 completing_phase = -1;

static void mmx4_pc_cd_ready_callback(void)
{
    if (D_80137CD8 == 0)
        MyCdReadyCallback(CdlDataReady, NULL);
    else
        func_80013E68(CdlDataReady, NULL);
}

void mmx4_pc_advance_cd_load(void)
{
    if (D_801406AC == 1) {
        if (mmx4_pc_replay_frame() < 0 && completing_phase < 0) {
            mmx4_pc_cd_ready_callback();
        } else if (completing_phase >= 0 && mmx4_pc_replay_cd_load_due(completing_phase)) {
            while (D_801406AC == 1) {
                mmx4_pc_cd_ready_callback();
                if (D_801406AC == 1 || !completing_phase)
                    func_80014780();
            }
            if (D_801406AC == 2) {
                if (completing_phase && mmx4_pc_replay_cd_load_pending())
                    D_8013BD40 = 1;
                mmx4_pc_cd_read_pending = mmx4_pc_replay_cd_load_pending();
                mmx4_pc_replay_cd_load_consume();
                mmx4_pc_cd_reads++;
                mmx4_pc_cd_read_sample = mmx4_pc_replay_consumed();
            }
        }
    }
    if (!mmx4_pc_canonical_load)
        func_80014780();
}

void mmx4_pc_finish_cd_load(void)
{
    if ((D_801406AC == 1 || D_8013BD40 != 0)
        && mmx4_pc_replay_frame() >= 0)
        return;
    while (D_801406AC == 1 || D_8013BD40 != 0) {
        mmx4_pc_advance_cd_load();
        func_80014780();
    }
}

void mmx4_pc_complete_scheduled_cd_load(int input_phase)
{
    if (!mmx4_pc_replay_active() || (!input_phase && mmx4_pc_replay_frame() < 0))
        return;
    completing_phase = input_phase;
    while ((D_801406AC == 1 && mmx4_pc_replay_cd_load_due(input_phase))
        || (!input_phase && D_8013BD40 != 0)) {
        mmx4_pc_advance_cd_load();
        if (!input_phase)
            func_80014780();
    }
    completing_phase = -1;
}

void func_80013530(void)
{
    if (!mmx4_pc_canonical_load) {
        SetDispMask(0);
        return;
    }
    func_800129F0(0x10);
    if (main_bss_state.transition.active != 0) {
        do {
            func_80013404(0);
            func_800127C8(1);
        } while (main_bss_state.transition.active != 0);
    }
}

void func_80012E18(u8* start, u8* end)
{
    do {
        *(s32*)start = 0;
        start += 4;
    } while (start != end);
}

void func_80014A90(s32 arg0, s32 arg1)
{
    u8 mode = 0xA0;
    u32 state = D_801406AC;

    cd_fade_requested = 0;
    D_8013BD44 = 0;
    while (state != 2 || D_8013BD40 != 0) {
        mmx4_pc_advance_cd_load();
        if (mmx4_pc_canonical_load) {
            if (cd_fade_requested == 0 && !(arg1 & 0xff) && main_bss_state.transition.active == 0) {
                func_800129A4(8);
                cd_fade_requested++;
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
        mmx4_pc_advance_cd_load();
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

extern u8* pc_archive_slots[22];
