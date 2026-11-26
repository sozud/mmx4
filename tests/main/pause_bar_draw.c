#include "test_runtime.h"
#include "main/55C4.h"
#ifndef MMX4_SATURN
#include "support/pause_draw.h"

static u8 sprite_list[64];
static u32 sprite_count;
static void push(u8 index)
{
    sprite_list[sprite_count++] = index;
}
static void expect_sprites(u32 zero, u32 stage)
{
    u32 s;
    sprite_count = 0;
    if (!zero) {
        push(0x14), push(0), push(1);
        if (bar_object.options.items[1])
            push(0x15), push(2), push(3);
    }
    for (s = zero ? 0 : 2; s < (zero ? 8u : 10u); s++)
        if (bar_object.options.items[s])
            push(s + 0x14), push(s * 2), push(s * 2 + 1);
    if (bar_object.options.fields.unk20)
        push(0x23);
    if (bar_object.options.fields.unk21)
        push(0x24);
    if (bar_object.options.fields.unk22)
        push(0x25);
    push(0x1F);
    if (bar_object.options.fields.unk25)
        push(0x26);
    push(0x1E);
    push(0x20);
    if (stage >= 1 && stage <= 8 && bar_object.options.items[zero ? D_800F1C10[stage - 1] : stage + 1])
        push(0x21);
    push(0x22);
}
static u32 test_pause_screen(u32 row)
{
    static const u8 stages[] = { 3, 3, 3, 2 };
    u32 zero = row & 1, stage = stages[row], i, n = 0;
    pause_draw_begin();
    memset(&engine_obj, 0, sizeof(engine_obj));
    memset(&g_Player, 0, sizeof(g_Player));
    memset(&bar_object, 0, sizeof(bar_object));
    engine_obj.cur_character = zero ? CHARACTER_ZERO : CHARACTER_X;
    engine_obj.stage = stage;
    engine_obj.max_hp = 0x20;
    engine_obj.player_lives = 2;
    engine_obj.sub_tanks[0] = 5;
    engine_obj.sub_tanks[1] = 9;
    engine_obj.sub_tanks[2] = 12;
    g_Player.hp = 14;
    for (i = 0; i < 16; i++) {
        bar_object.options.items[i] = row == 2 ? i == 0 || i == 2 : 1;
        g_Player.weapon_energy[i] = row == 2 ? 0 : 3 + i;
    }
    if (row == 1)
        bar_object.options.items[D_800F1C10[stage - 1]] = 0;
    bar_object.unk14 = -1;
    func_80017340();
    pause_draw_collect();
    expect_sprites(zero, stage);
    for (i = 0; i < sprite_count; i++, n++) {
        u8 index = sprite_list[i];
        s16 x = index < 38 ? D_800F1AD8[index].x : D_800F1C08[0];
        s16 y = index < 38 ? D_800F1AD8[index].y : D_800F1C08[1];
        assert(!pause_drawn[n].bar);
        assert(pause_drawn[n].x0 == (index == 0x20 ? 0x80 + 0x20 * 2 : x));
        assert(pause_drawn[n].y0 == (index == 0x20 ? 0xD8 : y));
    }
    for (i = 0; i < 14; i++) {
        u8 flag = bar_object.options.items[i];
        const s16* geometry = i < 13 ? &D_800F1C18[i].x0 : D_800F1D04;
        s16 x1 = geometry[2], x3 = geometry[6];
        if (flag ? i != 0 && zero && i < 9 : i < 13)
            continue;
        if (i < 10) {
            if (i >= 2 || (i == 0) != !zero) {
                s8 amount = g_Player.weapon_energy[i < 2 ? 0 : i - 1];
                x1 = amount ? geometry[0] + amount * 2 - 1 : geometry[0];
                x3 = amount ? geometry[4] + amount * 2 - 1 : geometry[4] - 1;
            }
        } else if (i == 13) {
            x1 = 0x6E + 14 * 2;
            x3 = 0x67 + 14 * 2;
        } else {
            s8 amount = i == 12 ? engine_obj.sub_tanks[2] : TANK_VALUE(engine_obj.sub_tanks[i - 10]);
            x1 = geometry[0] + amount;
            x3 = geometry[4] - 1 + amount;
        }
        assert(pause_drawn[n].bar);
        assert(pause_drawn[n].x0 == (i == 13 ? 0x6E : geometry[0]) && pause_drawn[n].x2 == (i == 13 ? 0x67 : geometry[4] - 1));
        assert(pause_drawn[n].x1 == x1 && pause_drawn[n].x3 == x3);
        n++;
    }
    assert(n == pause_drawn_count);
    return n;
}
#define PAUSE_SCREEN_CASES 4
#else
#define test_pause_screen NULL
#define PAUSE_SCREEN_CASES 0
#endif

const struct CTestGroup c_test_groups[] = {
    { "pause_screen_sprites_and_bars", 0, 0, PAUSE_SCREEN_CASES, test_pause_screen },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = PAUSE_SCREEN_CASES;
