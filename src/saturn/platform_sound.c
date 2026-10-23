#include "common.h"
#include "saturn/platform.h"

#define SOUND_DRIVER_PENDING 0x60
#define SOUND_DRIVER_REQUEST 0x80
#define SOUND_COMMAND_SEQ_START 0x0100
#define SOUND_COMMAND_SEQ_STOP 0x0200
#define SOUND_COMMAND_SEQ_PAUSE 0x0300
#define SOUND_COMMAND_SEQ_CONTINUE 0x0400
#define SOUND_COMMAND_SEQ_VOLUME 0x0500
#define SOUND_COMMAND_SEQ_TEMPO 0x0700
#define SOUND_COMMAND_CHANGE_MAP 0x0800
#define SOUND_COMMAND_CUT_ALL 0x0C00
#define SOUND_COMMAND_SEQ_CONTROL 0x0E00
#define SOUND_COMMAND_SEQUENCE_MODE 0x1000
#define SOUND_COMMAND_CDDA_LEVEL 0x8000
#define SOUND_COMMAND_CDDA_PAN 0x8100
#define SOUND_COMMAND_TOTAL_VOLUME 0x8200
#define SOUND_COMMAND_EFFECT 0x8300
#define SOUND_COMMAND_PCM_START 0x8500
#define SOUND_COMMAND_PCM_STOP 0x8600
#define SOUND_COMMAND_MIX 0x8700
#define SOUND_COMMAND_MIX_PARAM 0x8800
#define SOUND_COMMAND_PCM_CHANGE 0x8A00
#define SOUND_STATUS_PLAYING 0x0100
#define SOUND_STATUS_PAUSED 0x0300
#define SOUND_STATUS_MASK 0xFF00
#define SOUND_FADE_UP 1
#define SOUND_FADE_DOWN 2
#define SOUND_LEVEL_MAX 127
#define SOUND_LEVEL_NEGATIVE 0x80
#define SOUND_FADE_SEQUENCE 7
#define SOUND_PAN_CENTER 15
#define SOUND_PAN_MAX 31
#define SOUND_SCREEN_WIDTH 320
#define SOUND_CAMERA_STRIDE 84
#define SOUND_KIND_EFFECT_LAST 1
#define SOUND_FIRST_EFFECT 8
#define SOUND_NO_SEQUENCE 0xFF
#define SOUND_SPECIAL_STAGE 4
#define SOUND_LAST_STAGE 8
#define SOUND_GROUP_LIMIT 4
#define SOUND_REQUEST_BURST 6
#define SOUND_KEY_TABLE ((volatile u32*)0x25A00500)
#define SOUND_KEY_END 0x80000000
#define SOUND_KEY_MASKED 0x80000000
#define SOUND_MAP_NONE 0xFF
#define SOUND_MAP_UNSET 0x80
#define SOUND_FINAL_VOLUME 15
#define SOUND_MIX_CHANNELS 16
#define STREAM_SEQUENCE 7
#define STREAM_PCM_LEFT 0x80E0
#define STREAM_PCM_RIGHT 0x90E0
#define STREAM_PCM_MONO_ADDRESS 0x7800
#define STREAM_PCM_STEREO_ADDRESS 0x7A00
#define STREAM_PCM_MONO_SIZE 0x2000
#define STREAM_PCM_STEREO_SIZE 0x3000
#define STREAM_STATUS_BUSY 1
#define MUSIC_THREAD_SLOT 3
#define ENGINE_STAGE 0x0C
#define ENGINE_FORTRESS_FLAG 0x43
#define SOUND_DRIVER_OUTPUT 3
#define SOUND_RAW_EFFECT 1
#define SOUND_RAW_MAP 5
#define SOUND_RAW_MAP_SLOT 4
#define SOUND_RAW_PAN 14
#define SOUND_RAW_EFFECT_SLOT 3
#define SOUND_RAW_PAN_SLOT 5
#define SOUND_PAN_FIXED 0x80
#define SOUND_MIX_LEVEL 7
#define SOUND_OUTPUT_UNSET 0x56
#define SOUND_STAGE_MAP_INITIAL 0x55
#define STREAM_STATE_BYTES 100
#define PERIPHERAL_FLAGS 4
#define PERIPHERAL_MONO 0x200
#define MUSIC_BOSS 19
#define MUSIC_FORTRESS_BOSS 24
#define MUSIC_FORTRESS_A 23
#define MUSIC_FORTRESS_B 22
#define MUSIC_FINAL_A 25
#define MUSIC_FINAL_B 26
#define ENGINE_SUBSTAGE 0x0D
#define OBJECT_X 8
#define OBJECT_CAMERA 0x14
#define CAMERA_X 8

extern u8 saturn_sprite_cameras[];
extern s8 saturn_engine_bytes[];
extern u8 D_80171EA8;

#define SOUND_COMMAND_LEVEL_ANALYSIS 0x8900
#define SOUND_ANALYSIS_RESULT (*(volatile u16*)0x25A00418)
#define SOUND_ANALYSIS_DELAY 31
#define SMPC_IREG0 (*(volatile u8*)0x20100001)
#define SMPC_IREG1 (*(volatile u8*)0x20100003)
#define SMPC_IREG2 (*(volatile u8*)0x20100005)
#define SMPC_IREG3 (*(volatile u8*)0x20100007)
#define SMPC_COMREG (*(volatile u8*)0x2010001F)
#define SMPC_SF (*(volatile u8*)0x20100063)
#define SMPC_SET_MEMORY 0x17
#define SMPC_MEMORY_MONO 0x200
#define SMPC_MEMORY_WORD 1

#define SOUND_WAIT_LONG 0x4E20
#define SOUND_WAIT_SHORT 0x4E2
#define SOUND_WAIT_RETRY_LIMIT 32

extern u8 saturn_sound_wait_retries;

#define SOUND_QUEUE_BACKLOG 6
#define SOUND_DRIVER_STATUS (*(volatile u32*)0x25A00420)
#define SOUND_DRIVER_STATUS_MASK 0xFFFFFF
#define SOUND_DRIVER_PEAK (*(volatile u8*)0x25A08827)
#define SOUND_DRIVER_LEVEL (*(volatile u16*)0x25A00416)

extern u8 saturn_movie_active;
extern s16 saturn_music_fading;
extern u8 saturn_sound_peak;
extern u16 saturn_sound_level;

#define SOUND_RAM ((u8*)0x25A00000)
#define SOUND_RAM_CLEAR_END ((u32*)0x25A0B000)
#define SOUND_DRIVER_HEADER(offset) (*(volatile u32*)(SOUND_RAM + 0x400 + (offset)))
#define SOUND_DRIVER_HALF(offset) (*(volatile u16*)(SOUND_RAM + 0x400 + (offset)))
#define SCSP_COMMON (*(volatile u16*)0x25B00400)
#define SCSP_COMMON_4MBIT 0x200
#define SMPC_SF (*(volatile u8*)0x20100063)
#define SMPC_COMREG (*(volatile u8*)0x2010001F)
#define SMPC_SNDON 6
#define SMPC_SNDOFF 7
#define SOUND_DRIVER_BUFFER 0x060F0000
#define SOUND_MAP_BUFFER 0x060F7000
#define SOUND_DRIVER_BYTES 0x67F2
#define SOUND_MAP_BYTES 0x0374
#define SOUND_SEQUENCE_OFFSET 0x80
#define SOUND_TABLE_90 0x90
#define SOUND_TABLE_94 0x94
#define SOUND_PCM_OFFSET 0xA0
#define SOUND_TABLE_B0 0xB0
#define SOUND_DRIVER_BOOT 0x61

extern u8* saturn_sound_driver_buffer;
extern u16 saturn_sound_driver_bytes;
extern u8* saturn_sound_map_buffer;
extern u16 saturn_sound_map_bytes;
extern volatile u8* saturn_sound_driver_header;
extern volatile u8* saturn_sound_table_d8;
extern volatile u8* saturn_sound_table_e0;
extern volatile u8* saturn_sound_table_e4;
extern volatile u8* saturn_sound_table_ec;
s32 saturn_cd_load_file(const char* name, void* buffer);
void DMA_ScuMemCopy(void* destination, void* source, u32 count);
u32 DMA_ScuResult(void);

#define STREAM_TRACK_LIMIT 82
#define STREAM_NO_LOOP 0x7FFFFFFF
#define STREAM_TRANSFER_SECTORS 2
#define STREAM_GATE_ON 0x300
#define STREAM_GATE_OFF 0x301
#define STREAM_SERVER_END 0x104
#define STREAM_LOW_BUFFERS 0xA0
#define STREAM_COPY_BYTES 0x1000
#define STREAM_ERASE_ALL 0xFFFF
#define STREAM_MONO_BUFFER ((volatile u32*)0x25A7A000)
#define STREAM_STEREO_BUFFER ((volatile u32*)0x25A78000)
#define STREAM_MONO_BUFFER_ADDRESS 0x25A7A000
#define STREAM_STEREO_BUFFER_ADDRESS 0x25A78000
#define STREAM_MONO_LONGS 0x1800
#define STREAM_STEREO_LONGS 0x2000
#define STREAM_MAX_HANDLES 4
#define TRANSFER_REQUESTED 2
#define MODE_ONE_SHOT 0
#define MODE_LOOP 1
#define MODE_STEREO 2
#define PHASE_IDLE 0
#define PHASE_START 1
#define PHASE_SWITCH 3
#define PHASE_PLAYING 5
#define PHASE_ENDING 6
#define SOUND_NO_TRACK 0xFF
#define TRACK_CHARACTER 0
#define TRACK_VARIANT_A 2
#define TRACK_VARIANT_B 14
#define TRACK_ONCE_A 20
#define TRACK_ONCE_B 21
#define TRACK_ONCE_FIRST 33
#define TRACK_STEREO_ONCE 81
#define TRACK_CHARACTER_ZERO 67
#define TRACK_VARIANT_FLAG 13
#define TRACK_ZERO_VOLUME 16
#define TRACK_VARIANT_A_VOLUME 17
#define TRACK_VARIANT_B_VOLUME 15

