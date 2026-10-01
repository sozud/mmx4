// 80021158..80021DBC
#include "common.h"

void TitleScalingXUpdate(struct EffectObj*);
void MegamanInBriefingRoomUpdate(struct MiscObj*);
void MegamanRelatedUpdate(struct MiscObj*);
void TitleUpdate(struct MiscObj*);
void SelectACharacterUpdate(struct MiscObj*);
void TitleLogoUpdate(struct MiscObj*);
void TitleUpdate2(struct QuadObj*);

void func_80021158(void)
{
    player_read_input();
    func_80021C14();
    player_update();
    update_weapon_objects();
    update_main_objects();
    update_shot_objects();
    update_visual_objects();
    update_effect_objects();
    update_item_objects();
    update_misc_objects();
    update_quad_objects();
    func_80028E24();
    func_80021D20();
    CollisionRelated(&g_Player);
    func_80027850();
    func_80027D40();
    func_800281E8();
    update_layer_objects();
    func_8002A484();
    func_80021D84();
    func_80021CC8();
    decompress_player_gfx(GRAPHICS_OBJECT(&g_Player), 0x140, 0);
}

void update_main_objects(void)
{
#define current SP_CUR_MAIN_OBJ
    if (!g_Player.update_delay) {
        for (current = main_objects; current < &main_objects[COUNT(main_objects)]; current++) {
            if (current->active) {
                if (g_Player.update_delay != 0 || (engine_obj.unk12 != 0 && !(current->active & 0x8))) {
                    if (current->on_screen != 0) {
                        func_8002B3C0(current);
                    }
                } else {
                    main_object_update_funcs[current->id](current);
                }
            }
        }
    }
#undef current
}

void update_weapon_objects(void)
{
#define current SP_CUR_WEAPON_OBJ
    if (!g_Player.update_delay) {
        for (current = weapon_objects; current < &weapon_objects[COUNT(weapon_objects)]; current++) {
            if (current->active) {
                if (g_Player.update_delay != 0 || (engine_obj.unk11 != 0 && !(current->active & 0x8))) {
                    if (current->on_screen != 0) {
                        func_8002B3C0(current);
                    }
                } else {
                    weapon_object_update_funcs[current->id](current);
                }
            }
        }
    }
#undef current
}

void update_shot_objects(void)
{
#define current SP_CUR_SHOT_OBJ
    if (!g_Player.update_delay) {
        for (current = shot_objects; current < &shot_objects[COUNT(shot_objects)]; current++) {
            if (current->active) {
                if (g_Player.update_delay != 0 || (engine_obj.unk13 != 0 && !(current->active & 0x8))) {
                    if (current->on_screen != 0) {
                        func_8002B3C0(current);
                    }
                } else {
                    shot_object_update_funcs[current->id](current);
                }
            }
        }
    }
#undef current
}

void update_visual_objects(void)
{
#define current SP_CUR_VISUAL_OBJ
    for (current = visual_objects; current < &visual_objects[COUNT(visual_objects)]; current++) {
        if (engine_obj.unk14 == 0 && current->active != 0) {
            visual_object_update_funcs[current->id](current);
        } else if (current->active != 0) {
            if (current->active & 8) {
                visual_object_update_funcs[current->id](current);
            } else if (current->on_screen != 0) {
                func_8002B3C0(current);
            }
        }
    }
#undef current
}

void update_effect_objects(void)
{
#define current SP_CUR_EFFECT_OBJ
    for (current = effect_objects; current < &effect_objects[COUNT(effect_objects)]; current++) {
        if (0 == engine_obj.unk15 && current->active) {
            effect_object_update_funcs[current->id](current);
        } else if (engine_obj.unk15 && current->active & 8) {
            effect_object_update_funcs[current->id](current);
        }
    }
#undef current
}

void update_item_objects(void)
{
#define current SP_CUR_ITEM_OBJ
    if (!g_Player.update_delay) {
        for (current = item_objects; current < &item_objects[COUNT(item_objects)]; current++) {
            if (current->active) {
                if (g_Player.update_delay != 0 || (engine_obj.unk16 != 0 && !(current->active & 0x8))) {
                    if (current->on_screen != 0) {
                        func_8002B3C0(current);
                    }
                } else {
                    item_object_update_funcs[current->id](current);
                }
            }
        }
    }
#undef current
}

void update_misc_objects(void)
{
#define current SP_CUR_MISC_OBJ
    for (current = misc_objects; current < &misc_objects[COUNT(misc_objects)]; current++) {
        if (engine_obj.unk17 == 0 && current->active != 0) {
            misc_object_update_funcs[current->id](current);
        } else if (current->active != 0) {
            if (current->active & 8) {
                misc_object_update_funcs[current->id](current);
            } else if (current->on_screen != 0) {
                func_8002B3C0(current);
            }
        }
    }
#undef current
}

