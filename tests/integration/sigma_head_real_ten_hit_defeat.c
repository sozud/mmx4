#include "test_runtime.h"
#include "main/player_animations.h"
#include "main/sprite_animations.h"
#include "main/player_weapon.h"
#include "main/player_check.h"
#include "main/player.h"
#include "main/objects.h"
#include "main/player_enter.h"
void player_update_shooting(struct PlayerObj* self);
void sigma_head_update(struct ShotObj*);
void charge_muzzle_flash_update(struct VisualObj*);
void charge_shot_update(struct WeaponObj*);
extern void* sigma_final_animations[];
static struct MainObj owner, owner_before;
static struct ShotObj shots[32];
static struct WeaponObj weapons[16];
static struct VisualObj visuals[32];
static u32 gfx[64], frames[64];
static u32 zero_difference(const u32* p, u32 count)
{
    u32 different = 0;
    while (count >= 8) {
        different |= p[0] | p[1] | p[2] | p[3] | p[4] | p[5] | p[6] | p[7];
        p += 8;
        count -= 8;
    }
    while (count--)
        different |= *p++;
    return different;
}
static u32 ten_real_hits(u32 row)
{
    struct PlayerObj player, entity;
    struct EngineObj engine;
    struct MainBssState main_before;
    struct BackgroundObj cameras[3];
    struct ControllerInput input;
    struct MainObj* current = SP_CUR_MAIN_OBJ;
    struct ShotObj* head;
    struct VisualObj* flash;
    s16 contact[2] = { -1, -1 };
    u8 *old_gfx = TEST_PLAYER_GFX, *old_frames = TEST_SPRITE_FRAMES;
    u16 rng;
    u8 dirty;
    u32 hit, i;
    (void)row;
    c_test_zero_words((u32*)&owner, sizeof(owner) / 4);
    c_test_zero_words((u32*)&g_Player, sizeof(g_Player) / 4);
    c_test_zero_words((u32*)&engine_obj, sizeof(engine_obj) / 4);
    c_test_zero_words((u32*)background_objects, sizeof(background_objects) / 4);
    c_test_zero_words((u32*)shot_objects, sizeof(shot_objects) / 4);
    c_test_zero_words((u32*)weapon_objects, sizeof(weapon_objects) / 4);
    c_test_zero_words((u32*)visual_objects, sizeof(visual_objects) / 4);
    c_test_zero_words((u32*)misc_objects, sizeof(misc_objects) / 4);
    for (i = 0; i < 8; i++)
        frames[i] = gfx[i] = 64;
    TEST_PLAYER_GFX = (u8*)gfx;
    TEST_SPRITE_FRAMES = (u8*)frames;
    for (i = 0; i < 6; i++)
        D_8013E198[i] = -1;
    cur_random = 0x1234;
    background_objects[0].x_pos.i.hi = -160;
    background_objects[0].y_pos.i.hi = -120;
    engine_obj.stage = 12;
    engine_obj.substage = 1;
    owner.active = 0x41;
    owner.id = 74;
    owner.state = 1;
    owner.unk16 = 6;
    owner.unk40 = 0xB0;
    owner.animation_table = (const u8* const*)sigma_final_animations;
    owner.sprite_frames = (u8*)frames;
    owner.unk42 = 0x7804;
    SP_CUR_MAIN_OBJ = &owner;
    head = find_free_shot_obj();
    assert(head == &shot_objects[0]);
    head->active = 0x41;
    head->id = 53;
    head->unk2 = 0;
    head->unk7C = WEAPON_OBJECT(&owner);
    sigma_head_update(head);
    assert(head->state == 1 && head->unk5 == 3 && head->unk5C == 48 && head->x_pos.val == 0 && head->y_pos.val == 0);
    g_Player.active = 0x41;
    g_Player.state = PLAYER_STATE_NORMAL;
    g_Player.hp = 24;
    g_Player.x_pos.i.hi = -38;
    g_Player.y_pos.i.hi = 9;
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
    player_enter_idle(&g_Player);
    assert(g_Player.shot_type == 9 && g_Player.attacking == 1 && g_Player.shot_count == 1);
    for (hit = 0; hit < 10; hit++) {
        if (hit != 0)
            player_fire_charged_buster(&g_Player);
        flash = &visual_objects[hit * 2];
        assert(flash->active == 0x21 && flash->id == 2 && flash->unk2 == 9 && flash->state == 0);
        charge_muzzle_flash_update(flash);
        for (i = 0; i < 4; i++)
            charge_muzzle_flash_update(flash);
        assert(weapon_objects[hit].active == 0x21 && weapon_objects[hit].id == 9 && weapon_objects[hit].state == 0);
        charge_shot_update(&weapon_objects[hit]);
        assert(weapon_objects[hit].state == 1 && weapon_objects[hit].x_pos.val == 0 && weapon_objects[hit].y_pos.val == 0);
        if (hit == 9)
            break;
        sigma_head_update(head);
        assert(head->unk5C == 48 - (hit + 1) * 5 && head->unk5 == 3 && head->state == 1 && weapon_objects[hit].unk98 == 1);
        charge_shot_update(&weapon_objects[hit]);
        assert(weapon_objects[hit].state == 3 && weapon_objects[hit].on_screen == 0 && weapon_objects[hit].unk50 == NULL);
    }
    assert(head->unk5C == 3 && g_Player.shot_count == 1);
    c_test_copy_words((u32*)shots, (u32*)shot_objects, sizeof(shots) / 4);
    c_test_copy_words((u32*)weapons, (u32*)weapon_objects, sizeof(weapons) / 4);
    c_test_copy_words((u32*)visuals, (u32*)visual_objects, sizeof(visuals) / 4);
    owner_before = owner;
    player = g_Player;
    entity = g_Entity;
    engine = engine_obj;
    main_before = main_bss_state;
    input = controller_input;
    c_test_copy_words((u32*)cameras, (u32*)background_objects, sizeof(cameras) / 4);
    rng = cur_random;
    dirty = need_palette_load;
    shots[0].unk5C = 48;
    shots[0].unk42 |= 0x8000;
    memcpy(&weapons[9].unk80, contact, sizeof(contact));
    visuals[19].active = 0x21;
    visuals[19].id = 3;
    visuals[19].unk2 = 3;
    visuals[19].animation_table = D_8011BF40;
    visuals[19].unk42 = 0x7802;
    visuals[19].unk3C = (u8*)frames + 64;
    visuals[19].x_pos.i.hi = visuals[19].y_pos.i.hi = -1;
    for (i = 0; i < 6; i++) {
        struct VisualObj* v = &visuals[20 + i];
        v->active = 0x21;
        v->id = 4;
        v->unk5C.value = i == 0 ? 0 : i == 1 ? 1
                                             : -1;
        v->x_pos.i.hi = (i & 1) ? -15 : 15;
        v->y_pos.i.hi = i < 2 ? 20 : i < 4 ? 0
                                           : -20;
        v->unk16 = 1;
    }
    sigma_head_update(head);
    assert(c_test_word_difference((u32*)shot_objects, (u32*)shots, sizeof(shots) / 4) == 0 && c_test_word_difference((u32*)weapon_objects, (u32*)weapons, sizeof(weapons) / 4) == 0 && c_test_word_difference((u32*)visual_objects, (u32*)visuals, sizeof(visuals) / 4) == 0 && zero_difference((u32*)misc_objects, sizeof(misc_objects) / 4) == 0);
    assert(c_test_word_difference((u32*)&owner, (u32*)&owner_before, sizeof(owner) / 4) == 0 && c_test_word_difference((u32*)&g_Player, (u32*)&player, sizeof(player) / 4) == 0 && c_test_word_difference((u32*)&g_Entity, (u32*)&entity, sizeof(entity) / 4) == 0 && c_test_word_difference((u32*)&engine_obj, (u32*)&engine, sizeof(engine) / 4) == 0 && c_test_word_difference((u32*)&main_bss_state, (u32*)&main_before, sizeof(main_before) / 4) == 0 && c_test_word_difference((u32*)background_objects, (u32*)cameras, sizeof(cameras) / 4) == 0);
    assert(controller_input.held == input.held && controller_input.previous == input.previous && controller_input.pressed == input.pressed && cur_random == rng && need_palette_load == dirty && SP_CUR_MAIN_OBJ == &owner);
    for (i = 0; i < COUNT(frames); i++)
        assert(frames[i] == (i < 8 ? 64u : 0) && gfx[i] == (i < 8 ? 64u : 0));
    for (i = 0; i < 6; i++)
        assert(D_8013E198[i] == -1);
    assert(TEST_PLAYER_GFX == (u8*)gfx && TEST_SPRITE_FRAMES == (u8*)frames);
    SP_CUR_MAIN_OBJ = current;
    TEST_PLAYER_GFX = old_gfx;
    TEST_SPRITE_FRAMES = old_frames;
    return 1;
}
const struct CTestGroup c_test_groups[] = { { "head_ctor_HP48_nine_real5damage_hits_then_tenth_lethal_hit", NULL, NULL, 1, ten_real_hits } };
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 1;
