#ifndef MAIN_MAINS_MAIN_43_WEB_SPIDER_H
#define MAIN_MAINS_MAIN_43_WEB_SPIDER_H

void web_spider_update(struct MainObj* arg0);

void func_8006398C(struct MainObj*);

// spiderling_state_funcs
void func_80065574(struct MainObj*);

// web_spider_intro_funcs
void web_spider_intro_warning(struct MainObj*);

void func_8006346C(struct MainObj*);

// web_spider_drop_funcs
void func_80063B20(struct MainObj*);
void web_spider_drop_climb(struct MainObj*);
void web_spider_drop_climb(struct MainObj*);

void web_spider_spawn_web_flash(struct AnimatedObj*);
void web_spider_spawn_web_shot(struct AnimatedObj*, u8);

void func_80064154(struct MainObj*);

// web_spider_big_web_funcs
void func_800646EC(struct MainObj*);
void web_spider_big_web_spin(struct MainObj*);
void web_spider_spawn_web_piece(struct VisualObj*, u8);
void web_spider_big_web_center(struct MainObj*);

void web_spider_fall_rethread(struct MainObj*);

// web_spider_death_funcs
void web_spider_set_attack_cooldown(struct MainObj*);

void web_spider_death_explode(struct MainObj*);
void web_spider_death_finish(struct MainObj*);

void spiderling_crawl(struct MainObj* arg0);

extern u16 web_spider_arena_x;
extern u16 web_spider_arena_y;

extern union AnimationStep* web_spider_animations[40];

struct ShotObj* web_spider_spawn_thread(struct MainObj*, s32);

void web_spider_set_move_timer(struct MainObj*);
void web_spider_set_swing_animation(struct MainObj*);

#endif
