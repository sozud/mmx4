#ifndef MMX4_TESTS_TRAIN_SECTIONS_H
#define MMX4_TESTS_TRAIN_SECTIONS_H

static u32 section_case(u32 mode)
{
    struct LayerObj obj, expected;
    struct PlayerObj saved_player = g_Player, player_before;
    struct EngineObj saved_engine = engine_obj, engine_before;
    struct BackgroundObj saved_bg[3], bg_before[3];
    u32 i, actual;
    memcpy(saved_bg, background_objects, sizeof(saved_bg));
    memset(&obj, 0, sizeof(obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(background_objects, 0, sizeof(saved_bg));
    obj.active = 1;
    obj.id = mode >= 7 ? 2 : 0;
    obj.state = 1;
    obj.unk5 = mode >= 9 ? 4 : mode >= 7 ? 3
                                         : 4;
    obj.unk6 = mode == 1 || mode == 4 || mode == 8 || mode == 10 ? 1 : 0;
    obj.unk7 = 3;
    obj.bg_offset = 4;
    background_objects[0].x_pos.val = 100 * 65536 + 0x1234;
    background_objects[0].unk24 = 7;
    background_objects[0].unk26 = 101;
    g_Player.x_pos.i.hi = mode == 3 ? 0x1A50 : mode == 5 ? 0x1A60
        : mode == 6                                      ? 0x1A61
                                                         : 0x1A4F;
    expected = obj;
    player_before = g_Player;
    engine_before = engine_obj;
    memcpy(bg_before, background_objects, sizeof(bg_before));
    if (mode == 3 || mode == 5) {
        expected.unk7 = 0;
        expected.unk6 = 1;
        bg_before[0].unk24 = bg_before[0].unk26 = 0x1A50;
        player_before.script_state = 1;
        player_before.script_action = 0x14;
        player_before.script_facing = 0x40;
        player_before.spike_immune = 1;
        engine_before.gameplay_locked = 1;
    } else if (mode >= 7) {
        if (mode == 7 || mode == 9) {
            expected.unk7 = 0;
            expected.unk6 = 1;
        } else {
            expected.unk5 = 5;
            expected.unk6 = 0;
        }
    }
    if (mode < 2)
        train_scroll_section_3(&obj);
    else if (mode < 5)
        train_scroll_section_4(&obj);
    else if (mode < 7)
        train_scroll_section_4_lock(&obj);
    else if (mode < 9)
        train_tunnel_section_3(&obj);
    else
        train_tunnel_section_4(&obj);
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&expected)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    for (i = 0; i < sizeof(engine_obj) / 4; i++)
        assert(((u32*)&engine_obj)[i] == ((u32*)&engine_before)[i]);
    for (i = 0; i < sizeof(bg_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)bg_before)[i]);
    actual = (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)(u8)g_Player.script_state << 16);
    g_Player = saved_player;
    engine_obj = saved_engine;
    memcpy(background_objects, saved_bg, sizeof(saved_bg));
    return actual;
}
#define SECTION_CASE(m)                                          \
    static u32 train_section_script_boundaries_section_##m(void) \
    {                                                            \
        return section_case(m);                                  \
    }
#define SECTION_ENTRY(m) train_section_script_boundaries_section_##m,
#endif
