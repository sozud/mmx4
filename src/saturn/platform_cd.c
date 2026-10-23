#include "common.h"
#include "saturn/platform.h"
#include "saturn.h"

#define CD_STATUS_MASK 0x0F
#define CD_STATUS_OPEN 6
#define CD_STATUS_NO_DISC 7
#define CD_HIRQ_DISC_CHANGE 0x20
#define CD_EXIT_CODE 1

extern u8 saturn_cd_status[];
void saturn_system_exit(s32 code);

#define CD_HIRQ_SCDQ 0x400
#define CD_HIRQ_CMOK 0x01
#define CD_READY_POLLS 0x5F34
#define CD_INIT_RETRIES 15
#define CD_PERI_RETRIES 16
#define GFS_OPEN_MAX 2
#define GFS_DIR_NAME 1
#define GFS_DIR_MAX 255
#define GFS_ERR_CDRD -1
#define CDC_PTYPE_NOCHG 3
#define GFS_ERR_TMOUT -25
#define CD_LOAD_RETRIES 15

struct SaturnGfsDirTable {
    s32 type;
    s32 count;
    void* entries;
};

struct SaturnCdcStat {
    u8 status;
    u8 pad[3];
    u8 flags;
    u8 control_address;
    u8 track;
    u8 index;
    s32 fad;
};

extern struct SaturnGfsDirTable saturn_gfs_dir_table;
extern u8 saturn_gfs_dir_names[];
extern u8 saturn_gfs_work[];
extern u8 saturn_stm_work[];
extern s32 saturn_cd_seek_position[2];
extern volatile s32 saturn_cd_error;
extern void (*saturn_cd_error_hook)(void);
void saturn_archive_queue_reset(void);
s32 CDC_ClrHirqReq(s32 bits);
s32 CDC_CdInit(s32 iflag, s32 standby, s32 ecc, s32 retry);
s32 CDC_CdSeek(void* position);
s32 GFS_Init(s32 open_max, void* work, void* dir_table);
s32 STM_Init(s32 keys, s32 streams, void* work);
s32 GFS_NameToId(const char* name);
s32 GFS_Load(s32 id, s32 offset, void* buffer, s32 size);
extern volatile u8 saturn_cd_retries;
extern volatile s32 saturn_cd_file_id;

extern volatile s32 saturn_cd_error, saturn_cd_file_id;
extern volatile u32 saturn_cd_handle, saturn_archive_metadata_pointer;
extern volatile u8 saturn_cd_retries;
extern u16 saturn_color_ram[], saturn_color_ram_shadow[];
extern u8 saturn_archive_destination_9[];
extern s32 saturn_cd_name_to_id(const char*);
extern u32 saturn_cd_open(s32);
extern void saturn_cd_close(u32);
extern s32 saturn_cd_set_get_mode(u32, s32);
extern void saturn_cd_file_size(u32, s32*, s32*, s32*);
extern s32 saturn_cd_set_transfer_mode(u32, s32);
extern s32 saturn_cd_read_ahead(u32, s32);
extern s32 saturn_cd_read(u32, s32, u32, s32);
extern void saturn_cd_start_pending(u32);
extern u32 saturn_cd_wait(u32);
extern void saturn_cd_copy16(u32, u32, s32);
extern void saturn_cd_copy32(u32, u32, s32);
extern s32 saturn_cd_dma_result(void);

u8 saturn_archive_header[2048] __attribute__((aligned(16)));
u8 saturn_archive_sector[2048] __attribute__((aligned(16)));

extern volatile s32 saturn_cd_access_mode, saturn_cd_transferred_bytes;
extern volatile SaturnArchiveQueue saturn_archive_queue;
extern s32 saturn_cd_execute(u32);
extern void saturn_cd_get_status(u32, volatile s32*, volatile s32*);
extern s32 saturn_cd_stop(u32);

