// 80028B68..80028DB4
#include "common.h"

extern u8 D_800F4A50[16];
extern u8 D_800F4A60[16];
extern u8 D_800F5008[12];
extern u8 D_800F5014[12];
extern u8 D_800F55E0[12];
extern u8 D_800F55EC[12];
extern u8 D_800F611C[12];
extern u8 D_800F6128[16];
extern u8 D_800F669C[12];
extern u8 D_800F66A8[12];
extern u8 D_800F6AC4[8];
extern u8 D_800F6ACC[12];
extern u8 D_800F7204[8];
extern u8 D_800F720C[12];
extern u8 D_800F76A0[12];
extern u8 D_800F76AC[12];
extern u8 D_800F7AAC[12];
extern u8 D_800F7AB8[12];
extern u8 D_800F817C[8];
extern u8 D_800F81E0[12];
extern u8 D_800F8470[12];
extern u8 D_800F847C[16];
extern u8 D_800F87C8[8];
extern u8 D_800F87D0[16];
extern struct StageObjectRecord stage_object_records_0_0[];
extern struct StageObjectRecord stage_object_records_0_1[];
extern struct StageObjectRecord stage_object_records_1_0[];
extern struct StageObjectRecord stage_object_records_1_1[];
extern struct StageObjectRecord stage_object_records_2_0[];
extern struct StageObjectRecord stage_object_records_2_1[];
extern struct StageObjectRecord stage_object_records_3_0[];
extern struct StageObjectRecord stage_object_records_3_1[];
extern struct StageObjectRecord stage_object_records_4_0[];
extern struct StageObjectRecord stage_object_records_4_1[];
extern struct StageObjectRecord stage_object_records_5_0[];
extern struct StageObjectRecord stage_object_records_5_1[];
extern struct StageObjectRecord stage_object_records_6_0[];
extern struct StageObjectRecord stage_object_records_6_1[];
extern struct StageObjectRecord stage_object_records_7_0[];
extern struct StageObjectRecord stage_object_records_7_1[];
extern struct StageObjectRecord stage_object_records_8_0[];
extern struct StageObjectRecord stage_object_records_8_1[];
extern struct StageObjectRecord stage_object_records_9_0[];
extern struct StageObjectRecord stage_object_records_10_0[];
extern struct StageObjectRecord stage_object_records_11_0[];
extern struct StageObjectRecord stage_object_records_11_1[];
extern struct StageObjectRecord stage_object_records_12_0[];
extern struct StageObjectRecord stage_object_records_12_1[];
extern struct Checkpoint* checkpoint_list_800F4124[];
extern struct Checkpoint* checkpoint_list_800F4130[];
extern struct Checkpoint* checkpoint_list_800F413C[];
extern struct Checkpoint* checkpoint_list_800F4150[];
extern struct Checkpoint* checkpoint_list_800F4168[];
extern struct Checkpoint* checkpoint_list_800F417C[];
extern struct Checkpoint* checkpoint_list_800F418C[];
extern struct Checkpoint* checkpoint_list_800F419C[];
extern struct Checkpoint* checkpoint_list_800F41AC[];
extern struct Checkpoint* checkpoint_list_800F41B4[];
extern struct Checkpoint* checkpoint_list_800F41C4[];
extern struct Checkpoint* checkpoint_list_800F41C8[];
extern struct Checkpoint* checkpoint_list_800F41D0[];
extern struct Checkpoint* checkpoint_list_800F41E8[];
extern struct Checkpoint* checkpoint_list_800F41F0[];
extern struct Checkpoint* checkpoint_list_800F41FC[];
extern struct Checkpoint* checkpoint_list_800F420C[];
extern struct Checkpoint* checkpoint_list_800F4218[];
extern struct Checkpoint* checkpoint_list_800F4228[];
extern struct Checkpoint* checkpoint_list_800F422C[];
extern struct Checkpoint* checkpoint_list_800F4238[];
extern struct Checkpoint* checkpoint_list_800F4240[];
extern struct Checkpoint* checkpoint_list_800F424C[];
extern struct Checkpoint* checkpoint_list_800F4298[];
extern struct Checkpoint* checkpoint_list_800F429C[];
extern struct Checkpoint* checkpoint_list_800F42A0[];
extern struct Checkpoint* checkpoint_list_800F42A4[];
extern struct Checkpoint* checkpoint_list_800F42A8[];
extern struct Checkpoint* checkpoint_list_800F42AC[];
extern struct Checkpoint* checkpoint_list_800F42B0[];
extern struct Checkpoint** D_800F42B4[32];
extern struct StageObjectMarginData D_800F4334;

