#ifndef MAIN_EFFECTS_EFFECT_34_ROCK_DROP_SEQUENCE_H
#define MAIN_EFFECTS_EFFECT_34_ROCK_DROP_SEQUENCE_H

void rock_drop_sequence_update(struct EffectObj* arg0);

void rock_drop_sequence_spawn(struct EffectObj*);

extern s16 rock_drop_sequence_delays[10];
extern u8 rock_drop_sequence_subtypes[12];
extern s16 rock_drop_sequence_x_positions[10];

#endif
