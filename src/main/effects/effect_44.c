// EffectObj, effect_object_update_funcs[44]
// 800BE83C..800BE9A0
#include "common.h"

void func_800BE83C(struct EffectObj* arg0)
{
    D_8010C13C[arg0->state](arg0);
}

void func_800BE878(struct EffectObj* arg0)
{
    if (engine_obj.character_state.bytes[9] != 0) {
        func_8002B108(OBJECT_HEADER(arg0));
        return;
    }

    if (engine_obj.unk1C == 0) {
        func_80036AE4(0x14, 0x40);
        arg0->ext.unk_effect.unk14 = 0x30;
        arg0->state = 1;
    }
}

void func_800BE8E4(struct EffectObj* arg0)
{
    u16 sound_id;
    s8 timer;

    timer = arg0->ext.unk_effect.unk14 - 1;
    arg0->ext.unk_effect.unk14 = timer;
    if (timer == 0) {
        sound_id = 0x2F;
        if (engine_obj.cur_character == 0) {
            sound_id = 0x34;
        }
        func_8002217C(sound_id, 9, engine_obj.character_state.bytes[9]);
        engine_obj.character_state.bytes[9] = 1;
        arg0->state = 2;
    }
}

void func_800BE960(struct EffectObj* arg0)
{
    if (abc_object.unkC == 0) {
        func_80036B18();
        func_8002B108(arg0);
    }
}

void (*D_8010C13C[])(struct EffectObj*) = {
    func_800BE878,
    func_800BE8E4,
    func_800BE960,
};
