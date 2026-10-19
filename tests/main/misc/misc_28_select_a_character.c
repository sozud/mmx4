#include "test_runtime.h"
#include "main/misc/misc_28_select_a_character.h"
#include "main/55C4.h"
void character_select_state_3(struct EngineObj*);
void character_select_state_4(struct EngineObj*);
void select_char_character_idle(struct MiscObj* arg0);
void select_char_main(struct MiscObj* arg0);
void select_char_portrait_slide_in(struct MiscObj* arg0);

static u32 select_case(u32 mode, u32 observation)
{
    static const u8 subtypes[4] = { 7, 8, 9, 12 };
    struct MiscObj obj, before;
    s32 archive[128];
    u32 resources[3] = { 0x10000, 0x18000, 0x20000 };
    u32 i, subtype = subtypes[mode], animation, resource;
    u32** table;
    memset(&obj, 0, sizeof(obj));
    memset(archive, 0, sizeof(archive));
    archive[0] = 64;
    archive[1] = 128;
    archive[2] = 192;
    TEST_MENU_FRAMES = (u8*)archive;
    D_801406A8 = resources;
    obj.active = 0x41;
    obj.id = 28;
    obj.state = 0;
    obj.unk2 = subtype;
    obj.unk15 = 0x27;
    obj.unk6 = 0x25;
    obj.unk7 = 0x26;
    obj.unk5 = 0x24;
    obj.unk16 = 0x28;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.x_vel.val = 65536;
    obj.y_vel.val = -65536;
    obj.ext.title_logo.palette_shift_speed = 7;
    obj.ext.title_logo.unk57 = 8;
    before = obj;
    select_char_init(&obj);
    if (mode == 1) {
        table = select_char_zero_animations;
        resource = 0;
        before.unk42 = 0x7800;
        before.unk15 = 0;
    } else if (mode == 3) {
        table = select_char_menu_animations;
        resource = 1;
        before.unk42 = 0x7808;
    } else {
        table = select_char_x_animations;
        resource = 2;
        before.unk42 = 0x7840;
        before.unk15 = 0x40;
    }
    animation = select_char_initial_animations[subtype];
    before.unk40 = resources[resource] >> 7;
    before.unk3C = (u8*)archive + archive[resource];
    before.animation_table = table;
    before.animation_cursor = table[animation];
    before.animation_step.packed = *table[animation];
    before.unk17 = animation;
    before.previous_animation_index = 0xFF;
    if (mode < 2) {
        before.x_pos.val = select_char_positions[subtype].x * 65536;
        before.y_pos.val = select_char_positions[subtype].y * 65536;
    }
    if (mode == 3) {
        before.x_pos.val = select_char_text_positions[0].x * 65536;
        before.y_pos.val = select_char_text_positions[0].y * 65536;
    }
    before.unk16 = select_char_priorities[subtype];
    before.bg_offset = -1;
    before.x_vel.val = before.y_vel.val = 0;
    before.ext.title_logo.palette_shift_speed = before.ext.title_logo.unk57 = before.unk6 = before.unk7 = 0;
    before.state = 1;
    before.unk5 = subtype;
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    assert(resources[0] == 0x10000 && resources[1] == 0x18000 && resources[2] == 0x20000);
    for (i = 0; i < 128; i++)
        assert(archive[i] == (i < 3 ? (s32)(64 + i * 64) : 0));
    return observation == 0 ? (u16)obj.x_pos.i.hi | ((u32)(u16)obj.y_pos.i.hi << 16) : obj.animation_step.packed;
}
static const u32 select_character_text_context_cases_expected[] = { 0xA00020u, 0x8u, 0xA00120u, 0x1u, 0xC80064u, 0xF010103u, 0x38FF40u, 0x5000001u };
static u32 select_character_text_context_cases_row(u32 row)
{
    return select_case(row / 2, row % 2);
}