void start_screen_shake_x(s8 arg0, s8 arg1, s8 arg2)
{
    background_objects[0].unk36 = arg0;
    background_objects[0].unk45 = arg1;
    background_objects[0].unk3E.bytes[0] = arg1;
    background_objects[0].unk3C = arg2;
    background_objects[0].unk3A = arg2;
    background_objects[0].unk34 |= 0x10;
}

void start_screen_shake_y(s8 arg0, s8 arg1, s8 arg2)
{
    background_objects[0].unk37 = arg0;
    background_objects[0].unk46 = arg1;
    background_objects[0].unk3E.bytes[1] = arg1;
    background_objects[0].unk3D = arg2;
    background_objects[0].unk3B = arg2;
    background_objects[0].unk34 |= 1;
}

extern struct Checkpoint** D_800F42B4[32];

void func_80028BF0(void)
{
    s16 bg1_x;
    s16 bg1_y;
    s16 bg2_x;
    s16 bg2_y;
    s32 x;
    s32 y;
    struct Checkpoint* checkpoint;
    u16 bg1_offset_y;
    u16 bg2_offset_y;
    u16 bg1_offset_x;
    u16 bg2_offset_x;
    struct BackgroundObj* bg_obj;
    struct PlayerObj* player;

    checkpoint = D_800F42B4[engine_obj.stage * 2 + engine_obj.substage][engine_obj.checkpoint];
    player = &g_Player;

    x = FIXED(checkpoint->x);
    player->x_pos.val = x;
    y = FIXED(checkpoint->y);
    player->y_pos.val = y;
    player->unk18.val = x;
    player->unk1C.val = y;

    player->unk15 = checkpoint->facing;
    bg_obj = background_objects;
    bg_obj->x_pos.i.hi = checkpoint->bg0_x;
    bg_obj->unk14.i.hi = checkpoint->bg0_x;
    bg_obj->y_pos.i.hi = checkpoint->bg0_y;
    bg_obj->unk18.i.hi = checkpoint->bg0_y;
    bg_obj->unk1E = checkpoint->bg0_right;
    bg_obj->unk26 = checkpoint->bg0_right;
    bg_obj->unk1C = checkpoint->bg0_bottom;
    bg_obj->unk24 = checkpoint->bg0_bottom;
    bg_obj->unk22 = checkpoint->bg0_left;
    bg_obj->unk2A = checkpoint->bg0_left;
    bg_obj->unk20 = checkpoint->bg0_top;
    bg_obj->unk28 = checkpoint->bg0_top;
    bg1_offset_x = checkpoint->bg1_off_x;
    bg_obj++;
    bg_obj->unk40 = bg1_offset_x;
    bg1_offset_y = checkpoint->bg1_off_y;
    bg_obj->unk42 = bg1_offset_y;
    bg1_x = checkpoint->bg1_x + bg1_offset_x;
    bg_obj->x_pos.i.hi = bg1_x;
    bg_obj->unk14.i.hi = bg1_x;
    bg1_y = checkpoint->bg1_y + bg1_offset_y;
    bg_obj->y_pos.i.hi = bg1_y;
    bg_obj->unk18.i.hi = bg1_y;
    bg2_offset_x = checkpoint->bg2_off_x;
    bg_obj++;
    bg_obj->unk40 = bg2_offset_x;
    bg2_offset_y = checkpoint->bg2_off_y;
    bg_obj->unk42 = bg2_offset_y;
    bg2_x = checkpoint->bg2_x + bg2_offset_x;
    bg_obj->x_pos.i.hi = bg2_x;
    bg_obj->unk14.i.hi = bg2_x;
    bg2_y = checkpoint->bg2_y + bg2_offset_y;
    bg_obj->y_pos.i.hi = bg2_y;
    bg_obj->unk18.i.hi = bg2_y;
    player->beam_in_delay = checkpoint->player_unkBE;
}

// find_stage_main_index

