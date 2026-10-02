#include "common.h"

#include <libspu.h>

void SelectACharacterUpdate(struct MiscObj*);
void player_enter_beam_out(struct PlayerObj*);
void caterkiller_check_fall(struct MainObj*);
u8 pod_spawner_player_quadrant(struct MainObj*);
void func_8005ABC0(struct MainObj*, u8);
void wall_crawler_update_surface(struct MainObj*);
void func_80089C7C(struct MainObj*);
void ride_armor_pilot_check_dash(struct MainObj*);
void ride_armor_pilot_set_step(struct BaseObj*, s8);
u8 ride_armor_pilot_update_facing(struct MainObj*);
void ride_armor_pilot_set_jump_speed(struct MainObj*);
void ride_armor_pilot_spawn_dust(struct VisualObj*, u8);
void func_80062AEC(struct MainObj*);
void ride_armor_pilot_stub(struct MainObj*, s32, s32);
void ride_armor_pilot_set_scripted_speed(struct MainObj*);
void ride_armor_pilot_return_to_idle(struct MainObj*);
void ride_armor_pilot_apply_x_speed(struct MainObj*);
void ride_armor_pilot_set_walk_speed(struct MainObj*);
void gravity_switch_flip_objects(void);
void func_800C5210(struct ItemObj*);
void layout_gate_apply_layout(struct ItemObj*);
void layout_gate_check_layout(struct ItemObj*);
void func_800B9354(struct EffectObj*);
void func_800B94B8(struct EffectObj*);
void double_spawn_afterimage(struct MainObj*, s8);
void data_hopper_spawn_item(struct MainObj*);

extern u16 D_800F1868[18];
extern u8 D_800F164C[4];
extern s16 D_800F1650[2];
extern union MainPaletteData D_800F1660;
extern const u32* D_800F2FD4[];
extern const u32* D_8011AFF0[];
extern struct StageObjectMarginData D_800F4334;
extern u16* palette_animator_stage_timings[27];
extern s8** palette_animator_stage_scripts[27];
extern u8 D_800F2B5C[21][12];
extern struct HudSpriteOrigin D_800F30F4[8];
extern struct PlayerGaugePosition D_800F3124[2];
extern u16 D_800F312C[4];
extern s32 search_light_accels[3];
extern u32* D_80137E08;
extern struct Unk_unk68 lemon_hit_box[];
extern struct Unk_unk68 D_80106EF4[];
extern struct Unk_unk68 D_8010871C[];
extern struct Unk_unk68 D_80108720[];
extern struct Unk_unk68 wall_crawler_terrain_box;
extern struct Unk_unk68 D_800FB568;
extern struct Unk_unk68 D_800FB56C;
extern struct Unk_unk68 D_801067F0[];
extern union AnimationStep* wall_crawler_animations[];
extern u8 wall_crawler_debris[];
extern union AnimationStep* thorn_trap_animations[];
extern void* iris_animations[];
extern struct Unk_unk68 D_801035BC;
extern struct Unk_unk68 D_801035C4;
extern struct Unk_unk68 D_801035C8;
extern struct Unk_unk68 D_801035C0;
extern struct Unk_unk68 D_801035CC;
extern struct Unk_unk68 D_80107DFC[];
extern union AnimationStep* falling_rock_d_animations[];
extern u8 breakable_wall_hit_box[4];
extern struct Unk_unk68 D_80108684[];
extern u8 wall_crawler_shot_hit_boxes[8];
extern u8 wall_crawler_shot_terrain_box[4];
extern s8 wall_crawler_shot_spawn_offsets[16];
extern void (*data_hopper_step_funcs[8])();
extern struct Unk_unk68 data_hopper_hurt_box;
extern void* double_animations[31];
extern struct Unk_unk68 double_terrain_box;
extern struct Unk_unk68 double_slide_attack_box;
extern struct Unk_unk68 double_slide_hurt_box;
extern u8 layout_gate_frames[4];
extern s32 layout_gate_unused[4];
extern u8 freeze_blast_tile_patches[4][6];
struct Effect17SpawnRecordPC {
    u16 x;
    u16 y;
    u8 count;
    u8 unused;
};
struct Effect17SpawnGroupPC {
    struct Effect17SpawnRecordPC* records;
    u32 count;
};
extern struct Effect17SpawnGroupPC freeze_blast_spawn_groups[4];
extern u8 dragon_spread_shot_hit_box[4];
extern u8 dragon_spread_shot_large_hit_box[4];
extern u8* dragon_spread_shot_animations[16];
extern s8 D_800FDC40[8];
extern s8 sigma_shot_boxes[10][4];
extern u8 sigma_shot_init_box[4];
extern u8 sigma_fx_x_offsets[4];
extern u8 sigma_fx_y_offsets[4];
extern u8 sigma_fx_cloak_piece_animations[4];
extern s32 sigma_fx_cloak_piece_x_vels[8];
extern s32 sigma_fx_cloak_piece_y_vels[8];
extern struct Unk_unk68 D_80106D74[];
extern struct Unk_unk68 bee_hive_hurt_box;
extern union AnimationStep* bee_hive_animations[8];
extern u8 bee_hive_debris[8];
extern void (*bee_hive_step_funcs[])(struct MainObj*);
extern struct Unk_unk68 D_80103EEC;
extern struct Unk_unk68 D_80103EF8;
extern void (*sigma_cloak_step_funcs[5])();
extern struct Unk_unk68 D_80108204[];
extern struct Unk_unk68 D_801071F4[];
extern struct Unk_unk68 D_800FDA0C[];
extern void (*thorn_trap_step_funcs[10])();
extern u8 D_800FDC28[];
extern u8 D_800FDC30[];
extern u8 D_800FDC34[];
extern u8 D_800FDC38[];
extern u8 D_800FDC3C[];
extern u8 moving_block_terrain_box[4];
extern u8 D_800FD5C8[32];
extern struct Unk_unk68 D_80104914;
extern union AnimationStep* D_80104974[14];
extern struct Unk_unk68 ride_armor_pilot_guard_box;
extern u16 gravity_switch_camera_bounds[16];
extern s32 D_800FA130[2];
extern u8 depth_charge_sink_box[4];
extern u8 depth_charge_boxes[];
extern void (*drone_pod_step_funcs[4])(struct MainObj*);
extern void (*double_step_funcs[6])(struct MainObj*);
extern u8* double_script_table_0[2];
extern void* double_script_table_1[2];
extern s8 ice_shard_offsets[4][2];
extern u8 D_801049B8[20];
extern s16 D_801049CC[12];
extern u8 hopper_switch_box[4];
extern u8 double_ball_boxes[2][4];
extern void (*wall_crawler_step_funcs[])(struct MainObj*);
extern union AnimationStep* pod_spawner_animations[];
extern struct Unk_unk68 D_800FD830[];
extern struct Unk_unk68 D_800FD834[];
extern s16 D_800FD86C[];
extern s16 D_800FD884[];
extern u8 gravity_switch_terrain_box[4];
extern u8 gravity_switch_hit_box[4];
extern struct Unk_unk68 D_80107F84[];
extern void* sigma_animations[];
extern struct Unk_unk68 D_800FCFD4[];
extern struct Unk_unk68 D_800FCFE4[];
extern struct Unk_unk68 D_800FCFF4[];
extern struct Unk_unk68 D_800FD004[];
extern struct Unk_unk68 D_800FD014[];
extern struct Unk_unk68* D_800FD018[];
extern struct Unk_unk68* D_800FD048[];
extern struct Unk_unk68* D_800FD04C[];
extern u8 caterkiller_debris[];
extern void (*caterkiller_step_funcs[])(struct MainObj*);
extern union AnimationStep* caterkiller_animations[];
extern u8 eregion_fireball_hit_box[];
extern u8 eregion_fireball_terrain_box[];
extern u8 eregion_wing_slash_hit_box[];
extern s8 eregion_part_offsets_left[58][2];
extern s8 eregion_part_offsets_right[58][2];
extern s8 eregion_part_offsets_center[58][2];
extern void (*eregion_part_funcs[])(struct VisualObj*);
extern union AnimationStep* D_800FADD0[];
extern const u8* magma_dragoon_animations[38];
extern struct Unk_unk68 D_80107D7C[];
extern u8 magma_dragoon_arena_right[4];
extern u8 magma_dragoon_arena_left[4];
extern void (*magma_dragoon_step_funcs[14])(struct MainObj*);
extern u32 D_800FA734;
extern union AnimationStep* hover_sentry_animations[];
extern struct Unk_unk68 D_800FB684;
extern struct Unk_unk68 D_800FB688;
extern struct Unk_unk68 D_800FB68C;
extern struct Unk_unk68 D_800FB690;
extern struct Unk_unk68 D_800FB694;
extern struct Unk_unk68 D_800FB698;
extern struct Unk_unk68 D_800FB69C;
extern struct Unk_unk68 D_800FB6A0;
extern struct Unk_unk68 D_800FB6A4;
extern struct Unk_unk68 D_80106870[];
extern void* common_effect_animations[];
extern union AnimationStep* trident_mech_animations[];
extern struct Unk_unk68 D_800FBBC8;
extern struct Unk_unk68 D_80106A74[];
extern u8 trident_shot_flash_box[4];
extern u8 trident_shot_hit_box[4];
extern s8 trident_shot_muzzle_offsets[6][2];
extern union AnimationStep* surface_hopper_animations[];
extern struct Unk_unk68* D_800FC744[2];
extern struct Unk_unk68* D_800FC74C[2];
extern struct Unk_unk68 D_80106BF4[];
extern u8 surface_hopper_debris[8];
extern void (*surface_hopper_step_funcs[])(struct MainObj*);
extern u8 D_800FC7D4[4];
extern u8 D_800FC7D8[4];
extern s16 D_800FC7E8[6];
extern u8 enemy_bullet_hit_box[4];
extern u8 spike_crawler_debris[4];
extern u8 light_capsule_terrain_box[4];
extern u8 light_capsule_part_bits[8];
extern u8 light_capsule_part_animations[8];
extern u8 light_capsule_part_visuals[8];
extern void* light_capsule_animations[14];
extern s8 D_800FE944[4];
extern s8 D_800FE948[4];
extern s8 D_800FE94C[4];
extern union AnimationStep* falling_ceiling_animations[4];
extern u8 D_800FD89C[16];
extern void* ride_armor_pilot_animations[31];
extern struct Unk_unk68 ride_armor_pilot_terrain_box;
extern u8 jet_stingray_flyby_animations[];
extern struct Unk_unk68 jet_stingray_flyby_attack_box;
extern struct Unk_unk68 jet_stingray_flyby_hurt_box;
extern struct Unk_unk68 D_80107978[];
extern struct Unk_unk68 D_80107AF8[];
extern struct Unk_unk68 beam_drone_hit_box;
extern u8 turret_laser_full_beam_box[4];
extern u8* turret_laser_beam_boxes[12];
extern struct Unk_unk68 ride_armor_pilot_debris[2];
extern void (*ride_armor_pilot_step_funcs[12])(struct MainObj*);
extern struct Unk_unk68 beam_drone_debris;
extern void (*beam_drone_step_funcs[6])(struct MainObj*);
extern struct Unk_unk68 anchored_mine_hurt_box;
extern struct Unk_unk68 anchored_mine_attack_box;
extern union AnimationStep* anchored_mine_animations[2];
extern struct FixedPointPosition D_800FD618[4];
extern struct FixedPointPosition D_800FD638[4];
extern u8 D_800FD5C8[32];
extern struct Unk_unk68* D_800FD5B0[2];
extern struct Unk_unk68* D_800FD5B8[2];
extern struct Unk_unk68* D_800FD5C0[2];
extern void* breakable_panel_animations[7];
extern u8 breakable_panel_terrain_box[4];
extern u32 breakable_panel_hit_box;
struct Item19SpawnPosition {
    u16 x, y;
};
extern struct Item19SpawnPosition data_capsule_positions[4];
extern u8 data_capsule_box_0[4];
extern u8 data_capsule_box_1[4];
extern u8 data_capsule_box_2[4];

struct Effect10Trigger {
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;
    u8 sound_id;
    u8 pad;
};

extern struct Effect10Trigger* sound_zone_lists[2];
u8 player_in_bounds(s16* bounds);

s32 func_800154E8(s32 arg0, s32 arg1, struct BaseObj* source, u8 pan);
s32 func_8002BD58(struct MainObj*, struct MainObj*, s16*, s16*);
s32 func_8002DE30(struct MainObj*, struct WeaponObj*);
s32 func_8002C160(struct CollisionObj*, struct CollisionObj*);
void robot_bee_check_dive(struct MainObj*);
void hover_sentry_face_player(struct MainObj*);
void trident_mech_fire_tracked_shot(struct MainObj*);
u8 surface_hopper_probe_collision(struct PlayerObj*, s16, s16);
u8 surface_hopper_probe_tile(struct PlayerObj*, s16, s16);
u8 surface_hopper_aim_at_player(struct MainObj*);
void spike_crawler_fall(struct MainObj*);
extern struct Unk_unk68 D_80108708[];

struct Effect00BackgroundUpdate {
    u16 object_index;
    u16 value;
};

extern struct Effect00BackgroundUpdate camera_trigger_bound_values[74];
extern u16* camera_trigger_bound_fields[4];

struct EffectSpawnData {
    u8 visual_id;
    s8 effect_type;
    s8 set_facing;
    s8 keep_facing;
    u8 animation_id;
};

extern struct EffectSpawnData D_800F460C[64];
void func_8002DF7C(struct WeaponObj*, s32);
extern u8 drop_item_table[24][6];
extern u8* blast_animations[1];
extern s32 debris_x_speeds[8];
extern s32 debris_y_speeds[8];
extern s32 rubble_x_speeds[8];
extern s32 rubble_y_speeds[8];
extern struct Item02AnimationStep* pickup_animations[11];
extern s8* pickup_hit_boxes[11];

struct PlayerHurtVelocity {
    s32 x_vel;
    s32 x_accel;
    s32 y_vel;
    s32 gravity;
};

extern u8 player_hurt_animations[8];
extern struct PlayerHurtVelocity player_hurt_velocities[5];
extern u8 player_hurt_invincibility[8];
extern union AnimationStep* highway_trooper_animations[27];
extern u8 D_800FFB5C[4];
extern u8 train_soldier_guard_hurt_box[];
extern u8 train_soldier_guard_attack_box[];
extern u32 D_801076F8[];
extern u8 grenade_hit_box[4];
extern u8 grenade_terrain_box[4];
extern s8 grenade_spawn_offsets[8];
extern union AnimationStep* D_800F9934[16];
extern struct Unk_unk68 D_801062F0[32];
void background_dragon_spawn_trail(struct PlayerObj*, s8);
extern void (*background_dragon_step_funcs[13])(struct MainObj*);
extern s16 D_800F98EC[36];
extern u8 background_dragon_attack_map[128];
extern u16 D_800F99BC[4];
extern union AnimationStep* item_carrier_animations[11];
extern u8 item_carrier_capsule_debris[4];
extern struct Unk_unk68* item_carrier_part_hurtboxes[2];
extern u8* item_carrier_part_debris[2];
extern u8 item_carrier_part_debris_counts[4];
extern void (*item_carrier_action_funcs[])(struct MainObj*);
extern struct Unk_unk68 D_801063F0[32];
extern struct Unk_unk68 D_801065F0[];
extern struct Unk_unk68 bulldozer_terrain_box;
extern struct Unk_unk68 bulldozer_hurt_boxes[2];
extern struct Unk_unk68 D_800FA430;
extern struct Unk_unk68 D_800FA434[2];
extern union AnimationStep* D_800FA4E8[16];
extern u8 bulldozer_debris[16];
extern void (*bulldozer_step_funcs[])(struct MainObj*);
extern u8 dragon_shot_flame_box[4];
extern u8 dragon_shot_pulse_hit_box[4];
extern u8 dragon_shot_bomb_box[4];
extern u8 dragon_shot_box_0[4];
extern u8 dragon_shot_box_1[4];
extern u8 dragon_shot_box_2[4];
extern u8 dragon_shot_box_3[4];
extern u8 dragon_shot_box_4[4];
extern u8 dragon_shot_box_5[4];
extern u32* dragon_rubble_animations[14];
extern u8 dragon_rubble_debris[8];
extern u8 dragon_rubble_c_debris_0[8];
extern u8 dragon_rubble_c_debris_1[8];
extern u8 dragon_rubble_c_debris_2[8];
extern s8 death_orb_frames[4];
struct Misc04SpawnPosition {
    u16 x;
    u16 y;
};
extern struct Misc04SpawnPosition dragon_rubble_c_positions[3];
extern struct Item04Data destructible_core_data;
extern u8 destructible_core_boxes[4][4];
extern struct Unk_unk68 D_80108504[];
extern struct Unk_unk68 ambush_gunner_terrain_box;
extern union AnimationStep* ambush_gunner_animations[];
extern union AnimationStep* robot_bee_animations[];
extern struct Unk_unk68 D_800FA100;
extern struct Unk_unk68 D_800FA104;
extern u16 D_80106570[];
extern u8 robot_bee_debris[];
extern void (*robot_bee_step_funcs[])(struct MainObj*);
extern union AnimationStep* stage_cutscene_animations[3];
extern union AnimationStep* D_800FAD68[];
extern u32 D_800FA724;
extern u32 D_800FA728;
extern u32 D_800FA738;
extern u32 D_800FA73C;
extern u32 D_800FA740;
extern u32 D_800FA744;
extern struct Unk_unk68 D_801066F0[];
extern void (*eregion_step_funcs[])(struct MainObj*);
extern s16 stage_select_flyout_targets[8][2];
extern s32 D_800F459C[];
extern s16 frost_walrus_fx_sparkle_offsets[];
void walrus_ice_choose_drop_pattern(struct ShotObj*);
extern s16 walrus_ice_icicle_offsets[2][2];
extern struct Unk_unk68 walrus_ice_ball_terrain_box;
extern s32 D_800F45C0[];
extern u8 boss_warning_quad_blink_levels[16];
void stage_select_flyout_scale(struct QuadObj*);
extern u8 stage_block_boxes[60];
struct PcItem01DebrisPosition {
    s16 x;
    s16 y;
};
extern struct PcItem01DebrisPosition stage_block_spawn_positions[6];
extern u8 falling_pillar_box[4];
extern u8 gunner_shot_hit_box[4];
extern s8 gunner_shot_spawn_offsets[2][2];
extern struct TileEffectRecord** tile_effect_tables[26];
extern u8 D_8013B8E0[];
void func_800DADA0(struct TileEffectRecord*, u16, u16, u8, u8);
s32 func_800157AC(u8 type, s32 unused, struct BaseObj* source);

ret_u8 func_8002938C(s32 id)
{
    const u8* ids = s_StageMainIds[(u8)engine_obj.stage][(u8)engine_obj.substage];
    s32 index = 0;

    while (ids[index] != 0xFF && ids[index] != (u8)id)
        index++;
    return index;
}

s32 func_8001540C(s32 arg0, s32 arg1, void* arg2)
{
    u32 bank = arg0 & 0x7F;
    u32 group = arg0 & 0xF;
    u32 index = arg1 & 0xFF;
    u32* command;
    u32 count;

    if (bank >= COUNT(D_8013E198) || D_8013E198[bank] == -1)
        return -1;
    if (D_80141F50[group] == NULL || D_80141EE8[group] == NULL)
        return -2;
    count = (u32*)D_80141EE8[group] - (u32*)D_80141F50[group];
    if (index >= count)
        return -2;
    command = &((u32*)D_80141F50[group])[index];
    D_80137E08 = command;
    if (*command == 0)
        return -5;
    if (D_800F164C[*(u8*)command >> 6] != 0)
        return func_800157AC(D_800F164C[*(u8*)command >> 6], index, arg2);
    return func_800154E8(arg0 & 0xFF, *(u8*)command & 0x3F, arg2, arg0 & 0xFF);
}

s32 func_800154E8(s32 arg0, s32 arg1, struct BaseObj* source, u8 pan)
{
    VagAtr tone;
    u8 packed1 = ((u8*)D_80137E08)[1];
    u8 packed2 = ((u8*)D_80137E08)[2];
    u8 packed3 = ((u8*)D_80137E08)[3];
    u8 fixed_pan = packed1 >> 7;
    u8 priority = packed2 & 0xF;
    s16 program = packed2 >> 4;
    s16 vag = packed1 & 0x7F;
    s16 voice = packed3 & 0x1F;
    s8 remaining = (packed3 & 0x60) >> 5;

    if (source != NULL) {
        if (arg0 & 0x80) {
            pan = source->unk2;
        } else {
            s16 x = source->x_pos.i.hi;
            s8 background = source->bg_offset;

            if (background >= 0 && background < COUNT(background_objects))
                x -= background_objects[background].x_pos.i.hi;
            pan = x / 10;
            if ((s8)pan < 5)
                pan = 5;
            if ((s8)pan >= 0x1C)
                pan = 0x1B;
        }
    }

    while (remaining-- >= 0) {
        s32 left;
        s32 right;
        u8 voice_index = voice & 0xFF;

        SsUtGetVagAtr(arg1 & 0xFF, vag, program, &tone);
        left = right = tone.vol;
        if (!fixed_pan && source != NULL) {
            if ((s8)pan < 0x10)
                left = (s8)pan * ((u32)left >> 4);
            else if ((s8)pan >= 0x11)
                right = (left >> 4) * (0x20 - (s8)pan);
        }
        if (SpuGetKeyStatus(1u << voice_index) != 0 && priority < D_80139234[voice_index])
            return -4;
        SsUtKeyOnV(voice_index, arg1 & 0xFF, vag, program, tone.min, tone.shift, right, left);
        D_80139234[voice_index] = priority;
        if (++program >= 0x10) {
            vag++;
            program = 0;
        }
        voice++;
    }
    return 0;
}

s32 func_800157AC(u8 type, s32 unused, struct BaseObj* source)
{
    u8 packed1 = ((u8*)D_80137E08)[1];
    u8 packed2 = ((u8*)D_80137E08)[2];
    u8 packed3 = ((u8*)D_80137E08)[3];
    u8 fixed_pan = packed1 >> 7;
    u8 access = packed1 & 0x7F;
    u8 priority = packed2 & 0xF;
    u8 slot = packed2 >> 4;
    u8 current = D_8013924C[slot];
    u8 sequence = packed3 & 0x1F;

    (void)unused;
    (void)source;
    if (current != 0xFF && SsIsEos(access, current & 0x1F)) {
        if (priority < (current >> 5))
            return -1;
        if ((current & 0x1F) == 0x1F)
            SsSeqStop(access);
        else
            SsSepStop(access, current & 0xF);
    }
    if (type == 2) {
        SsSepPlay(access, sequence, SSPLAY_PLAY, D_800F1650[fixed_pan]);
        D_8013924C[slot] = sequence | (priority << 5);
    } else {
        SsSeqPlay(access, SSPLAY_PLAY, D_800F1650[fixed_pan]);
        D_8013924C[slot] = 0x1F | (priority << 5);
    }
    return 0;
}

struct ControllerButtons {
    u16 current;
    u16 previous;
    u16 pressed;
};

struct ControllerButtons D_80166D50;
static u16 decode_pad_buttons(const u8* pad)
{
    u16 buttons;

    if (pad[0] == 0xFF || pad[1] != 0x41)
        return 0;
    buttons = ~((pad[2] << 8) | pad[3]);
    if ((buttons & 0xA000) == 0xA000)
        buttons &= 0x5FFF;
    if ((buttons & 0x5000) == 0x5000)
        buttons &= 0xAFFF;
    return buttons;
}

void func_80012328(void)
{
    u16 buttons;

    mmx4_pc_input_update(pad_port1_packet);
    buttons = decode_pad_buttons(pad_port1_packet);
    controller_input.previous = controller_input.held;
    controller_input.held = buttons;
    controller_input.pressed = buttons & (buttons ^ controller_input.previous);

    buttons = decode_pad_buttons(D_8012F46C);
    D_80166D50.previous = D_80166D50.current;
    D_80166D50.current = buttons;
    D_80166D50.pressed = buttons & (buttons ^ D_80166D50.previous);
}

void func_80016124(void)
{
    SPRT* sprites = D_80139268[SP_DRAW_BUFFER];
    DR_MODE* draw_mode = &D_80139250[SP_DRAW_BUFFER];
    s16 x = 0;
    s16 y = 0;
    s32 i;

    for (i = 0; i < 17; i++) {
        SPRT* sprite = &sprites[i];
        s16 width;

        setSprt(sprite);
        switch (D_800F1868[i]) {
        case 0:
            setUV0(sprite, 0x00, 0xD0);
            width = 0x70;
            break;
        case 1:
            setUV0(sprite, 0x70, 0xD0);
            width = 0x60;
            break;
        case 2:
            setUV0(sprite, 0x00, 0xD0);
            width = 0x10;
            break;
        default:
            abort();
        }

        sprite->clut = 0x784C;
        setWH(sprite, width, 0x30);
        setXY0(sprite, x, y);
        setShadeTex(sprite, 1);
        setSemiTrans(sprite, 0);
        addPrim(&cur_draw_info->ordering_table.ui, sprite);

        x += width;
        if ((u16)x >= 0x140) {
            x = 0;
            y += 0x30;
        }
    }

    SetDrawMode(draw_mode, 0, 0, GetTPage(0, 0, 0x380, 0x100), 0);
    addPrim(&cur_draw_info->ordering_table.ui, draw_mode);
}

s32 func_8002B1E8(struct BaseObj* object, s32 x_margin, s32 y_margin)
{
    s32 x = (u16)object->x_pos.i.hi;
    s32 y = (u16)object->y_pos.i.hi;

    if (object->bg_offset >= 0) {
        x -= (u16)background_objects[object->bg_offset].x_pos.i.hi;
        y -= (u16)background_objects[object->bg_offset].y_pos.i.hi;
    }

    if ((u16)(x + x_margin) >= (u16)(0x140 + 2 * x_margin))
        return 1;
    return (u16)(y + y_margin) >= (u16)(0xF0 + 2 * y_margin);
}

void func_80029A48(void)
{
    static const u16 sequence[] = { 0x20, 0x20, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000 };
    s8* phase = &engine_obj.character_state.fields.secret_code_phase;
    s8* index = &engine_obj.character_state.fields.secret_code_index;
    u16 input = controller_input.pressed;
    u16 held = controller_input.held;

    switch (*phase) {
    case 0:
        *index = 0;
        if (input != 0 && input == sequence[0] && held == input) {
            *index = 1;
            *phase = 1;
        }
        break;
    case 1:
        if (input == 0)
            break;
        if (input != sequence[(u8)*index] || held != input) {
            *phase = 0;
            break;
        }
        if (*index == 7)
            (*phase)++;
        (*index)++;
        break;
    case 2:
        if (input == 0)
            break;
        if (input & (PADstart | PAD_CONFIRM)) {
            u16 expected = sequence[(u8)*index];

            if ((held & expected) == expected)
                engine_obj.unk37 = 1;
        } else if (input & sequence[(u8)*index]) {
            break;
        }
        *phase = 0;
        break;
    }
}

void func_80029BD8(void)
{
    static const u16 sequence[] = { 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x20 };
    s8* phase = &engine_obj.character_state.fields.secret_code_phase;
    s8* index = &engine_obj.character_state.fields.secret_code_index;
    u16 input = controller_input.pressed;
    u16 held = controller_input.held;

    switch (*phase) {
    case 0:
        *index = 0;
        if (input != 0 && input == sequence[0] && held == (input | 8)) {
            *index = 1;
            *phase = 1;
        } else if (input != 0) {
            *phase = 0;
        }
        break;
    case 1:
        if (input == 0)
            break;
        if (input != sequence[(u8)*index] || held != (input | 8)) {
            *phase = 0;
            break;
        }
        if (*index == 5)
            (*phase)++;
        (*index)++;
        break;
    case 2:
        if (held == 0) {
            (*phase)++;
        } else if (input == 0 || !(held & (sequence[(u8)*index - 1] | 8))) {
            *phase = 0;
        }
        break;
    case 3:
        if (input == 0)
            break;
        if (input & (PADstart | PAD_CONFIRM)) {
            u16 expected = sequence[(u8)*index];

            if ((held & expected) == expected)
                engine_obj.unk37 = 1;
        } else if (input & sequence[(u8)*index]) {
            break;
        }
        *phase = 0;
        break;
    }
}

static s32 stage_tile_block(s8 layer, s16 x, s16 y)
{
    s32 block_x = x >> 8;
    s32 block_y = y >> 8;
    s32 index = layer * layout_size + block_y * layout_width + block_x;

    if (block_x < 0 || block_y < 0 || index < 0 || index >= PC_TILEMAP_SIZE)
        return 0;
    return SP_BG_TILEMAP[index];
}

static u8 get_stage_tile_attribute(s8 layer, s16 x, s16 y)
{
    u8 block;
    u16 tile;

    block = stage_tile_block(layer, x, y);
    if (block == 0)
        return 0;
    tile = SP_BG_TILE_PIXELS[block * 0x100 + ((y & 0xF0) >> 4) * 0x10 + ((x & 0xF0) >> 4)];
    return SP_BG_TILE_ATTRS[tile & 0x3FFF] & 0xFF;
}

u8 func_8002D724(struct PlayerObj* object, s16 x, s16 y)
{
    return get_stage_tile_attribute(object->bg_offset, x, y);
}

u8 func_8002D7E4(struct PlayerObj* object, s16 x, s16 y)
{
    u8 block;
    u16 tile;

    block = stage_tile_block(object->bg_offset, x, y);
    if (block == 0)
        return 0;
    object->unk6C = x & 0xF;
    object->unk6E = y & 0xF;
    tile = SP_BG_TILE_PIXELS[block * 0x100 + ((y & 0xF0) >> 4) * 0x10 + ((x & 0xF0) >> 4)];
    return SP_BG_TILE_ATTRS[tile & 0x3FFF] & 0xFF;
}

void func_8002E994(struct EngineObj* arg0)
{
    u16 direction = controller_input.held & 0xF000;
    s8 selection = arg0->unk3;
    s8 next = selection;
    int moved = 0;

    if (direction == PADLup || direction == PADLright || direction == PADLdown || direction == PADLleft) {
        if ((controller_input.held ^ controller_input.pressed) & direction) {
            if (arg0->unk8 != 0) {
                arg0->unk8--;
            } else {
                s16 repeats = arg0->unkA++;
                arg0->unk8 = repeats < 3 ? 0x1E : 0xA;
                if (direction == PADLup) {
                    if ((u8)arg0->unk5F >= 5) {
                        if (selection == 8)
                            next = 0;
                        else if (selection >= 4)
                            next = 8;
                    } else if (selection >= 4) {
                        next = selection - 4;
                    }
                } else if (direction == PADLdown) {
                    if ((u8)arg0->unk5F >= 5) {
                        if (selection == 8)
                            next = 4;
                        else if (selection < 4)
                            next = 8;
                    } else if (selection < 4) {
                        next = selection + 4;
                    }
                } else if (direction == PADLright) {
                    if (selection != 8 && (selection & 3) != 3)
                        next = selection + 1;
                } else {
                    if (selection != 8 && (selection & 3) != 0)
                        next = selection - 1;
                }
                moved = next != selection;
            }
        }
    } else {
        arg0->unk8 = 0;
        arg0->unkA = 0;
    }

    if (moved) {
        arg0->unk3 = next;
        func_8001540C(5, 0, 0);
    }

    if (controller_input.pressed & (PADstart | PAD_CONFIRM)) {
        if (arg0->unk3 == 8) {
            if ((u8)arg0->unk5F < 7) {
                arg0->stage = 0xA;
                arg0->unk40 = arg0->cur_character == 0 ? 0x31 : 0x11;
            } else {
                arg0->stage = (u8)arg0->unk5F < 0xA ? 0xB : 0xC;
                arg0->unk40 = 0x11;
            }
            D_8013B814 = 0;
        } else {
            arg0->unk40 = arg0->cur_character == 0 ? 0x31 : 0x11;
            arg0->stage = mission_stage_order[(u8)arg0->unk3];
            arg0->substage = D_8013B814;
        }
        func_8001540C(5, 1, 0);
        arg0->unk2 = 0;
        arg0->unk1++;
    }
}

extern const u16* D_800F19E0;
extern const u16* D_800F19E4;
extern const u16* D_800F19E8;
extern const u16* D_800F19EC;
extern const u16* D_800F19F0;
extern const u16* D_800F19F4;
extern const u16* D_800F19F8;
extern const u16* D_800F19FC;
extern const u16* D_800F1A00;
extern const u16* D_800F1A04;
extern const u16* D_800F1A08;
extern s16 D_80139560;
extern s32 D_80139538;
extern s32 D_80139540;
extern s32 D_80139544;
s32 func_80013614(s32 arg0, s32* arg1);
void func_80016420(s8 arg0);

void func_8001663C(u8 selection, u8 volume)
{
    const u16* entry;
    u8 index = selection;
    u8 channel = 0;
    s32 start;
    u16 i;

    D_80139568 = 0;
    switch (selection >> 3) {
    case 0:
        D_80139560 = XA_ARCHIVE_BGM1;
        entry = D_800F19E0;
        if (selection == 0)
            D_80139568 = 1;
        break;
    case 1:
        D_80139560 = XA_ARCHIVE_BGM2;
        entry = D_800F19E4;
        index &= 7;
        break;
    case 2:
        D_80139560 = XA_ARCHIVE_BGM3;
        entry = D_800F19E8;
        index &= 7;
        break;
    case 3:
        D_80139560 = XA_ARCHIVE_BGM4;
        entry = D_800F19EC;
        index &= 7;
        break;
    case 4:
        D_80139560 = XA_ARCHIVE_BGM5;
        entry = D_800F19F0;
        index &= 7;
        D_80139568 = 1;
        break;
    case 5:
        D_80139560 = XA_ARCHIVE_VOICE1;
        entry = D_800F19F4;
        index &= 7;
        D_80139568 = 1;
        break;
    case 6:
        D_80139560 = XA_ARCHIVE_VOICE2;
        entry = D_800F19F8;
        index &= 7;
        D_80139568 = 1;
        break;
    case 7:
        D_80139560 = XA_ARCHIVE_VOICE3;
        entry = D_800F19FC;
        index &= 7;
        D_80139568 = 1;
        break;
    case 8:
        D_80139560 = XA_ARCHIVE_VOICE4;
        entry = D_800F1A00;
        index &= 7;
        D_80139568 = 1;
        break;
    case 9:
        D_80139560 = XA_ARCHIVE_VOICE5;
        entry = D_800F1A04;
        index &= 7;
        D_80139568 = 1;
        break;
    case 10:
        D_80139560 = XA_ARCHIVE_BOSS_INTRO;
        entry = D_800F1A08;
        index &= 7;
        D_80139568 = 1;
        break;
    default:
        return;
    }

    for (i = 0; i < index; i++) {
        if (*entry & 0x8000) {
            channel++;
            entry++;
        }
        entry++;
    }

    ((u8*)D_80175EE8)[0] = 1;
    ((u8*)D_80175EE8)[1] = channel;
    start = func_80013614(D_80139560, &D_80139538) + channel;
    D_80139540 = start + ((entry[0] & 0x7FFF) * 8);
    D_80139544 = start + ((entry[1] & 0x7FFF) * 8);
    CdIntToPos(D_80139540, (CdlLOC*)&D_80139514);
    SsSetSerialAttr(0, 0, 1);
    func_80016420(volume);
    D_80141BD4 = 2;
    D_80173C84 = 1;
    D_80139530 = 7;
}

void func_8002217C(u16 message, u8 portrait, u8 delay_only)
{
    struct MiscObj* window;
    u8* window_archive;
    u32 window_frame_offset;
    u16* dialogue_palette;
    u16* messages;

    if (abc_object.unkC != 0) {
        abc_object.unk10 = message | 0x8000;
        if (abc_object.unkC != 0x80) {
            abc_object.unkC = 0x80;
            abc_object.unkA = 0x27;
            abc_object.unkD = 4;
        }
        return;
    }
    abc_object.unkC = 0x80;
    abc_object.unk10 = 0;
    abc_object.unkE = 0;
    D_801397D8 = portrait;
    if (!(portrait & 0x80)) {
        D_801397DC = (struct Func80022730Config*)(D_800F2DD0[(u8)engine_obj.cur_character]
            + portrait * sizeof(struct Func80022730Config));
        if (engine_obj.cur_character == 0) {
            u8 palette_index = ((u8*)D_801397DC)[3];
            u16* portrait_palette = (u16*)((u8*)SP_PALETTE
                + 0x360 + palette_index * 0x80);

            memcpy(portrait_palette, D_800F2F40, sizeof(D_800F2F40));
        }
    }
    D_801397BC = D_801397C0 = D_801397C4 = D_801397C8 = NULL;
    D_801397CC = D_801397D0 = D_801397D4 = NULL;
    if (delay_only) {
        abc_object.unkA = 0x3C;
        abc_object.unkD = 6;
        return;
    }
    D_80139828 = engine_obj.enable_boss;
    D_80139824 = engine_obj.unk1F;
    engine_obj.enable_boss = 0;
    engine_obj.unk1F = 0;
    dialogue_palette = SP_PALETTE + (engine_obj.stage == 0xD ? 0x7C0 / 2 : 0x2A0 / 2);
    memcpy(D_801397E4, dialogue_palette, sizeof(D_801397E4));
    memcpy(dialogue_palette, D_800F1660.dialogue_palette, sizeof(D_800F1660.dialogue_palette));
    messages = (u16*)pc_archive_slots[21];
    abc_object.unk0 = (u16*)((u8*)messages + messages[message]);
    abc_object.unk4 = *abc_object.unk0;
    abc_object.unk6 = -0x78;
    abc_object.unk8 = 0x1D;
    abc_object.unkF = 1;
    abc_object.unkA = 0x27;
    abc_object.unkD = 0;
    D_801397E0 = 0;
    need_palette_load |= 1;
    window = find_free_misc_obj();
    D_801397BC = window;
    if (window != NULL) {
        window_archive = WINDOW_ARCHIVE_DATA;
        memcpy(&window_frame_offset, window_archive + 8, sizeof(window_frame_offset));
        window->active = 1;
        window->id = 0x16;
        window->unk2 = 2;
        window->unk16 = 0x11;
        window->animation_table = (u32**)D_800F2FD4;
        window->unk40 = 0x1E00;
        window->unk42 = engine_obj.stage == 0xD ? 0x78CF : 0x7846;
        window->bg_offset = -1;
        window->x_pos.i.hi = 0xA0;
        window->y_pos.i.hi = (abc_object.unk4 & 0x800)
            ? (portrait == 0xFF ? 0xB4 : 0xAC)
            : (portrait == 0x80 ? 0x74 : 0x3C);
        window->unk3C = window_archive + window_frame_offset;
        window->unk15 = 0;
        set_animation(window, 0);
    }
}

void func_80028690(struct BackgroundObj* bg)
{
    s16 target;
    s16 origin;
    s16 delta;
    s16 next;

    target = bg->unk26;
    if (bg->unk1E != target) {
        origin = bg->x_pos.i.hi;
        if (target >= origin) {
            next = origin + (s8)bg->unk47;
        } else if ((s16)(g_Player.x_pos.i.hi - origin - bg->unk30 + 2) < 5) {
            next = target;
        } else {
            delta = g_Player.x_pos.i.hi - g_Player.unk18.i.hi;
            if (delta >= 0)
                delta = 0;
            next = delta + origin - (s8)bg->unk47;
        }
        bg->unk1E = next < target ? next : target;
    }

    target = bg->unk24;
    if (bg->unk1C != target) {
        origin = bg->x_pos.i.hi;
        if (target < origin) {
            next = origin - (s8)bg->unk47;
            bg->unk1C = next < target ? target : next;
        } else if ((s16)(g_Player.x_pos.i.hi - origin - bg->unk32 + 2) >= 4) {
            bg->unk1C = target;
        } else {
            delta = g_Player.x_pos.i.hi - g_Player.unk18.i.hi;
            if (delta < 0)
                delta = 0;
            next = delta + origin + (s8)bg->unk47;
            bg->unk1C = target < next ? next : target;
        }
    }

    target = bg->unk2A;
    if (bg->unk22 != target) {
        origin = bg->y_pos.i.hi;
        if (target >= origin) {
            next = origin + (s8)bg->unk47;
            bg->unk22 = next < target ? next : target;
        } else {
            next = g_Player.y_pos.i.hi - origin - bg->unk2C + 2;
            if (next < 4) {
                delta = g_Player.y_pos.i.hi - g_Player.unk1C.i.hi;
                if (delta >= 0)
                    delta = 0;
                next = delta + origin - (s8)bg->unk47;
                if (next < target)
                    next = target;
            }
            bg->unk22 = next;
        }
    }

    target = bg->unk28;
    if (bg->unk20 != target) {
        origin = bg->y_pos.i.hi;
        if (target < origin) {
            next = origin - (s8)bg->unk47;
            bg->unk20 = next < target ? target : next;
        } else if ((s16)(g_Player.y_pos.i.hi - origin - bg->unk2E + 2) >= 4) {
            bg->unk20 = target;
        } else {
            delta = g_Player.y_pos.i.hi - g_Player.unk1C.i.hi;
            if (delta < 0)
                delta = 0;
            next = delta + origin + (s8)bg->unk47;
            bg->unk20 = next < target ? next : target;
        }
    }
}

void func_80028FEC(s16 left, s16 right, s16 top, s16 bottom, u8 direction)
{
    struct StageObjectRecord* start;
    struct StageObjectRecord* record;

    if ((u8)engine_obj.stage >= 13 || (u8)engine_obj.substage >= 2)
        abort();
    start = D_800F43C8[engine_obj.stage][engine_obj.substage];
    record = start;
    while (record->object_type != 0xFF) {
        u8 flags = record->flags;
        s16 scan_left = left;
        s16 scan_right = right;
        s16 scan_top = top;
        s16 scan_bottom = bottom;
        s16 x = record->x;
        s16 y = record->y;

        if (!(flags & 0x81)) {
            if (flags & 0x70) {
                u16 margin = D_800F4334.margins[(flags >> 4) - 1];

                if (direction == 1) {
                    scan_left += margin;
                    scan_right += margin;
                }
                if (direction == 2) {
                    scan_left -= margin;
                    scan_right -= margin;
                }
                if (direction == 3) {
                    scan_top += margin;
                    scan_bottom += margin;
                }
                if (direction == 4) {
                    scan_top -= margin;
                    scan_bottom -= margin;
                }
            }
            if (scan_left < x && x < scan_right && scan_top < y && y < scan_bottom) {
                struct ObjectHeader* object = MakeObject(record->object_type);

                if (object != NULL) {
                    u8 index;

                    object->active = 0x41;
                    object->id = record->id;
                    object->unk2 = record->subtype;
                    object->x_pos.i.hi = x;
                    object->y_pos.i.hi = y;
                    object->backref = record;
                    if (record->object_type == 0) {
                        struct MainObj* main = (struct MainObj*)object;

                        index = (u8)func_8002938C(record->id);
                        main->unk40 = D_801406A8[index] >> 7;
                        main->unk42 = SOME_COORDINATE_CONVERSION(index);
                        main->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[index];
                    }
                    record->flags |= 1;
                }
            }
        }
        record++;
    }
}

void func_80028E24(void)
{
    struct BackgroundObj* bg = &background_objects[0];
    s16 old_x = bg->unk14.i.hi;
    s16 x = bg->x_pos.i.hi;
    s16 old_y = bg->unk18.i.hi;
    s16 y = bg->y_pos.i.hi;

    if (old_x != x) {
        if (old_x < x)
            func_80028FEC(x + 0x150, x + 0x170, y - 0x30, y + 0x120, 1);
        else
            func_80028FEC(x - 0x30, x - 0x10, y - 0x30, y + 0x120, 2);
    }
    if (old_y != y) {
        if (old_y < y)
            func_80028FEC(x - 0x30, x + 0x170, y + 0x100, y + 0x120, 3);
        else
            func_80028FEC(x - 0x30, x + 0x170, y - 0x30, y - 0x10, 4);
    }
}

void func_800B5D04(struct EffectObj* arg0)
{
    u32 stage_index;
    s8** animations;
    u16* destinations;
    const s8* animation;
    u16 destination;

    arg0->active = 1;
    stage_index = (u8)engine_obj.stage * 2 + (u8)engine_obj.substage;
    if (stage_index >= COUNT(palette_animator_stage_timings))
        abort();
    animations = palette_animator_stage_scripts[stage_index];
    destinations = palette_animator_stage_timings[stage_index];
    if (animations == NULL || destinations == NULL)
        abort();
    animation = animations[(u8)arg0->unk2];
    arg0->ext.palette_animation.cursor = (s8*)animation;
    if (animation == NULL) {
        despawn_object_permanently(OBJECT_HEADER(arg0));
        return;
    }
    destination = destinations[(u8)arg0->unk2];
    arg0->ext.palette_animation.destination = (s32*)SP_PALETTE + (destination & 0xFF) * 8;
    arg0->ext.palette_animation.source = SP_ARC_30 + (u8)animation[0] * 8;
    arg0->ext.palette_animation.timer = animation[1];
    arg0->ext.palette_animation.palette_count = destination >> 8;
    copy_animated_palette(arg0);
    arg0->state++;
}

void func_800B7EE8(struct EffectObj* arg0)
{
    struct Effect10Trigger* triggers;
    u8 index;

    if (arg0->state == 0) {
        arg0->state++;
        arg0->ext.unk_effect.unk14 = 0;
        return;
    }

    triggers = sound_zone_lists[(s8)engine_obj.substage];
    for (index = 0; index < 4; index++) {
        struct Effect10Trigger* trigger = &triggers[index];
        u8 bit = 1 << index;
        u8 active = arg0->ext.unk_effect.unk14;

        if (player_in_bounds(&trigger->left)) {
            if (!(active & bit)) {
                if (engine_obj.substage == 0 || active == 0)
                    func_8001540C(5, trigger->sound_id, NULL);
                arg0->ext.unk_effect.unk14 = active | bit;
            }
        } else if (active & bit) {
            if (engine_obj.substage == 0 || (active != 3 && active != 6))
                stop_sound(5, trigger->sound_id);
            arg0->ext.unk_effect.unk14 = active & ~bit;
        }
    }
}

void func_800D3C58(struct QuadObj* arg0)
{
    const struct SearchLightInit* init = &search_light_shapes[(u8)arg0->unk2];
    s16 origin = init->vertices[0];
    s16 span = (s16)(init->vertices[2] - origin);
    s32 x_accum = arg0->runtime.search_light.x_accumulator;
    s32 y_accum = arg0->runtime.search_light.y_accumulator;
    u16 direction = arg0->link.direction;

    if (arg0->runtime.search_light.pause_timer != 0) {
        arg0->runtime.search_light.pause_timer--;
    } else {
        x_accum += arg0->ext.search_light.velocity;
        y_accum += arg0->ext.search_light.vertical_velocity;
        arg0->ext.search_light.velocity += arg0->ext.search_light.acceleration;
        arg0->ext.search_light.vertical_velocity += arg0->ext.search_light.vertical_acceleration;
        arg0->vertices[0].x.val += arg0->ext.search_light.velocity;
        arg0->vertices[1].x.val += arg0->ext.search_light.velocity;
        switch (arg0->unk5) {
        case 0:
            if ((!direction && arg0->vertices[0].x.i.hi >= (s16)(arg0->runtime.search_light.extent + origin - 0x20)) || (direction && arg0->vertices[0].x.i.hi <= (s16)(origin + 0x20 - arg0->runtime.search_light.extent))) {
                arg0->unk5 = 1;
                arg0->ext.search_light.acceleration = direction
                    ? search_light_accels[(u8)arg0->unk2 >> 1]
                    : -search_light_accels[(u8)arg0->unk2 >> 1];
            }
            break;
        case 1:
            if (!direction) {
                if (arg0->ext.search_light.velocity <= 0x7FFF) {
                    arg0->ext.search_light.velocity = 0x8000;
                    arg0->ext.search_light.acceleration = 0;
                }
                if (arg0->vertices[0].x.i.hi >= (s16)(origin + arg0->runtime.search_light.extent)) {
                    arg0->unk5 = 2;
                    arg0->ext.search_light.velocity = 0;
                    arg0->ext.search_light.acceleration = 0;
                    arg0->vertices[0].x.val = 0;
                    arg0->vertices[1].x.val = 0;
                    arg0->vertices[0].x.i.hi = origin + arg0->runtime.search_light.extent;
                    arg0->vertices[1].x.i.hi = span + origin + arg0->runtime.search_light.extent;
                    arg0->runtime.search_light.pause_timer = get_random() & 7;
                    direction ^= 1;
                }
            } else {
                if (arg0->ext.search_light.velocity >= -0x7FFF) {
                    arg0->ext.search_light.velocity = -0x8000;
                    arg0->ext.search_light.acceleration = 0;
                }
                if (arg0->vertices[0].x.i.hi <= (s16)(origin - arg0->runtime.search_light.extent)) {
                    arg0->unk5 = 2;
                    arg0->ext.search_light.velocity = 0;
                    arg0->ext.search_light.acceleration = 0;
                    arg0->vertices[0].x.val = 0;
                    arg0->vertices[1].x.val = 0;
                    arg0->vertices[0].x.i.hi = origin - arg0->runtime.search_light.extent;
                    arg0->vertices[1].x.i.hi = span + origin - arg0->runtime.search_light.extent;
                    arg0->runtime.search_light.pause_timer = get_random() & 7;
                    direction ^= 1;
                }
            }
            break;
        case 2:
            arg0->ext.search_light.acceleration = direction
                ? -search_light_accels[(u8)arg0->unk2 >> 1]
                : search_light_accels[(u8)arg0->unk2 >> 1];
            arg0->unk5 = 3;
            arg0->runtime.search_light.base_speed = -arg0->runtime.search_light.base_speed;
            break;
        case 3:
            if ((!direction && arg0->vertices[0].x.i.hi >= (s16)(origin + 0x20 - arg0->runtime.search_light.extent)) || (direction && arg0->vertices[0].x.i.hi <= (s16)(arg0->runtime.search_light.extent + origin - 0x20))) {
                arg0->ext.search_light.acceleration = 0;
                arg0->unk5 = 0;
                arg0->ext.search_light.velocity = arg0->runtime.search_light.base_speed;
            }
            break;
        }
        arg0->runtime.search_light.x_accumulator = x_accum;
        arg0->runtime.search_light.y_accumulator = y_accum;
        arg0->link.direction = direction;
    }
    if (search_light_is_visible(arg0)) {
        arg0->on_screen = 1;
    } else {
        arg0->on_screen = 0;
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

static P_TAG* background_heads[2][6][8];
static P_TAG* background_tails[2][6][8];

struct PcSpriteFrame {
    void* data;
    u16 texture;
    u16 clut;
    u8 index;
};

#define PC_OBJECT_IN_ARRAY(object, array) \
    ((uintptr_t)(object) >= (uintptr_t) & (array)[0] && (uintptr_t)(object) < (uintptr_t) & (array)[COUNT(array)])

static s32 get_pc_sprite_frame(struct VisualObj* object,
    struct PcSpriteFrame* frame)
{
    if (object == (struct VisualObj*)&g_Player || object == (struct VisualObj*)&g_Entity) {
        struct PlayerObj* player = (struct PlayerObj*)object;

        frame->data = player->unk3C;
        frame->texture = player->unk40;
        frame->clut = player->unk42;
        frame->index = player->animation_step.fields.frame_index;
    } else if (object == (struct VisualObj*)&qux_object) {
        frame->data = qux_object.unk3C;
        frame->texture = qux_object.unk40;
        frame->clut = qux_object.unk42;
        frame->index = qux_object.animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, baz_objects)) {
        struct BazObj* baz = (struct BazObj*)object;

        frame->data = baz->unk3C;
        frame->texture = baz->unk40;
        frame->clut = baz->unk42;
        frame->index = baz->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, foo_objects) || PC_OBJECT_IN_ARRAY(object, unk_objects)) {
        struct UnkObj* unknown = (struct UnkObj*)object;

        frame->data = unknown->unk3C;
        frame->texture = unknown->unk40;
        frame->clut = unknown->unk42;
        frame->index = unknown->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, main_objects)) {
        struct MainObj* main = (struct MainObj*)object;

        frame->data = (void*)main->sprite_frames;
        frame->texture = main->unk40;
        frame->clut = main->unk42;
        frame->index = main->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, shot_objects)) {
        struct ShotObj* shot = (struct ShotObj*)object;

        frame->data = shot->unk3C;
        frame->texture = shot->unk40;
        frame->clut = shot->unk42;
        frame->index = shot->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, weapon_objects)) {
        struct WeaponObj* weapon = (struct WeaponObj*)object;

        frame->data = weapon->unk3C;
        frame->texture = weapon->unk40;
        frame->clut = weapon->unk42;
        frame->index = weapon->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, visual_objects)) {
        struct VisualObj* visual = object;

        frame->data = visual->unk3C;
        frame->texture = visual->unk40;
        frame->clut = visual->unk42;
        frame->index = visual->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, misc_objects)) {
        struct MiscObj* misc = (struct MiscObj*)object;

        frame->data = misc->unk3C;
        frame->texture = misc->unk40;
        frame->clut = misc->unk42;
        frame->index = misc->animation_step.fields.frame_index;
    } else if (PC_OBJECT_IN_ARRAY(object, item_objects)) {
        struct ItemObj* item = (struct ItemObj*)object;

        frame->data = (void*)item->sprite_frames;
        frame->texture = item->unk40;
        frame->clut = item->unk42;
        frame->index = item->animation_step.fields.frame_index;
    } else {
        return 0;
    }

    if (frame->data != NULL && pc_archive_slots[0] != NULL && ((uintptr_t)frame->data >> 32) != ((uintptr_t)pc_archive_slots[0] >> 32)) {
        frame->data = (void*)(((uintptr_t)pc_archive_slots[0] & ~(uintptr_t)UINT32_MAX) | ((uintptr_t)frame->data & UINT32_MAX));
    }

    return frame->data != NULL;
}

#undef PC_OBJECT_IN_ARRAY

void func_80024334(struct VisualObj* object)
{
    POLY_FT4* primitive;
    DR_TPAGE* draw_mode;
    u8* frame_data;
    u16* frame_header;
    s32 frame_count;
    s32 origin_x;
    s32 origin_y;
    u8 flipped;
    u16 texture;
    u16 clut;
    P_TAG* first_draw_mode;
    struct PcSpriteFrame frame;

    if (SP_SPRITE_COUNT >= 1000)
        return;

    if (!get_pc_sprite_frame(object, &frame))
        return;

    if (object->bg_offset < 0) {
        origin_x = object->x_pos.i.hi;
        origin_y = object->y_pos.i.hi;
    } else {
        struct BackgroundObj* background = &background_objects[object->bg_offset];

        origin_x = object->x_pos.i.hi - background->x_pos.i.hi;
        origin_y = object->y_pos.i.hi - background->y_pos.i.hi;
    }

    primitive = SP_PRIM_CURSOR;
    draw_mode = SP_DRAW_MODE_CURSOR;
    first_draw_mode = (P_TAG*)draw_mode;
    frame_header = (u16*)((u8*)frame.data + frame.index * 4);
    frame_count = frame_header[0];
    frame_data = (u8*)frame.data + frame_header[1] * 4;
    flipped = object->unk15;
    texture = frame.texture;
    clut = frame.clut;

    while (frame_count-- != 0) {
        u8 flags;
        u32 texture_index;
        s32 x0;
        s32 x1;
        s32 y0;
        s32 y1;
        s32 u0;
        s32 u1;
        s32 v0;
        s32 v1;
        u16 primitive_clut;

        if (SP_SPRITE_COUNT >= 1000)
            return;
        SP_SPRITE_COUNT++;

        flags = frame_data[0];
        x0 = (s8)frame_data[2];
        if (flipped == 0) {
            x1 = x0 + 16;
        } else {
            x1 = -x0;
            x0 = -(x0 + 16);
        }
        x0 += origin_x;
        x1 += origin_x;
        y0 = origin_y + (s8)frame_data[3];
        y1 = y0 + 16;

        texture_index = texture + (frame_data[1] | ((flags & 3) << 8));
        if (object->active & 0x40) {
            u32 index = texture_index & 0xFFFF;

            texture_index = ((index / 176) << 8) + index % 176 + 0x600;
        }
        if (object->active & 0x20) {
            u32 index = texture_index & 0xFFFF;

            texture_index = ((index / 80) << 8) + index % 80 + 0x5B0;
        }

        if (clut & 0x8000) {
            primitive_clut = 0x7840;
        } else {
            primitive_clut = clut + ((flags & 0xC) >> 2);
            if (primitive_clut & 0x30)
                primitive_clut += 0x30;
        }

        v0 = texture_index & 0xF0;
        if (!(flags & 0x80) && ((flags & 0x40) ^ flipped) == 0) {
            setSprt16(primitive);
            setShadeTex(primitive, 1);
            setSemiTrans(primitive, object->active & 0x10);
            primitive->clut = primitive_clut;
            primitive->x0 = x0;
            primitive->y0 = y0;
            primitive->u0 = texture_index * 16;
            primitive->v0 = v0;
        } else {
            if (!(flags & 0x80)) {
                setPolyFT4(primitive);
                setShadeTex(primitive, 1);
                setSemiTrans(primitive, object->active & 0x10);
                u0 = texture_index * 16 - 1;
                u1 = texture_index * 16 | 0xF;
                if ((u8)u0 == 0xFF) {
                    u0 = texture_index * 16;
                    x1--;
                }
                v1 = v0 + 16;
                if ((u8)v1 == 0) {
                    v1 = v0 + 15;
                    y1--;
                }
            } else {
                setlen(primitive, 9);
                setcode(primitive,
                    object->active & 0x10 ? 0x2F : 0x2D);
                v1 = (texture_index & 0xF0) - 1;
                v0 = (texture_index & 0xF0) | 0xF;
                if ((u8)v1 == 0xFF) {
                    v1 = texture_index & 0xF0;
                    y1--;
                }
                if (((flags & 0x40) ^ flipped) == 0) {
                    u0 = texture_index * 16 + 16;
                    u1 = texture_index * 16;
                    if ((u8)u0 == 0) {
                        u0 = texture_index * 16 | 0xF;
                        x1--;
                    }
                } else {
                    u0 = texture_index * 16 - 1;
                    u1 = texture_index * 16 | 0xF;
                    if ((u8)u0 == 0xFF) {
                        u0 = texture_index * 16;
                        x1--;
                    }
                }
            }

            primitive->clut = primitive_clut;
            primitive->tpage = (texture_index >> 8) | 0x20;
            setXY4(primitive, x0, y0, x1, y0, x0, y1, x1, y1);
            setUV4(primitive, u1, v0, u0, v0, u1, v1, u0, v1);
        }

        setlen(draw_mode, 1);
        draw_mode->code[0] = !(flags & 0x80) && ((flags & 0x40) ^ flipped) == 0
            ? (texture_index >> 8) | 0xE1000020
            : 0xE1000020;
        setaddr(draw_mode, primitive);
        setaddr(primitive, draw_mode + 1);
        primitive++;
        draw_mode++;
        frame_data += 4;
    }

    if (primitive != SP_PRIM_CURSOR) {
        u32 buffer = SP_DRAW_BUFFER;
        u32 group = (object->unk16 >> 4) & 3;
        u32 priority = object->unk16 & 7;

        setaddr(D_8013BC40[buffer][group][priority], first_draw_mode);
        D_8013BC40[buffer][group][priority] = (P_TAG*)(primitive - 1);
    }

    SP_PRIM_CURSOR = primitive;
    SP_DRAW_MODE_CURSOR = draw_mode;
}

void func_8002588C(struct PlayerObj* arg0, s32 part, s32 clut)
{
    POLY_FT4* primitive;
    DR_TPAGE* draw_mode;
    P_TAG* first_draw_mode;
    P_TAG** tail;
    u8* table;
    u8* frame_data;
    u16* frame_header;
    s32 frame_count;
    s32 origin_x;
    s32 origin_y;
    u8 flipped;
    u16 texture;

    if (arg0->bg_offset < 0) {
        origin_x = arg0->x_pos.i.hi;
        origin_y = arg0->y_pos.i.hi;
    } else {
        struct BackgroundObj* background = &background_objects[arg0->bg_offset];

        origin_x = (u16)(arg0->x_pos.i.hi - background->x_pos.i.hi);
        origin_y = (u16)(arg0->y_pos.i.hi - background->y_pos.i.hi);
    }
    origin_x = (s16)origin_x;
    origin_y = (s16)origin_y;

    primitive = SP_PRIM_CURSOR;
    draw_mode = SP_DRAW_MODE_CURSOR;
    first_draw_mode = (P_TAG*)draw_mode;
    table = (u8*)SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, part + 5);
    frame_header = (u16*)(table + arg0->animation_step.fields.frame_index * 4);
    frame_count = frame_header[0];
    frame_data = table + frame_header[1] * 4;
    flipped = arg0->unk15;
    texture = arg0->unk40;

    if (frame_count == 0)
        return;

    while (frame_count-- != 0) {
        u8 flags = frame_data[0];
        s32 x0 = (s8)frame_data[2];
        s32 x1;
        s32 y0;
        s32 y1;
        u32 texture_index;
        u16 primitive_clut;
        s32 v0;

        if (flipped == 0) {
            x1 = x0 + 16;
        } else {
            x1 = -x0;
            x0 = -(x0 + 16);
        }
        x0 += origin_x;
        x1 += origin_x;
        y0 = origin_y + (s8)frame_data[3];
        y1 = y0 + 16;
        primitive_clut = clut + ((flags & 0xC) >> 2);
        texture_index = texture + (frame_data[1] | ((flags & 3) << 8));
        v0 = texture_index & 0xF0;

        if (((flags & 0x40) ^ flipped) == 0) {
            setlen(primitive, 3);
            setcode(primitive, arg0->active & 0x10 ? 0x7F : 0x7D);
            primitive->clut = primitive_clut;
            primitive->x0 = x0;
            primitive->y0 = y0;
            primitive->u0 = texture_index * 16;
            primitive->v0 = v0;
            draw_mode->code[0] = ((texture_index & 0xFFFF) >> 8) | 0xE1000020;
        } else {
            s32 u0 = texture_index * 16 - 1;
            s32 u1 = texture_index * 16 | 0xF;
            s32 v1 = v0 + 16;

            setlen(primitive, 9);
            setcode(primitive, arg0->active & 0x10 ? 0x2F : 0x2D);
            primitive->tpage = ((texture_index & 0xFFFF) >> 8) | 0x20;
            primitive->clut = primitive_clut;
            if ((u8)u0 == 0xFF) {
                u0 = texture_index * 16;
                x1--;
            }
            if ((u8)v1 == 0) {
                v1 = v0 | 0xF;
                y1--;
            }
            setXY4(primitive, x0, y0, x1, y0, x0, y1, x1, y1);
            setUV4(primitive, u1, v0, u0, v0, u1, v1, u0, v1);
            draw_mode->code[0] = 0xE1000020;
        }

        setlen(draw_mode, 1);
        setaddr(draw_mode, primitive);
        setaddr(primitive, draw_mode + 1);
        primitive++;
        draw_mode++;
        frame_data += 4;
    }

    SP_PRIM_CURSOR = primitive;
    tail = &((P_TAG**)D_8013BC40[SP_DRAW_BUFFER])[(arg0->unk16 >> 4) * 8 + (arg0->unk16 & 0xF)];
    setaddr(*tail, first_draw_mode);
    *tail = (P_TAG*)(primitive - 1);
    SP_DRAW_MODE_CURSOR = draw_mode;
}

void func_80024920(struct QuadObj* arg0)
{
    POLY_F4* primitive;
    DR_MODE* draw_mode;
    s32 x;
    s32 y;
    u32 red;
    u32 green;
    u32 blue;
    u8 ordering;
    u32 group;
    u32 priority;
    u32 buffer;

    if (SP_SPRITE_COUNT >= 1000)
        return;
    SP_SPRITE_COUNT++;

    if (arg0->bg_offset < 0) {
        x = arg0->x_pos.i.hi;
        y = arg0->y_pos.i.hi;
    } else {
        struct BackgroundObj* background = &background_objects[arg0->bg_offset];

        x = arg0->x_pos.i.hi - background->x_pos.i.hi;
        y = arg0->y_pos.i.hi - background->y_pos.i.hi;
    }

    primitive = SP_PRIM_CURSOR;
    draw_mode = SP_DRAW_MODE_CURSOR;
    setPolyF4(primitive);
    setSemiTrans(primitive, (arg0->active & 0x10) != 0);
    setXY4(primitive,
        x + arg0->vertices[0].x.i.hi, y + arg0->vertices[0].y.i.hi,
        x + arg0->vertices[1].x.i.hi, y + arg0->vertices[1].y.i.hi,
        x + arg0->vertices[3].x.i.hi, y + arg0->vertices[3].y.i.hi,
        x + arg0->vertices[2].x.i.hi, y + arg0->vertices[2].y.i.hi);

    red = arg0->unk34 & 0x1F;
    green = (arg0->unk34 >> 5) & 0x1F;
    blue = arg0->unk34 >> 10;
    setRGB0(primitive,
        red * 8 + (red >> 2),
        green * 8 + (green >> 2),
        blue * 8 + (blue >> 2));
    setlen(draw_mode, 1);
    draw_mode->code[0] = 0xE1000000;

    ordering = arg0->unk36;
    group = (ordering >> 4) & 3;
    priority = ordering & 0xF;
    buffer = SP_DRAW_BUFFER;
    setaddr(D_8013BC40[buffer][group][priority], draw_mode);
    setaddr(draw_mode, primitive);
    D_8013BC40[buffer][group][priority] = (P_TAG*)primitive;

    SP_PRIM_CURSOR = primitive + 1;
    SP_DRAW_MODE_CURSOR = draw_mode + 1;
}

void func_80024B9C(struct QuadObj* arg0)
{
    POLY_G4* primitive;
    DR_MODE* draw_mode;
    const u8* color;
    s32 x;
    s32 y;
    u32 group;
    u32 priority;
    u32 buffer;

    if (SP_SPRITE_COUNT >= 1000 || arg0->unk34 >= COUNT(D_800F2B5C))
        return;
    if (arg0->bg_offset < 0) {
        x = arg0->x_pos.i.hi;
        y = arg0->y_pos.i.hi;
    } else {
        struct BackgroundObj* background = &background_objects[arg0->bg_offset];

        x = arg0->x_pos.i.hi - background->x_pos.i.hi;
        y = arg0->y_pos.i.hi - background->y_pos.i.hi;
    }
    primitive = SP_PRIM_CURSOR;
    draw_mode = SP_DRAW_MODE_CURSOR;
    color = D_800F2B5C[arg0->unk34];
    setPolyG4(primitive);
    setSemiTrans(primitive, (arg0->active & 0x10) != 0);
    setXY4(primitive,
        x + arg0->vertices[0].x.i.hi, y + arg0->vertices[0].y.i.hi,
        x + arg0->vertices[1].x.i.hi, y + arg0->vertices[1].y.i.hi,
        x + arg0->vertices[3].x.i.hi, y + arg0->vertices[3].y.i.hi,
        x + arg0->vertices[2].x.i.hi, y + arg0->vertices[2].y.i.hi);
    setRGB0(primitive, color[0], color[1], color[2]);
    setRGB1(primitive, color[3], color[4], color[5]);
    setRGB2(primitive, color[6], color[7], color[8]);
    setRGB3(primitive, color[9], color[10], color[11]);
    SetDrawMode(draw_mode, 0, 0, 0, NULL);
    group = ((u8)arg0->unk36 >> 4) & 3;
    priority = (u8)arg0->unk36 & 0xF;
    if (priority >= 8)
        return;
    buffer = SP_DRAW_BUFFER;
    setaddr(D_8013BC40[buffer][group][priority], draw_mode);
    setaddr(draw_mode, primitive);
    D_8013BC40[buffer][group][priority] = (P_TAG*)primitive;
    SP_PRIM_CURSOR = primitive + 1;
    SP_DRAW_MODE_CURSOR = draw_mode + 1;
    SP_SPRITE_COUNT++;
}

void func_80025188(s32 slot, u8 index)
{
    const u8* archive = (const u8*)SP_SPRITE_FRAMES;
    const u8* table;
    const u8* pieces;
    u16 count;

    if ((u32)slot >= COUNT(D_800F30F4) || archive == NULL)
        return;
    table = archive + *(const s32*)(archive + 4);
    count = *(const u16*)(table + (u32)index * 4);
    pieces = table + *(const u16*)(table + (u32)index * 4 + 2) * 4;
    while (count-- != 0 && SP_SPRITE_COUNT < 1000) {
        SPRT_16* sprite = SP_BG_PRIM_CURSOR;
        DR_TPAGE* mode = SP_OT_CURSOR;
        u8 flags = pieces[0];
        u16 texture = pieces[1] | ((flags & 3) << 8);
        s32 texture_index = texture % 80 + ((texture / 80) << 8);
        u16 clut = D_800F30F4[slot].clut + ((flags & 0xC) >> 2);

        setSprt16(sprite);
        sprite->code |= 1;
        setXY0(sprite, D_800F30F4[slot].x + (s8)pieces[2],
            D_800F30F4[slot].y + (s8)pieces[3]);
        setUV0(sprite, (u8)((texture_index + 0x5B0) << 4),
            (u8)((texture_index + 0x5B0) & 0xF0));
        sprite->clut = clut;
        setlen(mode, 1);
        mode->code[0] = 0xE1000000 | ((texture_index + 0x5B0) >> 8);
        addPrim(&cur_draw_info->ordering_table.unk3, sprite);
        addPrim(&cur_draw_info->ordering_table.unk3, mode);
        SP_BG_PRIM_CURSOR = sprite + 1;
        SP_OT_CURSOR = mode + 1;
        SP_SPRITE_COUNT++;
        pieces += 4;
    }
}

void func_800253F0(struct MainObj* player, s32 gauge)
{
    s8 value = player->hp & 0x7F;
    s8 target = gauge == 0 ? engine_obj.unk46 : 0x30;
    s16 x = D_800F3124[gauge].x;
    u16 bottom = D_800F3124[gauge].bottom;

    func_80025588(x, x + 5, bottom - value, bottom, value < target / 3);
    if (value == player->unk5D)
        return;
    if (player->unk5D < value) {
        player->unk5D = value;
        return;
    }
    if (player->hp & 0x80)
        player->unk5F = 0x10;
    func_80025588(x, x + 5, bottom - (s8)player->unk5D, bottom - value, 2);
    if (player->unk5F != 0) {
        player->unk5F--;
        return;
    }
    if (!(main_bss_state.frame_counter & 3))
        player->unk5D--;
}

void func_80036F50(struct PlayerObj* player)
{
    static const u8 weapon_masks[] = { 0, 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80 };
    u16 input;
    s8 weapon;

    if (player->input_locked != 0 || player->is_clone != 0 || player->special_shot_count != 0 || player->ride_state != 0 || player->nova_strike_active != 0 || engine_obj.unk1C != 0)
        return;
    input = player->pressed_input;
    if (((player->input.buttons.held & 0x600) == 0x600) || ((input & 0x600) == 0x600)) {
        if (player->weapon != 0) {
            player->weapon = 0;
            player_reset_charge(player);
            func_8001540C(0, 0xC, 0);
        }
        return;
    }
    if (!(input & 0x600))
        return;
    weapon = player->weapon;
    if (input & 0x200) {
        do {
            if (++weapon == 9) {
                weapon = 0;
                break;
            }
        } while (!(weapon_masks[(u8)weapon] & player->boss_flags));
    } else {
        do {
            if (--weapon < 0)
                weapon = 8;
            if (weapon == 0)
                break;
        } while (!(weapon_masks[(u8)weapon] & player->boss_flags));
    }
    if (player->weapon != weapon) {
        player->weapon = weapon;
        player_reset_charge(player);
        func_8001540C(0, 0xC, 0);
        player->stock_charge = 0;
    }
}

ret_s8 func_8002DD04(struct MainObj* object)
{
    struct WeaponObj* weapon;

    if (object->unk7A != 0) {
        object->unk65 = 0;
        return 0;
    }
    if (object->collision_data == D_80106070 && (g_Player.unk2 == 0 || !(g_Player.boss_flags & 0x40)))
        return 0;
    if (object->unk5 != 0)
        object->unk42 &= 0x7FFF;
    for (weapon = weapon_objects; weapon < weapon_objects + COUNT(weapon_objects); weapon++) {
        s32 result;

        if (!weapon->active)
            continue;
        if (!func_8002BD58((struct MainObj*)weapon, object,
                &((s16*)&weapon->unk80)[0], &((s16*)&weapon->unk80)[1]))
            continue;
        result = (s8)func_8002DE30(object, weapon);
        if (result == 0x7E)
            return 0;
        if (result != 0)
            return result;
    }
    object->unk65 = 0;
    return 0;
}

void func_800262B8(u8 layer)
{
    struct BackgroundObj* background = &background_objects[layer];
    s32 source_tile_x = background->x_pos.i.hi / 16;
    s32 source_tile_y = background->y_pos.i.hi / 16;
    s32 block_x = source_tile_x / 16;
    s32 block_y = source_tile_y / 16;
    s32 tile_y = source_tile_y & 31;
    s32 inner_y = source_tile_y & 15;
    s32 layer_offset = layer * layout_size;
    s32 row_offset = block_y * layout_width;
    s32 row;

    for (row = 0; row < 17; row++) {
        s32 current_block_x = block_x;
        s32 tile_x = source_tile_x & 31;
        s32 inner_x = source_tile_x & 15;
        u8 block = SP_BG_TILEMAP[layer_offset + row_offset + current_block_x];
        s32 column;

        for (column = 0; column < 22; column++) {
            D_801441C8[layer][tile_y][tile_x] = SP_BG_TILE_PIXELS[block * 256 + inner_y * 16 + inner_x];
            tile_x = (tile_x + 1) & 31;
            inner_x++;
            if (inner_x == 16) {
                inner_x = 0;
                current_block_x++;
                block = SP_BG_TILEMAP[layer_offset + row_offset + current_block_x];
            }
        }

        tile_y = (tile_y + 1) & 31;
        inner_y++;
        if (inner_y == 16) {
            inner_y = 0;
            row_offset += layout_width;
        }
    }

    background->unk4C = 0;
}

void func_80026894(s32 layer)
{
    s32 buffer = SP_DRAW_BUFFER;
    s32 back_layer = layer + 3;
    s32 i;

    for (i = 0; i < 8; i++) {
        P_TAG* head = background_heads[buffer][layer][i];

        if (head != NULL) {
            DR_TPAGE* page = &D_80171EB0[buffer][layer][i];

            setaddr(page, head);
            addPrims(&cur_draw_info->ordering_table.start + *(s8*)&background_objects[layer].unk4A,
                page,
                background_tails[buffer][layer][i]);
            background_heads[buffer][layer][i] = NULL;
            background_tails[buffer][layer][i] = NULL;
        }

        head = background_heads[buffer][back_layer][i];
        if (head != NULL) {
            DR_TPAGE* page = &D_80171EB0[buffer][back_layer][i];

            setaddr(page, head);
            addPrims(&cur_draw_info->ordering_table.start + *(s8*)&background_objects[layer].unk4B,
                page,
                background_tails[buffer][back_layer][i]);
            background_heads[buffer][back_layer][i] = NULL;
            background_tails[buffer][back_layer][i] = NULL;
        }
    }
}

void func_80026AA0(s32 layer)
{
    struct BackgroundObj* bg = &background_objects[layer];
    SPRT_16* sprite = SP_BG_PRIM_CURSOR;
    s32 tile_x = (bg->x_pos.i.hi / 16) & 31;
    s32 tile_y = (bg->y_pos.i.hi / 16) & 31;
    s32 screen_y = -(bg->y_pos.i.hi & 15);
    s32 row;

    if (mmx4_pc_hide_background)
        return;

    for (row = 0; row < 16; row++) {
        s32 current_tile_x = tile_x;
        s32 screen_x = -(bg->x_pos.i.hi & 15);
        s32 column;

        for (column = 0; column < 21; column++) {
            u16 tile = D_801441C8[layer][tile_y][current_tile_x];

            if (tile != 0) {
                u32 attributes;
                s32 ordering_layer;
                s32 priority;
                P_TAG* tail;

                if (SP_BG_SPRITE_COUNT >= 1000)
                    return;
                SP_BG_SPRITE_COUNT++;

                attributes = SP_BG_TILE_ATTRS[tile & 0x3FFF];
                sprite->clut = 0x7900 | ((attributes & 0xF000) >> 6) | ((attributes & 0xF00) >> 8);
                setSemiTrans(sprite, (tile & 0x4000) != 0);
                setUV0(sprite, (attributes >> 12) & 0xF0,
                    (attributes >> 16) & 0xF0);
                setXY0(sprite, screen_x, screen_y);

                ordering_layer = layer + ((tile & 0x8000) != 0 ? 3 : 0);
                priority = attributes >> 24;
                tail = background_tails[SP_DRAW_BUFFER][ordering_layer][priority];
                if (tail == NULL) {
                    background_heads[SP_DRAW_BUFFER][ordering_layer][priority] = (P_TAG*)sprite;
                } else {
                    setaddr(tail, sprite);
                }
                background_tails[SP_DRAW_BUFFER][ordering_layer][priority] = (P_TAG*)sprite;
                sprite++;
            }

            screen_x += 16;
            current_tile_x = (current_tile_x + 1) & 31;
        }

        screen_y += 16;
        tile_y = (tile_y + 1) & 31;
    }

    SP_BG_PRIM_CURSOR = sprite;
}

void func_80027344(s32 layer, s32 x, s32 y)
{
    struct BackgroundObj* bg = &background_objects[layer];
    s32 tile_count = 18;
    s32 block_x, block_y;
    s32 tile_x, tile_y;
    s32 inner_x, inner_y;
    s32 min_block_x, max_block_x;
    s32 layer_offset, row_offset;
    s32 width;
    s32 i;
    u8 block;

    if (x < 0)
        return;
    if (y < 0) {
        y = 0;
        tile_count = 17;
    }

    block_x = x / 256;
    block_y = y / 256;
    tile_x = (x % 512) / 16;
    tile_y = (y % 512) / 16;
    inner_x = tile_x & 15;
    inner_y = tile_y & 15;
    min_block_x = bg->unk4D;
    max_block_x = bg->unk4E;

    if ((u32)block_x < min_block_x) {
        block_x += max_block_x - min_block_x + 1;
        if (bg->x_pos.i.hi <= (min_block_x - 1) * 256) {
            bg->x_pos.i.hi = max_block_x * 256;
            return;
        }
    }
    if ((u32)block_x > max_block_x) {
        block_x -= max_block_x - min_block_x + 1;
        if (bg->x_pos.i.hi >= (max_block_x + 1) * 256) {
            bg->x_pos.i.hi = min_block_x * 256;
            return;
        }
    }

    layer_offset = layer * layout_size;
    width = layout_width;
    row_offset = width * block_y;
    block = SP_BG_TILEMAP[layer_offset + row_offset + block_x];
    for (i = 0; i < tile_count; i++) {
        D_801441C8[layer][tile_y][tile_x] = SP_BG_TILE_PIXELS[block * 256 + inner_y * 16 + inner_x];
        tile_y = (tile_y + 1) & 31;
        inner_y++;
        if (inner_y == 16) {
            inner_y = 0;
            row_offset += width;
            block = SP_BG_TILEMAP[layer_offset + row_offset + block_x];
        }
    }
}

void func_800275DC(s32 layer, s32 x, s32 y)
{
    s32 block_x, block_y;
    s32 tile_x, tile_y;
    s32 inner_x, inner_y;
    s32 layer_offset, row_offset;
    s32 i;
    u8 block;

    if (y < 0)
        return;

    block_x = x / 256;
    block_y = y / 256;
    tile_x = (x % 512) / 16;
    tile_y = (y % 512) / 16;
    inner_x = tile_x & 15;
    inner_y = tile_y & 15;
    layer_offset = layer * layout_size;
    row_offset = layout_width * block_y;
    block = SP_BG_TILEMAP[layer_offset + row_offset + block_x];

    for (i = 0; i < 21; i++) {
        D_801441C8[layer][tile_y][tile_x] = SP_BG_TILE_PIXELS[block * 256 + inner_y * 16 + inner_x];
        tile_x = (tile_x + 1) & 31;
        inner_x++;
        if (inner_x == 16) {
            inner_x = 0;
            block_x++;
            block = SP_BG_TILEMAP[layer_offset + row_offset + block_x];
        }
    }
}

void func_800E0D0C(void)
{
    SpuSetReverb(1);
}

void func_800E9040(void)
{
    Psyz_GteCtrlWrite(29, 0x155);
    Psyz_GteCtrlWrite(30, 0x100);
    Psyz_GteCtrlWrite(26, 0x3E8);
    Psyz_GteCtrlWrite(27, (u32)-0x1062);
    Psyz_GteCtrlWrite(28, 0x01400000);
    Psyz_GteCtrlWrite(24, 0);
    Psyz_GteCtrlWrite(25, 0);
}

extern s16 D_800F224C[];
extern union TitleScratch D_80169498;

void func_8001E130(struct GameInfo* arg0)
{
    s16* target;
    s32* x;
    s32* y;
    u8* flags;
    s32 x_diff;
    s32 y_diff;
    s32 i;
    struct MiscObj* obj;
    u8 direction;

    x = &D_80169498.sector[0];
    i = 0;
    flags = (u8*)&D_80169498;
    y = &D_80169498.sector[1];
    do {
        target = &D_800F224C[i * 2];
        x_diff = *x - (target[0] << 16);
        y_diff = *y - (target[1] << 16);
        direction = angle_from_delta(x_diff, y_diff);
        if (((((flags[0xA2] ^ direction) & 0x10) != 0) || (flags[0x90] != 0)) && (D_80169498.title.settled == 0)) {
            *x = target[0] << 16;
            *y = target[1] << 16;
            flags[0x90] = 1;
        } else {
            *x -= x_diff / arg0->unk6;
            *y -= y_diff / arg0->unk6;
            flags[0x90] = 0;
            if (i == 0x11) {
                D_80169498.title.settled = 0;
            }
        }
        y += 2;
        x += 2;
        flags[0xA2] = direction;
        i++;
        flags++;
    } while (i < 0x12);

    arg0->unk6--;
    if (arg0->unk6 == 0) {
        target = D_800F224C;
        x = D_80169498.sector;
        i = 0;
        do {
            *x = *target << 16;
            target++;
            x++;
            i++;
        } while (i < 0x24);
        arg0->mode++;

#ifdef VERSION_JP
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0x1D;
            obj->unk2 = 0x22;
        }
#else
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0x13;
            obj->unk2 = 0xC;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0x13;
            obj->unk2 = 0x14;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0x13;
            obj->unk2 = 0x15;
        }
#endif
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0x1D;
            obj->unk2 = 0x21;
        }
        D_80139690 = OBJECT_HEADER(obj);
    }
}

void func_800C00BC(struct ItemObj* arg0)
{
    struct CollisionObj* player;
    u16 flag;
    s32 shift;

    if (g_Player.ride_state == 0) {
        player = (struct CollisionObj*)&g_Player;
        if (!(g_Player.hp & 0x7F)) {
            return;
        }
    } else {
        player = (struct CollisionObj*)&qux_object;
        if (!(qux_object.unk5C & 0x7F)) {
            return;
        }
    }
    if (!func_8002C160((struct CollisionObj*)arg0, player)) {
        return;
    }

    arg0->unk5 = 0;
    switch (arg0->unk7C.value) {
    case 0:
        pickup_collect_health(arg0, 4, 1);
        break;
    case 1:
        pickup_collect_health(arg0, 0x10, 2);
        break;
    case 2:
    case 3:
    case 6:
        func_800BFCC0(arg0, arg0->unk7C.value);
        arg0->state = 3;
        break;
    case 4:
        engine_obj.unk44++;
        if (engine_obj.unk44 >= 10) {
            engine_obj.unk44 = 9;
        } else {
            func_8001540C(0, 0x15, 0);
        }
        arg0->state = 3;
        break;
    case 5:
        pickup_collect_health(arg0, engine_obj.unk46, 4);
        break;
    case 7:
        flag = engine_obj.unk5A;
        if ((flag & 0xFF) == 0xFF) {
            arg0->state = 3;
            break;
        }
        shift = arg0->unk2 - 7;
        if (flag & (1 << shift)) {
            arg0->state = 3;
            break;
        }
        engine_obj.unk5A = flag | (1 << shift);
        engine_obj.unk46 += 2;
        func_8001540C(0, 0x15, 0);
        arg0->state = 3;
        break;
    case 8:
        flag = engine_obj.unk5A;
        if ((flag & 0x3000) == 0x3000) {
            break;
        }
        shift = arg0->unk2 - 15;
        if (flag & (0x1000 << shift)) {
            break;
        }
        engine_obj.unk5A = flag | (0x1000 << shift);
        arg0->state = 3;
        engine_obj.unk5C[arg0->unk2 == 15 ? 0 : 1] = -0x80;
        func_8001540C(0, 0x15, 0);
        break;
    case 9:
        flag = engine_obj.unk5A;
        if ((flag & 0x4000) || (flag & (0x4000 << (arg0->unk2 - 17)))) {
            break;
        }
        engine_obj.unk5A = flag | (0x4000 << (arg0->unk2 - 17));
        arg0->state = 3;
        func_8001540C(0, 0x15, 0);
        engine_obj.unk5C[2] = 0;
        break;
    case 10:
        flag = engine_obj.unk5A;
        if ((flag & 0x8000) || (flag & (0x8000 << (arg0->unk2 - 18)))) {
            break;
        }
        engine_obj.unk5A = flag | (0x8000 << (arg0->unk2 - 18));
        arg0->state = 3;
        func_8001540C(0, 0x15, 0);
        break;
    default:
        arg0->state = 3;
        break;
    }
}

void func_80068D6C(struct MainObj* arg0)
{
    s16 x;
    s16 y;

    if (arg0->air_state != 0) {
        return;
    }

    CollisionRelated((struct PlayerObj*)arg0);
    if (!(arg0->collision_flags & 8)) {
        set_animation(arg0, 0xF);
        SP_CUR_MAIN_OBJ->ext.main_49.unk80 = 5;
        arg0->unk5 = 3;
        arg0->gravity = 0x4200;
        arg0->unk6 = 0;
        arg0->y_speed = 0;
        arg0->x_accel = 0;
        arg0->air_state = -1;
        return;
    }

    if (SP_CUR_MAIN_OBJ->ext.main_49.unk85 == 2 || arg0->unk5 == 6) {
        return;
    }

    if (arg0->unk15 != 0) {
        x = arg0->x_pos.i.hi + arg0->terrain_box->unk0 + arg0->terrain_box->unk2;
    } else {
        x = arg0->x_pos.i.hi - arg0->terrain_box->unk0 - arg0->terrain_box->unk2;
    }
    y = arg0->y_pos.i.hi + arg0->terrain_box->unk1 + arg0->terrain_box->unk3 + 8;
    if (func_8002D724((struct PlayerObj*)arg0, x, y) != 0) {
        return;
    }

    if (arg0->unk2 == 0) {
        arg0->unk15 = arg0->unk15 == 0 ? 0x40 : 0;
        arg0->x_speed = -arg0->x_speed;
        return;
    }
    if (arg0->collision_flags & 3) {
        return;
    }

    set_animation(arg0, 0x19);
    arg0->unk5 = 4;
    arg0->unk6 = 0;
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk86 == 0) {
        arg0->y_speed = 0x38000;
        arg0->gravity = 0x4200;
        arg0->x_speed = arg0->unk15 == 0 ? -0x10000 : 0x10000;
    } else {
        arg0->y_speed = 0x48000;
        arg0->gravity = 0x5200;
        arg0->x_speed = arg0->unk15 == 0 ? -0x20000 : 0x20000;
    }
    arg0->air_state = 1;
}

void func_80038568(struct PlayerObj* arg0, s32 arg1)
{
    s32 relative;
    s8 duration;

    if (arg0->unk2 != 0) {
        return;
    }
    relative = arg1 + 0x70;
    if (arg0->attack_ended == 0) {
        if (arg0->attacking == 0 || arg0->unk17 == relative) {
            return;
        }
        arg1 = relative;
    }
    duration = arg0->animation_step.fields.duration;
    player_set_animation_frame(arg0, arg1, arg0->animation_step.fields.event & 0x3F);
    arg0->animation_step.fields.duration = duration;
}

s32 player_zero_check_shippuuga(struct PlayerObj*);
void player_enter_dash_end(struct PlayerObj*);

void player_zero_shippuuga(struct PlayerObj*);

void func_80036BF4(struct PlayerObj* arg0, s16 ground_y)
{
    struct VisualObj* visual;
    s32 resource;
    s32 column;
    s32 row;

    if (func_8002D724(arg0, arg0->x_pos.i.hi, ground_y) != 0x24 || arg0->unkDF != 0) {
        return;
    }

    arg0->unkDF = 1;
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 3;
        visual->unk2 = 9;
        visual->bg_offset = arg0->bg_offset;
        visual->unk16 = 1;
        visual->animation_table = D_8011BF40;
        resource = func_8002938C(0x84) & 0xFF;
        visual->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
        resource = func_8002938C(0x84) & 0xFF;
        visual->unk40 = D_801406A8[resource] >> 7;
        column = ((func_8002938C(0x84) & 0xFF) << 2) + 0x18;
        row = func_8002938C(0x84) & 0xFF;
        visual->unk42 = (u16)((column - (column & 0x7F0))
            | ((((row + 6) >> 2) + 0x1E0) << 6));
        visual->unk15 = arg0->unk15;
        visual->x_pos.i.hi = arg0->x_pos.i.hi;
        visual->y_pos.i.hi = ground_y - 8;
    }

    if (engine_obj.stage == 1) {
        func_8001540C(5, (get_random() & 1) + 3, arg0);
    } else {
        func_8001540C(2, 0xAE, arg0);
    }
}

void func_8004B8FC(struct MainObj* arg0)
{
    arg0->state = 1;
    arg0->unk6 = 0;
    arg0->unk7C = 0x90;
    arg0->invincibility_timer = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)hover_sentry_animations;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
    arg0->ext.main_12.unk88 = 0;
    arg0->air_state = 0;
    arg0->ext.main_12.unk81 = 0;
    arg0->collision_data = D_80106870;

    switch (arg0->unk2) {
    case 0:
        arg0->hp = 3;
        arg0->contact_damage = 3;
        arg0->unk5 = 2;
        arg0->y_speed = -0x8000;
        arg0->gravity = -0x800;
        arg0->unk16 = 6;
        arg0->terrain_box = &D_800FB684;
        arg0->hurt_box = &D_800FB68C;
        arg0->attack_box = &D_800FB688;
        arg0->x_speed = 0;
        arg0->x_accel = 0;
        set_animation(ANIMATED_OBJECT(arg0), 0);
        break;
    case 1:
        arg0->hp = 3;
        arg0->contact_damage = 3;
        arg0->unk5 = 6;
        arg0->ext.main_12.unk86 = arg0->y_pos.u.hi;
        arg0->y_speed = 0x4000;
        arg0->x_speed = 0;
        arg0->x_accel = 0;
        arg0->gravity = 0;
        arg0->unk16 = 6;
        arg0->terrain_box = &D_800FB690;
        arg0->hurt_box = NULL;
        arg0->attack_box = NULL;
        arg0->ext.main_12.unk8A = 0;
        set_animation(ANIMATED_OBJECT(arg0), 3);
        break;
    case 2:
        arg0->hp = 3;
        arg0->contact_damage = 3;
        arg0->unk7E = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        arg0->ext.main_12.unk86 = arg0->y_pos.u.hi;
        arg0->unk16 = 6;
        arg0->terrain_box = NULL;
        arg0->hurt_box = NULL;
        arg0->attack_box = NULL;
        arg0->ext.main_12.unk8A = 0;
        set_animation(ANIMATED_OBJECT(arg0), 2);
        break;
    }
}

void func_8004BCFC(struct MainObj* arg0)
{
    s32 transition = 0;

    switch (arg0->unk6) {
    case 0:
        if (arg0->unk7E-- != 0)
            return;
        arg0->unk6 = 1;
        arg0->unk7 = 0;
        arg0->air_state = 1;
        arg0->ext.main_12.unk86 = arg0->y_pos.u.hi;
        arg0->y_speed = 0x80000;
        arg0->x_speed = 0;
        arg0->x_accel = 0;
        if (arg0->unk2 == 2) {
            if ((get_random() & 3) == 0) {
                arg0->ext.main_12.unk80 = 0x10;
                arg0->ext.main_12.unk81 = 1;
            } else {
                arg0->ext.main_12.unk80 = 0xF;
                arg0->ext.main_12.unk81 = 0;
            }
        } else {
            arg0->ext.main_12.unk80 = get_random() & 0xF;
        }
        arg0->gravity = 0;
        arg0->terrain_box = &D_800FB690;
        arg0->hurt_box = &D_800FB698;
        arg0->attack_box = &D_800FB694;
        set_animation(ANIMATED_OBJECT(arg0), 2);
        break;

    case 1: {
        struct Unk_unk68* bounds;
        s16 x;
        s16 y;

        move_with_gravity(ANIMATED_OBJECT(arg0));
        bounds = arg0->terrain_box;
        x = arg0->x_pos.i.hi + bounds->unk0;
        y = arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 + 4;
        if (func_8002D724(PLAYER_OBJECT(arg0), x, y) != 0x24) {
            arg0->unk6 = 2;
            set_animation(ANIMATED_OBJECT(arg0), 9);
        } else if (arg0->unk7 == 0) {
            spawn_common_effect(arg0, 1);
            arg0->unk7 = 1;
            func_8001540C(2, 0x25, arg0);
        }
        transition = (u8)arg0->collision_flags & 4;
        break;
    }

    case 2:
        move_with_gravity(ANIMATED_OBJECT(arg0));
        transition = arg0->y_pos.i.hi < g_Player.y_pos.i.hi;
        break;
    }

    if (transition) {
        hover_sentry_face_player(arg0);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        set_animation(ANIMATED_OBJECT(arg0), 0xA);
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_8004BF5C(struct MainObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        if (arg0->animation_step.fields.event != 0) {
            arg0->unk6 = 1;
            set_animation(ANIMATED_OBJECT(arg0), 6);
        }
        break;
    case 1:
        if (arg0->animation_step.fields.event != 0) {
            arg0->unk6 = 2;
            set_animation(ANIMATED_OBJECT(arg0), 7);
            arg0->terrain_box = &D_800FB69C;
            arg0->hurt_box = &D_800FB6A4;
            arg0->attack_box = &D_800FB6A0;
        }
        break;
    case 2:
        if (arg0->animation_step.fields.event != 0) {
            arg0->unk6 = 3;
            arg0->unk7E = 10;
        }
        break;
    case 3:
        if (--arg0->unk7E == 0) {
            u8 direction;

            arg0->unk6 = 4;
            arg0->ext.main_12.unk8C = 0;
            direction = (u8)angle_to_object(
                OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
            if ((u8)(direction - 8) < 0x10) {
                arg0->unk15 = 0;
                if (direction < 0xC)
                    direction = 0xC;
                if (direction >= 0x15)
                    direction = 0x14;
            } else {
                arg0->unk15 = 0x40;
                if ((u8)(direction - 0x18) < 4)
                    direction = 0x1C;
                else if ((u8)(direction - 5) < 3)
                    direction = 4;
            }
            set_velocity_from_angle(MOVING_OBJECT(arg0), direction);
            arg0->x_accel = 0;
            arg0->gravity = 0;
            arg0->x_speed *= 6;
            arg0->y_speed *= 6;
            set_animation(ANIMATED_OBJECT(arg0), 8);
        }
        break;
    case 4: {
        struct Unk_unk68* bounds;
        s16 x;
        s16 y;

        move_with_gravity(ANIMATED_OBJECT(arg0));
        bounds = arg0->terrain_box;
        x = arg0->x_pos.i.hi + bounds->unk0 + bounds->unk2;
        y = arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3;
        if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0x24) {
            s16 tile = x / 16;
            if ((u16)tile != arg0->ext.main_12.unk8C) {
                spawn_common_effect(arg0, 1);
                func_8001540C(2, 0x25, arg0);
                arg0->ext.main_12.unk8C = tile;
            }
        }
        break;
    }
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_8004E8E0(struct MainObj* arg0)
{
    arg0->hp = 0x10;
    arg0->contact_damage = 3;
    arg0->invincibility_timer = 0;
    arg0->collision_data = D_80106A74;
    arg0->animation_table = (const u8* const*)trident_mech_animations;
    arg0->unk16 = 6;
    arg0->terrain_box = &D_800FBBC8;
    arg0->hurt_box = &trident_mech_stunned_hurt_box;
    arg0->attack_box = &trident_mech_attack_box;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    trident_mech_face_player(ANIMATED_OBJECT(arg0));

    arg0->ext.main_16.unk80 = 0;
    arg0->ext.main_16.unk84 = 0;
    arg0->ext.main_16.unk8C = 0;
    arg0->ext.main_16.unk90 = 0;
    arg0->ext.main_16.shot_09_active = 1;

    switch (arg0->unk2) {
    case 0:
        set_animation(ANIMATED_OBJECT(arg0), 0);
        arg0->unk5 = 2;
        break;
    case 1:
        set_animation(ANIMATED_OBJECT(arg0), 2);
        arg0->unk5 = 2;
        break;
    case 2:
        set_animation(ANIMATED_OBJECT(arg0), 1);
        arg0->unk7C = 0x14;
        arg0->unk5 = 9;
        break;
    case 3:
        set_animation(ANIMATED_OBJECT(arg0), 2);
        arg0->unk5 = 0xA;
        break;
    case 4:
        set_animation(ANIMATED_OBJECT(arg0), 0x11);
        arg0->unk7E = 3;
        arg0->unk5 = 8;
        arg0->unk42 += 2;
        break;
    case 5:
        set_animation(ANIMATED_OBJECT(arg0), 2);
        arg0->unk7E = 3;
        arg0->unk5 = 2;
        arg0->unk42 += 2;
        break;
    }

    arg0->state = 1;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

void func_8004FD38(struct MainObj* arg0, s32 animation)
{
    struct MiscObj* misc;
    struct Unk_unk68* bounds;
    s16 x;
    s16 y;
    s32 resource;

    if (arg0->air_state != 0)
        return;

    bounds = arg0->terrain_box;
    x = arg0->x_pos.i.hi + bounds->unk0;
    y = arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 - 4;
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) != 0x24)
        return;

    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 5;
        misc->animation_table = (u32**)common_effect_animations;
        misc->unk42 = 0x7888;
        misc->unk40 = (u16)((u32)D_801406A8[4] >> 7);
        misc->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 4);
        misc->bg_offset = arg0->bg_offset;
        misc->y_pos.val = arg0->y_pos.val + FIXED(6);
        misc->unk15 = arg0->unk15;
        if ((s8)animation == 2) {
            misc->unk2 = 1;
            misc->ext.misc_5.owner = arg0;
            misc->x_pos.val = arg0->x_pos.val - FIXED(13);
        } else {
            misc->unk2 = 0;
            misc->x_pos.val = arg0->x_pos.val;
        }
        misc->ext.misc_5.animation = (s8)animation;
        misc->state = 3;
    }

    if ((s8)animation != 2)
        return;

    misc = find_free_misc_obj();
    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 5;
    misc->unk2 = 1;
    misc->animation_table = (u32**)common_effect_animations;
    resource = func_8002938C(0x84);
    misc->unk40 = (u16)((u32)D_801406A8[resource] >> 7);
    resource = func_8002938C(0x84);
    misc->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
    misc->unk42 = 0x7888;
    misc->bg_offset = arg0->bg_offset;
    misc->y_pos.val = arg0->y_pos.val + FIXED(6);
    misc->unk15 = arg0->unk15;
    misc->state = 3;
    misc->ext.misc_5.animation = (s8)animation;
    misc->ext.misc_5.owner = arg0;
    misc->x_pos.val = arg0->x_pos.val + FIXED(13);
}

void func_8004ED60(struct MainObj* arg0)
{
    s32 random;
    s32 distance;

    trident_mech_face_player(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;

    arg0->ext.main_16.unk8C = 0;
    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (distance < 0)
        distance = -distance;

    if (distance < 0x61) {
        if (weapon_objects[0].active != 0)
            goto choose_state_6;
        if ((get_random() & 7) < 5)
            goto choose_state_6;
        set_animation(ANIMATED_OBJECT(arg0), 0x10);
        arg0->ext.main_16.unk80 = 1;
        arg0->ext.main_16.unk90 = 1;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }

    random = get_random() & 0xF;
    if (weapon_objects[0].active != 0) {
        if (random < 0xC) {
            set_animation(ANIMATED_OBJECT(arg0), 0x10);
            arg0->ext.main_16.unk90 = 1;
            arg0->ext.main_16.unk80 = 0;
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            return;
        }
        if (random < 0xE) {
            set_animation(ANIMATED_OBJECT(arg0), 0x10);
            arg0->ext.main_16.unk80 = 1;
            arg0->ext.main_16.unk90 = 1;
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            return;
        }
    } else {
        if (random < 0xC) {
            set_animation(ANIMATED_OBJECT(arg0), 0x11);
            arg0->unk5 = 8;
            arg0->unk6 = 0;
            return;
        }
        if (random < 0xE) {
            set_animation(ANIMATED_OBJECT(arg0), 0x10);
            arg0->ext.main_16.unk80 = 1;
            arg0->ext.main_16.unk90 = 1;
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            return;
        }
    }

choose_state_6:
    arg0->ext.main_16.unk8C = 1;
    arg0->invincibility_timer = (u8)engine_obj.cur_character;
    trident_mech_fire_tracked_shot(arg0);
    arg0->unk5 = 6;
    arg0->unk6 = 0;
}

void func_8004F1A0(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;

    arg0->hurt_box = &trident_mech_stunned_hurt_box;
    trident_mech_face_player(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 >= 4) {
        arg0->unk7E = 3;
        set_animation(ANIMATED_OBJECT(arg0), 0x11);
        arg0->unk5 = 8;
    } else {
        set_animation(ANIMATED_OBJECT(arg0), 0);
        arg0->unk5 = 2;
    }
    arg0->unk6 = 0;
}

void func_8009B0B8(struct ShotObj* arg0)
{
    arg0->unk58.collision_bounds = D_801060F0;
    arg0->unk16 = 5;
    arg0->unk54 = trident_shot_flash_box;
    arg0->unk50.data = trident_shot_flash_box;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->unk68 = NULL;
    arg0->unk84.value = 0x1E;
    arg0->unk42 &= 0x7FFF;
    set_animation(ANIMATED_OBJECT(arg0), 5);
}

void func_8009B1E8(struct ShotObj* arg0)
{
    s32 index = arg0->unk2;

    arg0->state = 4;
    arg0->on_screen = 1;
    arg0->unk58.collision_data = D_80106070;
    arg0->unk54 = trident_shot_hit_box;
    arg0->unk50.data = trident_shot_hit_box;
    arg0->unk42 &= 0x7FFF;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    if (arg0->unk15 == 0)
        arg0->x_pos.i.hi += trident_shot_muzzle_offsets[index][0];
    else
        arg0->x_pos.i.hi -= trident_shot_muzzle_offsets[index][0];
    arg0->y_vel.val *= 4;
    arg0->x_vel.val *= 4;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->y_pos.i.hi += trident_shot_muzzle_offsets[index][1];
    set_animation(ANIMATED_OBJECT(arg0), index + 8);
}

void func_8009B6B8(struct ShotObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk54 = enemy_bullet_hit_box;
    arg0->unk50.data = enemy_bullet_hit_box;
    arg0->unk58.collision_data = D_80106070;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk60 = 3;
    arg0->x_vel.val *= 3;
    arg0->y_vel.val *= 3;
    set_animation(ANIMATED_OBJECT(arg0), 0x11);
}

void func_80091B1C(struct MainObj* arg0)
{
    struct Unk_unk68* bounds;
    s32 velocity = arg0->x_speed;
    s16 x;
    s16 y;
    s32 reverse = 0;

    if (!(arg0->collision_flags & 8)) {
        arg0->unk5 = 1;
        arg0->unk6 = 0;
        arg0->unk7C = 0;
        arg0->x_speed = 0;
        arg0->y_speed = 0;
        arg0->x_accel = 0;
        arg0->gravity = 0x4200;
        arg0->ext.main_76.saved_x_velocity = velocity;
        return;
    }

    bounds = arg0->terrain_box;
    y = arg0->y_pos.i.hi + bounds->unk1 + (u8)bounds->unk3 + 4;
    if (arg0->x_speed < 0) {
        reverse = (arg0->collision_flags & 2) != 0;
        x = arg0->x_pos.i.hi + bounds->unk0 - (u8)bounds->unk2;
    } else {
        reverse = (arg0->collision_flags & 1) != 0;
        x = arg0->x_pos.i.hi + bounds->unk0 + (u8)bounds->unk2;
    }
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) < 0x38)
        reverse = 1;
    if (reverse)
        arg0->x_speed = -arg0->x_speed;
    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_800C63BC(struct ItemObj* arg0)
{
    struct ItemObj* child;
    s32 discard;
    u8 resource;
    s32 column;
    s32 row;

    discard = g_Player.unk2 != 0;
    if (engine_obj.unk37 != 0) {
        if (g_Player.armor_parts != 0)
            discard = 1;
    } else {
        if (light_capsule_part_bits[(u8)arg0->unk2] & g_Player.armor_parts)
            discard = 1;
        if (arg0->unk2 == 2 && g_Player.arm_type == 2)
            discard = 0;
        if (arg0->unk2 == 3 && g_Player.arm_type == 1)
            discard = 0;
    }

    if (discard) {
        despawn_object(OBJECT_HEADER(arg0));
        return;
    }

    arg0->on_screen = 1;
    arg0->unk68 = (struct Unk_unk68*)light_capsule_terrain_box;
    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0xA2) & 0xFF;
    arg0->animation_table = (const u8* const*)light_capsule_animations;
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
    arg0->unk40 = (u16)((u32)D_801406A8[resource] >> 7);
    column = resource * 4 + 0x18;
    row = resource + 6;
    arg0->unk42 = (u16)((column - (column & 0x7F0)) | (((row >> 2) + 0x1E0) << 6));
    arg0->unk16 = 4;
    arg0->unk15 = 0;
    arg0->unk75 = 1;
    g_Player.item_step = 0;
    set_animation(ANIMATED_OBJECT(arg0), 0);

    do {
        arg0->y_pos.u.hi += 0x10;
        CollisionRelated(PLAYER_OBJECT(arg0));
    } while (!(arg0->unk70 & 8));

    child = find_free_item_obj();
    if (child != NULL) {
        child->active = 1;
        child->id = 0x1A;
        child->unk2 = 6;
        child->unk7C.object = arg0;
        child->bg_offset = arg0->bg_offset;
    }

    light_capsule_spawn_visual(arg0, 0x23, light_capsule_part_visuals[(u8)arg0->unk2]);
    arg0->unk5 = 0;
    arg0->state++;
    collide_with_players(PLAYER_OBJECT(arg0));
    update_on_screen(BASE_OBJECT(arg0), 0x88, 0x88);
}

s32 func_800B8490(struct EffectObj* arg0)
{
    if ((u16)(arg0->x_pos.i.hi - background_objects[0].x_pos.i.hi + 0x40) >= 0x1C0)
        return 1;
    return (u16)(arg0->y_pos.i.hi - background_objects[0].y_pos.i.hi + 0x40) >= 0x170;
}

void func_800B8114(struct EffectObj* arg0)
{
    struct Effect12Ext* ext = &arg0->ext.effect_12;
    struct MainObj* child;
    s32 distance;
    u8 index;
    s16 i;

    if (func_800B8490(arg0) != 0) {
        arg0->state = 2;
        return;
    }

    for (i = 0; i < ext->child_count; i++) {
        child = ext->children[i];
        if (child != NULL && child->active == 0)
            ext->children[i] = NULL;
    }

    switch (arg0->unk5) {
    case 0:
        distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
        if (distance < 0)
            distance = -distance;
        if ((s16)distance < 0x80)
            arg0->unk5 = 1;
        break;
    case 1:
        for (i = 0; i < ext->child_count; i++) {
            if (ext->children[i] != NULL)
                continue;
            if (ext->cooldown != 0) {
                ext->cooldown--;
                continue;
            }
            child = find_free_main_obj();
            if (child == NULL)
                continue;
            ext->children[i] = child;
            child->active = 0x41;
            child->id = ext->child_id;
            child->unk2 = ext->child_subtype;
            child->x_pos.val = arg0->x_pos.val;
            child->y_pos.val = arg0->y_pos.val;
            ext->cooldown = 0x20;
            index = func_8002938C(child->id);
            child->unk40 = D_801406A8[index] >> 7;
            index = func_8002938C(child->id);
            child->unk42 = SOME_COORDINATE_CONVERSION(index);
            index = func_8002938C(child->id);
            child->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[index];
            ext->spawned++;
            if (ext->spawned >= ext->child_count)
                arg0->unk5 = 2;
        }
        break;
    case 2:
        child = NULL;
        for (i = 0; i < ext->child_count; i++)
            child = ext->children[i];
        if (child == NULL) {
            arg0->unk5 = 3;
            ext->spawned = 0;
            ext->cooldown = 0;
            ext->timer = 0x60;
        }
        break;
    case 3:
        if (--ext->timer == 0)
            arg0->unk5 = 0;
        break;
    }
}

struct Item05MotionConfig {
    u32 collision_mode;
    s32 velocity;
    s16 acceleration;
    s16 unused;
};

struct Item05StageConfig {
    u16 tile;
    u16 index;
    u16 x;
    u16 y;
};

extern void* moving_lift_animations[4];
extern struct Item05MotionConfig moving_lift_motion[9];
extern struct Item05StageConfig moving_lift_placements[9];
extern u8 moving_lift_boxes[9][4];
void moving_lift_spawn_effect(struct ItemObj*);
void moving_lift_spawn_all(void);

void func_800C0EBC(struct ItemObj* arg0)
{
    s8 index;

    arg0->active = 0x41;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)moving_lift_animations;
    arg0->unk42 = 0x788C;
    arg0->unk40 = D_801406A8[5] >> 7;
    arg0->unk16 = 6;
    arg0->unk5C = 0xF;
    arg0->unk61 = 0;
    arg0->unk54 = NULL;
    index = arg0->unk2;
    arg0->unk68 = (struct Unk_unk68*)moving_lift_boxes[index];
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[5];
    arg0->x_pos.i.hi = moving_lift_placements[index].x;
    arg0->y_pos.i.hi = moving_lift_placements[index].y;
    arg0->y_vel.val = moving_lift_motion[index].velocity;
    arg0->unk2C = (u16)moving_lift_motion[index].acceleration;
    arg0->unk75 = 1;
    arg0->unk76 = 0;
    set_animation(arg0, (u8)moving_lift_motion[index].collision_mode != 0 ? 2 : 0);
    moving_lift_spawn_effect(arg0);
    if (arg0->unk2 == 0)
        moving_lift_spawn_all();
}

void func_800C1050(struct ItemObj* arg0)
{
    const struct Item05MotionConfig* config;
    s32 offset;
    s32 y;
    u8 old_flags;
    u8 flags;

    update_on_screen(BASE_OBJECT(arg0), moving_lift_boxes[arg0->unk2][2], moving_lift_boxes[arg0->unk2][3]);
    config = &moving_lift_motion[arg0->unk2];
    if (arg0->unk76 == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        arg0->y_vel.val = config->velocity;
    } else if ((u8)config->collision_mode != 0) {
        arg0->y_vel.val = -0x1A000;
    }

    offset = arg0->y_pos.val - g_Player.y_pos.val;
    old_flags = g_Player.unk71;
    move_object((struct MovingObj*)arg0);
    collide_with_players(PLAYER_OBJECT(arg0));
    flags = g_Player.unk71;
    if (flags != old_flags && (flags & 3)) {
        y = arg0->y_pos.val - offset - arg0->y_vel.val / 4;
        g_Player.y_pos.val = y;
        g_Player.unk71 = 0;
        collide_with_players(PLAYER_OBJECT(arg0));
        g_Player.y_pos.val = y;
        if (g_Player.unk71 & 3)
            g_Player.y_pos.val = y + g_Player.y_vel.val;
        else
            g_Player.y_pos.val = y - arg0->y_vel.val * 3;
        g_Player.unk71 = flags;
    }

    if (arg0->y_pos.i.hi >= 0x621) {
        arg0->y_pos.i.hi = 0x4E0;
        arg0->y_vel.val = config->velocity;
    }
}

void player_enter_ladder_climb_off_top(struct PlayerObj* arg0);
void player_enter_ladder_step_off_bottom(struct PlayerObj* arg0);

s32 func_80033FF0(struct PlayerObj* arg0)
{
    u8 attribute = func_8002D994(arg0);

    if (arg0->unk88.bytes.collision_flags & 8) {
        player_enter_ladder_step_off_bottom(arg0);
        return 1;
    }
    if ((arg0->input.buttons.held & 4) && attribute == 0x21) {
        player_enter_ladder_climb_off_top(arg0);
        return 1;
    }
    if ((u8)(attribute - 0x20) < 2 && !(arg0->pressed_input & 0x80))
        return 0;
    player_set_animation(arg0, 0x1E);
    arg0->unk5 = 0xE;
    arg0->unk6 = 4;
    return 1;
}

void player_enter_frost_tower_pose(struct PlayerObj* arg0);
void player_enter_soul_body(struct PlayerObj* arg0);
void player_enter_rising_fire(struct PlayerObj* arg0, s32 arg1);
void player_enter_rising_fire_charged(struct PlayerObj* arg0, s32 arg1);
void player_enter_double_cyclone_pose(struct PlayerObj* arg0);
s32 player_check_nova_strike(struct PlayerObj* arg0);
void player_update_shooting(struct PlayerObj* arg0);
void player_enter_ladder_shoot(struct PlayerObj* arg0);

void func_80037484(struct PlayerObj* arg0, s32 arg1)
{
    switch ((s8)(arg0->shot_type - 2)) {
    case 0:
    case 9:
        player_enter_frost_tower_pose(arg0);
        break;
    case 10:
        player_enter_soul_body(arg0);
        break;
    case 2:
        player_enter_rising_fire(arg0, arg1);
        break;
    case 11:
        player_enter_rising_fire_charged(arg0, arg1);
        break;
    case 5:
    case 14:
        player_enter_double_cyclone_pose(arg0);
        break;
    }
}

void func_800B6660(struct EffectObj* arg0);

static u8 effect_05_probe(s16 x, s32 y_offset)
{
    s16 y = (u16)g_Player.y_pos.i.hi + y_offset;

    if (g_Player.unk68 != NULL)
        y += (s8)g_Player.unk68->unk1 + g_Player.unk68->unk3;

    return func_8002D724(&g_Player, x, y);
}

static void effect_05_dispatch(struct EffectObj* arg0)
{
    if (arg0->state < 2)
        tile_scanner_state_funcs[arg0->state](arg0);
    else
        tile_scanner_fill_funcs[arg0->state - 2](arg0);
}

void func_800B60BC(struct EffectObj* arg0)
{
    struct Effect5Ext* ext = &arg0->ext.effect_5;
    s32 delta;
    s32 step;
    u8 tile;

    ext->unk21 = ext->unk20;
    ext->unk20 = effect_05_probe(g_Player.x_pos.i.hi, 0);
    delta = g_Player.x_pos.val - g_Player.unk18.val;
    if (g_Player.state != 1)
        goto facing;

    for (;;) {
        switch (ext->unk20) {
        case 0:
            if (arg0->state == 2)
                tile_scanner_fill_funcs[0](arg0);
            goto record;
        case 16:
            ext->unk20 = effect_05_probe(g_Player.x_pos.i.hi, -0x10);
            continue;
        case 17:
        case 18:
        case 19:
        case 20:
        case 25:
        case 26:
            arg0->state = 1;
            if (ext->unk21 == 0x3C && g_Player.unk15 != 0 && g_Player.unk5 != 0xC)
                goto hold;
            step = delta - 0x38000;
            if (step < -0x68000)
                step = -0x68000;
            goto push;
        case 21:
        case 22:
        case 23:
        case 24:
        case 27:
        case 28:
            arg0->state = 1;
            if (ext->unk21 == 0x3C && g_Player.unk15 == 0 && g_Player.unk5 != 0xC)
                goto hold;
            step = delta + 0x38000;
            if (step > 0x68000)
                step = 0x68000;
            goto push;
        case 60:
            effect_05_dispatch(arg0);
            goto record;
        default:
            arg0->state = 1;
            goto record;
        }
    }

hold:
    g_Player.x_pos.val = g_Player.unk18.val;
    goto probe;
push:
    g_Player.x_pos.val = g_Player.unk18.val + step;
probe:
    tile = effect_05_probe(g_Player.x_pos.i.hi, 0);
    ext->unk20 = tile;
    if (tile < 0x1D) {
        if (tile >= 0x10)
            goto facing;
        if (tile == 0 && arg0->state == 2)
            goto record;
    }
    effect_05_dispatch(arg0);
record:
    ext->unk1C = g_Player.unk5;
facing:
    if (g_Player.x_pos.val != g_Player.unk18.val)
        ext->unk1E = (g_Player.x_pos.val >= g_Player.unk18.val) << 6;
}

void func_800B64BC(struct EffectObj* arg0)
{
    struct Effect5Ext* ext = &arg0->ext.effect_5;

    ext->unk1F = 0;
    if (g_Player.state != 1)
        return;

    switch (g_Player.unk5) {
    case 48:
        if (ext->unk1C != 0x32)
            return;
        ext->unk14 = g_Player.x_vel.val;
        goto adjust;
    case 2:
        ext->unk14 = g_Player.x_pos.val - g_Player.unk18.val;
    adjust:
        if (ext->unk1C == 3)
            ext->unk14 = ext->unk1E != 0 ? 0x8000 : -0x8000;
        if (ext->unk1C == 4)
            ext->unk14 = ext->unk1E != 0 ? 0x20000 : -0x20000;
        goto accelerate;
    case 5:
    case 8:
        ext->unk14 = g_Player.x_vel.val;
    accelerate:
        if (ext->unk1E != 0) {
            ext->unk18 = -0x1800;
            ext->unk1D = 1;
        } else {
            ext->unk18 = 0x1800;
            ext->unk1D = 0;
        }
        break;
    case 12: {
        s32 speed;

        if (g_Player.unk6 != 2)
            return;
        ext->unk14 = 0;
        speed = g_Player.x_vel.val;
        if (speed < 0)
            speed = -speed;
        ext->unk1F = speed / 0xC000;
        ext->unk1E = g_Player.unk15;
        if (g_Player.unk15 != 0) {
            ext->unk18 = 0x2800;
            ext->unk1D = 3;
        } else {
            ext->unk18 = -0x2800;
            ext->unk1D = 2;
        }
        break;
    }
    default:
        return;
    }
    arg0->state++;
}

static int effect_05_tile_slides(u8 tile)
{
    return tile == 0x3C || tile == 0 || tile == 0x18 || tile == 0x1C || tile == 0x14 || tile == 0x1A;
}

void func_800B6660(struct EffectObj* arg0)
{
    struct Effect5Ext* ext = &arg0->ext.effect_5;
    s16 x;
    s16 previous;

    if (g_Player.unk5 == 6 || g_Player.unk5 == 9 || (g_Player.unk88.bytes.collision_flags & 3)) {
        arg0->state = 1;
        return;
    }

    if (ext->unk1D < 2) {
        arg0->x_pos.val = g_Player.x_pos.val + ext->unk14;
        ext->unk14 += ext->unk18;
        if (!effect_05_tile_slides(effect_05_probe(arg0->x_pos.i.hi, 0))) {
            g_Player.x_pos.val = arg0->x_pos.val;
            arg0->state = 1;
            return;
        }
        g_Player.x_pos.val = arg0->x_pos.val;
        if (ext->unk1D != 0 ? ext->unk14 < 0 : ext->unk14 >= 0)
            arg0->state = 1;
    } else if (--ext->unk1F == 0xFF) {
        ext->unk18 = ext->unk18 > 0 ? -0x600 : 0x600;
        ext->unk1D -= 2;
        func_800B6660(arg0);
    } else {
        s32 moved;

        arg0->x_pos.val = g_Player.x_pos.val + ext->unk14;
        ext->unk14 += ext->unk18;
        if (!effect_05_tile_slides(effect_05_probe(arg0->x_pos.i.hi, 0))) {
            g_Player.x_pos.val = arg0->x_pos.val;
            arg0->state = 1;
            return;
        }
        g_Player.x_pos.val = arg0->x_pos.val;
        if (g_Player.unk5 != 0xC && g_Player.unk6 != 2) {
            moved = arg0->x_pos.val - g_Player.unk18.val;
            if (ext->unk14 > 0 ? ext->unk14 < moved : moved < ext->unk14)
                arg0->state = 1;
        }
    }

    x = g_Player.x_pos.i.hi;
    previous = g_Player.unk18.i.hi;
    if (ext->unk1D & 1) {
        if (g_Player.x_pos.val < g_Player.unk18.val && previous == x)
            arg0->state = 1;
    } else if (g_Player.unk18.val < g_Player.x_pos.val) {
        if (x - previous < 0 ? x != (s16)(previous - 1) : x - previous != 1)
            arg0->state = 1;
    }
}

extern u8* crumble_sequencer_groups[8];

s32 func_800B9E54(struct Effect21SpawnRecord* record)
{
    struct BackgroundObj* background = &background_objects[g_Player.bg_offset];

    if ((u16)(record->x - background->x_pos.i.hi + 0x280) >= 0x640)
        return 0;
    return (u16)(record->y - background->y_pos.i.hi + 0x1E0) < 0x4B0;
}

void func_800B9EC0(struct EffectObj* arg0)
{
    struct Effect21Ext* ext = &arg0->ext.effect_21;

    ext->timer = 0;
    arg0->state++;
    switch (arg0->unk2) {
    case 0:
        ext->spawned = 0;
        ext->phase = 0;
        break;
    case 1:
    case 2:
    case 4:
    case 5:
        ext->cursor = crumble_sequencer_sequences[ext->index & 0x7F];
        break;
    case 3:
        ext->index = 8;
        break;
    }
}

void func_800B9F38(struct EffectObj* arg0)
{
    struct Effect21Ext* ext = &arg0->ext.effect_21;
    struct EffectObj* effect;
    u8* list;
    u32 bit;
    u8 id;

    ext->was_inside = ext->inside;
    if ((u16)(g_Player.x_pos.i.hi - 0x2A1) < 0x9BF)
        ext->inside = 1;
    if (ext->inside == 0)
        return;
    if (ext->inside != ext->was_inside) {
        ext->phase = 0;
        ext->timer = 0;
    }
    if (ext->timer != 0) {
        ext->timer--;
        return;
    }

    list = crumble_sequencer_groups[ext->phase * 2 + ext->inside - 1];
    do {
        id = *list & 0x7F;
        bit = 1 << id;
        if ((u8)func_800B9E54(crumble_sequencer_sequences[id]) != 0 && !(ext->spawned & bit)) {
            effect = find_free_effect_obj();
            if (effect != NULL) {
                effect->active = 1;
                effect->id = 0x15;
                effect->unk2 = 1;
                effect->ext.effect_21.index = id;
                ext->spawned |= bit;
            }
        }
    } while (!(*list++ & 0x80));

    list = crumble_sequencer_groups[((ext->phase + 2) & 3) * 2 + ext->inside - 1];
    do {
        id = *list & 0x7F;
        bit = 1 << id;
        if (ext->spawned & bit) {
            effect = find_free_effect_obj();
            if (effect != NULL) {
                effect->active = 1;
                effect->id = 0x15;
                effect->unk2 = 2;
                effect->ext.effect_21.index = id;
                ext->spawned &= ~bit;
            }
        }
    } while (!(*list++ & 0x80));

    ext->phase = (ext->phase + 1) & 3;
    ext->timer = ext->inside == 1 ? 0x96 : 0x8C;
}

extern u16 bg_zone_controller_b_zone_bounds[6];

void func_800BA178(struct EffectObj* arg0)
{
    struct Effect21Ext* ext = &arg0->ext.effect_21;
    struct MiscObj* misc;
    struct ItemObj* item;
    struct EffectObj* effect;

    if (arg0->unk5 != 0) {
        if (--ext->timer != 0)
            return;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x15;
            effect->unk2 = 5;
            effect->ext.effect_21.index = ext->index;
        }
        arg0->state++;
        return;
    }

    if (ext->timer != 0) {
        ext->timer--;
        return;
    }
    misc = find_free_misc_obj();
    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 8;
    misc->x_pos.i.hi = ext->cursor->x;
    misc->y_pos.i.hi = ext->cursor->y;
    misc->unk2 = ext->cursor->object_id;
    if (!(arg0->unk2 & 1)) {
        misc->unk2 = ext->cursor->flags | 0x80;
        ext->timer = 4;
    } else {
        ext->timer = 3;
    }
    if (!(ext->cursor->flags & 0x80)) {
        ext->cursor++;
        return;
    }
    if (arg0->unk2 == 4) {
        ext->timer = 0x78;
        arg0->unk5++;
        return;
    }
    if (arg0->unk2 == 5) {
        item = find_free_item_obj();
        if (item != NULL) {
            item->active = 1;
            item->id = 0x11;
            item->unk2 = ext->index - 8;
        }
    }
    arg0->state++;
}

void func_800B8E74(struct EffectObj* arg0)
{
    s8 index;

    if (g_Player.y_pos.i.hi < 0x500) {
        for (index = 0; index < 2; index++) {
            if (g_Player.x_pos.i.hi - (s16)bg_zone_controller_b_zone_bounds[index] < 0)
                break;
        }
        if (index == 2)
            index = 1;
    } else {
        for (index = 2; index < 5; index++) {
            if (g_Player.x_pos.i.hi - (s16)bg_zone_controller_b_zone_bounds[index] < 0)
                break;
        }
    }
    arg0->ext.effect_15.unk14 = index;
    if (index != arg0->ext.effect_15.unk15) {
        arg0->unk5 = index;
        arg0->unk6 = 0;
    }
}

extern u8 bg_wind_steps_fast[];

void func_800B76A4(struct EffectObj* arg0)
{
    struct Effect9Ext* ext = &arg0->ext.effect_9;

    if (ext->direction != 0) {
        background_objects[2].y_pos.val = 0;
        ext->transition_timer = 1;
        background_objects[2].unk4C = 1;
        arg0->unk5 = 0;
        arg0->state--;
        return;
    }
    background_objects[2].y_pos.val = 0x1800000;
    background_objects[2].unk4C = 1;
    ext->movement_timer = 0x168;
    ext->movement_table = bg_wind_steps_fast;
    ext->timer = ext->movement_table[0];
    ext->frame = ext->movement_table[1];
    ext->target_x = ext->movement_table[2];
    background_objects[2].x_pos.i.hi = (ext->target_x << 9) + (u8)background_objects[2].x_pos.i.hi;
    ext->velocity = 0x10000;
    arg0->unk5++;
}

extern u8 bg_wind_steps_slow[];

void func_80050278(struct MainObj* arg0)
{
    struct Main17Ext* ext = &arg0->ext.main_17;
    s32 dx;

    if (--ext->unk80 != 0) {
        if (arg0->collision_flags & 3)
            arg0->unk15 ^= 0x40;
        arg0->x_speed = arg0->unk15 != 0 ? 0x10000 : -0x10000;
        arg0->y_speed = 0x80000;
        ext->saved_unk5 = arg0->y_pos.val;
        move_object(MOVING_OBJECT(arg0));
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }

    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (dx < 0)
        dx = -dx;
    if (!(dx < 0x61 && arg0->y_pos.i.hi - g_Player.y_pos.i.hi < 0x11) && --ext->unk88 != 0) {
        if (--ext->unk84 == 0) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            set_animation(arg0, 1);
        } else {
            arg0->unk7C = 0x14;
            arg0->unk5 = 6;
            arg0->unk6 = 0;
        }
        return;
    }
    arg0->x_speed = arg0->unk15 != 0 ? 0x30000 : -0x30000;
    arg0->x_accel = -0x1000;
    ext->unk8C = 1;
    arg0->unk5 = 4;
    arg0->unk6 = 0;
    set_animation(arg0, 2);
}

extern void (*heavy_mech_step_funcs[])(struct MainObj*);
extern u8 heavy_mech_debris[];
void heavy_mech_check_fall(struct MainObj* arg0);
void heavy_mech_check_catch(struct MainObj* arg0);

void func_8004C860(struct MainObj* arg0)
{
    heavy_mech_check_fall(arg0);
    heavy_mech_check_catch(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    heavy_mech_step_funcs[arg0->unk5](arg0);
    if (arg0->state != 2)
        func_8002D9BC(arg0);
    arg0->ext.main_13.saved_unk5 = arg0->unk5;
    if (func_8002DD04(arg0) < 0) {
        spawn_explosion(BASE_OBJECT(arg0));
        spawn_debris(9, heavy_mech_debris, arg0);
        drop_item(BASE_OBJECT(arg0), 8);
        arg0->unk7C = 0x20;
        arg0->unk7E = 6;
        arg0->on_screen = 0;
        arg0->state = 2;
        return;
    }
    if (arg0->state == 2)
        return;
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x68, 0x68) != 0) {
        arg0->state = 3;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x48, 0x48);
}

void heavy_mech_face_player(struct AnimatedObj* arg0);

void func_8004CA94(struct MainObj* arg0)
{
    u8 roll;
    s32 dx;
    u32 animation;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    roll = get_random() & 0xF;
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (dx < 0)
        dx = -dx;
    if (roll < 2) {
        arg0->unk7C = 0x3C;
        return;
    }
    if (roll < 4) {
        arg0->ext.main_13.unk80 = 0x8001;
        return;
    }
    animation = roll < (dx < 0x81 ? 12 : 8) ? 2 : 1;
    heavy_mech_face_player(ANIMATED_OBJECT(arg0));
    set_animation(arg0, animation);
    arg0->ext.main_13.unk88 = animation;
    arg0->unk5 = 4;
    arg0->unk6 = 0;
}

extern u8 mech_boulder_shockwave_boxes[28];
extern u8 mech_boulder_debris[8];

void func_8009A5F4(struct ShotObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk15 != 0)
        arg0->x_pos.i.hi += 0x20;
    else
        arg0->x_pos.i.hi -= 0x20;
    arg0->y_vel.val = 0x70000;
    arg0->unk2C = 0x4200;
    arg0->unk16 = 0;
    arg0->y_pos.i.hi = (u16)arg0->y_pos.i.hi + 0x18;
    arg0->x_vel.val = arg0->unk15 != 0 ? 0x2C000 : -0x2C000;
    arg0->unk54 = mech_boulder_shockwave_boxes;
    arg0->unk50.data = mech_boulder_shockwave_boxes;
    arg0->unk5C = 6;
    arg0->unk68 = NULL;
    arg0->unk60 = 2;
    set_animation(arg0, 5);
}

void func_800B7CFC(struct EffectObj* arg0)
{
    struct Effect9Ext* ext = &arg0->ext.effect_9;
    s32 target;

    if (--ext->movement_timer == 0) {
        ext->direction = 1;
        ext->movement_timer = 0x78;
        ext->movement_table = bg_wind_steps_slow;
        ext->timer = ext->movement_table[0];
        ext->frame = ext->movement_table[1];
        arg0->unk5--;
        ext->target_x = ext->movement_table[2];
        return;
    }
    if (--ext->timer == 0) {
        ext->movement_table += ext->frame * 4;
        ext->target_x = ext->movement_table[2];
        ext->timer = ext->movement_table[0];
        ext->frame = ext->movement_table[1];
        background_objects[2].unk4C = 1;
        background_objects[2].x_pos.i.hi = (ext->target_x << 9) + (u8)background_objects[2].x_pos.i.hi;
    }
    if (ext->velocity <= 0x47FFF)
        ext->velocity += 0x400;
    background_objects[2].x_pos.val += ext->velocity;
    target = ext->target_x << 9;
    if (background_objects[2].x_pos.i.hi >= target + 0xC0) {
        background_objects[2].x_pos.i.hi = target;
        background_objects[2].unk4C = 1;
    }
    background_objects[2].y_pos.val -= 0x20000;
    if (background_objects[2].y_pos.val == 0x1000000) {
        background_objects[2].y_pos.val = 0x1800000;
        background_objects[2].unk4C = 1;
    }
}

void func_800C9510(struct MiscObj* arg0)
{
    s32 resource;
    u8 alternate;

    arg0->animation_table = (u32**)D_8010DF48;
    alternate = (u8)arg0->unk2 >> 7;
    arg0->ext.misc_8.alternate = alternate;
    arg0->unk2 &= 0x7F;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0x99);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    resource = func_8002938C(0x99);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x99);
    arg0->unk42 = SOME_COORDINATE_CONVERSION(resource);
    arg0->unk16 = 7;
    arg0->unk15 = 0;
    if ((u8)(arg0->unk2 - 0xD) < 6) {
        arg0->unk15 = 0x40;
        arg0->x_pos.i.hi += 0x10;
    }
    arg0->ext.misc_8.timer = 0;
    if (arg0->ext.misc_8.alternate != 0)
        set_animation(arg0, crumbling_tile_second_effects.entries[arg0->unk2].first);
    else
        set_animation(arg0, crumbling_tile_first_effects[arg0->unk2].effect_id);
}

extern union AnimationStep* slope_skier_animations[];
extern struct Unk_unk68 slope_skier_hurt_box[];
extern struct Unk_unk68 slope_skier_terrain_box;
extern struct VisualSpawnOffset D_800FCE90[5];
extern struct Unk_unk68 D_800FCE9C[];
extern union AnimationStep jet_drone_anim_3[];
extern struct Unk_unk68 D_80106DF4[];

void func_800564B4(struct MainObj* arg0)
{
    arg0->unk5 = 1;
    arg0->state++;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    switch (arg0->unk2) {
    case 0:
        arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
        break;
    case 1:
        arg0->unk15 = 0;
        break;
    case 2:
        arg0->unk15 = 0x40;
        break;
    }
    arg0->animation_table = (const u8* const*)slope_skier_animations;
    arg0->unk16 = 6;
    arg0->terrain_box = slope_skier_hurt_box;
    arg0->hurt_box = &slope_skier_terrain_box;
    arg0->attack_box = &slope_skier_terrain_box;
    arg0->hp = 3;
    arg0->contact_damage = 1;
    arg0->collision_data = (const u16*)D_80106DF4;
    arg0->ext.main_23.unk80 = 0;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk7C = 10;
    arg0->ext.main_23.unk81 = 0;
    arg0->ext.main_23.unk82 = 0;
    set_animation(arg0, arg0->ext.main_23.unk80 + 4);
}

void func_80055F1C(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_23.unk80 & 0x80) {
        arg0->y_speed = 0x40000;
        arg0->x_speed = arg0->unk15 != 0 ? 0x30000 : -0x30000;
    } else {
        arg0->y_speed = 0x38000;
        arg0->x_speed = arg0->unk15 != 0 ? 0x48000 : -0x48000;
    }
    arg0->gravity = 0x4200;
    arg0->air_state = 1;
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6++;
        set_animation(arg0, 0x11);
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
}

static struct VisualObj* main_23_spawn_visual(struct MainObj* arg0, u8 facing)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return NULL;
    visual->active = 0x41;
    visual->id = 3;
    visual->unk2 = 5;
    visual->bg_offset = arg0->bg_offset;
    visual->unk15 = facing;
    visual->unk40 = arg0->unk40;
    visual->unk3C = (void*)arg0->sprite_frames;
    visual->animation_table = (u32**)arg0->animation_table;
    visual->unk42 = arg0->unk42;
    return visual;
}

void func_80056054(struct MainObj* arg0)
{
    struct VisualObj* visual;
    u8 i;

    if (arg0->unk6 == 0) {
        arg0->unk6++;
        set_animation(arg0, arg0->ext.main_23.unk80 + 0xA);
        return;
    }
    if (arg0->unk6 != 1)
        return;
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        if (arg0->ext.main_23.unk82 & 1) {
            arg0->unk5 = 1;
            arg0->unk6 = 0;
            arg0->ext.main_23.unk82 &= 0xFE;
            arg0->unk15 ^= 0x40;
        }
        return;
    }
    if (arg0->animation_step.fields.event != 2)
        return;
    for (i = 0; i < 5; i++) {
        visual = main_23_spawn_visual(arg0, arg0->unk15 ^ 0x40);
        if (visual == NULL)
            continue;
        if (arg0->unk15 != 0)
            visual->x_pos.i.hi = arg0->x_pos.i.hi - D_800FCE90[i].x;
        else
            visual->x_pos.i.hi = arg0->x_pos.i.hi + D_800FCE90[i].x;
        visual->y_pos.i.hi = (u16)arg0->y_pos.i.hi + D_800FCE90[i].y;
        visual->unk16 = arg0->unk16;
        arg0->animation_step.fields.event = 0;
    }
}

void func_800562AC(struct MainObj* arg0)
{
    struct Main23Ext* ext = &arg0->ext.main_23;
    struct VisualObj* visual;
    u8 wall;

    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    slope_skier_read_slope(arg0);
    if (ext->unk81 != ext->unk80) {
        if (ext->unk80 == 3 || (ext->unk80 & 0x80)) {
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            set_animation(arg0, ext->unk81 + 0xD);
        } else {
            set_animation(arg0, (ext->unk80 & 0x7F) + 4);
        }
    }
    wall = arg0->unk15 != 0 ? arg0->collision_flags & 1 : arg0->collision_flags & 2;
    if (wall) {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        ext->unk82 |= 1;
    }
    if (--arg0->unk7C != 0)
        return;
    visual = main_23_spawn_visual(arg0, arg0->unk15);
    if (visual == NULL)
        return;
    visual->x_pos.i.hi = arg0->unk15 != 0 ? arg0->x_pos.i.hi - 0x28 : arg0->x_pos.i.hi + 0x28;
    visual->y_pos.i.hi = (u16)arg0->y_pos.i.hi + (s8)(ext->unk80 < 0x80 ? ((u8*)D_800FCE9C)[ext->unk80] : ((u8*)jet_drone_anim_3)[ext->unk80 - 0x80]);
    visual->unk16 = arg0->unk16;
    arg0->unk7C = 5;
}

void func_800B8630(struct EffectObj* arg0)
{
    struct MainObj* main = find_free_main_obj();
    s32 resource;
    s32 row;

    if (main == NULL)
        return;
    main->active = 0x41;
    main->id = 0x15;
    main->unk2 = get_random_nonzero() % 4;
    main->x_pos.val = arg0->x_pos.val;
    main->y_pos.val = arg0->y_pos.val;
    main->unk40 = D_801406A8[(u8)func_8002938C(0x15)] >> 7;
    resource = (u8)func_8002938C(0x15);
    row = (u8)func_8002938C(0x15);
    main->unk42 = ((resource * 4 + 0x18) % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
    resource = (u8)func_8002938C(0x15);
    main->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
}

void func_800B875C(struct EffectObj* arg0, s16 unused)
{
    s16 x;
    s16 y;
    u8 i;

    x = arg0->x_pos.i.hi - 0x10;
    arg0->x_pos.i.hi = x;
    y = arg0->y_pos.i.hi - 0x10;
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) != 0) {
        for (i = 1; i < 0x10; i++) {
            if (func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, y + i * 16) == 0) {
                arg0->y_pos.i.hi += i * 16;
                func_800B8630(arg0);
                return;
            }
        }
        return;
    }
    for (i = 1; i < 0x10; i++) {
        if (func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, y - i * 16) != 0) {
            arg0->y_pos.i.hi -= (i - 1) * 16;
            func_800B8630(arg0);
            return;
        }
    }
}

extern void (*falling_icicle_step_funcs[])(struct MainObj*);
extern u8 falling_icicle_debris[];

void func_80054D8C(struct MainObj* arg0)
{
    s32 collision;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    falling_icicle_step_funcs[arg0->unk5](arg0);
    arg0->ext.main_21.saved_unk5 = arg0->unk5;
    collision = func_8002DD04(arg0);
    func_8002D9BC(arg0);
    if (collision < 0 || func_8002BB80(arg0, MAIN_OBJECT(&g_Player)) != 0 || (arg0->collision_flags & 8)) {
        set_animation(arg0, 4);
        spawn_debris(3, falling_icicle_debris, arg0);
        func_8001540C(5, 1, NULL);
        arg0->state = 2;
        return;
    }
    if (func_8002B160(BASE_OBJECT(arg0)) != 0) {
        arg0->state = 3;
        return;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

extern void* rising_platform_animations[];
extern struct Unk_unk68 rising_platform_start_y[];

void func_800C16F0(struct ItemObj* arg0)
{
    s32 resource;
    s32 row;

    arg0->active = 0x41;
    arg0->animation_table = (const u8* const*)rising_platform_animations;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0x87);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk40 = D_801406A8[func_8002938C(0x87)] >> 7;
    resource = func_8002938C(0x87);
    row = func_8002938C(0x87);
    arg0->unk42 = ((resource * 4 + 0x18) % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
    arg0->unk16 = 6;
    arg0->unk15 = 0;
    arg0->unk68 = rising_platform_start_y;
    set_animation(ANIMATED_OBJECT(arg0), 0);
    arg0->unk76 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0x8000;
    arg0->unk7C.value = 0;
}

extern void* D_800FC2B4[];
extern struct Unk_unk68 D_800FBF0C;
extern void (*ice_core_step_funcs[])(struct MainObj*);
extern u8 D_800FC33C[];
void ice_core_face_player(struct AnimatedObj* arg0);
void func_800527F0(struct MainObj* arg0);
void ice_core_pick_attack(struct MainObj* arg0);
void ice_core_check_rebuild(struct MainObj* arg0);
void ice_core_shed_ice(struct MainObj* arg0);

void func_8005077C(struct MainObj* arg0)
{
    struct Main18Ext* ext = &arg0->ext.main_18;

    arg0->contact_damage = 4;
    arg0->invincibility_timer = -0x80;
    arg0->hp = 0;
    arg0->collision_data = (const u16*)D_80106B74;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)D_800FC2B4;
    arg0->unk16 = 0x22;
    arg0->air_state = 0;
    arg0->terrain_box = &D_800FBF0C;
    arg0->hurt_box = NULL;
    arg0->attack_box = NULL;
    ice_core_face_player(ANIMATED_OBJECT(arg0));
    set_animation(arg0, 0x21);
    ext->ice_pieces = 0x8000;
    *(u8*)&arg0->unk7E = 0xFF;
    ext->state.runtime.unk80 = 0;
    ext->state.runtime.unk81 = 0;
    ext->state.runtime.unk82 = 0;
    ext->state.runtime.unk83 = 0;
    ext->state.runtime.unk84 = 0;
    ext->state.runtime.unk85 = 0;
    ext->state.runtime.unk86 = 0;
    ext->state.runtime.unk87 = 0;
    ext->unk88 = 1;
    ext->shed_timer = 0;
    ext->state.runtime.unk82 = 1;
    ext->ice_pieces = 0;
    ext->unk8C = 0;
    ext->unk90 = 0;
    arg0->state = 1;
    arg0->unk5 = 0xB;
    arg0->unk6 = 0;
}

void func_80050874(struct MainObj* arg0)
{
    struct Main18Ext* ext = &arg0->ext.main_18;
    s32 hit;
    u8 invulnerable;

    ice_core_pick_attack(arg0);
    ice_core_check_rebuild(arg0);
    ice_core_shed_ice(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    ice_core_step_funcs[arg0->unk5](arg0);
    if (arg0->state >= 2) {
        update_on_screen(BASE_OBJECT(arg0), 0x80, 0x80);
        return;
    }
    invulnerable = arg0->invincibility_timer;
    if (invulnerable & 0x7F) {
        arg0->invincibility_timer = invulnerable - 1;
        if ((u8)(invulnerable - 1) == 0)
            arg0->unk42 &= 0x7FFF;
    } else {
        ext->saved_unk5 = arg0->unk5;
        hit = func_8002DD04(arg0);
        if (hit < 0) {
            g_Player.invincibility_timer = 0x7F;
            func_8001540C(5, 2, NULL);
            spawn_explosion(BASE_OBJECT(arg0));
            g_Player.spike_immune = 1;
            spawn_debris(4, D_800FC33C, arg0);
            arg0->unk7C = 4;
            arg0->unk7E = 8;
            ext->ice_pieces = 0;
            ext->shed_timer = 0;
            arg0->terrain_box = NULL;
            arg0->state = 2;
            arg0->unk42 &= 0x7FFF;
            return;
        }
        if (hit == 0 || hit == 0x7F) {
            ext->state.runtime.unk87 = 0;
        } else {
            arg0->invincibility_timer = engine_obj.cur_character != 0 ? 1 : 6;
            ext->state.runtime.unk87 = 1;
            arg0->unk42 |= 0x8000;
            if (!(ext->state.runtime.unk80 & 0xC0))
                ext->state.runtime.unk80 = (ext->state.runtime.unk80 | 0x40) + 1;
            if (ext->state.runtime.unk81 != 0) {
                switch (hit - 1) {
                case 0:
                    ext->state.runtime.unk83 += 2;
                    break;
                case 9:
                case 23:
                case 24:
                case 25:
                case 26:
                    ext->state.runtime.unk83 += 5;
                    break;
                case 18:
                    ext->state.runtime.unk83 += 10;
                    break;
                }
            }
        }
    }
    func_8002D9BC(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x80, 0x80);
}

void func_80050D14(struct MainObj* arg0)
{
    if (arg0->unk15 == 0 ? (arg0->collision_flags & 2) : (arg0->collision_flags & 1)) {
        if (arg0->ext.main_18.state.runtime.unk84 != 0) {
            ice_core_face_player(ANIMATED_OBJECT(arg0));
            set_animation(arg0, 6);
            arg0->unk5 = 3;
            arg0->unk6 = 2;
        } else {
            arg0->unk15 = arg0->unk15 == 0 ? 0x40 : 0;
            func_800527F0(arg0);
        }
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->y_speed == 0x30000)
        arg0->gravity = 0x2000;
    if (arg0->y_speed == -0x30000)
        arg0->gravity = -0x2000;
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_80052218(struct MainObj* arg0)
{
    u32 i;

    for (i = 0; i < 0x20; i++) {
        if (item_objects[i].id != 8)
            item_objects[i].active = 0;
    }
    arg0->y_speed = 0x10000;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->unk7C = 0x74;
    player_start_script_action(0x15, 0);
    arg0->unk6 = 1;
}

void func_800527F0(struct MainObj* arg0)
{
    arg0->unk5 = 7;
    arg0->unk6 = 0;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    if (arg0->ext.main_18.state.runtime.unk84 == 0)
        arg0->gravity = arg0->y_pos.i.hi < 0x891 ? 0x1000 : -0x1000;
    else
        arg0->gravity = arg0->y_pos.i.hi >= 0x8B1 ? -0x1000 : 0x1000;
}

extern u16 D_800FBEDC[12];
extern struct Unk_unk68 D_800FBF08;

void func_800517D0(struct MainObj* arg0)
{
    struct Main18Ext* ext = &arg0->ext.main_18;
    struct ShotObj* shot;
    struct MiscObj* misc;
    s16 i;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 3) {
        for (i = 0; i < 10; i++) {
            if (D_800FBEDC[i] & ext->ice_pieces)
                continue;
            shot = find_free_shot_obj();
            if (shot == NULL)
                continue;
            shot->active = 0x41;
            shot->id = 0xC;
            shot->unk2 = i;
            shot->unk40 = arg0->unk40;
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)arg0->animation_table;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->x_pos.val = (i << 21) + 0x17B10000;
            shot->y_pos.val = 0x8200000;
            shot->state = 3;
            shot->unk15 = 0;
            shot->unk7C = (struct WeaponObj*)&ext->ice_pieces;
            shot->bg_offset = arg0->bg_offset;
        }
        ext->ice_pieces = 0x83FF;
    }
    if (arg0->animation_step.fields.event == 4) {
        arg0->attack_box = (const u8*)&D_800FBF08;
        arg0->hurt_box = (const u8*)&D_800FBF08;
    }
    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, 0x34, arg0);
        for (i = 0; i < 8; i++) {
            misc = find_free_misc_obj();
            if (misc == NULL)
                continue;
            misc->active = 0x41;
            misc->id = 6;
            misc->unk2 = i;
            misc->unk40 = arg0->unk40;
            misc->unk42 = arg0->unk42 & 0x7FFF;
            misc->animation_table = (u32**)arg0->animation_table;
            misc->unk3C = (void*)arg0->sprite_frames;
            misc->bg_offset = arg0->bg_offset;
            misc->x_pos.val = arg0->x_pos.val;
            misc->unk15 = 0;
            misc->state = 0;
            misc->y_pos.val = arg0->y_pos.val;
        }
        arg0->invincibility_timer = -0x80;
    }
    if (arg0->animation_step.fields.event != 1)
        return;
    if (ext->unk88 == 0) {
        arg0->attack_box = (const u8*)&D_800FBEF8;
        arg0->hurt_box = (const u8*)&D_800FBEF8;
        set_animation(arg0, 0xA);
    } else {
        ice_core_face_player(ANIMATED_OBJECT(arg0));
        arg0->attack_box = (const u8*)&D_800FBEF4;
        arg0->hurt_box = (const u8*)&D_800FBEF4;
        set_animation(arg0, 9);
    }
    ext->state.runtime.unk85 = 3;
    arg0->unk6 = 2;
}

void func_800C91EC(struct MiscObj* arg0)
{
    set_animation(arg0, arg0->unk2 + 0x11);
    arg0->ext.misc_6.saved_position.position.x = arg0->x_pos.i.hi;
    arg0->ext.misc_6.saved_position.position.y = arg0->y_pos.i.hi;
    set_velocity_from_angle(MOVING_OBJECT(arg0), (arg0->unk2 * 4) & 0xFC);
    arg0->ext.misc_6.timer = 0x14;
    arg0->state = 1;
    arg0->x_pos.val += arg0->x_vel.val * 180;
    arg0->y_pos.val -= arg0->y_vel.val * 180;
    arg0->x_vel.val = -(arg0->x_vel.val * 4);
    arg0->y_vel.val = -(arg0->y_vel.val * 4);
}

extern u8 ice_core_spray_hit_box[4];
extern u8 ice_core_shard_hit_box[4];
extern u8 ice_core_shard_terrain_box[4];
extern u8 ice_core_shard_debris[4];

void func_8009B85C(struct ShotObj* arg0)
{
    const u8* offsets = (const u8*)&ice_core_shard_data + 0x14 + arg0->unk2 * 2;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk42 &= 0x7FFF;
    set_velocity_from_angle(MOVING_OBJECT(arg0), (arg0->unk2 * 4) & 0xFC);
    arg0->y_vel.val *= 6;
    arg0->y_pos.i.hi = (u16)arg0->y_pos.i.hi + (s8)offsets[1];
    if (arg0->unk15 == 0) {
        arg0->x_vel.val *= 6;
        arg0->x_pos.i.hi = (u16)arg0->x_pos.i.hi + (s8)offsets[0];
    } else {
        arg0->x_vel.val = -(arg0->x_vel.val * 6);
        arg0->x_pos.i.hi = (u16)arg0->x_pos.i.hi - (s8)offsets[0];
    }
    arg0->unk54 = ice_core_spray_hit_box;
    arg0->unk50.data = ice_core_spray_hit_box;
    arg0->unk5C = 6;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk60 = 3;
    set_animation(arg0, arg0->unk2 + 0x11);
}

void func_8009BA6C(struct ShotObj* arg0)
{
    arg0->state = 4;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk68 = (struct Unk_unk68*)ice_core_shard_terrain_box;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk54 = ice_core_shard_hit_box;
    arg0->unk50.data = ice_core_shard_hit_box;
    arg0->unk16 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk60 = 3;
    arg0->unk42 &= 0x7FFF;
    set_animation(arg0, 0x1D);
}

extern u8 D_8013B8E4[4];

void func_800AF95C(struct ObjectHeader* arg0, s32 type, s32 x_range, s32 y_range, s32 divisor)
{
    s16 x;
    s16 y;
    s32 roll;
    u8 variant;

    x_range &= get_random();
    if (get_random() & 1)
        x = arg0->x_pos.u.hi + (x_range & 0xFF);
    else
        x = arg0->x_pos.u.hi - (x_range & 0xFF);
    y_range &= get_random();
    if (get_random() & 1)
        y = arg0->y_pos.u.hi + (y_range & 0xFF);
    else
        y = arg0->y_pos.u.hi - (y_range & 0xFF);
    roll = get_random_nonzero();
    divisor &= 0xFF;
    if (divisor == 0 || roll % divisor == 0) {
        D_8013B8E4[0]++;
        variant = (D_8013B8E4[0] & 1) ? 2 : 3;
    } else {
        variant = 0xFF;
    }
    spawn_explosion_at((s8)type, x, y, variant);
}

extern union AnimationStep* ice_wall_animations[];
extern struct Unk_unk68 D_80106F74[];
extern struct Unk_unk68 ice_wall_hurt_box[];

void func_80058194(struct MainObj* arg0)
{
    arg0->state++;
    arg0->unk5 = 2;
    arg0->unk2 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)ice_wall_animations;
    arg0->unk16 = 6;
    arg0->collision_data = (const u16*)D_80106F74;
    arg0->hurt_box = (const u8*)ice_wall_hurt_box;
    arg0->contact_damage = 3;
    arg0->hp = 9;
    arg0->ext.main_26.last_health = 9;
    arg0->ext.main_26.stage = 2;
    arg0->unk15 = 0;
    arg0->terrain_box = NULL;
    arg0->attack_box = NULL;
    arg0->invincibility_timer = 0;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->x_pos.i.hi &= ~0xF;
    arg0->y_pos.i.hi &= ~0xF;
}

void func_800583B0(struct MainObj* arg0, s16 x, s16 y, s32 base)
{
    u8 above;
    u8 below;
    u8 tile;
    s16 left = (x & -0x10) - 0x10;
    s16 top = y & -0x10;

    above = func_8002D724(PLAYER_OBJECT(arg0), x, y - 0x20);
    if (above != 0x38)
        above = func_8002D724(PLAYER_OBJECT(arg0), x, y - 0x30);
    below = func_8002D724(PLAYER_OBJECT(arg0), x, y + 0x30);

    switch (above) {
    case 0x31:
        tile = 2;
        break;
    case 0:
        tile = 3;
        break;
    case 0x30:
        tile = 1;
        break;
    case 0x3C:
        tile = 0;
        break;
    default:
        tile = 4;
        break;
    }
    apply_tile_effect(tile + base, left, top - 0x20);

    switch (below) {
    case 0x31:
        tile = 0x11;
        break;
    case 0:
        tile = 0x12;
        break;
    case 0x30:
        tile = 0x10;
        break;
    case 0x3C:
        tile = 0xF;
        break;
    default:
        tile = 0x13;
        break;
    }
    apply_tile_effect(tile + base, left, top + 0x10);

    base &= 0xFF;
    apply_tile_effect(base == 0 ? 0x1E : base == 5 ? 0x1F
                                                   : 0x20,
        left, top);
}

extern union AnimationStep* dash_gunner_animations[];
extern struct Unk_unk68 dash_gunner_boxes[10];
extern struct Unk_unk68* D_8013B828;
extern struct Unk_unk68* D_8013B82C;
extern struct Unk_unk68* D_8013B830;
extern struct Unk_unk68* D_8013B834;
extern void (*dash_gunner_step_funcs[])(struct MainObj*);
extern struct Unk_unk68 D_80106FF4[];
extern u8 dash_gunner_debris[];

void func_80058740(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;
    u8 subtype;

    arg0->hp = 6;
    arg0->invincibility_timer = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->air_state = 0;
    arg0->animation_table = (const u8* const*)dash_gunner_animations;
    arg0->unk16 = 6;
    arg0->hurt_box = NULL;
    arg0->attack_box = NULL;
    arg0->collision_flags = 0;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    ext->unk8B = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    switch ((u8)arg0->unk2) {
    case 0:
    case 4:
        arg0->x_speed = -0x18000;
        ext->unk90 = 0;
        arg0->unk15 = 0;
        ext->unk80 = 0;
        ext->unk8C = 0x1E;
        func_8001540C(2, 0x51, arg0);
        arg0->unk5 = 2;
        break;
    case 1:
    case 5:
        arg0->unk15 = 0x40;
        ext->unk8C = 0x1E;
        arg0->unk5 = 3;
        ext->unk90 = 0;
        arg0->x_speed = 0x18000;
        ext->unk80 = 0;
        arg0->unk7A = 1;
        break;
    case 2:
    case 6:
        ext->unk82 = 0x1E;
        ext->unk80 = 1;
        ext->unk8C = 0x12C;
        ext->unk90 = 0;
        arg0->unk15 = 0;
        ext->unk88 = 0;
        ext->unk89 = 0x14;
        ext->unk8A = 0;
        func_8001540C(2, 0x51, arg0);
        arg0->unk5 = 6;
        break;
    case 3:
    case 7:
        arg0->unk15 = 0x40;
        ext->unk82 = 0x1E;
        ext->unk8C = 0x12C;
        ext->unk89 = 0x14;
        ext->unk90 = 0;
        ext->unk80 = 1;
        ext->unk88 = 1;
        ext->unk8A = 0;
        arg0->unk7A = 1;
        arg0->unk5 = 3;
        break;
    case 8:
    case 9:
    case 10:
    case 11:
        subtype = arg0->unk2;
        ext->unk90 = subtype < 10 ? 1 : 2;
        ext->unk91 = 0x30;
        if (subtype >= 10)
            ext->unk92 = 2;
        arg0->unk15 = (subtype & 1) ? 0x40 : 0;
        ext->unk80 = 0;
        ext->unk8A = 0;
        func_8001540C(2, 0x51, arg0);
        arg0->x_speed = (subtype & 1) ? 0x18000 : -0x18000;
        arg0->unk5 = 2;
        break;
    }

    subtype = arg0->unk2;
    if (subtype < 4 || (u8)(subtype - 8) < 4) {
        arg0->contact_damage = 6;
        arg0->terrain_box = &dash_gunner_boxes[4];
        D_8013B828 = &dash_gunner_boxes[0];
        D_8013B82C = &dash_gunner_boxes[1];
        D_8013B830 = &dash_gunner_boxes[3];
        D_8013B834 = &dash_gunner_boxes[2];
    } else {
        arg0->contact_damage = 7;
        arg0->terrain_box = &dash_gunner_boxes[9];
        D_8013B828 = &dash_gunner_boxes[5];
        D_8013B82C = &dash_gunner_boxes[6];
        D_8013B830 = &dash_gunner_boxes[8];
        D_8013B834 = &dash_gunner_boxes[7];
    }
    set_animation(arg0, 1);
    arg0->state = 1;
    arg0->unk6 = 0;
}

void func_80058AC8(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;
    s32 facing_player;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    dash_gunner_step_funcs[arg0->unk5](arg0);
    if (engine_obj.stage == 3 && arg0->x_pos.i.hi < 0x20)
        arg0->x_pos.i.hi = 0x20;
    if ((u8)arg0->unk2 < 4) {
        if (arg0->x_pos.i.hi > 0x780)
            arg0->x_pos.i.hi = 0x780;
    } else if (arg0->x_pos.i.hi > 0x980) {
        arg0->x_pos.i.hi = 0x980;
    }
    if (arg0->unk5 == 3)
        return;
    ext->saved_unk5 = arg0->unk5;
    ext->unk84 = g_Player.x_pos.val;
    if (arg0->state != 2) {
        arg0->attack_box = (const u8*)(ext->unk8B != 0 ? D_8013B82C : D_8013B828);
        func_8002D9BC(arg0);
        arg0->attack_box = (const u8*)D_8013B834;
        func_8002D9BC(arg0);
    }
    facing_player = arg0->unk15 == 0 ? g_Player.x_pos.i.hi < arg0->x_pos.i.hi
                                     : arg0->x_pos.i.hi < g_Player.x_pos.i.hi;
    if (ext->unk8B == 0 && facing_player) {
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->hurt_box = (const u8*)D_8013B828;
        func_8002DD04(arg0);
    } else {
        arg0->collision_data = (const u16*)D_80106FF4;
        arg0->hurt_box = (const u8*)D_8013B830;
        if (func_8002DD04(arg0) < 0) {
            spawn_explosion(BASE_OBJECT(arg0));
            spawn_debris(4, dash_gunner_debris, arg0);
            drop_item(BASE_OBJECT(arg0), 0x11);
            arg0->unk7C = 0x20;
            arg0->unk7E = 6;
            arg0->on_screen = 0;
            stop_sound(2, 0x51);
            arg0->state = 2;
            return;
        }
    }
    if (arg0->state == 2)
        return;
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x60, 0x60) != 0) {
        stop_sound(2, 0x51);
        arg0->state = 3;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_80059154(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    set_animation(arg0, 1);
    if (ext->unk80 == 0) {
        arg0->x_speed = arg0->unk15 != 0 ? 0x18000 : -0x18000;
        arg0->unk5 = 2;
    } else {
        ext->unk89 = 0x14;
        ext->unk88 = 0;
        arg0->unk5 = 6;
    }
    arg0->unk6 = 0;
}

void func_80059590(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    set_animation(arg0, 1);
    func_8001540C(2, 0x51, arg0);
    if (ext->unk80 == 0) {
        ext->unk8C = 0xB4;
        arg0->x_speed = arg0->unk15 != 0 ? 0x18000 : -0x18000;
        arg0->unk5 = 2;
    } else {
        ext->unk89 = 0x14;
        ext->unk8C = 0x12C;
        ext->unk88 = 0;
        arg0->unk5 = 6;
    }
    arg0->unk6 = 0;
}

void func_80059640(struct MainObj* arg0)
{
    struct Main27Ext* ext = &arg0->ext.main_27;
    s32 dy;
    s32 dx;

    if (--ext->unk8C == 0 && (arg0->unk15 == 0 ? g_Player.x_pos.i.hi < arg0->x_pos.i.hi : arg0->x_pos.i.hi < g_Player.x_pos.i.hi)) {
        set_animation(arg0, 3);
        arg0->x_speed = 0;
        stop_sound(2, 0x51);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        return;
    }
    if (--ext->unk82 == 0) {
        ext->unk82 = 0x1E;
        if ((get_random() & 7) < 5) {
            arg0->unk7C = 0xA;
            arg0->x_speed = 0;
            arg0->unk5 = 7;
            arg0->unk6 = 0;
            return;
        }
    }
    if (ext->unk89 != 0)
        ext->unk89--;
    animate_object(ANIMATED_OBJECT(arg0));
    if (ext->unk88 == 0) {
        dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
        if (dy < 0)
            dy = -dy;
        if (dy < 0x31) {
            dx = arg0->unk15 == 0 ? ext->unk84 - g_Player.x_pos.val
                                  : g_Player.x_pos.val - ext->unk84;
            if (dx > 0x3FFFF) {
                ext->unk88 = 1;
                set_animation(arg0, 7);
            }
        }
    } else {
        dx = g_Player.x_pos.val - ext->unk84;
        if (dx < 0)
            dx = ext->unk84 - g_Player.x_pos.val;
        if (dx <= 0x3FFFF) {
            ext->unk88 = 0;
            set_animation(arg0, 1);
        }
    }
    if (arg0->unk15 == 0 ? (arg0->collision_flags & 2) : (arg0->collision_flags & 1)) {
        arg0->unk7C = 0x14;
        arg0->x_accel = 0;
        arg0->y_speed = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    if (ext->unk89 == 0 && (arg0->unk15 == 0 ? arg0->x_pos.i.hi < g_Player.x_pos.i.hi : g_Player.x_pos.i.hi < arg0->x_pos.i.hi)) {
        arg0->unk7C = 0x14;
        arg0->x_accel = -0x2000;
        arg0->y_speed = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    if (ext->unk88 == 0)
        arg0->x_speed = arg0->unk15 != 0 ? 0x20000 : -0x20000;
    else
        arg0->x_speed = arg0->unk15 != 0 ? 0x40000 : -0x40000;
    move_object(MOVING_OBJECT(arg0));
}

extern struct Unk_unk68 D_80107274[];
extern union AnimationStep* bomb_bat_animations[8];
extern struct Unk_unk68 D_800FDC88[2];
extern s32 D_800FDC98[2];

void func_8005C860(struct MainObj* arg0)
{
    struct Main32Ext* ext = &arg0->ext.main_32;

    arg0->active = 0x41;
    arg0->hp = 3;
    arg0->contact_damage = 3;
    arg0->invincibility_timer = 0;
    arg0->collision_data = (const u16*)D_80107274;
    arg0->animation_table = (const u8* const*)bomb_bat_animations;
    arg0->unk16 = 6;
    arg0->hurt_box = (const u8*)&bomb_bat_body_box;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->terrain_box = NULL;
    arg0->attack_box = (const u8*)D_800FDC88;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    set_animation(arg0, 0);
    ext->unk80 = 0;
    ext->unk84 = 0;
    ext->unk88 = 0;
    ext->unk8C = 0;
    ext->unk90 = 0;
    ext->saved_unk5 = 0;
    arg0->state++;
    arg0->unk5 = arg0->unk2 == 0 ? 2 : arg0->unk2 == 1 ? 5
                                                       : 6;
    arg0->unk6 = 0;
}

void func_8005CB90(struct MainObj* arg0)
{
    s32 limit;
    s32 distance;

    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    set_velocity_from_angle(MOVING_OBJECT(arg0),
        angle_to_point(OBJECT_HEADER(arg0), g_Player.x_pos.val, g_Player.y_pos.val - 0x500000) & 0xFF);
    arg0->x_speed += arg0->x_speed / 2;
    limit = arg0->x_speed;
    if (limit < 0)
        limit = -limit;
    limit += 0x20000;
    distance = g_Player.x_pos.val - arg0->x_pos.val;
    if (distance < 0)
        distance = arg0->x_pos.val - g_Player.x_pos.val;
    if (limit < distance && --arg0->unk7C != 0)
        return;
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_8005CF9C(struct MainObj* arg0)
{
    s32 spread;

    set_animation(arg0, 3);
    spread = get_random() << 8;
    spread += get_random();
    arg0->x_speed = D_800FDC98[(arg0->unk15 & 0x40) ? 1 : 0];
    if (get_random() & 1)
        arg0->x_speed += spread & 0xFFFF;
    else
        arg0->x_speed -= spread & 0xFFFF;
    arg0->y_speed = 0x18000;
    arg0->x_accel = -0x1000;
    arg0->attack_box = (const u8*)&bomb_bat_body_box;
    arg0->ext.main_32.unk88 = 1;
    if (arg0->unk2 == 2) {
        arg0->unk7C = get_random() & 0x3F;
        arg0->unk6++;
    } else {
        arg0->unk6 += 2;
    }
}

extern u8 dropped_bomb_hit_box[4];
extern u8 dropped_bomb_terrain_box[4];

void func_8009AD6C(struct ShotObj* arg0)
{
    arg0->y_vel.val = -0x10000;
    arg0->unk2C = 0x3000;
    arg0->unk68 = (struct Unk_unk68*)dropped_bomb_hit_box;
    arg0->unk54 = dropped_bomb_terrain_box;
    arg0->unk50.data = dropped_bomb_terrain_box;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk60 = 5;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    set_animation(arg0, 2);
}

extern struct Unk_unk68 D_80106E74[];
extern union AnimationStep* jet_drone_animations[];
extern struct Unk_unk68 jet_drone_hurt_box[];
extern struct Unk_unk68 jet_drone_terrain_box[];

void func_800567C4(struct MainObj* arg0)
{
    static const s32 motion[4][3] = {
        { -0x4000, -0x1C000, 0x14 },
        { -0x2000, -0xC000, 0x24 },
        { 0x4000, 0x1C000, 0x14 },
        { 0x2000, 0xC000, 0x24 },
    };
    u8 subtype = arg0->unk2;

    arg0->hp = 2;
    arg0->contact_damage = 3;
    arg0->invincibility_timer = 0;
    arg0->collision_data = (const u16*)D_80106E74;
    arg0->animation_table = (const u8* const*)jet_drone_animations;
    arg0->unk16 = 6;
    arg0->hurt_box = (const u8*)jet_drone_hurt_box;
    arg0->air_state = 0;
    arg0->terrain_box = NULL;
    arg0->attack_box = (const u8*)jet_drone_terrain_box;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (subtype < 8) {
        arg0->x_accel = -0x8000;
        arg0->gravity = motion[subtype & 3][0];
        arg0->y_speed = motion[subtype & 3][1];
        arg0->unk7C = motion[subtype & 3][2];
        if (subtype < 4) {
            arg0->x_speed = -0x50000;
            arg0->unk15 = 0;
            func_8001540C(2, 0x50, arg0);
            arg0->unk5 = 2;
        } else {
            arg0->unk7A = 1;
            arg0->unk15 = 0x40;
            arg0->x_speed = 0x50000;
            arg0->unk5 = 3;
        }
    }
    set_animation(arg0, 0);
    arg0->ext.main_24.unk80 = 0;
    arg0->state = 1;
    arg0->unk6 = 0;
}

extern void* teleporter_animations[5];
extern u8 teleporter_terrain_box[4];

extern union AnimationStep* regen_turret_animations[];
extern struct Unk_unk68 regen_turret_hurt_box[];
extern struct Unk_unk68 regen_turret_terrain_box[];
extern struct Unk_unk68 D_80107174[];

void func_8005B438(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = arg0->unk2 != 0 ? 0x40 : 0;
    arg0->animation_table = (const u8* const*)regen_turret_animations;
    arg0->collision_data = (const u16*)D_80107174;
    arg0->hurt_box = (const u8*)regen_turret_terrain_box;
    arg0->attack_box = (const u8*)regen_turret_hurt_box;
    arg0->unk16 = 6;
    arg0->terrain_box = NULL;
    arg0->invincibility_timer = 0;
    arg0->hp = 6;
    arg0->contact_damage = 3;
    arg0->air_state = 0;
    arg0->unk7C = 0;
    set_animation(arg0, 0);
    update_on_screen(BASE_OBJECT(arg0), 0x50, 0x50);
}

#define MAIN_37_U8(object, offset) (((u8*)&(object)->ext.main_37)[(offset)-0x80])
#define MAIN_37_S16(object, offset) (*(s16*)&MAIN_37_U8(object, offset))

extern union AnimationStep* rocket_spiker_animations[28];
extern struct Unk_unk68 D_800FE4D4;
extern struct Unk_unk68 D_800FE4D8;
extern struct Unk_unk68 D_800FE4DC;
extern struct Unk_unk68 D_800FE4E0;
extern struct Unk_unk68 D_800FE4E4;
extern struct Unk_unk68 D_80107474[];
void rocket_spiker_face_player(struct AnimatedObj* arg0);

void func_8005FE1C(struct MainObj* arg0)
{
    static const s16 lanes[3][3] = {
        { 0x3F0, 0x480, 0x410 },
        { 0x390, 0x40B, 0x3B0 },
        { 0x330, 0x380, 0x350 },
    };
    u8 lane;

    arg0->hp = 6;
    arg0->contact_damage = 4;
    arg0->invincibility_timer = 0;
    arg0->unk62 = 2;
    arg0->animation_table = (const u8* const*)rocket_spiker_animations;
    arg0->terrain_box = &D_800FE4E4;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->air_state = 0;
    arg0->unk16 = 6;
    switch (arg0->unk2) {
    case 0:
        arg0->collision_data = (const u16*)D_80107474;
        arg0->hurt_box = (const u8*)&D_800FE4D4;
        arg0->attack_box = (const u8*)&D_800FE4D8;
        rocket_spiker_face_player(ANIMATED_OBJECT(arg0));
        arg0->x_speed = 0;
        arg0->y_speed = -0x18000;
        set_animation(arg0, 1);
        arg0->unk5 = 2;
        break;
    case 1:
    case 2:
        arg0->collision_data = (const u16*)D_80107474;
        arg0->hurt_box = (const u8*)&D_800FE4D4;
        arg0->attack_box = (const u8*)&D_800FE4D8;
        arg0->unk15 = arg0->unk2 == 2 ? 0x40 : 0;
        arg0->x_speed = arg0->unk2 == 2 ? 0x18000 : -0x18000;
        arg0->y_speed = 0;
        set_animation(arg0, 0);
        arg0->unk5 = 3;
        break;
    case 3:
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->hurt_box = (const u8*)&D_800FE4DC;
        arg0->attack_box = (const u8*)&D_800FE4E0;
        arg0->y_speed = 0;
        arg0->unk42 += 2;
        if (arg0->x_pos.i.hi >= 0x1799) {
            MAIN_37_S16(arg0, 0x84) = 0x17E0;
            arg0->x_pos.val = 0x18180000;
            arg0->x_speed = 0x10000;
            arg0->unk15 = 0;
            MAIN_37_U8(arg0, 0x81) = 0;
        } else {
            MAIN_37_S16(arg0, 0x84) = 0x1710;
            arg0->x_pos.val = 0x17080000;
            arg0->x_speed = -0x10000;
            arg0->unk15 = 0x40;
            MAIN_37_U8(arg0, 0x81) = 1;
        }
        if (arg0->y_pos.i.hi < 0x370)
            MAIN_37_U8(arg0, 0x81) += 2;
        if (arg0->y_pos.i.hi < 0x3D0)
            MAIN_37_U8(arg0, 0x81) += 2;
        lane = MAIN_37_U8(arg0, 0x81);
        if (lane < 6) {
            MAIN_37_S16(arg0, 0x86) = lanes[lane / 2][0];
            MAIN_37_S16(arg0, 0x88) = lanes[lane / 2][1];
            arg0->y_pos.val = lanes[lane / 2][2] << 16;
        }
        set_animation(arg0, 7);
        arg0->unk5 = 4;
        break;
    }
    MAIN_37_U8(arg0, 0x8C) = 0;
    MAIN_37_U8(arg0, 0x8D) = 1;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->state = 1;
    arg0->unk6 = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
}

static void main_37_rumble(struct MainObj* arg0)
{
    if (--MAIN_37_U8(arg0, 0x8D) == 0) {
        func_8001540C(2, 0x59, arg0);
        MAIN_37_U8(arg0, 0x8D) = 0x1E;
    }
}

static void main_37_debris(struct MainObj* arg0)
{
    if ((arg0->unk7E & 3) == 0) {
        spawn_owner_debris(1, &rocket_spiker_exhaust_variants[MAIN_37_U8(arg0, 0x8C)], arg0, 0x7988,
            arg0->unk15 != 0 ? 0x200000 : -0x200000, 0);
        if (++MAIN_37_U8(arg0, 0x8C) == 0xA)
            MAIN_37_U8(arg0, 0x8C) = 0;
    }
    if ((++arg0->unk7E & 7) == 0) {
        func_800B10E4(0x11, (s16)(MAIN_37_S16(arg0, 0x84) + 0x10),
            (s16)(MAIN_37_S16(arg0, 0x86) + 0x10), (s16)(MAIN_37_S16(arg0, 0x84) + 0x20),
            (s16)(MAIN_37_S16(arg0, 0x86) + 0x30), 1);
    }
}

void func_800608CC(struct MainObj* arg0)
{
    s32 velocity;

    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 == 0) {
        if (arg0->x_pos.i.hi >= 0x17A0)
            return;
        arg0->x_pos.i.hi = 0x17A0;
        func_8001540C(2, 0x5A, arg0);
        velocity = 0x58000;
    } else {
        if (arg0->x_pos.i.hi < 0x1781)
            return;
        velocity = -0x58000;
        arg0->x_pos.i.hi = 0x1780;
    }
    arg0->unk7C = 0x28;
    arg0->x_accel = 0x2000;
    arg0->x_speed = velocity;
    arg0->unk6 = 4;
}

extern u8 turret_laser_hit_box[4];

void func_8009C12C(struct ShotObj* arg0)
{
    struct MainObj* owner = MAIN_OBJECT(arg0->unk7C);

    arg0->unk40 = owner->unk40;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk15 = owner->unk15;
    arg0->bg_offset = owner->bg_offset;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->state++;
    arg0->unk5 = 2;
    arg0->y_pos.val = owner->y_pos.val;
    set_velocity_from_angle(MOVING_OBJECT(arg0),
        angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
    arg0->unk58.data = (const u8*)D_80106070;
    arg0->unk54 = turret_laser_hit_box;
    arg0->unk50.data = turret_laser_hit_box;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->x_vel.val *= 2;
    arg0->y_vel.val *= 2;
    set_animation(arg0, 4);
}

extern void* trap_floor_animations[2];
extern u8 trap_floor_terrain_box[];

extern struct Unk_unk68 D_801072F4[];
extern union AnimationStep* spike_sled_animations[23];
extern struct Unk_unk68 D_800FDD88;
extern struct Unk_unk68 D_800FDD8C;
extern u8 D_800FDD90[8];
extern u8 D_800FDD98[8];
extern u8 D_800FDF4C[8];

#define MAIN_33_SLOT_X(index) ((s16)D_800FDDA0[(index)*2])
#define MAIN_33_SLOT_Y(index) ((s16)D_800FDDA0[(index)*2 + 1])

void func_8005D4E0(struct MainObj* arg0)
{
    struct Main33Ext* ext = &arg0->ext.main_33;
    s32 x;
    s32 y;
    s32 i;

    switch (arg0->unk5) {
    case 0:
        if (--arg0->unk7C == 0) {
            engine_obj.enable_boss = 0;
            engine_obj.boss_ptr = NULL;
            arg0->unk7C = 0x50;
            arg0->unk7E = 1;
            arg0->unk42 = 0x798F;
            for (i = 0; i < 7; i++) {
                if (!(D_800FDD90[i] & ext->unk80))
                    continue;
                arg0->x_pos.i.hi = MAIN_33_SLOT_X(i) + 0x20;
                arg0->y_pos.i.hi = MAIN_33_SLOT_Y(i) + 0x20;
                apply_tile_effect(0, MAIN_33_SLOT_X(i), MAIN_33_SLOT_Y(i));
                spawn_debris(6, D_800FDF4C, arg0);
            }
            arg0->unk5 = 1;
            return;
        }
        if (!(--arg0->unk7E & 1)) {
            x = arg0->x_pos.val;
            y = arg0->y_pos.val;
            arg0->x_pos.i.hi = 0x12A0;
            arg0->y_pos.i.hi = 0x300;
            func_800AF95C(OBJECT_HEADER(arg0), 1, 0xA0, 0x18, 4);
            arg0->x_pos.val = x;
            arg0->y_pos.val = y;
        }
        if (arg0->unk7E == 0) {
            arg0->unk7E = 6;
            func_800AF95C(OBJECT_HEADER(arg0), 1, 0x20, 0x20, 4);
        }
        break;
    case 1:
        if (--arg0->unk7C == 0) {
            arg0->unk7C = 0x80;
            ext->unk88 = 0x1200;
            arg0->unk5 = 2;
            return;
        }
        if (--arg0->unk7E != 0)
            return;
        arg0->unk7E = 6;
        for (i = 0; i < 7; i++) {
            if (!(D_800FDD90[i] & ext->unk80))
                continue;
            arg0->x_pos.i.hi = MAIN_33_SLOT_X(i) + 0x20;
            arg0->y_pos.i.hi = MAIN_33_SLOT_Y(i) + 0x20;
            func_800AF95C(OBJECT_HEADER(arg0), 1, 0x28, 0x18, 4);
        }
        break;
    case 2:
        if (--arg0->unk7C == 0) {
            arg0->state = 3;
            return;
        }
        ext->unk88 -= 2;
        if (ext->unk88 < 0x1100)
            ext->unk88 = 0x1100;
        background_objects[0].unk26 = ext->unk88;
        break;
    }
}

void func_8005DC58(struct MainObj* arg0)
{
    struct Main33Ext* ext = &arg0->ext.main_33;
    s16 target;
    s32 delta;
    u8 slot;
    u8 first;

    animate_object(ANIMATED_OBJECT(arg0));
    if (ext->target_x != 0) {
        arg0->unk6 = 3;
        return;
    }
    move_object(MOVING_OBJECT(arg0));
    target = g_Player.x_pos.i.hi;
    if (--arg0->unk7C == 0) {
        if (g_Player.x_pos.i.hi < 0x1220) {
            ext->variant = 0;
            if (!(D_800FDD98[0] & ext->unk80)) {
                ext->variant = 1;
                if (!(D_800FDD98[1] & ext->unk80))
                    ext->variant = 0;
            }
        } else if (g_Player.x_pos.i.hi >= 0x1321) {
            ext->variant = 4;
            if (!(D_800FDD98[4] & ext->unk80)) {
                ext->variant = 3;
                if (!(D_800FDD98[3] & ext->unk80))
                    ext->variant = 4;
            }
        } else {
            delta = (u16)g_Player.x_pos.i.hi - 0x1220;
            slot = (u8)((s16)delta >> 6);
            ext->variant = (delta & 0x3F) < 0x21 ? slot : slot + 1;
            first = ext->variant;
            if (!(D_800FDD98[first] & ext->unk80)) {
                ext->variant = (delta & 0x3F) < 0x21 ? first + 1 : first - 1;
                if (!(D_800FDD98[ext->variant] & ext->unk80))
                    ext->variant = first;
            }
        }
        ext->target_x = ext->variant * 64 + 0x1220;
        target = ext->target_x;
    }
    if (arg0->unk15 == 0) {
        if (!(arg0->x_pos.i.hi < 0x1220 && ext->target_x == 0) && !(arg0->x_pos.i.hi < target))
            return;
    } else {
        if (!(arg0->x_pos.i.hi >= 0x1321 && ext->target_x == 0) && !(target < arg0->x_pos.i.hi))
            return;
    }
    set_animation(arg0, 4);
    arg0->x_accel = -0x4000;
    arg0->unk6 = 2;
}

void func_8005DED4(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0)
        arg0->unk7C = 1;
    animate_object(ANIMATED_OBJECT(arg0));
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->x_speed != 0)
        return;
    func_8001540C(2, 0x52, arg0);
    if (arg0->unk15 == 0) {
        arg0->unk15 = 0x40;
        arg0->x_speed = 0x40000;
    } else {
        arg0->x_speed = -0x40000;
        arg0->unk15 = 0;
    }
    set_animation(arg0, 3);
    arg0->x_accel = 0;
    arg0->unk6 = 1;
}

void func_8005E108(struct MainObj* arg0)
{
    struct Main33Ext* ext = &arg0->ext.main_33;
    u8 slot;
    u8 mask;

    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    slot = ext->variant;
    mask = ext->unk80;
    if (D_800FDD90[slot] & mask) {
        arg0->unk7C = 0xC;
    } else if (slot < 2 && (mask & 0x20)) {
        ext->variant = 5;
        arg0->unk7C = 0x22;
    } else if (slot >= 2 && (u8)(slot - 3) < 2 && (mask & 0x40)) {
        ext->variant = 6;
        arg0->unk7C = 0x22;
    } else {
        ext->variant = 0xFF;
        arg0->unk7C = 0x26;
    }
    arg0->unk6 = 1;
}

void func_8005E298(struct MainObj* arg0)
{
    struct Main33Ext* ext = &arg0->ext.main_33;
    u8 slot;
    s32 x;
    s32 y;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7E != 0)
        return;
    func_8001540C(2, 0x55, arg0);
    start_screen_shake_y(0x10, 8, 2);
    slot = ext->variant;
    apply_tile_effect(0, MAIN_33_SLOT_X(slot), MAIN_33_SLOT_Y(slot));
    x = arg0->x_pos.val;
    y = arg0->y_pos.val;
    arg0->x_pos.i.hi = MAIN_33_SLOT_X(slot) + 0x20;
    arg0->unk42 = 0x798F;
    arg0->y_pos.i.hi = MAIN_33_SLOT_Y(slot) + 0x20;
    spawn_debris(6, D_800FDF4C, arg0);
    arg0->x_pos.val = x;
    arg0->y_pos.val = y;
    arg0->unk42 = ext->unk8E;
    ext->flash_timer = 0x20;
    ext->unk91 = 6;
    ext->variant = 0xFF;
    ext->unk87 = slot;
    arg0->unk6 = 1;
    ext->unk80 ^= D_800FDD90[slot];
}

void func_800C6EDC(struct VisualObj* arg0)
{
    s32 resource;
    s32 column;
    s32 index;

    if (arg0->state == 0) {
        arg0->active = 1;
        arg0->on_screen = 1;
        resource = func_8002938C(0xA2) & 0xFF;
        column = resource * 4 + 0x18;
        index = (s8)light_capsule_part_animations[arg0->unk2];
        arg0->unk38 = SP_ARCHIVE_ENTRY(SP_PLAYER_GFX, index + 10);
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, index + 18);
        arg0->animation_table = D_8011BF40;
        arg0->unk40 = 0x520;
        arg0->unk42 = (column - (column & 0x7F0)) | ((((resource + 6) >> 2) + 0x1E0) << 6);
        arg0->unk16 = 0;
        arg0->unk15 = g_Player.unk15;
        arg0->x_pos.val = g_Player.x_pos.val;
        arg0->y_pos.val = g_Player.y_pos.val;
        set_animation(ANIMATED_OBJECT(arg0), engine_obj.unk37 != 0 ? 0x26 : 0x25);
        arg0->state++;
        decompress_player_gfx((struct GraphicsObj*)arg0, 0x140, 0x20);
    } else if (arg0->animation_step.fields.relative_step == 0) {
        g_Player.item_step = 4;
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    } else {
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            arg0->animation_step.fields.event = 0;
            if (engine_obj.unk37 != 0) {
                g_Player.armor_parts = 0xF;
                g_Player.arm_type = 2;
                engine_obj.unk48 = 2;
            } else {
                u8 bit = light_capsule_part_bits[arg0->unk2];

                g_Player.armor_parts |= bit;
                if (bit == 4) {
                    if (arg0->unk2 == 2)
                        g_Player.arm_type = 1;
                    if (arg0->unk2 == 3)
                        g_Player.arm_type = 2;
                    engine_obj.unk48 = g_Player.arm_type;
                }
            }
            engine_obj.unk47 = g_Player.armor_parts;
        }
    }
    update_on_screen(BASE_OBJECT(arg0), 0x88, 0x88);
}

void func_800528BC(struct MainObj* arg0)
{
    s32 index;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk5 = 2;
    arg0->hp = 4;
    arg0->contact_damage = 3;
    arg0->animation_table = (const u8* const*)surface_hopper_animations;
    arg0->unk6 = 0;
    arg0->unk7C = 0;
    arg0->invincibility_timer = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    CollisionRelated(PLAYER_OBJECT(arg0));
    arg0->air_state = 0;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;

    switch (arg0->unk2) {
    case 0:
        arg0->x_speed = FIXED(8);
        arg0->unk15 = 0x40;
        break;
    case 1:
        arg0->x_speed = FIXED(-8);
        arg0->unk15 = 0;
        break;
    case 2:
        arg0->y_speed = FIXED(8);
        break;
    }
    arg0->unk16 = 6;

    arg0->ext.main_19.unk80 = get_random() & 1;
    if (arg0->ext.main_19.unk8A > 0x17)
        arg0->ext.main_19.unk8A = 1;
    arg0->ext.main_19.animation_index = (u8)arg0->unk2;
    index = arg0->unk2 >> 1;
    arg0->hurt_box = D_800FC744[index];
    arg0->attack_box = D_800FC74C[index];
    arg0->terrain_box = surface_hopper_attach_terrain_boxes[index];
    arg0->collision_data = D_80106BF4;
    func_8002C808(PLAYER_OBJECT(arg0));
    arg0->unk5 = arg0->collision_flags != 0 ? 2 : 5;
}

void func_80052A68(struct MainObj* arg0)
{
    s32 collision;
    s16 x;
    s16 y;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    surface_hopper_step_funcs[(u8)arg0->unk5](arg0);
    func_8002D9BC(arg0);
    collision = func_8002DD04(arg0);
    if (collision < 0) {
        arg0->x_speed = 0;
        arg0->y_speed = 0;
        arg0->x_accel = 0;
        arg0->gravity = 0;
        spawn_explosion(BASE_OBJECT(arg0));
        spawn_debris(8, surface_hopper_debris, arg0);
        x = arg0->x_pos.i.hi;
        y = arg0->y_pos.i.hi;
        if (arg0->ext.main_19.animation_index < 2) {
            x += arg0->unk15 != 0 ? -0x10 : 0x10;
        } else {
            y += 0x10;
        }
        func_800BF638(BASE_OBJECT(arg0), 0xC, x, y);
        arg0->state = 2;
        return;
    }

    if (func_8002B160(BASE_OBJECT(arg0)) != 0)
        arg0->state = 2;
    else
        is_on_screen(BASE_OBJECT(arg0));
}

u16 func_800537E0(struct MainObj* arg0, u8 direction, u8 vertical)
{
    struct Unk_unk68* bounds = arg0->terrain_box;
    s32 first;
    s32 second;
    s16 probe;
    s16 edge;

    if (vertical == 0) {
        if (direction == 0) {
            probe = -(u16)arg0->ext.main_19.unk8A;
            edge = probe - (u8)bounds->unk3;
        } else {
            probe = arg0->ext.main_19.unk8A;
            edge = probe + (u8)bounds->unk3;
        }
        if (arg0->unk15 == 0) {
            first = surface_hopper_probe_collision(PLAYER_OBJECT(arg0), -1, probe);
            second = surface_hopper_probe_tile(PLAYER_OBJECT(arg0), -4, edge);
        } else {
            first = surface_hopper_probe_collision(PLAYER_OBJECT(arg0), 1, probe);
            second = surface_hopper_probe_tile(PLAYER_OBJECT(arg0), 4, edge);
        }
        if ((first & 0xF) == (1 << arg0->ext.main_19.animation_index))
            return (u8)second < 0x38;
        return 1;
    }

    if (direction == 0) {
        probe = -(u16)arg0->ext.main_19.unk8A;
        edge = probe - (u8)bounds->unk2;
    } else {
        probe = arg0->ext.main_19.unk8A;
        edge = probe + (u8)bounds->unk2;
    }
    first = surface_hopper_probe_collision(PLAYER_OBJECT(arg0), probe, -1);
    second = surface_hopper_probe_tile(PLAYER_OBJECT(arg0), edge, -4);
    if ((first & 0xF) == 4)
        return (u8)second < 0x38;
    return 1;
}

void func_80052CB8(struct MainObj* arg0)
{
    u8 animation;
    u16 probe_result;

    if (arg0->ext.main_19.animation_index < 2) {
        if (arg0->ext.main_19.animation_index == 0) {
            arg0->unk15 = 0x40;
            arg0->ext.main_19.unk82 = 1;
        } else {
            arg0->unk15 = 0;
            arg0->ext.main_19.unk82 = 2;
        }
        arg0->ext.main_19.unk84 = (get_random() & 1) ? 0x50 : 0x20;
        probe_result = func_800537E0(arg0, arg0->ext.main_19.unk80, 0);
        if (probe_result != 0)
            arg0->ext.main_19.unk80 ^= 1;
        animation = D_800FC7D4[arg0->ext.main_19.unk80];
        arg0->ext.main_19.unk8A = 0x15;
    } else {
        arg0->ext.main_19.unk84 = (get_random() & 1) ? 0x40 : 0x20;
        if (func_800537E0(arg0, arg0->ext.main_19.unk80, 1) != 0)
            arg0->ext.main_19.unk80 ^= 1;
        arg0->unk15 = D_800FC7D8[arg0->ext.main_19.unk80];
        arg0->ext.main_19.unk8A = 0x17;
        arg0->ext.main_19.unk82 = 4;
        animation = 2;
    }

    arg0->terrain_box = surface_hopper_attach_terrain_boxes[arg0->unk2 >> 1];
    set_animation(ANIMATED_OBJECT(arg0), animation);
    arg0->unk6 = 1;
    arg0->ext.main_19.unk86 = arg0->x_pos.u.hi;
    arg0->ext.main_19.unk88 = arg0->y_pos.u.hi;
}

u8 func_80053B54(struct MainObj* arg0)
{
    s16 dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    s16 dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
    u8 direction;
    s32 selected = 0;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    direction = (u8)angle_to_object(
        OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));

    if (arg0->ext.main_19.animation_index < 2) {
        if (dx < 0x40 && dy >= 0x60)
            return 0;
        if (arg0->ext.main_19.animation_index == 0)
            selected = (u8)(direction - 8) < 0x11;
        else
            selected = (u8)(direction - 9) >= 0xF;
    } else {
        if (dx >= 0x80)
            return 0;
        selected = (u8)(direction - 0x10) < 0x11;
    }

    if (selected)
        arg0->ext.main_19.unk83 = direction & 0x1E;
    return selected;
}

void func_80052E94(struct MainObj* arg0)
{
    s32 distance;
    u8 flags;

    if (arg0->ext.main_19.animation_index < 2) {
        if (arg0->animation_step.fields.relative_step < 0) {
            distance = arg0->y_pos.i.hi - (s16)arg0->ext.main_19.unk88;
            if (distance < 0)
                distance = -distance;
            if (distance <= arg0->ext.main_19.unk84 && func_800537E0(arg0, arg0->ext.main_19.unk80, 0) == 0) {
                if (arg0->unk7C >= 0x3C && func_80053B54(arg0) != 0) {
                    arg0->unk5 = 4;
                    arg0->unk6 = 0;
                }
                goto update_animation;
            }

            flags = surface_hopper_aim_at_player(arg0);
            if (flags & 1) {
                arg0->unk6 = 4;
                arg0->ext.main_19.unk80 = arg0->y_speed < 0 ? 1 : 0;
                arg0->x_speed = 0;
                arg0->y_speed *= 3;
                set_animation(ANIMATED_OBJECT(arg0), 6);
            } else if (func_80053B54(arg0) != 0) {
                arg0->unk5 = 4;
                arg0->unk6 = 0;
            } else {
                arg0->unk6 = 2;
                set_animation(ANIMATED_OBJECT(arg0), 6);
            }
        } else if (arg0->animation_step.fields.event != 0) {
            if (arg0->ext.main_19.unk80 == 0)
                arg0->y_pos.u.hi -= arg0->ext.main_19.unk8A;
            else
                arg0->y_pos.u.hi += arg0->ext.main_19.unk8A;
            arg0->animation_step.fields.event = 0;
        }
    } else {
        if (arg0->animation_step.fields.relative_step < 0) {
            distance = arg0->x_pos.i.hi - (s16)arg0->ext.main_19.unk86;
            if (distance < 0)
                distance = -distance;
            if (distance <= arg0->ext.main_19.unk84 && func_800537E0(arg0, arg0->ext.main_19.unk80, 1) == 0) {
                if (arg0->unk7C >= 0x3C && func_80053B54(arg0) != 0) {
                    arg0->unk5 = 4;
                    arg0->unk6 = 0;
                }
                goto update_animation;
            }

            flags = surface_hopper_aim_at_player(arg0);
            if (flags & 2) {
                arg0->unk6 = 4;
                if (arg0->x_speed >= 0) {
                    arg0->unk15 = 0x40;
                    arg0->ext.main_19.unk80 = 1;
                } else {
                    arg0->unk15 = 0;
                    arg0->ext.main_19.unk80 = 0;
                }
                arg0->y_speed = 0;
                arg0->x_speed *= 3;
                set_animation(ANIMATED_OBJECT(arg0), 5);
            } else if (func_80053B54(arg0) != 0) {
                arg0->unk5 = 4;
                arg0->unk6 = 0;
            } else {
                arg0->unk6 = 2;
                set_animation(ANIMATED_OBJECT(arg0), 5);
            }
        } else if (arg0->animation_step.fields.event != 0) {
            if (arg0->ext.main_19.unk80 == 0)
                arg0->x_pos.u.hi -= arg0->ext.main_19.unk8A;
            else
                arg0->x_pos.u.hi += arg0->ext.main_19.unk8A;
            arg0->animation_step.fields.event = 0;
        }
    }

update_animation:
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_8005368C(struct MainObj* arg0)
{
    struct ShotObj* shot;
    s32 index;

    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->ext.main_19.unk80 = get_random() & 1;
        return;
    }

    if (arg0->animation_step.fields.event == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }

    shot = find_free_shot_obj();
    if (shot != NULL) {
        index = arg0->ext.main_19.animation_index;
        shot->active = 0x41;
        shot->id = 0xB;
        shot->x_pos.i.hi = arg0->x_pos.i.hi + D_800FC7E8[index * 2];
        shot->y_pos.i.hi = arg0->y_pos.i.hi + D_800FC7E8[index * 2 + 1];
        shot->animation_table = (u32**)arg0->animation_table;
        shot->unk40 = arg0->unk40;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->unk42 = arg0->unk42 & 0x7FFF;
        shot->unk7C = (struct WeaponObj*)arg0;
        shot->unk16 = arg0->unk16;
        shot->unk15 = arg0->unk15;
        set_velocity_from_angle(MOVING_OBJECT(shot), arg0->ext.main_19.unk83);
    }
    arg0->animation_step.fields.event = 0;
}

void func_80053338(struct MainObj* arg0)
{
    struct Unk_unk68* bounds;
    s16 probe_x;
    s16 probe_y;
    s32 distance;
    s32 nearby;
    u8 collision;
    u8 direction;

    move_object(MOVING_OBJECT(arg0));
    CollisionRelated(PLAYER_OBJECT(arg0));
    bounds = arg0->terrain_box;
    nearby = 0;
    if (arg0->ext.main_19.animation_index < 2) {
        probe_y = arg0->y_pos.i.hi;
        if (arg0->ext.main_19.unk80 == 0)
            probe_y -= (u8)bounds->unk3;
        else
            probe_y += (u8)bounds->unk3;
        probe_x = arg0->x_pos.i.hi + (arg0->unk15 != 0 ? 4 : -4);
        distance = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
    } else {
        probe_x = arg0->x_pos.i.hi;
        if (arg0->unk15 == 0)
            probe_x -= (u8)bounds->unk2;
        else
            probe_x += (u8)bounds->unk2;
        probe_y = arg0->y_pos.i.hi - 4;
        distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    }
    if (distance < 0)
        distance = -distance;
    if (distance < 0x18)
        nearby = 1;

    collision = func_8002D724(PLAYER_OBJECT(arg0), probe_x, probe_y);
    if ((arg0->collision_flags & (u8)~arg0->ext.main_19.unk82) == 0 && collision >= 0x38 && !nearby) {
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }

    if (arg0->ext.main_19.animation_index < 2) {
        set_animation(ANIMATED_OBJECT(arg0), 0xB);
        arg0->unk6 = 6;
        arg0->ext.main_19.unk80 ^= 1;
        direction = arg0->ext.main_19.unk80;
        if ((arg0->collision_flags >> (direction + 2)) & 1)
            arg0->ext.main_19.unk80 = direction ^ 1;
    } else {
        set_animation(ANIMATED_OBJECT(arg0), 0xA);
        arg0->unk6 = 6;
        arg0->unk15 ^= 0x40;
        arg0->ext.main_19.unk80 ^= 1;
        direction = arg0->ext.main_19.unk80;
        if ((arg0->collision_flags >> direction) & 1)
            arg0->ext.main_19.unk80 = direction ^ 1;
    }
}

s32 func_8002BD58(struct MainObj* obj0, struct MainObj* obj1, s16* out_x,
    s16* out_y)
{
    const struct Unk_unk68* box0;
    const struct Unk_unk68* box1;
    s32 flip0;
    s32 flip1;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 sum;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 result;

    if (obj1->invincibility_timer != 0) {
        return 0;
    }
    box0 = (const struct Unk_unk68*)obj0->attack_box;
    if (box0 == NULL) {
        return 0;
    }
    box1 = (const struct Unk_unk68*)obj1->hurt_box;
    if (box1 == NULL) {
        return 0;
    }

    flip0 = (u8)obj0->unk15 & 0x40;
    flip1 = (u8)obj1->unk15 & 0x40;
    t1 = box0->unk2;
    t2 = box1->unk2;
    sum = t1 + t2;
    a2 = flip0 ? obj0->x_pos.i.hi - box0->unk0 : obj0->x_pos.i.hi + box0->unk0;
    a0 = flip1 ? obj1->x_pos.i.hi - box1->unk0 : obj1->x_pos.i.hi + box1->unk0;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }

    if (a0 < a2) {
        if (flip0 && flip1) {
            if (!(a1 < t1)) {
                return 0;
            }
            if (a2 < a0 || t1 < t2 + a1) {
                result = a0 + (t1 - a1) / 2;
            } else {
                result = a0 - (t2 >> 1);
            }
        } else if (flip0) {
            if (!(a1 < sum)) {
                return 0;
            }
            if (!(a0 < a2 - t1) && t2 < a1) {
                result = a0 + (t2 >> 1);
            } else if (!(t2 + a0 < a2) && t1 < a1) {
                result = a2 - (t1 >> 1);
            } else {
                t0 = a2 - t1;
                if (t0 < a0) {
                    result = a0 + a1 / 2;
                } else {
                    result = t0 + ((t2 + a0) - t0) / 2;
                }
            }
        } else if (flip1) {
            return 0;
        } else {
            if (!(a1 < t2)) {
                return 0;
            }
            if (a2 < a0 || t2 < a1 + t1) {
                result = a2 + (t2 - a1) / 2;
            } else {
                result = (t1 >> 1) + a2;
            }
        }
    } else if (flip0) {
        if (!flip1 || !(a1 < t2)) {
            return 0;
        }
        if (t2 < a1 + t1) {
            result = a2 - (t2 - a1) / 2;
        } else {
            result = a2 - (t1 >> 1);
        }
    } else if (flip1) {
        if (!(a1 < sum)) {
            return 0;
        }
        if (t1 < a1) {
            result = (t1 >> 1) + a2;
        } else if (t2 < a1) {
            result = a0 - (t2 >> 1);
        } else {
            result = a0 - (a0 - a2) / 2;
        }
    } else {
        if (!(a1 < t1)) {
            return 0;
        }
        result = a0 + (t1 - a1) / 2;
    }
    *out_x = (s16)result;

    t1 = box0->unk3;
    t2 = box1->unk3;
    a2 = obj0->y_pos.i.hi + box0->unk1;
    a0 = obj1->y_pos.i.hi + box1->unk1;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }
    if (a0 < a2) {
        if (!(a1 < t2)) {
            return 0;
        }
        if (a2 < a0 || t2 < a1 + t1) {
            result = a2 + (t2 - a1) / 2;
        } else {
            result = (t1 >> 1) + a2;
        }
    } else {
        if (!(a1 < t1)) {
            return 0;
        }
        if (t1 < a1 + t2) {
            result = a0 + (t1 - a1) / 2;
        } else {
            result = a0 + (t2 >> 1);
        }
    }
    *out_y = (s16)result;
    return 1;
}

extern union AnimationStep* D_800F9E1C[];
extern struct Unk_unk68 spike_marl_terrain_box;

void func_80043390(struct MainObj* arg0)
{
    s32 index;
    s32 column;
    s32 row;

    arg0->unk7C = 0;
    arg0->hp = 6;
    arg0->invincibility_timer = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
    arg0->animation_table = (const u8* const*)D_800F9E1C;
    arg0->terrain_box = &spike_marl_terrain_box;
    arg0->hurt_box = (const u8*)&spike_marl_walk_hurt_box;
    arg0->attack_box = (const u8*)&spike_marl_walk_attack_box;
    arg0->unk16 = 4;
    index = func_8002938C(3);
    arg0->unk40 = (u16)((u32)D_801406A8[index] >> 7);
    index = func_8002938C(3);
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
    column = (func_8002938C(3) << 2) + 0x18;
    row = func_8002938C(3);
    arg0->unk42 = (u16)((column - ((column >> 4) << 4))
        | ((((row + 6) >> 2) + 0x1E0) << 6));
    arg0->air_state = 0;
    switch (arg0->unk2) {
    case 0:
        arg0->collision_data = D_80106470;
        set_animation(arg0, 1);
        arg0->contact_damage = 3;
        arg0->ext.main_3.turn_timer = 0x78;
        arg0->ext.main_3.alerted = 0;
        arg0->ext.main_3.player_ahead = 0;
        arg0->unk5 = 2;
        break;
    case 1:
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->ext.main_3.turn_timer = 0x78;
        arg0->contact_damage = 4;
        arg0->ext.main_3.alerted = 1;
        arg0->ext.main_3.player_ahead = 0;
        arg0->unk5 = 5;
        break;
    default:
        arg0->collision_data = (const u16*)D_801060F0;
        arg0->contact_damage = 4;
        arg0->ext.main_3.alerted = 1;
        arg0->ext.main_3.player_ahead = 0;
        arg0->ext.main_3.turn_timer = 0x78;
        set_animation(arg0, 5);
        arg0->unk5 = 8;
        break;
    }
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->state = 1;
    arg0->unk6 = 0;
}

s32 func_8002BB80(struct MainObj* obj0, struct MainObj* obj1)
{
    const struct Unk_unk68* box0;
    const struct Unk_unk68* box1;
    s32 flip0;
    s32 flip1;
    s32 sum;
    s32 t1;
    s32 t2;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 overlap;

    if (obj1->invincibility_timer != 0) {
        return 0;
    }
    box0 = (const struct Unk_unk68*)obj0->attack_box;
    if (box0 == NULL) {
        return 0;
    }
    box1 = (const struct Unk_unk68*)obj1->hurt_box;
    if (box1 == NULL) {
        return 0;
    }

    flip0 = (u8)obj0->unk15 & 0x40;
    flip1 = (u8)obj1->unk15 & 0x40;
    t1 = box0->unk2;
    t2 = box1->unk2;
    sum = t1 + t2;
    a2 = flip0 ? obj0->x_pos.i.hi - box0->unk0 : obj0->x_pos.i.hi + box0->unk0;
    a0 = flip1 ? obj1->x_pos.i.hi - box1->unk0 : obj1->x_pos.i.hi + box1->unk0;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }

    if (a0 < a2) {
        if (flip0) {
            overlap = flip1 ? a1 < t1 : a1 < sum;
        } else if (flip1) {
            return 0;
        } else {
            overlap = a1 < t2;
        }
    } else if (flip0) {
        if (!flip1) {
            return 0;
        }
        overlap = a1 < t2;
    } else {
        overlap = flip1 ? a1 < sum : a1 < t1;
    }
    if (overlap == 0) {
        return 0;
    }

    a2 = obj0->y_pos.i.hi + box0->unk1;
    a0 = obj1->y_pos.i.hi + box1->unk1;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }
    if (a0 < a2) {
        return a1 < box1->unk3;
    }
    return a1 < box0->unk3;
}

ret_u8 func_8002D9BC(void* shot)
{
    struct ShotObj* arg0 = (struct ShotObj*)shot;
    s32 result;
    s8 health;
    s8 damage;
    u32 amount;
    u8 charge;

    if (g_Player.spike_immune != 0) {
        return 0;
    }

    if (g_Player.ride_state < 0) {
        if (qux_object.unk5C & 0x80) {
            return 0;
        }
        if (qux_object.unk85 != 0) {
            return 0;
        }
        if (!func_8002BB80(MAIN_OBJECT(arg0), MAIN_OBJECT(&qux_object))) {
            return 0;
        }
        qux_object.unk63 = 0;
        qux_object.unk86 = 0;
        qux_object.unk63 = arg0->unk60 < 5 ? 1 : 2;
        health = (u8)qux_object.unk5C - (u8)arg0->unk60;
        qux_object.unk5C = health;
        qux_object.unk5C = (health << 24) > 0 ? (s8)(health | 0x80) : (s8)-0x80;
        qux_object.unk84 = qux_object.x_pos.i.hi < arg0->x_pos.i.hi ? 0x40 : 0;
        return 1;
    }

    if (g_Player.hp & 0x80) {
        return 0;
    }
    if (g_Player.hurt_phase != 0) {
        return 0;
    }
    if (!func_8002BB80(MAIN_OBJECT(arg0), MAIN_OBJECT(&g_Player))) {
        return 0;
    }

    g_Player.stun_timer = 0;
    g_Player.hurt_type = (u8)arg0->unk62;
    switch (arg0->unk62) {
    case 0:
        if (g_Player.unk2 == 0 && ((u8)g_Player.armor_parts & 2)) {
            g_Player.hurt_type = 4;
        } else {
            g_Player.hurt_type = arg0->unk60 < 5 ? 1 : 2;
        }
        break;
    case 3:
        g_Player.stun_timer = 1;
        break;
    }

    damage = arg0->unk60;
    if (damage != 0) {
        if ((u8)g_Player.armor_parts & 2) {
            amount = damage < 3 ? 1 : (u32)(((arg0->unk60 / 3) << 24) >> 23);
            g_Player.hp = (u8)g_Player.hp - amount;
        } else {
            g_Player.hp = (u8)g_Player.hp - (u8)damage;
        }
    }
    g_Player.hp = g_Player.hp > 0 ? (s8)(g_Player.hp | 0x80) : (s8)-0x80;

    if (arg0->unk62 != 3) {
        g_Player.hit_facing = g_Player.x_pos.i.hi < arg0->x_pos.i.hi ? 0x40 : 0;
    }

    result = 1;
    if (g_Player.unk2 == 0) {
        if (!((u8)g_Player.armor_parts & 2)) {
            return 1;
        }
    } else if (!((u8)g_Player.boss_flags & 0x20)) {
        return 1;
    }

    if (g_Player.weapon_energy[0] != 0x30) {
        charge = (s8)g_Player.weapon_energy[0] + 6;
        g_Player.weapon_energy[0] = charge;
        if ((s8)charge >= 0x31) {
            g_Player.weapon_energy[0] = 0x30;
        }
    }
    return result;
}

void func_80092684(struct WeaponObj* arg0)
{
    s32 velocity;

    arg0->on_screen = 1;
    if (arg0->id == 9) {
        velocity = FIXED(8);
        arg0->unk2 = 0;
    } else {
        velocity = FIXED(10);
        arg0->unk2 = 1;
    }
    arg0->x_vel.val = velocity;
    arg0->unk50 = (const u8*)&D_80108708[arg0->unk2];
    if (arg0->unk15 == 0) {
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    set_animation(arg0, arg0->unk2 + 0x1A);
    arg0->state = (u8)arg0->state + 1;
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x14);
}

void func_80043C0C(struct MainObj* arg0)
{
    s32 magnitude = arg0->x_speed;

    if (magnitude < 0) {
        magnitude = -magnitude;
    }
    if (magnitude <= 0xFFFF
        || ((arg0->collision_flags & 2) && arg0->unk15 == 0)
        || ((arg0->collision_flags & 1) && arg0->unk15 != 0)) {
        arg0->contact_damage = 3;
        arg0->x_speed = 0;
        arg0->x_accel = 0;
        arg0->unk5 = 7;
        arg0->unk6 = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_8002DF7C(struct WeaponObj* arg0, s32 arg1)
{
    const struct EffectSpawnData* entry = &D_800F460C[arg0->id];
    struct VisualObj* visual;
    s32 visual_id;

    if (entry->effect_type == 4) {
        return;
    }

    if (arg1 < 0) {
        if (entry->set_facing != 0) {
            arg0->unk98 = -1;
        }
        func_8001540C(0, 6, arg0);
        visual_id = 0;
    } else {
        if (entry->set_facing != 0 && (arg1 == 0 || entry->keep_facing == 0)) {
            arg0->unk98 = 1;
        }
        switch (entry->effect_type) {
        case 0:
            func_8001540C(1, entry->animation_id, arg0);
            break;
        case 1:
            func_8001540C(1, arg1 != 0 ? 0xA : 9, arg0);
            break;
        case 2:
        case 3:
            func_8001540C(5, entry->animation_id, arg0);
            break;
        }
        visual_id = entry->visual_id;
    }

    visual = find_free_visual_obj();
    if (visual == NULL) {
        return;
    }
    visual->active = 0x21;
    visual->id = 3;
    visual->unk2 = (s8)visual_id;
    visual->bg_offset = arg0->bg_offset;
    visual->animation_table = D_8011BF40;
    visual->unk40 = 0;
    visual->unk42 = 0x7802;
    visual->unk16 = 0;
    visual->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
    visual->x_pos.i.hi = (s16)((u16*)&arg0->unk80)[0];
    visual->y_pos.i.hi = (s16)((u16*)&arg0->unk80)[1];
    visual->unk15 = arg0->unk15 ^ 0x40;
}

s32 func_8002DE30(struct MainObj* arg0, struct WeaponObj* arg1)
{
    const u8* table;
    s8 hit;
    u8 id;
    u8 kind;

    hit = arg1->unk64;
    id = arg1->id;
    if (hit != 0) {
        if (hit == arg0->unk65) {
            return 0x7E;
        }
        arg0->unk65 = hit;
    } else {
        arg0->unk65 = 0;
    }

    table = (const u8*)arg0->collision_data;
    kind = table[(s8)id * 2];
    arg0->unk63 = kind;
    if ((s8)kind == 2) {
        return 0;
    }
    if (((s8)id >= 0x1A && (s8)id < 0x24)
        || ((s8)id >= 0x3D && (s8)id < 0x3F)) {
        g_Player.update_delay_request = 1;
    }
    if (arg0->unk63 == -1) {
        func_8002DF7C(arg1, -1);
        return 0x7F;
    }

    arg0->hp = (u8)arg0->hp - table[((s8)id * 2) + 1];
    arg0->unk42 |= 0x8000;
    if (arg0->hp <= 0) {
        arg0->hp = 0;
        func_8002DF7C(arg1, 1);
        return -1;
    }
    if (arg0->unk63 != 0) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
    func_8002DF7C(arg1, 0);
    return (s8)(id + 1);
}

void func_800BF638(struct BaseObj* arg0, s8 arg1, s16 arg2, s16 arg3)
{
    const u8* weights = &drop_item_table[0][0];
    s32 offset = (s8)arg1 * 6;
    s32 roll = get_random() & 0xFF;
    struct ItemObj* item;
    s32 index;
    s32 counter;

    if (engine_obj.stage == 5) {
        return;
    }

    counter = 0xFF;
    do {
        counter++;
        index = counter & 0xFF;
        roll = (roll & 0xFF) - weights[index + (offset & 0xFF)];
    } while ((u32)(roll & 0xFFFF) < 0x100);

    if (index == 0) {
        return;
    }
    item = find_free_item_obj();
    if (item == NULL) {
        return;
    }
    item->active = 0x21;
    item->id = 2;
    item->unk2 = counter - 1;
    item->x_pos.i.hi = arg2;
    item->y_pos.i.hi = arg3;
    item->backref = NULL;
    item->unk7C.value = 0;
    item->bg_offset = arg0->bg_offset;
}

void func_800AFB90(struct VisualObj* arg0)
{
    s32 index = arg0->unk2;
    s32 column = index + 4;
    s32 row = column < 0 ? index + 0x13 : column;

    arg0->on_screen = 1;
    arg0->unk38 = NULL;
    arg0->animation_table = (u32**)blast_animations;
    arg0->unk40 = 0;
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 2);
    row >>= 4;
    arg0->unk42 = (u16)((column - (row << 4)) | ((row + 0x1E0) << 6));
    set_animation(arg0, 0);
    if ((u8)arg0->unk5C.value != 0xFF) {
        func_8001540C(0, (u8)arg0->unk5C.value, arg0);
    }
    arg0->state = (u8)arg0->state + 1;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800C8610(struct MiscObj* arg0)
{
    struct MainObj* owner = arg0->ext.misc_2.owner;

    arg0->on_screen = 1;
    if (arg0->unk2 == 0) {
        arg0->unk3C = (void*)owner->sprite_frames;
        arg0->animation_table = (u32**)owner->animation_table;
        arg0->unk40 = owner->unk40;
        arg0->unk42 = owner->unk42 & 0x7FFF;
    }
    arg0->unk16 = 1;
    arg0->unk2C = 0x5000;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_vel.val = debris_x_speeds[get_random() & 7] + owner->x_speed / 2;
    arg0->y_vel.val = debris_y_speeds[get_random() & 7];
    set_animation(arg0, arg0->ext.misc_2.unk58);
    arg0->state = (u8)arg0->state + 1;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800BF76C(struct ItemObj* arg0)
{
    u16 flags;
    u8 kind;
    s32 blocked;

    arg0->active = 0x21;
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk15 = 0;
    arg0->animation_table = (const u8* const*)pickup_animations;
    arg0->unk42 = 0x7807;
    arg0->unk16 = 6;
    arg0->unk40 = 0;
    arg0->bg_offset = 0;
    arg0->unk2 = (u8)arg0->unk2 & 0x7F;
    arg0->active |= 0x20;
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 3);
    if (arg0->unk2 == 4) {
        arg0->unk42 = 0x780B;
    }

    kind = (u8)arg0->unk2;
    if ((u32)(kind - 7) < 8) {
        arg0->unk7C.value = 7;
    } else if ((u32)(kind - 0xF) < 2) {
        arg0->unk7C.value = 8;
    } else if ((s8)kind == 0x11) {
        arg0->unk7C.value = 9;
    } else if ((s8)kind == 0x12) {
        arg0->unk7C.value = 0xA;
        arg0->unk42 = 0x780B;
    } else {
        arg0->unk7C.value = kind;
    }

    kind = arg0->unk7C.value;
    arg0->unk68 = (struct Unk_unk68*)pickup_hit_boxes[kind];
    arg0->ext.item_2.unk82 = 0xF0;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    if (arg0->backref == NULL) {
        arg0->y_vel.val = FIXED(8);
        arg0->unk2C = 0x8000;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 1;
    } else {
        arg0->y_vel.val = 0;
        arg0->unk2C = 0x8000;
        arg0->unk67 = 0;
    }

    blocked = 0;
    flags = engine_obj.unk5A;
    switch (kind) {
    case 7:
        if ((flags & 0xFF) == 0xFF
            || (((s32)flags >> (arg0->unk2 - 7)) & 1) != 0) {
            blocked = 1;
        }
        break;
    case 8:
        if ((flags & 0x3000) == 0x3000
            || (flags & (0x1000 << (arg0->unk2 - 0xF))) != 0) {
            blocked = 1;
        }
        break;
    case 9:
        if ((flags & 0x4000)
            || (flags & (0x4000 << (arg0->unk2 - 0x11))) != 0) {
            blocked = 1;
        }
        break;
    case 0xA:
        if ((flags & 0x8000)
            || (flags & (0x8000 << (arg0->unk2 - 0x12))) != 0) {
            blocked = 1;
        }
        break;
    }

    if (blocked) {
        arg0->state = 3;
        return;
    }
    ((u8*)&arg0->unk7C)[1] = 0;
    set_animation(arg0, kind);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80049E68(struct MainObj* arg0)
{
    u32 timer;
    s32 distance;

    move_object(MOVING_OBJECT(arg0));

    timer = arg0->ext.main_10.timer - 1;
    arg0->ext.main_10.timer = timer;
    if (timer == 0) {
        arg0->y_speed = FIXED(2);
        arg0->x_speed = 0;
        arg0->unk62 = 0;
        arg0->attack_box = NULL;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }

    if (arg0->unk15 == 0) {
        distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    } else {
        distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    }
    if (distance >= 0x30) {
        arg0->ext.main_10.timer = 0x14;
        arg0->x_speed = 0;
        arg0->unk6 = 2;
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_800BFCC0(struct ItemObj* arg0, u8 arg1)
{
    struct PlayerObj* player = &g_Player;
    s32 charge_step;
    s32 engine_step;
    u32 index;
    u32 selected;
    u8 buttons;
    u8 value;
    s8 current;
    s8 next;

    (void)arg0;
    if (arg1 == 2) {
        charge_step = 4;
        engine_step = 1;
    } else if (arg1 == 3) {
        charge_step = 0x10;
        engine_step = 2;
    } else if (arg1 == 6) {
        charge_step = 0x30;
        engine_step = 4;
    } else {
        charge_step = 0;
        engine_step = 0;
    }

    if (engine_obj.cur_character == 0 && g_Player.weapon == 0) {
        index = 1;
        selected = 0;
        buttons = (u8)g_Player.boss_flags;
        do {
            if (((buttons >> (index - 1)) & 1) != 0) {
                if (player->weapon_energy[index] < player->weapon_energy[selected]) {
                    selected = index;
                }
            }
            index++;
        } while (index < 9);

        if (selected != 0) {
            value = (u8)g_Player.weapon_energy[0] + charge_step;
            g_Player.weapon_energy[0] = value;
            if ((s8)value >= 0x31) {
                g_Player.weapon_energy[0] = 0x30;
            }
        }
        value = (u8)player->weapon_energy[selected] + charge_step;
        player->weapon_energy[selected] = value;
        if ((s8)value >= 0x31) {
            player->weapon_energy[selected] = 0x30;
        }
    } else {
        u8 mask = engine_obj.cur_character == 0
            ? (u8)((u8)g_Player.boss_flags >> (g_Player.weapon - 1))
            : (u8)g_Player.boss_flags;

        if ((mask & 1) != 0) {
            current = player->weapon_energy[g_Player.weapon];
            if (current < 0x30) {
                next = current + charge_step;
                player->weapon_energy[g_Player.weapon] = next;
                if (next >= 0x31) {
                    player->weapon_energy[g_Player.weapon] = 0x30;
                }
                func_8001540C(0, 0x16, 0);
            } else {
                player->weapon_energy[g_Player.weapon] = 0x30;
            }
        }
    }

    if ((engine_obj.unk5A & 0x4000) != 0) {
        value = (u8)engine_obj.unk5C[2] + engine_step;
        engine_obj.unk5C[2] = value;
        if ((s8)value >= 0x21) {
            engine_obj.unk5C[2] = 0x20;
        }
    }
}

void func_80033D54(struct PlayerObj* arg0)
{
    const struct PlayerHurtVelocity* state;
    s32 index;

    player_set_collision_bounds(arg0);
    arg0->hp = (u8)arg0->hp & 0x7F;
    if (arg0->unk5 == 0x11) {
        return;
    }

    arg0->hurt_phase = 1;
    player_reset_actions(arg0);
    index = arg0->hurt_type;
    arg0->unk15 = (u8)arg0->hit_facing;
    player_set_animation(arg0, player_hurt_animations[index]);
    state = &player_hurt_velocities[index];
    arg0->x_vel.val = state->x_vel;
    arg0->unk28 = state->x_accel;
    arg0->y_vel.val = state->y_vel;
    arg0->unk2C = state->gravity;
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->invincibility_timer = player_hurt_invincibility[index];
    if ((u8)(index - 2) < 2) {
        arg0->air_state = 1;
    }
    func_8001540C(3, (get_random() & 1) ^ 1, arg0);
    arg0->unk5 = 0x11;
    arg0->unk6 = 0;
}

void func_8004A178(struct MainObj* arg0)
{
    s32 saved_x;
    s32 saved_y;
    s32 x_vel;
    s32 y_vel;
    u32 timer;
    s32 past_player;

    if (arg0->unk15 != 0) {
        past_player = arg0->x_pos.val > g_Player.x_pos.val;
    } else {
        past_player = g_Player.x_pos.val > arg0->x_pos.val;
    }

    if (!past_player) {
        timer = arg0->ext.main_10.timer - 1;
        arg0->ext.main_10.timer = timer;
        if (timer != 0
            && !(arg0->ext.main_10.hold_state == 1 && g_Player.stun_timer != 0)) {
            saved_x = arg0->x_pos.val;
            saved_y = arg0->y_pos.val;
            if (arg0->unk15 != 0) {
                arg0->x_pos.i.hi = (u16)arg0->x_pos.i.hi + 0x18;
            } else {
                arg0->x_pos.i.hi = (u16)arg0->x_pos.i.hi - 0x18;
            }
            arg0->y_pos.i.hi = (u16)arg0->y_pos.i.hi + 0x18;
            set_velocity_from_angle(MOVING_OBJECT(arg0), angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
            x_vel = arg0->x_speed;
            y_vel = arg0->y_speed;
            arg0->x_pos.val = saved_x;
            arg0->y_pos.val = saved_y;
            arg0->x_speed = x_vel + (x_vel / 2);
            arg0->y_speed = y_vel + (y_vel / 2);
            move_object(MOVING_OBJECT(arg0));
            if (g_Player.stun_timer != 0) {
                set_animation(arg0, 3);
                arg0->x_speed = 0;
                arg0->y_speed = 0;
                arg0->unk6 = 2;
            }
            animate_object(ANIMATED_OBJECT(arg0));
            return;
        }
    }

    arg0->y_speed = FIXED(2);
    arg0->x_speed = 0;
    arg0->unk62 = 0;
    arg0->attack_box = NULL;
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void func_80068548(struct MainObj* arg0)
{
    u8* shared = (u8*)&SP_CUR_MAIN_OBJ->ext;
    s32 column;
    s32 wrapped;
    s32 index;
    s32 row;
    s32 sub;
    s32 spawned_late;

    spawned_late = arg0->unk2 >= 6;
    if (!spawned_late) {
        shared[6] = 0;
        shared[5] = (s8)arg0->unk2 / 2;
        sub = (u8)arg0->unk2 & 1;
        arg0->unk2 = sub;
        index = func_8002938C(0x22);
        row = func_8002938C(0x22);
        if (shared[5] == 0 || (shared[5] == 2 && sub == 0)) {
            column = index * 4 + 0x18;
            wrapped = column < 0 ? index * 4 + 0x27 : column;
        } else {
            column = index * 4 + 0x1A;
            wrapped = column < 0 ? index * 4 + 0x29 : column;
        }
    } else {
        shared[6] = 1;
        if (arg0->unk2 != 9) {
            arg0->unk7A = 1;
        }
        index = func_8002938C(0x22);
        row = func_8002938C(0x22);
        column = index * 4 + 0x18;
        wrapped = column < 0 ? index * 4 + 0x27 : column;
    }

    row = row + 6 < 0 ? row + 9 : row + 6;
    arg0->unk42 = (u16)((column - ((wrapped >> 4) << 4))
        | (((row >> 2) + 0x1E0) << 6));
    if (spawned_late) {
        shared[5] = (u8)arg0->unk2;
    }

    arg0->unk40 = (u16)((u32)D_801406A8[func_8002938C(0x22)] >> 7);
    arg0->sprite_frames
        = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x22));
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk15 = 0;
    arg0->invincibility_timer = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)highway_trooper_animations;
    arg0->terrain_box = (struct Unk_unk68*)D_800FFB5C;
    arg0->attack_box = train_soldier_guard_attack_box;
    arg0->hurt_box = train_soldier_guard_hurt_box;
    arg0->collision_data = (const u16*)D_801076F8;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk16 = 6;
    arg0->hp = 6;
    arg0->contact_damage = 3;
    set_animation(arg0, 1);
    arg0->state = 1;
    arg0->unk5 = shared[5] == 2 ? 7 : 2;
    if (shared[6] != 0) {
        arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
        if (arg0->unk2 != 9) {
            arg0->state = 3;
            arg0->unk5 = 0;
        } else {
            arg0->state = 1;
            arg0->unk5 = 2;
        }
    }
    arg0->unk6 = 0;
    shared[1] = 0;
    shared[3] = 0;
}

void func_8009EBA8(struct ShotObj* self)
{
    s32 velocity;
    s32 variant;
    s16 x;

    self->on_screen = 1;
    self->state = (u8)self->state + 1;
    variant = (u8)self->unk2 & 0xF;

    if (self->unk2 & 0x80) {
        self->y_vel.val = 0;
        velocity = variant == 1 ? -FIXED(3) : -FIXED(1.5);
        if (self->unk15 != 0) {
            velocity = FIXED(3);
        }
        self->x_vel.val = velocity;
        if (variant == 0) {
            self->y_vel.val = FIXED(1.5);
        }
        if (variant == 2) {
            self->y_vel.val = -FIXED(1.5);
        }
        self->unk28 = 0;
        self->unk2C = 0;
        set_animation(self, 0x10);
        self->unk60 = 2;
    } else {
        velocity = self->unk15 != 0 ? FIXED(3) : -FIXED(3);
        self->y_vel.val = FIXED(1.5);
        self->x_vel.val = velocity;
        self->unk28 = 0;
        self->unk2C = 0x4000;
        set_animation(self, 0x16);
        self->unk60 = 5;
    }

    x = self->x_pos.i.hi;
    if (self->unk15 != 0) {
        x += grenade_spawn_offsets[variant << 1];
    } else {
        x -= grenade_spawn_offsets[variant << 1];
    }
    self->x_pos.i.hi = x;

    self->unk16 = 6;
    self->unk68 = (struct Unk_unk68*)grenade_terrain_box;
    self->unk54 = grenade_hit_box;
    self->unk50.data = grenade_hit_box;
    self->unk67 = 0;
    self->y_pos.u.hi += (s8)grenade_spawn_offsets[(variant << 1) + 1];
}

void func_80068B80(struct MainObj* arg0)
{
    s32 velocity;

    arg0->collision_data = (const u16*)D_801076F8;
    arg0->hurt_box = train_soldier_guard_hurt_box;
    arg0->unk6 = (u8)arg0->unk6 + 1;
    arg0->attack_box = train_soldier_guard_attack_box;
    if (((u8*)&SP_CUR_MAIN_OBJ->ext)[6] == 0) {
        velocity = arg0->unk15 != 0 ? FIXED(1.75) : -FIXED(1.75);
    } else {
        velocity = arg0->unk15 != 0 ? FIXED(3) : -FIXED(3);
    }
    arg0->x_speed = velocity;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    set_animation(arg0, 1);
}

void func_80042950(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;
    u8 weapon;
    s32 flags;

    arg0->active = (u8)arg0->active | 4;
    weapon = (u8)g_Player.weapon;
    flags = 0;
    if (((s8)engine_obj.unk46 / 2) >= g_Player.hp) {
        flags = 1;
        ext[0] = 1;
    }
    if (engine_obj.cur_character == 0) {
        if (weapon != 0 && g_Player.weapon_energy[weapon] < 0x19) {
            flags |= 2;
            ext[0] = 3;
        }
    }
    if ((flags & 0xFF) == 0) {
        despawn_object(OBJECT_HEADER(arg0));
        return;
    }
    if ((flags & 0xFF) == 3) {
        ext[0] = g_Player.weapon_energy[weapon] >= g_Player.hp ? 1 : 3;
    }
    arg0->state = (u8)arg0->state + 1;
}

void func_80040644(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;

    arg0->hp = 0x30;
    arg0->animation_table = (const u8* const*)D_800F9934;
    arg0->unk16 = 0x22;
    arg0->collision_data = (const u16*)D_801062F0;
    arg0->on_screen = 1;
    arg0->unk15 = 0;
    arg0->bg_offset = 0;
    arg0->contact_damage = 1;
    arg0->invincibility_timer = 0;
    arg0->attack_box = NULL;
    arg0->hurt_box = NULL;
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 2;
    engine_obj.boss_ptr = arg0;
    arg0->x_pos.val = 0;
    arg0->y_pos.val = 0;
    background_dragon_spawn_trail(PLAYER_OBJECT(arg0), 0);
    background_dragon_spawn_trail(PLAYER_OBJECT(arg0), 1);
    set_animation(arg0, 0);

    arg0->unk5 = 6;
    arg0->y_speed = 0x18000;
    arg0->x_pos.val = 0x06200000;
    arg0->y_pos.val = 0;
    arg0->x_speed = 0;
    ext[0] = 1;
    ext[2] = 0;
    ext[3] = 0;
    ext[4] = 0;
    arg0->unk7C = 0;
    arg0->unk7E = 0;
    ext[6] = 0;
    ext[5] = 0;
    ext[1] = 0;
    arg0->state = (u8)arg0->state + 1;
    update_on_screen(BASE_OBJECT(arg0), 0xA0, 0xA0);
}

void func_80040838(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;
    s32 result;
    u8 saved_step;
    u8 saved_substep;
    s8 flash;
    s32 spawn;
    s32 blocked;
    u8 timer;
    u8 next;
    s16 x;
    s16 y;
    u8 offset_index;

    if (engine_obj.character_state.bytes[0] != 0) {
        ext[5] = 1;
    }
    saved_step = (u8)arg0->unk5;
    saved_substep = (u8)arg0->unk6;
    result = func_8002DD04(arg0);
    if (result < 0) {
        ext[5] = 2;
        arg0->unk5 = saved_step;
        arg0->unk6 = saved_substep;
        arg0->invincibility_timer = 0x1E;
        arg0->unk42 &= 0x7FFF;
        update_on_screen(BASE_OBJECT(arg0), 0xA0, 0xA0);
        return;
    }
    if (result > 0) {
        arg0->unk5 = saved_step;
        arg0->unk6 = saved_substep;
        func_8001540C(2, 0xC, arg0);
        arg0->invincibility_timer = 0x1E;
    }

    flash = arg0->invincibility_timer;
    if (flash != 0) {
        arg0->invincibility_timer = flash - 1;
        if (flash & 2) {
            arg0->unk42 |= 0x8000;
        } else {
            arg0->unk42 &= ~0x8000;
        }
        if (arg0->invincibility_timer == 0) {
            arg0->unk42 &= 0x7FFF;
        }
    }

    background_dragon_step_funcs[arg0->unk5](arg0);

    blocked = get_random_nonzero() & 1;
    if (!blocked && ext[5] == 2) {
        spawn = ((u8)main_bss_state.frame_counter ^ 1) & 1;
        x = arg0->x_pos.i.hi;
        offset_index = (get_random() & 0x1F) % (COUNT(D_800F98EC) / 2);
        if (arg0->unk15 != 0) {
            x -= D_800F98EC[offset_index * 2];
        } else {
            x += D_800F98EC[offset_index * 2];
        }
        offset_index = (get_random() & 0x1F) % (COUNT(D_800F98EC) / 2);
        y = (s16)(arg0->y_pos.u.hi
            + (u16)D_800F98EC[offset_index * 2 + 1]);
        spawn_explosion_at(0, x, y, (u8)spawn)->unk16 = 0x21;
        blocked = 1;
    }

    if (blocked && ext[5] == 2) {
        timer = ext[6];
        ext[6] = timer - 1;
        if (timer != 0) {
            return;
        }
        next = 4;
    } else {
        if (arg0->hp >= 0x18) {
            return;
        }
        timer = ext[6];
        ext[6] = timer - 1;
        if (timer != 0) {
            return;
        }
        next = 0x1E;
    }
    ext[6] = next;
    arg0->unk42 ^= 0x8000;
}

void func_800419B8(struct MainObj* arg0)
{
    s32 distance;

    set_velocity_from_angle(MOVING_OBJECT(arg0),
        angle_to_point(OBJECT_HEADER(arg0), g_Player.x_pos.val, 0x01700000));

    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 0x38) {
        distance = 0x38;
    } else if (distance >= 0x40) {
        distance = 0x40;
    }
    arg0->x_speed = (arg0->x_speed * distance) >> 4;

    distance = g_Player.y_pos.i.hi - (arg0->y_pos.i.hi + 0x40);
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 0x18) {
        distance = 0x18;
    } else if (distance >= 0x40) {
        distance = 0x40;
    }
    arg0->y_speed = (arg0->y_speed * distance) >> 4;

    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));

    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance < 8) {
        s32 height = arg0->y_pos.i.hi - 0x170;

        if (height < 0) {
            height = -height;
        }
        if (height < 8) {
            arg0->y_pos.i.hi = 0x170;
            arg0->unk5 = 0xC;
            arg0->x_pos.i.hi = g_Player.x_pos.u.hi;
        }
    }

    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_800B158C(struct VisualObj* arg0)
{
    struct PlayerObj* owner = arg0->unk50;

    if (owner->active == 0 || owner->state == 2) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 == 0) {
        arg0->x_pos.i.hi = (u16)owner->x_pos.i.hi + 0x58;
    } else {
        arg0->x_pos.i.hi = (u16)owner->x_pos.i.hi - 0x58;
    }
    arg0->y_pos.i.hi = (u16)owner->y_pos.i.hi - 0x38;

    if (((u8*)&MAIN_OBJECT(owner)->ext)[0] != 0) {
        arg0->unk42 = owner->unk42;
        update_on_screen(BASE_OBJECT(arg0), 0xA0, 0xA0);
        if (arg0->animation_step.fields.event != 0 && arg0->unk2 != 0) {
            arg0->animation_step.fields.event = 0;
            if (arg0->unk5 != 0) {
                func_8001540C(2, 5, owner);
            } else {
                func_8001540C(2, 6, owner);
            }
            arg0->unk5 ^= 1;
        }
    }
}

void func_80040CCC(struct MainObj* arg0)
{
    s32 distance;

    animate_object(ANIMATED_OBJECT(arg0));
    arg0->y_pos.u.hi += (s8)arg0->animation_step.fields.event;

    distance = g_Player.x_pos.val - arg0->x_pos.val;
    if (distance < 0) {
        distance = arg0->x_pos.val - g_Player.x_pos.val;
    }
    if (distance > 0x20000) {
        distance = 0x20000;
    }
    arg0->x_speed = distance;
    if (arg0->x_pos.val < g_Player.x_pos.val) {
        arg0->x_speed = -distance;
    }

    arg0->y_speed = 0;
    move_object(MOVING_OBJECT(arg0));
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);

    arg0->unk15 = g_Player.x_pos.i.hi < arg0->x_pos.i.hi ? 0x40 : 0;
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = func_80040ABC(arg0);
    }
}

s32 func_80040ABC(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;
    const s8* flags = &engine_obj.character_state.bytes[1];
    s32 distance;
    s32 index;
    s32 kind;
    s32 value;
    s32 remainder;

    arg0->unk2 = get_random() & 1;
    if (ext[5] != 0) {
        return 8;
    }

    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (distance < 0) {
        distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    }
    if (distance >= 0x49) {
        return 6;
    }

    index = (s32)(s16)arg0->x_pos.i.hi >> 4;
    if (index < 0x50) {
        return 0xC;
    }
    index -= 0x50;
    kind = background_dragon_attack_map[index];

    switch (kind) {
    case 0:
        value = get_random() & 3;
        if (value == 1) {
            ext[1] = 3;
            return 3;
        }
        if (value == 0) {
            return 0xC;
        }
        return value == 2 ? 2 : 5;
    case 1:
    case 2:
    case 3:
        ext[2 + ext[1]] = (u8)flags[ext[1]];
        kind = background_dragon_attack_map[index];
        if (ext[1 + kind] != 0) {
            return 2;
        }
        ext[1] = kind - 1;
        return 3;
    case 4:
        ext[1] = 3;
        return 3;
    case 5:
        return 2;
    case 6:
        return 5;
    case 8:
        value = get_random_nonzero();
        remainder = value - ((value >= 0 ? value >> 2 : (value + 3) >> 2) * 4);
        if (remainder >= 3) {
            return 0xC;
        }
        if (remainder > 0) {
            return 2;
        }
        if (remainder != 0) {
            return 0xC;
        }
        return 8;
    default:
        remainder = get_random_nonzero() % 3;
        if (remainder == 1) {
            ext[1] = 3;
            return 3;
        }
        return remainder == 0 ? 2 : 5;
    }
}

void func_80041060(struct MainObj* arg0)
{
    s32 velocity;
    u8 next_substep;
    u8 index = arg0->ext.main_0.index;
    s32 distance;

    if (index != 3) {
        distance = arg0->x_pos.i.hi - D_800F99BC[index];
        if (distance < 0) {
            distance = -distance;
        }
        if (distance < 2) {
            distance = arg0->y_pos.i.hi - 0x170;
            if (distance < 0) {
                distance = -distance;
            }
            if (distance < 2) {
                arg0->y_pos.val = 0x01700000;
                next_substep = (u8)arg0->unk6;
                velocity = -0xC000;
                arg0->unk15 = 0;
                goto start_attack;
            }
        }

        set_velocity_from_angle(MOVING_OBJECT(arg0),
            angle_to_point(OBJECT_HEADER(arg0),
                (s32)D_800F99BC[index] << 16, 0x01700000));
        arg0->x_speed *= 2;
        arg0->y_speed *= 2;
        move_object(MOVING_OBJECT(arg0));
        animate_object(ANIMATED_OBJECT(arg0));
    } else {
        velocity = -0xC000;
        arg0->y_pos.val = 0x01700000;
        next_substep = (u8)arg0->unk6;

    start_attack:
        arg0->unk6 = next_substep + 1;
        if (arg0->unk15 != 0) {
            velocity = 0xC000;
        }
        arg0->x_speed = velocity;
        arg0->y_speed = 0x8000;
        set_animation(arg0, 1);
    }

    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_800415B0(struct MainObj* arg0)
{
    s32 offset = engine_obj.cur_character == 0 ? 0x480000 : 0x4A0000;
    struct ShotObj* shot;
    struct MiscObj* misc;
    s32 target;
    s32 distance;

    animate_object(ANIMATED_OBJECT(arg0));
    target = arg0->unk15 != 0 ? g_Player.x_pos.val + offset
                              : g_Player.x_pos.val - offset;
    set_velocity_from_angle(MOVING_OBJECT(arg0), angle_to_point(OBJECT_HEADER(arg0), target, 0x02140000));
    arg0->x_speed *= 4;
    arg0->y_speed *= 4;
    move_object(MOVING_OBJECT(arg0));

    distance = arg0->x_pos.val - target;
    if (distance < 0) {
        distance = -distance;
    }
    if (distance <= 0x7FFFF) {
        distance = arg0->y_pos.i.hi - 0x214;
        if (distance < 0) {
            distance = -distance;
        }
        if (distance < 8) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0;
                shot->unk2 = 4;
                shot->unk7C = (struct WeaponObj*)arg0;
                shot->state = 0;
            }
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 0x41;
                misc->id = 4;
                misc->unk2 = 0;
                misc->ext.pointer.unk50 = arg0;
                misc->state = 2;
            }
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 0x41;
                misc->id = 4;
                misc->unk2 = 1;
                misc->ext.pointer.unk50 = arg0;
                misc->state = 2;
            }
            set_animation(arg0, arg0->unk7E != 0 ? 0xD : 0xF);
            arg0->x_speed = 0;
            arg0->x_pos.val = target;
            arg0->y_pos.i.hi = 0x214;
            arg0->unk6 = (u8)arg0->unk6 + 1;
            func_8001540C(2, 4, arg0);
        }
    }
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_800994DC(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s32 animation;
    s32 x_offset;
    s32 velocity;

    arg0->unk40 = owner->unk40;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk15 = owner->unk15;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk5C = 0;
    arg0->unk42 = owner->unk42;

    switch (arg0->unk2) {
    case 0:
    case 1:
        arg0->unk16 = 1;
        arg0->unk60 = 5;
        arg0->x_pos.val = owner->x_pos.val;
        arg0->y_pos.val = owner->y_pos.val;
        arg0->bg_offset = owner->bg_offset;
        if (arg0->unk2 == 0) {
            owner->hurt_box = dragon_shot_box_3;
            arg0->unk50.data = dragon_shot_flame_box;
            arg0->state = 1;
            set_animation(arg0, 2);
        } else {
            owner->hurt_box = dragon_shot_box_4;
            arg0->unk50.data = dragon_shot_pulse_hit_box;
            arg0->state = 2;
            set_animation(arg0, 4);
        }
        break;
    case 2:
    case 3:
        arg0->unk16 = 1;
        arg0->unk60 = 5;
        arg0->unk68 = (struct Unk_unk68*)dragon_shot_box_2;
        arg0->bg_offset = 0;
        arg0->unk42 &= 0x7FFF;
        x_offset = owner->unk15 == 0 ? 0x280000 : -0x280000;
        arg0->x_pos.val
            = owner->x_pos.val + (background_objects[0].x_pos.val + x_offset);
        arg0->y_pos.val = owner->y_pos.val + background_objects[0].y_pos.val;
        if (arg0->unk2 == 2) {
            velocity = owner->unk15 != 0 ? (-0x40000 | 0x8000) : 0x38000;
        } else {
            velocity = owner->unk15 != 0 ? (-0x30000 | 0x8000) : 0x28000;
        }
        arg0->x_vel.val = velocity;
        arg0->y_vel.val = 0x18000;
        arg0->unk2C = 0x1000;
        arg0->unk50.data = dragon_shot_bomb_box;
        arg0->unk28 = 0;
        arg0->state = 3;
        set_animation(arg0, 0xA);
        break;
    case 4:
        arg0->unk60 = 5;
        arg0->x_pos.val = owner->x_pos.val;
        arg0->bg_offset = 0;
        arg0->unk16 = 6;
        arg0->state = 5;
        arg0->y_pos.val = owner->y_pos.val;
        if (owner->unk7E != 0) {
            set_animation(arg0, 0xE);
            arg0->unk50.data = dragon_shot_box_0;
            owner->hurt_box = dragon_shot_box_5;
        } else {
            set_animation(arg0, 0xC);
            arg0->unk50.data = dragon_shot_box_1;
        }
        break;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_800C899C(struct MiscObj* arg0)
{
    struct MainObj* owner = arg0->ext.pointer.unk50;
    s32 column;
    s32 wrapped;
    s32 row;
    s32 index;
    s16 count;

    arg0->animation_table = (u32**)dragon_rubble_animations;
    arg0->state = (u8)arg0->state + 1;

    index = func_8002938C(0x85);
    row = func_8002938C(0x85);
    column = index * 4 + 0x18;
    wrapped = column < 0 ? index * 4 + 0x27 : column;
    row = row + 6 < 0 ? row + 9 : row + 6;
    arg0->unk42 = (u16)((column - ((wrapped >> 4) << 4))
        | (((row >> 2) + 0x1E0) << 6));
    arg0->unk40 = (u16)((u32)D_801406A8[func_8002938C(0x85)] >> 7);
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x85));

    arg0->x_pos.val = (owner->unk15 == 0 ? owner->x_pos.i.hi + 0x30
                                         : owner->x_pos.i.hi - 0x30)
        << 16;
    arg0->y_pos.val = (owner->y_pos.i.hi - 0x5C) << 16;

    if (arg0->unk2 != 0) {
        spawn_debris(8, dragon_rubble_debris, arg0);
        spawn_explosion_variant(BASE_OBJECT(arg0), 2);
        arg0->unk16 = 1;
        arg0->animation_step.fields.frame_index = 2;
        start_screen_shake_y(0xA, 4, 2);
        func_8001540C(5, 1, arg0);
        arg0->bg_offset = 0;
    } else {
        arg0->unk16 = 6;
        arg0->animation_step.fields.frame_index = 1;
        arg0->bg_offset = 0;
    }
    arg0->unk15 = 0;
    arg0->x_vel.val = 0;

    count = owner->unk7C;
    if (count >= 0x15) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    owner->unk7C = count + 1;
    update_on_screen(BASE_OBJECT(arg0), 0x38, 0x20);
}

void func_800C0864(struct ItemObj* arg0)
{
    const u16* layout = (const u16*)&destructible_core_data;
    s32 slot = arg0->unk2;

    if (engine_obj.checkpoint >= 2 && slot == 0) {
        apply_tile_effect(destructible_core_data.object_ids[slot * 0x10], 0, 0);
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    arg0->state = 0;
    arg0->unk5 = 1;
    arg0->active = 1;
    arg0->state = (u8)arg0->state + 1;
    arg0->animation_table = (const u8* const*)dragon_rubble_animations;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk42 = 0x78C0;
    arg0->unk40 = (u16)((u32)D_801406A8[6] >> 7);
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 6);
    arg0->x_pos.i.hi = layout[slot * 8];
    arg0->unk58 = (const u8*)D_80108504;
    arg0->y_pos.i.hi = layout[slot * 8 + 1];
    arg0->unk5C = slot != 0 ? 0x20 : 0x50;
    arg0->unk75 = 1;
    arg0->ext.packed = 5;
    arg0->unk61 = 0;
    arg0->unk68 = NULL;
    arg0->on_screen = 0;
    arg0->unk7C.timer = 0;
    arg0->tail_ext.unk1.unk88 = 0;
    arg0->unk54 = (const u8*)destructible_core_boxes[slot];
    arg0->tail_ext.unk1.unk84.previous_value = arg0->unk5C;
}

void func_800DADA0(struct TileEffectRecord* arg0, u16 arg1, u16 arg2, u8 arg3,
    u8 arg4)
{
    u32 x = arg1;
    u32 y = arg2;
    u16 tile = arg0->tiles[arg3];
    u8 block;

    block = (SP_BG_TILEMAP + arg0->layer * layout_size
        + layout_width * (y >> 4))[x >> 4];
    *(u16*)((u8*)SP_BG_TILE_PIXELS + (block << 9) + ((y & 0xF) << 5)
        + ((x & 0xF) * 2))
        = tile;

    if (arg4 != 0) {
        D_801441C8[arg0->layer][arg2 & 0x1F][arg1 & 0x1F] = tile;
    }
}

void func_800AF878(struct BaseObj* arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 x = arg2 & get_random();
    s16 y;
    u8 toggle;

    if (get_random() & 1) {
        x = arg0->x_pos.u.hi + (x & 0xFF);
    } else {
        x = arg0->x_pos.u.hi - (x & 0xFF);
    }

    y = arg3 & get_random();
    if (get_random() & 1) {
        y = arg0->y_pos.u.hi + (y & 0xFF);
    } else {
        y = arg0->y_pos.u.hi - (y & 0xFF);
    }

    toggle = D_8013B8E0[0] + 1;
    D_8013B8E0[0] = toggle;
    spawn_explosion_at((s8)arg1, (s16)x, y, (toggle & 1) ^ 1);
}

void func_800C8BDC(struct MiscObj* arg0)
{
    struct MainObj* owner = arg0->ext.misc_4.owner;
    s32 column;
    s32 wrapped;
    s32 row;
    s32 index;

    arg0->unk5 = 0x10;
    arg0->state = (u8)arg0->state + 1;
    arg0->animation_table = (u32**)dragon_rubble_animations;

    index = func_8002938C(0x85);
    row = func_8002938C(0x85);
    column = index * 4 + 0x18;
    wrapped = column < 0 ? index * 4 + 0x27 : column;
    row = row + 6 < 0 ? row + 9 : row + 6;
    arg0->unk42 = (u16)((column - ((wrapped >> 4) << 4))
        | (((row >> 2) + 0x1E0) << 6));
    arg0->unk40 = (u16)((u32)D_801406A8[func_8002938C(0x85)] >> 7);
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x85));

    arg0->x_pos.i.hi = dragon_rubble_c_positions[arg0->unk2].x;
    arg0->y_pos.i.hi = dragon_rubble_c_positions[arg0->unk2].y;
    arg0->x_vel.val = owner->unk15 != 0 ? -0x60000 : 0x60000;

    func_8001540C(5, 1, arg0);
    func_8001540C(5, 0, arg0);
    spawn_debris(8, dragon_rubble_c_debris_1, arg0);
    spawn_debris(8, dragon_rubble_c_debris_2, arg0);
    spawn_debris(8, dragon_rubble_c_debris_0, arg0);
    spawn_debris(8, dragon_rubble_c_debris_2, arg0);

    spawn_explosion_at(2, arg0->x_pos.i.hi + 0x10, arg0->y_pos.i.hi + 0x18, 0);
    spawn_explosion_at(2, arg0->x_pos.i.hi - 8, arg0->y_pos.i.hi + 6, 1);
    spawn_explosion_at(2, arg0->x_pos.i.hi, arg0->y_pos.i.hi - 0x1C, 0);
    spawn_explosion_at(2, arg0->x_pos.i.hi - 0x16, arg0->y_pos.i.hi - 0x20, 1);
    spawn_explosion_at(2, arg0->x_pos.i.hi + 6, arg0->y_pos.i.hi + 0x2C, 0);
    spawn_explosion_at(2, arg0->x_pos.i.hi - 0xC, arg0->y_pos.i.hi + 0x20, 1);
}

void func_800C8E90(struct MiscObj* arg0)
{
    s8 timer = arg0->unk5;

    arg0->unk5--;
    switch (timer) {
    case 0:
        ZeroObjectState(OBJECT_HEADER(arg0));
        break;
    case 1:
        spawn_explosion_at(2, arg0->x_pos.i.hi - 8, arg0->y_pos.i.hi + 6, 1);
        break;
    case 4:
        spawn_explosion_at(2, arg0->x_pos.i.hi - 0xC,
            arg0->y_pos.i.hi + 0x20, 1);
        break;
    case 8:
        spawn_explosion_at(2, arg0->x_pos.i.hi - 0x16,
            arg0->y_pos.i.hi - 0x20, 1);
        break;
    case 13:
        spawn_explosion_at(2, arg0->x_pos.i.hi + 6,
            arg0->y_pos.i.hi + 0x2C, 0);
        break;
    case 15:
        spawn_explosion_at(2, arg0->x_pos.i.hi, arg0->y_pos.i.hi - 0x1C, 0);
        break;
    }
}

void func_800B5798(struct EffectObj* arg0)
{
    const u16* trigger = arg0->ext.unk_effect.unk18;
    u32 i;

    if (func_8002B160(BASE_OBJECT(arg0)) != 0) {
        despawn_object(OBJECT_HEADER(arg0));
        return;
    }

    if (trigger[0] < g_Player.x_pos.i.hi
        || g_Player.x_pos.i.hi < trigger[1]
        || trigger[2] < g_Player.y_pos.i.hi
        || g_Player.y_pos.i.hi < trigger[3]) {
        return;
    }

    background_objects[0].unk47 = 2;
    for (i = 4; trigger[i] != 0; i++) {
        const struct Effect00BackgroundUpdate* update
            = &camera_trigger_bound_values[trigger[i] - 1];
        *camera_trigger_bound_fields[update->object_index] = update->value;
    }
}

void func_80042A48(struct MainObj* arg0)
{
    arg0->unk5 = 0;
    arg0->unk2 = 0;
    arg0->state = (u8)arg0->state + 1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)item_carrier_animations;
    arg0->unk16 = 4;
    arg0->hp = 1;
    arg0->contact_damage = 1;
    arg0->attack_box = NULL;
    arg0->terrain_box = NULL;
    arg0->collision_data = (const u16*)D_801063F0;
    arg0->air_state = 0;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    arg0->unk15 = (g_Player.x_pos.val >= arg0->x_pos.val) << 6;
    set_animation(arg0, 0);
}

void func_80042AFC(struct MainObj* arg0)
{
    struct ItemObj* item;
    s32 i;

    if (arg0->unk2 == 0) {
        for (i = 0; i < 2; i++) {
            arg0->hurt_box = (const u8*)item_carrier_part_hurtboxes[i];
            if (func_8002DD04(arg0) < 0) {
                spawn_explosion(BASE_OBJECT(arg0));
                spawn_debris(item_carrier_part_debris_counts[i], item_carrier_part_debris[i], arg0);
                if (i == 0) {
                    arg0->unk2 = 2;
                    arg0->unk5 = 2;
                    arg0->unk6 = 0;
                    arg0->hp = 1;
                    break;
                }
                goto spawn_item;
            }
        }
    } else if (func_8002DD04(arg0) < 0) {
        spawn_explosion(BASE_OBJECT(arg0));
        spawn_debris(3, item_carrier_capsule_debris, arg0);
    spawn_item:
        item = find_free_item_obj();
        if (item != NULL) {
            item->active = 0x21;
            item->id = 2;
            item->unk2 = (u8)arg0->ext.main_10.timer;
            item->x_pos.val = arg0->x_pos.val;
            item->y_pos.val = arg0->y_pos.val;
            item->backref = NULL;
            item->bg_offset = arg0->bg_offset;
        }
        arg0->state = (u8)arg0->state + 1;
        return;
    }

    item_carrier_action_funcs[arg0->unk5](arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
        return;
    }
    arg0->state = (u8)arg0->state + 1;
}

void func_80046B80(struct MainObj* arg0)
{
    arg0->hp = 0x7F;
    arg0->contact_damage = 4;
    arg0->unk7C = 0;
    arg0->invincibility_timer = 0;
    arg0->collision_data = (const u16*)D_801065F0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
    arg0->animation_table = (const u8* const*)D_800FA4E8;
    arg0->unk16 = 6;
    arg0->terrain_box = &bulldozer_terrain_box;
    arg0->hurt_box = (const u8*)bulldozer_hurt_boxes;
    arg0->attack_box = (const u8*)bulldozer_hurt_boxes;
    arg0->ext.main_6.armor_broken = 0;
    arg0->ext.main_6.ground_probe_distance = 0;
    arg0->ext.main_6.armor_health = 0x12;
    arg0->ext.main_6.core_health = 9;
    arg0->ext.main_6.hitbox_toggle = 0;
    arg0->air_state = 0;
    set_animation(arg0, 0);
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
}

void func_80046C8C(struct MainObj* arg0)
{
    s32 facing_offset;

    bulldozer_check_fall(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    bulldozer_step_funcs[arg0->unk5](arg0);

    arg0->hp = 0x7F;
    arg0->ext.main_6.hitbox_toggle ^= 1;
    if (arg0->ext.main_6.hitbox_toggle != 0) {
        arg0->hurt_box += 4;
        arg0->attack_box += 4;
    } else {
        arg0->hurt_box -= 4;
        arg0->attack_box -= 4;
    }
    func_8002D9BC(arg0);
    arg0->ext.main_6.saved_step = arg0->unk5;

    if (func_8002DD04(arg0) != 0) {
        if (arg0->ext.main_6.armor_broken == 0
            && arg0->ext.main_6.hitbox_toggle == 0) {
            arg0->ext.main_6.armor_health
                += arg0->hp - 0x7F;
        } else {
            arg0->ext.main_6.core_health += arg0->hp - 0x7F;
        }

        if ((s32)arg0->ext.main_6.core_health < 0) {
            if (arg0->ext.main_6.armor_broken == 0) {
                facing_offset = arg0->unk15 != 0 ? -0x24 : 0x24;
                spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi, 1);
                spawn_explosion(BASE_OBJECT(arg0));
                facing_offset = arg0->unk15 != 0 ? 0x20 : -0x20;
                spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi, 1);
                facing_offset = arg0->unk15 != 0 ? 0x18 : -0x18;
                spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi - 0x1B, 1);
                spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi - 0x37, 1);
                spawn_debris(0xF, bulldozer_debris, arg0);
            } else {
                spawn_explosion(BASE_OBJECT(arg0));
                facing_offset = arg0->unk15 != 0 ? -0x24 : 0x24;
                spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi, 1);
                spawn_debris(8, bulldozer_debris + 7, arg0);
            }
            drop_item(BASE_OBJECT(arg0), 0x13);
            arg0->state = 2;
            return;
        }

        if (arg0->ext.main_6.armor_broken == 0
            && (s32)arg0->ext.main_6.armor_health < 0) {
            facing_offset = arg0->unk15 != 0 ? 0x20 : -0x20;
            spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                arg0->y_pos.i.hi, 1);
            facing_offset = arg0->unk15 != 0 ? 0x18 : -0x18;
            spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                arg0->y_pos.i.hi - 0x1B, 1);
            spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                arg0->y_pos.i.hi - 0x37, 1);
            spawn_debris(7, bulldozer_debris, arg0);
            set_animation(arg0, 1);
            arg0->contact_damage = 3;
            arg0->terrain_box = &D_800FA430;
            arg0->hurt_box = (const u8*)D_800FA434;
            arg0->attack_box = (const u8*)D_800FA434;
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->ext.main_6.armor_broken = 1;
        }
    }

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x68, 0x68) != 0) {
        arg0->state = 2;
    } else {
        update_on_screen(BASE_OBJECT(arg0), 0x48, 0x48);
    }
}

void func_80035C20(struct PlayerObj* arg0)
{
    s32 i;

    if ((arg0->death_timer & 3) == 0) {
        for (i = 0; i < 4; i++) {
            player_spawn_death_orb((get_random() & 0x1F) | -0x80);
        }
    }

    if (arg0->unkC6 == 3) {
        arg0->death_timer = 0x14;
        arg0->unk5 = (u8)arg0->unk5 + 1;
    } else if (arg0->death_timer == 0) {
        player_spawn_death_orbs(arg0->unkC6);
        if (arg0->unkC6 == 2) {
            player_spawn_death_orbs(3);
        }
        arg0->death_timer = 0x12;
        arg0->unkC6++;
    } else {
        arg0->death_timer--;
    }
}

void func_800CAE38(struct MiscObj* arg0)
{
    u8 variant = (u8)arg0->unk2;
    s32 animation;

    arg0->on_screen = 1;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk38 = NULL;
    arg0->animation_table = D_8011BF40;
    arg0->unk42 = 0x7802;
    arg0->unk40 = 0;
    arg0->unk16 = 0x10;
    arg0->unk15 = 0;
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->y_pos.val = g_Player.y_pos.val;

    set_velocity_from_angle(MOVING_OBJECT(arg0), variant & 0x7F);
    if (variant & 0x80) {
        arg0->x_vel.val *= 8;
        arg0->y_vel.val *= 8;
        animation = 7;
    } else {
        arg0->x_vel.val += (arg0->x_vel.val / 2) * death_orb_frames[variant & 3];
        arg0->y_vel.val += (arg0->y_vel.val / 2) * death_orb_frames[variant & 3];
        animation = 6;
    }

    set_animation(arg0, animation);
    move_object(MOVING_OBJECT(arg0));
    arg0->state = (u8)arg0->state + 1;
    update_on_screen(BASE_OBJECT(arg0), 0x80000, 0x80000);
}

void func_800200D4(struct EngineObj* arg0)
{
    s32 i;

    if (arg0->unkF > 0) {
        arg0->unk1E = 0;
        if (arg0->stage > 0 && arg0->stage < 9) {
            if (arg0->substage != 0) {
                arg0->state
                    = (((u8)arg0->palette_flags >> (arg0->stage - 1)) & 1)
                    ? 9
                    : 7;
            } else {
                arg0->substage++;
                arg0->state = 4;
            }
        } else if (arg0->substage == 0
            && (arg0->stage >= 0xB || arg0->stage == 0)) {
            arg0->substage = 1;
            arg0->state = 4;
        } else if (*(u16*)&arg0->stage == 0x10C) {
            arg0->state = 0xB;
        } else {
            arg0->state = 9;
            switch (arg0->stage) {
            case 0:
                arg0->unk5F = 2;
                break;
            case 9:
                arg0->unk5F = 4;
                break;
            case 0xA:
                arg0->unk5F = 7;
                break;
            case 0xB:
                arg0->unk5F = 0xA;
                break;
            }
        }
    } else if (arg0->unkF < 0) {
        arg0->unk1E = -1;
        func_8002B560(2, 0xE);
        arg0->unk45 = g_Player.hp;
        for (i = 0; i < 0x10; i++) {
            arg0->player_initial_data[i] = g_Player.weapon_energy[i];
        }
        arg0->unk60 = g_Player.weapon;
        if (arg0->stage != 0xC
            || (*(u16*)&arg0->stage == 0xC && arg0->checkpoint == 0xA)) {
            arg0->unk42 = 1;
        }
        arg0->state = 5;
    } else {
        arg0->unk44--;
        if (arg0->unk44 < 0) {
            arg0->state = 8;
            if (*(u16*)&arg0->stage == 0xC) {
                for (i = 0; i < 0x10; i++) {
                    arg0->character_state.bytes[i] = 0;
                }
            }
        } else {
            arg0->unk1E = 0;
            if (func_8001FD7C(arg0) != 0) {
                arg0->checkpoint = 1;
            }
            if (*(u16*)&arg0->stage == 0x10C && D_80171EA8 != 0) {
                arg0->state = 4;
            } else {
                arg0->state = 5;
            }
        }
    }

    arg0->unk1 = 0;
    arg0->unkF = 0;
}

void func_800BFBD0(struct ItemObj* arg0)
{
    u8 health;
    u8 status;

    if (arg0->unk6 == 0) {
        arg0->ext.item_2.unk81--;
        if (arg0->ext.item_2.unk81 != 0) {
            return;
        }

        arg0->ext.item_2.unk81 = 2;
        health = g_Player.hp;
        status = health & 0x80;
        if ((health & 0x7F) >= engine_obj.unk46) {
            arg0->unk6 = 1;
            g_Player.hp = (u8)engine_obj.unk46 | status;
        } else {
            g_Player.hp = (health + 1) | status;
        }
        func_8001540C(0, 0xD, NULL);

        arg0->ext.item_2.unk80--;
        if (arg0->ext.item_2.unk80 == 0) {
            arg0->unk6 = 1;
        }
    } else {
        set_objects_frozen(0);
        arg0->state = 3;
        arg0->unk5 = 0;
        arg0->active &= 0xF7;
    }
}

void func_800BBC50(struct EffectObj* arg0)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8013E188[i] = -1;
    }
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    arg0->ext.effect_28.timer = 0x28;
    arg0->ext.effect_28.filter_timer = 4;
    arg0->ext.effect_28.pad1A = 3;
    arg0->ext.effect_28.palette_index = 0;
    func_8002B560(2, 1);
    arg0->state++;
    start_screen_shake_y(0x28, 4, 2);
    arg0->unk7 = 0x27;
}

void func_8002B560(s8 id, s8 subtype)
{
    s32 i;

    for (i = 0; i < 0x20; i++) {
        struct EffectObj* effect = &effect_objects[i];

        if (!effect->active)
            continue;
        if (id >= 0) {
            if (effect->id == id && effect->unk2 == subtype)
                ZeroObjectState(OBJECT_HEADER(effect));
        } else if (effect->id == (id & 0x7F)) {
            ZeroObjectState(OBJECT_HEADER(effect));
        }
    }
}

void func_800BBD88(struct EffectObj* arg0)
{
    if (arg0->ext.effect_28.finished) {
        fortress_collapse_flash_funcs[arg0->ext.effect_28.palette_index](arg0);
    } else if (--arg0->ext.effect_28.timer == 0) {
        arg0->ext.effect_28.finished = 1;
    }

    arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0xA0;
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi + 0x80;
    if (--arg0->ext.effect_28.pad1A == 0) {
        fortress_collapse_spawn_random_explosion(arg0);
        arg0->ext.effect_28.pad1A = 3;
    }
    if (arg0->unk7 == 0) {
        start_screen_shake_y(10, 4, 2);
        arg0->unk7 = 10;
    }
    arg0->unk7--;
}

void func_8002E294(struct PlayerObj* arg0, struct PlayerObj* arg1)
{
    s16 x_overlap;
    s16 y_overlap;

    if (arg1->unk68 == NULL || !func_8002C160(COLLISION_OBJECT(arg0), COLLISION_OBJECT(arg1)))
        return;
    func_8002C26C(COLLISION_OBJECT(arg0), COLLISION_OBJECT(arg1));
    func_8002C2EC(COLLISION_OBJECT(arg0), COLLISION_OBJECT(arg1));
    x_overlap = arg1->unk6C < 0 ? -arg1->unk6C : arg1->unk6C;
    y_overlap = arg1->unk6E < 0 ? -arg1->unk6E : arg1->unk6E;
    if ((arg0->unk66 == 0 && x_overlap < y_overlap) || arg0->unk66 > 0)
        arg1->x_pos.i.hi += arg1->unk6C;
    else
        arg1->y_pos.i.hi += arg1->unk6E;
}

void func_8002C36C(struct PlayerObj* arg0, struct PlayerObj* arg1, s32 slot)
{
    struct Unk_unk68* bounds0 = arg0->unk68;
    struct Unk_unk68* bounds1 = arg1->unk68;
    if (bounds0 == NULL || bounds1 == NULL) {
        if (slot == 0) {
            arg0->unk72 = 0;
            arg0->unk76 = 0;
        } else if (slot == 1) {
            arg0->unk73 = 0;
            arg0->unk77 = 0;
        } else if (slot == 2) {
            arg0->unk74 = 0;
            arg0->unk78 = 0;
        }
        return;
    }
    s16 x0 = arg0->x_pos.i.hi + bounds0->unk0;
    s16 y0 = arg0->y_pos.i.hi + bounds0->unk1;
    s16 x1 = arg1->x_pos.i.hi + bounds1->unk0;
    s16 y1 = arg1->y_pos.i.hi + bounds1->unk1;
    s16 dx = x0 >= x1 ? x0 - x1 : x1 - x0;
    s16 dy = y0 >= y1 ? y0 - y1 : y1 - y0;
    u8 flags = 0;

    if (dy == bounds0->unk3 + bounds1->unk3 && dx < bounds0->unk2 + bounds1->unk2) {
        flags |= y0 < y1 ? 4 : 8;
    }
    if (dx == bounds0->unk2 + bounds1->unk2 && dy < bounds0->unk3 + bounds1->unk3) {
        flags |= x0 < x1 ? 2 : 1;
        arg1->wall_climbable = arg0->unk75;
    }

    if (slot == 0)
        arg0->unk72 = flags;
    else if (slot == 1)
        arg0->unk73 = flags;
    else if (slot == 2)
        arg0->unk74 = flags;
    arg1->unk71 |= flags;

    if (slot == 0)
        arg0->unk76 = (flags & 0xB) != 0;
    else if (slot == 1)
        arg0->unk77 = (flags & 0xB) != 0;
    else if (slot == 2)
        arg0->unk78 = (flags & 0xB) != 0;
}

s8 func_800C1E7C(struct ItemObj* arg0)
{
    struct Unk_unk68* item_bounds;
    struct Unk_unk68* player_bounds;
    s16 item_x;
    s16 player_x;
    s16 dx;

    if (g_Player.hurt_phase != 0 || g_Player.unk5 == 3 || g_Player.unk5 == 0xB)
        return 0;
    if (g_Player.unk2 != 0 && g_Player.attacking != 0)
        return 0;
    if (g_Player.spike_immune != 0 || arg0->x_pos.i.hi < g_Player.x_pos.i.hi)
        return 0;

    item_bounds = arg0->unk68;
    player_bounds = g_Player.unk68;
    if (item_bounds == NULL || player_bounds == NULL)
        return 0;
    item_x = arg0->x_pos.i.hi + item_bounds->unk0;
    player_x = g_Player.x_pos.i.hi + player_bounds->unk0;
    dx = item_x >= player_x ? item_x - player_x : player_x - item_x;
    if (dx > item_bounds->unk2 + player_bounds->unk2)
        return 0;
    if (g_Player.y_pos.i.hi - player_bounds->unk3 < arg0->y_pos.i.hi - item_bounds->unk3)
        return 0;
    return arg0->y_pos.i.hi + item_bounds->unk3 >= g_Player.y_pos.i.hi + player_bounds->unk3;
}

void func_80032FA4(struct PlayerObj* arg0)
{
    if (arg0->capsule_state == 0) {
        if (arg0->unk88.unsigned_bytes.collision_flags & 8) {
            player_enter_stand(arg0);
            arg0->dash_momentum = 0;
        } else {
            player_set_animation(arg0, 0xB);
            arg0->unk2C = 0x4200;
            arg0->x_vel.val = 0;
            arg0->unk28 = 0;
            arg0->y_vel.val = 0;
            arg0->air_state = -1;
            arg0->unk6++;
            arg0->dash_momentum = 0;
        }
        arg0->air_action = 0;
    } else if (arg0->air_state == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
    }
}

void func_800C1C88(struct ItemObj* arg0, struct EngineObj* arg1,
    struct PlayerObj* arg2)
{
    static const s16 offsets[7] = { 0, 0x30, 0xA0, 0, 0x50, 0xB0, 0x5A0 };
    (void)arg2;

    if (arg0->animation_step.fields.event < 2) {
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event == 1) {
            func_8001540C(0, 0x11, arg0);
            arg0->animation_step.fields.event = 0;
        }
        return;
    }

    arg1->unk10 = 0;
    arg1->unk12 = 0;
    if ((u8)arg0->unk2 < COUNT(offsets))
        background_objects[0].unk24 = arg0->x_pos.i.hi + offsets[(u8)arg0->unk2];
    background_objects[0].unk26 = arg0->x_pos.i.hi;
    arg0->unk5 = 3;
}

s32 func_80034E2C(void)
{
    struct PlayerObj* player = &g_Player;

    player->unk6 = 0;
    player->unk5 = player->script_action;
    player_clear_dash_and_attack(player);
    switch ((u8)(player->unk5 - 0x14)) {
    case 0:
        if ((u8)(player->unk17 - 5) >= 2)
            player_set_idle_animation(player);
        player->script_state = -1;
        player->unk15 = player->script_facing;
        break;
    case 1:
        player_set_animation(player, 0x26);
        player->y_vel.val = 0;
        player->unk28 = 0;
        player->unk2C = 0;
        if (player->script_facing == 0) {
            player_script_walk_to_mark(player);
            break;
        }
        player->unk15 = 0x40;
        break;
    case 2:
        player_set_animation(player, 3);
        player->script_state = -1;
        player->unk15 = player->script_facing;
        break;
    case 3:
        player_set_animation(player, 0xA);
        player_set_collision_bounds(player);
        player->y_vel.val = 0x5D000;
        player->unk2C = 0x4200;
        player->x_vel.val = 0;
        player->unk28 = 0;
        player->air_state = 1;
        player->unk15 = player->script_facing;
        break;
    case 4:
        player_set_animation(player, 0x6B);
        player_reset_weapon(player);
        player->unk15 = player->script_facing;
        break;
    }
    return 0;
}

void func_80033108(struct PlayerObj* arg0)
{
    if (engine_obj.unkF != 0) {
        player_start_stage_clear(arg0);
        return;
    }
    arg0->x_vel.val = arg0->animation_step.fields.event == 0 ? 0x8000 : 0x20000;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -arg0->x_vel.val;
    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->script_facing == 0)
        player_script_walk_to_mark(arg0);
}

void func_800AFF78(struct VisualObj* arg0)
{
    struct PlayerObj* owner = arg0->unk50;
    u8 frame;
    s8 x_offset;
    s8 y_offset;

    arg0->x_pos.val = owner->x_pos.val;
    arg0->y_pos.val = owner->y_pos.val;
    arg0->on_screen = 0;
    arg0->unk15 = owner->unk15;

    switch (arg0->unk2) {
    case 0:
        frame = owner->animation_step.fields.frame_index;
        if (owner->unk15 == 0)
            arg0->x_pos.i.hi += (u8)eregion_part_offsets_center[frame][0];
        else
            arg0->x_pos.i.hi -= (u8)eregion_part_offsets_center[frame][0];
        arg0->y_pos.i.hi -= eregion_part_offsets_center[frame][1];
        arg0->unk42 = owner->unk42;
        eregion_part_funcs[arg0->state](arg0);
        return;

    case 1:
        arg0->x_pos.val += owner->unk15 == 0 ? -FIXED(75) : FIXED(75);
        arg0->y_pos.val += FIXED(2);
        arg0->unk42 = owner->unk42;
        break;

    case 3:
        frame = owner->animation_step.fields.frame_index;
        x_offset = eregion_part_offsets_left[frame][0];
        y_offset = eregion_part_offsets_left[frame][1];
        if (owner->unk15 == 0)
            arg0->x_pos.i.hi += x_offset;
        else
            arg0->x_pos.i.hi -= x_offset;
        arg0->y_pos.i.hi += y_offset;
        arg0->unk42 = (arg0->unk42 & 0x7FFF) | (owner->unk42 & 0x8000);
        eregion_part_funcs[arg0->state](arg0);
        return;

    case 4:
        frame = owner->animation_step.fields.frame_index;
        x_offset = eregion_part_offsets_right[frame][0];
        y_offset = eregion_part_offsets_right[frame][1];
        if (owner->unk15 == 0)
            arg0->x_pos.i.hi += x_offset;
        else
            arg0->x_pos.i.hi -= x_offset;
        arg0->y_pos.i.hi += y_offset;
        arg0->unk42 = (arg0->unk42 & 0x7FFF) | (owner->unk42 & 0x8000);
        eregion_part_funcs[arg0->state](arg0);
        return;

    case 5:
        arg0->unk42 = (arg0->unk42 & 0x7FFF) | (owner->unk42 & 0x8000);
        eregion_part_funcs[arg0->state](arg0);
        return;
    }

    if (owner->state == 1)
        eregion_part_funcs[arg0->state](arg0);
    else
        ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800B0320(struct VisualObj* arg0)
{
    struct PlayerObj* owner = arg0->unk50;
    s32 animation;

    if (arg0->unk2 == 3 || arg0->unk2 == 4) {
        s32 column;
        s32 row;
        s32 resource;

        arg0->animation_table = (u32**)D_800FADD0;
        column = (func_8002938C(9) << 2) + 0x18;
        row = func_8002938C(9);
        arg0->unk42 = (u16)((column - ((column >> 4) << 4))
            | ((((row + 6) >> 2) + 0x1E0) << 6));
        arg0->unk40 = (u16)((D_801406A8[1] >> 7) + 0xB0);
        resource = func_8002938C(9);
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
    } else {
        arg0->unk3C = owner->unk3C;
        arg0->unk40 = owner->unk40;
        arg0->animation_table = owner->animation_table;
        arg0->unk42 = owner->unk42 & 0x7FFF;
    }

    arg0->bg_offset = 0;
    arg0->unk15 = owner->unk15;
    switch (arg0->unk2) {
    case 0:
        arg0->unk16 = 7;
        arg0->state++;
        animation = owner->unk17 + 1;
        break;
    case 1:
        arg0->unk16 = 7;
        animation = 0x15;
        break;
    case 2:
        arg0->unk16 = 5;
        animation = 0x16;
        break;
    case 3:
        animation = owner->unk17;
        arg0->unk16 = 7;
        arg0->unk54 = 0;
        arg0->state += 2;
        break;
    case 4:
        arg0->state += 2;
        animation = owner->unk17 + 1;
        break;
    case 5:
        animation = 0x17;
        arg0->unk16 = 4;
        arg0->state += 3;
        break;
    default:
        return;
    }

    set_animation(ANIMATED_OBJECT(arg0), animation);
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_80047E58(struct MainObj* arg0)
{
    s32 collision;
    u8 frame;

    arg0->hurt_box = engine_obj.cur_character == 0
        ? (const void*)&D_800FA740
        : (const void*)&D_800FA744;
    arg0->collision_data = (const u16*)D_801060F0;
    arg0->unk65 = arg0->ext.main_8.unk8B;
    func_8002DD04(arg0);

    arg0->collision_data = (const u16*)D_801066F0;
    frame = arg0->animation_step.fields.frame_index;
    if (frame >= 0x16 && frame < 0x18)
        arg0->hurt_box = (const void*)&D_800FA73C;
    else if (frame >= 0x1F && frame < 0x21)
        arg0->hurt_box = (const void*)&D_800FA738;
    else
        arg0->hurt_box = (const void*)&D_800FA728;

    arg0->ext.main_8.unk8B = arg0->unk65;
    arg0->unk65 = arg0->ext.main_8.unk8C;
    collision = func_8002DD04(arg0);
    if (collision < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
        g_Player.spike_immune = 1;
        return;
    }
    if (collision > 0) {
        func_8001540C(2, 0x21, arg0);
        arg0->invincibility_timer = 0x1E;
        if (arg0->unk7C != 0) {
            arg0->state = 3;
            arg0->unk5 = 0;
            arg0->unk6 = 0;
            arg0->unk42 |= 0x8000;
        }
    }

    arg0->ext.main_8.unk8C = arg0->unk65;
    eregion_step_funcs[arg0->unk5](arg0);

    if (arg0->invincibility_timer != 0) {
        s8 timer = arg0->invincibility_timer--;
        if (timer & 2)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (arg0->invincibility_timer == 0)
            arg0->unk42 &= 0x7FFF;
    }

    func_8002D9BC(arg0);
    if (arg0->ext.main_8.unk88 != 0) {
        arg0->attack_box = arg0->ext.main_8.unk80;
        func_8002D9BC(arg0);
        arg0->attack_box = arg0->ext.main_8.unk84;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_800BABA8(struct EffectObj* arg0)
{
    struct EffectObj* spawned;
    s32 stage = engine_obj.stage;

    if (stage >= 1 && stage <= 8
        && ((engine_obj.palette_flags >> (stage - 1)) & 1) != 0) {
        engine_obj.unkF = 1;
        return;
    }

    spawned = find_free_effect_obj();
    if (spawned != NULL) {
        spawned->active = 1;
        spawned->id = 4;
        arg0->ext.effect_24.spawned_effect = spawned;
    }
    arg0->ext.effect_24.timer = 0;
    arg0->ext.effect_24.unk1A = 5;
    arg0->ext.effect_24.unk1B = 0;
    arg0->state++;
}

void func_800BAC58(struct EffectObj* arg0)
{
    struct QuadObj* quad;

    if (arg0->ext.effect_24.timer != 0) {
        arg0->ext.effect_24.timer--;
        return;
    }

    quad = find_free_quad_obj();
    if (quad == NULL)
        return;
    quad->active = -0x7D;
    quad->id = 3;
    quad->unk2 = arg0->ext.effect_24.unk1B;
    boss_warning_tiles[arg0->ext.effect_24.unk1B] = (struct EffectObj*)quad;
    arg0->ext.effect_24.timer = 2;
    arg0->ext.effect_24.unk1B++;
    if (arg0->ext.effect_24.unk1B == 0x16) {
        arg0->ext.effect_24.unk1B = 0;
        arg0->ext.effect_24.timer = 0xB4;
        arg0->unk5++;
    }
}

void func_8008D5C8(struct MainObj* arg0)
{
    extern void* sigma_final_animations[39];
    extern void* D_8013B8B4;
    s32 i;

    for (i = 0; i < 3; i++) {
        struct ShotObj* shot = find_free_shot_obj();

        if (shot == NULL)
            continue;
        shot->active = 0x41;
        shot->id = 0x35;
        shot->unk2 = i;
        shot->x_pos = arg0->x_pos;
        shot->y_pos = arg0->y_pos;
        shot->unk7C = (struct WeaponObj*)arg0;
        arg0->ext.main_74.children[i] = (struct MainObj*)shot;
    }

    arg0->unk15 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)sigma_final_animations;
    arg0->unk16 = 6;
    arg0->collision_data = D_801062F0;
    arg0->contact_damage = 9;
    arg0->invincibility_timer = 0;
    arg0->unk62 = 0;
    D_8013B8B0 = NULL;
    D_8013B8B4 = NULL;
    arg0->terrain_box = NULL;
    arg0->hp = 0;
    arg0->unk40 = (u16)((D_801406A8[0] >> 7) + 0xB0);
    engine_obj.boss_ptr = arg0;
    engine_obj.unk25 = 0;
    arg0->unk5 = 3;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->ext.main_74.target = 0;
    arg0->ext.main_74.upper_health = 0;
    arg0->ext.main_74.lower_health = 0x30;
    arg0->state++;
}

void func_800D4C50(struct QuadObj* arg0)
{
    u8 index = (u8)arg0->unk2;
    const u16* vertices = boss_warning_quad_motions[index].vertex;

    arg0->bg_offset = -1;
    arg0->unk34 = 4;
    arg0->unk36 = 0x10;
    arg0->on_screen = 1;
    arg0->x_pos.val = 0;
    arg0->y_pos.val = 0;
    arg0->ext.quad_2.x_scale.bytes.fraction = 0;
    arg0->state++;
    arg0->vertices[0].x.val = (s32)vertices[0] << 16;
    arg0->vertices[0].y.val = (s32)vertices[1] << 16;
    arg0->vertices[1].x.val = (s32)vertices[2] << 16;
    arg0->vertices[1].y.val = (s32)vertices[3] << 16;
    arg0->vertices[2].x.val = (s32)vertices[2] << 16;
    arg0->vertices[2].y.val = (s32)vertices[3] << 16;
    arg0->vertices[3].x.val = (s32)vertices[0] << 16;
    arg0->vertices[3].y.val = (s32)vertices[1] << 16;
    arg0->ext.quad_2.x_scale.bytes.integer = index == 0x15 ? 0xF : 2;
    arg0->ext.quad_2.y_scale.bytes.fraction = 0;
    if (index == 0)
        D_8013B960[0] = 0;
}

void func_800D5144(struct QuadObj* arg0)
{
    u8 index;

    boss_warning_quad_step_funcs[arg0->unk5](arg0);
    if (arg0->unk5 == 0 || D_8013B960[0] == 0
        || main_bss_state.frame_counter % 3 != 0) {
        return;
    }

    index = arg0->ext.quad_2.x_scale.bytes.fraction;
    arg0->unk34 = boss_warning_quad_blink_levels[index];
    index++;
    arg0->ext.quad_2.x_scale.bytes.fraction = index;
    if (index == 0xE)
        arg0->ext.quad_2.x_scale.bytes.fraction = 0;
}

static u8 pc_func_800D41EC(s32* x, s32* y, s32 target_x, s32 target_y,
    s32 x_speed, s32 y_speed)
{
    u8 direction = angle_from_delta(*x - target_x, *y - target_y);
    s32 table_index;
    s32 x_sign;
    s32 y_sign;

    if (direction < 8) {
        table_index = 8 - direction;
        x_sign = 1;
        y_sign = -1;
    } else if (direction < 0x10) {
        table_index = direction - 8;
        x_sign = -1;
        y_sign = -1;
    } else if (direction < 0x18) {
        table_index = 0x18 - direction;
        x_sign = -1;
        y_sign = 1;
    } else {
        table_index = direction - 0x18;
        x_sign = 1;
        y_sign = 1;
    }
    *x += (D_800F459C[table_index] * x_sign * x_speed) >> 4;
    *y += (D_800F45C0[table_index] * y_sign * y_speed) >> 4;
    return direction;
}

void func_800D4B30(struct QuadObj* arg0)
{
    u8 old_direction;
    u8 direction;
    s16 target_x = stage_select_flyout_targets[(u8)arg0->unk2][0];
    s16 target_y = stage_select_flyout_targets[(u8)arg0->unk2][1];

    arg0->ext.quad_2.x_scale.value += 0xC;
    old_direction = arg0->ext.quad_2.direction[0];
    arg0->ext.quad_2.direction[1] = old_direction;
    arg0->ext.quad_2.y_scale.value += 0xC;
    direction = pc_func_800D41EC(&arg0->x_pos.val, &arg0->y_pos.val,
        (s32)target_x << 16, (s32)target_y << 16, 0x28, 0x28);
    arg0->ext.quad_2.direction[1] = direction;
    if (((direction ^ old_direction) & 0x10) != 0) {
        arg0->x_pos.i.hi = target_x;
        arg0->y_pos.i.hi = target_y;
        arg0->state = 2;
        arg0->unk7 = 0x3C;
    }
    stage_select_flyout_scale(arg0);
    quad_is_on_screen(arg0);
}

void func_8007DD98(struct MainObj* arg0)
{
    if (engine_obj.stage == 0xC) {
        *(s16*)magma_dragoon_arena_right = 0x2B0;
        magma_dragoon_arena_center[0] = 0x200;
        *(s16*)magma_dragoon_arena_left = 0x150;
        magma_dragoon_arena_floor[0] = 0x690;
        magma_dragoon_arena_ceiling[0] = 0x670;
    } else {
        *(s16*)magma_dragoon_arena_right = 0x1590;
        magma_dragoon_arena_center[0] = 0x14E0;
        *(s16*)magma_dragoon_arena_left = 0x1430;
        magma_dragoon_arena_floor[0] = 0x280;
        magma_dragoon_arena_ceiling[0] = 0x260;
    }

    arg0->animation_table = (const u8* const*)magma_dragoon_animations;
    arg0->unk16 = 5;
    arg0->attack_box = &magma_dragoon_attack_box;
    arg0->invincibility_timer = 0;
    arg0->ext.main_65.flash_timer = 0;
    arg0->unk62 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->terrain_box = NULL;
    arg0->collision_data = D_80107D7C;
    arg0->hurt_box = NULL;
    arg0->unk40 = (u16)((D_801406A8[0] >> 7) + 0x160);

    if (engine_obj.stage == 0xC) {
        arg0->unk42 = 0x7888;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
        arg0->x_pos.i.hi = 0x2CE;
        arg0->y_pos.i.hi = 0x69F;
    } else {
        arg0->x_pos.i.hi = 0x15A5;
        arg0->y_pos.i.hi = 0x28F;
    }

    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    engine_obj.unk25 = 0;
    engine_obj.boss_ptr = arg0;
    arg0->contact_damage = 4;
    arg0->hp = 0;
    arg0->air_state = 0;
    arg0->unk5 = 2;
    arg0->state++;
    if (engine_obj.stage == 4)
        engine_obj.checkpoint = 3;
}

void func_8007F174(struct MainObj* arg0)
{
    s32 distance;

    if (arg0->ext.main_65.leap_frames != 0) {
        if (arg0->ext.main_65.leap_to_right != 0)
            distance = *(s16*)magma_dragoon_arena_right - (arg0->x_pos.i.hi + 0x30);
        else
            distance = (arg0->x_pos.i.hi - 0x30) - *(s16*)magma_dragoon_arena_left;
        if (distance < 0)
            distance = -distance;
        arg0->x_speed = (distance << 16)
            / arg0->ext.main_65.leap_frames;
        if (arg0->ext.main_65.leap_to_right == 0)
            arg0->x_speed = -arg0->x_speed;
        arg0->ext.main_65.leap_frames--;
    }

    move_with_gravity(ANIMATED_OBJECT(arg0));
    if ((arg0->collision_flags & 8) != 0 && arg0->y_speed < 0) {
        if (arg0->ext.main_65.leap_to_right != 0)
            arg0->x_pos.i.hi = *(s16*)magma_dragoon_arena_right - 0x30;
        else
            arg0->x_pos.i.hi = *(s16*)magma_dragoon_arena_left + 0x30;
        set_animation(arg0, 6);
        magma_dragoon_spawn_flames(ANIMATED_OBJECT(arg0), 2);
        arg0->air_state = 0;
        func_8001540C(2, 2, arg0);
        arg0->x_speed = 0;
        arg0->y_speed = 0;
        arg0->gravity = 0;
        arg0->unk6++;
    }
}

void func_8007FD24(struct MainObj* arg0)
{
    s32 hit = func_8002DD04(arg0);
    u8 flash;

    if (hit < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
        update_on_screen(BASE_OBJECT(arg0), 0x40, 0x40);
        return;
    }

    if (hit > 0 && hit != 0x7F) {
        arg0->ext.main_65.flash_timer = (hit == 0x19 || hit == 0x1A) ? 2 : 0x1E;
        arg0->collision_data = D_801060F0;
        if (hit == 8 || hit == 0x11) {
            arg0->unk5 = 0xD;
            arg0->unk6 = 0;
            arg0->ext.main_65.flash_timer = 0xFF;
        }
    }

    flash = arg0->ext.main_65.flash_timer;
    if (flash != 0) {
        arg0->ext.main_65.flash_timer--;
        if ((flash & 2) != 0)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (arg0->ext.main_65.flash_timer == 0) {
            arg0->collision_data = D_80107D7C;
            arg0->unk42 &= 0x7FFF;
        }
    }

    magma_dragoon_step_funcs[(u8)arg0->unk5](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    func_8002D9BC(arg0);
}

void func_8004970C(struct MainObj* arg0)
{
    if (arg0->unk7E != 0) {
        arg0->unk7E--;
        return;
    }

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        func_800B0CA0(0x21, 2, arg0, 0x18, 6);
        func_800B0CA0(0x22, 2, arg0, 0x18, 6);
        func_8001540C(2, 0x18, arg0);
        start_screen_shake_y(0xA, 4, 2);
        arg0->animation_step.fields.event = 0;
    }
    if (arg0->animation_step.fields.event < 0) {
        arg0->unk6++;
        engine_obj.enable_boss = 1;
        arg0->ext.main_9.animation_1 = (const u8*)&D_800FA734;
        arg0->unk7E = 3;
    }
}

void func_8004932C(struct MainObj* arg0)
{
    s32 x_pos = arg0->x_speed;
    u8 frame = arg0->animation_step.fields.frame_index;

    if (frame >= 0x1C && frame <= 0x1D) {
        x_pos += arg0->unk15 != 0 ? -0x16 : 0x16;
    }
    arg0->x_pos.i.hi = (s16)x_pos;
    arg0->unk42 &= 0x7FFF;
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->state = 1;
        if (arg0->unk7C != 0) {
            set_animation(ANIMATED_OBJECT(arg0), 0);
            arg0->unk5 = 1;
            arg0->unk7C = 1;
        } else {
            eregion_pick_start(arg0);
        }
        arg0->unk6 = 0;
        arg0->x_pos.i.hi = (s16)arg0->x_speed;
    }
}

void func_800480D0(struct MainObj* arg0)
{
    s32 distance;
    u16 timer;
    u8 choice;

    animate_object(ANIMATED_OBJECT(arg0));
    timer = (u16)arg0->unk7C;
    arg0->unk7C = (s16)(timer - 1);
    if (timer != 0)
        return;

    arg0->unk7C = 0;
    if (arg0->ext.main_8.unk8A++ >= 2) {
        arg0->ext.main_8.unk8A = 0;
        arg0->unk5 = arg0->hp < 0x19 ? 6 : 4;
        return;
    }

    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0)
        distance = -distance;
    if (arg0->hp >= 0x19) {
        if (distance < 0x90) {
            if (arg0->unk15 != 0) {
                choice = 0x12B0 - arg0->x_pos.i.hi < 0xD0 ? 4 : 5;
            } else {
                choice = arg0->x_pos.i.hi - 0x11A0 < 0xD0 ? 4 : 5;
            }
        } else {
            choice = get_random_nonzero() % 8 < 3 ? 3 : 8;
        }
    } else if (distance < 0x90) {
        choice = get_random_nonzero() % 8 < 6 ? 7 : 5;
    } else {
        choice = get_random_nonzero() % 8 < 7 ? 7 : 6;
    }
    arg0->unk5 = choice;

    if (arg0->unk15 != 0) {
        if (g_Player.x_pos.val < arg0->x_pos.val)
            arg0->unk5 = 4;
    } else if (g_Player.x_pos.val >= arg0->x_pos.val) {
        arg0->unk5 = 4;
    }
}

void func_80099F48(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;
    s32 target;
    s32 offset;
    s32 subtype = arg0->unk2;
    s32 angle;

    arg0->unk40 = owner->unk40;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->animation_table = owner->animation_table;
    arg0->unk3C = owner->unk3C;
    arg0->unk15 = owner->unk15;
    arg0->bg_offset = owner->bg_offset;
    arg0->x_pos.val = owner->x_pos.val
        + (owner->unk15 != 0 ? 0x530000 : -0x530000);
    arg0->y_pos.val = owner->y_pos.val;
    arg0->state = 1;
    arg0->on_screen = 1;

    if (subtype == 0) {
        angle = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
        set_velocity_from_angle(MOVING_OBJECT(arg0), angle & 0xFF);
        arg0->x_vel.val *= 4;
        arg0->y_vel.val *= 4;
    } else {
        offset = ((subtype - 1) * 11 << 17) - 0x200000;
        target = arg0->x_pos.val
            + (owner->unk15 != 0 ? offset : -offset);
        angle = angle_to_point(OBJECT_HEADER(arg0), target, 0x1E00000);
        set_velocity_from_angle(MOVING_OBJECT(arg0), angle & 0xFF);
        arg0->x_vel.val *= 8;
        arg0->y_vel.val *= 8;
    }

    arg0->unk68 = (struct Unk_unk68*)eregion_fireball_terrain_box;
    arg0->unk50.data = eregion_fireball_hit_box;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->unk16 = 0;
    arg0->unk54 = NULL;
    set_animation(ANIMATED_OBJECT(arg0), 0x17);
}

void func_8009A10C(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;
    s32 subtype = arg0->unk2;
    s32 offset;
    s32 target;
    s32 angle;

    func_8002D9BC(arg0);
    if (subtype != 0) {
        offset = ((subtype - 1) * 19 << 16) - 0x200000;
        target = arg0->x_pos.val
            + (owner->unk15 != 0 ? offset : -offset);
        angle = angle_to_point(OBJECT_HEADER(arg0), target, 0x1E00000);
        set_velocity_from_angle(MOVING_OBJECT(arg0), angle & 0xFF);
        arg0->x_vel.val *= 8;
        arg0->y_vel.val *= 8;
    }

    if (func_8002BB80(MAIN_OBJECT(arg0), MAIN_OBJECT(&g_Player)) != 0) {
        arg0->state = 2;
        return;
    }
    if ((arg0->unk70 & 8) != 0) {
        arg0->unk68 = NULL;
        arg0->state = 3;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x19, 0x19) != 0) {
        arg0->state = 2;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x19, 0x19);
}

void func_8009A448(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;

    arg0->unk40 = owner->unk40;
    arg0->animation_table = owner->animation_table;
    arg0->unk3C = owner->unk3C;
    arg0->unk15 = owner->unk15;
    arg0->unk16 = 5;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk60 = 5;
    arg0->state++;
    arg0->unk50.data = eregion_wing_slash_hit_box;
    arg0->unk5C = 0x7F;
    arg0->bg_offset = owner->bg_offset;
    set_animation(ANIMATED_OBJECT(arg0), 0x14);
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}

void func_80048B04(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));

    if (arg0->animation_step.fields.frame_index != 0xC) {
        if (arg0->unk15 != 0) {
            arg0->x_pos.u.hi = arg0->x_speed - 8;
        } else {
            arg0->x_pos.u.hi = arg0->x_speed + 8;
        }
    }

    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, 0x19, BASE_OBJECT(arg0));
        arg0->animation_step.fields.event = 0;
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->x_pos.u.hi = arg0->x_speed;
    }
}

void func_800BEBFC(struct ItemObj* arg0)
{
    u8 index = (u8)arg0->unk2;
    const struct Item01StageEntry* entry = &stage_block_entries[index];

    arg0->active = 1;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_pos.i.hi = entry->x;
    arg0->y_pos.i.hi = entry->y;
    arg0->animation_step.fields.frame_index = entry->flags_and_palette & 0x3F;
    arg0->y_vel.val = index == 9 ? 0x40000 : 0;
    arg0->unk2C = entry->velocity;
    arg0->unk40 = 0x1500;
    if (index == 8 || index == 9)
        arg0->unk42 = 0x7941;
    else if (index == 13)
        arg0->unk42 = 0x79C4;
    else
        arg0->unk42 = 0x7983;
    arg0->unk16 = 6;
    arg0->unk68 = (struct Unk_unk68*)&stage_block_bounds[index];
    arg0->unk5C = 0x10;
    arg0->unk61 = 0;
    arg0->unk75 = 1;
    arg0->unk54 = &stage_block_boxes[index * 4];
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 8);
    if (index == 1)
        arg0->unk66 = 1;
    arg0->unk58 = (const u8*)D_80108504;
    arg0->tail_ext.unk1.unk84.previous_value = 0;
    arg0->tail_ext.unk1.unk88 = 0;
}

void func_800BEFCC(struct ItemObj* arg0)
{
    u8 kind = (u8)arg0->unk2;
    const struct Item01StageEntry* entry = &stage_block_entries[kind];
    u16 boundary;
    int reached_boundary;

    if (--arg0->ext.timer == 0) {
        if (kind == 8) {
            func_800B10E4(0x21, 0xA40, 0x1D0, 0xB80, 0x1F0, 1);
            func_800B10E4(0x22, 0xA40, 0x1D0, 0xB80, 0x1F0, 1);
        } else if (kind == 9) {
            func_800B10E4(0x21, 0xB80, 0x1D0, 0xC40, 0x1F0, 1);
            func_800B10E4(0x22, 0xB80, 0x1D0, 0xC40, 0x1F0, 1);
        }
        arg0->ext.timer = 4;
    }

    if ((kind == 5 || kind == 8) && arg0->tail_ext.unk1.unk84.previous_value == 0) {
        if (kind == 5 && arg0->tail_ext.unk1.unk88 == 0 && arg0->y_pos.i.hi >= 0x1C0) {
            func_8001540C(5, 0, NULL);
            start_screen_shake_y(0x20, 4, 1);
            arg0->tail_ext.unk1.unk88++;
        }
        if (arg0->y_pos.i.hi >= entry->trigger_x && !(entry->flags_and_palette & 0x40)) {
            apply_tile_effect((u8)entry->sound_id, 0, 0);
            arg0->tail_ext.unk1.unk84.previous_value++;
        }
    }

    move_with_gravity(ANIMATED_OBJECT(arg0));
    boundary = entry->right;
    reached_boundary = kind == 9
        ? arg0->y_pos.i.hi <= boundary
        : arg0->y_pos.i.hi >= boundary;
    if (reached_boundary) {
        arg0->y_pos.i.hi = boundary;
        arg0->ext.timer = 0;
        arg0->unk5++;
    }
}

void func_800BF1FC(struct ItemObj* arg0)
{
    u8 kind = (u8)arg0->unk2;
    const struct Item01StageEntry* entry = &stage_block_entries[kind];
    int first;
    int last;
    int index;

    if (arg0->y_pos.i.hi == entry->trigger_x && !(entry->flags_and_palette & 0x40)) {
        apply_tile_effect((u8)entry->sound_id, 0, 0);
        if (kind != 3 && kind != 4)
            arg0->state = 3;
    }
    if (kind != 13 && kind != 5 && kind != 1 && kind != 11) {
        func_8001540C(5, 0, NULL);
        start_screen_shake_y(0x20, 4, 1);
    }
    arg0->unk5++;

    if ((kind >= 2 && kind <= 7) || kind == 11 || kind == 13) {
        func_800B0CA0(0x21, 2, (struct MainObj*)arg0, 0x18, 6);
        func_800B0CA0(0x22, 2, (struct MainObj*)arg0, 0x18, 6);
    }

    if (kind == 1) {
        first = 0;
        last = 1;
    } else if (kind == 10) {
        first = 1;
        last = 4;
    } else if (kind == 11) {
        first = 4;
        last = 6;
    } else {
        return;
    }

    for (index = first; index < last; index++) {
        struct MainObj* obj = find_free_main_obj();
        s32 resource;

        if (obj == NULL)
            continue;
        obj->active = 0x41;
        obj->id = 7;
        obj->unk2 = index == 3 ? 3 : 2;
        obj->x_pos.i.hi = stage_block_spawn_positions[index].x;
        obj->y_pos.i.hi = stage_block_spawn_positions[index].y;
        resource = func_8002938C(7);
        obj->unk40 = (u16)((u32)D_801406A8[(u8)resource] >> 7);
        resource = func_8002938C(7);
        obj->unk42 = SOME_COORDINATE_CONVERSION((u8)resource);
        resource = func_8002938C(7);
        obj->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES,
            (u8)resource);
    }
}

void func_80047404(struct MainObj* arg0)
{
    u8 kind = (u8)arg0->unk2;

    arg0->hp = 6;
    arg0->contact_damage = 3;
    arg0->invincibility_timer = 0;
    arg0->collision_data = D_80106670;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk16 = 6;
    arg0->animation_table = (const u8* const*)ambush_gunner_animations;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->terrain_box = NULL;
    arg0->attack_box = &ambush_gunner_terrain_box;
    arg0->hurt_box = &ambush_gunner_terrain_box;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    if (kind == 1) {
        set_animation(arg0, 1);
        arg0->unk5 = 3;
        arg0->unk15 = 0x40;
        arg0->ext.main_7.unk90 = 1;
    } else if (kind >= 2 && kind <= 7) {
        set_animation(arg0, 0);
        arg0->unk5 = 2;
        arg0->unk7A = 1;
        arg0->invincibility_timer = 1;
        arg0->unk15 = (kind & 1) ? 0x40 : 0;
        arg0->ext.main_7.unk80 = kind >= 6;
        arg0->ext.main_7.unk84 = kind >= 6 ? 0x28
            : kind >= 4                    ? 0x8C
                                           : 0x64;
        arg0->ext.main_7.unk90 = 0;
    } else {
        set_animation(arg0, 1);
        arg0->unk5 = 3;
        arg0->unk15 = 0;
        arg0->ext.main_7.unk90 = 1;
    }
    arg0->state = 1;
    arg0->unk6 = 0;
}

void func_80047818(struct MainObj* arg0)
{
    s32 distance;

    if (arg0->unk15 == 0) {
        if (g_Player.x_pos.val >= arg0->x_pos.val)
            return;
    } else if (arg0->x_pos.val >= g_Player.x_pos.val) {
        return;
    }
    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0)
        distance = -distance;
    if ((!arg0->ext.main_7.unk80 && distance < (s32)arg0->ext.main_7.unk84) || (arg0->ext.main_7.unk80 && distance > (s32)arg0->ext.main_7.unk84)) {
        arg0->unk7A = 0;
        arg0->unk6 = 1;
    }
}

void func_80047D04(struct MainObj* arg0)
{
    struct VisualObj* visual;

    arg0->ext.main_8.queued_sound = 0xFF;
    arg0->ext.main_8.unk8B = 0;
    arg0->ext.main_8.unk8C = 0;
    arg0->on_screen = 1;
    arg0->unk15 = 0;
    arg0->bg_offset = 0;
    arg0->air_state = 1;
    arg0->hp = 0;
    arg0->contact_damage = 3;
    arg0->invincibility_timer = 0;
    arg0->unk16 = 6;
    arg0->animation_table = (const u8* const*)D_800FAD68;
    arg0->terrain_box = (struct Unk_unk68*)&D_800FA724;
    arg0->collision_data = (const u16*)D_801066F0;
    arg0->hurt_box = (const u8*)&D_800FA728;
    arg0->attack_box = (const u8*)&D_800FA72C;
    arg0->ext.main_8.unk84 = &D_800FA72C;
    arg0->ext.main_8.unk88 = 1;
    arg0->ext.main_8.unk80 = 0;
    arg0->unk40 = (u16)((D_801406A8[0] >> 7) + 0xB0);
    engine_obj.unk25 = 2;
    engine_obj.boss_ptr = arg0;
    set_animation(arg0, 0);
    arg0->unk5 = 9;
    arg0->state++;

    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 6;
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->unk2 = 0;
    }
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 6;
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->unk2 = 5;
    }
    arg0->x_pos.val = FIXED(0xF60);
    arg0->y_pos.val = FIXED(0x170);
}

void func_80044F88(struct MainObj* arg0)
{
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk7C = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)robot_bee_animations;
    arg0->hurt_box = (const u8*)&D_800FA100;
    arg0->attack_box = (const u8*)&D_800FA104;
    arg0->collision_data = D_80106570;
    arg0->contact_damage = 3;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
    arg0->unk16 = 5;
    arg0->terrain_box = NULL;
    arg0->hp = 2;
    arg0->invincibility_timer = 0;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    if (arg0->unk2 == 1)
        arg0->unk5 = 5;
    else if (arg0->unk2 == 2)
        arg0->unk5 = 6;
    else if (arg0->unk2 == 3)
        arg0->unk5 = 8;
    else if (arg0->unk2 == 4)
        arg0->unk5 = 9;
    set_animation(arg0, 1);
}

void func_80099D54(struct ShotObj* arg0)
{
    u8 kind = (u8)arg0->unk2;

    arg0->unk58.animation_steps = D_80105FF0;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk42 &= 0x7FFF;
    arg0->x_pos.i.hi += gunner_shot_spawn_offsets[kind][0];
    arg0->x_vel.val *= 3;
    arg0->y_vel.val *= 3;
    arg0->unk54 = gunner_shot_hit_box;
    arg0->unk50.data = gunner_shot_hit_box;
    arg0->unk60 = 2;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk5C = 1;
    arg0->y_pos.i.hi += gunner_shot_spawn_offsets[kind][1];
    set_animation(arg0, 8);
}

void func_800B0CA0(s32 type, s32 mode, struct MainObj* source, s32 radius,
    s32 count)
{
    const struct Unk_unk68* bounds = source->terrain_box;
    s32 left = source->x_pos.i.hi;
    s32 right = left;
    s32 base_y = source->y_pos.i.hi + bounds->unk1;
    s32 top = base_y;
    s32 bottom = base_y;
    s32 width;
    s32 height;
    s32 i;

    switch ((u8)mode) {
    case 1:
    case 2:
        if (source->unk15 == 0) {
            left = source->x_pos.i.hi + bounds->unk0 - bounds->unk2;
            right = left + bounds->unk2 * 2;
        } else {
            right = source->x_pos.i.hi - bounds->unk0 + bounds->unk2;
            left = right - bounds->unk2 * 2;
        }
        if ((u8)mode == 1)
            top = bottom = base_y - bounds->unk3;
        else
            top = bottom = base_y + bounds->unk3;
        break;
    case 3:
        left = source->unk15 == 0
            ? source->x_pos.i.hi + bounds->unk0 - bounds->unk2
            : source->x_pos.i.hi - bounds->unk0 + bounds->unk2;
        right = left;
        top -= bounds->unk3;
        bottom += bounds->unk3;
        break;
    case 4:
        left = source->unk15 == 0
            ? source->x_pos.i.hi + bounds->unk0 + bounds->unk2
            : source->x_pos.i.hi - bounds->unk0 - bounds->unk2;
        right = left;
        top -= bounds->unk3;
        bottom += bounds->unk3;
        break;
    default:
        break;
    }
    left -= radius;
    top -= radius;
    right += radius;
    bottom += radius;
    width = (s16)(right - left);
    height = (s16)(bottom - top);

    for (i = 0; i < (s16)count; i++) {
        struct VisualObj* visual = find_free_visual_obj();
        u32 random_value;

        if (visual == NULL)
            continue;
        visual->active = 0x21;
        visual->id = 9;
        visual->unk2 = 0;
        random_value = ((get_random() & 0xFF) << 8) | (get_random() & 0xFF);
        visual->x_pos.i.hi = width == 0 ? left : left + (random_value + 1) % width;
        random_value = ((get_random() & 0xFF) << 8) | (get_random() & 0xFF);
        visual->y_pos.i.hi = height == 0 ? top : top + (random_value + 1) % height;
        visual->x_pos.u.lo = 0;
        visual->y_pos.u.lo = 0;
        if (((u8)type & 3) == 1) {
            visual->x_vel.val = 0;
            visual->y_vel.val = FIXED(1);
        } else if (((u8)type & 3) == 2) {
            visual->x_vel.val = visual->x_pos.i.hi < source->x_pos.i.hi
                ? FIXED(-1.5)
                : FIXED(1.5);
            visual->y_vel.val = 0;
        } else {
            visual->x_vel.val = 0;
            visual->y_vel.val = 0;
        }
        visual->unk15 = 0;
        visual->state = 0;
        visual->unk5 = 0;
        visual->unk6 = 0;
        visual->unk5C.value = (u8)type >> 4;
    }
}

void func_800349F4(struct PlayerObj* arg0)
{
    player_set_animation_shooting(arg0, 0xE);
    func_8001540C(1, 3, BASE_OBJECT(arg0));
    player_play_voice(arg0, 2);
    arg0->air_state = 1;
    if (arg0->input.buttons.held & 0x100) {
        arg0->dash_momentum = 1;
        arg0->air_action = 1;
        arg0->afterimage = 1;
    } else {
        player_clear_dash(arg0);
    }
    if (arg0->unk88.bytes.collision_flags & 1) {
        arg0->unk15 = 0x40;
        arg0->x_vel.val = arg0->dash_momentum != 0 ? FIXED(-4.125) : FIXED(-2);
    } else {
        arg0->unk15 = 0;
        arg0->x_vel.val = arg0->dash_momentum != 0 ? FIXED(4.125) : FIXED(2);
    }
    arg0->y_vel.val = FIXED(5.625);
    arg0->unk28 = 0;
    arg0->unk2C = 0x4200;
    arg0->unk8A.bytes.low = 10;
    player_spawn_wall_kick_spark(arg0);
    arg0->unk5 = 10;
    arg0->unk6 = 0;
}

void func_80034B64(struct PlayerObj* arg0)
{
    player_set_animation_shooting(arg0, 0xB);
    arg0->x_vel.val = (arg0->unk88.bytes.collision_flags & 1)
        ? FIXED(-2)
        : FIXED(2);
    arg0->unk2C = 0x4200;
    arg0->unk8A.bytes.low = 4;
    arg0->air_state = -1;
    arg0->unk5 = 0xB;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk6 = 1;
}

void func_800C044C(struct ItemObj* arg0)
{
    u8 index = (u8)arg0->unk2;
    const struct Item03StageEntry* entry = &falling_pillar_entries[index];

    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_pos.i.hi = entry->x;
    arg0->y_pos.i.hi = entry->y;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_step.fields.frame_index = entry->object_id;
    arg0->x_vel.val = index < 10 || index == 20 ? 0x4000 : -0x4000;
    arg0->unk40 = 0x1500;
    arg0->unk42 = 0x79C1;
    arg0->unk16 = 6;
    arg0->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 8);
    arg0->unk61 = 0;
    arg0->unk68 = index == 4 || index == 14
        ? (struct Unk_unk68*)falling_pillar_box
        : NULL;
    arg0->unk75 = 1;
    arg0->ext.packed = 0;
}

void func_800C7F1C(struct MiscObj* arg0)
{
    s32 index;

    arg0->on_screen = 1;
    arg0->animation_step.fields.frame_index = arg0->ext.unk.unk54;
    if (engine_obj.stage == 3) {
        index = func_8002938C(0x8A);
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
        index = func_8002938C(0x8A);
        arg0->unk40 = (u16)((u32)D_801406A8[index] >> 7);
        arg0->unk42 = 0x7987;
    } else {
        index = func_8002938C(0x83);
        arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
        index = func_8002938C(0x83);
        arg0->unk40 = (u16)((u32)D_801406A8[index] >> 7);
        if (arg0->unk2 == 0)
            arg0->unk42 = 0x7983;
        else
            arg0->unk42 = SOME_COORDINATE_CONVERSION(func_8002938C(0x83));
    }
    arg0->unk16 = 1;
    arg0->unk2C = 0x5000;
    arg0->x_vel.val += rubble_x_speeds[get_random() & 7];
    arg0->y_vel.val = rubble_y_speeds[get_random() & 7];
    arg0->state++;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800D0828(struct MiscObj* arg0)
{
    s32 resource;

    if (engine_obj.cur_character == 0 || engine_obj.character_state.bytes[8] != 0) {
        despawn_object_permanently(OBJECT_HEADER(arg0));
        return;
    }
    arg0->bg_offset = g_Player.bg_offset;
    arg0->y_vel.val = FIXED(10);
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0x2000;
    resource = func_8002938C(0x42);
    arg0->unk40 = (u16)((u32)D_801406A8[resource] >> 7);
    resource = func_8002938C(0x42);
    arg0->unk42 = SOME_COORDINATE_CONVERSION(resource);
    resource = func_8002938C(0x42);
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
    arg0->animation_table = (u32**)stage_cutscene_animations;
    arg0->unk16 = 6;
    arg0->unk15 = 0;
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->ext.unk.unk55 = 0;
    set_animation(arg0, 0);
}

void func_800BC784(struct EffectObj* arg0)
{
    struct Effect33Ext* ext = &arg0->ext.effect_33;

    switch (arg0->unk2 & 0xF0) {
    case 0x00:
        if (arg0->x_pos.i.hi < g_Player.x_pos.i.hi) {
            ext->timer = 1;
            ext->period = 0x50;
            arg0->state = 1;
        }
        return;
    case 0x10:
        ext->timer = 0x3C;
        ext->period = 0x26;
        ext->cooldown = 0x8C;
        ext->burst = 4;
        arg0->state = 1;
        arg0->unk5 = 0;
        ext->variant = arg0->unk2 & 0xF;
        return;
    case 0x20:
        switch (arg0->unk2 & 0xF) {
        case 0:
            ext->timer = 1;
            ext->period = 0x3C;
            ext->proximity = 0;
            ext->variant = 0;
            break;
        case 1:
            ext->timer = 1;
            ext->period = 0x50;
            ext->proximity = 0;
            ext->variant = 0;
            break;
        case 2:
            ext->timer = 1;
            ext->period = 0x64;
            ext->proximity = 0;
            ext->variant = 0;
            break;
        case 3:
            ext->timer = 0xB4;
            ext->period = 0xB4;
            ext->proximity = 1;
            ext->variant = 0;
            break;
        case 4:
            ext->timer = 1;
            ext->period = 0x78;
            ext->proximity = 0;
            ext->variant = 1;
            break;
        case 5:
            ext->timer = 1;
            ext->period = 0xB4;
            ext->proximity = 0;
            ext->variant = 1;
            break;
        case 6:
            ext->timer = 0x3C;
            ext->period = 0x3C;
            ext->proximity = 1;
            ext->variant = 0;
            break;
        case 7:
            ext->timer = 1;
            ext->period = 0x78;
            ext->proximity = 0;
            ext->variant = 2;
            break;
        case 8:
            ext->timer = 1;
            ext->period = 0xB4;
            ext->proximity = 0;
            ext->variant = 2;
            break;
        }
        arg0->state = 1;
        arg0->unk6 = 0;
        return;
    }
}

static void effect_33_spawn_dropper(struct EffectObj* arg0)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0x21;
    shot->unk2 = arg0->ext.effect_33.variant;
    shot->x_pos.i.hi = arg0->x_pos.i.hi;
    shot->state = 6;
    shot->unk84.effect = arg0;
    shot->unk6 = arg0->unk6;
    arg0->unk6 = 1;
}

void func_800BC92C(struct EffectObj* arg0)
{
    struct Effect33Ext* ext = &arg0->ext.effect_33;
    struct ShotObj* shot;
    s32 x;
    s32 player_x;
    s32 bg_x;
    s32 distance;

    switch (arg0->unk2 & 0xF0) {
    case 0x00:
        if (arg0->x_pos.i.hi + 0x3B0 < g_Player.x_pos.i.hi) {
            arg0->state = 2;
            return;
        }
        if (--ext->timer != 0)
            return;
        ext->timer = ext->period;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x21;
            shot->unk2 = 0;
            shot->state = 0;
        }
        return;

    case 0x10:
        if (ext->variant == 0) {
            if (arg0->x_pos.i.hi + 0x4C0 < g_Player.x_pos.i.hi) {
                arg0->state = 2;
                return;
            }
        } else if (arg0->x_pos.i.hi - g_Player.x_pos.i.hi < 0x181) {
            arg0->state = 3;
            return;
        }
        switch (arg0->unk5) {
        case 0:
            if (ext->variant == 0) {
                if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi < 0x181)
                    return;
                shot = find_free_shot_obj();
                if (shot != NULL) {
                    shot->active = 0x41;
                    shot->id = 0x21;
                    shot->unk15 = 0;
                }
            } else {
                if ((u32)(arg0->x_pos.i.hi - g_Player.x_pos.i.hi - 0x181) >= 0x23F)
                    return;
                shot = find_free_shot_obj();
                if (shot != NULL) {
                    shot->active = 0x41;
                    shot->id = 0x21;
                    shot->unk15 = 0x40;
                }
            }
            if (shot != NULL) {
                shot->unk2 = 4 - ext->burst;
                shot->x_pos.i.hi = arg0->x_pos.i.hi;
                shot->state = 3;
                shot->y_pos.i.hi = arg0->y_pos.i.hi;
            }
            arg0->unk5 = 1;
            return;
        case 1:
            if (--ext->timer != 0)
                return;
            if (--ext->burst == 0) {
                arg0->unk5 = 2;
                return;
            }
            arg0->unk5 = 0;
            ext->timer = ext->period;
            return;
        case 2:
            if (--ext->cooldown != 0)
                return;
            ext->cooldown = 0x78;
            ext->burst = 4;
            arg0->unk5 = 0;
            ext->timer = ext->period;
            return;
        }
        return;

    case 0x20:
        x = arg0->x_pos.i.hi;
        bg_x = background_objects[g_Player.bg_offset].x_pos.i.hi;
        if (x + 0x240 - bg_x <= 0 || bg_x - (x - 0x3C0) <= 0) {
            arg0->state = 2;
            return;
        }
        if (ext->proximity == 0) {
            if (--ext->timer != 0)
                return;
            ext->timer = ext->period;
            effect_33_spawn_dropper(arg0);
            return;
        }
        player_x = g_Player.x_pos.i.hi;
        distance = player_x - x;
        if (distance < 0)
            distance = x - player_x;
        if (distance >= 0x20) {
            ext->timer = ext->period;
            return;
        }
        if (--ext->timer != 0)
            return;
        effect_33_spawn_dropper(arg0);
        return;
    }
}

extern union AnimationStep* falling_rock_a_animations[];
extern union AnimationStep* falling_rock_b_animations[];
extern union AnimationStep* falling_rock_c_animations[];
extern union AnimationStep* falling_rock_d_animations[];
extern struct Unk_unk68 falling_rock_box_0[];
extern struct Unk_unk68 falling_rock_box_1[];
extern struct Unk_unk68 falling_rock_box_2[];
extern struct Unk_unk68 falling_rock_box_3[];
extern struct Unk_unk68 falling_rock_box_4[];
extern struct Unk_unk68 falling_rock_box_5[];
extern u8 falling_rock_debris_0[];
extern u8 falling_rock_debris_1[];
extern u8 falling_rock_debris_2[];
extern u8 falling_rock_debris_3[];
extern u8 falling_rock_debris_4[];
extern u8 falling_rock_debris_5[];
extern u8 falling_rock_debris_6[];

static void shot_33_load_graphics(struct ShotObj* arg0, s32 id)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(id);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(id);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    clut_x = func_8002938C(id);
    clut_y = func_8002938C(id);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
}

static void shot_33_spawn_shadow(struct ShotObj* arg0, s8 shadow_kind, s8 unk6,
    s32 animation)
{
    struct MiscObj* misc = find_free_misc_obj();

    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 0x1B;
    misc->unk16 = shadow_kind;
    misc->unk40 = arg0->unk40;
    misc->unk42 = arg0->unk42 & 0x7FFF;
    misc->animation_table = arg0->animation_table;
    misc->unk3C = arg0->unk3C;
    misc->bg_offset = arg0->bg_offset;
    misc->x_pos.val = arg0->x_pos.val;
    misc->y_pos.val = arg0->y_pos.val;
    misc->ext.misc_5.owner = (struct MainObj*)arg0;
    misc->state = 0;
    misc->unk6 = unk6;
    misc->unk7 = 0;
    misc->unk15 = arg0->unk15;
    set_animation(misc, animation);
    arg0->unk7C = (struct WeaponObj*)misc;
}

static s32 shot_33_touches_floor(struct ShotObj* arg0, s32 dx_extra, s32 dy_extra)
{
    const struct Unk_unk68* bounds = arg0->unk68;

    return func_8002D724((struct PlayerObj*)arg0,
               (s16)(arg0->x_pos.i.hi + bounds->unk0 + dx_extra),
               (s16)(arg0->y_pos.i.hi + bounds->unk1 + dy_extra))
        != 0;
}

static void shot_33_quake(void)
{
    if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
        start_screen_shake_x(0x10, 6, 2);
}

static void shot_33_hit_sound(struct ShotObj* arg0)
{
    if (arg0->on_screen != 0)
        func_8001540C(2, 0xA0, arg0);
}

static s32 shot_33_below_screen(struct ShotObj* arg0)
{
    return background_objects[g_Player.bg_offset].y_pos.i.hi + 0x150 < arg0->y_pos.i.hi;
}

void func_800A03F4(struct ShotObj* arg0)
{
    s32 random;

    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk5C = 0xF;
    arg0->on_screen = 1;
    arg0->unk60 = 3;
    arg0->unk42 &= 0x7FFF;
    shot_33_load_graphics(arg0, 0x8E);
    arg0->animation_table = (u32**)falling_rock_a_animations;
    random = get_random();
    random = ((random & 1) << 8) + (get_random() & 0xFF) + 0x40;
    arg0->x_pos.i.hi = background_objects[g_Player.bg_offset].x_pos.i.hi + random;
    arg0->x_vel.val = -0x10000;
    arg0->y_vel.val = -0x10000;
    arg0->unk28 = 0x400;
    arg0->unk2C = 0x400;
    arg0->unk68 = falling_rock_box_3;
    arg0->unk54 = (const u8*)falling_rock_box_0;
    arg0->unk50.data = (const u8*)falling_rock_box_0;
    arg0->unk16 = 1;
    arg0->unk15 = 0;
    arg0->unk62 = 2;
    arg0->y_pos.i.hi = background_objects[g_Player.bg_offset].y_pos.i.hi - 0x40;
    set_animation(arg0, 1);
    shot_33_spawn_shadow(arg0, 0, 0, 0);
    arg0->state = 1;
    arg0->unk5 = 0;
}

void func_800A068C(struct ShotObj* arg0)
{
    s32 hit;
    s32 collision;

    arg0->unk42 &= 0x7FFF;
    switch (arg0->unk5) {
    case 0:
        move_with_gravity(ANIMATED_OBJECT(arg0));
        animate_object(ANIMATED_OBJECT(arg0));
        hit = shot_33_touches_floor(arg0, -arg0->unk68->unk2, arg0->unk68->unk3);
        if (shot_33_touches_floor(arg0, -arg0->unk68->unk2, 0))
            hit = 1;
        if (shot_33_touches_floor(arg0, 0, arg0->unk68->unk3))
            hit = 1;
        if (hit) {
            shot_33_quake();
            arg0->x_vel.val = 0;
            arg0->unk28 = 0;
            arg0->y_vel.val = 0;
            arg0->unk2C = 0;
            set_animation(arg0, 2);
            arg0->unk5 = 1;
            return;
        }
        func_8002D9BC(arg0);
        if (func_8002BB80((struct MainObj*)arg0, (struct MainObj*)&g_Player) != 0) {
            set_animation(arg0, 2);
            arg0->unk5 = 1;
        }
        collision = func_8002DD04((struct MainObj*)arg0);
        if (collision < 0) {
            set_animation(arg0, 2);
            arg0->unk5 = 1;
        } else if (collision == 3 || collision == 0xC || collision == 0x22) {
            arg0->unk84.value = 8;
            set_animation(arg0, 8);
            arg0->unk7C->active = 0;
            arg0->unk7C->on_screen = 0;
            arg0->unk5 = 2;
        }
        break;
    case 1:
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event == 0)
            break;
        spawn_debris(5, falling_rock_debris_0, arg0);
        if (arg0->on_screen != 0)
            func_8001540C(2, 0xA0, arg0);
        arg0->state = 2;
        break;
    case 2:
        if (--arg0->unk84.value != 0)
            break;
        spawn_debris(5, falling_rock_debris_1, arg0);
        arg0->state = 2;
        break;
    }
    if (shot_33_below_screen(arg0)) {
        arg0->state = 2;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_800A0A38(struct ShotObj* arg0)
{
    arg0->on_screen = 1;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk5C = 0x7F;
    arg0->unk60 = 6;
    arg0->unk42 &= 0x7FFF;
    shot_33_load_graphics(arg0, 0x8C);
    arg0->animation_table = (u32**)falling_rock_b_animations;
    arg0->unk16 = 0;
    arg0->x_vel.val = arg0->unk15 != 0 ? -0x38000 : 0x38000;
    arg0->unk68 = falling_rock_box_4;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk54 = (const u8*)falling_rock_box_1;
    arg0->unk50.data = (const u8*)falling_rock_box_1;
    set_animation(arg0, 1);
    shot_33_spawn_shadow(arg0, 1, 1, 0);
    arg0->state = 4;
    arg0->unk5 = 0;
}

static void shot_33_burst(struct ShotObj* arg0, u8* effect)
{
    shot_33_quake();
    spawn_debris(5, effect, arg0);
    if (arg0->on_screen != 0) {
        func_8001540C(2, 0xA0, arg0);
        arg0->state = 5;
    } else {
        arg0->state = 5;
    }
}

void func_800A0C4C(struct ShotObj* arg0)
{
    s32 collision;

    arg0->unk42 &= 0x7FFF;
    if (arg0->unk5 != 0) {
        if (--arg0->unk84.value == 0) {
            spawn_debris(5, falling_rock_debris_3, arg0);
            arg0->state = 5;
        }
    } else {
        if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
            start_screen_shake_x(8, 4, 2);
        move_with_gravity(ANIMATED_OBJECT(arg0));
        animate_object(ANIMATED_OBJECT(arg0));
        CollisionRelated((struct PlayerObj*)arg0);
        if (!(arg0->unk70 & 8))
            arg0->unk2C = 0x8000;
        else
            arg0->unk2C = 0;
        if (arg0->unk15 != 0 ? (arg0->unk70 & 2) : (arg0->unk70 & 1)) {
            shot_33_burst(arg0, falling_rock_debris_2);
            return;
        }
        func_8002D9BC(arg0);
        if (func_8002BB80((struct MainObj*)arg0, (struct MainObj*)&g_Player) != 0) {
            spawn_debris(5, falling_rock_debris_2, arg0);
            shot_33_hit_sound(arg0);
            arg0->state = 5;
        }
        collision = func_8002DD04((struct MainObj*)arg0);
        if (collision < 0) {
            spawn_debris(5, falling_rock_debris_2, arg0);
            shot_33_hit_sound(arg0);
            arg0->state = 5;
        } else if (collision == 3 || collision == 0xC || collision == 0x22) {
            arg0->unk84.value = 8;
            set_animation(arg0, 7);
            arg0->unk7C->active = 0;
            arg0->unk7C->on_screen = 0;
            arg0->unk5 = 1;
        }
    }
    if (shot_33_below_screen(arg0)) {
        arg0->state = 5;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_800A0FE8(struct ShotObj* arg0)
{
    if (engine_obj.character_state.bytes[0] != 0) {
        arg0->state = 8;
        return;
    }
    arg0->on_screen = 1;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk5C = 0xF;
    arg0->unk60 = 6;
    arg0->unk42 &= 0x7FFF;
    shot_33_load_graphics(arg0, 0x8D);
    arg0->animation_table = (u32**)falling_rock_c_animations;
    arg0->unk16 = 0;
    arg0->unk15 = 0;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    if (arg0->unk2 == 0) {
        set_animation(arg0, 3);
        arg0->y_vel.val = -0x18000;
        arg0->unk2C = 0x2000;
        arg0->y_pos.i.hi = background_objects[g_Player.bg_offset].y_pos.i.hi - 0x40;
    } else {
        set_animation(arg0, 1);
        arg0->y_vel.val = 0xA0000;
        arg0->unk2C = 0x2000;
        if (engine_obj.substage != 0 && (u16)(arg0->x_pos.i.hi - 0x61) < 0x47F)
            arg0->y_pos.i.hi = 0x330;
        else
            arg0->y_pos.i.hi = background_objects[g_Player.bg_offset].y_pos.i.hi + 0x130;
    }
    arg0->unk68 = falling_rock_box_5;
    arg0->unk54 = (const u8*)falling_rock_box_2;
    arg0->unk50.data = (const u8*)falling_rock_box_2;
    shot_33_spawn_shadow(arg0, 1, 1, arg0->unk2 == 0 ? 2 : 0);
    arg0->state = 7;
    arg0->unk5 = 0;
}

static void shot_33_release(struct ShotObj* arg0, u8* effect)
{
    arg0->unk84.effect->ext.effect_33.timer = 0xB4;
    spawn_debris(5, effect, arg0);
    arg0->state = 8;
}

void func_800A12EC(struct ShotObj* arg0)
{
    s32 collision;

    arg0->unk42 &= 0x7FFF;
    if (arg0->unk5 != 0) {
        if (--arg0->timer == 0)
            shot_33_release(arg0, falling_rock_debris_5);
    } else {
        move_with_gravity(ANIMATED_OBJECT(arg0));
        CollisionRelated((struct PlayerObj*)arg0);
        if (arg0->unk70 & 4) {
            if (engine_obj.substage != 0 && (u16)(arg0->x_pos.i.hi - 0x61) < 0x47F) {
                if (arg0->unk6 != 0) {
                    arg0->y_pos.i.hi -= 0x28;
                    if (arg0->on_screen != 0)
                        func_8001540C(2, 0xA0, arg0);
                    func_800C842C(7, falling_rock_debris_6, arg0, 0x9A, falling_rock_d_animations);
                    arg0->y_pos.i.hi += 0x28;
                }
                apply_tile_effect(arg0->unk6, (s16)(arg0->x_pos.i.hi - 0x18),
                    (s16)(arg0->y_pos.i.hi - 0x58));
            }
            shot_33_quake();
            shot_33_hit_sound(arg0);
            spawn_debris(5, falling_rock_debris_4, arg0);
            arg0->state = 8;
            return;
        }
        if (arg0->unk70 & 8) {
            shot_33_quake();
            shot_33_hit_sound(arg0);
            spawn_debris(5, falling_rock_debris_4, arg0);
            arg0->state = 8;
            return;
        }
        if (arg0->y_vel.val == 0) {
            if (arg0->unk2 == 2) {
                arg0->state = 8;
                return;
            }
            set_animation(arg0, 3);
            set_animation(arg0->unk7C, 2);
        }
        animate_object(ANIMATED_OBJECT(arg0));
        func_8002D9BC(arg0);
        if (func_8002BB80((struct MainObj*)arg0, (struct MainObj*)&g_Player) != 0) {
            shot_33_hit_sound(arg0);
            spawn_debris(5, falling_rock_debris_4, arg0);
            arg0->state = 8;
        }
        collision = func_8002DD04((struct MainObj*)arg0);
        if (collision < 0 || engine_obj.character_state.bytes[0] != 0) {
            shot_33_hit_sound(arg0);
            shot_33_release(arg0, falling_rock_debris_4);
        } else if (collision == 3 || collision == 0xC || collision == 0x22) {
            arg0->timer = 8;
            set_animation(arg0, 9);
            arg0->unk7C->active = 0;
            arg0->unk7C->on_screen = 0;
            arg0->unk5 = 1;
        }
    }
    if (shot_33_below_screen(arg0)) {
        arg0->state = 8;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_800C842C(s32 count, u8* variants, void* owner, s32 id, void* animation_table)
{
    struct MiscObj* obj;
    s32 clut_x;
    s32 clut_y;
    s32 resource;

    for (; count & 0xFF; count--) {
        obj = find_free_misc_obj();
        if (obj == NULL)
            continue;
        obj->active = 0x41;
        obj->id = 3;
        obj->unk2 = 1;
        obj->unk15 = get_random() & 0x40;
        obj->state = 0;
        obj->unk5 = 0;
        obj->unk6 = 0;
        obj->x_pos.val = ((struct MainObj*)owner)->x_pos.val + ((get_random() & 3) << 16);
        obj->y_pos.val = ((struct MainObj*)owner)->y_pos.val + ((get_random() & 3) << 16);
        obj->ext.misc_2.owner = owner;
        obj->animation_table = animation_table;
        obj->ext.misc_2.unk58 = *variants++;
        clut_x = func_8002938C(id);
        clut_y = func_8002938C(id);
        obj->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
        resource = func_8002938C(id);
        obj->unk40 = D_801406A8[resource] >> 7;
        resource = func_8002938C(id);
        obj->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    }
}

extern struct Unk_unk68 D_80107374[];
extern union AnimationStep* wheel_charger_animations[9];
extern struct Unk_unk68 D_800FE1B0;
extern struct Unk_unk68 D_800FE1B4;
extern struct Unk_unk68 D_800FE1B8;
void wheel_charger_check_fall(struct MainObj*);

void func_8005ECA8(struct MainObj* arg0)
{
    arg0->contact_damage = 3;
    arg0->hp = 4;
    arg0->invincibility_timer = 0;
    arg0->collision_data = D_80107374;
    arg0->animation_table = (const u8* const*)wheel_charger_animations;
    arg0->unk16 = 6;
    arg0->terrain_box = &D_800FE1B8;
    arg0->hurt_box = &D_800FE1B0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->attack_box = &D_800FE1B4;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    switch (arg0->unk2) {
    case 0:
        arg0->x_speed = -0x28000;
        arg0->unk15 = 0;
        arg0->ext.main_35.unk80 = 0;
        arg0->unk5 = 2;
        break;
    case 1:
        arg0->unk7A = 1;
        arg0->unk15 = 0x40;
        arg0->ext.main_35.unk80 = 0;
        arg0->x_speed = 0x28000;
        arg0->unk5 = 4;
        break;
    case 2:
        arg0->x_speed = -0x28000;
        arg0->unk15 = 0;
        arg0->ext.main_35.unk80 = 1;
        arg0->unk5 = 2;
        break;
    case 3:
        arg0->unk7A = 1;
        arg0->unk15 = 0x40;
        arg0->ext.main_35.unk80 = 1;
        arg0->x_speed = 0x28000;
        arg0->unk5 = 4;
        break;
    }
    set_animation(arg0, 0);
    arg0->state = 1;
    arg0->unk6 = 0;
}

void func_8005EFB0(struct MainObj* arg0)
{
    u32 mode;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->collision_flags & 8) {
        func_8001540C(2, 0x57, arg0);
        mode = arg0->ext.main_35.unk80;
        arg0->y_speed = 0;
        arg0->gravity = 0;
        if (mode == 0) {
            arg0->unk5 = 2;
        } else if (mode == 1) {
            arg0->ext.main_35.unk80 = 2;
            set_animation(arg0, 1);
            arg0->contact_damage = 4;
            arg0->ext.main_35.sound_timer = 1;
            arg0->unk5 = 5;
        } else {
            arg0->x_speed = arg0->unk15 != 0 ? 0x40000 : -0x40000;
            arg0->ext.main_35.sound_timer = 1;
            arg0->unk5 = 5;
            arg0->unk6 = 3;
        }
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_35.unk80 == 2)
        return;
    if (arg0->unk15 == 0) {
        if (arg0->collision_flags & 2) {
            arg0->unk15 = 0x40;
            arg0->x_speed = 0x28000;
        }
    } else if (arg0->collision_flags & 1) {
        arg0->unk15 = 0;
        arg0->x_speed = -0x28000;
    }
}

extern u8 flame_jet_intervals[8];
extern struct Unk_unk68 flame_jet_debris[2];
extern struct Unk_unk68 flame_jet_extinguish_debris[2];
extern union AnimationStep* flame_jet_animations[9];
extern struct Unk_unk68 D_80107C78[];
extern s16 flame_jet_smoke_offsets[20];

static struct VisualObj* main_62_spawn_arm(struct MainObj* arg0, s8 side)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return NULL;
    visual->active = 0x41;
    visual->id = 0x19;
    visual->unk2 = side;
    visual->x_pos.val = arg0->x_pos.val + (arg0->unk15 != 0 ? -0x690000 : 0x690000);
    visual->unk50 = (struct PlayerObj*)arg0;
    visual->y_pos.val = arg0->y_pos.val - 0x80000;
    return visual;
}

void func_8007B90C(struct MainObj* arg0)
{
    struct VisualObj* visual = NULL;

    arg0->active |= 4;
    arg0->unk15 = (arg0->unk2 & 1) ? 0x40 : 0;
    arg0->unk7C = flame_jet_intervals[arg0->unk2];
    if (arg0->unk2 < 4) {
        main_62_spawn_arm(arg0, 1);
        visual = main_62_spawn_arm(arg0, 0);
        spawn_debris_offset(6, (u8*)flame_jet_debris, (struct MiscObj*)arg0,
            arg0->unk15 != 0 ? -0x690000 : 0x690000, 0);
    }
    arg0->ext.main_62.unk80 = visual;
    arg0->ext.main_62.unk86 = 0;
    arg0->animation_table = (const u8* const*)flame_jet_animations;
    arg0->unk16 = 2;
    arg0->collision_data = D_80107C78;
    arg0->hp = 0x7F;
    arg0->terrain_box = NULL;
    arg0->invincibility_timer = 0;
    arg0->unk62 = 0;
    arg0->contact_damage = 4;
    arg0->air_state = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk5++;
}

u8 func_8007BABC(struct MainObj* arg0)
{
    struct WeaponObj* weapon;

    arg0->hurt_box = &flame_jet_vent_box;
    for (weapon = weapon_objects; weapon < weapon_objects + COUNT(weapon_objects); weapon++) {
        if (!weapon->active)
            continue;
        if (!func_8002BD58((struct MainObj*)weapon, arg0,
                &((s16*)&weapon->unk80)[0], &((s16*)&weapon->unk80)[1]))
            continue;
        if (weapon->id == 2 || weapon->id == 0xB || weapon->id == 0x21)
            return 1;
    }
    return 0;
}

void func_8007BE40(struct MainObj* arg0)
{
    s32 index;
    s32 x_offset;

    if (--arg0->unk7E != 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
        arg0->ext.main_62.unk86 = arg0->on_screen;
        return;
    }
    arg0->unk5++;
    index = arg0->animation_step.fields.frame_index - 3;
    x_offset = flame_jet_smoke_offsets[index * 2];
    if (arg0->unk15 != 0)
        x_offset = -x_offset;
    spawn_debris_offset(8, (u8*)flame_jet_extinguish_debris, (struct MiscObj*)arg0, x_offset << 16,
        flame_jet_smoke_offsets[index * 2 + 1] << 16);
    arg0->state = 1;
    arg0->unk5 = 3;
    arg0->unk7E = 0xC8;
    arg0->hp = 0x7F;
    arg0->unk42 -= 2;
    set_animation(arg0, 2);
}

void func_800B3D3C(struct VisualObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk50;

    arg0->unk40 = owner->unk40;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk15 = owner->unk15;
    arg0->bg_offset = owner->bg_offset;
    arg0->unk16 = arg0->unk2 != 0 ? 1 : 6;
    set_animation(arg0, arg0->unk2);
    arg0->state++;
}

extern struct Unk_unk68 shell_crawler_terrain_box;
extern union AnimationStep* shell_crawler_animations[14];

void func_8004D9CC(struct MainObj* arg0)
{
    struct Main0Ext* ext = &arg0->ext.main_0;
    s32 dy;

    if (arg0->air_state != 0 || (ext->background_relative & 3))
        return;
    if (ext->flags[1] != 0) {
        ext->flags[1]--;
        return;
    }
    dy = arg0->y_pos.i.hi - g_Player.y_pos.i.hi;
    if (dy < 0)
        dy = -dy;
    if (dy >= 0x28) {
        ext->index = 0;
        return;
    }
    if (arg0->unk15 != 0) {
        if (g_Player.x_pos.i.hi < arg0->x_pos.i.hi + 0x50)
            ext->index++;
        else
            ext->index = 0;
    } else {
        if (arg0->x_pos.i.hi - 0x50 < g_Player.x_pos.i.hi)
            ext->index++;
        else
            ext->index = 0;
    }
    if (ext->index >= 0x3D) {
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        set_animation(arg0, 7);
        ext->index = 0;
        ext->background_relative |= 2;
    }
}

void func_8004DB10(struct MainObj* arg0)
{
    const struct Unk_unk68* bounds;
    s32 x;

    if (arg0->air_state != 0)
        return;
    CollisionRelated(PLAYER_OBJECT(arg0));
    if (!(arg0->collision_flags & 8)) {
        set_animation(arg0, 3);
        arg0->unk5 = 2;
        arg0->gravity = 0x4200;
        arg0->unk6 = 0;
        arg0->y_speed = 0;
        arg0->x_accel = 0;
        arg0->air_state = -1;
        return;
    }
    bounds = arg0->terrain_box;
    if (arg0->unk15 != 0)
        x = arg0->x_pos.i.hi + bounds->unk0 + bounds->unk2;
    else
        x = arg0->x_pos.i.hi - bounds->unk0 - bounds->unk2;
    if (func_8002D724(PLAYER_OBJECT(arg0), (s16)x,
            (s16)(arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 + 8)))
        return;
    if (arg0->unk2 == 1) {
        arg0->unk15 = (arg0->unk15 == 0) << 6;
        arg0->x_speed = -arg0->x_speed;
        return;
    }
    if (arg0->collision_flags & 3)
        return;
    set_animation(arg0, 2);
    arg0->y_speed = 0x38000;
    arg0->unk5 = 5;
    arg0->unk6 = 0;
    arg0->gravity = 0x4200;
    arg0->x_speed = arg0->unk15 != 0 ? 0x10000 : -0x10000;
    arg0->air_state = 1;
}

void func_8004DCB0(struct MainObj* arg0)
{
    struct Main0Ext* ext = &arg0->ext.main_0;
    struct WeaponObj* weapon;
    s32 dy;

    if (arg0->air_state != 0 || (ext->background_relative & 1))
        return;
    if (ext->flags[0] != 0) {
        ext->flags[0]--;
        return;
    }
    for (weapon = weapon_objects; weapon < weapon_objects + COUNT(weapon_objects); weapon++) {
        if (!weapon->active || weapon->id != 0)
            continue;
        if (arg0->unk15 != 0) {
            if (g_Player.unk15 == 0 && arg0->x_pos.val < g_Player.x_pos.val) {
                dy = weapon->y_pos.i.hi - arg0->y_pos.i.hi;
                if (dy < 0)
                    dy = -dy;
                if (dy < 0x18 && weapon->x_pos.i.hi < arg0->x_pos.i.hi + 0x80)
                    ext->background_relative |= 1;
            }
        } else {
            if (g_Player.unk15 != 0 && g_Player.x_pos.val < arg0->x_pos.val) {
                dy = weapon->y_pos.i.hi - arg0->y_pos.i.hi;
                if (dy < 0)
                    dy = -dy;
                if (dy < 0x18 && arg0->x_pos.i.hi - 0x80 < weapon->x_pos.i.hi)
                    ext->background_relative |= 1;
            }
        }
        if (ext->background_relative & 1) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            set_animation(arg0, 5);
            return;
        }
    }
}

static void main_15_spawn_spark(struct MainObj* arg0, u8 index)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0xA;
    shot->unk42 = 0x7885;
    shot->bg_offset = arg0->bg_offset;
    shot->x_pos.val = arg0->x_pos.val;
    shot->unk2 = index * 2;
    shot->y_pos.val = arg0->y_pos.val;
    set_velocity_from_angle(MOVING_OBJECT(shot), (s8)(index * 2));
    arg0->unk7C = 0xA;
}

void func_8004E300(struct MainObj* arg0)
{
    u8 i;

    switch (arg0->unk6) {
    case 0:
        arg0->unk6++;
        arg0->gravity = 0x4200;
        arg0->air_state = -1;
        arg0->y_speed = 0;
        arg0->x_speed = 0;
        arg0->x_accel = 0;
        arg0->collision_data = D_801069F4;
        set_animation(arg0, 0xD);
        /* fallthrough */
    case 1:
        if (arg0->collision_flags & 8) {
            arg0->gravity = 0;
            arg0->air_state = 0;
        }
        move_with_gravity(ANIMATED_OBJECT(arg0));
        break;
    }
    if (func_8002DD04(arg0) != 0 || func_8002D9BC(arg0) != 0) {
        arg0->state = 2;
        spawn_explosion(BASE_OBJECT(arg0));
        for (i = 0; i < 0x10; i += 2)
            main_15_spawn_spark(arg0, i);
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) != 0) {
        arg0->state = 2;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x25, 0x25);
}

void func_8004E490(struct MainObj* arg0)
{
    u8 i;

    if (--arg0->unk7C != 0)
        return;
    arg0->state = 2;
    for (i = 1; i < 0x10; i += 2)
        main_15_spawn_spark(arg0, i);
}

void func_8004E55C(struct MainObj* arg0)
{
    struct Main0Ext* ext = &arg0->ext.main_0;

    arg0->unk5 = 1;
    arg0->state++;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)shell_crawler_animations;
    arg0->unk16 = 6;
    arg0->terrain_box = &shell_crawler_terrain_box;
    arg0->hurt_box = &shell_crawler_body_box;
    arg0->attack_box = &shell_crawler_body_box;
    arg0->hp = 3;
    arg0->collision_data = D_801069F4;
    arg0->invincibility_timer = 0;
    arg0->air_state = 0;
    arg0->contact_damage = 1;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    ext->background_relative = 0;
    ext->flags[0] = 0;
    ext->index = 0;
    ext->flags[1] = 0;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : 0x40;
    if ((u8)(arg0->unk2 - 2) < 2) {
        arg0->state = 5;
        arg0->hurt_box = NULL;
        arg0->attack_box = NULL;
        arg0->x_pos.i.hi = (arg0->x_pos.i.hi & ~0xF) + 8;
        arg0->y_pos.i.hi = (arg0->y_pos.i.hi & ~0xF) + 0x14;
        set_animation(arg0, 0);
    } else {
        set_animation(arg0, 1);
    }
}

extern u8 fortress_cannon_debris[8];
extern void (*fortress_cannon_step_funcs[7])(struct MainObj*);
void fortress_cannon_check_fall(struct MainObj*);

void func_80069BE4(struct MainObj* arg0)
{
    s32 collision;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    fortress_cannon_step_funcs[arg0->unk5](arg0);
    collision = func_8002DD04(arg0);
    func_8002D9BC(arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
    fortress_cannon_check_fall(arg0);
    if (arg0->unk5 != 0)
        arg0->ext.main_51.saved_unk5 = arg0->unk5;
    if (collision < 0) {
        spawn_debris(5, fortress_cannon_debris, arg0);
        arg0->unk7C = 0x1E;
        arg0->on_screen = 0;
        arg0->unk7E = 5;
        arg0->state++;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x60, 0x40) != 0) {
        arg0->state = 3;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
}

void func_80069F28(struct MainObj* arg0)
{
    struct Main51Ext* ext = &arg0->ext.main_51;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    arg0->unk6 = 0;
    ext->unk84++;
    if (arg0->unk2 == 0) {
        if ((s32)ext->unk84 < engine_obj.cur_character + 3)
            return;
    } else if ((s32)ext->unk84 < 4) {
        return;
    }
    arg0->unk5 = 4;
    arg0->unk7C = 0x14;
    ext->unk84 = 0;
}

extern struct Unk_unk68 D_80106170[32];
extern u8 cannon_shot_boxes[4][4];
extern s32 cannon_shot_speeds[4];
void func_8009FB9C(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s32 dx;
    s32 dy;

    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 6;
    arg0->unk58.collision_bounds = D_80106170;
    arg0->unk50.data = (const u8*)cannon_shot_boxes;
    arg0->unk54 = (const u8*)cannon_shot_boxes;
    arg0->unk68 = NULL;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk42 &= 0x7FFF;
    arg0->state++;
    if (arg0->unk2 == 0) {
        dx = 0x20;
        dy = -8;
    } else if (arg0->unk2 == 1) {
        dx = 0x1D;
        dy = 0xE;
    } else {
        dx = 0xC;
        dy = 0x12;
    }
    arg0->x_pos.i.hi = owner->x_pos.i.hi + (arg0->unk15 != 0 ? dx : -dx);
    arg0->y_pos.i.hi = owner->y_pos.i.hi + dy;
    set_animation(arg0, 3);
    cannon_shot_spawn_flash(arg0);
    arg0->unk84.value = 0x10;
    arg0->unk8C.word = 0;
}

void func_8009FD00(struct ShotObj* arg0)
{
    s32 speed;

    animate_object(ANIMATED_OBJECT(arg0));
    move_with_gravity(ANIMATED_OBJECT(arg0));
    speed = arg0->x_vel.val;
    if (speed < 0)
        speed = -speed;
    if (speed > 0x30000)
        arg0->unk28 = 0;
    if (func_8002DD04((struct MainObj*)arg0) < 0) {
        spawn_explosion(BASE_OBJECT(arg0));
    } else {
        func_8002D9BC(arg0);
        if (--arg0->unk84.value == 0 && arg0->unk17 != 4) {
            arg0->unk28 = 0x600;
            arg0->x_vel.val = cannon_shot_speeds[(arg0->unk15 & 0x40) ? 1 : 0];
            if (arg0->unk15 & 0x40)
                arg0->x_pos.i.hi += 0x10;
            else
                arg0->x_pos.i.hi -= 0x10;
            set_animation(arg0, 4);
        }
        if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
            update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
            return;
        }
    }
    arg0->unk8C.word = 1;
    arg0->state++;
}

void func_800B1F78(struct VisualObj* arg0)
{
    struct MainObj* owner;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 == 0) {
        owner = (struct MainObj*)arg0->unk50;
        if (owner->ext.main_38.unk88 == 1 && owner->id == 0x26)
            set_animation(arg0, 0x13);
        if (owner->ext.main_38.unk88 == 2 || owner->unk5 != 3)
            arg0->state = 2;
        update_on_screen(BASE_OBJECT(arg0), 0x50, 0x50);
        return;
    }
    shot = (struct ShotObj*)arg0->unk50;
    if (shot->active == 0 || shot->unk8C.word != 0)
        arg0->state = 2;
    arg0->x_pos.i.hi = shot->x_pos.i.hi;
    arg0->y_pos.i.hi = shot->y_pos.i.hi;
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
}

extern struct Unk_unk68 D_801044F8;
extern void* D_80104770[25];
extern void (*colonel_step_funcs[9])();
extern u8 D_801044A0[8];
extern u8 D_801044A8[8];
extern void* D_801044EC[2];
extern u8 D_801044F4[4];
void colonel_spawn_afterimages(struct MainObj*);
void colonel_face_player(struct MainObj*);

void func_80086008(struct MainObj* arg0)
{
    struct Main69Ext* ext = &arg0->ext.main_69;

    if (ext->state.bytes.variant == 0) {
        if (ext->effect->active != 0)
            return;
        arg0->unk6 = 0;
    } else {
        arg0->unk6 = 1;
    }
    arg0->unk16 = 5;
    arg0->contact_damage = 6;
    arg0->air_state = 0;
    arg0->unk15 = 0;
    arg0->hp = 0;
    arg0->invincibility_timer = 0;
    arg0->terrain_box = &D_801044F8;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->hurt_box = NULL;
    arg0->attack_box = NULL;
    arg0->collision_data = NULL;
    arg0->animation_table = (const u8* const*)D_80104770;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    set_animation(arg0, 0);
    colonel_spawn_afterimages(arg0);
    engine_obj.unk25 = 1;
    engine_obj.boss_ptr = arg0;
    arg0->state = 1;
    ext->state.bytes.unk8D = 0;
    ext->state.bytes.unk8E = 0;
    arg0->unk5 = 2;
}

void func_80086124(struct MainObj* arg0)
{
    struct Main69Ext* ext = &arg0->ext.main_69;
    s32 collision;

    colonel_step_funcs[arg0->unk5](arg0);
    collision = func_8002DD04(arg0);
    if (ext->state.bytes.unk8D != 0) {
        if (ext->state.bytes.unk8D & 1)
            arg0->unk42 &= 0x7FFF;
        else
            arg0->unk42 |= 0x8000;
        if (--ext->state.bytes.unk8D == 0) {
            arg0->collision_data = D_80108084;
            ext->state.bytes.unk8E = 0;
        }
    } else if (collision < 0) {
        arg0->state = 2;
        arg0->unk5 = ext->state.bytes.variant != 0 ? 1 : 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
        is_on_screen(BASE_OBJECT(arg0));
        return;
    } else if (collision != 0 && collision != 0x7F) {
        arg0->collision_data = D_801060F0;
        ext->state.bytes.unk8D = 0x40;
        ext->state.bytes.unk8E = 1;
    }
    func_8002D9BC(arg0);
}

void func_80086860(struct MainObj* arg0)
{
    if (arg0->unk7C != 0) {
        arg0->unk7C--;
        return;
    }
    if (g_Player.script_state != -1)
        return;
    arg0->unk7C = 0x20;
    arg0->x_speed = 0x200000;
    arg0->x_accel = -0x10000;
    arg0->x_pos.i.hi = background_objects[0].unk1E + 0x100;
    colonel_face_player(arg0);
    func_8001540C(2, 0xD3, arg0);
    arg0->unk6++;
}

void func_80086C00(struct MainObj* arg0)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return;
    visual->active = 0x41;
    visual->id = 0x1E;
    visual->unk2 = 0;
    visual->unk50 = PLAYER_OBJECT(arg0);
    arg0->ext.main_69.linked_object = visual;
    arg0->unk7C = 0x10;
    arg0->unk7++;
    func_8001540C(2, 0xD7, arg0);
}

void func_800877A4(struct MainObj* arg0)
{
    s16 player_x;

    if (--arg0->unk7C != 0)
        return;
    player_x = g_Player.x_pos.i.hi;
    if (player_x < background_objects[0].x_pos.i.hi + 0xB0)
        arg0->x_pos.i.hi = player_x + 0x30;
    else
        arg0->x_pos.i.hi = player_x - 0x30;
    colonel_face_player(arg0);
    set_animation(arg0, 5);
    func_8001540C(2, 0xD4, arg0);
    arg0->hurt_box = &D_80104508;
    arg0->attack_box = &D_80104504;
    arg0->unk7C = 0x1E;
    arg0->unk6++;
}

void func_80087A00(struct MainObj* arg0)
{
    s32 speed;

    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 != 0) {
        if (arg0->x_speed <= 0x41FFF)
            arg0->x_speed = 0x42000;
    } else if (arg0->x_speed > -0x42000) {
        arg0->x_speed = -0x42000;
    }
    if (arg0->unk15 != 0) {
        if (arg0->x_pos.i.hi < (s16)background_objects[0].unk1E + 0x110)
            return;
        speed = 0x42000;
    } else {
        if ((s16)background_objects[0].unk1E + 0x50 < arg0->x_pos.i.hi)
            return;
        speed = -0x42000;
    }
    arg0->x_speed = speed;
    arg0->x_accel = -0x3000;
    arg0->unk4B = -1;
    set_animation(arg0, 2);
    arg0->unk6++;
}

static struct VisualObj* main_69_spawn_part(struct MainObj* arg0, s8 part)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return NULL;
    visual->active = 0x41;
    visual->id = 0x1E;
    visual->unk2 = part;
    visual->unk50 = PLAYER_OBJECT(arg0);
    return visual;
}

void func_800881F8(struct MainObj* arg0)
{
    struct VisualObj* visual;
    struct EffectObj* effect;

    if (arg0->animation_step.fields.event != 1) {
        animate_object(ANIMATED_OBJECT(arg0));
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    func_8001540C(2, 0xD5, arg0);
    visual = main_69_spawn_part(arg0, 0);
    if (visual != NULL) {
        arg0->unk7C = 0x30;
        arg0->ext.main_69.linked_object = visual;
    }
    main_69_spawn_part(arg0, 0x20);
    visual = main_69_spawn_part(arg0, 0x10);
    if (visual != NULL)
        visual->unk54 = 0x50;
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 0x41;
        effect->id = 0x25;
        effect->unk2 = 0x10;
        effect->ext.effect_37.unk1E = 8;
        effect->ext.effect_37.unk1F = 2;
        effect->ext.effect_37.unk20 = 3;
        effect->ext.effect_37.unk21 = 6;
    }
    arg0->unk6++;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800883CC(struct MainObj* arg0)
{
    struct ShotObj* shot;
    u8 i;

    if (arg0->animation_step.fields.relative_step != 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    for (i = 0; i < 2; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x2D;
            shot->unk2 = i + 0x10;
            shot->unk7C = WEAPON_OBJECT(arg0);
            shot->unk8C.object = OBJECT_HEADER(arg0);
        }
        func_8001540C(2, 0xD7, arg0);
    }
    main_69_spawn_part(arg0, 0x30);
    start_screen_shake_y(0x10, 2, 1);
    arg0->unk7C = 0x50;
    arg0->unk6++;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800889DC(struct MainObj* arg0)
{
    struct Main69Ext* ext = &arg0->ext.main_69;
    u8 roll = get_random() & 0xF;
    u8 level;
    u8** scripts;
    u8 i;

    if (ext->state.bytes.variant == 1) {
        ext->script = roll < 10 ? D_801044A0 : D_801044A8;
        return;
    }
    level = (arg0->hp - 1) / 24;
    scripts = D_801044EC[level];
    for (i = 0; i < 2; i++) {
        if (roll < D_801044F4[level * 2 + i]) {
            ext->script = scripts[i];
            return;
        }
    }
}

extern s16 colonel_wave_offsets[2][2];
extern s8 colonel_shot_boxes[14][4];

void func_800A7CE8(struct ShotObj* arg0)
{
    s32 speed;

    set_animation(arg0, 0xE);
    arg0->unk5C = 5;
    if (engine_obj.stage == 0xA) {
        arg0->unk60 = 7;
        speed = arg0->unk15 != 0 ? 0x60000 : -0x60000;
    } else {
        arg0->unk60 = 6;
        speed = arg0->unk15 != 0 ? 0x50000 : -0x50000;
    }
    arg0->x_vel.val = speed;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    if (arg0->unk15 != 0)
        arg0->x_pos.i.hi += colonel_wave_offsets[arg0->unk2][0];
    else
        arg0->x_pos.i.hi -= colonel_wave_offsets[arg0->unk2][0];
    arg0->unk58.collision_bounds = D_801060F0;
    arg0->unk54 = (const u8*)colonel_shot_boxes[1];
    arg0->unk50.data = (const u8*)colonel_shot_boxes[0];
    arg0->unk6++;
    arg0->y_pos.i.hi += colonel_wave_offsets[arg0->unk2][1];
}

void func_800A83C4(struct ShotObj* arg0)
{
    u8 kind;

    arg0->unk60 = 9;
    arg0->unk50.data = (const u8*)colonel_shot_boxes[0];
    arg0->unk5C = 0;
    arg0->unk58.data = NULL;
    arg0->unk54 = NULL;
    kind = arg0->unk2 & 0xF;
    arg0->x_vel.val = arg0->unk15 != 0 ? 0x18000 : -0x18000;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->x_pos.i.hi += arg0->unk15 != 0 ? 0x10 : -0x10;
    if (kind < 5) {
        set_animation(arg0, 0xB);
    } else if (kind < 8) {
        set_animation(arg0, 0xC);
        arg0->x_pos.i.hi += arg0->unk15 != 0 ? 4 : -4;
    } else {
        set_animation(arg0, 0xD);
        arg0->x_pos.i.hi += arg0->unk15 != 0 ? 8 : -8;
    }
    arg0->unk6++;
}

void func_800A858C(struct ShotObj* arg0)
{
    static const u8 bounds[6] = { 2, 3, 4, 6, 7, 8 };
    u32 index = arg0->animation_step.fields.frame_index - 0x37;

    if (index < 6)
        arg0->unk50.data = (const u8*)colonel_shot_boxes[bounds[index]];
    else
        arg0->unk50.data = NULL;
}

extern struct Unk_unk68 D_80107574[];
extern s8 homing_orb_hurt_box[4];
extern s8 homing_orb_attack_box[4];
extern union AnimationStep* homing_orb_animations[7];

void func_80062D9C(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->state++;
    arg0->unk16 = 6;
    arg0->hp = 3;
    arg0->contact_damage = 3;
    arg0->collision_data = D_80107574;
    arg0->attack_box = homing_orb_hurt_box;
    arg0->hurt_box = homing_orb_attack_box;
    arg0->unk15 = 0;
    arg0->terrain_box = NULL;
    arg0->invincibility_timer = 0;
    arg0->animation_table = (const u8* const*)homing_orb_animations;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk7C = 0xB4;
    arg0->ext.main_42.background_relative = 0;
    arg0->ext.main_42.unk84 = NULL;
    arg0->bg_offset = g_Player.bg_offset;
    set_animation(arg0, 0);
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}

extern struct Unk_unk68 latcher_hurt_box;
extern struct Unk_unk68 D_801073F4[];

void func_8005F558(struct MainObj* arg0)
{
    struct MainObj* current;
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    resource = func_8002938C(0x24);
    arg0->unk40 = D_801406A8[resource] >> 7;
    clut_x = func_8002938C(0x24);
    clut_y = func_8002938C(0x24);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    resource = func_8002938C(0x24);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->attack_box = &latcher_hurt_box;
    arg0->hurt_box = &latcher_hurt_box;
    arg0->animation_table = (const u8* const*)latcher_animations;
    arg0->unk16 = 6;
    arg0->unk62 = 3;
    arg0->collision_data = D_801073F4;
    arg0->hp = 0x10;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk15 = 0;
    arg0->contact_damage = 0;
    arg0->terrain_box = NULL;
    arg0->invincibility_timer = 0;
    arg0->bg_offset = g_Player.bg_offset;
    switch (arg0->unk2) {
    case 0:
        set_animation(arg0, 0);
        memset(SP_CUR_MAIN_OBJ->ext.main_36.pad80, 0, sizeof(SP_CUR_MAIN_OBJ->ext.main_36.pad80));
        break;
    case 1:
        set_animation(arg0, 1);
        arg0->x_speed = 0x18000;
        break;
    case 2:
        set_animation(arg0, 1);
        arg0->unk15 = 0x40;
        arg0->x_speed = -0x18000;
        break;
    }
    current = SP_CUR_MAIN_OBJ;
    current->ext.main_36.unk8A = 0x80;
    current->ext.main_36.unk8C = 0;
    SP_CUR_MAIN_OBJ->ext.main_36.unk8D = 0;
    arg0->state = 1;
    arg0->unk5 = 2;
}

extern union AnimationStep* cyberspace_guide_animations[5];
extern u8 cyberspace_guide_offsets[12];

void func_800CE8DC(struct MiscObj* arg0)
{
    struct Misc34Ext* ext = &arg0->ext.misc_34;
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->unk16 = 2;
    arg0->unk15 = 0;
    arg0->animation_table = (u32**)cyberspace_guide_animations;
    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0x90);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x90);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    clut_x = func_8002938C(0x90);
    clut_y = func_8002938C(0x90);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    arg0->x_pos.i.hi = g_Player.x_pos.i.hi;
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    ext->timer = 0;
    ext->pad55 = 0;
    ext->variant = 0;
    ext->unk57 = 0;
    ext->unk58 = 0;
    ext->enabled = 0;
    ext->unk5A = 0;
    ext->unk5C = 0;
    ext->unk5D = 0;
    ext->timer = 0x24;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi;
    set_animation(arg0, 0);
    func_8001540C(2, 0xE9, arg0);
}

static void misc_34_track_axis(f32* position, s32 target, s16 target_hi)
{
    s32 delta = target - position->val;

    if (delta < 0)
        delta = -delta;
    if (delta <= 0x1FFFFF)
        return;
    position->i.hi = target < position->val ? target_hi + 0x20 : target_hi - 0x20;
}

void func_800CEBC0(struct MiscObj* arg0)
{
    struct EffectObj* related = arg0->ext.misc_34.related;
    s32 dx;
    s32 dy;

    animate_object(ANIMATED_OBJECT(arg0));
    set_velocity_from_angle(MOVING_OBJECT(arg0),
        (u8)angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)));
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->x_vel.val *= 4;
    arg0->y_vel.val *= 3;
    misc_34_track_axis(&arg0->x_pos, g_Player.x_pos.val, g_Player.x_pos.i.hi);
    misc_34_track_axis(&arg0->y_pos, g_Player.y_pos.val, g_Player.y_pos.i.hi);
    dx = g_Player.x_pos.val - arg0->x_pos.val;
    if (dx < 0)
        dx = -dx;
    dy = g_Player.y_pos.val - arg0->y_pos.val;
    if (dy < 0)
        dy = -dy;
    if (dx > 0x20000 || dy > 0x20000) {
        move_with_gravity(ANIMATED_OBJECT(arg0));
    } else {
        arg0->x_pos.val = g_Player.x_pos.val;
        arg0->y_pos.val = g_Player.y_pos.val;
    }
    if (related->state >= 3)
        arg0->ext.misc_34.enabled = 1;
    if (related->state >= 4)
        arg0->unk5 = 3;
}

void func_800CEFC0(struct MiscObj* arg0)
{
    struct Misc34Ext* ext = &arg0->ext.misc_34;
    u8 limit;
    u8 counter;

    if (ext->enabled == 0 || ext->variant == 2)
        return;
    limit = cyberspace_guide_offsets[engine_obj.checkpoint * 2 + ext->variant];
    counter = ext->unk58;
    ext->unk58 = counter + 1;
    if (counter >= 0x3C) {
        if (++ext->unk57 == limit - 3 && arg0->unk17 != 3) {
            set_animation(arg0, 2);
            ext->unk5A = 0xB4;
        }
        ext->unk58 = 0;
    }
    if (ext->unk57 >= limit) {
        ext->variant = ext->variant == 0 ? 1 : 2;
        ext->unk57 = 0;
    }
}

extern union AnimationStep* cyberspace_warp_animations[5];
extern s16 cyberspace_warp_positions[6][2];
extern s16 cyberspace_warp_exit_position[2];

void func_800CE388(struct MiscObj* arg0)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->unk16 = 2;
    arg0->unk15 = 0;
    arg0->animation_table = (u32**)cyberspace_warp_animations;
    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0x9B);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x9B);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    clut_x = func_8002938C(0x9B);
    clut_y = func_8002938C(0x9B);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    arg0->x_pos.i.hi = g_Player.x_pos.i.hi;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi;
    switch ((u32)arg0->unk2) {
    case 0:
        set_animation(arg0, 0);
        arg0->ext.misc_33.timer = 0x48;
        arg0->unk5 = 0;
        arg0->unk16 = 6;
        break;
    case 1:
        set_animation(arg0, 1);
        arg0->ext.misc_33.timer = 0x48;
        arg0->unk5 = 0;
        arg0->unk16 = 0x11;
        break;
    case 2:
    case 3:
    case 4:
        set_animation(arg0, arg0->unk2);
        arg0->unk5 = 1;
        arg0->unk16 = 0x10;
        break;
    }
    if (engine_obj.substage != 0) {
        arg0->x_pos.i.hi = cyberspace_warp_exit_position[0];
        arg0->y_pos.i.hi = cyberspace_warp_exit_position[1];
    } else if (arg0->unk2 >= 2) {
        arg0->x_pos.i.hi = cyberspace_warp_positions[engine_obj.checkpoint][0];
        arg0->y_pos.i.hi = cyberspace_warp_positions[engine_obj.checkpoint][1];
    } else {
        arg0->x_pos.i.hi = cyberspace_warp_positions[engine_obj.checkpoint][0] - 0xA;
        arg0->y_pos.i.hi = cyberspace_warp_positions[engine_obj.checkpoint][1] + 0x30;
    }
    arg0->state = 1;
    arg0->unk6 = 0;
}

extern union AnimationStep* enemy_hatch_animations[4];

void func_800CBF14(struct MiscObj* arg0)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->unk15 = arg0->x_pos.i.hi - g_Player.x_pos.i.hi > 0 ? 0 : 0x40;
    resource = func_8002938C(0x8F);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x8F);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    clut_x = func_8002938C(0x8F);
    clut_y = func_8002938C(0x8F);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    arg0->animation_table = (u32**)enemy_hatch_animations;
    arg0->unk5 = 0;
    arg0->unk16 = 5;
    arg0->unk6 = 0;
    arg0->ext.misc_24.child_active = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->state++;
}

void func_800CC114(struct MiscObj* arg0)
{
    struct MiscObj* child;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk6 = 0;
    arg0->unk5 = 1;
    child = find_free_misc_obj();
    if (child == NULL)
        return;
    child->active = 0x41;
    child->id = 0xB;
    child->unk2 = 3;
    child->unk16 = 3;
    child->unk15 = arg0->unk15;
    child->unk40 = arg0->unk40;
    child->unk42 = arg0->unk42;
    child->unk3C = arg0->unk3C;
    child->animation_table = arg0->animation_table;
    child->bg_offset = arg0->bg_offset;
    child->x_pos.val = arg0->x_pos.val;
    child->y_pos.val = arg0->y_pos.val;
    set_animation(child, 2);
    child->ext.misc_11.active = 0;
    arg0->ext.misc_24.child = child;
    arg0->ext.misc_24.child_active = 1;
}

extern union AnimationStep* ambient_bubble_animations[3];
extern u16 ambient_bubble_positions[8];
extern s32 ambient_bubble_speeds[4];
extern s32 ambient_bubble_accels[4];
extern u16 ambient_bubble_respawn_delays[4];

void func_800CFB70(struct MiscObj* arg0)
{
    u8 resource = func_8002938C(0x9F);

    arg0->active |= 0x40;
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk40 = D_801406A8[resource] >> 7;
    arg0->unk42 = SOME_COORDINATE_CONVERSION(resource);
    arg0->animation_table = (u32**)ambient_bubble_animations;
    arg0->unk16 = 0x20;
    arg0->bg_offset = 1;
    arg0->unk15 = 0x40;
    arg0->state++;
    arg0->unk2 &= 3;
    arg0->ext.misc_24.timer = ambient_bubble_respawn_delays[arg0->unk2];
}

void func_800CFC6C(struct MiscObj* arg0)
{
    if (arg0->ext.misc_24.timer != 0) {
        arg0->ext.misc_24.timer--;
        return;
    }
    arg0->x_pos.i.hi = background_objects[1].x_pos.i.hi + 0x14A;
    arg0->y_pos.i.hi = background_objects[1].y_pos.i.hi + ambient_bubble_positions[get_random() & 7];
    set_animation(arg0, 1);
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk5++;
    arg0->x_vel.val = ambient_bubble_speeds[arg0->unk2];
    arg0->unk2C = ambient_bubble_accels[arg0->unk2];
}

void airship_bob_update_section(struct LayerObj*);
void airship_bob_sway(struct LayerObj*);
extern void (*airship_bob_section_funcs[])(struct LayerObj*);

static s32 layer_05_scroll(struct LayerObj* arg0)
{
    s32 value;

    memcpy(&value, &arg0->bg_offset, sizeof(value));
    return value;
}

void func_800DA2D4(struct LayerObj* arg0)
{
    s32 scroll = 0x8000;

    arg0->state++;
    background_objects[1].unk4D = 2;
    background_objects[2].unk4D = 2;
    background_objects[1].unk4E = 7;
    background_objects[2].unk4E = 8;
    memcpy(&arg0->bg_offset, &scroll, sizeof(scroll));
    arg0->unk18.val = -0x5800;
    arg0->private_state.value.val = 0;
    memset(arg0->pad20, 0, sizeof(arg0->pad20));
    arg0->unk24 = 3;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    func_800DA358(arg0);
}

void func_800DA358(struct LayerObj* arg0)
{
    s32 half = (background_objects[0].unk14.val - background_objects[0].x_pos.val) / 2;

    background_objects[1].x_pos.val += layer_05_scroll(arg0) - half;
    background_objects[2].x_pos.val -= layer_05_scroll(arg0) / 2 + half / 2;
    arg0->unk25 = arg0->unk24;
    if (engine_obj.substage != 0)
        return;
    airship_bob_update_section(arg0);
    airship_bob_section_funcs[arg0->unk5](arg0);
    if (engine_obj.substage != 0)
        return;
    airship_bob_sway(arg0);
    if (g_Player.x_pos.i.hi >= 0x18D0)
        engine_obj.unkF = 1;
}

extern struct Unk_unk68 D_80107F04[];
extern struct Unk_unk68 gunship_hurt_box;
extern struct Unk_unk68 gunship_terrain_box;
extern void (*gunship_step_funcs[7])();
void gunship_bob(struct MainObj*);
void collide_with_players(struct PlayerObj*);

void func_80082574(struct MainObj* arg0)
{
    s32 collision;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    gunship_step_funcs[arg0->unk5](arg0);
    collision = func_8002DD04(arg0);
    func_8002D9BC(arg0);
    if (arg0->ext.main_67.unk89 == 0)
        gunship_bob(arg0);
    collide_with_players(PLAYER_OBJECT(arg0));
    if (arg0->unk5 != 0)
        arg0->ext.main_67.saved_unk5 = arg0->unk5;
    if (collision < 0) {
        arg0->unk7C = 0x64;
        arg0->unk7E = 5;
        arg0->unk5 = 0;
        arg0->unk42 &= 0x7FFF;
        arg0->state++;
        return;
    }
    if (collision != 0
        && (engine_obj.cur_character == 0 ? (collision == 2 || collision == 0xB) : collision == 0x21)
        && arg0->unk5 != 6) {
        arg0->unk5 = 6;
        arg0->unk6 = 0;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x60, 0x60) != 0) {
        despawn_object(OBJECT_HEADER(arg0));
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800828B4(struct MainObj* arg0)
{
    s32 dx;
    s32 dy;

    animate_object(ANIMATED_OBJECT(arg0));
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (dx < 0)
        dx = -dx;
    if (--arg0->unk7C == 0) {
        if (dx < 0xC1) {
            dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
            if (dy < 0)
                dy = -dy;
            arg0->unk5 = dy < 0x31 ? 3 : 4;
        } else {
            arg0->unk5 = 4;
        }
        arg0->unk6 = 0;
        arg0->ext.main_67.unk8D = 0;
    }
    if (arg0->unk72 == 8 && arg0->ext.main_67.unk8D != 0) {
        dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
        if (dx < 0)
            dx = -dx;
        if (dx < 0xC1) {
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            arg0->ext.main_67.unk8D = 1;
        }
    }
}

extern u8 gunship_shot_bullet_hit_box[4];
extern u8 gunship_shot_missile_hit_box[4];
extern s32 gunship_shot_missile_speeds[2];

void func_800A699C(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;

    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 5;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk2 < 2) {
        arg0->x_pos.i.hi = owner->x_pos.i.hi + (arg0->unk15 != 0 ? 0x45 : -0x45);
        arg0->y_pos.i.hi = owner->y_pos.i.hi + (arg0->unk2 == 0 ? -0x1A : -9);
        arg0->unk50.data = gunship_shot_bullet_hit_box;
        arg0->unk58.collision_data = D_80106070;
        arg0->unk68 = NULL;
        arg0->unk54 = gunship_shot_bullet_hit_box;
        arg0->x_vel.val = gunship_shot_missile_speeds[arg0->unk15 != 0 ? 1 : 0];
        set_animation(arg0, 2);
        arg0->state = 1;
        arg0->unk60 = 4;
        return;
    }
    arg0->unk50.data = gunship_shot_missile_hit_box;
    arg0->unk54 = gunship_shot_missile_hit_box;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk68 = NULL;
    arg0->x_vel.val = -0x28000;
    arg0->y_vel.val = 0x28000;
    switch (arg0->unk2) {
    case 2:
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x14;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x27;
        break;
    case 3:
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 8;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x19;
        break;
    case 4:
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 8;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x33;
        break;
    case 5:
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x14;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x40;
        break;
    }
    arg0->unk90.bytes[1] = 0x14;
    arg0->unk90.bytes[0] = 0xC;
    arg0->unk8C.word = 0x5A;
    set_animation(arg0, 5);
    arg0->unk7 = 2;
    arg0->state = 2;
    arg0->unk60 = 6;
}

void func_800A6DF4(struct ShotObj* arg0)
{
    u8 timer = arg0->unk90.bytes[1];
    u8 target;
    u8 current;
    u8 next;
    s32 animation;

    arg0->unk90.bytes[1] = timer - 1;
    if (timer != 0)
        return;
    arg0->unk90.bytes[1] = 1;
    arg0->unk16 = 5;
    target = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    current = arg0->unk90.bytes[0];
    if (current < target) {
        if (target == current + 1)
            return;
        if (target - current < 0x11)
            next = (current + 1) & 0x1F;
        else
            next = ((current | 0x20) - 1) & 0x1F;
    } else if (target < current) {
        if (target == current - 1)
            return;
        if (current - target < 0x11)
            next = ((current | 0x20) - 1) & 0x1F;
        else
            next = (current + 1) & 0x1F;
    } else {
        return;
    }
    arg0->unk90.bytes[0] = next;
    set_velocity_from_angle(MOVING_OBJECT(arg0), next);
    arg0->x_vel.val <<= 2;
    arg0->y_vel.val <<= 2;
    animation = next / 2;
    set_animation(arg0, animation < 4 ? animation + 0xF : animation - 1);
}

extern u8 train_crate_hurt_box[4];
extern u8 D_800FFBDC[6];
extern u8 train_crate_debris[6];
extern void (*train_crate_step_funcs[2])();

void func_80069748(struct MainObj* arg0)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->on_screen = 0;
    arg0->contact_damage = 0;
    arg0->invincibility_timer = 0;
    resource = func_8002938C(0x28);
    arg0->unk40 = D_801406A8[resource] >> 7;
    clut_x = func_8002938C(0x28);
    clut_y = func_8002938C(0x28);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    resource = func_8002938C(0x28);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk16 = 6;
    arg0->hurt_box = train_crate_hurt_box;
    arg0->animation_table = (const u8* const*)train_crate_animations;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->attack_box = NULL;
    arg0->terrain_box = NULL;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->ext.main_50.unk84 = (u8)arg0->unk2 >> 4;
    arg0->unk2 &= 0xF;
    arg0->collision_data = arg0->ext.main_50.unk84 == 8 ? D_80108584 : D_80108504;
    arg0->hp = 3;
    arg0->unk15 = 0;
    arg0->state = 1;
    arg0->unk5 = 1;
}

void func_800698D8(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    train_crate_step_funcs[arg0->unk5](arg0);
    if (func_8002DD04(arg0) >= 0) {
        if (func_8002B160(BASE_OBJECT(arg0)) != 0)
            despawn_object(OBJECT_HEADER(arg0));
        return;
    }
    arg0->ext.main_50.timer = 0;
    spawn_debris(6, arg0->ext.main_50.unk84 == 8 ? train_crate_debris : D_800FFBDC, arg0);
    if (engine_obj.stage == 8) {
        apply_tile_effect(arg0->unk2 + 8, arg0->x_pos.i.hi - 0x20, arg0->y_pos.i.hi - 0x40);
    } else {
        apply_tile_effect(arg0->unk2, arg0->x_pos.i.hi - 0x20, arg0->y_pos.i.hi - 0x30);
        if (arg0->ext.main_50.unk84 != 0)
            apply_tile_effect(arg0->ext.main_50.unk84, arg0->x_pos.i.hi - 0x20, arg0->y_pos.i.hi);
    }
    arg0->ext.main_50.unk84 = 0;
    arg0->state = 2;
    arg0->unk5 = 0;
}

extern struct Unk_unk68 train_cannon_hurt_box;
extern struct Unk_unk68 train_cannon_attack_box;
extern struct Unk_unk68 train_cannon_terrain_box;

extern u8 cannon_blast_box_0[4];
extern u8 cannon_blast_box_1[4];

void func_8009D048(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;
    s32 distance;

    animate_object(ANIMATED_OBJECT(arg0));
    if ((u32)(arg0->unk84.value - 0x1A) < 0x4A)
        func_8002D9BC(arg0);
    if (arg0->unk84.value == 0x46)
        arg0->unk50.data = arg0->unk2 != 0 ? cannon_blast_box_1 : cannon_blast_box_0;
    if (arg0->unk84.value == 0x19)
        set_animation(arg0, arg0->unk2 != 0 ? 0xC : 0xB);
    distance = background_objects[0].x_pos.i.hi - owner->x_pos.i.hi;
    if (distance < 0)
        distance = -distance;
    if ((u16)distance >= 0x1A0) {
        if (arg0->unk2 != 0)
            arg0->x_pos.i.hi = owner->x_pos.i.hi - distance + 0x29;
        else
            arg0->x_pos.i.hi = owner->x_pos.i.hi - (distance - 0x129);
    }
    if (--arg0->unk84.value == 0 || owner->active == 0 || owner->state >= 2)
        arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x80, 0x20);
}

extern u8 cannon_shell_hit_box[4];
extern u8 cannon_shell_flat_hit_box[4];
extern u8 cannon_shell_steep_hit_box[4];
extern u8 cannon_shell_terrain_box[4];
extern u8 cannon_shell_flat_terrain_box[4];
extern u8 cannon_shell_steep_terrain_box[4];

void func_8009D23C(struct ShotObj* arg0)
{
    struct WeaponObj* owner;
    s32 distance;
    u32 half;
    u32 steps;

    arg0->unk68 = (struct Unk_unk68*)cannon_shell_terrain_box;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk60 = 3;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk54 = cannon_shell_hit_box;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    owner = arg0->unk7C;
    if (arg0->unk2 != 0) {
        arg0->unk50.data = cannon_shell_flat_hit_box;
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 0xA;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x10;
    } else {
        arg0->unk50.data = cannon_shell_hit_box;
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x12;
        arg0->y_pos.i.hi = owner->y_pos.i.hi;
    }
    arg0->x_vel.val = -0x28000;
    arg0->y_vel.val = 0x28000;
    arg0->unk28 = 0;
    distance = arg0->x_pos.val - g_Player.x_pos.val;
    if (distance < 0)
        distance = -distance;
    half = distance / 2;
    if (half <= 0x1FFFFF)
        half += 0x100000;
    if (half > 0x400000)
        half -= arg0->unk2 << 21;
    distance = arg0->x_vel.val;
    if (distance < 0)
        distance = -distance;
    steps = half / (u32)distance;
    if (steps == 0)
        steps = 1;
    arg0->unk84.value = 0;
    arg0->unk70 = 0;
    arg0->unk7 = 1;
    arg0->unk2C = (u32)arg0->y_vel.val / steps;
    set_animation(arg0, 7);
}

static s32 shot_21_abs(s32 value)
{
    return value < 0 ? -value : value;
}

void func_8009D588(struct ShotObj* arg0)
{
    switch (arg0->unk84.value) {
    case 0:
        if (shot_21_abs(arg0->y_vel.val) >= shot_21_abs(arg0->x_vel.val / 2))
            return;
        set_animation(arg0, 8);
        arg0->unk68 = (struct Unk_unk68*)cannon_shell_flat_terrain_box;
        arg0->unk54 = cannon_shell_flat_hit_box;
        arg0->unk50.data = cannon_shell_flat_hit_box;
        break;
    case 1:
        if (shot_21_abs(arg0->y_vel.val) < shot_21_abs(arg0->x_vel.val / 2))
            return;
        set_animation(arg0, 9);
        arg0->unk68 = (struct Unk_unk68*)cannon_shell_terrain_box;
        arg0->unk54 = cannon_shell_hit_box;
        arg0->unk50.data = cannon_shell_hit_box;
        break;
    case 2:
        if (shot_21_abs(arg0->x_vel.val) >= shot_21_abs(arg0->y_vel.val / 2))
            return;
        set_animation(arg0, 0xA);
        arg0->unk68 = (struct Unk_unk68*)cannon_shell_steep_terrain_box;
        arg0->unk54 = cannon_shell_steep_hit_box;
        arg0->unk50.data = cannon_shell_steep_hit_box;
        break;
    default:
        return;
    }
    arg0->unk84.value++;
}

extern s16 D_800FE18C[][2];

void func_8005E5C0(struct MainObj* arg0)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    resource = func_8002938C(0x22);
    arg0->unk40 = D_801406A8[resource] >> 7;
    clut_x = func_8002938C(0x22);
    clut_y = func_8002938C(0x22);
    arg0->unk42 = ((clut_x * 4 + 0x1A) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    resource = func_8002938C(0x22);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_pos.i.hi = D_800FE18C[arg0->unk2][0];
    arg0->y_pos.i.hi = D_800FE18C[arg0->unk2][1];
    arg0->animation_table = (const u8* const*)highway_trooper_animations;
    arg0->unk16 = 6;
    arg0->x_speed = -0x1C000;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk15 = 0;
    arg0->attack_box = NULL;
    arg0->hurt_box = NULL;
    arg0->collision_data = NULL;
    arg0->invincibility_timer = 0;
    arg0->hp = 1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (arg0->unk2 != 2)
        arg0->terrain_box = &highway_trooper_terrain_box;
    set_animation(arg0, 1);
    arg0->state = 1;
    arg0->unk5 = 0;
}

void func_8005EB40(struct MainObj* arg0)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_34.unk80 > 0)
        return;
    if (arg0->unk2 == 0) {
        arg0->x_speed = -0x1C000;
        arg0->y_speed = 0xC000;
        arg0->gravity = 0x2000;
        arg0->terrain_box = NULL;
        set_animation(arg0, 5);
        arg0->unk5 = 4;
    } else {
        arg0->terrain_box = NULL;
        arg0->unk15 = 0x40;
        arg0->x_speed = 0x38000;
        arg0->y_speed = 0;
        arg0->gravity = 0;
        set_animation(arg0, 1);
        arg0->unk5 = 5;
    }
}

extern u8 trooper_bomb_terrain_box[4];
extern u8 trooper_bomb_debris[8];
extern s8 trooper_bomb_offsets[4];

void func_8009CCB4(struct ShotObj* arg0)
{
    arg0->unk68 = (struct Unk_unk68*)trooper_bomb_terrain_box;
    arg0->unk60 = 2;
    arg0->unk2C = 0x2000;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->y_vel.val = 0x1F000;
    arg0->unk28 = 0;
    arg0->unk67 = 0;
    arg0->unk16 = 0;
    arg0->unk54 = NULL;
    arg0->unk50.data = NULL;
    arg0->unk58.data = NULL;
    arg0->x_vel.val = -0x1C000;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    arg0->x_pos.i.hi += trooper_bomb_offsets[0];
    arg0->y_pos.i.hi += trooper_bomb_offsets[1];
    set_animation(arg0, 6);
}

#define RIDE_U8(object, offset) (((u8*)&(object)->unk7C)[(offset)-0x7C])
#define RIDE_S8(object, offset) (*(s8*)&RIDE_U8(object, offset))
#define RIDE_U16(object, offset) (*(u16*)&RIDE_U8(object, offset))

MMX4_STATIC_ASSERT(ride_armor_tail_layout,
    MMX4_OFFSET_OF(struct RideArmorObj, saved_y_vel) - MMX4_OFFSET_OF(struct RideArmorObj, unk7C) == 0x9E - 0x7C);
MMX4_STATIC_ASSERT(ride_armor_player_unk9A,
    MMX4_OFFSET_OF(struct RideArmorObj, pad9A) == MMX4_OFFSET_OF(struct PlayerObj, shot_cycle));

extern union AnimationStep* D_800F8FC4[38];
extern u8 D_800F905C[12];
extern u8 D_800F9068[4];
extern u8 D_800F906C[4];
extern s32 D_800F9090[2];
extern s32 D_800F9098[2];
extern u8 D_800F9100[4];
extern u8 D_800F9104[4];
extern u8 D_800F9108[4];
extern u8 D_800F910C[4];
extern u8 D_800F9110[4];
extern u8 D_800F9114[4];
extern void (*D_800F90E8[])(struct RideArmorObj*);
void func_8003B458(void*, s8);
void func_8003D164(struct RideArmorObj*, s32);
void func_8003CF6C(struct RideArmorObj*);
void func_8003CA44(struct RideArmorObj*);
void func_8003D01C(struct RideArmorObj*);
void func_8003D3B4(struct PlayerObj*);
void func_8003B98C(struct PlayerObj*);
void func_8003B694(struct RideArmorObj*);
void func_8003CCBC(struct RideArmorObj*);
void func_8003C9A4(struct RideArmorObj*);

static u16 ride_chaser_clut(void)
{
    u8 resource = func_8002938C(0x82);

    return SOME_COORDINATE_CONVERSION(resource);
}

static void ride_chaser_spawn_body(struct RideArmorObj* arg0)
{
    struct WeaponObj* weapon = find_free_weapon_obj();
    u8 unk16;

    if (weapon == NULL)
        return;
    weapon->active = 0x41;
    weapon->id = 0x39;
    weapon->x_pos.i.hi = arg0->x_pos.i.hi;
    weapon->y_pos.i.hi = arg0->y_pos.i.hi;
    weapon->animation_table = (u32**)arg0->animation_table;
    weapon->unk40 = arg0->unk40;
    weapon->unk3C = arg0->unk3C;
    weapon->unk42 = ride_chaser_clut();
    weapon->owner = (struct PlayerObj*)arg0;
    unk16 = arg0->unk16;
    weapon->unk16 = unk16;
    weapon->unk15 = arg0->unk15;
}

void func_8003B470(struct RideArmorObj* arg0)
{
    struct EffectObj* effect;
    u8 resource;

    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->on_screen = 1;
    arg0->active |= 0x40;
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->unk15 = 0x40;
    arg0->animation_table = (u32**)D_800F8FC4;
    arg0->y_pos.val = g_Player.y_pos.val;
    resource = func_8002938C(0x82);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk40 = D_801406A8[resource] >> 7;
    arg0->unk42 = SOME_COORDINATE_CONVERSION(resource);
    if (g_Player.unk2 != 0)
        arg0->unk42 += 2;
    arg0->unk16 = 4;
    arg0->unk54 = D_800F906C;
    arg0->unk60 = 0;
    arg0->unk61 = 0;
    arg0->unk67 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk50 = NULL;
    arg0->unk68 = (struct Unk_unk68*)D_800F9068;
    arg0->unk58 = NULL;
    arg0->unk5C = g_Player.hp;
    func_8002C808((struct PlayerObj*)arg0);
    arg0->unk7D = 0;
    arg0->unk7E = 0;
    arg0->unk80.bytes.unk83 = 0;
    arg0->unk80.bytes.unk82 = 0;
    arg0->unk7C = 1;
    arg0->unk7D = 0;
    arg0->unk80.bytes.unk81 = 0;
    arg0->unk80.bytes.unk80 = 0;
    g_Player.ride_state = 1;
    RIDE_U8(arg0, 0x9B) = 1;
    arg0->unk8E.value = 0;
    set_animation(arg0, 0);
    func_8003B458(arg0, 0x41);
    RIDE_U8(arg0, 0x89) = 0;
    RIDE_U8(arg0, 0x98) = 0;
    RIDE_U8(arg0, 0x9A) = 0;
    RIDE_U16(arg0, 0x9C) = 0;
    background_objects[arg0->bg_offset].unk30 = 0x200;
    func_8003D164(arg0, 0);
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x1B;
        arg0->unkA0.chaser_effect = effect;
    }
    background_objects[0].unk44 = 1;
    background_objects[1].unk44 = 1;
    background_objects[2].unk44 = 1;
}

void func_8003B694(struct RideArmorObj* arg0)
{
    const struct Unk_unk68* bounds = arg0->unk68;
    s32 x;

    if (arg0->unk15 == 0)
        x = arg0->x_pos.i.hi + bounds->unk0;
    else
        x = arg0->x_pos.i.hi - bounds->unk0;
    if ((u8)func_8002D724((struct PlayerObj*)arg0, (s16)x,
            (s16)(arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 - 0xF))
        != 0x24) {
        RIDE_U16(arg0, 0x9C) = 0;
        return;
    }
    if (RIDE_U16(arg0, 0x9C) != 0) {
        RIDE_U16(arg0, 0x9C) -= 1;
        return;
    }
    arg0->x_pos.i.hi -= 8;
    arg0->y_pos.i.hi += 0x10;
    spawn_common_effect((struct MainObj*)arg0, 4);
    RIDE_U16(arg0, 0x9C) = 2;
    arg0->y_pos.i.hi -= 0x10;
    arg0->x_pos.i.hi += 8;
}

void func_8003B7B4(struct RideArmorObj* arg0)
{
    s8 health = arg0->unk5C;

    if (health == 0 || g_Player.hp == 0) {
        g_Player.hp = -0x80;
        arg0->unk5C = -0x80;
        spawn_debris(0xB, D_800F905C, arg0);
        arg0->state = 3;
        return;
    }
    if (health < 0 && (health & 0x7F) != 0) {
        RIDE_U8(arg0, 0x9A) = 1;
        arg0->unk61 = 0x79;
        arg0->unk85 = 1;
        g_Player.hp = arg0->unk5C & 0x7F;
    }
    if (background_objects[0].pad51[0] != 0) {
        RIDE_U8(arg0, 0x9B) = 0;
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    if (background_objects[0].unk4 == 1 && RIDE_S8(arg0, 0x9B) != 0) {
        arg0->x_pos.i.hi += background_objects[0].x_pos.i.hi - background_objects[0].unk14.i.hi;
        arg0->y_pos.i.hi += background_objects[0].y_pos.i.hi - background_objects[0].unk18.i.hi;
    }
    D_800F90E8[arg0->unk5](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    func_8003B694(arg0);
    if (arg0->unk5 != 0) {
        func_8003CF6C(arg0);
        arg0->unk80.bytes.unk83 = arg0->unk80.bytes.unk82;
        arg0->unk80.bytes.unk82 = func_8003CF24(arg0);
        func_8003CA44(arg0);
        if (RIDE_U8(arg0, 0x89) != 0)
            RIDE_U8(arg0, 0x89) -= 1;
        func_8003D01C(arg0);
    }
    func_8003D3B4((struct PlayerObj*)arg0);
    func_8003B98C((struct PlayerObj*)arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_8003BB20(struct RideArmorObj* arg0)
{
    s16 dx = arg0->x_pos.i.hi - background_objects[arg0->bg_offset].x_pos.i.hi;
    struct EffectObj* effect;
    s32 speed;

    switch (arg0->unk6) {
    case 0:
        arg0->unk6 = 1;
        arg0->unk7C = 1;
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk28 = 0x8000;
        arg0->unk2C = 0;
        arg0->unk15 = 0x40;
        func_8001540C(5, 0, NULL);
        set_animation(arg0, 6);
        func_8003B458(arg0, 0x47);
        ride_chaser_spawn_body(arg0);
        move_with_gravity(ANIMATED_OBJECT(arg0));
        return;
    case 1:
        speed = arg0->x_vel.val;
        if (speed < 0)
            speed = -speed;
        if (speed > 0x7FFFF) {
            arg0->x_vel.val = 0x80000;
            arg0->unk28 = 0;
        }
        if (dx >= 0xC0) {
            arg0->unk6 = 2;
            arg0->x_vel.val = 0x60000;
            arg0->unk28 = -0x4000;
        }
        break;
    case 2:
        if (dx < 0x91) {
            arg0->unk6 = 3;
            arg0->x_vel.val = 0;
            arg0->unk28 = 0;
            set_animation(arg0, 7);
            func_8003B458(arg0, 0x4B);
        }
        break;
    case 3:
        if (arg0->animation_step.fields.relative_step == 0)
            arg0->unk6 = 4;
        break;
    case 4:
        effect = arg0->unkA0.chaser_effect;
        if (effect->active == 0 || effect->unk5 == 3) {
            arg0->unk5 = 1;
            arg0->unk6 = 0;
        }
        break;
    default:
        move_with_gravity(ANIMATED_OBJECT(arg0));
        return;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    move_with_gravity(ANIMATED_OBJECT(arg0));
}

static void ride_chaser_land_animation(struct RideArmorObj* arg0)
{
    switch (arg0->unk80.bytes.unk82) {
    case 0:
        set_animation(arg0, 5);
        func_8003B458(arg0, 0x46);
        break;
    case 1:
        set_animation(arg0, 4);
        func_8003B458(arg0, 0x44);
        break;
    case 2:
        set_animation(arg0, 3);
        func_8003B458(arg0, 0x42);
        break;
    }
}

void func_8003BF1C(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk2C = 0x5000;
    }
    arg0->unk67 = 1;
    func_8003C6EC(arg0, 4);
    if (arg0->unk70 & 8) {
        arg0->unk67 = 0;
        arg0->unk2C = 0;
        arg0->y_vel.val = 0;
        if (arg0->unk7D != 0) {
            arg0->unk5 = 5;
            arg0->unk6 = 1;
            RIDE_U8(arg0, 0x99) = 0;
        } else {
            arg0->unk5 = 1;
            arg0->unk80.bytes.unk80 &= 0xFD;
            ride_chaser_land_animation(arg0);
        }
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (0x68000 - arg0->y_vel.val < 0)
        arg0->y_vel.val = 0x68000;
    func_8003CCBC(arg0);
    if (arg0->unk7D != 0)
        arg0->unk8E.value = 1;
    func_8003CBCC(arg0);
}

void func_8003C08C(struct RideArmorObj* arg0)
{
    u8 value;

    switch (arg0->unk6) {
    case 0:
        if (arg0->unk8E.value != 0) {
            arg0->unk6 = 6;
            arg0->y_vel.val = 0;
            arg0->unk2C = 0;
        } else {
            arg0->unk6 = 1;
        }
        arg0->spawned_parts = 1;
        arg0->x_vel.val = 0x40000;
        arg0->unk28 = -0x1000;
        arg0->unk90.value = 0x1000;
        arg0->unk94.value = 0;
        arg0->unk80.bytes.unk80 |= 1;
        background_objects[arg0->bg_offset].unk47 = 8;
        set_animation(arg0, D_800F9100[arg0->unk80.bytes.unk82]);
        func_8003B458(arg0, D_800F910C[arg0->unk80.bytes.unk82]);
        move_with_gravity(ANIMATED_OBJECT(arg0));
        ride_chaser_spawn_body(arg0);
        goto end;
    case 1:
        if (arg0->x_vel.val <= 0) {
            arg0->unk6 = 4;
            set_animation(arg0, D_800F9104[arg0->unk80.bytes.unk82]);
            func_8003B458(arg0, D_800F9110[arg0->unk80.bytes.unk82]);
            arg0->spawned_parts = 0;
            func_8001540C(5, 0, NULL);
        } else if (arg0->unk70 & 8) {
            func_8003C9A4(arg0);
            if (arg0->unk8C.value & 0x80) {
                arg0->y_vel.val = 0x68000;
                arg0->unk6 = 2;
                arg0->unk2C = 0x5000;
                arg0->unk28 = 0;
                arg0->unk80.bytes.unk80 |= 2;
            }
        } else {
            arg0->unk6 = 3;
            arg0->unk2C = 0x5000;
        }
        break;
    case 2:
        func_8003C584(arg0);
        goto end;
    case 3:
        if (arg0->unk70 & 8) {
            arg0->unk6 = 4;
            arg0->unk67 = 0;
            arg0->unk28 = 0;
            arg0->unk2C = 0;
            arg0->y_vel.val = 0;
            arg0->spawned_parts = 0;
            ride_chaser_land_animation(arg0);
        }
        func_8003C624(arg0);
        goto end;
    case 4:
        if (arg0->animation_step.fields.relative_step == 0)
            arg0->unk6 = 5;
        break;
    case 5:
        arg0->unk5 = 1;
        arg0->spawned_parts = 0;
        arg0->unk6 = 0;
        arg0->unk7D = 0;
        arg0->unk80.bytes.unk80 &= 0xFC;
        background_objects[arg0->bg_offset].unk47 = 6;
        set_animation(arg0, D_800F9108[arg0->unk80.bytes.unk82]);
        func_8003B458(arg0, D_800F9114[arg0->unk80.bytes.unk82]);
        move_with_gravity(ANIMATED_OBJECT(arg0));
        goto end;
    case 6:
        if (arg0->unk70 & 8) {
            RIDE_U8(arg0, 0x99) = 1;
        } else {
            value = arg0->unk80.bytes.unk81;
            if (value >= 0x38 || (value < 0x20 && value != 0))
                RIDE_U8(arg0, 0x99) = 1;
        }
        if (arg0->x_vel.val <= 0) {
            arg0->unk6 = 3;
            arg0->unk2C = 0x5000;
            arg0->unk8E.value = 0;
            RIDE_U8(arg0, 0x99) = 0;
            func_8001540C(5, 0, NULL);
        } else if (RIDE_U8(arg0, 0x99) == 0) {
            if (arg0->unk8A & 4)
                arg0->y_pos.val -= 0x8000;
            else if (arg0->unk8A & 8)
                arg0->y_pos.val += 0x8000;
        }
        break;
    default:
        goto end;
    }
    func_8003C624(arg0);
    animate_object(ANIMATED_OBJECT(arg0));
end:
    func_8003C6EC(arg0, arg0->spawned_parts != 0 ? 3 : 2);
}

void func_8003C6EC(struct RideArmorObj* arg0, u8 kind)
{
    struct WeaponObj* weapon;
    struct VisualObj* visual;

    if (!(arg0->unk8C.value & 0x30) || RIDE_U8(arg0, 0x89) != 0 || RIDE_U8(arg0, 0x98) >= 3)
        return;
    weapon = find_free_weapon_obj();
    if (weapon != NULL) {
        weapon->active = 0x41;
        weapon->id = 0x38;
        weapon->unk2 = kind;
        weapon->x_pos.i.hi = arg0->x_pos.i.hi;
        weapon->y_pos.i.hi = arg0->y_pos.i.hi;
        weapon->animation_table = (u32**)arg0->animation_table;
        weapon->unk40 = arg0->unk40;
        weapon->unk3C = arg0->unk3C;
        weapon->unk42 = ride_chaser_clut();
        weapon->owner = (struct PlayerObj*)arg0;
        weapon->unk16 = arg0->unk16;
        weapon->unk15 = arg0->unk15;
    }
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 0xC;
        visual->unk2 = kind;
        visual->x_pos.i.hi = arg0->x_pos.i.hi;
        visual->y_pos.i.hi = arg0->y_pos.i.hi;
        visual->animation_table = (u32**)arg0->animation_table;
        visual->unk40 = arg0->unk40;
        visual->unk3C = arg0->unk3C;
        visual->unk42 = ride_chaser_clut();
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->unk16 = arg0->unk16;
        visual->unk15 = arg0->unk15;
    }
    RIDE_U8(arg0, 0x89) = 4;
    RIDE_U8(arg0, 0x98) += 1;
    func_8001540C(5, 2, arg0);
}

void func_8003CA44(struct RideArmorObj* arg0)
{
    if (arg0->unk80.bytes.unk82 == arg0->unk80.bytes.unk83 || (arg0->unk80.bytes.unk80 & 2))
        return;
    switch (arg0->unk80.bytes.unk82) {
    case 0:
        set_animation(arg0, 2);
        func_8003B458(arg0, 0x45);
        break;
    case 1:
        set_animation(arg0, 1);
        func_8003B458(arg0, 0x43);
        break;
    case 2:
        set_animation(arg0, 0);
        func_8003B458(arg0, 0x41);
        break;
    }
}

u8 func_8003CF24(struct RideArmorObj* arg0)
{
    u8 tile = arg0->unk80.bytes.unk81;

    if (tile != 0 && tile < 9)
        return tile < 5 ? 0 : 1;
    if (tile != 0x10)
        return 2;
    return arg0->unk80.bytes.unk83;
}

void func_8003CF6C(struct RideArmorObj* arg0)
{
    const struct Unk_unk68* bounds = arg0->unk68;
    s32 x;

    if (arg0->unk15 == 0)
        x = arg0->x_pos.i.hi + bounds->unk0;
    else
        x = arg0->x_pos.i.hi - bounds->unk0;
    arg0->unk80.bytes.unk81 = func_8002D724((struct PlayerObj*)arg0, (s16)x,
        (s16)(arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 + 1));
}

void func_8003D01C(struct RideArmorObj* arg0)
{
    const struct Unk_unk68* bounds = arg0->unk68;
    s32 offset = (u16)arg0->x_pos.i.hi - (u16)background_objects[arg0->bg_offset].x_pos.i.hi;
    s16 edge;

    if (arg0->unk15 != 0)
        offset -= bounds->unk0;
    else
        offset += bounds->unk0;
    edge = offset - bounds->unk2;
    if (edge <= 0 && !(arg0->unk70 & 1)) {
        arg0->x_pos.i.hi -= edge;
    } else if (edge < -8) {
        g_Player.hp = -0x80;
        arg0->unk5C = -0x80;
    }
    edge = offset + bounds->unk2;
    if (edge >= 0x100)
        arg0->x_pos.i.hi -= (s16)(edge - 0x100);
}

extern u8 ride_chaser_shot_hit_box[4];
extern u16 ride_chaser_shot_offsets[][2];
extern u8 ride_chaser_shot_angles[];
extern u8 ride_chaser_shot_animations[];

void func_80098630(struct WeaponObj* arg0)
{
    s32 dx;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk50 = ride_chaser_shot_hit_box;
    dx = ride_chaser_shot_offsets[arg0->unk2][0];
    if (arg0->unk15 != 0)
        dx = -dx;
    arg0->x_pos.i.hi += dx;
    arg0->y_pos.i.hi += ride_chaser_shot_offsets[arg0->unk2][1];
    set_velocity_from_angle(MOVING_OBJECT(arg0), ride_chaser_shot_angles[arg0->unk2]);
    arg0->unk60 = 3;
    arg0->x_vel.val <<= 3;
    arg0->unk5C = 1;
    arg0->y_vel.val <<= 3;
    set_animation(arg0, ride_chaser_shot_animations[arg0->unk2]);
}

extern union AnimationStep* wave_rider_animations[27];
extern struct Unk_unk68 wave_rider_terrain_box;
extern struct Unk_unk68 wave_rider_attack_box;
extern struct Unk_unk68 D_80107878[];
void wave_rider_move(struct MainObj*);
s32 wave_rider_check_camera(struct MainObj*);

void func_8006AF70(struct MainObj* arg0)
{
    struct ShotObj* shot;
    struct VisualObj* visual;

    arg0->ext.main_53.unk84 = 0;
    switch (arg0->unk2) {
    case 0:
    case 1:
    case 2:
        arg0->x_speed = 0x80000;
        arg0->unk5 = 1;
        break;
    case 3:
        arg0->x_speed = 0x54000;
        arg0->unk5 = 2;
        arg0->state++;
        break;
    default:
        arg0->x_speed = 0x54000;
        arg0->unk5 = 5;
        arg0->state++;
        break;
    }
    arg0->unk15 = arg0->unk2 == 4 ? 0 : 0x40;
    arg0->ext.main_53.unk80 = func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi,
        (s16)(arg0->y_pos.i.hi + 0x20));
    arg0->animation_table = (const u8* const*)wave_rider_animations;
    arg0->terrain_box = &wave_rider_terrain_box;
    arg0->attack_box = &wave_rider_attack_box;
    arg0->unk7C = 0x3C;
    arg0->collision_data = D_80107878;
    arg0->unk16 = 5;
    arg0->invincibility_timer = 0;
    arg0->unk62 = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->hp = 6;
    arg0->contact_damage = 5;
    arg0->air_state = 0;
    arg0->bg_offset = g_Player.bg_offset;
    set_animation(arg0, 0);
    if (arg0->unk2 == 0) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x1C;
            shot->unk2 = 0;
            shot->unk7C = WEAPON_OBJECT(arg0);
        }
    }
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 0x15;
        visual->unk50 = PLAYER_OBJECT(arg0);
    }
}

u8 func_8006B1C4(struct MainObj* arg0, u8 side)
{
    const struct Unk_unk68* bounds = arg0->terrain_box;
    s32 x;
    s32 y;
    u8 tile;

    if (arg0->unk15 == 0)
        x = arg0->x_pos.i.hi + bounds->unk0;
    else
        x = arg0->x_pos.i.hi - bounds->unk0;
    y = arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3;
    y += side != 0 ? -0xF : 1;
    for (;;) {
        tile = func_8002D724(PLAYER_OBJECT(arg0), (s16)x, (s16)y);
        if (tile != 0x10)
            return tile;
        y -= 0x10;
    }
}

void func_8006B2A4(struct MainObj* arg0)
{
    struct Main53Ext* ext = &arg0->ext.main_53;

    ext->unk81 = func_8006B1C4(arg0, 0);
    arg0->air_state = 0;
    if (ext->unk81 == ext->unk80) {
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }
    switch (ext->unk81) {
    case 0:
        set_animation(arg0, 2);
        arg0->y_speed = 0x68000;
        arg0->gravity = 0x5000;
        arg0->air_state = 1;
        arg0->unk6++;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        set_animation(arg0, 2);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        set_animation(arg0, 1);
        break;
    case 0x38:
        set_animation(arg0, 0);
        break;
    }
    ext->unk80 = ext->unk81;
}

void func_8006B398(struct MainObj* arg0)
{
    struct Main53Ext* ext = &arg0->ext.main_53;
    u8 tile;
    s16 x;
    s16 y;

    animate_object(ANIMATED_OBJECT(arg0));
    tile = func_8006B1C4(arg0, 0);
    ext->unk81 = tile;
    if (arg0->unk7E != 0) {
        arg0->unk7E--;
        return;
    }
    if (tile == 0)
        return;
    if (ext->unk84 != 0)
        arg0->x_speed = arg0->x_pos.val < background_objects[arg0->bg_offset].x_pos.val + 0x400000
            ? 0x80000
            : 0x50000;
    else
        arg0->x_speed = arg0->unk2 == 4 ? 0x10000 : 0x60000;
    arg0->x_accel = 0;
    arg0->air_state = 0;
    arg0->unk6 = 0;
    set_animation(arg0, 0);
    if (ext->unk81 == 0x24)
        return;
    x = arg0->x_pos.i.hi;
    y = arg0->y_pos.i.hi;
    if (arg0->unk15 != 0)
        func_800B10E4(2, (s16)(x - 0x18), (s16)(y + 9), (s16)(x + 0xA), (s16)(y + 0x19), 0x10);
    else
        func_800B10E4(2, (s16)(x + 0x18), (s16)(y + 9), (s16)(x - 0xA), (s16)(y + 0x19), 0x10);
}

void func_8006B5F8(struct MainObj* arg0)
{
    if (wave_rider_check_camera(arg0) != 0) {
        switch (arg0->unk2) {
        case 0:
            arg0->x_speed = 0x60000;
            arg0->unk5 = 3;
            arg0->unk7C = 0x28;
            break;
        case 1:
            set_animation(arg0, 2);
            arg0->x_speed = 0x90000;
            arg0->y_speed = 0x80000;
            arg0->gravity = 0x5000;
            arg0->unk5 = 2;
            arg0->air_state = 1;
            arg0->unk6 = 1;
            arg0->unk7E = 2;
            break;
        }
    }
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x20);
}

void func_8006B6B0(struct MainObj* arg0)
{
    u8 tile;
    s32 animation;

    arg0->ext.main_53.unk84 = 0;
    wave_rider_move(arg0);
    if (arg0->unk7C != 0) {
        arg0->unk7C--;
        update_on_screen(BASE_OBJECT(arg0), 0x30, 0x20);
        return;
    }
    if (arg0->air_state != 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x30, 0x20);
        return;
    }
    tile = func_8006B1C4(arg0, 0);
    arg0->ext.main_53.unk81 = tile;
    if (tile == 0)
        animation = 3;
    else if (tile < 5)
        animation = 5;
    else if (tile < 9)
        animation = 4;
    else
        animation = 3;
    set_animation(arg0, animation);
    arg0->unk5 = 4;
    arg0->x_speed = 0x80000;
    arg0->x_accel = 0;
    arg0->air_state = 1;
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x20);
}

extern union AnimationStep* sentry_drone_animations[13];
extern u8 D_800FFAD0[4];
extern u8 D_800FFAD4[4];
extern s8 D_800FFACC[4];
extern u32 D_801076F8[];

void func_8006738C(struct MainObj* arg0)
{
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    resource = func_8002938C(0x30);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x30);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    clut_x = func_8002938C(0x30);
    clut_y = func_8002938C(0x30);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    arg0->animation_table = (const u8* const*)sentry_drone_animations;
    arg0->unk16 = 4;
    arg0->terrain_box = (struct Unk_unk68*)D_800FFAD0;
    arg0->attack_box = D_800FFAD4;
    arg0->hurt_box = D_800FFACC;
    arg0->collision_data = D_801076F8;
    arg0->air_state = 0;
    arg0->invincibility_timer = 0;
    arg0->hp = 5;
    arg0->contact_damage = 3;
    arg0->state = 1;
    arg0->unk6 = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.unk81 = get_random() & 3;
    if (arg0->unk2 & 0x80) {
        set_animation(arg0, 0);
        arg0->unk5 = 2;
        arg0->air_state = 1;
    } else {
        arg0->unk15 = 0;
        set_animation(arg0, 0);
        arg0->air_state = 0;
        arg0->unk5 = 3;
    }
    if ((arg0->unk2 & 0xF) == 1)
        arg0->state = 3;
}

static void main_48_face_toward(struct MainObj* arg0, s32 initial_face)
{
    s8 direction = SP_CUR_MAIN_OBJ->ext.main_48.collision_result;
    s32 animation = -1;

    switch ((u32)(direction & 0xFE)) {
    case 0:
        arg0->unk15 = 0x40;
        if (!initial_face)
            animation = 1;
        break;
    case 2:
    case 4:
    case 6:
        arg0->unk15 = 0x40;
        /* fallthrough */
    case 10:
    case 12:
    case 14:
        if (direction >= 0xA)
            arg0->unk15 = 0;
        animation = 4;
        break;
    case 8:
        animation = 2;
        break;
    case 16:
        arg0->unk15 = 0;
        if (!initial_face)
            animation = 1;
        break;
    case 18:
    case 20:
    case 22:
        arg0->unk15 = 0;
        /* fallthrough */
    case 26:
    case 28:
    case 30:
        if (direction >= 0x1A)
            arg0->unk15 = 0x40;
        animation = 5;
        break;
    case 24:
        animation = 3;
        break;
    }
    if (animation >= 0)
        set_animation(arg0, animation);
    arg0->unk6++;
}

void func_800678F8(struct MainObj* arg0)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_48.unk80 != 0)
        return;
    if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi > 0)
        arg0->unk15 = 0x40;
    SP_CUR_MAIN_OBJ->ext.main_48.collision_result
        = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    main_48_face_toward(arg0, 1);
}

void func_80067DAC(struct MainObj* arg0)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_48.unk80 != 0)
        return;
    main_48_face_toward(arg0, 0);
}

void func_800681C4(struct MainObj* arg0)
{
    struct Main48Ext* ext = &SP_CUR_MAIN_OBJ->ext.main_48;

    ext->unk88 = ext->collision_result & 0xFE;
    switch ((u32)((s8)ext->collision_result & 0xFE)) {
    case 0:
        ext->unk86 = 0x1E;
        ext->unk87 = 2;
        break;
    case 2:
    case 4:
    case 6:
        ext->unk86 = 0;
        ext->unk87 = 8;
        break;
    case 8:
        ext->unk86 = 6;
        ext->unk87 = 0xA;
        break;
    case 10:
    case 12:
    case 14:
        ext->unk86 = 8;
        ext->unk87 = 0x10;
        break;
    case 16:
        ext->unk86 = 0xE;
        ext->unk87 = 0x12;
        break;
    case 18:
    case 20:
    case 22:
        ext->unk86 = 0x10;
        ext->unk87 = 0x18;
        break;
    case 24:
        ext->unk86 = 0x16;
        ext->unk87 = 0x1A;
        break;
    case 26:
    case 28:
    case 30:
        ext->unk86 = 0x18;
        ext->unk87 = 0;
        break;
    }
}

void func_80068340(struct MainObj* arg0)
{
    struct Main48Ext* ext = &SP_CUR_MAIN_OBJ->ext.main_48;

    switch ((u32)(s8)(ext->unk82 - 1)) {
    case 0:
    case 4:
        ext->collision_result = ext->unk86;
        break;
    case 2:
    case 6:
        ext->collision_result = ext->unk87;
        break;
    case 1:
    case 3:
    case 5:
    case 7:
        ext->collision_result = ext->unk88;
        break;
    }
}

extern u8 sentry_shot_hit_boxes[8];
extern u8 sentry_shot_terrain_box[4];
extern s8 sentry_shot_spawn_offsets[16];

static s32 main_48_direction_pair(s8 direction, u8 facing)
{
    switch (direction & 0xFE) {
    case 2:
    case 4:
    case 6:
        return 3;
    case 8:
        return 4;
    case 10:
    case 12:
    case 14:
        return 2;
    case 18:
    case 20:
    case 22:
        return 6;
    case 24:
        return 5;
    case 26:
    case 28:
    case 30:
        return 7;
    default:
        return (facing & 0x40) ? 1 : 0;
    }
}

extern union AnimationStep* ice_block_animations[9];
extern struct Unk_unk68 D_80106C74[];
extern struct Unk_unk68 D_800FC844;
extern struct Unk_unk68 D_800FC848;
extern struct Unk_unk68 D_800FC84C;
extern struct Unk_unk68 D_800FC850;
extern struct Unk_unk68 D_800FC854;
extern struct Unk_unk68 D_800FC858;
extern struct Unk_unk68 D_800FC85C;
extern u8 ice_block_debris[4];
extern union AnimationStep* ice_wall_animations[];

void func_800545EC(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->state++;
    arg0->animation_table = (const u8* const*)ice_block_animations;
    arg0->unk16 = 6;
    arg0->collision_data = D_80106C74;
    arg0->unk15 = 0;
    arg0->terrain_box = NULL;
    arg0->invincibility_timer = 0;
    arg0->hp = 9;
    arg0->contact_damage = 3;
    arg0->ext.main_20.unk80 = 9;
    arg0->ext.main_20.unk81 = 2;
    arg0->bg_offset = g_Player.bg_offset;
    if (arg0->unk2 != 0) {
        arg0->attack_box = &D_800FC844;
        arg0->hurt_box = &D_800FC848;
    } else {
        arg0->attack_box = NULL;
        arg0->hurt_box = &D_800FC84C;
    }
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk7C = 0;
    arg0->x_pos.i.hi = (arg0->x_pos.i.hi & ~0xF) + 8;
    arg0->y_pos.i.hi = (arg0->y_pos.i.hi & ~0xF) + 0x14;
    set_animation(arg0, 0);
    update_on_screen(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800548B8(struct MainObj* arg0)
{
    struct WeaponObj* weapon;
    u8 flags = 0;
    u8 top;
    u8 bottom;

    if (arg0->unk2 == 0) {
        func_800583B0(arg0, arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi - 0x10), 0xA);
        top = func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi - 0x30));
        bottom = func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi + 0x30));
        if (top >= 0x30) {
            if (top < 0x32 || top == 0x3C)
                func_800583B0(arg0, arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi - 0x40), 0xA);
            else if (top == 0x38)
                flags = 1;
        }
        if (bottom >= 0x30) {
            if (bottom < 0x32 || bottom == 0x3C)
                func_800583B0(arg0, arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi + 0x20), 0xA);
            else if (bottom == 0x38)
                flags += 2;
        }
    }
    switch (flags) {
    case 1:
        set_animation(arg0, 7);
        arg0->attack_box = &D_800FC850;
        break;
    case 2:
        set_animation(arg0, 6);
        arg0->attack_box = &D_800FC854;
        break;
    case 3:
        arg0->unk7C = 1;
        arg0->attack_box = &D_800FC858;
        break;
    default:
        set_animation(arg0, 8);
        arg0->attack_box = &D_800FC85C;
        break;
    }
    weapon = find_free_weapon_obj();
    if (weapon != NULL) {
        weapon->active = 1;
        weapon->id = 0x3A;
        weapon->owner = PLAYER_OBJECT(arg0);
        weapon->state = 0;
        weapon->unk5 = 0;
        weapon->unk6 = 0;
        weapon->unk2 = flags;
    }
    arg0->unk5++;
    spawn_explosion(BASE_OBJECT(arg0));
    spawn_debris(4, ice_block_debris, arg0);
    if (arg0->unk2 == 0)
        func_800C842C(0xC, ice_wall_debris, arg0, 0x1A, ice_wall_animations);
}

extern s8* D_800FEA24[7];
extern union AnimationStep** D_800FEA40[7];
extern struct Unk_unk68 D_800FEAA0;
extern u8 D_800FEA1C[8];
u8 func_80062338(struct MainObj*);

void func_80061DFC(struct MainObj* arg0)
{
    struct Main40Ext* ext = &arg0->ext.main_40;

    arg0->invincibility_timer = 0;
    ext->unk81 = arg0->unk2 & 0xF;
    ext->unk80 = arg0->unk2 >> 4;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk16 = 6;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->hurt_box = D_800FEA24[ext->unk80];
    arg0->hp = 0;
    arg0->contact_damage = 0;
    arg0->attack_box = NULL;
    arg0->terrain_box = NULL;
    arg0->animation_table = (const u8* const*)D_800FEA40[ext->unk80];
    if (ext->unk80 == 1) {
        set_animation(arg0, 0);
        arg0->hp = 3;
        arg0->contact_damage = 2;
        arg0->terrain_box = &D_800FEAA0;
        arg0->attack_box = D_800FEA24[ext->unk80];
    }
    arg0->collision_data = D_80108504;
    arg0->unk15 = 0;
    arg0->state++;
}

void func_80061F2C(struct MainObj* arg0)
{
    struct Main40Ext* ext = &arg0->ext.main_40;
    s32 collision;
    s32 dy;

    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk18.val = arg0->x_pos.val;
    if (ext->unk80 == 1) {
        func_8002D9BC(arg0);
        collision = func_8002DD04(arg0);
        if (collision >= 0) {
            if (collision > 0)
                arg0->unk42 |= 0x8000;
            else
                arg0->unk42 &= 0x7FFF;
            if (!func_80062338(arg0))
                goto check;
        }
        ext->timer = 0x30;
        ext->trigger_time = 0x2F;
        arg0->on_screen = 0;
        spawn_debris(7, D_800FEA1C, arg0);
        arg0->state++;
        return;
    }
    if (ext->unk80 != 0 && ext->unk80 < 7) {
        dy = breakable_terrain_effect_offsets[(ext->unk80 - 2) * 2 + 1] << 16;
        if (arg0->y_pos.val - dy - background_objects[arg0->bg_offset].y_pos.val > 0xA80000) {
            ext->timer = 0x10;
            ext->trigger_time = 8;
            arg0->state++;
        }
    }
check:
    if (func_8002B160(BASE_OBJECT(arg0)) != 0) {
        despawn_object(OBJECT_HEADER(arg0));
        return;
    }
    if (ext->unk80 == 1)
        is_on_screen(BASE_OBJECT(arg0));
}

static const struct Unk_unk68* psx_null_relative_bounds(const struct Unk_unk68* bounds)
{
    static const struct Unk_unk68 zero;

    return bounds != NULL ? bounds : &zero;
}

u8 func_80062338(struct MainObj* arg0)
{
    const struct Unk_unk68* bounds = psx_null_relative_bounds(arg0->terrain_box);
    const struct Unk_unk68* player_bounds = psx_null_relative_bounds(g_Player.unk68);
    s16 edge = arg0->x_pos.i.hi + bounds->unk0;
    s16 player_edge = g_Player.x_pos.i.hi + player_bounds->unk0;
    s16 distance = edge - player_edge >= 0 ? (s16)(edge - player_edge) : (s16)(player_edge - edge);

    return distance <= bounds->unk2 + player_bounds->unk2;
}

extern u8 flame_pillar_tall_box[4];

void func_800A0170(struct ShotObj* arg0)
{
    struct WeaponObj* owner;
    s32 resource;
    s32 clut_x;
    s32 clut_y;

    arg0->state++;
    arg0->unk60 = 6;
    arg0->unk15 = 0;
    arg0->unk16 = 1;
    arg0->unk68 = NULL;
    arg0->unk58.data = NULL;
    arg0->unk61 = 0;
    arg0->unk5C = 1;
    arg0->animation_table = (u32**)ice_block_animations;
    arg0->bg_offset = g_Player.bg_offset;
    clut_x = func_8002938C(0x14);
    clut_y = func_8002938C(0x14);
    arg0->unk42 = ((clut_x * 4 + 0x18) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
    resource = func_8002938C(0x14);
    arg0->unk40 = D_801406A8[resource] >> 7;
    resource = func_8002938C(0x14);
    owner = arg0->unk7C;
    arg0->unk16 = 1;
    arg0->unk54 = NULL;
    arg0->unk68 = NULL;
    arg0->unk58.data = NULL;
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->x_pos.val = owner->x_pos.val + (arg0->unk2 != 0 ? 0x300000 : 0x100000);
    arg0->unk50.data = flame_pillar_tall_box;
    arg0->y_pos.val = owner->y_pos.val + 0x80000;
    set_animation(arg0, 8);
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_800BD080(struct EffectObj* arg0)
{
    struct MainObj* main;
    s32 x;
    s32 y;
    u32 i;

    if (--arg0->ext.unk_effect.unk14 != 0)
        return;
    x = background_objects[0].x_pos.u.hi + (u16)arg0->ext.effect_4.unk16;
    y = background_objects[0].y_pos.i.hi + (arg0->ext.unk_effect.unk15 != 0 ? 0x20 : 0x10);
    for (i = 0; i < 5; i++) {
        main = find_free_main_obj();
        if (main == NULL)
            continue;
        main->active = 0x21;
        main->id = 0x3B;
        main->unk2 = 0;
        main->x_pos.i.hi = x + (get_random() & 0xF);
        main->y_pos.i.hi = y + (get_random() & 0x1F);
        y += 0x20;
        main->unk7C = get_random() & 0xF;
    }
    arg0->ext.unk_effect.unk14 = 7;
    arg0->ext.unk_effect.unk15 ^= 1;
    if ((s16)arg0->ext.effect_4.unk16 < 0x70)
        arg0->ext.effect_4.unk16 += 3;
}

void func_800CE114(struct MiscObj* arg0)
{
    const u8* rows = (const u8*)arg0->ext.unk.unk50;

    arg0->unk40 = 0x1E00;
    arg0->animation_table = (u32**)option_toggle_animations;
    arg0->bg_offset = -1;
    arg0->unk42 = 0x7806;
    arg0->unk15 = 0;
    arg0->unk3C = WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[2];
    arg0->x_pos.i.hi += 8;
    arg0->y_pos.i.hi = rows[main_bss_state.transition.selection * 2 + 2] + 8;
    arg0->unk16 = 0x10;
    arg0->state++;
    arg0->ext.unk.unk54 = main_bss_state.transition.selection;
    set_animation(arg0, 0);
    is_on_screen(BASE_OBJECT(arg0));
}

static int misc_32_cancelled(s8 mode)
{
    return (controller_input.pressed & PAD_SELECTION_ALT) || ((controller_input.pressed & 0x800) && game_info.unk0 == mode);
}

void func_800CE1D4(struct MiscObj* arg0)
{
    const u8* rows = (const u8*)arg0->ext.unk.unk50;

    if (arg0->ext.unk.unk55 == 0) {
        if (arg0->unk2 == -1 || misc_32_cancelled(0xA))
            arg0->unk2 = -1;
        if (arg0->unk2 == -1 || misc_32_cancelled(8))
            arg0->unk2 = -1;
    }
    if (arg0->unk2 != -1 && (u8)arg0->ext.unk.unk54 != main_bss_state.transition.selection) {
        arg0->y_pos.i.hi = rows[main_bss_state.transition.selection * 2 + 2] + 8;
        arg0->ext.unk.unk54 = main_bss_state.transition.selection;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

extern union AnimationStep* D_800F9428[31];
extern union AnimationStep* D_800F965C[38];
extern struct Unk_unk68 D_800F9120;
extern struct Unk_unk68 D_800F9128;
extern void (*D_800F9150[])(struct RideArmorObj*);
extern void (*D_800F9188[])(struct RideArmorObj*);
void func_8003DC44(struct BaseObj*, s8);
void func_8003DC1C(struct PlayerObj*, s8);
void func_8003D638(struct VisualObj*, u8);
s32 func_8003DE08(struct MainObj*);
void func_8003DDDC(struct PlayerObj*);
void func_800401F8(struct PlayerObj*);
void func_800400C8(struct PlayerObj*);
void func_800402C4(struct PlayerObj*);
void func_8003FF9C(struct RideArmorObj*);
void func_8003DF9C(struct PlayerObj*);
s32 func_8003DC8C(struct RideArmorObj*);
s32 func_8003DC50(struct RideArmorObj*);
void func_8003DD14(struct MainObj*);
void func_8003DD2C(struct MainObj*);
void func_8003DD54(struct RideArmorObj*);
void func_8003DDA0(struct RideArmorObj*);
void func_8003D7A0(void);
s32 func_8003E048(struct PlayerObj*);
void func_8003D9E0(struct RideArmorObj*);
void func_8003DE84(struct RideArmorObj*);
void func_80040248(struct RideArmorObj*);

#define RIDE_ARMOR_STATE(object, state) func_8003DC44(BASE_OBJECT(object), (state))
#define RIDE_ARMOR_FLAGS(object) ((object)->unk94.bytes.unk97)

void func_8003D4C8(struct RideArmorObj* arg0)
{
    u8 resource;

    arg0->on_screen = 1;
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->bg_offset = 0;
    arg0->unk15 = 0;
    arg0->active |= 0x40;
    arg0->animation_table = (u32**)(arg0->unk2 != 0 ? D_800F965C : D_800F9428);
    resource = func_8002938C(0x86);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk40 = D_801406A8[resource] >> 7;
    arg0->unk42 = SOME_COORDINATE_CONVERSION(resource);
    arg0->unk5C = 0x20;
    arg0->unk16 = 3;
    arg0->unk68 = &D_800F9124;
    arg0->unk60 = 0;
    arg0->unk61 = 0;
    arg0->unk67 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk54 = NULL;
    arg0->unk50 = NULL;
    arg0->unk58 = NULL;
    arg0->unk7D = 0;
    arg0->unk7E = 0;
    arg0->unk80.bytes.unk83 = 0;
    arg0->unk80.bytes.unk82 = 0;
    arg0->unk7C = 1;
    arg0->unk86 = 0;
    arg0->unk80.bytes.unk81 = 0;
    arg0->unk80.bytes.unk80 = 0;
    arg0->spawned_parts = 0;
    RIDE_U8(arg0, 0x8E) = 0;
    RIDE_U8(arg0, 0x8D) = 0;
    RIDE_U8(arg0, 0x93) = 0;
    RIDE_ARMOR_FLAGS(arg0) = 0;
    arg0->unkA6 = 0;
    RIDE_U8(arg0, 0x8C) = 0;
    arg0->pad87 = 0;
}

void func_8003D8A8(struct RideArmorObj* arg0, s32 kind, s32 variant)
{
    struct WeaponObj* weapon;
    u8 resource;

    if (arg0->unk86 >= 3)
        return;
    weapon = find_free_weapon_obj();
    if (weapon == NULL)
        return;
    weapon->active = 0x41;
    weapon->id = variant + 0x3B;
    weapon->unk2 = kind;
    weapon->x_pos.i.hi = arg0->x_pos.i.hi;
    weapon->y_pos.i.hi = arg0->y_pos.i.hi;
    weapon->animation_table = arg0->animation_table;
    weapon->unk40 = arg0->unk40;
    weapon->unk3C = arg0->unk3C;
    resource = func_8002938C(0x86);
    weapon->unk42 = SOME_COORDINATE_CONVERSION(resource);
    weapon->owner = (struct PlayerObj*)arg0;
    weapon->unk16 = arg0->unk16;
    weapon->unk15 = arg0->unk15;
    if ((u8)variant == 0)
        arg0->unk86++;
}

void func_8003D9E0(struct RideArmorObj* arg0)
{
    u16 mode;
    u8 parts;
    u32 i;

    if (RIDE_ARMOR_FLAGS(arg0) & 2)
        return;
    mode = RIDE_U16(arg0, 0x96) & 0xC000;
    if (mode == 0x8000)
        return;
    switch (RIDE_U8(arg0, 0x94)) {
    case 0:
        if (arg0->collision_flags & 0x30) {
            RIDE_U8(arg0, 0x94) = 1;
            RIDE_U8(arg0, 0x95) = 0x3C;
            arg0->unkA6 = arg0->collision_flags & 0x30;
        }
        return;
    case 1:
        if (!(arg0->collision_flags & arg0->unkA6)) {
            RIDE_U8(arg0, 0x94) = 0;
            arg0->unkA6 = 0;
            return;
        }
        if (--RIDE_U8(arg0, 0x95) != 0)
            return;
        RIDE_U8(arg0, 0x94) = 2;
        if (arg0->unk2 == 0 || mode != 0x4000)
            return;
        func_8003D6EC(ANIMATED_OBJECT(arg0), 0x10);
        func_8001540C(5, 8, NULL);
        return;
    case 2:
        if (arg0->collision_flags & arg0->unkA6)
            return;
        if (arg0->unk2 == 0 || mode != 0x4000) {
            RIDE_U8(arg0, 0x94) = 0;
            arg0->unkA6 = 0;
            stop_sound(5, 8);
            return;
        }
        switch ((u8)arg0->unk5) {
        case 3:
        case 6:
        case 9:
        case 0xA:
        case 0xB:
        case 0xD:
        case 0x10:
        case 0x11:
            RIDE_U8(arg0, 0x94) = 0;
            arg0->unkA6 = 0;
            stop_sound(5, 8);
            return;
        }
        parts = arg0->spawned_parts;
        for (i = 0; i < 3; i++) {
            if (!(parts & 1)) {
                func_8003D8A8(arg0, i, 1);
                arg0->spawned_parts |= 1 << i;
            }
            parts >>= 1;
        }
        arg0->unk7E = 0x10;
        func_8001540C(5, 6, NULL);
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
        return;
    }
}

s32 func_8003DCD8(struct RideArmorObj* arg0)
{
    if (!(arg0->unk8A & 0x30))
        return 0;
    if (arg0->unk2 == 0)
        return 1;
    return arg0->unk7E == 0;
}

void func_8003E274(struct RideArmorObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
        arg0->unk68 = &D_800F9120;
        set_animation(arg0, 0x12);
        func_8003DC1C((struct PlayerObj*)arg0, 0x39);
        func_8001540C(5, arg0->id != 0 ? 4 : 6, NULL);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        if (RIDE_U8(arg0, 0x8C) == 0)
            arg0->unk61 = 0;
        RIDE_U8(arg0, 0x94) = 0;
        arg0->unkA6 = 0;
        RIDE_ARMOR_STATE(arg0, 1);
        arg0->unk54 = &D_800F9128;
        return;
    }
    if (arg0->animation_step.fields.event & 1) {
        func_8003D638((struct VisualObj*)arg0, 7);
        arg0->animation_step.fields.event = 0;
        return;
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_80040248(struct RideArmorObj* arg0)
{
    u8 count;

    if (!(RIDE_ARMOR_FLAGS(arg0) & 0x80))
        return;
    arg0->unk42 &= 0x7FFF;
    if (--RIDE_U8(arg0, 0x92) != 0)
        return;
    count = RIDE_U8(arg0, 0x91);
    RIDE_U8(arg0, 0x91) = count - 1;
    arg0->unk42 |= 0x8000;
    RIDE_U8(arg0, 0x92) = count;
    if ((u8)(count - 1) != 0)
        return;
    RIDE_U8(arg0, 0x8D) = 1;
    arg0->unk42 &= 0x7FFF;
}

void func_800403DC(struct RideArmorObj* arg0)
{
    u8 flags;

    arg0->on_screen = 0;
    if (func_8002B160(BASE_OBJECT(arg0)) != 0)
        return;
    if (arg0->unk5C < 0) {
        if (arg0->unk5C == -0x80) {
            RIDE_U8(arg0, 0x92) = 0x1E;
            RIDE_U8(arg0, 0x91) = 0x1E;
            RIDE_U8(arg0, 0x8C) = 0;
            RIDE_ARMOR_FLAGS(arg0) |= 0x80;
        }
        arg0->launch_speed = 0x400;
        RIDE_U8(arg0, 0x8C) = 0x79;
        func_8003D638((struct VisualObj*)arg0, 8);
        RIDE_U8(arg0, 0x93) = 1;
        arg0->unk85 = 1;
        RIDE_ARMOR_FLAGS(arg0) |= 2;
    }
    if (RIDE_U8(arg0, 0x8C) != 0 && --RIDE_U8(arg0, 0x8C) == 0 && (RIDE_ARMOR_FLAGS(arg0) & 1))
        g_Player.on_screen = 1;
    flags = RIDE_ARMOR_FLAGS(arg0);
    if ((flags & 0x41) == 0x41 || (engine_obj.unkF != 0 && (flags & 0x40))) {
        RIDE_ARMOR_FLAGS(arg0) = flags ^ 1;
        RIDE_ARMOR_STATE(arg0, 0xB);
    }
    func_8003DE84(arg0);
    func_8003DF9C((struct PlayerObj*)arg0);
    func_8003D9E0(arg0);
    if (RIDE_U8(arg0, 0x8D) == 0) {
        if (arg0->unk2 == 0) {
            if ((u8)arg0->unk5 < 14)
                D_800F9150[(u8)arg0->unk5](arg0);
            else if ((u8)arg0->unk5 < 32)
                D_800F9188[(u8)arg0->unk5 - 14](arg0);
        } else {
            if (arg0->unk7E != 0)
                arg0->unk7E--;
            D_800F9188[arg0->unk5](arg0);
        }
        func_8003FF9C(arg0);
        CollisionRelated((struct PlayerObj*)arg0);
        if (RIDE_ARMOR_FLAGS(arg0) & 0x40)
            func_8003DDDC((struct PlayerObj*)arg0);
        func_800401F8((struct PlayerObj*)arg0);
        func_80040248(arg0);
        func_8002B3C0(BASE_OBJECT(arg0));
    }
    func_800400C8((struct PlayerObj*)arg0);
    func_800402C4((struct PlayerObj*)arg0);
}

static u16 misc_31_palette(struct MiscObj* arg0)
{
    return arg0->unk2 == 3 && D_800F1D90.save.character == 0xFF ? 0x7804 : 0x7800;
}

void func_800CDE44(struct MiscObj* arg0)
{
    arg0->unk40 = 0x1F00;
    arg0->bg_offset = -1;
    arg0->unk3C = WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[0];
    arg0->unk15 = 0;
    arg0->unk42 = arg0->y_pos.i.hi == 0x10 ? 0x7802 : misc_31_palette(arg0);
    arg0->x_pos.i.hi = 0xA0;
    arg0->unk16 = 0x10;
    if ((u8)(arg0->unk2 - 0x56) < 2) {
        arg0->state += 2;
        arg0->ext.misc_31.animation = D_80171EA9;
        arg0->animation_step.fields.frame_index = D_80171EA9 != 0 ? 0x56 : 0x57;
    } else {
        arg0->state++;
        arg0->animation_step.fields.frame_index = arg0->unk2;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800CDF4C(struct MiscObj* arg0)
{
    if (arg0->y_pos.i.hi != 0x10) {
        if (arg0->ext.title_logo.palette_shift_value == 0) {
            if (arg0->unk2 == -1 || misc_32_cancelled(0xA))
                arg0->unk2 = -1;
            if (arg0->unk2 == -1 || misc_32_cancelled(8))
                arg0->unk2 = -1;
            if (arg0->unk2 == -1) {
                is_on_screen(BASE_OBJECT(arg0));
                return;
            }
        }
        if (arg0->unk7 == main_bss_state.transition.selection)
            arg0->unk42 = 0x7803;
        else
            arg0->unk42 = misc_31_palette(arg0);
    }
    is_on_screen(BASE_OBJECT(arg0));
}

extern u8 ride_armor_shot_hit_box[4];
extern s16 ride_armor_shot_offsets[2][2];

void func_80098AF8(struct WeaponObj* arg0)
{
    s32 dx;
    s32 direction;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 3;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk50 = ride_armor_shot_hit_box;
    dx = (u16)ride_armor_shot_offsets[arg0->unk2][0];
    if (arg0->unk15 != 0)
        dx = -dx;
    arg0->x_pos.i.hi += dx;
    arg0->y_pos.i.hi += ride_armor_shot_offsets[arg0->unk2][1];
    if (arg0->unk2 == 0)
        direction = arg0->unk15 == 0 ? 0x10 : 0;
    else
        direction = arg0->unk15 != 0 ? 0x1C : 0x14;
    set_velocity_from_angle(MOVING_OBJECT(arg0), direction);
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->x_vel.val <<= 3;
    arg0->y_vel.val <<= 3;
    set_animation(arg0, arg0->unk2 + 0x1F);
}

static s32 weapon_59_distance(s32 x0, s32 y0, s32 x1, s32 y1)
{
    s32 dx = x0 - x1;
    s32 dy = y0 - y1;

    if (dx < 0)
        dx = x1 - x0;
    if (dy < 0)
        dy = y1 - y0;
    return dx + dy;
}

void func_80098DA0(struct WeaponObj* arg0)
{
    struct MainObj* main;
    struct MainObj* target;
    s32 found = 0;

    for (main = main_objects; main < main_objects + COUNT(main_objects); main++) {
        if (main->active == 0 || main->on_screen == 0 || main->unk7A != 0)
            continue;
        target = arg0->ext.target;
        if (target == NULL
            || weapon_59_distance(arg0->x_pos.val, arg0->y_pos.val, main->x_pos.val, main->y_pos.val)
                < weapon_59_distance(arg0->x_pos.val, arg0->y_pos.val, target->x_pos.val, target->y_pos.val))
            arg0->ext.target = main;
        found = 1;
    }
    if (!found)
        arg0->ext.target = NULL;
}

void func_80098EA8(struct WeaponObj* arg0)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return;
    visual->id = 0x16;
    visual->unk2 = 0;
    visual->active = arg0->active;
    visual->x_pos.i.hi = arg0->x_pos.i.hi;
    visual->y_pos.i.hi = arg0->y_pos.i.hi;
    visual->animation_table = arg0->animation_table;
    visual->unk40 = arg0->unk40;
    visual->unk3C = arg0->unk3C;
    visual->unk42 = arg0->unk42;
    visual->unk50 = (struct PlayerObj*)arg0;
    visual->unk16 = arg0->unk16;
    visual->unk15 = arg0->unk15;
}

extern u8 ride_armor_missile_hit_box[4];
extern struct Weapon60SpawnOffset ride_armor_missile_offsets[3];

void func_80098F88(struct WeaponObj* self)
{
    u8 direction;
    struct Weapon60SpawnOffset offset = ride_armor_missile_offsets[self->unk2];

    self->state = 1;
    self->on_screen = 1;
    self->unk16 = 0;
    self->unk68 = NULL;
    self->unk54 = NULL;
    self->unk50 = ride_armor_missile_hit_box;
    self->x_pos.i.hi += self->unk15 == 0 ? offset.x : -offset.x;
    self->y_pos.i.hi += offset.y;

    switch (self->unk2) {
    case 0:
        direction = self->unk15 == 0 ? 0x10 : 0;
        break;
    case 1:
        direction = self->unk15 == 0 ? 0x14 : 0x1C;
        break;
    case 2:
        direction = self->unk15 == 0 ? 0xC : 4;
        break;
    default:
        direction = 0;
        break;
    }
    self->ext.weapon_60.direction = direction;
    set_velocity_from_angle(MOVING_OBJECT(self), direction);
    self->unk5C = 1;
    self->unk60 = 3;
    self->unk88.half = 8;
    self->unk28.val = 0;
    self->unk2C = 0;
    *(s16*)self->pad8A = 1;
    self->ext.target = NULL;
    self->unk84.word = 0;
    self->x_vel.val *= 6;
    self->y_vel.val *= 6;
    set_animation(self, 0x21);
}

void func_80099118(struct WeaponObj* arg0)
{
    s32 target_direction;
    s16 trail;

    if ((s16)arg0->unk88.half != 0) {
        arg0->unk88.half--;
        arg0->unk84.word = 0;
    }
    if (!(main_bss_state.frame_counter & 1) && (s16)arg0->unk88.half == 0) {
        if (++arg0->unk84.word >= 0x1E0)
            arg0->unk88.half = 0x3C;
        func_80098DA0(arg0);
        if (arg0->ext.target != NULL) {
            target_direction = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(arg0->ext.target));
            if (((arg0->ext.weapon_60.direction - (u8)target_direction) & 0x1F) >= 2) {
                if (((target_direction - arg0->ext.weapon_60.direction) & 0x1F) < 0x10)
                    arg0->ext.weapon_60.direction += 2;
                else
                    arg0->ext.weapon_60.direction -= 2;
                arg0->ext.weapon_60.direction &= 0x1F;
            }
            set_velocity_from_angle(MOVING_OBJECT(arg0), arg0->ext.weapon_60.direction);
            arg0->x_vel.val *= 6;
            arg0->y_vel.val *= 6;
        }
    }
    trail = *(s16*)arg0->pad8A;
    if (trail == 0) {
        func_80098EA8(arg0);
        *(s16*)arg0->pad8A = 1;
    } else {
        *(s16*)arg0->pad8A = trail - 1;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) != 0 || arg0->unk98 != 0) {
        arg0->state = 2;
        arg0->on_screen = 0;
        arg0->unk50 = NULL;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x10, 0x10);
}

extern u8 cannon_missile_boxes[8];
extern s32 cannon_missile_speeds[2];
extern s32 cannon_missile_accels[4];
extern void (*cannon_missile_step_funcs[])(struct ShotObj*);

void func_8009F674(struct ShotObj* arg0)
{
    struct MainObj* owner;
    s32 dx;

    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 5;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk50.data = cannon_missile_boxes;
    arg0->unk54 = cannon_missile_boxes;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk68 = NULL;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    owner = (struct MainObj*)arg0->unk7C;
    dx = arg0->unk15 != 0 ? -0x1A : 0x1A;
    arg0->x_pos.i.hi = owner->x_pos.i.hi + dx;
    arg0->y_pos.i.hi = owner->y_pos.i.hi + (arg0->unk2 == 0 ? -0x23 : -0x10);
    set_animation(arg0, 7);
    arg0->unk8C.bytes[3] = 0x20;
    arg0->unk5 = 0;
    arg0->unk8C.bytes[1] = 0;
    arg0->unk8C.bytes[2] = 0;
    arg0->unk90.bytes[2] = 0;
    arg0->unk90.bytes[0] = 2;
    arg0->unk90.bytes[1] = 0;
    arg0->unk8C.bytes[0] = arg0->unk2 * 20 + 0x1E;
}

void func_8009F7C0(struct ShotObj* arg0)
{
    s32 speed;

    cannon_missile_step_funcs[arg0->unk5](arg0);
    animate_object(ANIMATED_OBJECT(arg0));
    move_with_gravity(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (func_8002DD04((struct MainObj*)arg0) < 0) {
        spawn_explosion(BASE_OBJECT(arg0));
        arg0->state++;
        return;
    }
    speed = arg0->x_vel.val;
    if (speed < 0)
        speed = -speed;
    if (speed > 0x40000)
        arg0->unk28 = 0;
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x20) != 0) {
        arg0->state++;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_8009F89C(struct ShotObj* arg0)
{
    u8 timer = arg0->unk8C.bytes[3];
    u8 blink;

    if (timer == 0) {
        arg0->x_vel.val = cannon_missile_speeds[(arg0->unk15 & 0x40) ? 1 : 0];
        arg0->y_vel.val = cannon_missile_accels[arg0->unk2 != 0 ? 1 : 0];
        arg0->unk42 &= 0x7FFF;
        arg0->unk5++;
        return;
    }
    arg0->unk8C.bytes[3] = timer - 1;
    blink = arg0->unk90.bytes[0];
    arg0->unk90.bytes[0] = blink - 1;
    if (blink == 0) {
        arg0->unk90.bytes[0] = 2;
        arg0->unk42 &= 0x7FFF;
    } else {
        arg0->unk42 |= 0x8000;
    }
}

extern struct Unk_unk68 D_801077F8[];
extern union AnimationStep* jump_shooter_animations[28];
extern struct Unk_unk68 jump_shooter_hurt_box;
extern struct Unk_unk68 jump_shooter_attack_box;
extern struct Unk_unk68 jump_shooter_terrain_box;

void func_8006A55C(struct MainObj* arg0)
{
    arg0->hp = 9;
    arg0->contact_damage = 3;
    arg0->invincibility_timer = 0;
    arg0->collision_data = D_801077F8;
    arg0->animation_table = (const u8* const*)jump_shooter_animations;
    arg0->unk16 = 6;
    arg0->terrain_box = &jump_shooter_terrain_box;
    arg0->hurt_box = &jump_shooter_hurt_box;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->attack_box = &jump_shooter_attack_box;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    jump_shooter_face_player(ANIMATED_OBJECT(arg0));
    arg0->unk7C = 0x5A;
    arg0->ext.main_52.unk80 = 0;
    arg0->ext.main_52.unk8C = 0;
    arg0->state = 1;
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_8006AAB4(struct MainObj* arg0)
{
    struct Unk_unk68* bounds;
    s16 x;
    s16 y;
    s32 dy;

    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    bounds = arg0->terrain_box;
    y = arg0->y_pos.i.hi + bounds->unk1 + (u8)bounds->unk3 + 0x10;
    x = arg0->x_pos.i.hi + bounds->unk0;
    x = arg0->unk15 == 0 ? x - 0x10 : x + 0x10;
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0) {
        set_animation(arg0, 1);
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    if (arg0->unk15 == 0) {
        if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi > 0x40) {
            arg0->unk15 = 0x40;
            arg0->x_speed = 0x1CCCC;
            goto countdown;
        }
        if (!(arg0->collision_flags & 2)) {
            goto countdown;
        }
    } else {
        if (arg0->x_pos.i.hi - g_Player.x_pos.i.hi > 0x40) {
            arg0->unk15 = 0;
            arg0->x_speed = -0x1CCCC;
            goto countdown;
        }
        if (!(arg0->collision_flags & 1)) {
            goto countdown;
        }
    }
    set_animation(arg0, 1);
    arg0->unk5 = 4;
    arg0->unk6 = 0;
countdown:
    if (--arg0->unk7C != 0) {
        return;
    }
    arg0->ext.main_52.unk8C = 1;
    dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
    if (dy < 0) {
        dy = -dy;
    }
    if (dy > 0x20 || (get_random() & 0xF) < 3) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        return;
    }
    set_animation(arg0, 1);
    arg0->unk5 = 4;
    arg0->unk6 = 0;
}

void func_8006AE80(struct MainObj* arg0)
{
    u8 angle;
    u8 value;

    arg0->y_pos.i.hi -= 0x10;
    arg0->ext.main_52.unk84 = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    arg0->y_pos.i.hi += 0x10;
    angle = arg0->ext.main_52.unk84;
    if (arg0->unk15 == 0) {
        if ((u8)(angle - 8) > 0x10) {
            return;
        }
        if (angle < 10) {
            value = 0;
        } else if (angle < 14) {
            value = 1;
        } else if (angle < 19) {
            value = 2;
        } else if (angle < 23) {
            value = 3;
        } else {
            value = 4;
        }
    } else {
        if (angle >= 0x20) {
            return;
        }
        if (angle < 3) {
            value = 2;
        } else if (angle < 7) {
            value = 1;
        } else if (angle < 9) {
            value = 0;
        } else if (angle < 24) {
            return;
        } else if (angle < 26) {
            value = 4;
        } else if (angle < 30) {
            value = 3;
        } else {
            value = 2;
        }
    }
    arg0->ext.main_52.unk88 = value;
}

extern u8 jump_shooter_shot_hit_box[4];
extern s8 jump_shooter_shot_muzzle_offsets[20];

void func_8009F27C(struct ShotObj* arg0)
{
    s32 index = arg0->unk2;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk58.collision_data = D_80106070;
    arg0->unk42 &= 0x7FFF;
    arg0->unk28 *= 2;
    arg0->unk2C *= 2;
    if (arg0->unk15 == 0)
        arg0->x_pos.i.hi += jump_shooter_shot_muzzle_offsets[index * 2];
    else
        arg0->x_pos.i.hi -= jump_shooter_shot_muzzle_offsets[index * 2];
    arg0->y_vel.val *= 2;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->x_vel.val *= 2;
    arg0->unk54 = jump_shooter_shot_hit_box;
    arg0->unk50.data = jump_shooter_shot_hit_box;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->y_pos.i.hi += jump_shooter_shot_muzzle_offsets[index * 2 + 1];
    set_animation(ANIMATED_OBJECT(arg0), 0xC);
}

extern void* hatch_turret_animations[13];

void func_8007BFF4(struct MainObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk7A = 1;
    arg0->unk7C = 0x30;
    arg0->hp = 3;
    arg0->contact_damage = 3;
    arg0->animation_table = (const u8* const*)hatch_turret_animations;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->invincibility_timer = 0;
    arg0->hurt_box = NULL;
    arg0->attack_box = NULL;
    arg0->terrain_box = NULL;
    arg0->collision_data = NULL;
    arg0->air_state = 0;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->unk16 = 5;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->unk18.val = arg0->x_pos.val;
    set_animation(arg0, 0);
}

void func_8007C144(struct MainObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) != 0) {
        arg0->state = 2;
        return;
    }
    switch (arg0->unk5) {
    case 0:
        if (arg0->unk7C == 0) {
            arg0->unk5 = 1;
            set_animation(arg0, 0);
        } else {
            arg0->unk7C--;
        }
        break;
    case 1:
        if (arg0->animation_step.fields.relative_step != 0) {
            animate_object(ANIMATED_OBJECT(arg0));
            break;
        }
        arg0->unk5 = 2;
        func_8001540C(2, 0x78, arg0);
        set_animation(arg0, 1);
        break;
    case 2:
        if (arg0->animation_step.fields.relative_step != 0) {
            animate_object(ANIMATED_OBJECT(arg0));
            break;
        }
        arg0->unk5 = 3;
        func_8001540C(2, 0x79, arg0);
        func_8007C090(WEAPON_OBJECT(arg0));
        break;
    case 3:
        if (arg0->unk7 == 0) {
            arg0->unk5 = 4;
            set_animation(arg0, 5);
        }
        break;
    case 4:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk7C = 0x80;
            arg0->unk5 = 0;
        }
        animate_object(ANIMATED_OBJECT(arg0));
        break;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x80, 0x80);
}

extern void (*hatch_blast_step_funcs[3])(struct ShotObj*);

extern void* boss_teleporter_animations[11];
extern u8 boss_teleporter_box[4];

void func_800C71C0(struct ItemObj* arg0)
{
    s32 resource;
    s32 row;
    struct MiscObj* misc;

    arg0->active = 0x41;
    arg0->unk16 = 6;
    arg0->unk15 = 0;
    arg0->unk40 = D_801406A8[func_8002938C(0x88)] >> 7;
    resource = func_8002938C(0x88);
    arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    resource = func_8002938C(0x88);
    row = func_8002938C(0x88);
    arg0->unk42 = ((resource * 4 + 0x18) % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
    arg0->animation_table = (const u8* const*)boss_teleporter_animations;
    arg0->unk67 = 0;
    arg0->unk75 = 0;
    arg0->unk68 = (struct Unk_unk68*)boss_teleporter_box;
    if (arg0->unk2 & 0x10) {
        resource = func_8002938C(0x88);
        row = func_8002938C(0x88);
        arg0->unk42 = ((resource * 4 + 0x1A) % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
        set_animation(ANIMATED_OBJECT(arg0), 6);
        arg0->state = 1;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        arg0->unk2 &= 0xF;
        return;
    }
    switch (engine_obj.character_state.bytes[6 + arg0->unk2]) {
    case 0:
        set_animation(ANIMATED_OBJECT(arg0), 1);
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0x33;
            misc->unk2 = 0;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val;
            misc->ext.misc_51.source = MAIN_OBJECT(arg0);
            arg0->unk7C.misc = misc;
        }
        arg0->state = 1;
        break;
    case 1:
        set_animation(ANIMATED_OBJECT(arg0), 10);
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0x33;
            misc->unk2 = 0x30;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val;
            misc->ext.misc_51.source = MAIN_OBJECT(arg0);
            arg0->unk7C.misc = misc;
        }
        arg0->state = 2;
        break;
    case 2:
        set_animation(ANIMATED_OBJECT(arg0), 6);
        arg0->state = 3;
        break;
    default:
        arg0->unk6 = 0;
        return;
    }
    arg0->unk5 = 0;
    arg0->unk6 = 0;
}

s8 func_800C7970(struct ItemObj* self, struct PlayerObj* player)
{
    struct Unk_unk68* other = player->unk68;
    struct Unk_unk68* box;
    u16 self_y;
    u16 other_y;
    s16 distance;

    if (other == NULL)
        return 0;
    box = self->unk68;
    if ((s16)(player->x_pos.i.hi - other->unk2) < (s16)(self->x_pos.i.hi - (box->unk2 - 0x10)))
        return 0;
    if ((s16)(self->x_pos.i.hi + box->unk2 - 0x10) < (s16)(player->x_pos.i.hi + other->unk2))
        return 0;
    self_y = self->y_pos.i.hi + box->unk1;
    other_y = player->y_pos.i.hi + other->unk1;
    distance = (s16)self_y - (s16)other_y >= 0 ? (s16)(self_y - other_y) : (s16)(other_y - self_y);
    return box->unk3 + other->unk3 >= distance;
}

void func_800D2094(struct MiscObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk16 = 1;
        set_animation(arg0, 7);
        arg0->ext.misc_51.unk54 = 0x78;
        arg0->unk6++;
    } else if (--arg0->ext.misc_51.unk54 != 0) {
        animate_object(ANIMATED_OBJECT(arg0));
    } else {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

extern struct Unk_unk68 cyber_peacock_intro_hurt_box;
extern struct Unk_unk68 D_80107CFC[];

void func_8007C30C(struct MainObj* arg0)
{
    arg0->unk7C = 0x80;
    arg0->contact_damage = 5;
    arg0->animation_table = (const u8* const*)cyber_peacock_animations;
    arg0->hurt_box = &cyber_peacock_intro_hurt_box;
    arg0->attack_box = &cyber_peacock_hit_box;
    arg0->collision_data = D_80107CFC;
    arg0->state = 0;
    arg0->unk5 = 1;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->on_screen = 0;
    arg0->unk2 = 0;
    arg0->hp = 0;
    arg0->invincibility_timer = 0;
    arg0->ext.main_64.saved_health = 0;
    arg0->ext.main_64.flash_timer = 0;
    arg0->ext.main_64.force_laser = 0;
    arg0->ext.main_64.hit_count = 0;
    arg0->terrain_box = NULL;
    arg0->air_state = 0;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->unk16 = 3;
    arg0->ext.main_64.shot_count = 0;
    arg0->ext.main_64.unk8A = 0;
    arg0->ext.main_64.skip_attack = 1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    engine_obj.character_state.bytes[7] = 0;
    if (engine_obj.stage == 6) {
        arg0->ext.main_64.arena_x = 0x3E0;
        arg0->ext.main_64.arena_y = 0x900;
    } else {
        arg0->ext.main_64.arena_x = 0x410;
        arg0->ext.main_64.arena_y = 0x600;
    }
}

extern u8 D_800FF724[16];

static u8 main43_column(s16 index)
{
    static const u8 following_pointer_low_byte = 0x6C;

    return index < 16 ? D_800FF724[index] : following_pointer_low_byte;
}

void func_8006346C(struct MainObj* arg0)
{
    u8 column;

    switch (arg0->unk6) {
    case 0:
        column = main43_column(arg0->unk7C);
        arg0->unk7C++;
        arg0->unk7E = 0x10;
        arg0->unk6 = 1;
        arg0->x_pos.i.hi = web_spider_arena_x + 0x30 + (column << 5);
        vent_spawn_puffs((struct MiscObj*)arg0, 2);
        break;
    case 1:
        if (--arg0->unk7E == 0) {
            if (arg0->unk7C >= 0x11) {
                arg0->unk5 = 3;
                arg0->unk6 = 0;
                arg0->unk7C = 0;
                arg0->x_pos.i.hi = web_spider_arena_x + 0xF0;
            } else {
                arg0->unk6 = 0;
            }
        }
        break;
    case 2:
        arg0->unk7E = 0x14;
        arg0->unk6 = 3;
        arg0->x_pos.i.hi = web_spider_arena_x + 0x30 + (arg0->unk7C << 5);
        arg0->unk7C++;
        vent_spawn_puffs((struct MiscObj*)arg0, 2);
        break;
    case 3:
        if (--arg0->unk7E == 0) {
            if (arg0->unk7C >= 7) {
                arg0->unk5 = 3;
                arg0->unk6 = 0;
                arg0->unk7C = 0;
            } else {
                arg0->unk6 = 2;
            }
        }
        break;
    }
}

extern void (*web_spider_step_funcs[7])();
void web_spider_check_big_web(struct MainObj* arg0);

void func_8006398C(struct MainObj* arg0)
{
    s32 result;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    web_spider_check_big_web(arg0);
    ((void (*)(struct MainObj*))web_spider_step_funcs[arg0->unk5])(arg0);
    result = -1;
    if (arg0->hp > 0)
        result = func_8002DD04(arg0);
    if (arg0->ext.main_43.flash_timer != 0) {
        if ((arg0->ext.main_43.flash_timer & 1) == 0)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (--arg0->ext.main_43.flash_timer == 0) {
            arg0->collision_data = D_801075F4;
            arg0->ext.main_43.hurt_collision = 0;
        }
    } else if (result < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
    } else if (result != 0 && result != 0x7F) {
        arg0->collision_data = D_801060F0;
        arg0->ext.main_43.flash_timer = 0x40;
        web_spider_spawn_web_piece((struct VisualObj*)arg0, 0);
        arg0->ext.main_43.hurt_collision = 1;
    }
    func_8002D9BC(arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_80063B20(struct MainObj* arg0)
{
    s32 threshold;

    switch (arg0->unk7) {
    case 0:
        arg0->unk7 = 1;
        arg0->unk7C = g_Player.stun_timer != 0 ? 0x10 : 0x40;
        if (g_Player.stun_timer == 0) {
            if ((get_random() & 7) < 5)
                arg0->ext.main_43.unk94 = ((g_Player.x_pos.i.hi - (s16)web_spider_arena_x) / 40 + 4) & 7;
            else
                arg0->ext.main_43.unk94 = get_random() & 7;
        } else {
            arg0->ext.main_43.unk94 = (g_Player.x_pos.i.hi - (s16)web_spider_arena_x) / 40;
        }
        arg0->gravity = 0x8000;
        arg0->y_speed = 0;
        arg0->x_pos.i.hi = web_spider_arena_x + 0x30 + (arg0->ext.main_43.unk94 << 5);
        vent_spawn_mixed_puffs((struct MiscObj*)arg0, 8);
        set_animation(arg0, 0);
        break;
    case 1:
        if (arg0->unk7C != 0) {
            arg0->unk7C--;
            break;
        }
        if (arg0->y_speed <= -0x80000) {
            arg0->y_speed = -0x80000;
            arg0->gravity = 0;
        }
        threshold = 0x80;
        if (g_Player.stun_timer == 0 && (get_random() & 3) == 0)
            threshold = 0x50;
        if (arg0->y_pos.i.hi - background_objects[arg0->bg_offset].y_pos.i.hi >= threshold) {
            arg0->unk7 = 2;
            arg0->unk7C = 0xA;
            arg0->y_speed = 0x10000;
            arg0->gravity = 0;
            set_animation(arg0, 0x20);
        }
        move_with_gravity(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        move_with_gravity(ANIMATED_OBJECT(arg0));
        if (--arg0->unk7C == 0) {
            arg0->y_speed = 0;
            arg0->gravity = 0;
        }
        if (arg0->unk7C == 0xF)
            arg0->y_speed = -0x10000;
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk6 = 1;
            arg0->unk7 = 0;
            arg0->unk7C = 0xA;
            set_animation(arg0, 0x21);
        }
        animate_object(ANIMATED_OBJECT(arg0));
        break;
    }
}

extern RECT* web_spider_swing_paths[6];
extern u16 web_spider_arena_y;
u8 angle_from_delta(s32 arg0, s32 arg1);

void func_80065168(struct MainObj* arg0, s16 x, s16 y)
{
    s32 dx = arg0->x_pos.val - (x << 16);
    s32 dy = arg0->y_pos.val - (y << 16);
    u8 direction = angle_from_delta(dx, dy);

    if ((arg0->ext.main_43.move_direction ^ direction) & 0x10) {
        arg0->x_pos.i.lo = 0;
        arg0->y_pos.i.lo = 0;
    } else {
        arg0->x_pos.val -= dx / arg0->unk7C;
        arg0->y_pos.val -= dy / arg0->unk7C;
    }
    arg0->ext.main_43.move_direction = direction;
}

void func_80064154(struct MainObj* arg0)
{
    const u16* point;
    s16 dx;
    s16 dy;

    if (arg0->ext.main_43.attack_cooldown == 0) {
        arg0->ext.main_43.unk94 = 0;
        if (g_Player.stun_timer != 0) {
            arg0->ext.main_43.unk94 = 1;
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            return;
        }
        dx = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
        dy = arg0->y_pos.i.hi - g_Player.y_pos.i.hi;
        if ((dx < 0 ? -dx : dx) >= 0x40 && (dy < 0 ? -dy : dy) >= 0x50) {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            return;
        }
    } else {
        arg0->ext.main_43.attack_cooldown--;
    }
    point = (const u16*)web_spider_swing_paths[arg0->ext.main_43.animation_set] + arg0->ext.main_43.animation_index * 2;
    func_80065168(arg0, (s16)(point[0] + web_spider_arena_x + 0x10), (s16)(point[1] + web_spider_arena_y));
    if (--arg0->unk7C == 0) {
        arg0->ext.main_43.animation_index++;
        if (arg0->ext.main_43.animation_length < arg0->ext.main_43.animation_index) {
            arg0->unk6 = 2;
            arg0->ext.main_43.animation_index = 0;
            arg0->unk7C = 0x20;
            web_spider_set_move_timer(arg0);
        } else {
            web_spider_set_move_timer(arg0);
            web_spider_set_swing_animation(arg0);
        }
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event = 0;
        func_8001540C(2, 0x70, arg0);
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_800643B0(struct MainObj* arg0)
{
    struct MainObj* child;
    u32 i;

    switch (arg0->unk6) {
    case 0:
        arg0->unk6 = 1;
        set_animation(arg0, 0xB);
        break;
    case 1:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk6 = 2;
            set_animation(arg0, 0xC);
            break;
        }
        if (arg0->animation_step.fields.event == 0)
            break;
        for (i = 0; i < 4; i++) {
            child = find_free_main_obj();
            if (child == NULL)
                continue;
            child->active = 0x41;
            child->id = 0x2B;
            child->unk2 = i + 1;
            child->x_pos.val = arg0->x_pos.val;
            child->y_pos.val = arg0->y_pos.val;
            child->y_pos.i.hi -= 0x18;
            child->animation_table = arg0->animation_table;
            child->unk40 = arg0->unk40;
            child->sprite_frames = arg0->sprite_frames;
            child->unk42 = arg0->unk42 & 0x7FFF;
            child->unk16 = arg0->unk16;
            child->ext.main_43.effect = (struct EffectObj*)arg0;
            child->unk15 = arg0->unk15;
        }
        arg0->animation_step.fields.event = 0;
        func_8001540C(2, 0x71, arg0);
        break;
    case 2:
        if (arg0->animation_step.fields.relative_step != 0)
            break;
        arg0->unk5 = 4;
        arg0->unk6 = 1;
        arg0->unk7 = 0;
        set_animation(arg0, arg0->ext.main_43.animation_id);
        web_spider_set_attack_cooldown(arg0);
        if (++arg0->ext.main_43.attack_count >= 3)
            arg0->ext.main_43.attack_count = 0;
        break;
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_800646EC(struct MainObj* arg0)
{
    switch (arg0->unk7) {
    case 0:
        arg0->unk7 = 1;
        arg0->unk7C = 0xC0;
        arg0->ext.main_43.attack_count = 0;
        arg0->gravity = 0x8000;
        arg0->ext.main_43.attack_cooldown = 0;
        arg0->x_pos.i.lo = 0;
        arg0->y_speed = 0;
        arg0->ext.main_43.flash_timer = 0;
        arg0->collision_data = D_801060F0;
        arg0->x_pos.i.hi = web_spider_arena_x + 0xB0;
        vent_spawn_mixed_puffs((struct MiscObj*)arg0, 8);
        set_animation(arg0, 0);
        break;
    case 1:
        if (arg0->unk7C != 0) {
            arg0->unk7C--;
            break;
        }
        if (arg0->y_speed <= -0x80000) {
            arg0->y_speed = -0x80000;
            arg0->gravity = 0;
        }
        if (arg0->y_pos.i.hi - background_objects[arg0->bg_offset].y_pos.i.hi >= 0x58) {
            arg0->unk7 = 2;
            arg0->unk7C = 0x1E;
            set_animation(arg0, 0x20);
            arg0->y_speed = 0x10000;
            arg0->gravity = 0;
        }
        move_with_gravity(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        move_with_gravity(ANIMATED_OBJECT(arg0));
        if (--arg0->unk7C == 0) {
            arg0->y_speed = 0;
            arg0->gravity = 0;
        }
        if (arg0->unk7C == 0xF)
            arg0->y_speed = -0x10000;
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk6 = 1;
            arg0->unk7 = 0;
            arg0->unk7C = 0x14;
            set_animation(arg0, 0x21);
        }
        animate_object(ANIMATED_OBJECT(arg0));
        break;
    }
}

extern struct FixedPointPosition spiderling_velocities[8];
extern struct Unk_unk68 D_800FF5B4;
extern struct Unk_unk68 D_800FF5B8;
extern struct Unk_unk68 D_800FF5BC;

void func_80065574(struct MainObj* arg0)
{
    const s32* velocity = (const s32*)&spiderling_velocities[((arg0->unk2 - 1) & 3) * 2];

    arg0->unk5 = 2;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk63 = 1;
    arg0->contact_damage = 4;
    arg0->unk6 = 0;
    arg0->unk7C = 0;
    arg0->hp = 3;
    arg0->invincibility_timer = 0;
    arg0->unk62 = 0;
    arg0->air_state = 0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->x_speed = velocity[0];
    arg0->x_accel = velocity[1];
    arg0->y_speed = velocity[2];
    arg0->gravity = velocity[3];
    arg0->hurt_box = &D_800FF5B8;
    arg0->attack_box = &D_800FF5B4;
    arg0->terrain_box = &D_800FF5BC;
    arg0->unk16 = 3;
    arg0->collision_flags = 0;
    arg0->collision_data = D_801075F4;
    set_animation(arg0, 0x1B);
}

void func_800CACF0(struct MiscObj* arg0)
{
    if (arg0->unk5 == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        move_with_gravity(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            arg0->animation_step.fields.event = 0;
            arg0->x_vel.val = -arg0->x_vel.val;
        }
        if (arg0->y_pos.i.hi >= (engine_obj.stage == 0xC ? 0x6D0 : 0x5D0)) {
            arg0->unk5 = 1;
            arg0->y_vel.val = 0;
            arg0->unk2C = 0;
            arg0->ext.misc_16.timer = 0x14;
        }
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    if (--arg0->ext.misc_16.timer == 0) {
        arg0->state = 2;
        return;
    }
    arg0->on_screen = 0;
    if (arg0->ext.misc_16.timer & 1)
        is_on_screen(BASE_OBJECT(arg0));
}

extern void (*web_thread_step_funcs[3])(struct ShotObj*);

MMX4_STATIC_ASSERT(bar_obj_size, sizeof(struct BarObj) == 0x34);
MMX4_STATIC_ASSERT(bar_obj_unk28_offset, MMX4_OFFSET_OF(struct BarObj, unk28) == 0x28);

#define BAR_BYTES(obj) ((u8*)(obj))

extern u8 D_800F48EC[8];
extern u8 D_8013B818[0x10];
void func_800170B0(void);

void func_8002FD70(struct BarObj* arg0)
{
    u8* bytes = BAR_BYTES(arg0);
    u32 i;

    if (main_bss_state.transition.active != 0) {
        func_80023D68();
        return;
    }
    func_800170B0();
    func_800129A4(8);
    arg0->unk5 = 2;
    arg0->unk14 = 0;
    if (g_Player.unk2 == 0) {
        bytes[0x16] = 1;
        bytes[0x17] = (g_Player.armor_parts & 2) ? 1 : 0;
        for (i = 2; i < 10; i++)
            bytes[0x16 + i] = ((u8)g_Player.boss_flags >> (i - 2)) & 1;
    } else {
        for (i = 0; i < 8; i++)
            bytes[0x16 + D_800F48EC[i]] = ((u8)g_Player.boss_flags >> i) & 1;
        bytes[0x1F] = 0;
        bytes[0x20] = 0;
    }
    if (engine_obj.unk5A & 0x3000) {
        if (engine_obj.unk5A & 0x1000) {
            bytes[0x20] = 1;
            engine_obj.unk5C[0] |= 0x80;
        }
        if (engine_obj.unk5A & 0x2000) {
            bytes[0x21] = 1;
            engine_obj.unk5C[1] |= 0x80;
        }
    } else {
        bytes[0x20] = 0;
        bytes[0x21] = 0;
    }
    bytes[0x22] = (engine_obj.unk5A & 0x4000) ? 1 : 0;
    if (engine_obj.stage != 0)
        bytes[0x23] = ((u8)engine_obj.palette_flags >> (engine_obj.stage - 1)) & 1;
    bytes[0x24] = 1;
    if (g_Player.unk2 != 0 || (engine_obj.stage == 5 && engine_obj.checkpoint == 0) || g_Player.ride_state < 0) {
        if (g_Player.unk2 == 0)
            arg0->unk2 = 1;
        for (i = 10; i < 15; i++) {
            if (bytes[0x16 + i] != 0) {
                arg0->unk14 = i;
                break;
            }
        }
    } else {
        arg0->unk2 = 0;
        if (g_Player.weapon != 0)
            arg0->unk14 = g_Player.weapon + 1;
    }
    bytes[0x25] = (engine_obj.unk5A & 0x8000) ? 1 : 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk30 = 0;
    D_8013B818[0] = g_Player.weapon;
}

void func_800301BC(struct BarObj* arg0)
{
    u8* bytes = BAR_BYTES(arg0);
    s32 original = (u8)arg0->unk14;
    s32 wrapped = 0;
    s32 target;
    s32 cursor;
    s32 count;

    switch (controller_input.pressed) {
    case PAD_CONFIRM:
        if ((u8)original < 10) {
            if ((s8)original < 2)
                g_Player.weapon = 0;
            else
                g_Player.weapon = original - 1;
        }
        func_8001540C(0, 0x22, 0);
        goto done;
    case 0x800:
        arg0->state = 2;
        arg0->unk5 = 0;
        goto done;
    case 0x1000:
        cursor = original;
        for (;;) {
            cursor -= 2;
            if ((s8)cursor < 0)
                cursor = (u8)arg0->unk14;
            if (arg0->unk14 == (s8)cursor || (s8)cursor == 0)
                goto store;
            if (bytes[0x16 + (s8)cursor] != 0)
                goto store;
        }
    case 0x4000:
        cursor = original;
        for (;;) {
            cursor += 2;
            if ((s8)cursor >= 10) {
                cursor = 9;
                for (count = 0; count < 5; count++) {
                    cursor++;
                    if (bytes[0x16 + (s8)cursor] != 0) {
                        arg0->unk5 = (s8)cursor < 0xD ? 1 : 2;
                        goto store;
                    }
                }
                goto store;
            }
            if (arg0->unk14 == (s8)cursor)
                goto store;
            if (bytes[0x16 + (s8)cursor] != 0)
                goto store;
        }
    case 0x2000:
        target = original + 1;
        cursor = target;
        if ((target & 1) == 0)
            goto done;
        original = target;
        if (bytes[0x16 + (s8)target] != 0) {
            original = target - 1;
            goto store;
        }
        for (;;) {
            if (wrapped == 0) {
                cursor += 2;
                if ((s8)cursor >= 0xB) {
                    cursor -= 2;
                    wrapped = 1;
                }
            } else {
                cursor -= 2;
            }
            if ((s8)cursor == (s8)target)
                goto unchanged;
            if (bytes[0x16 + (s8)cursor] != 0)
                goto store;
        }
    case 0x8000:
        target = original - 1;
        cursor = target;
        if (target & 1)
            goto done;
        original = target;
        if (bytes[0x16 + (s8)target] != 0) {
            original = target + 1;
            goto store;
        }
        for (;;) {
            if (wrapped == 0) {
                cursor -= 2;
                if ((s8)cursor < 0) {
                    cursor += 2;
                    wrapped = 1;
                }
            } else {
                cursor += 2;
            }
            if ((s8)cursor == (s8)target)
                goto unchanged;
            if (bytes[0x16 + (s8)cursor] != 0)
                goto store;
        }
    default:
        goto done;
    }
unchanged:
    original = (u8)arg0->unk14;
    cursor = original;
store:
    arg0->unk14 = cursor;
done:
    if (arg0->unk14 != (s8)original)
        func_8001540C(0, 0xC, 0);
}

void func_800304E4(struct BarObj* arg0)
{
    u8* bytes = BAR_BYTES(arg0);
    s32 original = (u8)arg0->unk14;
    s32 cursor;

    switch (controller_input.pressed) {
    case 0x800:
        arg0->state = 2;
        arg0->unk5 = 0;
        break;
    case PAD_CONFIRM:
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        switch (arg0->unk14) {
        case 10:
            arg0->unk5 = 3;
            if ((engine_obj.unk5C[0] & 0x7F) == 0x20)
                arg0->unk28 = 1;
            break;
        case 11:
            arg0->unk5 = 3;
            if ((engine_obj.unk5C[1] & 0x7F) == 0x20)
                arg0->unk28 = 1;
            break;
        case 12:
            arg0->unk5 = 4;
            if ((engine_obj.unk5C[2] & 0x7F) == 0x20)
                arg0->unk2C = 1;
            break;
        }
        break;
    case 0x1000:
        if (g_Player.unk2 != 0 || arg0->unk2 != 0)
            break;
        cursor = 9;
        while ((s8)cursor != 0 && bytes[0x16 + (s8)cursor] == 0)
            cursor--;
        arg0->unk5 = 0;
        arg0->unk14 = cursor;
        break;
    case 0x2000:
        cursor = original;
        for (;;) {
            cursor++;
            if ((s8)cursor >= 0xD) {
                if (bytes[0x16 + (s8)cursor] == 0)
                    cursor++;
                arg0->unk5 = 2;
                break;
            }
            if (bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    case 0x8000:
        cursor = original;
        for (;;) {
            cursor--;
            if ((s8)cursor < 10) {
                cursor = original;
                break;
            }
            if (bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    }
    if (arg0->unk14 != (s8)original)
        func_8001540C(0, 0xC, 0);
}

void func_80030728(struct BarObj* arg0)
{
    u8* bytes = BAR_BYTES(arg0);
    s32 original = (u8)arg0->unk14;
    s32 cursor;

    if (controller_input.pressed & 0x800) {
        arg0->state = 2;
        arg0->unk5 = 0;
        goto done;
    }
    switch (controller_input.pressed) {
    case PAD_CONFIRM:
        if ((s8)original == 0xD) {
            arg0->state = 2;
            arg0->unk5 = 0;
            arg0->unk30 = 1;
        } else {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            func_80023D90();
        }
        func_8001540C(0, 0x22, 0);
        break;
    case 0x1000:
        cursor = original;
        if (g_Player.unk2 != 0 || arg0->unk2 != 0) {
            cursor--;
            if ((s8)cursor < 0xD)
                cursor = 0xD;
            if (bytes[0x16 + (s8)cursor] != 0)
                arg0->unk14 = cursor;
            break;
        }
        for (;;) {
            cursor--;
            if ((s8)cursor < 0xD) {
                cursor = 9;
                while ((s8)cursor != 0 && bytes[0x16 + (s8)cursor] == 0)
                    cursor--;
                arg0->unk5 = 0;
                break;
            }
            if (arg0->unk14 == (s8)cursor || bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    case 0x4000:
        cursor = original;
        for (;;) {
            cursor++;
            if ((s8)cursor >= 0xF) {
                cursor = 0xE;
                break;
            }
            if (arg0->unk14 == (s8)cursor || bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    case 0x8000:
        cursor = 0xC;
        if (g_Player.unk2 != 0 || arg0->unk2 != 0) {
            for (;;) {
                if ((s8)cursor == 0 || bytes[0x16 + (s8)cursor] != 0) {
                    arg0->unk14 = cursor;
                    arg0->unk5 = 1;
                    break;
                }
                cursor--;
                if ((s8)cursor < 10)
                    break;
            }
            break;
        }
        while ((s8)cursor != 0 && bytes[0x16 + (s8)cursor] == 0)
            cursor--;
        arg0->unk14 = cursor;
        arg0->unk5 = (s8)cursor < 10 ? 0 : 1;
        break;
    }
done:
    if (arg0->unk14 != (s8)original)
        func_8001540C(0, 0xC, 0);
}

static void bar_merge_sub_tanks(void)
{
    s8 second = engine_obj.unk5C[1];

    if (second >= 0)
        return;
    engine_obj.unk5C[0] = second;
    engine_obj.unk5C[1] = second & 0x80;
}

void func_80030A2C(struct BarObj* arg0)
{
    s32 frame = main_bss_state.frame_counter;
    u32 tank;
    u8 energy;
    u8 health;
    u8 player_health;

    if (frame & 1)
        return;
    tank = arg0->unk14 != 10;
    if (arg0->unk28 != 0) {
        energy = engine_obj.unk5C[tank] & 0x7F;
        if (energy != 0) {
            engine_obj.unk5C[tank] = (energy - 1) | 0x80;
            health = (g_Player.hp & 0x7F) + 1;
            if (engine_obj.unk46 < (s8)health)
                health = engine_obj.unk46;
            g_Player.hp = health;
            if ((main_bss_state.frame_counter & 3) == 0)
                func_8001540C(0, 0x17, 0);
            return;
        }
        if (g_Player.hp != engine_obj.unk46) {
            health = (g_Player.hp & 0x7F) + 1;
            if (engine_obj.unk46 < (s8)health)
                health = engine_obj.unk46;
            g_Player.hp = health;
            if ((frame & 3) == 0)
                func_8001540C(0, 0x17, 0);
            return;
        }
        arg0->unk5 = 1;
        arg0->unk28 = 0;
        if (tank == 0)
            bar_merge_sub_tanks();
        return;
    }
    energy = engine_obj.unk5C[tank] & 0x7F;
    if (energy == 0) {
        arg0->unk5 = 1;
        if (tank == 0)
            bar_merge_sub_tanks();
        return;
    }
    engine_obj.unk5C[tank] = (energy - 1) | 0x80;
    player_health = g_Player.hp;
    health = (player_health & 0x7F) + 1;
    if (engine_obj.unk46 < (s8)health)
        health = engine_obj.unk46;
    g_Player.hp = health | (player_health & 0x80);
    if ((main_bss_state.frame_counter & 3) == 0)
        func_8001540C(0, 0x17, 0);
}

void func_80030C54(struct BarObj* arg0)
{
    u32 i;
    s32 refilled = 0;
    u8 energy;

    if (main_bss_state.frame_counter & 1)
        return;
    if (arg0->unk2C != 0) {
        for (i = 0; i < 9; i++) {
            if (g_Player.weapon_energy[i] < 0x30) {
                g_Player.weapon_energy[i]++;
                refilled = 1;
            } else {
                g_Player.weapon_energy[i] = 0x30;
            }
        }
        if (refilled == 0) {
            energy = engine_obj.unk5C[2] & 0x7F;
            if (energy != 0) {
                engine_obj.unk5C[2] = energy - 1;
            } else {
                arg0->unk5 = 1;
                arg0->unk2C = 0;
            }
            return;
        }
    } else {
        if ((engine_obj.unk5C[2] & 0x7F) == 0) {
            arg0->unk5 = 1;
            return;
        }
        for (i = 0; i < 9; i++) {
            if (g_Player.weapon_energy[i] < 0x30 && (s8)(g_Player.weapon_energy[i] + 1) < 0x30) {
                g_Player.weapon_energy[i]++;
                refilled = 1;
            } else {
                g_Player.weapon_energy[i] = 0x30;
            }
        }
        if (refilled == 0) {
            arg0->unk5 = 1;
            return;
        }
    }
    energy = engine_obj.unk5C[2] & 0x7F;
    engine_obj.unk5C[2] = energy != 0 ? energy - 1 : energy;
    if ((main_bss_state.frame_counter & 3) == 0)
        func_8001540C(0, 0x17, 0);
}

void player_cancel_released_charge(void);

void func_80031064(struct BarObj* arg0)
{
    if (arg0->unk30 == 0) {
        if (g_Player.unk2 == 0) {
            player_cancel_released_charge();
            if ((s8)D_8013B818[0] != g_Player.weapon) {
                player_reset_charge(&g_Player);
                g_Player.stock_charge = 0;
            }
            player_update_shot_types(&g_Player);
            if ((s8)D_8013B818[0] != g_Player.weapon)
                player_equip_weapon(&g_Player);
        }
        func_80021158();
        func_800129A4(8);
    }
    arg0->unk5 = 3;
}

static const u16* pause_screen_tiles;
static SPRT_16* pause_screen_sprites;
static DR_TPAGE pause_screen_page[2];

void func_80017268(s16 x_start)
{
    SPRT_16* sprite = pause_screen_sprites;
    u32 row;
    u32 column;
    s16 x;
    s16 y = 0;
    u16 tile;

    for (row = 0; row < 16; row++, y += 16) {
        x = x_start;
        for (column = 0; column < 16; column++, x += 16) {
            tile = *pause_screen_tiles++;
            if (x >= 0x140)
                continue;
            sprite->clut = (tile >> 12) | 0x7900;
            sprite->u0 = (tile & 0xF) << 4;
            sprite->v0 = tile & 0xF0;
            sprite->x0 = x;
            sprite->y0 = y;
            sprite->code &= 0xFD;
            setaddr(sprite, sprite + 1);
            sprite++;
        }
    }
    pause_screen_sprites = sprite;
}

void func_80017100(void)
{
    DR_TPAGE* page = &pause_screen_page[SP_DRAW_BUFFER];

    pause_screen_tiles = (const u16*)SP_ARC_34;
    pause_screen_sprites = D_8015D9D0[SP_DRAW_BUFFER].sprites;
    setlen(page, 1);
    page->code[0] = (GetGraphType() == 1 || GetGraphType() == 2) ? 0xE100002D : 0xE100001D;
    setaddr(page, pause_screen_sprites);
    func_80017268(0);
    func_80017268(0x100);
    setaddr(pause_screen_sprites - 1, getaddr(&cur_draw_info->ordering_table.ui));
    setaddr(&cur_draw_info->ordering_table.ui, page);
}

void func_80017E84(void)
{
    u32 buffer;
    u32 i;
    u32 j;

    for (buffer = 0; buffer < 2; buffer++) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 8; j++) {
                D_8013E1E8[buffer][i][j] = NULL;
                D_8013BC40[buffer][i][j] = (P_TAG*)&D_8013E1E8[buffer][i][j];
            }
        }
    }
}

extern struct HudLayoutData {
    s16 x;
    s16 y;
    u8 tile;
    u8 character;
    u8 clut;
    u8 alternate_clut;
} D_800F1AD8[38];

extern s16 D_800F1C08[2];

static struct HudLayoutData pause_menu_layout(u8 index)
{
    struct HudLayoutData layout;
    const u8* tail = (const u8*)&g_BootTransitionDataRegion;

    if (index < COUNT(D_800F1AD8))
        return D_800F1AD8[index];
    layout.x = D_800F1C08[0];
    layout.y = D_800F1C08[1];
    layout.tile = tail[0];
    layout.character = tail[1];
    layout.clut = tail[2];
    layout.alternate_clut = tail[3];
    return layout;
}

static u16 pause_menu_clut(u8 value)
{
    return (value & 0xF) | (((value >> 4) + 0x1E0) << 6);
}

void func_800175AC(u8 index)
{
    struct HudLayoutData entry = pause_menu_layout(index);
    struct HudLayoutData* layout = &entry;
    const u8* archive = SP_TITLE_FRAMES;
    const u16* frame;
    const u8* pieces;
    POLY_FT4* slot = SP_PRIM_CURSOR;
    DR_TPAGE* page = SP_DRAW_MODE_CURSOR;
    DR_TPAGE* first_page = page;
    SPRT_16* sprite = NULL;
    u32 count;
    s16 x = layout->x;
    s16 y = layout->y;
    u16 clut = 0;
    u16 texture;
    u32 buffer;

    if (index == 0x20) {
        y = 0xD8;
        x = ((s8)engine_obj.unk46 << 1) + 0x80;
    }
    if (index == 0x1F)
        frame = (const u16*)(archive + (layout->tile + engine_obj.unk44) * 4);
    else
        frame = (const u16*)(archive + layout->tile * 4);
    if (index == 0x26 && bar_object.unk25 != 0)
        frame = (const u16*)(archive + layout->tile * 4 + 0x28);
    count = frame[0];
    pieces = archive + frame[1] * 4;
    if (bar_object.unk14 == layout->character) {
        clut = pause_menu_clut((main_bss_state.frame_counter & 0x10) ? layout->alternate_clut : layout->clut);
    } else if (engine_obj.cur_character == CHARACTER_X) {
        clut = pause_menu_clut(layout->clut);
        if (g_Player.weapon + 1 == layout->character || (g_Player.weapon == 0 && layout->character == 0))
            clut = pause_menu_clut(layout->alternate_clut);
    } else {
        clut = pause_menu_clut(index < 0x21 ? layout->alternate_clut : layout->clut);
    }
    if (engine_obj.cur_character == CHARACTER_X && layout->character == 1)
        clut = pause_menu_clut(g_Player.weapon_energy[0] < 0x30 ? layout->clut : layout->alternate_clut);
    if (count == 0)
        return;
    while (count-- != 0) {
        sprite = (SPRT_16*)slot;
        setSprt16(sprite);
        setShadeTex(sprite, 1);
        sprite->x0 = (s8)pieces[2] + x;
        sprite->y0 = y + (s8)pieces[3];
        sprite->clut = clut + ((pieces[0] & 0xC) >> 2);
        texture = 0x1D60 + (pieces[1] | ((pieces[0] & 3) << 8));
        sprite->u0 = texture << 4;
        sprite->v0 = texture & 0xF0;
        setlen(page, 1);
        page->code[0] = 0xE1000000 | 0x20 | (texture >> 8);
        setaddr(page, sprite);
        setaddr(sprite, page + 1);
        page++;
        slot++;
        pieces += 4;
    }
    SP_PRIM_CURSOR = slot;
    SP_DRAW_MODE_CURSOR = page;
    buffer = SP_DRAW_BUFFER;
    setaddr(D_8013BC40[buffer][0][5], first_page);
    D_8013BC40[buffer][0][5] = (P_TAG*)sprite;
}

extern s16 D_800F1C18[13][9];
extern u8 D_800F1D04[];

static const s16* pause_bar_geometry(u32 index)
{
    return index < 13 ? D_800F1C18[index] : (const s16*)D_800F1D04;
}

void func_800179BC(void)
{
    const s16* row;
    POLY_F4* poly;
    DR_TPAGE* page;
    u32 buffer;
    u32 i;
    u8 flag;
    s8 amount;

    for (i = 0; i < 0xE; i++) {
        poly = SP_PRIM_CURSOR;
        page = SP_DRAW_MODE_CURSOR;
        setPolyF4(poly);
        flag = ((u8*)&bar_object)[0x16 + i];
        if (flag != 0 ? (i != 0 && engine_obj.cur_character != CHARACTER_X && i < 9) : i < 0xD)
            continue;
        row = pause_bar_geometry(i);
        poly->x0 = row[0];
        poly->y0 = row[1];
        poly->x1 = row[2];
        poly->y1 = row[3];
        poly->x2 = row[4] - 1;
        poly->y2 = row[5];
        poly->x3 = row[6];
        poly->y3 = row[7];
        if (i < 10) {
            if (i >= 2 || (i == 0) != (engine_obj.cur_character == CHARACTER_X)) {
                amount = g_Player.weapon_energy[i < 2 ? 0 : i - 1];
                if (amount != 0) {
                    poly->x1 = row[0] + amount * 2 - 1;
                    poly->x3 = row[4] + amount * 2 - 1;
                } else {
                    poly->x1 = poly->x0;
                    poly->x3 = poly->x2;
                }
            }
        } else if (i == 0xD) {
            if (g_Player.hp > 0) {
                poly->x0 = 0x6E;
                poly->y0 = 0xD2;
                poly->x2 = 0x67;
                poly->y2 = 0xD9;
                poly->y1 = 0xD2;
                poly->x1 = poly->x0 + (s8)g_Player.hp * 2;
                poly->y3 = 0xD9;
                poly->x3 = poly->x2 + (s8)g_Player.hp * 2;
            }
        } else if (i == 0xC) {
            poly->x1 = poly->x0 + (s8)engine_obj.unk5C[2];
            poly->x3 = poly->x2 + (s8)engine_obj.unk5C[2];
        } else {
            amount = engine_obj.unk5C[i - 10] & 0x7F;
            poly->x1 = poly->x0 + amount;
            poly->x3 = poly->x2 + amount;
        }
        setRGB0(poly, 0x29, 0xC6, 0x29);
        setlen(page, 1);
        page->code[0] = 0xE1000000;
        buffer = SP_DRAW_BUFFER;
        setaddr(D_8013BC40[buffer][0][5], page);
        setaddr(page, poly);
        D_8013BC40[buffer][0][5] = (P_TAG*)poly;
        SP_DRAW_MODE_CURSOR = page + 1;
        SP_PRIM_CURSOR = (POLY_FT4*)poly + 1;
    }
}

void func_80037C28(struct PlayerObj* arg0)
{
    s32 count;
    s8 i;

    if (arg0->shot_type == 8) {
        count = 2;
        func_8001540C(1, 9, arg0);
    } else {
        count = 8;
        func_8001540C(1, 0xA, arg0);
        player_play_voice(arg0, 9);
    }
    for (i = 0; i < count; i++)
        player_spawn_weapon(1, arg0->shot_type, i, NULL);
    arg0->shot_count += count;
    arg0->special_shot_count += count;
}

extern u32* D_8011C104[10];

void func_800978DC(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;

    arg0->on_screen = 1;
    arg0->unk50 = twin_slasher_hit_boxes;
    arg0->unk38 = (u8*)player_gfx + player_gfx[9];
    arg0->animation_table = D_8011C104;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x11];
    arg0->unk15 = g_Player.unk15;
    buster_shot_place_at_muzzle((struct VisualObj*)arg0, &g_Player, arg0->id);
    set_velocity_from_angle(MOVING_OBJECT(arg0), arg0->unk2 == 0 ? 2 : 0x1E);
    arg0->x_vel.val <<= 3;
    arg0->y_vel.val <<= 3;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -arg0->x_vel.val;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->ext.weapon_8.timer = 0x18;
    set_animation(arg0, arg0->unk2);
    move_object(MOVING_OBJECT(arg0));
    arg0->unk5 = 0;
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}

extern struct Unk_unk68 twin_slasher_charged_hit_boxes[];
extern u8 twin_slasher_charged_angles[];
void func_80097BA4(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    s32 level = arg0->unk2 >> 1;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = &twin_slasher_charged_hit_boxes[level];
    arg0->unk38 = (u8*)player_gfx + player_gfx[9];
    arg0->animation_table = D_8011C104;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x11];
    arg0->unk15 = g_Player.unk15;
    buster_shot_place_at_muzzle((struct VisualObj*)arg0, &g_Player, arg0->id);
    set_velocity_from_angle(MOVING_OBJECT(arg0), twin_slasher_charged_angles[arg0->unk2]);
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->x_vel.val *= 9;
    arg0->y_vel.val *= 9;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -arg0->x_vel.val;
    set_animation(arg0, level + 2);
    move_object(MOVING_OBJECT(arg0));
    arg0->ext.weapon_17.timer = 3;
    arg0->unk5 = 0;
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}

void func_80097DD8(struct MiscObj* arg0)
{
    s32* player_gfx;
    s32* sprite_frames;

    if (g_Player.input_locked != 0 || g_Player.capsule_state != 0 || g_Player.weapon != 8) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->state != 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->animation_step.fields.relative_step == 0) {
            ZeroObjectState(OBJECT_HEADER(arg0));
            return;
        }
    } else {
        player_gfx = SP_PLAYER_GFX;
        sprite_frames = SP_SPRITE_FRAMES;
        arg0->on_screen = 1;
        arg0->unk38 = (u8*)player_gfx + player_gfx[9];
        arg0->animation_table = D_8011C104;
        arg0->unk40 = 0x520;
        arg0->unk42 = 0x7801;
        arg0->unk16 = 1;
        arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x11];
        set_animation(arg0, arg0->unk2 + 6);
        arg0->state++;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}

extern s16 web_piece_positions_a[4][2];
extern s16 web_piece_positions_b[4][2];

static const s16* visual_17_target(struct VisualObj* arg0)
{
    return engine_obj.stage != 0xC ? web_piece_positions_a[arg0->unk2 - 1] : web_piece_positions_b[arg0->unk2 - 1];
}

void func_800B20CC(struct VisualObj* arg0)
{
    const s16* target;
    u8 direction;
    struct QuadObj* quad;

    arg0->state = 1;
    arg0->on_screen = 1;
    if (arg0->unk2 == 0) {
        arg0->unk16 = 3;
        set_animation(arg0, 0x18);
        return;
    }
    arg0->unk16 = 5;
    set_animation(arg0, 0x17);
    target = visual_17_target(arg0);
    direction = angle_from_delta(arg0->x_pos.val - (target[0] << 16), arg0->y_pos.val - (target[1] << 16));
    set_velocity_from_angle(MOVING_OBJECT(arg0), direction);
    arg0->unk54 = direction;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->x_vel.val <<= 1;
    arg0->y_vel.val <<= 1;
    quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = -0x7F;
        quad->id = 5;
        arg0->unk5C.owner = (struct PlayerObj*)quad;
    }
}

void func_800B22B4(struct VisualObj* arg0)
{
    const s16* target = visual_17_target(arg0);
    s32 target_x = target[0] << 16;
    s32 target_y = target[1] << 16;
    u8 direction = angle_from_delta(arg0->x_pos.val - target_x, arg0->y_pos.val - target_y);
    struct BaseObj* quad = (struct BaseObj*)arg0->unk5C.owner;

    if ((arg0->unk54 >> 3) != (direction >> 3)) {
        arg0->unk5 = 1;
        arg0->x_vel.val = 0;
        arg0->unk28 = 0;
        arg0->y_vel.val = 0;
        arg0->unk2C = 0;
        arg0->x_pos.val = target_x;
        arg0->y_pos.val = target_y;
        quad->state = 2;
        update_on_screen(BASE_OBJECT(arg0), 0x10, 0x10);
    } else {
        move_with_gravity(ANIMATED_OBJECT(arg0));
    }
    quad->x_pos.val = arg0->x_pos.val;
    quad->y_pos.val = arg0->y_pos.val;
}

extern u8 web_shot_hit_box[4];
extern void (*web_shot_step_funcs[5])(struct ShotObj*);

void func_8009D788(struct ShotObj* arg0)
{
    s32 direction;

    arg0->unk54 = web_shot_hit_box;
    arg0->unk50.data = web_shot_hit_box;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 3;
    arg0->unk68 = NULL;
    arg0->unk58.data = (u8*)D_80106070;
    direction = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    arg0->unk84.value = direction;
    set_velocity_from_angle(MOVING_OBJECT(arg0), direction);
    arg0->timer = 0x14;
    arg0->unk8A = 0;
    arg0->unk5C = 1;
    arg0->unk60 = 0;
    arg0->unk8C.word = 1;
    arg0->unk62 = 3;
    arg0->unk90.val = 0;
    arg0->x_vel.val *= 3;
    arg0->y_vel.val *= 3;
    set_animation(arg0, 0x16);
}

void boss_death_fx_spawn_explosions(struct EffectObj* arg0);
void boss_death_fx_spawn_ray(struct EffectObj* arg0);
void boss_death_fx_spawn_ring(struct EffectObj* arg0);

static void effect_26_spawn_spark(struct EffectObj* arg0, u8 angle)
{
    struct QuadObj* quad = find_free_quad_obj();

    if (quad == NULL)
        return;
    quad->active = 1;
    quad->id = 4;
    quad->unk2 = angle;
    quad->x_pos.i.hi = arg0->x_pos.i.hi;
    quad->y_pos.i.hi = arg0->y_pos.i.hi;
}

void func_800BB364(struct EffectObj* arg0)
{
    effect_26_spawn_spark(arg0, arg0->unk2);
    effect_26_spawn_spark(arg0, (arg0->unk2 + 0xA) & 0x1F);
    effect_26_spawn_spark(arg0, (arg0->unk2 + 0x15) & 0x1F);
    func_8002B560(0x82, 0);
    if (arg0->ext.effect_26.timer != 0) {
        arg0->ext.effect_26.timer--;
        spawn_explosion(BASE_OBJECT(arg0));
        return;
    }
    arg0->ext.effect_26.timer = 0x64;
    arg0->state++;
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    D_8013E188[0] = -1;
    D_8013E188[1] = -1;
    D_8013E188[2] = -1;
    D_8013E188[3] = -1;
    func_80016F0C();
    engine_obj.unk42 = 0;
}

void func_800BB750(struct EffectObj* arg0)
{
    arg0->ext.effect_26.timer++;
    boss_death_fx_spawn_explosions(arg0);
    boss_death_fx_spawn_ray(arg0);
    boss_death_fx_spawn_ring(arg0);
    if (arg0->ext.effect_26.timer % 5 != 0)
        return;
    g_FilterAmountR += 1;
    g_FilterAmountG += 0x20;
    g_FilterAmountB += 0x400;
    if (g_FilterAmountR != 0x1F)
        return;
    arg0->state++;
    arg0->ext.effect_26.timer = (arg0->active & 0x80) ? 0xC8 : 0x28;
    arg0->unk7 = 1;
    engine_obj.enable_boss = 0;
    func_8001540C(0, 5, NULL);
}

void func_800BB888(struct EffectObj* arg0)
{
    if (++arg0->ext.effect_26.timer % 5 != 0)
        return;
    g_FilterAmountR -= 1;
    g_FilterAmountG -= 0x20;
    g_FilterAmountB -= 0x400;
    if (g_FilterAmountR == 0)
        arg0->state++;
}

extern s16 boss_death_shard_shapes[64][2];

void func_800D52F4(struct QuadObj* arg0)
{
    u8 angle = arg0->ext.quad_4.unk38;
    const s16* outer = boss_death_shard_shapes[(arg0->ext.quad_4.unk39 + 1) * 16 + (angle & 0xF)];
    const s16* inner = boss_death_shard_shapes[arg0->ext.quad_4.unk39 * 16 + (angle & 0xF)];
    s32 sign = (angle & 0x1F) >= 0x10 ? -1 : 1;

    arg0->vertices[1].x.val = sign * (outer[0] << 16);
    arg0->vertices[1].y.val = sign * (outer[1] << 16);
    arg0->vertices[2].x.val = sign * (inner[0] << 16);
    arg0->vertices[2].y.val = sign * (inner[1] << 16);
    arg0->vertices[3].x.val = 0;
    arg0->vertices[3].y.val = 0;
    arg0->state++;
    arg0->ext.quad_4.timer = get_random_nonzero() % 7;
    quad_is_on_screen(arg0);
}

#define QUAD6_ANGLE(obj) ((obj)->ext.ready_line.x_vel.bytes[0])
#define QUAD6_DELAY(obj) ((obj)->ext.ready_line.x_vel.bytes[1])
#define QUAD6_AGE(obj) ((obj)->ext.ready_line.x_vel.bytes[2])
#define QUAD6_X_SPEED(obj) ((obj)->ext.ready_line.y_vel.val)
#define QUAD6_Y_SPEED(obj) ((obj)->ext.ready_line.x_accel.val)
#define QUAD6_X_SPEED2(obj) ((obj)->ext.ready_line.y_accel.val)
#define QUAD6_Y_SPEED2(obj) ((obj)->runtime.search_light.x_accumulator)
#define QUAD6_X_ACCEL(obj) ((obj)->runtime.search_light.y_accumulator)
#define QUAD6_Y_ACCEL(obj) (*(s32*)&(obj)->runtime.search_light.pause_timer)
#define QUAD6_X_ACCEL2(obj) ((obj)->runtime.search_light.base_speed)
#define QUAD6_Y_ACCEL2(obj) (*(s32*)&(obj)->link)

extern s32 D_800F459C[];
extern s32 D_800F45C0[];

void func_800D5934(struct QuadObj* arg0)
{
    u8 angle;
    s16 index;
    s16 x_sign;
    s16 y_sign;

    arg0->unk36 = 0;
    arg0->unk34 = 1;
    arg0->bg_offset = 0;
    arg0->active |= 0x82;
    angle = get_random() & 0x1F;
    QUAD6_ANGLE(arg0) = angle;
    if (angle < 0x10) {
        x_sign = -1;
        if (angle < 8) {
            index = 8 - angle;
            y_sign = 1;
        } else {
            index = angle - 8;
            y_sign = -1;
        }
    } else {
        x_sign = 1;
        if (angle < 0x18) {
            index = 0x18 - angle;
            y_sign = -1;
        } else {
            index = angle - 0x18;
            y_sign = 1;
        }
    }
    QUAD6_X_SPEED(arg0) = (s32)((u32)(D_800F459C[index] * y_sign) << 4) >> 4;
    QUAD6_Y_SPEED(arg0) = (s32)((u32)(D_800F45C0[index] * x_sign) << 4) >> 4;
    arg0->vertices[0].x.val = 0;
    arg0->vertices[0].y.val = 0;
    arg0->vertices[1].x.val = 0;
    arg0->vertices[1].y.val = 0;
    arg0->vertices[2].x.val = 0;
    arg0->vertices[2].y.val = 0;
    arg0->vertices[3].x.val = 0;
    arg0->vertices[3].y.val = 0;
    QUAD6_AGE(arg0) = 0;
    arg0->state++;
    QUAD6_X_ACCEL(arg0) = QUAD6_X_SPEED(arg0);
    QUAD6_X_SPEED2(arg0) = QUAD6_X_SPEED(arg0);
    QUAD6_Y_SPEED2(arg0) = QUAD6_Y_SPEED(arg0);
    QUAD6_Y_ACCEL(arg0) = QUAD6_Y_SPEED(arg0);
    QUAD6_DELAY(arg0) = 4;
    QUAD6_X_ACCEL2(arg0) = QUAD6_X_SPEED2(arg0) / 2;
    QUAD6_Y_ACCEL2(arg0) = QUAD6_Y_SPEED2(arg0) / 2;
}

void func_800CF4B8(struct MiscObj* arg0)
{
    struct MainObj* source = arg0->ext.misc_7.position;

    arg0->x_pos.val = source->x_pos.val;
    arg0->y_pos.val = source->y_pos.val;
    arg0->unk40 = source->unk40;
    arg0->unk42 = source->unk42 & 0x7FFF;
    arg0->animation_table = (u32**)source->animation_table;
    arg0->unk3C = (void*)source->sprite_frames;
    arg0->unk15 = 0;
    arg0->bg_offset = source->bg_offset;
    switch ((u8)arg0->unk2) {
    case 2:
        set_animation(arg0, 0x18);
        arg0->unk16 = 7;
        arg0->state = 1;
        break;
    case 3:
        set_animation(arg0, 0x17);
        arg0->unk16 = 4;
        arg0->state = 1;
        break;
    case 4:
        set_animation(arg0, 0xE);
        arg0->unk16 = 4;
        arg0->state = 4;
        break;
    case 5:
        set_animation(arg0, 0x15);
        arg0->unk16 = 4;
        arg0->state = 4;
        break;
    default:
        set_animation(arg0, 0x19);
        arg0->unk16 = 4;
        arg0->state = 3;
        break;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800CF660(struct MiscObj* arg0)
{
    struct MainObj* source = arg0->ext.misc_7.position;

    arg0->x_pos.val = source->x_pos.val;
    arg0->y_pos.val = source->y_pos.val;
    animate_object(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
    if (source->air_state == 0) {
        set_animation(arg0, 0x1A);
        arg0->state -= 2;
    } else if (arg0->animation_step.fields.relative_step < 0 && arg0->unk2 != 0) {
        arg0->state--;
    }
}

extern struct Unk_unk68 magma_dragoon_dive_kick_attack_box;

void magma_dragoon_face_player(struct MainObj* arg0);

void func_8007E4C8(struct MainObj* arg0)
{
    u8 roll;

    magma_dragoon_face_player(arg0);
    roll = get_random() & 0xF;
    arg0->ext.main_65.attack_repeat = 0;
    if (arg0->hp >= 0x19) {
        if (roll < 6)
            arg0->ext.main_65.attack = 0;
        else if (roll < 10)
            arg0->ext.main_65.attack = 1;
        else if (roll < 13)
            arg0->ext.main_65.attack = 2;
        else
            arg0->ext.main_65.attack = 3;
    } else {
        if (roll < 6)
            arg0->ext.main_65.attack = 4;
        else if (roll < 9)
            arg0->ext.main_65.attack = 5;
        else
            arg0->ext.main_65.attack = 6;
    }
    switch (arg0->ext.main_65.attack) {
    case 0:
    case 1:
    case 4:
        arg0->unk5 = 4;
        break;
    case 2:
    case 5:
        arg0->unk5 = 5;
        break;
    case 3:
        arg0->unk5 = 8;
        break;
    case 6:
        arg0->unk5 = 0xA;
        break;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    update_on_screen(BASE_OBJECT(arg0), 0x40, 0x40);
}

void func_8007E6F8(struct MainObj* arg0)
{
    s16 x;

    arg0->attack_box = arg0->animation_step.fields.event != 0 ? &magma_dragoon_dive_kick_attack_box : &magma_dragoon_attack_box;
    if (arg0->collision_flags & 8) {
        arg0->unk6++;
        set_animation(arg0, 6);
        arg0->attack_box = &magma_dragoon_attack_box;
        arg0->contact_damage = 4;
        arg0->air_state = 0;
        func_8001540C(2, 2, arg0);
    }
    if (arg0->animation_step.fields.event == 2) {
        x = arg0->x_pos.i.hi;
        if (x < g_Player.x_pos.i.hi)
            arg0->unk15 = x < *(s16*)magma_dragoon_arena_right - 0x50 ? 0x40 : 0;
        else
            arg0->unk15 = x < *(s16*)magma_dragoon_arena_left + 0x50 ? 0x40 : 0;
        arg0->x_speed = arg0->unk15 != 0 ? 0x80000 : -0x80000;
    }
    if (arg0->animation_step.fields.event == 1)
        move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_8007E848(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6 = 0;
        if (arg0->ext.main_65.attack == 0)
            arg0->unk5 = 0xA;
        else if (arg0->ext.main_65.attack == 1)
            arg0->unk5 = 0xB;
        else
            arg0->unk5 = arg0->ext.main_65.attack_repeat++ != 0 ? 0xC : 0xB;
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

static struct ShotObj* main_65_spawn_shot(struct MainObj* arg0, s8 subtype)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x29;
        shot->unk2 = subtype;
        shot->unk7C = (struct WeaponObj*)arg0;
    }
    return shot;
}

void func_8007E95C(struct MainObj* arg0)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        shot = main_65_spawn_shot(arg0, 0);
        func_8001540C(2, (arg0->animation_step.fields.event & 1) ? 6 : 7, shot);
        arg0->animation_step.fields.event = 0;
    }
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk6 = 0;
    if (arg0->ext.main_65.attack == 6) {
        arg0->unk5 = 6;
    } else if (arg0->ext.main_65.attack == 5) {
        arg0->unk5 = 7;
    } else {
        arg0->unk5 = 3;
        set_animation(arg0, 0);
    }
}

static void main_65_throw(struct MainObj* arg0, s16 y_offset)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 1)
        return;
    shot = main_65_spawn_shot(arg0, 3);
    if (shot != NULL) {
        shot->x_pos.i.hi = arg0->x_pos.i.hi + (arg0->unk15 != 0 ? 0x17 : -0x17);
        shot->y_pos.i.hi = arg0->y_pos.i.hi + y_offset;
        func_8001540C(2, 4, arg0);
    }
    arg0->animation_step.fields.event = 0;
}

void func_8007F404(struct MainObj* arg0)
{
    main_65_throw(arg0, 0);
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    if (arg0->ext.main_65.attack == 0)
        arg0->unk5 = 0xB;
    else if (arg0->ext.main_65.attack == 1)
        arg0->unk5 = 0xC;
    else
        arg0->unk5 = arg0->ext.main_65.attack_repeat++ != 0 ? 5 : 0xB;
    arg0->unk6 = 0;
}

void func_8007F5B0(struct MainObj* arg0)
{
    main_65_throw(arg0, 0x28);
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->attack_box = &magma_dragoon_leap_attack_box;
    arg0->unk6 = 0;
    if (arg0->ext.main_65.attack == 0)
        arg0->unk5 = 9;
    else if (arg0->ext.main_65.attack == 4)
        arg0->unk5 = 4;
    else
        arg0->unk5 = 0xA;
}

void func_8007F780(struct MainObj* arg0)
{
    s16 distance;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 1)
        return;
    arg0->air_state = 1;
    arg0->y_speed = 0x40000;
    arg0->gravity = 0x1C00;
    arg0->animation_step.fields.event = 0;
    arg0->unk6++;
    arg0->unk15 = g_Player.x_pos.i.hi < arg0->x_pos.i.hi ? 0 : 0x40;
    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0)
        distance = -distance;
    arg0->x_speed = arg0->unk15 != 0 ? 0x60000 : -0x60000;
    if (distance < 0x30)
        arg0->x_accel = -0x8000;
    else if (distance < 0x60)
        arg0->x_accel = -0x4000;
    else
        arg0->x_accel = -0x2000;
}

void func_8007FAA4(struct MainObj* arg0)
{
    struct MiscObj* misc;

    set_animation(arg0, 0xD);
    arg0->attack_box = &magma_dragoon_attack_box;
    arg0->hurt_box = &magma_dragoon_hurt_box;
    arg0->y_speed = 0x40000;
    arg0->contact_damage = 4;
    arg0->gravity = 0x1C00;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x26;
        misc->unk2 = 4;
        misc->ext.misc_7.position = arg0;
        arg0->ext.main_65.object = (struct MainObj*)misc;
    }
    arg0->unk6++;
}

void func_8007FFFC(struct MainObj* arg0)
{
    struct BaseObj* effect = (struct BaseObj*)arg0->ext.main_65.object;
    struct MiscObj* misc;
    u16 flash;
    s16 scroll;
    s16 y;

    if (effect->active == 0) {
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        if (engine_obj.stage == 0xC) {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        } else {
            engine_obj.unkF = 0x10;
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (effect->unk7 == 0) {
        flash = arg0->unk7E;
        arg0->unk7E = flash - 1;
        if (flash == 0) {
            arg0->unk7E = 5;
            arg0->unk42 ^= 0x8000;
        }
        update_on_screen(BASE_OBJECT(arg0), 0x40, 0x40);
        return;
    }
    if (engine_obj.stage != 4)
        return;
    arg0->unk5++;
    set_animation(arg0, 0x14);
    if (magma_dragoon_arena_center[0] < g_Player.x_pos.i.hi) {
        arg0->unk15 = 0;
        arg0->x_pos.i.hi = *(s16*)magma_dragoon_arena_right - 0x30;
        if (g_Player.ride_state < 0)
            qux_object.unk15 = 0x40;
        player_start_script_action(0x14, 0x40);
        scroll = 0x1490;
    } else {
        arg0->unk15 = 0x40;
        arg0->x_pos.i.hi = *(s16*)magma_dragoon_arena_left + 0x30;
        if (g_Player.ride_state < 0)
            qux_object.unk15 = 0;
        player_start_script_action(0x14, 0);
        scroll = 0x13F0;
    }
    background_objects[0].unk26 = scroll;
    background_objects[0].unk24 = scroll;
    y = magma_dragoon_arena_floor[0];
    arg0->y_pos.i.hi = y;
    if (g_Player.ride_state < 0) {
        qux_object.y_pos.i.hi = y;
        qux_object.x_pos.i.hi = magma_dragoon_arena_center[0];
    } else {
        g_Player.y_pos.i.hi = y;
        g_Player.x_pos.i.hi = magma_dragoon_arena_center[0];
    }
    background_objects[0].unk2A = 0x1EB;
    background_objects[0].unk28 = 0x1EB;
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x26;
        misc->unk2 = 5;
        misc->ext.misc_7.position = arg0;
        arg0->ext.main_65.smoke = (struct MainObj*)misc;
    }
    engine_obj.enable_boss = 0;
    engine_obj.boss_ptr = NULL;
    update_on_screen(BASE_OBJECT(arg0), 0x40, 0x40);
}

extern struct Unk_unk68 double_cyclone_hit_box[];
extern u8 double_cyclone_spawn_offsets[4];
extern u32* D_8011C0F0[5];

void func_80096EA4(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    s8 dx = double_cyclone_spawn_offsets[arg0->unk2 * 2];
    s8 dy = double_cyclone_spawn_offsets[arg0->unk2 * 2 + 1];

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = double_cyclone_hit_box;
    arg0->unk38 = (u8*)player_gfx + player_gfx[8];
    arg0->unk16 = 1;
    arg0->animation_table = D_8011C0F0;
    arg0->unk42 = 0x7801;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x10];
    if (arg0->unk2 == 0) {
        arg0->unk40 = 0x520;
        arg0->x_vel.val = -0x26000;
        arg0->unk15 = 0;
    } else {
        arg0->x_vel.val = 0x26000;
        arg0->unk40 = 0x530;
        arg0->unk15 = 0x40;
    }
    if (g_Player.unk15 == 0) {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + dx;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - dx;
        arg0->unk15 ^= 0x40;
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi + dy;
    arg0->unk49 = arg0->unk2;
    arg0->ext.weapon_7.timer = 0x23;
    arg0->ext.weapon_7.unk90 = 8;
    arg0->ext.weapon_7.unk91 = 4;
    set_animation(arg0, 0);
    func_8001540C(0, 0x1E, arg0);
    arg0->state++;
    double_cyclone_draw(arg0);
}

extern u8 double_cyclone_charged_spawn_offsets[4];
extern struct Unk_unk68 double_cyclone_charged_hit_box[];
void double_cyclone_charged_draw(struct WeaponObj* arg0);

void func_80097430(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    s32 side;
    s8 dx;
    s8 dy;

    arg0->unk38 = (u8*)player_gfx + player_gfx[8];
    arg0->animation_table = D_8011C0F0;
    arg0->unk40 = 0x530;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x10];
    if (arg0->unk2 < 0) {
        side = 1;
        arg0->x_vel.val = 0x60000;
        arg0->unk15 = 0x40;
    } else {
        side = 0;
        arg0->x_vel.val = -0x60000;
        arg0->unk15 = 0;
    }
    dx = double_cyclone_charged_spawn_offsets[side * 2];
    dy = double_cyclone_charged_spawn_offsets[side * 2 + 1];
    if (g_Player.unk15 == 0) {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + dx;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - dx;
        arg0->unk15 ^= 0x40;
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi + dy;
    arg0->ext.weapon_16.timer = 0x32;
    arg0->ext.weapon_16.unk91 = 4;
    arg0->ext.weapon_16.delay = (arg0->unk2 & 0x7F) << 2;
    arg0->unk49 = 1;
    set_animation(arg0, 4);
    func_8001540C(0, 0x1E, arg0);
    func_8001540C(1, 0xA, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    double_cyclone_charged_draw(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x18, 0x30);
}

void func_80097670(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_16.delay != 0) {
        arg0->ext.weapon_16.delay--;
        return;
    }
    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = double_cyclone_charged_hit_box;
    arg0->unk5++;
    update_on_screen(BASE_OBJECT(arg0), 0x18, 0x30);
}

extern struct VisualSpawnOffset double_cyclone_charged_fan_offsets[2];
void double_cyclone_charged_fan_draw(struct VisualObj* arg0);

void func_800B2698(struct VisualObj* arg0)
{
    s32* player_gfx;
    s32* sprite_frames;
    struct VisualSpawnOffset offset;

    if (g_Player.input_locked != 0 || g_Player.capsule_state != 0 || g_Player.weapon != 7 || g_Player.actions_reset != 0 || g_Player.hp == 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->state != 0) {
        if (arg0->unk5C.value == 0) {
            ZeroObjectState(OBJECT_HEADER(arg0));
            return;
        }
        arg0->unk5C.value--;
        animate_object(ANIMATED_OBJECT(arg0));
        double_cyclone_charged_fan_draw(arg0);
        return;
    }
    arg0->on_screen = 1;
    player_gfx = SP_PLAYER_GFX;
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + player_gfx[8];
    arg0->animation_table = D_8011C0F0;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x10];
    offset = double_cyclone_charged_fan_offsets[arg0->unk2];
    arg0->unk15 = arg0->unk2 != 0 ? 0x40 : 0;
    if (g_Player.unk15 == 0) {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + offset.x;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - offset.x;
        arg0->unk15 ^= 0x40;
    }
    arg0->unk5C.value = 0x10;
    arg0->unk49 = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi + offset.y;
    set_animation(arg0, 3);
    arg0->state++;
    double_cyclone_charged_fan_draw(arg0);
}

extern u8 magma_fire_wave_hit_box[4];
extern u8 magma_fire_pillar_hit_boxes[][4];
extern u8 magma_fire_ember_hit_box[4];
extern u8 magma_fire_ember_terrain_box[4];
extern u8 magma_fire_burst_hit_box[4];
extern u8 magma_fire_burst_terrain_box[4];
extern s16 magma_fire_wave_offsets[8];

void func_800A56E4(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;

    arg0->unk40 = owner->unk40;
    arg0->animation_table = (u32**)owner->animation_table;
    arg0->unk3C = (void*)owner->sprite_frames;
    arg0->unk5C = 0;
    arg0->unk16 = 1;
    arg0->unk42 = owner->unk42 & 0x7FFF;
    arg0->bg_offset = owner->bg_offset;
    switch (arg0->unk2) {
    case 0:
        arg0->unk58.data = (u8*)D_801060F0;
        arg0->unk54 = NULL;
        arg0->unk60 = 9;
        arg0->unk15 = owner->unk15;
        arg0->x_pos.val = owner->x_pos.val + (arg0->unk15 != 0 ? 0x180000 : -0x180000);
        arg0->y_pos.val = owner->y_pos.val + 0x100000;
        arg0->y_vel.val = 0x20000;
        arg0->unk5 = 2;
        arg0->timer = 7;
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x60000 : -0x60000;
        arg0->unk50.data = magma_fire_wave_hit_box;
        arg0->unk68 = NULL;
        arg0->state++;
        set_animation(arg0, 0x1C);
        break;
    case 1:
        arg0->unk58.data = (u8*)D_80105FF0;
        arg0->unk15 = 0;
        arg0->unk54 = NULL;
        arg0->unk60 = 4;
        arg0->x_pos.val = owner->x_pos.val + (owner->unk15 != 0 ? -0x100000 : 0x100000);
        arg0->y_pos.val = owner->y_pos.val - 0x200000;
        arg0->x_vel.val = magma_fire_wave_offsets[arg0->unk7] << 12;
        if (arg0->unk15 != 0)
            arg0->x_vel.val = -arg0->x_vel.val;
        arg0->y_vel.val = 0x50000;
        arg0->unk5 = 3;
        arg0->unk50.data = (u8*)magma_fire_pillar_hit_boxes;
        arg0->unk68 = NULL;
        arg0->state++;
        set_animation(arg0, 0x1D);
        break;
    case 2:
        arg0->unk58.data = (u8*)D_801060F0;
        arg0->unk50.data = magma_fire_ember_hit_box;
        arg0->unk54 = NULL;
        arg0->unk68 = (struct Unk_unk68*)magma_fire_ember_terrain_box;
        arg0->unk60 = 4;
        arg0->unk15 = owner->unk15;
        arg0->x_pos.val = owner->x_pos.val;
        arg0->y_pos.val = owner->y_pos.val - 0x400000;
        arg0->y_vel.val = 0x1C000;
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x40000 : -0x40000;
        arg0->unk28 = 0;
        arg0->unk2C = 0x1300;
        arg0->unk5 = 4;
        arg0->state++;
        set_animation(arg0, 0x1F);
        break;
    case 3:
        arg0->unk58.data = (u8*)D_801060F0;
        arg0->unk50.data = magma_fire_burst_hit_box;
        arg0->unk68 = (struct Unk_unk68*)magma_fire_burst_terrain_box;
        arg0->unk60 = 6;
        arg0->unk5 = 5;
        arg0->unk54 = NULL;
        arg0->timer = 3;
        arg0->state++;
        arg0->unk15 = owner->unk15;
        set_animation(arg0, 0x1B);
        break;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
}

extern u8 magma_fire_breath_hit_box[4];
extern u8 magma_fire_column_hit_box[4];
extern u16 magma_fire_pillar_positions[8];

void func_800A5AA4(struct ShotObj* arg0)
{
    struct BaseObj* owner = (struct BaseObj*)arg0->unk7C;

    func_8002D9BC(arg0);
    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->on_screen != 0)
        return;
    if (owner->state != 1) {
        arg0->unk5 = 0;
        arg0->state++;
        return;
    }
    set_animation(arg0, 0x1E);
    arg0->unk54 = magma_fire_breath_hit_box;
    arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + magma_fire_pillar_positions[arg0->unk7] + (get_random() & 0x1F);
    arg0->x_vel.val = -0x60000;
    arg0->y_vel.val = -0x60000;
    arg0->unk6++;
    arg0->timer = (arg0->unk7 << 3) + 0x64;
    arg0->unk8A = 4;
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi - 0x20;
}

void func_800A5BA8(struct ShotObj* arg0)
{
    s16 timer = arg0->timer;
    s16 floor;

    if (timer >= 2) {
        arg0->timer = timer - 1;
        return;
    }
    if (timer == 1) {
        arg0->timer = 0;
        start_screen_shake_y(0x78, 4, 2);
    }
    func_8002D9BC(arg0);
    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    floor = engine_obj.stage == 0xC ? 0x6C8 : 0x2B8;
    if (arg0->y_pos.i.hi <= floor)
        return;
    set_animation(arg0, 0x20);
    arg0->y_pos.i.hi = floor;
    arg0->unk6++;
}

void func_800A5E60(struct ShotObj* arg0)
{
    func_8002D9BC(arg0);
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step != 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
        return;
    }
    arg0->unk60 = 9;
    arg0->unk6++;
    set_animation(arg0, 0x23);
    if (engine_obj.stage == 0xC)
        arg0->x_pos.i.hi = arg0->unk15 != 0 ? 0x2C8 : 0x138;
    else
        arg0->x_pos.i.hi = arg0->unk15 != 0 ? 0x15A8 : 0x1418;
    arg0->unk50.data = magma_fire_column_hit_box;
    arg0->y_vel.val = 0x40000;
    arg0->x_vel.val = 0;
    arg0->timer = 0xC8;
    arg0->y_pos.i.hi += 0x12C;
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x80);
}

void func_800A60D0(struct ShotObj* arg0)
{
    struct ShotObj* child;

    animate_object(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
    if (--arg0->timer == 0 && (arg0->unk70 & 3) == 0) {
        child = find_free_shot_obj();
        if (child != NULL) {
            child->active = 0x41;
            child->id = 0x29;
            child->unk2 = 3;
            child->unk7C = (struct WeaponObj*)arg0;
            child->x_pos.i.hi = arg0->x_pos.i.hi + (arg0->unk15 != 0 ? 0x18 : -0x18);
            child->timer = 3;
            child->y_pos.i.hi = arg0->y_pos.i.hi;
        }
    }
    if (arg0->animation_step.fields.frame_index == 0x8A)
        arg0->unk50.data = NULL;
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->state++;
    }
}

extern u8 cyber_peacock_attack_animations[];
extern u8 cyber_peacock_attack_steps[];
void cyber_peacock_face_player(struct MainObj* arg0);
u8 cyber_peacock_choose_attack(struct MainObj* arg0);
void cyber_peacock_start_teleport(struct MainObj* arg0);

void func_8007CA68(struct MainObj* arg0)
{
    s16 timer = --arg0->unk7C;
    u8 attack;
    s16 base;

    if (timer != 0) {
        if (timer == 0x14) {
            arg0->ext.main_64.target_x = g_Player.x_pos.i.hi;
            arg0->ext.main_64.target_y = g_Player.y_pos.i.hi - 0x18;
        }
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }
    arg0->unk7 = 0;
    arg0->unk6++;
    arg0->x_pos.i.hi = arg0->ext.main_64.target_x;
    arg0->y_pos.i.hi = arg0->ext.main_64.target_y;
    cyber_peacock_face_player(arg0);
    attack = cyber_peacock_choose_attack(arg0);
    arg0->ext.main_64.next_step = cyber_peacock_attack_steps[attack];
    set_animation(arg0, cyber_peacock_attack_animations[attack]);
    arg0->unk2 = attack;
    if (attack == 0) {
        func_8001540C(2, 0xC7, arg0);
        return;
    }
    base = arg0->ext.main_64.arena_x;
    switch ((s8)attack) {
    case 1:
        arg0->y_pos.i.hi = arg0->ext.main_64.arena_y + 0xB3;
        arg0->ext.main_64.target_y = arg0->y_pos.i.hi;
        func_8001540C(2, 0xC7, arg0);
        break;
    case 2:
        if (g_Player.x_pos.i.hi - base < 0xA0) {
            arg0->x_pos.i.hi = base + 0x90;
            arg0->unk15 = 0x40;
        } else {
            arg0->x_pos.i.hi = base + 0xE0;
            arg0->unk15 = 0;
        }
        arg0->ext.main_64.target_x = arg0->x_pos.i.hi;
        arg0->y_pos.i.hi = arg0->ext.main_64.arena_y + 0xB3;
        arg0->ext.main_64.target_y = arg0->y_pos.i.hi;
        break;
    case 3:
        if (g_Player.x_pos.i.hi - base < 0xA0) {
            arg0->x_pos.i.hi = base + 0x110;
            arg0->unk15 = 0;
        } else {
            arg0->x_pos.i.hi = base + 0x50;
            arg0->unk15 = 0x40;
        }
        arg0->ext.main_64.target_x = arg0->x_pos.i.hi;
        arg0->y_pos.i.hi = arg0->ext.main_64.arena_y + 0x70;
        arg0->ext.main_64.target_y = arg0->y_pos.i.hi;
        break;
    }
    arg0->unk2--;
}

void func_8007D5D0(struct MainObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        arg0->ext.main_64.shot_count = 0;
        arg0->unk6++;
        cyber_peacock_start_teleport(arg0);
        set_animation(arg0, 0x20);
        break;
    case 1:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk6++;
            arg0->unk7C = 0x3C;
            set_animation(arg0, 0x22);
            break;
        }
        arg0->x_speed += arg0->x_accel;
        if (main_bss_state.frame_counter & 1)
            arg0->x_pos.val = ((s16)arg0->ext.main_64.target_x << 16) + arg0->x_speed;
        else
            arg0->x_pos.val = ((s16)arg0->ext.main_64.target_x << 16) - arg0->x_speed;
        animate_object(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        cyber_peacock_start_teleport(arg0);
        arg0->x_speed = 0x160000;
        arg0->ext.main_64.flash_timer = 0;
        set_animation(arg0, 0x22);
        break;
    }
}

void func_8007D710(struct MainObj* arg0)
{
    s16 count;

    switch (arg0->unk6) {
    case 0:
        arg0->ext.main_64.shot_count = 0;
        arg0->unk7C = 0;
        arg0->unk7 = 0;
        arg0->unk6++;
        set_animation(arg0, 0x21);
        func_8001540C(2, 0xC8, arg0);
        arg0->attack_box = NULL;
        arg0->hurt_box = NULL;
        break;
    case 1:
        count = arg0->unk7C;
        if (count >= 3) {
            arg0->unk7C = 0x3C;
            arg0->unk6++;
            set_animation(arg0, 0x22);
            break;
        }
        if (arg0->animation_step.fields.relative_step < 0)
            arg0->unk7C = count + 1;
        animate_object(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        cyber_peacock_start_teleport(arg0);
        arg0->x_speed = 0x160000;
        arg0->ext.main_64.flash_timer = 0;
        set_animation(arg0, 0x22);
        break;
    }
}

extern void (*cyber_peacock_step_funcs[6])();

void func_8007D838(struct MainObj* arg0)
{
    s32 hit;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (arg0->ext.main_64.hit_count >= 7) {
        arg0->ext.main_64.hit_count = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
    ((void (*)(struct MainObj*))cyber_peacock_step_funcs[arg0->unk5])(arg0);
    hit = func_8002DD04(arg0);
    if (arg0->ext.main_64.flash_timer != 0) {
        arg0->ext.main_64.flash_timer--;
        arg0->hp = arg0->ext.main_64.saved_health;
        if (arg0->ext.main_64.flash_timer & 1)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
    } else if (hit < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
    } else if (hit > 0 && hit != 0x7F) {
        if (hit == 4 || hit == 0x24) {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            arg0->ext.main_64.flash_timer = 0x40;
            arg0->ext.main_64.saved_health = arg0->hp;
        } else {
            arg0->ext.main_64.flash_timer = 0x40;
            arg0->ext.main_64.saved_health = arg0->hp;
            arg0->ext.main_64.hit_count++;
        }
    }
    func_8002D9BC(arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

extern void (*laser_target_step_funcs[])(struct ItemObj*);
void laser_target_hold(struct ItemObj* arg0);

void func_800C5F90(struct ItemObj* arg0)
{
    struct MainObj* owner = arg0->unk7C.owner;

    if (owner->state != 1 || (owner->unk5 != 3 && owner->unk2 != 2)) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (owner->unk5 >= 4) {
        if (arg0->tail_ext.unk1.unk84.previous_value == 0)
            ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    laser_target_step_funcs[arg0->unk5](arg0);
    laser_target_hold(arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

extern u8 peacock_missile_hit_box[4];
extern u8 peacock_missile_terrain_box[4];
extern s16 peacock_missile_launch_offsets[8][2];
extern u8 peacock_missile_turn_steps_ccw[8];
extern u8 peacock_missile_turn_steps_cw[8];

void func_800A63B0(struct ShotObj* arg0)
{
    struct MainObj* boss = arg0->backref;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->timer = 0xA;
    arg0->unk16 = 4;
    arg0->unk68 = (struct Unk_unk68*)peacock_missile_terrain_box;
    arg0->unk50.data = peacock_missile_hit_box;
    arg0->unk5C = 3;
    arg0->unk60 = 6;
    arg0->unk90.val = 0x6E;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk8A = 0;
    arg0->unk84.value = 0;
    arg0->unk54 = NULL;
    arg0->unk58.data = NULL;
    arg0->unk61 = 0;
    arg0->unk8C.word = 0;
    if (boss->unk15 != 0) {
        arg0->x_pos.i.hi -= peacock_missile_launch_offsets[arg0->unk2][0];
        arg0->unk84.value = peacock_missile_turn_steps_cw[arg0->unk2];
    } else {
        arg0->x_pos.i.hi += peacock_missile_launch_offsets[arg0->unk2][0];
        arg0->unk84.value = peacock_missile_turn_steps_ccw[arg0->unk2];
    }
    arg0->y_pos.i.hi += peacock_missile_launch_offsets[arg0->unk2][1];
    set_animation(arg0, (arg0->unk84.value >> 1) + 0xD);
    set_velocity_from_angle(MOVING_OBJECT(arg0), (u8)arg0->unk84.value);
    arg0->unk2C = 0;
    arg0->unk28 = 0;
    arg0->x_vel.val <<= 2;
    arg0->y_vel.val <<= 2;
}

void func_800A6510(struct ShotObj* arg0)
{
    s32 target;
    s32 direction;

    if (arg0->timer != 0) {
        arg0->timer--;
    } else if ((main_bss_state.frame_counter & 1) == 0) {
        target = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(arg0->unk7C));
        direction = arg0->unk84.value;
        if (((direction - (target & 0xFF)) & 0x1F) >= 2) {
            direction = ((u32)((target - direction) & 0x1F) < 0x10) ? direction + 1 : direction - 1;
            arg0->unk84.value = direction & 0x1F;
            set_velocity_from_angle(MOVING_OBJECT(arg0), direction & 0x1E);
            arg0->x_vel.val <<= 2;
            arg0->y_vel.val <<= 2;
            set_animation(arg0, (arg0->unk84.value >> 1) + 0xD);
        }
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_800A666C(struct ShotObj* arg0, s32 x_range, s32 y_range)
{
    struct MiscObj* misc = find_free_misc_obj();
    u8 amount;

    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 0x31;
    misc->unk2 = 4;
    misc->x_pos.val = arg0->x_pos.val;
    misc->y_pos.val = arg0->y_pos.val;
    amount = x_range & get_random();
    if (get_random() & 1)
        misc->x_pos.i.hi += amount;
    else
        misc->x_pos.i.hi -= amount;
    amount = y_range & get_random();
    if (get_random() & 1)
        misc->y_pos.i.hi += amount;
    else
        misc->y_pos.i.hi -= amount;
    misc->animation_table = arg0->animation_table;
    misc->unk40 = arg0->unk40;
    misc->unk3C = arg0->unk3C;
    misc->unk42 = arg0->unk42 & 0x7FFF;
    misc->ext.misc_49.owner = arg0;
    misc->unk15 = 0;
    misc->unk16 = arg0->unk16;
}

extern u8 double_afterimage_angles[4];

void func_800D1990(struct MiscObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 3;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    if (arg0->unk2 == 4) {
        arg0->ext.misc_49.timer = 0x14;
        set_animation(arg0, 0x1E);
        return;
    }
    set_animation(arg0, 0x12);
    set_velocity_from_angle(MOVING_OBJECT(arg0), double_afterimage_angles[arg0->unk2]);
    arg0->unk2C = 0x4000;
    arg0->ext.misc_49.timer = 0xA;
    arg0->unk28 = 0;
    arg0->x_vel.val <<= 1;
    arg0->y_vel.val *= 3;
}

void func_800D1A48(struct MiscObj* arg0)
{
    if (--arg0->ext.misc_49.timer == 0) {
        arg0->on_screen = 0;
        arg0->state = 2;
        return;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 != 4)
        move_with_gravity(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

extern struct Unk_unk68 storm_owl_hurt_box;
extern void (*storm_owl_step_funcs[])(struct MainObj*);
void storm_owl_spawn_hit_flash(struct PlayerObj* arg0);

void func_800751AC(struct MainObj* arg0)
{
    arg0->hp = 0;
    arg0->contact_damage = 6;
    arg0->invincibility_timer = 0;
    if (engine_obj.stage != 0xC) {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    } else {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
        arg0->unk42 = 0x7888;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
    }
    arg0->collision_data = D_80107B78;
    arg0->animation_table = (const u8* const*)storm_owl_animations;
    arg0->unk16 = 5;
    arg0->terrain_box = &storm_owl_slam_terrain_box;
    arg0->hurt_box = &storm_owl_hurt_box;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->attack_box = &storm_owl_attack_box;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = g_Player.x_pos.val >= arg0->x_pos.val ? 0x40 : 0;
    set_animation(arg0, 1);
    arg0->state = 1;
    arg0->unk5 = 2;
    memset(&arg0->ext.main_60, 0, sizeof(arg0->ext.main_60));
    arg0->unk6 = 0;
    arg0->unk7 = 0x28;
}

static void main_60_flash(struct MainObj* arg0)
{
    storm_owl_spawn_hit_flash((struct PlayerObj*)arg0);
    arg0->collision_data = D_801060F0;
    arg0->ext.main_60.flash_timer = 0x40;
    arg0->ext.main_60.flash_mode = 1;
}

static void main_60_stagger(struct MainObj* arg0)
{
    if (arg0->unk5 != 0xB)
        func_8001540C(2, 0xBD, arg0);
    arg0->unk5 = 0xB;
    arg0->unk6 = 0;
}

void func_80075320(struct MainObj* arg0)
{
    s32 hit = func_8002DD04(arg0);

    if (arg0->unk5 != 0)
        arg0->ext.main_60.saved_unk5 = arg0->unk5;
    if (hit < 0) {
        g_Player.spike_immune = 1;
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        return;
    }
    if (arg0->ext.main_60.flash_mode == 1) {
        if ((arg0->ext.main_60.flash_timer & 1) == 0)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (--arg0->ext.main_60.flash_timer == 0) {
            arg0->collision_data = D_80107B78;
            arg0->ext.main_60.flash_mode = 0;
        }
    } else if (hit != 0) {
        if (engine_obj.cur_character == CHARACTER_X) {
            if (hit == 7 || hit == 0x10) {
                if (arg0->unk5 != 0xB)
                    func_8001540C(2, 0xBD, arg0);
                if (hit == 0x10) {
                    arg0->collision_data = D_80106070;
                    arg0->unk42 &= 0x7FFF;
                }
                arg0->unk5 = 0xB;
                arg0->unk6 = 0;
                arg0->active |= 4;
            } else {
                main_60_flash(arg0);
            }
        } else {
            switch (hit - 0x1A) {
            case 0:
            case 2:
            case 4:
            case 6:
            case 7:
            case 8:
                main_60_flash(arg0);
                break;
            case 9:
            case 10:
                if (arg0->ext.main_60.flash_mode == 0) {
                    arg0->ext.main_60.flash_mode = 2;
                    arg0->ext.main_60.flash_timer = 8;
                } else {
                    main_60_flash(arg0);
                }
                break;
            case 11:
                main_60_stagger(arg0);
                break;
            }
        }
    } else if (arg0->ext.main_60.flash_mode == 2) {
        if (--arg0->ext.main_60.flash_timer == 0)
            arg0->ext.main_60.flash_mode = 0;
    }
    if (arg0->unk17 < 2 && --arg0->unk7 == 0) {
        func_8001540C(2, (get_random() & 1) ? 0xB7 : 0xB8, arg0);
        arg0->unk7 = 0x28;
    }
    storm_owl_step_funcs[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
}

void storm_owl_spawn_intro_wind(struct MainObj* arg0);

void func_80075944(struct MainObj* arg0)
{
    set_animation(arg0, 0);
    if (engine_obj.stage == 7) {
        arg0->unk15 = 0x40;
        arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0x20;
    } else {
        arg0->unk15 = 0;
        arg0->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0x120;
    }
    arg0->y_speed = -0x20000;
    arg0->y_pos.i.hi = background_objects[0].y_pos.i.hi - 0x20;
    storm_owl_spawn_intro_wind(arg0);
    func_8001540C(2, 0xB4, arg0);
    arg0->unk6++;
}

void func_80075C6C(struct MainObj* arg0)
{
    const Main60Waypoint* waypoint;
    u8 index;

    animate_object(ANIMATED_OBJECT(arg0));
    set_animation(arg0, 1);
    index = (engine_obj.stage != 7) * 2;
    arg0->ext.main_60.corner = index;
    waypoint = &storm_owl_waypoints[index];
    set_velocity_from_angle(MOVING_OBJECT(arg0),
        angle_to_point(OBJECT_HEADER(arg0), (waypoint->x + background_objects[0].x_pos.i.hi) << 16,
            (waypoint->y + background_objects[0].y_pos.i.hi) << 16)
            & 0xFF);
    arg0->x_speed <<= 1;
    arg0->y_speed <<= 1;
    arg0->unk6++;
}

void func_80075E78(struct MainObj* arg0)
{
    const Main60Waypoint* waypoint = &storm_owl_waypoints[arg0->ext.main_60.corner];
    s32 target_x = (waypoint->x + background_objects[0].x_pos.i.hi) << 16;
    s32 target_y = (waypoint->y + background_objects[0].y_pos.i.hi) << 16;
    s32 dx;
    s32 dy;
    u8 next;

    set_velocity_from_angle(MOVING_OBJECT(arg0), angle_to_point(OBJECT_HEADER(arg0), target_x, target_y) & 0xFF);
    arg0->x_speed <<= 1;
    arg0->y_speed <<= 1;
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    dx = target_x - arg0->x_pos.val;
    if (dx >= 0 ? dx > 0x3FFFF : arg0->x_pos.val - target_x > 0x3FFFF)
        return;
    dy = target_y - arg0->y_pos.val;
    if (dy >= 0 ? dy > 0x3FFFF : arg0->y_pos.val - target_y > 0x3FFFF)
        return;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    if (arg0->ext.main_60.pattern[0] == 0xFF)
        storm_owl_choose_pattern(arg0);
    next = *arg0->ext.main_60.pattern++;
    arg0->unk5 = next;
    if (arg0->unk5 == 3)
        arg0->unk6++;
    else
        arg0->unk6 = 0;
}

void storm_owl_choose_corner(struct MainObj* arg0);

static void main_60_release(struct MainObj* arg0)
{
    g_Player.stun_timer = 0;
    arg0->contact_damage = 6;
    arg0->terrain_box = &storm_owl_slam_terrain_box;
    arg0->attack_box = &storm_owl_attack_box;
    arg0->unk62 = 0;
    arg0->unk16 = 5;
}

void func_800760C4(struct MainObj* arg0)
{
    s16 distance;

    animate_object(ANIMATED_OBJECT(arg0));
    move_with_gravity(ANIMATED_OBJECT(arg0));
    arg0->y_speed += 0x400;
    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if ((distance < 0 ? -distance : distance) > 0x30)
        return;
    if ((get_random() & 7) < 5) {
        arg0->unk5 = g_Player.y_pos.i.hi < arg0->y_pos.i.hi ? 6 : 4;
        arg0->unk6 = 0;
        arg0->x_speed = 0;
        arg0->y_speed = 0;
    } else {
        arg0->ext.main_60.corner ^= 2;
        arg0->unk6++;
    }
}

void func_80076364(struct MainObj* arg0)
{
    s16 distance;

    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    if (arg0->y_pos.i.hi + 0x14 >= g_Player.y_pos.i.hi) {
        arg0->x_speed = arg0->unk15 != 0 ? 0x20000 : -0x20000;
        arg0->y_speed = -0x10000;
        set_animation(arg0, 1);
        main_60_release(arg0);
        arg0->unk6 = 5;
        return;
    }
    if (g_Player.stun_timer != 0) {
        func_8001540C(2, 0xBA, arg0);
        distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
        if ((distance < 0 ? -distance : distance) < 8)
            arg0->x_speed = 0;
        else
            arg0->x_speed = arg0->x_pos.i.hi < g_Player.x_pos.i.hi ? 0x10000 : -0x10000;
        arg0->y_speed = 0;
        arg0->unk6++;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(arg0);
        main_60_release(arg0);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_8007651C(struct MainObj* arg0)
{
    s16 x;
    s16 background_x;
    s16 distance;
    s32 stop = 0;

    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if ((distance < 0 ? -distance : distance) >= 8)
        return;
    x = arg0->x_pos.i.hi;
    background_x = background_objects[0].x_pos.i.hi;
    if (x < background_x + 0x40 && arg0->x_speed < 0)
        stop = 1;
    else if (background_x + 0x100 < x && arg0->x_speed > 0)
        stop = 1;
    else if (arg0->unk15 == 0 ? arg0->x_speed > 0 : arg0->x_speed < 0)
        stop = 1;
    if (stop)
        arg0->x_speed = 0;
    arg0->y_speed = 0x10000;
    arg0->unk7C = 0x3C;
    arg0->unk6++;
}

void storm_owl_spawn_volley_feather(struct MainObj* arg0, s8 arg1);

void func_80076D14(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    if (++arg0->ext.main_60.shot_count >= 4) {
        arg0->unk7C = 0x3C;
        arg0->unk6++;
    } else {
        arg0->unk7C = 0x3D;
    }
    storm_owl_spawn_volley_feather(arg0, arg0->ext.main_60.shot_count);
    func_8001540C(2, 0xB5, arg0);
}

void func_80077580(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    if ((get_random() & 7) < 3) {
        arg0->unk6++;
        func_8001540C(2, 0xBC, arg0);
    } else {
        arg0->unk6 += 2;
    }
    arg0->unk7C = 0x1E;
}

static void main_60_shot_setup(struct ShotObj* shot, struct MainObj* arg0, s8 id, s8 subtype, s8 layer)
{
    shot->active = 0x41;
    shot->id = id;
    shot->unk2 = subtype;
    shot->unk7C = (struct WeaponObj*)arg0;
    shot->animation_table = (u32**)storm_owl_animations;
    shot->unk42 = arg0->unk42;
    shot->unk3C = (void*)arg0->sprite_frames;
    shot->unk40 = arg0->unk40;
    shot->unk16 = layer;
    shot->bg_offset = arg0->bg_offset;
    shot->unk15 = arg0->unk15;
}

void func_80078180(struct MainObj* arg0)
{
    struct ShotObj* shot;
    u32 i;

    if (arg0->ext.main_60.storm_active == 1) {
        if (--arg0->unk7E != 0)
            return;
        for (i = 0; i < 4; i++) {
            shot = find_free_shot_obj();
            if (shot != NULL)
                main_60_shot_setup(shot, arg0, 0x25, i + 5, 5);
        }
    }
    arg0->unk7E = 10;
}

void func_80078314(struct MainObj* arg0)
{
    static const s16 x_offsets[3] = { 0, -0x30, 0x30 };
    static const s16 shot_timers[3] = { 0x20, 0x28, 0x28 };
    struct VisualObj* visual;
    struct ShotObj* shot;
    u32 i;

    for (i = 0; i < 3; i++) {
        visual = find_free_visual_obj();
        if (visual == NULL)
            continue;
        visual->active = 0x41;
        visual->id = 0x1C;
        visual->unk2 = 1;
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->animation_table = (u32**)storm_owl_animations;
        visual->unk42 = arg0->unk42;
        visual->unk3C = (void*)arg0->sprite_frames;
        visual->unk40 = arg0->unk40;
        visual->unk16 = 2;
        visual->bg_offset = arg0->bg_offset;
        visual->unk15 = arg0->unk15;
        visual->x_pos.i.hi = g_Player.x_pos.i.hi + x_offsets[i];
        visual->unk5C.fields.mode = i;
        visual->y_pos.i.hi = background_objects[0].y_pos.i.hi + 0x60;
    }
    for (i = 0; i < 3; i++) {
        shot = find_free_shot_obj();
        if (shot == NULL)
            continue;
        main_60_shot_setup(shot, arg0, 0x26, 5, 2);
        shot->timer = shot_timers[i];
        shot->x_pos.i.hi = g_Player.x_pos.i.hi + x_offsets[i];
        shot->y_pos.i.hi = background_objects[0].y_pos.i.hi + 0x150;
    }
}

extern s8 owl_feather_hit_box[4];
extern u16 owl_feather_velocities[11][2];

void func_800A3CB4(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s16 background_x;
    s16 background_y;
    u16 best;
    u16 dx;
    u16 dy;
    u8 index;
    u8 i;

    arg0->on_screen = 1;
    arg0->unk58.data = (u8*)D_801060F0;
    arg0->unk60 = 6;
    arg0->unk68 = NULL;
    arg0->unk54 = (u8*)owl_feather_hit_box;
    arg0->unk5C = 0;
    arg0->unk84.value = 0;
    arg0->unk8C.word = 0;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    set_animation(arg0, 0xD);
    arg0->unk50.data = (u8*)owl_feather_hit_box;
    arg0->x_pos.i.hi = owner->x_pos.i.hi + (owner->unk15 != 0 ? 0x26 : -0x26);
    arg0->y_pos.i.hi = owner->y_pos.i.hi + 6;
    if (arg0->unk2 == 0) {
        set_velocity_from_angle(MOVING_OBJECT(arg0), angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
        arg0->x_vel.val <<= 2;
        arg0->y_vel.val <<= 2;
        return;
    }
    if (arg0->unk2 >= 5) {
        arg0->x_pos.i.hi = owner->x_pos.i.hi;
        arg0->y_pos.i.hi = owner->y_pos.i.hi;
        set_velocity_from_angle(MOVING_OBJECT(arg0), (owner->ext.main_60.storm_timer + (arg0->unk2 - 5) * 8 + 4) & 0x1F);
        arg0->x_vel.val <<= 3;
        arg0->y_vel.val <<= 3;
        return;
    }
    background_x = background_objects[0].x_pos.i.hi;
    background_y = background_objects[0].y_pos.i.hi;
    if (arg0->unk2 == 1) {
        best = 0xFFFF;
        index = 0;
        for (i = 0; i < 11; i++) {
            s32 point_x = background_x + owl_feather_velocities[i][0];
            s32 point_y = background_y + owl_feather_velocities[i][1];
            dx = g_Player.x_pos.i.hi - point_x >= 0 ? g_Player.x_pos.i.hi - point_x : point_x - g_Player.x_pos.i.hi;
            dy = g_Player.y_pos.i.hi - point_y >= 0 ? g_Player.y_pos.i.hi - point_y : point_y - g_Player.y_pos.i.hi;
            if ((u16)(dx + dy) < best) {
                best = dx + dy;
                index = i;
            }
        }
        arg0->unk84.value = index;
    } else {
        do {
            arg0->unk84.value = (u8)get_random() % 11;
        } while ((owner->ext.main_60.feather_mask >> arg0->unk84.value) & 1);
    }
    owner->ext.main_60.feather_mask += 1 << arg0->unk84.value;
    set_velocity_from_angle(MOVING_OBJECT(arg0),
        angle_to_point(OBJECT_HEADER(arg0), (background_x + owl_feather_velocities[arg0->unk84.value][0]) << 16,
            (background_y + owl_feather_velocities[arg0->unk84.value][1]) << 16)
            & 0xFF);
    arg0->x_vel.val <<= 1;
    arg0->y_vel.val <<= 1;
}

void func_800A3FEC(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s32 target_x;
    s32 target_y;
    s32 d;

    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);
    func_8002DD04((struct MainObj*)arg0);
    if (arg0->unk2 != 0 && arg0->unk2 < 5) {
        if (owner->ext.main_60.feathers_holding == 0) {
            target_x = background_objects[0].x_pos.i.hi + owl_feather_velocities[arg0->unk84.value][0];
            target_y = background_objects[0].y_pos.i.hi + owl_feather_velocities[arg0->unk84.value][1];
            set_velocity_from_angle(MOVING_OBJECT(arg0),
                angle_to_point(OBJECT_HEADER(arg0), target_x << 16, target_y << 16) & 0xFF);
            arg0->x_vel.val <<= 1;
            arg0->y_vel.val <<= 1;
            d = arg0->x_pos.i.hi - target_x;
            if ((d < 0 ? -d : d) < 8)
                arg0->x_vel.val = 0;
            d = arg0->y_pos.i.hi - target_y;
            if ((d < 0 ? -d : d) < 8)
                arg0->y_vel.val = 0;
        } else if (arg0->unk8C.word == 0) {
            set_velocity_from_angle(MOVING_OBJECT(arg0), angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
            arg0->unk8C.word = 1;
            arg0->x_vel.val *= 5;
            arg0->y_vel.val *= 5;
        }
    }
    if (owner->state == 2 || owner->active == 0 || func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) != 0) {
        arg0->state++;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}

extern u8 owl_cyclone_hit_box[4];
extern u8 owl_cyclone_column_box[4];

void func_800A42C8(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s16 dx = 0;
    s16 dy = 0;

    arg0->unk58.data = (u8*)D_80105FF0;
    arg0->unk60 = 6;
    arg0->unk54 = owl_cyclone_hit_box;
    arg0->unk50.data = owl_cyclone_hit_box;
    arg0->unk84.value = 4;
    arg0->state++;
    arg0->on_screen = 1;
    arg0->unk68 = NULL;
    arg0->unk5C = 1;
    arg0->unk42 &= 0x7FFF;
    switch ((u8)arg0->unk2) {
    case 0:
        set_animation(arg0, 0xF);
        arg0->x_vel.val = 0x45000;
        arg0->y_vel.val = 0x45000;
        dx = 0xB;
        dy = -0x15;
        break;
    case 1:
        set_animation(arg0, 0x10);
        arg0->x_vel.val = 0x52800;
        arg0->y_vel.val = 0x2A000;
        dx = 0x10;
        dy = -0x13;
        break;
    case 2:
        set_animation(arg0, 0x11);
        arg0->x_vel.val = 0x60000;
        arg0->y_vel.val = 0;
        if (owner->unk17 == 4) {
            dx = 0x19;
            dy = -6;
        } else {
            dx = 0x13;
            dy = -0xD;
        }
        break;
    case 3:
        set_animation(arg0, 0x12);
        arg0->x_vel.val = 0x52800;
        arg0->y_vel.val = -0x2A000;
        dx = 0x19;
        dy = 0;
        break;
    case 4:
        set_animation(arg0, 0x13);
        arg0->x_vel.val = 0x45000;
        arg0->y_vel.val = -0x45000;
        dx = 0x14;
        dy = 5;
        break;
    case 5:
        arg0->unk58.data = (u8*)D_80105FF0;
        arg0->unk50.data = owl_cyclone_column_box;
        arg0->unk54 = NULL;
        set_animation(arg0, 0x1D);
        arg0->unk60 = 9;
        arg0->on_screen = 0;
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->unk84.value = 0;
        arg0->timer = 1;
        break;
    }
    if (arg0->unk2 >= 5)
        return;
    if (owner->unk15 == 0) {
        arg0->x_pos.i.hi = owner->x_pos.i.hi - dx;
        arg0->x_vel.val = -arg0->x_vel.val;
    } else {
        arg0->x_pos.i.hi = owner->x_pos.i.hi + dx;
    }
    arg0->y_pos.i.hi = owner->y_pos.i.hi + dy;
}

extern struct Unk_unk68 aiming_laser_reticle_box[];
void aiming_laser_reticle_init(struct WeaponObj* arg0, struct PlayerObj* arg1);
void aiming_laser_reticle_place(struct WeaponObj* arg0, struct PlayerObj* arg1);

void func_800963E8(struct WeaponObj* arg0, struct PlayerObj* player)
{
    s32 hidden = player->weapon_energy[6] == 0;
    u32 i;

    if (!(player->armor_parts & 1) && player->weapon_energy[6] < player_weapon_energy.charge.initial_thresholds[0])
        hidden = 1;
    if (player->special_shot_count >= 3)
        hidden = 1;
    if (player->hurt_phase > 0)
        hidden = 1;
    if (player->attacking != 0 && (player->last_shot_type == 6 || player->last_shot_type == 0xF))
        hidden = 1;
    if (hidden) {
        arg0->on_screen = 0;
        return;
    }
    arg0->on_screen = 1;
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->ext.weapon_6.direction != 0 && (player->input.buttons.held & 4))
        arg0->ext.weapon_6.direction--;
    if (arg0->ext.weapon_6.direction != 0x10 && (player->input.buttons.held & 8))
        arg0->ext.weapon_6.direction++;
    aiming_laser_reticle_place(arg0, player);
    arg0->unk50 = aiming_laser_reticle_box;
    for (i = 0; i < COUNT(main_objects); i++) {
        if (aiming_laser_try_lock_on(arg0, player, &main_objects[i]))
            return;
    }
    arg0->unk50 = NULL;
}

void func_800961B0(struct WeaponObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    struct MainObj* owner;
    s32 reset;

    if (arg0->unk2 == 3) {
        reset = engine_obj.unkF != 0;
        if (player->weapon != 6)
            reset = 1;
        if (player->hp == 0)
            reset = 1;
        if (reset)
            ZeroObjectState(OBJECT_HEADER(arg0));
        else if (arg0->state == 0)
            aiming_laser_reticle_init(arg0, player);
        else
            func_800963E8(arg0, player);
        return;
    }
    owner = (struct MainObj*)arg0->owner;
    reset = player->input_locked != 0;
    if (player->capsule_state != 0 || player->weapon != 6 || player->actions_reset != 0 || player->hp == 0 || owner->active == 0 || owner->hp == 0)
        reset = 1;
    if (reset)
        arg0->state = 3;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->y_pos.val = owner->y_pos.val;
    ((void (*)(struct WeaponObj*, struct PlayerObj*, struct PlayerObj*))aiming_laser_marker_state_funcs[arg0->state])(
        arg0, player, (struct PlayerObj*)owner);
}

void func_800D69A8(struct QuadObj* arg0, struct PlayerObj* player, struct PlayerObj* target)
{
    const s8* offsets = (const s8*)&D_8011B230 + player->animation_step.fields.frame_index * 2;
    s32 dx = target->x_pos.val - player->x_pos.val;
    s32 dy = target->y_pos.val - player->y_pos.val;
    s16 x;
    s16 y;
    s16 near_x;
    s16 far_x;
    s16 near_y;
    s16 far_y;

    if (player->unk15 == 0)
        x = player->x_pos.i.hi + offsets[0] + 3;
    else
        x = player->x_pos.i.hi - offsets[0] - 3;
    near_x = target->x_pos.i.hi - (x + 6);
    far_x = target->x_pos.i.hi - (x - 6);
    arg0->x_pos.i.hi = x;
    arg0->vertices[0].x.val = 0;
    arg0->vertices[0].y.val = 0;
    y = player->y_pos.i.hi + offsets[1];
    arg0->y_pos.i.hi = y;
    near_y = target->y_pos.i.hi - (y + 6);
    far_y = target->y_pos.i.hi - (y - 6);
    if (dx < 0) {
        arg0->vertices[1].x.i.hi = far_x;
        arg0->vertices[2].x.i.hi = near_x;
        arg0->vertices[3].x.i.hi = near_x;
    } else {
        arg0->vertices[1].x.i.hi = near_x;
        arg0->vertices[2].x.i.hi = far_x;
        arg0->vertices[3].x.i.hi = far_x;
    }
    if (dy < 0) {
        arg0->vertices[1].y.i.hi = near_y;
        arg0->vertices[2].y.i.hi = near_y;
        arg0->vertices[3].y.i.hi = far_y;
    } else {
        arg0->vertices[1].y.i.hi = far_y;
        arg0->vertices[2].y.i.hi = far_y;
        arg0->vertices[3].y.i.hi = near_y;
    }
}

void func_800CF184(struct MiscObj* arg0)
{
    struct BaseObj* source = arg0->ext.pointer.unk50;

    arg0->on_screen = 1;
    arg0->unk16 = 6;
    arg0->state++;
    if ((u8)arg0->unk2 < 5)
        set_animation(arg0, 0x14 + arg0->unk2);
    arg0->x_pos.i.hi = source->x_pos.i.hi;
    arg0->y_pos.i.hi = source->y_pos.i.hi;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk15 = source->unk15;
    is_on_screen(BASE_OBJECT(arg0));
}

struct MainObj* func_8006FB20(struct MainObj* arg0, s32 dx, s32 dy)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return NULL;
    visual->active = 0x41;
    visual->id = 0x17;
    visual->unk2 = 1;
    visual->x_pos.i.hi = arg0->x_pos.i.hi + dx;
    visual->y_pos.i.hi = arg0->y_pos.i.hi + dy;
    visual->unk40 = arg0->unk40;
    visual->animation_table = (u32**)arg0->animation_table;
    visual->unk3C = (void*)arg0->sprite_frames;
    visual->unk42 = arg0->unk42;
    visual->unk15 = arg0->unk15;
    visual->unk50 = (struct PlayerObj*)arg0;
    visual->x_vel.val = 0;
    visual->y_vel.val = 0;
    visual->bg_offset = arg0->bg_offset;
    return (struct MainObj*)visual;
}

extern struct Unk_unk68 jet_stingray_terrain_box;
extern struct Unk_unk68 jet_stingray_land_attack_box;
extern struct Unk_unk68 jet_stingray_land_hurt_box;
s32 jet_stingray_at_target(struct MainObj* arg0, s32 arg1, s32 arg2);

void func_80070514(struct MainObj* arg0)
{
    struct BackgroundObj* background = &background_objects[arg0->bg_offset];
    s16 target_x;
    s16 target_y;

    if (arg0->x_pos.val < background->x_pos.val + 0xA00000) {
        arg0->unk15 = 0x40;
        target_x = background->unk1E + 0x40;
    } else {
        arg0->unk15 = 0;
        target_x = background->unk1E + 0x120;
    }
    target_y = background->unk22 + 0x98;
    set_velocity_from_angle(MOVING_OBJECT(arg0), angle_to_point(OBJECT_HEADER(arg0), target_x << 16, target_y << 16) & 0xFF);
    arg0->x_speed <<= 1;
    arg0->y_speed <<= 1;
    if (jet_stingray_at_target(arg0, target_x, target_y) & 0xFF) {
        arg0->x_speed = 0;
        arg0->y_speed = 0;
        arg0->unk7C = 0;
        arg0->unk6++;
    }
}

extern u16 jet_stingray_vortex_debris_offsets[24];
extern s8 jet_stingray_splash_x_offsets[4];
extern s8 jet_stingray_splash_y_offsets[4];
extern void (*jet_stingray_ambush_funcs[])(struct MainObj*);

void func_80070A38(struct MainObj* arg0)
{
    struct MainObj* debris;
    s16 dx;
    s16 dy;
    u32 roll;

    if (g_Player.x_pos.i.hi < arg0->x_pos.i.hi)
        g_Player.x_pos.i.hi += 3;
    else
        g_Player.x_pos.i.hi -= 3;
    if (arg0->y_pos.i.hi < g_Player.y_pos.i.hi)
        g_Player.y_pos.i.hi -= 1;
    else
        g_Player.y_pos.i.hi += 1;
    g_Player.y_pos.i.hi += 1;
    dy = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if ((dy < 0 ? -dy : dy) < 0x30 && (dx < 0 ? -dx : dx) < 0x20) {
        arg0->ext.main_56.vortex_result = 2;
        arg0->unk6++;
        return;
    }
    if (--arg0->unk7C == 0) {
        arg0->ext.main_56.vortex_result = 1;
        arg0->unk6++;
    }
    if (main_bss_state.frame_counter % 5 != 0)
        return;
    debris = func_8006FB20(arg0, 0, 0);
    roll = get_random();
    if (debris != NULL)
        debris->x_pos.i.hi = background_objects[0].unk1E + jet_stingray_vortex_debris_offsets[(arg0->unk15 != 0 ? 8 : 0) + (roll & 7)];
    roll = get_random();
    if (debris == NULL)
        return;
    debris->y_pos.i.hi = background_objects[0].unk22 + jet_stingray_vortex_debris_offsets[0x10 + (roll & 7)];
    debris->x_speed = arg0->unk15 != 0 ? -0x38000 : 0x38000;
    debris->y_speed = arg0->y_pos.i.hi < debris->y_pos.i.hi ? 0x10000 : -0x10000;
}

void func_800710D4(struct MainObj* arg0)
{
    struct MainObj* debris;
    u8 tile;
    s8 i;

    jet_stingray_ambush_funcs[arg0->unk6](arg0);
    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    tile = jet_stingray_check_surface(PLAYER_OBJECT(arg0), 0, 0);
    if (tile == 0)
        return;
    if (tile < 3) {
        if (arg0->ext.main_56.flags & 1)
            return;
        for (i = 0; i < 4; i++) {
            debris = func_8006FB20(arg0, jet_stingray_splash_x_offsets[get_random() & 3], 0);
            if (debris != NULL)
                debris->y_pos.i.hi = jet_stingray_splash_y_offsets[get_random() & 3] + 0x13B;
            else
                get_random();
        }
        arg0->ext.main_56.flags |= 1;
    } else if (tile == 3) {
        if (arg0->ext.main_56.flags & 2)
            return;
        jet_stingray_spawn_splash(arg0);
        arg0->ext.main_56.flags |= 2;
    }
}

void func_80071740(struct MainObj* arg0)
{
    struct ShotObj* shot;

    switch (arg0->unk7) {
    case 0:
        arg0->unk7 = 1;
        func_8001540C(2, 0xB2, arg0);
        arg0->unk7C = 0x32;
    case 1:
        if (--arg0->unk7C == 0) {
            arg0->unk7E = arg0->unk5 == 9 ? 4 : 3;
            arg0->unk7++;
            set_animation(arg0, 9);
        }
        break;
    case 2:
        if (arg0->animation_step.fields.event == 1) {
            func_8001540C(2, 0xB1, arg0);
            arg0->animation_step.fields.event = 0;
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x22;
                shot->unk2 = arg0->unk5 == 9 ? 3 : 2;
                shot->unk40 = arg0->unk40;
                shot->animation_table = (u32**)arg0->animation_table;
                shot->unk3C = (void*)arg0->sprite_frames;
                shot->unk42 = arg0->unk42;
                shot->bg_offset = arg0->bg_offset;
                shot->x_pos.val = arg0->x_pos.val;
                shot->y_pos.val = arg0->y_pos.val;
                shot->unk7C = (struct WeaponObj*)arg0;
                shot->unk15 = arg0->unk15;
            }
        }
        if (arg0->animation_step.fields.event == 2) {
            arg0->animation_step.fields.event = 0;
            arg0->unk7C = 0x14;
            arg0->unk6++;
        }
        break;
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

extern void (*jet_stingray_step_funcs[])(struct MainObj*);

void func_80071D30(struct MainObj* arg0)
{
    s32 hit = func_8002DD04(arg0);
    s32 flash = 0;

    if (arg0->ext.main_56.flash_timer != 0) {
        arg0->ext.main_56.flash_timer--;
        if (arg0->ext.main_56.flash_timer & 1)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
    } else {
        arg0->collision_data = D_801079F8;
    }
    if (hit < 0) {
        arg0->unk5 = 0;
        arg0->state++;
        arg0->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
        return;
    }
    if (hit != 0) {
        if (engine_obj.cur_character == CHARACTER_X) {
            if (hit == 0xC || hit == 3) {
                arg0->state = 3;
                arg0->unk6 = 0;
                arg0->unk7 = 0;
                return;
            }
            flash = hit != 0x7F;
        } else {
            if (hit == 0x22) {
                arg0->state = 3;
                arg0->unk6 = 0;
                arg0->unk7 = 0;
                return;
            }
            flash = hit != 0x7F && hit != 0x19 && hit != 0x1A;
        }
    }
    if (flash && arg0->ext.main_56.flash_timer == 0) {
        arg0->collision_data = D_801060F0;
        arg0->ext.main_56.flash_timer = 0x40;
    }
    jet_stingray_step_funcs[arg0->unk5](arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x80, 0x80);
    func_8002D9BC(arg0);
}

extern struct Unk_unk68 frost_tower_hit_box[];
extern u32* D_8011C094[];

void func_80093D78(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = frost_tower_hit_box;
    arg0->unk38 = (u8*)player_gfx + player_gfx[3];
    arg0->animation_table = D_8011C094;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 3;
    arg0->unk15 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0xB];
    arg0->x_pos.i.hi = g_Player.x_pos.i.hi + (g_Player.unk15 != 0 ? -5 : 5);
    arg0->unk67 = 1;
    arg0->x_vel.val = 0;
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk49 = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi - 6;
    arg0->ext.weapon_2.lifetime = 0x96;
    arg0->ext.weapon_2.timer = 8;
    set_animation(arg0, 0);
    arg0->unk5 = 0;
    arg0->state++;
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    update_on_screen(BASE_OBJECT(arg0), 0x28, 0x38);
}

struct Shot34Data {
    struct Unk_unk68 bounds[6];
    u8 effect_animation_ids[3][4];
    s8 trailing_data[4];
};

extern struct Shot34Data ray_trap_data;
extern s32 ray_trap_wall_animations[4];
extern s32 ray_trap_floor_animations[4];
extern u8 ray_trap_crawl_boxes[4][4];
extern void (*ray_trap_step_funcs[])(struct ShotObj*);
void func_80021DBC(s16* arg0, s16* arg1, s32 arg2);
void ray_trap_check_airborne(struct ShotObj* arg0);

void func_800A16FC(struct ShotObj* arg0)
{
    arg0->x_vel.val = 0x60000;
    arg0->unk16 = 5;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->state = 1;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk1C.val = arg0->y_pos.val;
    switch (arg0->unk2) {
    case 0:
        arg0->unk54 = (u8*)&ray_trap_data.bounds[4];
        arg0->unk50.data = (u8*)&ray_trap_data.bounds[3];
        arg0->unk68 = &ray_trap_data.bounds[5];
        arg0->unk5C = 1;
        arg0->unk8C.bytes[3] = 0;
        arg0->timer = 0;
        arg0->unk15 = arg0->x_pos.val < g_Player.x_pos.val ? 0x40 : 0;
        break;
    case 1:
        arg0->unk54 = (u8*)&ray_trap_data.bounds[1];
        arg0->unk5C = 1;
        arg0->unk50.data = (u8*)&ray_trap_data.bounds[0];
        arg0->unk68 = NULL;
        arg0->timer = 0;
        break;
    case 2:
    case 3:
        arg0->unk5C = 3;
        arg0->unk54 = (u8*)&ray_trap_data.bounds[1];
        arg0->unk50.data = (u8*)&ray_trap_data.bounds[0];
        arg0->unk68 = &ray_trap_data.bounds[2];
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x30000 : -0x30000;
        arg0->unk8C.bytes[3] = 1;
        arg0->timer = 0xE10;
        break;
    }
    arg0->unk60 = 6;
    arg0->unk5C = 3;
    arg0->unk58.data = (u8*)D_80105FF0;
    arg0->unk67 = 0;
    arg0->unk8C.bytes[0] = 7;
    arg0->unk8C.bytes[2] = 0;
    arg0->unk5 = ray_trap_floor_animations[arg0->unk2];
    set_animation(arg0, ray_trap_wall_animations[arg0->unk2]);
}

static void shot_34_orbit(struct ShotObj* arg0, struct MainObj* owner)
{
    arg0->unk84.halves[0] = 0x20;
    arg0->unk84.halves[1] = 0x20;
    func_80021DBC((s16*)&arg0->unk84.halves[0], (s16*)&arg0->unk84.halves[1], arg0->unk8C.bytes[0]);
}

void func_800A19A8(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;

    switch (arg0->unk7) {
    case 0:
        arg0->unk7 = 1;
        arg0->y_vel.val = 0xA0000;
        arg0->x_vel.val = 0;
        arg0->unk8C.bytes[1] = 2;
    case 1:
        if (arg0->unk8C.bytes[1] != 0) {
            arg0->unk8C.bytes[1]--;
        } else {
            arg0->y_vel.val = 0;
            arg0->unk7++;
        }
        move_object(MOVING_OBJECT(arg0));
        break;
    case 2:
        if (owner->ext.main_55.unk87 != 0) {
            arg0->unk7 = 0;
            arg0->unk6++;
            break;
        }
        shot_34_orbit(arg0, owner);
        if (arg0->timer == 0) {
            arg0->timer = 3;
            arg0->unk8C.bytes[0] = (arg0->unk8C.bytes[0] - 1) & 0xF;
        } else {
            arg0->timer--;
        }
        arg0->x_pos.i.hi = owner->x_pos.i.hi + arg0->unk84.halves[0];
        arg0->y_pos.i.hi = owner->y_pos.i.hi + arg0->unk84.halves[1];
        break;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    if (owner->active == 0)
        arg0->state = 2;
}

void func_800A1B1C(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;

    if (!((owner->ext.main_55.unk88 >> arg0->unk8A) & 1)) {
        arg0->unk7 = 0;
        arg0->unk15 = g_Player.x_pos.val >= arg0->x_pos.val ? 0x40 : 0;
        arg0->unk6++;
    }
    shot_34_orbit(arg0, owner);
    arg0->x_pos.i.hi = owner->x_pos.i.hi + arg0->unk84.halves[0];
    arg0->y_pos.i.hi = owner->y_pos.i.hi + arg0->unk84.halves[1];
    animate_object(ANIMATED_OBJECT(arg0));
    if (owner->active == 0)
        arg0->state = 2;
}

void func_800A1BEC(struct ShotObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->unk7 = 1;
        arg0->unk15 = g_Player.x_pos.val >= arg0->x_pos.val ? 0x40 : 0;
        set_velocity_from_angle(MOVING_OBJECT(arg0),
            angle_to_point(OBJECT_HEADER(arg0), g_Player.x_pos.val + 0x1400000, g_Player.y_pos.val) & 0xFF);
        arg0->y_vel.val -= 0x30000;
    }
    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}

void func_800A1CCC(struct ShotObj* arg0)
{
    u8 flags;
    s32 reverse;

    arg0->unk8C.bytes[3] = 1;
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    arg0->unk54 = (u8*)&ray_trap_data.bounds[1];
    arg0->unk50.data = (u8*)&ray_trap_data.bounds[0];
    arg0->unk68 = &ray_trap_data.bounds[2];
    if (arg0->unk6 == 0) {
        flags = arg0->unk70;
        if ((flags & 3) == 0)
            return;
        if (arg0->unk15 != 0)
            reverse = flags & 1;
        else
            reverse = (flags & 2) != 0;
        if (!(arg0->unk70 & 8)) {
            arg0->unk6++;
            arg0->x_vel.val = 0;
            arg0->unk15 ^= 0x40;
            set_animation(arg0, ray_trap_crawl_boxes[0][arg0->unk2]);
        } else if (reverse) {
            arg0->unk15 ^= 0x40;
            arg0->x_vel.val = -arg0->x_vel.val;
        }
        return;
    }
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk5 = 4;
    arg0->unk6 = 0;
    arg0->y_vel.val = -0x30000;
    set_animation(arg0, ray_trap_crawl_boxes[1][arg0->unk2]);
    arg0->unk68 = &ray_trap_data.bounds[5];
    arg0->x_pos.i.hi += arg0->unk15 != 0 ? -0x10 : 0x10;
    arg0->unk67 = 0;
}

void func_800A1E3C(struct ShotObj* arg0)
{
    arg0->unk8C.bytes[3] = 0;
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    arg0->unk54 = (u8*)&ray_trap_data.bounds[4];
    arg0->unk50.data = (u8*)&ray_trap_data.bounds[3];
    arg0->unk68 = &ray_trap_data.bounds[5];
    if (arg0->unk6 == 0) {
        if (arg0->unk70 & 8) {
            arg0->unk6 = 1;
            arg0->y_vel.val = 0;
            set_animation(arg0, ray_trap_crawl_boxes[2][arg0->unk2]);
        }
        return;
    }
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk5 = 3;
    arg0->unk6 = 0;
    arg0->unk15 = arg0->x_pos.val < g_Player.x_pos.val ? 0x40 : 0;
    if (arg0->unk2 < 2)
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x90000 : -0x10000;
    else
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x30000 : -0x30000;
    set_animation(arg0, ray_trap_crawl_boxes[3][arg0->unk2]);
    arg0->unk68 = &ray_trap_data.bounds[2];
    arg0->unk67 = 0;
    arg0->y_pos.i.hi += 0x10;
}

void func_800A2098(struct ShotObj* arg0)
{
    s32 hit = func_8002DD04((struct MainObj*)arg0);

    if (arg0->unk2 >= 2) {
        if (((struct BaseObj*)arg0->unk7C)->state == 2)
            hit = -1;
        if (arg0->timer == 0)
            hit = -1;
        else
            arg0->timer--;
    }
    if (hit < 0) {
        spawn_explosion(BASE_OBJECT(arg0));
        if (arg0->unk2 == 2)
            spawn_debris(4, ray_trap_data.effect_animation_ids[1], arg0);
        else if (arg0->unk2 == 3)
            spawn_debris(4, ray_trap_data.effect_animation_ids[2], arg0);
        else if (arg0->unk2 >= 0 && arg0->unk2 < 2)
            spawn_debris(4, ray_trap_data.effect_animation_ids[0], arg0);
        arg0->state = 2;
        return;
    }
    arg0->unk8C.bytes[2] = 1;
    func_8002D9BC(arg0);
    if (arg0->unk2 == 0)
        ray_trap_check_airborne(arg0);
    ray_trap_step_funcs[arg0->unk5](arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) != 0)
        arg0->state = 2;
    else
        is_on_screen(BASE_OBJECT(arg0));
}

extern u16 frost_tower_charged_part_offsets[];
void frost_tower_charged_spawn_part(s8 arg0);
void frost_tower_hide(struct WeaponObj* arg0);

void func_80094280(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;

    arg0->unk40 = 0x520;
    arg0->previous_animation_index = 0xFF;
    arg0->state++;
    arg0->animation_step.fields.frame_index = 9;
    arg0->ext.raw[2] = 0;
    arg0->ext.raw[3] = 0;
    arg0->unk5 = 0;
    arg0->unk38 = (u8*)player_gfx + player_gfx[3];
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
}

void func_800942E8(struct WeaponObj* arg0)
{
    s32 strength = 0x20;

    if (arg0->ext.raw[2] != 0) {
        arg0->ext.raw[2]--;
        return;
    }
    arg0->ext.raw[2] = 0x28;
    switch (arg0->ext.raw[3]) {
    case 0:
        frost_tower_charged_spawn_part(1);
        break;
    case 1:
        frost_tower_charged_spawn_part(2);
        frost_tower_charged_spawn_part(-0x7E);
        break;
    case 2:
        frost_tower_charged_spawn_part(1);
        frost_tower_charged_spawn_part(3);
        frost_tower_charged_spawn_part(-0x7D);
        break;
    case 3:
        frost_tower_charged_spawn_part(4);
        frost_tower_charged_spawn_part(-0x7C);
        frost_tower_charged_spawn_part(5);
        frost_tower_charged_spawn_part(-0x7B);
        strength = 0x40;
        break;
    }
    func_8001540C(0, 0x1A, 0);
    start_screen_shake_x(strength, 8, 1);
    if (++arg0->ext.raw[3] == 4)
        frost_tower_hide(arg0);
}

void func_800944B8(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    struct BackgroundObj* background = &background_objects[g_Player.bg_offset];
    u16 base;

    arg0->on_screen = 1;
    arg0->unk38 = (u8*)player_gfx + player_gfx[3];
    arg0->animation_table = D_8011C094;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 1;
    arg0->unk15 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0xB];
    base = background->x_pos.i.hi + 0xA0;
    if (arg0->unk2 & 0x80)
        arg0->x_pos.i.hi = base - frost_tower_charged_part_offsets[arg0->unk2 & 0x7F];
    else
        arg0->x_pos.i.hi = base + frost_tower_charged_part_offsets[arg0->unk2 & 0x7F];
    arg0->x_vel.val = 0;
    arg0->unk28.val = 0;
    arg0->y_vel.val = -0x80000;
    arg0->unk2C = 0;
    arg0->y_pos.i.hi = background->y_pos.i.hi + 0x30;
    set_animation(arg0, 6);
    arg0->unk5 = 0;
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x28, 0x38);
}

extern struct Unk_unk68 frost_walrus_terrain_box;
extern void* frost_walrus_animations[39];
extern void (*frost_walrus_step_funcs[12])();

void func_800722A0(struct MainObj* arg0)
{
    if (((struct BaseObj*)arg0->ext.main_57.effect)->active != 0)
        return;
    arg0->unk16 = 5;
    arg0->contact_damage = 6;
    arg0->terrain_box = &frost_walrus_terrain_box;
    arg0->hurt_box = &frost_walrus_hurt_box;
    arg0->attack_box = &frost_walrus_attack_box;
    arg0->collision_data = D_80107A78;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk15 = 0;
    arg0->hp = 0;
    arg0->invincibility_timer = 0;
    arg0->animation_table = (const u8* const*)frost_walrus_animations;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (engine_obj.stage != 0xC) {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    } else {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
        arg0->unk42 = 0x7888;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
    }
    engine_obj.unk25 = 1;
    engine_obj.boss_ptr = arg0;
    set_animation(arg0, 0x26);
    arg0->ext.main_57.tusks_broken = 0;
    arg0->ext.main_57.flash_timer = 0;
    arg0->ext.main_57.flashing = 0;
    arg0->ext.main_57.staggered = 0;
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
}

void func_80072418(struct MainObj* arg0)
{
    s32 hit;
    s32 flash = 0;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    ((void (*)(struct MainObj*))frost_walrus_step_funcs[arg0->unk5])(arg0);
    hit = func_8002DD04(arg0);
    if (arg0->ext.main_57.flash_timer != 0) {
        if (arg0->ext.main_57.flash_timer & 1)
            arg0->unk42 &= 0x7FFF;
        else
            arg0->unk42 |= 0x8000;
        if (--arg0->ext.main_57.flash_timer == 0) {
            arg0->collision_data = D_80107A78;
            arg0->ext.main_57.flashing = 0;
        }
    } else if (hit < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
        update_on_screen(BASE_OBJECT(arg0), 0x60, 0x60);
        return;
    } else if (hit != 0) {
        s32 weakness = engine_obj.cur_character == CHARACTER_X ? (hit == 5 || hit == 0xE) : hit == 0x24;

        if (weakness && arg0->ext.main_57.staggered == 0) {
            arg0->unk5 = 0xA;
            arg0->unk6 = 0;
            return;
        }
        flash = engine_obj.cur_character == CHARACTER_X || hit != 0x7F;
    }
    if (flash) {
        arg0->collision_data = D_801060F0;
        arg0->ext.main_57.flash_timer = 0x40;
        arg0->ext.main_57.flashing = 1;
    }
    func_8002D9BC(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_80072628(struct MainObj* arg0)
{
    g_Player.stun_timer = 0;
    player_start_script_action(0x14, g_Player.unk15);
    arg0->unk5 = 1;
    arg0->unk42 &= 0x7FFF;
    set_animation(arg0, arg0->ext.main_57.tusks_broken != 0 ? 0x1C : 0x1B);
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->invincibility_timer = 0x19;
    frost_walrus_set_floor_tiles(0x38);
    update_on_screen(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_80073E80(struct MainObj* arg0)
{
    struct VisualObj* visual;
    u32 i;

    arg0->ext.main_57.staggered = 1;
    for (i = 0; i < 4; i++) {
        visual = find_free_visual_obj();
        if (visual == NULL)
            continue;
        visual->active = 0x41;
        visual->id = 0x18;
        visual->unk2 = i + 0x40;
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->unk15 = arg0->unk15;
    }
    set_animation(arg0, 0x12);
    func_8001540C(2, 0x99, arg0);
    arg0->x_speed = arg0->x_pos.i.hi < g_Player.x_pos.i.hi ? -0x20000 : 0x20000;
    arg0->y_speed = 0x38000;
    arg0->gravity = 0x4200;
    arg0->ext.main_57.flash_timer = 0xC8;
    arg0->air_state = 1;
    arg0->ext.main_57.flashing = 1;
    arg0->x_accel = 0;
    arg0->collision_data = D_801060F0;
    arg0->unk6++;
}

extern struct Unk_unk68 rising_fire_hit_box[];
extern u32* D_8011C0B0[];
extern s8 rising_fire_charged_offsets[];
void rising_fire_draw(struct WeaponObj* arg0);

void func_80095254(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    s8 dx = rising_fire_charged_offsets[arg0->unk2 * 2];
    s8 dy = rising_fire_charged_offsets[arg0->unk2 * 2 + 1];

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = rising_fire_hit_box;
    arg0->unk38 = (u8*)player_gfx + player_gfx[5];
    arg0->animation_table = D_8011C0B0;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 1;
    arg0->unk15 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0xD];
    if (g_Player.unk15 == 0)
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + dx;
    else
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - dx;
    arg0->y_vel.val = 0x70000;
    arg0->x_vel.val = 0;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 1;
    arg0->unk49 = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi + dy;
    set_animation(arg0, 1);
    func_8001540C(0, 0x1B, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    rising_fire_draw(arg0);
}

void func_80095538(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk38 = (u8*)player_gfx + player_gfx[5];
    arg0->animation_table = D_8011C0B0;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 1;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0xD];
    arg0->unk15 = g_Player.unk15;
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->y_vel.val = 0x70000;
    arg0->x_vel.val = 0;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 1;
    arg0->unk49 = 0;
    arg0->ext.weapon_13.timer = 4;
    arg0->y_pos.val = g_Player.y_pos.val;
    set_animation(arg0, arg0->unk2 == 0 ? 3 : 5);
    func_8001540C(0, 0x1B, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    rising_fire_charged_draw(arg0);
}

void func_800B3B94(struct VisualObj* arg0)
{
    struct PlayerObj* source = arg0->unk50;

    animate_object(ANIMATED_OBJECT(arg0));
    arg0->x_pos.val = source->x_pos.val + (frost_walrus_fx_sparkle_offsets[(s8)arg0->unk2 * 2] << 16);
    arg0->y_pos.val = source->y_pos.val + (frost_walrus_fx_sparkle_offsets[(s8)arg0->unk2 * 2 + 1] << 16);
    is_on_screen(BASE_OBJECT(arg0));
    if ((s8)source->unk6 == 2) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void func_800A241C(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;

    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0x60000;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->unk68 = &walrus_ice_ball_terrain_box;
    arg0->unk5C = 5;
    arg0->unk60 = 6;
    arg0->unk16 = 4;
    arg0->unk54 = NULL;
    arg0->unk50.data = NULL;
    arg0->y_pos.val = owner->y_pos.val;
    arg0->unk42 = owner->unk42;
    set_animation(arg0, (s8)arg0->unk2 >= 2 ? 9 : 8);
    if ((s8)arg0->unk2 == 0) {
        walrus_ice_choose_drop_pattern(arg0);
    }
    arg0->unk5++;
}

void func_800A25EC(struct ShotObj* arg0)
{
    struct WeaponObj* owner = arg0->unk7C;
    struct VisualObj* visual;
    u8 i;

    arg0->unk42 = owner->unk42;
    arg0->x_pos.val = owner->x_pos.val;
    arg0->y_pos.val = owner->y_pos.val;
    animate_object(ANIMATED_OBJECT(arg0));
    if ((s8)owner->unk5 == 0xA) {
        arg0->state = 6;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        return;
    }
    if ((u8)arg0->unk2 & 1) {
        is_on_screen(BASE_OBJECT(arg0));
    }
    if (arg0->animation_step.fields.relative_step != 0) {
        return;
    }
    arg0->unk6++;
    if ((u8)arg0->unk2 & 1) {
        return;
    }
    func_8001540C(2, 0x95, arg0);
    for (i = 0; i < 2; i++) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x18;
            visual->unk2 = 0;
            if (owner->unk15 != 0) {
                visual->x_pos.i.hi = owner->x_pos.i.hi + walrus_ice_icicle_offsets[i][0];
            } else {
                visual->x_pos.i.hi = owner->x_pos.i.hi - walrus_ice_icicle_offsets[i][0];
            }
            visual->unk50 = (struct PlayerObj*)owner;
            visual->y_pos.i.hi = owner->y_pos.i.hi - 0x1F;
        }
    }
}

void func_800A348C(struct ShotObj* arg0)
{
    if (--arg0->timer == 0) {
        arg0->unk54 = (const u8*)&walrus_ice_ball_hurt_box;
        arg0->unk50.data = (const u8*)&walrus_ice_ball_attack_box;
        func_8001540C(2, 0x96, arg0);
        arg0->unk6++;
    } else {
        arg0->on_screen ^= 1;
        if (arg0->on_screen != 0) {
            is_on_screen(BASE_OBJECT(arg0));
        }
    }
}

extern struct Unk_unk68 D_80107BF8[];
extern void* split_mushroom_animations[];
extern struct Unk_unk68 split_mushroom_attack_box;
extern struct Unk_unk68 split_mushroom_hurt_box;
extern struct Unk_unk68 split_mushroom_wall_terrain_box;
extern s16 split_mushroom_hop_speeds[];
extern void (*split_mushroom_step_funcs[8])();
void split_mushroom_load_palette(void);

void func_8007877C(struct MainObj* arg0)
{
    arg0->contact_damage = 5;
    arg0->hp = 0;
    arg0->invincibility_timer = 0;
    arg0->collision_data = D_80107BF8;
    if (engine_obj.stage != 0xC) {
        arg0->unk15 = 0x40;
        arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    } else {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
        arg0->unk42 = 0x7888;
        arg0->unk15 = 0;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
    }
    arg0->gravity = 0x3800;
    arg0->animation_table = (const u8* const*)split_mushroom_animations;
    arg0->unk16 = 6;
    arg0->hurt_box = &split_mushroom_hurt_box;
    arg0->attack_box = &split_mushroom_attack_box;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->air_state = 0;
    arg0->terrain_box = &split_mushroom_terrain_box;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    set_animation(arg0, 5);
    arg0->ext.main_61.flash_timer = 0;
    arg0->ext.main_61.split = 0;
    arg0->ext.main_61.stunned = 0;
    arg0->ext.main_61.split_hits = 3;
    arg0->ext.main_61.merge = 0;
    arg0->ext.main_61.hit_lock = 0;
    arg0->ext.main_61.active = 0;
    arg0->ext.main_61.speed_level = 0;
    arg0->ext.main_61.split_done = 0;
    split_mushroom_load_palette();
    arg0->state = 1;
    arg0->unk5 = 1;
    arg0->unk6 = 0;
}

static struct ShotObj* main61_spawn_shot(struct MainObj* self, s8 subtype, s8 state)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x27;
        shot->unk2 = subtype;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (void*)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk15 = self->unk15;
        shot->bg_offset = self->bg_offset;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->unk15 = self->unk15;
        if (self->unk2 == 0)
            shot->unk7C = (struct WeaponObj*)self;
        else
            shot->unk7C = (struct WeaponObj*)self->ext.main_61.partner;
        shot->state = state;
    }
    return shot;
}

void func_800788E4(struct MainObj* arg0)
{
    s32 hit;
    s8 flash;
    struct VisualObj* visual;
    struct MainObj* other;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    ((void (*)(struct MainObj*))split_mushroom_step_funcs[arg0->unk5])(arg0);
    if (arg0->unk2 == 0 && arg0->ext.main_61.active == 0)
        return;
    hit = 0;
    if (arg0->ext.main_61.split != 0xFF && arg0->ext.main_61.hit_lock == 0 && arg0->unk2 == 0)
        hit = func_8002DD04(arg0);
    flash = (s8)arg0->ext.main_61.flash_timer;
    if (flash == 0) {
        arg0->ext.main_61.hit_lock = 0;
        if (hit < 0) {
            g_Player.spike_immune = 1;
            stop_sound(2, 0xA7);
            if (arg0->unk2 == 0) {
                arg0->state = 2;
                arg0->unk5 = 0;
                if (arg0->ext.main_61.split != 0) {
                    arg0->ext.main_61.partner->on_screen = 0;
                    ZeroObjectState(OBJECT_HEADER(arg0->ext.main_61.partner));
                }
            } else {
                arg0->ext.main_61.partner->state = 2;
                arg0->ext.main_61.partner->unk5 = 0;
                arg0->on_screen = 0;
                ZeroObjectState(OBJECT_HEADER(arg0));
            }
            return;
        }
        if (hit != 0 && hit != 0x7F) {
            if (arg0->unk5 != 6 && hit != 2 && hit != 0xB && hit != 0x21 && (get_random() & 0xF) < 4)
                main61_spawn_shot(arg0, 0, 7);
            if ((u32)(hit - 0x19) < 2) {
                arg0->ext.main_61.flash_timer = 6;
                arg0->ext.main_61.hit_lock = 1;
            } else {
                arg0->ext.main_61.flash_timer = 0x40;
            }
            if (hit != 2 && hit != 0xB && hit != 0x21) {
                visual = find_free_visual_obj();
                if (visual != NULL) {
                    visual->active = 0x41;
                    visual->id = 0x22;
                    visual->unk2 = 1;
                    visual->unk16 = 0;
                    visual->unk40 = arg0->unk40;
                    visual->unk42 = arg0->unk42;
                    visual->animation_table = (void*)arg0->animation_table;
                    visual->unk3C = (void*)arg0->sprite_frames;
                    visual->unk15 = arg0->unk15;
                    visual->unk15 = 0;
                    visual->unk50 = (struct PlayerObj*)arg0;
                    visual->bg_offset = arg0->bg_offset;
                    visual->state = 0;
                    visual->unk5C.value = arg0->ext.main_61.flash_timer;
                    set_animation(visual, 0x14);
                }
            }
            arg0->collision_data = D_801060F0;
            arg0->unk42 |= 0x8000;
            if ((hit == 2 || hit == 0xB || hit == 0x21) && arg0->ext.main_61.stunned == 0) {
                stop_sound(2, 0xA7);
                arg0->ext.main_61.stunned = 1;
                set_animation(arg0, 0x13);
                arg0->unk7E = 1;
                arg0->invincibility_timer = 1;
                arg0->unk5 = 2;
                arg0->unk6 = 0;
                if (arg0->ext.main_61.split != 0) {
                    if (arg0->unk2 == 0) {
                        if (--arg0->ext.main_61.split_hits == 0)
                            arg0->ext.main_61.merge = 1;
                    } else {
                        other = arg0->ext.main_61.partner;
                        if (--other->ext.main_61.split_hits == 0)
                            arg0->ext.main_61.partner->ext.main_61.merge = 1;
                    }
                    set_animation(arg0->ext.main_61.partner, 0x13);
                    arg0->ext.main_61.partner->invincibility_timer = 1;
                    arg0->ext.main_61.partner->unk5 = 2;
                    arg0->ext.main_61.partner->unk6 = 0;
                }
            }
        }
    } else {
        arg0->ext.main_61.flash_timer = --flash;
        if (flash == 0) {
            arg0->collision_data = D_80107BF8;
            arg0->unk42 &= 0x7FFF;
        } else if (flash & 1) {
            arg0->unk42 |= 0x8000;
        } else {
            arg0->unk42 &= 0x7FFF;
        }
    }
    if (arg0->ext.main_61.blink_timer != 0) {
        if ((--arg0->ext.main_61.blink_timer & 1) == 0) {
            arg0->on_screen = 0;
            return;
        }
    }
    arg0->ext.main_61.speed_level = 0;
    if (arg0->hp < 0x20)
        arg0->ext.main_61.speed_level = 1;
    else if (arg0->hp < 0x10)
        arg0->ext.main_61.speed_level = 2;
    if ((u32)((u8)arg0->unk5 - 1) >= 2)
        func_8002D9BC(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x60, 0x60);
}

void func_800793AC(struct MainObj* arg0)
{
    s32 i;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        func_8001540C(2, 0xA9, arg0);
        for (i = 0; i < 5; i++)
            main61_spawn_shot(arg0, i, 7);
    }
    if (arg0->animation_step.fields.event == 2) {
        if (engine_obj.stage == 3) {
            func_8002217C(0xA, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
        arg0->unk6 = 5;
    }
}

void func_80079824(struct MainObj* arg0)
{
    struct MainObj* other = arg0->ext.main_61.partner;
    s32 dx = arg0->x_pos.i.hi - other->x_pos.i.hi;
    s32 dy;

    if (dx < 0)
        dx = -dx;
    if (dx < 4) {
        dy = arg0->y_pos.i.hi - arg0->ext.main_61.partner->y_pos.i.hi;
        if (dy < 0)
            dy = -dy;
        if (dy < 4) {
            arg0->ext.main_61.partner->ext.main_61.split = 0;
            arg0->on_screen = 0;
            ZeroObjectState(OBJECT_HEADER(arg0));
            return;
        }
    }
    set_velocity_from_angle(MOVING_OBJECT(arg0),
        (u8)angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(arg0->ext.main_61.partner)));
    arg0->x_speed *= 4;
    arg0->y_speed *= 4;
    move_object(MOVING_OBJECT(arg0));
}

void func_80079A8C(struct MainObj* arg0)
{
    s32 target;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;
    arg0->ext.main_61.stunned = 1;
    target = background_objects[g_Player.bg_offset].x_pos.val - (arg0->x_pos.val + (s32)0xFF600000);
    arg0->y_speed = 0x85C00;
    arg0->gravity = 0x3800;
    arg0->unk7C = 0x30;
    arg0->unk6 = 1;
    arg0->x_speed = target / 48;
    func_8001540C(2, 0xA5, arg0);
}

void func_80079B50(struct MainObj* arg0)
{
    s32 row;
    s32 col;
    s32 x_step;
    s8 phase;
    u16 delay;
    u16 base_y;
    s16 base_x;
    s16 y;

    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    set_animation(arg0, 4);
    phase = 0;
    delay = 0x104;
    base_y = background_objects[g_Player.bg_offset].y_pos.i.hi - 0x20;
    base_x = background_objects[g_Player.bg_offset].x_pos.i.hi - 0x10;
    for (row = 0; row < 0xC0; row += 0x20) {
        y = base_y - row;
        for (col = 0, x_step = 0; col < 10; col++, x_step += 0x40) {
            if (!(col & 1)) {
                struct VisualObj* visual = find_free_visual_obj();

                if (visual == NULL)
                    continue;
                visual->active = 0x41;
                visual->id = 0x22;
                visual->unk2 = 0;
                visual->x_pos.i.hi = base_x + phase + x_step;
                visual->y_pos.i.hi = y;
                visual->unk15 = 0;
                visual->bg_offset = arg0->bg_offset;
                visual->animation_table = (void*)arg0->animation_table;
                visual->unk40 = arg0->unk40;
                visual->unk3C = (void*)arg0->sprite_frames;
                visual->unk42 = arg0->unk42 & 0x7FFF;
                visual->unk16 = row < 0x41 ? 0x13 : 0x12;
                visual->unk5C.value = phase;
                visual->unk50 = (struct PlayerObj*)arg0;
                visual->state = 0;
                visual->unk5C.fields.unk5E = delay;
                set_animation(visual, 0xE);
            } else {
                struct MiscObj* misc = find_free_misc_obj();

                if (misc == NULL)
                    continue;
                misc->active = 0x41;
                misc->id = 0x1E;
                misc->unk2 = 0;
                misc->x_pos.i.hi = base_x + phase + x_step;
                misc->y_pos.i.hi = y;
                misc->unk15 = 0;
                misc->bg_offset = arg0->bg_offset;
                misc->animation_table = (void*)arg0->animation_table;
                misc->unk40 = arg0->unk40;
                misc->unk3C = (void*)arg0->sprite_frames;
                misc->unk42 = arg0->unk42 & 0x7FFF;
                misc->unk16 = row < 0x41 ? 0x13 : 0x12;
                misc->ext.misc_30.unk54 = phase;
                misc->ext.misc_30.owner = arg0;
                misc->state = 0;
                misc->ext.misc_30.unk56 = delay;
                set_animation(misc, 0xE);
            }
        }
        phase ^= 0x20;
        delay += 0x20;
    }
    arg0->unk7C = 0xF0;
    arg0->unk6 = 2;
}

void func_8007A2B4(struct MainObj* arg0)
{
    s16 speed = split_mushroom_hop_speeds[arg0->ext.main_61.speed_level];

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;
    arg0->x_speed = (arg0->unk15 != 0 ? 0xE30000 : -0xE30000) / speed;
    arg0->y_speed = (speed + 1) * 7 << 10;
    arg0->gravity = 0x3800;
    move_with_gravity(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0xA5, arg0);
    arg0->unk6 = 3;
    arg0->unk7 = 0;
}

void func_8007A444(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;
    arg0->unk15 ^= 0x40;
    if (--arg0->unk7C == 0)
        func_8007B6BC(ANIMATED_OBJECT(arg0));
    else
        arg0->unk6 = 0;
}

void func_8007A4EC(struct MainObj* arg0)
{
    struct MiscObj* misc;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    arg0->x_speed = arg0->unk15 != 0 ? 0x64E38 : (s32)0xFFF9B1C8;
    if (arg0->unk7E == 3) {
        arg0->y_speed = 0;
        arg0->gravity = 0;
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0x16;
            misc->unk2 = 8;
            misc->unk15 = arg0->unk15;
            misc->x_pos.i.hi = arg0->x_pos.i.hi;
            misc->y_pos.i.hi = arg0->y_pos.i.hi;
            misc->bg_offset = arg0->bg_offset;
            misc->animation_table = (void*)arg0->animation_table;
            misc->unk40 = arg0->unk40;
            misc->unk3C = (void*)arg0->sprite_frames;
            misc->unk16 = 5;
            misc->ext.misc_22.owner = arg0;
            misc->ext.misc_22.timer = 0x24;
            misc->unk42 = arg0->unk42 & 0x7FFF;
            set_animation(misc, 0x18);
            misc->state = 0;
            misc->unk5 = 0;
            misc->unk6 = 1;
        }
    } else {
        arg0->y_speed = 0x5D31C;
        arg0->gravity = 0x3800;
    }
    arg0->unk6 = 1;
}

static void main61_wall_hit(struct MainObj* arg0)
{
    func_8001540C(2, 0xA8, arg0);
    split_mushroom_spawn_afterimage(arg0);
    if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
        start_screen_shake_x(0x10, 8, 2);
}

void func_8007A96C(struct MainObj* arg0)
{
    s32 offset;
    s32 target;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    offset = arg0->unk15 != 0 ? (s32)0xFEE80000 : (s32)0xFFD40000;
    target = background_objects[g_Player.bg_offset].x_pos.val - (arg0->x_pos.val + offset);
    if (arg0->ext.main_61.combo_count == 0) {
        arg0->x_speed = target / 48;
        arg0->y_speed = 0x55C00;
        func_8001540C(2, 0xA5, arg0);
    } else {
        arg0->x_speed = target / 36;
        func_8001540C(2, 0xA5, arg0);
        arg0->y_speed = 0x5D31C;
    }
    arg0->gravity = 0x3800;
    move_with_gravity(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 1;
    arg0->unk7 = 0;
}

void func_8007AB1C(struct MainObj* arg0)
{
    s32 dx;

    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_61.stunned != 0 && arg0->y_speed < 0)
        arg0->ext.main_61.stunned = 0;
    animate_object(ANIMATED_OBJECT(arg0));
    if ((s8)arg0->ext.main_61.combo_count == 0) {
        if (arg0->unk7 == 0) {
            set_animation(arg0, 3);
            arg0->unk7 = 1;
        }
        if (!(arg0->collision_flags & 8))
            return;
        if (arg0->ext.main_61.split_done == 0) {
            func_8001540C(2, 0xA9, arg0);
            func_8001540C(2, 0xA8, arg0);
        } else {
            func_8001540C(2, 0xA6, arg0);
            arg0->ext.main_61.split_done = 0;
        }
        arg0->contact_damage = 5;
        set_animation(arg0, 0);
        arg0->unk7C = 0x28;
        arg0->unk6 = 5;
        arg0->unk15 ^= 0x40;
        return;
    }
    if (arg0->unk7E == 0) {
        dx = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
        if (dx < 0)
            dx = -dx;
        if (dx < 0x1C) {
            stop_sound(2, 0xA7);
            arg0->unk7C = 0x14;
            arg0->unk6 = 2;
        }
    }
    if (arg0->unk15 == 0) {
        if (!(arg0->collision_flags & 2))
            return;
        main61_wall_hit(arg0);
        arg0->unk15 = 0x40;
    } else {
        if (!(arg0->collision_flags & 1))
            return;
        main61_wall_hit(arg0);
        arg0->unk15 = 0;
    }
    arg0->unk7E = 0;
    arg0->unk7C = 0xA;
    arg0->unk6 = 0;
}

void func_8007AE2C(struct MainObj* arg0)
{
    s32 i;

    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (!(arg0->collision_flags & 8))
        return;
    func_8001540C(2, 0xA8, arg0);
    if (!(background_objects[g_Player.bg_offset].unk34 & 1))
        start_screen_shake_y(0x10, 8, 2);
    for (i = 0; i < 4; i++)
        main61_spawn_shot(arg0, i, 0);
    set_animation(arg0, 9);
    arg0->unk7C = 0x30;
    arg0->unk6 = 4;
}

void func_8007B1BC(struct MainObj* arg0)
{
    s32 offset;
    s32 target;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;
    arg0->terrain_box = &split_mushroom_wall_terrain_box;
    if (arg0->x_pos.i.hi < background_objects[g_Player.bg_offset].x_pos.i.hi + 0xA0)
        arg0->unk15 = 0x40;
    else
        arg0->unk15 = 0;
    offset = arg0->unk15 != 0 ? (s32)0xFEE80000 : (s32)0xFFD40000;
    target = background_objects[g_Player.bg_offset].x_pos.val - (arg0->x_pos.val + offset);
    arg0->x_speed = target / 48;
    arg0->y_speed = 0x706AA;
    func_8001540C(2, 0xA5, arg0);
    arg0->gravity = 0x3800;
    move_with_gravity(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 1;
    arg0->unk7 = 0;
}

void func_8007B418(struct MainObj* arg0)
{
    struct ShotObj* shot;
    s16 count;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    count = arg0->unk7E;
    arg0->unk7E = count - 1;
    if (count == 0) {
        set_animation(arg0, 0x17);
        arg0->unk6 = 4;
        return;
    }
    func_8001540C(2, 0xAA, arg0);
    arg0->unk7C = 0x28;
    shot = find_free_shot_obj();
    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0x27;
    shot->unk2 = 0;
    shot->unk40 = arg0->unk40;
    shot->unk42 = engine_obj.stage == 3 ? 0x78CC : 0x788C;
    shot->unk68 = arg0->terrain_box;
    shot->unk54 = arg0->hurt_box;
    shot->unk50.data = arg0->attack_box;
    shot->animation_table = (void*)arg0->animation_table;
    shot->unk3C = (void*)arg0->sprite_frames;
    shot->unk15 = arg0->unk15 ^ 0x40;
    shot->bg_offset = arg0->bg_offset;
    shot->x_pos.val = arg0->x_pos.val;
    shot->y_pos.val = arg0->y_pos.val;
    if (arg0->unk2 == 0)
        shot->unk7C = (struct WeaponObj*)arg0;
    else
        shot->unk7C = (struct WeaponObj*)arg0->ext.main_61.partner;
    shot->state = 4;
    shot->unk6 = 0;
}

void func_8007B6BC(struct AnimatedObj* obj)
{
    struct MainObj* arg0 = (struct MainObj*)obj;
    s8 hp = arg0->unk2 == 0 ? arg0->hp : arg0->ext.main_61.partner->hp;

    set_animation(arg0, 5);
    func_8001540C(2, 0xA7, arg0);
    if (hp >= 0x19) {
        arg0->unk7C = 0x28;
        arg0->unk7E = 3;
        arg0->contact_damage = 6;
        arg0->unk5 = 5;
    } else {
        arg0->unk7C = arg0->unk2 != 0 ? 0x50 : 0x28;
        arg0->unk7E = 1;
        arg0->ext.main_61.combo_count = 2;
        arg0->contact_damage = 9;
        arg0->unk5 = 6;
    }
    arg0->unk6 = 0;
}

extern u8 mushroom_shot_sprout_hit_box[];
extern u8 mushroom_shot_sprout_palettes[];
extern u8 mushroom_shot_sprout_alt_palettes[];
extern u8 mushroom_shot_spray_offsets[];
extern s32 mushroom_shot_spray_speeds[];
extern void (*mushroom_shot_sprout_step_funcs[7])(struct ShotObj*);

void func_800A4D20(struct ShotObj* arg0)
{
    s8 index = arg0->unk2;

    arg0->state = 8;
    arg0->on_screen = 1;
    arg0->unk61 = 1;
    arg0->y_vel.val = 0x18000;
    arg0->unk58.data = NULL;
    arg0->x_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk15 == 0)
        arg0->x_pos.i.hi += (s8)mushroom_shot_spray_offsets[index * 2];
    else
        arg0->x_pos.i.hi -= (s8)mushroom_shot_spray_offsets[index * 2];
    arg0->y_pos.i.hi += (s8)mushroom_shot_spray_offsets[index * 2 + 1];
    arg0->unk50.data = mushroom_shot_sprout_hit_box;
    arg0->unk5C = 1;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk60 = 6;
    arg0->unk28 = mushroom_shot_spray_speeds[index];
    set_animation(arg0, 0x12);
}

void func_800A5194(struct ShotObj* arg0)
{
    s32 dx;
    s32 steps;
    s16 divisor;
    s32 x = arg0->x_pos.val;
    s32 y = arg0->y_pos.val;
    s32 vx;
    s32 vy;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->timer != 0)
        return;
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (dx < 0)
        dx = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    steps = 0x2A - (0xCD - dx) / 6;
    do {
        divisor = steps;
        arg0->x_vel.val = (g_Player.x_pos.val - x) / divisor;
        steps += 5;
        arg0->y_vel.val = ((divisor + 1) << 11) + (y - g_Player.y_pos.val) / divisor;
        vx = arg0->x_vel.val < 0 ? -arg0->x_vel.val : arg0->x_vel.val;
        vy = arg0->y_vel.val < 0 ? -arg0->y_vel.val : arg0->y_vel.val;
    } while (vx > 0x60000 || vy > 0x60000);
    arg0->unk2C = 0x1000;
    arg0->unk5 = 6;
}

extern char D_801005B4[];
extern u16 D_801005B8[];
extern u16 D_801005C8[];
extern union AnimationStep* slash_beast_animations[];
extern struct Unk_unk68 D_801078F8[];
extern struct Unk_unk68 D_8010020C;
extern struct Unk_unk68 D_80100218;
extern struct Unk_unk68 D_8010021C;
extern struct Unk_unk68 D_8010023C;
extern struct Unk_unk68 D_80100228;
extern struct Unk_unk68 D_8010022C;
extern union AnimationStep D_80100230[];
extern union AnimationStep D_80100234[];
extern union AnimationStep D_80100238[];
extern struct Unk_unk68 D_80100240;
extern struct Unk_unk68 D_80100244;
extern struct Unk_unk68 D_80100248;

#define M54_FLASH(o) ((o)->ext.main_54.flash_timer)
#define M54_81(o) ((o)->ext.main_54.powered_up)
#define M54_82(o) ((o)->ext.main_54.was_hit)
#define M54_84(o) ((o)->ext.main_54.grab)
#define M54_85(o) ((o)->ext.main_54.active)

void func_8006E920(struct MainObj* arg0, s32 value)
{
    s32 start = 0;
    s32 end;
    s32 i;
    u32* attrs;
    u16 index;

    if (value == 0x38) {
        end = engine_obj.stage == 0xC ? 0xE : 8;
    } else if (arg0->unk15 == 0) {
        if (engine_obj.stage == 0xC) {
            start = 7;
            end = 0xE;
        } else {
            start = 4;
            end = 8;
        }
    } else {
        end = engine_obj.stage == 0xC ? 7 : 4;
    }
    for (i = start; i < end; i++) {
        index = engine_obj.stage == 0xC ? D_801005C8[i] : D_801005B8[i];
        attrs = SP_BG_TILE_ATTRS;
        attrs[index] &= ~0xFF;
        attrs[index] |= value;
    }
}

void func_8006BB70(struct MainObj* arg0)
{
    arg0->contact_damage = 6;
    arg0->hp = 0;
    arg0->invincibility_timer = 0;
    arg0->collision_data = D_801078F8;
    if (engine_obj.stage != 0xC) {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    } else {
        arg0->unk40 = (D_801406A8[0] >> 7) + 0x160;
        arg0->unk42 = 0x7888;
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
        arg0->y_pos.val = background_objects[g_Player.bg_offset].y_pos.val + (s32)0xFFD00000;
    }
    arg0->animation_table = (const u8* const*)slash_beast_animations;
    arg0->unk16 = 6;
    arg0->hurt_box = D_801001FC;
    arg0->attack_box = D_801001F8;
    arg0->unk15 = 0x40;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->terrain_box = NULL;
    M54_FLASH(arg0) = 0;
    M54_81(arg0) = 1;
    M54_82(arg0) = 0;
    M54_84(arg0) = 0;
    M54_85(arg0) = 0;
    arg0->ext.main_54.claw_hitbox = 0;
    arg0->ext.main_54.pattern_set = 0;
    arg0->ext.main_54.power_hits = 1;
    arg0->ext.main_54.fight_started = 0;
    arg0->ext.main_54.high_jump = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_8006E920(arg0, 0x38);
    set_animation(arg0, 0);
    arg0->state = 1;
    arg0->unk5 = 9;
    arg0->unk6 = 0;
}

void func_8006BD1C(struct MainObj* arg0)
{
    s32 hit;
    s8 flash;
    const void* saved;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    slash_beast_step_funcs[arg0->unk5](arg0);
    if (arg0->ext.main_54.crash_timer != 0) {
        if (--arg0->ext.main_54.crash_timer == 0)
            func_8006E920(arg0, 0x38);
    }
    if (engine_obj.stage == 8 && arg0->ext.main_54.pattern_set == 1 && arg0->ext.main_54.fight_started != 0)
        engine_obj.character_state.bytes[1] = 1;
    if (M54_85(arg0) == 0)
        return;
    hit = func_8002DD04(arg0);
    flash = (s8)M54_FLASH(arg0);
    M54_82(arg0) = 0;
    if (flash == 0) {
        if (hit < 0) {
            func_8006E920(arg0, 0x38);
            g_Player.spike_immune = 1;
            arg0->state = 2;
            arg0->unk5 = 0;
            return;
        }
        if (hit != 0 && hit != 0x7F) {
            M54_82(arg0) = 1;
            arg0->collision_data = D_801060F0;
            arg0->unk42 |= 0x8000;
            M54_FLASH(arg0) = (u32)(hit - 0x19) < 2 ? 4 : 0x40;
            if ((hit == 6 || hit == 0xF) && M54_84(arg0) == 0 && arg0->ext.main_54.claw_hitbox == 0) {
                arg0->contact_damage = 6;
                arg0->unk5 = 0xA;
                arg0->unk6 = 0;
            }
        }
    } else {
        M54_FLASH(arg0) = --flash;
        if (flash == 0) {
            arg0->collision_data = D_801078F8;
            arg0->unk42 &= 0x7FFF;
        } else if (flash & 1) {
            arg0->unk42 &= 0x7FFF;
        } else {
            arg0->unk42 |= 0x8000;
        }
    }
    if (arg0->hp < 0x11)
        arg0->ext.main_54.pattern_set = 2;
    else if (arg0->hp < 0x21)
        arg0->ext.main_54.pattern_set = 1;
    if (M54_84(arg0) & 0x80)
        arg0->attack_box = &D_80100218;
    func_8002D9BC(arg0);
    if (arg0->ext.main_54.claw_hitbox != 0) {
        saved = arg0->attack_box;
        arg0->attack_box = &D_8010021C;
        func_8002D9BC(arg0);
        arg0->attack_box = saved;
    }
    if (arg0->animation_step.fields.frame_index == 0x25) {
        saved = arg0->attack_box;
        arg0->attack_box = &D_8010023C;
        func_8002D9BC(arg0);
        arg0->attack_box = saved;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x60, 0x60);
}

static void main54_spawn_shot(struct MainObj* arg0, s8 subtype)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0x1F;
    shot->unk2 = subtype;
    shot->unk40 = arg0->unk40;
    shot->unk42 = arg0->unk42;
    shot->animation_table = (void*)arg0->animation_table;
    shot->unk3C = (void*)arg0->sprite_frames;
    shot->bg_offset = arg0->bg_offset;
    shot->x_pos.val = arg0->x_pos.val;
    shot->y_pos.val = arg0->y_pos.val;
    shot->unk7C = (struct WeaponObj*)arg0;
    shot->state = 0;
    shot->unk15 = arg0->unk15;
}

void func_8006C378(struct MainObj* arg0)
{
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->x_speed == 0) {
        arg0->x_accel = 0;
        arg0->gravity = 0;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    switch (arg0->animation_step.fields.event) {
    case 1:
        set_animation(arg0, 0x25);
        arg0->gravity = 0x3800;
        arg0->unk6 = 2;
        break;
    case 2:
        arg0->attack_box = D_80100230;
        arg0->hurt_box = D_80100234;
        func_8001540C(2, 0x84, arg0);
        main54_spawn_shot(arg0, 0);
        break;
    case 3:
        arg0->attack_box = D_80100238;
        arg0->hurt_box = &D_80100240;
        func_8001540C(2, 0x84, arg0);
        if (M54_81(arg0) != 0)
            main54_spawn_shot(arg0, 1);
        break;
    case 4:
        arg0->attack_box = &D_80100228;
        arg0->hurt_box = &D_8010022C;
        break;
    case 5:
        arg0->attack_box = &D_80100244;
        arg0->hurt_box = &D_80100248;
        break;
    case 6:
        arg0->attack_box = D_801001F8;
        arg0->hurt_box = D_801001FC;
    case 7:
        arg0->attack_box = &D_80100208;
        arg0->hurt_box = &D_8010020C;
        break;
    }
}

static s32 main54_player_dx(struct MainObj* arg0)
{
    s32 dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;

    return dx < 0 ? -dx : dx;
}

static void main54_face_anim(struct MainObj* arg0, s32 anim)
{
    slash_beast_face_player(arg0);
    set_animation(arg0, anim);
}

extern u8 slash_beast_pattern_steps[9][4];

void func_8006C6AC(struct MainObj* arg0)
{
    u8* cursor;
    s8 next;

    if (main54_player_dx(arg0) >= 0xA1 && (get_random() & 7) == 0) {
        if (arg0->hp < 0x10) {
            main54_face_anim(arg0, 0x26);
            M54_84(arg0) = 1;
            next = 7;
        } else {
            main54_face_anim(arg0, 8);
            next = 2;
        }
        goto set_state;
    }
    cursor = arg0->ext.main_54.pattern;
    arg0->ext.main_54.pattern = cursor + 1;
    if ((cursor + 1 == slash_beast_pattern_steps[0] ? (u8)D_8010024C.unk3 : *cursor) == 0xFF)
        slash_beast_pick_pattern(arg0);
    switch (*arg0->ext.main_54.pattern) {
    case 0:
        if ((get_random() & 7) == 0) {
            main54_face_anim(arg0, 8);
            next = 2;
            goto set_state;
        }
        main54_face_anim(arg0, 0xB);
        arg0->unk7C = 0x3C;
        arg0->unk6 = 1;
        return;
    case 1:
        if ((get_random() & 7) == 0) {
            main54_face_anim(arg0, 8);
            next = 2;
        } else if (main54_player_dx(arg0) < 0x70) {
            if (M54_81(arg0) != 0) {
                set_animation(arg0, 0x26);
                next = 0xB;
            } else {
                main54_face_anim(arg0, 0xC);
                arg0->unk7C = 0x24;
                arg0->unk7E = 2;
                next = 6;
            }
        } else {
            main54_face_anim(arg0, 1);
            arg0->ext.main_54.high_jump = 0;
            next = 4;
        }
        break;
    case 2:
        if (main54_player_dx(arg0) < 0x70 && (get_random() & 7) != 0) {
            if (M54_81(arg0) != 0) {
                set_animation(arg0, 0x26);
                next = 0xB;
            } else {
                main54_face_anim(arg0, 0xC);
                arg0->unk7C = 0x24;
                arg0->unk7E = 2;
                next = 6;
            }
        } else {
            main54_face_anim(arg0, 8);
            next = 2;
        }
        break;
    case 3:
        main54_face_anim(arg0, 0x26);
        next = 7;
        break;
    case 4:
        main54_face_anim(arg0, 0xC);
        arg0->unk7C = 0x24;
        arg0->unk7E = 2;
        next = 6;
        break;
    case 5:
        main54_face_anim(arg0, 0x14);
        func_8001540C(2, 0x85, arg0);
        arg0->unk7C = 0x5A;
        next = 5;
        break;
    case 6:
        main54_face_anim(arg0, 0x26);
        M54_84(arg0) = 1;
        next = 7;
        break;
    case 7:
        main54_face_anim(arg0, 1);
        arg0->ext.main_54.high_jump = 1;
        next = 4;
        break;
    default:
        return;
    }
set_state:
    arg0->unk5 = next;
    arg0->unk6 = 0;
}

void func_8006CB50(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }
    arg0->x_accel = 0;
    set_animation(arg0, 2);
    arg0->hurt_box = &D_8010020C;
    arg0->attack_box = &D_80100208;
    if (arg0->ext.main_54.high_jump == 0) {
        arg0->x_speed = arg0->unk15 != 0 ? 0x24000 : -0x24000;
        arg0->y_speed = 0x5C000;
    } else {
        arg0->x_speed = arg0->unk15 != 0 ? 0x36000 : -0x36000;
        arg0->y_speed = 0x7C000;
    }
    arg0->gravity = 0x3800;
    func_8001540C(2, 0x81, arg0);
    move_with_gravity(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 1;
}

void func_8006CC3C(struct MainObj* arg0)
{
    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->contact_damage = 6;
        arg0->hurt_box = D_801001FC;
        arg0->unk62 = 0;
        arg0->attack_box = D_801001F8;
    }
    if (M54_84(arg0) != 0 && g_Player.stun_timer != 0) {
        func_8001540C(2, 0x86, arg0);
        g_Player.unk15 = arg0->unk15;
        if (arg0->unk15 == 0)
            g_Player.x_pos.i.hi = arg0->x_pos.i.hi - 0x12;
        else
            g_Player.x_pos.i.hi = arg0->x_pos.i.hi + 0x12;
        g_Player.y_pos.i.hi = arg0->y_pos.i.hi - 8;
        arg0->unk6 = 1;
    }
    if (arg0->collision_flags & 8) {
        func_8001540C(2, 0x82, arg0);
        arg0->y_speed = 0;
        arg0->gravity = 0;
        if (M54_84(arg0) != 0) {
            arg0->unk7C = 0xA;
            arg0->unk5 = 8;
            arg0->unk6 = 0;
        } else {
            set_animation(arg0, 3);
            arg0->unk6 = 2;
        }
    }
}

void func_8006CDD4(struct MainObj* arg0)
{
    s32 behind;

    animate_object(ANIMATED_OBJECT(arg0));
    if (M54_82(arg0) != 0) {
        if (arg0->unk15 == 0)
            behind = g_Player.x_pos.i.hi < arg0->x_pos.i.hi;
        else
            behind = arg0->x_pos.i.hi < g_Player.x_pos.i.hi;
        if (behind) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            return;
        }
    }
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x1E;
        set_animation(arg0, 0);
        slash_beast_face_player(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 1;
    }
}

static void main54_spawn_trail(struct MainObj* arg0, u8 layer, u8 frame_offset)
{
    struct MiscObj* misc = find_free_misc_obj();

    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 0x1A;
    misc->unk2 = 1;
    misc->unk16 = layer;
    misc->unk40 = arg0->unk40;
    misc->unk42 = arg0->unk42 & 0x7FFF;
    misc->animation_table = (void*)arg0->animation_table;
    misc->unk3C = (void*)arg0->sprite_frames;
    misc->bg_offset = arg0->bg_offset;
    misc->x_pos.val = arg0->x_pos.val;
    misc->y_pos.val = arg0->y_pos.val;
    misc->unk15 = arg0->unk15;
    misc->ext.misc_26.timer = 0x1E;
    misc->ext.misc_26.owner = arg0;
    misc->state = 0;
    misc->animation_step.fields.frame_index = arg0->animation_step.fields.frame_index + frame_offset;
}

static void main54_trails(struct MainObj* arg0)
{
    if (--arg0->ext.main_54.afterimage_timer != 0)
        return;
    main54_spawn_trail(arg0, 0x21, 0);
    if (M54_81(arg0) != 0)
        main54_spawn_trail(arg0, 0x20, 0x3C);
    arg0->ext.main_54.afterimage_timer = 0xA;
}

void func_8006CFB8(struct MainObj* arg0)
{
    s32 limit;
    s32 speed;

    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    main54_trails(arg0);
    limit = M54_81(arg0) != 0 ? 0x77FFF : 0x5FFFF;
    speed = arg0->x_speed < 0 ? -arg0->x_speed : arg0->x_speed;
    if (limit < speed)
        arg0->x_accel = 0;
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 == 0) {
        if (!(arg0->collision_flags & 2))
            return;
    } else {
        if (!(arg0->collision_flags & 1))
            return;
    }
    start_screen_shake_x(0x1E, 8, 2);
    arg0->contact_damage = 6;
    set_animation(arg0, 0xF);
    arg0->unk6 = 3;
    arg0->hurt_box = NULL;
    arg0->attack_box = NULL;
    arg0->ext.main_54.crash_timer = 0x1E;
    func_8001540C(2, 0x88, arg0);
    func_8006E920(arg0, 0x39);
}

void func_8006D280(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->hurt_box = D_801001FC;
        arg0->ext.main_54.claw_hitbox = 0;
        arg0->attack_box = D_801001F8;
    }
    if (arg0->animation_step.fields.event != 1)
        return;
    arg0->unk15 ^= 0x40;
    if (--arg0->unk7E == 0) {
        set_animation(arg0, 0x25);
        arg0->gravity = 0x3800;
        arg0->unk5 = 4;
        arg0->unk6 = 1;
    } else {
        set_animation(arg0, 0x10);
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi -= 0x20;
        else
            arg0->x_pos.i.hi += 0x20;
        arg0->unk6 = 4;
    }
}

void func_8006D3DC(struct MainObj* arg0)
{
    s32 target;
    s32 steps;
    s32 dist;
    s32 speed;
    s32 d;

    if (main54_player_dx(arg0) < 0x70) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        return;
    }
    if (arg0->animation_step.fields.event == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }
    arg0->x_accel = 0;
    if (M54_84(arg0) == 0) {
        set_animation(arg0, 2);
        target = arg0->x_pos.val;
        arg0->hurt_box = &D_8010020C;
        arg0->attack_box = &D_80100208;
    } else {
        M54_84(arg0) |= 0x80;
        target = arg0->x_pos.val + (arg0->unk15 != 0 ? 0x100000 : (s32)0xFFF00000);
        arg0->contact_damage = 0;
        arg0->unk62 = 3;
        set_animation(arg0, 4);
        func_8001540C(2, 0x87, arg0);
    }
    d = target - g_Player.x_pos.val;
    if (M54_84(arg0) != 0) {
        if (d >= 0) {
            steps = (u32)d >> 16;
        } else {
            d = g_Player.x_pos.val - target;
            if (d < 0)
                d += 0xFFFF;
            steps = (u32)d >> 16;
        }
        arg0->gravity = 0x6800;
    } else {
        if (d < 0)
            d = g_Player.x_pos.val - target;
        steps = d / 0x24000;
        arg0->gravity = 0x3800;
    }
    if (arg0->unk15 == 0)
        arg0->x_speed = -0x1C000 - (s16)steps * 0x480;
    else
        arg0->x_speed = (s16)steps * 0x480 + 0x1C000;
    dist = target - g_Player.x_pos.val;
    if (dist < 0)
        dist = g_Player.x_pos.val - target;
    speed = arg0->x_speed < 0 ? -arg0->x_speed : arg0->x_speed;
    arg0->y_speed = (((s16)(dist / speed) + 1) * arg0->gravity) / 2;
    move_with_gravity(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0x81, arg0);
    arg0->unk5 = 4;
    arg0->unk6 = 1;
}

void func_8006D888(struct MainObj* arg0)
{
    s16 y;
    s16 x;

    move_object(MOVING_OBJECT(arg0));
    main54_trails(arg0);
    y = arg0->y_pos.i.hi + arg0->terrain_box->unk1;
    if (arg0->unk15 == 0) {
        g_Player.x_pos.i.hi = arg0->x_pos.i.hi - 0x23;
        x = arg0->x_pos.i.hi + arg0->terrain_box->unk0 - 0x30;
    } else {
        g_Player.x_pos.i.hi = arg0->x_pos.i.hi + 0x23;
        x = arg0->x_pos.i.hi + arg0->terrain_box->unk0 + 0x30;
    }
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0x38) {
        func_8001540C(2, 0x88, arg0);
        arg0->unk6 = 3;
    }
}

void func_8006DD44(struct MainObj* arg0)
{
    struct ItemObj* item;
    struct MiscObj* misc;

    if (--arg0->unk7E != 0)
        return;
    if (engine_obj.stage != 0xC) {
        item = find_free_item_obj();
        if (item != NULL) {
            item->active = 0x41;
            item->id = 0x12;
            item->unk16 = 5;
            item->unk2 = 3 - (u8)arg0->unk7C;
            item->unk40 = arg0->unk40;
            item->unk42 = arg0->unk42 & 0x7FFF;
            item->animation_table = arg0->animation_table;
            item->sprite_frames = arg0->sprite_frames;
            item->animation_step.fields.frame_index = 0x79;
            item->state = 0;
            item->bg_offset = arg0->bg_offset;
        }
    }
    if (--arg0->unk7C != 0 && engine_obj.stage != 0xC) {
        arg0->unk7E = 0x1E;
        return;
    }
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 1;
    engine_obj.boss_ptr = arg0;
    arg0->unk7C = 0xC8;
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x1A;
        misc->unk2 = 0;
        misc->unk16 = 5;
        misc->unk40 = arg0->unk40;
        misc->unk42 = arg0->unk42 & 0x7FFF;
        misc->animation_table = (void*)arg0->animation_table;
        misc->unk3C = (void*)arg0->sprite_frames;
        misc->bg_offset = arg0->bg_offset;
        misc->x_pos.val = arg0->x_pos.val;
        misc->y_pos.val = arg0->y_pos.val;
        misc->unk15 = arg0->unk15;
        misc->ext.misc_26.owner = arg0;
        misc->state = 0;
        misc->animation_step.fields.frame_index = arg0->animation_step.fields.frame_index + 0x3C;
    }
    if (engine_obj.stage == 8) {
        arg0->unk15 = 0x40;
        set_animation(arg0, 0x15);
        arg0->x_speed = 0x10000;
        arg0->unk6 = 3;
    } else {
        arg0->unk15 = 0;
        set_animation(arg0, 0x17);
        arg0->unk7E = 1;
        arg0->unk6 = 4;
    }
}

void func_8006E450(struct MainObj* arg0)
{
    s16 x;
    s16 y;

    if (--arg0->ext.main_54.power_hits == 0) {
        y = arg0->y_pos.i.hi;
        arg0->y_pos.i.hi = y - 4;
        x = arg0->x_pos.i.hi;
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi = x + 0x1B;
        else
            arg0->x_pos.i.hi = x - 0x1B;
        spawn_debris(3, D_801005B4, arg0);
        arg0->y_pos.i.hi = y + 0xC;
        if (arg0->unk15 == 0)
            arg0->x_pos.i.hi = x + 0x1D;
        else
            arg0->x_pos.i.hi = x - 0x1D;
        spawn_debris(3, D_801005B4, arg0);
        arg0->x_pos.i.hi = x;
        arg0->y_pos.i.hi = y;
        M54_81(arg0) = 0;
    }
    set_animation(arg0, 0x11);
    if (arg0->x_pos.i.hi < g_Player.x_pos.i.hi) {
        arg0->unk15 = 0;
        arg0->x_speed = -0x10000;
    } else {
        arg0->unk15 = 0x40;
        arg0->x_speed = 0x10000;
    }
    arg0->y_speed = 0x40000;
    arg0->x_accel = 0;
    arg0->gravity = 0x8000;
    move_object(MOVING_OBJECT(arg0));
    arg0->unk6 = 1;
}

void func_800CC7F8(struct MiscObj* arg0)
{
    struct MainObj* owner = arg0->ext.misc_26.owner;

    if (arg0->unk2 == 0) {
        arg0->x_pos.val = owner->x_pos.val;
        arg0->y_pos.val = arg0->ext.misc_26.owner->y_pos.val;
        arg0->unk15 = arg0->ext.misc_26.owner->unk15;
        arg0->unk42 = arg0->ext.misc_26.owner->unk42;
        arg0->animation_step.fields.frame_index = arg0->ext.misc_26.owner->animation_step.fields.frame_index + 0x3C;
        owner = arg0->ext.misc_26.owner;
        if (owner->state >= 2 || owner->ext.main_54.powered_up == 0) {
            arg0->state = 1;
            return;
        }
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->ext.misc_26.timer--;
    if (owner->state >= 2 || arg0->ext.misc_26.timer == 0) {
        arg0->state = 1;
        return;
    }
    if (arg0->ext.misc_26.timer & 3)
        arg0->on_screen = 0;
    else
        is_on_screen(BASE_OBJECT(arg0));
}

extern u32* D_8011C0C8[];
extern struct Unk_unk68 ground_hunter_terrain_box[];

void func_80095854(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = ground_hunter_crawl_box;
    arg0->unk68 = ground_hunter_terrain_box;
    arg0->unk38 = (u8*)player_gfx + player_gfx[6];
    arg0->animation_table = D_8011C0C8;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0xE];
    arg0->unk15 = g_Player.unk15;
    buster_shot_place_at_muzzle((struct VisualObj*)arg0, &g_Player, arg0->id);
    arg0->x_vel.val = arg0->unk15 != 0 ? 0x60000 : -0x60000;
    arg0->y_vel.val = -0x20000;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 1;
    set_animation(arg0, 0);
    func_8001540C(1, 8, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x2C, 0x20);
}

void func_80057160(struct MainObj* self)
{
    self->hp = 3;
    self->contact_damage = 3;
    self->collision_data = D_80106EF4;
    self->animation_table = (const u8* const*)caterkiller_animations;
    self->invincibility_timer = 0;
    self->unk16 = 6;
    self->terrain_box = D_800FD014;
    self->bg_offset = g_Player.bg_offset;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    caterkiller_face_player(self);

    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    if (self->unk2 == 0) {
        set_animation(self, 0);
        self->unk5 = 2;
        self->ext.main_25.unk80 = 0x40;
        self->hurt_box = D_800FCFD4;
        self->attack_box = D_800FCFF4;
        self->gravity = 0;
        self->air_state = 0;
        self->ext.main_25.unk84 = 0;
    } else if (self->unk2 == 1 || self->unk2 == 2) {
        set_animation(self, 4);
        self->gravity = 0x4200;
        self->hurt_box = D_800FCFE4;
        self->attack_box = D_800FD004;
        self->unk6 = 1;
        self->air_state = 1;
        if (self->unk2 == 1) {
            self->unk5 = 4;
            self->ext.main_25.unk84 = 2;
        } else {
            self->unk5 = 6;
            self->ext.main_25.unk84 = 2;
        }
    }
    self->ext.main_25.unk88 = 0;
    self->state = 1;
    self->unk6 = 0;
}

void func_80057308(struct MainObj* self)
{
    unsigned index;

    caterkiller_check_fall(self);
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    caterkiller_step_funcs[self->unk5](self);
    if (self->y_speed < -0x50000)
        self->y_speed = -0x50000;
    if (self->unk5 == 6)
        return;

    self->ext.main_25.saved_unk5 = self->unk5;
    index = self->ext.main_25.unk84 * 2;
    self->attack_box = index == 0 ? D_800FD048[0] : D_800FD04C[index - 1];
    func_8002D9BC(self);
    self->attack_box = D_800FD04C[index];
    func_8002D9BC(self);
    self->hurt_box = D_800FD018[index];
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, caterkiller_debris, self);
        drop_item(BASE_OBJECT(self), 0xC);
        self->state = 2;
        return;
    }
    self->hurt_box = D_800FD018[index + 1];
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, caterkiller_debris, self);
        drop_item(BASE_OBJECT(self), 0xC);
        self->state = 2;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x28) != 0) {
        self->state = 2;
    } else {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    }
}

void func_8005754C(struct MainObj* self)
{
    s32 dy;
    s32 dx;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2)
        self->ext.main_25.unk84 = 1;
    if (self->animation_step.fields.event == 1)
        self->ext.main_25.unk84 = 0;

    self->ext.main_25.unk80--;
    if (self->ext.main_25.unk80 == 0 || (self->unk15 == 0 && (self->collision_flags & 2)) || (self->unk15 != 0 && (self->collision_flags & 1))) {
        self->unk6 = 2;
        self->x_accel = -0x1000;
        self->ext.main_25.unk80 = 0x80;
    }

    dy = g_Player.y_pos.i.hi - self->y_pos.i.hi;
    if (dy > -0x1A && dy < 0x1A) {
        set_animation(self, 1);
        self->unk5 = 3;
        self->unk6 = 0;
        self->ext.main_25.unk84 = 0;
    }

    if (dy >= 0x49) {
        dx = g_Player.x_pos.i.hi - self->x_pos.i.hi;
        if (dx > -0x31 && dx < 0x31) {
            self->air_state = 1;
            self->x_speed = 0;
            self->x_accel = 0;
            set_animation(self, 2);
            self->ext.main_25.unk88 = 1;
            self->unk5 = 5;
            self->unk6 = 0;
            self->ext.main_25.unk84 = 5;
        }
    }
    move_object(MOVING_OBJECT(self));
}

void func_80057874(struct MainObj* self)
{
    s32 dy;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2)
        self->ext.main_25.unk84 = 1;
    if (self->animation_step.fields.event == 1)
        self->ext.main_25.unk84 = 0;
    move_object(MOVING_OBJECT(self));

    dy = g_Player.y_pos.i.hi - self->y_pos.i.hi;
    if (dy <= -0x1A || dy >= 0x1A) {
        set_animation(self, 0);
        self->unk5 = 2;
        self->unk6 = 0;
        self->ext.main_25.unk80 = 0x40;
        self->ext.main_25.unk84 = 0;
        return;
    }
    if ((self->unk15 == 0 && self->x_pos.i.hi < g_Player.x_pos.i.hi) || (self->unk15 != 0 && g_Player.x_pos.i.hi < self->x_pos.i.hi)) {
        self->x_accel = -0x1000;
        self->unk6 = 2;
    }
}

void func_80057C00(struct MainObj* self)
{
    s32 dy;

    animate_object(ANIMATED_OBJECT(self));
    switch (self->animation_step.fields.event) {
    case 1:
        dy = g_Player.y_pos.i.hi - self->y_pos.i.hi;
        if (dy > -0x1A && dy < 0x1A) {
            set_animation(self, 1);
            self->unk5 = 3;
            self->unk6 = 0;
        } else {
            set_animation(self, 0);
            self->unk5 = 2;
            self->unk6 = 0;
            self->ext.main_25.unk80 = 0x40;
        }
        self->ext.main_25.unk84 = 0;
        break;
    case 2:
        self->y_pos.u.hi += 5;
        break;
    case 3:
        self->ext.main_25.unk84 = 3;
        self->y_pos.u.hi += 0xC;
        break;
    case 4:
        self->ext.main_25.unk84 = 4;
        self->y_speed = -0x50000;
        self->y_pos.u.hi += 0xC;
        break;
    case 5:
        if (self->collision_flags & 8) {
            self->air_state = 0;
            self->y_speed = 0;
        } else {
            move_object(MOVING_OBJECT(self));
        }
        break;
    case 6:
        self->ext.main_25.unk84 = 5;
        break;
    }
}

void func_800929DC(struct WeaponObj* self)
{
    self->on_screen = 1;
    self->animation_table = D_8011BF40;
    self->unk42 = 0x7802;
    self->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 12);
    self->unk40 = 0;
    if (self->id == 0x14) {
        self->unk16 = 0;
        self->unk50 = D_8010871C;
        self->unk64 = 1;
        self->x_vel.val = self->unk15 ? 0xB0000 : -0xB0000;
        set_animation(self, 0x1D);
    } else {
        self->unk50 = D_80108720;
        self->unk64 = 2;
        self->ext.weapon_20.lifetime = 0x5A;
        self->unk16 = 1;
        self->x_vel.val = 0;
        self->ext.weapon_20.timer = 4;
        set_animation(self, 0x1E);
    }
    self->unk28.val = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->unk5 = 0;
    self->state++;
    update_on_screen(BASE_OBJECT(self), 0x2A, 0x22);
}

void func_80092B5C(struct WeaponObj* self)
{
    struct WeaponObj* child;

    move_object(MOVING_OBJECT(self));
    if (self->unk98 != 0) {
        self->unk98 = 0;
        if (g_Player.shot_count < 4) {
            child = find_free_weapon_obj();
            if (child != NULL) {
                child->active = 0x21;
                child->id = 0x15;
                child->unk2 = 0;
                child->bg_offset = self->bg_offset;
                child->x_pos = self->x_pos;
                child->y_pos = self->y_pos;
                child->unk15 = self->unk15;
                g_Player.shot_count++;
            }
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x2A, 0x22);
}

void func_8005A538(struct MainObj* self)
{
    struct MainObj* controller = SP_CUR_MAIN_OBJ;
    struct MainObj* child;
    u8* context = (u8*)&controller->ext;

    self->unk5 = 2;
    self->hp = 8;
    self->contact_damage = 3;
    self->state = 1;
    self->unk6 = 0;
    self->unk7C = 0;
    self->on_screen = 1;
    self->invincibility_timer = 0;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    *(u16*)(context + 2) = self->x_pos.u.hi;
    *(u16*)(context + 4) = self->y_pos.u.hi;
    self->animation_table = (const u8* const*)pod_spawner_animations;
    self->hurt_box = D_800FD834;
    self->attack_box = D_800FD830;
    self->collision_data = D_801060F0;
    self->terrain_box = NULL;
    self->air_state = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk16 = 7;
    context[0] = 0;
    context[1] = self->unk2 == 3;
    controller->ext.main_29.slots.controller.target = NULL;
    controller->ext.main_29.slots.controller.record = NULL;

    child = find_free_main_obj();
    if (child != NULL) {
        child->active = self->active;
        child->id = self->id;
        child->unk2 = -0x80;
        controller->ext.main_29.slots.controller.target = (struct Main29Record*)child;
        child->ext.main_29.source = self;
        __builtin_memset(child->ext.main_29.slots.children, 0, sizeof(child->ext.main_29.slots.children));
    }
    set_animation(self, 0);
}

void func_800745E8(struct MainObj* self)
{
    s32 status;
    s32 x_margin = 0;
    s32 y_margin = 0;

    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    if (self->unk5 != 4 && func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1)
        self->unk5 = 2;
    beam_drone_step_funcs[self->unk5](self);
    status = func_8002DD04(self);
    func_8002D9BC(self);
    if (self->unk5 != 0)
        self->ext.main_58.saved_unk5 = self->unk5;
    if (status < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(3, &beam_drone_debris, self);
        if (self->unk2 == 0)
            drop_item(BASE_OBJECT(self), 8);
        self->ext.main_58.unk88 = 2;
        self->state = 2;
        return;
    }
    if (self->unk2 != 0 && engine_obj.character_state.fields.active != 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(3, &beam_drone_debris, self);
        self->ext.main_58.unk88 = 2;
        self->state = 2;
        return;
    }
    switch (self->unk2) {
    case 0:
        x_margin = 0x60;
        y_margin = 0x40;
        break;
    case 1:
        x_margin = 0x40;
        y_margin = 0x50;
        break;
    case 2:
        x_margin = 0x50;
        y_margin = 0x40;
        break;
    }
    if (func_8002B1E8(BASE_OBJECT(self), x_margin, y_margin) == 0) {
        if (self->active != 0)
            update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else if (self->unk5 != 4) {
        self->state = 2;
    }
}

void func_8004B418(struct MainObj* self)
{
    u8* context = (u8*)&SP_CUR_MAIN_OBJ->ext;
    u8 angle = context[4] & 0xFE;
    u8 animation = 0x11;
    switch (angle) {
    case 2:
    case 4:
    case 6:
    case 10:
    case 12:
    case 14:
        animation = 0x12;
        break;
    case 8:
        animation = 0x13;
        break;
    case 18:
    case 20:
    case 22:
    case 26:
    case 28:
    case 30:
        animation = 0x14;
        break;
    case 24:
        animation = 0x15;
        break;
    }
    if (animation != 0x11 && self->animation_step.fields.event != 1)
        return;
    set_animation(self, animation);
    context[5]++;
    self->unk6++;
}

void func_8004B2BC(struct MainObj* self)
{
    u8* context = (u8*)&SP_CUR_MAIN_OBJ->ext;
    u8 angle = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    u8 direction = angle & 0xFE;
    context[4] = angle;

    switch (direction) {
    case 0:
        self->unk15 = 0x40;
        break;
    case 2:
    case 4:
    case 6:
        self->unk15 = 0x40;
        /* fall through */
    case 10:
    case 12:
    case 14:
        if (angle >= 10)
            self->unk15 = 0;
        set_animation(self, 7);
        break;
    case 8:
        set_animation(self, 3);
        break;
    case 16:
        self->unk15 = 0;
        break;
    case 18:
    case 20:
    case 22:
        self->unk15 = 0;
        /* fall through */
    case 26:
    case 28:
    case 30:
        if (angle >= 26)
            self->unk15 = 0x40;
        set_animation(self, 9);
        break;
    case 24:
        set_animation(self, 5);
        break;
    }
    context[6] = 0x14;
    context[5] = 0;
    self->unk6++;
}

void func_8004B0A0(struct MainObj* self)
{
    u8* context = (u8*)&SP_CUR_MAIN_OBJ->ext;
    u16* timer = (u16*)(context + 2);

    if (self->unk2 == 0) {
        s32 dx = self->x_pos.i.hi - g_Player.x_pos.i.hi;
        s32 dy = self->y_pos.i.hi - g_Player.y_pos.i.hi;
        if (dx > -0x90 && dx < 0x90 && dy > -0x90 && dy < 0x90) {
            self->unk5 = 5;
            *timer = 0x78;
        } else {
            self->unk5 = 2;
            *timer = 0x3C;
        }
        return;
    }

    if (self->x_pos.i.hi < g_Player.x_pos.i.hi - 0x10 || self->x_pos.i.hi > g_Player.x_pos.i.hi + 0x10) {
        if (--*timer != 0) {
            s16 old_y = g_Player.y_pos.i.hi;
            g_Player.y_pos.i.hi = old_y - 0x30;
            context[4] = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
            g_Player.y_pos.i.hi = old_y;
            set_velocity_from_angle(MOVING_OBJECT(self), context[4]);
            move_object(MOVING_OBJECT(self));
            return;
        }
    }
    context[4] = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    self->unk5 = 5;
    self->unk6 = 0;
}

void func_80061B58(struct MainObj* self)
{
    struct Main39Ext* ext = &self->ext.main_39;
    if (--ext->unk94 == 0) {
        func_8001540C(2, 0x59, self);
        ext->unk94 = 0x1E;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_pos.i.hi >= 0x119) {
        self->y_speed = 0;
        self->gravity = 0;
    }
    self->unk7E++;
    if ((self->unk7E & 7) == 0 && (!(background_objects[0].unk34 & 0x10) || (((u8*)&background_objects[0].unk3E)[0] & 7) != 4))
        start_screen_shake_x(8, 4, 2);
    if ((self->unk7E & 0xF) == 0)
        spawn_explosion_at(0, self->x_pos.i.hi, self->y_pos.i.hi + 0x10, 1);
    if (--self->unk7C != 0)
        return;
    if (self->unk2 & 1) {
        self->unk6 = 2;
        return;
    }
    for (s32 i = 0; i < 2; i++) {
        struct ItemObj* item = find_free_item_obj();
        if (item != NULL) {
            item->active = 0x41;
            item->id = 0xF;
            item->unk2 = self->unk2 < 8 ? i : i + 2;
            item->bg_offset = self->bg_offset;
            item->x_pos.val = 0;
            item->y_pos.val = 0;
            item->x_pos.u.hi = ext->unk80.h.unk80;
            item->y_pos.u.hi = ext->unk84.h.unk86;
            item->state = 0;
        }
    }
    self->unk6 = 2;
}

void func_80061918(struct MainObj* self)
{
    struct Main39Ext* ext = &self->ext.main_39;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_speed == 0x10000 || self->y_speed == -0x10000)
        self->gravity = -self->gravity;
    if (ext->unk88 == 0) {
        if (ext->unk84.h.unk84 < g_Player.x_pos.i.hi) {
            self->gravity = 0x2000;
            set_animation(self, 1);
            self->unk5 = 1;
        }
        return;
    }
    ext->unk8C += ext->unk90;
    ext->unk90 += 0x1000;
    if (ext->unk90 > 0x10000)
        ext->unk90 = 0x10000;
    if (ext->unk8C > 0x3000000)
        ext->unk8C = 0x3000000;
    if (g_Player.y_pos.val >= ext->unk8C || self->y_pos.val >= g_Player.y_pos.val)
        return;
    s32 target_x = g_Player.x_pos.i.hi + (self->unk2 & 1 ? 0x10 : -0x10);
    if (target_x - self->x_pos.i.hi >= -0x10 && target_x - self->x_pos.i.hi <= 0x10) {
        self->gravity = 0x8000;
        self->unk5 = 2;
    }
}

void func_8009C45C(struct ShotObj* self)
{
    struct WeaponObj* owner = self->unk7C;

    if (self->unk5 == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            set_animation(self, self->unk84.value + 1);
            self->unk5 = 1;
            if (owner->active != 0 && owner->id == 0x1D && owner->state == 1 && owner->unk2 >= 0)
                owner->unk5 = 4;
        } else {
            s8 index = self->animation_step.fields.event;
            self->unk50.data = index > 0 && index <= 12 ? turret_laser_beam_boxes[index - 1]
                                                        : turret_laser_full_beam_box;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
    self->x_pos = owner->x_pos;
    self->y_pos = owner->y_pos;
    func_8002D9BC(self);
    func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(&g_Player));
    if (self->unk2 < 2)
        update_on_screen(BASE_OBJECT(self), 0x68, 0x10);
    else
        update_on_screen(BASE_OBJECT(self), 0x10, 0x68);
}

void func_800C4778(struct ItemObj* self)
{
    if (self->unk2 < 4) {
        s32 index;
        self->state = 1;
        self->on_screen = 1;
        self->unk5 = 0;
        self->unk6 = 0;
        self->unk7 = 0;
        self->active |= 0x40;
        self->unk18 = self->x_pos;
        self->unk1C = self->y_pos;
        index = (u8)func_8002938C(0x29);
        self->animation_table = (const u8* const*)data_hopper_animations;
        self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
        self->unk40 = D_801406A8[index] >> 7;
        self->unk42 = ((index * 4 + 0x18) & 0xF) | ((((index + 6) / 4 + 0x1E0) << 6) & 0xFFFF);
        self->unk54 = NULL;
        self->unk50 = NULL;
        self->unk68 = (struct Unk_unk68*)(self->unk2 == 0 ? data_capsule_box_0 : self->unk2 == 1 ? data_capsule_box_1
                                                                                                 : data_capsule_box_2);
        self->unk76 = -1;
        self->unk75 = 1;
        self->unk16 = 6;
        self->unk67 = 0;
        self->x_vel.val = 0;
        self->y_vel.val = 0;
        self->unk28 = 0;
        self->unk2C = 0;
        self->unk7C.timer16 = 0xA;
        ((u16*)&self->unk7C)[1] = 0;
        self->unk7 = engine_obj.character_state.fields.active;
        set_animation(self, self->unk2 + 0xF);
    } else {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
        self->unk7 = 0;
        self->on_screen = 0;
        for (s32 i = 0; i < 2; i++) {
            struct ItemObj* child = find_free_item_obj();
            if (child != NULL) {
                struct Item19SpawnPosition* pos = &data_capsule_positions[(self->unk2 - 4) * 2 + i];
                child->active = 1;
                child->id = 0x13;
                child->unk2 = i;
                child->x_pos.u.hi = pos->x;
                child->y_pos.u.hi = pos->y;
            }
        }
        despawn_object_permanently(OBJECT_HEADER(self));
    }
}

void func_800C3BA4(struct ItemObj* self)
{
    u8* phase = (u8*)&self->ext;
    struct BackgroundObj* bg = &background_objects[0];

    if (self->y_pos.i.hi < 0x3B1 && bg->y_pos.i.hi == 0x2D0) {
        bg->unk20 = 0x2D0;
        bg->unk22 = 0x2D0;
        start_screen_shake_y(0x1E, 2, 1);
        stop_sound(5, 5);
        self->unk5++;
        return;
    }
    *phase = 1 - *phase;
    if (*phase != 0) {
        bg->unk47 = 1;
        return;
    }
    if (self->y_pos.i.hi >= 0x3B1)
        self->y_pos.u.hi--;
    bg->unk47 = 0;
}

void func_800C609C(struct ItemObj* self)
{
    s32 index;
    self->state = 1;
    self->unk5 = 0;
    self->on_screen = 1;
    index = func_8002938C(0x9E);
    self->unk40 = D_801406A8[index] >> 7;
    self->unk42 = ((((index * 4 + 0x18) & 0xF)) | ((((index + 6) / 4 + 0x1E0) << 6) & 0xFFFF));
    self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
    self->animation_table = (const u8* const*)breakable_panel_animations;
    self->unk5C = 0x20;
    self->unk58 = (const u8*)D_80108504;
    self->unk15 = 0;
    self->unk61 = 0;
    self->unk75 = 1;
    self->unk16 = 5;
    self->unk54 = (const u8*)&breakable_panel_hit_box;
    self->unk68 = (struct Unk_unk68*)breakable_panel_terrain_box;
    self->bg_offset = g_Player.bg_offset;
    set_animation(self, 0);
}

void func_8008AAF4(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = 0x4200;
        self->air_state = 1;
        set_animation(self, 3);
        self->hurt_box = ride_armor_pilot_hurt_box;
        self->attack_box = ride_armor_pilot_attack_box;
        self->contact_damage = 5;
    }
    if (self->collision_flags & 8) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 5);
        return;
    }
    if (ext->unk8D & 2)
        return;
    if (ext->unk87 != 0) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 0xA);
        return;
    }
    if (self->id == 0x48 && ext->unk86 != 0) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 0xC);
        return;
    }
    self->x_speed = 0;
    ride_armor_pilot_set_jump_speed(self);
    if (self->y_speed < -0x5E000)
        self->y_speed = -0x5E000;
    move_with_gravity(ANIMATED_OBJECT(self));
}

void func_8008A064(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        ext->unk8A = 0;
        set_animation(self, 0);
        ext->unk84 = 0x160;
        ext->pad8B[1] = get_random() & 0x3F;
        ride_armor_pilot_update_facing(self);
    }
    if (!(self->collision_flags & 8)) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        return;
    }
    if (ext->pad8B[1] != 0) {
        ext->pad8B[1]--;
    } else if (!(ext->unk8D & 2)) {
        if (ride_armor_pilot_update_facing(self) != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 3);
            return;
        }
        if (ext->unk86 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 8);
            return;
        }
        if (ext->unk87 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 9);
            return;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_80089C7C(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;
    s32 dx;
    s16 x;
    s16 y;

    if (self->unk5 < 2)
        return;
    dx = self->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (dx > -0x41 && dx < 0x41) {
        ext->unk87 = 1;
    } else if (self->unk2 == 0) {
        if (dx <= -0x98 || dx >= 0x98)
            ext->unk88 = 1;
        ext->unk8A = dx < 0 ? 1 : 2;
    } else {
        ext->unk8A = 0;
    }
    if (self->air_state != 0 || ext->unk86 != 0 || ext->unk87 != 0 || (ext->unk8D & 8) != 0)
        return;
    y = self->y_pos.u.hi + self->terrain_box->unk3;
    if (ext->unk8A & self->collision_flags) {
        x = self->unk15 == 0 ? self->x_pos.u.hi - self->terrain_box->unk2
                             : self->x_pos.u.hi + self->terrain_box->unk2 + 1;
        y--;
        for (u32 i = 0; i < 5; i++, y -= 0x10) {
            if ((u8)func_8002D724(PLAYER_OBJECT(self), x, y) == 0) {
                ext->unk86 = 1;
                break;
            }
        }
        if (ext->unk86 == 0)
            ext->unk8A = 0;
    } else if ((u8)func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi, y + 2) == 0) {
        ext->unk86 = 1;
    }
}

void func_8008AC40(struct MainObj* self)
{
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    if (self->ext.main_71.pad8B[0] != 0)
        self->ext.main_71.pad8B[0]--;
    func_80089C7C(self);
    ride_armor_pilot_check_dash(self);
    ride_armor_pilot_step_funcs[self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
    func_8002D9BC(self);
    s32 status = func_8002DD04(self);
    if (status < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(7, ride_armor_pilot_debris, self);
        drop_item(BASE_OBJECT(self), 0x11);
        self->state = 2;
        self->unk5 = 0;
    } else if (status != 0) {
        ride_armor_pilot_spawn_dust((struct VisualObj*)self, 8);
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0)
        is_on_screen(BASE_OBJECT(self));
    else {
        self->state = 2;
        self->unk5 = 0;
    }
}

void func_80074438(struct MainObj* self)
{
    self->active = 0x41;
    self->hp = 5;
    self->contact_damage = 3;
    self->invincibility_timer = 0;
    self->collision_data = D_80107AF8;
    self->bg_offset = g_Player.bg_offset;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    if (self->unk2 == 0)
        self->unk15 = g_Player.x_pos.val < self->x_pos.val ? 0 : 0x40;
    switch (self->unk2) {
    case 0:
        self->x_speed = 0;
        self->y_speed = 0;
        self->unk7E = 0x28;
        break;
    case 1:
        self->x_speed = 0;
        self->y_speed = self->y_pos.val < g_Player.y_pos.val ? -0x18000 : 0x18000;
        self->unk7E = 0x3C;
        break;
    case 2:
        self->x_speed = g_Player.x_pos.val < self->x_pos.val ? -0x15000 : 0x15000;
        self->y_speed = 0;
        self->unk7E = 0x3C;
        break;
    }
    self->animation_table = (const u8* const*)beam_drone_animations;
    self->unk16 = 5;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->terrain_box = NULL;
    self->hurt_box = &beam_drone_hit_box;
    self->attack_box = &beam_drone_hit_box;
    set_animation(self, 0);
    self->state = 1;
    memset(&self->ext, 0, 0x18);
    self->unk7C = 0;
    self->unk5 = 2;
    self->unk6 = 0;
}

void func_8006EB40(struct MainObj* self)
{
    if (engine_obj.palette_flags & 0x10) {
        self->state = 2;
        return;
    }
    self->on_screen = 1;
    self->state = 1;
    self->unk5 = 2;
    self->unk16 = 6;
    self->contact_damage = 6;
    self->unk15 = 0x40;
    self->animation_table = (const u8* const*)jet_stingray_flyby_animations;
    self->hp = 0x20;
    self->attack_box = &jet_stingray_flyby_attack_box;
    self->hurt_box = &jet_stingray_flyby_hurt_box;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->terrain_box = NULL;
    self->collision_data = D_80107978;
    self->bg_offset = g_Player.bg_offset;
    self->y_pos = g_Player.y_pos;
    if (self->unk2 != 0) {
        self->y_pos = g_Player.y_pos;
        self->x_speed = 0x90000;
        self->x_pos.val = background_objects[(u8)self->bg_offset].x_pos.val - 0x400000;
    } else {
        self->y_pos.val = background_objects[(u8)self->bg_offset].y_pos.val + 0x400000;
        self->x_speed = 0x40000;
        self->ext.main_55.pad80[4] = 0;
        self->x_pos.val = background_objects[(u8)self->bg_offset].x_pos.val + 0x1B00000;
    }
    set_animation(self, 0);
}

void func_80089AA4(struct MainObj* self)
{
    self->unk5 = 2;
    self->state = 1;
    self->on_screen = 1;
    self->hp = 0x18;
    self->animation_table = (const u8* const*)ride_armor_pilot_animations;
    self->hurt_box = ride_armor_pilot_hurt_box;
    self->attack_box = ride_armor_pilot_attack_box;
    self->terrain_box = &ride_armor_pilot_terrain_box;
    self->unk6 = 0;
    self->unk7 = 0;
    self->unk7C = 0;
    self->contact_damage = 5;
    self->invincibility_timer = 0;
    self->collision_data = D_80108184;
    self->air_state = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk16 = 5;
    self->ext.main_71.unk86 = 0;
    self->ext.main_71.unk87 = 0;
    self->ext.main_71.unk88 = 0;
    self->ext.main_71.pad89 = 0;
    self->ext.main_71.unk8A = 0;
    self->ext.main_71.unk8D = 0;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
}

void func_80059E40(struct MainObj* self)
{
    struct Main28Ext* ext = &self->ext.main_28;
    if (self->animation_step.fields.relative_step == 0) {
        u8 index = (u8)self->unk2 * 2;
        self->unk5 = 3;
        ext->context->unk7C = 0;
        set_animation(self, ext->unk84 + 1);
        self->x_speed = 0;
        self->y_speed = 0;
        if (get_random() & 7) {
            self->x_accel = D_800FD618[index / 2].x;
            self->gravity = D_800FD618[index / 2].y;
        } else {
            self->x_accel = D_800FD638[index / 2].x;
            self->gravity = D_800FD638[index / 2].y;
        }
        self->unk7C = 0;
        self->unk7E = D_800FD5C8[get_random() & 0x1F];
        self->hurt_box = D_800FD5B8[0];
        self->attack_box = D_800FD5C0[0];
        self->terrain_box = D_800FD5B0[0];
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8004D6FC(struct MainObj* self)
{
    struct Main14Ext* ext = &self->ext.main_14;

    if (self->unk5 == 2 || self->unk5 == 5)
        return;
    if (--ext->unk84 != 0)
        return;
    if (ext->visual_variant >= 7)
        return;
    switch (++ext->visual_variant) {
    case 4:
        ext->unk84 = 0x1E;
        break;
    case 5:
        ext->unk84 = 0x14;
        break;
    case 6:
        ext->unk84 = 0x32;
        break;
    }
}

void func_8005BFC0(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        struct ShotObj* shot;
        s32 direction;

        get_random_nonzero();
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x11;
            shot->unk7C = (struct WeaponObj*)self;
            shot->state = 0;
            shot->x_pos.val = self->x_pos.val + (self->unk15 ? -0x540000 : 0x540000);
            shot->y_pos.val = self->y_pos.val - 0x20000;
            shot->unk2 = 1;
            direction = (s8)angle_to_object(OBJECT_HEADER(shot), OBJECT_HEADER(&g_Player));
            if (self->unk15)
                direction += self->animation_step.fields.event + 1;
            else
                direction -= self->animation_step.fields.event - 1;
            shot->unk6 = direction & 0x1F;
            self->animation_step.fields.event = 0;
        }
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 0);
        self->unk5 = 3;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void func_8005B24C(struct MainObj* self)
{
    struct Main29Ext* ext = &self->ext.main_29;

    ext->unk94 = 0;
    for (u32 i = 0; i < 4; i++) {
        struct MainObj* child = ext->slots.children[i];
        if (child != NULL && child->active != 0 && child->id == 0x1C)
            child->state = 3;
        ext->slots.children[i] = NULL;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void func_80088C40(struct MainObj* self)
{
    if (engine_obj.checkpoint >= 2) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    self->active = 0x41;
    self->hp = 0;
    self->contact_damage = 0;
    self->invincibility_timer = 0;
    self->collision_data = D_80108104;
    self->animation_table = (u32**)D_80104974;
    self->unk16 = 5;
    self->hurt_box = &D_80104914;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->attack_box = NULL;
    self->terrain_box = NULL;
    self->unk15 = 0;
    self->unk1C = self->y_pos;
    self->bg_offset = g_Player.bg_offset;
    self->unk18 = self->x_pos;
    set_animation(self, 0);
    memset(&self->ext.main_70, 0, sizeof(self->ext.main_70));
    self->unk5++;
}

void func_8008A9F4(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        set_animation(self, 8);
        self->attack_box = &ride_armor_pilot_guard_box;
        self->contact_damage = 6;
        ext->unk8D |= 8;
        func_8001540C(2, 0x3C, self);
    }

    ext->unk8E--;
    if (!(self->collision_flags & 8)) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        return;
    }
    if (!(ext->unk8D & 2)) {
        if ((self->collision_flags & 3) || (self->animation_step.fields.event & 1)) {
            if ((s8)ext->unk8E < 0) {
                ride_armor_pilot_set_step(BASE_OBJECT(self), 7);
                ext->unk8D &= ~8;
            } else {
                ride_armor_pilot_apply_x_speed(self);
            }
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_800C4F40(struct ItemObj* self)
{
    for (u32 i = 0; i < 3; i++)
        background_objects[i].unk4C = 1;

    g_Player.y_pos.val = 0x8000000 - g_Player.y_pos.val;
    g_Player.unk1C.val = 0x8000000 - g_Player.unk1C.val;
    background_objects[0].y_pos.val = 0x7000000 - background_objects[0].y_pos.val;
    background_objects[0].unk18.val = 0x7000000 - background_objects[0].unk18.val;
    for (u32 i = 1; i < 3; i++) {
        background_objects[i].y_pos.val = 0x9000000 - background_objects[i].y_pos.val;
        background_objects[i].unk18.val = 0x9000000 - background_objects[i].unk18.val;
    }
    gravity_switch_flip_objects();
    engine_obj.character_state.bytes[0] = 1 - (u8)engine_obj.character_state.bytes[0];
    func_800C5210(self);
    self->unk5 = 0;
}

void func_800C5210(struct ItemObj* self)
{
    u32 index = (u8)self->unk2 >> 4;
    s32 offset = engine_obj.character_state.bytes[0] ? 1 : -1;

    background_objects[0].unk22 = gravity_switch_camera_bounds[index * 2];
    background_objects[0].unk2A = gravity_switch_camera_bounds[index * 2];
    background_objects[0].unk20 = gravity_switch_camera_bounds[index * 2 + 1];
    background_objects[0].unk28 = gravity_switch_camera_bounds[index * 2 + 1];
    background_objects[1].unk42 += 0x80 * offset;
    background_objects[2].unk42 += 0xC0 * offset;
}

void func_8004619C(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 1);
    func_8001540C(2, 0x13, self);
    self->x_accel = 0x400;
    self->x_speed = 0;
    self->ext.main_5.unk80 = self->unk15;
    self->ext.main_5.pad81[0] = 0;
    self->gravity = -0x400;
    self->unk7C = 0x3C;
    self->unk6++;
    self->y_speed = D_800FA130[0];
}

void func_800B1864(struct VisualObj* self)
{
    struct MainObj* parent = (struct MainObj*)self->unk50;
    s32 variant = parent->ext.main_14.visual_variant;

    if (parent->active != 0)
        parent->id = 0xE;
    else
        self->state++;

    if (variant == 0xFF || parent->state == 2) {
        self->state++;
        return;
    }
    if (variant != self->unk2 && !(variant == 6 && parent->unk5 < 3)) {
        self->unk2 = variant;
        set_animation(self, (s8)variant);
    }
    animate_object(ANIMATED_OBJECT(self));
    self->x_pos.u.hi = parent->x_pos.u.hi;
    self->y_pos.u.hi = parent->y_pos.u.hi;
    if (parent->unk5 == 1)
        self->y_pos.u.hi -= 5;
    else if (parent->unk5 != 0) {
        self->x_pos.u.hi -= 2;
        self->y_pos.u.hi -= 10;
    }
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
}

void func_8009C638(struct ShotObj* self)
{
    struct MainObj* parent = (struct MainObj*)self->unk7C;
    s32 direction;

    self->unk40 = parent->unk40;
    self->unk42 = parent->unk42 & 0x7FFF;
    self->animation_table = parent->animation_table;
    self->unk3C = (void*)parent->sprite_frames;
    self->unk15 = parent->unk15;
    self->bg_offset = parent->bg_offset;
    self->unk50.data = depth_charge_sink_box;
    self->unk54 = depth_charge_sink_box;
    self->unk5C = 1;
    self->unk60 = 3;
    if (self->unk2 != 0) {
        self->unk16 = 0x20;
        self->unk68 = (struct Unk_unk68*)depth_charge_boxes;
        self->unk58.animation_steps = D_80105FF0;
        set_animation(self, 5);
        direction = (u8)self->unk6;
    } else {
        self->unk16 = 0x10;
        self->unk68 = NULL;
        self->unk58.collision_data = D_80106070;
        set_animation(self, 8);
        direction = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF;
    }
    set_velocity_from_angle(MOVING_OBJECT(self), direction);
    self->unk5 = 2;
    self->x_vel.val *= 2;
    self->y_vel.val *= 2;
    self->state++;
}

void func_80088EA4(struct MainObj* self)
{
    s8 old_unk5C = self->hp;
    s32 collision;

    drone_pod_step_funcs[self->unk5](self);
    collision = func_8002DD04(self);
    if ((s32)old_unk5C - self->hp >= 4)
        spawn_debris(4, &D_801049AC, self);
    if (self->unk5 != 0)
        self->ext.main_70.saved_unk5 = self->unk5;
    if (collision < 0) {
        set_animation(self, 3);
        self->unk5 = 0;
        self->unk6 = 0;
        self->state++;
    } else {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    }
}

void func_8009C784(struct ShotObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    if ((u32)(self->x_pos.u.hi - 0x1721) >= 0xFF && self->unk2 != 0) {
        self->x_vel.val = 0;
        self->y_vel.val = -0x20000;
    }
    if (self->y_pos.i.hi - background_objects[(s8)self->bg_offset].y_pos.i.hi >= 0xAC && self->unk2 != 0) {
        self->unk2C = 0x1000;
        self->unk28 = 0;
        self->y_vel.val = 0x10000 - self->y_vel.val;
        self->unk5++;
    }
}

void func_8008A8E4(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        ext->unk84 = 0x160;
        set_animation(self, 6);
        self->hurt_box = ride_armor_pilot_hurt_box;
        self->attack_box = ride_armor_pilot_attack_box;
        self->contact_damage = 5;
        ext->unk8D &= ~4;
    }
    if (!(ext->unk8D & 2)) {
        if (self->animation_step.fields.relative_step == 0) {
            ride_armor_pilot_return_to_idle(self);
            return;
        }
        if (ext->unk86) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 8);
            return;
        }
        if (ext->unk87) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 9);
            return;
        }
        if (ext->unk8A) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 3);
            return;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_80046220(struct MainObj* self)
{
    struct Main5Ext* ext = &self->ext.main_5;
    s32 distance;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    self->unk7C--;
    if (self->unk7C == 0x1E) {
        ext->pad81[0] = ext->pad81[0] == 0;
        self->gravity = -self->gravity;
        self->y_speed = D_800FA130[ext->pad81[0]];
    }
    if (self->unk7C == 0) {
        ext->unk80 = ext->unk80 == 0;
        self->x_speed = 0;
        self->x_accel = -self->x_accel;
        ext->pad81[0] = ext->pad81[0] == 0;
        self->gravity = -self->gravity;
        self->unk7C = 0x3C;
        self->y_speed = D_800FA130[ext->pad81[0]];
    }
    distance = g_Player.x_pos.val - self->x_pos.val;
    if (distance >= -0x6FFFFF && distance <= 0x6FFFFF) {
        set_animation(self, 2);
        self->unk5 = 7;
        self->unk6 = 0;
    }
}

void func_8008CD80(struct MainObj* self)
{
    struct Main73Ext* ext = &self->ext.main_73;
    s32 collision;

    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    double_step_funcs[self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
    collision = func_8002DD04(self);

    if (ext->blink_delay != 0) {
        ext->blink_delay--;
        if (ext->blink_delay == 0)
            self->collision_data = D_80108204;
        if (ext->blink_delay & 1)
            self->unk42 |= 0x8000;
        else
            self->unk42 &= 0x7FFF;
    } else if (collision < 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
        self->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
    } else if (collision > 0 && collision != 0x7F) {
        self->collision_data = D_801060F0;
        ext->blink_delay = 0x40;
        if (collision < 0x13 || collision > 0x17) {
            s32 kind = (get_random() & 1) ? 2 : 3;
            double_spawn_shot(self, kind, 0);
            double_spawn_shot(self, kind, 1);
            for (s8 i = 0; i < 4; i++)
                double_spawn_afterimage(self, i);
        }
    }
    func_8002D9BC(self);
    is_on_screen(BASE_OBJECT(self));
}

void func_8008C10C(struct MainObj* self)
{
    struct Main73Ext* ext = &self->ext.main_73;
    u8* step = &ext->cycle_step;

    if (self->unk7C != 0) {
        self->unk7C--;
        animate_object(ANIMATED_OBJECT(self));
        return;
    }
    if (*step == 0) {
        u32 index = get_random() & 1;
        ext->cycle_script = self->hp < 0x19 ? (u8*)double_script_table_1[index] : double_script_table_0[index];
    }
    (*step)++;
    self->unk5 = ext->cycle_script[*step];
    if (self->unk5 == -1) {
        *step = 0;
        self->unk5 = 2;
    }
    self->unk6 = 0;
    self->unk7 = 0;
}

void func_8008A180(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        set_animation(self, 1);
        ext->unk84 = 0x160;
        ride_armor_pilot_update_facing(self);
        self->hurt_box = ride_armor_pilot_hurt_box;
        self->attack_box = ride_armor_pilot_attack_box;
        self->contact_damage = 5;
        ext->unk8D &= ~0xC;
    }
    if (!(self->collision_flags & 8)) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        return;
    }
    if (!(ext->unk8D & 2)) {
        if (!(u8)ride_armor_pilot_update_facing(self)) {
            ride_armor_pilot_return_to_idle(self);
            return;
        }
        if (ext->unk86) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 8);
            return;
        }
        if (ext->unk87) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 9);
            return;
        }
        ride_armor_pilot_set_walk_speed(self);
        ride_armor_pilot_apply_x_speed(self);
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0)
            func_8001540C(2, 0x3D, self);
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_80062778(struct MainObj* self)
{
    struct Main41Ext* ext = &self->ext.main_41;
    u8 flags;
    u8 direction;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        ext->unk84 = 1;
        ext->unk83 = 0;
        self->x_speed = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->x_accel = 0x2000;
        self->unk15 = (ext->unk80 & 1) ? 0x40 : 0;
        set_animation(self, 0);
        data_hopper_spawn_item(self);
        ext->pad81 = ext->unk80;
    }
    func_80062650(self);
    flags = self->collision_flags;
    if (!(flags & 8)) {
        self->unk5 = 3;
        self->unk6 = 0;
        return;
    }
    direction = self->unk15 ? 1 : 2;
    if (((flags & 3) && (flags & direction)) || ext->unk80 == (self->unk15 ? 2 : 1)) {
        self->unk5 = 2;
        self->unk6 = 0;
        ext->unk82 = self->animation_step.fields.event;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->x_speed > 0x41FFF || self->x_speed < -0x41FFF) {
        if (ext->unk80 == 1)
            self->x_speed = 0x42000;
        else if (ext->unk80 == 2)
            self->x_speed = -0x42000;
        self->x_accel = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    ext->pad81 = ext->unk80;
}

void func_800B08CC(struct VisualObj* self)
{
    s32 kind = self->unk2 % 4;

    self->on_screen = 1;
    self->state++;
    self->x_vel.val = 0;
    self->y_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    if (kind >= 0 && kind < 4) {
        self->x_pos.u.hi += ice_shard_offsets[kind][0] + get_random_nonzero() % 32;
        self->y_pos.u.hi += ice_shard_offsets[kind][1] + get_random_nonzero() % 32;
    }
    set_animation(self, 0xE + get_random_nonzero() % 3);
}

void func_80089588(struct MainObj* self)
{
    u8 start = self->ext.main_70.pad84;

    for (u8 i = 0; i < 2; i++) {
        struct MainObj* child = find_free_main_obj();
        u8 part = D_801049B8[(u8)(start + i)];
        s32 index;
        s32 column;
        s32 row;

        if (child == NULL)
            continue;
        child->active = 0x41;
        child->id = 0x3A;
        if (part == 1 || part == 4)
            child->unk2 = 2;
        else if (part < 6)
            child->unk2 = 1;
        child->unk42 = self->unk42;
        index = func_8002938C(0x3A);
        child->unk40 = D_801406A8[index] >> 7;
        index = func_8002938C(0x3A);
        column = index * 4 + 0x18;
        index = func_8002938C(0x3A);
        row = index + 6;
        child->unk42 = (column - (column / 16) * 16) | (((row / 4 + 0x1E0) << 6) & 0xFFFF);
        index = func_8002938C(0x3A);
        child->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
        child->unk15 = part < 3 ? 0x40 : 0;
        child->unk16 = 5;
        child->bg_offset = self->bg_offset;
        child->x_pos.u.hi = (u16)D_801049CC[part * 2];
        child->y_pos.u.hi = (u16)D_801049CC[part * 2 + 1];
    }
    self->ext.main_70.pad84 = start + 2;
    if (D_801049B8[self->ext.main_70.pad84] == 0xFF)
        self->ext.main_70.pad84 = start - 0xE;
}

void func_800B913C(struct EffectObj* self)
{
    engine_obj.unk10 = 1;
    engine_obj.unk11 = 1;
    engine_obj.unk12 = 1;
    engine_obj.unk13 = 1;
    self->ext.effect_17.phase = 1;
    for (u32 i = 0; i < 4; i++)
        D_8013E188[i] = -1;
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    self->ext.effect_17.timer = 2;
    self->state++;
}

void func_800C52CC(struct ItemObj* self)
{
    s32 index = func_8002938C(0x29);
    s32 column = index * 4 + 0x18;
    s32 row = index + 6;

    self->active |= 0x41;
    self->on_screen = 0;
    self->animation_table = (const u8* const*)data_hopper_animations;
    self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
    self->unk40 = D_801406A8[index] >> 7;
    self->unk42 = (column - (column & 0x7F0)) | (((row / 4 + 0x1E0) << 6) & 0xFFFF);
    self->unk16 = 6;
    self->unk68 = (struct Unk_unk68*)hopper_switch_box;
    self->state = 1;
}

void func_800A9964(struct ShotObj* self)
{
    s32 direction;
    s32 dx;
    s32 dy;

    self->unk16 = 3;
    self->unk5C = 3;
    self->state = 1;
    self->on_screen = 1;
    self->unk54 = double_ball_boxes[0];
    self->unk50.data = double_ball_boxes[0];
    self->unk58.collision_bounds = D_801060F0;
    self->unk5 = 0;
    self->unk6 = 0;
    self->unk7 = 0;
    self->timer = 0;
    self->bg_offset = 0;
    self->unk68 = NULL;
    self->unk60 = 6;
    self->unk61 = 0;
    self->x_pos.u.hi += self->unk15 ? 0x17 : -0x17;
    self->y_pos.u.hi += 0xD;
    set_animation(self, 0xC);
    self->unk8C.halves[0] = g_Player.x_pos.u.hi;
    self->unk8C.halves[1] = g_Player.y_pos.u.hi;
    direction = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    self->unk84.value = direction;
    set_velocity_from_angle(MOVING_OBJECT(self), direction);
    self->unk28 = 0;
    self->unk2C = 0;
    self->x_vel.val *= 4;
    self->y_vel.val *= 4;
    dx = self->x_pos.i.hi - g_Player.x_pos.i.hi;
    dy = self->y_pos.i.hi - g_Player.y_pos.i.hi;
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    self->unk8A = ((dx + dy) / 4) + 1;
}

void func_8005AA14(struct MainObj* self)
{
    switch (self->unk6) {
    case 0:
        set_animation(self, 1);
        self->unk6 = 1;
        break;
    case 1:
        if (self->animation_step.fields.relative_step == 0) {
            set_animation(self, 2);
            self->unk6 = 2;
        }
        break;
    case 2:
        if (self->animation_step.fields.relative_step == 0) {
            struct MainObj* controller = (struct MainObj*)SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.target;
            controller->unk6 = 1;
            self->unk6 = 3;
        }
        break;
    case 4:
        if (self->unk7C == 0) {
            set_animation(self, 4);
            self->unk6 = 5;
        } else {
            self->unk7C--;
        }
        break;
    case 5:
        if (self->animation_step.fields.relative_step == 0)
            self->unk6 = 6;
        break;
    case 6:
        self->unk5 = 2;
        self->unk6 = 0;
        break;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8005AF5C(struct MainObj* self)
{
    struct MainObj* source = self->ext.main_29.source;
    u8* source_ext = (u8*)&source->ext;

    self->x_pos = source->x_pos;
    self->y_pos = source->y_pos;
    self->unk42 = source->unk42;
    animate_object(ANIMATED_OBJECT(self));

    switch (self->unk6) {
    case 0:
        self->unk7C = 0;
        self->ext.main_29.unk96 = D_800FD89C[get_random() & 0xF];
        break;
    case 1: {
        u16 count = self->ext.main_29.unk96;
        u16* spawned = &self->ext.main_29.unk94;
        if (count != 0) {
            for (u32 i = 0; i < count; i++) {
                struct MainObj* slot = self->ext.main_29.slots.children[i];
                if (slot == NULL && self->unk7C == 0) {
                    struct MainObj* child = find_free_main_obj();
                    if (child != NULL) {
                        s32 index;
                        s32 column;
                        s32 row;
                        self->ext.main_29.slots.children[i] = child;
                        child->id = 0x1C;
                        child->state = 0;
                        child->unk5 = 0;
                        child->unk6 = 0;
                        child->active = self->active;
                        child->unk2 = ((u8*)source->ext.main_29.slots.controller.record)[2];
                        child->x_pos = self->x_pos;
                        child->y_pos = self->y_pos;
                        index = func_8002938C(child->id);
                        child->unk40 = D_801406A8[index] >> 7;
                        index = func_8002938C(child->id);
                        column = index * 4 + 0x18;
                        row = index + 6;
                        child->unk42 = (column - (column / 16) * 16) | (((row / 4 + 0x1E0) << 6) & 0xFFFF);
                        index = func_8002938C(child->id);
                        child->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
                        self->unk7C = 1;
                        child->ext.main_28.context = self;
                        child->ext.main_28.index = i;
                        (*spawned)++;
                    }
                }
                if (*spawned >= count) {
                    self->unk6 = 2;
                    break;
                }
            }
        }
        break;
    }
    case 2:
        self->unk6 = 3;
        source->unk6 = 4;
        source->unk7C = 0x1E;
        break;
    case 3:
        if (self->ext.main_29.unk94 == 0) {
            self->unk6 = 4;
            self->unk7C = 0x78;
            if (source->ext.main_29.slots.controller.record != NULL && source->ext.main_29.slots.controller.record->unk0 != 0) {
                source->ext.main_29.slots.controller.record->unk4 = 2;
                source_ext[1] |= 2;
            }
        }
        break;
    case 4:
        if (self->unk7C == 0) {
            self->unk6 = 0;
            source_ext[1] = 0;
        } else {
            self->unk7C--;
        }
        break;
    }
    update_on_screen(BASE_OBJECT(self), 0x68, 0x68);
}

void func_800615CC(struct MainObj* self)
{
    static const u16 top[6] = { 0xB20, 0xC20, 0xD20, 0xE20, 0xEA0, 0xF20 };
    static const u16 left[6] = { 0xB60, 0xC60, 0xD60, 0xE60, 0xEE0, 0xF60 };
    static const u16 center[6] = { 0xB70, 0xBF0, 0xCE0, 0xDD0, 0xE50, 0xEB0 };
    u8* ext = (u8*)&self->ext;

    self->contact_damage = 0x14;
    self->hp = 6;
    self->invincibility_timer = 0;
    self->collision_data = D_801060F0;
    self->animation_table = (const u8* const*)falling_ceiling_animations;
    self->terrain_box = (struct Unk_unk68*)D_800FE94C;
    self->hurt_box = D_800FE944;
    self->attack_box = D_800FE948;
    self->air_state = 0;
    self->unk16 = 6;
    self->unk15 = 0;
    self->bg_offset = g_Player.bg_offset;
    set_animation(self, 0);

    if ((u8)self->unk2 < 12) {
        u8 group = (u8)self->unk2 >> 1;
        *(u16*)(ext + 2) = top[group];
        if (!(self->unk2 & 1)) {
            *(u16*)(ext + 0) = left[group];
            *(u16*)(ext + 6) = group < 4 ? 0x188 : 0x180;
        }
        self->x_pos.val = (u32)(top[group] + ((self->unk2 & 1) ? 0x70 : 0x10)) << 16;
        *(u16*)(ext + 4) = center[group];
    }
    *(u32*)(ext + 0xC) = 0x1200000;
    self->y_pos.val = 0x1100000;
    ext[8] = 0;
    *(u32*)(ext + 0x10) = 0;
    ext[0x14] = 1;
    self->unk7E = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0x2000;
    self->state = 1;
    self->unk5 = 0;
    self->unk6 = 0;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
}

void func_8004AE20(struct MainObj* self)
{
    struct MainObj* owner = SP_CUR_MAIN_OBJ;
    u8 flags = owner->ext.main_11.unk80;

    if (flags & 0x10) {
        wall_crawler_update_surface(self);
        flags = owner->ext.main_11.unk80;
        switch (flags) {
        case 1:
            self->x_speed = -0x18000;
            self->y_speed = 0;
            if (self->unk15 == 0) {
                set_animation(self, 0);
                break;
            }
            self->unk5 = 3;
            set_animation(self, 2);
            break;
        case 2:
            self->x_speed = 0x18000;
            self->y_speed = 0;
            if (self->unk15 == 0x40) {
                set_animation(self, 0);
                break;
            }
            self->unk5 = 3;
            set_animation(self, 2);
            break;
        case 4:
            self->x_speed = 0;
            self->y_speed = 0x18000;
            set_animation(self, 1);
            break;
        case 8:
            self->x_speed = 0;
            self->y_speed = -0x18000;
            set_animation(self, 1);
            break;
        }
    } else if (self->unk2 == 0) {
        if ((flags == 1 && (self->collision_flags & 2)) || (flags == 2 && (self->collision_flags & 1)) || (flags == 4 && (self->collision_flags & 4)) || (flags == 8 && (self->collision_flags & 8))) {
            owner->ext.main_11.unk80 = flags | 0x10;
        }
    } else {
        s32 distance = self->unk15 ? self->x_pos.i.hi - g_Player.x_pos.i.hi
                                   : g_Player.x_pos.i.hi - self->x_pos.i.hi;
        if (distance >= 0x20) {
            set_animation(self, 2);
            self->unk5 = 3;
        }
    }
    move_object(MOVING_OBJECT(self));
}

void func_8004A78C(struct MainObj* self)
{
    u16 x;

    self->contact_damage = 3;
    self->invincibility_timer = 0;
    self->bg_offset = g_Player.bg_offset;
    self->animation_table = (const u8* const*)wall_crawler_animations;
    self->unk16 = 6;
    self->collision_data = D_801067F0;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->attack_box = &wall_crawler_terrain_box;
    if (self->unk2 == 2) {
        self->hp = 5;
        set_animation(self, 0x17);
        self->terrain_box = &D_800FB568;
        self->unk5 = 7;
        self->unk6 = 0;
        self->hurt_box = NULL;
        self->state++;
        self->x_pos.u.hi = (self->x_pos.u.hi & -0x10) + 8;
        self->y_pos.u.hi = (self->y_pos.u.hi & -0x10) + 0x14;
        return;
    }

    self->hurt_box = &wall_crawler_terrain_box;
    if (g_Player.x_pos.val < self->x_pos.val) {
        self->unk15 = 0;
        SP_CUR_MAIN_OBJ->ext.main_11.unk80 = 1;
        self->x_speed = -0x18000;
    } else {
        self->unk15 = 0x40;
        SP_CUR_MAIN_OBJ->ext.main_11.unk80 = 2;
        self->x_speed = 0x18000;
    }
    move_object(MOVING_OBJECT(self));
    x = self->x_pos.u.hi;
    if (engine_obj.character_state.fields.active != 0 && ((u32)(x - 0xC0F) < 0x1E2 || (u32)(x - 0x100F) < 0x1E2 || (u32)(x - 0x1315) < 0x1DC || (u32)(x - 0x1613) < 0x1BF)) {
        set_animation(self, 0x16);
        self->state = 2;
        self->hp = 1;
        self->gravity = 0x8000;
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->terrain_box = &D_800FB56C;
        return;
    }
    if (engine_obj.character_state.fields.active == 0) {
        self->hp = 5;
        set_animation(self, 0);
        self->terrain_box = &D_800FB568;
        self->state++;
    }
    self->unk5 = 2;
    self->unk6 = 0;
    *(u16*)((u8*)&SP_CUR_MAIN_OBJ->ext + 2) = self->unk2 == 0 ? 0x3C : 0xB4;
}

void func_8004A9F4(struct MainObj* self)
{
    u16* timer = (u16*)((u8*)&SP_CUR_MAIN_OBJ->ext + 2);

    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    if (engine_obj.character_state.fields.active != 0) {
        set_animation(self, 0x16);
        self->hp = 1;
        self->gravity = 0x8000;
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->terrain_box = &D_800FB56C;
        self->state++;
        return;
    }
    if (self->unk2 == 0 && self->unk5 == 2) {
        --*timer;
        if (*timer == 0)
            self->unk5 = 4;
    }
    SP_CUR_MAIN_OBJ->ext.main_11.saved_unk5 = self->unk5;
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(5, wall_crawler_debris, self);
        drop_item(BASE_OBJECT(self), 7);
        self->state = 4;
        return;
    }
    wall_crawler_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B160(BASE_OBJECT(self)) != 0) {
        self->state = 4;
    } else {
        animate_object(ANIMATED_OBJECT(self));
        is_on_screen(BASE_OBJECT(self));
    }
}

void func_8005A758(struct MainObj* self)
{
    u8* context = (u8*)&SP_CUR_MAIN_OBJ->ext;
    u8 direction;
    u8 result;
    s32 dx;
    s32 dy;

    if ((main_bss_state.frame_counter & 3) == 0) {
        context[0]++;
        if (context[0] >= 12)
            context[0] = 0;
        *(s16*)(context + 6) = D_800FD86C[context[0]];
        *(s16*)(context + 8) = D_800FD884[context[0]];
        self->x_pos.u.hi = *(u16*)(context + 2) + *(u16*)(context + 6);
        self->y_pos.u.hi = *(u16*)(context + 4) + *(u16*)(context + 8);
    }

    if (context[1] == 0) {
        dx = g_Player.x_pos.i.hi - self->x_pos.i.hi;
        dy = g_Player.y_pos.i.hi - self->y_pos.i.hi;
        if (dx > -0x81 && dx < 0x81 && dy > -0x41 && dy < 0x41) {
            direction = pod_spawner_player_quadrant(self);
            if (self->unk2 == 0) {
                func_8005ABC0(self, direction);
            } else if (self->unk2 == 1) {
                if (direction < 2) {
                    result = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
                    if ((direction == 0 && result < 0x10) || (direction == 1 && result < 5))
                        direction = 2;
                    else
                        direction = 3;
                }
                func_8005ABC0(self, direction);
            } else if (self->unk2 == 2) {
                if (direction >= 2) {
                    result = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
                    if ((direction == 2 && result < 8) || (direction != 2 && result < 0x18))
                        direction = 1;
                    else
                        direction = 0;
                }
                func_8005ABC0(self, direction);
            }
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8005ABC0(struct MainObj* self, u8 direction)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot == NULL)
        return;
    shot->id = 0x10;
    shot->unk2 = direction;
    shot->active = self->active;
    shot->x_pos = self->x_pos;
    shot->y_pos = self->y_pos;
    shot->animation_table = (u32**)self->animation_table;
    __builtin_memcpy(&shot->unk38, &self->animation_speed, sizeof(u32));
    shot->unk3C = (void*)self->sprite_frames;
    shot->unk40 = self->unk40;
    shot->unk42 = self->unk42 & 0x7FFF;
    shot->unk16 = self->unk16;
    shot->unk7C = (struct WeaponObj*)self;
    ((u8*)&SP_CUR_MAIN_OBJ->ext)[1] = 1;
    SP_CUR_MAIN_OBJ->ext.main_29.slots.controller.record = (struct Main29Record*)shot;
    self->unk5 = 3;
}

void func_8004AD18(struct MainObj* self)
{
    if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi, self->y_pos.i.hi) != 0)
        return;
    set_animation(self, 0);
    if (g_Player.x_pos.val < self->x_pos.val) {
        self->unk15 = 0;
        SP_CUR_MAIN_OBJ->ext.main_11.unk80 = 1;
        self->x_speed = -0x18000;
    } else {
        self->unk15 = 0x40;
        SP_CUR_MAIN_OBJ->ext.main_11.unk80 = 2;
        self->x_speed = 0x18000;
    }
    move_object(MOVING_OBJECT(self));
    self->unk2 = 0;
    self->unk5 = 2;
    *(u16*)((u8*)&SP_CUR_MAIN_OBJ->ext + 2) = 0x3C;
    self->hurt_box = &wall_crawler_terrain_box;
}

void func_800C4D20(struct ItemObj* self)
{
    s32 index;
    s32 column;
    s32 row;

    self->active = 0x41;
    self->unk16 = 6;
    index = func_8002938C(0x9C);
    self->unk40 = D_801406A8[index] >> 7;
    index = func_8002938C(0x9C);
    self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
    column = func_8002938C(0x9C);
    row = func_8002938C(0x9C);
    self->unk42 = ((column * 4 + 0x18) & 0xF) | (((row + 6) / 4 + 0x1E0) << 6);
    self->animation_step.fields.frame_index = self->unk2 & 7;
    self->unk15 = (self->unk2 & 8) ? 0x40 : 0;
    self->unk68 = (struct Unk_unk68*)gravity_switch_terrain_box;
    self->unk54 = gravity_switch_hit_box;
    self->unk50 = gravity_switch_hit_box;
    self->unk58 = NULL;
    self->unk61 = 0;
    self->unk75 = 0;
    self->unk67 = 0;
    self->state = 1;
    self->unk5 = 0;
    self->bg_offset = g_Player.bg_offset;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
}

void func_800D9268(struct LayerObj* self)
{
    self->unk18.val = 0x80000;
    self->unk16 = 0x78;
    self->unk17 = 1;
    self->private_state.signed_byte = -1;
    ((u8*)&self->private_state)[1] = 0;
    self->unk5 = 2;
    self->bg_offset = 5;
    self->state++;
    background_objects[1].unk4E = 0xD;
    background_objects[0].unk2E = 0xA0;
    background_objects[1].unk4D = 2;
    background_objects[2].unk4D = 2;
    background_objects[2].unk4E = 5;
    engine_obj.character_state.fields.flags = 0;
    engine_obj.character_state.fields.active = 0;
    background_objects[0].unk2C = 0x30;
    func_8001540C(5, 9, NULL);
    train_tunnel_main(self);
}

void func_800D9B48(struct LayerObj* self)
{
    u8* private_bytes = (u8*)&self->private_state;
    s16 value;

    if (engine_obj.character_state.fields.flags == 0)
        return;
    if (private_bytes[1] == 0)
        private_bytes[1] = 2;
    if (private_bytes[1] == 0xFF)
        return;
    if (private_bytes[1] == 2) {
        if (get_layout_screen(1, 0x14F, 0x80) == 0x1D)
            return;
        if (get_layout_screen(1, 0x14F, 0x80) == 0x18)
            return;
        private_bytes[2] = get_layout_screen(1, 0x14F, 0x80);
        private_bytes[1]--;
        return;
    }
    value = get_layout_screen(1, 0x14F, 0x80);
    if (private_bytes[2] == value)
        return;
    background_objects[1].unk4E++;
    if (background_objects[1].unk4E == 0x1D)
        private_bytes[1] = 0xFF;
    background_objects[1].unk4D++;
    private_bytes[2] = get_layout_screen(1, 0x14F, 0x80);
}

void func_8008329C(struct MainObj* self)
{
    struct ShotObj* shot;

    self->on_screen = 0;
    if (self->ext.main_68.effect->active != 0)
        return;
    self->contact_damage = 4;
    self->hurt_box = NULL;
    self->attack_box = NULL;
    self->terrain_box = NULL;
    self->collision_data = D_80107F84;
    self->unk16 = 6;
    self->animation_table = (const u8* const*)sigma_animations;
    self->unk63 = 2;
    self->x_pos.val = 0x5200000;
    self->y_pos.val = 0x16B0000;
    self->unk7C = 1;
    self->hp = 0;
    self->unk62 = 0;
    self->unk7E = 0x3C;
    self->ext.main_68.next_attack = 0;
    self->bg_offset = g_Player.bg_offset;

    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x2E;
        shot->unk2 = 0;
        shot->on_screen = 0;
        shot->unk7C = (struct WeaponObj*)self;
        self->ext.main_68.scythe = (struct MainObj*)shot;
    }
    engine_obj.enable_boss = 1;
    engine_obj.unk25 = 0;
    engine_obj.boss_ptr = self;
    set_animation(self, 0);
    func_8001540C(2, 3, self);
    self->unk5++;
    play_boss_voice(0xC);
    colonel_spawn_afterimages(self);
}

void func_8008A4D8(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        ext->unk84 = 0x160;
        self->air_state = 0;
        set_animation(self, 4);
        self->hurt_box = ride_armor_pilot_hurt_box;
        self->attack_box = ride_armor_pilot_attack_box;
        ext->unk86 = 0;
        self->contact_damage = 5;
        self->collision_flags |= 8;
        func_8001540C(2, 0x3D, self);
    }
    if (self->animation_step.fields.relative_step == 0) {
        ride_armor_pilot_return_to_idle(self);
        return;
    }
    if (!(ext->unk8D & 2)) {
        if (!(self->collision_flags & 8))
            ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        else if (ext->unk87)
            ride_armor_pilot_set_step(BASE_OBJECT(self), 9);
        else if (ride_armor_pilot_update_facing(self)) {
            ride_armor_pilot_set_walk_speed(self);
            ride_armor_pilot_apply_x_speed(self);
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8004B514(struct MainObj* self)
{
    struct MainObj* current;
    struct ShotObj* shot;

    if (self->animation_step.fields.event == 1) {
        current = SP_CUR_MAIN_OBJ;
        if ((s8)current->ext.main_11.pad81[4] == 3) {
            current->ext.main_11.pad81[5] = 0x20;
            self->unk6++;
        } else if ((s8)--current->ext.main_11.pad81[5] <= 0) {
            current->ext.main_11.pad81[5] = 0x20;
            self->unk6--;
        }
    }
    if (self->animation_step.fields.event != 2)
        return;
    shot = find_free_shot_obj();
    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 6;
    shot->x_pos = self->x_pos;
    shot->y_pos = self->y_pos;
    shot->unk40 = self->unk40;
    shot->unk42 = self->unk42;
    shot->animation_table = (u32**)self->animation_table;
    shot->unk3C = (void*)self->sprite_frames;
    shot->unk15 = self->unk15;
    shot->bg_offset = self->bg_offset;
    shot->unk2 = SP_CUR_MAIN_OBJ->ext.main_11.pad81[3];
    set_velocity_from_angle(MOVING_OBJECT(shot), SP_CUR_MAIN_OBJ->ext.main_11.pad81[3]);
}

void func_800A3A4C(struct ShotObj* self)
{
    struct WeaponObj* owner = self->unk7C;
    s32 distance;
    s32 camera_x = background_objects[0].x_pos.i.hi;

    animate_object(ANIMATED_OBJECT(self));
    if ((u32)(self->unk84.value - 0x1A) < 0x4A)
        func_8002D9BC((struct MainObj*)self);
    if (self->unk84.value == 0x46)
        self->unk50.frames = self->unk2 ? drone_beam_boxes[1] : drone_beam_boxes[0];
    if (self->unk84.value == 0x19)
        set_animation(self, self->unk2 ? 6 : 5);

    distance = abs(camera_x - owner->x_pos.i.hi);
    if ((u16)distance >= 0x180) {
        if (self->unk2) {
            if (self->unk15 == 0)
                self->x_pos.i.hi = owner->x_pos.u.hi - distance - 0x10;
            else
                self->x_pos.i.hi = owner->x_pos.u.hi + distance + 0x10;
        } else {
            if (self->unk15 == 0)
                self->x_pos.i.hi = owner->x_pos.u.hi - (distance - 0xF0);
            else
                self->x_pos.i.hi = owner->x_pos.u.hi + (distance - 0xF0);
        }
    }
    self->unk84.value--;
    if (self->unk84.value == 0 || owner->active == 0 || owner->state >= 2)
        self->state++;
    distance = abs(camera_x - (owner->x_pos.i.hi - 0xA0));
    update_on_screen(BASE_OBJECT(self), (u16)distance, 0x20);
}

void func_8005B8D0(struct MainObj* self)
{
    s32 variant = ((s8)self->unk2 >> 1) % 3;

    self->unk5 = 2;
    self->active |= 4;
    self->state++;
    self->bg_offset = g_Player.bg_offset;
    if (!(self->unk2 & 1)) {
        self->x_pos.val = background_objects[0].x_pos.val - 0x6C0000;
        self->unk15 = 0;
    } else {
        self->x_pos.val = background_objects[0].x_pos.val + 0x1AC0000;
        self->unk15 = 0x40;
    }
    self->animation_table = (const u8* const*)thorn_trap_animations;
    self->unk16 = 0x21;
    self->attack_box = thorn_trap_attack_box;
    self->hp = 6;
    self->contact_damage = 6;
    self->terrain_box = NULL;
    self->hurt_box = NULL;
    self->invincibility_timer = 0;
    self->unk62 = 0;
    self->air_state = 0;
    self->unk7C = 0x96;
    ((u8*)&self->ext)[2] = 0;
    *(s16*)&self->ext = variant == 0 ? 0x60 : variant == 1 ? 0x80
                                                           : 0xB0;
    set_animation(self, 1);
    update_on_screen(BASE_OBJECT(self), 0x70, 0x30);
}

void func_800C49BC(struct ItemObj* self)
{
    u16* second_timer = (u16*)&self->unk7C;
    struct MainObj* spawned;
    s32 index;
    s16 right_edge;

    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    if (engine_obj.character_state.fields.active != self->unk7)
        self->unk7C.timer16 = 0x1E;

    if (self->unk2 == 0) {
        if (self->unk7C.timer16 != 0) {
            self->unk7C.timer16--;
        } else if (self->animation_step.fields.relative_step != 0) {
            animate_object(ANIMATED_OBJECT(self));
        } else {
            right_edge = (s16)(background_objects[(u8)self->bg_offset].y_pos.u.hi + 0xF0);
            if (self->y_pos.i.hi < right_edge) {
                self->unk7C.timer16 = 0x1E;
                spawned = find_free_main_obj();
                if (spawned != NULL) {
                    spawned->active = 0x41;
                    spawned->id = 0x29;
                    spawned->unk2 = 1;
                    index = (u8)func_8002938C(0x29);
                    spawned->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
                    spawned->unk40 = D_801406A8[index] >> 7;
                    spawned->unk42 = ((index * 4 + 0x18) & 0xF) | (((index + 6) / 4 + 0x1E0) << 6);
                    spawned->x_pos = self->x_pos;
                    spawned->y_pos.val = self->y_pos.val + 0x280000;
                    spawned->unk15 = 0;
                    set_animation(self, self->unk2 + 0xF);
                    if (self->on_screen)
                        func_8001540C(2, 0xEA, spawned);
                }
            }
        }
    } else if (second_timer[1] != 0) {
        if (self->animation_step.fields.relative_step != 0) {
            animate_object(ANIMATED_OBJECT(self));
        } else {
            second_timer[1] = 0;
            set_animation(self, self->unk2 + 0xF);
        }
    }
    self->unk7 = engine_obj.character_state.fields.active;
    collide_with_players(self);
    is_on_screen(BASE_OBJECT(self));
}

void func_800BE9E8(struct ItemObj* self)
{
    s32 column;
    s32 row;
    s32 index;

    self->unk16 = 6;
    self->on_screen = 0;
    self->unk5C = 1;
    self->unk61 = 0;
    self->animation_table = (const u8* const*)falling_rock_d_animations;
    column = func_8002938C(0x9A);
    row = func_8002938C(0x9A);
    self->unk42 = ((column * 4 + 0x18) & 0xF) | (((row + 6) / 4 + 0x1E0) << 6);
    index = func_8002938C(0x9A);
    self->unk40 = D_801406A8[index] >> 7;
    index = func_8002938C(0x9A);
    self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
    self->unk54 = breakable_wall_hit_box;
    self->unk50 = NULL;
    self->unk68 = NULL;
    self->unk58 = (const u8*)D_80108684;
    self->x_vel.val = 0;
    self->y_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->state = 1;
}

void func_80080700(struct MainObj* self)
{
    struct Main66Ext* ext = &self->ext.main_66;
    s32 index;

    if (engine_obj.cur_character == 0) {
        despawn_object_permanently(OBJECT_HEADER(self));
        return;
    }
    self->contact_damage = 4;
    self->collision_data = D_80107DFC;
    self->hp = 0;
    self->invincibility_timer = 0;
    index = func_8002938C(0x42);
    self->unk40 = D_801406A8[index] >> 7;
    self->unk1C = self->y_pos;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->unk2 = 0;
    self->unk15 = 0;
    self->unk18 = self->x_pos;
    self->animation_table = (const u8* const*)iris_animations;
    self->unk16 = 6;
    self->terrain_box = &D_801035CC;
    self->hurt_box = &D_801035C0;
    self->attack_box = &D_801035BC;
    self->bg_offset = g_Player.bg_offset;
    set_animation(self, 9);
    ext->hover_timer = 0xF0;
    ext->release_countdown = 8;
    self->state = 1;
    ext->drone_count = 0;
    ext->crystal_released = 0;
    ext->flash_timer = 0;
    ext->blink_timer = 0;
    ext->active = 0;
    self->unk5 = 2;
    self->unk6 = 0;
}

void func_8008A778(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;

    if (self->unk6 == 0) {
        ride_armor_pilot_update_facing(self);
        self->unk6 = 1;
        ext->unk84 = 0x420;
        self->x_speed = self->unk15 ? 0x42000 : -0x42000;
        ext->unk8E = 0x1E;
        ride_armor_pilot_spawn_dust((struct VisualObj*)self, 5);
        set_animation(self, 5);
        func_8001540C(2, 0x3F, self);
        ext->unk8D |= 4;
    }
    if (!(ext->unk8D & 2)) {
        if (ext->unk86) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 8);
        } else if (ext->unk87) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 0xB);
        } else if (!(self->collision_flags & 8)) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        } else if (!(self->collision_flags & 3)) {
            ride_armor_pilot_apply_x_speed(self);
            s8 old_timer = ext->unk8E;
            ext->unk8E--;
            if (old_timer < 0) {
                ride_armor_pilot_set_step(BASE_OBJECT(self), 7);
                return;
            }
        } else {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 7);
            return;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_80062AEC(struct MainObj* self)
{
    for (s32 i = 0; i < 0x20; i++) {
        struct ItemObj* item = &item_objects[i];
        if (item->active == 0 || item->id != 0x13 || (u8)(item->unk2 - 1) >= 3)
            continue;
        if (func_8002C160(COLLISION_OBJECT(self), COLLISION_OBJECT(item)) == 0)
            continue;
        self->unk5 = 7;
        self->unk6 = 0;
        ((u16*)&item->unk7C)[1] = 1;
        return;
    }
}

void func_80062BBC(struct MainObj* self)
{
    struct Main41Ext* ext = &self->ext.main_41;
    s32 status = 0;

    self->unk1C = self->y_pos;
    self->unk18 = self->x_pos;
    self->on_screen = 0;
    if (self->unk5 != 7)
        func_80062AEC(self);
    ((void (*)(struct MainObj*))data_hopper_step_funcs[self->unk5])(self);
    CollisionRelated(PLAYER_OBJECT(self));
    if (ext->unk84 != 0) {
        func_8002D9BC(self);
        status = func_8002DD04(self);
    }
    if (ext->unk83 != 0) {
        self->unk76 = -1;
        self->unk75 = 1;
        collide_with_players(PLAYER_OBJECT(self));
    } else {
        self->unk76 = 0;
        self->unk75 = 0;
    }
    if (status < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, &data_hopper_hurt_box, self);
        self->state = 2;
        return;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        self->unk7E = 0xF0;
    } else if (self->unk2 != 0) {
        if (self->unk7E == 0)
            self->state = 2;
        else
            self->unk7E--;
    }
}

void func_8008A3B0(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->gravity = 0x4200;
        self->y_speed = 0x58000;
        self->x_speed = 0;
        self->x_accel = 0;
        self->air_state = 1;
        set_animation(self, 2);
        ride_armor_pilot_stub(self, 2, 0);
        self->collision_flags &= ~8;
        ride_armor_pilot_spawn_dust((struct VisualObj*)self, 6);
        self->attack_box = &ride_armor_pilot_punch_box;
        self->contact_damage = 6;
        func_8001540C(2, 0x40, self);
    }
    if (ext->unk87) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 0xA);
        return;
    }
    if (ext->unk8D & 2)
        return;
    self->x_speed = 0;
    ride_armor_pilot_set_jump_speed(self);
    if (!(self->collision_flags & 4)) {
        if (self->y_speed >= 0) {
            move_with_gravity(MOVING_OBJECT(self));
            return;
        }
    }
    ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
}

void func_8008BA38(struct MainObj* self)
{
    struct Main73Ext* ext = &self->ext.main_73;
    s32 index;

    if (engine_obj.cur_character != 0) {
        despawn_object_permanently(OBJECT_HEADER(self));
        return;
    }
    self->unk5 = 1;
    self->unk7C = 0x80;
    self->contact_damage = 6;
    self->hurt_box = &double_hurt_box;
    self->attack_box = &double_attack_box;
    self->terrain_box = &double_terrain_box;
    self->collision_data = D_80108204;
    self->state = 0;
    self->unk6 = 0;
    self->unk7 = 0;
    self->on_screen = 0;
    self->hp = 0;
    self->invincibility_timer = 0;
    self->animation_table = (const u8* const*)double_animations;
    self->air_state = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk16 = 4;
    ext->blink_delay = 0;
    ext->pad8A = 0;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    self->bg_offset = g_Player.bg_offset;
    index = func_8002938C(0x49);
    self->unk40 = D_801406A8[index] >> 7;
    set_animation(self, 0);
}

void func_8005C0E4(struct MainObj* self)
{
    struct Unk_unk68* saved_bounds;
    u8* ext = (u8*)&self->ext;
    s16 x;
    s16 y;
    s32 direction;

    self->collision_data = D_801071F4;
    self->unk65 = ext[3];
    if (func_8002DD04(self) < 0) {
        self->unk5 = 0;
        self->state++;
        self->unk42 &= 0x7FFF;
        update_on_screen(BASE_OBJECT(self), 0x70, 0x30);
        return;
    }
    ext[3] = self->unk65;
    saved_bounds = (struct Unk_unk68*)self->hurt_box;
    self->collision_data = D_801060F0;
    self->hurt_box = D_800FDA0C;
    self->unk65 = ext[4];
    func_8002DD04(self);
    ext[4] = self->unk65;
    self->hurt_box = saved_bounds;
    ((void (*)(struct MainObj*))thorn_trap_step_funcs[self->unk5])(self);

    if (self->y_pos.val - background_objects[(u8)self->bg_offset].y_pos.val > 0xA80000) {
        self->state++;
        self->unk5 = 0;
        x = self->x_pos.i.hi;
        y = self->y_pos.i.hi;
        direction = self->unk15 != 0 ? -1 : 1;
        spawn_explosion_at(0, x + direction * 0x47, (s16)((u16)y + 1), 0);
        spawn_explosion_at(0, x + direction * 0x28, y, 1);
        spawn_explosion_at(0, x + direction * 0xC, (s16)((u16)y - 1), 0xFF);
        spawn_explosion_at(0, x - direction * 0x15, (s16)((u16)y + 2), 0xFF);
        spawn_explosion_at(0, x - direction * 0x33, (s16)((u16)y - 1), 0xFF);
        spawn_explosion_at(0, x - direction * 0x50, y, 0xFF);
        spawn_debris_offset(5, D_800FDC28, (struct MiscObj*)self,
            direction * 0x470000, 0x10000);
        spawn_debris_offset(1, D_800FDC30, (struct MiscObj*)self,
            direction * 0x280000, 0);
        spawn_debris_offset(1, D_800FDC34, (struct MiscObj*)self,
            direction * 0xC0000, -0x10000);
        spawn_debris_offset(1, D_800FDC38, (struct MiscObj*)self,
            -direction * 0x150000, 0x20000);
        spawn_debris_offset(1, D_800FDC3C, (struct MiscObj*)self,
            -direction * 0x330000, -0x10000);
    }
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0)
        update_on_screen(BASE_OBJECT(self), 0x70, 0x30);
    else
        despawn_object(OBJECT_HEADER(self));
}

void func_800C20F4(struct ItemObj* self)
{
    s32 index;
    s32 column;
    s32 row;

    self->active = 0x41;
    self->state++;
    self->bg_offset = g_Player.bg_offset;
    index = func_8002938C(0xA1);
    self->unk40 = D_801406A8[index] >> 7;
    index = func_8002938C(0xA1);
    self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, index);
    column = func_8002938C(0xA1);
    row = func_8002938C(0xA1);
    self->unk42 = ((column * 4 + 0x18) & 0xF) | (((row + 6) / 4 + 0x1E0) << 6);
    self->unk16 = 6;
    self->animation_step.fields.frame_index = 0;
    self->unk5C = 0;
    self->unk61 = 0;
    self->unk54 = NULL;
    self->unk68 = (struct Unk_unk68*)(moving_block_terrain_box + 4 * self->unk2);
    self->x_vel.val = moving_block_motion[self->unk2].x_velocity;
    self->y_vel.val = moving_block_motion[self->unk2].y_velocity;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk7C.timer16 = self->x_pos.u.hi;
    ((u16*)&self->unk7C)[1] = self->y_pos.u.hi;
    if (g_Player.x_pos.val < self->x_pos.val)
        self->x_vel.val = -self->x_vel.val;
    self->unk75 = 0;
    self->unk76 = 0;
}

void func_80059F60(struct MainObj* self)
{
    struct Main28Ext* ext = &self->ext.main_28;
    struct ShotObj* shot;
    s32 turn = 0;

    switch (self->unk2) {
    case 0:
        turn = (self->x_speed <= -0x500000 && self->unk15 == 0) || (self->x_speed >= -0x10000 && self->unk15 != 0);
        break;
    case 1:
        turn = (self->x_speed > 0x4FFFFF && self->unk15 != 0) || (self->x_speed <= 0x10000 && self->unk15 == 0);
        break;
    case 2:
        turn = (self->y_speed <= -0x500000 && self->unk15 == 0) || (self->y_speed >= -0x10000 && self->unk15 != 0);
        break;
    case 3:
        turn = (self->y_speed > 0x4FFFFF && self->unk15 != 0) || (self->y_speed <= 0x10000 && self->unk15 == 0);
        break;
    }
    if (self->unk7E != 0)
        self->unk7E--;

    switch ((u8)self->unk6) {
    case 0:
        if (self->unk7E == 0 || turn) {
            ext->unk85++;
            self->unk6 = 1;
            self->unk7C = 0x3C;
        } else {
            self->x_speed += self->x_accel;
            self->y_speed += self->gravity;
            animate_object(ANIMATED_OBJECT(self));
        }
        break;
    case 1:
        if (ext->unk85 >= 4) {
            ext->unk85 = 0;
            set_animation(self, ext->unk84 + 2);
            self->unk6 = 2;
            break;
        }
        self->unk15 ^= 0x40;
        if (self->unk2 >= 2) {
            ext->unk84 ^= 8;
            set_animation(self, ext->unk84 + 1);
        }
        self->unk7C = 0x20;
        self->unk6 = 4;
        self->x_accel = -self->x_accel;
        self->gravity = -self->gravity;
        self->unk7E = 0;
        break;
    case 2:
        if (self->animation_step.fields.relative_step == 0) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x12;
                shot->x_pos.val = self->x_pos.val + self->x_speed;
                shot->y_pos.val = self->y_pos.val + self->y_speed;
                shot->animation_table = (u32**)self->animation_table;
                shot->unk40 = self->unk40;
                shot->unk3C = (void*)self->sprite_frames;
                shot->unk42 = self->unk42 & 0x7FFF;
                shot->unk7C = (struct WeaponObj*)self;
                shot->unk16 = self->unk16;
                shot->unk15 = self->unk15;
            }
            self->unk7C = 0x10;
            self->unk6 = 3;
        }
        animate_object(ANIMATED_OBJECT(self));
        break;
    case 3:
        if (self->unk7C != 0) {
            self->unk7C--;
            break;
        }
        self->unk15 ^= 0x40;
        if (self->unk2 >= 2)
            ext->unk84 ^= 8;
        self->x_accel = -self->x_accel;
        self->gravity = -self->gravity;
        self->unk6 = 0;
        self->unk7C = 0;
        self->unk7E = D_800FD5C8[get_random() & 0x1F];
        set_animation(self, ext->unk84 + 1);
        break;
    case 4:
        if (self->unk7C != 0) {
            self->unk7C--;
            break;
        }
        self->unk7C = 0;
        self->unk7E = D_800FD5C8[get_random() & 0x1F];
        self->unk6 = 0;
        break;
    }
    self->x_pos.val += self->x_speed;
    self->y_pos.val += self->y_speed;
}

void func_8005BA2C(struct MainObj* self)
{
    u8* ext = (u8*)&self->ext;
    s16* distance = (s16*)ext;
    s32 step;

    if (self->unk7C != 0) {
        self->unk7C--;
        return;
    }
    if (*distance < 0) {
        if (self->unk2 < 6) {
            self->unk5 = 4;
            set_animation(self, 2);
        } else if (self->unk2 < 0xC) {
            if (ext[2] != 0) {
                self->unk5 = 7;
                set_animation(self, 7);
            } else {
                self->unk5 = 6;
                set_animation(self, 3);
            }
        } else if (ext[2] != 0) {
            self->unk5 = 9;
            set_animation(self, 4);
        } else {
            self->unk5 = 8;
            set_animation(self, 3);
        }
        return;
    }
    step = *distance < 9 ? *distance : 8;
    self->x_pos.i.hi += self->unk15 ? -step : step;
    *distance = (u16)*distance - 8;
    animate_object(ANIMATED_OBJECT(self));
}

void func_80062650(struct MainObj* self)
{
    s32 x = self->x_pos.i.hi;
    s32 y = (s16)((u16)self->y_pos.u.hi + self->terrain_box->unk1 + self->terrain_box->unk3);
    u8 result = func_8002D724(PLAYER_OBJECT(self), x, y);
    u8 index = result - 1;

    if (index < 4 || index == 8 || index == 9)
        self->ext.main_41.unk80 = 2;
    else if ((index >= 4 && index < 8) || index == 10 || index == 11)
        self->ext.main_41.unk80 = 1;
    else
        self->ext.main_41.unk80 = 0;
}

void func_8008BB6C(struct MainObj* self)
{
    struct Main73Ext* ext = &self->ext.main_73;
    struct EffectObj* effect;

    if (g_Player.capsule_state == 0) {
        switch (self->unk6) {
        case 0:
            effect = find_free_effect_obj();
            if (effect != NULL) {
                effect->active = 1;
                effect->id = 0x18;
                ext->unk80.effect = effect;
            }
            player_start_script_action(0x14, 0x40);
            self->unk6 = 1;
            self->unk7 = 0;
            break;
        case 1:
            if (ext->unk80.effect->active == 0) {
                self->contact_damage = 6;
                self->invincibility_timer = -0x80;
                self->unk6 = 2;
                self->hp = 0;
                self->unk62 = 0;
                self->unk63 = 2;
                self->unk7C = 0x20;
                engine_obj.enable_boss = 0;
                engine_obj.unk25 = 0;
                engine_obj.boss_ptr = self;
            }
            break;
        case 2:
            if (--self->unk7C == 0) {
                self->unk5 = 2;
                self->unk6 = 0;
                self->unk7 = 0;
            }
            break;
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

void func_8008A60C(struct MainObj* self)
{
    struct Main71Ext* ext = &self->ext.main_71;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        ride_armor_pilot_stub(self, 0, 1);
        set_animation(self, 0xA);
        func_8001540C(2, 0x41, self);
    }
    if (self->collision_flags & 8) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 5);
        return;
    }
    if (!(ext->unk8D & 2)) {
        self->x_speed = 0;
        self->x_accel = 0;
        ride_armor_pilot_set_scripted_speed(self);
        if (self->y_speed >= 0 && (self->collision_flags & 4))
            self->y_speed = 0;
        if (self->animation_step.fields.relative_step == 0) {
            self->unk5 = self->y_speed < 0 ? 4 : 8;
        } else {
            if (self->y_speed < -0x5E000)
                self->y_speed = -0x5E000;
            move_with_gravity(ANIMATED_OBJECT(self));
        }
        if (self->animation_step.fields.event == 1) {
            self->attack_box = &ride_armor_pilot_punch_box;
            self->contact_damage = 6;
        } else if (self->animation_step.fields.event == 2) {
            self->attack_box = ride_armor_pilot_attack_box;
            self->contact_damage = 5;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_8004B668(struct MainObj* self)
{
    struct Main11Ext* ext = &SP_CUR_MAIN_OBJ->ext.main_11;
    u8 angle;
    s32 animation = -1;

    if ((s8)--ext->pad81[5] != 0)
        return;
    angle = ext->pad81[3] & 0xFE;
    switch (angle) {
    case 2:
    case 4:
    case 6:
    case 10:
    case 12:
    case 14:
        animation = 0x12;
        break;
    case 8:
        animation = 0x13;
        break;
    case 18:
    case 20:
    case 22:
    case 26:
    case 28:
    case 30:
        animation = 0x14;
        break;
    case 24:
        animation = 0x15;
        break;
    }
    if (animation >= 0)
        set_animation(self, animation);
    self->unk6++;
    ext->pad81[4] = 0;
}

void func_800C229C(struct ItemObj* self)
{
    u8* wait_timer = (u8*)&self->ext;
    s32 old_velocity;
    s32 center;
    s32 position;
    struct MovingBlockMotion* motion = &moving_block_motion[self->unk2];
    u16 range = motion->range;

    if (*wait_timer != 0)
        --*wait_timer;
    else
        move_object(MOVING_OBJECT(self));
    if (motion->vertical == 0) {
        old_velocity = self->x_vel.val;
        center = (s16)self->unk7C.timer16;
        position = self->x_pos.i.hi;
        if ((old_velocity > 0 && position >= center + range) || (old_velocity <= 0 && position <= center - range))
            self->x_vel.val = -old_velocity;
        if (func_8002B1E8(BASE_OBJECT(self), range + 0xA0, 0x30) == 0)
            update_on_screen(BASE_OBJECT(self), 0x30, 0x20);
        else
            self->state++;
        if (self->x_vel.val != old_velocity)
            *wait_timer = 0xA;
    } else {
        old_velocity = self->y_vel.val;
        center = ((s16*)&self->unk7C)[1];
        position = self->y_pos.i.hi;
        if ((old_velocity > 0 && position <= center - range) || (old_velocity <= 0 && position >= center + range))
            self->y_vel.val = -old_velocity;
        if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x30) == 0)
            update_on_screen(BASE_OBJECT(self), 0x30, range + 0x78);
        else
            self->state++;
        if (self->y_vel.val != old_velocity)
            *wait_timer = 0xA;
    }
    collide_with_players(PLAYER_OBJECT(self));
}

void func_800B0B48(struct VisualObj* self)
{
    struct MainObj* parent = (struct MainObj*)self->unk50;
    s32 direction;
    s32 old_x_vel;
    s32 old_y_vel;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    direction = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(parent));
    set_velocity_from_angle(MOVING_OBJECT(self), direction);
    if ((u32)(direction / 8) < 4) {
        old_x_vel = self->x_vel.val;
        old_y_vel = self->y_vel.val;
        self->x_vel.val = (s32)(0u - (u32)old_y_vel * 24u);
        self->y_vel.val = (s32)((u32)old_x_vel * 24u);
    }
    if (parent->ext.main_14.unk8C != 0)
        self->state++;
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0)
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
    else
        self->state++;
}

void func_800BD3C0(struct EffectObj* self)
{
    struct Effect37Ext* ext = &self->ext.effect_37;
    s32 i;

    for (i = 0; i < 4; i++)
        D_8013E188[i] = -1;
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    self->unk7 = 0x27;
    ext->action = (s8)self->unk2 >> 4;
    ext->timer = ext->unk1E;
    ext->unk19 = ext->unk1F;
    ext->pad1A[0] = ext->unk20;
    ext->unk22 = (s8)self->unk2 >> 4;
    self->state++;
}

void func_8008C664(struct MainObj* self)
{
    s32 direction;
    s32 facing;

    if (--self->unk7C != 0) {
        animate_object(ANIMATED_OBJECT(self));
        return;
    }
    self->unk6++;
    if ((self->collision_flags & 3) != 0)
        facing = (self->collision_flags >> 1) & 1;
    else
        facing = self->x_pos.i.hi < g_Player.x_pos.i.hi;
    self->unk15 = facing ? 0x40 : 0;
    direction = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    if (facing) {
        if ((u8)(direction - 2) < 14)
            direction = 1;
        if ((u8)(direction - 0x11) < 15)
            direction = 0;
    } else {
        if ((u8)direction < 14)
            direction = 15;
        if ((u8)direction >= 17)
            direction = 16;
    }
    set_velocity_from_angle(MOVING_OBJECT(self), direction & 0xFF);
    self->x_accel = 0;
    self->gravity = 0;
    self->x_speed = (s32)((u32)self->x_speed * 8u);
    self->y_speed = (s32)((u32)self->y_speed * 8u);
    move_with_gravity(ANIMATED_OBJECT(self));
    set_animation(self, 7);
    self->hurt_box = &double_slide_hurt_box;
    self->attack_box = &double_slide_attack_box;
}

void func_800C5994(struct ItemObj* self, u8 collision)
{
    s16 original_x = self->x_pos.i.hi;
    s16 original_y = self->y_pos.i.hi;
    s32 x = original_x;
    s32 y = original_y;
    s32 side = get_random_nonzero() % 4;

    if (side == 1 || side == 3)
        x -= 0x10;
    if (side == 2 || side == 3)
        y -= 0x20;
    x += get_random_nonzero() % 208;
    x += get_random_nonzero() % 208;
    y += get_random_nonzero() % 80;
    if (collision != 0) {
        self->x_pos.i.hi = x;
        self->y_pos.i.hi = y;
        spawn_debris(4, layout_gate_frames, self);
        self->x_pos.i.hi = original_x;
        self->y_pos.i.hi = original_y;
    } else {
        spawn_explosion_at(0, (s16)x, (s16)y, 0xFF);
    }
}

void func_800C580C(struct ItemObj* self)
{
    if (--self->unk7C.timer == 0) {
        self->state = 3;
        self->unk5 = 0;
        self->unk2 = self->tail_ext.unk1.unk84.bytes[0];
        return;
    }
    if ((main_bss_state.frame_counter & 3) == 0)
        func_800C5994(self, 0);
    if ((main_bss_state.frame_counter & 7) == 0)
        func_800C5994(self, 1);
    if ((main_bss_state.frame_counter & 15) == 0)
        func_8001540C(0, layout_gate_unused[get_random() & 3], self);
    if (self->unk7C.timer == 0x1E) {
        layout_gate_check_layout(self);
        layout_gate_apply_layout(self);
    }
}

void func_800B9354(struct EffectObj* self)
{
    const u8* tiles = freeze_blast_tile_patches[(s8)self->unk2];
    for (s32 i = 0; i < 2; i++) {
        s32 column = tiles[5] + i;
        D_80141BE8[column] = tiles[0] + i;
        D_80141BE8[layout_width + column] = tiles[1] + i;
        D_80141BE8[layout_size + column] = tiles[2] ? tiles[2] + i : 0;
        D_80141BE8[layout_size + layout_width + column] = tiles[3] + i;
        D_80141BE8[2 * layout_size + layout_width + column] = tiles[4] + i;
    }
    for (s32 i = 0; i < 3; i++)
        background_objects[i].unk4C = 1;
}

void func_800B94B8(struct EffectObj* self)
{
    struct Effect17SpawnGroupPC* group = &freeze_blast_spawn_groups[(s8)self->unk2];
    for (u32 i = 0; i < (u8)group->count; i++) {
        struct Effect17SpawnRecordPC* record = &group->records[i];
        for (u32 j = 0; j < record->count; j++) {
            struct MainObj* child = find_free_main_obj();
            s32 index;
            s32 column;
            s32 row;
            if (child == NULL)
                continue;
            child->active = 0x41;
            child->id = 0x15;
            child->unk2 = (get_random_nonzero() % 6) + 6;
            child->x_pos.u.hi = record->x + (j & 0xFF) * 0x10;
            child->y_pos.u.hi = record->y;
            index = func_8002938C(0x15);
            child->unk40 = D_801406A8[index] >> 7;
            column = func_8002938C(0x15) * 4 + 0x18;
            row = func_8002938C(0x15);
            child->unk42 = (column % 16) | (((row + 6) / 4 + 0x1E0) << 6);
            child->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x15));
        }
    }
}

void func_800B91E0(struct EffectObj* self)
{
    struct Effect17Ext* ext = &self->ext.effect_17;
    u8 phase = ext->phase;
    ext->phase--;
    if (phase != 0)
        return;
    if ((u16)g_FilterAmountR >= 0x1E) {
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        engine_obj.character_state.fields.active = 1;
        need_palette_load |= 1;
        func_800B9354(self);
        engine_obj.unk10 = 0;
        engine_obj.unk11 = 0;
        engine_obj.unk12 = 0;
        engine_obj.unk13 = 0;
        func_800B94B8(self);
        ext->timer = 2;
        self->state++;
        return;
    }
    ext->phase = 1;
    if (--ext->timer == 0) {
        ext->timer = 2;
        return;
    }
    g_FilterAmountR += 2;
    g_FilterAmountG += 0x40;
    g_FilterAmountB += 0x800;
}

void func_8004AB6C(struct MainObj* self)
{
    s32 collision;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    func_8002D9BC(self);
    SP_CUR_MAIN_OBJ->ext.main_11.saved_unk5 = self->unk5;
    collision = func_8002DD04(self);
    if (func_8002BB80(self, MAIN_OBJECT(&g_Player)) != 0)
        collision = -1;
    if (collision < 0) {
        spawn_explosion(BASE_OBJECT(self));
        SP_CUR_MAIN_OBJ->ext.main_11.pad81[5] = 0x10;
        for (s32 i = 0; i < 0x10; i++) {
            struct ShotObj* shot = find_free_shot_obj();
            if (shot == NULL)
                continue;
            shot->active = 0x41;
            shot->id = 0xA;
            shot->bg_offset = self->bg_offset;
            shot->x_pos = self->x_pos;
            shot->y_pos = self->y_pos;
            shot->unk2 = i * 2;
            set_velocity_from_angle(MOVING_OBJECT(shot), i * 2);
        }
        self->state++;
        return;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        animate_object(ANIMATED_OBJECT(self));
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state = 4;
    }
    if (!(self->collision_flags & 8))
        move_with_gravity(ANIMATED_OBJECT(self));
}

void func_8009B424(struct ShotObj* self)
{
    s32 column;
    s32 row;

    self->unk54 = dragon_spread_shot_hit_box;
    self->unk50.data = dragon_spread_shot_hit_box;
    self->on_screen = 1;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk67 = 0;
    self->unk16 = 0;
    self->unk15 = 0;
    self->unk68 = NULL;
    self->unk58.animation_steps = D_80105FF0;
    self->state++;
    self->unk42 &= 0x7FFF;
    self->unk40 = D_801406A8[9] >> 7;
    self->animation_table = (u32**)dragon_spread_shot_animations;
    self->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 9);
    column = func_8002938C(0xB) * 4 + 0x18;
    row = func_8002938C(0xB);
    self->unk42 = (column % 16) | (((row + 6) / 4 + 0x1E0) << 6);
    self->unk60 = 2;
    self->unk5C = 1;
    self->unk54 = dragon_spread_shot_large_hit_box;
    self->x_vel.val *= 5;
    self->y_vel.val *= 5;
    self->y_pos.u.hi -= 8;
    set_animation(self, (u8)self->unk2 >> 1);
    self->unk84.value = 0;
}

void func_8005C474(struct MainObj* self)
{
    u8* ext = (u8*)&self->ext;
    const void* saved_bounds;
    s16 x;
    s16 y;
    s32 direction;

    if (self->unk5 == 0) {
        self->unk5++;
        x = self->x_pos.i.hi;
        y = self->y_pos.i.hi;
        direction = self->unk15 ? -1 : 1;
        spawn_explosion_at(0, x + direction * 0x4D, y, 1);
        spawn_debris_offset(5, D_800FDC28, (struct MiscObj*)self,
            direction * 0x4D0000, 0);
        set_animation(self, 0xB);
    }
    if (self->y_pos.val - background_objects[(u8)self->bg_offset].y_pos.val > 0xA80000) {
        self->state++;
        x = self->x_pos.i.hi;
        y = self->y_pos.i.hi;
        direction = self->unk15 ? -1 : 1;
        spawn_explosion_at(0, x + direction * 0x47, (s16)((u16)y + 1), 0);
        spawn_explosion_at(0, x + direction * 0x28, y, 1);
        spawn_explosion_at(0, x + direction * 0xC, (s16)((u16)y - 1), 0xFF);
        spawn_explosion_at(0, x - direction * 0x15, (s16)((u16)y + 2), 0xFF);
        spawn_explosion_at(0, x - direction * 0x33, (s16)((u16)y - 1), 0xFF);
        spawn_explosion_at(0, x - direction * 0x50, y, 0xFF);
        spawn_debris_offset(5, D_800FDC28, (struct MiscObj*)self,
            direction * 0x470000, 0x10000);
        spawn_debris_offset(1, D_800FDC30, (struct MiscObj*)self,
            direction * 0x280000, 0);
        spawn_debris_offset(1, D_800FDC34, (struct MiscObj*)self,
            direction * 0xC0000, -0x10000);
        spawn_debris_offset(1, D_800FDC38, (struct MiscObj*)self,
            -direction * 0x150000, 0x20000);
        spawn_debris_offset(1, D_800FDC3C, (struct MiscObj*)self,
            -direction * 0x330000, -0x10000);
    }
    saved_bounds = self->hurt_box;
    self->collision_data = D_801060F0;
    self->hurt_box = D_800FDA0C;
    self->unk65 = ext[3];
    func_8002DD04(self);
    ext[4] = self->unk65;
    self->hurt_box = saved_bounds;
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0)
        update_on_screen(BASE_OBJECT(self), 0x70, 0x30);
    else
        despawn_object(OBJECT_HEADER(self));
}

void func_8005BDE4(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        s32 choice;
        struct ShotObj* shot;
        if (self->unk2 >= 0xA)
            choice = (u8)get_random_nonzero() % 3;
        else
            choice = get_random_nonzero() & 1;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            s32 x_offset = D_800FDC40[choice * 2];
            s32 y_offset = D_800FDC40[choice * 2 + 1];
            shot->active = 0x41;
            shot->id = 0x11;
            shot->unk7C = (struct WeaponObj*)self;
            shot->state = 0;
            shot->unk5 = 0;
            shot->unk6 = 0;
            shot->x_pos.val = self->x_pos.val + (self->unk15 ? -x_offset : x_offset) * 0x10000;
            shot->y_pos.val = self->y_pos.val + y_offset * 0x10000;
            shot->unk2 = 0;
            self->animation_step.fields.event = 0;
        }
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 0);
        self->unk5 = 3;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void func_800A8628(struct ShotObj* self)
{
    struct WeaponObj* parent = self->unk7C;
    s32 subtype = (s8)self->unk2;
    s32 direction;

    self->state = 1;
    self->unk40 = parent->unk40;
    self->animation_table = parent->animation_table;
    self->unk3C = parent->unk3C;
    self->unk42 = parent->unk42;
    self->unk15 = parent->unk15;
    self->bg_offset = parent->bg_offset;
    self->x_pos = parent->x_pos;
    self->y_pos = parent->y_pos;
    self->unk16 = 5;
    self->unk58.data = NULL;
    self->unk50.data = NULL;
    self->unk54 = NULL;
    self->unk68 = NULL;

    switch (subtype) {
    case 0:
        self->unk60 = 9;
        set_animation(self, 5);
        break;
    case 1:
    case 2:
        self->unk58.collision_data = D_80106070;
        self->unk68 = (struct Unk_unk68*)sigma_shot_boxes[0];
        self->unk50.data = (u8*)sigma_shot_boxes[1];
        self->unk60 = 6;
        set_animation(self, 3);
        break;
    case 3:
        direction = (u8)angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
        if ((u8)direction < 9)
            direction = 0;
        else if ((u8)(direction - 9) < 8)
            direction = 0x10;
        self->pad94 = direction;
        self->unk60 = 9;
        self->y_pos.u.hi -= 0x15;
        self->x_pos.i.hi += self->unk15 ? 0x21 : -0x21;
        self->unk68 = (struct Unk_unk68*)sigma_shot_boxes[6];
        self->unk50.data = (u8*)sigma_shot_boxes[5];
        set_velocity_from_angle(MOVING_OBJECT(self), (u8)self->pad94);
        set_animation(self, 0x1E);
        func_8001540C(2, 5, self);
        break;
    case 4:
        self->x_vel.val = 0;
        self->y_vel.val = self->timer == 0 ? -0x80000 : 0x80000;
        self->unk50.data = (u8*)sigma_shot_boxes[8];
        self->unk60 = 6;
        set_animation(self, 0x23);
        func_8001540C(2, 7, self);
        break;
    case 5:
        self->x_vel.val = self->timer == 0 ? -0x80000 : 0x80000;
        self->y_vel.val = 0;
        self->unk50.data = (u8*)sigma_shot_boxes[7];
        self->unk60 = 6;
        set_animation(self, 0x25);
        func_8001540C(2, 7, self);
        break;
    case 6:
        self->unk58.data = (const u8*)D_801060F0;
        self->unk50.data = (u8*)sigma_shot_boxes[2];
        self->unk54 = (u8*)sigma_shot_boxes[3];
        self->unk95 = (u8)self->timer;
        self->unk60 = 6;
        self->unk90.i.lo = self->x_pos.i.hi + (self->unk15 ? -1 : 1) * (s8)sigma_shot_init_box[self->unk95];
        self->unk90.i.hi = self->y_pos.i.hi - 0x40;
        set_animation_frame(ANIMATED_OBJECT(self), 0x21, 2);
        break;
    case 7:
        self->pad96[0] = 6;
        self->unk60 = 9;
        self->unk50.data = (u8*)sigma_shot_boxes[5];
        self->pad94 = self->unk15 ? 5 : 7;
        set_animation(self, 0x1E);
        func_8001540C(2, 5, self);
        break;
    case 8: {
        struct QuadObj* quad = (struct QuadObj*)self->unk7C;
        struct MainObj* owner = (struct MainObj*)quad->unk5C;

        self->unk16 = 5;
        self->unk40 = owner->unk40;
        self->animation_table = (u32**)owner->animation_table;
        self->unk3C = (void*)owner->sprite_frames;
        self->unk42 = owner->unk42;
        self->unk15 = owner->unk15 ^ 0x40;
        self->bg_offset = owner->bg_offset;
        self->x_pos.i.hi = quad->x_pos.i.hi + quad->vertices[2].x.i.hi + 4;
        self->unk50.data = (u8*)sigma_shot_boxes[9];
        self->unk60 = 9;
        self->y_pos.i.hi = quad->y_pos.i.hi + quad->vertices[2].y.i.hi - 8;
        set_animation(self, 0x26);
        func_8001540C(2, 0xC, self);
        break;
    }
    case 9:
        self->y_vel.val = 0x60000;
        self->unk2C = 0x4200;
        self->x_vel.val = 0;
        self->unk28 = 0;
        self->unk68 = (struct Unk_unk68*)sigma_shot_boxes[6];
        set_animation(self, 0x1E);
        break;
    case 10:
        set_animation(self, 0x2A);
        break;
    }
}

void func_80084EE4(struct MainObj* self)
{
    struct Main68Ext* ext = &self->ext.main_68;
    s32 collision = func_8002DD04(self);

    if (ext->flash_timer != 0) {
        ext->flash_timer--;
        if (ext->flash_timer & 1)
            self->unk42 |= 0x8000;
        else
            self->unk42 &= 0x7FFF;
    } else {
        self->collision_data = D_80107F84;
    }
    if (collision < 0) {
        self->state = 4;
        self->unk5 = 0;
        self->unk6 = 0;
        return;
    }
    if (collision == 5 || collision == 0x24) {
        if (self->unk5 != 4) {
            self->state = 3;
            self->unk5 = 0;
            return;
        }
        if (ext->flash_timer == 0) {
            self->collision_data = D_801060F0;
            ext->flash_timer = 0x40;
        }
    }
    func_8002D9BC(self);
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    sigma_cloak_step_funcs[(s8)self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->on_screen == 0) {
        self->attack_box = NULL;
        self->hurt_box = NULL;
    }
}

void func_80083710(struct MainObj* self)
{
    struct Main68Ext* ext = &self->ext.main_68;

    if (--self->unk7C == 0) {
        struct VisualObj* visual;
        s32 distance;
        self->unk7C = 0xA;
        ext->count = 0;
        self->unk6++;
        set_animation(self, 4);
        set_animation(ext->scythe, 7);
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x20;
            visual->unk2 = 0;
            visual->unk50 = (struct PlayerObj*)self;
            ext->visual = visual;
        }
        distance = self->x_pos.val - g_Player.x_pos.val;
        ext->shot_type = (distance > 0x3FFFFF || distance < -0x3FFFFF) ? 1 : 2;
    }
    is_on_screen(BASE_OBJECT(self));
}

void func_800837FC(struct MainObj* self)
{
    struct Main68Ext* ext = &self->ext.main_68;
    u8 i;

    if (self->unk7 == 0) {
        if (--self->unk7C == 0) {
            func_8001540C(2, 0xD, self);
            for (i = 0; i < 2; i++) {
                struct ShotObj* shot = find_free_shot_obj();
                if (shot != NULL) {
                    shot->active = 0x41;
                    shot->id = 0x2E;
                    shot->unk2 = ext->shot_type;
                    shot->unk99 = i;
                    shot->unk7C = (struct WeaponObj*)self;
                    shot->pad9A[0] = ext->count;
                    self->unk7C = 0x1E;
                    ext->active_shots++;
                }
            }
            if (++ext->count == 3) {
                self->unk7C = 0x14;
                self->unk7++;
            }
        }
    } else if (--self->unk7C == 0) {
        ext->visual->state++;
        self->unk7 = 0;
        self->unk6++;
    }
    is_on_screen(BASE_OBJECT(self));
}

void func_80083C2C(struct MainObj* self)
{
    if (self->unk7 == 0) {
        self->attack_box = &D_80103EE4;
        self->hurt_box = &D_80103EE8;
        if (--self->unk7C == 0) {
            self->hurt_box = &D_80103EF8;
            self->unk7++;
            self->unk15 ^= 0x40;
            set_animation(self, 1);
            set_animation(self->ext.main_68.scythe, 6);
            func_8001540C(2, 2, self);
        }
    } else if (self->animation_step.fields.event != 0) {
        self->unk7 = 0;
        self->unk6++;
        self->x_speed = self->unk15 ? -0x60000 : 0x60000;
        self->terrain_box = &D_80103EEC;
        self->unk4B = 1;
    }
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void func_800B4E34(struct VisualObj* self)
{
    struct PlayerObj* parent = self->unk50;

    self->state = 1;
    self->unk40 = parent->unk40;
    self->animation_table = parent->animation_table;
    self->unk3C = parent->unk3C;
    self->unk42 = parent->unk42;
    self->unk15 = parent->unk15;
    self->bg_offset = parent->bg_offset;
    self->x_pos.val = parent->x_pos.val;
    self->y_pos.val = parent->y_pos.val;
    self->unk16 = parent->unk16;

    switch (self->unk2) {
    case 0:
        self->unk16 = 5;
        set_animation(self, 2);
        break;
    case 1:
        self->x_pos.i.hi += (parent->unk15 ? -1 : 1) * (s8)sigma_fx_x_offsets[get_random() & 3];
        self->y_pos.i.hi += (s8)sigma_fx_y_offsets[get_random() & 3];
        self->y_vel.val = sigma_fx_cloak_piece_y_vels[get_random() & 7];
        self->x_vel.val = sigma_fx_cloak_piece_x_vels[get_random() & 7];
        set_animation(self, sigma_fx_cloak_piece_animations[self->unk54]);
        self->unk54 = 0x14;
        break;
    case 2:
    case 5:
        self->unk16 = 5;
        self->x_pos.i.hi += (parent->unk15 ? -1 : 1) * (s8)sigma_fx_x_offsets[get_random() & 3];
        self->y_pos.i.hi += (s8)sigma_fx_y_offsets[get_random() & 3];
        set_animation(self, 0xA);
        break;
    case 3:
        self->x_pos.val += self->unk15 ? 0x90000 : -0x90000;
        self->y_pos.val -= 0x160000;
        set_animation(self, 0x22);
        break;
    case 4:
        self->x_pos.val += self->unk15 ? -0x160000 : 0x160000;
        self->y_pos.val += 0x40000;
        set_animation(self, 0x24);
        break;
    case 6:
        self->unk16 = 5;
        set_animation(self, 0x2A);
        self->unk42 &= 0x7FFF;
        break;
    }
}

void func_80046400(struct MainObj* self)
{
    s16 timer = self->unk7C;
    u8 direction;
    s32 speed;

    animate_object(ANIMATED_OBJECT(self));
    self->unk7C = timer - 1;
    if (timer >= 5)
        return;

    func_8001540C(2, 0x14, self);
    direction = (u8)angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    set_velocity_from_angle(MOVING_OBJECT(self), direction);
    if (self->unk15 == 0 && self->x_speed > 0)
        self->unk15 = 0x40;
    if (self->unk15 == 0x40 && self->x_speed < 0)
        self->unk15 = 0;
    if (self->y_speed > 0)
        self->y_speed = 0;
    if ((self->x_speed >= 0 && self->x_speed + self->y_speed == 0)
        || (self->x_speed < 0 && self->x_speed == self->y_speed))
        self->x_speed = self->unk15 ? 0x10000 : -0x10000;

    if (direction == 0x11 || direction == 0x1F)
        set_animation(self, 0xF);
    else if (direction >= 0x12 && direction <= 0x1E && direction != 0x17 && direction != 0x18 && direction != 0x19)
        set_animation(self, 0xE);
    else if (direction == 0x17 || direction == 0x19)
        set_animation(self, 0xD);
    else if (direction == 0x18)
        set_animation(self, 0xC);
    else {
        self->unk5 = 4;
        self->unk6 = 0;
        self->unk7C = 5;
    }

    self->x_speed *= 3;
    self->y_speed *= 3;
    speed = self->x_speed;
    self->x_accel = (speed < 0 ? -speed : speed) >> 6;
    speed = self->y_speed;
    self->gravity = (speed < 0 ? -speed : speed) >> 6;
    self->unk6++;
}

void func_80055024(struct MainObj* self)
{
    s32 resource;
    s32 column;
    s32 row;

    self->hp = 0xF;
    self->contact_damage = 4;
    self->invincibility_timer = 0;
    self->collision_data = (const u16*)D_80106D74;
    self->bg_offset = g_Player.bg_offset;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    resource = func_8002938C(5);
    row = func_8002938C(5);
    column = resource * 4 + 0x18;
    self->unk42 = (column % 16) | (((row + 6) / 4 + 0x1E0) << 6);
    self->animation_table = (const u8* const*)bee_hive_animations;
    self->unk16 = 6;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->unk15 = 0;
    self->hurt_box = (const u8*)&bee_hive_hurt_box;
    self->attack_box = &bee_hive_hurt_box;
    self->terrain_box = NULL;
    set_animation(self, 0);
    self->ext.main_22.saved_unk5 = 0;
    self->ext.main_22.unk84 = 0;
    self->ext.main_22.pad88[0] = 0;
    self->ext.main_22.pad88[1] = 0;
    self->ext.main_22.pad88[2] = 0;
    self->ext.main_22.pad88[3] = 0;
    self->ext.main_22.unk8C = 1;
    self->ext.main_22.unk90 = 0;
    self->ext.main_22.parts_mask = 0;
    self->unk5 = 2;
    self->unk6 = 0;
    self->state++;
}

void func_80055164(struct MainObj* self)
{
    struct Main22Ext* ext = &self->ext.main_22;
    s32 collision = 0;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    bee_hive_step_funcs[self->unk5](self);
    if (ext->pad88[0] == 0 && ext->pad88[1] == 0
        && ext->pad88[2] == 0 && ext->pad88[3] == 0) {
        func_8002D9BC(self);
        collision = func_8002DD04(self);
    }
    if (self->unk5 != 0)
        ext->saved_unk5 = self->unk5;
    if (collision < 0) {
        self->unk5 = 6;
        self->unk6 = 0;
        spawn_debris(8, bee_hive_debris, self);
        drop_item(BASE_OBJECT(self), 9);
        ext->pad88[0] = 1;
        self->unk42 &= 0x7FFF;
        set_animation(self, 3);
    } else if (func_8002B1E8(BASE_OBJECT(self), 0x30, 0x30) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else if (ext->parts_mask == 0) {
        self->state++;
    }
}

void func_80055358(struct MainObj* self)
{
    static const struct {
        s16 x;
        s16 y;
        u8 subtype;
    } parts[10] = {
        { -48, 10, 3 },
        { 48, 10, 3 },
        { -22, 69, 4 },
        { 22, 69, 4 },
        { -40, -16, 3 },
        { 40, -16, 3 },
        { -40, 36, 4 },
        { 40, 36, 4 },
        { -26, -28, 3 },
        { 26, -28, 3 },
    };
    struct Main22Ext* ext = &self->ext.main_22;
    u8 i;

    animate_object(ANIMATED_OBJECT(self));
    if (--ext->unk84 != 0)
        return;
    for (i = 0; i < 2; i++) {
        struct MainObj* child = find_free_main_obj();
        s32 part = ext->unk90;
        s32 resource;
        s32 column;
        if (child != NULL) {
            child->active = 0x41;
            child->id = 5;
            child->unk2 = parts[part].subtype;
            child->on_screen = 0;
            child->state = 0;
            memset(&child->ext.main_5, 0, 12);
            child->ext.main_5.part_index = part;
            child->ext.main_5.target_x = self->y_pos.i.hi + parts[part].y;
            child->ext.main_5.target_y = self->x_pos.i.hi + parts[part].x;
            child->ext.main_5.owner = self;
            child->x_pos.i.hi = self->x_pos.i.hi + ((part & 1) ? 0x10 : -0x10);
            child->y_pos.i.hi = self->y_pos.i.hi + 9;
            resource = func_8002938C(5);
            child->unk40 = D_801406A8[resource] >> 7;
            resource = func_8002938C(5);
            column = resource * 4 + 0x18;
            child->unk42 = (column % 16) | (((resource + 6) / 4 + 0x1E0) << 6);
            resource = func_8002938C(5);
            child->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
            ext->unk90++;
            ext->parts_mask |= 1u << part;
            if (ext->unk90 >= 10) {
                set_animation(self, 2);
                ext->unk84 = 0x12;
                self->unk6++;
            }
        }
    }
    ext->unk84 = 8;
}

void func_800559BC(struct MainObj* self)
{
    static const struct {
        s16 x;
        s16 y;
        u8 subtype;
    } parts[10] = {
        { -48, 10, 3 },
        { 48, 10, 3 },
        { -22, 69, 4 },
        { 22, 69, 4 },
        { -40, -16, 3 },
        { 40, -16, 3 },
        { -40, 36, 4 },
        { 40, 36, 4 },
        { -26, -28, 3 },
        { 26, -28, 3 },
    };
    struct Main22Ext* ext = &self->ext.main_22;
    u8 spawned = 0;
    u8 side = 0;
    u8 part;

    for (part = 0; part < 10 && spawned < 2; part++) {
        struct MainObj* child;
        s32 resource;
        s32 column;
        if (ext->parts_mask & (1u << part))
            continue;
        child = find_free_main_obj();
        if (child == NULL)
            continue;
        child->active = 0x41;
        child->id = 5;
        child->unk2 = parts[part].subtype;
        child->on_screen = 0;
        child->state = 0;
        memset(&child->ext.main_5, 0, 12);
        child->ext.main_5.part_index = part;
        child->ext.main_5.target_x = self->y_pos.i.hi + parts[part].y;
        child->ext.main_5.target_y = self->x_pos.i.hi + parts[part].x;
        child->ext.main_5.owner = self;
        child->x_pos.i.hi = self->x_pos.i.hi;
        if (part & 1) {
            if (side != 1) {
                child->x_pos.i.hi += 0x10;
                side = 1;
            }
        } else if (side != 2) {
            child->x_pos.i.hi -= 0x10;
            side = 2;
        }
        child->y_pos.i.hi = self->y_pos.i.hi + 9;
        if (child->x_pos.val > g_Player.x_pos.val && (part & 1))
            child->ext.main_5.target_y += 8;
        if (child->x_pos.val < g_Player.x_pos.val && !(part & 1))
            child->ext.main_5.target_y -= 8;
        resource = func_8002938C(5);
        child->unk40 = D_801406A8[resource] >> 7;
        resource = func_8002938C(5);
        column = resource * 4 + 0x18;
        child->unk42 = (column % 16) | (((resource + 6) / 4 + 0x1E0) << 6);
        resource = func_8002938C(5);
        child->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
        ext->parts_mask |= 1u << part;
        if (++spawned == 1)
            ext->unk8C = 1;
    }
}

extern s32 D_801396B8;
extern s32 D_801396BC;

void func_8001F198(struct EngineObj* arg0)
{
    s32* dst;
    s32* src;
    u8 stage;
    u32 i;

    for (i = 0; i < 0x10; i++)
        arg0->character_state.bytes[i] = 0;
    stage = arg0->stage;
    arg0->character_state.bytes[2] = 0;
    arg0->character_state.bytes[1] = 0;
    arg0->stage = 0xF;
    arg0->substage = 0;
    arg0->checkpoint = 0;
    arg0->unk1F = 0;
    arg0->enable_boss = 0;
    arg0->character_state.bytes[0] = stage;
    func_80013014();
    reset_objects();
    func_8002AB20();
    func_80028BF0();
    func_8002771C();
    func_80023CE0();
    arg0->unkE = 0;
    arg0->unk2 = 1;
    arg0->unk3 = 0;
    D_801396B8 = 0;
    D_801396BC = 0;
    if (arg0->cur_character != 0)
        return;
    src = SP_ARC_30 + (arg0->character_state.bytes[0] - 1) * 0x30;
    dst = SP_PALETTE_WORDS + 0xAE0 / 4;
    for (i = 0; i < 0x30; i++)
        *dst++ = *src++;
    need_palette_load |= 1;
}

extern struct MiscObj* D_801396C0;
extern struct MiscObj* D_801396C4;
struct MiscObj* func_8001F150(struct EngineObj*, u8);

void func_8001F2BC(struct EngineObj* arg0)
{
    u8 index;

    func_800129A4(8);
    func_8001663C(MUSIC_WEAPON_GET, 0x70);
    arg0->unk2 = 0;
    arg0->unk1++;
    if (arg0->cur_character == 0) {
        D_801396B8 = 0x100000;
        background_objects[0].x_pos.val = 0;
    } else {
        D_801396B8 = 0xFFF00000;
        background_objects[1].x_pos.val = 0x3000000;
    }
    D_801396C0 = func_8001F150(arg0, arg0->cur_character != 0 ? 9 : 0);
    index = arg0->character_state.bytes[0];
    if (arg0->cur_character != 0)
        index += 9;
    D_801396C4 = func_8001F150(arg0, index);
}

struct Misc45PositionData {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};

extern struct Misc45PositionData scripted_slider_offsets[];
extern u8 stage_cutscene_data[24];
void func_8001F3D4(struct MainObj*);
void func_8001F5D8(struct EngineObj*);

void func_800D0D68(struct MiscObj* self, u8 kind)
{
    struct MiscObj* child;

    self->x_pos.i.hi = scripted_slider_offsets[self->unk2].x;
    self->y_pos.i.hi = scripted_slider_offsets[self->unk2].y;
    self->ext.misc_45.unk58 = scripted_slider_offsets[self->unk2].width;
    self->ext.misc_45.target_x = scripted_slider_offsets[self->unk2].height;
    self->x_vel.val = 0xFFF20000;
    self->unk28 = 0;
    child = find_free_misc_obj();
    if (child != NULL) {
        child->active = 0x41;
        child->id = 0x2D;
        child->unk2 = kind;
        child->x_pos.val = self->x_pos.val;
        child->ext.misc_45.owner = (struct MainObj*)self;
        child->y_pos.val = self->y_pos.val;
    }
}

void func_800D0E48(struct MiscObj* self)
{
    self->active = 0x41;
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[0];
    self->unk42 = 0x7848;
    self->bg_offset = -1;
    self->ext.misc_45.direction = 1;
    self->unk40 = D_801406A8[0] >> 7;
    self->unk16 = 0;
    self->state++;
    self->unk15 = 0;
    switch (self->unk2) {
    case 1:
        func_800D0D68(self, 0x12);
        break;
    case 5:
        func_800D0D68(self, 0x13);
        break;
    case 7:
        func_800D0D68(self, 0x14);
        break;
#ifndef VERSION_JP
    case 11:
        func_800D0D68(self, 0x15);
        break;
#endif
    default:
        if (self->unk2 >= 0x12) {
            self->x_pos.i.hi += scripted_slider_offsets[self->unk2].x;
            self->unk5 = 3;
            self->y_pos.i.hi += scripted_slider_offsets[self->unk2].y;
            break;
        }
        self->x_pos.i.hi = scripted_slider_offsets[self->unk2].x;
        self->y_pos.i.hi = scripted_slider_offsets[self->unk2].y;
        self->ext.misc_45.unk58 = scripted_slider_offsets[self->unk2].width;
        self->ext.misc_45.target_x = scripted_slider_offsets[self->unk2].height;
        if (self->unk2 == 0 || self->unk2 == 9) {
            self->x_vel.val = 0xE0000;
            self->ext.misc_45.direction = 0;
        } else {
            self->x_vel.val = 0xFFF20000;
        }
        self->unk28 = 0;
        break;
    }
    self->animation_step.fields.frame_index = stage_cutscene_data[self->unk2];
}

void func_8001F488(struct EngineObj* arg0)
{
    struct BackgroundObj* background;

    if (controller_input.pressed & 0x8FF) {
        func_8001F3D4((struct MainObj*)arg0);
        background_objects[arg0->cur_character].unk4C = 1;
        arg0->character_state.bytes[2] = 1;
        arg0->character_state.bytes[1] = 1;
        D_801396C0->state = 1;
        D_801396C4->state = 1;
        D_801396C0->unk5 = 4;
        D_801396C4->unk5 = 4;
        return;
    }
    background = &background_objects[arg0->cur_character];
    background->x_pos.val += D_801396B8;
    if (arg0->cur_character == 0) {
        if (background->x_pos.val <= 0x2000000)
            return;
    } else if (background->x_pos.val > 0xFFFFFF) {
        return;
    }
    func_8001F3D4((struct MainObj*)arg0);
}

void func_8001F634(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        if (arg0->character_state.bytes[2] == 0) {
            arg0->unk4 = 0x1E;
            arg0->unk3 = 0;
            arg0->character_state.bytes[1] = 1;
            arg0->unk2++;
        } else {
            arg0->unk2 = 4;
            arg0->unk3 = 0;
            arg0->unk4 = 0x78;
        }
    } else {
        func_8001F5D8(arg0);
    }
    need_palette_load |= 1;
}

void func_8001F6E8(struct EngineObj* arg0)
{
    if (D_801396C0->unk5 != 2 || D_801396C4->unk5 != 2) {
        if (!(controller_input.pressed & 0x8FF))
            return;
        D_801396C0->state = 1;
        D_801396C4->state = 1;
        D_801396C0->unk5 = 4;
        D_801396C4->unk5 = 4;
    }
    arg0->unk3 = 0;
    arg0->unk4 = 6;
    arg0->unk2++;
}

void func_800D11B0(struct MiscObj* self)
{
    self->unk28 = 0;
    self->x_vel.val = 0;
    self->unk5 = 2;
    self->x_pos.i.hi = self->ext.misc_45.target_x;
}

void func_8001FA24(struct EngineObj* arg0)
{
    u8 flags;
    u32 i;

    flags = arg0->palette_flags | (1 << (arg0->character_state.bytes[0] - 1));
    arg0->palette_flags = flags;
    if ((u8)g_Player.boss_flags != 0xFF && flags == 0xFF)
        arg0->unk5F = 5;
    g_Player.boss_flags |= 1 << (arg0->character_state.bytes[0] - 1);
    arg0->state = 9;
    arg0->unk1 = 0;
    arg0->unk2 = 0;
    for (i = 0; i < 0x10; i++)
        arg0->character_state.bytes[i] = 0;
}

extern union AnimationStep* stage_portrait_animations[1];

void func_800CA52C(struct MiscObj* self)
{
    self->unk42 = 0x780B;
    self->unk40 = D_801406A8[1] >> 7;
    self->animation_table = (u32**)stage_portrait_animations;
    self->bg_offset = 0;
    self->unk15 = 0;
    self->unk16 = 1;
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[1];
    if (self->unk2 == 0) {
        self->x_pos.val = 0xE40000;
        self->y_pos.val = 0x1880000;
        set_animation_frame(ANIMATED_OBJECT(self), 0, 1);
        self->unk7 = 1;
        self->state++;
    } else {
        self->x_pos.i.hi = 0x60;
        self->y_pos.i.hi = 0x180;
        set_animation_frame(ANIMATED_OBJECT(self), 0, 10);
        self->unk42 = 0x784F;
        self->state = 2;
    }
}

extern s16 stage_select_panel_shapes[8][8];

void func_800D4334(struct QuadObj* self)
{
    self->unk36 = 0x13;
    self->bg_offset = -1;
    self->vertices[2].y.val = 0x900000;
    self->vertices[3].y.val = 0x900000;
    self->vertices[0].y.val = 0x900000;
    self->vertices[1].y.val = 0x900000;
    self->ext.quad_1.steps = 0x1E;
    self->vertices[2].x.val = 0xA00000;
    self->vertices[3].x.val = 0xA00000;
    self->vertices[0].x.val = 0xA00000;
    self->vertices[1].x.val = 0xA00000;
    self->unk34 = 0;
    self->x_pos.val = 0;
    self->y_pos.val = 0;
    self->ext.quad_1.settled[0] = 0;
    self->ext.quad_1.settled[1] = 0;
    self->ext.quad_1.settled[2] = 0;
    self->ext.quad_1.settled[3] = 0;
    self->ext.quad_1.unk42 = 1;
    self->active |= 0x92;
    if (self->unk2 & 0x10) {
        self->unk2 &= 0xF;
        self->ext.quad_1.delay = 1;
    } else {
        self->ext.quad_1.delay = self->unk2 << 3;
    }
    self->state++;
    quad_is_on_screen(self);
}

void func_800D43F4(struct QuadObj* self)
{
    f32* vertex_x;
    f32* vertex_y;
    struct MiscObj* misc;
    struct EffectObj* effect;
    s16* target;
    s32 dx;
    s32 dy;
    s32 i;
    u8 region;

    if (self->ext.quad_1.delay != 0) {
        self->ext.quad_1.delay--;
        quad_is_on_screen(self);
        return;
    }
    vertex_x = &self->vertices[0].x;
    vertex_y = &self->vertices[0].y;
    for (i = 0; i < 4; i++) {
        target = &stage_select_panel_shapes[self->unk2][i * 2];
        dx = vertex_x->val - (target[0] << 16);
        dy = vertex_y->val - (target[1] << 16);
        region = angle_from_delta(dx, dy);
        if ((((self->ext.quad_1.region[i] ^ region) & 0x10) || self->ext.quad_1.settled[i] != 0) && self->ext.quad_1.unk42 == 0) {
            self->x_pos.i.lo = 0;
            self->y_pos.i.lo = 0;
            self->ext.quad_1.settled[i] = 1;
        } else {
            vertex_x->val -= dx / (s32)self->ext.quad_1.steps;
            vertex_y->val -= dy / (s32)self->ext.quad_1.steps;
            self->ext.quad_1.settled[i] = 0;
            if (i == 3)
                self->ext.quad_1.unk42 = 0;
        }
        vertex_x += 2;
        vertex_y += 2;
        self->ext.quad_1.region[i] = region;
    }
    if (--self->ext.quad_1.steps == 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0xC;
            misc->unk2 = self->unk2;
        }
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 3;
            effect->unk2 = 0;
        }
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0xC;
            misc->unk2 = self->unk2 | 0x80;
        }
        target = stage_select_panel_shapes[self->unk2];
        self->vertices[0].x.i.hi = target[0];
        self->vertices[0].y.i.hi = target[1];
        self->vertices[1].x.i.hi = target[2];
        self->vertices[1].y.i.hi = target[3];
        self->vertices[2].x.i.hi = target[4];
        self->vertices[2].y.i.hi = target[5];
        self->vertices[3].x.i.hi = target[6];
        self->state = 2;
        self->vertices[3].y.i.hi = target[7];
    }
    quad_is_on_screen(self);
}

struct Misc12Position {
    s16 x;
    s16 y;
};

extern union AnimationStep* stage_icon_animations[2];
extern struct Misc12Position stage_icon_positions[8];

void func_800CA228(struct MiscObj* self)
{
    s32 index;

    self->unk40 = D_801406A8[0] >> 7;
    self->animation_table = (u32**)stage_icon_animations;
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[0];
    index = self->unk2 & 0x7F;
    self->x_pos.val = index < 8 ? stage_icon_positions[index].x << 16 : 0;
    self->y_pos.val = index < 8 ? stage_icon_positions[index].y << 16 : 0;
    self->bg_offset = 0;
    self->unk15 = 0;
    if (self->unk2 < 0) {
        index = self->unk2 & 0x7F;
        self->unk42 = (index & 0xF) | (((index >> 4) | 0x1E0) << 6);
        self->unk16 = 0x12;
        set_animation_frame(ANIMATED_OBJECT(self), 1, index);
        self->state = 2;
    } else {
        self->unk42 = 0x780A;
        self->unk16 = 0x10;
        if ((u8)(self->unk2 - 8) < 2) {
            if (self->unk2 == 8) {
                self->x_pos.i.hi = 0x60;
                self->y_pos.i.hi = 0x180;
                self->state = 3;
            } else {
                self->x_pos.i.hi = 0x3C;
                self->y_pos.i.hi = 0x160;
                self->state = 4;
            }
            self->unk2 = 8;
        } else {
            self->state++;
        }
        set_animation_frame(ANIMATED_OBJECT(self), 0, self->unk2);
    }
    self->unk7 = 0;
}

void func_800CA40C(struct MiscObj* self)
{
    s32 index = self->unk2 & 0x7F;

    self->unk42 = (index & 0xF) | (((index >> 4) | 0x1E0) << 6);
    is_on_screen(BASE_OBJECT(self));
}

extern union AnimationStep* vent_animations[2];

void func_800CA86C(struct MiscObj* self)
{
    s32 animation;

    self->unk42 = 0x7881;
    self->unk40 = D_801406A8[4] >> 7;
    self->animation_table = (u32**)vent_animations;
    self->x_pos.val = 0x7C0000;
    self->y_pos.val = 0x1880000;
    self->bg_offset = 0;
    self->unk15 = 0;
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
    if (self->unk2 == 0) {
        set_animation(self, 0);
        self->unk16 = 2;
    } else {
        if (engine_obj.unk5F < 5)
            animation = 0;
        else if (engine_obj.unk5F < 7)
            animation = 1;
        else
            animation = 2;
        set_animation_frame(ANIMATED_OBJECT(self), 1, animation);
        self->unk16 = 1;
    }
    self->state++;
    is_on_screen(BASE_OBJECT(self));
}

extern u8 slash_beast_crescent_boxes[2][4];
extern s8 slash_beast_crescent_offsets[4];

void func_8009FF4C(struct ShotObj* self)
{
    self->state = 1;
    self->on_screen = 1;
    self->unk58.collision_data = D_80106070;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk42 &= 0x7FFF;
    if (self->unk15 == 0)
        self->x_pos.i.hi += slash_beast_crescent_offsets[self->unk2 * 2];
    else
        self->x_pos.i.hi -= slash_beast_crescent_offsets[self->unk2 * 2];
    self->y_pos.i.hi += slash_beast_crescent_offsets[self->unk2 * 2 + 1];
    if (self->unk2 == 0) {
        self->y_vel.val = 0;
        self->x_vel.val = self->unk15 != 0 ? 0x50000 : 0xFFFB0000;
    } else {
        self->y_vel.val = 0x38919;
        self->x_vel.val = self->unk15 != 0 ? 0x38919 : 0xFFFC76E7;
    }
    self->unk5C = 1;
    self->unk60 = 6;
    self->unk16 = 0;
    self->unk68 = NULL;
    self->unk54 = slash_beast_crescent_boxes[self->unk2];
    self->unk50.data = slash_beast_crescent_boxes[self->unk2];
    set_animation(self, self->unk2 + 0x1A);
}

extern struct Unk_unk68 D_801059BC;
extern struct Unk_unk68 D_801059C4[5];
extern void* general_animations[46];

void func_8008FBCC(struct MainObj* self)
{
    struct Main75Ext* ext = &self->ext.main_75;
    struct ShotObj* shot;

    if (ext->object.shot != NULL && ext->object.shot->active != 0)
        return;
    self->hp = 0;
    self->contact_damage = 5;
    self->invincibility_timer = 0;
    self->x_pos.i.hi = 0xE98;
    self->unk5++;
    self->y_pos.i.hi = 0x27B;
    self->unk40 = (D_801406A8[0] >> 7) + 0xB0;
    self->unk18.val = self->x_pos.val;
    self->unk16 = 5;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->terrain_box = NULL;
    self->unk1C.val = self->y_pos.val;
    self->collision_data = D_80107B78;
    self->contact_damage = 9;
    self->animation_table = (const u8* const*)general_animations;
    self->hurt_box = D_801059C4;
    self->attack_box = &D_801059BC;
    self->bg_offset = g_Player.bg_offset;
    self->unk15 = (g_Player.x_pos.val >= self->x_pos.val) << 6;
    set_animation(self, 0);
    memset(ext, 0, sizeof(*ext));
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x37;
        shot->unk2 = 1;
        shot->unk7C = (struct WeaponObj*)self;
        ext->object.shot = shot;
    }
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x37;
        shot->unk2 = 0;
        shot->unk7C = (struct WeaponObj*)self;
        ext->thruster = shot;
    }
    player_end_script_action();
}

extern s8 general_shot_boxes[3][4];
extern s8 general_shot_attack_boxes[3][4];
extern u8 D_8013B8DC[4];

void func_800AC8C4(struct ShotObj* self)
{
    struct MainObj* parent = (struct MainObj*)self->unk7C;
    s32 animation;

    self->state++;
    self->unk40 = parent->unk40;
    self->animation_table = (u32**)parent->animation_table;
    self->unk3C = (void*)parent->sprite_frames;
    self->unk42 = parent->unk42;
    self->unk15 = parent->unk15;
    self->bg_offset = parent->bg_offset;
    self->unk16 = parent->unk16;
    self->x_pos.val = parent->x_pos.val;
    self->unk58.data = NULL;
    self->unk50.data = NULL;
    self->unk54 = NULL;
    self->unk68 = NULL;
    self->unk75 = 0;
    self->y_pos.val = parent->y_pos.val;
    self->unk60 = 3;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    switch ((u8)self->unk2) {
    case 0:
        self->unk16 = 7;
        self->unk84.value = 0;
        self->timer = 0;
        animation = 2;
        break;
    case 1:
        self->unk16 = 7;
        animation = 0x27;
        break;
    case 2:
        self->unk16 = 5;
        self->timer = 0;
        self->unk8A = 0;
        if (self->unk15 != 0)
            self->x_pos.i.hi += 0x50;
        else
            self->x_pos.i.hi -= 0x50;
        self->unk75 = 1;
        self->unk50.data = (u8*)general_shot_boxes[1];
        self->unk54 = (u8*)general_shot_boxes[2];
        self->y_pos.i.hi -= 0x28;
        self->unk58.collision_bounds = D_801060F0;
        self->unk84.shot_55.x = self->x_pos.i.hi;
        self->unk84.shot_55.y = self->y_pos.i.hi;
        set_animation(self, 0xD);
        self->unk60 = 6;
        return;
    case 3:
        self->unk16 = 5;
        self->y_pos.i.hi -= 0x28;
        self->timer = 0;
        self->unk8A = 0;
        self->unk75 = 1;
        self->unk84.shot_55.x = self->x_pos.i.hi;
        self->unk84.shot_55.y = self->y_pos.i.hi;
        set_animation(self, 0x12);
        self->unk50.data = (u8*)general_shot_boxes[1];
        self->unk54 = (u8*)general_shot_boxes[2];
        self->unk58.collision_bounds = D_801060F0;
        self->unk60 = 6;
        return;
    case 4:
    case 5:
        self->unk50.data = (u8*)general_shot_attack_boxes[1];
        self->timer = 0x20;
        self->unk8A = 0;
        self->unk60 = 6;
        animation = self->unk2 == 4 ? 0x21 : 0x22;
        break;
    case 6:
        self->unk16 = 5;
        self->unk60 = 9;
        animation = 0x18;
        break;
    case 7:
        self->unk16 = 7;
        animation = 0x1B;
        break;
    case 8:
        self->unk42 &= 0x7FFF;
        animation = 0x26;
        break;
    case 9:
        D_8013B8DC[0] = 0;
        if (self->unk15 != 0)
            self->x_pos.i.hi += 0x1B;
        else
            self->x_pos.i.hi -= 0x1B;
        self->y_pos.i.hi -= 0x1A;
        animation = 0x1E;
        break;
    case 10:
    case 11:
        self->unk8A = self->timer != 0 ? 0xF : 0x1E;
        self->x_pos.i.hi += self->unk84.shot_55.x;
        self->y_pos.i.hi += self->unk84.shot_55.y;
        self->x_vel.val = self->unk15 != 0 ? 0x10000 : 0xFFFF0000;
        self->y_vel.val = self->unk2 == 10 ? 0x18000 : 0xFFFE8000;
        animation = 0x1F;
        break;
    default:
        return;
    }
    set_animation(self, animation);
}

extern struct Unk_unk68 D_80108404[];
extern struct Unk_unk68 D_80108384[];
extern struct Unk_unk68 D_801059C0;
extern void (*general_step_funcs[7])();

void func_80091218(struct MainObj* self)
{
    struct Main75Ext* ext = &self->ext.main_75;
    struct ShotObj* shot;
    s32 hit;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    CollisionRelated((struct PlayerObj*)self);
    self->collision_data = D_80108404;
    self->hurt_box = D_801059C4;
    func_8002DD04(self);
    if (ext->hit_active == 0)
        self->collision_data = D_80108384;
    self->hurt_box = &D_801059C0;
    hit = func_8002DD04(self);
    if (self->unk5 != 0)
        ext->saved_unk5 = self->unk5;
    if (ext->hit_active != 0) {
        if (!(ext->hit_timer & 1))
            self->unk42 |= 0x8000;
        else
            self->unk42 &= 0x7FFF;
        if (--ext->hit_timer == 0)
            ext->hit_active = 0;
    } else if (hit < 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
        self->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
        return;
    } else if (hit != 0) {
        s32 spawn = 0;
        s32 flash = 1;

        if (engine_obj.cur_character == 0) {
            if (hit == 0x12 || hit == 9)
                spawn = 1;
            else if (hit == 0x7F)
                flash = 0;
        } else if (hit == 0x1E) {
            spawn = 1;
        } else if (hit < 0x1F) {
            if (hit < 0x1A && hit >= 0x18)
                flash = 0;
        } else if (hit == 0x7F) {
            flash = 0;
        }
        if (spawn) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x37;
                shot->unk2 = 8;
                shot->unk7C = (struct WeaponObj*)self;
            }
        }
        if (flash) {
            self->collision_data = D_801060F0;
            ext->hit_timer = 0x40;
            ext->hit_active = 1;
        }
    }
    general_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

extern void* general_scripts[2];
extern u8 general_script_weights[4];
u8 general_at_position(struct ObjectHeader*, s16, s16);
void general_pick_script(struct MainObj* arg0);

void func_8009027C(struct MainObj* self)
{
    struct Main75Ext* ext = &self->ext.main_75;
    u8 next;

    switch (self->unk6) {
    case 0:
        self->unk6 = 1;
        set_animation(self, 8);
        if (self->y_pos.i.hi >= 0x24B) {
            set_animation(ext->thruster, 5);
            func_8001540C(2, 1, self);
        } else {
            set_animation(ext->thruster, 6);
            func_8001540C(2, 2, self);
        }
        ext->thruster->unk84.shot_55.x = self->unk15 != 0 ? -0x18 : 0x18;
        ext->thruster->unk84.shot_55.y = 4;
        break;
    case 1:
        set_velocity_from_angle(MOVING_OBJECT(self),
            (u8)angle_to_point(OBJECT_HEADER(self),
                self->unk15 != 0 ? 0xD7E0000 : 0xEC50000, 0x24B0000));
        animate_object(ANIMATED_OBJECT(self));
        move_object(MOVING_OBJECT(self));
        if (general_at_position(OBJECT_HEADER(self), self->unk15 != 0 ? 0xD7E : 0xEC5, 0x24B)) {
            self->unk7C = 0x3C;
            self->x_speed = 0;
            self->y_speed = 0;
            self->unk6++;
            set_animation(ext->thruster, 7);
            stop_sound(2, 2);
        }
        break;
    case 2:
        animate_object(ANIMATED_OBJECT(self));
        if (--self->unk7C != 0)
            break;
        if (ext->script == NULL || *ext->script == 0xFF)
            general_pick_script(self);
        next = *ext->script;
        self->unk6 = 0;
        self->unk7 = 0;
        ext->script++;
        self->unk5 = next;
        break;
    }
}

void func_800905D4(struct MainObj* self)
{
    s32 dx;
    s32 turned;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->ext.main_75.random_index == 0 && self->y_pos.i.hi + 0x30 < g_Player.y_pos.i.hi) {
        dx = self->x_pos.i.hi - g_Player.x_pos.i.hi;
        if (dx < 0)
            dx = -dx;
        if (dx < 8) {
            self->unk5 = 6;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk7C = 0x1E;
            return;
        }
    }
    if (!(self->collision_flags & 3))
        return;
    turned = self->unk15 != 0 ? self->collision_flags & 1 : self->collision_flags & 2;
    if (turned) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
        self->x_speed = 0;
        self->y_speed = 0;
        self->unk15 ^= 0x40;
    }
}

extern u8 D_8013B8C8[4];
extern u8 D_8013B8CC[4];
extern u8 D_8013B8D0[0xC];
extern s8 general_ring_offsets[4];

void func_800ACDE4(struct ShotObj* self)
{
    s16 player_y;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step != 0)
        return;
    self->unk5++;
    self->x_vel.val = self->unk15 != 0 ? 0x40000 : 0xFFFC0000;
    set_animation(self, 0x14);
    func_8001540C(2, 5, self);
    player_y = g_Player.y_pos.i.hi;
    if (player_y < 0x210)
        self->timer = 0;
    else if (player_y < 0x240)
        self->timer = 1;
    else if (player_y < 0x270)
        self->timer = 2;
    else
        self->timer = 3;
}

void func_800ACF60(struct ShotObj* self)
{
    s16 probe_x;
    u8 tile;

    self->unk68 = (struct Unk_unk68*)general_shot_boxes;
    probe_x = self->unk15 != 0 ? self->x_pos.i.hi + 0x59 : self->x_pos.i.hi - 0x59;
    *(s16*)D_8013B8C8 = probe_x;
    *(s16*)D_8013B8CC = self->y_pos.i.hi;
    tile = func_8002D724(PLAYER_OBJECT(self), probe_x, self->y_pos.i.hi);
    D_8013B8D0[0] = tile;
    if (tile == 0x38) {
        self->x_vel.val = 0;
        self->unk90.i.lo = 0x3C;
        self->unk5++;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void func_800AD338(struct ShotObj* self)
{
    self->unk68 = NULL;
    set_velocity_from_angle(MOVING_OBJECT(self),
        (u8)angle_to_point(OBJECT_HEADER(self), self->unk84.shot_55.x << 16,
            self->unk84.shot_55.y << 16));
    self->x_vel.val <<= 2;
    self->y_vel.val <<= 2;
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (sigma_final_shot_at_position(self, self->unk84.shot_55.x, self->unk84.shot_55.y) & 0xFF) {
        self->unk5++;
        set_animation(self, self->unk2 == 3 ? 0x13 : 0xE);
        func_8001540C(2, 6, self);
    }
}

void func_800AD6DC(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->unk42 = self->unk7C->unk42;
    if (--self->timer != 0)
        return;
    self->unk5++;
    if (self->unk15 != 0)
        self->x_pos.i.hi -= general_ring_offsets[(self->unk2 - 4) * 2];
    else
        self->x_pos.i.hi += general_ring_offsets[(self->unk2 - 4) * 2];
    self->y_pos.i.hi += general_ring_offsets[(self->unk2 - 4) * 2 + 1];
    set_animation(self, 0x23);
    set_velocity_from_angle(MOVING_OBJECT(self),
        (u8)angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)));
    self->x_vel.val *= 3;
    self->y_vel.val *= 3;
    self->unk42 &= 0x7FFF;
    func_8001540C(2, 7, self);
}

void func_80085A44(struct MainObj* self)
{
    struct Main68Ext* ext = &self->ext.main_68;
    struct VisualObj* visual;
    struct ShotObj* shot;
    u8 i;

    if (main_bss_state.frame_counter == (main_bss_state.frame_counter / 3) * 3) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x20;
            visual->unk2 = 5;
            visual->unk50 = PLAYER_OBJECT(self);
        }
    }
    if (--self->unk7C == 0) {
        self->unk5++;
        ext->scythe->state++;
        for (i = 0; i < 0x14; i++) {
            visual = find_free_visual_obj();
            if (visual == NULL)
                continue;
            visual->active = 0x41;
            visual->id = 0x20;
            visual->unk2 = 1;
            visual->unk54 = get_random() & 3;
            visual->unk50 = PLAYER_OBJECT(self);
            ext->count++;
        }
        set_animation(self, 0xE);
        self->unk15 = (self->x_pos.i.hi < g_Player.x_pos.i.hi) << 6;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x2E;
            shot->unk2 = 9;
            ext->scythe = (struct MainObj*)shot;
            shot->unk7C = (struct WeaponObj*)self;
        }
    }
    self->on_screen = 0;
    if (self->unk7C & 1)
        is_on_screen(BASE_OBJECT(self));
}

extern void (*sigma_step_funcs[9])();
extern void (*sigma_cloak_step_funcs[5])();
extern struct Unk_unk68 D_80107F84[];

static void main68_hit_flicker(struct MainObj* self, const void* idle_collision)
{
    if (self->ext.main_68.flash_timer != 0) {
        if (--self->ext.main_68.flash_timer & 1)
            self->unk42 |= 0x8000;
        else
            self->unk42 &= 0x7FFF;
    } else {
        self->collision_data = idle_collision;
    }
}

static void main68_start_hit_flicker(struct MainObj* self)
{
    if (self->ext.main_68.flash_timer == 0) {
        self->collision_data = D_801060F0;
        self->ext.main_68.flash_timer = 0x40;
    }
}

void func_8008502C(struct MainObj* self)
{
    struct VisualObj* visual;
    s32 hit = func_8002DD04(self);
    s32 spawn = 0;
    s32 flash = 1;

    main68_hit_flicker(self, D_80108004);
    if (hit < 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
        return;
    }
    if (hit != 0) {
        if (engine_obj.cur_character == 0) {
            if (hit == 0xB || hit == 2)
                spawn = 1;
            else if (hit == 0x7F)
                flash = 0;
        } else if (hit == 0x25) {
            spawn = 1;
        } else if (hit < 0x26) {
            if (hit < 0x1A && hit >= 0x18)
                flash = 0;
        } else if (hit == 0x7F) {
            flash = 0;
        }
        if (spawn) {
            visual = find_free_visual_obj();
            if (visual != NULL) {
                visual->active = 0x41;
                visual->id = 0x20;
                visual->unk2 = 6;
                visual->unk50 = PLAYER_OBJECT(self);
            }
        }
        if (flash)
            main68_start_hit_flicker(self);
    }
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    sigma_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    CollisionRelated((struct PlayerObj*)self);
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void func_800A9544(struct ShotObj* self)
{
    struct WeaponObj* owner = self->unk7C;
    u8* angle = (u8*)&self->pad94;
    u8* delay = (u8*)&self->pad96[0];

    if (--*delay == 0) {
        if (self->unk15 != 0)
            *angle = (*angle - 1) & 0xF;
        else
            *angle = (*angle + 1) & 0xF;
        *delay = 6;
    }
    self->unk90.i.lo = 0x40;
    self->unk90.i.hi = 0x40;
    func_80021DBC(&self->unk90.i.lo, &self->unk90.i.hi, *angle);
    self->x_pos.i.hi = owner->x_pos.i.hi + (self->unk15 != 0 ? self->unk90.i.lo + 0x30 : self->unk90.i.lo - 0x30);
    self->y_pos.i.hi = owner->y_pos.i.hi + self->unk90.i.hi + 0x30;
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (*angle == 6)
        self->state = 2;
    if (self->unk7C->state == 2)
        self->state = 2;
}

extern u8 sigma_shot_debris[20];

void func_800A8E50(struct ShotObj* self)
{
    s32 x_speed;
    s32 y_speed;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    set_velocity_from_angle(MOVING_OBJECT(self), (u8)self->pad94);
    self->x_vel.val *= 6;
    self->y_vel.val *= 6;
    if (self->unk70 & 3) {
        self->unk5++;
        start_screen_shake_x(0x14, 4, 2);
        set_animation(self, 0x1F);
        self->timer = 0x18;
        self->unk15 = ((self->unk70 & 2) == 0) << 6;
        self->unk95 = 3;
        x_speed = self->unk15 != 0 ? 0xFFED0000 : 0x130000;
        y_speed = 0xFFEA0000;
    } else if (self->unk70 & 8) {
        self->unk5++;
        self->unk15 ^= 0x40;
        start_screen_shake_y(0x14, 4, 2);
        set_animation(self, 0x20);
        self->timer = 0x24;
        self->unk95 = 4;
        x_speed = self->unk15 != 0 ? 0xFFF10000 : 0xF0000;
        y_speed = 0;
    } else {
        return;
    }
    spawn_debris_offset(6, sigma_shot_debris, (struct MiscObj*)self, x_speed, y_speed);
    stop_sound(2, 5);
    func_8001540C(2, 6, self);
}

extern struct Unk_unk68 D_80103F00;
extern struct Unk_unk68 D_80103F04;
extern struct Unk_unk68 D_80103F08;
extern struct Unk_unk68 D_80103F0C;

void func_80084B14(struct MainObj* self)
{
    switch (self->unk7) {
    case 0:
        self->unk7++;
        set_animation(self, 0x11);
        func_8001540C(2, 0, self);
        /* fallthrough */
    case 1:
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step != 0)
            return;
        self->unk7++;
        self->y_speed = 0x60000;
        self->gravity = 0x4200;
        self->attack_box = &D_80103F08;
        self->x_speed = self->unk15 != 0 ? 0xFFFD8000 : 0x28000;
        self->x_accel = 0;
        self->hurt_box = &D_80103F0C;
        set_animation(self, 0x12);
        break;
    case 2:
        animate_object(ANIMATED_OBJECT(self));
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->y_speed >= 0)
            return;
        self->y_speed = 0;
        self->unk7++;
        set_animation(self, 0x13);
        break;
    case 3:
        animate_object(ANIMATED_OBJECT(self));
        move_with_gravity(ANIMATED_OBJECT(self));
        if (!(self->collision_flags & 8))
            return;
        self->attack_box = &D_80103F00;
        self->hurt_box = &D_80103F04;
        self->unk7++;
        set_animation(self, 0x14);
        func_8001540C(2, 1, self);
        break;
    case 4:
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step != 0)
            return;
        self->unk7 = 0;
        self->unk6++;
        set_animation(self, 0x1C);
        break;
    }
}

extern s16 D_8010442C[16];

void func_80085460(struct MainObj* self)
{
    u8 kind;
    s16 x;
    s16 y;

    engine_obj.unk1C = 0;
    self->on_screen = 0;
    if (self->unk7C == 0) {
        apply_tile_effect(6, 0x430, 0x1C0);
        self->unk5++;
        return;
    }
    if ((u8)get_random() % 7 == 0) {
        kind = ((u8)main_bss_state.frame_counter ^ 1) & 1;
        x = D_8010442C[(get_random() & 7) * 2] + 0x470;
        y = D_8010442C[(get_random() & 7) * 2 + 1] + 0x1E0;
        spawn_explosion_at(0, x, y, kind);
    }
    self->unk7C--;
}

extern union AnimationStep* menu_text_animations[];

void func_800D3388(struct MiscObj* self)
{
    s32 resource;
    s32 column;
    s32 row;

    self->x_pos.i.hi = background_objects[0].x_pos.i.hi + (get_random() & 0xFF) + 0x30;
    self->y_pos.i.hi = background_objects[0].y_pos.i.hi - 0x10;
    resource = func_8002938C(0xA4);
    self->animation_table = (u32**)menu_text_animations;
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    column = func_8002938C(0xA4) * 4 + 0x18;
    row = func_8002938C(0xA4) + 6;
    self->unk42 = (column % 16) | ((row / 4 + 0x1E0) << 6);
    self->bg_offset = 0;
    self->unk15 = 0;
    self->unk16 = 0x10;
    set_animation_frame(ANIMATED_OBJECT(self), 0, self->unk2);
    self->y_vel.val = 0xFFFE0000;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0x4200;
    self->state++;
}

extern s8 sigma_head_boxes[3][4];

void func_800AAC98(struct ShotObj* self)
{
    struct MainObj* parent = (struct MainObj*)self->unk7C;

    self->unk40 = parent->unk40;
    self->animation_table = (u32**)parent->animation_table;
    self->unk3C = (void*)parent->sprite_frames;
    self->unk75 = 1;
    self->unk15 = 0;
    self->unk42 = (self->unk2 + parent->unk42 + 4) & 0x7FFF;
    self->x_pos.i.hi = 0;
    self->y_pos.i.hi = 0;
    self->unk16 = 0;
    self->unk50.data = NULL;
    self->state++;
    self->unk5 = 3;
    self->unk58.animation_steps = D_80105FF0;
    self->unk54 = (u8*)sigma_head_boxes;
    self->unk5C = 0x30;
    self->unk60 = 9;
    self->bg_offset = parent->bg_offset;
}

void func_800AB050(struct ShotObj* self)
{
    struct Main74Ext* owner = &((struct MainObj*)self->unk7C)->ext.main_74;
    u8 phase;
    u8 slot;

    if (self->unk7 != 0) {
        self->unk7--;
        return;
    }
    if (self->unk8C.bytes[0] == 0) {
        if (owner->unk8C == 1)
            self->unk5 = 2;
        return;
    }
    phase = owner->unk8C;
    if (phase == 3) {
        self->unk5 = 7;
        return;
    }
    slot = self->unk8C.bytes[2];
    if (phase == 2 && slot == (u8)self->unk2) {
        if (slot == 0)
            self->unk5 = 4;
        else if (slot == 1)
            self->unk5 = 5;
        else if (slot == 2)
            self->unk5 = 6;
    }
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
}

void func_800AB170(struct ShotObj* self)
{
    s16 y;
    s16 player_y;
    s32 dy;

    if (--self->timer == 0) {
        self->timer = 1;
        self->unk6++;
    }
    y = self->y_pos.i.hi;
    player_y = g_Player.y_pos.i.hi;
    dy = y - player_y;
    if (dy < 0)
        dy = -dy;
    if (dy < 4)
        self->y_pos.i.hi = player_y;
    else
        self->y_pos.i.hi = y < player_y ? y + 3 : y - 3;
    animate_object(ANIMATED_OBJECT(self));
}

extern u8 D_8013B898[4];
extern u8 D_8013B89C[4];
extern u8 D_8013B8A4[4];
extern void* D_8013B8B4;
extern void (*sigma_final_step_funcs[14])();
extern struct Unk_unk68 D_80108284[];
extern struct Unk_unk68 D_80108304[];

void func_8008F1A8(struct MainObj* self)
{
    struct Main74Ext* ext = &self->ext.main_74;
    s32 hit;
    u8 flash;

    sigma_final_step_funcs[self->unk5](self);
    if (ext->target == 0)
        goto done;
    self->unk65 = D_8013B89C[0];
    self->collision_data = D_801060F0;
    self->hurt_box = D_8013B8B4;
    func_8002DD04(self);
    D_8013B89C[0] = self->unk65;
    if (D_8013B8A4[0] == 0)
        self->collision_data = ext->target == 1 ? D_80108284 : D_80108304;
    self->unk65 = D_8013B898[0];
    self->hurt_box = D_8013B8B0;
    hit = func_8002DD04(self);
    D_8013B898[0] = self->unk65;
    if (hit < 0) {
        stop_sound(2, 1);
        self->unk5 = 0;
        self->unk6 = 0;
        self->unk62 = 0;
        self->state++;
        self->unk42 &= 0x7FFF;
        if (D_8013B8B8[0] != 0) {
            ext->death_kind = 2;
            player_start_script_action(0x14, g_Player.unk15);
            g_Player.spike_immune = 1;
            engine_obj.unk1C = 1;
        } else {
            ext->death_kind = 1;
        }
        return;
    }
    if (hit > 0 && hit != 0x7F) {
        D_8013B8A4[0] = (u32)(hit - 0x19) < 2 ? 2 : 0x1E;
        self->collision_data = D_801060F0;
    }
    flash = D_8013B8A4[0];
    if (flash != 0) {
        D_8013B8A4[0] = flash - 1;
        if (flash & 2)
            self->unk42 |= 0x8000;
        else
            self->unk42 &= 0x7FFF;
        if (D_8013B8A4[0] == 0) {
            self->unk42 &= 0x7FFF;
            self->collision_data = ext->target == 1 ? D_80108284 : D_80108304;
        }
    }
done:
    func_8002D9BC(self);
}

void func_8008DAE8(struct MainObj* self)
{
    struct Main74Ext* ext = &self->ext.main_74;

    if (D_8013B8A0[0] != 0) {
        D_8013B8A0[0]--;
        if (ext->target != 0)
            goto animate;
    }
    switch (ext->pattern_index) {
    case 0:
        self->unk5 = 5;
        ext->pattern_index++;
        break;
    case 1:
    case 5:
        self->unk5 = 8;
        ext->pattern_index++;
        break;
    case 2:
        if (D_8013B8B8[0] == 2) {
            ext->pattern_index = 6;
            self->unk5 = 4;
        } else {
            self->unk5 = 6;
        }
        ext->pattern_index++;
        break;
    case 3:
        self->unk5 = (get_random() & 1) ? 0xC : 0xD;
        ext->pattern_index++;
        break;
    case 4:
        self->unk5 = 7;
        ext->pattern_index++;
        break;
    case 6:
        if (D_8013B8B8[0] == 1) {
            ext->pattern_index = 2;
            self->unk5 = 6;
        } else {
            self->unk5 = 4;
        }
        ext->pattern_index++;
        break;
    case 7:
        self->unk5 = (get_random() & 1) ? 9 : 0xA;
        ext->pattern_index = 0;
        break;
    }
    if (ext->target == 0)
        return;
animate:
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void func_800BE364(struct EffectObj* self)
{
    struct Main73PartsExt* owner = &self->ext.effect_42.owner.main->ext.main_73_parts;
    u32 ready = 0;
    u32 matched = 0;
    u32 i;

    for (i = 0; i < 3; i++) {
        if (owner->parts[i]->unk5 == 3)
            ready++;
    }
    if (ready != 3)
        return;
    for (i = 0; i < 3; i++) {
        if (owner->parts[i]->unk2 == owner->object_id)
            matched = 1;
    }
    if (matched) {
        owner->effect_state = 2;
        self->unk5++;
    } else {
        owner->effect_state = 3;
        self->ext.effect_42.timer = 0xC8;
        self->unk5 += 2;
    }
}

extern u8 sigma_final_shot_box_0[4];
extern u8 sigma_final_shot_box_1[4];
extern u8 sigma_final_shot_box_2[4];
extern u8 sigma_final_shot_tall_box[4];
extern u8 sigma_final_shot_wide_box[4];
extern u8 sigma_final_shot_terrain_box_0[4];
extern u8 sigma_final_shot_terrain_box_1[4];
extern s16 sigma_final_shot_offsets[4];

void func_800ABE08(struct ShotObj* self)
{
    struct MainObj* parent = (struct MainObj*)self->unk7C;
    u8 odd;

    self->unk40 = parent->unk40;
    self->animation_table = (u32**)parent->animation_table;
    self->unk58.collision_data = D_80106070;
    self->unk54 = NULL;
    self->unk3C = (void*)parent->sprite_frames;
    switch ((u8)self->unk2) {
    case 0:
        self->unk42 = (parent->unk42 + 7) & 0x7FFF;
        set_animation(self, 0xD);
        self->unk5 = 2;
        self->x_vel.val = 0x40000;
        self->timer = 0x19;
        self->unk50.data = sigma_final_shot_box_0;
        self->unk15 = 0x40;
        self->unk68 = NULL;
        self->y_pos.i.hi += 0x10;
        self->x_pos.i.hi += 0x18;
        self->unk5C = 1;
        self->unk60 = 6;
        self->y_vel.val = sigma_final_shot_offsets[self->unk7] << 16;
        break;
    case 1:
        self->timer = 0x14;
        self->unk42 = (parent->unk42 + 2) & 0x7FFF;
        set_animation(self, 0xE);
        self->unk5 = 3;
        self->unk50.data = sigma_final_shot_box_1;
        self->unk68 = (struct Unk_unk68*)sigma_final_shot_terrain_box_0;
        self->unk5C = 1;
        self->unk15 = 0;
        self->unk60 = 6;
        break;
    case 2:
        set_animation(self, 0x10);
        self->unk5 = 4;
        self->x_vel.val = 0xFFFD0000;
        self->y_vel.val = 0x10000;
        self->unk2C = 0x8000;
        self->unk50.data = sigma_final_shot_box_2;
        self->unk68 = (struct Unk_unk68*)sigma_final_shot_terrain_box_1;
        self->unk5C = 1;
        self->unk60 = 9;
        self->unk28 = 0;
        self->unk70 = 0;
        self->unk42 = (parent->unk42 + 3) & 0x7FFF;
        self->x_pos.i.hi -= 0x18;
        self->y_pos.i.hi += 0x10;
        break;
    case 3:
    case 4:
    case 5:
    case 6:
        odd = self->unk2 & 1;
        if (self->unk2 <= 4) {
            set_animation(self, 0x13);
            self->x_vel.val = odd ? 0x40000 : 0xFFFC0000;
            self->y_vel.val = 0;
            self->unk50.data = sigma_final_shot_wide_box;
        } else {
            set_animation(self, 0x12);
            self->x_vel.val = 0;
            self->y_vel.val = odd ? 0x40000 : 0xFFFC0000;
            self->unk50.data = sigma_final_shot_tall_box;
        }
        self->unk15 = (odd == 0) << 6;
        self->unk5 = 6;
        self->unk5C = 1;
        self->unk60 = 6;
        self->unk42 = (parent->unk42 + 2) & 0x7FFF;
        break;
    case 7:
        set_animation(self, 0x14);
        self->unk15 = 0x40;
        self->unk5 = 5;
        self->unk5C = 1;
        self->unk60 = 0x18;
        self->unk50.data = NULL;
        self->timer = 0x3C;
        self->unk42 = (parent->unk42 + 4) & 0x7FFF;
        break;
    }
    self->state = 1;
    self->unk16 = 0;
    self->bg_offset = parent->bg_offset;
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
}

s32 sigma_spawn_sequencer(struct MainObj* arg0, s8 arg1);

void func_8008EC48(struct MainObj* self)
{
    struct ShotObj* shot;
    s16 y = 0x228;
    u32 i;

    sigma_spawn_sequencer(self, 6);
    set_animation(self, 2);
    self->unk7C = 0x3C;
    for (i = 0; i < 0xC; i++, y += 0x10) {
        shot = find_free_shot_obj();
        if (shot == NULL)
            continue;
        shot->active = 0x41;
        shot->id = 0x36;
        shot->unk2 = 7;
        shot->x_pos.i.hi = 0x5A0;
        shot->y_pos.i.hi = y;
        shot->unk7C = (struct WeaponObj*)self;
    }
    self->unk6++;
}

void func_800D3084(struct MiscObj* self)
{
    struct MainObj* owner = (struct MainObj*)self->ext.misc_55.owner;
    s32 animation;

    self->x_pos.val = owner->x_pos.val;
    self->y_pos.val = owner->y_pos.val;
    self->unk40 = owner->unk40;
    self->unk42 = owner->unk42 & 0x7FFF;
    self->animation_table = (u32**)owner->animation_table;
    self->unk3C = (void*)owner->sprite_frames;
    self->unk15 = 0;
    self->bg_offset = owner->bg_offset;
    switch (self->unk2) {
    case 0:
        self->x_pos.i.hi = 0x4FF;
        self->y_pos.i.hi = 0x279;
        animation = 0x26;
        self->state = 1;
        break;
    case 1:
        self->x_pos.i.hi = 0x4FD;
        self->y_pos.i.hi = 0x259;
        animation = 0x26;
        self->state = 1;
        break;
    case 2:
        self->x_pos.i.hi = background_objects[0].x_pos.i.hi - 0x20;
        self->y_pos.i.hi = background_objects[0].y_pos.i.hi + (get_random() & 0xFF);
        self->x_vel.val = 0x30000;
        self->unk28 = -0x1000;
        self->state = 3;
        self->y_vel.val = 0;
        self->unk2C = 0;
        self->unk42 += 3;
        animation = 0x16;
        break;
    default:
        animation = 0xF;
        self->state = 4;
        break;
    }
    set_animation(self, animation);
    self->unk16 = 0x13;
    is_on_screen(BASE_OBJECT(self));
}

s32 player_zero_check_ryuenjin(struct PlayerObj*);
void player_zero_rakuhouha(struct PlayerObj*);
void player_zero_raijingeki(struct PlayerObj*);
void player_reset_palette(struct PlayerObj*);
extern u8 player_zero_combo_sounds[4][2];

s32 func_8003A1DC(struct PlayerObj* arg0)
{
    s8 combo;

    if (arg0->input_locked != 0) {
        return 0;
    }
    if (!(arg0->animation_step.fields.event & 0x20)) {
        return 0;
    }
    if (arg0->pressed_input & 0x10) {
        combo = arg0->combo + 1;
        arg0->combo = combo;
        player_set_animation(arg0, combo + 0x58);
        func_8001540C(1, player_zero_combo_sounds[arg0->combo][0], arg0);
        player_play_voice(arg0, player_zero_combo_sounds[arg0->combo][1]);
        player_zero_spawn_saber(arg0, (s8)(arg0->combo + 0x18));
        return 1;
    }
    arg0->attacking = 0;
    if (player_zero_check_ryuenjin(arg0) != 0) {
        return 1;
    }
    arg0->attacking = 1;
    if (!(arg0->boss_flags & 1) || !(arg0->pressed_input & 0x20)) {
        return 0;
    }
    player_set_animation(arg0, 0x60);
    arg0->combo = 1;
    arg0->unk5 = 0x35;
    arg0->unk6 = 0;
    player_zero_raijingeki(arg0);
    return 1;
}

extern u8 zero_saber_animations[24];

void func_80097FC4(struct WeaponObj* weapon, struct PlayerObj* player)
{
    u8 animation;
    u8 palette;
    s32 index;

    weapon->on_screen = 1;
    if (weapon->id == 0x21) {
        weapon->active = 0x21;
        weapon->unk40 = 0;
        weapon->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 6);
    } else {
        weapon->unk40 = player->unk40;
        weapon->unk3C = player->unk3C;
    }
    weapon->unk42 = 0x7801;
    weapon->unk16 = 2;
    weapon->animation_table = player->animation_table;
    index = (weapon->id - 0x18) * 2;
    animation = zero_saber_animations[index];
    palette = zero_saber_animations[index + 1];
    if (palette == 3 && ((u8)player->boss_flags & 0x40)) {
        palette = 4;
    }
    if (weapon->id == 0x20 && weapon->unk2 != 0) {
        animation = 0x78;
    }
    if (weapon->id == 0x1C) {
        set_animation_frame(ANIMATED_OBJECT(weapon), 0x74, (u8)player->animation_step.fields.event & 0x1F);
        weapon->animation_step.fields.duration = player->animation_step.fields.duration;
    } else {
        set_animation(weapon, animation);
    }
    player_copy_palette(player, palette, 1);
    need_palette_load |= 1;
    weapon->state++;
}

void func_80080834(struct MainObj* self)
{
    struct Main66Ext* ext = &self->ext.main_66;
    struct MiscObj* misc;
    struct ShotObj* shot;
    s32 hit;
    s32 first = 0;
    s32 value;
    s8 i;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    if (ext->active != 0 && self->unk5 == 3) {
        if (--ext->hover_timer == 0) {
            self->y_speed = -0x20000;
            self->x_speed = 0;
            set_animation(self, 2);
            self->collision_data = D_80107E84;
            self->unk5 = 4;
            self->unk6 = 0;
        } else if (ext->crystal_released == 0 && g_Player.hp < 8) {
            set_animation(self, 0x20);
            self->collision_data = D_80107E84;
            self->unk5 = 5;
            self->unk6 = 0;
        }
    }
    iris_step_funcs[self->unk5](self);
    if (ext->active == 0) {
        update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
        return;
    }
    if (self->unk2 == 0) {
        self->hp = 0x7F;
        hit = func_8002DD04(self);
        self->hp = 0x30;
    } else {
        hit = func_8002DD04(self);
    }
    if (ext->flash_timer != 0) {
        if (ext->blink_timer != 0) {
            if (--ext->blink_timer & 1) {
                self->unk42 |= 0x8000;
                ext->partner->unk42 |= 0x8000;
            } else {
                self->unk42 &= 0x7FFF;
                ext->partner->unk42 &= 0x7FFF;
            }
        }
        if (--ext->flash_timer == 0) {
            if (ext->crystal_released != 0) {
                ext->partner->unk42 &= 0x7FFF;
            }
            if (self->unk2 != 0) {
                self->collision_data = D_80107E84;
            }
            self->invincibility_timer = 0;
            self->unk42 &= 0x7FFF;
        }
    }
    if (hit < 0) {
        stop_sound(2, 0xE1);
        g_Player.spike_immune = 1;
        self->state = 2;
        self->unk5 = 0;
        ext->partner->state = 3;
        ext->partner->unk5 = 0;
        return;
    }
    if (hit != 0 && hit != 0x7F) {
        if (self->unk2 == 0) {
            ext->flash_timer = 0x18;
            self->invincibility_timer = 1;
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 0x41;
                misc->id = 0x16;
                misc->unk2 = 8;
                misc->bg_offset = self->bg_offset;
                misc->animation_table = (u32**)self->animation_table;
                misc->unk40 = self->unk40;
                misc->unk3C = (void*)self->sprite_frames;
                misc->ext.unk.unk50 = (void*)self;
                misc->unk42 = self->unk42 & 0x7FFF;
                set_animation(misc, 0x22);
                misc->ext.unk.unk56.byte = 0x12;
                misc->unk5 = 0;
                misc->unk6 = 1;
            }
            if (self->unk5 != 4) {
                for (i = 0; i < 2; i++) {
                    if ((s8)ext->drone_count == 0x10) {
                        continue;
                    }
                    ext->drone_count++;
                    shot = find_free_shot_obj();
                    if (shot == NULL) {
                        continue;
                    }
                    shot->active = 0x41;
                    shot->id = 0x2C;
                    shot->unk2 = i;
                    if (i == 0) {
                        first = (get_random() & 0xFF) % 9;
                        shot->unk84.value = first;
                    } else {
                        do {
                            value = (get_random() & 0xFF) % 9;
                            shot->unk84.value = value;
                        } while (first == value);
                    }
                    if (self->unk15 != 0) {
                        shot->unk84.value += 8;
                    }
                    shot->x_pos.val = self->x_pos.val;
                    shot->unk67 = 0;
                    shot->y_pos.val = self->y_pos.val;
                    shot->bg_offset = self->bg_offset;
                    shot->animation_table = (u32**)self->animation_table;
                    shot->unk40 = self->unk40;
                    shot->unk3C = (void*)self->sprite_frames;
                    shot->unk42 = self->unk42 & 0x7FFF;
                    shot->unk7C = WEAPON_OBJECT(self);
                    shot->state = 0;
                    shot->unk15 = self->unk15;
                }
            }
        } else {
            ext->flash_timer = 0x18;
            ext->blink_timer = 0x18;
            self->collision_data = D_801060F0;
        }
    }
    if (self->unk2 == 0) {
        self->unk42 &= 0x7FFF;
    } else {
        ext->partner->unk42 = self->unk42;
    }
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

void func_800CF950(struct MiscObj* self)
{
    struct MiscObj* piece;
    s32 i;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 0) {
        return;
    }
    set_animation(self, 0x10);
    set_animation(((struct MainObj*)self->ext.misc_39.related), 0x24);
    func_8001540C(2, 0xDE, ((struct MainObj*)self->ext.misc_39.related));
    ((struct MainObj*)self->ext.misc_39.related)->unk6 = 8;
    for (i = 0; i < 5; i++) {
        piece = find_free_misc_obj();
        if (piece == NULL) {
            continue;
        }
        piece->active = 0x41;
        piece->id = 0x16;
        piece->unk2 = 8;
        switch (i) {
        case 0:
        case 2:
            piece->unk16 = 0x21;
            break;
        case 1:
        case 3:
            piece->unk16 = 0;
            break;
        case 4:
            piece->unk16 = 0x20;
            break;
        }
        piece->x_pos.val = self->x_pos.val + 0x10000;
        piece->y_pos.val = self->y_pos.val + 0x400000;
        piece->bg_offset = self->bg_offset;
        piece->animation_table = self->animation_table;
        piece->unk40 = self->unk40;
        piece->unk3C = self->unk3C;
        piece->ext.unk.unk56.byte = 0x30;
        piece->unk42 = self->unk42 & 0x7FFF;
        set_animation(piece, i + 0x12);
        piece->unk5 = 0;
        piece->unk6 = 0;
    }
    self->ext.misc_39.timer = 0x88;
    self->unk5 = 4;
}

void iris_face_player(struct MainObj*);

void func_80081718(struct MainObj* self)
{
    s32 saved_y = g_Player.y_pos.val;
    s32 direction;
    s32 dx;
    s32 dy;

    if (g_Player.y_pos.i.hi < 0x150) {
        g_Player.y_pos.i.hi = 0x150;
    }
    direction = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF;
    g_Player.y_pos.val = saved_y;
    set_velocity_from_angle(MOVING_OBJECT(self), direction);
    self->x_speed += self->x_speed >> 16;
    self->y_speed += self->y_speed >> 16;
    dx = self->x_pos.i.hi - g_Player.x_pos.i.hi;
    dy = self->y_pos.i.hi - g_Player.y_pos.i.hi;
    if ((dx >= 0 ? dx : -dx) >= 3 || (dy >= 0 ? dy : -dy) >= 3) {
        iris_face_player(self);
        move_object(MOVING_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
}

extern u8 iris_drone_attack_box[4];
extern u8 iris_drone_hurt_box[4];

void func_800A7008(struct ShotObj* self)
{
    self->on_screen = 1;
    self->unk58.data = (u8*)D_80105FF0;
    self->unk61 = 1;
    self->unk42 &= 0x7FFF;
    set_velocity_from_angle(MOVING_OBJECT(self), self->unk84.bytes[0]);
    self->unk16 = 2;
    self->unk54 = iris_drone_hurt_box;
    self->unk50.data = iris_drone_attack_box;
    self->timer = 0x10;
    self->unk60 = 4;
    self->x_vel.val *= 5;
    self->y_vel.val *= 5;
    self->unk2C = 0;
    self->unk28 = 0;
    self->unk68 = NULL;
    self->unk5C = 1;
    self->x_pos.val += self->x_vel.val * 5;
    self->y_pos.val -= self->y_vel.val * 5;
    set_animation(self, 0xD);
    self->state = 1;
    self->unk5 = 0;
}

void func_800A766C(struct ShotObj* self)
{
    s32 dx;
    s32 dy;

    if (--self->unk8A == 0) {
        set_animation(self, 0xE);
        self->unk5 = 4;
        return;
    }
    if (--self->timer == 0) {
        if (self->unk2 == 0) {
            self->unk2 = 1;
            self->timer = 0xB4;
        } else {
            self->timer = 0x78;
            self->unk2 = 0;
        }
    }
    if (!(main_bss_state.frame_counter & 3)) {
        set_velocity_from_angle(MOVING_OBJECT(self),
            angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);
        if (self->unk2 == 0) {
            self->x_vel.val *= 2;
            self->y_vel.val *= 2;
        }
    }
    dx = self->x_pos.i.hi - g_Player.x_pos.i.hi;
    dy = self->y_pos.i.hi - g_Player.y_pos.i.hi;
    if ((dx >= 0 ? dx : -dx) >= 3 || (dy >= 0 ? dy : -dy) >= 3) {
        move_object(MOVING_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
}

void func_800818C4(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        if (g_Player.x_pos.i.hi < self->x_pos.i.hi) {
            self->unk15 = 0;
            self->x_speed = FIXED(4);
        } else {
            self->unk15 = 0x40;
            self->x_speed = FIXED(-4);
        }
        func_8001540C(2, 0xE0, self);
        set_animation(self, 4);
        self->unk6 = 2;
    }
}

void func_80080DF4(struct MainObj* self)
{
    struct MainObj* other;
    struct EffectObj* effect;
    s8 delay;

    if (--self->unk7C == 0) {
        self->unk5 = 2;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.i.hi;
            effect->y_pos.i.hi = self->y_pos.i.hi;
            self->ext.main_66.effect = effect;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
    if (self->unk7E-- == 0) {
        other = self->ext.main_66.partner;
        self->unk42 ^= 0x8000;
        other->unk42 ^= 0x8000;
        self->invincibility_timer -= 5;
        if (self->invincibility_timer >= 0x1A) {
            self->invincibility_timer = 0;
        }
        delay = self->invincibility_timer;
        if (delay < 5) {
            delay = 5;
        }
        self->unk7E = delay;
    }
}

void func_80081AD0(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->ext.main_66.hover_timer = self->hp >= 0x18 ? 0xF0 : 0xB4;
        set_animation(self, 1);
        self->collision_data = D_80107DFC;
        func_8001540C(2, 0xE1, self);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void func_80081BA0(struct MainObj* self)
{
    struct MainObj* body;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 0) {
        return;
    }
    body = find_free_main_obj();
    if (body != NULL) {
        body->active = 0x41;
        body->id = 0x42;
        body->unk2 = 1;
        body->contact_damage = 4;
        body->x_pos.val = self->x_pos.val;
        body->collision_data = D_80107E84;
        body->hurt_box = &D_801035C8;
        body->air_state = 0;
        body->attack_box = &D_801035C4;
        body->terrain_box = NULL;
        body->y_pos.val = self->y_pos.val;
        body->bg_offset = self->bg_offset;
        body->animation_table = self->animation_table;
        body->unk40 = self->unk40;
        body->sprite_frames = self->sprite_frames;
        body->unk16 = 5;
        body->hp = 0x30;
        body->unk42 = self->unk42 & 0x7FFF;
        body->y_speed = 0x10000;
        body->unk7C = 0x60;
        body->x_speed = 0;
        body->x_accel = 0;
        body->gravity = 0;
        body->state = 1;
        body->unk15 = self->unk15;
        body->unk5 = 5;
        body->unk6 = 2;
        engine_obj.boss_ptr = body;
        set_animation(body, 0x10);
        body->ext.main_66.active = 1;
        body->ext.main_66.partner = self;
        self->ext.main_66.partner = body;
    }
    self->unk6 = 1;
}

void func_80081E44(struct MainObj* self)
{
    struct Main66Ext* ext = &self->ext.main_66;
    u8 index;
    s32 direction;
    s32 dx;
    s32 dy;

    if (!(main_bss_state.frame_counter & 1)) {
        D_8013B858[ext->trail_write] = ext->partner->x_pos.i.hi;
        D_8013B878[ext->trail_write] = ext->partner->y_pos.i.hi - 0x50;
        if (++ext->trail_write == 0x10) {
            ext->trail_write = 0;
        }
        index = ext->trail_read;
        direction = angle_to_point(OBJECT_HEADER(self), (s16)D_8013B858[index] << 16, D_8013B878[index] << 16);
        ext->trail_target = ext->trail_read;
        if (++ext->trail_read == 0x10) {
            ext->trail_read = 0;
        }
        set_velocity_from_angle(MOVING_OBJECT(self), direction & 0xFF);
        self->x_speed *= 2;
        self->y_speed *= 2;
    }
    dx = self->x_pos.i.hi - (s16)D_8013B858[ext->trail_target];
    dy = self->y_pos.i.hi - D_8013B878[ext->trail_target];
    if ((dx >= 0 ? dx : -dx) >= 3 || (dy >= 0 ? dy : -dy) >= 3) {
        move_object(MOVING_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
    if (ext->partner->unk5 == 4) {
        self->y_speed = -0x40000;
        self->x_speed = 0;
        self->unk5 = 7;
        self->unk6 = 0;
    }
}

void func_800A73C4(struct ShotObj* self)
{
    self->timer = 0x78;
    self->unk60 = 8;
    self->on_screen = 1;
    self->unk61 = 1;
    self->unk5C = 1;
    self->unk58.data = NULL;
    self->x_vel.val = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->unk28 = 0;
    self->unk16 = 0;
    self->unk68 = NULL;
    self->unk54 = NULL;
    self->unk50.data = NULL;
    self->unk42 &= 0x7FFF;
    self->y_pos.i.hi -= 0x86;
    set_animation(self, 0x1B);
    self->state = 7;
    self->unk5 = 0;
}

extern s16 title_quad_shapes[][8];

#ifdef VERSION_JP
extern u16 title_quad_palette[][15];

void title_quad_morph(struct QuadObj* arg0)
{
    f32* xy_ptr;
    s32 x_diff;
    s32 y_diff;
    s32 pos;
    s16* ptr;
    u16* palette;
    u16* var_v0;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v1;

    xy_ptr = &arg0->vertices[0].x;
    pos = 0;
    do {
        ptr = &title_quad_shapes[arg0->unk2 + 5][pos * 2];
        x_diff = xy_ptr[0].val - FIXED(ptr[0]);
        y_diff = xy_ptr[1].val - FIXED(ptr[1]);
        temp_v0 = angle_from_delta(x_diff, y_diff);
        if ((((arg0->ext.title_quad.unk3E[pos] ^ temp_v0) & 0x10) || (arg0->ext.title_quad.unk3A[pos] != 0)) && (arg0->ext.title_quad.unk42 == 0)) {
            xy_ptr[0].val = FIXED(ptr[0]);
            xy_ptr[1].val = FIXED(ptr[1]);
            arg0->ext.title_quad.unk3A[pos] = 1;
        } else {
            xy_ptr[0].val -= x_diff / arg0->ext.title_quad.unk38;
            xy_ptr[1].val -= y_diff / arg0->ext.title_quad.unk38;
            arg0->ext.title_quad.unk3A[pos] = 0;
            if (pos == 3) {
                arg0->ext.title_quad.unk42 = 0;
            }
        }
        xy_ptr += 2;
        arg0->ext.title_quad.unk3E[pos] = temp_v0;
        pos++;
    } while (pos < 4);

    if ((arg0->ext.title_quad.unk38 % 3) == 0) {
        palette = title_quad_palette[arg0->unk2 - 2];
        temp_v1 = arg0->ext.title_quad.unk43;
        temp_v0_2 = temp_v1 + 1;
        arg0->ext.title_quad.unk43 = temp_v0_2;
        var_v0 = palette;
        if (temp_v0_2 < 0xE) {
            temp_v0_2 = temp_v1 + 2;
            arg0->ext.title_quad.unk43 = temp_v0_2;
            var_v0 = &palette[temp_v0_2];
        } else {
            var_v0 += 14;
        }
        arg0->unk34 = *var_v0;
    }

    arg0->ext.title_quad.unk38--;
    if (arg0->ext.title_quad.unk38 == 0) {
        ptr = title_quad_shapes[arg0->unk2 + 5];
        arg0->vertices[0].x.i.hi = *(u16*)ptr++;
        arg0->vertices[0].y.i.hi = *(u16*)ptr++;
        arg0->vertices[1].x.i.hi = *(u16*)ptr++;
        arg0->vertices[1].y.i.hi = *(u16*)ptr++;
        arg0->vertices[2].x.i.hi = *(u16*)ptr++;
        arg0->vertices[2].y.i.hi = *(u16*)ptr++;
        arg0->vertices[3].x.i.hi = *(u16*)ptr++;
        arg0->vertices[3].y.i.hi = *(u16*)ptr;
        arg0->unk2 = 4;
        arg0->state = 4;
        arg0->ext.title_quad.unk38 = 3;
    }
    quad_is_on_screen(arg0);
}
#endif