extern volatile u8 saturn_engine_bytes[];
extern volatile u16 saturn_stage_video_shadow[], saturn_stage_vram_marker;
extern u8 D_80110064[];
extern volatile u32 saturn_stage_background_header[];
extern volatile u32 saturn_stage_background_tiles, saturn_stage_background_attrs;
extern volatile u32 saturn_stage_background_layout, saturn_stage_background_workspace;
extern volatile u32 saturn_stage_work_pointer_0, saturn_stage_work_pointer_1;
extern volatile u32 saturn_stage_work_pointer_2, saturn_stage_work_pointer_3;
extern u8 saturn_stage_background_work[], saturn_stage_work_0[], saturn_stage_work_1[];
extern u8 saturn_stage_work_2[], saturn_stage_work_3[];
extern volatile u8 saturn_stage_mode, saturn_stage_flags;
extern volatile u8 saturn_stage_layout_width, saturn_stage_layout_height;
extern volatile u16 saturn_stage_layout_size;
extern void saturn_stage_prepare_video(u32, u32), saturn_stage_commit_video(void);
extern void saturn_stage_sound_command(u32, u32), saturn_stage_select_sound(void);
extern void saturn_stage_sound_finalize(void), saturn_stage_restore_video(void);

static s32 archive_fatal(void);

const char saturn_stage_zero_b0[] = "STB_0_1.ARC";

const char saturn_stage_zero_d0[] = "STD_0_1.ARC";

const char saturn_stage_zero_f0[] = "STF_0_1.ARC";

const u32 saturn_archive_destinations[] = {
    (u32)saturn_color_ram,
    0x060A7040,
    0x060BB040,
    0x0609D000,
    0x00200000,
    0x25E00000,
    0x25E40000,
    0x25E63000,
    0x0600E000,
    (u32)saturn_archive_destination_9,
    (u32)saturn_color_ram_shadow,
    0x25E50000,
    0x002E0000,
    0x002FE800,
    0x05C24000,
    0x25E60000,
    0x002D2000,
    0x25C08000,
    0x060A5040,
    0x002DB000,
    0x25A0B000,
    0x25A2907A,
    0x25A5A3E0,
    0x25A4A1C4,
    0x25A0B000,
    0x25A0B000,
    0x002D0000,
    0x05C78000,
    0x05C70000,
    0x002D3000,
    0x25C68000,
    0x002C2C00,
    0x25C63000,
    0x002C8000,
    0x25E70000,
    0x05C29800,
    0x002C6400,
    0x05C2F000,
    0x05C7C000,
    0x002C5C00,
    0x25E53000,
    0x002C5400,
};

const u8 saturn_stage_video_modes[] = {
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x00,
    0x01,
    0x01,
    0x01,
    0x00,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
};

static s32 archive_dump_r4(s32 input)
{
    register s32 result __asm__("r4") = input;
    __asm__ volatile(""
                     : "+r"(result)
                     :
                     : "memory");
    saturn_cd_error_hook();
    __asm__ volatile(""
                     : "=r"(result)
                     :
                     : "memory");
    return result;
}

static const SaturnCdControlIO cd_control_io = {
    saturn_cd_execute, saturn_cd_get_status, saturn_cd_stop,
    archive_dump_r4, saturn_thread_sleep, saturn_cd_close
};

static const SaturnCdControlState cd_control_state = {
    &saturn_cd_error, &saturn_cd_handle, &saturn_cd_retries,
    &saturn_cd_access_mode, &saturn_cd_transferred_bytes
};

static const SaturnArchiveIO archive_io = {
    saturn_cd_name_to_id, saturn_cd_open, saturn_cd_close, saturn_cd_set_get_mode,
    saturn_cd_file_size, saturn_cd_set_transfer_mode, saturn_cd_read_ahead,
    saturn_cd_read, saturn_cd_start_pending, saturn_thread_sleep, saturn_cd_wait,
    saturn_cd_copy16, saturn_cd_copy32, saturn_cd_dma_result, archive_fatal
};

static const SaturnArchiveState archive_state = {
    &saturn_cd_error, &saturn_cd_file_id, &saturn_cd_handle, &saturn_cd_retries,
    &saturn_archive_metadata_pointer, saturn_archive_header, saturn_archive_sector,
    saturn_archive_destinations, 0x060A5000
};

