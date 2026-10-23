#ifndef MMX4_SATURN_WEAPON_RESOURCES_H
#define MMX4_SATURN_WEAPON_RESOURCES_H

#include "saturn/player_resources.h"
extern u32 saturn_frame_counter;
#define WEAPON_FRAME_COUNTER saturn_frame_counter
void saturn_music_play(s32 track, s32 arg);
void saturn_music_stop(void);
void saturn_music_request(s32 track, s32 arg1, s32 arg2, s32 arg3);
void saturn_archive_queue_push(const char* path, s32 indicator);
extern u8 saturn_archive_queue_busy;
extern s16 saturn_music_fading;
struct QuadObj;
void saturn_queue_frozen_quad(struct QuadObj*);

#endif