struct SaturnStream {
    void* group;
    s32 file;
    s32 file_right;
    u8 padding0[4];
    void* stream;
    void* stream_right;
    u8 padding1[8];
    u8 mode;
    u8 transfer_state;
    u8 server_state;
    u8 exec_pending;
    u8 copy_pending;
    u8 padding2;
    u16 track;
    u16 phase;
    u8 padding3[2];
    s32 handle_count;
    u32 buffer_count;
    s32 server_result;
    u32* copy_source;
    u32* copy_destination;
    u32 copy_bytes;
    s32 copy_stride;
    void* handles[STREAM_MAX_HANDLES];
    u8 transfer[5];
    u8 padding4;
    u16 stereo_files;
    u16 stereo_output;
};

struct SaturnStreamKey {
    s16 value[6];
};

extern struct SaturnStream saturn_stream;
extern u8 saturn_stream_error_object[];
extern void (*saturn_cd_error_hook)(void);

void* STM_OpenGrp(void);
void STM_CloseGrp(void* group);
void* STM_OpenFid(void* group, s32 file, struct SaturnStreamKey* key, s32 mode);
void STM_SetTrPara(void* stream, s32 sectors);
void STM_SetTrFunc(void* stream, s32 (*function)(void*, void*, s32), void* object);
void STM_SetLoop(void* group, void* stream, s32 count);
void STM_EraseCdbuf(void* stream, s32 offset, s32 sectors);
void STM_SetErrFunc(void (*function)(void*, s32), void* object);
void STM_SetTrGate(void* stream, s32 gate);
s32 STM_IsComplete(void* stream);

void STM_ExecTrans(void* stream);
s32 STM_ExecServer(void);
void STM_SetExecGrp(void* group);
s32 STM_GetStmNum(void* group);
void* STM_GetStmHndl(void* group, s32 index);
u32* STM_StartTrans(void* stream, s32* stride);
void STM_GetInfo(void* stream, s32* file, s32* frame, s32* sectors, void* key);
s32 STM_GetNumCdbuf(void* stream);
void STM_Recover(void);
s32 GFS_NameToId(char* name);

s8 saturn_sound_pan_table[] = {
    48,
    48,
    48,
    48,
    56,
    56,
    56,
    56,
    60,
    60,
    60,
    60,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    64,
    72,
    72,
    72,
    72,
    76,
    76,
    76,
    76,
    80,
    80,
    80,
    80,
};

s8 saturn_sound_mix_table[] = {
    19,
    19,
    19,
    19,
    18,
    18,
    18,
    18,
    17,
    17,
    17,
    17,
    16,
    16,
    16,
};

u8 saturn_sound_mix_default = 0x10;

s16 saturn_sound_tempos[] = {
    -32768,
    -28672,
    -24576,
    -20480,
    -16384,
    -12288,
    -8192,
    -4096,
    0,
    4096,
    8192,
    12288,
    16384,
    20480,
    24576,
    28672,
    32767,
};

u8 saturn_hex_digits[] = {
    0x30,
    0x31,
    0x32,
    0x33,
    0x34,
    0x35,
    0x36,
    0x37,
    0x38,
    0x39,
    0x41,
    0x42,
    0x43,
    0x44,
    0x45,
    0x46,
};

u8 saturn_music_track_volumes[] = {
    0x0C,
    0x05,
    0x05,
    0x09,
    0x09,
    0x0A,
    0x06,
    0x05,
    0x05,
    0x05,
    0x09,
    0x05,
    0x05,
    0x0B,
    0x00,
    0x0E,
    0x0C,
    0x06,
    0x0E,
    0x0C,
    0x0C,
    0x0C,
    0x06,
    0x08,
    0x0A,
    0x08,
    0x09,
    0x0D,
    0x08,
    0x05,
    0x05,
    0x05,
    0x05,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xFF,
    0xFF,
    0xFF,
};

u32 saturn_stream_stereo_halves[] = {
    0x0,
    0x4000,
    0x1000,
    0x5000,
};

u32 saturn_stream_stereo_offsets[] = {
    0x0,
    0x2000,
};

u32 saturn_stream_mono_halves[] = {
    0x0,
    0x3000,
    0x800,
    0x2800,
};

u32 saturn_stream_mono_offsets[] = {
    0x0,
    0x1000,
    0x2000,
    0x79ce,
    0x78007000,
};

s32 saturn_sound_fade_steps[] = {
    256,
    384,
    512,
    640,
    768,
    896,
    1024,
    1152,
};

const char saturn_sound_driver_name[] = "SDDRVS.TSK";

const char saturn_sound_map_name[] = "SDDRVS.MP";

static char stream_name_left[16] = "01234567.BIN";

static char stream_name_right[16] = "89ABCDEF.BIN";

struct SaturnStreamTrack saturn_stream_track_info = {
    0,
    0,
    1,
    { 0 },
    0x7FFFFFFF,
    stream_name_left,
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF },
    stream_name_right,
};

u8 saturn_sound_stage_maps[] = {
    0x00,
    0x00,
    0x01,
    0x01,
    0x02,
    0x02,
    0x03,
    0x03,
    0x04,
    0x04,
    0x05,
    0x05,
    0x06,
    0x06,
    0x07,
    0x07,
    0x08,
    0x08,
    0x09,
    0xFF,
    0x08,
    0xFF,
    0x09,
    0x09,
    0x0A,
    0x0A,
    0x00,
    0xFF,
    0x00,
    0x00,
    0x00,
    0xFF,
    0x00,
    0x01,
    0x00,
    0x02,
    0x00,
    0x00,
};

s16 saturn_sound_kind_bases[] = {
    8,
    47,
    176,
    112,
    416,
    416,
    0,
};

static void sound_smpc_command(u8 command)
{
    while ((SMPC_SF & 1) == 1) { }
    SMPC_SF = 1;
    SMPC_COMREG = command;
    while (SMPC_SF & 1) { }
}

void saturn_sound_initialize(void)
{
    u32* clear;
    u32 bytes;
    saturn_sound_driver_buffer = (u8*)SOUND_DRIVER_BUFFER;
    saturn_sound_map_buffer = (u8*)SOUND_MAP_BUFFER;
    saturn_sound_driver_bytes = SOUND_DRIVER_BYTES;
    saturn_sound_map_bytes = SOUND_MAP_BYTES;
    saturn_cd_load_file(saturn_sound_driver_name, saturn_sound_driver_buffer);
    saturn_cd_load_file(saturn_sound_map_name, saturn_sound_map_buffer);
    sound_smpc_command(SMPC_SNDOFF);
    SCSP_COMMON = SCSP_COMMON_4MBIT;
    for (clear = (u32*)SOUND_RAM; clear < SOUND_RAM_CLEAR_END; clear++)
        *clear = 0;
    DMA_ScuMemCopy(SOUND_RAM, saturn_sound_driver_buffer, saturn_sound_driver_bytes);
    while (DMA_ScuResult() != 0) { }
    saturn_sound_driver_header = SOUND_RAM + SOUND_DRIVER_HEADER(0);
    saturn_sound_command_queue = SOUND_RAM + SOUND_DRIVER_HEADER(4);
    saturn_sound_driver_area = SOUND_RAM + (((u32)SOUND_DRIVER_HALF(0x12) << 16) | SOUND_DRIVER_HALF(0x14));
    saturn_sound_driver_area[SOUND_DRIVER_BOOT] = SOUND_DRIVER_REQUEST;
    saturn_sound_command_slot = saturn_sound_command_queue;
    saturn_sound_table_d8 = SOUND_RAM + SOUND_DRIVER_HEADER(8);
    saturn_sound_sequence_table = saturn_sound_command_queue + SOUND_SEQUENCE_OFFSET;
    saturn_sound_pcm_table = saturn_sound_command_queue + SOUND_PCM_OFFSET;
    saturn_sound_table_ec = saturn_sound_command_queue + SOUND_TABLE_B0;
    saturn_sound_table_e0 = saturn_sound_command_queue + SOUND_TABLE_90;
    saturn_sound_table_e4 = saturn_sound_command_queue + SOUND_TABLE_94;
    bytes = (u32)saturn_sound_map_bytes * 2;
    bytes = bytes - (u32)((s32)bytes % 4) + 4;
    DMA_ScuMemCopy(SOUND_RAM + *(volatile u32*)(saturn_sound_driver_header + 8), saturn_sound_map_buffer, bytes);
    while (DMA_ScuResult() != 0) { }
    saturn_sound_command_lock = 0;
    sound_smpc_command(SMPC_SNDON);
    saturn_sound_enable_sequences();
    saturn_sound_reset_state();
}