volatile u8 saturn_stage_archive_name[] = "ST0_0_0.ARC";

s32 saturn_cd_load_file(const char* name, void* buffer)
{
    s32 result;
    saturn_cd_retries = CD_LOAD_RETRIES;
    saturn_cd_file_id = GFS_NameToId(name);
    if (saturn_cd_file_id < 0) {
        saturn_cd_error = saturn_cd_file_id;
        saturn_cd_error_hook();
    }
    while (saturn_cd_retries) {
        result = GFS_Load(saturn_cd_file_id, 0, buffer, -1);
        saturn_cd_error = result;
        if (result >= 0)
            break;
        if (saturn_cd_error == GFS_ERR_TMOUT || saturn_cd_error == GFS_ERR_CDRD) {
            if (!saturn_cd_retries)
                saturn_cd_error_hook();
            saturn_cd_retries--;
        } else {
            saturn_cd_error_hook();
        }
    }
    return saturn_cd_error;
}

static s32 archive_fatal(void)
{
    register s32 result __asm__("r0");
    saturn_cd_error_hook();
    __asm__ volatile(""
                     : "=r"(result)
                     :
                     : "memory");
    return result;
}

void saturn_archive_metadata_state(const SaturnArchiveState* state, const SaturnArchiveIO* io)
{
    const u8* table = state->header + 0x400;
    if (table[4] | table[5] | table[6] | table[7]) {
        io->copy16(state->metadata_destination, (u32)table, 32);
        while (io->dma_result() == 2) { }
    }
    *state->metadata_pointer = state->metadata_destination;
}

static void archive_copy(const SaturnArchiveIO* io, u32 destination, u32 source,
    s32 bytes, u32 mode)
{
    if (mode)
        io->copy16(destination, source, bytes / 2);
    else
        io->copy32(destination, source, bytes / 4);
    while (io->dma_result() == 2) { }
}

s32 saturn_archive_load_state(const SaturnArchiveState* state, const SaturnArchiveIO* io,
    const char* path, u32 yielding)
{
    u8 attempts = 5;
    for (;;) {
        s32 sectors;
        *state->file_id = io->name_to_id(path);
        if (*state->file_id < 0) {
            *state->error = *state->file_id;
            io->fatal();
        }
        for (;;) {
            u8 old = *state->retries;
            *state->retries = (u8)(old - 1);
            if (!old) {
                *state->error = -25;
                io->fatal();
                break;
            }
            *state->handle = io->open(*state->file_id);
            if (*state->handle)
                break;
        }
        *state->retries = 15;
        io->set_get_mode(*state->handle, 0);
        io->file_size(*state->handle, NULL, &sectors, NULL);
        io->set_transfer_mode(*state->handle, 3);
        io->read_ahead(*state->handle, sectors);
        io->read(*state->handle, 1, (u32)state->header, 2048);
        if (yielding) {
            io->start_pending(*state->handle);
            io->sleep(1);
        }
        u32 failed = (u8)io->wait(yielding);
        s32 remaining = 0;
        volatile SaturnArchiveRecord* record = (volatile SaturnArchiveRecord*)state->header;
        while (!failed && record->destination_id != 255) {
            u32 destination = state->destinations[record->destination_id];
            io->set_transfer_mode(*state->handle, yielding ? 3 : 0);
            while (!failed && record->chunks) {
                u32 final = record->chunks == 1;
                s32 bytes = final ? record->last_bytes : record->first_bytes;
                if (bytes < 2048) {
                    if (!remaining) {
                        io->read(*state->handle, 1, (u32)state->sector, 2048);
                        remaining = 2048;
                        failed = (u8)io->wait(yielding);
                        if (failed)
                            break;
                    }
                    archive_copy(io, destination, (u32)state->sector + 2048 - remaining,
                        bytes, record->copy_mode);
                    remaining -= bytes;
                } else {
                    u32 buffered = !final && record->copy_mode;
                    io->read(*state->handle, 1, buffered ? (u32)state->sector : destination, 2048);
                    if (!final && !buffered) {
                        destination += (u32)(bytes > 2048 ? 2048 : bytes);
                        record->first_bytes = 2048;
                        record->chunks--;
                    }
                    failed = (u8)io->wait(yielding);
                    if (failed)
                        break;
                    if (buffered)
                        archive_copy(io, destination, (u32)state->sector, bytes, record->copy_mode);
                    if (!final && !buffered)
                        continue;
                }
                if (final)
                    record->chunks = 0;
                else {
                    destination += (u32)(bytes > 2048 ? 2048 : bytes);
                    record->first_bytes = 2048;
                    record->chunks--;
                }
            }
            record++;
        }
        if (!failed) {
            io->close(*state->handle);
            saturn_archive_metadata_state(state, io);
            return 1;
        }
        if (!attempts) {
            *state->error = -25;
            return io->fatal();
        }
        attempts--;
        io->close(*state->handle);
    }
}

