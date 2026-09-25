// MainObj, main_object_update_funcs[14]
// 8004CF24..8004D930
#include "common.h"

void func_8004CF24(struct MainObj* arg0)
{
    D_800FB9FC[arg0->state](arg0);
}

void func_8004CF60(struct MainObj* arg0)
{
    u8 bg_offset;
    s32 x_pos;
    s32 y_pos;

    arg0->active = 0x41;
    arg0->unk5C = 0xE;
    arg0->unk60 = 3;
    arg0->unk61 = 0;

    bg_offset = g_Player.bg_offset;
    x_pos = arg0->x_pos.val;
    y_pos = arg0->y_pos.val;

    arg0->collision_data = D_80106974;
    arg0->animation_table = (const u8* const*)D_800FB9AC;
    arg0->unk16 = 5;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk68 = 0;
    arg0->unk54 = &D_800FB88C;
    arg0->unk50 = &D_800FB88C;
    arg0->bg_offset = bg_offset;
    arg0->unk18.val = x_pos;
    arg0->unk1C.val = y_pos;
    func_8004D6CC(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 0);
    arg0->ext.main_14.unk80 = 0;
    arg0->ext.main_14.unk84 = 0;
    arg0->ext.main_14.visual_variant = 0;
    arg0->ext.main_14.unk8C = 0;
    arg0->ext.main_14.saved_unk5 = 0;
    arg0->ext.main_14.unk94 = 0;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->state++;
}

void func_8004D044(struct MainObj* arg0)
{
    s32 collision;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FBA08[arg0->unk5](arg0);
    func_8004D6FC(arg0);
    func_8002D9BC(arg0);
    collision = func_8002DD04(arg0);
    if (arg0->unk5 != 0) {
        arg0->ext.main_14.saved_unk5 = arg0->unk5;
    }
    if (collision < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(6, D_800FB9F4, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 8);
    } else {
        if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) == 0) {
            func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
            return;
        }
        if (arg0->x_pos.val > g_Player.x_pos.val && arg0->ext.main_14.unk8C == 0) {
            arg0->ext.main_14.unk94 = 1;
        }
    }
    arg0->state = 2;
}

void func_8004D160(struct MainObj* arg0)
{
    arg0->ext.main_14.unk80 = 0;
    arg0->ext.main_14.unk84 = 0;
    engine_obj.character_state.bytes[0] = 0;
    func_80015930(2, 0x40);
    if (arg0->ext.main_14.unk94 != 0) {
        func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8004D1C8(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_14.saved_unk5;
}

void func_8004D1D4(struct MainObj* arg0)
{
    D_800FBA20[arg0->unk6](arg0);
}

void func_8004D210(struct MainObj* arg0)
{
    s32* velocity;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8004D784(arg0, 3);
    func_8001540C(2, 0x40, arg0);

    velocity = D_800FB89C;
    arg0->ext.main_14.unk80 = 0x20;
    arg0->ext.main_14.unk84 = 1;
    if (arg0->unk15 & 0x40) {
        velocity++;
    }
    arg0->unk20 = *velocity;
    arg0->unk6++;
}

void func_8004D290(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (--arg0->ext.main_14.unk80 == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_8004D2E0(struct MainObj* arg0)
{
    D_800FBA28[arg0->unk6](arg0);
}

void func_8004D31C(struct MainObj* arg0)
{
    func_80015D60(arg0, 1);
    arg0->ext.main_14.unk80 = 0x2E;
    arg0->unk20 = 0;
    arg0->unk54 = (const u8*)D_800FB890;
    arg0->unk50 = (const u8*)D_800FB890;
    arg0->unk6++;
}

void func_8004D370(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_14.unk80 == 0) {
        func_80015D60(arg0, 2);
        arg0->unk6++;
    }
}

void func_8004D3C8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_14.visual_variant == 7) {
        arg0->unk5 = 4;
        arg0->unk6 = 0;
    }
}

void func_8004D408(struct MainObj* arg0)
{
    D_800FBA34[arg0->unk6](arg0);
}

void func_8004D444(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->ext.main_14.unk80 = 0xC;
    arg0->unk6++;
}

void func_8004D480(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_14.unk80 == 0) {
        arg0->ext.main_14.visual_variant = 0xFF;
        arg0->unk6++;
    }
}

