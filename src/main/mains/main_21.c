// MainObj, main_object_update_funcs[21]
// 80054C50..80054FE8
#include "common.h"

void func_80054C50(struct MainObj* arg0)
{
    D_800FC9FC[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    func_80015DC8(arg0);
}

void func_80054CA8(struct MainObj* arg0)
{
    struct MainObj* self;
    u8 bg_offset;

    self = arg0;
    self->unk60 = 1;
    self->unk61 = 0;
    bg_offset = g_Player.bg_offset;
    self->animation_table = (const u8* const*)D_800FC9DC;
    self->unk16 = 6;
    self->unk54 = &D_800FC9F4;
    self->unk50 = &D_800FC9F4;
    self->unk68 = &D_800FC9F8;
    self->collision_data = D_80108504;
    self->ext.main_21.timer_80 = 0x1E;
    self->unk20 = 0;
    self->unk24 = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk67 = 0;
    self->unk15 = 0;
    self->unk5C = 3;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->bg_offset = bg_offset;
    self->ext.main_21.timer_82 = self->unk2 * 0x14;
    func_80015D60(arg0, 0);
    self->state = 1;
    self->unk5 = 2;
}

INCLUDE_ASM("main/nonmatchings/mains/main_21", func_80054D8C);

void func_80054EF8(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 1) {
        arg0->state = 3;
    }
}

void func_80054F14(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_80054F34(struct MainObj* arg0)
{
    if (arg0->ext.main_21.timer_80 == 0) {
        if (arg0->ext.main_21.timer_82 == 0) {
            arg0->unk5 = 3;
            func_80015D60(arg0, 0);
            return;
        }
        arg0->ext.main_21.timer_82--;
        return;
    }
    arg0->ext.main_21.timer_80--;
}

void func_80054F98(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk2C = 0x5000;
        arg0->unk5 = 4;
    }
}

void func_80054FBC(struct MainObj* arg0)
{
    func_8002B694((struct AnimatedObj*)arg0);
}

void func_80054FDC(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_21.saved_unk5;
}
