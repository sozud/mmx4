#include "test_runtime.h"
#include "main/1CF60.h"
#include "main/mains/main_19_surface_hopper.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "support/state_cases.h"
void surface_hopper_appear(struct MainObj* arg0);
u8 func_80053B54(struct MainObj*);
extern union AnimationStep* surface_hopper_animations[27];
extern u8 D_800FC80C[8];
u16 func_800537E0(struct MainObj*, u8, u8);
u8 surface_hopper_aim_at_player(struct MainObj*);

static struct AimInput {
    s16 object_x, object_y, player_x, player_y;
    u8 animation;
};
static const struct AimInput hopper_aim_edges_inputs[] = {
    { -16384, 100, 16384, 200, 1 },
    { 100, -16384, 100, 16384, 0 },
    { 100, 32767, 100, -32768, 0 },
    { 100, 100, 100, 100, 1 },
    { -16384, 100, 16384, 100, 2 },
    { 32767, 100, -32768, 100, 2 },
};
static u32 aim_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    u32 i, result;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 19;
    obj.state = 1;
    obj.x_pos.val = (s32)hopper_aim_edges_inputs[mode].object_x * 65536;
    obj.y_pos.val = (s32)hopper_aim_edges_inputs[mode].object_y * 65536;
    obj.ext.main_19.animation_index = hopper_aim_edges_inputs[mode].animation;
    obj.ext.main_19.unk83 = 0x27;
    g_Player.x_pos.val = (s32)hopper_aim_edges_inputs[mode].player_x * 65536;
    g_Player.y_pos.val = (s32)hopper_aim_edges_inputs[mode].player_y * 65536;
    before = obj;
    player_before = g_Player;
    SP_CUR_MAIN_OBJ = &obj;
    result = func_80053B54(&obj);
    before.ext.main_19.unk83 = obj.ext.main_19.unk83;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return observation == 0 ? result : obj.ext.main_19.unk83;
}
static const u32 hopper_aim_edges_cases_expected[] = { 0x1u, 0x1Cu, 0x0u, 0x27u, 0x1u, 0x18u, 0x0u, 0x27u, 0x0u, 0x27u, 0x0u, 0x27u };
static u32 hopper_aim_edges_cases_row(u32 row)
{
    return aim_case(row / 2, row % 2);
}

static u32 launch_case(u32 observation)
{
    struct MainObj obj, before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 19;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 0;
    obj.unk7C = 0x2468;
    obj.unk15 = 0x35;
    obj.unk17 = 0x12;
    obj.previous_animation_index = 0xA5;
    obj.animation_table = (u32**)surface_hopper_animations;
    obj.ext.main_19.animation_index = 0;
    obj.ext.main_19.unk80 = 0;
    before = obj;
    SP_CUR_MAIN_OBJ = &obj;
    surface_hopper_launch(&obj);
    before.x_speed = obj.x_speed;
    before.y_speed = obj.y_speed;
    before.unk15 = obj.unk15;
    before.unk17 = obj.unk17;
    before.previous_animation_index = obj.previous_animation_index;
    before.animation_cursor = obj.animation_cursor;
    before.animation_step = obj.animation_step;
    before.hurt_box = obj.hurt_box;
    before.attack_box = obj.attack_box;
    before.terrain_box = obj.terrain_box;
    before.unk6 = obj.unk6;
    before.unk7C = obj.unk7C;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(obj.hurt_box == surface_hopper_launch_hurt_boxes[0]);
    assert(obj.attack_box == surface_hopper_launch_attack_boxes[0]);
    assert(obj.terrain_box == surface_hopper_launch_terrain_boxes[0]);
    assert(obj.animation_table == (u32**)surface_hopper_animations);
    assert(obj.animation_cursor == (u32*)surface_hopper_animations[obj.unk17]);
    switch (observation) {
    case 0:
        actual = obj.x_speed;
        break;
    case 1:
        actual = obj.y_speed;
        break;
    case 2:
        actual = obj.animation_step.packed;
        break;
    case 3:
        actual = (u8)obj.unk6 | ((u32)(u16)obj.unk7C << 8);
        break;
    case 4:
        actual = obj.unk15 | ((u32)obj.unk17 << 8) | ((u32)obj.previous_animation_index << 16);
        break;
    default:
        actual = ((u32*)&obj)[1];
        break;
    }
    return actual;
}
static const u32 hopper_launch_binding_cases_expected[] = { 0xFFFE0000u, 0x0u, 0x45010003u, 0x1E01u, 0xFF1A00u, 0x10101u };

static struct CrawlInput {
    u8 started, solid, index, orientation, flags;
};
enum { INIT,
    EDGE_UP,
    EDGE_DOWN,
    MASK_1,
    MASK_2,
    MASK_4,
    MASK_4_REVERSE,
    MASK_8,
    NO_CONTACT,
    MASK_2_REVERSE,
    MASK_8_REVERSE };
static const struct CrawlInput surface_hopper_crawl_inputs[] = {
    { 0, 1, 0, 0, 0 },
    { 1, 0, 0, 1, 0 },
    { 1, 0, 1, 0, 0 },
    { 1, 1, 0, 2, 1 },
    { 1, 1, 0, 0, 2 },
    { 1, 1, 0, 3, 4 },
    { 1, 1, 1, 1, 4 },
    { 1, 1, 0, 1, 8 },
    { 1, 1, 0, 0, 0 },
    { 1, 1, 1, 2, 2 },
    { 1, 1, 1, 3, 8 },
};
static u8 surface_hopper_crawl_tilemap[256];
static u16 surface_hopper_crawl_tiles[2][16][16];
static u32 surface_hopper_crawl_attributes[1];
static u32 surface_hopper_crawl_steps[2];
static u32* surface_hopper_crawl_table[0x20];
static struct Unk_unk68 surface_hopper_crawl_box = { 3, 4, 5, 6 };
static struct MainObj surface_hopper_crawl_hopper, surface_hopper_crawl_expected, surface_hopper_crawl_owner;

static void launch(u8 animation_index, u8 orientation)
{
    u32 index = animation_index * 4 + orientation;
    surface_hopper_crawl_expected.x_speed = surface_hopper_launch_x_speeds[index] * FIXED(1);
    surface_hopper_crawl_expected.y_speed = surface_hopper_launch_y_speeds[index] * FIXED(1);
    surface_hopper_crawl_expected.unk15 = surface_hopper_launch_facings[index];
    surface_hopper_crawl_expected.animation_cursor = surface_hopper_crawl_table[surface_hopper_launch_animations[index]];
    surface_hopper_crawl_expected.unk17 = surface_hopper_launch_animations[index];
    surface_hopper_crawl_expected.previous_animation_index = 0xFF;
    surface_hopper_crawl_expected.animation_step.packed = surface_hopper_crawl_steps[1];
    surface_hopper_crawl_expected.hurt_box = surface_hopper_launch_hurt_boxes[orientation];
    surface_hopper_crawl_expected.attack_box = surface_hopper_launch_attack_boxes[orientation];
    surface_hopper_crawl_expected.terrain_box = surface_hopper_launch_terrain_boxes[orientation];
}

