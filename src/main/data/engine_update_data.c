#include "common.h"

void (*D_800F23B0[2])(struct EngineObj*) = {
    func_8001F198, func_8001F2BC,
};

void (*D_800F23B8[7])(struct EngineObj*) = {
    func_8001F488, func_8001F634, func_8001F6E8, func_8001F798,
    func_8001F850, func_8001F93C, func_8001F968,
};

void (*D_800F23D4[2])(struct EngineObj*) = {
    func_8001F9DC, func_8001FA24,
};

void (*D_800F23DC[3])(struct EngineObj*) = {
    func_8001F398, func_8001F9A0, func_8001FAC0,
};

void (*engine_update_funcs[13])(struct EngineObj*) = {
    engine_state_0, engine_state_1, engine_state_2, engine_state_3,
    engine_state_4, func_8001FC20, engine_state_6, func_8001FAFC,
    func_80020AC8, func_80020D98, func_80020464, func_80023A54,
    func_800204AC,
};

void (*D_800F241C[3])(struct EngineObj*) = {
    func_8001FF8C, func_80020060, func_80020368,
};
