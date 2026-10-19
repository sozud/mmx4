#include "test_runtime.h"
#include "main/mains/main_75_general.h"
#include "main/195B4.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/shots/shot_55_general_shot.h"
void general_intro_wait_player(struct MainObj*);
void general_resume_step(struct MainObj* arg0);
void func_80091898(struct MainObj*);
void general_slam(struct MainObj* arg0);
extern union AnimationStep* final_cutscene_animations[1];
extern void* general_animations[46];
extern struct Unk_unk68 D_801059BC, D_801059C4[5];
void general_rise(struct MainObj*);
u8 general_at_position(struct ObjectHeader*, s16, s16);
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static s32 menu_frames[32];
static u32 page_metadata[2] = { 0x400, 0x480 };
static u32 ending_case(u32 mode)
{
    struct MainObj obj, expected;
    struct EffectObj effect, effect_before;
    struct BackgroundObj backgrounds_expected[3];
    struct EngineObj engine_expected;
    struct PlayerObj player_before = g_Player;
    u32 i, index = mode == 4 ? 6 : 8;
    memset(&obj, 0, sizeof(obj));
    memset(&effect, 0, sizeof(effect));
    for (i = 0; i < 16; i++) {
        menu_frames[i] = 64 + i * 4;
        menu_frames[i + 16] = i + 1;
    }
    engine_obj.stage = mode == 4 ? 12 : 11;
    engine_obj.substage = 1;
    background_objects[0].x_pos.val = 40 * 65536 + 0xBEEF;
    background_objects[0].y_pos.val = 50 * 65536 + 0xCAFE;
    background_objects[0].unk24 = 1;
    background_objects[0].unk26 = 2;
    background_objects[0].unk28 = 3;
    background_objects[0].unk2A = 4;
    effect.active = mode ? 1 : 0;
    effect.id = 26;
    effect.state = 2;
    effect.unk7 = mode >= 3 ? 1 : 0;
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 8;
    obj.unk6 = 4;
    obj.on_screen = 1;
    obj.ext.main_75.object.effect = &effect;
    obj.unk7E = mode == 2 ? 0 : 1;
    obj.unk42 = 0x2345;
    obj.unk15 = 0x40;
    obj.unk17 = 3;
    obj.previous_animation_index = 9;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    D_801406A8 = page_metadata;
    TEST_MENU_FRAMES = (u8*)menu_frames;
    expected = obj;
    effect_before = effect;
    engine_expected = engine_obj;
    memcpy(backgrounds_expected, background_objects, sizeof(backgrounds_expected));
    expected.on_screen = 0;
    if (mode == 1)
        expected.unk7E = 0;
    if (mode == 2) {
        expected.unk7E = 5;
        expected.unk42 ^= 0x8000;
    }
    if (mode >= 3) {
        assert(s_StageMainIds[(u8)engine_obj.stage][1][index] == 0xA3 && (u8)func_8002938C(0xA3) == index);
        expected.unk5 = 9;
        expected.unk40 = 0xB9;
        expected.unk42 = mode == 4 ? 0x78C0 : 0x78C8;
        expected.sprite_frames = (u8*)&menu_frames[16 + index];
        expected.animation_table = (const u8* const*)final_cutscene_animations;
        ANIMATED_OBJECT(&expected)->animation_cursor = (u32*)final_cutscene_animations[0];
        expected.animation_step = final_cutscene_animations[0][0];
        expected.unk17 = 0;
        expected.previous_animation_index = 0xFF;
        expected.x_pos.u.hi = 264;
        expected.y_pos.u.hi = 154;
        expected.unk15 = 0;
        backgrounds_expected[0].unk24 = backgrounds_expected[0].unk26 = 40;
        backgrounds_expected[0].unk28 = backgrounds_expected[0].unk2A = 50;
    }
    func_800915C4(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(effect) / 4; i++)
        assert(((u32*)&effect)[i] == ((u32*)&effect_before)[i]);
    for (i = 0; i < sizeof(backgrounds_expected) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < 16; i++) {
        assert(menu_frames[i] == 64 + i * 4);
        assert(menu_frames[i + 16] == i + 1);
    }
    assert(D_801406A8 == page_metadata && page_metadata[0] == 0x400 && page_metadata[1] == 0x480 && SP_MENU_FRAMES == menu_frames);
    i = obj.unk42 | ((u32)(u8)obj.unk7E << 16) | ((u32)(u8)obj.unk5 << 24);
    return i;
}
static const u32 general_ending_effect_context_cases_expected[] = { 0x8012345u, 0x8002345u, 0x805A345u, 0x90178C8u, 0x90178C0u };

static u32 far_player(u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    u32 i, actual, original_step;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 5;
    obj.unk6 = 2;
    obj.unk7 = 3;
    obj.unk7C = 0x27;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    g_Player.x_pos.i.hi = 109;
    g_Player.y_pos.i.hi = 200;
    obj.collision_flags = 2;
    obj.animation_table = (u32**)general_animations;
    obj.animation_cursor = general_animations[1];
    obj.animation_step.packed = *(u32*)general_animations[1];
    before = obj;
    player_before = g_Player;
    original_step = *(u32*)general_animations[1];
    func_800905D4(&obj);
    before.unk5 = obj.unk5;
    before.unk6 = obj.unk6;
    before.unk7 = obj.unk7;
    before.unk15 = obj.unk15;
    before.animation_step = obj.animation_step;
    for (i = 0; i < sizeof(obj); i++)
        assert(((u8*)&obj)[i] == ((u8*)&before)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&player_before)[i]);
    assert(*(u32*)general_animations[1] == original_step);
    actual = observation == 0 ? (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8)
            | ((u32)(u8)obj.unk7 << 16) | ((u32)(u8)obj.unk15 << 24)
                              : obj.animation_step.packed;
    return actual;
}
static u32 far_state(void)
{
    return far_player(0);
}
static u32 far_animation(void)
{
    return far_player(1);
}
static const CTestCase general_far_player_cases[] = { far_state, far_animation };
static const u32 general_far_player_cases_expected[] = { 0x40000002u, 0x10001u };

