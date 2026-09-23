// ItemObj, item_object_update_funcs[27]
// 800C7164..800C7A68
#include "common.h"

struct Item26AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

extern struct Item26AnimationStep D_8010D6BC[];
extern struct Item26AnimationStep D_8010D6C0[];
extern struct Item26AnimationStep D_8010D750[];
extern struct Item26AnimationStep D_8010D7E0[];
extern struct Item26AnimationStep D_8010D7EC[];
extern struct Item26AnimationStep D_8010D7F0[];
extern struct Item26AnimationStep D_8010D810[];
extern struct Item26AnimationStep D_8010D814[];
extern struct Item26AnimationStep D_8010D8C8[];
extern struct Item26AnimationStep D_8010D904[];
extern struct Item26AnimationStep D_8010D94C[];

struct Item26AnimationStep* D_8010D964[11] = {
    D_8010D6BC,
    D_8010D6C0,
    D_8010D750,
    D_8010D7E0,
    D_8010D7EC,
    D_8010D7F0,
    D_8010D810,
    D_8010D814,
    D_8010D8C8,
    D_8010D904,
    D_8010D94C,
};

void func_800C7164(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010D990[arg0->state](arg0);
    func_8002E184(arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_27", func_800C71C0);

void func_800C7460(struct ItemObj* arg0)
{
    D_8010D9A4[arg0->unk5](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->state = 4;
}

void func_800C74D4(struct ItemObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 3;
        engine_obj.character_state.bytes[arg0->unk2 + 6] = 2;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800C7538(struct ItemObj* arg0)
{
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800C7558(struct ItemObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_800C7578(struct ItemObj* self)
{
    struct MiscObj* effect;
    u8 height;

    if (func_800C7970(self, &g_Player)) {
        g_Player.x_pos.i.hi = (s16)(u16)self->x_pos.i.hi;
        height = self->unk68->unk3;
        g_Player.y_pos.i.hi = ((u16)self->y_pos.i.hi - height) - g_Player.unk68->unk3;
        func_80036AE4(0x14, g_Player.unk15);
        reset_main_and_shots();
        effect = find_free_misc_obj();
        if (effect != NULL) {
            effect->active = 0x41;
            effect->id = 0x33;
            effect->unk2 = 0x10;
            effect->x_pos.val = self->x_pos.val;
            effect->y_pos.val = self->y_pos.val;
            effect->ext.misc_5.owner = MAIN_OBJECT(self);
        }
        self->unk5 = 1;
    }
}

void func_800C7648(struct ItemObj* arg0)
{
    if (g_Player.unkC0 < 0) {
        arg0->tail_ext.unk1.unk84.timer = 0;
        background_objects[0].unk26 = background_objects[0].x_pos.i.hi;
        background_objects[0].unk24 = background_objects[0].x_pos.i.hi;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        func_8001540C(5, 0, NULL);
    }
}

void func_800C76A4(struct ItemObj* arg0)
{
    D_8010D9DC[arg0->unk6](arg0);
}

void func_800C76E0(struct ItemObj* arg0)
{
    struct MiscObj* misc;

    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x33;
        misc->unk2 = 0x20;
        misc->x_pos.val = arg0->x_pos.val;
        misc->y_pos.val = arg0->y_pos.val;
        misc->ext.misc_24.main = MAIN_OBJECT(arg0);
        arg0->tail_ext.unk1.unk84.timer = 0x78;
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

void func_800C7754(struct ItemObj* arg0)
{
    if (--arg0->tail_ext.unk1.unk84.timer == 0) {
        func_80015D60(arg0, 4);
        func_80015D60(arg0->unk7C.object, 8);
        arg0->tail_ext.unk1.unk84.timer = 0x78;
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

void func_800C77BC(struct ItemObj* arg0)
{
    if (--arg0->tail_ext.unk1.unk84.timer == 0) {
        func_80036AE4(0x16, g_Player.unk15);
        func_8001540C(5, 1, NULL);
        arg0->tail_ext.unk1.unk84.timer = 0x28;
        arg0->unk6 = (u8)arg0->unk6 + 1;
    }
}

void func_800C7830(struct ItemObj* arg0)
{
    if (--arg0->tail_ext.unk1.unk84.timer == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_800C785C(struct ItemObj* arg0)
{
    u8 checkpoint;

    if (g_Player.unkC0 < 0) {
        func_80036B18();
        checkpoint = (u8)arg0->unk2;
        engine_obj.unkF = -0x40;
        engine_obj.checkpoint = checkpoint & 0xF;
        arg0->state = 3;
        arg0->unk5 = 0;
    }
}

void func_800C78BC(struct ItemObj* self)
{
    u8 slot;
    struct MiscObj* misc;

    for (slot = 8; slot < 0x10; slot++) {
        if (engine_obj.character_state.bytes[slot] == 0) {
            break;
        }
    }

    if (slot == 0x10) {
        func_80015D60(self, 1);
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0x33;
            misc->unk2 = 0;
            misc->x_pos.val = self->x_pos.val;
            misc->y_pos.val = self->y_pos.val;
            misc->ext.misc_51.source = MAIN_OBJECT(self);
            self->unk7C.misc = misc;
        }
        self->unk5 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/items/item_27", func_800C7970);

void (*D_8010D990[])(struct ItemObj*) = {
    func_800C71C0,
    func_800C7460,
    func_800C74D4,
    func_800C7538,
    func_800C7558,
};

void (*D_8010D9A4[])(struct ItemObj*) = {
    func_800C7578,
    func_800C7648,
    func_800C76A4,
    func_800C785C,
    func_800C78BC,
};

u8 D_8010D9B8[4] = { 0, 0, 0x20, 8 };

u8* D_8010D9BC[8] = {
    &engine_obj.character_state.bytes[8],
    &engine_obj.character_state.bytes[9],
    &engine_obj.character_state.bytes[10],
    &engine_obj.character_state.bytes[11],
    &engine_obj.character_state.bytes[12],
    &engine_obj.character_state.bytes[13],
    &engine_obj.character_state.bytes[14],
    &engine_obj.character_state.bytes[15],
};

void (*D_8010D9DC[])(struct ItemObj*) = {
    func_800C76E0,
    func_800C7754,
    func_800C77BC,
    func_800C7830,
};
