#ifndef MMX4_TESTS_CHARGED_DISPATCH_H
#define MMX4_TESTS_CHARGED_DISPATCH_H

static u8 hitbox = 0x5A;
static u8 sound_entries[0x78];

static u32 dispatch_case(u32 kind, u32 mode, u32 observation)
{
    struct WeaponObj obj, owner, before_owner;
    u8* saved_sound;
    u8 selected = kind == 0 ? 1 : kind == 1 ? 2
        : kind == 2                         ? 6
                                            : 7;
    u32 i, actual;

    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(sound_entries, 0, sizeof(sound_entries));
    saved_sound = D_80141F50[0];
    D_80141F50[0] = sound_entries;
    g_Player.weapon = mode == 3 || mode == 6 ? 0 : selected;
    g_Player.input_locked = mode == 1;
    g_Player.capsule_state = mode == 2;
    g_Player.hp = mode == 4 ? 0 : 16;
    g_Player.actions_reset = mode == 5;
    g_Player.shot_count = 5;
    g_Player.special_shot_count = 6;
    obj.active = 0x91;
    obj.id = kind == 0 ? 0xA : kind == 1 ? 0xB
        : kind == 2                      ? 0xF
                                         : 0x10;
    obj.on_screen = 1;
    obj.state = kind == 3 ? 2 : 1;
    obj.unk2 = kind == 0 ? 2 : kind == 3 ? 1
                                         : 0;
    if (mode == 6)
        obj.unk2 = kind == 1 ? 1 : 0;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x2468;
    obj.unk50 = &hitbox;
    owner.active = 1;
    obj.owner = PLAYER_OBJECT(&owner);
    before_owner = owner;
    if (kind == 1)
        obj.ext.raw[2] = 2;
    if (kind == 0)
        lightning_web_charged_update(&obj);
    if (kind == 1)
        frost_tower_charged_update(&obj);
    if (kind == 2)
        aiming_laser_charged_update(&obj);
    if (kind == 3)
        double_cyclone_charged_update(&obj);

    assert(obj.x_pos.val == 100 * 65536 + 0x1234);
    assert(obj.y_pos.val == 200 * 65536 + 0x2468);
    assert(obj.owner == PLAYER_OBJECT(&owner));
    for (i = 0; i < sizeof(owner); i++)
        assert(((u8*)&owner)[i] == ((u8*)&before_owner)[i]);
    assert(hitbox == 0x5A);
    assert((u8)obj.id == (mode != 0 ? 0 : kind == 0 ? 0xA
                   : kind == 1                      ? 0xB
                   : kind == 2                      ? 0xF
                                                    : 0x10));
    assert(obj.unk50 == (mode != 0 || kind == 3 ? NULL : &hitbox));
    assert(g_Player.weapon == (mode == 3 || mode == 6 ? 0 : selected));
    assert(g_Player.input_locked == (mode == 1));
    assert(g_Player.capsule_state == (mode == 2));
    assert(g_Player.hp == (mode == 4 ? 0 : 16));
    assert(g_Player.actions_reset == (mode == 5));
    if (kind == 1)
        assert(obj.ext.raw[2] == (mode == 0 ? 1 : 2));
    for (i = 0; i < COUNT(sound_entries); i++)
        assert(sound_entries[i] == 0);
    D_80141F50[0] = saved_sound;
    if (observation == 0)
        actual = (u8)obj.active | ((u32)(u8)obj.state << 8) | ((u32)(u8)obj.unk2 << 16) | ((u32)(u8)obj.on_screen << 24);
    else
        actual = (u8)g_Player.shot_count | ((u32)(u8)g_Player.special_shot_count << 8);
    return actual;
}
#define CHARGED_OBSERVE(kind, mode, field)                              \
    static u32 charged_dispatch_charged_##kind##_##mode##_##field(void) \
    {                                                                   \
        return dispatch_case(kind, mode, field);                        \
    }
#define CHARGED_CASE(kind, mode) CHARGED_OBSERVE(kind, mode, 0) CHARGED_OBSERVE(kind, mode, 1)
#define CHARGED_BASIC(kind) CHARGED_CASE(kind, 0) CHARGED_CASE(kind, 1) CHARGED_CASE(kind, 2) CHARGED_CASE(kind, 3)
#define CHARGED_ENTRY(kind, mode, field) charged_dispatch_charged_##kind##_##mode##_##field,
#define CHARGED_ENTRIES(kind, mode) CHARGED_ENTRY(kind, mode, 0) CHARGED_ENTRY(kind, mode, 1)
#define CHARGED_BASIC_ENTRIES(kind) CHARGED_ENTRIES(kind, 0) CHARGED_ENTRIES(kind, 1) CHARGED_ENTRIES(kind, 2) CHARGED_ENTRIES(kind, 3)
#endif