static void sound_write_command(u16 command)
{
    *(volatile u16*)saturn_sound_command_slot = command;
}

static void sound_submit(void)
{
    saturn_sound_driver_area[SOUND_DRIVER_PENDING] = SOUND_DRIVER_REQUEST;
}

static void sound_wait(void)
{
    while (!saturn_sound_wait_ready()) {
    }
}

void saturn_sound_enable_sequences(void)
{
    sound_wait();
    saturn_sound_next_slot();
    saturn_sound_command_slot[2] = 1;
    saturn_sound_command_slot[3] = 1;
    saturn_sound_command_slot[4] = 1;
    saturn_sound_command_slot[5] = 1;
    saturn_sound_command_slot[6] = 1;
    sound_write_command(SOUND_COMMAND_SEQUENCE_MODE);
    sound_submit();
    sound_wait();
    saturn_sound_command_lock = 0;
}

u8 saturn_sound_change_map(u8 map)
{
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    sound_wait();
    saturn_sound_next_slot();
    saturn_sound_command_slot[2] = map;
    sound_write_command(SOUND_COMMAND_CHANGE_MAP);
    sound_submit();
    sound_wait();
    saturn_sound_next_slot();
    saturn_sound_command_slot[2] = map;
    sound_write_command(SOUND_COMMAND_CHANGE_MAP);
    sound_submit();
    sound_wait();
    saturn_sound_command_lock = 0;
    return 0;
}

static u8 sound_queue_byte(u16 command, u8 value)
{
    u8 result;
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    result = 1;
    if (saturn_sound_next_slot() == 1) {
        result = 0;
        saturn_sound_command_slot[2] = value;
        sound_write_command(command);
    }
    saturn_sound_command_lock = 0;
    return result;
}

u8 saturn_sound_set_total_volume(u8 volume)
{
    return sound_queue_byte(SOUND_COMMAND_TOTAL_VOLUME, volume);
}

u8 saturn_sound_set_effect(u8 effect)
{
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    sound_wait();
    saturn_sound_next_slot();
    saturn_sound_command_slot[2] = effect;
    sound_write_command(SOUND_COMMAND_EFFECT);
    sound_submit();
    sound_wait();
    saturn_sound_command_lock = 0;
    return 0;
}

static u8 sound_queue_pair(u16 command, u8 first, u8 second)
{
    u8 result;
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    result = 1;
    if (saturn_sound_next_slot() == 1) {
        result = 0;
        saturn_sound_command_slot[2] = first;
        saturn_sound_command_slot[3] = second;
        sound_write_command(command);
    }
    saturn_sound_command_lock = 0;
    return result;
}

u8 saturn_sound_set_mix(u8 mix, u8 level)
{
    return sound_queue_pair(SOUND_COMMAND_MIX, mix, level);
}

u8 saturn_sound_set_mix_param(u8 number, u8 level, u8 pan)
{
    return sound_queue_pair(SOUND_COMMAND_MIX_PARAM, number, (u8)((level << 5) | pan));
}

u8 saturn_sound_level_analysis(u16* result, u8 channel)
{
    volatile u16* out = result;
    s32 delay;
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    sound_wait();
    saturn_sound_next_slot();
    SOUND_ANALYSIS_RESULT = 0;
    saturn_sound_command_slot[2] = channel;
    sound_write_command(SOUND_COMMAND_LEVEL_ANALYSIS);
    sound_submit();
    for (;;) {
        *out = SOUND_ANALYSIS_RESULT;
        if (*out != 0) {
            break;
        }
        for (delay = SOUND_ANALYSIS_DELAY; delay != 0; delay--) {
            (void)*(volatile u32*)0;
        }
    }
    saturn_sound_command_lock = 0;
    return 0;
}

u8 saturn_sound_cut_all(void)
{
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    sound_wait();
    saturn_sound_next_slot();
    sound_write_command(SOUND_COMMAND_CUT_ALL);
    sound_submit();
    sound_wait();
    saturn_sound_command_lock = 0;
    return 0;
}

u8 saturn_sound_disable_sequences(void)
{
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    sound_wait();
    saturn_sound_next_slot();
    saturn_sound_command_slot[2] = 1;
    saturn_sound_command_slot[3] = 0;
    saturn_sound_command_slot[4] = 0;
    saturn_sound_command_slot[5] = 0;
    saturn_sound_command_slot[6] = 0;
    sound_write_command(SOUND_COMMAND_SEQUENCE_MODE);
    sound_submit();
    sound_wait();
    saturn_sound_command_lock = 0;
    return 0;
}

u8 saturn_sound_seq_start(u8 sequence, u8 bank, u8 song, u8 priority)
{
    u8 result;
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    result = 1;
    if (saturn_sound_next_slot() == 1) {
        result = 0;
        saturn_sound_command_slot[2] = sequence;
        saturn_sound_command_slot[3] = bank;
        saturn_sound_command_slot[4] = song;
        saturn_sound_command_slot[5] = priority;
        sound_write_command(SOUND_COMMAND_SEQ_START);
    }
    saturn_sound_command_lock = 0;
    return result;
}

u8 saturn_sound_seq_stop(u8 sequence)
{
    return sound_queue_byte(SOUND_COMMAND_SEQ_STOP, sequence);
}

u8 saturn_sound_seq_pause(u8 sequence)
{
    return sound_queue_byte(SOUND_COMMAND_SEQ_PAUSE, sequence);
}

u8 saturn_sound_seq_continue(u8 sequence)
{
    return sound_queue_byte(SOUND_COMMAND_SEQ_CONTINUE, sequence);
}

u8 saturn_sound_seq_volume(u8 sequence, u8 volume, u8 fade)
{
    u8 result;
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    result = 1;
    if (saturn_sound_next_slot() == 1) {
        result = 0;
        saturn_sound_command_slot[2] = sequence;
        saturn_sound_command_slot[3] = volume;
        saturn_sound_command_slot[4] = fade;
        sound_write_command(SOUND_COMMAND_SEQ_VOLUME);
    }
    saturn_sound_command_lock = 0;
    return result;
}

u8 saturn_sound_seq_tempo(u8 sequence, s16 tempo)
{
    u8 result;
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    result = 1;
    if (saturn_sound_next_slot() == 1) {
        result = 0;
        saturn_sound_command_slot[2] = sequence;
        saturn_sound_command_slot[4] = (u8)(tempo >> 8);
        saturn_sound_command_slot[5] = (u8)tempo;
        sound_write_command(SOUND_COMMAND_SEQ_TEMPO);
    }
    saturn_sound_command_lock = 0;
    return result;
}

u8 saturn_sound_seq_control(u8 sequence, u8 high, u8 low)
{
    return sound_queue_pair(SOUND_COMMAND_SEQ_CONTROL, sequence, (u8)(low | high));
}

u8 saturn_sound_cdda_level(u8 left, u8 right)
{
    return sound_queue_pair(SOUND_COMMAND_CDDA_LEVEL, (u8)(left << 5), (u8)(right << 5));
}

u8 saturn_sound_cdda_pan(u8 left, u8 right)
{
    return sound_queue_pair(SOUND_COMMAND_CDDA_PAN, left, right);
}

void saturn_sound_seq_status(struct SaturnSoundStatus* status, u8 sequence)
{
    volatile u8* entry = saturn_sound_sequence_table + sequence * 2;
    status->command = *(volatile u16*)entry & SOUND_STATUS_MASK;
    status->value = entry[1];
}

void saturn_sound_apply_output(u8 output)
{
    if (output == SOUND_MAP_UNSET) {
        saturn_sound_mode = SOUND_MAP_UNSET;
        saturn_sound_output = SOUND_MAP_UNSET;
        saturn_sound_driver_area[SOUND_DRIVER_OUTPUT] = SOUND_MAP_UNSET;
    } else {
        saturn_sound_mode = 0;
        saturn_sound_output = 0;
        saturn_sound_driver_area[SOUND_DRIVER_OUTPUT] = 0;
    }
    if (saturn_stream_active != 0) {
        saturn_music_stop();
    }
}

static void smpc_set_memory(u32 set)
{
    static const u8 shifts[4] = { 24, 16, 8, 0 };
    volatile u32* memory;
    u32 value;
    u32 i;
    while ((SMPC_SF & 1) == 1) {
    }
    SMPC_SF = 1;
    for (i = 0; i < 4; i++) {
        memory = (volatile u32*)(saturn_peripheral_record + SMPC_MEMORY_WORD * 4);
        value = set ? (*memory | SMPC_MEMORY_MONO) : (*memory ^ SMPC_MEMORY_MONO);
        *memory = value;
        (&SMPC_IREG0)[i * 2] = (u8)(value >> shifts[i]);
    }
    SMPC_COMREG = SMPC_SET_MEMORY;
    while (SMPC_SF & 1) {
    }
}

