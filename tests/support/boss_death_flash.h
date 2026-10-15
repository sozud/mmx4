#ifndef MMX4_TESTS_BOSS_DEATH_FLASH_H
#define MMX4_TESTS_BOSS_DEATH_FLASH_H

static u32 boss_death_flash_case(void (*step)(struct MainObj*), u32 boss, u32 mode)
{
    static const u8 ids[4] = { 54, 60, 61, 65 };
    struct MainObj obj, expected;
    struct EffectObj pool_before[32];
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(effect_objects, 0, sizeof(effect_objects));
    for (i = 0; i < 32; i++) {
        effect_objects[i].active = 1;
        effect_objects[i].id = 39;
        effect_objects[i].state = 40;
        effect_objects[i].x_pos.val = 50 * 65536 + 0xBEEF;
        effect_objects[i].y_pos.val = 60 * 65536 + 0xCAFE;
        effect_objects[i].backref = &obj;
    }
    if (mode == 2)
        effect_objects[31].active = 0;
    obj.active = 0x41;
    obj.id = ids[boss];
    obj.state = 1;
    obj.unk5 = 1;
    obj.bg_offset = -1;
    obj.on_screen = 0;
    obj.unk42 = 0x1234;
    obj.x_pos.val = 100 * 65536 + 0x1234;
    obj.y_pos.val = 200 * 65536 + 0x5678;
    obj.unk7C = mode == 1 || mode == 2 ? 1 : 2;
    obj.unk7E = mode >= 3 ? 0 : 2;
    obj.invincibility_timer = mode == 6 ? 40 : mode == 5 ? 0
        : mode == 4                                      ? 20
                                                         : 5;
    expected = obj;
    memcpy(pool_before, effect_objects, sizeof(pool_before));
    expected.unk7C--;
    expected.unk7E--;
    expected.on_screen = 1;
    if (mode == 1 || mode == 2) {
        expected.unk5 = 2;
        if (mode == 2) {
            pool_before[31].active = boss == 3 ? -127 : 1;
            pool_before[31].id = 26;
            pool_before[31].x_pos.i.hi = 100;
            pool_before[31].y_pos.i.hi = 200;
            if (boss == 0)
                expected.ext.main_54.effect = &effect_objects[31];
            if (boss == 1)
                expected.ext.main_60.effect = &effect_objects[31];
            if (boss == 2)
                expected.ext.main_61.data.effect = &effect_objects[31];
            if (boss == 3)
                expected.ext.main_65.object = MAIN_OBJECT(&effect_objects[31]);
        }
    }
    if (mode >= 3) {
        expected.unk42 = 0x9234;
        expected.invincibility_timer = mode == 4 ? 15 : mode == 5 ? -5
                                                                  : 0;
        expected.unk7E = mode == 4 ? 15 : 5;
    }
    step(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(pool_before) / 4; i++)
        assert(((u32*)effect_objects)[i] == ((u32*)pool_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u8)obj.invincibility_timer << 8) | ((u32)(u8)obj.unk7E << 16);
}

#define BOSS_DEATH_FLASH_CASE(prefix, step, b, m) \
    static u32 prefix##_##m(void)                 \
    {                                             \
        return boss_death_flash_case(step, b, m); \
    }
#define BOSS_DEATH_FLASH_ENTRY(prefix, b, m) prefix##_##m,
#define BOSS_DEATH_FLASH_TESTS(prefix, step, b)                                                                                  \
    BOSS_DEATH_FLASH_CASE(prefix, step, b, 0)                                                                                    \
    BOSS_DEATH_FLASH_CASE(prefix, step, b, 1)                                                                                    \
    BOSS_DEATH_FLASH_CASE(prefix, step, b, 2)                                                                                    \
    BOSS_DEATH_FLASH_CASE(prefix, step, b, 3)                                                                                    \
    BOSS_DEATH_FLASH_CASE(prefix, step, b, 4)                                                                                    \
    BOSS_DEATH_FLASH_CASE(prefix, step, b, 5)                                                                                    \
    BOSS_DEATH_FLASH_CASE(prefix, step, b, 6)                                                                                    \
    static const CTestCase prefix##_cases[]                                                                                      \
        = {                                                                                                                      \
              BOSS_DEATH_FLASH_ENTRY(prefix, b, 0) BOSS_DEATH_FLASH_ENTRY(prefix, b, 1) BOSS_DEATH_FLASH_ENTRY(prefix, b, 2)     \
                  BOSS_DEATH_FLASH_ENTRY(prefix, b, 3) BOSS_DEATH_FLASH_ENTRY(prefix, b, 4) BOSS_DEATH_FLASH_ENTRY(prefix, b, 5) \
                      BOSS_DEATH_FLASH_ENTRY(prefix, b, 6)                                                                       \
          };
#endif
