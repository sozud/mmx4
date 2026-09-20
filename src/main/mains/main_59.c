// MainObj, main_object_update_funcs[59]
// 80074E84..8007501C
#include "common.h"

void func_80074E84(struct MainObj* self)
{
    s32* sprite_archive;
    s32 offset;

    if (--self->unk7C == 0) {
        sprite_archive = SP_SPRITE_FRAMES;
        *(s32*)&self->animation_speed = 0;
        offset = sprite_archive[2];
        self->animation_table = (const u8* const*)D_8010A4C0;
        self->unk42 = 0x788F;
        self->unk40 = 0;
        self->unk54 = 0;
        self->unk50 = &D_801016A4;
        self->sprite_frames = (u8*)sprite_archive + offset;
        func_80015D60(self, 2);

        if (get_random() & 1) {
            func_8001540C(0, 0, self);
        } else {
            func_8001540C(0, 1, self);
        }
        self->state++;
        func_8002B318(BASE_OBJECT(self), 0x18, 0x18);
    }
}

void func_80074F4C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x18);
    if ((arg0->animation_step.fields.relative_step < 0) || (func_8002B1E8(BASE_OBJECT(arg0), 0x18, 0x18) != 0)) {
        arg0->state++;
    }
}

void func_80074FC0(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_80074FE0(struct MainObj* arg0)
{
    D_801016A8[arg0->state](arg0);
}
