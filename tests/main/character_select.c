#include "test_runtime.h"
#include "main/character_select.h"
#include "main/1A5BC.h"
void character_select_state_1(struct EngineObj*);

static u32 select_case(u32 available)
{
    static const u8 variants[] = { 2, 7, 4, 3, 8, 5, 6 };
    struct EngineObj obj, expected;
    struct MiscObj pool[64];
    struct PlayerObj player_before = g_Player;
    u32 i, actual = 0;
    memset(&obj, 0, sizeof(obj));
    memset(misc_objects, 0, sizeof(misc_objects));
    obj.state = 1;
    obj.unk1 = 4;
    obj.unk2 = 2;
    obj.unk3 = 7;
    obj.stage = 13;
    obj.substage = 1;
    for (i = 0; i < 64; i++) {
        misc_objects[i].active = i >= 64 - available ? 0 : 1;
        misc_objects[i].id = 39;
        misc_objects[i].state = 40;
        misc_objects[i].unk2 = 9;
        misc_objects[i].unk5 = 3;
        misc_objects[i].unk6 = 4;
        misc_objects[i].unk7 = 5;
        misc_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        misc_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
    }
    expected = obj;
    expected.unk1 = 5;
    expected.unk2 = 0;
    memcpy(pool, misc_objects, sizeof(pool));
    for (i = 0; i < available; i++) {
        struct MiscObj* child = &pool[64 - available + i];
        child->active = 0x41;
        child->id = 0x1C;
        child->unk2 = variants[i];
    }
    character_select_spawn_objects(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool) / 4; i++)
        assert(((u32*)misc_objects)[i] == ((u32*)pool)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 57; i < 64; i++)
        if (misc_objects[i].active == 0x41)
            actual |= 1 << (i - 57);
    return actual | ((u32)obj.unk1 << 8);
}
static const u32 character_select_allocation_steps_cases_expected[] = { 0x500u, 0x540u, 0x560u, 0x570u, 0x578u, 0x57Cu, 0x57Eu, 0x57Fu };

#undef controller_input

#undef controller_input

static u32 code_default(s8 phase, void (*update)(void))
{
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&controller_input, 0, sizeof(controller_input));
    engine_obj.character_state.fields.secret_code_phase = phase;
    engine_obj.character_state.fields.secret_code_index = 5;
    engine_obj.unk37 = 0x55;
    update();
    assert(engine_obj.character_state.fields.secret_code_phase == phase);
    assert(engine_obj.character_state.fields.secret_code_index == 5);
    assert(engine_obj.unk37 == 0x55);
    return (u8)engine_obj.character_state.fields.secret_code_phase | ((u32)(u8)engine_obj.character_state.fields.secret_code_index << 8) | ((u32)(u8)engine_obj.unk37 << 16);
}
static u32 x_high_default(void)
{
    return code_default(3, func_80029A48);
}
static u32 zero_high_default(void)
{
    return code_default(4, func_80029BD8);
}
static const CTestCase secret_code_defaults_cases[] = {
    x_high_default,
    zero_high_default,
};
static const u32 secret_code_defaults_cases_expected[] = { 0x550503u, 0x550504u };
#undef controller_input

static void secret_input(u32 zero, u16 pressed, u16 held)
{
    controller_input.pressed = pressed;
    controller_input.held = held;
    if (zero)
        func_80029BD8();
    else
        func_80029A48();
    assert(controller_input.pressed == pressed && controller_input.held == held);
}

static void secret_prefix(u32 zero)
{
    const u16* sequence = zero ? D_800F44D8 : D_800F44C4;
    u32 i, length = zero ? 6 : 8;
    for (i = 0; i < length; i++) {
        secret_input(zero, sequence[i], sequence[i] | (zero ? PADR1 : 0));
        assert(engine_obj.character_state.fields.secret_code_index == i + 1);
        assert(engine_obj.character_state.fields.secret_code_phase == (i + 1 == length ? 2 : 1));
        if (i + 1 != length)
            secret_input(zero, 0, zero ? PADR1 : 0);
    }
}

