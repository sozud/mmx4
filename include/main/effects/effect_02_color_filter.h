#ifndef MAIN_EFFECTS_EFFECT_02_COLOR_FILTER_H
#define MAIN_EFFECTS_EFFECT_02_COLOR_FILTER_H

void color_filter_init(struct EffectObj*);

#ifdef MMX4_PC
extern void TitleScalingXUpdate (struct EffectObj *arg0);

extern void copy_animated_palette (struct EffectObj *arg0);
#endif

extern struct Unk14* color_filter_scripts[];

#endif
