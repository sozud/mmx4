// EffectObj, effect_object_update_funcs[4]
// 800B5EB0..800B60BC
#include "common.h"

void stage_music_init(struct EffectObj* self)
{
    self->ext.effect_4.unk16 = -1;
    self->ext.effect_4.timer = 0x64;
    self->state++;
    func_80016FB4(3);
}
u8 stage_music_tracks[16] = {
#ifdef VERSION_JP
    0x75,
    0x76,
    0x77,
    0x78,
    0x79,
    0x7A,
    0x7B,
    0x7C,
    0x7D,
    0,
    0x7E,
    0x7F,
    0x80,
    0,
    0,
    0,
#elif defined(VERSION_EU)
    0x77,
    0x78,
    0x79,
    0x7A,
    0x7B,
    0x7C,
    0x7D,
    0x7E,
    0x7F,
    0,
    0x80,
    0x81,
    0x82,
    0,
    0,
    0,
#else
    0x76,
    0x77,
    0x78,
    0x79,
    0x7A,
    0x7B,
    0x7C,
    0x7D,
    0x7E,
    0,
    0x7F,
    0x80,
    0x81,
    0,
    0,
    0,
#endif
};

void stage_music_load(struct EffectObj* self)
{
    switch (self->unk5) {
    case 0:
        if (0 != D_80173C84) {
            break;
        }
        if ((engine_obj.stage == 0xA && engine_obj.substage == 0)) {
            if (D_80171EA8 == 0) {
                self->unk5 = 1;
            } else {
                self->unk5 = 3;
            }
        } else if ((engine_obj.stage == 0xC && engine_obj.substage == 1) || D_80171EA8 != 0) {
            self->unk5 = 3;
        } else if (engine_obj.substage != 0) {
            self->unk5++;
        } else {
            self->unk5 = 3;
        }
        break;
    case 1:
        D_80171EA8 = 1;
        func_80013AD8(stage_music_tracks[engine_obj.stage], 4, D_80141F38);
        self->unk5++;
        break;
    case 2:
        if (D_801406AC == 2 && D_8013BD40 == 0) {
            self->unk5++;
        }
        break;
    case 3:
        self->state++;
        break;
    }
}

void stage_music_despawn(struct EffectObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void stage_music_update(struct EffectObj* self)
{
    stage_music_state_funcs[self->state](self);
}

void (*stage_music_state_funcs[])(struct EffectObj*) = {
    stage_music_init,
    stage_music_load,
    stage_music_despawn,
};
