#include "test_runtime.h"
#include "main/mains/main_08_eregion.h"
#include "main/55C4.h"
void eregion_pounce_jump(struct MainObj*);
void eregion_death(struct MainObj* arg0);
void eregion_pounce(struct MainObj* arg0);
void eregion_stomp_land(struct MainObj*);
extern union AnimationStep* D_800FAD68[];
extern u32 D_800FA724, D_800FA728, D_800FA72C;
extern struct Unk_unk68 D_801066F0[];
extern union AnimationStep D_800FA87C[6];
extern u32* D_80137E08;
extern u8* D_80141EE8[6];

static struct EregionInput {
    s16 x, player_x;
    s8 hp;
    u8 facing;
    u16 seed;
};
static const struct EregionInput inputs[] = {
    { 4700, 4701, 25, 0x40, 0 },
    { 4800, 4801, 25, 0, 0 },
    { 4800, 4801, 24, 0x40, 6 },
    { 4800, 5000, 24, 0x40, 7 },
};
static u32 eregion_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    struct PlayerObj player_before;
    const struct EregionInput* input = &inputs[mode];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    obj.active = 0x41;
    obj.id = 8;
    obj.state = 1;
    obj.unk5 = 0x27;
    obj.x_pos.val = input->x * 65536 + 0x1234;
    obj.hp = input->hp;
    obj.unk15 = input->facing;
    g_Player.x_pos.val = input->player_x * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)D_800FAD68;
    set_animation(&obj, 0);
    obj.animation_step.fields.duration = 1;
    cur_random = input->seed;
    before = obj;
    player_before = g_Player;
    func_800480D0(&obj);
    before.unk5 = obj.unk5;
    before.ext.main_8.unk8A = 1;
    before.animation_cursor = (const u8*)&D_800FAD68[0][1];
    before.animation_step = D_800FAD68[0][1];
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    if (observation == 0)
        return (u8)obj.unk5 | ((u32)obj.ext.main_8.unk8A << 8)
            | ((u32)(u16)obj.unk7C << 16);
    if (observation == 1)
        return cur_random;
    return obj.animation_step.packed;
}
static const u32 eregion_choice_context_cases_expected[] = { 0x104u, 0x0u, 0x1010010u, 0x104u, 0x0u, 0x1010010u, 0x105u, 0x6u, 0x1010010u, 0x106u, 0x7u, 0x1010010u };
static u32 eregion_choice_context_cases_row(u32 row)
{
    return eregion_case(row / 3, row % 3);
}

static u32 graphics_header[4] = { 0x1800, 0x12345678, 0x87654321, 0x55555555 };
static u32 intro_case(u32 mode)
{
    struct MainObj obj, expected;
    struct VisualObj pool_expected[32];
    struct PlayerObj player_before = g_Player;
    struct EngineObj engine_expected;
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    memset(&obj.ext, 0xA5, sizeof(obj.ext));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
        visual_objects[i].unk2 = 9;
        visual_objects[i].state = 40;
        visual_objects[i].unk5 = 3;
        visual_objects[i].unk6 = 4;
        visual_objects[i].unk7 = 5;
        visual_objects[i].unk50 = &g_Player;
        visual_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        visual_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
        visual_objects[i].unk42 = 0x7777;
        visual_objects[i].bg_offset = 2;
    }
    if (mode >= 1)
        visual_objects[29].active = 0;
    if (mode == 2)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 8;
    obj.state = 0;
    obj.unk5 = 1;
    obj.unk6 = 9;
    obj.unk7 = 7;
    obj.on_screen = 3;
    obj.unk15 = 0x40;
    obj.bg_offset = -1;
    obj.hp = 127;
    obj.contact_damage = 7;
    obj.invincibility_timer = 3;
    obj.air_state = 7;
    obj.unk16 = 12;
    obj.unk40 = 0x1234;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_speed = 12345;
    obj.y_speed = -12345;
    obj.x_accel = 123;
    obj.gravity = -321;
    obj.animation_step.packed = 0x12345678;
    obj.unk17 = 13;
    obj.previous_animation_index = 14;
    D_801406A8 = graphics_header;
    expected = obj;
    engine_expected = engine_obj;
    memcpy(pool_expected, visual_objects, sizeof(pool_expected));
    expected.ext.main_8.queued_sound = 0xFF;
    expected.ext.main_8.unk8B = expected.ext.main_8.unk8C = 0;
    expected.on_screen = 1;
    expected.unk15 = 0;
    expected.bg_offset = 0;
    expected.air_state = 1;
    expected.hp = 0;
    expected.contact_damage = 3;
    expected.invincibility_timer = 0;
    expected.unk16 = 6;
    expected.animation_table = (const u8* const*)D_800FAD68;
    expected.terrain_box = (struct Unk_unk68*)&D_800FA724;
    expected.collision_data = (const u16*)D_801066F0;
    expected.hurt_box = (const u8*)&D_800FA728;
    expected.attack_box = (const u8*)&D_800FA72C;
    expected.ext.main_8.unk84 = &D_800FA72C;
    expected.ext.main_8.unk88 = 1;
    expected.ext.main_8.unk80 = NULL;
    expected.unk40 = 0xE0;
    expected.animation_cursor = (const u8*)D_800FAD68[0];
    expected.animation_step = *D_800FAD68[0];
    expected.unk17 = 0;
    expected.previous_animation_index = 0xFF;
    expected.unk5 = 9;
    expected.state = 1;
    expected.x_pos.val = 0xF60 * 65536;
    expected.y_pos.val = 0x170 * 65536;
    engine_expected.unk25 = 2;
    engine_expected.boss_ptr = &obj;
    if (mode >= 1) {
        pool_expected[29].active = 0x41;
        pool_expected[29].id = 6;
        pool_expected[29].unk50 = (struct PlayerObj*)&obj;
        pool_expected[29].unk2 = 0;
    }
    if (mode == 2) {
        pool_expected[31].active = 0x41;
        pool_expected[31].id = 6;
        pool_expected[31].unk50 = (struct PlayerObj*)&obj;
        pool_expected[31].unk2 = 5;
    }
    func_80047D04(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool_expected) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)pool_expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_expected)[i]);
    assert(D_801406A8 == graphics_header && graphics_header[0] == 0x1800);
    assert(graphics_header[1] == 0x12345678 && graphics_header[2] == 0x87654321 && graphics_header[3] == 0x55555555);
    actual = (u8)obj.unk5 | ((u32)visual_objects[29].active << 8) | ((u32)visual_objects[31].active << 16);
    return actual;
}
static const u32 eregion_intro_two_visual_pool_cases_expected[] = { 0x10109u, 0x14109u, 0x414109u };