void func_8004D4D0(struct MainObj* arg0)
{
    struct EffectObj* effect;

    effect = find_free_effect_obj();
    if (effect != 0) {
        effect->active = 1;
        effect->id = 0x11;
        effect->unk2 = arg0->unk2;
        effect->on_screen = 0;
        effect->state = 0;
        effect->unk5 = 0;
        effect->unk6 = 0;
        effect->unk7 = 0;
        effect->x_pos.val = arg0->x_pos.val;
        effect->y_pos.val = arg0->y_pos.val;
        effect->ext.effect_17.source = ANIMATED_OBJECT(arg0);
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015930(2, 0x40);
    func_8001540C(2, 0x41, arg0);
    func_8004D84C(ANIMATED_OBJECT(arg0));
    arg0->unk6++;
}

void func_8004D580(struct MainObj* arg0)
{
    arg0->ext.main_14.unk8C = 1;
    func_8001540C(5, 4, arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 0);
    arg0->unk6 = 0;
    arg0->unk5++;
}

void func_8004D5E0(struct MainObj* arg0)
{
    D_800FBA44[arg0->unk6](arg0);
}

void func_8004D61C(struct MainObj* self)
{
    s32* table;
    s32 velocity;

    func_80015D60(self, 0);
    func_80015DC8(ANIMATED_OBJECT(self));

    table = D_800FB89C;
    if (self->unk15 & 0x40) {
        table++;
    }

    velocity = *table;
    self->unk54 = (const u8*)&D_800FB88C;
    self->unk50 = (const u8*)&D_800FB88C;
    self->unk20 = velocity;
    engine_obj.character_state.bytes[0] = 0;
    self->unk6++;
}

void func_8004D69C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8004D6CC(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D6FC);

void func_8004D784(struct MainObj* arg0, s8 arg1)
{
    struct VisualObj* temp_v0;

    temp_v0 = find_free_visual_obj();
    if (temp_v0 != 0) {
        temp_v0->active = 0x41;
        temp_v0->id = 0xB;
        temp_v0->unk50 = PLAYER_OBJECT(arg0);
        temp_v0->unk2 = arg1;
        arg0->ext.main_14.visual_variant = arg1;
        temp_v0->state = 0;
        temp_v0->unk5 = 0;
        temp_v0->unk6 = 0;
        temp_v0->unk38 = 0;
        temp_v0->unk3C = ANIMATED_OBJECT(arg0)->unk3C;
        temp_v0->animation_table = ANIMATED_OBJECT(arg0)->animation_table;
        temp_v0->unk40 = arg0->unk40;
        temp_v0->unk42 = arg0->unk42;
        temp_v0->unk16 = 4;
        temp_v0->x_pos.val = arg0->x_pos.val;
        temp_v0->y_pos.val = arg0->y_pos.val;
    }
}

void func_8004D84C(struct AnimatedObj* arg0)
{
    struct VisualObj* visual_obj;
    u32 i;
    u32 j;

    for (j = 0; j < 3; j++) {
        for (i = 0; i < 4; i++) {
            visual_obj = find_free_visual_obj();
            if (visual_obj == NULL) {
                return;
            }

            visual_obj->active = 0x41;
            visual_obj->unk50 = PLAYER_OBJECT(arg0);
            visual_obj->id = 8;
            visual_obj->unk2 = i;
            visual_obj->state = 0;
            visual_obj->unk5 = 0;
            visual_obj->unk6 = 0;
            visual_obj->bg_offset = arg0->bg_offset;
            visual_obj->unk38 = 0;
            visual_obj->unk3C = arg0->unk3C;
            visual_obj->animation_table = arg0->animation_table;
            visual_obj->unk40 = arg0->unk40;
            visual_obj->unk42 = arg0->unk42;
            visual_obj->unk16 = 6;
            visual_obj->x_pos.val = arg0->x_pos.val;
            visual_obj->y_pos.val = arg0->y_pos.val;
        }
    }
}
