#include "common.h"
#include "main/player_animations_2.h"

u8 D_8011A030[256] = {
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x01,
    0x01,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x03,
    0x04,
    0x04,
    0x04,
    0x04,
    0x03,
    0x03,
    0x03,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x01,
    0x01,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x01,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x00,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x00,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x04,
    0x04,
    0x00,
    0x04,
    0x00,
    0x04,
    0x00,
    0x04,
    0x00,
    0x04,
    0x00,
    0x03,
    0x00,
    0x03,
    0x00,
    0x03,
    0x00,
    0x03,
    0x00,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

u8 D_8011A130[256] = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x02,
    0x02,
    0x00,
    0x02,
    0x02,
    0x00,
    0x02,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x01,
    0x01,
    0x01,
    0x00,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x01,
    0x00,
    0x01,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x00,
    0x01,
    0x00,
    0x00,
    0x01,
    0x00,
    0x00,
    0x01,
    0x00,
    0x00,
    0x01,
    0x01,
    0x01,
    0x01,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x01,
    0x00,
    0x05,
    0x00,
    0x05,
    0x00,
    0x05,
    0x00,
    0x05,
    0x00,
    0x05,
    0x00,
    0x02,
    0x00,
    0x02,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x02,
    0x00,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

struct Unk_unk68 D_8011A230[6] = {
    { 0, 0, 0, 0 },
    { -10, -17, 21, 39 },
    { -10, -17, 21, 30 },
    { -8, -12, 18, 35 },
    { -14, -6, 26, 28 },
    { -18, -17, 21, 30 },
};

union AnimationStep D_8011A248[2] = {
    { 2, 0, 1, 0x35 },
    { 2, 0, -1, 0x36 },
};

union AnimationStep D_8011A250[14] = {
    { 2, 0, 1, 0x37 },
    { 2, 0, 1, 0x38 },
    { 2, 0, 1, 0x39 },
    { 2, 0, 1, 0x3A },
    { 2, 0, 1, 0x3B },
    { 2, 0, 1, 0x3C },
    { 2, 0, 1, 0xF7 },
    { 2, 0, 1, 0xF8 },
    { 2, 0, 1, 0xF9 },
    { 3, 0, 1, 0xFA },
    { 12, 0, 1, 0xFB },
    { 3, 0, 1, 0xFC },
    { 3, 0, 1, 0xFD },
    { 96, 0, 0, 0xFD },
};

union AnimationStep D_8011A288[11] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 0, 0x0B },
};

union AnimationStep D_8011A2B4[2] = {
    { 2, 0, 1, 0x0C },
    { 2, 0, -1, 0x0D },
};

union AnimationStep D_8011A2BC[8] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 3, 0, 1, 0x04 },
    { 6, 0, 1, 0x05 },
    { 48, -128, 1, 0x06 },
    { 96, 0, 0, 0x06 },
};

union AnimationStep D_8011A2DC[7] = {
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 96, 0, 0, 0x0B },
};

union AnimationStep D_8011A2F8[12] = {
    { 21, 0, 1, 0x00 },
    { 12, 0, 1, 0x92 },
    { 42, 0, 1, 0x93 },
    { 12, 0, 1, 0x94 },
    { 54, 0, 1, 0x00 },
    { 12, 0, 1, 0x92 },
    { 42, 0, 1, 0x93 },
    { 12, 0, 1, 0x94 },
    { 24, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, -11, 0x01 },
};

union AnimationStep D_8011A328[10] = {
    { 12, 0, 1, 0x95 },
    { 14, 0, 1, 0x97 },
    { 12, 0, 1, 0x96 },
    { 6, 0, 1, 0x98 },
    { 8, 0, 1, 0x99 },
    { 12, 0, 1, 0x95 },
    { 14, 0, 1, 0x97 },
    { 12, 0, 1, 0x96 },
    { 6, 0, 1, 0x98 },
    { 8, 0, -9, 0x9A },
};

union AnimationStep D_8011A350[3] = {
    { 3, 0, 1, 0x03 },
    { 3, 1, 1, 0x04 },
    { 96, 2, -1, 0x04 },
};

union AnimationStep D_8011A35C[14] = {
    { 2, 0, 1, 0x07 },
    { 3, 1, 1, 0x08 },
    { 2, 2, 1, 0x09 },
    { 2, 3, 1, 0x0A },
    { 2, 4, 1, 0x0B },
    { 3, 5, 1, 0x0C },
    { 2, 6, 1, 0x0D },
    { 2, 7, 1, 0x0E },
    { 3, 8, 1, 0x0F },
    { 2, 9, 1, 0x10 },
    { 2, 10, 1, 0x11 },
    { 2, 11, 1, 0x12 },
    { 3, 12, 1, 0x13 },
    { 2, 13, -13, 0x14 },
};

union AnimationStep D_8011A394[3] = {
    { 4, 0, 1, 0x05 },
    { 4, 1, 1, 0x06 },
    { 96, 2, -1, 0x06 },
};

union AnimationStep D_8011A3A0[16] = {
    { 3, 0, 1, 0x03 },
    { 3, 0, 1, 0x04 },
    { 2, 1, 1, 0x07 },
    { 3, 1, 1, 0x08 },
    { 2, 1, 1, 0x09 },
    { 2, 1, 1, 0x0A },
    { 2, 1, 1, 0x0B },
    { 3, 1, 1, 0x0C },
    { 2, 1, 1, 0x0D },
    { 2, 1, 1, 0x0E },
    { 3, 1, 1, 0x0F },
    { 2, 1, 1, 0x10 },
    { 2, 1, 1, 0x11 },
    { 2, 1, 1, 0x12 },
    { 3, 1, 1, 0x13 },
    { 2, 1, -13, 0x14 },
};

union AnimationStep D_8011A3E0[5] = {
    { 3, 0, 1, 0x15 },
    { 4, -127, 1, 0x16 },
    { 3, 2, 1, 0x17 },
    { 4, 3, 1, 0x16 },
    { 3, 4, -1, 0x17 },
};

