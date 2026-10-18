#include "test_runtime.h"
#include "main/quads/quad_15_sigma_beam.h"

#undef main_bss_state

void sigma_beam_extend(struct QuadObj*);
void sigma_beam_fade(struct QuadObj*);
void sigma_beam_init(struct QuadObj*);
extern s8 sigma_beam_sweep_speeds[4];
extern void* sigma_animations[44];
static struct ShotObj shots_expected[32];
static u32 fade(u32 row)
{
    struct MainObj owner, owner_before;
    struct QuadObj obj, expected;
    struct PlayerObj player_before;
    struct EngineObj engine_before;
    struct MainBssState main_before;
    u32 type = row % 4, free = row / 4 % 2, character = row / 8, i, duration = character ? 70 : 210;
    engine_obj.stage = 12;
    engine_obj.substage = 1;
    engine_obj.cur_character = character;
    engine_before = engine_obj;
    g_Player.bg_offset = 0;
    player_before = g_Player;
    main_bss_state.frame_counter = 2;
    memset(&owner, 0, sizeof(owner));
    owner.active = 0x41;
    owner.id = 68;
    owner.state = 1;
    owner.unk2 = 1;
    owner.hp = 48;
    owner.animation_table = (const u8* const*)sigma_animations;
    owner.unk5 = 7;
    owner.unk6 = 2;
    owner.unk15 = type >= 2 ? 0x40 : 0;
    owner.x_pos.i.hi = 1361;
    owner.y_pos.i.hi = 451;
    owner_before = owner;
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    for (i = 0; i < COUNT(shot_objects); i++)
        shot_objects[i].active = 1;
    memset(&obj, 0, sizeof(obj));
    obj.active = 1;
    obj.id = 15;
    obj.unk2 = type;
    obj.unk5C = PLAYER_OBJECT(&owner);
    owner.ext.main_68.effect = (struct EffectObj*)&obj;
    owner.ext.main_68.scythe = MAIN_OBJECT(&shot_objects[0]);
    shot_objects[0].active = 0x41;
    shot_objects[0].id = 46;
    shot_objects[0].state = 1;
    shot_objects[0].unk7C = WEAPON_OBJECT(&owner);
    sigma_beam_init(&obj);
    for (i = 0; i < 17; i++) {
        main_bss_state.frame_counter++;
        sigma_beam_extend(&obj);
    }
    for (i = 0; i < 45; i++) {
        main_bss_state.frame_counter++;
        sigma_beam_sweep(&obj);
    }
    assert(obj.unk5 == 2 && obj.ext.unk_ext4.unk3C == duration && obj.vertices[2].y.i.hi == 68 && obj.vertices[2].x.i.hi == 2 + sigma_beam_sweep_speeds[type] * 44 && main_bss_state.frame_counter == 64);
    for (i = 0; i < 3; i++) {
        main_bss_state.frame_counter++;
        sigma_beam_fade(&obj);
    }
    main_bss_state.frame_counter++;
    assert(obj.ext.unk_ext4.unk3C == duration - 3 && main_bss_state.frame_counter == 68);
    shot_objects[31].active = free ? 0 : 1;
    memcpy(shots_expected, shot_objects, sizeof(shots_expected));
    main_before = main_bss_state;
    owner_before = owner;
    expected = obj;
    expected.ext.unk_ext4.unk3C--;
    if (free) {
        struct ShotObj* s = &shots_expected[31];
        s->active = 0x41;
        s->id = 46;
        s->unk2 = 8;
        s->unk7C = (void*)&obj;
    }
    sigma_beam_fade(&obj);
    c_test_same_words(&obj, &expected, sizeof(obj));
    c_test_same_words(shot_objects, shots_expected, sizeof(shots_expected));
    c_test_same_words(&owner, &owner_before, sizeof(owner));
    c_test_same_words(&g_Player, &player_before, sizeof(g_Player));
    c_test_same_words(&engine_obj, &engine_before, sizeof(engine_obj));
    c_test_same_words(&main_bss_state, &main_before, sizeof(main_bss_state));
    return 1;
}

const struct CTestGroup c_test_groups[] = {
    { "own_Sigma_eye_beam_extend_sweep_to_periodic_fade_full_shot_pool", NULL, NULL, 16, fade },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 16;