void update_unk_objects(void)
{
#define current SP_CUR_UNK_OBJ
    for (current = unk_objects; current < &unk_objects[COUNT(unk_objects)]; current++) {
        if (current->active) {
            unk_object_update_funcs[current->id](current);
        }
    }
#undef current
}

void update_quad_objects(void)
{
#define current SP_CUR_QUAD_OBJ
    for (current = g_QuadObjects; current < &g_QuadObjects[COUNT(g_QuadObjects)]; current++) {
        if (engine_obj.unk18 == 0 && current->active != 0) {
            quad_object_update_funcs[current->id](current);
        } else if (current->active != 0) {
            if (current->active & 8) {
                quad_object_update_funcs[current->id](current);
            } else if (current->on_screen != 0) {
                func_8002B458(current); // no-op
            }
        }
    }
#undef current
}

void update_layer_objects(void)
{
#define current SP_CUR_LAYER_OBJ
    for (current = layer_objects; current < &layer_objects[COUNT(layer_objects)]; current++) {
        if (engine_obj.unk19 == 0 && current->active) {
            layer_object_update_funcs[current->id](current);
        } else if (engine_obj.unk19 && current->active & 8) {
            layer_object_update_funcs[current->id](current);
        }
    }
#undef current
}

void func_80021C14(void)
{
    if (engine_obj.unk10 == 0) {
        if (qux_object.active != 0) {
            D_800F2AD4[qux_object.id](&qux_object);
            return;
        }
    } else if (qux_object.active != 0) {
        if (qux_object.active & 8) {
            D_800F2AD4[qux_object.id](&qux_object);
            return;
        }
        if (qux_object.on_screen != 0) {
            func_8002B3C0(&qux_object);
        }
    }
}

void func_80021CC8(void)
{
    struct UnkObj* var_s0;

    for (var_s0 = &foo_objects; var_s0 < &foo_objects[COUNT(foo_objects)]; var_s0++) {
        func_800AE7DC(var_s0);
    }
}

void func_80021D20(void)
{
    if (abc_object.unkC != 0) {
        func_80022730(&abc_object);
    } else if (abc_object.unk10 != 0) {
        func_8002217C(abc_object.unk10 & ~0x8000, 0xFF, 0);
    }
}

void func_80021D84(void)
{
    func_800AE6B4(&baz_objects[0]);
    func_800AE6B4(&baz_objects[1]);
}

void (*main_object_update_funcs[])(struct MainObj*) = {
    background_dragon_update,
    armored_walker_update,
    item_carrier_update,
    spike_marl_update,
    drill_copter_update,
    robot_bee_update,
    bulldozer_update,
    ambush_gunner_update,
    eregion_update,
    unused_main_09_update,
    dragonfly_update,
    wall_crawler_update,
    hover_sentry_update,
    heavy_mech_update,
    ice_bird_update,
    shell_crawler_update,
    trident_mech_update,
    snowman_bomb_update,
    ice_core_update,
    surface_hopper_update,
    ice_block_update,
    falling_icicle_update,
    bee_hive_update,
    slope_skier_update,
    jet_drone_update,
    caterkiller_update,
    ice_wall_update,
    dash_gunner_update,
    spawner_pod_update,
    pod_spawner_update,
    regen_turret_update,
    thorn_trap_update,
    bomb_bat_update,
    spike_sled_update,
    highway_trooper_update,
    wheel_charger_update,
    latcher_update,
    rocket_spiker_update,
    train_cannon_update,
    falling_ceiling_update,
    breakable_terrain_update,
    data_hopper_update,
    homing_orb_update,
    web_spider_update,
    anchored_mine_update,
    train_boss_update,
    train_boss_turret_update,
    train_boss_armor_update,
    sentry_drone_update,
    train_soldier_update,
    train_crate_update,
    fortress_cannon_update,
    jump_shooter_update,
    wave_rider_update,
    slash_beast_update,
    jet_stingray_flyby_update,
    jet_stingray_update,
    frost_walrus_update,
    beam_drone_update,
    timed_explosion_update,
    storm_owl_update,
    split_mushroom_update,
    flame_jet_update,
    hatch_turret_update,
    cyber_peacock_update,
    magma_dragoon_update,
    iris_update,
    gunship_update,
    sigma_update,
    colonel_update,
    drone_pod_update,
    ride_armor_pilot_update,
    unused_ride_armor_update,
    double_update,
    sigma_final_update,
    general_update,
    spike_crawler_update,
};