struct select_char_portrait_bounce_1_case {
    u32 unk7, on_screen, blast_timer, hi;
    u32 expected[4];
};
static const struct select_char_portrait_bounce_1_case select_char_portrait_bounce_1_cases[] = {
    { -1, 0, 0, 0, { 0u, 0u, 0xFFFFFFFFu, 0u } },
    { 2, 0, 0, 0, { 0xFFu, 0u, 2u, 0u } },
    { 2, 0, 1, 0, { 0u, 0u, 3u, 0xFFF00000u } },
    { 1, -1, 0, 0, { 0u, 0u, 1u, 0u } },
    { 3, 0, 0, 0, { 0u, 0u, 3u, 0u } },
    { 3, 0, 0, 224, { 0u, 1u, 0u, 0u } },
    { 0, 0, 0, 0, { 0x14u, 0u, 1u, 0x100000u } },
};
static u32 test_select_char_portrait_bounce_1(u32 row)
{
    const struct select_char_portrait_bounce_1_case* c = &select_char_portrait_bounce_1_cases[row];
    u32 observed_values[4];
    struct MiscObj obj;
    memset(&obj, 0, sizeof(obj));
    obj.unk7 = c->unk7;
    obj.on_screen = c->on_screen;
    obj.ext.sel_char.blast_timer = c->blast_timer;
    obj.x_pos.i.hi = c->hi;
    select_char_portrait_bounce(&obj);
    observed_values[0] = (u32)obj.ext.sel_char.blast_timer;
    observed_values[1] = (u32)obj.unk6;
    observed_values[2] = (u32)obj.unk7;
    observed_values[3] = (u32)obj.x_vel.val;
    return c_test_observe(0, row, observed_values, c->expected, 4);
}

#include "support/pool_full.h"
static u32 pool_full_select_char_character_shoot(void)
{
    u32 actual;
    pf_prepare();
    pf_misc.animation_step.fields.event = 1;
    pf_snapshot();
    select_char_character_shoot(&pf_misc);
    pf_misc_expected.animation_step.fields.event = 0;
    pf_misc_expected.animation_step.fields.duration--;
    actual = pf_finish(0);
    return actual;
}
static u32 pool_full_select_char_shot_burst(void)
{
    u32 actual;
    pf_prepare();
    pf_misc.animation_step.fields.event = 1;
    pf_snapshot();
    select_char_shot_burst(&pf_misc);
    pf_misc_expected.animation_step.fields.event = 0;
    pf_misc_expected.animation_step.fields.duration--;
    actual = pf_finish(0);
    return actual;
}
static const CTestCase pool_full_cases[] = {
    pool_full_select_char_character_shoot,
    pool_full_select_char_shot_burst,
};