void saturn_sound_set_output(u8 output)
{
    if (output == SOUND_MAP_UNSET) {
        saturn_sound_mode = SOUND_MAP_UNSET;
        saturn_sound_output = SOUND_MAP_UNSET;
        saturn_sound_driver_area[SOUND_DRIVER_OUTPUT] = SOUND_MAP_UNSET;
        smpc_set_memory(1);
    } else {
        saturn_sound_mode = 0;
        saturn_sound_output = 0;
        saturn_sound_driver_area[SOUND_DRIVER_OUTPUT] = 0;
        smpc_set_memory(0);
    }
    if (saturn_stream_active != 0) {
        saturn_music_stop();
    }
}

void saturn_sound_change_map_quiet(u8 map)
{
    saturn_sound_key_mask(0);
    saturn_sound_change_map(map);
    saturn_sound_key_mask(1);
}

void saturn_stage_select_sound(void)
{
    u8 map = saturn_sound_stage_maps[saturn_engine_bytes[ENGINE_STAGE] * 2 + saturn_engine_bytes[ENGINE_SUBSTAGE]];
    if (map == SOUND_MAP_NONE) {
        saturn_sound_stage_map = SOUND_MAP_UNSET;
        return;
    }
    saturn_sound_enable_sequences();
    saturn_sound_key_mask(0);
    saturn_sound_stage_map = map;
    saturn_sound_change_map(saturn_sound_stage_map);
}

void saturn_stage_sound_finalize(void)
{
    if (saturn_sound_stage_map < SOUND_MAP_UNSET) {
        saturn_sound_key_mask(1);
        saturn_sound_set_mix(0, 0);
        saturn_sound_total_volume = SOUND_FINAL_VOLUME;
        saturn_sound_set_total_volume(SOUND_FINAL_VOLUME);
    }
}

static void sound_push_request(struct SaturnSoundRequest* queue, u8* index, s32 kind, s32 id, s32 pan)
{
    struct SaturnSoundRequest* request = &queue[*index];
    request->id = (s16)id;
    request->kind = (s16)kind;
    request->pan = (s16)pan;
    *index = (u8)((*index + 1) & SATURN_SOUND_REQUEST_MASK);
}

void saturn_music_request(s32 kind, s32 id, s32 pan, s32 unused)
{
    struct SaturnSoundRequest* request;
    struct SaturnSoundEffect* effect;
    s32 count;
    s8 stage;
    if ((u16)kind > SOUND_KIND_EFFECT_LAST) {
        if (!saturn_sound_wait_ready()) {
            sound_push_request(saturn_sound_requests, &saturn_sound_request_write, kind, id, pan);
            return;
        }
        if (saturn_sound_request_read != saturn_sound_request_write) {
            sound_push_request(saturn_sound_requests, &saturn_sound_request_write, kind, id, pan);
            request = &saturn_sound_requests[saturn_sound_request_read];
            id = request->id;
            kind = request->kind;
            pan = request->pan;
            saturn_sound_request_read = (u8)((saturn_sound_request_read + 1) & SATURN_SOUND_REQUEST_MASK);
        }
        saturn_sound_dispatch(kind, id, pan);
        count = 0;
        while (saturn_sound_request_read != saturn_sound_request_write) {
            if (count > SOUND_REQUEST_BURST) {
                break;
            }
            count++;
            request = &saturn_sound_requests[saturn_sound_request_read];
            id = request->id;
            kind = request->kind;
            pan = request->pan;
            saturn_sound_request_read = (u8)((saturn_sound_request_read + 1) & SATURN_SOUND_REQUEST_MASK);
            saturn_sound_dispatch(kind, id, pan);
        }
        sound_submit();
        return;
    }
    if ((u16)id >= SOUND_FIRST_EFFECT) {
        effect = &saturn_sound_effects[(u16)id];
        if ((u32)(s32)effect->priority < (u32)(s32)saturn_sound_effects[saturn_sound_channel_effects[effect->channel]].priority) {
            return;
        }
        if (effect->sequence == SOUND_NO_SEQUENCE) {
            return;
        }
        if (effect->group == saturn_sound_last_group) {
            return;
        }
        stage = saturn_engine_bytes[ENGINE_STAGE];
        if (stage != SOUND_SPECIAL_STAGE && stage >= 0 && stage <= SOUND_LAST_STAGE && D_80171EA8 != 0 && (u8)effect->group >= SOUND_GROUP_LIMIT) {
            return;
        }
        saturn_sound_channel_effects[effect->channel] = (u16)id;
    }
    sound_push_request(saturn_sound_effect_requests, &saturn_sound_effect_request_write, kind, id, pan);
}

void saturn_stream_frame(void)
{
    if ((saturn_sound_driver_area[SOUND_DRIVER_PENDING] & SOUND_DRIVER_REQUEST) == 0) {
        SOUND_DRIVER_STATUS &= SOUND_DRIVER_STATUS_MASK;
        saturn_sound_frame();
    }
    saturn_sound_peak = SOUND_DRIVER_PEAK;
    saturn_sound_level = SOUND_DRIVER_LEVEL;
    saturn_sound_counter = SOUND_DRIVER_STATUS;
    saturn_sound_clear_stopped_effects();
}

void saturn_sound_frame(void)
{
    struct SaturnSoundRequest* request;
    s32 backlog;
    if (saturn_movie_active != 0) {
        if ((saturn_sound_driver_area[SOUND_DRIVER_PENDING] & SOUND_DRIVER_REQUEST) == 0 && *saturn_sound_command_slot != 0) {
            sound_submit();
            saturn_sound_wait_ready();
        }
        return;
    }
    saturn_sound_wait_ready();
    if (saturn_sound_request_read != saturn_sound_request_write) {
        request = &saturn_sound_requests[saturn_sound_request_read];
        saturn_sound_dispatch(request->kind, request->id, request->pan);
        saturn_sound_request_read = (u8)((saturn_sound_request_read + 1) & SATURN_SOUND_REQUEST_MASK);
    }
    if (saturn_sound_effect_request_read != saturn_sound_effect_request_write) {
        saturn_sound_effect_start(&saturn_sound_effect_requests[saturn_sound_effect_request_read]);
        saturn_sound_effect_request_read = (u8)((saturn_sound_effect_request_read + 1) & SATURN_SOUND_REQUEST_MASK);
    }
    saturn_sound_update_fades();
    if (saturn_music_fading != 0) {
        backlog = (s32)(saturn_sound_command_slot - saturn_sound_command_queue) / SATURN_SOUND_SLOT_BYTES;
        if (backlog > SOUND_QUEUE_BACKLOG) {
            sound_submit();
            saturn_sound_wait_ready();
        }
    } else if (*saturn_sound_command_slot != 0) {
        sound_submit();
        saturn_sound_wait_ready();
    }
}

void saturn_sound_update_fades(void)
{
    struct SaturnSoundFade* fade = &saturn_sound_fade;
    struct SaturnSoundPcmParam param;
    u8* sequence_level = (u8*)&fade->sequence_level;
    u8* stream_level = (u8*)&fade->stream_level;
    switch (fade->sequence_mode) {
    case SOUND_FADE_UP:
        fade->sequence_level += fade->sequence_step;
        if (sequence_level[0] == SOUND_LEVEL_MAX) {
            fade->sequence_mode = 0;
        }
        saturn_sound_seq_volume(SOUND_FADE_SEQUENCE, sequence_level[0], 0);
        break;
    case SOUND_FADE_DOWN:
        fade->sequence_level -= fade->sequence_step;
        if (sequence_level[0] == 0) {
            fade->sequence_mode = 0;
        }
        saturn_sound_seq_volume(SOUND_FADE_SEQUENCE, sequence_level[0], 0);
        break;
    }
    switch (fade->stream_mode) {
    case SOUND_FADE_UP:
        fade->stream_level -= fade->stream_step;
        if (stream_level[0] >= SOUND_LEVEL_NEGATIVE) {
            fade->stream_mode = 0;
            stream_level[0] = 0;
        }
        break;
    case SOUND_FADE_DOWN:
        fade->stream_level += fade->stream_step;
        if (stream_level[0] >= SOUND_LEVEL_MAX) {
            fade->stream_mode = 0;
            stream_level[0] = SOUND_LEVEL_MAX;
        }
        break;
    default:
        return;
    }
    param.number = 0;
    param.level = STREAM_SEQUENCE;
    param.pitch = saturn_stream_pitch;
    param.effect_route = 0;
    param.effect_level = 0;
    param.filter_route = 0;
    param.filter_level = 0;
    saturn_sound_pcm_change(&param, stream_level[0]);
}

void saturn_stream_reset(void)
{
    saturn_sound_pending_word = 0;
    saturn_sound_total_volume = 0;
    saturn_sound_set_total_volume(0);
    saturn_sound_enable_sequences();
}

void saturn_sound_effect_status(u16 effect)
{
    struct SaturnSoundStatus status;
    if (effect < SATURN_SOUND_EFFECT_COUNT) {
        saturn_sound_seq_status(&status, saturn_sound_effects[effect].channel);
    }
}

void saturn_sound_set_mix_params(u8 count, u8 level, u8 pan, u8 enable)
{
    u32 i;
    u8 value = pan;
    if (saturn_sound_mode == SOUND_MAP_UNSET) {
        value = saturn_sound_mix_default;
    }
    if (count > 0 && count <= SOUND_MIX_CHANNELS && enable == 1) {
        for (i = 0; i < count; i++) {
            saturn_sound_set_mix_param((u8)i, level, value);
        }
    } else {
        for (i = 0; i < count; i++) {
            saturn_sound_set_mix_param((u8)i, 0, saturn_sound_mix_default);
        }
    }
}