void (*weapon_object_update_funcs[])(struct WeaponObj*) = {
    lemon_update,
    lightning_web_update,
    frost_tower_update,
    soul_body_update,
    rising_fire_update,
    ground_hunter_update,
    func_800961B0,
    double_cyclone_update,
    twin_slasher_update,
    charge_shot_update,
    lightning_web_charged_update,
    frost_tower_charged_update,
    lemon_update,
    rising_fire_charged_update,
    ground_hunter_charged_update,
    aiming_laser_charged_update,
    double_cyclone_charged_update,
    twin_slasher_charged_update,
    charge_shot_update,
    stock_shot_update,
    plasma_shot_update,
    plasma_shot_update,
    nova_strike_hitbox_update,
    lemon_update,
    zero_saber_update,
    zero_saber_update,
    zero_saber_update,
    zero_saber_update,
    zero_saber_update,
    zero_saber_update,
    zero_saber_update,
    zero_saber_update,
    zero_saber_update,
    zero_saber_update,
    zero_saber_update,
    zero_saber_update,
    func_800981CC,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    lemon_update,
    ride_chaser_shot_update,
    ride_chaser_ram_update,
    ice_block_hitbox_update,
    ride_armor_shot_update,
    ride_armor_missile_update,
    ride_armor_punch_update,
    ride_armor_punch_update,
};

void (*shot_object_update_funcs[])(struct ShotObj*) = {
    dragon_shot_update,
    drill_copter_shot_update,
    gunner_shot_update,
    eregion_fireball_update,
    eregion_wing_slash_update,
    mech_boulder_update,
    wall_crawler_shot_update,
    dropped_bomb_update,
    shell_crawler_shot_update,
    trident_shot_update,
    dragon_spread_shot_update,
    enemy_bullet_update,
    ice_core_shot_update,
    jet_drone_bullet_update,
    dash_gunner_shot_update,
    turret_laser_update,
    linked_spark_update,
    depth_charge_update,
    aimed_bullet_update,
    trooper_bomb_update,
    cannon_blast_update,
    cannon_shell_update,
    web_shot_update,
    web_thread_update,
    train_boss_shot_update,
    grenade_update,
    sentry_shot_update,
    jump_shooter_shot_update,
    melee_hitbox_update,
    cannon_missile_update,
    cannon_shot_update,
    slash_beast_crescent_update,
    flame_pillar_update,
    falling_rock_update,
    ray_trap_update,
    walrus_ice_update,
    drone_beam_update,
    owl_feather_update,
    owl_cyclone_update,
    mushroom_shot_update,
    hatch_blast_update,
    magma_fire_update,
    peacock_missile_update,
    gunship_shot_update,
    iris_shot_update,
    colonel_shot_update,
    sigma_shot_update,
    enemy_ride_armor_shot_update,
    double_ball_update,
    double_aerial_update,
    double_bouncer_update,
    double_mine_update,
    double_mine_shot_update,
    sigma_head_update,
    sigma_final_shot_update,
    general_shot_update,
    sigma_spit_update,
    sigma_beam_hitbox_update,
};

void (*visual_object_update_funcs[])(struct VisualObj*) = {
    wall_slide_dust_update,
    dash_dust_update,
    charge_muzzle_flash_update,
    small_effect_update,
    blast_update,
    object_afterimage_update,
    func_800AFF78,
    water_wake_update,
    ice_shard_update,
    dust_puff_update,
    dragon_fx_update,
    charge_ring_update,
    ride_dust_update,
    ride_chaser_jet_update,
    lift_effect_update,
    ride_chaser_flash_update,
    enemy_charge_glow_update,
    web_piece_update,
    aiming_laser_scope_update,
    func_800B2698,
    web_flash_update,
    wave_rider_jet_update,
    missile_smoke_update,
    jet_stingray_fx_update,
    frost_walrus_fx_update,
    flame_jet_fx_update,
    weapon_overlay_update,
    weapon_gfx_preload_update,
    storm_owl_fx_update,
    peacock_target_update,
    colonel_fx_update,
    gunship_exhaust_update,
    sigma_fx_update,
    hover_jet_update,
    split_mushroom_fx_update,
    capsule_glass_update,
    capsule_scan_update,
    capsule_beam_update,
    func_800C6EDC,
    func_80098338,
};