static u32 leap_case(u32 mode)
{
    struct MainObj obj, expected;
    struct EffectObj effect, effect_before;
    struct VisualObj pool_before[32];
    struct BackgroundObj backgrounds_before[3];
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&effect, 0, sizeof(effect));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        visual_objects[i].active = 1;
        visual_objects[i].id = 0x27;
        visual_objects[i].state = 0x28;
    }
    if (mode >= 2)
        visual_objects[31].active = 0;
    if (mode >= 3)
        visual_objects[30].active = 0;
    obj.active = 0x41;
    obj.id = 8;
    obj.state = 1;
    obj.unk6 = 1;
    obj.unk15 = mode == 4 ? 0x40 : 0;
    obj.x_speed = 123;
    obj.y_speed = 456;
    obj.x_accel = 789;
    obj.gravity = 987;
    obj.ext.main_9.effect = &effect;
    obj.unk7E = 7;
    obj.animation_table = (const u8* const*)D_800FAD68;
    set_animation(&obj, 0);
    effect.active = mode == 0 ? 1 : 0;
    effect.id = 0x27;
    expected = obj;
    effect_before = effect;
    memcpy(pool_before, visual_objects, sizeof(pool_before));
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    if (mode != 0) {
        expected.unk6 = 2;
        expected.x_speed = mode == 4 ? 0x88000 : -0x88000;
        expected.y_speed = -6 * 65536;
        expected.x_accel = 0;
        expected.gravity = -0x1800;
        expected.unk17 = 4;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = (const u8*)D_800FAD68[4];
        expected.animation_step = *D_800FAD68[4];
        expected.unk7E = 20;
        backgrounds_before[0].unk37 = -1;
        backgrounds_before[0].unk46 = 4;
        backgrounds_before[0].unk3E.bytes[1] = 4;
        backgrounds_before[0].unk3D = 2;
        backgrounds_before[0].unk3B = 2;
        backgrounds_before[0].unk34 |= 1;
        if (mode >= 2) {
            u32 first = mode == 2 ? 31 : 30;
            pool_before[first].active = 0x41;
            pool_before[first].id = 6;
            pool_before[first].unk50 = PLAYER_OBJECT(&obj);
            pool_before[first].unk2 = 3;
            if (mode >= 3) {
                pool_before[31].active = 0x41;
                pool_before[31].id = 6;
                pool_before[31].unk50 = PLAYER_OBJECT(&obj);
                pool_before[31].unk2 = 4;
            }
        }
    }
    eregion_intro_leap(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(effect) / 4; i++)
        assert(((u32*)&effect)[i] == ((u32*)&effect_before)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk6 | ((u32)obj.unk17 << 8) | ((u32)(u8)visual_objects[30].unk2 << 16) | ((u32)(u8)visual_objects[31].unk2 << 24);
}
static const u32 eregion_intro_visual_pool_cases_expected[] = { 0x1u, 0x402u, 0x3000402u, 0x4030402u, 0x4030402u };

