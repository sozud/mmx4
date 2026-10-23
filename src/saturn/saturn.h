#ifndef MMX4_SATURN_H
#define MMX4_SATURN_H

#include "common.h"

enum { SATURN_THREAD_COUNT = 6,
    SATURN_THREAD_CONTEXT_BYTES = 64 };

typedef struct {
    u32 state;
    u32 sleep_timer;
    u32 context_argument;
    u32 entry;
    u32 saved_stack_pointer;
    u32 initial_stack_pointer;
} SaturnThread;

void saturn_thread_create_state(volatile SaturnThread* table, u32 slot, u32 entry);
void saturn_thread_suspend_state(volatile SaturnThread* table, u32 slot);
void saturn_thread_resume_state(volatile SaturnThread* table, u32 slot);

void saturn_decompress_gfx(const u16* source, u16* destination);

enum { SATURN_TRANSFER_SLOTS = 80 };

typedef struct {
    u32 byte_length;
    u32 destination;
    u32 source_and_group_end;
} SaturnTransferCommand;

typedef struct {
    u32 add_a;
    u32 add_b;
    u32 attribute_a;
    u32 attribute_b;
} SaturnTransferProfile;

typedef struct {
    SaturnTransferCommand commands[SATURN_TRANSFER_SLOTS];
    SaturnTransferProfile profiles[SATURN_TRANSFER_SLOTS];
    u8 command_count;
    u8 profile_count;
    u8 padding[2];
} SaturnTransferBank;

void saturn_transfer_append(volatile SaturnTransferBank* bank, volatile u8* join,
    u32 source, u32 destination, u32 byte_length);
void saturn_transfer_add_profile(volatile SaturnTransferBank* bank, volatile u8* join,
    u32 add_a, u32 add_b, const u16 attributes[2]);
void saturn_transfer_copy(volatile SaturnTransferBank* primary, volatile u8* primary_join,
    volatile SaturnTransferBank* secondary, volatile u8* secondary_join);

typedef struct {
    u32 destination_id;
    u32 chunks;
    s16 last_bytes;
    s16 first_bytes;
    u32 copy_mode;
} SaturnArchiveRecord;

typedef struct {
    volatile s32* error;
    volatile s32* file_id;
    volatile u32* handle;
    volatile u8* retries;
    volatile u32* metadata_pointer;
    u8* header;
    u8* sector;
    const u32* destinations;
    u32 metadata_destination;
} SaturnArchiveState;

typedef struct {
    s32 (*name_to_id)(const char*);
    u32 (*open)(s32);
    void (*close)(u32);
    s32 (*set_get_mode)(u32, s32);
    void (*file_size)(u32, s32*, s32*, s32*);
    s32 (*set_transfer_mode)(u32, s32);
    s32 (*read_ahead)(u32, s32);
    s32 (*read)(u32, s32, u32, s32);
    void (*start_pending)(u32);
    void (*sleep)(unsigned int);
    u32 (*wait)(u32);
    void (*copy16)(u32, u32, s32);
    void (*copy32)(u32, u32, s32);
    s32 (*dma_result)(void);
    s32 (*fatal)(void);
} SaturnArchiveIO;

s32 saturn_archive_load_state(const SaturnArchiveState*, const SaturnArchiveIO*, const char*, u32 yielding);
void saturn_archive_metadata_state(const SaturnArchiveState*, const SaturnArchiveIO*);

typedef struct {
    volatile s32* error;
    volatile u32* handle;
    volatile u8* retries;
    volatile s32* mode;
    volatile s32* bytes;
} SaturnCdControlState;

typedef struct {
    s32 (*execute)(u32);
    void (*get_status)(u32, volatile s32*, volatile s32*);
    s32 (*stop)(u32);
    s32 (*dump_r4)(s32);
    void (*sleep)(unsigned int);
    void (*close)(u32);
} SaturnCdControlIO;