static u32 surface_hopper_crawl_run(u32 mode, u32 observation)
{
    const struct CrawlInput* input = &surface_hopper_crawl_inputs[mode];
    u16 x = 0x68, y = 0x50;
    u8 mask, orientation = input->orientation;
    union AnimationStep value;
    u32 i, difference = 0, actual;
    struct Main19Ext want;
    memset(surface_hopper_crawl_tilemap, 1, sizeof(surface_hopper_crawl_tilemap));
    memset(surface_hopper_crawl_tiles, 0, sizeof(surface_hopper_crawl_tiles));
    surface_hopper_crawl_attributes[0] = input->solid ? 0x39 : 0;
    SP_BG_TILEMAP = surface_hopper_crawl_tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)surface_hopper_crawl_tiles;
    TEST_BG_TILE_ATTRS = (u8*)surface_hopper_crawl_attributes;
    value.fields.duration = 3;
    value.fields.event = 0;
    value.fields.relative_step = 1;
    value.fields.frame_index = 2;
    surface_hopper_crawl_steps[0] = value.packed;
    value.fields.duration = 8;
    surface_hopper_crawl_steps[1] = value.packed;
    for (i = 0; i < COUNT(surface_hopper_crawl_table); i++)
        surface_hopper_crawl_table[i] = &surface_hopper_crawl_steps[1];
    memset(&surface_hopper_crawl_owner, 0, sizeof(surface_hopper_crawl_owner));
    surface_hopper_crawl_owner.ext.main_19.unk80 = input->orientation;
    surface_hopper_crawl_owner.ext.main_19.animation_index = input->index;
    surface_hopper_crawl_owner.ext.main_19.unk83 = 1;
    surface_hopper_crawl_owner.ext.main_19.unk86 = 0x60;
    surface_hopper_crawl_owner.ext.main_19.unk88 = 0x48;
    SP_CUR_MAIN_OBJ = &surface_hopper_crawl_owner;
    memset(&surface_hopper_crawl_hopper, 0, sizeof(surface_hopper_crawl_hopper));
    surface_hopper_crawl_hopper.active = 0x41;
    surface_hopper_crawl_hopper.id = 0x13;
    surface_hopper_crawl_hopper.state = 1;
    surface_hopper_crawl_hopper.unk6 = input->started;
    surface_hopper_crawl_hopper.x_pos.u.hi = x;
    surface_hopper_crawl_hopper.y_pos.u.hi = y;
    surface_hopper_crawl_hopper.unk18 = surface_hopper_crawl_hopper.x_pos;
    surface_hopper_crawl_hopper.unk1C = surface_hopper_crawl_hopper.y_pos;
    surface_hopper_crawl_hopper.collision_flags = input->flags;
    surface_hopper_crawl_hopper.terrain_box = &surface_hopper_crawl_box;
    surface_hopper_crawl_hopper.animation_table = surface_hopper_crawl_table;
    surface_hopper_crawl_hopper.animation_cursor = &surface_hopper_crawl_steps[0];
    surface_hopper_crawl_hopper.animation_step.packed = surface_hopper_crawl_steps[0];
    surface_hopper_crawl_expected = surface_hopper_crawl_hopper;
    want = surface_hopper_crawl_owner.ext.main_19;
    func_8005402C(&surface_hopper_crawl_hopper);

    if (!input->started) {
        launch(input->index, input->orientation);
        surface_hopper_crawl_expected.unk6 = 1;
    } else {
        mask = D_800FC80C[input->index * 4 + input->orientation];
        want.unk82 = surface_hopper_crawl_attributes[0];
        if (!input->solid) {
            x = want.unk86;
            y = want.unk88;
            want.unk83 ^= 1;
            want.unk80 = (want.unk80 + (input->index == 0 ? 1 : -1)) & 3;
            launch(input->index, want.unk80);
        } else if (input->flags & mask) {
            if (mask == 1) {
                x += surface_hopper_crawl_box.unk0 + surface_hopper_crawl_box.unk2;
                y += surface_hopper_crawl_box.unk1;
                want.unk80 = 1;
            }
            if (mask == 2) {
                x -= surface_hopper_crawl_box.unk0 + surface_hopper_crawl_box.unk2;
                y += surface_hopper_crawl_box.unk1;
                want.unk80 = 3;
            }
            if (mask == 4 || mask == 8) {
                x += orientation == 1 ? -surface_hopper_crawl_box.unk0 : surface_hopper_crawl_box.unk0;
                y += mask == 4 ? -(surface_hopper_crawl_box.unk1 + surface_hopper_crawl_box.unk3) : surface_hopper_crawl_box.unk1 + surface_hopper_crawl_box.unk3;
                want.unk80 = mask == 4 ? 2 : 0;
            }
            launch(input->index, want.unk80);
        } else {
            surface_hopper_crawl_expected.animation_step.fields.duration--;
        }
        want.unk86 = x;
        want.unk88 = y;
        if (surface_hopper_crawl_expected.y_speed < FIXED(-6.5))
            surface_hopper_crawl_expected.y_speed = FIXED(-6.5);
        surface_hopper_crawl_expected.x_pos = surface_hopper_crawl_hopper.x_pos;
        surface_hopper_crawl_expected.y_pos = surface_hopper_crawl_hopper.y_pos;
        surface_hopper_crawl_expected.collision_flags = surface_hopper_crawl_hopper.collision_flags;
        surface_hopper_crawl_expected.unk6C = surface_hopper_crawl_hopper.unk6C;
        surface_hopper_crawl_expected.unk6E = surface_hopper_crawl_hopper.unk6E;
        ((u8*)&surface_hopper_crawl_expected)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)] = ((u8*)&surface_hopper_crawl_hopper)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)];
        ((u8*)&surface_hopper_crawl_expected)[MMX4_OFFSET_OF(struct PlayerObj, wall_climbable)] = ((u8*)&surface_hopper_crawl_hopper)[MMX4_OFFSET_OF(struct PlayerObj, wall_climbable)];
    }
    for (i = 0; i < sizeof(surface_hopper_crawl_hopper) / 4; i++)
        difference |= ((u32*)&surface_hopper_crawl_hopper)[i] ^ ((u32*)&surface_hopper_crawl_expected)[i];
    assert(difference == 0);
    assert(surface_hopper_crawl_owner.ext.main_19.unk80 == want.unk80 && surface_hopper_crawl_owner.ext.main_19.unk83 == want.unk83);
    assert(!input->started || (surface_hopper_crawl_owner.ext.main_19.unk82 == want.unk82 && surface_hopper_crawl_owner.ext.main_19.unk86 == want.unk86 && surface_hopper_crawl_owner.ext.main_19.unk88 == want.unk88));
    if (observation == 0)
        actual = surface_hopper_crawl_owner.ext.main_19.unk80 | ((u32)surface_hopper_crawl_owner.ext.main_19.unk82 << 8) | ((u32)surface_hopper_crawl_owner.ext.main_19.unk86 << 16);
    else
        actual = (u16)surface_hopper_crawl_hopper.x_pos.u.hi | ((u32)surface_hopper_crawl_hopper.y_pos.u.hi << 16) ^ surface_hopper_crawl_hopper.collision_flags;
    return actual;
}