static u32 graphics_header[4] = { 0x1800, 0x12345678, 0x87654321, 0x55555555 };
static u32 intro_case(u32 mode)
{
    struct MainObj obj, expected;
    struct ShotObj linked, linked_before, pool_expected[32];
    struct PlayerObj player_expected;
    struct EngineObj engine_expected;
    u32 i, free_count = mode < 2 ? 0 : mode == 2 ? 1
                                                 : 2;
    memset(&obj, 0, sizeof(obj));
    memset(&linked, 0, sizeof(linked));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = i < 32 - free_count ? 1 : 0;
        shot_objects[i].id = 39;
        shot_objects[i].unk2 = 9;
        shot_objects[i].state = 40;
        shot_objects[i].unk5 = 3;
        shot_objects[i].unk6 = 4;
        shot_objects[i].unk7 = 5;
        shot_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        shot_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
        shot_objects[i].unk42 = 0x7777;
        shot_objects[i].bg_offset = 2;
    }
    linked.active = mode == 0 ? 1 : 0;
    linked.id = 55;
    linked.state = 2;
    memset(&obj.ext.main_75, 0xA5, sizeof(obj.ext.main_75));
    obj.ext.main_75.object.shot = mode == 1 || mode == 3 ? NULL : &linked;
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = 9;
    obj.hp = 127;
    obj.contact_damage = 7;
    obj.invincibility_timer = 3;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_speed = 12345;
    obj.y_speed = -12345;
    obj.x_accel = 123;
    obj.gravity = -321;
    obj.air_state = 7;
    obj.bg_offset = -1;
    obj.unk42 = 0x1234;
    obj.terrain_box = &D_801059BC;
    g_Player.x_pos.val = (mode == 4 ? 3700 : 3736) * 65536 + 0x1234;
    g_Player.bg_offset = 1;
    g_Player.script_state = 1;
    g_Player.spike_immune = 1;
    g_Player.script_action = 0x14;
    g_Player.script_facing = 0x40;
    engine_obj.gameplay_locked = 1;
    D_801406A8 = graphics_header;
    expected = obj;
    linked_before = linked;
    player_expected = g_Player;
    engine_expected = engine_obj;
    memcpy(pool_expected, shot_objects, sizeof(pool_expected));
    if (mode != 0) {
        expected.hp = 0;
        expected.contact_damage = 9;
        expected.invincibility_timer = 0;
        expected.x_pos.i.hi = 0xE98;
        expected.y_pos.i.hi = 0x27B;
        expected.unk5 = 2;
        expected.unk18.val = expected.x_pos.val;
        expected.unk1C.val = expected.y_pos.val;
        expected.unk40 = 0xE0;
        expected.unk16 = 5;
        expected.x_speed = expected.y_speed = expected.x_accel = expected.gravity = 0;
        expected.air_state = 0;
        expected.terrain_box = NULL;
        expected.collision_data = D_80107B78;
        expected.hurt_box = D_801059C4;
        expected.attack_box = &D_801059BC;
        expected.bg_offset = 1;
        expected.unk15 = mode == 4 ? 0 : 0x40;
        expected.animation_table = (const u8* const*)general_animations;
        expected.animation_cursor = general_animations[0];
        expected.animation_step = *(union AnimationStep*)general_animations[0];
        expected.unk17 = 0;
        expected.previous_animation_index = 0xFF;
        assert(expected.animation_step.packed == 1);
        memset(&expected.ext.main_75, 0, sizeof(expected.ext.main_75));
        if (free_count) {
            u32 first = 32 - free_count;
            pool_expected[first].active = 0x41;
            pool_expected[first].id = 55;
            pool_expected[first].unk2 = 1;
            pool_expected[first].unk7C = (struct WeaponObj*)&obj;
            expected.ext.main_75.object.shot = &shot_objects[first];
        }
        if (free_count == 2) {
            pool_expected[31].active = 0x41;
            pool_expected[31].id = 55;
            pool_expected[31].unk2 = 0;
            pool_expected[31].unk7C = (struct WeaponObj*)&obj;
            expected.ext.main_75.thruster = &shot_objects[31];
        }
        player_expected.script_state = 0;
        player_expected.spike_immune = 0;
        engine_expected.gameplay_locked = 0;
    }
    func_8008FBCC(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(linked) / 4; i++)
        assert(((u32*)&linked)[i] == ((u32*)&linked_before)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_expected)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    assert(D_801406A8 == graphics_header && graphics_header[0] == 0x1800);
    assert(graphics_header[1] == 0x12345678 && graphics_header[2] == 0x87654321 && graphics_header[3] == 0x55555555);
    i = (u8)obj.unk5 | ((u32)obj.unk15 << 8) | ((u32)(u8)obj.hp << 16);
    return i;
}
static const u32 general_intro_two_shot_pool_cases_expected[] = { 0x7F0001u, 0x4002u, 0x4002u, 0x4002u, 0x2u, 0x4002u };

