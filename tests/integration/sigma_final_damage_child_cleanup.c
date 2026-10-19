#include "test_runtime.h"
#include "main/player_animations.h"
#include "main/player_weapon.h"
#include "main/player_check.h"
#include "main/player.h"
#include "main/objects.h"
#include "main/player_enter.h"
void player_update_shooting(struct PlayerObj* self);
void sigma_final_show_upper_start(struct MainObj*);
void sigma_final_update(struct MainObj*);
void sigma_final_shot_update(struct ShotObj*);
void sigma_final_fx_update(struct MiscObj*);
void charge_muzzle_flash_update(struct VisualObj*);
void charge_shot_update(struct WeaponObj*);
extern void* sigma_final_animations[];
extern void* D_8013B8B4;
extern u8 D_8013B898[4], D_8013B89C[4], D_8013B8A4[4];
static struct MainObj owner, owner_before;
static struct ShotObj shots[32];
static struct MiscObj misc[64];
static struct WeaponObj weapons[16];
static struct VisualObj visuals[32];
static u32 frames[64], gfx[64];
static u8 commands[8], collision_before[12];
static u32 lethal_cleanup(u32 row)
{
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct ShotObj* shot;
    struct MiscObj* effect;
    struct Unk_unk68* body;
    void* guard;
    u8 *old_frames = TEST_SPRITE_FRAMES, *old_gfx = TEST_PLAYER_GFX, *old_commands = D_80141F50[2];
    u16 rng;
    u8 dirty;
    u32 i;
    (void)row;
    c_test_zero_words((u32*)&owner, sizeof(owner) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    for (i = 0; i < 8; i++)
        gfx[i] = frames[i] = 64;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    D_80141F50[2] = commands;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    cur_random = 0x1234;
    D_8013B8B8 = 0;
    for (i = 0; i < 4; i++)
        D_8013B898[i] = D_8013B89C[i] = D_8013B8A4[i] = 0;
    background_objects[0].x_pos.i.hi = 1200;
    background_objects[0].y_pos.i.hi = 512;
    engine_obj.stage = 12;
    engine_obj.substage = 1;
    owner.active = 0x41;
    owner.id = 74;
    owner.state = 1;
    owner.unk5 = 4;
    owner.unk16 = 6;
    owner.unk40 = 0xB0;
    owner.ext.main_74.pattern_index = 7;
    engine_obj.boss_ptr = &owner;
    engine_obj.enable_boss = 1;
    owner.ext.main_74.upper_health = 1;
    owner.ext.main_74.lower_health = 48;
    owner.animation_table = (const u8* const*)sigma_final_animations;
    owner.sprite_frames = (u8*)frames;
    owner.unk42 = 0x7804;
    SP_CUR_MAIN_OBJ = &owner;
    sigma_final_show_upper_start(&owner);
    assert(owner.hp == 1 && owner.ext.main_74.target == 1 && owner.unk6 == 1 && owner.ext.main_74.death_kind == 0);
    shot = find_free_shot_obj();
    assert(shot == &shot_objects[0]);
    shot->active = 0x41;
    shot->id = 54;
    shot->unk2 = 0;
    shot->unk7C = WEAPON_OBJECT(&owner);
    shot->x_pos = owner.x_pos;
    shot->y_pos = owner.y_pos;
    sigma_final_shot_update(shot);
    assert(shot->state == 1 && shot->unk5 == 2);
    effect = find_free_misc_obj();
    assert(effect == &misc_objects[0]);
    effect->active = 0x41;
    effect->id = 55;
    effect->unk2 = 0;
    effect->ext.misc_55.owner = &owner;
    sigma_final_fx_update(effect);
    assert(effect->state == 1 && effect->animation_table == (u32**)sigma_final_animations);
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = 1348;
    g_Player.y_pos.i.hi = 575;
    g_Player.unk15 = 0x40;
    g_Player.animation_table = (u32**)D_80119DF0;
    player_enter_idle(&g_Player);
    g_Player.input.buttons.held = PLAYER_INPUT_SHOOT;
    for (i = 0; i < 25; i++)
        player_charge_shoot_button(&g_Player);
    assert(g_Player.charge_state[0] == PLAYER_CHARGE_PARTIAL);
    g_Player.input.buttons.previous = PLAYER_INPUT_SHOOT;
    g_Player.input.buttons.held = 0;
    player_update_shot_types(&g_Player);
    player_update_shooting(&g_Player);
    assert(g_Player.attacking == 1 && g_Player.shot_fired == 1 && g_Player.last_shot_type == 9 && visual_objects[0].id == 2);
    player_enter_idle(&g_Player);
    charge_muzzle_flash_update(&visual_objects[0]);
    for (i = 0; i < 16 && weapon_objects[0].active == 0; i++)
        charge_muzzle_flash_update(&visual_objects[0]);
    assert(i == 4 && weapon_objects[0].active == 0x21 && weapon_objects[0].id == 9 && visual_objects[0].unk5 == 1);
    charge_shot_update(&weapon_objects[0]);
    assert(weapon_objects[0].state == 1 && weapon_objects[0].x_pos.i.hi == 1386 && weapon_objects[0].y_pos.i.hi == 566);
    sigma_final_update(&owner);
    assert(owner.hp == 0 && owner.state == 2 && owner.ext.main_74.death_kind == 1 && weapon_objects[0].unk98 == 0);
    c_test_copy_words((u32*)shots, (u32*)shot_objects, sizeof(shots) / 4);
    c_test_copy_words((u32*)misc, (u32*)misc_objects, sizeof(misc) / 4);
    c_test_copy_words((u32*)weapons, (u32*)weapon_objects, sizeof(weapons) / 4);
    c_test_copy_words((u32*)visuals, (u32*)visual_objects, sizeof(visuals) / 4);
    c_test_zero_words((u32*)&shots[0], 2);
    c_test_zero_words((u32*)&misc[0], 2);
    owner_before = owner;
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    memcpy(collision_before, D_8013B898, 4);
    memcpy(collision_before + 4, D_8013B89C, 4);
    memcpy(collision_before + 8, D_8013B8A4, 4);
    body = D_8013B8B0;
    guard = D_8013B8B4;
    rng = cur_random;
    dirty = need_palette_load;
    sigma_final_shot_update(shot);
    sigma_final_fx_update(effect);
    assert(c_test_word_difference((u32*)shot_objects, (u32*)shots, sizeof(shots) / 4) == 0 && c_test_word_difference((u32*)misc_objects, (u32*)misc, sizeof(misc) / 4) == 0);
    assert(c_test_word_difference((u32*)weapon_objects, (u32*)weapons, sizeof(weapons) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0);
    assert(c_test_word_difference((u32*)&owner, (u32*)&owner_before, sizeof(owner) / 4) == 0 && c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0 && c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && need_palette_load == dirty && D_8013B8B8 == 0 && D_8013B8B0 == body && D_8013B8B4 == guard && SP_CUR_MAIN_OBJ == &owner);
    for (i = 0; i < 4; i++)
        assert(D_8013B898[i] == collision_before[i] && D_8013B89C[i] == collision_before[4 + i] && D_8013B8A4[i] == collision_before[8 + i]);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i < 8 ? 64u : 0) && gfx[i] == (i < 8 ? 64u : 0));
    for (i = 0; i < COUNT(commands); i++)
        assert(commands[i] == 0);
    assert(TEST_SPRITE_FRAMES == (u8*)frames && TEST_PLAYER_GFX == (u8*)gfx && D_80141F50[2] == commands && D_8013E198[1] == -1 && D_8013E198[2] == -1);
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    SP_CUR_MAIN_OBJ = current;
    TEST_SPRITE_FRAMES = old_frames;
    TEST_PLAYER_GFX = old_gfx;
    D_80141F50[2] = old_commands;
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "late_fight_HP1_actual_25_tick_Buster_hit_sets_flag_before_child_cleanup", NULL, NULL, 1, lethal_cleanup } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