typedef struct {
    u32 paths[16];
    u8 read_index;
    u8 write_index;
    u8 busy;
    u8 padding;
} SaturnArchiveQueue;

s32 saturn_cd_check_result_state(const SaturnCdControlState*, const SaturnCdControlIO*,
    s32 result, volatile u8* retries, u32 allow_restart);
u32 saturn_cd_wait_state(const SaturnCdControlState*, const SaturnCdControlIO*, u32 yielding);
void saturn_archive_queue_reset_state(volatile SaturnArchiveQueue*);
u32 saturn_archive_queue_push_state(volatile SaturnArchiveQueue*, u32 path);
u32 saturn_archive_queue_pop_state(volatile SaturnArchiveQueue*);
void saturn_archive_queue_cancel_state(volatile SaturnArchiveQueue*, const SaturnCdControlState*,
    const SaturnCdControlIO*, void (*kill)(u32));

enum { SATURN_SPRITE_COMMAND_LIMIT = 960 };
typedef struct {
    u16 words[16];
} SaturnSpriteCommand;
typedef struct {
    volatile SaturnSpriteCommand* commands;
    volatile u16* count;
    volatile u16* pass_count;
    volatile u16* pending;
    volatile u16* palette_group;
    const volatile u8* cameras;
    const volatile u8* hidden_mode;
    const volatile u8* hidden_bits;
} SaturnSpriteState;

void saturn_draw_normal_sprite_state(volatile u8* object, const u8* frame_bank,
    const SaturnSpriteState* state);

typedef struct {
    volatile SaturnSpriteCommand* commands;
    volatile u16* count;
    volatile u16* pending;
    volatile u16* uploaded_pending;
    volatile u16* link_slots;
    const volatile u16* local_x;
    const volatile u16* local_y;
    u32 video_commands;
} SaturnVdp1State;
typedef struct {
    void (*copy_bytes)(u32 destination, u32 source, u32 bytes);
    u32 (*result)(void);
} SaturnVdp1IO;

void saturn_vdp1_init_state(const SaturnVdp1State*);
void saturn_vdp1_upload_state(const SaturnVdp1State*, const SaturnVdp1IO*);

typedef struct {
    volatile SaturnSpriteCommand* commands;
    volatile u16* count;
    volatile u16* link_slots;
    volatile u16* saved_link;
    volatile u8* active_group;
    volatile u16* group_start;
    u32 video_commands;
} SaturnVdp1GroupState;
typedef struct {
    const volatile u16* ticks;
    volatile u16* draw_trigger;
    volatile u16* phase;
    volatile u16* submitted_phase;
} SaturnVdp1PresentState;

void saturn_vdp1_begin_group_state(const SaturnVdp1GroupState*, u32 group);
void saturn_vdp1_end_group_state(const SaturnVdp1GroupState*);
void saturn_vdp1_present_state(const SaturnVdp1PresentState*);

typedef struct {
    const volatile s8* counts;
    const volatile u32* objects;
    u32 channels;
} SaturnSpriteDrawLists;
typedef struct {
    volatile u16* palette;
    const volatile s8* group;
    SaturnSpriteDrawLists lists;
} SaturnSpritePassState;
typedef struct {
    void (*begin)(u32);
    void (*end)(void);
    void (*draw)(u32);
    void (*overlay)(void);
    void (*player)(void);
} SaturnSpritePassIO;
void saturn_sprite_pass_state(const SaturnSpritePassState*, const SaturnSpritePassIO*);
void saturn_sprite_main_pass_state(const SaturnSpritePassState*, const SaturnSpritePassIO*,
    const SaturnSpriteDrawLists* foreground,
    const SaturnSpriteDrawLists* final_lists);

#if defined(__sh__)
__attribute__((noipa, noreturn)) void saturn_main(void);
__attribute__((noipa)) void saturn_main_frame(void);
__attribute__((noipa)) void saturn_platform_initialize(void);
__attribute__((noipa)) void saturn_runtime_initialize(void);
__attribute__((noipa)) void saturn_frame_finish(void);
__attribute__((noipa)) void saturn_frame_wait(void);
__attribute__((noipa)) void saturn_vdp1_init_commands(void);
__attribute__((noipa)) void saturn_vdp1_upload_commands(void);
__attribute__((noipa)) void saturn_vdp1_present(void);

