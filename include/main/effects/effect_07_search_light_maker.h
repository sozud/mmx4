#ifndef MAIN_EFFECTS_EFFECT_07_SEARCH_LIGHT_MAKER_H
#define MAIN_EFFECTS_EFFECT_07_SEARCH_LIGHT_MAKER_H

struct SearchLightSpawner {
    u8 active, type, reserved, background_index;
    s16 x, y;
};

void search_light_maker_update(struct EffectObj* arg0);

void search_light_maker_spawn_in_rect(s16, s16, s16, s16, s32);

#endif