struct Checkpoint D_800F3314[100] = {
    { 200, 256, 40, 256, 40, 256, 20, 256, 0, 2976, 256, 256, 64, 0, 0, 0, 0, 18 },
    { 1360, 256, 1200, 256, 1200, 256, 600, 256, 1200, 2976, 256, 256, 64, 0, 0, 0, 0, 18 },
    { 3328, 256, 3280, 256, 3280, 256, 1640, 256, 3280, 4544, 256, 256, 64, 0, 0, 0, 0, 18 },
    { 144, 256, 0, 256, 0, 256, 0, 256, 0, 4528, 256, 256, 64, 0, 0, 0, 0, 18 },
    { 1616, 256, 1456, 256, 1456, 256, 728, 256, 1456, 4528, 256, 256, 64, 0, 0, 0, 0, 18 },
    { 3936, 256, 3856, 256, 3856, 256, 1928, 256, 3856, 4528, 256, 256, 64, 0, 0, 0, 0, 18 },
    { 56, 16, 0, 0, 0, 0, 0, 0, 0, 1808, 0, 2560, 64, 0, 0, 0, 128, 8 },
    { 1872, 288, 1808, 388, 1808, 388, 904, 194, 1808, 1808, 256, 2560, 64, 0, 0, 0, 128, 18 },
    { 1856, 1232, 1808, 1280, 1808, 1280, 904, 640, 1808, 5584, 1280, 1280, 64, 0, 0, 0, 128, 18 },
    { 4112, 1232, 4064, 1280, 4064, 1280, 2032, 640, 4064, 5584, 1280, 1280, 64, 0, 0, 0, 128, 4 },
    { 5680, 1200, 5520, 1184, 5520, 1184, 2760, 592, 5376, 5584, 256, 1280, 64, 0, 0, 0, 128, 4 },
    { 112, 128, 0, 256, 40, 256, 0, 128, 0, 1200, 256, 2560, 64, 0, 0, 0, 128, 18 },
    { 1408, 448, 1200, 480, 1712, 480, 600, 240, 0, 1200, 480, 2560, 0, 0, 0, 0, 128, 18 },
    { 640, 736, 512, 768, 1024, 768, 256, 384, 512, 1792, 480, 2560, 64, 0, 0, 0, 128, 18 },
    { 1920, 1264, 1792, 1280, 2304, 1280, 896, 640, 1792, 4016, 1280, 1280, 64, 0, 0, 0, 128, 18 },
    { 3408, 1280, 3328, 1280, 3608, 1280, 1664, 640, 3328, 4016, 1024, 1280, 64, 0, 0, 0, 128, 21 },
    { 4480, 1280, 4320, 1280, 4352, 1280, 2160, 640, 4320, 4320, 1280, 1280, 64, 0, 0, 0, 128, 18 },
    { 144, 144, 0, 155, 0, 38, 0, 0, 0, 5312, 0, 2048, 64, 0, 0, 0, 0, 18 },
    { 1776, 224, 1616, 203, 404, 50, 0, 0, 0, 5312, 0, 2048, 64, 0, 0, 0, 0, 3 },
    { 3088, 176, 2928, 203, 732, 50, 0, 0, 0, 5312, 0, 2048, 64, 0, 0, 0, 0, 18 },
    { 4704, 1328, 4544, 1291, 1136, 322, 0, 0, 0, 5312, 0, 2048, 64, 0, 0, 0, 0, 18 },
    { 5856, 2048, 5696, 2048, 1424, 512, 0, 0, 0, 5728, 2048, 2048, 64, 0, 0, 0, 0, 18 },
    { 96, 0, 0, 0, 0, 0, 0, 0, 0, 2496, 0, 768, 64, 0, 0, 0, 0, 8 },
    { 1328, 304, 1280, 256, 1280, 256, 1280, 256, 1280, 2496, 256, 768, 64, 0, 0, 0, 0, 8 },
    { 2944, 272, 2832, 256, 2832, 256, 2832, 256, 2832, 6288, 256, 256, 64, 0, 0, 0, 0, 8 },
    { 6736, 256, 6592, 256, 6592, 256, 6592, 256, 6592, 6592, 256, 256, 64, 0, 0, 0, 0, 8 },
    { 160, 512, 0, 512, 0, 512, 0, 0, 0, 1728, 0, 512, 64, 0, 0, 0, 0, 18 },
    { 2344, 0, 2304, 0, 1152, 0, 512, 0, 2304, 3248, 0, 0, 64, 128, 0, 0, 0, 18 },
    { 6048, 2304, 5888, 2304, 4416, 1728, 2944, 1152, 5888, 5888, 256, 2304, 64, 1472, 576, 2944, 1152, 18 },
    { 5552, 544, 5312, 544, 2656, 272, 1328, 136, 4352, 5312, 544, 544, 0, 2656, 240, 144, 376, 1 },
    { 160, 512, 0, 512, 0, 512, 0, 0, 0, 2240, 0, 512, 64, 0, 0, 0, 0, 18 },
    { 2912, 256, 2816, 256, 1408, 128, 704, 64, 2816, 3776, 256, 256, 64, 1408, 128, 2112, 192, 18 },
    { 6048, 2048, 5888, 2048, 2944, 1024, 1472, 512, 5888, 5888, 2048, 2048, 64, 2944, 768, 4416, 512, 18 },
    { 6048, 512, 5888, 528, 2944, 264, 1472, 132, 5888, 5888, 256, 528, 64, 2944, 760, 4416, 512, 18 },
    { 128, 512, 0, 512, 0, 256, 0, 128, 0, 6064, 512, 768, 64, 0, 0, 0, 128, 18 },
    { 2848, 768, 2736, 768, 1368, 384, 684, 192, 2736, 6064, 768, 768, 64, 0, 0, 0, 128, 18 },
    { 64, 512, 0, 512, 0, 512, 0, 256, 0, 5280, 512, 512, 64, 0, 0, 0, 128, 18 },
    { 1488, 512, 1392, 512, 1392, 512, 696, 256, 1392, 5280, 256, 512, 64, 0, 0, 0, 128, 18 },
    { 2864, 256, 2704, 491, 2704, 491, 1352, 245, 2704, 5280, 256, 512, 64, 0, 0, 0, 128, 18 },
    { 5120, 256, 5024, 312, 5024, 312, 2512, 156, 5024, 5280, 256, 512, 64, 0, 0, 0, 128, 16 },
    { 160, 182, 256, 0, 192, 0, 64, 0, 256, 28864, 0, 0, 64, 64, 0, 192, 0, 18 },
    { 160, 182, 256, 0, 256, 0, 128, 0, 256, 16720, 0, 0, 64, 0, 0, 0, 0, 18 },
    { 16480, 0, 16384, 0, 16384, 0, 8192, 0, 16384, 16720, 0, 0, 64, 0, 0, 0, 0, 18 },
    { 72, 0, 0, 0, 0, 0, 0, 0, 0, 1632, 0, 0, 64, 0, 0, 0, 0, 3 },
    { 72, 768, 0, 768, 0, 384, 0, 192, 0, 608, 768, 768, 64, 0, 384, 0, 576, 3 },
    { 72, 512, 0, 512, 0, 256, 0, 128, 0, 1888, 256, 512, 64, 0, 256, 0, 384, 3 },
    { 72, 768, 0, 768, 0, 384, 0, 192, 0, 608, 768, 768, 64, 0, 384, 0, 576, 3 },
    { 72, 2304, 0, 2304, 0, 1152, 0, 576, 0, 2912, 1280, 2304, 64, 0, 1120, 0, 1728, 3 },
    { 72, 768, 0, 768, 0, 384, 0, 192, 0, 608, 768, 768, 64, 0, 384, 0, 576, 3 },
    { 328, 768, 256, 768, 64, 384, 64, 192, 256, 3824, 768, 768, 64, 128, 640, 192, 832, 8 },
    { 328, 2304, 256, 2304, 128, 1152, 64, 576, 256, 384, 2304, 2304, 64, 128, 1152, 192, 1728, 8 },
    { 56, 256, 0, 256, 512, 128, 512, 64, 0, 6080, 256, 256, 64, 0, 128, 0, 192, 1 },
    { 1120, 256, 960, 256, 512, 128, 512, 64, 960, 6080, 256, 256, 64, 0, 128, 0, 192, 1 },
    { 3424, 256, 3264, 256, 512, 128, 512, 64, 3264, 6080, 256, 256, 64, 0, 128, 0, 192, 1 },
    { 224, 768, 64, 768, 512, 384, 512, 256, 64, 1936, 768, 768, 64, 0, 384, 0, 0, 1 },
    { 2160, 768, 1936, 768, 512, 384, 512, 256, 64, 1936, 768, 768, 64, 0, 384, 0, 0, 8 },
    { 2624, 768, 2560, 768, 512, 384, 512, 256, 2560, 2560, 512, 768, 64, 0, 384, 0, 0, 19 },
    { 2640, 512, 2480, 504, 512, 384, 512, 256, 2256, 2480, 504, 504, 0, 0, 384, 0, 0, 14 },
    { 864, 128, 768, 248, 512, 0, 512, 0, 768, 6736, 248, 248, 64, 0, 0, 0, 0, 18 },
    { 4688, 128, 4528, 248, 512, 0, 512, 0, 4528, 6736, 248, 248, 64, 0, 0, 0, 0, 18 },
    { 6464, 128, 6304, 248, 512, 0, 512, 0, 6304, 6736, 248, 248, 64, 0, 0, 0, 0, 18 },
    { 104, 128, 48, 248, 512, 256, 512, 256, 48, 10048, 248, 248, 64, 0, 0, 0, 0, 18 },
    { 5280, 128, 5120, 248, 512, 256, 512, 256, 5120, 10048, 248, 248, 64, 0, 0, 0, 0, 2 },
    { 7728, 128, 7648, 248, 512, 256, 512, 256, 7648, 10048, 248, 248, 64, 0, 0, 0, 0, 2 },
    { 9232, 128, 9072, 248, 512, 256, 512, 256, 9072, 10048, 248, 248, 64, 0, 0, 0, 0, 2 },
    { 104, 0, 0, 0, 0, 0, 0, 0, 0, 704, 0, 0, 64, 176, 0, 176, 0, 8 },
    { 360, 2048, 256, 2048, 256, 2048, 128, 1024, 256, 3776, 2048, 2048, 64, 0, 0, 128, 1024, 8 },
    { 3937, 2048, 3776, 2048, 256, 2048, 1888, 1024, 3776, 3776, 2048, 2048, 64, 0, 0, 128, 1024, 8 },
    { 4304, 736, 4160, 736, 256, 736, 2080, 368, 4160, 4160, 736, 736, 64, 0, 0, 128, 1024, 8 },
    { 360, 272, 256, 272, 256, 272, 64, 68, 256, 1440, 272, 272, 64, 0, 0, 192, 204, 8 },
    { 1896, 256, 1744, 272, 256, 272, 436, 68, 1744, 1744, 272, 272, 64, 0, 0, 0, 204, 8 },
    { 360, 272, 256, 272, 0, 256, 64, 68, 256, 560, 272, 512, 64, 0, 0, 192, 204, 8 },
    { 1056, 272, 992, 272, 0, 256, 248, 68, 992, 1024, 272, 512, 64, 0, 0, 192, 204, 8 },
    { 3232, 272, 3072, 427, 0, 256, 768, 106, 3072, 3072, 272, 512, 64, 0, 0, 192, 204, 40 },
    { 360, 0, 256, 0, 0, 0, 128, 0, 256, 1696, 0, 1024, 64, 0, 0, 128, 0, 8 },
    { 1864, 880, 1704, 891, 1704, 890, 980, 445, 1536, 1872, 768, 1024, 64, 0, 0, 0, 0, 8 },
    { 384, 1536, 256, 1536, 256, 1536, 128, 768, 256, 448, 1536, 1536, 64, 0, 0, 128, 768, 8 },
    { 1152, 1536, 1040, 1536, 1040, 1536, 520, 768, 1040, 1120, 1536, 1536, 64, 0, 0, 520, 768, 8 },
    { 1872, 1536, 1792, 1536, 1792, 1536, 896, 768, 1792, 1792, 1536, 1536, 64, 0, 0, 896, 768, 8 },
    { 2688, 1536, 2576, 1536, 2576, 1536, 1288, 768, 2576, 2624, 1424, 1536, 64, 0, 0, 1288, 768, 8 },
    { 3376, 1544, 3360, 1544, 3360, 1544, 1680, 772, 3360, 3360, 1544, 1544, 64, 0, 0, 1680, 772, 8 },
    { 4160, 1536, 4112, 1536, 4112, 1536, 2056, 768, 4112, 4160, 1536, 1536, 64, 0, 0, 2056, 768, 8 },
    { 328, 2304, 272, 2304, 272, 2304, 136, 1152, 272, 304, 2304, 2304, 64, 0, 0, 136, 1152, 8 },
    { 1072, 2304, 1024, 2304, 1024, 2304, 512, 1152, 1024, 1216, 2304, 2304, 64, 0, 0, 512, 1152, 8 },
    { 1840, 2304, 1792, 2304, 1792, 2304, 896, 1152, 1792, 2240, 2304, 2304, 64, 0, 0, 896, 1152, 8 },
    { 2096, 768, 1872, 768, 1872, 768, 936, 384, 1536, 1872, 768, 1024, 0, 0, 0, 0, 0, 8 },
    { 1696, 768, 1536, 779, 1536, 779, 768, 389, 1536, 1872, 768, 1024, 64, 0, 0, 0, 0, 24 },
    { 1792, 1024, 1632, 1024, 1632, 1024, 816, 512, 1536, 1872, 768, 1024, 64, 0, 0, 0, 0, 16 },
    { 1760, 960, 1600, 960, 1600, 960, 928, 480, 1536, 1872, 768, 1024, 64, 0, 0, 0, 0, 16 },
    { 2032, 832, 1872, 832, 1872, 832, 936, 416, 1536, 1872, 768, 1024, 0, 0, 0, 0, 0, 16 },
    { 1632, 768, 1536, 768, 1536, 768, 768, 384, 1536, 1872, 768, 1024, 64, 0, 0, 0, 0, 8 },
    { 1936, 1024, 1776, 1019, 1776, 1019, 888, 509, 1536, 1872, 768, 1024, 0, 0, 0, 0, 0, 16 },
    { 1968, 896, 1808, 907, 1808, 907, 904, 453, 1536, 1872, 768, 1024, 0, 0, 0, 0, 0, 16 },
    { 528, 256, 448, 256, 448, 256, 112, 64, 448, 448, 256, 256, 64, 0, 0, 248, 128, 8 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 256, 64, 0, 0, 0, 0, 0 },
    { 0, 0, 2240, 0, 0, 240, 0, 16, 0, 3584, 0, 256, 64, 0, 0, 0, 0, 0 },
#ifdef VERSION_JP
    { 0, 0, 128, 0, 576, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0 },
#else
    { 0, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0 },
#endif
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 768, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0 },
};

