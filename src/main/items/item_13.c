// ItemObj, item_object_update_funcs[13]
// 800C351C..800C3880
#include "common.h"

struct Item13AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item13AnimationStep D_8010D008[1] = {
    { 8, 0, 0, 0 },
};

struct Item13AnimationStep D_8010D00C[7] = {
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 3, 0, 1, 4 },
    { 3, 0, 1, 5 },
    { 3, 0, 1, 6 },
    { 0x21, 1, 0, 7 },
};

struct Item13AnimationStep* D_8010D028[2] = {
    D_8010D008,
    D_8010D00C,
};

void func_800C351C(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010D030[arg0->state](arg0);
    is_on_screen(arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_13", func_800C3578);

void func_800C369C(struct ItemObj* arg0)
{
    struct EngineObj* engine = &engine_obj;
    struct PlayerObj* player = &g_Player;

    if (arg0->unk5 == 0) {
        func_800C36E8(arg0, engine, player);
        return;
    }
    func_800C37C4(arg0, engine, player);
}

void func_800C36E8(struct ItemObj* self, struct EngineObj* engine,
    struct PlayerObj* player)
{
    s16 y_diff;
    struct Unk_unk68* player_bounds;
    struct Unk_unk68* item_bounds;

    y_diff = (u16)self->y_pos.i.hi - (u16)player->y_pos.i.hi;
    if (y_diff >= 0) {
        player_bounds = player->unk68;
        item_bounds = self->unk68;
        if (y_diff >= player_bounds->unk3 + player_bounds->unk1 + (item_bounds->unk3 - item_bounds->unk1)) {
            if (engine->unk10 == 0) {
                engine->unk10 = 1;
                engine->unk11 = 1;
                engine->unk12 = 1;
                engine->unk13 = 1;
                engine->unk14 = 1;
            }
            func_80015D60(self, 1);
            func_8001540C(5, 2, self);
            if (self->unk2 != 0) {
                background_objects[0].unk28 = 0x100;
            }
            self->unk5++;
        }
    }
}

void func_800C37C4(struct ItemObj* arg0, struct EngineObj* arg1,
    struct PlayerObj* arg2)
{
    if (arg0->animation_step.fields.event == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    } else {
        if (arg1->unk10 != 0) {
            arg1->unk10 = 0;
            arg1->unk11 = 0;
            arg1->unk12 = 0;
            arg1->unk13 = 0;
            arg1->unk14 = 0;
        }
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void func_800C3828(struct ItemObj* arg0)
{
    u8 type;

    func_8002E184(PLAYER_OBJECT(arg0));

    type = 7;
    if (engine_obj.substage != 0) {
        type = 0x10;
    }

    func_800DABE4(type, (s16)(arg0->x_pos.u.hi - 0x10),
        arg0->y_pos.i.hi);
}

void (*D_8010D030[])(struct ItemObj*) = {
    func_800C3578,
    func_800C369C,
    func_800C3828,
};

u8 D_8010D03C[4] = { 0, 8, 0x20, 0x10 };
