#include "test_runtime.h"
#include "saturn/platform.h"

u8 saturn_sound_set_total_volume(u8 volume);
u8 saturn_sound_set_mix(u8 mix, u8 level);
u8 saturn_sound_set_mix_param(u8 number, u8 level, u8 pan);
u8 saturn_sound_seq_start(u8 sequence, u8 bank, u8 song, u8 priority);
u8 saturn_sound_seq_stop(u8 sequence);
u8 saturn_sound_seq_pause(u8 sequence);
u8 saturn_sound_seq_continue(u8 sequence);
u8 saturn_sound_seq_volume(u8 sequence, u8 volume, u8 fade);
u8 saturn_sound_seq_tempo(u8 sequence, s16 tempo);
u8 saturn_sound_seq_control(u8 sequence, u8 high, u8 low);
u8 saturn_sound_cdda_level(u8 left, u8 right);
u8 saturn_sound_cdda_pan(u8 left, u8 right);
void saturn_sound_clear_stopped_effects(void);
s16 saturn_sound_seq_state(u8 sequence);
void saturn_sound_pause_playing(void);
void saturn_sound_continue_paused(void);
void saturn_sound_stop_sequences(void);
void saturn_sound_mute_playing(void);
void saturn_sound_set_playing_volume(u8 volume);
void saturn_sound_set_mix_params(u8 count, u8 level, u8 pan, u8 enable);
void saturn_sound_update_fades(void);
void saturn_sound_set_output(u8 output);
u8 saturn_sound_wait_ready(void);

static u8 queue[2048];
static u8 driver[0x80];
static u8 sequences[SATURN_SOUND_SEQUENCES * 2];
static u32 results;

static void setup(void)
{
    saturn_sound_command_queue = queue;
    saturn_sound_command_slot = queue;
    saturn_sound_driver_area = driver;
    saturn_sound_sequence_table = sequences;
}

static void status_sweeps(void)
{
    static const u16 states[SATURN_SOUND_SEQUENCES] = { 0x0100, 0x0300, 0x0000, 0x0200, 0x0100, 0x0300, 0x0000, 0x0500 };
    u32 i;
    setup();
    for (i = 0; i < SATURN_SOUND_SEQUENCES; i++) {
        *(u16*)&sequences[i * 2] = states[i] | (u8)(i + 1);
        saturn_sound_channel_effects[i] = (u16)(0x100 + i);
    }
    saturn_sound_clear_stopped_effects();
    saturn_sound_pause_playing();
    saturn_sound_continue_paused();
    saturn_sound_stop_sequences();
    saturn_sound_mute_playing();
    saturn_sound_set_playing_volume(0x40);
    results = (u16)saturn_sound_seq_state(1) | (u32)(u16)saturn_sound_seq_state(7) << 16;
}

static void output_modes(void)
{
    setup();
    saturn_sound_set_output(0x80);
    results = saturn_sound_mode | saturn_sound_output << 8 | driver[3] << 16;
    saturn_sound_set_output(0);
    results |= (u32)(saturn_sound_mode | saturn_sound_output | driver[3]) << 24;
    results ^= saturn_sound_wait_ready() << 4;
}

static void sequence_fades(void)
{
    setup();
    saturn_sound_fade.sequence_mode = 1;
    saturn_sound_fade.sequence_level = 0x7E00;
    saturn_sound_fade.sequence_step = 0x100;
    saturn_sound_update_fades();
    results = saturn_sound_fade.sequence_mode | saturn_sound_fade.sequence_level << 8;
    saturn_sound_fade.sequence_mode = 2;
    saturn_sound_fade.sequence_level = 0x0100;
    saturn_sound_update_fades();
    saturn_sound_update_fades();
    results ^= (u32)(saturn_sound_fade.sequence_mode | saturn_sound_fade.sequence_level) << 24;
}

static void effect(u32 id, u8 sequence, u8 channel, s8 group, u8 pan_mode, s8 priority)
{
    struct SaturnSoundEffect* e = &saturn_sound_effects[id];
    e->sequence = sequence;
    e->channel = channel;
    e->group = group;
    e->volume = 0x70;
    e->pan_mode = pan_mode;
    e->priority = priority;
    e->map = 3;
}

