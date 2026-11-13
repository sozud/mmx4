#ifndef MAIN_QUADS_QUAD_16_SIGMA_LASER_H
#define MAIN_QUADS_QUAD_16_SIGMA_LASER_H

void sigma_laser_update(struct QuadObj* arg0);

void func_800D845C(struct QuadObj*);

void func_800D802C(struct QuadObj*);

#ifdef MMX4_PC
// one array on PC: the PSX code reads past the origin pair into the sweep table
extern s16 sigma_laser_offsets[16][2];
#define sigma_laser_origin_offsets sigma_laser_offsets
#define sigma_laser_sweep_offsets (sigma_laser_offsets + 2)
#else
extern s16 sigma_laser_sweep_offsets[14][2];
#endif

#endif