union AnimationStep D_8011A3F4[9] = {
    { 3, 0, 1, 0x18 },
    { 3, 1, 1, 0x19 },
    { 3, 2, 1, 0x1A },
    { 3, 3, 1, 0x1B },
    { 3, 4, 1, 0x1C },
    { 4, 5, 1, 0x1D },
    { 3, 6, 1, 0x1E },
    { 4, 7, 1, 0x1F },
    { 3, 8, -3, 0x20 },
};

union AnimationStep D_8011A418[3] = {
    { 4, 0, 1, 0x21 },
    { 5, 1, 1, 0x22 },
    { 96, 2, -1, 0x22 },
};

union AnimationStep D_8011A424[4] = {
    { 2, 0, 1, 0x23 },
    { 2, -127, 1, 0x26 },
    { 2, 2, 1, 0x27 },
    { 96, 3, 0, 0x28 },
};

union AnimationStep D_8011A434[5] = {
    { 3, 0, 1, 0x23 },
    { 3, 1, 1, 0x24 },
    { 3, 2, 1, 0x25 },
    { 4, 3, 1, 0x16 },
    { 3, 4, -1, 0x17 },
};

union AnimationStep D_8011A448[3] = {
    { 2, 0, 1, 0x29 },
    { 2, 1, 1, 0x2A },
    { 2, 2, -2, 0x2B },
};

union AnimationStep D_8011A454[11] = {
    { 1, 0, 1, 0x03 },
    { 1, 1, 1, 0x04 },
    { 2, 34, 1, 0x2C },
    { 1, 3, 1, 0x2D },
    { 1, -124, 1, 0x2D },
    { 2, 69, 1, 0x2E },
    { 2, 6, 1, 0x2F },
    { 2, 7, 1, 0x30 },
    { 2, 8, 1, 0x2E },
    { 2, 9, 1, 0x2F },
    { 2, 10, -2, 0x30 },
};

union AnimationStep D_8011A480[5] = {
    { 3, 64, 1, 0x31 },
    { 2, 65, 1, 0x32 },
    { 7, -62, 1, 0x33 },
    { 5, 3, 1, 0x34 },
    { 96, 4, -1, 0x34 },
};

union AnimationStep D_8011A494[9] = {
    { 3, 0, 1, 0x2C },
    { 1, 1, 1, 0x2D },
    { 1, -126, 1, 0x2D },
    { 2, 67, 1, 0x2E },
    { 2, 4, 1, 0x2F },
    { 2, 5, 1, 0x30 },
    { 2, 6, 1, 0x2E },
    { 2, 7, 1, 0x2F },
    { 2, 8, -2, 0x30 },
};

union AnimationStep D_8011A4B8[3] = {
    { 3, 0, 1, 0x2D },
    { 4, 1, 1, 0x2C },
    { 96, 2, -1, 0x2C },
};

union AnimationStep D_8011A4C4[9] = {
    { 3, 0, 1, 0x18 },
    { 3, 1, 1, 0x19 },
    { 3, 2, 1, 0x1A },
    { 3, 3, 1, 0x1B },
    { 3, 4, 1, 0x1C },
    { 4, 5, 1, 0x1D },
    { 3, 6, 1, 0x1E },
    { 4, 7, 1, 0x1F },
    { 3, 8, -3, 0x20 },
};

union AnimationStep D_8011A4E8[4] = {
    { 3, 0, 1, 0xC2 },
    { 3, 0, 1, 0xB8 },
    { 3, 0, 1, 0xBB },
    { 96, 0, -1, 0xBB },
};

union AnimationStep D_8011A4F8[5] = {
    { 5, 0, 1, 0xBE },
    { 5, 0, 1, 0xBF },
    { 5, -128, 1, 0xC0 },
    { 5, 0, 1, 0xC1 },
    { 96, 0, -1, 0xC1 },
};

union AnimationStep D_8011A50C[4] = {
    { 5, 0, 1, 0xC0 },
    { 5, -128, 1, 0xBF },
    { 5, 0, 1, 0xBE },
    { 96, 0, -1, 0xBE },
};

union AnimationStep D_8011A51C[2] = {
    { 5, 0, 1, 0xC2 },
    { 96, 0, -1, 0xC2 },
};

union AnimationStep D_8011A524[10] = {
    { 2, 0, 1, 0xAE },
    { 4, 1, 1, 0xAF },
    { 5, 9, 1, 0xB2 },
    { 5, 8, 1, 0xB6 },
    { 5, 7, 1, 0xBA },
    { 2, 6, 1, 0xB0 },
    { 4, 5, 1, 0xB1 },
    { 5, 4, 1, 0xB4 },
    { 5, 3, 1, 0xB8 },
    { 5, 2, -9, 0xBB },
};

union AnimationStep D_8011A54C[10] = {
    { 2, 0, 1, 0xAE },
    { 4, 1, 1, 0xAF },
    { 5, 9, 1, 0xBD },
    { 5, 8, 1, 0xB9 },
    { 5, 7, 1, 0xB5 },
    { 2, 6, 1, 0xB0 },
    { 4, 5, 1, 0xB1 },
    { 5, 4, 1, 0xBC },
    { 5, 3, 1, 0xB7 },
    { 5, 2, -9, 0xB3 },
};

union AnimationStep D_8011A574[4] = {
    { 2, 0, 1, 0x87 },
    { 2, 0, 1, 0x8A },
    { 2, 0, 1, 0x88 },
    { 2, 0, -3, 0x89 },
};

union AnimationStep D_8011A584[20] = {
    { 2, 0, 1, 0x87 },
    { 2, 0, 1, 0x8B },
    { 2, 0, 1, 0x8E },
    { 2, 0, 1, 0x8F },
    { 2, 0, 1, 0x8C },
    { 2, 0, 1, 0x90 },
    { 2, 0, 1, 0x8E },
    { 2, 0, 1, 0x91 },
    { 2, 0, 1, 0x8D },
    { 2, 0, 1, 0x8B },
    { 2, 0, 1, 0x8E },
    { 2, 0, 1, 0x8F },
    { 2, 0, 1, 0x8C },
    { 2, 0, 1, 0x90 },
    { 2, 0, 1, 0x8E },
    { 2, 0, 1, 0x91 },
    { 2, 0, 1, 0x8D },
    { 2, 0, 1, 0x8B },
    { 2, 0, 1, 0x8E },
    { 96, 0, 0, 0x87 },
};

