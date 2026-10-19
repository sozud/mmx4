#ifndef MAIN_MISC_MISC_08_CRUMBLING_TILE_H
#define MAIN_MISC_MISC_08_CRUMBLING_TILE_H

struct Misc08EffectTripletTable {
    struct Misc08EffectTriplet entries[26];
    u8 padding[2];
};

struct Misc08EffectDescriptor {
    u8 effect_id;
    u8 variant;
};

void crumbling_tile_update(struct MiscObj* arg0);

extern union AnimationStep* D_8010DF48[57];

#endif
