// MainObj, main_object_update_funcs[14]
// 8004CF24..8004D930
#include "common.h"
#include "func_tables.h"

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

struct Unk_unk68 D_800FB88C = { -10, -15, 32, 25 };

struct Unk_unk68 D_800FB890[3] = {
    { -9, -25, 28, 48 },
    { -27, -25, 33, 52 },
    { -10, 27, 26, 3 },
};

s32 D_800FB89C[] = {
    (s32)0xFFFE0000,
    (s32)0x00020000,
};

union AnimationStep D_800FB8A4[] = {
    { 0x00010005 },
    { 0x01010004 },
    { 0x02010003 },
    { 0x03010004 },
    { 0x04010005 },
    { 0x03010004 },
    { 0x05010003 },
    { 0x01F90004 },
};

union AnimationStep D_800FB8C4[] = {
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010006 },
    { 0x0A010008 },
    { 0x0B010003 },
    { 0x0C010003 },
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F010003 },
    { 0x10010005 },
    { 0x0F010003 },
    { 0x0E000003 },
};

union AnimationStep D_800FB8F8[] = {
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x11010001 },
    { 0x12FD0001 },
};

union AnimationStep D_800FB908[] = {
    { 0x13010006 },
    { 0x14010006 },
    { 0x15010006 },
    { 0x16FD0006 },
};

union AnimationStep D_800FB918[] = {
    { 0x17010004 },
    { 0x18010004 },
    { 0x19010004 },
    { 0x1AFD0004 },
};

union AnimationStep D_800FB928[] = {
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1EFD0002 },
};

union AnimationStep D_800FB938[] = {
    { 0x1F010001 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x22FD0001 },
};

union AnimationStep D_800FB948[] = {
    { 0x28010003 },
    { 0x23010003 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x3A010002 },
    { 0x39010002 },
    { 0x3B000002 },
};

union AnimationStep D_800FB96C[] = {
    { 0x29000001 },
};

union AnimationStep D_800FB970[] = {
    { 0x2A000001 },
};

union AnimationStep D_800FB974[] = {
    { 0x2B000001 },
};

union AnimationStep D_800FB978[] = {
    { 0x2C000001 },
};

union AnimationStep D_800FB97C[] = {
    { 0x2D000001 },
};

union AnimationStep D_800FB980[] = {
    { 0x2E000001 },
};

union AnimationStep D_800FB984[] = {
    { 0x2F010005 },
    { 0x30010004 },
    { 0x31010003 },
    { 0x32FD0004 },
};

union AnimationStep D_800FB994[] = {
    { 0x33000001 },
};

union AnimationStep D_800FB998[] = {
    { 0x34000001 },
};

union AnimationStep D_800FB99C[] = {
    { 0x35010005 },
    { 0x36010005 },
    { 0x37010005 },
    { 0x38FD0005 },
};

union AnimationStep* D_800FB9AC[] = {
    D_800FB8A4,
    D_800FB8C4,
    D_800FB8F8,
    D_800FB908,
    D_800FB918,
    D_800FB928,
    D_800FB938,
    D_800FB948,
    D_800FB96C,
    D_800FB970,
    D_800FB974,
    D_800FB978,
    D_800FB97C,
    D_800FB980,
    D_800FB984,
    D_800FB994,
    D_800FB998,
    D_800FB99C,
};

u8 D_800FB9F4[] = {
    0x08,
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x00,
    0x00,
};

void (*D_800FB9FC[])(struct MainObj*) = {
    func_8004CF60,
    func_8004D044,
    func_8004D160,
};

void (*D_800FBA08[6])() = {
    func_8009216C,
    func_8004D1C8,
    func_8004D1D4,
    func_8004D2E0,
    func_8004D408,
    func_8004D5E0,
};

void (*D_800FBA20[2])() = {
    func_8004D210,
    func_8004D290,
};

void (*D_800FBA28[3])() = {
    func_8004D31C,
    func_8004D370,
    func_8004D3C8,
};

void (*D_800FBA34[4])(struct MainObj*) = {
    func_8004D444,
    func_8004D480,
    func_8004D4D0,
    func_8004D580,
};

void (*D_800FBA44[2])() = {
    func_8004D61C,
    func_8004D69C,
};
