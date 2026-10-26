#include "common.h"
#include "saturn/platform.h"
#include "saturn/game_low.h"
#include "saturn/player_resources.h"
#include "saturn/weapon_resources.h"
#include "archive_memory.h"

u16 web_spider_arena_x;

u16 web_spider_arena_y;

struct ObjectHeader* D_80139690;

u16 saturn_title_window_backup[16];

s32 D_801396B8;

s32 D_801396BC;

struct MiscObj* D_801396C0;

struct MiscObj* D_801396C4;

u8 saturn_demo_return;

u8* D_8013B80C;

s8 D_8013B810;

u8 D_8013B814;

struct MiscObj* D_8013B808;

u32 D_801396C8[61];

struct MiscObj* D_801397BC;

struct MiscObj* D_801397C0;

struct MiscObj* D_801397C4;

struct MiscObj* D_801397C8;

struct MiscObj* D_801397CC;

struct MiscObj* D_801397D0;

struct MiscObj* D_801397D4;

u8 D_801397D8;

struct Func80022730Config* D_801397DC;

s16 D_801397E0;

u16 D_801397E4[0x20];

u8 D_80139824;

u8 D_80139828;

u8 saturn_dialogue_flags;

struct Unk_unk68* D_8013B828;

struct Unk_unk68* D_8013B82C;

struct Unk_unk68* D_8013B830;

struct Unk_unk68* D_8013B834;

u8 jet_stingray_bubble_index;

s16 magma_dragoon_arena_right;

s16 magma_dragoon_arena_center;

s16 magma_dragoon_arena_left;

s16 magma_dragoon_arena_floor;

s16 magma_dragoon_arena_ceiling;

u16 D_8013B858[0x10];

s16 D_8013B878[0x10];

u8 D_8013B898;

u8 D_8013B89C;

u8 D_8013B8A0;

u8 D_8013B8A4;

struct ObjectHeader* D_8013B8A8;

struct EffectObj* sigma_sequencer;

struct Unk_unk68* D_8013B8B0;

void* D_8013B8B4;

u8 D_8013B8B8;

struct ShotObj* general_fists[2];

u8 D_8013B8DC[1];

s16 D_8013B8C8;

s16 D_8013B8CC;

u8 D_8013B8D0[1];

u8 D_8013B8E0;

u8 D_8013B8E4;

struct EffectObj* boss_warning_tiles[22];

u16 D_8013B940[16];

u8 D_8013B960;

u8* saturn_error_context;

u8 saturn_reset_flag_a;

u8 saturn_title_skip;

u8 saturn_backup_cart_status;

volatile u32 saturn_soft_reset_request;

volatile u32 saturn_peripheral_result;

u32 saturn_peripheral_attempts;

u32 saturn_smpc_attempts;

u16 saturn_debug_register_save[144];

u32 saturn_debug_dump_address;

u32 saturn_debug_vram_save;

u32 saturn_debug_query_attempts;

volatile s32 saturn_debug_query_result;

u32 saturn_debug_reset_request;

volatile u16 saturn_vdp1_group_start;

s32 saturn_debug_column;

s32 saturn_debug_row;

s32 saturn_debug_margin;

s32 saturn_debug_top;

u8 saturn_transfer_lock;

void* saturn_transfer_saved_handler;

volatile u8 saturn_transfer_join;

volatile u8 saturn_transfer_join_secondary;

u32 saturn_transfer_primary[240];

u32 saturn_transfer_profiles[320];

u8 saturn_transfer_command_count;

u8 saturn_transfer_profile_count;

u32 saturn_transfer_secondary[240];

u8 saturn_transfer_command_count_secondary;

u8 saturn_transfer_profile_count_secondary;

volatile u8* saturn_sound_driver_header;

volatile u8* saturn_sound_command_queue;

volatile u8* saturn_sound_driver_area;

volatile u8* saturn_sound_command_slot;

volatile u8* saturn_sound_table_d8;

volatile u8* saturn_sound_sequence_table;

volatile u8* saturn_sound_table_e0;

volatile u8* saturn_sound_table_e4;

volatile u8* saturn_sound_pcm_table;

volatile u8* saturn_sound_table_ec;

u8* saturn_sound_driver_buffer;

u16 saturn_sound_driver_bytes;