u8 saturn_sound_send_command(u8 command, u8 slot, u16* data)
{
    volatile u16* words;
    sound_wait();
    words = (volatile u16*)(saturn_sound_command_queue + slot * SATURN_SOUND_SLOT_BYTES);
    words[1] = data[0];
    words[2] = data[1];
    words[3] = data[2];
    words[4] = data[3];
    words[5] = data[4];
    words[6] = data[5];
    words[7] = data[6];
    words[0] = (u16)(command << 8);
    return 0;
}

void saturn_sound_effect_start(struct SaturnSoundRequest* request)
{
    u16 id = (u16)request->id;
    struct SaturnSoundEffect* effect = &saturn_sound_effects[id];
    u8 map = effect->map;
    u16 level;
    u16 flags;
    if (id < SATURN_SOUND_EFFECT_COUNT && effect->channel != SOUND_NO_SEQUENCE) {
        if (saturn_sound_effect_mode == 1) {
            saturn_sound_effect_data[0] = (u16)((effect->channel << 8) | (u8)effect->group);
            saturn_sound_effect_data[1] = (u16)((effect->volume << 8) | (u8)effect->priority);
            saturn_sound_send_command(SOUND_RAW_EFFECT, SOUND_RAW_EFFECT_SLOT, saturn_sound_effect_data);
            saturn_sound_effect_data[0] = (u16)((effect->channel << 8) | map);
            saturn_sound_effect_data[1] = 0;
            saturn_sound_send_command(SOUND_RAW_MAP, SOUND_RAW_MAP_SLOT, saturn_sound_effect_data);
        }
        level = SOUND_PAN_CENTER;
        flags = (u16)request->kind == 1 ? 0 : SOUND_PAN_FIXED;
        if (saturn_sound_output == 0) {
            if (effect->pan_mode == 0) {
                if (flags == 0) {
                    level = (u16)request->pan;
                } else {
                    level = SOUND_PAN_CENTER;
                }
            } else {
                flags = SOUND_PAN_FIXED;
            }
        } else {
            flags = SOUND_PAN_FIXED;
        }
        if (level <= SOUND_PAN_MAX) {
            saturn_sound_effect_data[0] = (u16)((effect->channel << 8) | flags | (u8)saturn_sound_pan_table[level]);
            saturn_sound_effect_data[1] = 0;
            saturn_sound_send_command(SOUND_RAW_PAN, SOUND_RAW_PAN_SLOT, saturn_sound_effect_data);
        }
    }
    sound_submit();
}

static void sound_set_stream_fade(u16 mode, s32 pan)
{
    saturn_sound_fade.stream_mode = mode;
    saturn_sound_fade.stream_step = (s16)saturn_sound_fade_steps[(u16)pan];
}

void saturn_sound_dispatch(s32 kind, s32 id, s32 pan)
{
    struct SaturnSoundEffect* effect = &saturn_sound_effects[(u16)id];
    struct SaturnSoundStatus status;
    s8* mix;
    u16 level;
    u8 count;
    switch ((u32)(u16)kind - 2) {
    case 0:
        if (saturn_sound_output != 0) {
            level = SOUND_PAN_CENTER;
        } else if (effect->pan_mode != 0) {
            level = SOUND_PAN_CENTER;
        } else {
            level = (u16)pan;
        }
        if (level > SOUND_PAN_MAX) {
            break;
        }
        saturn_sound_seq_control(effect->channel, 0, (u8)saturn_sound_pan_table[level]);
        mix = &saturn_sound_mix_table[level];
        count = saturn_sound_mix_count;
        if (count > 0 && count <= SOUND_MIX_CHANNELS) {
            saturn_sound_set_mix_param(0, SOUND_MIX_LEVEL, (u8)*mix);
            saturn_sound_set_mix_param(1, SOUND_MIX_LEVEL, (u8)*mix);
        } else {
            saturn_sound_set_mix_param(0, 0, (u8)*mix);
            saturn_sound_set_mix_param(1, 0, (u8)*mix);
        }
        break;
    case 1:
        saturn_sound_disable_sequences();
        break;
    case 2:
        saturn_sound_seq_status(&status, effect->channel);
        if (status.command != 0) {
            saturn_sound_seq_stop(effect->channel);
        }
        break;
    case 3:
        saturn_sound_seq_tempo(effect->channel, saturn_sound_tempos[(u16)pan]);
        break;
    case 4:
        saturn_sound_seq_volume(effect->channel, (u8)pan, 0);
        break;
    case 5:
        saturn_sound_seq_pause(effect->channel);
        break;
    case 6:
        saturn_sound_seq_status(&status, effect->channel);
        if (status.command == SOUND_STATUS_PAUSED) {
            saturn_sound_seq_continue(effect->channel);
        }
        break;
    case 8:
        saturn_music_start((s16)id, pan);
        break;
    case 9:
        saturn_music_stop();
        break;
    case 10:
        saturn_stream_pcm_stop();
        break;
    case 11:
        if (saturn_stream_active != 0) {
            saturn_stream_pcm_start();
        }
        break;
    case 12:
        saturn_sound_fade.stream_mode = 0;
        saturn_stream_set_volume((u8)pan);
        break;
    case 13:
        sound_set_stream_fade(SOUND_FADE_UP, pan);
        break;
    case 14:
        sound_set_stream_fade(SOUND_FADE_DOWN, pan);
        break;
    case 15:
        saturn_sound_enable_sequences();
        break;
    case 16:
        saturn_sound_effect_mode = 0;
        break;
    case 17:
        saturn_sound_effect_mode = 1;
        break;
    case 18:
        saturn_sound_pause_playing();
        break;
    case 19:
        saturn_sound_continue_paused();
        break;
    case 20:
        saturn_sound_fade.sequence_mode = SOUND_FADE_UP;
        break;
    case 21:
        saturn_sound_fade.sequence_mode = SOUND_FADE_DOWN;
        break;
    case 22:
        saturn_sound_stop_sequences();
        break;
    }
}

void saturn_sound_clear_stopped_effects(void)
{
    struct SaturnSoundStatus status;
    u16 i;
    for (i = 0; i < SATURN_SOUND_SEQUENCES; i++) {
        saturn_sound_seq_status(&status, (u8)i);
        if (status.command != SOUND_STATUS_PLAYING) {
            saturn_sound_channel_effects[i] = 0;
        }
    }
}

s16 saturn_sound_seq_state(u8 sequence)
{
    struct SaturnSoundStatus status;
    saturn_sound_seq_status(&status, sequence);
    return (s16)status.command;
}

void saturn_sound_pause_playing(void)
{
    struct SaturnSoundStatus status;
    u32 i;
    for (i = 0; i < SATURN_SOUND_SEQUENCES; i++) {
        saturn_sound_seq_status(&status, (u8)i);
        if (status.command == SOUND_STATUS_PLAYING) {
            saturn_sound_seq_pause((u8)i);
        }
    }
}

void saturn_sound_continue_paused(void)
{
    struct SaturnSoundStatus status;
    u32 i;
    for (i = 0; i < SATURN_SOUND_SEQUENCES; i++) {
        saturn_sound_seq_status(&status, (u8)i);
        if (status.command == SOUND_STATUS_PAUSED) {
            saturn_sound_seq_continue((u8)i);
        }
    }
}

void saturn_sound_stop_sequences(void)
{
    struct SaturnSoundStatus status;
    u32 i;
    for (i = 0; i < SATURN_SOUND_SEQUENCES; i++) {
        saturn_sound_seq_status(&status, (u8)i);
        if (status.command != 0) {
            saturn_sound_seq_stop((u8)i);
        }
    }
}

void saturn_sound_mute_playing(void)
{
    struct SaturnSoundStatus status;
    u32 i;
    for (i = 0; i < SATURN_SOUND_SEQUENCES; i++) {
        saturn_sound_seq_status(&status, (u8)i);
        if (status.command == SOUND_STATUS_PLAYING) {
            saturn_sound_seq_volume((u8)i, 0, 0);
        }
    }
}

void saturn_sound_set_playing_volume(u8 volume)
{
    struct SaturnSoundStatus status;
    u32 i;
    for (i = 0; i < SATURN_SOUND_SEQUENCES; i++) {
        saturn_sound_seq_status(&status, (u8)i);
        if (status.command == SOUND_STATUS_PLAYING) {
            saturn_sound_seq_volume((u8)i, volume, 0);
        }
    }
}

u8 saturn_sound_next_slot(void)
{
    if (saturn_sound_driver_busy == 1) {
        return 0;
    }
    if (*saturn_sound_command_slot != 0) {
        saturn_sound_command_slot += SATURN_SOUND_SLOT_BYTES;
    } else {
        saturn_sound_command_slot = saturn_sound_command_queue;
    }
    return 1;
}

