#ifndef MMX4_PC_SATURN_EXTRAS_H
#define MMX4_PC_SATURN_EXTRAS_H

int mmx4_pc_saturn_music_open(const char* path);
int mmx4_pc_saturn_music_enabled(void);
void mmx4_pc_saturn_music_select(int psx_track);
void mmx4_pc_saturn_music_set_playing(int playing);

struct Mmx4PcLineScroll {
    u32 vdp2[0x40];
    s32 work[512];
    s32 table[512];
};
extern int mmx4_pc_saturn_heat;
extern struct Mmx4PcLineScroll mmx4_pc_line_scroll;
void mmx4_pc_line_scroll_commit(void);
void mmx4_pc_line_scroll_alive(void);
void mmx4_pc_line_scroll_reset(void);
int mmx4_pc_line_scroll_active(void);
int mmx4_pc_heat_plane_for(s32 stage, s32 substage, s32 layer);
int mmx4_pc_heat_layer_plane(s32 layer);
struct StageObjectRecord* mmx4_pc_saturn_heat_records(s32 stage, s32 substage);
int mmx4_pc_heat_line_offsets(int plane, s32 scroll_x, s32 scroll_y, s32* world_x, s32* world_y, int lines);

#endif