static u32 recoil_case(u32 mode, u32 observation)
{
    struct MainObj obj, before;
    union AnimationStep animation_before[6];
    u32 i, actual;
    memset(&obj, 0, sizeof(obj));
    obj.active = 0x41;
    obj.id = 8;
    obj.state = 1;
    obj.unk6 = 0x27;
    obj.unk15 = mode == 0 ? 0x40 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.animation_table = (const u8* const*)D_800FAD68;
    set_animation(&obj, 0);
    assert(D_800FAD68[10] == D_800FA87C);
    memcpy(animation_before, D_800FA87C, sizeof(animation_before));
    assert(D_800FA87C[0].fields.frame_index == 0x1C);
    if (mode != 0)
        D_800FA87C[0].fields.frame_index = mode == 1 ? 0x1D : 0x0C;
    before = obj;
    eregion_recoil_start(&obj);
    before.unk6++;
    before.unk17 = 10;
    before.previous_animation_index = 0xFF;
    before.animation_cursor = (const u8*)D_800FA87C;
    before.animation_step = D_800FA87C[0];
    before.x_speed = 100;
    if (mode != 2)
        before.x_pos.i.hi = mode == 0 ? 78 : 122;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(D_800FA87C[0].packed == before.animation_step.packed);
    for (i = 1; i < 6; i++)
        assert(D_800FA87C[i].packed == animation_before[i].packed);
    actual = observation == 0 ? (u16)obj.x_pos.i.hi | ((u32)(u8)obj.unk6 << 16) : obj.animation_step.packed;
    return actual;
}
static const u32 eregion_recoil_frames_cases_expected[] = { 0x28004Eu, 0x1C010003u, 0x28007Au, 0x1D010003u, 0x280064u, 0xC010003u };
static u32 eregion_recoil_frames_cases_row(u32 row)
{
    return recoil_case(row / 2, row % 2);
}

static const u8 words[6] = { 0, 1, 3, 3, 4, 0 };
static u32 recovery_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    u32 i, animation = mode == 5 ? 0 : 10;
    memset(&obj, 0, sizeof(obj));
    memset(&obj.ext, 0xA5, sizeof(obj.ext));
    obj.active = 0x41;
    obj.id = 8;
    obj.state = 3;
    obj.unk5 = 4;
    obj.unk6 = 5;
    obj.unk7 = 6;
    obj.unk15 = mode & 1 ? 0 : 0x40;
    obj.x_speed = 300;
    obj.unk7C = mode & 1 ? 7 : 0;
    obj.x_pos.val = 50 * 65536 + 0xBEEF;
    obj.y_pos.val = 60 * 65536 + 0xCAFE;
    obj.unk42 = 0x9234;
    obj.animation_table = (const u8* const*)D_800FAD68;
    obj.animation_cursor = (const u8*)&D_800FAD68[animation][words[mode]];
    obj.animation_step = D_800FAD68[animation][words[mode]];
    obj.unk17 = animation;
    obj.previous_animation_index = 9;
    if (mode == 2 || mode == 3)
        obj.animation_step.fields.duration = 1;
    expected = obj;
    expected.x_pos.i.hi = 300;
    if (mode < 4)
        expected.x_pos.i.hi += obj.unk15 ? -22 : 22;
    expected.unk42 = 0x1234;
    if (--expected.animation_step.fields.duration == 0) {
        expected.animation_cursor = (const u8*)&D_800FAD68[animation][words[mode] + 1];
        expected.animation_step = D_800FAD68[animation][words[mode] + 1];
    }
    if (mode >= 2 && mode <= 4) {
        expected.state = 1;
        expected.unk6 = 0;
        expected.x_pos.i.hi = 300;
        expected.animation_cursor = (const u8*)D_800FAD68[0];
        expected.animation_step = *D_800FAD68[0];
        expected.unk17 = 0;
        expected.previous_animation_index = 0xFF;
        expected.unk5 = mode == 3 ? 1 : 5;
        expected.unk7C = mode == 3 ? 1 : 43;
    }
    func_8004932C(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(D_800FAD68[10][0].packed == 0x1C010003);
    assert(D_800FAD68[10][3].packed == 0x1D010003);
    assert(D_800FAD68[10][4].packed == 0x0C010105);
    return (u8)obj.state | ((u32)(u8)obj.unk5 << 8) | ((u32)(u16)obj.unk7C << 16);
}
static const u32 eregion_recovery_animation_cases_expected[] = { 0x403u, 0x70403u, 0x2B0501u, 0x10101u, 0x2B0501u, 0x70403u };

