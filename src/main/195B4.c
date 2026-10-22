// 80028DB4..80029420
#include "common.h"
#include "main/objects.h"
#include "main/195B4.h"
#include "main/stage_object_record_tables.h"
#include "main/stage_objects.h"
#ifdef MMX4_SATURN
#include "weapon_resources.h"
#endif

extern u8 D_800F4A50[];
extern u8 D_800F4A60[];
extern u8 D_800F5008[];
extern u8 D_800F5014[];
extern u8 D_800F55E0[];
extern u8 D_800F55EC[];
extern u8 D_800F611C[];
extern u8 D_800F6128[];
extern u8 D_800F669C[];
extern u8 D_800F66A8[];
extern u8 D_800F6AC4[];
extern u8 D_800F6ACC[];
extern u8 D_800F7204[];
extern u8 D_800F720C[];
extern u8 D_800F76A0[];
extern u8 D_800F76AC[];
extern u8 D_800F7AAC[];
extern u8 D_800F7AB8[];
extern u8 D_800F817C[];
extern u8 D_800F81E0[];
extern u8 D_800F8470[];
extern u8 D_800F847C[];
extern u8 D_800F87C8[];
extern u8 D_800F87D0[];
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
extern struct ObjectHeader* (*g_MakeObjectFuncs[8])();

void start_screen_shake_x(s8 arg0, s8 arg1, s8 arg2);

void start_screen_shake_y(s8 arg0, s8 arg1, s8 arg2);

extern struct Checkpoint** D_800F42B4[32];

void func_80028BF0(void);

struct StageObjectMarginData D_800F4334 = {
    { 0x20, 0x40, 0x60, 0x80, 0xA0 },
    0,
};

const u8* s_StageMainIds[13][2] = {
    { D_800F4A50, D_800F4A60 },
    { D_800F5008, D_800F5014 },
    { D_800F55E0, D_800F55EC },
    { D_800F611C, D_800F6128 },
    { D_800F669C, D_800F66A8 },
    { D_800F6AC4, D_800F6ACC },
    { D_800F7204, D_800F720C },
    { D_800F76A0, D_800F76AC },
    { D_800F7AAC, D_800F7AB8 },
    { D_800F817C, NULL },
    { D_800F81E0, NULL },
    { D_800F8470, D_800F847C },
    { D_800F87C8, D_800F87D0 },
};

struct ObjectHeader* (*g_MakeObjectFuncs[8])() = {
    find_free_main_obj,
    find_free_weapon_obj,
    find_free_visual_obj,
    find_free_effect_obj,
    find_free_item_obj,
    find_free_misc_obj,
    find_free_quad_obj,
    find_free_layer_obj,
};

void func_80028DB4(void)
{
    u8* dataPtr = (u8*)D_800F43C8[engine_obj.stage][engine_obj.substage];

    while (dataPtr[3] != 0xFF) {
        dataPtr[0] &= 0x70;
        dataPtr += 8;
    }
}

#ifdef MMX4_SATURN
void func_80028E24(void)
{
    struct BackgroundObj* bg = &background_objects[0];
    s16 old_x = bg->unk14.i.hi;
    s16 x = bg->x_pos.i.hi;
    s16 old_y = bg->unk18.i.hi;
    s16 y = bg->y_pos.i.hi;

    if (old_x != x) {
        if (old_x < x) {
            func_80028FEC(x + 0x150, x + 0x170, y - 0x30, y + 0x120, 1);
        } else {
            func_80028FEC(x - 0x30, x - 0x10, y - 0x30, y + 0x120, 2);
        }
    }
    if (old_y != y) {
        if (old_y < y) {
            func_80028FEC(x - 0x30, x + 0x170, y + 0x100, y + 0x120, 3);
        } else {
            func_80028FEC(x - 0x30, x + 0x170, y - 0x30, y - 0x10, 4);
        }
    }
}
#else
INCLUDE_ASM("main/nonmatchings/195B4", func_80028E24);
#endif
void func_80028F58(void)
{
    func_80028FEC(background_objects[0].x_pos.i.hi - 0x30,
        background_objects[0].x_pos.i.hi + 0x170,
        background_objects[0].y_pos.i.hi - 0x30,
        background_objects[0].y_pos.i.hi + 0x120,
        0);
    func_800292D0(D_800F4430[engine_obj.stage][engine_obj.substage]);
}

#ifdef MMX4_SATURN
void func_80028FEC(s16 left, s16 right, s16 top, s16 bottom, u8 direction)
{
    struct StageObjectRecord* record = D_800F43C8[engine_obj.stage][engine_obj.substage];

    while (record->object_type != 0xFF) {
        u8 flags = record->flags;
        s16 scan_left = left;
        s16 scan_right = right;
        s16 scan_top = top;
        s16 scan_bottom = bottom;

        if (!(flags & 0x81)) {
            if (flags & 0x70) {
                u16 margin = D_800F4334.margins[(flags >> 4) - 1];

                switch (direction) {
                case 1:
                    scan_left += margin;
                    scan_right += margin;
                    break;
                case 2:
                    scan_left -= margin;
                    scan_right -= margin;
                    break;
                case 3:
                    scan_top += margin;
                    scan_bottom += margin;
                    break;
                case 4:
                    scan_top -= margin;
                    scan_bottom -= margin;
                    break;
                }
            }
            if (scan_left < record->x && record->x < scan_right && scan_top < record->y && record->y < scan_bottom) {
                struct ObjectHeader* object = MakeObject(record->object_type);

                if (object != NULL) {
                    object->active = 0x41;
                    object->id = record->id;
                    object->unk2 = record->subtype;
                    object->x_pos.i.hi = record->x;
                    object->y_pos.i.hi = record->y;
                    object->backref = record;
                    if (record->object_type == 0) {
                        struct MainObj* main = (struct MainObj*)object;

                        main->unk40 = OBJECT_STAGE_TEXTURE((u8)func_8002938C(record->id));
                        main->unk42 = VISUAL_STAGE_PALETTE((u8)func_8002938C(record->id));
                        main->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, (u8)func_8002938C(record->id));
                    }
                    record->flags |= 1;
                }
            }
        }
        record++;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/195B4", func_80028FEC);
#endif
void func_800292D0(struct StageObjectRecord* arg0)
{
    struct StageObjectRecord* var_s1 = arg0;
    struct ObjectHeader* obj;

    while (0xFF != var_s1->object_type && var_s1->flags <= engine_obj.checkpoint) {
        obj = MakeObject(var_s1->object_type);
        if (obj != NULL) {
            obj->active = 1;
            obj->id = var_s1->id;
            obj->unk2 = var_s1->subtype;
            obj->x_pos.i.hi = var_s1->x;
            obj->y_pos.i.hi = var_s1->y;
            obj->backref = var_s1;
        }
        var_s1++;
    }
}

// find_stage_main_index
ret_u8 func_8002938C(arg_u8 id)
{
    u8 i = 0;
    do {
        u8 sid = s_StageMainIds[engine_obj.stage][engine_obj.substage][i];
        if (sid == 0xFF || sid == (u8)id)
            return i;
        ++i;
    } while (1);
}

extern struct ObjectHeader* (*g_MakeObjectFuncs[8])();

struct ObjectHeader* MakeObject(u8 arg0)
{
    return g_MakeObjectFuncs[arg0]();
}
