#include "common.h"

void character_select_state_0(struct EngineObj*);
void character_select_state_1(struct EngineObj*);
void character_select_state_2(struct EngineObj*);
void character_select_state_3(struct EngineObj*);
void character_select_state_4(struct EngineObj*);
void character_select_state_5(struct EngineObj*);
void character_select_state_6(struct EngineObj*);

void (*D_800F44A8[])(struct EngineObj*) = {
    character_select_state_0,
    character_select_state_1,
    character_select_state_2,
    character_select_state_3,
    character_select_state_4,
    character_select_state_5,
    character_select_state_6,
};