static const u32 surface_hopper_crawl_cases_expected[] = { 0x600000u, 0x500068u, 0x600002u, 0x480062u, 0x600003u, 0x4A0060u, 0x703901u, 0x50006Fu, 0x603903u, 0x50007Fu, 0x6B3902u, 0x50006Fu, 0x653902u, 0x50007Fu, 0x653900u, 0x50007Fu, 0x683900u, 0x50006Fu, 0x603903u, 0x50007Fu, 0x6B3900u, 0x50006Fu };
static u32 surface_hopper_crawl_cases_row(u32 row)
{
    return surface_hopper_crawl_run(row / 2, row % 2);
}

enum { KILL_DOWN,
    KILL_LEFT,
    KILL_UP,
    KILL_RIGHT,
    SURVIVE,
    VISIBLE,
    FAR_AWAY,
    TIMEOUT };
static u32 surface_hopper_launched_steps[2];
static u32* surface_hopper_launched_table[0x20];
static u8 damage[0x100];
static struct Unk_unk68 weapon_box = { -60, -60, 0x7F, 0x7F };
static struct MainObj surface_hopper_launched_hopper, surface_hopper_launched_expected, surface_hopper_launched_owner;
static struct VisualObj want_visuals[0x20];
static struct MiscObj want_miscs[0x40];
static struct WeaponObj weapon;
static s8 banks[6];

static void zero(void* target, u32 size)
{
    u32 i;
    for (i = 0; i < size / 4; i++)
        ((u32*)target)[i] = 0;
}

static void same(const void* a, const void* b, u32 size)
{
    u32 i, difference = 0;
    for (i = 0; i < size / 4; i++)
        difference |= ((const u32*)a)[i] ^ ((const u32*)b)[i];
    assert(difference == 0);
}

static u32 surface_hopper_launched_run(u32 mode, u32 observation)
{
    u32 i, actual, hit = mode <= SURVIVE;
    union AnimationStep value;
    u16 x, y;
    for (i = 0; i < 6; i++)
        banks[i] = D_8013E198[i];
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    zero(visual_objects, sizeof(visual_objects));
    zero(misc_objects, sizeof(misc_objects));
    zero(weapon_objects, sizeof(weapon_objects));
    for (i = 0; i < 0x20; i++)
        visual_objects[i].active = 1;
    for (i = 0; i < 0x40; i++)
        misc_objects[i].active = 1;
    zero(want_visuals, sizeof(want_visuals));
    zero(want_miscs, sizeof(want_miscs));
    for (i = 0; i < 0x20; i++)
        want_visuals[i].active = 1;
    for (i = 0; i < 0x40; i++)
        want_miscs[i].active = 1;
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.spike_immune = 1;
    engine_obj.stage = 5;
    background_objects[0].x_pos.val = 0;
    background_objects[0].y_pos.val = 0;
    cur_random = 0x1357;
    memset(damage, 0, sizeof(damage));
    damage[1 * 2 + 1] = 10;
    value.fields.duration = 3;
    value.fields.event = 0;
    value.fields.relative_step = 1;
    value.fields.frame_index = 2;
    surface_hopper_launched_steps[0] = value.packed;
    value.fields.duration = 8;
    surface_hopper_launched_steps[1] = value.packed;
    for (i = 0; i < COUNT(surface_hopper_launched_table); i++)
        surface_hopper_launched_table[i] = &surface_hopper_launched_steps[1];
    memset(&surface_hopper_launched_owner, 0, sizeof(surface_hopper_launched_owner));
    surface_hopper_launched_owner.ext.main_19.unk80 = mode <= KILL_RIGHT ? mode : 0;
    surface_hopper_launched_owner.ext.main_19.unk82 = mode == TIMEOUT ? 0x40 : 0x10;
    SP_CUR_MAIN_OBJ = &surface_hopper_launched_owner;
    memset(&surface_hopper_launched_hopper, 0, sizeof(surface_hopper_launched_hopper));
    surface_hopper_launched_hopper.active = 0x41;
    surface_hopper_launched_hopper.id = 0x13;
    surface_hopper_launched_hopper.state = 1;
    surface_hopper_launched_hopper.unk5 = 2;
    surface_hopper_launched_hopper.unk6 = 0;
    surface_hopper_launched_hopper.hp = mode == SURVIVE ? 20 : 1;
    surface_hopper_launched_hopper.unk42 = 0x8123;
    surface_hopper_launched_hopper.x_pos.val = (mode == FAR_AWAY ? 0x04000000 : 0x00800000) | 0x4444;
    surface_hopper_launched_hopper.y_pos.val = 0x00605555;
    surface_hopper_launched_hopper.collision_data = damage;
    surface_hopper_launched_hopper.animation_table = surface_hopper_launched_table;
    surface_hopper_launched_hopper.animation_cursor = &surface_hopper_launched_steps[0];
    surface_hopper_launched_hopper.animation_step.packed = surface_hopper_launched_steps[0];
    if (hit) {
        weapon_objects[0].active = 1;
        weapon_objects[0].id = 1;
        weapon_objects[0].x_pos = surface_hopper_launched_hopper.x_pos;
        weapon_objects[0].y_pos = surface_hopper_launched_hopper.y_pos;
        ((struct MainObj*)&weapon_objects[0])->attack_box = &weapon_box;
    }
    weapon = weapon_objects[0];
    surface_hopper_launched_expected = surface_hopper_launched_hopper;
    func_80053EB8(&surface_hopper_launched_hopper);

    {
        u32 index = surface_hopper_launched_owner.ext.main_19.unk80;
        surface_hopper_launched_expected.x_speed = surface_hopper_launch_x_speeds[index] * FIXED(1);
        surface_hopper_launched_expected.y_speed = surface_hopper_launch_y_speeds[index] * FIXED(1);
        surface_hopper_launched_expected.unk15 = surface_hopper_launch_facings[index];
        surface_hopper_launched_expected.unk17 = surface_hopper_launch_animations[index];
        surface_hopper_launched_expected.animation_cursor = surface_hopper_launched_table[surface_hopper_launched_expected.unk17];
        surface_hopper_launched_expected.previous_animation_index = 0xFF;
        surface_hopper_launched_expected.animation_step.packed = surface_hopper_launched_steps[1];
        surface_hopper_launched_expected.hurt_box = surface_hopper_launch_hurt_boxes[index];
        surface_hopper_launched_expected.attack_box = surface_hopper_launch_attack_boxes[index];
        surface_hopper_launched_expected.terrain_box = surface_hopper_launch_terrain_boxes[index];
        surface_hopper_launched_expected.unk6 = 1;
    }
    surface_hopper_launched_expected.unk18 = surface_hopper_launched_expected.x_pos;
    surface_hopper_launched_expected.unk1C = surface_hopper_launched_expected.y_pos;
    surface_hopper_launched_expected.unk42 &= 0x7FFF;
    if (hit) {
        surface_hopper_launched_expected.unk42 |= 0x8000;
        surface_hopper_launched_expected.hp = mode == SURVIVE ? 10 : 0;
    }
    if (mode <= KILL_RIGHT) {
        surface_hopper_launched_expected.state = 2;
    } else {
        if (mode == SURVIVE) {
            surface_hopper_launched_expected.unk5 = 1;
            surface_hopper_launched_expected.unk6 = 0;
        }
        if (mode == FAR_AWAY)
            surface_hopper_launched_expected.state = 2;
        else
            surface_hopper_launched_expected.on_screen = 1;
        if (mode == TIMEOUT)
            surface_hopper_launched_expected.state = 2;
    }
    same(&surface_hopper_launched_hopper, &surface_hopper_launched_expected, sizeof(surface_hopper_launched_hopper));
    same(visual_objects, want_visuals, sizeof(want_visuals));
    same(misc_objects, want_miscs, sizeof(want_miscs));
    for (i = 1; i < COUNT(weapon_objects); i++)
        assert(!weapon_objects[i].active);
    assert(g_Player.spike_immune == 1 && engine_obj.stage == 5);
    x = (u16)weapon_objects[0].x_pos.i.hi;
    y = ((u16*)&weapon_objects[0].unk80)[0];
    if (observation == 0)
        actual = (u8)surface_hopper_launched_hopper.state | ((u32)(u8)surface_hopper_launched_hopper.unk5 << 8) | ((u32)(u8)surface_hopper_launched_hopper.hp << 16) | ((u32)(u8)surface_hopper_launched_hopper.on_screen << 24);
    else
        actual = ((u32)((u16*)&weapon_objects[0].unk80)[1] << 16 | y) ^ (u32)(u8)weapon_objects[0].unk98 ^ x;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = banks[i];
    return actual;
}

