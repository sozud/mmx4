#include "common.h"

void (*spike_marl_patrol_funcs[])(struct MainObj*) = {
    spike_marl_patrol_begin,
    spike_marl_patrol_update,
};

void (*spike_marl_turn_funcs[])(struct MainObj*) = {
    func_80043858,
    func_80043898,
};

void (*spike_marl_curl_funcs[])(struct MainObj*) = {
    spike_marl_curl_begin,
    spike_marl_curl_update,
};

void (*spike_marl_roll_funcs[])(struct MainObj*) = {
    spike_marl_roll_begin,
    spike_marl_roll_update,
    func_80043C0C,
};

void (*spike_marl_uncurl_funcs[])(struct MainObj*) = {
    spike_marl_uncurl_begin,
    spike_marl_uncurl_update,
};

void (*spike_marl_roll_entry_funcs[])(struct MainObj*) = {
    spike_marl_roll_entry_begin,
    spike_marl_roll_entry_update,
};