static void dispatch_pan(void)
{
    setup();
    effect(8, 1, 2, 1, 0, 5);
    effect(9, 1, 3, 1, 1, 5);
    saturn_sound_output = 0;
    saturn_sound_mix_count = 0;
    saturn_sound_dispatch(2, 8, 5);
    saturn_sound_dispatch(2, 8, 40);
    saturn_sound_dispatch(2, 9, 5);
    saturn_sound_mix_count = 3;
    saturn_sound_output = 0x80;
    saturn_sound_dispatch(2, 8, 5);
    saturn_sound_mix_count = 17;
    saturn_sound_dispatch(2, 8, 6);
}

static void dispatch_status(void)
{
    u32 i;
    setup();
    effect(8, 1, 2, 1, 0, 5);
    effect(10, 1, 4, 1, 0, 5);
    for (i = 0; i < SATURN_SOUND_SEQUENCES; i++)
        *(u16*)&sequences[i * 2] = i == 2 ? 0x0300 : 0;
    saturn_sound_dispatch(4, 8, 0);
    saturn_sound_dispatch(4, 10, 0);
    saturn_sound_dispatch(8, 8, 0);
    saturn_sound_dispatch(8, 10, 0);
    saturn_sound_dispatch(5, 8, 1);
    saturn_sound_dispatch(6, 8, 0x50);
    saturn_sound_dispatch(7, 8, 0);
    saturn_sound_dispatch(15, 8, 2);
    saturn_sound_dispatch(16, 8, 3);
    saturn_sound_dispatch(18, 8, 0);
    saturn_sound_dispatch(19, 8, 0);
    saturn_sound_dispatch(22, 8, 0);
    results = saturn_sound_effect_mode | saturn_sound_fade.stream_mode << 8 | (u16)saturn_sound_fade.stream_step << 16;
    saturn_sound_dispatch(23, 8, 0);
    results ^= saturn_sound_fade.sequence_mode << 4;
}

static void driver_requests(void)
{
    setup();
    effect(8, 1, 2, 1, 0, 5);
    saturn_sound_requests[0].kind = 22;
    saturn_sound_requests[0].id = 8;
    saturn_sound_requests[1].kind = 18;
    saturn_sound_requests[1].id = 8;
    saturn_sound_request_write = 2;
    saturn_music_request(23, 8, 0, 0);
    results = saturn_sound_request_read | saturn_sound_request_write << 8 | saturn_sound_effect_mode << 16;
}

static void (*const sound_cases[])(void) = {
    dispatch_pan,
    dispatch_status,
    driver_requests,
    status_sweeps,
    output_modes,
    sequence_fades,
};

#define WORDS 6
static const u32 sound_expected[][WORDS] = {
#include "platform_sound_expected.inc"
};

static u32 sound_run(u32 row)
{
    u32 observed[WORDS];
    u32 i, sum = 0, used = 0;
    results = 0xFFFF;
    sound_cases[row]();
    for (i = 0; i < sizeof(queue); i += 2) {
        u16 half = queue[i] << 8 | queue[i + 1];
        sum = sum * 31 + half;
        used += half != 0;
    }
    observed[0] = results;
    observed[1] = sum;
    observed[2] = used | (u32)(saturn_sound_command_slot - queue) << 16;
    observed[3] = driver[0x60] | saturn_sound_command_lock << 8 | saturn_sound_driver_busy << 16;
    observed[4] = 0;
    for (i = 0; i < SATURN_SOUND_SEQUENCES; i++)
        observed[4] = observed[4] * 7 + saturn_sound_channel_effects[i];
    observed[5] = saturn_sound_fade.sequence_mode | saturn_sound_fade.sequence_level << 16;
    return c_test_observe(0, row, observed, sound_expected[row], WORDS);
}

const struct CTestGroup c_test_groups[] = {
    { "saturn_sound", 0, 0, COUNT(sound_cases), sound_run },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(sound_cases);
