#include "test_runtime.h"
#include "main/effects/effect_11_null_effect.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#ifdef MMX4_PC
#include "pc_saturn_extras.h"
#define HEAT_VDP2 ((u8*)mmx4_pc_line_scroll.vdp2)
#define HEAT_TABLE (mmx4_pc_line_scroll.table)
#define HEAT_RESET() mmx4_pc_line_scroll_reset()
#define HEAT_ENABLE(on) (mmx4_pc_saturn_heat = (on))
#define HEAT_FIRST_ROW 0
#else
extern u16 saturn_vdp2_shadow[];
#define HEAT_VDP2 ((u8*)saturn_vdp2_shadow)
#define HEAT_TABLE ((s32*)0x06002000)
#define HEAT_RESET() ((void)0)
#define HEAT_ENABLE(on) ((void)0)
#define HEAT_FIRST_ROW 1
#endif
extern u16 sound_zone_data[65];
#define CONTROL (*(u16*)(HEAT_VDP2 + 0x9A))
#define TABLE_A (*(u32*)(HEAT_VDP2 + 0xA0))
#define TABLE_B (*(u32*)(HEAT_VDP2 + 0xA4))
struct HeatWave {
    u16 phase_x, delay_x, phase_y, delay_y;
};
#define WAVE(obj) ((struct HeatWave*)&(obj).ext)

static u32 heat_wave(u32 row)
{
    static const u8 variants[] = { 0, 0, 0, 0, 0, 1, 1, 2, 2 }, states[] = { 1, 0, 1, 1, 1, 0, 1, 0, 1 };
    struct EffectObj obj;
    s32 line0_wave = sound_zone_data[0];
    u32 i;
    HEAT_RESET();
    CONTROL = 0x1234;
    memset(&obj, 0, sizeof(obj));
    memset(background_objects, 0, sizeof(background_objects));
    HEAT_ENABLE(row != 0);
    obj.active = 1;
    obj.id = 11;
    obj.unk2 = variants[row];
    obj.state = states[row];
    WAVE(obj)->delay_x = WAVE(obj)->delay_y = row == 3 || row == 4 ? 1 : 3;
    WAVE(obj)->phase_x = row == 3 ? 15 : 3;
    WAVE(obj)->phase_y = row == 3 ? 31 : 3;
    background_objects[0].x_pos.i.hi = row == 1 ? 100 : 200;
    background_objects[0].y_pos.i.hi = row == 1 ? 0x1F0 : row == 2 ? 0x200 : 0x100;
    background_objects[2].y_pos.i.hi = row == 6 || row == 8 ? 0x201 : 0x200;
    null_effect_update(&obj);
    HEAT_ENABLE(0);
    assert(obj.state == 1);
    switch (row) {
    case 0:
        assert(CONTROL == 0x1234 && WAVE(obj)->delay_x == 3);
        break;
    case 1:
        assert(CONTROL == 0x600 && TABLE_B == 0x12F37000);
        assert(HEAT_TABLE[0] == line0_wave * 2 + 0x20000);
        assert(HEAT_TABLE[1] == (line0_wave * 4 < 0x10000 ? 0x10000 : line0_wave * 4));
        assert(HEAT_TABLE[32] == 0 && HEAT_TABLE[33] == 16 << 16);
        assert(HEAT_TABLE[34] == 0 && HEAT_TABLE[35] == 17 << 16);
        assert(WAVE(obj)->phase_x == 0 && WAVE(obj)->delay_x == 2 && WAVE(obj)->delay_y == 2);
        break;
    case 2:
    case 6:
    case 8:
        assert(CONTROL == 0 && WAVE(obj)->delay_x == 3 && WAVE(obj)->phase_x == 3);
        assert(HEAT_TABLE[0] == 0);
        break;
    case 3:
    case 4:
        assert(CONTROL == 0x600 && HEAT_TABLE[510] != 0);
        assert(WAVE(obj)->delay_x == 3 && WAVE(obj)->delay_y == 3);
        assert(WAVE(obj)->phase_x == (row == 3 ? 0 : 4) && WAVE(obj)->phase_y == (row == 3 ? 0 : 4));
        for (i = 0; i < 256; i++)
            assert(HEAT_TABLE[i * 2] > -0x20000 && HEAT_TABLE[i * 2] < 0x20000);
        break;
    case 5:
        assert(CONTROL == 0x402);
        assert(TABLE_A == 0x12F37000 && TABLE_B == 0x12F37200);
        assert(HEAT_TABLE[0] == line0_wave * 2);
        assert(HEAT_TABLE[256] == (line0_wave * 3 < 0x10000 ? 0x10000 : line0_wave * 3));
        assert(WAVE(obj)->delay_x == 2 && WAVE(obj)->delay_y == 2);
        break;
    default:
        assert(CONTROL == 0x400 && TABLE_B == 0x12F37200);
        assert(HEAT_TABLE[0] == 0 && HEAT_TABLE[255] == 0);
        assert(HEAT_TABLE[256] == (line0_wave * 3 < 0x10000 ? 0x10000 : line0_wave * 3));
        assert(WAVE(obj)->delay_x == 3 && WAVE(obj)->delay_y == 2);
        break;
    }
    HEAT_RESET();
    return 1;
}

static u32 heat_wave_row(u32 row)
{
    return heat_wave(row + HEAT_FIRST_ROW);
}

const struct CTestGroup c_test_groups[] = {
    { "heat_wave", 0, 0, 9 - HEAT_FIRST_ROW, heat_wave_row },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = 9 - HEAT_FIRST_ROW;
#else
const struct CTestGroup c_test_groups[] = {};
const u32 c_test_group_count = 0;
const u32 c_test_count = 0;
#endif