struct Checkpoint* checkpoint_list_800F4124[] = {
    &D_800F3314[0],
    &D_800F3314[1],
    &D_800F3314[2],
};

struct Checkpoint* checkpoint_list_800F4130[] = {
    &D_800F3314[3],
    &D_800F3314[4],
    &D_800F3314[5],
};

struct Checkpoint* checkpoint_list_800F413C[] = {
    &D_800F3314[6],
    &D_800F3314[7],
    &D_800F3314[8],
    &D_800F3314[9],
    &D_800F3314[10],
};

struct Checkpoint* checkpoint_list_800F4150[] = {
    &D_800F3314[11],
    &D_800F3314[12],
    &D_800F3314[13],
    &D_800F3314[14],
    &D_800F3314[15],
    &D_800F3314[16],
};

struct Checkpoint* checkpoint_list_800F4168[] = {
    &D_800F3314[17],
    &D_800F3314[18],
    &D_800F3314[19],
    &D_800F3314[20],
    &D_800F3314[21],
};

struct Checkpoint* checkpoint_list_800F417C[] = {
    &D_800F3314[22],
    &D_800F3314[23],
    &D_800F3314[24],
    &D_800F3314[25],
};

struct Checkpoint* checkpoint_list_800F418C[] = {
    &D_800F3314[26],
    &D_800F3314[27],
    &D_800F3314[28],
    &D_800F3314[29],
};

