#ifndef MAIN_VISUALS_VISUAL_04_BLAST_H
#define MAIN_VISUALS_VISUAL_04_BLAST_H

void blast_update(struct VisualObj*);

struct VisualObj* spawn_explosion_at(s8, s16, s16, u8);

void func_800AF95C(struct ObjectHeader*, s32, s32, s32, s32);

void spawn_explosion_variant(struct BaseObj* arg0, s8 arg1);

#endif