static u32 wing_case(u32 mode)
{
    struct MainObj obj, expected;
    struct ShotObj shots[32];
    struct VisualObj visuals[32];
    struct PlayerObj player_before = g_Player;
    struct Unk_unk68 box = { -2, -2, 4, 4 };
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(shot_objects, 0, sizeof(shot_objects));
    memset(visual_objects, 0, sizeof(visual_objects));
    for (i = 0; i < 32; i++) {
        struct ShotObj* s = &shot_objects[i];
        s->active = 1;
        s->id = 39;
        s->state = 40;
        s->unk2 = 9;
        s->unk5 = 3;
        s->unk6 = 4;
        s->unk7 = 5;
        s->x_pos.val = 50 * 65536 + 0xBEEF;
        s->y_pos.val = 60 * 65536 + 0xCAFE;
        s->unk50.data = (const u8*)&box;
        s->unk54 = (const u8*)&box;
        s->unk68 = &box;
        s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = 7;
        s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = s->unk78 = 7;
        s->unk62 = s->unk63 = s->unk7A = s->unk75 = 7;
        visual_objects[i].active = 1;
        visual_objects[i].id = 39;
        visual_objects[i].state = 40;
        visual_objects[i].unk2 = 9;
        visual_objects[i].unk5 = 3;
        visual_objects[i].unk6 = 4;
        visual_objects[i].x_pos.val = s->x_pos.val;
        visual_objects[i].y_pos.val = s->y_pos.val;
    }
    if (mode & 1)
        shot_objects[31].active = 0;
    if (mode & 2)
        visual_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = 8;
    obj.state = 1;
    obj.unk5 = 6;
    obj.unk6 = 0;
    obj.x_pos.val = 4800 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_speed = 123;
    obj.y_speed = 456;
    obj.x_accel = 789;
    obj.gravity = 987;
    obj.animation_table = (const u8* const*)D_800FAD68;
    set_animation(&obj, 0);
    expected = obj;
    memcpy(shots, shot_objects, sizeof(shots));
    memcpy(visuals, visual_objects, sizeof(visuals));
    expected.unk6 = 1;
    expected.x_speed = 4800;
    expected.unk17 = 8;
    expected.previous_animation_index = 0xFF;
    expected.animation_cursor = (const u8*)D_800FAD68[8];
    expected.animation_step = D_800FAD68[8][0];
    if (mode & 1) {
        struct ShotObj* s = &shots[31];
        s->active = 0x41;
        s->id = 4;
        s->unk7C = WEAPON_OBJECT(&obj);
        s->state = s->unk5 = s->unk6 = 0;
        s->unk50.data = NULL;
        s->unk54 = NULL;
        s->unk68 = NULL;
        s->unk98 = s->unk61 = s->unk64 = s->unk65 = s->unk66 = 0;
        s->unk72 = s->unk73 = s->unk74 = s->unk76 = s->unk77 = s->unk78 = 0;
        s->unk62 = s->unk63 = s->unk7A = s->unk75 = 0;
    }
    if (mode & 2) {
        visuals[31].active = 0x41;
        visuals[31].id = 6;
        visuals[31].state = visuals[31].unk5 = visuals[31].unk6 = 0;
        visuals[31].unk50 = PLAYER_OBJECT(&obj);
        visuals[31].unk2 = 1;
    }
    eregion_wing_slash_start(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(shots) / 4; i++)
        assert(((u32*)shot_objects)[i] == ((u32*)shots)[i]);
    for (i = 0; i < sizeof(visuals) / 4; i++)
        assert(((u32*)visual_objects)[i] == ((u32*)visuals)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return obj.unk17 | ((u32)(u8)shot_objects[31].active << 8) | ((u32)(u8)visual_objects[31].active << 16);
}
static const u32 eregion_wing_slash_pools_cases_expected[] = { 0x10108u, 0x14108u, 0x410108u, 0x414108u };

static const u32 eregion_fireball_fire_expected[] = { 2u, 2u, 0u, 1u, 0u, 0u };
static u32 test_eregion_fireball_fire(u32 row)
{
    u32 observed_values[6];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.animation_step.fields.event = 2;
    pool_0_full = 255;
    obj.animation_step.fields.relative_step = -128;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    eregion_fireball_fire(&obj);
    observed_values[0] = (u32)obj.animation_step.fields.event;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)shot_objects[0].active;
    observed_values[4] = (u32)shot_objects[0].id;
    observed_values[5] = (u32)shot_objects[0].unk2;
    return c_test_observe(0, row, observed_values, eregion_fireball_fire_expected, 6);
}

static const u32 eregion_intro_rise_expected[] = { 0u, 0u, 1u, 0x78u, 0u, 0x1240u, 0u, 0xFFFD8000u };
static u32 test_eregion_intro_rise(u32 row)
{
    u32 observed_values[8];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.unk7E = 255;
    obj.animation_step.fields.event = -1;
    eregion_intro_rise(&obj);
    observed_values[0] = (u32)obj.gravity;
    observed_values[1] = (u32)obj.unk15;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)obj.unk7E;
    observed_values[4] = (u32)obj.x_accel;
    observed_values[5] = (u32)obj.x_pos.i.hi;
    observed_values[6] = (u32)obj.x_speed;
    observed_values[7] = (u32)obj.y_speed;
    return c_test_observe(0, row, observed_values, eregion_intro_rise_expected, 8);
}

