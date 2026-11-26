#include "test_runtime.h"
#include "main/effects/effect_34_rock_drop_sequence.h"

static u32 rock_case(u32 mode)
{
    struct EffectObj obj, expected, pool_before[32];
    struct BackgroundObj bg_before[3];
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(effect_objects, 0, sizeof(effect_objects));
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = 1;
        effect_objects[i].id = 0x27;
        effect_objects[i].state = 0x28;
        effect_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        effect_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
        effect_objects[i].backref = &obj;
    }
    if (mode >= 4)
        effect_objects[31].active = 0;
    background_objects[0].unk34 = mode == 1 ? 0x10 : 0;
    obj.active = 0x41;
    obj.id = 34;
    obj.state = 1;
    obj.ext.effect_34.unk14 = mode == 2 ? 2 : mode == 5 ? 8
        : mode < 3                                      ? 1
                                                        : 0;
    obj.ext.effect_34.timer = mode < 3 ? 2 : 1;
    expected = obj;
    player_before = g_Player;
    memcpy(pool_before, effect_objects, sizeof(pool_before));
    memcpy(bg_before, background_objects, sizeof(bg_before));
    expected.ext.effect_34.timer = mode < 3 ? 1 : mode == 5 ? 0
                                                            : 2;
    if (mode >= 3) {
        expected.ext.effect_34.unk14 = mode == 5 ? 9 : 1;
        assert(rock_drop_sequence_delays[mode == 5 ? 9 : 1] == (mode == 5 ? 0 : 2));
        if (mode == 5)
            expected.state = 2;
        if (mode >= 4) {
            assert(rock_drop_sequence_subtypes[mode == 5 ? 8 : 0] == 0x24);
            assert(rock_drop_sequence_x_positions[mode == 5 ? 8 : 0] == (mode == 5 ? 0x4C0 : 0xC0));
            pool_before[31].active = 1;
            pool_before[31].id = 33;
            pool_before[31].unk2 = 0x24;
            pool_before[31].x_pos.u.hi = mode == 5 ? 0x4C0 : 0xC0;
            pool_before[31].y_pos.u.hi = 0x270;
            pool_before[31].backref = NULL;
            pool_before[31].state = 0;
        }
    } else if (mode == 0) {
        bg_before[0].unk36 = 8;
        bg_before[0].unk45 = 4;
        bg_before[0].unk3E.bytes[0] = 4;
        bg_before[0].unk3C = 2;
        bg_before[0].unk3A = 2;
        bg_before[0].unk34 |= 0x10;
    }
    rock_drop_sequence_spawn(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u16)obj.ext.effect_34.timer | ((u32)(u8)obj.ext.effect_34.unk14 << 16) | ((u32)(u8)obj.state << 24);
}
static const u32 rock_sequence_real_pool_cases_expected[] = { 0x1010001u, 0x1010001u, 0x1020001u, 0x1010002u, 0x1010002u, 0x2090000u };

void rock_drop_sequence_wait_player(struct EffectObj*);
void func_800BD080(struct EffectObj*);
static u32 rds_wait(u8 checkpoint, s16 player_x)
{
    struct EffectObj obj;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    engine_obj.checkpoint = checkpoint;
    g_Player.x_pos.i.hi = player_x;
    obj.active = 1;
    obj.ext.effect_34.unk14 = 5;
    rock_drop_sequence_wait_player(&obj);
    return (u8)obj.active | (u32)obj.state << 8 | (u32)obj.ext.effect_34.unk14 << 16 | (u32)(u16)obj.ext.effect_34.timer << 24;
}
static u32 rds_checkpoint(void) { return rds_wait(1, 0x300); }
static u32 rds_waiting(void) { return rds_wait(0, 0x240); }
static u32 rds_passed(void) { return rds_wait(0, 0x241); }
static u32 rds_swarm(void)
{
    struct EffectObj obj;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(main_objects, 0, sizeof(main_objects));
    memset(background_objects, 0, sizeof(background_objects));
    background_objects[0].x_pos.i.hi = 0x100;
    background_objects[0].y_pos.i.hi = 0x80;
    obj.ext.unk_effect.unk14 = 1;
    obj.ext.effect_4.unk16 = 0x10;
    cur_random = 0x1234;
    func_800BD080(&obj);
    for (i = 0; i < 5; i++) {
        assert(main_objects[i].active == 0x21 && main_objects[i].id == 0x3B && main_objects[i].unk2 == 0);
        assert(main_objects[i].x_pos.i.hi >= 0x110 && main_objects[i].x_pos.i.hi < 0x120);
        assert(main_objects[i].y_pos.i.hi >= 0x90 + i * 0x20 && main_objects[i].y_pos.i.hi < 0xB0 + i * 0x20);
    }
    assert(main_objects[5].active == 0);
    return obj.ext.unk_effect.unk14 | (u32)obj.ext.unk_effect.unk15 << 8 | (u32)(u16)obj.ext.effect_4.unk16 << 16;
}
static const CTestCase rock_drop_sequence_paths_cases[] = {
    rds_checkpoint,
    rds_waiting,
    rds_passed,
    rds_swarm,
};
static const u32 rock_drop_sequence_paths_cases_expected[] = { 0x00050000u, 0x00050001u, 0x02000101u, 0x00130107u };

const struct CTestGroup c_test_groups[] = {
    { "rock_sequence_real_pool", NULL, rock_sequence_real_pool_cases_expected, COUNT(rock_sequence_real_pool_cases_expected), rock_case },
    { "rock_drop_sequence_paths", rock_drop_sequence_paths_cases, rock_drop_sequence_paths_cases_expected, COUNT(rock_drop_sequence_paths_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(rock_sequence_real_pool_cases_expected) + COUNT(rock_drop_sequence_paths_cases);
