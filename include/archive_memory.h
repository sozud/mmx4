#ifndef ARCHIVE_MEMORY_H
#define ARCHIVE_MEMORY_H

#ifdef MMX4_PC
extern u8 pc_archive_arena[0x88000];
extern u8 replay_data[0x2000];
extern u8 window_archive_data[0x3000];
#define MAIN_ARCHIVE_ARENA pc_archive_arena
#define REPLAY_DATA replay_data
#define WINDOW_ARCHIVE_DATA window_archive_data
#elif defined(MMX4_WIN32)
extern u8* win32_main_ram;
#define MAIN_ARCHIVE_ARENA (win32_main_ram + 0x178000)
#define REPLAY_DATA (win32_main_ram + 0x1F6000)
#define WINDOW_ARCHIVE_DATA (win32_main_ram + 0x1F3000)
#elif defined(MMX4_SATURN)
extern u8 saturn_demo_data[];
#define REPLAY_DATA saturn_demo_data
#elif defined(MMX4_BIG_ENDIAN)
extern u8 gc_archive_arena[];
extern u8 gc_replay_data[0x2000];
#define MAIN_ARCHIVE_ARENA gc_archive_arena
#define REPLAY_DATA gc_replay_data
extern u8 gc_window_archive_data[0x3000];
#define WINDOW_ARCHIVE_DATA gc_window_archive_data
#else
#ifdef VERSION_DEMO
#define MAIN_ARCHIVE_ARENA ((u8*)0x80140000)
#else
#define MAIN_ARCHIVE_ARENA ((u8*)0x80178000)
#endif
#define REPLAY_DATA ((u8*)0x801F6000)
#define WINDOW_ARCHIVE_DATA ((u8*)0x801F3000)
#endif

#endif