s32 saturn_archive_load_yielding(const char* path)
{
    return saturn_archive_load_state(&archive_state, &archive_io, path, 1);
}

s32 saturn_archive_load_blocking(const char* path)
{
    return saturn_archive_load_state(&archive_state, &archive_io, path, 0);
}

void saturn_archive_metadata(void)
{
    saturn_archive_metadata_state(&archive_state, &archive_io);
}

s32 saturn_cd_check_result_state(const SaturnCdControlState* state, const SaturnCdControlIO* io,
    s32 result, volatile u8* retries, u32 allow_restart)
{
    *state->error = result;
    if (result >= 0)
        return 1;
    if (result == -25 || result == -1) {
        if (!*retries) {
            if (result == -25 && (u8)allow_restart)
                return 2;
            io->dump_r4(result);
        }
        *retries = (u8)(*retries - 1);
        return 0;
    }
    return io->dump_r4(result);
}

u32 saturn_cd_wait_state(const SaturnCdControlState* state, const SaturnCdControlIO* io,
    u32 yielding)
{
    *state->retries = 15;
    for (;;) {
        u32 result = (u8)saturn_cd_check_result_state(state, io,
            io->execute(*state->handle), state->retries, 1);
        if (result == 2)
            return 1;
        if (result != 0) {
            if (yielding)
                io->sleep(1);
            io->get_status(*state->handle, state->mode, state->bytes);
        }
        if (*state->bytes >= 2048 || *state->mode != 1)
            return 0;
    }
}

u32 saturn_cd_wait(u32 yielding)
{
    return saturn_cd_wait_state(&cd_control_state, &cd_control_io, yielding);
}

s32 saturn_cd_check_result(s32 result, volatile u8* retries, u32 allow_restart)
{
    return saturn_cd_check_result_state(&cd_control_state, &cd_control_io, result, retries, allow_restart);
}

void saturn_archive_queue_reset_state(volatile SaturnArchiveQueue* queue)
{
    queue->read_index = 0;
    queue->write_index = 0;
    queue->busy = 0;
    for (unsigned i = 0; i < 8; ++i)
        queue->paths[i] = 0;
}

void saturn_archive_queue_reset(void) { saturn_archive_queue_reset_state(&saturn_archive_queue); }

void saturn_archive_queue_cancel_state(volatile SaturnArchiveQueue* queue, const SaturnCdControlState* state,
    const SaturnCdControlIO* io, void (*kill)(u32))
{
    if (queue->busy) {
        *state->retries = 15;
        for (;;) {
            u8 old = *state->retries;
            *state->retries = (u8)(old - 1);
            if (!old) {
                io->dump_r4(*state->error);
                break;
            }
            *state->error = io->stop(*state->handle);
            if (*state->error >= 0)
                break;
        }
        io->close(*state->handle);
        kill(2);
        kill(4);
    }
    saturn_archive_queue_reset_state(queue);
}

