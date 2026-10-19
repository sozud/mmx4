#include "test_runtime.h"
#include "main/bike.h"
#include "main/195B4.h"
#include "main/55C4.h"
void func_8003D01C(struct RideArmorObj*);

extern union AnimationStep* D_800F8FC4[38];
extern u8 D_800F9068[4];
extern s32 D_800F9070[2], D_800F9078[2], D_800F9080[2], D_800F9088[2], D_800F9090[2], D_800F9098[2];
void func_8003B3DC(struct RideArmorObj*);
void func_8003B470(struct RideArmorObj*);
void func_8003B694(struct RideArmorObj*);
void func_8003B7B4(struct RideArmorObj*);
void func_8003B98C(struct PlayerObj*);
void func_8003BA24(struct RideArmorObj*);
void func_8003BAE8(struct RideArmorObj*);
void func_8003BB20(struct RideArmorObj*);
void func_8003BDA0(struct RideArmorObj*);
void func_8003BE28(struct RideArmorObj*);
void func_8003BF1C(struct RideArmorObj*);
void func_8003C08C(struct RideArmorObj*);
void func_8003C584(struct RideArmorObj*);
void func_8003C624(struct RideArmorObj*);
void func_8003C6EC(struct RideArmorObj*, u8);
void func_8003C8F4(struct RideArmorObj*);
void func_8003C9A4(struct RideArmorObj*);
void func_8003CA44(struct RideArmorObj*);
void func_8003CB08(struct RideArmorObj*);
void func_8003CBCC(struct RideArmorObj*);
void func_8003CCBC(struct RideArmorObj*);
void func_8003CD38(struct RideArmorObj*);
u8 func_8003CF24(struct RideArmorObj*);
void func_8003CF6C(struct RideArmorObj*);
void func_8003D01C(struct RideArmorObj*);
void func_8003D164(struct VisualObj*, s32);
void func_8003D254(struct VisualObj*);
void func_8003D35C(struct MainObj*);
void func_8003D3B4(struct PlayerObj*);

#define RIDE_BYTE(object, offset) (((u8*)&(object)->unk7C)[(offset)-0x7C])

static u8 tilemap[256];
static u16 tiles[2][16][16];
static u32 attributes[2];
static u8 frames[32];
static struct RideArmorObj bike;
static struct EffectObj partner;
static u32 menu_header[4] = { 16, 20, 24, 28 };
static u32 texture_pages[4] = { 0x80, 0x100, 0x180, 0x200 };

static struct RideArmorObj* chaser(void)
{
    u32 i, x;

