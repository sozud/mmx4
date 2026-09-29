// EffectObj, effect_object_update_funcs[27]
// 800BB9B8..800BBC14
#include "common.h"

// megaman never teleports in if nopped out
// asm(".rept 13 ; nop ; .endr");
void TeleportRelatedObjectUpdate(struct EffectObj* self)
{
    teleport_intro_state_funcs[self->state](self);
}

// teleport_intro_state_funcs state 0
void teleport_intro_init(struct EffectObj* self)
{
    if (D_80141BDC[0] == 0) {
        self->ext.effect_27.unk14 = 0;
        self->ext.effect_27.unk15 = 0;
        self->ext.effect_27.unk16 = 0;
        self->state = 1;
        self->unk5 = 0;
    }
}

// teleport_intro_state_funcs state 1
void teleport_intro_spawn_quads(struct EffectObj* self)
{
    struct QuadObj* quad;
    u32 var_i;

    switch (self->unk5) {
    case 0:
        quad = find_free_quad_obj();
        if (quad != NULL) {
            quad->active = 0x81;
            quad->id = 7;
            quad->unk2 = 0;
            quad->link.owner = self;
        }
        self->unk5 = 1;
        self->ext.effect_27.unk14++;
        return;
    case 1:
        var_i = 0;
        // spawn blue quads behind "READY"
        if (self->ext.effect_27.unk14 == 0) {
            self->ext.effect_27.unk14 = 0;
            do {
                quad = find_free_quad_obj();
                if (quad != NULL) {
                    quad->active = 0x81;
                    quad->id = 7;
                    quad->unk2 = 1;
                    quad->unk7 = var_i;
                    quad->link.owner = self;
                    self->ext.effect_27.unk14++;
                }
                var_i += 1;
            } while (var_i < 0xA);
            self->unk5 = 2;
            return;
        }
        return;
    case 2:
        var_i = 0;
        if (self->ext.effect_27.unk14 == 0) {
            self->ext.effect_27.unk14 = 0;
            do {
                quad = find_free_quad_obj();
                if (quad != NULL) {
                    quad->active = 0x81;
                    quad->id = 7;
                    quad->unk2 = 2;
                    quad->unk7 = get_random() & 3;
                    quad->link.owner = self;
                    self->ext.effect_27.unk14++;
                }
                var_i += 1;
            } while (var_i < 8);
            self->unk5 = 3;
            return;
        }
        break;
    case 3:
        if (self->ext.effect_27.unk14 == 0) {
            self->ext.effect_27.unk14 = 0;
            self->ext.effect_27.unk16 = 1;
        }
        break;
    }
}

// teleport_intro_state_funcs state 2
void teleport_intro_despawn(struct EffectObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*teleport_intro_state_funcs[])(struct EffectObj*) = {
    teleport_intro_init,
    teleport_intro_spawn_quads,
    teleport_intro_despawn,
};
