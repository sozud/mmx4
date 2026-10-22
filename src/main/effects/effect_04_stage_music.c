// EffectObj, effect_object_update_funcs[4]
// 800B5EB0..800B60BC
#include "common.h"
#include "main/55C4.h"
#include "main/effects/effect_04_stage_music.h"
#include "main/3D88.h"
#include "main/objects.h"

// stage_music_state_funcs
extern void (*stage_music_state_funcs[])(struct EffectObj*);
void stage_music_init(struct EffectObj*);
void stage_music_load(struct EffectObj*);
void stage_music_despawn(struct EffectObj*);

#ifdef MMX4_SATURN
#define STAGE_MUSIC_SOUND_KIND 4
#define STAGE_ARCHIVE_STAGE_DIGIT 2
#define STAGE_ARCHIVE_SUBSTAGE_DIGIT 4

void saturn_music_request(s32 kind, s32 id, s32 pan, s32 unused);
void saturn_music_stop(void);
void saturn_archive_queue_push(const char* path, u32 suppress_indicator);
extern volatile u8 saturn_archive_queue_busy;
char stage_music_archive_name[] = "ST0_1_1.ARC";

void stage_music_init(struct EffectObj* self)
{
    self->state = 1;
    self->unk5 = 0;
    self->ext.effect_4.timer = 0x64;
    saturn_music_request(STAGE_MUSIC_SOUND_KIND, 1, 0, 0);
    saturn_music_request(STAGE_MUSIC_SOUND_KIND, 2, 0, 0);
    saturn_music_request(STAGE_MUSIC_SOUND_KIND, 3, 0, 0);
    saturn_music_request(STAGE_MUSIC_SOUND_KIND, 4, 0, 0);
    saturn_music_request(STAGE_MUSIC_SOUND_KIND, 5, 0, 0);
    saturn_music_request(STAGE_MUSIC_SOUND_KIND, 7, 0, 0);
    D_80141BD0 = 1;
}
#else
void stage_music_init(struct EffectObj* self)
{
    self->ext.effect_4.unk16 = -1;
    self->ext.effect_4.timer = 0x64;
    self->state++;
    func_80016FB4(3);
}
#endif
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

#ifdef MMX4_SATURN
void stage_music_load(struct EffectObj* self)
{
    s32 stage;
    switch (self->unk5) {
    case 0:
        saturn_music_stop();
        if (engine_obj.stage == 0xA && engine_obj.substage == 0) {
            self->unk5 = D_80171EA8 != 0 ? 3 : 1;
        } else if (engine_obj.stage == 0xC && engine_obj.substage == 1) {
            self->unk5 = 3;
        } else if (D_80171EA8 == 0 && engine_obj.substage != 0) {
            self->unk5++;
        } else {
            self->unk5 = 3;
        }
        break;
    case 1:
        D_80171EA8 = 1;
        D_80141BD0 = 1;
        stage = (s8)engine_obj.stage;
        stage_music_archive_name[STAGE_ARCHIVE_STAGE_DIGIT] = (char)((stage >= 10 ? stage + 7 : stage) + '0');
        stage_music_archive_name[STAGE_ARCHIVE_SUBSTAGE_DIGIT] = (char)(engine_obj.substage + '0');
        saturn_archive_queue_push(stage_music_archive_name, 1);
        self->unk5++;
        break;
    case 2:
        if (!saturn_archive_queue_busy)
            self->unk5++;
        break;
    case 3:
        self->state = 2;
        self->unk5 = 0;
        break;
    }
}
#else
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
        func_80013AD8(stage_music_tracks[engine_obj.stage], 4, D_80141F30[2]);
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

#endif

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