u8* saturn_sound_map_buffer;

u16 saturn_sound_map_bytes;

s32 saturn_sound_command_lock;

u16 saturn_sound_effect_data[2];

u16 saturn_sound_channel_effects[SATURN_SOUND_SEQUENCES];

u16 saturn_music_thread_track;

u16 saturn_music_thread_arg;

u16 saturn_music_thread_active;

u8 saturn_stream_error_object[6];

s32 saturn_boot_state;

s32 saturn_boot_substate;

s32 saturn_boot_timer;

u8 saturn_save_icons[3][24];

u8* saturn_save_box_objects;

u8* saturn_save_cursor;

u16 saturn_save_cursor_rows[4];

u8 saturn_save_draw_mode;

u8 saturn_save_device;

s8 saturn_save_slot;

u8 saturn_save_selection;

s16 saturn_fade_out_step;

u16 saturn_background_staging_offset;

u16 saturn_background_tile_column;

u16 saturn_background_tile_row;

u32 saturn_background_run_destination;

u32* saturn_background_staging_cursor;

u8 saturn_background_staging[1656];

u16* saturn_background_tile_source;

u16 saturn_background_run_start;

u8 saturn_background_run_state;

u16 saturn_background_run_bytes;

volatile u16 saturn_sprite_palette_group;

u32 saturn_background_scroll_word;

u8 saturn_player_part[80];

struct SaturnHudSprite saturn_hud_sprite;

s16 saturn_hud_color;

struct SaturnHudOffsets saturn_hud_offsets;

s16 saturn_color_offset_saved[6];

u8 saturn_archive_indicator_state;

volatile s32 saturn_cd_access_mode;

volatile s32 saturn_cd_transferred_bytes;

u8 saturn_cd_status[12];

u16 saturn_pause_palette_save[512];

u16 saturn_pause_shadow_save[144];

u8 saturn_pause_sprite_counts_save[20];

u32 saturn_pause_sprite_lists_save[160];

u8 saturn_pause_player_visible;

struct MainBssState main_bss_state;

struct GameInfo game_info;

struct EngineObj engine_obj;

struct PlayerObj g_Player;

struct PlayerObj g_Entity;

struct UnkObj foo_objects[3];

struct BazObj baz_objects[2];

struct MainObj main_objects[0x30];

struct WeaponObj weapon_objects[0x10];

struct ShotObj shot_objects[0x20];

struct VisualObj visual_objects[0x20];

struct BackgroundObj background_objects[3];

struct EffectObj effect_objects[0x20];

struct ItemObj item_objects[0x20];

struct MiscObj misc_objects[0x40];

struct LayerObj layer_objects[4];

struct QuadObj g_QuadObjects[0x20];

struct RideArmorObj qux_object;

struct BarObj bar_object;

struct AbcObj abc_object;

struct UnkObj unk_objects[UNK_OBJECT_COUNT];

u16 saturn_color_ram[2048];

u8 need_palette_load;

u16 g_FilterAmountR;

u16 g_FilterAmountG;

u16 g_FilterAmountB;

s32 D_8013E188[4];

u8 g_FilterModeR;

u8 g_FilterModeG;

u8 g_FilterModeB;

u8 D_80171EA8;

s8 D_80173C6C[4];

u8 layout_width;

u8 layout_height;

u16 layout_size;

u32* saturn_stage_graphics_offsets_pointer;

u16 cur_random;

u8 saturn_movie_active;

u16 saturn_vblank_count;

volatile u16 saturn_frame_request;

volatile u16 saturn_frame_ready;

volatile u16 saturn_peripheral_ready;

volatile u16 saturn_vdp1_phase;

u16 saturn_sprite_pending;

volatile u16 saturn_vdp1_submitted_phase;

u16 saturn_present_inhibit;

u16 saturn_vdp1_ticks;

u16 saturn_vdp1_end_tick;

u8 saturn_soft_reset_mode;

volatile u8 saturn_reset_inhibit;

s16 saturn_fade_level_b;

u16 saturn_screen_width;

u16 saturn_screen_height;

u16 saturn_vdp1_uploaded_pending;

u32 saturn_archive_queue[17];

u8* volatile saturn_peripheral_record;

u8* saturn_peripheral_data;

u8* saturn_peripheral_work;