static const u32 pool_full_cases_expected[] = { 0x50000u, 0x50000u };
static u32 test_character_exit_lifecycle(u32 selected)
{
    struct MiscObj characters[2];
    s32 archive[128];
    u32 resources[3] = { 0x10000, 0x18000, 0x20000 };
    u32 i, ticks;
    memset(characters, 0, sizeof(characters));
    memset(archive, 0, sizeof(archive));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&D_80141F50, 0, sizeof(D_80141F50));
    archive[0] = 64;
    archive[1] = 128;
    archive[2] = 192;
    TEST_MENU_FRAMES = (u8*)archive;
    D_801406A8 = resources;
    engine_obj.cur_character = selected;
    engine_obj.character_state.bytes[3] = selected;
    engine_obj.unk1 = 3;
    for (i = 0; i < 2; i++) {
        characters[i].active = 0x41;
        characters[i].id = 28;
        characters[i].unk2 = i + 7;
        select_char_init(&characters[i]);
        assert(characters[i].state == 1 && characters[i].unk6 == 0);
    }
    controller_input.pressed = PAD_CONFIRM;
    character_select_state_3(&engine_obj);
    assert(engine_obj.unk1 == 4);
    assert(engine_obj.character_state.bytes[0] == 1);
    controller_input.pressed = 0;
    character_select_state_4(&engine_obj);
    assert(engine_obj.unk2 == 0 && engine_obj.character_state.fields.flags == 0);
    for (i = 0; i < 2; i++) {
        select_char_main(&characters[i]);
        assert(characters[i].unk5 == 15 && characters[i].unk6 == 0);
        select_char_main(&characters[i]);
        assert(characters[i].unk6 == 1);
        assert(characters[i].unk17 == (i == selected ? 3 : 0));
        assert(characters[i].on_screen == 1);
    }
    for (ticks = 0; ticks < 64 && engine_obj.character_state.fields.flags != 3; ticks++) {
        select_char_main(&characters[0]);
        select_char_main(&characters[1]);
        assert(characters[0].unk6 == 1 && characters[1].unk6 == 1);
    }
    assert(ticks == (selected == CHARACTER_X ? 10 : 31));
    assert(engine_obj.character_state.fields.flags == 3);
    character_select_state_4(&engine_obj);
    assert(engine_obj.unk2 == 1 && (u8)engine_obj.character_state.fields.flags == 0x83);
    character_select_state_4(&engine_obj);
    assert(engine_obj.unk1 == 4 && engine_obj.unk2 == 1);
    for (i = 0; i < 2; i++) {
        select_char_main(&characters[i]);
        assert(characters[i].unk6 == 2 && characters[i].unk17 == 4);
        for (ticks = 0; ticks < 32 && characters[i].unk6 == 2; ticks++)
            select_char_main(&characters[i]);
        assert(ticks == (i == CHARACTER_X ? 12 : 13));
        assert(characters[i].unk6 == 3 && characters[i].unk17 == 5);
        assert(characters[i].y_vel.val == 0x80000);
        assert(characters[i].y_pos.val == 160 * 65536);
        for (ticks = 0; ticks < 32 && characters[i].state == 1; ticks++)
            select_char_main(&characters[i]);
        assert(ticks == 28);
        assert(characters[i].state == 2 && characters[i].on_screen == 0);
        assert(characters[i].y_pos.val == -64 * 65536);
        assert(characters[i].x_pos.i.hi == (i == CHARACTER_X ? 32 : 288));
        assert((u8)engine_obj.character_state.fields.flags == (i == 0 ? 0x82 : 0x80));
    }
    character_select_state_4(&engine_obj);
    assert(engine_obj.unk1 == 5 && engine_obj.unk2 == 0 && engine_obj.unk4 == 20);
    return 1;
}

static const struct {
    u8 subtype;
    s32 x, initial_speed, expected_x, expected_speed;
} scroll_boundaries[] = {
    { 2, -111 * 65536 + 0x8000, -0x18000, -112 * 65536, -0x18000 },
    { 2, -112 * 65536 + 0x8000, -0x18000, 432 * 65536, -0x18000 },
    { 2, -111 * 65536 + 0x4000, -0x18000, 432 * 65536 + 0xC000, -0x18000 },
    { 3, 430 * 65536 + 0x8000, 0x18000, 432 * 65536, 0x18000 },
    { 3, 431 * 65536 + 0x8000, 0x18000, -112 * 65536, 0x18000 },
    { 3, 431 * 65536 + 0x4000, 0x18000, 432 * 65536 + 0xC000, 0x18000 },
    { 12, 121 * 65536, 0x40000, 125 * 65536, 0x40000 },
    { 12, 122 * 65536, 0x40000, 126 * 65536, 0 },
    { 12, 123 * 65536, 0x40000, 127 * 65536, 0x40000 },
    { 13, 163 * 65536, -0x40000, 159 * 65536, -0x40000 },
    { 13, 164 * 65536, -0x40000, 160 * 65536, 0 },
    { 13, 165 * 65536, -0x40000, 161 * 65536, -0x40000 },
    { 14, 273 * 65536, 0x40000, 277 * 65536, 0x40000 },
    { 14, 274 * 65536, 0x40000, 278 * 65536, 0 },
    { 14, 275 * 65536, 0x40000, 279 * 65536, 0x40000 },
};