union AnimationStep D_8011A5D4[1] = {
    { 96, 0, 0, 0x87 },
};

union AnimationStep D_8011A5D8[9] = {
    { 2, 0, 1, 0x87 },
    { 2, 0, 1, 0x8A },
    { 2, 0, 1, 0x88 },
    { 2, 0, 1, 0x89 },
    { 2, 0, 1, 0x87 },
    { 2, 0, 1, 0x8A },
    { 2, 0, 1, 0x88 },
    { 1, 0, 1, 0x89 },
    { 96, 0, -1, 0x89 },
};

union AnimationStep D_8011A5FC[4] = {
    { 100, 0, 1, 0x42 },
    { 7, 0, 1, 0x43 },
    { 50, 0, 1, 0x46 },
    { 8, 0, -3, 0x43 },
};

union AnimationStep D_8011A60C[8] = {
    { 6, 0, 1, 0x43 },
    { 6, 0, 1, 0x44 },
    { 6, 0, 1, 0x45 },
    { 10, 0, 1, 0x44 },
    { 6, 0, 1, 0x43 },
    { 6, 0, 1, 0x44 },
    { 6, 0, 1, 0x45 },
    { 10, 0, -7, 0x44 },
};

union AnimationStep D_8011A62C[1] = {
    { 96, 0, 0, 0x51 },
};

union AnimationStep D_8011A630[1] = {
    { 96, 0, 0, 0x42 },
};

union AnimationStep D_8011A634[4] = {
    { 2, 0, 1, 0x43 },
    { 8, 0, 1, 0x46 },
    { 7, 0, 1, 0x43 },
    { 96, 0, 0, 0x42 },
};

union AnimationStep D_8011A644[1] = {
    { 96, 0, 0, 0x47 },
};

union AnimationStep D_8011A648[1] = {
    { 96, 0, 0, 0x49 },
};

union AnimationStep D_8011A64C[1] = {
    { 96, 0, 0, 0x47 },
};

union AnimationStep D_8011A650[8] = {
    { 1, 0, 1, 0x4B },
    { 1, 0, 1, 0x4B },
    { 2, 0, 1, 0x4C },
    { 2, 0, 1, 0x4C },
    { 2, 0, 1, 0x4C },
    { 2, 0, 1, 0x4C },
    { 3, 0, 1, 0x4B },
    { 96, 0, 0, 0x4B },
};

union AnimationStep D_8011A670[16] = {
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x50 },
    { 1, 0, 1, 0x4B },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4D },
    { 10, 0, 1, 0x4D },
    { 5, 0, 1, 0x4C },
    { 96, 0, 0, 0x4B },
};

union AnimationStep D_8011A6B0[15] = {
    { 1, 0, 1, 0x46 },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x50 },
    { 1, 0, 1, 0x4B },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4D },
    { 6, 0, 1, 0x4D },
    { 6, 0, 1, 0x4C },
    { 96, 0, 0, 0x4B },
};

union AnimationStep D_8011A6EC[2] = {
    { 5, 0, 1, 0x49 },
    { 96, 0, 0, 0x4E },
};

union AnimationStep D_8011A6F4[3] = {
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4F },
    { 96, 0, 0, 0x4F },
};

union AnimationStep D_8011A700[3] = {
    { 1, 0, 1, 0x4B },
    { 1, 0, 1, 0x4C },
    { 96, 0, 0, 0x4C },
};

union AnimationStep D_8011A70C[3] = {
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4D },
    { 96, 0, 0, 0x4D },
};

union AnimationStep D_8011A718[3] = {
    { 5, 0, 1, 0x4C },
    { 2, 0, 1, 0x4C },
    { 96, 0, 0, 0x4B },
};

union AnimationStep D_8011A724[7] = {
    { 10, 0, 1, 0x54 },
    { 10, 0, 1, 0x55 },
    { 10, 0, 1, 0x53 },
    { 10, 0, 1, 0x52 },
    { 5, 0, 1, 0x42 },
    { 6, 0, 1, 0x4A },
    { 96, 0, 0, 0x42 },
};

union AnimationStep D_8011A740[1] = {
    { 96, 0, 0, 0x42 },
};

union AnimationStep D_8011A744[1] = {
    { 96, 0, 0, 0x51 },
};

union AnimationStep D_8011A748[3] = {
    { 5, 0, 1, 0x43 },
    { 8, 0, 1, 0x46 },
    { 96, 0, 0, 0x43 },
};

union AnimationStep D_8011A754[1] = {
    { 96, 0, 0, 0x43 },
};

union AnimationStep D_8011A758[4] = {
    { 3, 0, 1, 0x10 },
    { 3, 0, 1, 0x11 },
    { 3, 0, 1, 0x0E },
    { 3, 0, -3, 0x0F },
};

union AnimationStep D_8011A768[10] = {
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x12 },
    { 6, 0, 1, 0x13 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x0E },
    { 3, 0, 1, 0x15 },
    { 3, 0, 1, 0x10 },
    { 3, 0, 1, 0x11 },
    { 3, 0, 1, 0x0E },
    { 3, 0, -3, 0x0F },
};

union AnimationStep D_8011A790[4] = {
    { 3, 0, 1, 0x18 },
    { 3, 0, 1, 0x19 },
    { 3, 0, 1, 0x16 },
    { 3, 0, -3, 0x17 },
};

union AnimationStep D_8011A7A0[10] = {
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x1A },
    { 6, 0, 1, 0x1B },
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x16 },
    { 3, 0, 1, 0x1D },
    { 3, 0, 1, 0x18 },
    { 3, 0, 1, 0x19 },
    { 3, 0, 1, 0x16 },
    { 3, 0, -3, 0x17 },
};

union AnimationStep D_8011A7C8[4] = {
    { 3, 0, 1, 0x20 },
    { 3, 0, 1, 0x21 },
    { 3, 0, 1, 0x1E },
    { 3, 0, -3, 0x1F },
};

