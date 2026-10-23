#ifndef MMX4_SATURN_PLATFORM_H
#define MMX4_SATURN_PLATFORM_H

#ifndef MMX4_SHC
static inline u32 _builtin_get_cr(void)
{
    u32 sr;
    __asm__ volatile("stc sr,%0" : "=r"(sr));
    return sr;
}

static inline void _builtin_set_cr(u32 sr)
{
    __asm__ volatile("ldc %0,sr" : : "r"(sr) : "memory");
}
#endif

#define SATURN_SOUND_SEQUENCES 8
#define SATURN_SOUND_SLOT_BYTES 16
#define SATURN_SOUND_REQUEST_MASK 31
#define SATURN_SOUND_EFFECT_COUNT 0x207

struct SaturnSoundStatus {
    u16 command;
    u8 value;
};

struct SaturnSoundPcmState {
    u8 mode;
    u8 value;
};

struct SaturnSoundPcmStart {
    u8 mode;
    u8 padding;
    u16 address;
    u16 size;
};

struct SaturnSoundPcmParam {
    u8 number;
    u8 level;
    u8 pitch_padding[2];
    u16 pitch;
    u8 effect_route;
    u8 effect_level;
    u8 filter_route;
    u8 filter_level;
};

struct SaturnSoundFade {
    s16 sequence_step;
    s16 stream_step;
    u16 sequence_level;
    u16 stream_level;
    u16 sequence_mode;
    u16 stream_mode;
};

struct SaturnSoundRequest {
    s16 id;
    s16 kind;
    s16 pan;
};

struct SaturnSoundEffect {
    u8 sequence;
    u8 channel;
    s8 group;
    u8 volume;
    u8 pan_mode;
    s8 priority;
    u8 map;
    u8 padding;
};

extern volatile u8* saturn_sound_command_queue;
extern volatile u8* saturn_sound_driver_area;
extern volatile u8* saturn_sound_command_slot;
extern volatile u8* saturn_sound_sequence_table;
extern volatile u8* saturn_sound_pcm_table;
extern s32 saturn_sound_command_lock;
extern u16 saturn_sound_channel_effects[SATURN_SOUND_SEQUENCES];
extern u8 saturn_sound_driver_busy;
extern struct SaturnSoundFade saturn_sound_fade;
extern u16 saturn_stream_pitch;
extern u16 saturn_stream_stereo;
extern u16 saturn_stream_active;
extern u16 saturn_stream_mode;
extern u8 saturn_stream_status;
extern u8 saturn_sound_stage_map;
extern u8 saturn_sound_mode;
extern u16 saturn_sound_pending_word;
extern u8 saturn_sound_total_volume;
extern s8 saturn_sound_last_group;
extern struct SaturnSoundRequest saturn_sound_requests[SATURN_SOUND_REQUEST_MASK + 1];
extern u8 saturn_sound_request_read;
extern u8 saturn_sound_request_write;
extern struct SaturnSoundRequest saturn_sound_effect_requests[SATURN_SOUND_REQUEST_MASK + 1];
extern u8 saturn_sound_effect_request_write;
extern struct SaturnSoundEffect saturn_sound_effects[SATURN_SOUND_EFFECT_COUNT];
extern u8 saturn_sound_stage_maps[];
extern s16 saturn_sound_kind_bases[];
extern u8 saturn_sound_mix_default;
extern s8 saturn_sound_pan_table[];
extern s8 saturn_sound_mix_table[];
extern s16 saturn_sound_tempos[];
extern s32 saturn_sound_fade_steps[];
extern u16 saturn_sound_effect_data[2];
extern u8 saturn_sound_mix_count;
extern u8 saturn_sound_effect_mode;
extern u8 saturn_sound_output;
extern u32 saturn_sound_counter;
extern u8 saturn_stream_state[];
extern u16 saturn_stream_track;
extern u8* volatile saturn_peripheral_record;
extern u8 saturn_sound_effect_request_read;
extern u16 saturn_music_thread_track;
extern u16 saturn_music_thread_arg;
extern u16 saturn_music_thread_active;

u8 saturn_sound_wait_ready(void);
void saturn_sound_dispatch(s32 kind, s32 id, s32 pan);
void saturn_sound_key_mask(u8 enable);
void saturn_stream_close(void);
void saturn_music_thread(void);
void saturn_thread_create(u32 slot, u32 entry);

