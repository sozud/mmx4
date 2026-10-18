#ifndef MAIN_SHOTS_SHOT_40_HATCH_BLAST_H
#define MAIN_SHOTS_SHOT_40_HATCH_BLAST_H

void hatch_blast_update(struct ShotObj*);

// hatch_blast_step_funcs
extern void (*hatch_blast_step_funcs[])(struct ShotObj*);

#endif
