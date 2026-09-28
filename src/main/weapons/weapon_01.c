// WeaponObj, weapon_object_update_funcs[1]
// 80092F08..80093CBC
#include "common.h"

void func_80092F08(struct WeaponObj* self)
{
    s32 should_reset;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;

    should_reset = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        should_reset = 1;
    }
    if (g_Player.weapon != 1) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        self->state = 3;
    }

    D_801087D4[self->state](self);
    if (self->unk75 != 0) {
        func_8002E184(PLAYER_OBJECT(self));
        if (self->unk72 & 4) {
            g_Player.unk71 &= 0xB;
        }
        if (self->unk72 & 8) {
            g_Player.unk71 &= 7;
        }
    }
}

void func_80093014(struct WeaponObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s32* player_gfx;
    s32* sprite_frames;
    s32 gfx_offset;
    s32 frames_offset;
    struct Weapon1Ext* ext;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    player_gfx = SP_PLAYER_GFX;
    arg0->unk50 = (const u8*)D_801087E8;
    gfx_offset = player_gfx[2];
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + gfx_offset;
    frames_offset = sprite_frames[10];
    arg0->animation_table = D_8011C070;
    arg0->unk40 = 0x520;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    arg0->unk15 = player->unk15;
    ext = &arg0->ext.weapon_1;
    func_80092E2C((struct VisualObj*)arg0, player, arg0->id);
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(8);
    } else {
        arg0->x_vel.val = FIXED(-8);
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk49 = 0;
    ext->lifetime = 0x69;
    ext->timer = 0x10;
    func_80015D60(arg0, 0);
    func_8001540C(1, 8, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    func_80093524(arg0);
}

void func_80093130(struct WeaponObj* arg0)
{
    u8 temp_v0;

    temp_v0 = arg0->ext.weapon_1.timer - 1;
    arg0->ext.weapon_1.timer = temp_v0;
    if (temp_v0 == 0) {
        func_80015D60(arg0, 1);
        arg0->unk16 = 3;
        arg0->state++;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B718(MOVING_OBJECT(arg0));
    }
    func_80093524(arg0);
}

void func_800931A8(struct WeaponObj* arg0)
{
    s32 expired;
    u8 timer;

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x18, 0x28) == 0) {
        timer = arg0->ext.weapon_1.lifetime - 1;
        expired = (timer & 0xFF) == 0;
        arg0->ext.weapon_1.lifetime = timer;
        if (arg0->unk72 & 0xC) {
            expired = 1;
        }
        if (expired != 0) {
            func_80093260(arg0);
        } else {
            D_801087EC[arg0->unk5](arg0);
        }
        func_80093524(arg0);
    } else {
        arg0->on_screen = 0;
        arg0->state = 3;
        arg0->unk50 = 0;
        arg0->unk75 = 0;
    }
}

void func_80093260(struct WeaponObj* arg0)
{
    func_80015D60(arg0, 3);
    arg0->unk50 = 0;
    arg0->unk75 = 0;
    arg0->state = 4;
    arg0->unk5 = 0;
}

void func_800932A0(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 2);
        arg0->unk50 = (const u8*)D_801087FC;
        arg0->unk68 = D_80108800;
        arg0->ext.weapon_1.unk90 = 0;
        arg0->unk75 = 1;
        arg0->unk5++;
    }
}

void func_80093310(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_800933A0(arg0, &arg0->ext.weapon_1.lifetime);
    if ((arg0->unk76 != 0) && ((arg0->unk72 & 3) != 0)) {
        func_80015D60(arg0, 4);
        if (arg0->unk72 & 1) {
            arg0->unk15 = 0x40;
        } else {
            arg0->unk15 = 0;
        }
        arg0->unk5++;
    }
}

void func_800933A0(struct WeaponObj* arg0, u8* arg1)
{
    if (arg1[4] == 0) {
        arg1[4] = 0xA;
        func_8001540C(0, 0x19, arg0);
        return;
    }
    arg1[4]--;
}