u8 saturn_sound_wait_ready(void)
{
    volatile s32 delay;
    saturn_sound_wait_retries = 0;
    for (;;) {
        if ((saturn_sound_driver_area[SOUND_DRIVER_PENDING] & SOUND_DRIVER_REQUEST) == 0) {
            saturn_sound_driver_busy = 0;
            return 1;
        }
        saturn_sound_driver_busy = 1;
        delay = saturn_sound_wait_retries > SOUND_WAIT_RETRY_LIMIT ? SOUND_WAIT_LONG : SOUND_WAIT_SHORT;
        while (delay-- != 0) {
        }
        saturn_sound_wait_retries++;
    }
}

void saturn_sound_reset_state(void)
{
    u32 i;
    saturn_sound_counter = 0;
    saturn_sound_driver_busy = 0;
    saturn_sound_pending_word = 0;
    for (i = 0; i < STREAM_STATE_BYTES; i++) {
        saturn_stream_state[i] = 0;
    }
    saturn_stream_track = SOUND_MAP_NONE;
    saturn_stream_active = 0;
    saturn_sound_fade.stream_step = 0;
    saturn_sound_fade.stream_level = 0;
    saturn_sound_fade.stream_mode = 0;
    if (saturn_sound_output == SOUND_OUTPUT_UNSET) {
        saturn_sound_output = (*(u32*)(saturn_peripheral_record + PERIPHERAL_FLAGS) & PERIPHERAL_MONO) ? SOUND_MAP_UNSET : 0;
    }
    saturn_sound_fade.sequence_step = 0;
    saturn_sound_fade.sequence_level = SOUND_LEVEL_MAX << 8;
    saturn_sound_fade.sequence_mode = 0;
    saturn_sound_stage_map = SOUND_STAGE_MAP_INITIAL;
    saturn_sound_total_volume = SOUND_FINAL_VOLUME;
    saturn_sound_effect_mode = 1;
    saturn_sound_set_total_volume(saturn_sound_total_volume);
    saturn_sound_mix_count = 0;
    saturn_sound_apply_output(saturn_sound_output);
    saturn_sound_effect_request_write = 0;
    saturn_sound_effect_request_read = 0;
    saturn_sound_request_write = 0;
    saturn_sound_request_read = 0;
    for (i = 0; i < SATURN_SOUND_SEQUENCES; i++) {
        saturn_sound_channel_effects[i] = 0;
    }
    saturn_sound_last_group = -1;
    saturn_music_thread_active = 0;
}

void saturn_sound_key_mask(u8 enable)
{
    volatile u32* entry = SOUND_KEY_TABLE;
    u32 flags;
    while ((entry[0] & SOUND_KEY_END) != SOUND_KEY_END) {
        flags = entry[1];
        if (enable == 1) {
            if ((flags & SOUND_KEY_MASKED) != SOUND_KEY_MASKED) {
                entry[1] = flags | SOUND_KEY_MASKED;
            }
        } else if (enable == 0) {
            if ((flags & SOUND_KEY_MASKED) == SOUND_KEY_MASKED) {
                entry[1] = flags & ~SOUND_KEY_MASKED;
            }
        }
        entry += 2;
    }
}

void saturn_sound_pcm_status(struct SaturnSoundPcmState* state, u8 number)
{
    volatile u8* entry = saturn_sound_pcm_table + number * 2;
    state->mode = (u8)(*(volatile u16*)entry >> 8);
    state->value = entry[1];
}

void saturn_stage_music_play(void)
{
    u16 key = (u16)(((u16)saturn_engine_bytes[ENGINE_STAGE] << 8) | saturn_engine_bytes[ENGINE_SUBSTAGE]);
    u8 track;
    switch (key) {
    case 0x0101:
    case 0x0201:
    case 0x0301:
    case 0x0401:
    case 0x0501:
    case 0x0601:
    case 0x0701:
    case 0x0801:
    case 0x0C00:
        track = MUSIC_BOSS;
        break;
    case 0x0900:
    case 0x0A00:
    case 0x0B01:
        track = MUSIC_FORTRESS_BOSS;
        break;
    case 0x0B00:
        track = saturn_engine_bytes[ENGINE_FORTRESS_FLAG] == 0 ? MUSIC_FORTRESS_A : MUSIC_FORTRESS_B;
        break;
    case 0x0C01:
        track = D_80171EA8 == 0 ? MUSIC_FINAL_A : MUSIC_FINAL_B;
        break;
    default:
        track = 0;
        break;
    }
    if (track != 0) {
        saturn_music_play(track, 0);
    }
}

void saturn_music_start(s32 track, s32 arg)
{
    saturn_music_track_setup((u16)(s16)track);
    saturn_music_stop();
    saturn_stream_open((u16)(s16)track);
    while (saturn_stream_ready() == 0) {
        saturn_thread_sleep(1);
    }
    saturn_stream_pcm_stop();
    if (saturn_stream_active != 0) {
        saturn_stream_pcm_start();
    }
    saturn_stream_set_volume(saturn_stream_track_info.volume);
    saturn_music_thread_active = 0;
}

void saturn_music_play(s32 track, s32 arg)
{
    saturn_music_thread_track = (u16)track;
    saturn_music_thread_arg = (u16)arg;
    saturn_thread_create(MUSIC_THREAD_SLOT, (u32)saturn_music_thread);
    saturn_music_thread_active = 1;
}

static void music_thread_wait(void)
{
    saturn_thread_sleep(1);
    if (!saturn_music_thread_active) {
        saturn_music_thread_active = 0;
        saturn_thread_exit();
    }
}

void saturn_music_thread(void)
{
    saturn_music_track_setup(saturn_music_thread_track);
    saturn_music_stop();
    saturn_music_thread_active = 1;
    saturn_stream_open(saturn_music_thread_track);
    while (saturn_stream_ready() == 0)
        music_thread_wait();
    saturn_stream_pcm_stop();
    music_thread_wait();
    if (saturn_stream_active != 0)
        saturn_stream_pcm_start();
    saturn_stream_set_volume(saturn_stream_track_info.volume);
    saturn_music_thread_active = 0;
    saturn_thread_exit();
}

void saturn_music_track_setup(u16 track)
{
    struct SaturnStreamTrack* info = &saturn_stream_track_info;
    char* name;
    char* name_right;
    u8 digit;
    info->stereo = 1;
    info->loop = STREAM_NO_LOOP;
    name = info->name;
    name_right = info->name_right;
    *name++ = 'S';
    *name_right++ = 'S';
    *name++ = 'T';
    *name_right++ = 'T';
    digit = saturn_hex_digits[track >> 4];
    *name++ = digit;
    *name_right++ = digit;
    digit = saturn_hex_digits[(s32)track % 16];
    *name++ = digit;
    *name_right++ = digit;
    *name++ = '_';
    *name_right++ = '_';
    *name++ = '0';
    *name_right++ = '1';
    saturn_stream.stereo_output = 0;
    if (track >= TRACK_ONCE_FIRST && track != TRACK_STEREO_ONCE) {
        info->stereo = 0;
        info->loop = 1;
        *(u16*)info = saturn_music_track_volumes[track];
    } else {
        switch (track) {
        case TRACK_CHARACTER:
            *name++ = '_';
            *name_right++ = '_';
            if (saturn_engine_bytes[TRACK_CHARACTER_ZERO] == 0) {
                *name++ = 'X';
                *name_right++ = 'X';
                *(u16*)info = saturn_music_track_volumes[0];
            } else {
                *name++ = 'Z';
                *name_right++ = 'Z';
                *(u16*)info = saturn_music_track_volumes[TRACK_ZERO_VOLUME];
            }
            break;
        case TRACK_VARIANT_A:
            *name++ = '_';
            *name_right++ = '_';
            if (saturn_engine_bytes[TRACK_VARIANT_FLAG] == 0) {
                *name++ = '0';
                *name_right++ = '0';
                *(u16*)info = saturn_music_track_volumes[0];
            } else {
                *name++ = '1';
                *name_right++ = '1';
                *(u16*)info = saturn_music_track_volumes[TRACK_VARIANT_A_VOLUME];
            }
            break;
        case TRACK_VARIANT_B:
            *name++ = '_';
            *name_right++ = '_';
            if (saturn_engine_bytes[TRACK_VARIANT_FLAG] == 0) {
                *name++ = '0';
                *name_right++ = '0';
                *(u16*)info = saturn_music_track_volumes[0];
            } else {
                *name++ = '1';
                *name_right++ = '1';
                *(u16*)info = saturn_music_track_volumes[TRACK_VARIANT_B_VOLUME];
            }
            break;
        case TRACK_ONCE_A:
        case TRACK_ONCE_B:
            info->stereo = 0;
            info->loop = 1;
            *(u16*)info = saturn_music_track_volumes[track];
            break;
        case TRACK_STEREO_ONCE:
            saturn_stream.stereo_output = 1;
            info->stereo = 0;
            *(u16*)info = saturn_music_track_volumes[track];
            info->loop = 1;
            break;
        default:
            *(u16*)info = saturn_music_track_volumes[track];
            break;
        }
    }
    *name++ = '.';
    *name_right++ = '.';
    *name++ = 'B';
    *name_right++ = 'B';
    *name++ = 'I';
    *name_right++ = 'I';
    *name++ = 'N';
    *name_right++ = 'N';
    *name = 0;
    *name_right = 0;
}