static const u32 surface_hopper_launched_cases_expected[] = { 0x202u, 0x4E0018u, 0x202u, 0x5F00EDu, 0x202u, 0x720001u, 0x202u, 0x5F0021u, 0x10A0101u, 0x4E0018u, 0x1010201u, 0x0u, 0x10202u, 0x0u, 0x1010202u, 0x0u };
static u32 surface_hopper_launched_cases_row(u32 row)
{
    return surface_hopper_launched_run(row / 2, row % 2);
}

static struct TurnInput {
    u8 index, direction, facing, ignore, solid, near;
};
enum { V_TURN,
    V_TURN_DOWN,
    H_TURN,
    H_TURN_RIGHT,
    H_NEARBY,
    V_NEARBY,
    H_CRAWL,
    V_EMPTY };
static const struct TurnInput wall_crawler_turn_inputs[] = {
    { 0, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 1, 0 },
    { 2, 0, 0, 0, 1, 0 },
    { 2, 1, 0x40, 0, 1, 0 },
    { 2, 0, 0, 0xFF, 1, 1 },
    { 0, 0, 0x40, 0xFF, 1, 1 },
    { 2, 0, 0, 0xFF, 1, 0 },
    { 0, 0, 0, 0xFF, 0, 0 },
};
static u8 wall_crawler_turn_tilemap[256];
static u16 wall_crawler_turn_tiles[2][16][16];
static u32 wall_crawler_turn_attributes[1];
static u32 wall_crawler_turn_steps[2];
static u32* wall_crawler_turn_table[0x10];
static struct Unk_unk68 wall_crawler_turn_box = { 0, 0, 8, 8 };
static struct MainObj crawler, wall_crawler_turn_expected;

static u32 wall_crawler_turn_run(u32 mode, u32 observation)
{
    const struct TurnInput* input = &wall_crawler_turn_inputs[mode];
    union AnimationStep value;
    u32 i, difference = 0, actual, turned;
    u8 direction, flags;
    memset(wall_crawler_turn_tilemap, 1, sizeof(wall_crawler_turn_tilemap));
    memset(wall_crawler_turn_tiles, 0, sizeof(wall_crawler_turn_tiles));
    wall_crawler_turn_attributes[0] = input->solid ? 0x39 : 0;
    SP_BG_TILEMAP = wall_crawler_turn_tilemap;
    layout_width = 16;
    layout_size = 256;
    TEST_BG_TILE_PIXELS = (u8*)wall_crawler_turn_tiles;
    TEST_BG_TILE_ATTRS = (u8*)wall_crawler_turn_attributes;
    value.fields.duration = 4;
    value.fields.event = 0;
    value.fields.relative_step = 1;
    value.fields.frame_index = 1;
    wall_crawler_turn_steps[0] = value.packed;
    value.fields.duration = 7;
    wall_crawler_turn_steps[1] = value.packed;
    for (i = 0; i < COUNT(wall_crawler_turn_table); i++)
        wall_crawler_turn_table[i] = &wall_crawler_turn_steps[1];
    memset(&g_Player, 0, sizeof(g_Player));
    g_Player.x_pos.i.hi = input->near && input->index >= 2 ? 0x88 : 0x10;
    g_Player.y_pos.i.hi = input->near && input->index < 2 ? 0x64 : 0x10;
    memset(&crawler, 0, sizeof(crawler));
    crawler.active = 0x41;
    crawler.id = 0x15;
    crawler.state = 1;
    crawler.unk5 = 2;
    crawler.unk6 = 1;
    crawler.unk15 = input->facing;
    crawler.x_pos.val = 0x00801234;
    crawler.y_pos.val = 0x00605678;
    crawler.unk18 = crawler.x_pos;
    crawler.unk1C = crawler.y_pos;
    crawler.terrain_box = &wall_crawler_turn_box;
    crawler.animation_table = wall_crawler_turn_table;
    crawler.animation_cursor = &wall_crawler_turn_steps[0];
    crawler.animation_step.packed = wall_crawler_turn_steps[0];
    crawler.ext.main_19.unk80 = input->direction;
    crawler.ext.main_19.animation_index = input->index;
    crawler.ext.main_19.unk82 = input->ignore;
    SP_CUR_MAIN_OBJ = &crawler;
    wall_crawler_turn_expected = crawler;
    func_80053338(&crawler);

    flags = crawler.collision_flags;
    wall_crawler_turn_expected.x_pos = crawler.x_pos;
    wall_crawler_turn_expected.y_pos = crawler.y_pos;
    wall_crawler_turn_expected.collision_flags = flags;
    wall_crawler_turn_expected.unk6C = crawler.unk6C;
    wall_crawler_turn_expected.unk6E = crawler.unk6E;
    ((u8*)&wall_crawler_turn_expected)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)] = ((u8*)&crawler)[MMX4_OFFSET_OF(struct PlayerObj, touching_spikes)];
    ((u8*)&wall_crawler_turn_expected)[MMX4_OFFSET_OF(struct PlayerObj, wall_climbable)] = ((u8*)&crawler)[MMX4_OFFSET_OF(struct PlayerObj, wall_climbable)];
    turned = !((flags & (u8)~input->ignore) == 0 && input->solid && !input->near);
    if (!turned) {
        wall_crawler_turn_expected.animation_step.fields.duration--;
    } else {
        wall_crawler_turn_expected.unk17 = input->index < 2 ? 0xB : 0xA;
        wall_crawler_turn_expected.previous_animation_index = 0xFF;
        wall_crawler_turn_expected.animation_cursor = &wall_crawler_turn_steps[1];
        wall_crawler_turn_expected.animation_step.packed = wall_crawler_turn_steps[1];
        wall_crawler_turn_expected.unk6 = 6;
        direction = input->direction ^ 1;
        if (input->index >= 2)
            wall_crawler_turn_expected.unk15 ^= 0x40;
        wall_crawler_turn_expected.ext.main_19.unk80 = ((flags >> (input->index < 2 ? direction + 2 : direction)) & 1) ? direction ^ 1 : direction;
    }
    for (i = 0; i < sizeof(crawler) / 4; i++)
        difference |= ((u32*)&crawler)[i] ^ ((u32*)&wall_crawler_turn_expected)[i];
    assert(difference == 0);
    if (observation == 0)
        actual = turned | ((u32)crawler.ext.main_19.unk80 << 8) | ((u32)(u8)crawler.unk15 << 16) | ((u32)flags << 24);
    else
        actual = (u16)crawler.x_pos.i.hi | ((u32)(u16)crawler.y_pos.i.hi << 16);
    return actual;
}

