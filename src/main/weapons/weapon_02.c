// WeaponObj, weapon_object_update_funcs[2]
// 80093CBC..80094A78
#include "common.h"

void func_80093CBC(struct WeaponObj* arg0)
{
    s32 should_change_state;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    should_change_state = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        should_change_state = 1;
    }
    if (g_Player.weapon != 2) {
        should_change_state = 1;
    }
    if (g_Player.shot_type == 0xB) {
        should_change_state = 1;
    }
    if (should_change_state != 0) {
        arg0->state = 3;
    }

    D_80108854[arg0->state](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_80093D78);

void func_80093EB4(struct WeaponObj* arg0)
{
    u32 i;

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x28, 0x38) == 0) {
        if (arg0->ext.weapon_2.lifetime == 0) {
            func_8001540C(0, 0x1A, arg0);
            for (i = 0; i < 8U; i++) {
                func_8009416C(arg0);
            }
        } else {
            arg0->ext.weapon_2.lifetime--;
            func_80015DC8(ANIMATED_OBJECT(arg0));
            D_80108864[arg0->unk5](arg0);
            if (arg0->unk50 != NULL) {
                if (arg0->ext.weapon_2.timer == 0) {
                    arg0->ext.weapon_2.timer = 8;
                    arg0->unk64++;
                } else {
                    arg0->ext.weapon_2.timer--;
                }
            }
            func_8002B318(BASE_OBJECT(arg0), 0x28, 0x38);
            return;
        }
    }
    func_80094154(arg0);
}

void func_80093FC4(struct WeaponObj* arg0)
{
    if (arg0->animation_step.fields.event & 0x40) {
        arg0->animation_step.fields.event = 0;
        func_8001540C(0, 0x1A, arg0);
    }
    if (arg0->animation_step.fields.event & 0x80) {
        arg0->unk68 = D_8010884C;
        arg0->animation_step.fields.event = 0;
        arg0->unk67 = 0;
        arg0->unk5 = 1;
    }
}

void func_8009403C(struct WeaponObj* arg0)
{
    if (!(arg0->unk70 & 8)) {
        arg0->unk67 = -1;
        arg0->unk2C = 0x4200;
        arg0->x_vel.val = 0;
        arg0->unk28.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk5 = 2;
    }
}

void func_80094078(struct WeaponObj* arg0)
{
    u32 i;

    if (arg0->unk70 & 8) {
        func_8001540C(0, 0x1A, arg0);
        arg0->unk67 = 0;
        i = 0;
        do {
            func_8009416C(arg0);
            i++;
        } while (i < 4);
        func_80028B68(8, 6, 1);
        arg0->unk5 = 1;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_80094104(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    arg0->unk68 = 0;
    g_Player.shot_count--;
    g_Player.special_shot_count--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_80094154(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
    arg0->unk68 = 0;
}

void func_8009416C(struct WeaponObj* arg0)
{
    struct MiscObj* temp_v0;

    temp_v0 = find_free_misc_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 1;
        temp_v0->id = 0x25;
        temp_v0->unk2 = 0;
        temp_v0->bg_offset = arg0->bg_offset;
        temp_v0->x_pos.val = arg0->x_pos.val;
        temp_v0->y_pos.val = arg0->y_pos.val;
    }
}

// WeaponObj, weapon_object_update_funcs[11]

void func_800941D4(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        disabled = 1;
    }
    if (g_Player.weapon != 2) {
        disabled = 1;
    }
    if (disabled != 0) {
        arg0->state = 3;
    }
    if (arg0->unk2 == 0) {
        D_80108870[arg0->state](arg0);
    } else {
        D_80108880[arg0->state](arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_80094280);

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_800942E8);

void func_8009443C(s8 arg0)
{
    struct WeaponObj* weapon_obj;

    weapon_obj = find_free_weapon_obj();
    if (weapon_obj != NULL) {
        weapon_obj->active = 1;
        weapon_obj->id = 0xB;
        weapon_obj->unk2 = arg0;
        weapon_obj->bg_offset = g_Player.bg_offset;
        g_Player.shot_count++;
        g_Player.special_shot_count++;
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_02", func_800944B8);

void func_8009462C(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x28, 0x38) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->unk5 == 0) {
            if (arg0->animation_step.fields.event == 1) {
                arg0->unk50 = D_80108850;
                arg0->animation_step.fields.event = 0;
                arg0->unk64 = 1;
            }
            if (arg0->animation_step.fields.event == 2) {
                arg0->animation_step.fields.event = 0;
                arg0->unk5 = (u8)arg0->unk5 + 1;
            }
        } else {
            func_8002B718(MOVING_OBJECT(arg0));
        }
        func_8002B318(BASE_OBJECT(arg0), 0x28, 0x38);
        return;
    }
    func_80094154(arg0);
}

void func_800946F0(struct MiscObj* arg0)
{
    s32 var_a1;

    var_a1 = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        var_a1 = 1;
    }
    if (g_Player.weapon != 2) {
        var_a1 = 1;
    }
    if (g_Player.shot_type == 0xB) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->state == 0) {
        func_80094794(arg0);
        return;
    }
    func_80094A04(arg0);
}

