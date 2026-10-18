// 80021158..80021DBC
#include "common.h"
#include "main/144A4.h"
#include "main/bike.h"
#include "main/effects/effect_00_camera_trigger.h"
#include "main/effects/effect_01_tile_animator.h"
#include "main/effects/effect_03_palette_animator.h"
#include "main/effects/effect_04_stage_music.h"
#include "main/effects/effect_05_tile_scanner.h"
#include "main/effects/effect_06_checkpoint_trigger.h"
#include "main/effects/effect_07_search_light_maker.h"
#include "main/effects/effect_08_bg_zone_controller.h"
#include "main/effects/effect_09_bg_wind.h"
#include "main/effects/effect_10.h"
#include "main/effects/effect_11_null_effect.h"
#include "main/effects/effect_12_enemy_spawner.h"
#include "main/effects/effect_13_edge_spawner.h"
#include "main/effects/effect_14_item_scatter.h"
#include "main/effects/effect_15_bg_zone_controller_b.h"
#include "main/effects/effect_16_autoscroll_segment.h"
#include "main/effects/effect_17_freeze_blast.h"
#include "main/effects/effect_18_world_flip.h"
#include "main/effects/effect_19_bg_zone_controller_c.h"
#include "main/effects/effect_20_bg_zone_controller_d.h"
#include "main/effects/effect_21_crumble_sequencer.h"
#include "main/effects/effect_22_bg_zone_controller_e.h"
#include "main/effects/effect_23_tile_flicker.h"
#include "main/effects/effect_24_boss_warning.h"
#include "main/effects/effect_25_bg_zone_controller_f.h"
#include "main/effects/effect_26_boss_death_fx.h"
#include "main/effects/effect_28_fortress_collapse.h"
#include "main/effects/effect_29_tile_anim_trigger.h"
#include "main/effects/effect_30_qux_spawner.h"
#include "main/effects/effect_31_floor_trap.h"
#include "main/effects/effect_32_proximity_door.h"
#include "main/effects/effect_33_rock_dropper.h"
#include "main/effects/effect_34_rock_drop_sequence.h"
#include "main/effects/effect_35_palette_pulse.h"
#include "main/effects/effect_36_stage_exit_fade.h"
#include "main/effects/effect_37_alarm_flash.h"
#include "main/effects/effect_38_cyberspace_trial.h"
#include "main/effects/effect_39_tile_strip_anim.h"
#include "main/effects/effect_40_tile_loop_anim.h"
#include "main/effects/effect_41_tile_blink_anim.h"
#include "main/effects/effect_42_sigma_sequencer_fx.h"
#include "main/effects/effect_43_sigma_collapse.h"
#include "main/effects/effect_44_stage_dialogue_trigger.h"
#include "main/items/item_00_breakable_wall.h"
#include "main/items/item_01_stage_block.h"
#include "main/items/item_02_pickup.h"
#include "main/items/item_03_falling_pillar.h"
#include "main/items/item_04_destructible_core.h"
#include "main/items/item_05_moving_lift.h"
#include "main/items/item_06_gate_core.h"
#include "main/items/item_07_rising_platform.h"
#include "main/items/item_08_boss_door.h"
#include "main/items/item_09_moving_block.h"
#include "main/items/item_10_spark_machine.h"
#include "main/items/item_11_teleporter.h"
#include "main/items/item_12_crusher_wall.h"
#include "main/items/item_13_trap_floor.h"
#include "main/items/item_14_big_elevator.h"
#include "main/items/item_15_rising_slab.h"
#include "main/items/item_16_sliding_floor.h"
#include "main/items/item_17_crumble_trigger.h"
#include "main/items/item_18_drop_pillar.h"
#include "main/items/item_19_data_capsule.h"
#include "main/items/item_20_gravity_switch.h"
#include "main/items/item_21_hopper_switch.h"
#include "main/items/item_22_layout_gate.h"
#include "main/items/item_23_laser_target.h"
#include "main/items/item_24_breakable_panel.h"
#include "main/items/item_25_breakable_boulder.h"
#include "main/items/item_26_light_capsule.h"
#include "main/items/item_27_boss_teleporter.h"
#include "main/layers/layer_00_train_scroll.h"
#include "main/layers/layer_01_jungle_parallax.h"
#include "main/layers/layer_02_train_tunnel.h"
#include "main/layers/layer_03.h"
#include "main/layers/layer_04_volcano_camera.h"
#include "main/layers/layer_05_airship_bob.h"
#include "main/layers/layer_06_final_weapon_bg_cycle.h"
#include "main/layers/layer_07_space_port_parallax.h"
#include "main/mains/main_00_background_dragon.h"
#include "main/mains/main_01_armored_walker.h"
#include "main/mains/main_02_item_carrier.h"
#include "main/mains/main_03_spike_marl.h"
#include "main/mains/main_04_drill_copter.h"
#include "main/mains/main_05_robot_bee.h"
#include "main/mains/main_06_bulldozer.h"
#include "main/mains/main_07_ambush_gunner.h"
#include "main/mains/main_08_eregion.h"
#include "main/mains/main_09_unused.h"
#include "main/mains/main_10_dragonfly.h"
#include "main/mains/main_11_wall_crawler.h"
#include "main/mains/main_12_hover_sentry.h"
#include "main/mains/main_13_heavy_mech.h"
#include "main/mains/main_14_ice_bird.h"
#include "main/mains/main_15_shell_crawler.h"
#include "main/mains/main_16_trident_mech.h"
#include "main/mains/main_17_snowman_bomb.h"
#include "main/mains/main_18_ice_core.h"
#include "main/mains/main_19_surface_hopper.h"
#include "main/mains/main_20_ice_block.h"
#include "main/mains/main_21_falling_icicle.h"
#include "main/mains/main_22_bee_hive.h"
#include "main/mains/main_23_slope_skier.h"
#include "main/mains/main_24_jet_drone.h"
#include "main/mains/main_25_caterkiller.h"
#include "main/mains/main_26_ice_wall.h"
#include "main/mains/main_27_dash_gunner.h"
#include "main/mains/main_28_spawner_pod.h"
#include "main/mains/main_29_pod_spawner.h"
#include "main/mains/main_30_regen_turret.h"
#include "main/mains/main_31_thorn_trap.h"
#include "main/mains/main_32_bomb_bat.h"
#include "main/mains/main_33_spike_sled.h"
#include "main/mains/main_34_highway_trooper.h"
#include "main/mains/main_35_wheel_charger.h"
#include "main/mains/main_36_latcher.h"
#include "main/mains/main_37_rocket_spiker.h"
#include "main/mains/main_38_train_cannon.h"
#include "main/mains/main_39_falling_ceiling.h"
#include "main/mains/main_40_breakable_terrain.h"
#include "main/mains/main_41_data_hopper.h"
#include "main/mains/main_42_homing_orb.h"
#include "main/mains/main_43_web_spider.h"
#include "main/mains/main_44_anchored_mine.h"
#include "main/mains/main_45_train_boss.h"
#include "main/mains/main_46_train_boss_turret.h"
#include "main/mains/main_47_train_boss_armor.h"
#include "main/mains/main_48_sentry_drone.h"
#include "main/mains/main_49_train_soldier.h"
#include "main/mains/main_50_train_crate.h"
#include "main/mains/main_51_fortress_cannon.h"
#include "main/mains/main_52_jump_shooter.h"
#include "main/mains/main_53_wave_rider.h"
#include "main/mains/main_54_slash_beast.h"
#include "main/mains/main_56_jet_stingray.h"
#include "main/mains/main_57_frost_walrus.h"
#include "main/mains/main_58_beam_drone.h"
#include "main/mains/main_59_timed_explosion.h"
#include "main/mains/main_60_storm_owl.h"
#include "main/mains/main_61_split_mushroom.h"
#include "main/mains/main_62_flame_jet.h"
#include "main/mains/main_63_hatch_turret.h"
#include "main/mains/main_64_cyber_peacock.h"
#include "main/mains/main_65_magma_dragoon.h"
#include "main/mains/main_66_iris.h"
#include "main/mains/main_67_gunship.h"
#include "main/mains/main_68_sigma.h"
#include "main/mains/main_69_colonel.h"
#include "main/mains/main_70_drone_pod.h"
#include "main/mains/main_71_ride_armor_pilot.h"
#include "main/mains/main_72_unused_ride_armor.h"
#include "main/mains/main_73_double.h"
#include "main/mains/main_74_sigma_final.h"
#include "main/mains/main_75_general.h"
#include "main/mains/main_76_spike_crawler.h"
#include "main/mech.h"
#include "main/misc/misc_00_static_sprite.h"
#include "main/misc/misc_01_common_effect.h"
#include "main/misc/misc_02_rubble.h"
#include "main/misc/misc_03_debris.h"
#include "main/misc/misc_04_dragon_rubble.h"
#include "main/misc/misc_05_pod_effect.h"
#include "main/misc/misc_06_homing_point.h"
#include "main/misc/misc_07_attached_effect.h"
#include "main/misc/misc_08_crumbling_tile.h"
#include "main/misc/misc_09_owner_fx.h"
#include "main/misc/misc_11_blink_marker.h"
#include "main/misc/misc_12_stage_icon.h"
#include "main/misc/misc_13_stage_portrait.h"
#include "main/misc/misc_14_frame_ghost.h"
#include "main/misc/misc_15_vent.h"
#include "main/misc/misc_16_vent_puff.h"
#include "main/misc/misc_17_death_orb.h"
#include "main/misc/misc_20_scroll_prop.h"
#include "main/misc/misc_21_center_sprite.h"
#include "main/misc/misc_22_dialogue_ui.h"
#include "main/misc/misc_23_explosion_puff.h"
#include "main/misc/misc_24_enemy_hatch.h"
#include "main/misc/misc_25_sentry_flash.h"
#include "main/misc/misc_26_slash_beast_afterimage.h"
#include "main/misc/misc_27_owner_aura.h"
#include "main/misc/misc_30_spore_rain_fx.h"
#include "main/misc/misc_31_option_toggle.h"
#include "main/misc/misc_32_option_sprite.h"
#include "main/misc/misc_33_cyberspace_warp.h"
#include "main/misc/misc_34_cyberspace_guide.h"
#include "main/misc/misc_35_cyclone_trail.h"
#include "main/misc/misc_36_item_sparkle.h"
#include "main/misc/misc_38_dragoon_flame.h"
#include "main/misc/misc_39_iris_intro_crystal.h"
#include "main/misc/misc_40_ambient_bubble.h"
#include "main/misc/misc_42_menu_icon.h"
#include "main/misc/misc_43_intro_messenger.h"
#include "main/misc/misc_44_stage_cutscene.h"
#include "main/misc/misc_45_scripted_slider.h"
#include "main/misc/misc_46_post_boss_cutscene.h"
#include "main/misc/misc_49_double_afterimage.h"
#include "main/misc/misc_50_cutscene_actor.h"
#include "main/misc/misc_51_capsule_part.h"
#include "main/misc/misc_52_npc_cutscene.h"
#include "main/misc/misc_53_final_cutscene.h"
#include "main/misc/misc_55_sigma_final_fx.h"
#include "main/misc/misc_57_falling_piece.h"
#include "main/quads/quad_00_search_light.h"
#include "main/quads/quad_01_stage_select_panel.h"
#include "main/quads/quad_02_stage_select_flyout.h"
#include "main/quads/quad_03_boss_warning_quad.h"
#include "main/quads/quad_04_boss_death_shard.h"
#include "main/quads/quad_05_web_piece_quad.h"
#include "main/quads/quad_06_light_ray.h"
#include "main/quads/quad_07_ready_line.h"
#include "main/quads/quad_08_flash_band.h"
#include "main/quads/quad_09_aiming_laser_beam.h"
#include "main/quads/quad_10_aiming_laser_charged_beam.h"
#include "main/quads/quad_12_title_facet.h"
#include "main/quads/quad_13_null.h"
#include "main/quads/quad_14_colonel_beam.h"
#include "main/quads/quad_15_sigma_beam.h"
#include "main/quads/quad_16_sigma_laser.h"
#include "main/shots/shot_00_dragon_shot.h"
#include "main/shots/shot_01_drill_copter_shot.h"
#include "main/shots/shot_02_gunner_shot.h"
#include "main/shots/shot_06_wall_crawler_shot.h"
#include "main/shots/shot_07_dropped_bomb.h"
#include "main/shots/shot_08_shell_crawler_shot.h"
#include "main/shots/shot_09_trident_shot.h"
#include "main/shots/shot_10_dragon_spread_shot.h"
#include "main/shots/shot_11_enemy_bullet.h"
#include "main/shots/shot_12_ice_core_shot.h"
#include "main/shots/shot_13_jet_drone_bullet.h"
#include "main/shots/shot_14_dash_gunner_shot.h"
#include "main/shots/shot_15_turret_laser.h"
#include "main/shots/shot_16_linked_spark.h"
#include "main/shots/shot_17_depth_charge.h"
#include "main/shots/shot_18_aimed_bullet.h"
#include "main/shots/shot_19_trooper_bomb.h"
#include "main/shots/shot_20_cannon_blast.h"
#include "main/shots/shot_21_cannon_shell.h"
#include "main/shots/shot_22_web_shot.h"
#include "main/shots/shot_23_web_thread.h"
#include "main/shots/shot_24_train_boss_shot.h"
#include "main/shots/shot_25_grenade.h"
#include "main/shots/shot_26_sentry_shot.h"
#include "main/shots/shot_27_jump_shooter_shot.h"
#include "main/shots/shot_28_melee_hitbox.h"
#include "main/shots/shot_29_cannon_missile.h"
#include "main/shots/shot_30_cannon_shot.h"
#include "main/shots/shot_31_slash_beast_crescent.h"
#include "main/shots/shot_32_flame_pillar.h"
#include "main/shots/shot_33_falling_rock.h"
#include "main/shots/shot_34_ray_trap.h"
#include "main/shots/shot_35_walrus_ice.h"
#include "main/shots/shot_36_drone_beam.h"
#include "main/shots/shot_37_owl_feather.h"
#include "main/shots/shot_38_owl_cyclone.h"
#include "main/shots/shot_39_mushroom_shot.h"
#include "main/shots/shot_40_hatch_blast.h"
#include "main/shots/shot_41_magma_fire.h"
#include "main/shots/shot_42_peacock_missile.h"
#include "main/shots/shot_43_gunship_shot.h"
#include "main/shots/shot_44_iris_shot.h"
#include "main/shots/shot_45_colonel_shot.h"
#include "main/shots/shot_46_sigma_shot.h"
#include "main/shots/shot_48_double_ball.h"
#include "main/shots/shot_49_double_aerial.h"
#include "main/shots/shot_50_double_bouncer.h"
#include "main/shots/shot_51_double_mine.h"
#include "main/shots/shot_52_double_mine_shot.h"
#include "main/shots/shot_53_sigma_head.h"
#include "main/shots/shot_54_sigma_final_shot.h"
#include "main/shots/shot_55_general_shot.h"
#include "main/shots/shot_56_sigma_spit.h"
#include "main/shots/shot_57_sigma_beam_hitbox.h"
#include "main/unks/unk_00_menu_text.h"
#include "main/unks/unk_01_menu_label.h"
#include "main/visuals/visual_00_wall_slide_dust.h"
#include "main/visuals/visual_01_dash_dust.h"
#include "main/visuals/visual_02_charge_muzzle_flash.h"
#include "main/visuals/visual_03_small_effect.h"
#include "main/visuals/visual_04_blast.h"
#include "main/visuals/visual_05_object_afterimage.h"
#include "main/visuals/visual_06_eregion_part.h"
#include "main/visuals/visual_07_water_wake.h"
#include "main/visuals/visual_08_ice_shard.h"
#include "main/visuals/visual_09_dust_puff.h"
#include "main/visuals/visual_10_dragon_fx.h"
#include "main/visuals/visual_11_charge_ring.h"
#include "main/visuals/visual_12_ride_dust.h"
#include "main/visuals/visual_13_ride_chaser_jet.h"
#include "main/visuals/visual_14_lift_effect.h"
#include "main/visuals/visual_15_ride_chaser_flash.h"
#include "main/visuals/visual_16_enemy_charge_glow.h"
#include "main/visuals/visual_17_web_piece.h"
#include "main/visuals/visual_18_aiming_laser_scope.h"
#include "main/visuals/visual_19_double_cyclone_charged_fan.h"
#include "main/visuals/visual_20_web_flash.h"
#include "main/visuals/visual_21_wave_rider_jet.h"
#include "main/visuals/visual_22_missile_smoke.h"
#include "main/visuals/visual_23_jet_stingray_fx.h"
#include "main/visuals/visual_24_frost_walrus_fx.h"
#include "main/visuals/visual_25_flame_jet_fx.h"
#include "main/visuals/visual_26_weapon_overlay.h"
#include "main/visuals/visual_27_weapon_gfx_preload.h"
#include "main/visuals/visual_28_storm_owl_fx.h"
#include "main/visuals/visual_29_peacock_target.h"
#include "main/visuals/visual_30_colonel_fx.h"
#include "main/visuals/visual_31_gunship_exhaust.h"
#include "main/visuals/visual_32_sigma_fx.h"
#include "main/visuals/visual_33_hover_jet.h"
#include "main/visuals/visual_34_split_mushroom_fx.h"
#include "main/weapons/weapon_00_lemon.h"
#include "main/weapons/weapon_01_lightning_web.h"
#include "main/weapons/weapon_02_frost_tower.h"
#include "main/weapons/weapon_03_soul_body.h"
#include "main/weapons/weapon_04_rising_fire.h"
#include "main/weapons/weapon_05_ground_hunter.h"
#include "main/weapons/weapon_06_aiming_laser_charged.h"
#include "main/weapons/weapon_07_double_cyclone.h"
#include "main/weapons/weapon_08_twin_slasher.h"
#include "main/weapons/weapon_09_charge_shot.h"
#include "main/weapons/weapon_19_stock_shot.h"
#include "main/weapons/weapon_20_plasma_shot.h"
#include "main/weapons/weapon_22_nova_strike_hitbox.h"
#include "main/weapons/weapon_24_zero_saber.h"
#include "main/weapons/weapon_56_ride_chaser_shot.h"
#include "main/weapons/weapon_57_ride_chaser_ram.h"
#include "main/weapons/weapon_58_ice_block_hitbox.h"
#include "main/weapons/weapon_59_ride_armor_shot.h"
#include "main/weapons/weapon_60_ride_armor_missile.h"
#include "main/weapons/weapon_61_ride_armor_punch.h"
#include "main/afterimage.h"
#include "main/effects/effect_02_color_filter.h"
#include "main/misc/misc_10_briefing_character.h"
#include "main/misc/misc_18_ready_text.h"
#include "main/misc/misc_19_title.h"
#include "main/misc/misc_28_select_a_character.h"
#include "main/misc/misc_29_title_logo.h"
#include "main/object_update.h"
#include "main/player.h"
#include "main/quads/quad_11_title_quad.h"
#include "main/128C4.h"
#include "main/1A5BC.h"
#include "main/55C4.h"
#include "main/background.h"
#include "main/charge_glow.h"
#include "main/collision.h"
#include "main/effects/effect_27_teleport_intro.h"
#include "main/objects.h"
#include "main/player_common.h"