void (*effect_object_update_funcs[])(struct EffectObj*) = {
    camera_trigger_update,
    tile_animator_update,
    TitleScalingXUpdate,
    palette_animator_update,
    stage_music_update,
    func_800B60BC,
    checkpoint_trigger_update,
    search_light_maker_update,
    bg_zone_controller_update,
    bg_wind_update,
    func_800B7EE8,
    null_effect_update,
    enemy_spawner_update,
    edge_spawner_update,
    item_scatter_update,
    bg_zone_controller_b_update,
    autoscroll_segment_update,
    freeze_blast_update,
    world_flip_update,
    bg_zone_controller_c_update,
    bg_zone_controller_d_update,
    crumble_sequencer_update,
    bg_zone_controller_e_update,
    tile_flicker_update,
    boss_warning_update,
    bg_zone_controller_f_update,
    boss_death_fx_update,
    TeleportRelatedObjectUpdate,
    fortress_collapse_update,
    tile_anim_trigger_update,
    qux_spawner_update,
    floor_trap_update,
    proximity_door_update,
    rock_dropper_update,
    rock_drop_sequence_update,
    palette_pulse_update,
    stage_exit_fade_update,
    alarm_flash_update,
    cyberspace_trial_update,
    tile_strip_anim_update,
    tile_loop_anim_update,
    tile_blink_anim_update,
    sigma_sequencer_fx_update,
    sigma_collapse_update,
    stage_dialogue_trigger_update,
};

void (*item_object_update_funcs[])(struct ItemObj*) = {
    breakable_wall_update,
    stage_block_update,
    pickup_update,
    falling_pillar_update,
    destructible_core_update,
    moving_lift_update,
    gate_core_update,
    rising_platform_update,
    boss_door_update,
    moving_block_update,
    spark_machine_update,
    teleporter_update,
    crusher_wall_update,
    trap_floor_update,
    big_elevator_update,
    rising_slab_update,
    sliding_floor_update,
    crumble_trigger_update,
    drop_pillar_update,
    data_capsule_update,
    gravity_switch_update,
    hopper_switch_update,
    layout_gate_update,
    laser_target_update,
    breakable_panel_update,
    breakable_boulder_update,
    light_capsule_update,
    boss_teleporter_update,
};

void (*misc_object_update_funcs[])(struct MiscObj*) = {
    static_sprite_update,
    common_effect_update,
    rubble_update,
    debris_update,
    dragon_rubble_update,
    pod_effect_update,
    homing_point_update,
    attached_effect_update,
    crumbling_tile_update,
    owner_fx_update,
    MegamanInBriefingRoomUpdate,
    blink_marker_update,
    stage_icon_update,
    stage_portrait_update,
    frame_ghost_update,
    vent_update,
    vent_puff_update,
    death_orb_update,
    MegamanRelatedUpdate,
    TitleUpdate,
    scroll_prop_update,
    center_sprite_update,
    dialogue_ui_update,
    explosion_puff_update,
    enemy_hatch_update,
    sentry_flash_update,
    slash_beast_afterimage_update,
    owner_aura_update,
    SelectACharacterUpdate,
    TitleLogoUpdate,
    spore_rain_fx_update,
    option_toggle_update,
    option_sprite_update,
    cyberspace_warp_update,
    cyberspace_guide_update,
    cyclone_trail_update,
    item_sparkle_update,
    frost_shard_update,
    dragoon_flame_update,
    iris_intro_crystal_update,
    ambient_bubble_update,
    func_80097DD8,
    menu_icon_update,
    intro_messenger_update,
    stage_cutscene_update,
    scripted_slider_update,
    post_boss_cutscene_update,
    frost_sparkle_update,
    func_80098474,
    double_afterimage_update,
    cutscene_actor_update,
    capsule_part_update,
    npc_cutscene_update,
    final_cutscene_update,
    stock_charge_meter_update,
    sigma_final_fx_update,
    func_80023CA4,
    falling_piece_update,
};

void (*unk_object_update_funcs[])(struct UnkObj*) = {
    menu_text_update,
    menu_label_update,
};

void (*quad_object_update_funcs[])(struct QuadObj*) = {
    SearchLightUpdate,
    stage_select_panel_update,
    stage_select_flyout_update,
    boss_warning_quad_update,
    boss_death_shard_update,
    web_piece_quad_update,
    light_ray_update,
    ready_line_update,
    flash_band_update,
    aiming_laser_beam_update,
    aiming_laser_charged_beam_update,
    TitleUpdate2,
    title_facet_update,
    quad_null_update,
    colonel_beam_update,
    sigma_beam_update,
    sigma_laser_update,
};

void (*layer_object_update_funcs[])(struct LayerObj*) = {
    train_scroll_update,
    jungle_parallax_update,
    train_tunnel_update,
    func_800D9C84,
    volcano_camera_update,
    airship_bob_update,
    final_weapon_bg_cycle_update,
    space_port_parallax_update,
};

void (*D_800F2AD4[])(struct RideArmorObj*) = {
    func_8003B3DC,
    func_8003D3F8,
};
