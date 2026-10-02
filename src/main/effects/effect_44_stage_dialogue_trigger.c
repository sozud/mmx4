// EffectObj, effect_object_update_funcs[44]
// 800BE83C..800BE9A0
#include "common.h"

void stage_dialogue_trigger_update(struct EffectObj* self)
{
    stage_dialogue_trigger_state_funcs[self->state](self);
}

void stage_dialogue_trigger_wait(struct EffectObj* self)
{
    if (engine_obj.character_state.bytes[9] != 0) {
        despawn_object_permanently(OBJECT_HEADER(self));
        return;
    }

    if (engine_obj.unk1C == 0) {
        player_start_script_action(0x14, 0x40);
        self->ext.unk_effect.unk14 = 0x30;
        self->state = 1;
    }
}

void stage_dialogue_trigger_talk(struct EffectObj* self)
{
    s8 timer;

    timer = self->ext.unk_effect.unk14 - 1;
    self->ext.unk_effect.unk14 = timer;
    if (timer == 0) {
        if (engine_obj.cur_character == CHARACTER_X) {
            func_8002217C(0x34, 9, engine_obj.character_state.bytes[9]);
        } else {
            func_8002217C(0x2F, 9, engine_obj.character_state.bytes[9]);
        }
        engine_obj.character_state.bytes[9] = 1;
        self->state = 2;
    }
}

void stage_dialogue_trigger_finish(struct EffectObj* self)
{
    if (abc_object.unkC == 0) {
        player_end_script_action();
        despawn_object_permanently(self);
    }
}

void (*stage_dialogue_trigger_state_funcs[])(struct EffectObj*) = {
    stage_dialogue_trigger_wait,
    stage_dialogue_trigger_talk,
    stage_dialogue_trigger_finish,
};