union AnimationStep D_8011A7D8[10] = {
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x22 },
    { 6, 0, 1, 0x23 },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1E },
    { 3, 0, 1, 0x25 },
    { 3, 0, 1, 0x20 },
    { 3, 0, 1, 0x21 },
    { 3, 0, 1, 0x1E },
    { 3, 0, -3, 0x1F },
};

union AnimationStep D_8011A800[7] = {
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x20 },
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x28 },
    { 2, 0, -3, 0x29 },
};

union AnimationStep D_8011A81C[8] = {
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x20 },
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x28 },
    { 2, 0, -3, 0x29 },
};

union AnimationStep D_8011A83C[6] = {
    { 2, 0, 1, 0x20 },
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x28 },
    { 2, 0, -3, 0x29 },
};

union AnimationStep D_8011A854[3] = {
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x1F },
    { 96, 0, 0, 0x10 },
};

union AnimationStep D_8011A860[4] = {
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x10 },
    { 96, 0, 0, 0x19 },
};

union AnimationStep D_8011A870[2] = {
    { 2, 0, 1, 0x26 },
    { 96, 0, 0, 0x1F },
};

union AnimationStep D_8011A878[2] = {
    { 2, 0, 1, 0x2A },
    { 2, 0, -1, 0x2B },
};

union AnimationStep D_8011A880[2] = {
    { 2, 0, 1, 0x2C },
    { 2, 0, -1, 0x2D },
};

union AnimationStep D_8011A888[2] = {
    { 2, 0, 1, 0x2E },
    { 2, 0, -1, 0x2F },
};

union AnimationStep D_8011A890[2] = {
    { 2, 0, 1, 0x30 },
    { 2, 0, -1, 0x31 },
};

union AnimationStep D_8011A898[18] = {
    { 1, 0, 1, 0x3D },
    { 1, 0, 1, 0x3E },
    { 1, -128, 1, 0x3F },
    { 1, 0, 1, 0x41 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 1, 0x45 },
    { 2, 0, 1, 0x47 },
    { 2, 32, 1, 0x49 },
    { 2, 32, 1, 0x4B },
    { 3, 32, 1, 0x4D },
    { 4, 32, 1, 0x4F },
    { 2, 0, 1, 0x51 },
    { 2, 64, 1, 0x52 },
    { 2, 64, 1, 0x83 },
    { 4, 64, 1, 0x84 },
    { 6, 64, 1, 0x85 },
    { 4, 64, 1, 0x86 },
    { 96, 64, 0, 0x86 },
};

union AnimationStep D_8011A8E0[17] = {
    { 2, 0, 1, 0x53 },
    { 1, 0, 1, 0x55 },
    { 2, 0, 1, 0x57 },
    { 2, 0, 1, 0x59 },
    { 1, 0, 1, 0x5B },
    { 2, 32, 1, 0x5D },
    { 2, 32, 1, 0x5F },
    { 2, 32, 1, 0x61 },
    { 2, 32, 1, 0x63 },
    { 3, 32, 1, 0x65 },
    { 4, 32, 1, 0x65 },
    { 2, 0, 1, 0x65 },
    { 2, 64, 1, 0x83 },
    { 4, 64, 1, 0x84 },
    { 6, 64, 1, 0x85 },
    { 4, 64, 1, 0x86 },
    { 96, 64, 0, 0x86 },
};

union AnimationStep D_8011A924[19] = {
    { 1, 0, 1, 0x69 },
    { 1, 0, 1, 0x6B },
    { 1, 0, 1, 0x6D },
    { 1, 0, 1, 0x6F },
    { 2, 0, 1, 0x71 },
    { 1, 0, 1, 0x73 },
    { 1, 0, 1, 0x75 },
    { 1, 0, 1, 0x77 },
    { 2, 0, 1, 0x79 },
    { 2, 0, 1, 0x7B },
    { 3, 0, 1, 0x7D },
    { 4, 0, 1, 0x7F },
    { 6, 0, 1, 0x7F },
    { 4, 64, 1, 0x82 },
    { 2, 64, 1, 0x83 },
    { 4, 64, 1, 0x84 },
    { 6, 64, 1, 0x85 },
    { 4, 64, 1, 0x86 },
    { 96, 64, 0, 0x86 },
};

union AnimationStep D_8011A970[10] = {
    { 1, 1, 1, 0x40 },
    { 1, 2, 1, 0x42 },
    { 1, 3, 1, 0x44 },
    { 1, 4, 1, 0x46 },
    { 2, 5, 1, 0x48 },
    { 2, 0, 1, 0x4A },
    { 2, 0, 1, 0x4C },
    { 3, 0, 1, 0x4E },
    { 4, 0, 1, 0x50 },
    { 96, 0, 0, 0x50 },
};

union AnimationStep D_8011A998[12] = {
    { 2, 0, 1, 0x54 },
    { 1, 6, 1, 0x56 },
    { 2, 7, 1, 0x58 },
    { 2, 8, 1, 0x5A },
    { 1, 9, 1, 0x5C },
    { 2, 10, 1, 0x5E },
    { 2, 0, 1, 0x60 },
    { 2, 0, 1, 0x62 },
    { 2, 0, 1, 0x64 },
    { 3, 0, 1, 0x66 },
    { 4, 0, 1, 0x67 },
    { 96, 0, 0, 0x67 },
};

union AnimationStep D_8011A9C8[13] = {
    { 1, 0, 1, 0x6A },
    { 1, 0, 1, 0x6C },
    { 1, 11, 1, 0x6E },
    { 1, 12, 1, 0x70 },
    { 2, 13, 1, 0x72 },
    { 1, 14, 1, 0x74 },
    { 1, 15, 1, 0x76 },
    { 1, 16, 1, 0x78 },
    { 2, 0, 1, 0x7A },
    { 2, 0, 1, 0x7C },
    { 3, 0, 1, 0x7E },
    { 4, 0, 1, 0x80 },
    { 96, 0, 0, 0x80 },
};