void func_800933EC(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk76 == 0) {
        func_80015D60(arg0, 5);
        arg0->unk5++;
    }
}

void func_8009343C(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80093260(arg0);
    }
}

void func_8009347C(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    arg0->unk75 = 0;
    if (arg0->unk2 == 0) {
        g_Player.shot_count--;
        g_Player.special_shot_count--;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800934D8(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->on_screen = 0;
        arg0->state = 3;
    } else {
        func_80093524(arg0);
    }
}

void func_80093524(struct WeaponObj* arg0)
{
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x28);
}

// WeaponObj, weapon_object_update_funcs[10]

void func_80093564(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        disabled = 1;
    }
    if (g_Player.weapon != 1) {
        disabled = 1;
    }
    if (disabled != 0) {
        arg0->state = 3;
    }
    if (arg0->unk2 == 0) {
        D_80108804[arg0->state](arg0);
    } else {
        D_80108818[arg0->state](arg0);
    }
}

void func_80093610(struct WeaponObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s32* player_gfx;
    s32* sprite_frames;
    s32 gfx_offset;
    s32 frames_offset;
    struct Weapon10Ext* ext;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    player_gfx = SP_PLAYER_GFX;
    arg0->unk50 = (const u8*)D_801087C8;
    gfx_offset = player_gfx[2];
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk38 = (u8*)player_gfx + gfx_offset;
    frames_offset = sprite_frames[10];
    arg0->animation_table = D_8011C070;
    arg0->unk40 = 0x530;
    arg0->unk42 = 0x7801;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + frames_offset;
    arg0->unk15 = player->unk15;
    ext = &arg0->ext.weapon_10;
    func_80092E2C((struct VisualObj*)arg0, player, arg0->id);
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(8);
    } else {
        arg0->x_vel.val = FIXED(-8);
    }
    arg0->unk49 = 1;
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    ext->timer = 0x10;
    ext->unk8F = 0;
    func_80015D60(arg0, 0);
    func_8001540C(1, 8, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    func_80093C54(arg0);
}

void func_8009372C(struct WeaponObj* arg0)
{
    D_8010882C[arg0->unk5](arg0);
    func_80093C54(arg0);
}

void func_8009377C(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_10.timer == 0) {
        func_80015D60(arg0, 6);
        arg0->unk15 = 0;
        arg0->unk5++;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->ext.weapon_10.timer--;
}

void func_800937EC(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 7);
        arg0->unk50 = (const u8*)D_801087CC;
        arg0->unk64 = 2;
        arg0->ext.weapon_10.timer = 0x3C;
        arg0->ext.weapon_10.unk90 = 0;
        arg0->unk5++;
    }
}

void func_80093858(struct WeaponObj* arg0)
{
    u8 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_800933A0(arg0, &arg0->ext.weapon_10.timer);
    temp_v0 = arg0->ext.weapon_10.timer;
    if (temp_v0 == 0) {
        temp_v0 = 0x98;
        arg0->ext.weapon_10.timer = temp_v0;
        arg0->ext.weapon_10.unk8F = 1;
        arg0->unk5++;
    } else {
        arg0->ext.weapon_10.timer = temp_v0 - 1;
    }
}

