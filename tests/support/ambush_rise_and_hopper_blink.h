#ifndef MMX4_TESTS_AMBUSH_RISE_AND_HOPPER_BLINK_H
#define MMX4_TESTS_AMBUSH_RISE_AND_HOPPER_BLINK_H

static u32 start_case(u32 mode)
{
    struct MainObj obj, expected;
    struct PlayerObj player_before = g_Player;
    struct BackgroundObj backgrounds_before[3];
    struct EngineObj engine_before = engine_obj;
    s8 saved_bank = D_8013E198[2];
    u32 i;
    memset(&obj, 0, sizeof(obj));
    D_8013E198[2] = -1;
    obj.active = 0x41;
    obj.state = 1;
    obj.unk5 = 3;
    obj.unk6 = mode == 0 || mode == 3 ? 1 : mode == 4 ? 3
                                                      : 2;
    if (mode == 0 || mode == 3) {
        obj.id = 56;
        obj.unk7C = 1;
        obj.unk7 = mode == 3 ? 3 : 0;
        obj.ext.main_56.flags = 0xFF;
        obj.animation_table = (const u8* const*)jet_stingray_animations;
        set_animation(&obj, 0);
    } else {
        obj.id = 41;
        obj.unk7C = 6;
        obj.on_screen = mode == 2;
    }
    expected = obj;
    memcpy(backgrounds_before, background_objects, sizeof(backgrounds_before));
    if (mode == 0) {
        expected.unk7 = 1;
        expected.unk7C = 0;
        expected.x_pos = g_Player.x_pos;
        expected.y_pos.val = (background_objects[0].unk20 + 320) * 65536;
        expected.y_speed = 9 * 65536;
        expected.attack_box = (const u8*)&jet_stingray_ambush_attack_box;
        expected.ext.main_56.flags = 0xFE;
        expected.unk17 = 7;
        expected.previous_animation_index = 0xFF;
        expected.animation_cursor = jet_stingray_animations[7];
        expected.animation_step = *(union AnimationStep*)jet_stingray_animations[7];
    } else if (mode < 3) {
        expected.unk5 = 2;
        expected.unk6 = 0;
    }
    if (mode == 0 || mode == 3)
        jet_stingray_ambush_rise(&obj);
    else
        data_hopper_blink(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(backgrounds_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)backgrounds_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    assert(D_8013E198[2] == -1);
    D_8013E198[2] = saved_bank;
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u8)obj.unk7 << 16) | ((u32)obj.unk17 << 24);
}
#define RESET_CASE(m)                                       \
    static u32 boss_ambush_and_hopper_reset_start_##m(void) \
    {                                                       \
        return start_case(m);                               \
    }
#define RESET_ENTRY(m) boss_ambush_and_hopper_reset_start_##m,
#endif