static u32 test_secret_code_sequence(u32 row)
{
    u32 zero = row / 13, mode = row % 13;
    const u16* sequence = zero ? D_800F44D8 : D_800F44C4;
    struct EngineObj expected;
    s8 phase = 0, index = 0, enabled = 0;
    u16 hold = sequence[zero ? 6 : 8];
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&controller_input, 0, sizeof(controller_input));
    engine_obj.cur_character = zero;
    expected = engine_obj;
    secret_input(zero, 0, 0);
    if (mode == 1)
        secret_input(zero, PADselect, PADselect);
    else if (mode == 2)
        secret_input(zero, sequence[0], sequence[0] | (zero ? 0 : PADR1));
    else if (mode >= 3 && mode <= 5) {
        secret_input(zero, sequence[0], sequence[0] | (zero ? PADR1 : 0));
        index = 1;
        if (mode == 3) {
            secret_input(zero, 0, 0);
            phase = 1;
        }
        if (mode == 4)
            secret_input(zero, PADselect, PADselect | (zero ? PADR1 : 0));
        if (mode == 5)
            secret_input(zero, sequence[1], sequence[1] | (zero ? 0 : PADR1));
    } else {
        secret_prefix(zero);
        index = zero ? 6 : 8;
        phase = 2;
        if (mode == 6)
            secret_input(zero, 0, zero ? (PADR1 | sequence[5]) : 0);
        else if (mode == 7 && zero) {
            secret_input(zero, 0, PADL1);
            phase = 0;
        } else if (mode == 11 && zero) {
            secret_input(zero, PADstart, PADR1);
            phase = 0;
        } else {
            if (zero) {
                secret_input(zero, 0, 0);
                phase = 3;
            }
            if (mode == 0 || mode == 11) {
                secret_input(zero, mode == 11 ? PADstart : PAD_CONFIRM, hold | PAD_CONFIRM);
                phase = 0;
                enabled = 1;
            } else if (mode == 8) {
                secret_input(zero, PAD_CONFIRM, 0);
                phase = 0;
            } else if (mode == 10) {
                secret_input(zero, PADselect, PADselect);
                phase = 0;
            } else if (mode == 12)
                secret_input(zero, 0, 0);
            else
                secret_input(zero, hold, hold);
        }
    }
    expected.unk37 = enabled;
    expected.character_state.fields.secret_code_phase = phase;
    expected.character_state.fields.secret_code_index = index;
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    return 1;
}

static const struct {
    u8 phase, fade, ready, free_slots, next_phase, next_step, portraits;
} portrait_entries[] = {
    { 0, 0, 0, 2, 1, 1, 2 },
    { 0, 0, 0, 1, 1, 1, 1 },
    { 0, 0, 0, 0, 1, 1, 0 },
    { 1, 0, 0, 2, 1, 1, 0 },
    { 1, 0, 1, 2, 0, 2, 0 },
    { 1, 0, 3, 2, 0, 2, 0 },
    { 0, 0, 1, 2, 0, 2, 2 },
    { 0, 1, 0, 2, 0, 1, 0 },
    { 1, 1, 3, 2, 1, 1, 0 },
};

static u32 test_portrait_entry(u32 row)
{
    struct EngineObj expected;
    u32 i, spawned = 0;
    memset(&engine_obj, 0x25, sizeof(engine_obj));
    memset(&main_bss_state, 0, sizeof(main_bss_state));
    memset(misc_objects, 0, sizeof(misc_objects));
    engine_obj.unk1 = 1;
    engine_obj.unk2 = portrait_entries[row].phase;
    engine_obj.character_state.bytes[2] = portrait_entries[row].ready;
    main_bss_state.transition.active = portrait_entries[row].fade;
    for (i = 0; i < COUNT(misc_objects); i++) {
        misc_objects[i].active = i < COUNT(misc_objects) - portrait_entries[row].free_slots;
        misc_objects[i].id = 0x55;
    }
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 7;
    expected = engine_obj;
    expected.unk1 = portrait_entries[row].next_step;
    expected.unk2 = portrait_entries[row].next_phase;
    if (expected.unk1 == 2)
        expected.unk4 = 2;
    character_select_state_1(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(expected));
    for (i = 0; i < COUNT(misc_objects); i++)
        if (misc_objects[i].id == 28) {
            assert(misc_objects[i].active == 0x41 && misc_objects[i].unk2 == spawned);
            spawned++;
        }
    assert(spawned == portrait_entries[row].portraits);
    for (i = 0; i < 4; i++)
        assert(D_8013E188[i] == (expected.unk1 == 2 ? -1 : 7));
    return 1;
}

void character_select_state_3(struct EngineObj*);
static const struct {
    u16 pressed;
    u8 character;
} navigation[] = {
    { 0x8000, 0 },
    { 0x4000, 0 },
    { 0x1000, 1 },
    { 0x2000, 1 },
    { 0xA000, 1 },
    { 0x5000, 1 },
    { 0xF000, 1 },
    { 0xC000, 0 },
};
static const u16 confirmations[] = { 0, 0x40, 0x800, 0x840 };
static u32 navigate(u32 row)
{
    struct EngineObj expected;
    struct PlayerObj player_before = g_Player;
    struct ControllerInput input_before;
    u32 choice = row % COUNT(navigation), confirmation = row / COUNT(navigation) % 4, powered = row / COUNT(navigation) / 4;
    assert(PADLleft == 0x8000 && PADLdown == 0x4000 && PADLup == 0x1000 && PADLright == 0x2000 && PAD_CONFIRM == 0x40 && PADstart == 0x800);
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.state = 1;
    engine_obj.unk1 = 3;
    engine_obj.unk2 = 0x12FE;
    engine_obj.cur_character = 1 - navigation[choice].character;
    engine_obj.unk37 = powered;
    engine_obj.character_state.fields.previous_character = engine_obj.cur_character;
    engine_obj.character_state.fields.secret_code_phase = 7;
    engine_obj.character_state.fields.secret_code_index = 5;
    engine_obj.character_state.fields.menu_state = 0x12345678;
    controller_input.pressed = navigation[choice].pressed | confirmations[confirmation];
    controller_input.held = 0x1357;
    controller_input.previous = 0x2468;
    input_before = controller_input;
    expected = engine_obj;
    expected.cur_character = navigation[choice].character;
    expected.unk37 = 0;
    expected.character_state.fields.secret_code_phase = 0;
    expected.character_state.fields.previous_character = navigation[choice].character;
    if (confirmation) {
        expected.character_state.fields.active = 1;
        expected.unk1 = 4;
    }
    D_8013E198[5] = -1;
    character_select_state_3(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&controller_input, &input_before, sizeof(controller_input));
    assert(controller_input.pressed == input_before.pressed && D_8013E198[5] == -1);
    return 1;
}