    c_test_zero_words((u32*)&bike, sizeof(bike) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    c_test_zero_words((u32*)tiles, sizeof(tiles) / 4);
    for (i = 0; i < COUNT(tilemap); i++)
        tilemap[i] = 1;
    for (x = 0; x < 16; x++)
        tiles[1][14][x] = tiles[1][15][x] = 1;
    attributes[0] = 0;
    attributes[1] = 0x38;
    SP_BG_TILEMAP = tilemap;
    TEST_BG_TILE_PIXELS = (u8*)tiles;
    TEST_BG_TILE_ATTRS = (u8*)attributes;
    layout_width = layout_height = 16;
    layout_size = 256;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    engine_obj.stage = 5;
    engine_obj.substage = 0;
    bike.active = 0x41;
    bike.state = 2;
    bike.unk5 = 1;
    bike.on_screen = 1;
    bike.hp = 24;
    bike.unk16 = 4;
    bike.unk40 = 123;
    bike.unk3C = frames;
    bike.unk68 = (struct Unk_unk68*)D_800F9068;
    bike.animation_table = (u32**)D_800F8FC4;
    bike.x_pos.i.hi = 100;
    bike.y_pos.i.hi = 160;
    set_animation(&bike, 0);
    return &bike;
}

static u32 departure(u32 row)
{
    struct RideArmorObj* b = chaser();
    b->unk5 = row == 0 ? 0 : 1;
    b->on_screen = row != 3;
    b->unk70 = row == 1 ? 8 : 0;
    b->y_vel.val = 0x30000;
    b->unk2C = 0x4400;
    g_Player.ride_state = 1;
    func_8003BA24(b);
    switch (row) {
    case 0:
        assert(b->unk5 == 1 && b->x_vel.val == FIXED(10) && b->unk2C == 0x4400);
        assert(g_Player.ride_state == 0 && g_Player.script_action == 0x17);
        break;
    case 1:
        assert(b->unk2C == 0 && b->y_vel.val == 0);
        break;
    case 2:
        assert(b->y_vel.val == 0x30000 - 0x4400 && b->y_pos.i.hi == 157);
        break;
    default:
        assert(b->state == 3 && b->unk5 == 0);
    }
    return 1;
}

static u32 invincibility(u32 row)
{
    static struct PlayerObj owner;
    struct PlayerObj* p = &owner;
    c_test_zero_words((u32*)p, sizeof(*p) / 4);
    c_test_copy_words((u32*)p, (u32*)chaser(), sizeof(struct RideArmorObj) / 4);
    p->charge_state[0] = row != 0;
    p->shot_cycle = row != 1;
    p->invincibility_timer = row == 2 ? 0 : row == 3 ? 3
                                                     : 2;
    p->dash_timer = 5;
    func_8003B98C(p);
    if (row < 2)
        assert(p->dash_timer == 5 && visual_objects[0].active == 0);
    else if (row == 2)
        assert(p->shot_cycle == 0 && p->dash_timer == 0 && visual_objects[0].id == 0xF);
    else
        assert(p->invincibility_timer == (row == 3 ? 2 : 1) && visual_objects[0].active == 0);
    return p->unk42 >> 15;
}

static u32 shot(u32 row)
{
    struct RideArmorObj* b = chaser();
    u32 i;
    b->unk8C.value = row == 0 ? 0 : 0x10;
    RIDE_BYTE(b, 0x89) = row == 1;
    RIDE_BYTE(b, 0x98) = row == 2 ? 3 : 2;
    for (i = 0; row == 4 && i < 16; i++)
        weapon_objects[i].active = 1;
    for (i = 0; row == 4 && i < 32; i++)
        visual_objects[i].active = 1;
    func_8003C6EC(b, 3);
    if (row < 3) {
        assert(RIDE_BYTE(b, 0x98) == (row == 2 ? 3 : 2) && weapon_objects[0].active == 0);
        return 0;
    }
    assert(RIDE_BYTE(b, 0x89) == 4 && RIDE_BYTE(b, 0x98) == 3);
    if (row == 3)
        assert(weapon_objects[0].id == 0x38 && weapon_objects[0].unk2 == 3 && visual_objects[0].id == 0xC);
    return weapon_objects[0].unk42;
}

static u32 steer(u32 row)
{
    static const struct {
        u16 held;
        s32 speed;
    } cases[] = {
        { 0, 0x10000 },
        { 1, 0x10000 },
        { 1, 0x30000 },
        { 2, -0x10000 },
        { 2, -0x30000 },
    };
    struct RideArmorObj* b = chaser();
    b->unk8A = cases[row].held;
    b->x_vel.val = cases[row].speed;
    b->unk28 = 0x777;
    b->unk7C = 5;
    b->unk80.bytes.unk80 = 3;
    func_8003CB08(b);
    assert(b->unk80.bytes.unk80 == 2);
    return b->x_vel.val ^ b->unk28 ^ b->unk7C << 24;
}

static u32 accelerate(u32 row)
{
    static const struct {
        u16 held;
        u8 charged;
        s32 speed;
    } cases[] = {
        { 0, 0, 0x10000 },
        { 0, 1, 0x10000 },
        { 1, 0, 0 },
        { 1, 0, 0x30000 },
        { 1, 0, 0x10000 },
        { 2, 0, 0 },
        { 2, 0, -0x30000 },
        { 2, 0, -0x10000 },
    };
    struct RideArmorObj* b = chaser();
    b->unk8A = cases[row].held;
    b->unk7D = cases[row].charged;
    b->x_vel.val = cases[row].speed;
    b->unk28 = 0x777;
    b->unk7C = 5;
    func_8003CBCC(b);
    return b->x_vel.val ^ b->unk28 ^ b->unk7C << 24;
}

static u32 charge_and_jump(u32 row)
{
    struct RideArmorObj* b = chaser();
    b->unk7D = row == 0 || row == 5;
    b->unk7E = row == 1;
    b->unk8C.value = row == 2 ? 0x100 : row >= 4 ? 0x80
                                                 : 0;
    if (row < 4) {
        func_8003CCBC(b);
        assert(b->unk5 == (row == 1 || row == 2 ? 5 : 1));
        return b->unk7D | b->unk80.bytes.unk80 << 8;
    }
    func_8003C8F4(b);
    assert(b->y_vel.val == FIXED(6.5) && (b->unk80.bytes.unk80 & 2));
    assert(b->unk5 == (row == 4 ? 2 : 1) && b->unk8E.value == (row == 5));
    return 1;
}

static u32 slope(u32 row)
{
    static const u8 shapes[3] = { 3, 6, 0x20 };
    u32 shape = row / 4, uphill = row / 2 % 2, fast = row % 2;
    struct RideArmorObj* b = chaser();
    s32 limits[3][2] = {
        { D_800F9070[0], D_800F9078[0] },
        { D_800F9088[0], D_800F9080[0] },
        { D_800F9090[0], D_800F9098[0] },
    };
    s32 limit = limits[shape][uphill];
    b->unk80.bytes.unk81 = shapes[shape];
    b->unk7C = uphill;
    b->x_vel.val = fast ? limit + 0x8000 : limit - 0x8000;
    b->unk28 = 0x100;
    b->unk2C = 0x200;
    func_8003CD38(b);
    return b->x_vel.val ^ b->y_vel.val ^ b->x_pos.val;
}

static u32 slope_shape(u32 row)
{
    static const u8 shapes[] = { 0, 3, 6, 0x10, 0x10, 0x20 };
    struct RideArmorObj* b = chaser();
    b->unk80.bytes.unk81 = shapes[row];
    b->unk80.bytes.unk83 = row == 4;
    return func_8003CF24(b);
}

static u32 slope_animation(u32 row)
{
    struct RideArmorObj* b = chaser();
    b->unk80.bytes.unk82 = row < 4 ? row : 0;
    b->unk80.bytes.unk83 = row == 4 ? 0 : 7;
    b->unk80.bytes.unk80 = row == 5 ? 2 : 0;
    func_8003CA44(b);
    return g_Player.ride_animation | b->animation_step.packed << 8;
}

static u32 ramp_launch(u32 row)
{
    struct RideArmorObj* b = chaser();
    b->unk80.bytes.unk82 = row == 0 ? 1 : 2;
    b->unk80.bytes.unk83 = row == 1;
    b->unk80.bytes.unk80 = row != 2;
    b->x_vel.val = row == 4 ? 0x2F400 : -0x2F400;
    func_8003C9A4(b);
    if (row < 3)
        assert(b->unk6 == 0 && b->y_vel.val == 0);
    else
        assert(b->unk6 == 2 && b->unk2C == FIXED(0.3125) && b->y_vel.val == (0x2F400 * 2 / 237) << 8);
    return 1;
}

static u32 ground_drive(u32 row)
{
    struct RideArmorObj* b = chaser();
    b->unk70 = row == 0 ? 0 : 8;
    b->unk7D = row == 2;
    b->unk8A = 1;
    b->unk80.bytes.unk81 = 0x20;
    func_8003BDA0(b);
    if (row == 0)
        assert(b->unk5 == 4 && b->unk6 == 0);
    else
        assert(b->unk5 == 1 && b->unk7C == (row == 1));
    return b->x_vel.val;
}

static u32 jump_rise(u32 row)
{
    struct RideArmorObj* b = chaser();
    b->unk6 = row != 0;
    b->unk70 = row == 3 ? 5 : 0;
    b->unk8A = row == 2 ? 0 : 0x80;
    b->unk7D = row == 4;
    b->y_vel.val = row == 1 ? 0x100 : 0x40000;
    b->unk2C = 0x1000;
    b->x_vel.val = 0x10000;
    func_8003BE28(b);
    assert(b->unk67 == 1);
    if (row == 0)
        assert(b->unk2C == FIXED(0.3125) && b->unk5 == 1);
    else if (row == 1)
        assert(b->unk5 == 4 && b->y_vel.val < 0);
    else if (row == 2 || row == 3)
        assert(b->unk5 == 4 && b->y_vel.val == 0 && (row == 2 || b->x_vel.val == 0));
    else
        assert(b->unk8E.value == 1);
    return 1;
}

static u32 fall(u32 row)
{
    struct RideArmorObj* b = chaser();
    b->unk6 = row != 0;
    b->unk70 = row >= 2 && row <= 6 ? 8 : 0;
    b->unk7D = row == 6;
    b->unk80.bytes.unk82 = row - 2;
    b->unk80.bytes.unk80 = 2;
    b->y_vel.val = row == 1 ? 0x70000 : 0x10000;
    b->unk2C = 0x1000;
    func_8003BF1C(b);
    if (row == 0)
        assert(b->unk2C == 0x5000);
    else if (row == 1)
        assert(b->y_vel.val == 0x68000);
    else if (row == 6)
        assert(b->unk5 == 5 && b->unk6 == 1 && RIDE_BYTE(b, 0x99) == 0);
    else
        assert(b->unk5 == 1 && b->unk67 == 0 && !(b->unk80.bytes.unk80 & 2));
    return g_Player.ride_animation;
}

static u32 charge(u32 row)
{
    static const struct {
        u8 step, tapped, landed, jump, held, foot, still;
    } cases[] = {
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0 },
        { 1, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 8, 0x80, 0, 0, 0 },
        { 1, 0, 8, 0, 0, 0, 0 },
        { 1, 0, 0, 0, 0, 0, 0 },
        { 2, 0, 0, 0, 0, 0, 0 },
        { 3, 0, 8, 0, 0, 0, 0 },
        { 3, 0, 0, 0, 0, 0, 0 },
        { 4, 0, 0, 0, 0, 0, 0 },
        { 5, 0, 0, 0, 0, 0, 0 },
        { 6, 0, 8, 0, 0, 0, 0 },
        { 6, 0, 0, 0, 0, 0x38, 0 },
        { 6, 0, 0, 0, 0, 0x10, 0 },
        { 6, 0, 0, 0, 4, 0x20, 0 },
        { 6, 0, 0, 0, 8, 0x20, 0 },
        { 6, 0, 0, 0, 0, 0x20, 0 },
        { 6, 0, 0, 0, 0, 0x20, 1 },
        { 9, 0, 0, 0, 0, 0, 0 },
        { 4, 0, 0, 0, 0, 0, 0 },
        { 6, 0, 0, 0, 0, 0, 0 },
    };
    struct RideArmorObj* b = chaser();
    b->unk6 = cases[row].step;
    b->unk8E.value = cases[row].tapped;
    b->unk70 = cases[row].landed;
    b->unk8C.value = cases[row].jump;
    b->unk8A = cases[row].held;
    b->unk80.bytes.unk81 = cases[row].foot;
    b->x_vel.val = cases[row].still ? 0 : 0x10000;
    if (cases[row].step == 4) {
        b->animation_step.fields.duration = 2;
        b->animation_step.fields.relative_step = row != 9;
    }
    b->spawned_parts = 1;
    background_objects[0].unk47 = 9;
    func_8003C08C(b);
    switch (row) {
    case 0:
    case 1:
        assert(b->unk6 == (row ? 6 : 1) && background_objects[0].unk47 == 8 && weapon_objects[0].id == 0x39);
        break;
    case 2:
    case 7:
        assert(b->unk6 == 4 && b->spawned_parts == 0);
        break;
    case 3:
        assert(b->unk6 == 2 && b->unk2C == 0x5000);
        break;
    case 5:
    case 17:
        assert(b->unk6 == 3 && b->unk2C == 0x5000);
        break;
    case 9:
        assert(b->unk6 == 5);
        break;
    case 10:
        assert(b->unk5 == 1 && b->unk6 == 0 && background_objects[0].unk47 == 6);
        break;
    }
    return RIDE_BYTE(b, 0x99) | (u32)(u16)(b->y_pos.val >> 8) << 8;
}

