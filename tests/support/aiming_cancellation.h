#ifndef MMX4_TESTS_AIMING_CANCELLATION_H
#define MMX4_TESTS_AIMING_CANCELLATION_H

static u32 cancellation_case(u32 kind, u32 mode, u32 observation)
{
    struct WeaponObj weapon;
    struct QuadObj beam;
    struct VisualObj scope;
    struct MainObj owner, before_owner;
    struct PlayerObj expected_player;
    struct BaseObj* base;
    u32 i;
    memset(&weapon, 0, sizeof(weapon));
    memset(&beam, 0, sizeof(beam));
    memset(&scope, 0, sizeof(scope));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    g_Player.weapon = (kind == 1 && mode == 1) || (kind == 2 && mode == 2) ? 0 : 6;
    g_Player.input_locked = kind == 2 && mode == 0;
    g_Player.capsule_state = (kind == 1 && mode == 0) || (kind == 2 && mode == 1);
    g_Player.actions_reset = (kind == 1 && mode == 2) || (kind == 2 && mode == 4);
    g_Player.hp = kind == 0 || kind == 3 || ((kind == 1 || kind == 2) && mode == 3) ? 0 : 16;
    g_Player.special_shot_count = 6;
    if (kind == 1)
        g_Player.weapon_06_slots[0] = &owner;
    owner.active = (kind == 1 && mode == 4) || (kind == 2 && mode == 6) ? 0 : 1;
    owner.hp = 16;
    owner.x_pos.val = 300 * 65536 + 0x3456;
    owner.y_pos.val = 400 * 65536 + 0x4567;
    before_owner = owner;
    expected_player = g_Player;
    if (kind == 1) {
        expected_player.weapon_06_slots[0] = NULL;
        expected_player.special_shot_count = 5;
    }
    weapon.active = 1;
    weapon.id = 6;
    weapon.unk2 = kind == 0 ? 3 : 0;
    weapon.state = kind == 1 && mode == 5 ? 3 : 1;
    weapon.on_screen = 1;
    weapon.owner = PLAYER_OBJECT(&owner);
    weapon.x_pos.val = 100 * 65536 + 0x1234;
    weapon.y_pos.val = 200 * 65536 + 0x2468;
    beam.active = 0x83;
    beam.id = 9;
    beam.state = 1;
    beam.on_screen = 1;
    beam.unk5C = PLAYER_OBJECT(&owner);
    beam.x_pos.val = weapon.x_pos.val;
    beam.y_pos.val = weapon.y_pos.val;
    scope.active = 1;
    scope.id = 0x18;
    scope.state = 1;
    scope.on_screen = 1;
    scope.x_pos.val = weapon.x_pos.val;
    scope.y_pos.val = weapon.y_pos.val;
    if (kind <= 1) {
        func_800961B0(&weapon);
        base = BASE_OBJECT(&weapon);
    } else if (kind == 2) {
        aiming_laser_beam_update(&beam);
        base = BASE_OBJECT(&beam);
    } else {
        aiming_laser_scope_update(&scope);
        base = BASE_OBJECT(&scope);
    }
    for (i = 0; i < sizeof(owner); i++)
        assert(((u8*)&owner)[i] == ((u8*)&before_owner)[i]);
    for (i = 0; i < sizeof(g_Player); i++)
        assert(((u8*)&g_Player)[i] == ((u8*)&expected_player)[i]);
    assert(weapon.owner == PLAYER_OBJECT(&owner) && beam.unk5C == PLAYER_OBJECT(&owner));
    assert(weapon.unk50 == NULL && beam.ext.unk_ext3.unk38 == 0);
    assert(engine_obj.unkF == 0);
    if (kind == 1) {
        assert(base->x_pos.val == owner.x_pos.val && base->y_pos.val == owner.y_pos.val);
    } else {
        assert(base->x_pos.val == 100 * 65536 + 0x1234 && base->y_pos.val == 200 * 65536 + 0x2468);
    }
    if (observation == 0)
        return (u8)base->active | ((u32)(u8)base->id << 8) | ((u32)(u8)base->state << 16) | ((u32)(u8)base->on_screen << 24);
    if (observation == 1)
        return (u32)base->x_pos.val;
    if (observation == 2)
        return (u32)base->y_pos.val;
    return (u8)g_Player.special_shot_count;
}
#define AIMING_CANCEL_OBSERVE(kind, mode, field)                          \
    static u32 aiming_cancellation_cancel_##kind##_##mode##_##field(void) \
    {                                                                     \
        return cancellation_case(kind, mode, field);                      \
    }
#define AIMING_CANCEL_MODE(kind, mode) AIMING_CANCEL_OBSERVE(kind, mode, 0) AIMING_CANCEL_OBSERVE(kind, mode, 1) AIMING_CANCEL_OBSERVE(kind, mode, 2) AIMING_CANCEL_OBSERVE(kind, mode, 3)
#define AIMING_CANCEL_SIX(kind) AIMING_CANCEL_MODE(kind, 0) AIMING_CANCEL_MODE(kind, 1) AIMING_CANCEL_MODE(kind, 2) AIMING_CANCEL_MODE(kind, 3) AIMING_CANCEL_MODE(kind, 4) AIMING_CANCEL_MODE(kind, 5)
#define AIMING_CANCEL_ENTRY(kind, mode, field) aiming_cancellation_cancel_##kind##_##mode##_##field,
#define AIMING_CANCEL_ENTRIES(kind, mode) AIMING_CANCEL_ENTRY(kind, mode, 0) AIMING_CANCEL_ENTRY(kind, mode, 1) AIMING_CANCEL_ENTRY(kind, mode, 2) AIMING_CANCEL_ENTRY(kind, mode, 3)
#define AIMING_CANCEL_SIX_ENTRIES(kind) AIMING_CANCEL_ENTRIES(kind, 0) AIMING_CANCEL_ENTRIES(kind, 1) AIMING_CANCEL_ENTRIES(kind, 2) AIMING_CANCEL_ENTRIES(kind, 3) AIMING_CANCEL_ENTRIES(kind, 4) AIMING_CANCEL_ENTRIES(kind, 5)
#endif