static u32 test_scroll_boundaries(u32 row)
{
    struct MiscObj obj, expected;
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 28;
    obj.state = 1;
    obj.unk2 = scroll_boundaries[row].subtype;
    obj.x_pos.val = scroll_boundaries[row].x;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_vel.val = 12345;
    obj.y_vel.val = 0x8000;
    expected = obj;
    expected.x_vel.val = scroll_boundaries[row].initial_speed;
    expected.unk6 = 1;
    select_char_scroll_text_init(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    expected.x_pos.val = scroll_boundaries[row].expected_x;
    expected.x_vel.val = scroll_boundaries[row].expected_speed;
    expected.y_pos.val = 99 * 65536 + 0xD678;
    select_char_scroll_text_move(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    return 1;
}

static const struct {
    u8 portrait;
    s16 start_x, next_x;
    u8 complete, arrives;
} portrait_slide_cases[] = {
    { 0, 80, 96, 0, 1 },
    { 0, 96, 96, 1, 0 },
    { 0, 112, 128, 0, 0 },
    { 1, 208, 192, 0, 0 },
    { 1, 224, 224, 1, 0 },
    { 1, 240, 224, 0, 1 },
};

static u32 test_portrait_slide(u32 row)
{
    u32 index = row / 2, fraction = row % 2 ? 0x1234 : 0;
    struct MiscObj obj, expected;
    struct EngineObj engine_expected;
    memset(&obj, 0, sizeof(obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    obj.active = 0x41;
    obj.id = 28;
    obj.on_screen = 1;
    obj.state = 1;
    obj.unk2 = portrait_slide_cases[index].portrait;
    obj.unk7 = 0x27;
    obj.x_pos.val = portrait_slide_cases[index].start_x * 65536 + fraction;
    obj.y_pos.val = 100 * 65536 + 0x5678;
    obj.x_vel.val = 12345;
    obj.y_vel.val = 0x8000;
    obj.ext.sel_char.blast_timer = 0x19;
    engine_obj.character_state.bytes[0] = 0x35;
    engine_obj.character_state.bytes[1] = 0x46;
    engine_obj.character_state.bytes[2] = 0xA0;
    engine_obj.character_state.bytes[3] = 0x57;
    engine_obj.unk4 = 0x2468;
    expected = obj;
    engine_expected = engine_obj;
    expected.x_vel.val = obj.unk2 ? -16 * 65536 : 16 * 65536;
    expected.x_pos.val = portrait_slide_cases[index].next_x * 65536 + fraction;
    if (portrait_slide_cases[index].complete) {
        expected.unk6 = 1;
        engine_expected.character_state.bytes[2] = obj.unk2 ? 0xA2 : 0xA1;
    } else {
        expected.y_pos.val = 99 * 65536 + 0xD678;
    }
    select_char_portrait_slide_in(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    if (portrait_slide_cases[index].arrives) {
        expected.unk6 = 1;
        engine_expected.character_state.bytes[2] = obj.unk2 ? 0xA2 : 0xA1;
        select_char_portrait_slide_in(&obj);
        c_test_same_words(&obj, &expected, sizeof(obj));
        c_test_same_words(&engine_obj, &engine_expected, sizeof(engine_obj));
    }
    return 1;
}

static struct MiscObj character_expected_pool[64];

static void character_test_reset(struct MiscObj* obj, u8 character, u8 availability)
{
    u32 i;
    memset(obj, 0, sizeof(*obj));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(misc_objects, 0x5A, sizeof(misc_objects));
    for (i = 0; i < 64; i++)
        misc_objects[i].active = 1;
    if (availability)
        misc_objects[availability == 1 ? 0 : 63].active = 0;
    obj->active = 0x41;
    obj->id = 28;
    obj->unk2 = character + 7;
    obj->on_screen = 1;
    obj->state = 1;
    obj->unk5 = character + 7;
    obj->unk7 = 0x27;
    obj->x_pos.val = 100 * 65536 + 0x1234;
    obj->y_pos.val = 200 * 65536 + 0x5678;
    obj->x_vel.val = 0x18000;
    obj->y_vel.val = -0x24000;
    obj->animation_table = (u32**)(character ? select_char_zero_animations : select_char_x_animations);
    set_animation(obj, 0);
    obj->previous_animation_index = 0;
    engine_obj.cur_character = character;
    engine_obj.character_state.bytes[1] = 0x20;
    engine_obj.unk4 = 0x2468;
    memcpy(character_expected_pool, misc_objects, sizeof(character_expected_pool));
}

static void character_expected_animation(struct MiscObj* obj, u8 index)
{
    const u32* step = (const u32*)obj->animation_table[index];
    obj->unk17 = index;
    obj->previous_animation_index = 0xFF;
    obj->animation_cursor = (u32*)step;
    obj->animation_step.packed = *step;
}

static void character_expected_shot(u8 availability, u8 subtype)
{
    struct MiscObj* shot = &character_expected_pool[availability == 1 ? 0 : 63];
    shot->active = 0x41;
    shot->id = 28;
    shot->unk2 = subtype;
    shot->x_pos.i.hi = 100;
    shot->y_pos.i.hi = 200;
}

static const struct {
    u8 character, selected, confirmed, timer, availability, outcome;
} character_idle_cases[] = {
    { 0, 1, 1, 0, 2, 1 },
    { 1, 0, 1, 1, 0, 1 },
    { 0, 1, 0, 0, 0, 2 },
    { 0, 1, 0, 0, 1, 2 },
    { 0, 1, 0, 0, 2, 2 },
    { 1, 1, 0, 0, 1, 2 },
    { 0, 1, 0, 1, 2, 3 },
    { 1, 1, 0, 2, 2, 3 },
    { 0, 0, 0, 0, 1, 0 },
    { 1, 0, 0, 2, 1, 0 },
};

static u32 test_character_idle(u32 row)
{
    struct MiscObj obj, expected;
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    u8 character = character_idle_cases[row].character;
    u8 availability = character_idle_cases[row].availability;
    u8 outcome = character_idle_cases[row].outcome;
    character_test_reset(&obj, character, availability);
    engine_obj.cur_character = character_idle_cases[row].selected ? character : character ^ 1;
    engine_obj.character_state.bytes[0] = character_idle_cases[row].confirmed;
    obj.ext.sel_char.blast_timer = character_idle_cases[row].timer;
    expected = obj;
    engine_before = engine_obj;
    if (outcome == 1) {
        expected.unk5 = 15;
        expected.unk6 = 0;
    } else if (outcome == 2) {
        expected.unk6 = 1;
        character_expected_animation(&expected, 1);
        if (character == CHARACTER_X && availability)
            character_expected_shot(availability, 10);
    } else if (outcome == 3) {
        expected.ext.sel_char.blast_timer--;
    }
    select_char_character_idle(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(misc_objects, character_expected_pool, sizeof(misc_objects));
    if (row == 6) {
        expected.unk6 = 1;
        character_expected_animation(&expected, 1);
        character_expected_shot(availability, 10);
        select_char_character_idle(&obj);
        c_test_same_words(&obj, &expected, sizeof(obj));
        c_test_same_words(misc_objects, character_expected_pool, sizeof(misc_objects));
    }
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

static const struct {
    u8 character, step, next_step, availability, counter, confirmed, terminal, fires;
    u32 next_word;
} character_shoot_cases[] = {
    { 0, 0, 1, 1, 0, 0, 0, 0, 0x02010001 },
    { 1, 0, 1, 1, 0, 0, 0, 0, 0x02010002 },
    { 1, 1, 2, 0, 0, 0, 0, 1, 0x03010001 },
    { 1, 1, 2, 1, 0, 0, 0, 1, 0x03010001 },
    { 1, 1, 2, 2, 0, 0, 0, 1, 0x03010001 },
    { 1, 2, 3, 1, 0, 0, 0, 0, 0x05010001 },
    { 0, 6, 7, 1, 0, 0, 1, 0, 0 },
    { 0, 6, 7, 1, 1, 0, 1, 0, 0 },
    { 0, 6, 7, 1, 0, 1, 1, 0, 0 },
    { 0, 6, 7, 1, 1, 1, 1, 0, 0 },
    { 1, 16, 17, 1, 0, 0, 1, 0, 0 },
    { 1, 16, 17, 1, 1, 0, 1, 0, 0 },
    { 1, 16, 17, 1, 0, 1, 1, 0, 0 },
    { 1, 16, 17, 1, 1, 1, 1, 0, 0 },
    { 0, 6, 7, 1, 127, 0, 1, 0, 0 },
    { 0, 6, 7, 1, 127, 1, 1, 0, 0 },
    { 1, 16, 17, 1, 127, 0, 1, 0, 0 },
    { 1, 16, 17, 1, 127, 1, 1, 0, 0 },
};

static u32 test_character_shoot(u32 row)
{
    struct MiscObj obj, expected;
    struct EngineObj engine_before;
    struct PlayerObj player_before = g_Player;
    const u32* animation;
    u8 character = character_shoot_cases[row].character;
    u8 availability = character_shoot_cases[row].availability;
    character_test_reset(&obj, character, availability);
    animation = character ? select_char_zero_animations[1] : select_char_x_animations[1];
    obj.unk6 = 1;
    obj.unk17 = 1;
    obj.animation_cursor = (u32*)&animation[character_shoot_cases[row].step];
    obj.animation_step.packed = animation[character_shoot_cases[row].step];
    obj.previous_animation_index = obj.animation_step.fields.frame_index;
    obj.animation_step.fields.duration = 1;
    obj.animation_step.fields.event = 0;
    obj.ext.sel_char.unk54 = character_shoot_cases[row].counter;
    obj.ext.sel_char.blast_timer = 7;
    engine_obj.character_state.bytes[0] = character_shoot_cases[row].confirmed;
    expected = obj;
    engine_before = engine_obj;
    if (character_shoot_cases[row].fires && availability)
        character_expected_shot(availability, 11);
    if (character_shoot_cases[row].terminal) {
        expected.unk6 = 0;
        expected.ext.sel_char.blast_timer = character_shoot_cases[row].counter ? 150 : 90;
        expected.ext.sel_char.unk54 = (s8)(character_shoot_cases[row].counter + 1);
        if (character_shoot_cases[row].confirmed)
            expected.unk5 = 15;
        character_expected_animation(&expected, 0);
    } else {
        expected.animation_cursor = (u32*)&animation[character_shoot_cases[row].next_step];
        expected.animation_step.packed = character_shoot_cases[row].next_word;
    }
    select_char_character_shoot(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(misc_objects, character_expected_pool, sizeof(misc_objects));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    return 1;
}

void character_select_state_3(struct EngineObj*);
static struct MiscObj owner, expected_owner, pool[64];
static s32 frames[128];
static u32 resources[3] = { 0x10000, 0x18000, 0x20000 };
static u32 real_burst(u32 row)
{
    struct EngineObj engine;
    struct PlayerObj player = g_Player;
    struct MainBssState main = main_bss_state;
    struct ControllerInput input;
    u32 character = row == 1, i;
    u16 rng = cur_random;
    u32** table = character ? select_char_zero_animations : select_char_x_animations;
    memset(&engine_obj, 0, sizeof(engine_obj));
    engine_obj.state = 1;
    engine_obj.unk1 = 3;
    engine_obj.stage = 14;
    engine_obj.substage = 1;
    engine_obj.cur_character = character;
    engine_obj.character_state.bytes[3] = character;
    memset(&controller_input, 0, sizeof(controller_input));
    memset(&owner, 0, sizeof(owner));
    memset(misc_objects, 0, sizeof(misc_objects));
    memset(frames, 0, sizeof(frames));
    frames[0] = 64;
    frames[1] = 128;
    frames[2] = 192;
    TEST_MENU_FRAMES = (u8*)frames;
    D_801406A8 = resources;
    owner.active = 0x41;
    owner.id = 28;
    owner.unk2 = 7 + character;
    SelectACharacterUpdate(&owner);
    assert(owner.state == 1 && owner.unk6 == 0 && owner.x_pos.i.hi == (character ? 288 : 32) && owner.y_pos.i.hi == 160);
    SelectACharacterUpdate(&owner);
    assert(owner.unk6 == 1 && owner.unk17 == 1 && owner.animation_step.packed == (character ? 0x01010004u : 0x01010001u));
    if (character) {
        for (i = 0; i < 6; i++) {
            assert(!misc_objects[0].active);
            SelectACharacterUpdate(&owner);
        }
        assert(owner.animation_step.packed == 0x03010001 && owner.animation_cursor == table[1] + 2);
    }
    assert(misc_objects[0].active == 0x41 && misc_objects[0].id == 28 && misc_objects[0].unk2 == (character ? 11 : 10) && misc_objects[0].state == 0 && misc_objects[0].x_pos.i.hi == owner.x_pos.i.hi && misc_objects[0].y_pos.i.hi == 160);
    if (row == 2) {
        controller_input.pressed = PADLright;
        character_select_state_3(&engine_obj);
        assert(engine_obj.cur_character == CHARACTER_ZERO && engine_obj.character_state.bytes[3] == CHARACTER_ZERO);
        controller_input.pressed = 0;
    }
    engine = engine_obj;
    input = controller_input;
    expected_owner = owner;
    memcpy(pool, misc_objects, sizeof(pool));
    if (row == 2) {
        expected_owner.animation_cursor = table[1] + 1;
        expected_owner.animation_step.packed = 0x02010001;
        SelectACharacterUpdate(&owner);
    } else {
        struct MiscObj* expected = &pool[0];
        expected->state = 1;
        expected->unk40 = resources[character ? 0 : 2] >> 7;
        expected->unk3C = (u8*)frames + (character ? 64 : 192);
        expected->unk42 = character ? 0x7800 : 0x7840;
        expected->unk15 = character ? 0 : 0x40;
        expected->animation_table = table;
        expected->animation_cursor = table[2];
        expected->animation_step.packed = character ? 0x04010001 : 0x09010002;
        expected->unk17 = 2;
        expected->previous_animation_index = 0xFF;
        expected->unk16 = 3;
        expected->bg_offset = -1;
        expected->unk5 = 10 + character;
        SelectACharacterUpdate(&misc_objects[0]);
    }
    c_test_same_words(&owner, &expected_owner, sizeof(owner));
    c_test_same_words(misc_objects, pool, sizeof(pool));
    c_test_same_words(&engine_obj, &engine, sizeof(engine));
    c_test_same_words(&g_Player, &player, sizeof(player));
    c_test_same_words(&main_bss_state, &main, sizeof(main));
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed);
    assert(cur_random == rng && D_801406A8 == resources && TEST_MENU_FRAMES == (u8*)frames);
    assert(resources[0] == 0x10000 && resources[1] == 0x18000 && resources[2] == 0x20000);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i < 3 ? (s32)(64 + i * 64) : 0));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "character_idle", 0, 0, COUNT(character_idle_cases), test_character_idle },
    { "character_shoot", 0, 0, COUNT(character_shoot_cases), test_character_shoot },
    { "portrait_slide", 0, 0, COUNT(portrait_slide_cases) * 2, test_portrait_slide },
    { "scroll_boundaries", 0, 0, COUNT(scroll_boundaries), test_scroll_boundaries },
    { "character_exit_lifecycle", 0, 0, 2, test_character_exit_lifecycle },
    { "select_character_text_context", NULL, select_character_text_context_cases_expected, COUNT(select_character_text_context_cases_expected), select_character_text_context_cases_row },
    { "select_char_portrait_bounce_1", 0, 0, 7, test_select_char_portrait_bounce_1 },
    { "pool_full", pool_full_cases, pool_full_cases_expected, COUNT(pool_full_cases), 0 },
    { "real_character_select_births_and_switch_during_X_shooting", NULL, NULL, 3, real_burst },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(character_idle_cases) + COUNT(character_shoot_cases) + COUNT(portrait_slide_cases) * 2 + COUNT(scroll_boundaries) + 2 + COUNT(select_character_text_context_cases_expected) + 7 + COUNT(pool_full_cases) + 3;
