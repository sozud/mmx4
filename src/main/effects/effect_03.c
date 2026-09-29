// EffectObj, effect_object_update_funcs[3]
// 800B5CC4..800B5EB0
#include "common.h"

void palette_animator_update(struct EffectObj* self)
{
    if (self->state == 0) {
        func_800B5D04(self);
        return;
    }
    palette_animator_step(self);
}

// palette_animator_init
INCLUDE_ASM("main/nonmatchings/effects/effect_03", func_800B5D04);

void palette_animator_step(struct EffectObj* self)
{
    if (self->ext.palette_animation.timer-- == 0) {
        self->ext.palette_animation.cursor += 2;
        if (self->ext.palette_animation.cursor[1] < 0) {
            self->ext.palette_animation.cursor += self->ext.palette_animation.cursor[1] * 2;
        }
        self->ext.palette_animation.timer = self->ext.palette_animation.cursor[1];
        self->ext.palette_animation.source = SP_ARC_30 + ((u8)self->ext.palette_animation.cursor[0] << 3);
        copy_animated_palette(self);
    }
}

extern s8* palette_animator_scripts_s00_0[10];
extern s8* palette_animator_scripts_s00_1[3];
extern s8* palette_animator_scripts_s01_0[6];
extern s8* palette_animator_scripts_s01_1[5];
extern s8* palette_animator_scripts_s02_0[3];
extern s8* palette_animator_scripts_s02_1[9];
extern s8* palette_animator_scripts_s03_0[2];
extern s8* palette_animator_scripts_s03_1[4];
extern s8* palette_animator_scripts_s04_0[6];
extern s8* palette_animator_scripts_s04_1[7];
extern s8* palette_animator_scripts_s05_0[4];
extern s8* palette_animator_scripts_s05_1[5];
extern s8* palette_animator_scripts_s06_0[2];
extern s8* palette_animator_scripts_s06_1[4];
extern s8* palette_animator_scripts_s07_1[3];
extern s8* palette_animator_scripts_s08_1[2];
extern s8* palette_animator_scripts_s09_0[1];
extern s8* palette_animator_scripts_s10_0[3];
extern s8* palette_animator_scripts_s11_0[4];
extern s8* palette_animator_scripts_s11_1[4];
extern s8* palette_animator_scripts_s12_0[3];
extern s8* palette_animator_scripts_s12_1[3];
extern s8* palette_animator_scripts_s13_0[1];
extern u16 palette_animator_timings_s00_0[10];
extern u16 palette_animator_timings_s00_1[4];
extern u16 palette_animator_timings_s01_0[6];
extern u16 palette_animator_timings_s01_1[6];
extern u16 palette_animator_timings_s02_0[4];
extern u16 palette_animator_timings_s02_1[10];
extern u16 palette_animator_timings_s03_0[2];
extern u16 palette_animator_timings_s03_1[4];
extern u16 palette_animator_timings_s04_0[6];
extern u16 palette_animator_timings_s04_1[8];
extern u16 palette_animator_timings_s05_0[4];
extern u16 palette_animator_timings_s05_1[6];
extern u16 palette_animator_timings_s06_0[2];
extern u16 palette_animator_timings_s06_1[4];
extern u16 palette_animator_timings_s07_1[4];
extern u16 palette_animator_timings_s08_1[2];
extern u16 palette_animator_timings_s09_0[2];
extern u16 palette_animator_timings_s10_0[4];
extern u16 palette_animator_timings_s11_0[4];
extern u16 palette_animator_timings_s11_1[4];
extern u16 palette_animator_timings_s12_0[4];
extern u16 palette_animator_timings_s12_1[4];
extern u16 palette_animator_timings_s13_0[2];

u16* palette_animator_stage_timings[27] = {
    palette_animator_timings_s00_0,
    palette_animator_timings_s00_1,
    palette_animator_timings_s01_0,
    palette_animator_timings_s01_1,
    palette_animator_timings_s02_0,
    palette_animator_timings_s02_1,
    palette_animator_timings_s03_0,
    palette_animator_timings_s03_1,
    palette_animator_timings_s04_0,
    palette_animator_timings_s04_1,
    palette_animator_timings_s05_0,
    palette_animator_timings_s05_1,
    palette_animator_timings_s06_0,
    palette_animator_timings_s06_1,
    NULL,
    palette_animator_timings_s07_1,
    NULL,
    palette_animator_timings_s08_1,
    palette_animator_timings_s09_0,
    NULL,
    palette_animator_timings_s10_0,
    NULL,
    palette_animator_timings_s11_0,
    palette_animator_timings_s11_1,
    palette_animator_timings_s12_0,
    palette_animator_timings_s12_1,
    palette_animator_timings_s13_0,
};

s8** palette_animator_stage_scripts[27] = {
    palette_animator_scripts_s00_0,
    palette_animator_scripts_s00_1,
    palette_animator_scripts_s01_0,
    palette_animator_scripts_s01_1,
    palette_animator_scripts_s02_0,
    palette_animator_scripts_s02_1,
    palette_animator_scripts_s03_0,
    palette_animator_scripts_s03_1,
    palette_animator_scripts_s04_0,
    palette_animator_scripts_s04_1,
    palette_animator_scripts_s05_0,
    palette_animator_scripts_s05_1,
    palette_animator_scripts_s06_0,
    palette_animator_scripts_s06_1,
    NULL,
    palette_animator_scripts_s07_1,
    NULL,
    palette_animator_scripts_s08_1,
    palette_animator_scripts_s09_0,
    NULL,
    palette_animator_scripts_s10_0,
    NULL,
    palette_animator_scripts_s11_0,
    palette_animator_scripts_s11_1,
    palette_animator_scripts_s12_0,
    palette_animator_scripts_s12_1,
    palette_animator_scripts_s13_0,
};

void (*D_8010B42C[])(struct EffectObj*) = {
    func_800B5D04,
    palette_animator_step,
};