void saturn_archive_queue_cancel(void)
{
    saturn_archive_queue_cancel_state(&saturn_archive_queue, &cd_control_state, &cd_control_io, saturn_thread_kill);
}

u32 saturn_archive_queue_push_state(volatile SaturnArchiveQueue* queue, u32 path)
{
    u8 old = queue->write_index;
    queue->write_index = (u8)(old + 1);
    queue->paths[(s8)old] = path;
    queue->write_index &= 15;
    if (queue->busy)
        return 0;
    queue->busy = 1;
    return 1;
}

void saturn_archive_queue_push(const char* path, u32 suppress_indicator)
{
    if (saturn_archive_queue_push_state(&saturn_archive_queue, (u32)(u32)path)) {
        saturn_thread_create(2, (u32)(u32)saturn_archive_queue_worker);
        if (!(u8)suppress_indicator)
            saturn_archive_start_indicator();
    }
}

u32 saturn_archive_queue_pop_state(volatile SaturnArchiveQueue* queue)
{
    u8 old = queue->read_index;
    queue->read_index = (u8)(old + 1);
    queue->paths[(s8)old] = 0;
    queue->read_index &= 15;
    if (queue->read_index != queue->write_index)
        return 0;
    queue->busy = 0;
    return 1;
}

void saturn_archive_queue_worker(void)
{
    for (;;) {
        saturn_archive_queue.busy = 1;
        saturn_archive_load_yielding((const char*)(u32)
                                         saturn_archive_queue.paths[(s8)saturn_archive_queue.read_index]);
        __asm__ volatile(".global _saturn_archive_worker_loaded\n_saturn_archive_worker_loaded:"
                         :
                         :
                         : "memory");
        if (saturn_archive_queue_pop_state(&saturn_archive_queue))
            saturn_thread_exit();
    }
}

void saturn_system_exit(s32 code)
{
    ((void (*)(s32))saturn_cd_error_hook)(code);
}

static u8 cd_stm_init(void)
{
    return STM_Init(1, 2, saturn_stm_work);
}

static s32 cd_wait_scdq(void)
{
    s32 polls = 0;
    do {
        if (CDC_GetHirqReq() & CD_HIRQ_SCDQ) {
            CDC_ClrHirqReq(~CD_HIRQ_SCDQ);
            return 0;
        }
    } while (++polls < CD_READY_POLLS);
    return 1;
}

static s32 cd_wait_status(s32 expected)
{
    struct SaturnCdcStat status;
    s32 result = 0;
    u8 tries;
    for (tries = CD_PERI_RETRIES; tries; tries--) {
        result = CDC_GetPeriStat(&status);
        if (result == 0 && (s8)(status.status & 0x0F) == expected)
            break;
        cd_wait_scdq();
        cd_wait_scdq();
    }
    return result;
}

static s32 cd_gfs_error(s32 error)
{
    if (error != GFS_ERR_CDRD) {
        saturn_cd_error = error;
        saturn_system_exit(0);
        return 0;
    }
    saturn_cd_seek_position[0] = CDC_PTYPE_NOCHG;
    if (CDC_CdSeek(saturn_cd_seek_position) == 0)
        cd_wait_status(1);
    return 0;
}

static void cd_gfs_init(void)
{
    s32 result = 0;
    u8 tries;
    saturn_gfs_dir_table.type = GFS_DIR_NAME;
    saturn_gfs_dir_table.entries = saturn_gfs_dir_names;
    saturn_gfs_dir_table.count = GFS_DIR_MAX;
    for (tries = CD_INIT_RETRIES; tries; tries--) {
        result = GFS_Init(GFS_OPEN_MAX, saturn_gfs_work, &saturn_gfs_dir_table);
        if (result >= 0)
            return;
        cd_gfs_error(result);
    }
    saturn_cd_error = result;
    saturn_system_exit(0);
}