void func_80094794(struct MiscObj* arg0)
{
    s32* player_gfx;
    s32* sprite_frames;
    s32 gfx_offset;
    s32 frames_offset;

    func_800948D4(arg0);
    player_gfx = SP_PLAYER_GFX;
    gfx_offset = player_gfx[0xC / 4];
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + gfx_offset;
    frames_offset = sprite_frames[0x2C / 4];
    arg0->animation_table = D_8011C094;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    func_80015D60(arg0, (get_random() & 3) + 2);
}

void func_8009481C(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_8009485C(arg0);
    } else {
        func_80094A04(arg0);
    }
}

void func_8009485C(struct MiscObj* arg0)
{
    s32* sprite_frames;
    s32 offset;

    func_800948D4(arg0);
    sprite_frames = SP_SPRITE_FRAMES;
    offset = sprite_frames[6];
    arg0->animation_table = D_8011C018;
    arg0->unk40 = 0;
    arg0->unk42 = 0x7802;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + offset;
    func_80015D60(arg0, D_8010889C[get_random() & 7]);
}

void func_800948D4(struct MiscObj* self)
{
    self->on_screen = 1;

    if (get_random() & 1) {
        self->x_pos.u.hi += get_random() & 0xF;
    } else {
        self->x_pos.u.hi -= get_random() & 0xF;
    }

    if (get_random() & 1) {
        self->y_pos.u.hi += get_random() & 0x17;
    } else {
        self->y_pos.u.hi -= get_random() & 0x17;
    }

    if (get_random() & 1) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }

    self->x_vel.val = D_801088A4[get_random() & 7];
    self->y_vel.val = D_801088C4[get_random() & 7];
    self->unk28 = 0;
    self->unk2C = FIXED(0.3125);
    self->unk5 = 0;
    self->state++;
    func_8002B318(BASE_OBJECT(self), 0x14, 0x18);
}

void func_80094A04(struct MiscObj* arg0)
{
    s8 on_screen;

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x14, 0x18) == 0) {
        func_8002B694(ANIMATED_OBJECT(arg0));
        on_screen = arg0->on_screen ^ 1;
        arg0->on_screen = on_screen;
        if (on_screen != 0) {
            func_8002B318(BASE_OBJECT(arg0), 0x14, 0x18);
        }
    } else {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

struct Unk_unk68 D_80108848[] = {
    { -22, -44, 0x2C, 0x56 },
};

struct Unk_unk68 D_8010884C[] = {
    { 0, 0, 6, 0x1B },
};

struct Unk_unk68 D_80108850[] = {
    { -34, -46, 0x42, 0x60 },
};

void (*D_80108854[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80093D78,
    (void (*)(struct WeaponObj*))func_80093EB4,
    (void (*)(struct WeaponObj*))func_80094104,
    (void (*)(struct WeaponObj*))func_80094104,
};

void (*D_80108864[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80093FC4,
    (void (*)(struct WeaponObj*))func_8009403C,
    (void (*)(struct WeaponObj*))func_80094078,
};

void (*D_80108870[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80094280,
    (void (*)(struct WeaponObj*))func_800942E8,
    (void (*)(struct WeaponObj*))func_80094104,
    (void (*)(struct WeaponObj*))func_80094104,
};

void (*D_80108880[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_800944B8,
    (void (*)(struct WeaponObj*))func_8009462C,
    (void (*)(struct WeaponObj*))func_80094104,
    (void (*)(struct WeaponObj*))func_80094104,
};

u16 D_80108890[] = {
    0x0000,
    0x0000,
    0x0040,
    0x0060,
    0x0028,
    0x0070,
};

u8 D_8010889C[] = {
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x08,
    0x05,
};

s32 D_801088A4[] = {
    (s32)0xFFFD0000,
    (s32)0xFFFE0000,
    (s32)0x00018000,
    (s32)0x00028000,
    (s32)0xFFFC8000,
    (s32)0xFFFD8000,
    (s32)0x00020000,
    (s32)0x00030000,
};

s32 D_801088C4[] = {
    (s32)0x00038000,
    (s32)0x00048000,
    (s32)0x00060000,
    (s32)0x00030000,
    (s32)0x00040000,
    (s32)0x00050000,
    (s32)0x00058000,
    (s32)0x00028000,
};