struct eregion_recoil_case {
    u32 invincibility_timer;
    u32 expected[2];
};
static const struct eregion_recoil_case eregion_recoil_cases[] = {
    { 0, { 0u, 0u } },
    { 1, { 0u, 0u } },
};
static u32 test_eregion_recoil(u32 row)
{
    const struct eregion_recoil_case* c = &eregion_recoil_cases[row];
    u32 observed_values[2];
    struct MainObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&background_objects, 0, sizeof(background_objects));
    memset(&qux_object, 0, sizeof(qux_object));
    obj.unk6 = 1;
    obj.invincibility_timer = c->invincibility_timer;
    eregion_recoil(&obj);
    observed_values[0] = (u32)obj.invincibility_timer;
    observed_values[1] = (u32)obj.unk42;
    return c_test_observe(0, row, observed_values, c->expected, 2);
}

static const u32 eregion_spread_fire_expected[] = { 0x40u, 2u, 0u, 1u, 0u, 0u };
static u32 test_eregion_spread_fire(u32 row)
{
    u32 observed_values[6];
    struct MainObj obj;
    u8 pool_0_full;
    memset(&obj, 0, sizeof(obj));
    memset(&shot_objects, 0, sizeof(shot_objects));
    memset(&D_80137E08, 0, sizeof(D_80137E08));
    memset(&D_80139234, 0, sizeof(D_80139234));
    memset(&D_8013924C, 0, sizeof(D_8013924C));
    memset(&D_8013E198, 0, sizeof(D_8013E198));
    memset(&D_80141EE8, 0, sizeof(D_80141EE8));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    memset(&background_objects, 0, sizeof(background_objects));
    obj.animation_step.fields.event = 64;
    pool_0_full = 255;
    obj.animation_step.fields.relative_step = -128;
    {
        u32 slot;
        for (slot = 0; slot < 32; ++slot)
            shot_objects[slot].active = pool_0_full ? 1 : 0;
    }
    eregion_spread_fire(&obj);
    observed_values[0] = (u32)obj.animation_step.fields.event;
    observed_values[1] = (u32)obj.unk5;
    observed_values[2] = (u32)obj.unk6;
    observed_values[3] = (u32)shot_objects[0].active;
    observed_values[4] = (u32)shot_objects[0].id;
    observed_values[5] = (u32)shot_objects[0].unk2;
    return c_test_observe(0, row, observed_values, eregion_spread_fire_expected, 6);
}