void saturn_cd_initialize(void)
{
    s32 result = 0;
    u8 tries;
    cd_gfs_init();
    saturn_archive_queue_reset();
    for (tries = CD_INIT_RETRIES; tries; tries--) {
        if (cd_stm_init())
            break;
        cd_wait_scdq();
    }
    for (tries = CD_INIT_RETRIES; tries; tries--) {
        result = CDC_CdInit(8, 0, 5, 15);
        if (result >= 0)
            return;
        while (!(CDC_GetHirqReq() & CD_HIRQ_CMOK))
            cd_wait_scdq();
    }
    saturn_cd_error = result;
    saturn_system_exit(1);
}

void saturn_cd_vblank(void)
{
    u8 status;
    if (CDC_GetPeriStat(saturn_cd_status) == 0) {
        status = saturn_cd_status[0] & CD_STATUS_MASK;
        if (status == CD_STATUS_OPEN || status == CD_STATUS_NO_DISC) {
            saturn_system_exit(CD_EXIT_CODE);
        }
        return;
    }
    if (CDC_GetHirqReq() & CD_HIRQ_DISC_CHANGE) {
        saturn_system_exit(CD_EXIT_CODE);
    }
}

void saturn_stage_resource_setup(void)
{
    u32 saved_macl;
    __asm__ volatile("sts macl,%0"
                     : "=r"(saved_macl));
    saturn_stage_prepare_video(0, 1);
#define STAGE_VIDEO(offset) saturn_stage_video_shadow[(offset) / 2]
    STAGE_VIDEO(0x20) = 15;
    STAGE_VIDEO(0xEA) = (STAGE_VIDEO(0xEA) & 0xFFFC) | 1;
    STAGE_VIDEO(0xEA) = (STAGE_VIDEO(0xEA) & 0xFFF3) | 4;
    STAGE_VIDEO(0xEA) = (STAGE_VIDEO(0xEA) & 0xFFCF) | 0x10;
    STAGE_VIDEO(0xE0) = (STAGE_VIDEO(0xE0) & 0xFFF0) | 5;
    STAGE_VIDEO(0xF0) = (STAGE_VIDEO(0xF0) & 0xFFF0) | 7;
    STAGE_VIDEO(0xF0) = (STAGE_VIDEO(0xF0) & 0xF0FF) | 0x600;
    STAGE_VIDEO(0xF2) = (STAGE_VIDEO(0xF2) & 0xFFF0) | 5;
    STAGE_VIDEO(0xF2) = (STAGE_VIDEO(0xF2) & 0xF0FF) | 0x400;
    STAGE_VIDEO(0xF4) = (STAGE_VIDEO(0xF4) & 0xFFF0) | 3;
    STAGE_VIDEO(0xF4) = (STAGE_VIDEO(0xF4) & 0xF0FF) | 0x200;
    STAGE_VIDEO(0xF6) = (STAGE_VIDEO(0xF6) & 0xFFF0) | 1;
    STAGE_VIDEO(0xF6) = STAGE_VIDEO(0xF6) & 0xF0FF;
    STAGE_VIDEO(0xF8) = (STAGE_VIDEO(0xF8) & 0xFF00) | 6;
    STAGE_VIDEO(0xF8) = (STAGE_VIDEO(0xF8) & 0x00FF) | 0x400;
    STAGE_VIDEO(0xFA) = (STAGE_VIDEO(0xFA) & 0xFF00) | 3;
    STAGE_VIDEO(0xEC) = (STAGE_VIDEO(0xEC) & 0xFEFF) | ((saturn_stage_video_modes[(s8)saturn_engine_bytes[12] * 2 + (s8)saturn_engine_bytes[13]] & 1) << 8);
    STAGE_VIDEO(0xEC) = STAGE_VIDEO(0xEC) & 0xFDFF;
    STAGE_VIDEO(0xEE) = (STAGE_VIDEO(0xEE) & 0xFFFC) | 1;
    STAGE_VIDEO(0xEC) = (STAGE_VIDEO(0xEC) & 0xFFFE) | 1;
    STAGE_VIDEO(0x108) = (STAGE_VIDEO(0x108) & 0xFF00) | 15;
    STAGE_VIDEO(0xEE) = (STAGE_VIDEO(0xEE) & 0xFFF3) | 4;
    STAGE_VIDEO(0xEC) = (STAGE_VIDEO(0xEC) & 0xFFFD) | 2;
    STAGE_VIDEO(0x108) = (STAGE_VIDEO(0x108) & 0x00FF) | 0xF00;
    STAGE_VIDEO(0xEE) = (STAGE_VIDEO(0xEE) & 0xFFCF) | 0x10;
    STAGE_VIDEO(0xEC) = (STAGE_VIDEO(0xEC) & 0xFFFB) | 4;
    STAGE_VIDEO(0x10A) = (STAGE_VIDEO(0x10A) & 0xFF00) | 15;
#undef STAGE_VIDEO
    saturn_stage_commit_video();
    saturn_thread_sleep(1);
    s32 stage = (s8)saturn_engine_bytes[12];
    if (stage != 13 && stage != 14) {
        saturn_stage_sound_command(128, 1);
        saturn_stage_sound_command(3, 0);
    }
    saturn_thread_sleep(1);
    saturn_stage_vram_marker = 0;
    stage = (s8)saturn_engine_bytes[12];
    saturn_stage_archive_name[2] = stage + (stage >= 10 ? 7 : 0) + '0';
    saturn_stage_archive_name[4] = saturn_engine_bytes[13] + '0';
    saturn_stage_archive_name[6] = '0';
    saturn_stage_select_sound();
    u32 pair = ((u32)saturn_engine_bytes[12] << 8) | saturn_engine_bytes[13];
    const char* archive = (const char*)saturn_stage_archive_name;
    s8 character = (s8)saturn_engine_bytes[0x43];
    if (pair == 0x0B00) {
        if (character)
            archive = saturn_stage_zero_b0;
        saturn_archive_load_blocking(archive);
    } else if (pair == 0x0D00) {
        if (character)
            archive = saturn_stage_zero_d0;
        saturn_archive_queue_push(archive, 0);
    } else {
        if (pair == 0x0D01)
            saturn_stage_archive_name[6] = saturn_engine_bytes[0x40] + '0';
        if (pair == 0x0F00 && character)
            archive = saturn_stage_zero_f0;
        saturn_archive_load_blocking(archive);
    }
    u32 header = (u32)(u32)saturn_stage_background_header;
    saturn_stage_background_tiles = header + saturn_stage_background_header[0];
    saturn_stage_background_attrs = header + saturn_stage_background_header[1];
    saturn_stage_background_layout = header + saturn_stage_background_header[2];
    stage = (s8)saturn_engine_bytes[12];
    if (stage != 13 && stage != 14) {
        saturn_stage_sound_finalize();
        saturn_stage_restore_video();
    } else {
        if ((s8)saturn_engine_bytes[12] == 13 && saturn_engine_bytes[13]) {
            saturn_stage_sound_finalize();
            saturn_stage_restore_video();
        }
        if ((s8)saturn_engine_bytes[12] == 14)
            saturn_stage_sound_finalize();
    }
    s32 index = (s8)saturn_engine_bytes[12] * 4 + (s8)saturn_engine_bytes[13] * 2;
    saturn_stage_layout_width = D_80110064[index];
    saturn_stage_layout_height = D_80110064[index + 1];
    saturn_stage_layout_size = (u16)saturn_stage_layout_width * saturn_stage_layout_height;
    saturn_stage_background_workspace = (u32)(u32)saturn_stage_background_work;
    if (!saturn_stage_mode)
        saturn_stage_flags |= 1;
    saturn_stage_work_pointer_0 = (u32)(u32)saturn_stage_work_0;
    saturn_stage_work_pointer_1 = (u32)(u32)saturn_stage_work_1;
    saturn_stage_work_pointer_2 = (u32)(u32)saturn_stage_work_2;
    saturn_stage_work_pointer_3 = (u32)(u32)saturn_stage_work_3;
    __asm__ volatile("lds %0,macl"
                     :
                     : "r"(saved_macl)
                     : "macl");
}