static u32 punch_case(u32 right, u32 observation)
{
    struct MainObj obj, before;
    struct ShotObj thruster, thruster_before, pool_before[32];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&thruster, 0, sizeof(thruster));
    memset(shot_objects, 0, sizeof(shot_objects));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x27;
        shot_objects[i].state = 0x28;
    }
    shot_objects[17].active = shot_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk7C = 0x7777;
    obj.unk15 = right ? 0x40 : 0;
    obj.ext.main_75.thruster = &thruster;
    thruster.active = 0x41;
    thruster.id = 55;
    thruster.unk84.shot_55.x = 0x27;
    thruster.unk84.shot_55.y = 0x28;
    obj.animation_table = (const u8* const*)general_animations;
    set_animation_frame(&obj, 11, 2);
    before = obj;
    thruster_before = thruster;
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    general_punch_launch(&obj);
    before.animation_step.fields.duration = 1;
    before.animation_step.fields.event = 0;
    pool_before[17].active = pool_before[31].active = 0x41;
    pool_before[17].id = pool_before[31].id = 55;
    pool_before[17].unk2 = 2;
    pool_before[31].unk2 = 3;
    pool_before[17].unk7C = pool_before[31].unk7C = WEAPON_OBJECT(&obj);
    pool_before[17].unk8C.shot = &shot_objects[31];
    pool_before[31].unk8C.shot = &shot_objects[17];
    thruster_before.unk84.shot_55.x = right ? -0x20 : 0x20;
    thruster_before.unk84.shot_55.y = -4;
    assert(general_fists[0] == &shot_objects[17] && general_fists[1] == &shot_objects[31]);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(thruster) / 4; i++)
        assert(((u32*)&thruster)[i] == ((u32*)&thruster_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_before)[i]);
    return observation == 0 ? (u16)thruster.unk84.shot_55.x | ((u32)(u16)thruster.unk84.shot_55.y << 16) : obj.animation_step.packed;
}
static const u32 general_punch_linked_fists_cases_expected[] = { 0xFFFC0020u, 0x1E010001u, 0xFFFCFFE0u, 0x1E010001u };
static u32 general_punch_linked_fists_cases_row(u32 row)
{
    return punch_case(row / 2, row % 2);
}