u8 saturn_smpc_parameters[500];

u8 saturn_controller_refresh;

struct SaturnPad saturn_pads[2];

u16 saturn_pause_request;

u16 saturn_pause_latch;

u8 saturn_sound_peak;

u16 saturn_sound_level;

volatile s8 saturn_sprite_list_counts[20];

volatile u32 saturn_sprite_object_lists[768];

volatile u8 saturn_frame_dma_pending;

volatile u32 saturn_frame_dma_count;

volatile u32 saturn_frame_dma_arg_0;

volatile u32 saturn_frame_dma_arg_1;

u32 saturn_gfx_job[1];

u32 saturn_gfx_source;

u32 saturn_gfx_destination;

u8 saturn_save_slots[38];

u16 saturn_save_checksum;

volatile u16 saturn_vdp1_link_slots[16];

volatile u16 saturn_vdp1_saved_link;

u16 saturn_sprite_command_count;

volatile u8 saturn_vdp1_active_group;

u8 saturn_sprite_commands[32768];

volatile u16 saturn_sprite_pass_count;

u16 saturn_vdp1_frame_started;

volatile u32 saturn_gfx_staging_cursor;

u16 saturn_vdp2_shadow[77];

u16 saturn_background_redraw_word;

u16 saturn_vdp2_shadow_copy[144];

u8 saturn_vdp2_ram_control_config[6];

u8 saturn_color_ram_pending;

u16 saturn_color_ram_copy[2562];

u8 saturn_text_dirty_a;

u8 saturn_text_dirty_b;

u8 saturn_display_mode;

u8 saturn_gfs_work[3504];

u32 saturn_gfs_dir_table[3];

u8 saturn_gfs_dir_names[6120];

s32 saturn_cd_seek_position[2];

volatile s32 saturn_cd_error;

volatile s32 saturn_cd_file_id;

volatile u32 saturn_cd_handle;

volatile u8 saturn_cd_retries;

u32 saturn_sound_counter;

struct SaturnSoundRequest saturn_sound_requests[SATURN_SOUND_REQUEST_MASK + 1];

struct SaturnSoundRequest saturn_sound_effect_requests[SATURN_SOUND_REQUEST_MASK + 1];

u8 saturn_sound_mode;

u8 saturn_sound_stage_map;

u8 saturn_sound_total_volume;

u8 saturn_sound_mix_count;

u8 saturn_sound_effect_mode;

struct SaturnSoundFade saturn_sound_fade;

u16 saturn_sound_pending_word;

u8 saturn_sound_driver_busy;

u8 saturn_sound_request_read;

u8 saturn_sound_request_write;

u8 saturn_sound_effect_request_read;

u8 saturn_sound_effect_request_write;

s8 saturn_sound_last_group;

u8 saturn_stream_state[33];

u8 saturn_stream_status;

u16 saturn_stream_track;

u16 D_80173C84;

u16 saturn_stream_pitch;

u16 saturn_stream_stereo;

u8 saturn_stm_work[204];

u8 saturn_sound_wait_retries;

s8 D_80141BD0;

u16 saturn_tile_staging_offset;

u16 saturn_tile_column_offset;

u16 saturn_vdp2_field;

u32 saturn_tile_run_destination;

u32* saturn_tile_staging_cursor;

u8 saturn_tile_staging[3072];

u16* saturn_tile_column_high;

u16* saturn_tile_column_low;

u16* saturn_tile_source;

u16 saturn_tile_run_start;

u16 saturn_tile_column_start;

u16 saturn_tile_run_length;

u16 saturn_tile_column;

u16 saturn_tile_row;

u8 saturn_tile_run_state;

u8 saturn_tile_screen_state;

u8 D_8013B7D8;

u8 D_8013B7DC;

s16 D_8013B7E0;

s16 D_8013B7E4;

s16 D_8013B7E8;

s16 D_8013B7EC;

s16 D_8013B7F0;

s16 D_8013B7F4;

s16 D_8013B7F8;

s16 D_8013B7FC;

s16 D_8013B800;

s16 D_8013B804;

u8 D_8013B7D0;

u8 saturn_pause_weapon;

s32 saturn_runtime_error;

u8* saturn_rtc_time;

u8 saturn_smpc_output[12];

u8 saturn_smpc_status;