void saturn_stream_open(u16 track)
{
    struct SaturnStreamKey key;
    struct SaturnStreamTrack* info = &saturn_stream_track_info;
    volatile u32* buffer;
    u32 i;
    saturn_stream.transfer_state = 0;
    if (track > STREAM_TRACK_LIMIT) {
        return;
    }
    saturn_stream.track = track;
    saturn_stream.stereo_files = info->stereo;
    ((u8*)&saturn_sound_fade.stream_level)[0] = info->volume;
    ((u8*)&saturn_sound_fade.stream_level)[1] = 0;
    saturn_stream.group = STM_OpenGrp();
    for (i = 0; i < 6; i++) {
        key.value[i] = -1;
    }
    if (info->stereo == 0) {
        saturn_stream.file = GFS_NameToId(info->name);
        if (saturn_stream.file < 0) {
            return;
        }
        saturn_stream.stream = STM_OpenFid(saturn_stream.group, saturn_stream.file, &key, 1);
        STM_SetTrPara(saturn_stream.stream, STREAM_TRANSFER_SECTORS);
        STM_SetTrFunc(saturn_stream.stream, saturn_stream_transfer, saturn_stream.transfer);
        if (info->loop != STREAM_NO_LOOP) {
            STM_SetLoop(saturn_stream.group, saturn_stream.stream, info->loop);
            saturn_stream.mode = MODE_ONE_SHOT;
        } else {
            STM_SetLoop(saturn_stream.group, saturn_stream.stream, STREAM_NO_LOOP);
            saturn_stream.mode = MODE_LOOP;
        }
        STM_EraseCdbuf(saturn_stream.stream, 0, STREAM_ERASE_ALL);
    } else {
        saturn_stream.file = GFS_NameToId(info->name);
        if (saturn_stream.file < 0) {
            return;
        }
        saturn_stream.file_right = GFS_NameToId(info->name_right);
        if (saturn_stream.file_right < 0) {
            return;
        }
        saturn_stream.stream = STM_OpenFid(saturn_stream.group, saturn_stream.file, &key, 1);
        saturn_stream.stream_right = STM_OpenFid(saturn_stream.group, saturn_stream.file_right, &key, 1);
        STM_SetTrPara(saturn_stream.stream, STREAM_TRANSFER_SECTORS);
        STM_SetTrPara(saturn_stream.stream_right, STREAM_TRANSFER_SECTORS);
        STM_SetTrFunc(saturn_stream.stream, saturn_stream_transfer, saturn_stream.transfer);
        STM_SetTrFunc(saturn_stream.stream_right, saturn_stream_transfer, saturn_stream.transfer);
        STM_SetLoop(saturn_stream.group, saturn_stream.stream, 1);
        STM_SetLoop(saturn_stream.group, saturn_stream.stream_right, STREAM_NO_LOOP);
        STM_EraseCdbuf(saturn_stream.stream, 0, STREAM_ERASE_ALL);
        STM_EraseCdbuf(saturn_stream.stream_right, 0, STREAM_ERASE_ALL);
        saturn_stream.mode = MODE_STEREO;
    }
    STM_SetErrFunc(saturn_stream_error, saturn_stream_error_object);
    saturn_stream.transfer[0] = 1;
    saturn_stream.transfer[1] = 0;
    saturn_stream.transfer[2] = 0;
    saturn_stream.transfer[3] = 0;
    saturn_stream.transfer[4] = 0;
    saturn_stream.transfer_state = 1;
    saturn_stream.phase = PHASE_START;
    saturn_stream.copy_pending = 0;
    if (saturn_stream.stereo_output == 0) {
        buffer = STREAM_MONO_BUFFER;
        for (i = 0; i < STREAM_MONO_LONGS; i++) {
            buffer[i] = 0;
        }
    } else {
        buffer = STREAM_STEREO_BUFFER;
        for (i = 0; i < STREAM_STEREO_LONGS; i++) {
            buffer[i] = 0;
        }
    }
}

void saturn_stream_error(void* object, s32 code)
{
    if (code == -1) {
        STM_Recover();
        return;
    }
    if (code != 0) {
        saturn_cd_error_hook();
    }
}

static s32 stream_complete(void* stream)
{
    return STM_IsComplete(stream) == 1;
}

void saturn_stream_vblank(void)
{
    saturn_stream_server();
    switch (saturn_stream.phase) {
    case PHASE_START:
        saturn_stream_pcm_start();
        if (saturn_stream.mode == MODE_STEREO) {
            STM_SetTrGate(saturn_stream.stream_right, STREAM_GATE_OFF);
        }
        STM_SetTrGate(saturn_stream.stream, STREAM_GATE_ON);
        saturn_stream_set_exec_group(saturn_stream.group);
        switch (saturn_stream.mode) {
        case MODE_ONE_SHOT:
            saturn_stream.phase = PHASE_ENDING;
            break;
        case MODE_LOOP:
            saturn_stream.phase = PHASE_PLAYING;
            break;
        case MODE_STEREO:
            saturn_stream.phase = PHASE_SWITCH;
            break;
        }
        break;
    case PHASE_SWITCH:
        if (stream_complete(saturn_stream.stream)) {
            STM_SetTrGate(saturn_stream.stream, STREAM_GATE_OFF);
            STM_SetTrGate(saturn_stream.stream_right, STREAM_GATE_ON);
            saturn_stream.phase = PHASE_PLAYING;
        }
        break;
    case PHASE_ENDING:
        if (stream_complete(saturn_stream.stream)) {
            saturn_music_stop();
        }
        break;
    }
}

static void stream_exec_all(void)
{
    s16 i;
    for (i = 0; i < saturn_stream.handle_count; i++) {
        STM_ExecTrans(saturn_stream.handles[i]);
    }
}

void saturn_stream_server(void)
{
    if (saturn_stream.exec_pending == 1) {
        stream_exec_all();
        saturn_stream.exec_pending = 0;
    }
    saturn_stream.buffer_count = saturn_stream_count_buffers();
    switch (saturn_stream.server_state) {
    case 1:
        saturn_stream.server_result = STM_ExecServer();
        if (saturn_stream.copy_pending == 1) {
            saturn_stream.exec_pending = 1;
        }
        break;
    case 2:
        if (STM_ExecServer() == STREAM_SERVER_END) {
            saturn_stream.server_state = 3;
        }
        stream_exec_all();
        if (saturn_stream.copy_pending == 1) {
            saturn_stream.exec_pending = 2;
        }
        break;
    case 3:
        stream_exec_all();
        if (saturn_stream.copy_pending == 1) {
            saturn_stream.exec_pending = 1;
        }
        if (saturn_stream.buffer_count < STREAM_LOW_BUFFERS) {
            STM_SetExecGrp(saturn_stream.group);
            saturn_stream.server_state = 0;
        }
        break;
    }
    if (saturn_stream.copy_pending == 1) {
        saturn_stream_copy_strided(saturn_stream.copy_source, saturn_stream.copy_destination, saturn_stream.copy_bytes,
            saturn_stream.copy_stride);
        saturn_stream.copy_pending = 0;
    }
}

void saturn_stream_copy_strided(u32* source, u32* destination, u32 bytes, s32 stride)
{
    u32 i;
    for (i = 0; i < bytes >> 2; i++) {
        *destination++ = *source;
        source += stride;
    }
}

s32 saturn_stream_transfer(void* object, void* stream, s32 sectors)
{
    u8* transfer = (u8*)object;
    struct SaturnSoundPcmState state;
    s32 stride;
    if (sectors != TRANSFER_REQUESTED) {
        transfer[3]++;
        return 0;
    }
    if (saturn_stream.copy_pending == 1) {
        return 0;
    }
    switch (transfer[0]) {
    case 0:
        return 0;
    case 1:
        if (saturn_stream.exec_pending == 1) {
            return 0;
        }
        saturn_sound_pcm_status(&state, 0);
        if (state.mode == transfer[1]) {
            return 0;
        }
        if (saturn_stream.transfer_state == 1) {
            saturn_stream.transfer_state = 2;
        }
        transfer[0] = 2;
        transfer[5] = 0;
        transfer[2] = 0;
        break;
    case 2:
        break;
    default:
        return transfer[0];
    }
    if (transfer[2] == 0) {
        saturn_stream.copy_source = STM_StartTrans(stream, &stride);
        if (saturn_stream.stereo_output == 0) {
            saturn_stream.copy_destination = (u32*)(saturn_stream_mono_offsets[transfer[1]] + saturn_stream_mono_halves[transfer[5]] + STREAM_MONO_BUFFER_ADDRESS);
        } else {
            saturn_stream.copy_destination = (u32*)(saturn_stream_stereo_offsets[transfer[1]] + saturn_stream_stereo_halves[transfer[5]] + STREAM_STEREO_BUFFER_ADDRESS);
        }
        saturn_stream.copy_stride = stride;
        saturn_stream.copy_bytes = STREAM_COPY_BYTES;
        saturn_stream.copy_pending = 1;
        transfer[2] = 1;
        return -1;
    }
    transfer[2] = 0;
    transfer[5]++;
    if (saturn_stream.stereo_output == 0) {
        if (transfer[5] == 2) {
            transfer[0] = 1;
            transfer[1]++;
            if (transfer[1] >= 3) {
                transfer[1] = 0;
            }
        }
    } else if (transfer[5] == 4) {
        transfer[0] = 1;
        transfer[1] = (u8)(~transfer[1] & 1);
    }
    return 2;
}