union AnimationStep D_8011A9FC[10] = {
    { 1, -128, 1, 0xD5 },
    { 1, 1, 1, 0xD7 },
    { 1, 2, 1, 0xD9 },
    { 1, 3, 1, 0xDB },
    { 1, 4, 1, 0xDD },
    { 1, 5, 1, 0xDF },
    { 1, 6, 1, 0xE1 },
    { 2, 7, 1, 0xE3 },
    { 4, 72, 1, 0xE5 },
    { 96, 73, 0, 0xE5 },
};

union AnimationStep D_8011AA24[9] = {
    { 1, 0, 1, 0xD6 },
    { 1, 0, 1, 0xD8 },
    { 1, 25, 1, 0xDA },
    { 1, 26, 1, 0xDC },
    { 1, 27, 1, 0xDE },
    { 1, 28, 1, 0xE0 },
    { 1, 0, 1, 0xE2 },
    { 2, 0, 1, 0xE4 },
    { 96, 0, 0, 0xE4 },
};

union AnimationStep D_8011AA48[10] = {
    { 1, -128, 1, 0xE6 },
    { 1, 1, 1, 0xE8 },
    { 1, 2, 1, 0xEA },
    { 1, 3, 1, 0xEC },
    { 1, 4, 1, 0xEE },
    { 1, 5, 1, 0xF0 },
    { 1, 6, 1, 0xF2 },
    { 2, 7, 1, 0xF4 },
    { 4, 72, 1, 0xF6 },
    { 96, 73, 0, 0xF6 },
};

union AnimationStep D_8011AA70[9] = {
    { 1, 0, 1, 0xE7 },
    { 1, 0, 1, 0xE9 },
    { 1, 29, 1, 0xEB },
    { 1, 30, 1, 0xED },
    { 1, 31, 1, 0xEF },
    { 1, 32, 1, 0xF1 },
    { 1, 0, 1, 0xF3 },
    { 2, 0, 1, 0xF5 },
    { 96, 0, 0, 0xF5 },
};

union AnimationStep D_8011AA94[14] = {
    { 2, 0, 1, 0xC3 },
    { 1, -128, 1, 0xC5 },
    { 1, 0, 1, 0xC7 },
    { 2, 0, 1, 0xCA },
    { 2, 0, 1, 0xCC },
    { 2, 0, 1, 0xCE },
    { 2, 0, 1, 0xD0 },
    { 2, 0, 1, 0xD2 },
    { 2, 0, 1, 0xC9 },
    { 2, 64, 1, 0xD4 },
    { 3, 64, 1, 0xC4 },
    { 2, 64, 1, 0xAE },
    { 4, 64, 1, 0xAF },
    { 96, 64, 0, 0xAF },
};

union AnimationStep D_8011AACC[8] = {
    { 1, 0, 1, 0xC6 },
    { 1, 22, 1, 0xC8 },
    { 2, 23, 1, 0xCB },
    { 2, 24, 1, 0xCD },
    { 2, 0, 1, 0xCF },
    { 2, 0, 1, 0xD1 },
    { 2, 0, 1, 0xD3 },
    { 96, 0, 0, 0xD3 },
};

union AnimationStep D_8011AAEC[12] = {
    { 4, 0, 1, 0x32 },
    { 1, -128, 1, 0x33 },
    { 1, 0, 1, 0x36 },
    { 2, 0, 1, 0x39 },
    { 2, 0, 1, 0x3B },
    { 3, 0, 1, 0x3D },
    { 4, 0, 1, 0x3F },
    { 3, 0, 1, 0x41 },
    { 2, 64, 1, 0x38 },
    { 3, 64, 1, 0x35 },
    { 4, 64, 1, 0x32 },
    { 96, 64, 0, 0x32 },
};

union AnimationStep D_8011AB1C[7] = {
    { 1, 0, 1, 0x34 },
    { 1, 33, 1, 0x37 },
    { 2, 34, 1, 0x3A },
    { 2, 35, 1, 0x3C },
    { 3, 0, 1, 0x3E },
    { 4, 0, 1, 0x40 },
    { 96, 0, 0, 0x40 },
};

union AnimationStep D_8011AB38[45] = {
    { 2, 0, 1, 0x56 },
    { 2, 0, 1, 0x57 },
    { 2, 0, 1, 0x58 },
    { 2, -128, 1, 0x5B },
    { 2, 0, 1, 0x57 },
    { 2, 0, 1, 0x57 },
    { 2, 0, 1, 0x5D },
    { 2, 0, 1, 0x57 },
    { 2, 0, 1, 0x57 },
    { 2, 0, 1, 0x5D },
    { 2, 16, 1, 0x60 },
    { 2, 0, 1, 0x63 },
    { 2, 0, 1, 0x65 },
    { 2, 0, 1, 0x67 },
    { 2, 0, 1, 0x69 },
    { 2, 0, 1, 0x6C },
    { 2, 0, 1, 0x6E },
    { 2, 0, 1, 0x70 },
    { 2, 0, 1, 0x72 },
    { 2, 0, 1, 0x74 },
    { 2, 0, 1, 0x77 },
    { 2, 0, 1, 0x7A },
    { 2, 0, 1, 0x7D },
    { 2, 0, 1, 0x74 },
    { 2, 0, 1, 0x77 },
    { 2, 0, 1, 0x7A },
    { 2, 0, 1, 0x7D },
    { 2, 0, 1, 0x74 },
    { 2, 0, 1, 0x77 },
    { 2, 0, 1, 0x7A },
    { 2, 0, 1, 0x7D },
    { 2, 0, 1, 0x74 },
    { 2, 0, 1, 0x77 },
    { 2, 0, 1, 0x7A },
    { 2, 0, 1, 0x7D },
    { 2, 0, 1, 0x80 },
    { 2, 0, 1, 0x81 },
    { 3, 0, 1, 0x82 },
    { 4, 0, 1, 0x83 },
    { 2, 64, 1, 0x6B },
    { 2, 64, 1, 0x62 },
    { 4, 64, 1, 0x5F },
    { 6, 64, 1, 0x57 },
    { 4, 64, 1, 0x56 },
    { 96, 64, 0, 0x56 },
};