static u32 charge_ramp(u32 row)
{
    struct RideArmorObj* b = chaser();
    b->unk70 = row == 0 ? 4 : row == 1 ? 5
                                       : 0;
    b->unk6 = row == 3 ? 2 : 0;
    b->y_vel.val = row == 2 ? -0x100 : 0x100;
    b->x_vel.val = 0x10000;
    b->unk90.value = 0x20000;
    background_objects[0].unk47 = row == 3 ? 6 : 20;
    func_8003C584(b);
    if (row < 2)
        assert(b->unk6 == 3 && b->y_vel.val == 0 && b->x_vel.val == (row ? 0 : 0x10000));
    else if (row == 2)
        assert(b->unk6 == 3);
    else
        assert(background_objects[0].unk47 == 6);
    return 1;
}

static u32 startup(u32 row)
{
    static const struct {
        u8 step;
        s32 speed;
        s16 x;
        u8 partner_active, partner_step;
    } cases[] = {
        { 0, 0, 0x80, 1, 0 },
        { 1, 0x90000, 0x80, 1, 0 },
        { 1, 0x10000, 0xC0, 1, 0 },
        { 2, 0x10000, 0x80, 1, 0 },
        { 3, 0, 0x80, 1, 0 },
        { 4, 0, 0x80, 0, 0 },
        { 4, 0, 0x80, 1, 3 },
        { 4, 0, 0x80, 1, 0 },
        { 9, 0, 0x80, 1, 0 },
        { 0, 0, 0x80, 1, 0 },
        { 1, -0x90000, 0x80, 1, 0 },
        { 2, 0x10000, 0xC0, 1, 0 },
        { 3, 0, 0x80, 1, 0 },
    };
    struct RideArmorObj* b = chaser();
    u32 i;
    for (i = 0; row == 9 && i < 16; i++)
        weapon_objects[i].active = 1;
    b->unk6 = cases[row].step;
    b->x_vel.val = cases[row].speed;
    b->x_pos.i.hi = cases[row].x;
    if (row == 12) {
        b->animation_step.fields.duration = 2;
        b->animation_step.fields.relative_step = 1;
    }
    partner.active = cases[row].partner_active;
    partner.unk5 = cases[row].partner_step;
    b->unkA0.chaser_effect = &partner;
    func_8003BB20(b);
    switch (row) {
    case 0:
        assert(b->unk6 == 1 && b->unk15 == 0x40 && weapon_objects[0].id == 0x39);
        break;
    case 1:
    case 10:
        assert(b->unk6 == 1 && b->x_vel.val == 0x80000);
        break;
    case 2:
        assert(b->unk6 == 2 && b->unk28 == -0x4000);
        break;
    case 3:
        assert(b->unk6 == 3);
        break;
    case 4:
        assert(b->unk6 == 4);
        break;
    case 5:
    case 6:
        assert(b->unk5 == 1 && b->unk6 == 0);
        break;
    case 7:
        assert(b->unk6 == 4);
        break;
    case 12:
        assert(b->unk6 == 3);
        break;
    }
    return 1;
}