void func_800938C0(struct WeaponObj* arg0)
{
    u8* timer_ptr;

    timer_ptr = &arg0->ext.weapon_10.timer;
    if (arg0->ext.weapon_10.timer == 0) {
        func_80015D60(arg0, 8);
        arg0->unk50 = 0;
        arg0->state = 4;
    } else {
        arg0->ext.weapon_10.timer--;
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_800933A0(arg0, timer_ptr);
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_01", func_80093930);

void func_800939F4(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;
    u8 state;
    s32 y;

    owner = arg0->owner;
    if ((u8)owner->shot_fired != 0) {
        arg0->on_screen = 1;
        state = (u8)arg0->state + 1;
        arg0->x_pos.val = owner->x_pos.val;
        y = owner->y_pos.val;
        arg0->ext.weapon_10.timer = 0x10;
        arg0->state = state;
        arg0->unk5 = 0;
        arg0->y_pos.val = y;
        func_80093C54(arg0);
    }
}

void func_80093A5C(struct WeaponObj* arg0)
{
    D_8010883C[arg0->unk5](arg0);
    func_80093C54(arg0);
}

void func_80093AAC(struct WeaponObj* arg0)
{
    u8* timer;
    u8 temp_v0;

    timer = &arg0->ext.weapon_10.timer;
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 7);
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }

    temp_v0 = *timer;
    if (temp_v0 == 0) {
        arg0->unk50 = (const u8*)D_801087D0;
        arg0->unk64 = 1;
        *timer = 0x78;
        arg0->unk5++;
        return;
    }

    *timer = temp_v0 - 1;
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_80093B4C(struct WeaponObj* arg0)
{
    u8 temp_v0;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    temp_v0 = arg0->ext.weapon_10.timer;
    if (temp_v0 == 0) {
        arg0->unk64 = 2;
        arg0->ext.weapon_10.timer = 0x10;
        arg0->unk5++;
        return;
    }
    arg0->ext.weapon_10.timer = temp_v0 - 1;
}

void func_80093BA8(struct WeaponObj* arg0)
{
    u8 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->ext.weapon_10.timer;
    if (timer == 0) {
        func_80015D60(arg0, 8);
        arg0->unk50 = 0;
        arg0->state = 4;
    } else {
        arg0->ext.weapon_10.timer = timer - 1;
        func_8002B718(MOVING_OBJECT(arg0));
    }
}

void func_80093C08(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->on_screen = 0;
        arg0->state = 3;
    } else {
        func_80093C54(arg0);
    }
}

void func_80093C54(struct WeaponObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x30);
    }
    if (arg0->unk2 == 1) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x40);
    }
    func_8002B318(BASE_OBJECT(arg0), 0x28, 0x28);
}

struct Unk_unk68 D_801087C8[] = {
    { -8, -8, 0xE, 0xE },
};

struct Unk_unk68 D_801087CC[] = {
    { -22, -22, 0x2C, 0x2C },
};

struct Unk_unk68 D_801087D0[] = {
    { -22, -22, 0x2C, 0x2C },
};

void (*D_801087D4[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80093014,
    (void (*)(struct WeaponObj*))func_80093130,
    (void (*)(struct WeaponObj*))func_800931A8,
    (void (*)(struct WeaponObj*))func_8009347C,
    (void (*)(struct WeaponObj*))func_800934D8,
};

struct Unk_unk68 D_801087E8[] = {
    { -8, -8, 0xE, 0xE },
};

void (*D_801087EC[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_800932A0,
    func_80093310,
    (void (*)(struct WeaponObj*))func_800933EC,
    (void (*)(struct WeaponObj*))func_8009343C,
};

struct Unk_unk68 D_801087FC[] = {
    { -12, -22, 0x18, 0x2A },
};

struct Unk_unk68 D_80108800[] = {
    { 0, 0, 8, 0x16 },
};

void (*D_80108804[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80093610,
    (void (*)(struct WeaponObj*))func_8009372C,
    (void (*)(struct WeaponObj*))func_8009347C,
    (void (*)(struct WeaponObj*))func_8009347C,
    (void (*)(struct WeaponObj*))func_80093C08,
};

void (*D_80108818[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80093930,
    (void (*)(struct WeaponObj*))func_800939F4,
    (void (*)(struct WeaponObj*))func_80093A5C,
    (void (*)(struct WeaponObj*))func_8009347C,
    (void (*)(struct WeaponObj*))func_80093C08,
};

void (*D_8010882C[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_8009377C,
    (void (*)(struct WeaponObj*))func_800937EC,
    (void (*)(struct WeaponObj*))func_80093858,
    (void (*)(struct WeaponObj*))func_800938C0,
};

void (*D_8010883C[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80093AAC,
    (void (*)(struct WeaponObj*))func_80093B4C,
    (void (*)(struct WeaponObj*))func_80093BA8,
};