union AnimationStep D_8011ABEC[36] = {
    { 2, -128, 1, 0x5D },
    { 2, 16, 1, 0x60 },
    { 2, 0, 1, 0x63 },
    { 2, 0, 1, 0x65 },
    { 2, 0, 1, 0x67 },
    { 2, 0, 1, 0x69 },
    { 2, 0, 1, 0x6C },
    { 2, 0, 1, 0x6E },
    { 2, 0, 1, 0x70 },
    { 2, 0, 1, 0x72 },
    { 2, 0, 1, 0x74 },
    { 2, 0, 1, 0x77 },
    { 2, 0, 1, 0x7A },
    { 2, 0, 1, 0x7D },
    { 2, 0, 1, 0x74 },
    { 2, 0, 1, 0x77 },
    { 2, 0, 1, 0x7A },
    { 2, 0, 1, 0x7D },
    { 2, 0, 1, 0x74 },
    { 2, 0, 1, 0x77 },
    { 2, 0, 1, 0x7A },
    { 2, 0, 1, 0x7D },
    { 2, 0, 1, 0x74 },
    { 2, 0, 1, 0x77 },
    { 2, 0, 1, 0x7A },
    { 2, 0, 1, 0x7D },
    { 2, 0, 1, 0x80 },
    { 2, 0, 1, 0x81 },
    { 3, 0, 1, 0x82 },
    { 4, 0, 1, 0x83 },
    { 2, 64, 1, 0x6B },
    { 2, 64, 1, 0x62 },
    { 4, 64, 1, 0x5F },
    { 6, 64, 1, 0x57 },
    { 4, 64, 1, 0x56 },
    { 96, 64, 0, 0x56 },
};

union AnimationStep D_8011AC7C[33] = {
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x59 },
    { 2, 0, 1, 0x5A },
    { 2, 0, 1, 0x5E },
    { 2, 0, 1, 0x59 },
    { 2, 0, 1, 0x5A },
    { 2, 0, 1, 0x5E },
    { 2, 36, 1, 0x61 },
    { 2, 36, 1, 0x64 },
    { 2, 37, 1, 0x66 },
    { 2, 37, 1, 0x68 },
    { 2, 38, 1, 0x6A },
    { 2, 39, 1, 0x6D },
    { 2, 40, 1, 0x6F },
    { 2, 41, 1, 0x71 },
    { 2, 42, 1, 0x73 },
    { 2, 43, 1, 0x75 },
    { 2, 44, 1, 0x78 },
    { 2, 43, 1, 0x7B },
    { 2, 44, 1, 0x7E },
    { 2, 43, 1, 0x75 },
    { 2, 44, 1, 0x78 },
    { 2, 43, 1, 0x7B },
    { 2, 44, 1, 0x7E },
    { 2, 43, 1, 0x75 },
    { 2, 44, 1, 0x78 },
    { 2, 43, 1, 0x7B },
    { 2, 44, 1, 0x7E },
    { 2, 43, 1, 0x76 },
    { 2, 44, 1, 0x79 },
    { 2, 0, 1, 0x7C },
    { 2, 0, 1, 0x7F },
    { 96, 0, 0, 0x7F },
};

union AnimationStep D_8011AD00[27] = {
    { 2, 0, 1, 0x5E },
    { 2, 36, 1, 0x61 },
    { 2, 36, 1, 0x64 },
    { 2, 37, 1, 0x66 },
    { 2, 37, 1, 0x68 },
    { 2, 38, 1, 0x6A },
    { 2, 39, 1, 0x6D },
    { 2, 40, 1, 0x6F },
    { 2, 41, 1, 0x71 },
    { 2, 42, 1, 0x73 },
    { 2, 43, 1, 0x75 },
    { 2, 44, 1, 0x78 },
    { 2, 43, 1, 0x7B },
    { 2, 44, 1, 0x7E },
    { 2, 43, 1, 0x75 },
    { 2, 44, 1, 0x78 },
    { 2, 43, 1, 0x7B },
    { 2, 44, 1, 0x7E },
    { 2, 43, 1, 0x75 },
    { 2, 44, 1, 0x78 },
    { 2, 43, 1, 0x7B },
    { 2, 44, 1, 0x7E },
    { 2, 43, 1, 0x76 },
    { 2, 44, 1, 0x79 },
    { 2, 0, 1, 0x7C },
    { 2, 0, 1, 0x7F },
    { 96, 0, 0, 0x7F },
};

union AnimationStep D_8011AD6C[10] = {
    { 2, 0, 1, 0x84 },
    { 2, -128, 1, 0x85 },
    { 3, 16, 1, 0x86 },
    { 3, 0, 1, 0x87 },
    { 3, 0, 1, 0x88 },
    { 3, 0, 1, 0x89 },
    { 3, 0, 1, 0x86 },
    { 3, 0, 1, 0x87 },
    { 3, 0, 1, 0x88 },
    { 3, 0, -3, 0x89 },
};

union AnimationStep D_8011AD94[11] = {
    { 2, 0, 1, 0x8A },
    { 2, 0, 1, 0x8B },
    { 3, 0, 1, 0x8C },
    { 3, 0, 1, 0x8D },
    { 4, 0, 1, 0x8E },
    { 6, 64, 1, 0x8F },
    { 2, 64, 1, 0x62 },
    { 4, 64, 1, 0x5F },
    { 6, 64, 1, 0x57 },
    { 4, 64, 1, 0x56 },
    { 96, 64, 0, 0x56 },
};

union AnimationStep D_8011ADC0[5] = {
    { 2, 0, 1, 0x00 },
    { 3, 45, 1, 0x01 },
    { 3, 45, 1, 0x01 },
    { 3, 46, 1, 0x01 },
    { 3, 46, -3, 0x01 },
};

union AnimationStep D_8011ADD4[2] = {
    { 4, 0, 1, 0x16 },
    { 3, 0, -1, 0x17 },
};

union AnimationStep D_8011ADDC[11] = {
    { 2, 0, 1, 0x84 },
    { 2, -128, 1, 0xA1 },
    { 2, 0, 1, 0xA3 },
    { 2, 0, 1, 0xA5 },
    { 2, 0, 1, 0xA7 },
    { 2, 0, 1, 0xA9 },
    { 2, 0, 1, 0xAB },
    { 2, 0, 1, 0xAD },
    { 2, 0, 1, 0xAF },
    { 2, 0, 1, 0xA0 },
    { 96, 0, 0, 0xA0 },
};