struct Checkpoint* checkpoint_list_800F419C[] = {
    &D_800F3314[30],
    &D_800F3314[31],
    &D_800F3314[32],
    &D_800F3314[33],
};

struct Checkpoint* checkpoint_list_800F41AC[] = {
    &D_800F3314[34],
    &D_800F3314[35],
};

struct Checkpoint* checkpoint_list_800F41B4[] = {
    &D_800F3314[36],
    &D_800F3314[37],
    &D_800F3314[38],
    &D_800F3314[39],
};

struct Checkpoint* checkpoint_list_800F41C4[] = {
    &D_800F3314[40],
};

struct Checkpoint* checkpoint_list_800F41C8[] = {
    &D_800F3314[41],
    &D_800F3314[42],
};

struct Checkpoint* checkpoint_list_800F41D0[] = {
    &D_800F3314[43],
    &D_800F3314[44],
    &D_800F3314[45],
    &D_800F3314[46],
    &D_800F3314[47],
    &D_800F3314[48],
};

struct Checkpoint* checkpoint_list_800F41E8[] = {
    &D_800F3314[49],
    &D_800F3314[50],
};

struct Checkpoint* checkpoint_list_800F41F0[] = {
    &D_800F3314[51],
    &D_800F3314[52],
    &D_800F3314[53],
};