static u32 rise_case(u32 observation)
{
    struct MainObj obj, before;
    struct ShotObj thruster, thruster_before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&thruster, 0, sizeof(thruster));
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.unk7 = 0;
    obj.unk7C = 0x7777;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = -32768;
    obj.gravity = 0x1000;
    obj.ext.main_75.thruster = &thruster;
    thruster.active = 0x41;
    thruster.id = 55;
    thruster.unk84.shot_55.x = 0x27;
    thruster.unk84.shot_55.y = 0x28;
    obj.animation_table = (const u8* const*)general_animations;
    thruster.animation_table = (u32**)general_animations;
    set_animation(&obj, 0);
    set_animation(&thruster, 0);
    before = obj;
    thruster_before = thruster;
    general_rise(&obj);
    before.unk7 = 1;
    before.unk17 = 8;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)general_animations[8];
    before.animation_step = *(union AnimationStep*)general_animations[8];
    before.y_speed = 32768;
    before.unk7C = 60;
    before.terrain_box = &D_801059D8;
    thruster_before.unk17 = 5;
    thruster_before.previous_animation_index = 0xFF;
    thruster_before.animation_cursor = general_animations[5];
    thruster_before.animation_step = *(union AnimationStep*)general_animations[5];
    thruster_before.unk84.shot_55.x = 24;
    thruster_before.unk84.shot_55.y = 4;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(thruster) / 4; i++)
        assert(((u32*)&thruster)[i] == ((u32*)&thruster_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return observation ? thruster.animation_step.packed : (u8)obj.unk7 | ((u32)obj.unk17 << 8) | ((u32)(u16)obj.unk7C << 16);
}
static const u32 general_rise_animation_start_cases_expected[] = { 0x3C0801u, 0xF010001u };

static u8 sound_entries[12];
static u32 impact_case(u32 mode)
{
    struct MainObj obj, before;
    struct ShotObj thruster, thruster_before, pool_before[32];
    struct BackgroundObj backgrounds_before[3];
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 i, impact = mode != 0;
    memset(&obj, 0, sizeof(obj));
    memset(&thruster, 0, sizeof(thruster));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(sound_entries, 0, sizeof(sound_entries));
    for (i = 0; i < 32; i++) {
        shot_objects[i].active = 1;
        shot_objects[i].id = 0x27;
        shot_objects[i].state = 0x28;
    }
    if (mode == 2)
        shot_objects[31].active = 0;
    D_80141F50[2] = sound_entries;
    D_8013E198[2] = -1;
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = 2;
    obj.collision_flags = impact ? 8 : 0;
    obj.ext.main_75.thruster = &thruster;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = -2 * 65536;
    thruster.active = 0x41;
    thruster.id = 55;
    thruster.timer = 7;
    obj.animation_table = (const u8* const*)general_animations;
    set_animation(&obj, 0);
    before = obj;
    thruster_before = thruster;
    memcpy(pool_before, shot_objects, sizeof(pool_before));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    general_slam_fall(&obj);
    before.x_pos.val += 65536;
    before.y_pos.val += 2 * 65536;
    if (impact) {
        before.unk6++;
        before.unk17 = 10;
        before.previous_animation_index = 0xFF;
        before.animation_cursor = (const u8*)general_animations[10];
        before.animation_step = *(union AnimationStep*)general_animations[10];
        thruster_before.timer = 0;
        backgrounds_before[0].unk36 = 20;
        backgrounds_before[0].unk45 = 4;
        backgrounds_before[0].unk3E.bytes[0] = 4;
        backgrounds_before[0].unk3C = 2;
        backgrounds_before[0].unk3A = 2;
        backgrounds_before[0].unk34 |= 0x10;
    }
    if (mode == 2) {
        pool_before[31].active = 0x41;
        pool_before[31].id = 0x37;
        pool_before[31].unk2 = 6;
        pool_before[31].unk7C = WEAPON_OBJECT(&obj);
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(thruster) / 4; i++)
        assert(((u32*)&thruster)[i] == ((u32*)&thruster_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(sound_entries); i++)
        assert(sound_entries[i] == 0);
    assert(D_8013E198[2] == -1);
    return (u8)obj.unk6 | ((u32)(u8)thruster.timer << 8) | ((u32)shot_objects[31].active << 16);
}
static const u32 general_slam_impact_pool_cases_expected[] = { 0x10702u, 0x10003u, 0x410003u };

static u32 general_slam_right_launch_slam_case(void)
{
    struct MainObj obj, before;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk6 = 3;
    obj.unk7C = 1;
    obj.unk15 = 0x40;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 65536;
    obj.y_speed = 2 * 65536;
    obj.animation_table = (const u8* const*)general_animations;
    set_animation(&obj, 0);
    before = obj;
    general_slam_ascend(&obj);
    before.x_pos.val += 65536;
    before.y_pos.val -= 2 * 65536;
    before.x_speed = 2 * 65536;
    before.y_speed = 0;
    before.unk7C = 0;
    before.unk6 = 4;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    actual = (u16)obj.x_pos.i.hi | ((u32)(u16)obj.y_pos.i.hi << 16);
    return actual;
}
static const CTestCase general_slam_right_launch_cases[] = { general_slam_right_launch_slam_case };
static const u32 general_slam_right_launch_cases_expected[] = { 0xC60065u };

static u32 general_slam_thruster_transitions_slam_case(u32 mode)
{
    struct MainObj obj, expected;
    struct ShotObj thruster, expected_thruster;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before = engine_obj;
    u32 i, facing = mode & 1, rise = mode >= 2 && mode < 4;
    memset(&obj, 0, sizeof(obj));
    memset(&thruster, 0, sizeof(thruster));
    D_8013E198[2] = -1;
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk6 = 2;
    obj.unk7 = mode >= 4;
    obj.unk7C = rise ? 0 : 1;
    obj.unk15 = facing ? 0x40 : 0;
    obj.x_speed = 3 * 65536;
    obj.y_speed = 7 * 65536;
    obj.ext.main_75.thruster = &thruster;
    obj.animation_table = (const u8* const*)general_animations;
    set_animation(&obj, rise ? 10 : mode >= 4 ? 9
                                              : 0);
    if (rise || mode >= 4) {
        obj.animation_cursor += (rise ? 22 : 3) * sizeof(union AnimationStep);
        obj.animation_step = *(const union AnimationStep*)obj.animation_cursor;
        assert(rise ? obj.animation_step.packed == 0x09000001 : obj.animation_step.packed == 0x19000102);
    }
    thruster.active = 0x41;
    thruster.id = 55;
    thruster.timer = 7;
    thruster.animation_table = (const u8* const*)general_animations;
    set_animation(&thruster, 0);
    expected = obj;
    expected_thruster = thruster;
    if (mode >= 4) {
        expected.animation_step.fields.duration = 1;
        expected.x_speed = 0;
        expected.y_speed = -5 * 65536;
        expected.unk6 = 3;
        expected.unk7 = 0;
    } else {
        u32 anim = rise ? 8 : 9, thruster_anim = rise ? 5 : 6;
        expected.unk17 = anim;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = general_animations[anim];
        expected.animation_step = *(union AnimationStep*)general_animations[anim];
        expected_thruster.unk17 = thruster_anim;
        expected_thruster.previous_animation_index = 0xFF;
        expected_thruster.animation_cursor = general_animations[thruster_anim];
        expected_thruster.animation_step = *(union AnimationStep*)general_animations[thruster_anim];
        expected_thruster.unk84.halves[0] = facing ? -24 : 24;
        expected_thruster.unk84.halves[1] = rise ? 4 : -16;
        if (rise) {
            expected.unk6 = 3;
            expected.unk7C = 15;
            expected.x_speed = 0;
            expected.y_speed = 5 * 65536;
            expected.terrain_box = &D_801059D8;
            expected_thruster.timer = 1;
        } else {
            expected.unk7 = 1;
            expected.unk7C = 0;
            expected.terrain_box = &D_801059DC;
        }
    }
    if (rise)
        general_slam_rise(&obj);
    else
        general_slam_windup(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(thruster) / 4; i++)
        assert(((u32*)&thruster)[i] == ((u32*)&expected_thruster)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    assert(D_8013E198[2] == -1);
    return (u8)obj.unk6 | ((u32)(u8)obj.unk7 << 8) | ((u32)obj.unk17 << 16) | ((u32)thruster.unk17 << 24);
}
static const u32 general_slam_thruster_transitions_cases_expected[] = { 0x6090102u, 0x6090102u, 0x5080003u, 0x5080003u, 0x90003u, 0x90003u };

struct func_800905D4_case {
    u32 obj_y_pos_hi, g_Player_y_pos_hi, obj_x_pos_hi, g_Player_x_pos_hi, collision_flags, unk15;
    u32 expected[7];
};
static const struct func_800905D4_case func_800905D4_cases[] = {
    { -32626, -32512, 0, 0, 0, 0, { 0u, 6u, 0u, 0u, 0x1Eu, 0u, 0u } },
    { 0, 0, 0, 0, 3, 255, { 0xBFu, 2u, 0u, 0u, 0u, 0u, 0u } },
    { -32626, -32512, -28673, -28671, 0, 0, { 0u, 6u, 0u, 0u, 0x1Eu, 0u, 0u } },
    { -32626, -32512, 7, -16377, 3, 255, { 0xBFu, 2u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_func_800905D4(u32 row)
{
    const struct func_800905D4_case* c = &func_800905D4_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.y_pos.i.hi = c->obj_y_pos_hi;
    g_Player.y_pos.i.hi = c->g_Player_y_pos_hi;
    obj.x_pos.i.hi = c->obj_x_pos_hi;
    g_Player.x_pos.i.hi = c->g_Player_x_pos_hi;
    obj.collision_flags = c->collision_flags;
    obj.unk15 = c->unk15;
    func_800905D4(&obj);
    observed_values[0] = (u32)obj.unk15;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

static const u32 general_at_position_expected[] = { 0u };
static u32 test_general_at_position(u32 row)
{
    u32 observed_values[1];
    struct ObjectHeader obj;
    u8 return_value;
    s16 arg1;
    s16 arg2;
    memset(&obj, 0, sizeof(obj));
    obj.x_pos.i.hi = 4;
    arg1 = -32767;
    arg2 = 0;
    return_value = general_at_position(&obj, arg1, arg2);
    observed_values[0] = (u32)return_value;
    return c_test_observe(0, row, observed_values, general_at_position_expected, 1);
}

struct general_rise_case {
    u32 unk7C;
    u32 expected[7];
};
static const struct general_rise_case general_rise_cases[] = {
    { 0, { 0u, 0u, 0u, 0u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0u } },
    { 1, { 0u, 0u, 2u, 0u, 0u, 0u, 0u } },
};
static u32 test_general_rise(u32 row)
{
    const struct general_rise_case* c = &general_rise_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    struct ShotObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_801059D8, 0, sizeof(D_801059D8));
    obj.unk7 = -1;
    obj.unk7C = c->unk7C;
    obj.ext.main_75.thruster = NULL;
    general_rise(&obj);
    observed_values[0] = (u32)child_0.unk84.shot_55.x;
    observed_values[1] = (u32)child_0.unk84.shot_55.y;
    observed_values[2] = (u32)obj.unk5;
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7;
    observed_values[5] = (u32)obj.unk7C;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

struct general_slam_rise_case {
    u32 unk7C, relative_step;
    u32 expected[7];
};
static const struct general_slam_rise_case general_slam_rise_cases[] = {
    { 255, 0, { 0u, 0u, 0u, 0u, 0xFEu, 0u, 0u } },
    { 0, -1, { 0u, 0u, 0u, 0u, 0u, 0u, 0u } },
};
static u32 test_general_slam_rise(u32 row)
{
    const struct general_slam_rise_case* c = &general_slam_rise_cases[row];
    u32 observed_values[7];
    struct MainObj obj;
    struct ShotObj child_0;
    memset(&obj, 0, sizeof(obj));
    memset(&child_0, 0, sizeof(child_0));
    memset(&D_801059D8, 0, sizeof(D_801059D8));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7C = c->unk7C;
    obj.animation_step.fields.relative_step = c->relative_step;
    obj.ext.main_75.thruster = NULL;
    general_slam_rise(&obj);
    observed_values[0] = (u32)child_0.timer;
    observed_values[1] = (u32)child_0.unk84.halves[0];
    observed_values[2] = (u32)child_0.unk84.halves[1];
    observed_values[3] = (u32)obj.unk6;
    observed_values[4] = (u32)obj.unk7C;
    observed_values[5] = (u32)obj.x_speed;
    observed_values[6] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, c->expected, 7);
}

#include "support/pool_full.h"
static u32 pool_full_general_death_blink(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_self.unk7E = 1;
    pf_snapshot();
    pf_expected.unk7C = 0;
    pf_expected.unk7E = 0;
    pf_expected.on_screen = 1;
    general_death_blink(&pf_self);
    pf_expected.unk5++;
    pf_expected.on_screen = 0;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_general_punch_rings(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_snapshot();
    general_punch_rings(&pf_self);
    pf_animated();
    pf_expected.unk7C = 0x3C;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_general_death_blink,
    pool_full_general_punch_rings,
};

static const u32 pool_full_cases_expected[] = { 0x1u, 0x3C0000u };
#include "support/state_cases.h"

static struct ShotObj general_thruster;
static struct MainObj general_blast;
#define GEN(step, phase) (state_reset(step, phase, 0), memset(&general_thruster, 0, sizeof(general_thruster)), memset(&general_blast, 0, sizeof(general_blast)), general_thruster.animation_table = (void*)state_table, so.ext.main_75.thruster = &general_thruster, so.x_pos.i.hi = 0xC00, so.y_pos.i.hi = 0x100)
#define GEN_SEEN() (state_extra = so.ext.main_75.bob_timer | (u8)so.ext.main_75.bob_step << 8 | (u32)(u8)so.ext.main_75.blink_delay << 16 | (u32)(u8)general_thruster.timer << 24)
static void gd_start(void)
{
    GEN(0, 0);
    general_thruster.timer = 9;
    main_bss_state.frame_counter = 1;
    func_80091898(&so);
    GEN_SEEN();
}
static void gd_blink_spawn(void)
{
    GEN(1, 0);
    so.unk7C = 1;
    so.unk7E = 2;
    so.ext.main_75.bob_timer = 1;
    so.ext.main_75.bob_step = 1;
    main_bss_state.frame_counter = 10;
    func_80091898(&so);
    GEN_SEEN();
}
static void gd_blink(void)
{
    GEN(1, 0);
    so.unk7C = 3;
    so.ext.main_75.blink_delay = 0x19;
    so.ext.main_75.bob_timer = 3;
    main_bss_state.frame_counter = 20;
    func_80091898(&so);
    GEN_SEEN();
}
static void gd_blink_last(void)
{
    GEN(1, 0);
    so.unk7C = 3;
    so.ext.main_75.blink_delay = 7;
    main_bss_state.frame_counter = 1;
    func_80091898(&so);
    GEN_SEEN();
}
static void gd_wait(void)
{
    GEN(3, 0);
    general_blast.active = 1;
    so.ext.main_75.object.child = &general_blast;
    main_bss_state.frame_counter = 1;
    func_80091898(&so);
}
static void gd_wait_done(void)
{
    GEN(3, 0);
    so.ext.main_75.object.child = &general_blast;
    main_bss_state.frame_counter = 1;
    func_80091898(&so);
}
static void gd_rumble_x(void)
{
    GEN(4, 0);
    so.unk7C = 1;
    abc_object.unkC = 0x80;
    main_bss_state.frame_counter = 1;
    func_80091898(&so);
}
static void gd_rumble_zero(void)
{
    GEN(4, 0);
    so.unk7C = 1;
    abc_object.unkC = 0x80;
    engine_obj.cur_character = 1;
    main_bss_state.frame_counter = 1;
    func_80091898(&so);
}
static void gd_rumble_wait(void)
{
    GEN(4, 0);
    so.unk7C = 2;
    main_bss_state.frame_counter = 1;
    func_80091898(&so);
}
static void gd_talk(void)
{
    GEN(4, 1);
    so.unk7E = 1;
    abc_object.unkC = 0x80;
    main_bss_state.frame_counter = 1;
    func_80091898(&so);
}
static void gd_talk_done(void)
{
    GEN(4, 1);
    so.unk7E = 2;
    abc_object.unkC = 0;
    main_bss_state.frame_counter = 1;
    func_80091898(&so);
}
static void gs_windup_charge(void)
{
    GEN(6, 0);
    so.unk7C = 1;
    so.unk15 = 0x40;
    general_slam(&so);
    state_extra = general_thruster.unk84.value;
}
static void gs_windup_charge_left(void)
{
    GEN(6, 0);
    so.unk7C = 1;
    general_slam(&so);
    state_extra = general_thruster.unk84.value;
}
static void gs_windup_wait(void)
{
    GEN(6, 0);
    so.unk7C = 2;
    general_slam(&so);
}
static void gs_windup_jump(void)
{
    GEN(6, 0);
    so.unk7 = 1;
    so.animation_step.fields.event = 1;
    general_slam(&so);
}
static void gs_windup_hold(void)
{
    GEN(6, 0);
    so.unk7 = 1;
    general_slam(&so);
}
static void gs_land(void)
{
    GEN(6, 2);
    so.animation_step.fields.event = 1;
    general_slam(&so);
}
static void gs_land_wait(void)
{
    GEN(6, 2);
    general_slam(&so);
}
static void gs_ascend(void)
{
    GEN(6, 4);
    so.unk7C = 1;
    general_slam(&so);
}
static void gs_ascend_right(void)
{
    GEN(6, 4);
    so.unk7C = 1;
    so.unk15 = 0x40;
    general_slam(&so);
}
static void gs_ascend_wait(void)
{
    GEN(6, 4);
    so.unk7C = 2;
    so.y_speed = -0x10000;
    general_slam(&so);
}
static void gs_leave_right_wall(void)
{
    GEN(6, 5);
    so.unk15 = 0x40;
    so.collision_flags = 1;
    general_slam(&so);
}
static void gs_leave_left_wall(void)
{
    GEN(6, 5);
    so.collision_flags = 2;
    general_slam(&so);
}
static void gs_leave_wrong_wall(void)
{
    GEN(6, 5);
    so.collision_flags = 1;
    so.x_speed = -0x20000;
    general_slam(&so);
}
static void gs_leave_right_open(void)
{
    GEN(6, 5);
    so.unk15 = 0x40;
    so.collision_flags = 2;
    general_slam(&so);
}
static void g_resume(void)
{
    GEN(1, 0);
    so.ext.main_75.saved_unk5 = 5;
    general_resume_step(&so);
}
static void g_intro_capsule(void)
{
    GEN(0, 0);
    g_Player.capsule_state = 1;
    general_intro_wait_player(&so);
}
static void g_intro_ready(void)
{
    GEN(0, 0);
    g_Player.x_pos.i.hi = 0xD40;
    general_intro_wait_player(&so);
    state_extra = background_objects[1].unk3 | effect_objects[0].id << 8;
}
static void g_intro_ready_near(void)
{
    GEN(0, 0);
    background_objects[1].unk3 = 5;
    general_intro_wait_player(&so);
    state_extra = background_objects[1].unk3;
}

static void (*const general_states_cases[])(void) = {
    gd_start,
    gd_blink_spawn,
    gd_blink,
    gd_blink_last,
    gd_wait,
    gd_wait_done,
    gd_rumble_x,
    gd_rumble_zero,
    gd_rumble_wait,
    gd_talk,
    gd_talk_done,
    gs_windup_charge,
    gs_windup_charge_left,
    gs_windup_wait,
    gs_windup_jump,
    gs_windup_hold,
    gs_land,
    gs_land_wait,
    gs_ascend,
    gs_ascend_right,
    gs_ascend_wait,
    gs_leave_right_wall,
    gs_leave_left_wall,
    gs_leave_wrong_wall,
    gs_leave_right_open,
    g_resume,
    g_intro_capsule,
    g_intro_ready,
    g_intro_ready_near,
};
static const u32 general_states_expected[] = { 0x100u, 0xFF000000u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0x19010Au, 0u, 0x200u, 0u, 0xC000000u, 0x1010000u, 0u, 0u, 0u, 0x40000u, 0xFF0Au, 0xFFFFFF81u, 0x100u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x48000u, 0x140002u, 0u, 0x100u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x48000u, 0x20000u, 0u, 0x300u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x400u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10400u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x30000u, 0u, 0u, 0x10400u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x30000u, 0u, 0u, 0x400u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x30000u, 0u, 0u, 0x10400u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x30000u, 0u, 0u, 0x10400u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x30000u, 0u, 0u, 0x1000600u, 0xFF400000u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x50000u, 0xFFF0FFE8u, 0u, 0x1000600u, 0xFF000000u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x50000u, 0xFFF00018u, 0u, 0x600u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10600u, 0u, 0xC000000u, 0x1000000u, 0u, 0xFFFB0000u, 0u, 0x40000u, 0u, 0u, 0x1000600u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x30600u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20600u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x50600u, 0u, 0xC000000u, 0x1000000u, 0xFFFE0000u, 0u, 0u, 0x40000u, 0u, 0u, 0x50600u, 0x400000u, 0xC000000u, 0x1000000u, 0x20000u, 0u, 0u, 0x40000u, 0u, 0u, 0x40600u, 0u, 0xC000000u, 0x1010000u, 0u, 0xFFFF0000u, 0u, 0x40000u, 0u, 0u, 0x200u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x200u, 0x400000u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x50600u, 0u, 0xBFE0000u, 0x1000000u, 0xFFFE0000u, 0u, 0u, 0x40000u, 0u, 0u, 0x50600u, 0x400000u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x500u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0u, 0u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x100u, 4u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x50000u, 0x1800u, 1u, 0x100u, 4u, 0xC000000u, 0x1000000u, 0u, 0u, 0u, 0x50000u, 5u, 1u };

static u32 test_general_states(u32 row)
{
    return object_run(general_states_cases[row], row, &general_states_expected[row * 10]);
}

static const struct {
    s8 weapon;
    u8 character, hit_active, timer, hp, full_pool, step;
    u8 next_hp, next_active, next_timer, flash_bit, shot, dead;
} general_damage_cases[] = {
    { -1, 0, 0, 0, 64, 0, 1, 64, 0, 0, 0, 0, 0 },
    { -1, 0, 1, 2, 64, 0, 1, 64, 1, 1, 1, 0, 0 },
    { -1, 0, 1, 1, 64, 0, 1, 64, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 64, 0, 1, 63, 1, 64, 1, 0, 0 },
    { 8, 0, 0, 0, 64, 0, 1, 61, 1, 64, 1, 1, 0 },
    { 17, 0, 0, 0, 64, 0, 1, 59, 1, 64, 1, 1, 0 },
    { 2, 0, 0, 0, 64, 0, 1, 64, 0, 0, 0, 0, 0 },
    { 8, 1, 0, 0, 64, 0, 1, 61, 1, 64, 1, 0, 0 },
    { 23, 1, 0, 0, 64, 0, 1, 64, 0, 0, 1, 0, 0 },
    { 24, 1, 0, 0, 64, 0, 1, 62, 0, 0, 1, 0, 0 },
    { 25, 1, 0, 0, 64, 0, 1, 62, 1, 64, 1, 0, 0 },
    { 29, 1, 0, 0, 64, 0, 1, 61, 1, 64, 1, 1, 0 },
    { 30, 1, 0, 0, 64, 0, 1, 61, 1, 64, 1, 0, 0 },
    { 31, 1, 0, 0, 64, 0, 1, 61, 1, 64, 1, 0, 0 },
    { 2, 1, 0, 0, 64, 0, 1, 64, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 },
    { 8, 0, 0, 0, 64, 1, 1, 61, 1, 64, 1, 0, 0 },
    { 29, 1, 0, 0, 64, 1, 1, 61, 1, 64, 1, 0, 0 },
};

static u32 test_general_damage(u32 row)
{
    u32 i, spawned = 0;
    memset(&state_room, 0, sizeof(state_room));
    memset(visual_objects, 0, sizeof(visual_objects));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    D_8013E198[0] = D_8013E198[1] = -1;
    engine_obj.cur_character = general_damage_cases[row].character;
    g_Player.unk2 = general_damage_cases[row].character;
    g_Player.spike_immune = !general_damage_cases[row].dead;
    so.active = 0x41;
    so.id = 75;
    so.state = 1;
    so.hp = general_damage_cases[row].hp;
    so.unk5 = general_damage_cases[row].step;
    so.unk6 = 2;
    so.unk7 = 3;
    so.animation_table = (const u8* const*)general_animations;
    set_animation(&so, 0);
    so.bg_offset = -1;
    so.x_pos.val = FIXED(100);
    so.y_pos.val = FIXED(200);
    so.ext.main_75.hit_active = general_damage_cases[row].hit_active;
    so.ext.main_75.hit_timer = general_damage_cases[row].timer;
    so.ext.main_75.saved_unk5 = 0x55;
    if (general_damage_cases[row].weapon >= 0) {
        state_hit(&so, general_damage_cases[row].weapon, 0, 0);
        weapon_objects[0].x_pos.val = FIXED(91);
        weapon_objects[0].y_pos.val = FIXED(133);
    } else
        memset(weapon_objects, 0, sizeof(weapon_objects));
    if (general_damage_cases[row].full_pool)
        for (i = 0; i < COUNT(shot_objects); i++)
            shot_objects[i].active = 1;
    func_80091218(&so);
    assert(so.hp == general_damage_cases[row].next_hp);
    assert(so.ext.main_75.hit_active == general_damage_cases[row].next_active);
    assert(so.ext.main_75.hit_timer == general_damage_cases[row].next_timer);
    assert(!!(so.unk42 & 0x8000) == general_damage_cases[row].flash_bit);
    assert(so.state == (general_damage_cases[row].dead ? 2 : 1));
    assert(so.unk5 == (general_damage_cases[row].dead ? 0 : 1));
    assert(so.ext.main_75.saved_unk5 == (general_damage_cases[row].step ? 1 : 0x55));
    assert(so.x_pos.val == FIXED(100) && so.y_pos.val == FIXED(200));
    assert(so.unk18.val == FIXED(100) && so.unk1C.val == FIXED(200));
    if (general_damage_cases[row].dead)
        assert(so.unk6 == 0 && g_Player.spike_immune == 1);
    for (i = 0; i < COUNT(shot_objects); i++)
        if (shot_objects[i].active && shot_objects[i].id == 0x37 && shot_objects[i].unk7C == (void*)&so) {
            assert(shot_objects[i].active == 0x41 && shot_objects[i].unk2 == 8);
            spawned++;
        }
    assert(spawned == general_damage_cases[row].shot);
    return 1;
}

void general_orbs_recover(struct MainObj*);
extern void* general_animations[46];
static u32 recover(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_before;
    u32 wait = row % 2, face = row / 2;
    engine_obj.stage = 11;
    engine_obj.substage = 0;
    engine_before = engine_obj;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 75;
    obj.state = 1;
    obj.unk5 = 5;
    obj.unk6 = 3;
    obj.unk7 = 0;
    obj.unk15 = face ? 0x40 : 0;
    obj.unk7C = wait ? 2 : 1;
    obj.animation_table = (const u8* const*)general_animations;
    set_animation(&obj, 8);
    assert(obj.animation_step.packed == 0x17010001);
    expected = obj;
    expected.unk7C--;
    expected.animation_cursor += 4;
    expected.animation_step.packed = 0x17FF0001;
    if (!wait) {
        expected.unk5 = 2;
        expected.unk6 = expected.unk7 = 0;
    }
    general_orbs_recover(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    return 1;
}

void general_intro_wait_player(struct MainObj*);
void general_orbs_descend(struct MainObj*);
void general_orbs_fire(struct MainObj*);
extern void* general_animations[46];
static struct EffectObj expected_effects[32];
static struct ShotObj expected_shots[32];
static u32 stop_entries[3];
static u32 full(u32 row)
{
    struct MainObj obj, expected;
    struct PlayerObj player;
    struct EngineObj engine;
    u32 i;
    engine_obj.stage = 11;
    engine_obj.substage = 1;
    engine_obj.max_hp = 32;
    g_Player.active = 0x41;
    g_Player.state = 1;
    g_Player.hp = 24;
    g_Player.y_pos.val = 640 * 65536;
    g_Player.x_pos.val = 3376 * 65536;
    g_Player.capsule_state = 0;
    c_test_zero_words((u32*)effect_objects, sizeof(effect_objects) / 4);
    for (i = 0; i < COUNT(effect_objects); i++)
        effect_objects[i].active = row ? 0 : 1;
    memcpy(expected_effects, effect_objects, sizeof(expected_effects));
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 75;
    obj.x_pos.i.hi = 3456;
    obj.y_pos.i.hi = 640;
    obj.animation_table = (const u8* const*)general_animations;
    if (row) {
        g_Player.x_pos.val = 3672 * 65536;
        g_Player.y_pos.val = 635 * 65536;
        obj.state = 1;
        obj.hp = 48;
        obj.unk5 = 5;
        obj.x_pos.i.hi = 3736;
        obj.y_pos.i.hi = 540;
        set_animation(&obj, 0);
        for (i = 0; i < COUNT(shot_objects); i++)
            shot_objects[i].active = 1;
        for (i = 0; i < 2; i++) {
            shot_objects[i].active = 0x41;
            shot_objects[i].id = 55;
            shot_objects[i].unk2 = i;
            shot_objects[i].unk7C = WEAPON_OBJECT(&obj);
            func_800AC8C4(&shot_objects[i]);
        }
        obj.ext.main_75.thruster = &shot_objects[0];
        obj.ext.main_75.object.shot = &shot_objects[1];
        memset(stop_entries, 0, sizeof(stop_entries));
        D_80141F50[2] = (u8*)stop_entries;
        D_8013E198[2] = -1;
        general_orbs_descend(&obj);
        for (i = 0; i < 99; i++)
            general_orbs_fire(&obj);
        assert(obj.unk6 == 1 && obj.unk7C == 1 && obj.y_pos.val == 589 * 65536 + 32768);
    }
    expected = obj;
    player = g_Player;
    engine = engine_obj;
    memcpy(expected_shots, shot_objects, sizeof(expected_shots));
    if (row) {
        expected.y_pos.val += 32768;
        expected.unk7C = 0;
        expected.unk6 = 2;
        expected_shots[0].unk17 = 7;
        expected_shots[0].previous_animation_index = 255;
        expected_shots[0].animation_cursor = general_animations[7];
        expected_shots[0].animation_step.packed = 0x0E000001;
    } else {
        expected.active |= 4;
        expected.unk5 = 1;
        player.script_state = 1;
        player.script_action = 0x14;
        player.script_facing = 0x40;
        player.spike_immune = 1;
        engine.gameplay_locked = 1;
    }
    cur_random = 0x1234;
    if (row)
        general_orbs_fire(&obj);
    else
        general_intro_wait_player(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(effect_objects, expected_effects, sizeof(expected_effects));
    c_test_same_words(shot_objects, expected_shots, sizeof(expected_shots));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    assert(cur_random == 0x1234);
    if (row)
        assert(stop_entries[0] == 0 && stop_entries[1] == 0 && stop_entries[2] == 0 && D_80141F50[2] == (u8*)stop_entries && D_8013E198[2] == -1);
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "general_damage", 0, 0, COUNT(general_damage_cases), test_general_damage },
    { "general_states", 0, 0, COUNT(general_states_cases), test_general_states },
    { "general_ending_effect_context", NULL, general_ending_effect_context_cases_expected, COUNT(general_ending_effect_context_cases_expected), ending_case },
    { "general_far_player", general_far_player_cases, general_far_player_cases_expected, COUNT(general_far_player_cases), 0 },
    { "general_intro_two_shot_pool", NULL, general_intro_two_shot_pool_cases_expected, COUNT(general_intro_two_shot_pool_cases_expected), intro_case },
    { "general_punch_linked_fists", NULL, general_punch_linked_fists_cases_expected, COUNT(general_punch_linked_fists_cases_expected), general_punch_linked_fists_cases_row },
    { "general_rise_animation_start", NULL, general_rise_animation_start_cases_expected, COUNT(general_rise_animation_start_cases_expected), rise_case },
    { "general_slam_impact_pool", NULL, general_slam_impact_pool_cases_expected, COUNT(general_slam_impact_pool_cases_expected), impact_case },
    { "general_slam_right_launch", general_slam_right_launch_cases, general_slam_right_launch_cases_expected, COUNT(general_slam_right_launch_cases), 0 },
    { "general_slam_thruster_transitions", NULL, general_slam_thruster_transitions_cases_expected, COUNT(general_slam_thruster_transitions_cases_expected), general_slam_thruster_transitions_slam_case },
    { "func_800905D4", 0, 0, 4, test_func_800905D4 },
    { "general_at_position", 0, 0, 1, test_general_at_position },
    { "general_rise", 0, 0, 2, test_general_rise },
    { "general_slam_rise", 0, 0, 2, test_general_slam_rise },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "actual_inherited_idle_animation_orb_timer_terminal_tick", NULL, NULL, 4, recover },
    { "General_actual_intro_or_100_tick_orb_descent_full_effect_or_shot_pool", NULL, NULL, 2, full },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(general_damage_cases) + COUNT(general_states_cases) + COUNT(general_ending_effect_context_cases_expected) + COUNT(general_far_player_cases) + COUNT(general_intro_two_shot_pool_cases_expected) + COUNT(general_punch_linked_fists_cases_expected) + COUNT(general_rise_animation_start_cases_expected) + COUNT(general_slam_impact_pool_cases_expected) + COUNT(general_slam_right_launch_cases) + COUNT(general_slam_thruster_transitions_cases_expected) + 4 + 1 + 2 + 2 + COUNT(pool_full_cases) + 4 + 2;