static const u32 wall_crawler_turn_cases_expected[] = { 0xF000001u, 0x600080u, 0xF000101u, 0x600080u, 0xF400001u, 0x600080u, 0xF000101u, 0x600080u, 0xF400001u, 0x600080u, 0xF400001u, 0x600080u, 0xF000000u, 0x600080u, 0x101u, 0x600080u };
static u32 wall_crawler_turn_cases_row(u32 row)
{
    return wall_crawler_turn_run(row / 2, row % 2);
}

struct func_80052E94_0_case {
    u32 saved_y;
};
static const struct func_80052E94_0_case func_80052E94_0_cases[] = {
    { 67 },
    { 133 },
};
static u32 test_func_80052E94_0(u32 row)
{
    const struct func_80052E94_0_case* c = &func_80052E94_0_cases[row];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    u8 tiles[4], tiles_before[4];
    u16 pixels[512], pixels_before[512];
    u32 attrs[2], attrs_before[2];
    s16 saved_y, input_index;
    u8 probe_mode;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 19;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)surface_hopper_animations;
    obj.terrain_box = surface_hopper_attach_terrain_boxes[0];
    obj.hurt_box = surface_hopper_launch_hurt_boxes[0];
    obj.attack_box = surface_hopper_launch_hurt_boxes[0];
    obj.collision_data = D_801060F0;
    set_animation(&obj, 1);
    input_index = 0;
    saved_y = c->saved_y;
    probe_mode = 0;
    obj.unk2 = input_index;
    if (probe_mode) {
        obj.x_pos.i.hi = 105;
    }
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.unk7C = 59;
    obj.unk15 = 64;
    obj.ext.main_19.animation_index = input_index;
    obj.ext.main_19.unk80 = 0;
    obj.ext.main_19.unk84 = 32;
    obj.ext.main_19.unk86 = obj.x_pos.u.hi;
    obj.ext.main_19.unk88 = saved_y;
    obj.ext.main_19.unk8A = 21;
    obj.terrain_box = surface_hopper_attach_terrain_boxes[input_index >> 1];
    set_animation(&obj, 3);
    obj.animation_cursor = (const u8*)&surface_hopper_animations[3][14];
    obj.animation_step = surface_hopper_animations[3][14];
    g_Player.x_pos.i.hi = 220;
    g_Player.y_pos.i.hi = 100;
    memset(&tiles, 0, sizeof(tiles));
    memset(&pixels, 0, sizeof(pixels));
    memset(&attrs, 0, sizeof(attrs));
    tiles[0] = 1;
    if (probe_mode) {
        pixels[356] = 1;
    }
    if (probe_mode) {
        pixels[357] = 1;
    }
    attrs[1] = 0x38;
    SP_BG_TILEMAP = tiles;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attrs;
    layout_size = 1;
    layout_width = 1;
    memcpy(tiles_before, tiles, sizeof(tiles_before));
    memcpy(pixels_before, pixels, sizeof(pixels_before));
    memcpy(attrs_before, attrs, sizeof(attrs_before));
    SP_CUR_MAIN_OBJ = &obj;
    assert(!probe_mode || func_800537E0(&obj, 0, 1) == 0);
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    if (!probe_mode) {
        surface_hopper_aim_at_player(&expected);
    }
    assert(probe_mode || func_80053B54(&expected) == 0);
    if (!probe_mode) {
        expected.unk6 = 2;
    }
    if (!probe_mode) {
        set_animation(&expected, 6);
    }
    animate_object(ANIMATED_OBJECT(&expected));
    func_80052E94(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    c_test_same_words(pixels, pixels_before, sizeof(pixels));
    c_test_same_words(attrs, attrs_before, sizeof(attrs));
    c_test_same_words(tiles, tiles_before, sizeof(tiles));
    return 1;
}
static const u32 func_80052E94_1_expected[] = { 1u, 0xF30001u, 0u, 0u, 0u };
static u32 test_func_80052E94_1(u32 row)
{
    u32 observed_values[5];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    u8 tiles[4], tiles_before[4];
    u16 pixels[512], pixels_before[512];
    u32 attrs[2], attrs_before[2];
    s16 saved_y, input_index;
    u8 probe_mode;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 19;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)surface_hopper_animations;
    obj.terrain_box = surface_hopper_attach_terrain_boxes[0];
    obj.hurt_box = surface_hopper_launch_hurt_boxes[0];
    obj.attack_box = surface_hopper_launch_hurt_boxes[0];
    obj.collision_data = D_801060F0;
    set_animation(&obj, 1);
    input_index = 2;
    saved_y = 100;
    probe_mode = 1;
    obj.unk2 = input_index;
    if (probe_mode) {
        obj.x_pos.i.hi = 105;
    }
    obj.unk5 = 2;
    obj.unk6 = 1;
    obj.unk7C = 59;
    obj.unk15 = 0;
    obj.ext.main_19.animation_index = input_index;
    obj.ext.main_19.unk80 = 0;
    obj.ext.main_19.unk84 = 32;
    obj.ext.main_19.unk86 = obj.x_pos.u.hi;
    obj.ext.main_19.unk88 = saved_y;
    obj.ext.main_19.unk8A = 23;
    obj.terrain_box = surface_hopper_attach_terrain_boxes[input_index >> 1];
    set_animation(&obj, 2);
    obj.animation_cursor = (const u8*)&surface_hopper_animations[2][14];
    obj.animation_step = surface_hopper_animations[2][14];
    g_Player.x_pos.i.hi = 220;
    g_Player.y_pos.i.hi = 100;
    memset(&tiles, 0, sizeof(tiles));
    memset(&pixels, 0, sizeof(pixels));
    memset(&attrs, 0, sizeof(attrs));
    tiles[0] = 1;
    if (probe_mode) {
        pixels[356] = 1;
    }
    if (probe_mode) {
        pixels[357] = 1;
    }
    attrs[1] = 0x38;
    SP_BG_TILEMAP = tiles;
    TEST_BG_TILE_PIXELS = (u8*)pixels;
    TEST_BG_TILE_ATTRS = (u8*)attrs;
    layout_size = 1;
    layout_width = 1;
    memcpy(tiles_before, tiles, sizeof(tiles_before));
    memcpy(pixels_before, pixels, sizeof(pixels_before));
    memcpy(attrs_before, attrs, sizeof(attrs_before));
    SP_CUR_MAIN_OBJ = &obj;
    assert(!probe_mode || func_800537E0(&obj, 0, 1) == 0);
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    if (!probe_mode) {
        surface_hopper_aim_at_player(&expected);
    }
    assert(probe_mode || func_80053B54(&expected) == 0);
    if (!probe_mode) {
        expected.unk6 = 2;
    }
    if (!probe_mode) {
        set_animation(&expected, 6);
    }
    animate_object(ANIMATED_OBJECT(&expected));
    func_80052E94(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    c_test_same_words(pixels, pixels_before, sizeof(pixels));
    c_test_same_words(attrs, attrs_before, sizeof(attrs));
    c_test_same_words(tiles, tiles_before, sizeof(tiles));
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.animation_step.packed;
    observed_values[2] = (u32)obj.x_speed;
    observed_values[3] = (u32)obj.y_speed;
    observed_values[4] = (u32)obj.collision_flags;
    return c_test_observe(1, row, observed_values, func_80052E94_1_expected, 5);
}
static u32 test_func_80052E94(u32 index)
{
    if (index < 2)
        return test_func_80052E94_0(index);
    index -= 2;
    return test_func_80052E94_1(index);
}