u8 saturn_sound_next_slot(void);
void saturn_sound_enable_sequences(void);
u8 saturn_sound_change_map(u8 map);
u8 saturn_sound_set_total_volume(u8 volume);
u8 saturn_sound_set_effect(u8 effect);
u8 saturn_sound_set_mix(u8 mix, u8 level);
u8 saturn_sound_set_mix_param(u8 number, u8 level, u8 pan);
u8 saturn_sound_cut_all(void);
u8 saturn_sound_disable_sequences(void);
u8 saturn_sound_seq_start(u8 sequence, u8 bank, u8 song, u8 priority);
u8 saturn_sound_seq_stop(u8 sequence);
u8 saturn_sound_seq_pause(u8 sequence);
u8 saturn_sound_seq_continue(u8 sequence);
u8 saturn_sound_seq_volume(u8 sequence, u8 volume, u8 fade);
u8 saturn_sound_seq_tempo(u8 sequence, s16 tempo);
u8 saturn_sound_seq_control(u8 sequence, u8 high, u8 low);
u8 saturn_sound_cdda_level(u8 left, u8 right);
u8 saturn_sound_cdda_pan(u8 left, u8 right);
void saturn_sound_seq_status(struct SaturnSoundStatus* status, u8 sequence);
void saturn_sound_clear_stopped_effects(void);
s16 saturn_sound_seq_state(u8 sequence);
void saturn_sound_pause_playing(void);
void saturn_sound_continue_paused(void);
void saturn_sound_stop_sequences(void);
void saturn_sound_mute_playing(void);
void saturn_sound_set_playing_volume(u8 volume);
void saturn_sound_pcm_status(struct SaturnSoundPcmState* state, u8 number);
u8 saturn_stream_pcm_start(void);
u8 saturn_sound_pcm_start(struct SaturnSoundPcmStart* start, struct SaturnSoundPcmParam* param);
void saturn_music_stop(void);
void saturn_music_stop_paced(void);
void saturn_thread_sleep(u32 frames);
void saturn_thread_exit(void);
u8 saturn_sound_pcm_stop(u8 number);
u8 saturn_sound_pcm_change(struct SaturnSoundPcmParam* param, u8 level);
u8 saturn_sound_pcm_change_now(struct SaturnSoundPcmParam* param);
u8 saturn_stream_pcm_stop(void);
void saturn_stream_pcm_restart(void);
u8 saturn_stream_ready(void);
u8 saturn_stream_set_volume(u8 volume);
struct SaturnStreamTrack {
    u8 padding0;
    u8 volume;
    u16 stereo;
    u8 padding1[4];
    s32 loop;
    char* name;
    u8 padding2[12];
    char* name_right;
};
extern struct SaturnStreamTrack saturn_stream_track_info;
void saturn_sound_update_fades(void);
void saturn_stream_reset(void);
void saturn_sound_effect_status(u16 effect);
void saturn_sound_set_mix_params(u8 count, u8 level, u8 pan, u8 enable);
u8 saturn_sound_send_command(u8 command, u8 slot, u16* data);
void saturn_stage_select_sound(void);
void saturn_stage_sound_finalize(void);
void saturn_sound_change_map_quiet(u8 map);
void saturn_music_request(s32 kind, s32 id, s32 pan, s32 unused);
s32 func_8001540C(s32 kind, s32 id, void* object);
void saturn_music_play(s32 track, s32 arg);
void saturn_music_start(s32 track, s32 arg);
void saturn_sound_apply_output(u8 output);
void saturn_sound_effect_start(struct SaturnSoundRequest* request);
void saturn_sound_reset_state(void);
void saturn_stage_music_play(void);

struct SaturnPad {
    u8 type;
    u8 id;
    s8 port;
    u8 padding;
    u16 held;
    u16 previous;
    u16 pressed;
    u16 released;
};

extern struct SaturnPad saturn_pads[2];
extern u8* saturn_peripheral_data;
extern u8* saturn_peripheral_work;
extern u8 saturn_controller_refresh;
extern u16 saturn_pause_request;
extern u16 saturn_pause_latch;

void saturn_pad_clear(struct SaturnPad* pad);
void saturn_pad_read(s8 index, struct SaturnPad* pad);
void saturn_controller_select_ports(void);
void saturn_controller_update(void);

struct SaturnScrollPositions {
    s32 nbg0_x;
    s32 nbg0_y;
    s32 nbg0_zoom[2];
    s32 nbg1_x;
    s32 nbg1_y;
    s32 nbg1_zoom[2];
    s16 nbg2_x;
    s16 nbg2_y;
    s16 nbg3_x;
    s16 nbg3_y;
};

