#ifndef MAIN_MAINS_MAIN_03_SPIKE_MARL_H
#define MAIN_MAINS_MAIN_03_SPIKE_MARL_H

void spike_marl_update(struct MainObj* arg0);

void func_80043390(struct MainObj* arg0);

void spike_marl_check_patrol_path(struct MainObj* arg0);

void spike_marl_curl_update(struct MainObj* arg0);

void spike_marl_roll_update(struct MainObj* arg0);
void func_80043C0C(struct MainObj* arg0);

void spike_marl_uncurl_update(struct MainObj* arg0);

void spike_marl_roll_entry_update(struct MainObj*);

extern struct Unk_unk68 spike_marl_walk_attack_box;
extern struct Unk_unk68 spike_marl_walk_hurt_box;

#endif
