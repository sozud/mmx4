// MiscObj, misc_object_update_funcs[1]
// 800C7BF4..800C7EDC
#include "common.h"

struct Misc01AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Misc01AnimationStep D_8010D9F8[3] = {
    { 4, 0, 1, 0 },
    { 4, 0, 1, 1 },
    { 4, 0, 254, 2 },
};

struct Misc01AnimationStep D_8010DA04[7] = {
    { 4, 0, 1, 3 },
    { 4, 0, 1, 4 },
    { 4, 0, 1, 5 },
    { 4, 0, 1, 6 },
    { 4, 0, 1, 7 },
    { 4, 0, 1, 8 },
    { 4, 1, 0, 9 },
};

struct Misc01AnimationStep D_8010DA20[4] = {
    { 8, 0, 1, 10 },
    { 8, 0, 1, 11 },
    { 8, 0, 1, 12 },
    { 8, 0, 253, 11 },
};

struct Misc01AnimationStep D_8010DA30[4] = {
    { 6, 0, 1, 13 },
    { 6, 0, 1, 14 },
    { 6, 0, 1, 15 },
    { 6, 0, 253, 16 },
};

struct Misc01AnimationStep D_8010DA40[8] = {
    { 3, 0, 1, 17 },
    { 3, 0, 1, 18 },
    { 3, 0, 1, 19 },
    { 3, 0, 1, 20 },
    { 3, 0, 1, 21 },
    { 3, 0, 1, 22 },
    { 3, 0, 1, 23 },
    { 3, 1, 249, 24 },
};

struct Misc01AnimationStep D_8010DA60[9] = {
    { 3, 0, 1, 25 },
    { 3, 0, 1, 26 },
    { 3, 0, 1, 27 },
    { 3, 0, 1, 28 },
    { 3, 0, 1, 29 },
    { 3, 0, 1, 30 },
    { 3, 0, 1, 31 },
    { 3, 0, 1, 32 },
    { 3, 0, 248, 33 },
};

struct Misc01AnimationStep D_8010DA84[6] = {
    { 3, 0, 1, 34 },
    { 3, 0, 1, 35 },
    { 3, 0, 1, 36 },
    { 3, 0, 1, 37 },
    { 3, 0, 252, 38 },
    { 1, 0, 0, 40 },
};

struct Misc01AnimationStep* D_8010DA9C[8] = {
    D_8010D9F8,
    D_8010DA04,
    D_8010DA20,
    D_8010DA30,
    D_8010DA40,
    D_8010DA60,
    D_8010DA84,
    D_8010DA84,
};

void func_800C7BF4(struct MiscObj* arg0)
{
    D_8010DABC[arg0->state](arg0);
}

void func_800C7C30(struct MiscObj* arg0)
{
    s32 resource;
    s32 column;
    s32 row;

    arg0->state = 1;
    arg0->unk6 = 0;
    arg0->bg_offset = 0;
    arg0->animation_table = (u32**)D_8010DA9C;
    arg0->unk40 = D_801406A8[func_8002938C(0x84)] >> 7;
    column = func_8002938C(0x84);
    row = func_8002938C(0x84);
    column *= 4;
    arg0->unk42 = ((column + 0x18) % 16) | ((((row + 6) / 4) + 0x1E0) << 6);
    resource = func_8002938C(0x84);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    if (arg0->unk2 == 5) {
        arg0->unk16 = 5;
    } else {
        arg0->unk16 = 0x11;
    }
    func_80015D60(ANIMATED_OBJECT(arg0), arg0->unk2);
}

void func_800C7D40(struct MiscObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->state = 2;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800C7D84(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800C7DA4(s32 count, u8* variants, void* source, s32 x_velocity)
{
    struct BaseObj* source_obj;
    struct MiscObj* obj;
    s32 remaining;
    u8* variant;
    s32 velocity;

    variant = variants;
    remaining = count;
    velocity = x_velocity;
    source_obj = source;
    if (remaining & 0xFF) {
        do {
            obj = find_free_misc_obj();
            if (obj != NULL) {
                obj->active = 0x41;
                obj->id = 2;
                obj->unk15 = get_random() & 0x40;
                obj->state = 0;
                obj->unk5 = 0;
                obj->unk6 = 0;
                if (velocity != -1) {
                    obj->x_vel.val = velocity;
                    obj->unk2 = 0;
                } else {
                    obj->x_vel.val = 0;
                    obj->unk2 = 1;
                }
                obj->x_pos.val = source_obj->x_pos.val + D_8010DB08[get_random() & 7];
                obj->y_pos.val = source_obj->y_pos.val + D_8010DB28[get_random() & 7];
                obj->ext.unk.unk54 = *variant++;
            }
            remaining--;
        } while (remaining & 0xFF);
    }
}

void (*D_8010DABC[])(struct MiscObj*) = { func_800C7C30, func_800C7D40, func_800C7D84 };
