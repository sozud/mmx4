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

void func_80066B00(struct MainObj* self)
{
    struct Main45Ext* owner;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    D_800FF9B0[self->unk5](self);
    func_8002D9BC(self);
    owner = self->ext.main_46.owner;

    if ((func_8002DD04(self) < 0) || ((owner->attack_flags & 7) == 7)) {
        self->x_pos.i.hi = (u16)self->x_pos.i.hi - 0x54;
        self->y_pos.i.hi = (u16)self->y_pos.i.hi - 0x5B;
        func_800AF808(BASE_OBJECT(self));
        func_800C813C(6, D_800FF99C, self);
        self->x_pos.i.hi = (u16)self->x_pos.i.hi + 0x54;
        self->y_pos.i.hi = (u16)self->y_pos.i.hi + 0x5B;
        self->unk42 &= 0x7FFF;
        func_80015D60(self, 0xE);
        owner->attack_flags |= 8;
        self->state = 2;
    } else {
        if (self->unk42 & 0x8000) {
            owner->layer_signals->collision_state = 2;
        }
        func_8002B318(BASE_OBJECT(self), 0x100, 0x100);
    }
}

void func_80066C40(struct MainObj* arg0)
{
    func_8002B318(BASE_OBJECT(arg0), 0x100, 0x100);
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

    if (arg0->ext.main_46.owner->projectile_command == 3) {
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
            shot->unk7C = (struct WeaponObj*)arg0->ext.main_46.owner;
            shot->state = 0;
        }
        func_80015D60(arg0, 0xD);
        arg0->ext.main_46.owner->projectile_command = 0x80;
    }
}
