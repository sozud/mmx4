// ShotObj, shot_object_update_funcs[23]
// 8009DD40..8009E0B8
#include "common.h"

void func_8009DD40(struct ShotObj* arg0)
{
    D_801090AC[arg0->state](arg0);
}

void func_8009DD7C(struct ShotObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 5;
    arg0->timer = -0x32;
    if (arg0->unk2 != 0) {
        arg0->unk5 = 2;
    } else {
        arg0->unk5 = 0;
        arg0->unk84.value = 0;
    }
    arg0->unk54 = D_80109028;
    arg0->unk50.data = D_80109028;
    arg0->unk58.data = D_8010902C[0];
    arg0->unk68 = NULL;
    arg0->unk5C = 3;
    arg0->unk60 = 3;
    arg0->unk61 = 0;
    func_80015D60(arg0, 0x13);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_23", func_8009DE04);

void func_8009DF40(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
}

void func_8009DF60(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk7C->unk80.word = 0;
    }
    func_80015DC8(arg0);
}

void func_8009DFA0(struct ShotObj* self)
{
    struct VisualObj* visual;

    if (self->unk6 == 0) {
        self->unk6 = 1;
        func_80015D60(self, 0x12);
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = (s8)(u8)self->active;
            visual->id = 0x14;
            visual->unk2 = 0;
            visual->x_pos.val = self->x_pos.val;
            visual->y_pos.val = self->y_pos.val;
            visual->animation_table = self->animation_table;
            visual->unk40 = self->unk40;
            visual->unk3C = self->unk3C;
            visual->unk42 = self->unk42 & 0x7FFF;
            visual->unk16 = self->unk16;
            visual->unk15 = self->unk15;
            visual->unk50 = PLAYER_OBJECT(self);
        }
    } else {
        if (self->animation_step.fields.relative_step == 0) {
            self->unk5 = 0;
            self->unk6 = 0;
            self->unk2 = 0;
            func_80015D60(self, 0x13);
        }
        func_80015DC8(ANIMATED_OBJECT(self));
    }
}

void func_8009E098(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80109014[5])(struct ShotObj*) = {
    func_8009D85C,
    func_8009D8F0,
    func_8009DA28,
    func_8009DA7C,
    func_8009DB1C,
};

u8 D_80109028[4] = { 0xFC, 0x82, 0x07, 0x9B };

u8 D_8010902C[32][4] = {
    { 2, 1, 2, 0 },
    { 2, 0, 2, 2 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 0, 0, 2, 1 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 0, 0 },
    { 2, 1, 2, 1 },
    { 2, 1, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 1, 2, 1 },
    { 2, 1, 2, 1 },
    { 2, 1, 2, 1 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 1, 2, 1 },
    { 2, 0x7F, 2, 0 },
    { 2, 0, 2, 0 },
    { 2, 0, 2, 0 },
};

void (*D_801090AC[])(struct ShotObj*) = {
    func_8009DD7C,
    func_8009DE04,
    func_8009E098,
};

void (*D_801090B8[3])(struct ShotObj*) = {
    func_8009DF40,
    func_8009DF60,
    func_8009DFA0,
};