#include "support/pool_full.h"
static u32 pool_full_eregion_intro_warning(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    eregion_intro_warning(&pf_self);
    pf_expected.unk15 = 0x40;
    pf_expected.unk6++;
    pf_script(0x15, 0);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_eregion_fireball_open(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    eregion_fireball_open(&pf_self);
    pf_expected.unk6++;
    pf_animation(0xC);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_eregion_spread_open(void)
{
    u32 actual;
    pf_prepare();
    pf_snapshot();
    eregion_spread_open(&pf_self);
    pf_expected.unk6++;
    pf_animation(0x12);
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_eregion_death_blink(void)
{
    u32 actual;
    pf_prepare();
    pf_self.unk7C = 1;
    pf_self.unk7E = 1;
    pf_snapshot();
    pf_expected.unk7C = 0;
    pf_expected.unk7E = 0;
    pf_expected.on_screen = 1;
    eregion_death_blink(&pf_self);
    pf_expected.unk6++;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_eregion_intro_warning,
    pool_full_eregion_fireball_open,
    pool_full_eregion_spread_open,
    pool_full_eregion_death_blink,
};

static const u32 pool_full_cases_expected[] = { 0x50100u, 0x50100u, 0x50100u, 0x100u };
#include "support/state_cases.h"

static s8 eregion_blast[8];
static struct Unk_unk68 eregion_feet = { 0, 16, 16, 8 };
#define ER(step, phase) (state_reset(step, phase, 0), so.x_pos.i.hi = 0x1200, so.y_pos.i.hi = 0x100)
#define BLAST(alive, done) (eregion_blast[0] = alive, eregion_blast[7] = done, so.ext.main_9.effect = (void*)eregion_blast)
static void ee_death_start(void)
{
    ER(2, 0);
    g_Player.unk15 = 0x40;
    eregion_death(&so);
}
static void ee_death_blink_spawn(void)
{
    ER(2, 1);
    so.unk7C = 1;
    so.unk7E = 3;
    eregion_death(&so);
}
static void ee_death_blink(void)
{
    ER(2, 1);
    so.unk7C = 3;
    so.ext.main_9.object_id = 0x19;
    eregion_death(&so);
    state_extra = so.ext.main_9.object_id;
}
static void ee_death_blink_last(void)
{
    ER(2, 1);
    so.unk7C = 3;
    so.ext.main_9.object_id = 7;
    eregion_death(&so);
    state_extra = so.ext.main_9.object_id;
}
static void ee_wait_blink(void)
{
    ER(2, 2);
    BLAST(1, 0);
    eregion_death(&so);
}
static void ee_wait_count(void)
{
    ER(2, 2);
    BLAST(1, 0);
    so.unk7E = 3;
    eregion_death(&so);
}
static void ee_wait_boom(void)
{
    ER(2, 2);
    BLAST(1, 1);
    eregion_death(&so);
}
static void ee_wait_done(void)
{
    ER(2, 2);
    BLAST(0, 0);
    so.active = 1;
    eregion_death(&so);
}
static void ee_crouch_left(void)
{
    ER(3, 0);
    eregion_pounce(&so);
}
static void ee_crouch_right(void)
{
    ER(3, 0);
    so.unk15 = 0x40;
    eregion_pounce(&so);
}
static void ee_rise_wait(void)
{
    ER(3, 1);
    so.unk7E = 2;
    so.animation_step.fields.event = 1;
    eregion_pounce(&so);
}
static void ee_rise_top_left(void)
{
    ER(3, 1);
    so.y_pos.i.hi = 0x80;
    eregion_pounce(&so);
}
static void ee_rise_top_right(void)
{
    ER(3, 1);
    so.y_pos.i.hi = 0x80;
    so.unk15 = 0x40;
    eregion_pounce(&so);
}
static void ee_jump_left(void)
{
    ER(3, 2);
    so.animation_step.fields.event = 1;
    eregion_pounce(&so);
}
static void ee_jump_right(void)
{
    ER(3, 2);
    so.animation_step.fields.event = 1;
    so.unk15 = 0x40;
    eregion_pounce(&so);
}
static void ee_jump_roar(void)
{
    ER(3, 2);
    so.animation_step.fields.event = 3;
    so.x_speed = 0x10000;
    eregion_pounce(&so);
}
static void ee_stomp_shake(void)
{
    ER(5, 0);
    so.terrain_box = &eregion_feet;
    so.animation_step.fields.event = 1;
    eregion_stomp_land(&so);
}
static void ee_stomp_right_behind(void)
{
    ER(5, 0);
    so.terrain_box = &eregion_feet;
    so.collision_flags = 8;
    so.unk15 = 0x40;
    g_Player.x_pos.i.hi = 0x1000;
    eregion_stomp_land(&so);
}
static void ee_stomp_right_ahead(void)
{
    ER(5, 0);
    so.terrain_box = &eregion_feet;
    so.collision_flags = 8;
    so.unk15 = 0x40;
    g_Player.x_pos.i.hi = 0x1300;
    eregion_stomp_land(&so);
}
static void ee_stomp_left_behind(void)
{
    ER(5, 0);
    so.terrain_box = &eregion_feet;
    so.collision_flags = 8;
    g_Player.x_pos.i.hi = 0x1000;
    eregion_stomp_land(&so);
}
static void ee_stomp_left_ahead(void)
{
    ER(5, 0);
    so.terrain_box = &eregion_feet;
    so.collision_flags = 8;
    g_Player.x_pos.i.hi = 0x1300;
    eregion_stomp_land(&so);
}
static void ee_swipe_left(void)
{
    ER(6, 0);
    so.x_speed = 0x1234;
    func_80048B04(&so);
}
static void ee_swipe_right(void)
{
    ER(6, 0);
    so.x_speed = 0x1234;
    so.unk15 = 0x40;
    so.animation_step.fields.event = 2;
    func_80048B04(&so);
}
static void ee_swipe_end(void)
{
    ER(6, 0);
    so.x_speed = 0x1234;
    so.animation_step.fields.frame_index = 0xC;
    so.animation_step.fields.event = 1;
    func_80048B04(&so);
}
static void ee_pick_wait(void)
{
    ER(1, 0);
    so.unk7C = 2;
    func_800480D0(&so);
}
static void ee_pick_tired(void)
{
    ER(1, 0);
    so.ext.main_8.unk8A = 2;
    so.hp = 0x10;
    func_800480D0(&so);
}
static void ee_pick_tired_strong(void)
{
    ER(1, 0);
    so.ext.main_8.unk8A = 2;
    so.hp = 0x20;
    func_800480D0(&so);
}
static void ee_pick_near_right(void)
{
    ER(1, 0);
    so.hp = 0x20;
    so.unk15 = 0x40;
    so.x_pos.i.hi = 0x1250;
    g_Player.x_pos.i.hi = 0x1280;
    func_800480D0(&so);
}
static void ee_pick_near_right_edge(void)
{
    ER(1, 0);
    so.hp = 0x20;
    so.unk15 = 0x40;
    so.x_pos.i.hi = 0x11B0;
    g_Player.x_pos.i.hi = 0x11D0;
    func_800480D0(&so);
}
static void ee_pick_near_left(void)
{
    ER(1, 0);
    so.hp = 0x20;
    so.x_pos.i.hi = 0x11C0;
    g_Player.x_pos.i.hi = 0x1180;
    func_800480D0(&so);
}
static void ee_pick_near_left_edge(void)
{
    ER(1, 0);
    so.hp = 0x20;
    so.x_pos.i.hi = 0x1290;
    g_Player.x_pos.i.hi = 0x1250;
    func_800480D0(&so);
}
static void ee_pick_far_a(void)
{
    ER(1, 0);
    so.hp = 0x20;
    g_Player.x_pos.i.hi = 0x1000;
    cur_random = 1;
    func_800480D0(&so);
}
static void ee_pick_far_b(void)
{
    ER(1, 0);
    so.hp = 0x20;
    g_Player.x_pos.i.hi = 0x1000;
    cur_random = 5;
    func_800480D0(&so);
}
static void ee_pick_weak_near_a(void)
{
    ER(1, 0);
    so.hp = 0x10;
    g_Player.x_pos.i.hi = 0x1180;
    cur_random = 1;
    func_800480D0(&so);
}
static void ee_pick_weak_near_b(void)
{
    ER(1, 0);
    so.hp = 0x10;
    g_Player.x_pos.i.hi = 0x1180;
    cur_random = 7;
    func_800480D0(&so);
}
static void ee_pick_weak_far_a(void)
{
    ER(1, 0);
    so.hp = 0x10;
    g_Player.x_pos.i.hi = 0x1000;
    cur_random = 2;
    func_800480D0(&so);
}
static void ee_pick_weak_far_b(void)
{
    ER(1, 0);
    so.hp = 0x10;
    g_Player.x_pos.i.hi = 0x1000;
    cur_random = 9;
    func_800480D0(&so);
}

static void (*const eregion_states_cases[])(void) = {
    ee_death_start,
    ee_death_blink_spawn,
    ee_death_blink,
    ee_death_blink_last,
    ee_wait_blink,
    ee_wait_count,
    ee_wait_boom,
    ee_wait_done,
    ee_crouch_left,
    ee_crouch_right,
    ee_rise_wait,
    ee_rise_top_left,
    ee_rise_top_right,
    ee_jump_left,
    ee_jump_right,
    ee_jump_roar,
    ee_stomp_shake,
    ee_stomp_right_behind,
    ee_stomp_right_ahead,
    ee_stomp_left_behind,
    ee_stomp_left_ahead,
    ee_swipe_left,
    ee_swipe_right,
    ee_swipe_end,
    ee_pick_wait,
    ee_pick_tired,
    ee_pick_tired_strong,
    ee_pick_near_right,
    ee_pick_near_right_edge,
    ee_pick_near_left,
    ee_pick_near_left_edge,
    ee_pick_far_a,
    ee_pick_far_b,
    ee_pick_weak_near_a,
    ee_pick_weak_near_b,
    ee_pick_weak_far_a,
    ee_pick_weak_far_b,
};
static const u32 eregion_states_expected[] = { 0x1010200u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x20200u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x50000u, 0u, 1u, 0x10200u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x58000u, 0x14u, 0u, 0x10200u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x58000u, 2u, 0u, 0x20200u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x58000u, 0u, 0u, 0x20200u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0x80020200u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x50000u, 0u, 0u, 0u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x50000u, 0u, 0x41000000u, 0x10300u, 0xFF000000u, 0x12000000u, 0x1000000u, 0x30000u, 0x18000u, 0u, 0x50000u, 0u, 0u, 0x10300u, 0xFF400000u, 0x12000000u, 0x1000000u, 0xFFFD0000u, 0x18000u, 0u, 0x50000u, 0u, 0u, 0x20300u, 0xFF000000u, 0x12000000u, 0x1000000u, 0xFFF78000u, 0xFFFC0000u, 0xFFD00000u, 0x50000u, 0u, 0u, 0x10300u, 0u, 0x12000000u, 0x800000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x10300u, 0x400000u, 0x12000000u, 0x800000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20300u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20300u, 0x400000u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x20300u, 0u, 0x12010000u, 0x1000000u, 0x10000u, 0u, 0u, 0x40000u, 0u, 0u, 0x500u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0x2100u, 0x400u, 0x400000u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0x2100u, 0x500u, 0x400000u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0x2100u, 0x500u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0x2100u, 0x400u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0x2100u, 0x600u, 0u, 0x123C0000u, 0x1000000u, 0x1234u, 0u, 0u, 0x40000u, 0u, 0u, 0x600u, 0x400000u, 0x122C0000u, 0x1000000u, 0x1234u, 0u, 0u, 0x40000u, 0u, 0u, 0u, 0u, 0x12340000u, 0x1000000u, 0x1234u, 0u, 0u, 0x40000u, 0u, 0u, 0x100u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x600u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x400u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x400u, 0x400000u, 0x12500000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x500u, 0x400000u, 0x11B00000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x400u, 0u, 0x11C00000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x500u, 0u, 0x12900000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x300u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x800u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x700u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x500u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x700u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u, 0x700u, 0u, 0x12000000u, 0x1000000u, 0u, 0u, 0u, 0x40000u, 0u, 0u };

static u32 test_eregion_states(u32 row)
{
    return object_run(eregion_states_cases[row], row, &eregion_states_expected[row * 10]);
}

#define ER_SUB(sub) (state_reset(4, sub, 0), so.x_pos.i.hi = 0x1200, so.y_pos.i.hi = 0x100)
static void er_rise_hold(void)
{
    ER_SUB(2);
    so.unk7E = 2;
    eregion_pounce_rise(&so);
}
static void er_rise(void)
{
    ER_SUB(2);
    so.y_speed = 0x20000;
    so.animation_step.fields.event = 1;
    eregion_pounce_rise(&so);
}
static void er_rise_top_left(void)
{
    ER_SUB(2);
    so.y_pos.i.hi = 0x80;
    eregion_pounce_rise(&so);
    state_extra = so.ext.main_8.unk88;
}
static void er_rise_top_right(void)
{
    ER_SUB(2);
    so.y_pos.i.hi = 0x80;
    so.unk15 = 0x40;
    eregion_pounce_rise(&so);
}
static void er_jump_wait(void)
{
    ER_SUB(1);
    eregion_pounce_jump(&so);
}
static void er_jump_rumble(void)
{
    ER_SUB(1);
    so.animation_step.fields.event = 3;
    eregion_pounce_jump(&so);
}
static void er_jump_left(void)
{
    ER_SUB(1);
    so.animation_step.fields.event = 1;
    eregion_pounce_jump(&so);
}
static void er_jump_right(void)
{
    ER_SUB(1);
    so.animation_step.fields.event = 1;
    so.unk15 = 0x40;
    eregion_pounce_jump(&so);
}

static void (*const eregion_pounce_cases[])(void) = {
    er_rise_hold,
    er_rise,
    er_rise_top_left,
    er_rise_top_right,
    er_jump_wait,
    er_jump_rumble,
    er_jump_left,
    er_jump_right,
};
static const u32 eregion_pounce_expected[] = { 0x204u, 0x10000u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x204u, 0u, 0x12000000u, 0u, 0x20000u, 0u, 0u, 0u, 0u, 0u, 0x304u, 0u, 0x11A00000u, 0u, 0xFFFD8000u, 0u, 0x4000u, 2u, 1u, 0u, 0x304u, 0u, 0x12B00000u, 0u, 0xFFFD8000u, 0u, 0u, 2u, 0u, 0u, 0x104u, 0u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x104u, 0u, 0x12000000u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0x204u, 0x140000u, 0x12000000u, 0xFFF78000u, 0xFFFC0000u, 0xFFD00000u, 4u, 2u, 0u, 0u, 0x204u, 0x140000u, 0x12000000u, 0x88000u, 0xFFFC0000u, 0xFFD00000u, 0x4004u, 2u, 0u, 0u };

static u32 test_eregion_pounce(u32 row)
{
    return state_run(eregion_pounce_cases[row], row, &eregion_pounce_expected[row * 10]);
}

const struct CTestGroup c_test_groups[] = {
    { "eregion_pounce", 0, 0, COUNT(eregion_pounce_cases), test_eregion_pounce },
    { "eregion_states", 0, 0, COUNT(eregion_states_cases), test_eregion_states },
    { "eregion_choice_context", NULL, eregion_choice_context_cases_expected, COUNT(eregion_choice_context_cases_expected), eregion_choice_context_cases_row },
    { "eregion_intro_two_visual_pool", NULL, eregion_intro_two_visual_pool_cases_expected, COUNT(eregion_intro_two_visual_pool_cases_expected), intro_case },
    { "eregion_intro_visual_pool", NULL, eregion_intro_visual_pool_cases_expected, COUNT(eregion_intro_visual_pool_cases_expected), leap_case },
    { "eregion_recoil_frames", NULL, eregion_recoil_frames_cases_expected, COUNT(eregion_recoil_frames_cases_expected), eregion_recoil_frames_cases_row },
    { "eregion_recovery_animation", NULL, eregion_recovery_animation_cases_expected, COUNT(eregion_recovery_animation_cases_expected), recovery_case },
    { "eregion_wing_slash_pools", NULL, eregion_wing_slash_pools_cases_expected, COUNT(eregion_wing_slash_pools_cases_expected), wing_case },
    { "eregion_fireball_fire", 0, 0, 1, test_eregion_fireball_fire },
    { "eregion_intro_rise", 0, 0, 1, test_eregion_intro_rise },
    { "eregion_recoil", 0, 0, 2, test_eregion_recoil },
    { "eregion_spread_fire", 0, 0, 1, test_eregion_spread_fire },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(eregion_pounce_cases) + COUNT(eregion_states_cases) + COUNT(eregion_choice_context_cases_expected) + COUNT(eregion_intro_two_visual_pool_cases_expected) + COUNT(eregion_intro_visual_pool_cases_expected) + COUNT(eregion_recoil_frames_cases_expected) + COUNT(eregion_recovery_animation_cases_expected) + COUNT(eregion_wing_slash_pools_cases_expected) + 1 + 1 + 2 + 1 + COUNT(pool_full_cases);