extern u16* saturn_player_palette_destination;
extern u16 saturn_vdp2_shadow[];
extern u16 saturn_vdp2_shadow_copy[];
extern u16 saturn_vdp2_default_cycles[];
extern u16 saturn_debug_text_cycles[];
extern u16 saturn_vdp2_field;
extern u8 saturn_display_mode;
extern u16 saturn_color_ram[];
extern u16 saturn_color_ram_copy[];
extern u8 saturn_color_ram_pending;
extern s16 saturn_vdp1_local_x;
extern s16 saturn_vdp1_local_y;
extern struct SaturnScrollPositions saturn_scroll_positions;
extern u8 saturn_debug_text[];
extern s32 saturn_debug_column;
extern s32 saturn_debug_row;
extern s32 saturn_debug_margin;
extern s32 saturn_debug_top;
extern s32 saturn_debug_text_attribute;
extern u8 saturn_transfer_command_count;
extern u8 saturn_transfer_profile_count;
extern u8 saturn_transfer_command_count_secondary;
extern u8 saturn_transfer_profile_count_secondary;

void saturn_vdp2_init_sprite_control(void);
void saturn_vdp2_init_sprite_priority(void);
void saturn_vdp2_init_bg_priority(void);
void saturn_vdp2_init_sprite_ratio(void);
void saturn_vdp2_init_bg_ratio(void);
void saturn_vdp2_init_color_offset(void);
void saturn_vdp2_shadow_init(void);
void saturn_vdp2_set_ram_control(u8* config);
void saturn_vdp2_set_display(u8 enable);
void saturn_vdp2_set_map_offset(u32 plane, u32 address);
void saturn_vdp2_commit_frame(void);
void saturn_debug_put_tile(s32 column, s32 row, s32 attribute, s32 character);
void saturn_debug_putchar(u8 character);
void saturn_debug_set_cursor(u16 column, u16 row);
void saturn_debug_text_setup(s16 wide, s16 bitmap);
void saturn_transfer_reset_counts(void);
void saturn_vdp2_set_ram_control_stage(u8* config);
void saturn_vdp2_set_char_control(u16 plane, u16 colors, u16 bitmap, u16 size);
void saturn_vdp2_set_cycles(u16* cycles);

struct SaturnHudSprite {
    s16 x;
    s16 y;
    u8 bank;
    u8 frame;
    s16 character_base;
    s16 color;
    s16 padding;
    u8* frames;
};

struct SaturnHudRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 color;
};

struct SaturnHudOffsets {
    s16 x[4];
    s16 y[4];
};

extern s32* saturn_player_resource_section1;
extern struct SaturnHudSprite saturn_hud_sprite;
extern s16 saturn_hud_color;
extern struct SaturnHudOffsets saturn_hud_offsets;
extern u8 saturn_sprite_commands[];
extern u16 saturn_screen_width;
extern u16 saturn_screen_height;
extern u16 saturn_sprite_command_count;
extern u16 saturn_sprite_pending;

void saturn_hud_draw_sprite(struct SaturnHudSprite* sprite);
void saturn_hud_draw_rect(struct SaturnHudRect* rect);
void saturn_hud_update_bar(u8* object, s8 maximum);
void saturn_hud_draw_life(void);
void saturn_hud_draw_x_weapon(void);
void saturn_hud_draw_zero_weapon(void);
void saturn_hud_draw_ride(u8* ride);
void saturn_hud_draw(void);

struct SaturnTextItem {
    u8 column;
    u8 row;
    u16 attribute_high;
    u16 attribute_low;
    u16 padding;
    u8* text;
};

extern struct SaturnTextItem saturn_text_items[];
extern u8 saturn_text_mask_glyph[];
extern u16 saturn_text_table_tiles[];
extern u8 saturn_text_cells[];
extern u8 saturn_text_dirty_a;
extern u8 saturn_text_dirty_b;
extern u8 saturn_save_options[];
extern u16 saturn_button_masks[];

void saturn_text_render(struct SaturnTextItem* item, u32* cells, u32 flags);
void saturn_text_draw_item(u32 index, u32 flags);
void saturn_text_draw_item_on(u32 index, u32 flags, u32 debug_layer);
void saturn_text_clear(u32* cells, u16 width, u16 height);
void saturn_save_capture_options(void);

struct SaturnBackgroundStrip {
    u8* camera;
    s16 column;
    s16 row;
    s16 width;
    s16 height;
};

extern u32 saturn_background_planes[3];
extern u32 saturn_background_tile_planes[3];

