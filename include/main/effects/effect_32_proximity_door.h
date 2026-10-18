#ifndef MAIN_EFFECTS_EFFECT_32_PROXIMITY_DOOR_H
#define MAIN_EFFECTS_EFFECT_32_PROXIMITY_DOOR_H

void proximity_door_update(struct EffectObj* arg0);

// proximity_door_state_funcs
extern u8* tile_anim_trigger_scripts[];

void proximity_door_check_player(struct EffectObj*);

#endif