struct Checkpoint* checkpoint_list_800F41FC[] = {
    &D_800F3314[54],
    &D_800F3314[55],
    &D_800F3314[56],
    &D_800F3314[57],
};

struct Checkpoint* checkpoint_list_800F420C[] = {
    &D_800F3314[58],
    &D_800F3314[59],
    &D_800F3314[60],
};

struct Checkpoint* checkpoint_list_800F4218[] = {
    &D_800F3314[61],
    &D_800F3314[62],
    &D_800F3314[63],
    &D_800F3314[64],
};

struct Checkpoint* checkpoint_list_800F4228[] = {
    &D_800F3314[65],
};

struct Checkpoint* checkpoint_list_800F422C[] = {
    &D_800F3314[66],
    &D_800F3314[67],
    &D_800F3314[68],
};

struct Checkpoint* checkpoint_list_800F4238[] = {
    &D_800F3314[69],
    &D_800F3314[70],
};

struct Checkpoint* checkpoint_list_800F4240[] = {
    &D_800F3314[71],
    &D_800F3314[72],
    &D_800F3314[73],
};

struct Checkpoint* checkpoint_list_800F424C[] = {
    &D_800F3314[74],
    &D_800F3314[75],
    &D_800F3314[76],
    &D_800F3314[77],
    &D_800F3314[78],
    &D_800F3314[79],
    &D_800F3314[80],
    &D_800F3314[81],
    &D_800F3314[82],
    &D_800F3314[83],
    &D_800F3314[84],
    &D_800F3314[85],
    &D_800F3314[86],
    &D_800F3314[87],
    &D_800F3314[88],
    &D_800F3314[89],
    &D_800F3314[90],
    &D_800F3314[91],
    &D_800F3314[92],
};

