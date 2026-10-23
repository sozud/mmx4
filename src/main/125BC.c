// 80021DBC..80021E3C
#include "common.h"

struct FixedMatrix2 {
    s16 m00, m01;
    s16 m10, m11;
};

extern struct FixedMatrix2 D_800F2ADC[16];

void func_80021DBC(s16* arg0, s16* arg1, s32 arg2)
{
    struct FixedMatrix2* matrix;
    s16 x;
    s16 y;
    s32 product0;
    s32 product1;
    s32 product2;
    s32 product3;

    matrix = &D_800F2ADC[arg2 & 0xFF];
    x = *arg0;
    y = *arg1;
    product0 = x * matrix->m00;
    product1 = y * matrix->m01;
    product2 = x * matrix->m10;
    product3 = y * matrix->m11;
    *arg0 = (product0 >> 8) + (product1 >> 8);
    *arg1 = (product2 >> 8) + (product3 >> 8);
}

struct FixedMatrix2 D_800F2ADC[16] = {
    { 256, 0, 0, 256 },
    { 236, 97, -97, 236 },
    { 180, 180, -180, 180 },
    { 97, 236, -236, 97 },
    { 0, 256, -256, 0 },
    { -97, 236, -236, -97 },
    { -180, 180, -180, -180 },
    { -236, 97, -97, -236 },
    { -256, 0, 0, -256 },
    { -236, -97, 97, -236 },
    { -180, -180, 180, -180 },
    { -97, -236, 236, -97 },
    { 0, -256, 256, 0 },
    { 97, -236, 236, 97 },
    { 180, -180, 180, 180 },
    { 236, -97, 97, 236 },
};
