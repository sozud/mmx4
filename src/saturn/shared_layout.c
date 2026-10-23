#include "common.h"
#include "main/55C4.h"

#ifdef MMX4_SHC
#define CHECK_LAYOUT(name, condition) MMX4_STATIC_ASSERT(saturn_##name, condition)
#else
#define CHECK_LAYOUT(name, condition) typedef char saturn_layout_##name[(condition) ? 1 : -1]
#endif
CHECK_LAYOUT(pointer_width, sizeof(void*) == 4);
CHECK_LAYOUT(stage_clear_flag_width, sizeof(D_80173C84) == 2);
CHECK_LAYOUT(engine_stride, sizeof(struct EngineObj) == 100);
CHECK_LAYOUT(player_stride, sizeof(struct PlayerObj) == 228);
CHECK_LAYOUT(background_stride, sizeof(struct BackgroundObj) == 84);
CHECK_LAYOUT(character_state_size, sizeof(union EngineCharacterState) == 16);
#ifdef MMX4_SHC
CHECK_LAYOUT(character_menu_word, MMX4_OFFSET_OF(union EngineCharacterState, fields.menu_state_bytes) == 6);
#else
CHECK_LAYOUT(character_menu_word, MMX4_OFFSET_OF(union EngineCharacterState, fields.menu_state) == 6);
#endif
CHECK_LAYOUT(main_palette_size, sizeof(union MainPaletteData) == 0x200);
CHECK_LAYOUT(fixed_size, sizeof(f32) == 4);
CHECK_LAYOUT(fixed_signed_high, MMX4_OFFSET_OF(f32, i.hi) == 0);
CHECK_LAYOUT(fixed_signed_low, MMX4_OFFSET_OF(f32, i.lo) == 2);
CHECK_LAYOUT(fixed_unsigned_high, MMX4_OFFSET_OF(f32, u.hi) == 0);
CHECK_LAYOUT(fixed_unsigned_low, MMX4_OFFSET_OF(f32, u.lo) == 2);
CHECK_LAYOUT(animation_index, MMX4_OFFSET_OF(struct AnimatedObj, unk17) == 0x17);
CHECK_LAYOUT(animation_table, MMX4_OFFSET_OF(struct AnimatedObj, animation_table) == 0x30);
CHECK_LAYOUT(animation_cursor, MMX4_OFFSET_OF(struct AnimatedObj, animation_cursor) == 0x34);
CHECK_LAYOUT(animation_step, MMX4_OFFSET_OF(struct AnimatedObj, animation_step) == 0x44);
CHECK_LAYOUT(previous_frame, MMX4_OFFSET_OF(struct AnimatedObj, previous_animation_index) == 0x48);
CHECK_LAYOUT(step_size, sizeof(union AnimationStep) == 4);
CHECK_LAYOUT(duration, MMX4_OFFSET_OF(union AnimationStep, fields.duration) == 0);
CHECK_LAYOUT(event, MMX4_OFFSET_OF(union AnimationStep, fields.event) == 1);
CHECK_LAYOUT(relative_step, MMX4_OFFSET_OF(union AnimationStep, fields.relative_step) == 2);
CHECK_LAYOUT(frame_index, MMX4_OFFSET_OF(union AnimationStep, fields.frame_index) == 3);
CHECK_LAYOUT(engine_state, MMX4_OFFSET_OF(struct EngineObj, state) == 0);
CHECK_LAYOUT(engine_checkpoint, MMX4_OFFSET_OF(struct EngineObj, checkpoint) == 0x1D);
CHECK_LAYOUT(engine_checkpoint_aux, MMX4_OFFSET_OF(struct EngineObj, unk1E) == 0x1E);
CHECK_LAYOUT(engine_lives, MMX4_OFFSET_OF(struct EngineObj, player_lives) == 0x44);
CHECK_LAYOUT(engine_max_hp, MMX4_OFFSET_OF(struct EngineObj, max_hp) == 0x46);
CHECK_LAYOUT(main_stride, sizeof(struct MainObj) == 0x9C);
CHECK_LAYOUT(weapon_stride, sizeof(struct WeaponObj) == 0x9C);
CHECK_LAYOUT(shot_stride, sizeof(struct ShotObj) == 0x9C);
CHECK_LAYOUT(visual_stride, sizeof(struct VisualObj) == 0x70);
CHECK_LAYOUT(effect_stride, sizeof(struct EffectObj) == 0x30);
CHECK_LAYOUT(item_stride, sizeof(struct ItemObj) == 0x8C);
CHECK_LAYOUT(misc_stride, sizeof(struct MiscObj) == 0x60);
CHECK_LAYOUT(unk_stride, sizeof(struct UnkObj) == 0x60);
CHECK_LAYOUT(quad_stride, sizeof(struct QuadObj) == 0x60);
CHECK_LAYOUT(layer_stride, sizeof(struct LayerObj) == 0x30);
CHECK_LAYOUT(object_active, MMX4_OFFSET_OF(struct MainObj, active) == 0);
CHECK_LAYOUT(object_id, MMX4_OFFSET_OF(struct MainObj, id) == 1);
CHECK_LAYOUT(object_on_screen, MMX4_OFFSET_OF(struct MainObj, on_screen) == 3);
CHECK_LAYOUT(player_update_delay, MMX4_OFFSET_OF(struct PlayerObj, update_delay) == 0xBC);
CHECK_LAYOUT(dialogue_effect_state, MMX4_OFFSET_OF(struct EffectObj, state) == 4);
CHECK_LAYOUT(dialogue_effect_timer, MMX4_OFFSET_OF(struct EffectObj, ext.unk_effect.unk14) == 0x14);
CHECK_LAYOUT(dialogue_player_lock, MMX4_OFFSET_OF(struct EngineObj, gameplay_locked) == 0x1C);
CHECK_LAYOUT(dialogue_character, MMX4_OFFSET_OF(struct EngineObj, cur_character) == 0x43);
CHECK_LAYOUT(dialogue_state_size, sizeof(struct AbcObj) == 0x14);
CHECK_LAYOUT(dialogue_active, MMX4_OFFSET_OF(struct AbcObj, unkC) == 0xC);
CHECK_LAYOUT(player_script_state, MMX4_OFFSET_OF(struct PlayerObj, script_state) == 0xC0);
CHECK_LAYOUT(player_script_action, MMX4_OFFSET_OF(struct PlayerObj, script_action) == 0xC1);
CHECK_LAYOUT(player_script_facing, MMX4_OFFSET_OF(struct PlayerObj, script_facing) == 0xC2);
CHECK_LAYOUT(player_script_immunity, MMX4_OFFSET_OF(struct PlayerObj, spike_immune) == 0x7A);

CHECK_LAYOUT(dialogue_seen, MMX4_OFFSET_OF(struct EngineObj, character_state) + 9 == 0x2F);
