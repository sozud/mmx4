#ifndef MAIN_ENEMY_REACTION_H
#define MAIN_ENEMY_REACTION_H

void spike_crawler_hit_flash(struct MainObj*);
void func_80091EC4(struct MainObj*);
void spike_crawler_hit_knockback(struct MainObj*);

extern s32 spike_crawler_knockback_speeds[2];
extern u8 boss_voice_tracks[13][3];

#endif
