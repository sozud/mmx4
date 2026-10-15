#ifndef MMX4_TESTS_ANIMATION_ENDINGS_H
#define MMX4_TESTS_ANIMATION_ENDINGS_H

extern void* magma_dragoon_animations[38];
static u32 animation_case(u32 mode)
{
    struct WeaponObj web, web_before;
    struct ShotObj pillar, pillar_before;
    struct PlayerObj player_before = g_Player;
    u32 i;
    memset(&web, 0, sizeof(web));
    memset(&pillar, 0, sizeof(pillar));
    if (mode < 3) {
        web.active = 0x41;
        web.id = 1;
        web.unk2 = 2;
        web.state = 1;
        web.on_screen = 1;
        web.bg_offset = -1;
        web.x_pos.val = (mode == 2 ? 1000 : 100) * 65536 + 0x1234;
        web.y_pos.val = 200 * 65536 + 0x5678;
        web.animation_table = D_8011C070;
        set_animation(&web, 8);
        web.animation_cursor = D_8011C070[8] + (mode ? 0 : 10);
        web.animation_step = *(union AnimationStep*)web.animation_cursor;
        web_before = web;
        if (mode) {
            web_before.animation_cursor = D_8011C070[8] + 1;
            web_before.animation_step = *(union AnimationStep*)(D_8011C070[8] + 1);
            web_before.on_screen = mode == 1;
        } else {
            assert(web.animation_step.packed == 0x07000060);
            web_before.animation_step.fields.duration = 95;
            web_before.state = 3;
            web_before.on_screen = 0;
        }
        lightning_web_charged_vanish(&web);
        for (i = 0; i < sizeof(web) / 4; i++)
            assert(((u32*)&web)[i] == ((u32*)&web_before)[i]);
    } else {
        pillar.active = 0x41;
        pillar.id = 41;
        pillar.state = 1;
        pillar.unk5 = 3;
        pillar.unk6 = 4;
        pillar.unk8A = mode == 5 ? 1 : 2;
        pillar.on_screen = 1;
        pillar.bg_offset = -1;
        pillar.x_pos.val = (mode == 4 ? 1000 : 100) * 65536 + 0x1234;
        pillar.y_pos.val = 200 * 65536 + 0x5678;
        pillar.animation_table = (u32**)magma_dragoon_animations;
        set_animation(&pillar, mode < 5 ? 32 : 29);
        if (mode < 5) {
            pillar.animation_cursor = (u32*)magma_dragoon_animations[32] + 7;
            pillar.animation_step = *(union AnimationStep*)pillar.animation_cursor;
            assert(pillar.animation_step.packed == 0xB5000001);
        }
        pillar_before = pillar;
        if (mode < 5)
            pillar_before.on_screen = mode == 3;
        else {
            pillar_before.animation_step.fields.duration = 1;
            pillar_before.unk8A--;
            if (mode == 5)
                pillar_before.unk6 = 2;
            else {
                pillar_before.state = 2;
                pillar_before.unk5 = 0;
                pillar_before.unk6 = 0;
            }
        }
        magma_fire_pillar_repeat(&pillar);
        for (i = 0; i < sizeof(pillar) / 4; i++)
            assert(((u32*)&pillar)[i] == ((u32*)&pillar_before)[i]);
    }
    for (i = 0; i < sizeof(g_Player) / 4; i++)
        assert(((u32*)&g_Player)[i] == ((u32*)&player_before)[i]);
    return mode < 3 ? (u8)web.state | ((u32)(u8)web.on_screen << 8) | ((u32)web.animation_step.fields.duration << 16) : (u8)pillar.state | ((u32)(u8)pillar.unk6 << 8) | ((u32)(u16)pillar.unk8A << 16);
}
#define ENDING_CASE(m)                                          \
    static u32 web_and_magma_animation_endings_ending_##m(void) \
    {                                                           \
        return animation_case(m);                               \
    }
#define ENDING_ENTRY(m) web_and_magma_animation_endings_ending_##m,
#endif