struct func_8005368C_0_case {
    u32 full;
    u32 expected[3];
};
static const struct func_8005368C_0_case func_8005368C_0_cases[] = {
    { 1, { 0x32010003u, 1u, 0u } },
    { 0, { 0x32010003u, 0x41u, 0xBu } },
};
static u32 test_func_8005368C_0(u32 row)
{
    const struct func_8005368C_0_case* c = &func_8005368C_0_cases[row];
    u32 observed_values[3];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct ShotObj shots_expected[32];
    u8 full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 19;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)surface_hopper_animations;
    obj.terrain_box = surface_hopper_attach_terrain_boxes[0];
    obj.hurt_box = surface_hopper_launch_hurt_boxes[0];
    obj.attack_box = surface_hopper_launch_hurt_boxes[0];
    obj.collision_data = D_801060F0;
    set_animation(&obj, 1);
    obj.unk5 = 4;
    obj.unk6 = 1;
    obj.unk16 = 6;
    obj.unk15 = 64;
    obj.ext.main_19.animation_index = 0;
    obj.ext.main_19.unk83 = 0;
    set_animation(&obj, 13);
    obj.animation_cursor = (const u8*)&surface_hopper_animations[13][9];
    obj.animation_step = surface_hopper_animations[13][9];
    SP_CUR_MAIN_OBJ = &obj;
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    FILL_ACTIVE(shot_objects, 32, 1);
    full = c->full;
    if (!full) {
        memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    if (!full) {
        shots_expected[31].active = 0x41;
    }
    if (!full) {
        shots_expected[31].id = 11;
    }
    if (!full) {
        shots_expected[31].x_pos.i.hi = 70;
    }
    if (!full) {
        shots_expected[31].y_pos.i.hi = 100;
    }
    if (!full) {
        shots_expected[31].animation_table = (u32**)obj.animation_table;
    }
    if (!full) {
        shots_expected[31].unk40 = obj.unk40;
    }
    if (!full) {
        shots_expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (!full) {
        shots_expected[31].unk42 = obj.unk42 & 0x7FFF;
    }
    if (!full) {
        shots_expected[31].unk7C = (struct WeaponObj*)&obj;
    }
    if (!full) {
        shots_expected[31].unk16 = obj.unk16;
    }
    if (!full) {
        shots_expected[31].unk15 = obj.unk15;
    }
    if (!full) {
        shots_expected[31].x_vel.val = 65536;
    }
    if (!full) {
        shots_expected[31].y_vel.val = 0;
    }
    expected.animation_step.fields.event = 0;
    func_8005368C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    observed_values[0] = (u32)obj.animation_step.packed;
    observed_values[1] = (u32)shot_objects[31].active;
    observed_values[2] = (u32)shot_objects[31].id;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}
static const u32 inputs_1[2][21] = {
    { 0x41, 19, 1, 1, 1, 0, 0x00641234, 0x00645678, 3, 1, 0x56, 0x1234, 4, 1, 6, 64, 1, 0, 1, 1, 0 },
    { 0x41, 19, 1, 1, 1, 0, 0x00641234, 0x00645678, 3, 1, 0x56, 0x1234, 4, 1, 6, 64, 1, 0, 1, 0, 0 },
};
struct func_8005368C_1_case {
    u32 expected[3];
};
static const struct func_8005368C_1_case func_8005368C_1_cases[] = {
    { { 0x32010003u, 1u, 0u } },
    { { 0x32010003u, 0x41u, 0xBu } },
};
static u32 test_func_8005368C_1(u32 row)
{
    const struct func_8005368C_1_case* c = &func_8005368C_1_cases[row];
    u32 observed_values[3];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct ShotObj shots_expected[32];
    u8 full;
    memset(&obj, 0, sizeof(obj));
    obj.active = inputs_1[row][0];
    obj.id = inputs_1[row][1];
    obj.state = inputs_1[row][2];
    obj.unk5 = inputs_1[row][3];
    obj.unk6 = inputs_1[row][4];
    obj.bg_offset = inputs_1[row][5];
    obj.x_pos.val = inputs_1[row][6];
    obj.y_pos.val = inputs_1[row][7];
    obj.hp = inputs_1[row][8];
    obj.contact_damage = inputs_1[row][9];
    obj.unk40 = inputs_1[row][10];
    obj.unk42 = inputs_1[row][11];
    obj.animation_table = (const u8* const*)surface_hopper_animations;
    obj.terrain_box = surface_hopper_attach_terrain_boxes[0];
    obj.hurt_box = surface_hopper_launch_hurt_boxes[0];
    obj.attack_box = surface_hopper_launch_hurt_boxes[0];
    obj.collision_data = D_801060F0;
    set_animation(&obj, 1);
    obj.unk5 = inputs_1[row][12];
    obj.unk6 = inputs_1[row][13];
    obj.unk16 = inputs_1[row][14];
    obj.unk15 = inputs_1[row][15];
    obj.ext.main_19.animation_index = inputs_1[row][16];
    obj.ext.main_19.unk83 = inputs_1[row][17];
    set_animation(&obj, 13);
    obj.animation_cursor = (const u8*)&surface_hopper_animations[13][9];
    obj.animation_step = surface_hopper_animations[13][9];
    SP_CUR_MAIN_OBJ = &obj;
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    FILL_ACTIVE(shot_objects, 32, inputs_1[row][18] ? 1 : 0);
    full = inputs_1[row][19];
    if (!full) {
        memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    if (!full) {
        shots_expected[31].active = 0x41;
    }
    if (!full) {
        shots_expected[31].id = 11;
    }
    if (!full) {
        shots_expected[31].x_pos.i.hi = 130;
    }
    if (!full) {
        shots_expected[31].y_pos.i.hi = 100;
    }
    if (!full) {
        shots_expected[31].animation_table = (u32**)obj.animation_table;
    }
    if (!full) {
        shots_expected[31].unk40 = obj.unk40;
    }
    if (!full) {
        shots_expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (!full) {
        shots_expected[31].unk42 = obj.unk42 & 0x7FFF;
    }
    if (!full) {
        shots_expected[31].unk7C = (struct WeaponObj*)&obj;
    }
    if (!full) {
        shots_expected[31].unk16 = obj.unk16;
    }
    if (!full) {
        shots_expected[31].unk15 = obj.unk15;
    }
    if (!full) {
        shots_expected[31].x_vel.val = 65536;
    }
    if (!full) {
        shots_expected[31].y_vel.val = 0;
    }
    expected.animation_step.fields.event = inputs_1[row][20];
    func_8005368C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    observed_values[0] = (u32)obj.animation_step.packed;
    observed_values[1] = (u32)shot_objects[31].active;
    observed_values[2] = (u32)shot_objects[31].id;
    return c_test_observe(1, row, observed_values, c->expected, 3);
}
struct func_8005368C_2_case {
    u32 full;
    u32 expected[3];
};
static const struct func_8005368C_2_case func_8005368C_2_cases[] = {
    { 1, { 0x2A010003u, 1u, 0u } },
    { 0, { 0x2A010003u, 0x41u, 0xBu } },
};
static u32 test_func_8005368C_2(u32 row)
{
    const struct func_8005368C_2_case* c = &func_8005368C_2_cases[row];
    u32 observed_values[3];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    struct ShotObj shots_expected[32];
    u8 full;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 19;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)surface_hopper_animations;
    obj.terrain_box = surface_hopper_attach_terrain_boxes[0];
    obj.hurt_box = surface_hopper_launch_hurt_boxes[0];
    obj.attack_box = surface_hopper_launch_hurt_boxes[0];
    obj.collision_data = D_801060F0;
    set_animation(&obj, 1);
    obj.unk5 = 4;
    obj.unk6 = 1;
    obj.unk16 = 6;
    obj.unk15 = 64;
    obj.ext.main_19.animation_index = 2;
    obj.ext.main_19.unk83 = 0;
    set_animation(&obj, 12);
    obj.animation_cursor = (const u8*)&surface_hopper_animations[12][9];
    obj.animation_step = surface_hopper_animations[12][9];
    SP_CUR_MAIN_OBJ = &obj;
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    FILL_ACTIVE(shot_objects, 32, 1);
    full = c->full;
    if (!full) {
        memset(&shot_objects[31], 0, sizeof(shot_objects[31]));
    }
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    if (!full) {
        shots_expected[31].active = 0x41;
    }
    if (!full) {
        shots_expected[31].id = 11;
    }
    if (!full) {
        shots_expected[31].x_pos.i.hi = 100;
    }
    if (!full) {
        shots_expected[31].y_pos.i.hi = 128;
    }
    if (!full) {
        shots_expected[31].animation_table = (u32**)obj.animation_table;
    }
    if (!full) {
        shots_expected[31].unk40 = obj.unk40;
    }
    if (!full) {
        shots_expected[31].unk3C = (void*)obj.sprite_frames;
    }
    if (!full) {
        shots_expected[31].unk42 = obj.unk42 & 0x7FFF;
    }
    if (!full) {
        shots_expected[31].unk7C = (struct WeaponObj*)&obj;
    }
    if (!full) {
        shots_expected[31].unk16 = obj.unk16;
    }
    if (!full) {
        shots_expected[31].unk15 = obj.unk15;
    }
    if (!full) {
        shots_expected[31].x_vel.val = 65536;
    }
    if (!full) {
        shots_expected[31].y_vel.val = 0;
    }
    expected.animation_step.fields.event = 0;
    func_8005368C(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    observed_values[0] = (u32)obj.animation_step.packed;
    observed_values[1] = (u32)shot_objects[31].active;
    observed_values[2] = (u32)shot_objects[31].id;
    return c_test_observe(2, row, observed_values, c->expected, 3);
}
static u32 test_func_8005368C(u32 index)
{
    if (index < 2)
        return test_func_8005368C_0(index);
    index -= 2;
    if (index < 2)
        return test_func_8005368C_1(index);
    index -= 2;
    return test_func_8005368C_2(index);
}

static const u32 surface_hopper_crawl_turn_0_expected[] = { 3u, 0x1F010009u };
static u32 test_surface_hopper_crawl_turn_0(u32 row)
{
    u32 observed_values[2];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 19;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)surface_hopper_animations;
    obj.terrain_box = surface_hopper_attach_terrain_boxes[0];
    obj.hurt_box = surface_hopper_launch_hurt_boxes[0];
    obj.attack_box = surface_hopper_launch_hurt_boxes[0];
    obj.collision_data = D_801060F0;
    set_animation(&obj, 1);
    obj.unk5 = 2;
    obj.unk6 = 2;
    obj.ext.main_19.animation_index = 0;
    set_animation(&obj, 11);
    obj.animation_cursor = (const u8*)&surface_hopper_animations[11][6];
    obj.animation_step = surface_hopper_animations[11][6];
    SP_CUR_MAIN_OBJ = &obj;
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    expected.unk6 = 3;
    set_animation(&expected, 11);
    expected.animation_step.fields.duration = 9;
    surface_hopper_crawl_turn(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.animation_step.packed;
    return c_test_observe(0, row, observed_values, surface_hopper_crawl_turn_0_expected, 2);
}
static const u32 surface_hopper_crawl_turn_1_expected[] = { 3u, 0x18010009u };
static u32 test_surface_hopper_crawl_turn_1(u32 row)
{
    u32 observed_values[2];
    struct MainObj obj, expected;
    struct PlayerObj player_expected;
    struct EngineObj engine_before;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 19;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 1;
    obj.x_pos.val = 0x00641234;
    obj.y_pos.val = 0x00645678;
    obj.hp = 3;
    obj.contact_damage = 1;
    obj.unk40 = 0x56;
    obj.unk42 = 0x1234;
    obj.animation_table = (const u8* const*)surface_hopper_animations;
    obj.terrain_box = surface_hopper_attach_terrain_boxes[0];
    obj.hurt_box = surface_hopper_launch_hurt_boxes[0];
    obj.attack_box = surface_hopper_launch_hurt_boxes[0];
    obj.collision_data = D_801060F0;
    set_animation(&obj, 1);
    obj.unk5 = 2;
    obj.unk6 = 2;
    obj.ext.main_19.animation_index = 2;
    set_animation(&obj, 10);
    obj.animation_cursor = (const u8*)&surface_hopper_animations[10][6];
    obj.animation_step = surface_hopper_animations[10][6];
    SP_CUR_MAIN_OBJ = &obj;
    expected = obj;
    player_expected = g_Player;
    engine_before = engine_obj;
    expected.unk6 = 3;
    set_animation(&expected, 10);
    expected.animation_step.fields.duration = 9;
    surface_hopper_crawl_turn(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_expected, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    assert(SP_CUR_MAIN_OBJ == &obj);
    observed_values[0] = (u32)obj.unk6;
    observed_values[1] = (u32)obj.animation_step.packed;
    return c_test_observe(1, row, observed_values, surface_hopper_crawl_turn_1_expected, 2);
}
static u32 test_surface_hopper_crawl_turn(u32 index)
{
    if (index < 1)
        return test_surface_hopper_crawl_turn_0(index);
    index -= 1;
    return test_surface_hopper_crawl_turn_1(index);
}

struct surface_hopper_launch_case {
    u32 unk7C;
    u32 expected[3];
};
static const struct surface_hopper_launch_case surface_hopper_launch_cases[] = {
    { 0, { 0u, 0xFFFFFFFFu, 0xFFFFFFFFu } },
    { 1, { 2u, 0u, 0u } },
};
static u32 test_surface_hopper_launch(u32 row)
{
    const struct surface_hopper_launch_case* c = &surface_hopper_launch_cases[row];
    u32 observed_values[3];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk6 = -1;
    obj.unk7C = c->unk7C;
    surface_hopper_launch(&obj);
    observed_values[0] = (u32)obj.unk5;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7C;
    return c_test_observe(0, row, observed_values, c->expected, 3);
}

#define SH(kind, st, step, sub) (state_reset(step, sub, 0), so.unk2 = kind, so.state = st, so.x_pos.i.hi = 0x80, so.y_pos.i.hi = 0x60, so.terrain_box = &state_hit_box)
#define LAUNCH(kind, attr)                         \
    do {                                           \
        struct MainObj* current = SP_CUR_MAIN_OBJ; \
        SH(kind, 0, 0, 0);                         \
        state_terrain(attr);                       \
        SP_CUR_MAIN_OBJ = &so;                     \
        surface_hopper_update(&so);                \
        SP_CUR_MAIN_OBJ = current;                 \
        so.collision_data = NULL;                  \
    } while (0)
static void sh_launch_up(void)
{
    LAUNCH(3, 0);
}
static void sh_launch_up_wall(void) { LAUNCH(4, 0x38); }
static void sh_launch_right(void) { LAUNCH(5, 0); }
static void sh_launch_right_wall(void) { LAUNCH(6, 0x38); }
static void sh_launch_left(void) { LAUNCH(7, 0); }
static void sh_launch_left_wall(void) { LAUNCH(8, 0x38); }
static void sh_launch_other(void) { LAUNCH(9, 0); }
static void sh_appear_start(void)
{
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    SH(0, 1, 1, 0);
    so.animation_table = (void*)surface_hopper_animations;
    SP_CUR_MAIN_OBJ = &so;
    surface_hopper_appear(&so);
    SP_CUR_MAIN_OBJ = current;
}
static void sh_appear_wait(void)
{
    SH(0, 1, 1, 1);
    so.animation_step.fields.relative_step = 1;
    surface_hopper_appear(&so);
}
static void sh_appear_done(void)
{
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    SH(0, 1, 1, 1);
    so.animation_step.fields.relative_step = -1;
    cur_random = 0x1234;
    SP_CUR_MAIN_OBJ = &so;
    surface_hopper_appear(&so);
    SP_CUR_MAIN_OBJ = current;
    state_extra = so.ext.main_19.unk80;
}

static void (*const surface_hopper_states_cases[])(void) = {
    sh_launch_up,
    sh_launch_up_wall,
    sh_launch_right,
    sh_launch_right_wall,
    sh_launch_left,
    sh_launch_left_wall,
    sh_launch_other,
    sh_appear_start,
    sh_appear_wait,
    sh_appear_done,
};
static const u32 surface_hopper_states_expected[] = { 5u, 0u, 0x800000u, 0u, 0xFFF80000u, 0u, 0x1001Au, 0x1F0002u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0xFFF80000u, 0u, 0x1401Au, 0x1F0002u, 0u, 0u, 5u, 0u, 0x800000u, 0x80000u, 0u, 0u, 0x14009u, 0x1F0002u, 0u, 0u, 2u, 0u, 0x800000u, 0x80000u, 0u, 0u, 0x14008u, 0x1F0002u, 0u, 0u, 5u, 0u, 0x800000u, 0xFFF80000u, 0u, 0u, 0x10008u, 0x1F0002u, 0u, 0u, 2u, 0u, 0x800000u, 0xFFF80000u, 0u, 0u, 0x10009u, 0x1F0002u, 0u, 0u, 5u, 0u, 0x800000u, 0u, 0u, 0u, 0x1001Au, 0x1F0002u, 0u, 0u, 0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0xEu, 0u, 0u, 0u, 0x101u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 2u, 0u, 0x800000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

static u32 test_surface_hopper_states(u32 row)
{
    return state_run(surface_hopper_states_cases[row], row, &surface_hopper_states_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "surface_hopper_states", 0, 0, COUNT(surface_hopper_states_cases), test_surface_hopper_states },
    { "hopper_aim_edges", NULL, hopper_aim_edges_cases_expected, COUNT(hopper_aim_edges_cases_expected), hopper_aim_edges_cases_row },
    { "hopper_launch_binding", NULL, hopper_launch_binding_cases_expected, COUNT(hopper_launch_binding_cases_expected), launch_case },
    { "surface_hopper_crawl", NULL, surface_hopper_crawl_cases_expected, COUNT(surface_hopper_crawl_cases_expected), surface_hopper_crawl_cases_row },
    { "surface_hopper_launched", NULL, surface_hopper_launched_cases_expected, COUNT(surface_hopper_launched_cases_expected), surface_hopper_launched_cases_row },
    { "wall_crawler_turn", NULL, wall_crawler_turn_cases_expected, COUNT(wall_crawler_turn_cases_expected), wall_crawler_turn_cases_row },
    { "func_80052E94", 0, 0, 3, test_func_80052E94 },
    { "func_8005368C", 0, 0, 6, test_func_8005368C },
    { "surface_hopper_crawl_turn", 0, 0, 2, test_surface_hopper_crawl_turn },
    { "surface_hopper_launch", 0, 0, 2, test_surface_hopper_launch },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(surface_hopper_states_cases) + COUNT(hopper_aim_edges_cases_expected) + COUNT(hopper_launch_binding_cases_expected) + COUNT(surface_hopper_crawl_cases_expected) + COUNT(surface_hopper_launched_cases_expected) + COUNT(wall_crawler_turn_cases_expected) + 3 + 6 + 2 + 2;
