#include "common.h"
#include "func_tables.h"

void (*general_fly_funcs[3])() = { general_fly_descend, general_fly_start, func_800905D4 };
void (*general_punch_funcs[6])() = {
    general_punch_rise,
    general_punch_launch,
    general_punch_wait,
    general_punch_rings,
    general_punch_wait_return,
    general_punch_recover,
};
void (*general_orbs_funcs[4])() = { general_orbs_descend, general_orbs_fire, general_orbs_wait, general_orbs_recover };
void (*general_slam_funcs[6])(struct MainObj*) = {
    general_slam_windup,
    general_slam_fall,
    general_slam_land,
    general_slam_rise,
    general_slam_ascend,
    general_slam_leave,
};
void (*general_step_funcs[7])() = {
    func_8009216C,
    general_resume_step,
    func_8009027C,
    general_fly,
    general_punch,
    general_orbs,
    general_slam,
};
void (*general_death_funcs[5])() = {
    general_death_start,
    general_death_blink,
    func_800915C4,
    general_death_wait_explosion,
    func_800917AC,
};
