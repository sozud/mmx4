#ifndef MMX4_TESTS_BACKGROUND_ZONE_H
#define MMX4_TESTS_BACKGROUND_ZONE_H

static u32 zone_case(u32 controller, u32 done)
{
    struct EffectObj obj, before;
    struct BackgroundObj background_before[3];
    struct PlayerObj player_before;
    u32 i;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    obj.active = 0x41;
    obj.id = controller == 0 ? 20 : 22;
    obj.state = 1;
    obj.unk5 = 0x24;
    obj.unk6 = done ? 17 : 0;
    obj.x_pos.val = 0x123456;
    obj.y_pos.val = 0x234567;
    background_objects[0].unk2E = 0x7777;
    background_objects[1].unk4 = 7;
    before = obj;
    player_before = g_Player;
    memcpy(background_before, background_objects, sizeof(background_before));
    if (controller == 0)
        bg_zone_controller_d_zone_1(&obj);
    else
        bg_zone_controller_e_zone_4(&obj);
    if (done) {
        before.unk5 = controller == 0 ? 3 : 5;
        before.unk6 = 0;
    } else {
        before.unk6 = 1;
        if (controller == 0)
            background_before[0].unk2E = 0x90;
        else
            background_before[1].unk4 = 1;
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(background_before) / 4; i++)
        assert(((u32*)background_objects)[i] == ((u32*)background_before)[i]);
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8) | ((u32)background_objects[0].unk2E << 16);
}
#define ZONE_CASE(c, d)             \
    static u32 zone_##c##_##d(void) \
    {                               \
        return zone_case(c, d);     \
    }
#define ZONE_ENTRY(c, d) zone_##c##_##d,
#endif