void saturn_background_draw_strip(struct SaturnBackgroundStrip* strip);
void saturn_background_redraw(u32 index);
void saturn_background_scroll(u8* camera);
void saturn_background_queue_tile(u8* camera, s32 column, s32 row);
void saturn_background_redraw_queued(u8* camera);
void saturn_background_update(void);
void saturn_background_refresh(void);
void saturn_background_load_layout(void);

void saturn_pause_draw_icon(struct SaturnHudSprite* sprite, u32 index, s16 color);
void saturn_pause_draw_bars(void);
void saturn_pause_draw(void);

struct MemcardSaveSlot;

void saturn_save_capture_slot(void);
void saturn_save_load(struct MemcardSaveSlot* save, s32 mode);
void saturn_save_menu_init(u8* menu);
void saturn_save_menu_message(u8* menu);
void saturn_save_menu_result(u8* menu);

void saturn_vdp2_frame_upload(void);
void saturn_vdp2_set_color_ram_mode(u32 mode);
void saturn_interrupt_vblank_in(void);
void saturn_interrupt_vblank_out(void);
void saturn_interrupt_hblank(void);
void saturn_interrupt_dma(void);

void saturn_peripheral_initialize(void);
void saturn_soft_restart(void);
void saturn_debug_frame(void);
void saturn_debug_restore_screen(void);
void saturn_check_soft_reset(void);
void saturn_debug_error_message(void);
void saturn_fatal_error(void);
s32 saturn_debug_dump_line(u8* address, s32 count, s32 width);
u32 saturn_debug_dump(u32 address, u32 end, u32 count, u32 width);
void saturn_debug_viewer_input(void);
void saturn_debug_dump_registers(u32* context);

u8 saturn_sound_level_analysis(u16* result, u8 channel);
void saturn_sound_set_output(u8 output);
void saturn_vdp2_set_screen_mode(u8 interlace, u8 vertical, u8 horizontal);
u32 saturn_backup_status(void);
u32 saturn_backup_save(u32 device);
u32 saturn_backup_load(u32 device);

void saturn_stream_copy_strided(u32* source, u32* destination, u32 bytes, s32 stride);
void saturn_stream_vblank(void);
void saturn_stream_server(void);
s32 saturn_stream_transfer(void* object, void* stream, s32 sectors);
void saturn_stream_set_exec_group(void* group);
u32 saturn_stream_count_buffers(void);
void saturn_stream_open(u16 track);
void saturn_stream_error(void* object, s32 code);
void saturn_video_start(void);
void saturn_slave_main(void);
void saturn_vdp1_erase_setup(void);
void saturn_stage_commit_video(void);
u32 saturn_transfer_check_busy(void);
void saturn_transfer_unlock(void);
void saturn_background_copy_screen_tiles(void);

struct SaturnTileEffect {
    u8 camera;
    u8 padding0[3];
    u8 flags;
    u8 padding1[7];
    u16* tiles;
};

void saturn_tile_effect_write(struct SaturnTileEffect* effect, u16 column, u16 row, u8 tile);
void saturn_tile_effect_write_alternate(struct SaturnTileEffect* effect, u16 column, u16 row, u8 tile);
void saturn_tile_effect_set(struct SaturnTileEffect* effect, u16 column, u16 row, u8 tile);

void saturn_sound_frame(void);
void saturn_stream_frame(void);

void saturn_transfer_flush(void);
s32 CDC_GetPeriStat(void* status);
s32 CDC_GetHirqReq(void);
void saturn_cd_vblank(void);
void saturn_fade_start_in(void);
void saturn_fade_start_out(void);
void saturn_fade_in(void);
void saturn_fade_out(void);
void saturn_fade_set(s16 select, s16 level);
void saturn_vram_clear_banks(u32 banks);
void saturn_text_layers_clear(u32 layers);
void saturn_update_object_texture(u8* object);
void saturn_color_offset_suspend(void);
void saturn_music_track_setup(u16 track);
void saturn_color_offset_resume(void);
void saturn_loading_draw_title(struct SaturnHudSprite* sprite);
void saturn_loading_draw_status(struct SaturnHudSprite* sprite);
void saturn_loading_draw_prompt(struct SaturnHudSprite* sprite);
void saturn_loading_draw(u32 mode, u32 no_wait);
void saturn_loading_indicator_thread(void);
void saturn_render_frame(void);
void saturn_draw_quad(u8* quad);
void saturn_sprite_draw_object(u8* object);
void saturn_sprite_draw_player(void);
void saturn_sprite_draw_overlay(void);

#endif
