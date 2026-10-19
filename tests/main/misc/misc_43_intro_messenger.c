#include "test_runtime.h"
#include "main/misc/misc_43_intro_messenger.h"
#include "main/55C4.h"

static u32 messenger_case(u32 delay, u32 zero, u32 observation)
{
    struct MiscObj obj, before;
    struct AbcObj dialogue_before;
    struct EngineObj engine_before;
    struct PlayerObj player_before;
    u32 i, message;
    memset(&obj, 0, sizeof(obj));
    memset(&abc_object, 0, sizeof(abc_object));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.id = 43;
    obj.state = 1;
    obj.unk5 = delay ? 6 : 2;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.ext.unk.unk54 = 1;
    obj.animation_table = (u32**)intro_messenger_animations;
    set_animation_frame(&obj, 1, 3);
    abc_object.unkC = 0x80;
    abc_object.unkD = 7;
    abc_object.unkA = 0x25;
    abc_object.unk10 = 0x1234;
    engine_obj.cur_character = zero ? 1 : 0;
    engine_obj.stage = 2;
    engine_obj.enable_boss = 1;
    engine_obj.unk1F = 0x27;
    D_801397BC = D_801397C0 = D_801397C4 = D_801397C8 = NULL;
    D_801397CC = D_801397D0 = D_801397D4 = NULL;
    before = obj;
    dialogue_before = abc_object;
    engine_before = engine_obj;
    player_before = g_Player;
    if (delay) {
        intro_messenger_delay(&obj);
        before.ext.unk.unk54 = 0;
        before.unk5 = 7;
        message = zero ? 0x28 : 0x2F;
    } else {
        intro_messenger_land(&obj);
        before.unk5 = 3;
        message = zero ? 0x27 : 0x2E;
    }
    dialogue_before.unk10 = message | 0x8000;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(abc_object) / 4; i++)
        assert(((u32*)&abc_object)[i] == ((u32*)&dialogue_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    assert(D_801397BC == NULL && D_801397C0 == NULL && D_801397C4 == NULL && D_801397C8 == NULL);
    assert(D_801397CC == NULL && D_801397D0 == NULL && D_801397D4 == NULL);
    return observation == 0 ? (u16)abc_object.unk10 | ((u32)(u8)obj.unk5 << 16) : obj.animation_step.packed;
}
static const u32 intro_messenger_dialogue_context_cases_expected[] = { 0x3802Eu, 0x1000101u, 0x38027u, 0x1000101u, 0x7802Fu, 0x1000101u, 0x78028u, 0x1000101u };
static u32 intro_messenger_dialogue_context_cases_row(u32 row)
{
    return messenger_case(row / 4, row / 2 % 2, row % 2);
}

const struct CTestGroup c_test_groups[] = {
    { "intro_messenger_dialogue_context", NULL, intro_messenger_dialogue_context_cases_expected, COUNT(intro_messenger_dialogue_context_cases_expected), intro_messenger_dialogue_context_cases_row },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(intro_messenger_dialogue_context_cases_expected);