void saturn_stream_set_exec_group(void* group)
{
    s32 i;
    STM_SetExecGrp(group);
    saturn_stream.handle_count = STM_GetStmNum(group);
    for (i = 0; i < saturn_stream.handle_count; i++) {
        saturn_stream.handles[i] = STM_GetStmHndl(group, i);
    }
    saturn_stream.server_state = 1;
    saturn_stream.exec_pending = 0;
}

void saturn_stream_close(void)
{
    saturn_stream.phase = PHASE_IDLE;
    STM_CloseGrp(saturn_stream.group);
    if (saturn_stream.track != SOUND_NO_TRACK) {
        if (saturn_stream.stereo_files != 0) {
            STM_EraseCdbuf(saturn_stream.stream, 0, STREAM_ERASE_ALL);
            STM_EraseCdbuf(saturn_stream.stream_right, 0, STREAM_ERASE_ALL);
        } else {
            STM_EraseCdbuf(saturn_stream.stream, 0, STREAM_ERASE_ALL);
        }
    }
    saturn_stream.group = NULL;
    saturn_stream.server_state = 0;
    saturn_stream.handle_count = 0;
}

u32 saturn_stream_count_buffers(void)
{
    u8 key[12];
    s32 file;
    s32 frame;
    s32 sectors;
    u32 count = 0;
    u32 i;
    for (i = 0; i < (u32)saturn_stream.handle_count; i++) {
        STM_GetInfo(saturn_stream.handles[i], &file, &sectors, &frame, key);
        count += STM_GetNumCdbuf(saturn_stream.handles[i]);
    }
    return count;
}

u8 saturn_stream_pcm_start(void)
{
    volatile u16* words;
    u16 size;
    if (saturn_sound_command_lock) {
        return 0;
    }
    saturn_sound_command_lock = 1;
    saturn_sound_next_slot();
    words = (volatile u16*)saturn_sound_command_slot;
    if (saturn_stream_stereo != 0) {
        saturn_stream_pitch = 0;
        words[1] = STREAM_PCM_LEFT;
        words[2] = STREAM_PCM_MONO_ADDRESS;
        size = STREAM_PCM_MONO_SIZE;
    } else {
        saturn_stream_pitch = 0;
        words[1] = STREAM_PCM_RIGHT;
        words[2] = STREAM_PCM_STEREO_ADDRESS;
        size = STREAM_PCM_STEREO_SIZE;
    }
    words[3] = size;
    words[4] = 0;
    words[5] = 0;
    words[6] = 0;
    words[7] = 0;
    words[0] = SOUND_COMMAND_PCM_START;
    sound_submit();
    sound_wait();
    saturn_sound_command_lock = 0;
    return 1;
}

u8 saturn_sound_pcm_start(struct SaturnSoundPcmStart* start, struct SaturnSoundPcmParam* param)
{
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    sound_wait();
    saturn_sound_next_slot();
    saturn_sound_command_slot[2] = (u8)(start->mode | param->number);
    saturn_sound_command_slot[3] = (u8)((param->level << 5) | param->number);
    saturn_sound_command_slot[4] = (u8)(start->address >> 8);
    saturn_sound_command_slot[5] = (u8)start->address;
    saturn_sound_command_slot[6] = (u8)(start->size >> 8);
    saturn_sound_command_slot[7] = (u8)start->size;
    saturn_sound_command_slot[8] = (u8)(param->pitch >> 8);
    saturn_sound_command_slot[9] = (u8)param->pitch;
    saturn_sound_command_slot[10] = (u8)((param->effect_route << 3) | param->effect_level);
    saturn_sound_command_slot[11] = (u8)((param->filter_route << 3) | param->filter_level);
    sound_write_command(SOUND_COMMAND_PCM_START);
    sound_submit();
    sound_wait();
    saturn_sound_command_lock = 0;
    return 0;
}

static void sound_clear_parameters(volatile u8* slot)
{
    volatile u16* words = (volatile u16*)slot;
    words[1] = 0;
    words[2] = 0;
    words[3] = 0;
    words[4] = 0;
    words[5] = 0;
    words[6] = 0;
    words[7] = 0;
}

void saturn_music_stop(void)
{
    volatile u8* slot;
    saturn_music_thread_active = 0;
    if (saturn_stream_active == 0) {
        return;
    }
    if (saturn_sound_command_lock) {
        return;
    }
    saturn_sound_command_lock = 1;
    sound_wait();
    saturn_sound_next_slot();
    slot = saturn_sound_command_slot;
    sound_clear_parameters(slot);
    *(volatile u16*)slot = SOUND_COMMAND_PCM_STOP;
    sound_submit();
    sound_wait();
    saturn_sound_command_lock = 0;
    saturn_stream_close();
}

void saturn_music_stop_paced(void)
{
    saturn_thread_sleep(1);
    saturn_stream_pcm_stop();
    saturn_thread_sleep(1);
    saturn_music_stop();
    saturn_music_thread_active = 0;
}

u8 saturn_sound_pcm_stop(u8 number)
{
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    sound_wait();
    saturn_sound_next_slot();
    saturn_sound_command_slot[2] = number;
    sound_write_command(SOUND_COMMAND_PCM_STOP);
    sound_submit();
    sound_wait();
    saturn_sound_command_lock = 0;
    return 0;
}

static void sound_write_pcm_change(struct SaturnSoundPcmParam* param)
{
    saturn_sound_command_slot[2] = param->number;
    saturn_sound_command_slot[3] = (u8)((param->level << 5) | param->number);
    saturn_sound_command_slot[4] = (u8)(param->pitch >> 8);
    saturn_sound_command_slot[5] = (u8)param->pitch;
    saturn_sound_command_slot[6] = (u8)((param->effect_route << 3) | param->effect_level);
    saturn_sound_command_slot[7] = (u8)((param->filter_route << 3) | param->filter_level);
}

u8 saturn_sound_pcm_change(struct SaturnSoundPcmParam* param, u8 level)
{
    u8 result;
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    result = 1;
    if (saturn_sound_next_slot() == 1) {
        sound_write_pcm_change(param);
        result = 0;
        saturn_sound_command_slot[8] = level;
        sound_write_command(SOUND_COMMAND_PCM_CHANGE);
    }
    saturn_sound_command_lock = 0;
    return result;
}

u8 saturn_sound_pcm_change_now(struct SaturnSoundPcmParam* param)
{
    if (saturn_sound_command_lock) {
        return 1;
    }
    saturn_sound_command_lock = 1;
    sound_wait();
    saturn_sound_next_slot();
    sound_write_pcm_change(param);
    saturn_sound_command_slot[8] = 0;
    sound_write_command(SOUND_COMMAND_PCM_CHANGE);
    sound_submit();
    sound_wait();
    saturn_sound_command_lock = 0;
    return 0;
}

u8 saturn_stream_pcm_stop(void)
{
    volatile u8* slot;
    if (saturn_stream_active == 0) {
        return 1;
    }
    if (saturn_sound_command_lock) {
        return 0;
    }
    saturn_sound_command_lock = 1;
    sound_wait();
    saturn_sound_next_slot();
    slot = saturn_sound_command_slot;
    sound_clear_parameters(slot);
    *(volatile u16*)slot = SOUND_COMMAND_PCM_STOP;
    sound_submit();
    sound_wait();
    saturn_sound_command_lock = 0;
    return 1;
}

void saturn_stream_pcm_restart(void)
{
    if (saturn_stream_active != 0) {
        saturn_stream_pcm_start();
    }
}

u8 saturn_stream_ready(void)
{
    return saturn_stream_status != STREAM_STATUS_BUSY;
}

u8 saturn_stream_set_volume(u8 volume)
{
    struct SaturnSoundPcmParam param;
    param.number = 0;
    param.level = STREAM_SEQUENCE;
    param.pitch = saturn_stream_pitch;
    param.effect_route = 0;
    param.effect_level = 0;
    param.filter_route = 0;
    param.filter_level = 0;
    ((u8*)&saturn_sound_fade.stream_level)[0] = volume;
    ((u8*)&saturn_sound_fade.stream_level)[1] = 0;
    return saturn_sound_pcm_change(&param, ((u8*)&saturn_sound_fade.stream_level)[0]);
}

s32 func_8001540C(s32 kind, s32 id, void* object)
{
    u8* bytes = (u8*)object;
    s16 sound = (s16)(saturn_sound_kind_bases[(u8)kind] + id);
    s32 pan;
    s32 x;
    if (object == NULL) {
        pan = SOUND_PAN_CENTER;
    } else {
        if ((s8)bytes[OBJECT_CAMERA] >= 0) {
            x = *(s16*)(bytes + OBJECT_X) - *(s16*)(saturn_sprite_cameras + CAMERA_X + (u8)(bytes[OBJECT_CAMERA] * SOUND_CAMERA_STRIDE));
        } else {
            x = *(s16*)(bytes + OBJECT_X);
        }
        pan = (x * 32) / SOUND_SCREEN_WIDTH;
        if ((s16)pan < 0) {
            pan = 0;
        } else if ((s16)pan > SOUND_PAN_MAX) {
            pan = SOUND_PAN_MAX;
        }
    }
    saturn_music_request(1, sound, pan, 0);
    return 0;
}
