// MainObj, main_object_update_funcs[46]
// 80066A48..80066DAC
#include "common.h"

void func_80066A48(struct MainObj* arg0)
{
    D_800FF9A4[arg0->state](arg0);
}

void func_80066A84(struct MainObj* arg0)
{
    arg0->unk5C = 0x20;
    arg0->unk5D = 0x20;
    arg0->unk60 = 4;
    arg0->collision_data = (const u16*)D_80106670;
    arg0->unk20 = FIXED(1);
    arg0->unk16 = 3;
    arg0->unk54 = D_800FF994;
    arg0->unk50 = D_800FF998;
    arg0->state = 1;
    arg0->unk61 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk68 = NULL;
    arg0->unk15 = 0;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_46", func_80066B00);

void func_80066C40(struct MainObj* arg0)
{
    func_8002B318(arg0, 0x100, 0x100);
}

void func_80066C64(struct MainObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_80066C74(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        if (arg0->x_pos.i.hi >= 0x1AA1) {
            arg0->unk7C = 0x78;
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            return;
        }
        func_8002B718(MOVING_OBJECT(arg0));
    }
}

void func_80066CCC(struct MainObj* arg0)
{
    struct ShotObj* shot;

    if (arg0->ext.main_46.unk80->x_pos.bytes[0] == 3) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x18;
            shot->unk2 = 0;
            shot->unk40 = arg0->unk40;
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)arg0->animation_table;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->bg_offset = (u8)arg0->bg_offset;
            shot->x_pos.i.hi = (u16)arg0->x_pos.i.hi - 0x2D;
            shot->y_pos.i.hi = (u16)arg0->y_pos.i.hi - 0x5D;
            shot->unk15 = 0;
            shot->unk7C = arg0->ext.main_46.unk80;
            shot->state = 0;
        }
        func_80015D60(arg0, 0xD);
        arg0->ext.main_46.unk80->x_pos.bytes[0] = 0x80;
    }
}
