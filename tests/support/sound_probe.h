#ifndef MMX4_TESTS_SOUND_PROBE_H
#define MMX4_TESTS_SOUND_PROBE_H

#include "main/55C4.h"
extern u32* D_80137E08;
static u32 sound_probe_rows[0x100];

static void sound_probe_begin_group(u32 group)
{
    memset(sound_probe_rows, 0, sizeof(sound_probe_rows));
    memset(D_8013E198, -1, sizeof(D_8013E198));
    D_8013E198[group] = 0;
    D_80141F50[group] = (u8*)sound_probe_rows;
    D_80141EE8[group] = (u8*)&sound_probe_rows[0xFF];
    D_80137E08 = NULL;
}

static void sound_probe_begin(void)
{
    sound_probe_begin_group(2);
}

static s32 sound_probe_id(void)
{
    return D_80137E08 == NULL ? -1 : (s32)(D_80137E08 - sound_probe_rows);
}

#ifdef MMX4_SATURN
#define SOUND_CHECK(expression) ((void)0)
#else
#define SOUND_CHECK(expression) assert(expression)
#endif

#endif
