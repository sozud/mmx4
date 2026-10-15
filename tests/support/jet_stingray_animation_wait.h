#ifndef MMX4_TESTS_JET_STINGRAY_ANIMATION_WAIT_H
#define MMX4_TESTS_JET_STINGRAY_ANIMATION_WAIT_H

static u32 jet_case(u32 mode, u32 observation)
{
    struct MainObj obj, before, owner, owner_before;
    struct VisualObj visual, visual_before;
    u32 i, actual, vortex = mode & 1;
    memset(&obj, 0, sizeof(obj));
    memset(&owner, 0, sizeof(owner));
    memset(&visual, 0, sizeof(visual));
    obj.active = 0x41;
    obj.id = 56;
    obj.state = 1;
    obj.unk5 = 1;
    obj.unk6 = mode >= 2 ? 3 : 2;
    obj.unk7C = 1;
    obj.on_screen = 7;
    obj.animation_table = (const u8* const*)jet_stingray_animations;
    set_animation(&obj, 0);
    before = obj;
    visual.active = 0x41;
    visual.id = 23;
    visual.state = 1;
    visual.unk5 = mode >= 2 ? 3 : 1;
    visual.unk50 = (struct PlayerObj*)&owner;
    owner.active = 0x41;
    owner.state = 1;
    owner.ext.main_56.vortex_result = 1;
    visual.animation_table = (u32**)jet_stingray_animations;
    set_animation(&visual, 0);
    visual_before = visual;
    owner_before = owner;
    if (vortex) {
        jet_stingray_fx_vortex(&visual);
        if (mode < 2) {
            visual_before.unk5 = 2;
            visual_before.unk17 = 0x15;
            visual_before.previous_animation_index = 0xFF;
            visual_before.animation_cursor = jet_stingray_animations[0x15];
            visual_before.animation_step = *(union AnimationStep*)jet_stingray_animations[0x15];
        }
        actual = observation == 0 ? visual.animation_step.packed : (u8)visual.unk5 | ((u32)(u8)visual.state << 8);
    } else {
        jet_stingray_intro_warning(&obj);
        before.on_screen = 0;
        if (mode < 2) {
            before.unk7C = 0;
            before.unk5 = 2;
            before.unk6 = 0;
            before.unk17 = 0x1D;
            before.previous_animation_index = 0xFF;
            before.animation_cursor = (const u8*)jet_stingray_animations[0x1D];
            before.animation_step = *(union AnimationStep*)jet_stingray_animations[0x1D];
        }
        actual = observation == 0 ? obj.animation_step.packed : (u8)obj.unk5 | ((u32)(u8)obj.unk6 << 8);
    }
    for (i = 0; i < sizeof(obj) / 4; i++)
        assert(((u32*)&obj)[i] == ((u32*)&before)[i]);
    for (i = 0; i < sizeof(visual) / 4; i++)
        assert(((u32*)&visual)[i] == ((u32*)&visual_before)[i]);
    for (i = 0; i < sizeof(owner) / 4; i++)
        assert(((u32*)&owner)[i] == ((u32*)&owner_before)[i]);
    return actual;
}
#define JET_WAIT_CASE(m, n)                                    \
    static u32 jet_stingray_animation_wait_jet_##m##_##n(void) \
    {                                                          \
        return jet_case(m, n);                                 \
    }
#define JET_WAIT_ENTRY(m, n) jet_stingray_animation_wait_jet_##m##_##n,
#endif
