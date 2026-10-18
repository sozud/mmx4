#ifndef MAIN_MAINS_MAIN_64_CYBER_PEACOCK_H
#define MAIN_MAINS_MAIN_64_CYBER_PEACOCK_H

void cyber_peacock_update(struct MainObj *arg0);

void cyber_peacock_intro_appear_start(struct MainObj*);
void cyber_peacock_intro_pose(struct MainObj*);
void cyber_peacock_intro_start_health_bar(struct MainObj*);
void cyber_peacock_intro_fill_health(struct MainObj*);

void func_8007C30C(struct MainObj*);
void cyber_peacock_intro_wait_player(struct MainObj*);
void cyber_peacock_intro_appear(struct MainObj* arg0);

void cyber_peacock_teleport_start(struct MainObj*);
void cyber_peacock_teleport_vanish(struct MainObj*);
void func_8007CA68(struct MainObj*);
void cyber_peacock_teleport_appear(struct MainObj*);
void cyber_peacock_teleport_wait(struct MainObj*);

void cyber_peacock_rising_kick_start(struct MainObj*);
void cyber_peacock_rising_kick_jump(struct MainObj*);
void cyber_peacock_rising_kick_rise(struct MainObj*);
void cyber_peacock_rising_kick_finish(struct MainObj*);

void cyber_peacock_slash_start(struct MainObj*);
void cyber_peacock_slash_swing(struct MainObj*);
void cyber_peacock_slash_finish(struct MainObj*);

void cyber_peacock_spawn_laser_target(struct MainObj*);
void cyber_peacock_spawn_missile(struct MainObj*);
void cyber_peacock_aiming_laser_start(struct MainObj*);
void cyber_peacock_aiming_laser_raise(struct MainObj*);
void cyber_peacock_aiming_laser_target(struct MainObj*);
void cyber_peacock_aiming_laser_wait(struct MainObj* arg0);
void cyber_peacock_aiming_laser_fire(struct MainObj*);
void cyber_peacock_aiming_laser_next(struct MainObj*);
void cyber_peacock_aiming_laser_finish(struct MainObj*);

void cyber_peacock_rising_kick(struct MainObj* arg0);
void cyber_peacock_slash(struct MainObj* arg0);
void cyber_peacock_aiming_laser(struct MainObj* arg0);
void cyber_peacock_rising_kick(struct MainObj* arg0);

// cyber_peacock_step_funcs
void cyber_peacock_teleport(struct MainObj *arg0);
void cyber_peacock_attack(struct MainObj *arg0);
void func_8007D5D0(struct MainObj* arg0);
void func_8007D710(struct MainObj* arg0);

void cyber_peacock_death_start(struct MainObj*);
void cyber_peacock_death_explode(struct MainObj*);
void cyber_peacock_death_finish(struct MainObj*);

void cyber_peacock_intro(struct MainObj* arg0);
void func_8007D838(struct MainObj*);
void cyber_peacock_death(struct BarObj* arg0);

extern void* cyber_peacock_animations[38];

extern struct Unk_unk68 cyber_peacock_hit_box;

#endif