struct Checkpoint* checkpoint_list_800F4298[] = {
    &D_800F3314[93],
};

struct Checkpoint* checkpoint_list_800F429C[] = {
    &D_800F3314[94],
};

struct Checkpoint* checkpoint_list_800F42A0[] = {
    &D_800F3314[95],
};

struct Checkpoint* checkpoint_list_800F42A4[] = {
    &D_800F3314[96],
};

struct Checkpoint* checkpoint_list_800F42A8[] = {
    &D_800F3314[97],
};

struct Checkpoint* checkpoint_list_800F42AC[] = {
    &D_800F3314[98],
};

struct Checkpoint* checkpoint_list_800F42B0[] = {
    &D_800F3314[99],
};

struct Checkpoint** D_800F42B4[32] = {
    checkpoint_list_800F4124,
    checkpoint_list_800F4130,
    checkpoint_list_800F413C,
    checkpoint_list_800F4150,
    checkpoint_list_800F4168,
    checkpoint_list_800F417C,
    checkpoint_list_800F418C,
    checkpoint_list_800F419C,
    checkpoint_list_800F41AC,
    checkpoint_list_800F41B4,
    checkpoint_list_800F41C4,
    checkpoint_list_800F41C8,
    checkpoint_list_800F41D0,
    checkpoint_list_800F41E8,
    checkpoint_list_800F41F0,
    checkpoint_list_800F41FC,
    checkpoint_list_800F420C,
    checkpoint_list_800F4218,
    checkpoint_list_800F4228,
    NULL,
    checkpoint_list_800F422C,
    NULL,
    checkpoint_list_800F4238,
    checkpoint_list_800F4240,
    checkpoint_list_800F424C,
    checkpoint_list_800F4298,
    checkpoint_list_800F429C,
    checkpoint_list_800F42A0,
    checkpoint_list_800F42A4,
    checkpoint_list_800F42A8,
    checkpoint_list_800F42AC,
    checkpoint_list_800F42B0,
};