// D_800F24A4 (main_object_update_funcs)
extern void (*main_object_update_funcs[])(struct MainObj*);

// D_800F25D8 (weapon_object_update_funcs)
extern void (*weapon_object_update_funcs[])(struct WeaponObj*);

// D_800F26D4 (shot_object_update_funcs)
extern void (*shot_object_update_funcs[])(struct ShotObj*);

// D_800F27BC (visual_object_update_funcs)
extern void (*visual_object_update_funcs[])(struct VisualObj*);

// D_800F285C (effect_object_update_funcs)
extern void (*effect_object_update_funcs[])(struct EffectObj*);

// D_800F2910 (item_object_update_funcs)
extern void (*item_object_update_funcs[])(struct ItemObj*);

// D_800F2980 (misc_object_update_funcs)
extern void (*misc_object_update_funcs[])(struct MiscObj*);

// D_800F2A68 (unk_object_update_funcs)
extern void (*unk_object_update_funcs[])(struct UnkObj*);

// D_800F2A70 (quad_object_update_funcs)
extern void (*quad_object_update_funcs[])(struct QuadObj*);

// D_800F2AB4 (layer_object_update_funcs)
extern void (*layer_object_update_funcs[])(struct LayerObj*);

// D_800F2AD4
extern void (*D_800F2AD4[])(struct RideArmorObj*);

void func_80021C14(void);
void func_80021CC8(void);
void func_80021D84(void);
void func_800AE7DC(struct UnkObj* arg0);
void player_update(void);
void update_item_objects(void);
void update_layer_objects(void);
void update_main_objects(void);
void update_shot_objects(void);
void update_visual_objects(void);
void update_weapon_objects(void);

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
