#ifndef MAIN_MAINS_MAIN_76_SPIKE_CRAWLER_H
#define MAIN_MAINS_MAIN_76_SPIKE_CRAWLER_H

void spike_crawler_update(struct MainObj* arg0);

extern u8 spike_crawler_debris[4];
void spike_crawler_init(struct MainObj*);
void func_80091B1C(struct MainObj*);

void func_80091EC4(struct MainObj*);
void spike_crawler_hit_knockback(struct MainObj*);

extern union AnimationStep* spike_crawler_animations[5];

extern s8 spike_crawler_terrain_box[4];

#endif
