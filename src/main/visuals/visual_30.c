// VisualObj, visual_object_update_funcs[30]
// 800B4610..800B4B64
#include "common.h"

void func_800B4610(struct VisualObj* arg0)
{
    D_8010A6C8[arg0->state](arg0);
}

void func_800B464C(struct VisualObj* arg0)
{
    struct PlayerObj* player = arg0->unk50;

    arg0->state++;
    arg0->unk3C = player->unk3C;
    arg0->unk40 = player->unk40;
    arg0->unk42 = player->unk42 & 0x7FFF;
    arg0->bg_offset = player->bg_offset;
    arg0->animation_table = player->animation_table;
    arg0->unk15 = player->unk15;
    arg0->unk5 = (s8)((s32)((u8)arg0->unk2 << 24) >> 28);
    arg0->unk6 = 0;
    arg0->unk5C = 0;
    arg0->unk2 &= 0xF;
}

void func_800B46C8(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800B46E8(struct VisualObj* arg0)
{
    D_8010A6D4[arg0->unk5](arg0);
    if (arg0->unk50->state == 2) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
}

void func_800B4754(struct VisualObj* arg0)
{
    D_8010A6E4[arg0->unk6](arg0);
}

void func_800B4790(struct VisualObj* arg0)
{
    struct PlayerObj* player = arg0->unk50;

    arg0->unk16 = 4;
    arg0->x_pos.val = player->x_pos.val + ((arg0->unk15 == 0) ? FIXED(-5) : FIXED(5));
    arg0->y_pos.val = player->y_pos.val + FIXED(-224);
    func_80015D60(arg0, 0x12);
    arg0->unk6++;
}

void func_800B4808(struct VisualObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x100, 0x100);
    if (arg0->unk5C != 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void func_800B4858(struct VisualObj* arg0)
{
    D_8010A6EC[arg0->unk6](arg0);
}

void func_800B4894(struct VisualObj* arg0)
{
    struct PlayerObj* player;

    player = arg0->unk50;
    arg0->unk16 = 4;
    arg0->x_pos.val = player->x_pos.val + (arg0->unk15 != 0 ? FIXED(-5) : FIXED(5));
    arg0->y_pos.val = player->y_pos.val + FIXED(-16);
    func_80015D60(arg0, 0x14);
    arg0->unk6++;
}

void func_800B490C(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    is_on_screen(BASE_OBJECT(arg0));
    if (--arg0->unk54 == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void func_800B4960(struct VisualObj* arg0)
{
    D_8010A6F4[arg0->unk6](arg0);
}

void func_800B499C(struct VisualObj* arg0)
{
    struct PlayerObj* player;

    player = arg0->unk50;
    arg0->unk16 = 4;
    arg0->x_pos.val = player->x_pos.val + (arg0->unk15 == 0 ? FIXED(-7) : FIXED(7));
    arg0->y_pos.val = player->y_pos.val + FIXED(-93);
    func_80015D60(arg0, 0x11);
    arg0->unk54 = 0x30;
    arg0->unk6++;
}

void func_800B4A18(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    is_on_screen(arg0);
    if (--arg0->unk54 == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void func_800B4A6C(struct VisualObj* arg0)
{
    D_8010A6FC[arg0->unk6](arg0);
}

void func_800B4AA8(struct VisualObj* arg0)
{
    struct PlayerObj* entity = arg0->unk50;

    arg0->unk16 = 4;
    arg0->x_pos.val = entity->x_pos.val;
    arg0->y_pos.val = entity->y_pos.val + FIXED(32);
    func_80015D60(arg0, 0x15);
    arg0->unk54 = 0x20;
    arg0->unk6++;
}

void func_800B4B0C(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    if (--arg0->unk54 == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    } else {
        is_on_screen(arg0);
    }
}

void (*D_8010A6C8[])(struct VisualObj*) = {
    func_800B464C,
    func_800B46E8,
    func_800B46C8,
};

void (*D_8010A6D4[])(struct VisualObj*) = {
    func_800B4754,
    func_800B4858,
    func_800B4960,
    func_800B4A6C,
};

void (*D_8010A6E4[])(struct VisualObj*) = {
    func_800B4790,
    func_800B4808,
};

void (*D_8010A6EC[])(struct VisualObj*) = {
    func_800B4894,
    func_800B490C,
};

void (*D_8010A6F4[])(struct VisualObj*) = {
    func_800B499C,
    func_800B4A18,
};