void character_select_state_2_substate_0(struct EngineObj*);
static const s8 active_values[] = { 0, 1, -1 };
static const s16 low_bytes[] = { 0x1201, 0x12FE };
static struct UnkObj pool_expected[UNK_OBJECT_COUNT];
static u32 option_return(u32 row)
{
    struct GameInfo info, expected;
    struct MainBssState main_before;
    struct EngineObj engine_before = engine_obj;
    struct PlayerObj player_before = g_Player;
    u32 active = row % 3, character_mode = row / 3 % 2, byte = row / 6, i;
    for (i = 0; i < sizeof(unk_objects) / 4; i++)
        ((u32*)unk_objects)[i] = 0x25252525;
    memcpy(pool_expected, unk_objects, sizeof(pool_expected));
    memset(&info, 0x25, sizeof(info));
    info.unk0 = 10;
    info.mode = 3;
    info.unk6 = low_bytes[byte];
    expected = info;
    main_bss_state.transition.active = active_values[active];
    main_bss_state.character_mode = character_mode;
    main_before = main_bss_state;
    D_8013B7D0 = 2;
    need_palette_load = 0x20;
    if (active == 0) {
        memset(pool_expected, 0, sizeof(pool_expected));
        if (character_mode) {
            expected.unk0 = 8;
            expected.mode = expected.unk2 = expected.unk3 = 0;
        } else
            expected.unk6 = byte ? 0x12FF : 0x1202;
    }
    func_8002A394(&info);
    c_test_same_words(&info, &expected, sizeof(info));
    c_test_same_words(unk_objects, pool_expected, sizeof(pool_expected));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    assert(D_8013B7D0 == (active == 0 ? 0 : 2));
    assert(need_palette_load == (active == 0 && character_mode ? 0x21 : 0x20));
    return 1;
}
static u32 character_palette_wait(u32 row)
{
    struct EngineObj expected;
    struct MainBssState main_before = main_bss_state;
    struct PlayerObj player_before = g_Player;
    u32 timer = row % 3, dirty = row / 3, i;
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.state = 1;
    engine_obj.unk1 = 2;
    engine_obj.unk4 = timer;
    engine_obj.unk8 = 77;
    expected = engine_obj;
    need_palette_load = dirty ? 0x21 : 0x20;
    g_FilterAmountR = 16;
    g_FilterAmountG = 512;
    g_FilterAmountB = 0x4000;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 3;
    for (i = 0; i < 4; i++)
        D_8013E188[i] = 7;
    if (timer)
        expected.unk4--;
    else
        expected.unk2 = 1;
    character_select_state_2_substate_0(&engine_obj);
    c_test_same_words(&engine_obj, &expected, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    assert(g_FilterAmountR == (timer ? 31 : 0) && g_FilterAmountG == (timer ? 0x3E0 : 0) && g_FilterAmountB == (timer ? 0x7C00 : 0));
    assert(g_FilterModeR == 3 && g_FilterModeG == 3 && g_FilterModeB == 3);
    for (i = 0; i < 4; i++)
        assert(D_8013E188[i] == (timer ? 7 : 0));
    assert(need_palette_load == (timer && !dirty ? 0x20 : 0x21));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "secret_code_sequence", 0, 0, 26, test_secret_code_sequence },
    { "portrait_entry", 0, 0, COUNT(portrait_entries), test_portrait_entry },
    { "character_select_allocation_steps", NULL, character_select_allocation_steps_cases_expected, COUNT(character_select_allocation_steps_cases_expected), select_case },
    { "secret_code_defaults", secret_code_defaults_cases, secret_code_defaults_cases_expected, COUNT(secret_code_defaults_cases), 0 },
    { "navigation_priority_code_reset_and_confirm", NULL, NULL, COUNT(navigation) * 8, navigate },
    { "options_return_fade", NULL, NULL, 12, option_return },
    { "character_palette_wait", NULL, NULL, 6, character_palette_wait },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 26 + COUNT(portrait_entries) + COUNT(character_select_allocation_steps_cases_expected) + COUNT(secret_code_defaults_cases) + COUNT(navigation) * 8 + 12 + 6;
