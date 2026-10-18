#ifndef MAIN_MISC_MISC_23_EXPLOSION_PUFF_H
#define MAIN_MISC_MISC_23_EXPLOSION_PUFF_H

void explosion_puff_update(struct MiscObj* arg0);

#ifdef MMX4_PC
extern void explosion_puff_init (struct MiscObj *arg0);
extern void explosion_puff_animate (struct MiscObj *arg0);
#endif

extern u32* explosion_animations[3];

#endif