#define SATURN_THREAD_ABI __attribute__((noipa))
extern volatile SaturnThread saturn_threads[SATURN_THREAD_COUNT];
extern volatile SaturnThread* volatile saturn_current_thread;
extern u32 saturn_scheduler_stack_pointer;
u32 saturn_thread_context_prepare(u32 entry, u32 initial_stack, volatile SaturnThread* thread);
void saturn_thread_context_resume(u32 argument);
SATURN_THREAD_ABI void saturn_threads_init(void);
SATURN_THREAD_ABI void saturn_threads_run(void);
SATURN_THREAD_ABI void saturn_thread_create(unsigned int slot, unsigned int entry);
SATURN_THREAD_ABI void saturn_thread_sleep(unsigned int frames);
SATURN_THREAD_ABI void saturn_thread_exit(void);
SATURN_THREAD_ABI void saturn_thread_kill(u32 slot);
SATURN_THREAD_ABI void saturn_thread_kill_all(void);
SATURN_THREAD_ABI void saturn_thread_suspend(u32 slot);
SATURN_THREAD_ABI void saturn_thread_resume(u32 slot);
SATURN_THREAD_ABI void saturn_thread_restart(u32 entry);

extern const u16* saturn_gfx_source;
extern u16* saturn_gfx_destination;
void saturn_decompress_gfx_job(void);

extern volatile SaturnTransferBank saturn_transfer_primary;
extern volatile SaturnTransferBank saturn_transfer_secondary;
extern volatile u8 saturn_transfer_join;
extern volatile u8 saturn_transfer_join_secondary;
extern const u16 saturn_transfer_attributes[][2];
void saturn_transfer_enqueue(u32 source, u32 destination, u32 byte_length);
void saturn_transfer_profile(u32 add_a, u32 add_b, unsigned attribute_index);
void saturn_transfer_enqueue_secondary(u32 source, u32 destination, u32 byte_length);
void saturn_transfer_profile_secondary(u32 add_a, u32 add_b, unsigned attribute_index);
void saturn_transfer_use_secondary(void);

extern u8 saturn_archive_header[2048];
extern u8 saturn_archive_sector[2048];
SATURN_THREAD_ABI s32 saturn_archive_load_yielding(const char* path);
SATURN_THREAD_ABI s32 saturn_archive_load_blocking(const char* path);
void saturn_archive_metadata(void);
u32 saturn_cd_wait(u32 yielding);
s32 saturn_cd_check_result(s32 result, volatile u8* retries, u32 allow_restart);
void saturn_archive_queue_reset(void);
void saturn_archive_queue_cancel(void);
void saturn_archive_queue_push(const char* path, u32 suppress_indicator);
void saturn_archive_queue_worker(void);
void saturn_archive_start_indicator(void);
void saturn_draw_normal_sprite(volatile u8* object);
SATURN_THREAD_ABI void saturn_vdp1_init_commands(void);
SATURN_THREAD_ABI void saturn_vdp1_upload_commands(void);
SATURN_THREAD_ABI void saturn_vdp1_begin_group(u32 group);
SATURN_THREAD_ABI void saturn_vdp1_end_group(void);
SATURN_THREAD_ABI void saturn_vdp1_present(void);
SATURN_THREAD_ABI void saturn_sprite_draw_passes(void);
SATURN_THREAD_ABI void saturn_sprite_draw_main_pass(void);
SATURN_THREAD_ABI void saturn_sprite_draw_pass_1(void);
SATURN_THREAD_ABI void saturn_sprite_draw_pass_2(void);
SATURN_THREAD_ABI void saturn_sprite_draw_pass_3(void);
#endif

#endif