static u32 viewport(u32 row)
{
    static const s16 x[] = { 120, 12, 0, 270, 20 };
    struct RideArmorObj* b = chaser();
    b->x_pos.i.hi = x[row % 5];
    b->unk15 = row == 5 ? 0x40 : 0;
    b->unk70 = row == 2 || row == 4;
    g_Player.hp = 9;
    func_8003D01C(b);
    if (row == 2)
        assert(b->hp == -0x80 && g_Player.hp == -0x80);
    else
        assert(b->hp == 24 && g_Player.hp == 9);
    return b->x_pos.i.hi;
}

static u32 spawn_visual(u32 row)
{
    struct RideArmorObj* b = chaser();
    u32 i;
    for (i = 0; row >= 2 && i < 32; i++)
        visual_objects[i].active = 1;
    if (row == 0 || row == 3)
        func_8003D164((struct VisualObj*)b, 3);
    else
        func_8003D254((struct VisualObj*)b);
    if (row < 2)
        assert(visual_objects[0].id == (row ? 0xF : 0xD) && visual_objects[0].unk50 == (void*)b);
    return 1;
}

static u32 rider_follow(u32 row)
{
    struct PlayerObj owner;
    c_test_zero_words((u32*)&owner, sizeof(owner) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    owner.charge_state[0] = row != 1;
    owner.x_pos.val = 0x123456;
    g_Player.ride_state = row != 0;
    g_Player.x_pos.val = 0x654321;
    func_8003D3B4(&owner);
    assert(g_Player.x_pos.val == (row == 2 ? 0x123456 : 0x654321));
    return 1;
}

static u32 rider_gravity(u32 row)
{
    struct MainObj obj;
    c_test_zero_words((u32*)&obj, sizeof(obj) / 4);
    obj.y_speed = row ? -0x60000 : 0x20000;
    obj.gravity = 0x10000;
    func_8003D35C(&obj);
    assert(obj.y_speed == (row ? -FIXED(6.5) : 0x10000));
    return 1;
}

static u32 terrain(u32 row)
{
    struct RideArmorObj* b = chaser();
    attributes[1] = row < 2 ? 0x24 : 0x38;
    b->x_pos.i.hi = 256;
    b->y_pos.i.hi = 213;
    b->saved_x_vel = row == 1 ? 2 : 0;
    b->unk15 = row == 3 ? 0x40 : 0;
    if (row < 3) {
        func_8003B694(b);
        assert(b->saved_x_vel == (row == 0 ? 2 : row == 1 ? 1
                                                          : 0)
            && b->x_pos.i.hi == 256);
        return 1;
    }
    func_8003CF6C(b);
    return b->unk80.bytes.unk81;
}

static u32 initialize(u32 row)
{
    struct RideArmorObj* b = chaser();
    u32 i;
    D_801406A8 = texture_pages;
    TEST_MENU_FRAMES = (u8*)menu_header;
    g_Player.unk2 = row == 1;
    g_Player.hp = 17;
    g_Player.x_pos.i.hi = 64;
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    for (i = 0; row == 2 && i < 32; i++)
        effect_objects[i].active = 1;
    func_8003B470(b);
    assert(b->state == 1 && b->hp == 17 && b->x_pos.i.hi == 64 && g_Player.ride_state == 1);
    assert(b->unkA0.chaser_effect == (row == 2 ? NULL : &effect_objects[0]));
    return b->unk42;
}

static u32 update(u32 row)
{
    struct RideArmorObj* b = chaser();
    b->state = 1;
    b->unk5 = row == 6 ? 0 : 1;
    b->hp = row == 0 ? 0 : row == 2 ? (s8)0x8C
        : row == 7                  ? -0x80
                                    : 24;
    g_Player.hp = row == 1 ? 0 : 16;
    background_objects[0].unk51 = row == 3;
    background_objects[0].unk4 = row == 4 || row == 8;
    RIDE_BYTE(b, 0x9B) = row != 8;
    RIDE_BYTE(b, 0x89) = row == 9 ? 0 : 2;
    background_objects[0].x_pos.i.hi = 4;
    b->unk70 = 8;
    func_8003B3DC(b);
    switch (row) {
    case 0:
    case 1:
        assert(b->state == 3 && b->hp == 0 && g_Player.hp == -0x80);
        break;
    case 2:
        assert(RIDE_BYTE(b, 0x9A) == 1);
        assert(g_Player.hp == 12);
        break;
    case 3:
        assert(b->state == 2 && RIDE_BYTE(b, 0x9B) == 0);
        break;
    case 4:
        assert(b->x_pos.i.hi == 104);
        break;
    case 5:
        assert(RIDE_BYTE(b, 0x89) == 1);
        break;
    case 6:
        assert(RIDE_BYTE(b, 0x89) == 2);
        break;
    }
    return 1;
}

static u32 despawn(u32 row)
{
    static u32 silence;
#ifdef MMX4_PC
    u8** sounds = &D_80141F50[5];
#else
    extern u8 D_80141F58[16];
    u8** sounds = (u8**)(D_80141F58 + 12);
#endif
    u8* saved = *sounds;
    struct RideArmorObj* b = chaser();
    *sounds = (u8*)&silence;
    func_8003BAE8(b);
    *sounds = saved;
    assert(b->active == 0 && b->state == 0);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "departure", NULL, NULL, 4, departure },
    { "invincibility", NULL, NULL, 5, invincibility },
    { "shot", NULL, NULL, 5, shot },
    { "steer", NULL, NULL, 5, steer },
    { "accelerate", NULL, NULL, 8, accelerate },
    { "charge_and_jump", NULL, NULL, 6, charge_and_jump },
    { "slope", NULL, NULL, 12, slope },
    { "slope_shape", NULL, NULL, 6, slope_shape },
    { "slope_animation", NULL, NULL, 6, slope_animation },
    { "ramp_launch", NULL, NULL, 5, ramp_launch },
    { "ground_drive", NULL, NULL, 3, ground_drive },
    { "jump_rise", NULL, NULL, 5, jump_rise },
    { "fall", NULL, NULL, 7, fall },
    { "charge", NULL, NULL, 21, charge },
    { "charge_ramp", NULL, NULL, 4, charge_ramp },
    { "startup", NULL, NULL, 13, startup },
    { "viewport", NULL, NULL, 6, viewport },
    { "spawn_visual", NULL, NULL, 4, spawn_visual },
    { "rider_follow", NULL, NULL, 3, rider_follow },
    { "rider_gravity", NULL, NULL, 2, rider_gravity },
    { "terrain", NULL, NULL, 5, terrain },
    { "initialize", NULL, NULL, 3, initialize },
    { "update", NULL, NULL, 10, update },
    { "despawn", NULL, NULL, 1, despawn },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 4 + 5 + 5 + 5 + 8 + 6 + 12 + 6 + 6 + 5 + 3 + 5 + 7 + 21 + 4 + 13 + 6 + 4 + 3 + 2 + 5 + 3 + 10 + 1;
