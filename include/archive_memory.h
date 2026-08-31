#ifndef ARCHIVE_MEMORY_H
#define ARCHIVE_MEMORY_H

#ifdef MMX4_PC
extern u8 pc_archive_arena[0x88000];
extern u8 replay_data[0x1CF4];
extern u8 window_archive_data[0x3000];
#define MAIN_ARCHIVE_ARENA pc_archive_arena
#define REPLAY_DATA replay_data
#define WINDOW_ARCHIVE_DATA window_archive_data
#else
#define MAIN_ARCHIVE_ARENA ((u8*)0x80178000)
#define REPLAY_DATA ((u8*)0x801F6000)
#define WINDOW_ARCHIVE_DATA ((u8*)0x801F3000)
#endif

#endif