union AnimationStep D_8011AE08[9] = {
    { 2, 47, 1, 0xA2 },
    { 2, 48, 1, 0xA4 },
    { 2, 49, 1, 0xA6 },
    { 2, 50, 1, 0xA8 },
    { 2, 51, 1, 0xAA },
    { 2, 52, 1, 0xAC },
    { 2, 53, 1, 0xAE },
    { 2, 54, 1, 0xB0 },
    { 96, 54, 0, 0xB0 },
};

union AnimationStep D_8011AE2C[12] = {
    { 2, 0, 1, 0x56 },
    { 6, 0, 1, 0x57 },
    { 2, -128, 1, 0x90 },
    { 2, 0, 1, 0x92 },
    { 2, 32, 1, 0x94 },
    { 2, 0, 1, 0x96 },
    { 2, 0, 1, 0x98 },
    { 2, 0, 1, 0x9A },
    { 2, 0, 1, 0x94 },
    { 2, 0, 1, 0x96 },
    { 2, 0, 1, 0x98 },
    { 2, 0, -3, 0x9A },
};

union AnimationStep D_8011AE5C[4] = {
    { 3, 0, 1, 0x9C },
    { 3, 0, 1, 0x9E },
    { 4, 0, 1, 0xA0 },
    { 96, 0, 0, 0xA0 },
};

union AnimationStep D_8011AE6C[6] = {
    { 2, 55, 1, 0x91 },
    { 2, 56, 1, 0x93 },
    { 2, 57, 1, 0x95 },
    { 2, 58, 1, 0x97 },
    { 2, 59, 1, 0x99 },
    { 2, 60, -3, 0x9B },
};

union AnimationStep D_8011AE84[3] = {
    { 3, 0, 1, 0x9D },
    { 3, 0, 1, 0x9F },
    { 96, 0, 0, 0x9F },
};

union AnimationStep D_8011AE90[26] = {
    { 5, 0, 1, 0xB1 },
    { 6, 0, 1, 0xB2 },
    { 8, 0, 1, 0xB3 },
    { 2, 0, 1, 0xB4 },
    { 2, 0, 1, 0xB5 },
    { 1, -128, 1, 0xB6 },
    { 1, 0, 1, 0xB7 },
    { 1, 0, 1, 0xB8 },
    { 1, 0, 1, 0xB9 },
    { 2, 64, 1, 0xB6 },
    { 2, 0, 1, 0xB7 },
    { 2, 0, 1, 0xB8 },
    { 2, 0, 1, 0xB9 },
    { 3, 0, 1, 0xB6 },
    { 3, 0, 1, 0xB7 },
    { 3, 0, 1, 0xB8 },
    { 3, 0, 1, 0xB9 },
    { 4, 0, 1, 0xB6 },
    { 4, 0, 1, 0xB7 },
    { 4, 0, 1, 0xB8 },
    { 4, 0, 1, 0xB9 },
    { 4, 0, 1, 0xBA },
    { 4, 0, 1, 0xBB },
    { 4, 0, 1, 0xBC },
    { 3, 0, 1, 0xBD },
    { 96, 0, 0, 0xBD },
};

union AnimationStep D_8011AEF8[16] = {
    { 1, 0, 1, 0x9B },
    { 1, -128, 1, 0x9C },
    { 1, 0, 1, 0x9E },
    { 1, 0, 1, 0xA0 },
    { 2, 0, 1, 0xA2 },
    { 1, 0, 1, 0xA4 },
    { 1, 0, 1, 0xA6 },
    { 1, 0, 1, 0xA8 },
    { 1, 0, 1, 0xAA },
    { 1, 0, 1, 0xAC },
    { 1, 32, 1, 0xAC },
    { 2, 64, 1, 0x83 },
    { 4, 64, 1, 0x84 },
    { 6, 64, 1, 0x85 },
    { 4, 64, 1, 0x86 },
    { 96, 64, 0, 0x86 },
};

union AnimationStep D_8011AF38[10] = {
    { 1, 0, 1, 0x9D },
    { 1, 17, 1, 0x9F },
    { 1, 18, 1, 0xA1 },
    { 2, 19, 1, 0xA3 },
    { 1, 20, 1, 0xA5 },
    { 1, 21, 1, 0xA7 },
    { 1, 0, 1, 0xA9 },
    { 1, 0, 1, 0xAB },
    { 1, 0, 1, 0xAD },
    { 96, 0, 0, 0xAD },
};

u8 D_8011AF60[0x90] = {
    0,
    0,
    0,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    1,
    1,
    1,
    0,
    1,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

extern union AnimationStep D_8011A248[];
extern union AnimationStep D_8011A250[];
extern union AnimationStep D_8011A288[];
extern union AnimationStep D_8011A2B4[];
extern union AnimationStep D_8011A2BC[];
extern union AnimationStep D_8011A2DC[];
extern union AnimationStep D_8011A2F8[];
extern union AnimationStep D_8011A328[];
extern union AnimationStep D_8011A350[];
extern union AnimationStep D_8011A35C[];
extern union AnimationStep D_8011A394[];
extern union AnimationStep D_8011A3A0[];
extern union AnimationStep D_8011A3E0[];
extern union AnimationStep D_8011A3F4[];
extern union AnimationStep D_8011A418[];
extern union AnimationStep D_8011A424[];
extern union AnimationStep D_8011A434[];
extern union AnimationStep D_8011A448[];
extern union AnimationStep D_8011A454[];
extern union AnimationStep D_8011A480[];
extern union AnimationStep D_8011A494[];
extern union AnimationStep D_8011A4B8[];
extern union AnimationStep D_8011A4C4[];
extern union AnimationStep D_8011A4E8[];
extern union AnimationStep D_8011A4F8[];
extern union AnimationStep D_8011A50C[];
extern union AnimationStep D_8011A51C[];
extern union AnimationStep D_8011A524[];
extern union AnimationStep D_8011A54C[];
extern union AnimationStep D_8011A574[];
extern union AnimationStep D_8011A584[];
extern union AnimationStep D_8011A5D4[];
extern union AnimationStep D_8011A5D8[];
extern union AnimationStep D_8011A5FC[];
extern union AnimationStep D_8011A60C[];
extern union AnimationStep D_8011A62C[];
extern union AnimationStep D_8011A630[];
extern union AnimationStep D_8011A634[];
extern union AnimationStep D_8011A644[];
extern union AnimationStep D_8011A648[];
extern union AnimationStep D_8011A64C[];
extern union AnimationStep D_8011A650[];
extern union AnimationStep D_8011A670[];
extern union AnimationStep D_8011A6B0[];
extern union AnimationStep D_8011A6EC[];
extern union AnimationStep D_8011A6F4[];
extern union AnimationStep D_8011A700[];
extern union AnimationStep D_8011A70C[];
extern union AnimationStep D_8011A718[];
extern union AnimationStep D_8011A724[];
extern union AnimationStep D_8011A740[];
extern union AnimationStep D_8011A744[];
extern union AnimationStep D_8011A748[];
extern union AnimationStep D_8011A754[];
extern union AnimationStep D_8011A758[];
extern union AnimationStep D_8011A768[];
extern union AnimationStep D_8011A790[];
extern union AnimationStep D_8011A7A0[];
extern union AnimationStep D_8011A7C8[];
extern union AnimationStep D_8011A7D8[];
extern union AnimationStep D_8011A800[];
extern union AnimationStep D_8011A81C[];
extern union AnimationStep D_8011A83C[];
extern union AnimationStep D_8011A854[];
extern union AnimationStep D_8011A860[];
extern union AnimationStep D_8011A870[];
extern union AnimationStep D_8011A878[];
extern union AnimationStep D_8011A880[];
extern union AnimationStep D_8011A888[];
extern union AnimationStep D_8011A890[];
extern union AnimationStep D_8011A898[];
extern union AnimationStep D_8011A8E0[];
extern union AnimationStep D_8011A924[];
extern union AnimationStep D_8011A970[];
extern union AnimationStep D_8011A998[];
extern union AnimationStep D_8011A9C8[];
extern union AnimationStep D_8011A9FC[];
extern union AnimationStep D_8011AA24[];
extern union AnimationStep D_8011AA48[];
extern union AnimationStep D_8011AA70[];
extern union AnimationStep D_8011AA94[];
extern union AnimationStep D_8011AACC[];
extern union AnimationStep D_8011AAEC[];
extern union AnimationStep D_8011AB1C[];
extern union AnimationStep D_8011AB38[];
extern union AnimationStep D_8011ABEC[];
extern union AnimationStep D_8011AC7C[];
extern union AnimationStep D_8011AD00[];
extern union AnimationStep D_8011AD6C[];
extern union AnimationStep D_8011AD94[];
extern union AnimationStep D_8011ADC0[];
extern union AnimationStep D_8011ADD4[];
extern union AnimationStep D_8011ADDC[];
extern union AnimationStep D_8011AE08[];
extern union AnimationStep D_8011AE2C[];
extern union AnimationStep D_8011AE5C[];
extern union AnimationStep D_8011AE6C[];
extern union AnimationStep D_8011AE84[];
extern union AnimationStep D_8011AE90[];
extern union AnimationStep D_8011AEF8[];
extern union AnimationStep D_8011AF38[];

const union AnimationStep* D_8011AFF0[144] = {
    D_8011A2F8,
    D_8011A248,
    D_8011A250,
    D_8011A288,
    D_8011A2B4,
    D_8011A2F8,
    D_8011A328,
    D_8011A350,
    D_8011A35C,
    D_8011A394,
    D_8011A3E0,
    D_8011A3F4,
    D_8011A418,
    D_8011A424,
    D_8011A434,
    D_8011A448,
    D_8011A454,
    D_8011A480,
    D_8011A494,
    D_8011A4B8,
    D_8011A4C4,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A4E8,
    D_8011A4F8,
    D_8011A50C,
    D_8011A51C,
    D_8011A524,
    D_8011A54C,
    D_8011A574,
    D_8011A584,
    D_8011A2F8,
    D_8011A5D4,
    D_8011A5D8,
    D_8011A3A0,
    D_8011A2BC,
    D_8011A2DC,
    D_8011A5FC,
    D_8011A60C,
    D_8011A62C,
    D_8011A630,
    D_8011A634,
    D_8011A644,
    D_8011A648,
    D_8011A64C,
    D_8011A650,
    D_8011A670,
    D_8011A6B0,
    D_8011A6EC,
    D_8011A6F4,
    D_8011A700,
    D_8011A70C,
    D_8011A718,
    D_8011A724,
    D_8011A740,
    D_8011A740,
    D_8011A744,
    D_8011A740,
    D_8011A740,
    D_8011A748,
    D_8011A754,
    D_8011A758,
    D_8011A768,
    D_8011A790,
    D_8011A7A0,
    D_8011A7C8,
    D_8011A7D8,
    D_8011A800,
    D_8011A81C,
    D_8011A83C,
    D_8011A854,
    D_8011A860,
    D_8011A870,
    D_8011A878,
    D_8011A880,
    D_8011A888,
    D_8011A890,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A898,
    D_8011A8E0,
    D_8011A924,
    D_8011A9FC,
    D_8011AA48,
    D_8011AA94,
    D_8011AAEC,
    D_8011AB38,
    D_8011ABEC,
    D_8011AD6C,
    D_8011AD94,
    D_8011ADD4,
    D_8011ADDC,
    D_8011AE2C,
    D_8011AE5C,
    D_8011AE90,
    D_8011AEF8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A970,
    D_8011A998,
    D_8011A9C8,
    D_8011AA24,
    D_8011AA70,
    D_8011AACC,
    D_8011AB1C,
    D_8011AC7C,
    D_8011AD00,
    D_8011ADC0,
    D_8011AE08,
    D_8011AE6C,
    D_8011AE84,
    D_8011AF38,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
};
