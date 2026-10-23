// BarObj, bar_object
// 8002FCAC..800311EC
#include "common.h"
#include "main/1A5BC.h"
#include "main/pause_menu.h"
#include "main/11184.h"
#include "main/144A4.h"
#include "main/55C4.h"
#include "main/2824.h"
#include "main/player_weapon.h"
#ifdef MMX4_SATURN
#include "saturn/platform.h"
#include "saturn/game_low.h"
#endif

#ifdef MMX4_SATURN
#define SHADOW16(offset) (*(u16*)((u8*)saturn_vdp2_shadow + (offset)))
#define PAUSE_PRESSED saturn_pad_pressed
#define PAUSE_PAD_CONFIRM 0x0200
#define PAUSE_PAD_CONFIRM_ALT 0x0400
#define PAUSE_PAD_START 0x0800
#define PAUSE_PAD_UP 0x1000
#define PAUSE_PAD_DOWN 0x2000
#define PAUSE_PAD_LEFT 0x4000
#define PAUSE_PAD_RIGHT 0x8000
#define PAUSE_SOUND_CONFIRM 0x27
#define PAUSE_SOUND_MOVE 0x0D
#define PAUSE_SOUND_REFILL 0x20
#define PAUSE_STOP_SOUND() saturn_music_request(3, 0, 0, 0)
#define PAUSE_FADE_OUT() saturn_fade_start_out()
#define PAUSE_FADE_IN() saturn_fade_start_in()
#define PAUSE_RENDER() saturn_render_frame()
#define PAUSE_DRAW() saturn_pause_draw()
#define PAUSE_ENTER() saturn_pause_enter()
#define PAUSE_LEAVE() saturn_pause_leave()
#define PAUSE_SAVED_WEAPON saturn_pause_weapon
#define PAUSE_WINDOW_STEPS_OPEN 19
#define PAUSE_WINDOW_STEPS_MID 11
#define PAUSE_TEXT_COLUMN 11

extern u16 saturn_vdp2_shadow[];
extern u8 saturn_pause_weapon;
void saturn_pause_enter(void);
void saturn_pause_reload(void);
void saturn_pause_leave(void);
void saturn_fade_start_in(void);
void saturn_fade_start_out(void);
void saturn_render_frame(void);
void saturn_pause_draw(void);
void saturn_sprite_reset_queues(void);
void saturn_text_layers_clear(u32 layers);
void saturn_music_request(s32 kind, s32 id, s32 pan, s32 unused);
void saturn_debug_set_cursor(u16 column, u16 row);
void saturn_debug_putchar(u8 character);
#else
#define PAUSE_PRESSED controller_input.pressed
#define PAUSE_PAD_CONFIRM PAD_CONFIRM
#define PAUSE_PAD_START PADstart
#define PAUSE_PAD_UP PADLup
#define PAUSE_PAD_DOWN PADLdown
#define PAUSE_PAD_LEFT PADLleft
#define PAUSE_PAD_RIGHT PADLright
#define PAUSE_SOUND_CONFIRM 0x22
#define PAUSE_SOUND_MOVE 0xC
#define PAUSE_SOUND_REFILL 0x17
#define PAUSE_STOP_SOUND() stop_sound(0xFF, 0)
#define PAUSE_FADE_OUT() func_800129F0(8)
#define PAUSE_FADE_IN() func_800129A4(8)
#define PAUSE_RENDER() func_80023D68()
#define PAUSE_DRAW() func_80023D90()
#define PAUSE_ENTER() func_800170B0()
#define PAUSE_LEAVE() func_800170E0()
#define PAUSE_SAVED_WEAPON D_8013B818[0]
#endif

// D_800F48D4
extern void (*D_800F48D4[])(struct BarObj*);
void func_8002FCEC(struct BarObj*);
void func_80030128(struct BarObj*);
void func_80030F9C(struct BarObj*);

// D_800F48E0
extern void (*D_800F48E0[])(struct BarObj*);
void func_8002FD28(struct BarObj*);

// D_800F48F4
extern void (*D_800F48F4[])(struct BarObj*);

void func_80030DF8(struct BarObj*);
void func_80030EC8(struct BarObj*);

// D_800F4910
extern void (*D_800F4910[])(struct BarObj*);
void func_80030FD8(struct BarObj*);
void func_80031014(struct BarObj*);

void func_80031130(struct BarObj*);

void func_800170E0(void);
void func_800170B0(void);
extern u8 D_8013B818[0x10];
void func_80021104(struct EngineObj* arg0);
void func_80023D90(void);
void func_80021158(void);
void player_cancel_released_charge(void);

extern u8 D_800F48EC[8];

void func_8002FCAC(void)
{
    struct BarObj* bar = &bar_object;
    D_800F48D4[bar_object.state](bar);
}

void func_8002FCEC(struct BarObj* arg0)
{
    D_800F48E0[arg0->unk5](arg0);
}

void func_8002FD28(struct BarObj* arg0)
{
    PAUSE_STOP_SOUND();
    PAUSE_FADE_OUT();
    PAUSE_RENDER();
    arg0->unk5 = 1;
}

void func_8002FD70(struct BarObj* self)
{
    s8 weapon;
    u8 current_weapon;
    s32 option;
    u32 i;
    u32 j;
    if (main_bss_state.transition.active != 0) {
        PAUSE_RENDER();
        return;
    }
    PAUSE_ENTER();
    PAUSE_FADE_IN();
    self->unk5 = 2;
    self->unk14 = 0;
    if (g_Player.unk2 == 0) {
        self->options.fields.player[0] = 1;
        if (((u8)g_Player.armor_parts) & 2) {
            self->options.fields.player[1] = 1;
        } else {
            self->options.fields.player[1] = 0;
        }
        for (i = 2; i < 10; i++) {
            if (((u8)g_Player.boss_flags >> (i - 2)) & 1) {
                self->options.items[i] = 1;
            } else {
                self->options.items[i] = 0;
            }
        }
    } else {
        for (j = 0; j < 8; j++) {
            option = D_800F48EC[j];
            if (((u8)g_Player.boss_flags >> j) & 1) {
                self->options.items[option] = 1;
            } else {
                self->options.items[option] = 0;
            }
        }
        self->options.fields.weapons[7] = 0;
        self->options.fields.unk20 = 0;
    }
    if (engine_obj.collected_upgrades & 0x3000) {
        if (engine_obj.collected_upgrades & 0x1000) {
            self->options.fields.unk20 = 1;
            engine_obj.sub_tanks[0] |= 0x80;
        }
        if (engine_obj.collected_upgrades & 0x2000) {
            self->options.fields.unk21 = 1;
            engine_obj.sub_tanks[1] |= 0x80;
        }
    } else {
        self->options.fields.unk20 = 0;
        self->options.fields.unk21 = 0;
    }
    if (engine_obj.collected_upgrades & 0x4000) {
        self->options.fields.unk22 = 1;
    } else {
        self->options.fields.unk22 = 0;
    }
    if (engine_obj.stage != 0) {
        if ((((u8)engine_obj.palette_flags) >> (engine_obj.stage - 1)) & 1) {
            self->options.fields.unk23 = 1;
        } else {
            self->options.fields.unk23 = 0;
        }
    }
    self->options.fields.unk24 = 1;
    if (g_Player.unk2 != 0) {
        for (i = 0xA; i < 0xF; i++) {
            if (self->options.items[i] != 0) {
                self->unk14 = i;
                break;
            }
        }
    } else if (((engine_obj.stage == 5) && (engine_obj.checkpoint == 0)) || (g_Player.ride_state < 0)) {
        self->unk2 = 1;
        for (i = 0xA; i < 0xF; i++) {
            if (self->options.items[i] != 0) {
                self->unk14 = i;
                break;
            }
        }
    } else {
        self->unk2 = 0;
        weapon = g_Player.weapon;
        if (weapon != 0) {
            self->unk14 = weapon + 1;
        }
    }
    if (engine_obj.collected_upgrades & 0x8000) {
        self->options.fields.unk25 = 1;
    } else {
        self->options.fields.unk25 = 0;
    }
    current_weapon = g_Player.weapon;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk30 = 0;
    PAUSE_SAVED_WEAPON = current_weapon;
}

void func_800300AC(struct BarObj* arg0)
{
    if (main_bss_state.transition.active == 0) {
        arg0->state = 1;
        arg0->unk5 = 0;
        if (g_Player.unk2 || arg0->unk2) {
            if (arg0->unk14 >= 0xD) {
                arg0->unk5 = 2;
            } else {
                arg0->unk5 = 1;
            }
        }
#ifdef MMX4_SATURN
        if (saturn_pause_latch) {
            arg0->unk5 = 6;
            SHADOW16(0x20) |= 8;
            SHADOW16(0xFA) &= 0xFF;
            SHADOW16(0xFA) |= 0x304;
        }
#endif
    }
    PAUSE_DRAW();
}

void func_80030128(struct BarObj* arg0)
{
#ifndef MMX4_SATURN
    if (controller_input.pressed & PADselect) {
        if (arg0->unk5 < 3) {
            arg0->unk28 = arg0->unk5;
            arg0->unk5 = 6;
            arg0->unk6 = 0;
        }
    }
#endif
    D_800F48F4[arg0->unk5](arg0);
    if (arg0->unk5 < 5) {
        PAUSE_DRAW();
    }
}

void func_800301BC(struct BarObj* arg0)
{
    s16 var_a1;
    u16 var_a1_2;
    s8 var_a2;
    s8 initial_unk14;

    var_a1 = 0;
    initial_unk14 = arg0->unk14;
    switch (PAUSE_PRESSED) {
    case PAUSE_PAD_START:
        arg0->state = 2;
        arg0->unk5 = 0;
        break;
    case PAUSE_PAD_CONFIRM:
#ifdef MMX4_SATURN
    case PAUSE_PAD_CONFIRM_ALT:
#endif
        if (arg0->unk14 < 0xAU) {
            if (arg0->unk14 < 2) {
                g_Player.weapon = 0;
            } else {
                g_Player.weapon = arg0->unk14 - 1;
            }
        }
        func_8001540C(0, PAUSE_SOUND_CONFIRM, 0);
        break;
    case PAUSE_PAD_UP:
        var_a2 = arg0->unk14;
        do {
            var_a2 -= 2;
            if (var_a2 < 0) {
                var_a2 = arg0->unk14;
            }
            if (arg0->unk14 == var_a2) {
                break;
            }
            if (var_a2 == 0) {
                break;
            }
        } while (arg0->options.items[var_a2] == 0);
        arg0->unk14 = var_a2;
        break;
    case PAUSE_PAD_DOWN:
        var_a2 = initial_unk14;
        do {
            var_a2 += 2;
            if (var_a2 < 0xA) {
                continue;
            }
            var_a2 = 9;
            for (var_a1_2 = 0; var_a1_2 < 5; var_a1_2++) {
                var_a2++;
                if (arg0->options.items[var_a2] != 0) {
                    if (var_a2 >= 0xD) {
                        arg0->unk5 = 2;
                    } else {
                        arg0->unk5 = 1;
                    }
                    break;
                }
            }
            break;
        } while (arg0->unk14 != var_a2 && arg0->options.items[var_a2] == 0);
        arg0->unk14 = var_a2;
        break;
    case PAUSE_PAD_RIGHT:
        var_a2 = initial_unk14 + 1;
        if (!(var_a2 & 1)) {
            break;
        }
        initial_unk14 = var_a2;
        if (arg0->options.items[var_a2] == 0) {
            do {
                if (var_a1 == 0) {
                    var_a2 += 2;
                    if (var_a2 >= 0xB) {
                        var_a2 -= 2;
                        var_a1 = 1;
                    }
                } else {
                    var_a2 -= 2;
                }
                if (var_a2 == initial_unk14) {
                    var_a2 = initial_unk14 = arg0->unk14;
                    break;
                }
            } while (arg0->options.items[var_a2] == 0);
        } else {
            initial_unk14 = initial_unk14 - 1;
        }
        arg0->unk14 = var_a2;
        break;
    case PAUSE_PAD_LEFT:
        var_a2 = initial_unk14 - 1;
        if (var_a2 & 1) {
            break;
        }
        initial_unk14 = var_a2;
        if (arg0->options.items[var_a2] == 0) {
            do {
                if (var_a1 == 0) {
                    var_a2 -= 2;
                    if (var_a2 < 0) {
                        var_a2 += 2;
                        var_a1 = 1;
                    }
                } else {
                    var_a2 += 2;
                }
                if (var_a2 == initial_unk14) {
                    var_a2 = initial_unk14 = arg0->unk14;
                    break;
                }
            } while (arg0->options.items[var_a2] == 0);
        } else {
            initial_unk14++;
        }
        arg0->unk14 = var_a2;
        break;
    }

    if (arg0->unk14 != initial_unk14) {
        func_8001540C(0, PAUSE_SOUND_MOVE, 0);
    }
}

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800304E4(struct BarObj* arg0)
{
    u8* bytes = (u8*)arg0;
    s32 original = (u8)arg0->unk14;
    s32 cursor;

    switch (PAUSE_PRESSED) {
    case PAUSE_PAD_START:
        arg0->state = 2;
        arg0->unk5 = 0;
        break;
    case PAUSE_PAD_CONFIRM:
#ifdef MMX4_SATURN
    case PAUSE_PAD_CONFIRM_ALT:
#endif
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        switch (arg0->unk14) {
        case 10:
            arg0->unk5 = 3;
            if (TANK_VALUE(engine_obj.sub_tanks[0]) == 0x20)
                arg0->unk28 = 1;
            break;
        case 11:
            arg0->unk5 = 3;
            if (TANK_VALUE(engine_obj.sub_tanks[1]) == 0x20)
                arg0->unk28 = 1;
            break;
        case 12:
            arg0->unk5 = 4;
            if (TANK_VALUE(engine_obj.sub_tanks[2]) == 0x20)
                arg0->unk2C = 1;
            break;
        }
        break;
    case PAUSE_PAD_UP:
        if (g_Player.unk2 != 0 || arg0->unk2 != 0)
            break;
        cursor = 9;
        while ((s8)cursor != 0 && bytes[0x16 + (s8)cursor] == 0)
            cursor--;
        arg0->unk5 = 0;
        arg0->unk14 = cursor;
        break;
    case PAUSE_PAD_RIGHT:
        cursor = original;
        for (;;) {
            cursor++;
            if ((s8)cursor >= 0xD) {
                if (bytes[0x16 + (s8)cursor] == 0)
                    cursor++;
                arg0->unk5 = 2;
                break;
            }
            if (bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    case PAUSE_PAD_LEFT:
        cursor = original;
        for (;;) {
            cursor--;
            if ((s8)cursor < 10) {
                cursor = original;
                break;
            }
            if (bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    }
    if (arg0->unk14 != (s8)original)
        func_8001540C(0, PAUSE_SOUND_MOVE, 0);
}

void func_80030728(struct BarObj* arg0)
{
    u8* bytes = (u8*)arg0;
    s32 original = (u8)arg0->unk14;
    s32 cursor;

    if (PAUSE_PRESSED & PAUSE_PAD_START) {
        arg0->state = 2;
        arg0->unk5 = 0;
        goto done;
    }
    switch (PAUSE_PRESSED) {
    case PAUSE_PAD_CONFIRM:
#ifdef MMX4_SATURN
    case PAUSE_PAD_CONFIRM_ALT:
#endif
        if ((s8)original == 0xD) {
            arg0->state = 2;
            arg0->unk5 = 0;
            arg0->unk30 = 1;
        } else {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            PAUSE_DRAW();
        }
        func_8001540C(0, PAUSE_SOUND_CONFIRM, 0);
        break;
    case PAUSE_PAD_UP:
        cursor = original;
        if (g_Player.unk2 != 0 || arg0->unk2 != 0) {
            cursor--;
            if ((s8)cursor < 0xD)
                cursor = 0xD;
            if (bytes[0x16 + (s8)cursor] != 0)
                arg0->unk14 = cursor;
            break;
        }
        for (;;) {
            cursor--;
            if ((s8)cursor < 0xD) {
                cursor = 9;
                while ((s8)cursor != 0 && bytes[0x16 + (s8)cursor] == 0)
                    cursor--;
                arg0->unk5 = 0;
                break;
            }
            if (arg0->unk14 == (s8)cursor || bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    case PAUSE_PAD_DOWN:
        cursor = original;
        for (;;) {
            cursor++;
            if ((s8)cursor >= 0xF) {
                cursor = 0xE;
                break;
            }
            if (arg0->unk14 == (s8)cursor || bytes[0x16 + (s8)cursor] != 0)
                break;
        }
        arg0->unk14 = cursor;
        break;
    case PAUSE_PAD_LEFT:
        cursor = 0xC;
        if (g_Player.unk2 != 0 || arg0->unk2 != 0) {
            for (;;) {
                if ((s8)cursor == 0 || bytes[0x16 + (s8)cursor] != 0) {
                    arg0->unk14 = cursor;
                    arg0->unk5 = 1;
                    break;
                }
                cursor--;
                if ((s8)cursor < 10)
                    break;
            }
            break;
        }
        while ((s8)cursor != 0 && bytes[0x16 + (s8)cursor] == 0)
            cursor--;
        arg0->unk14 = cursor;
        arg0->unk5 = (s8)cursor < 10 ? 0 : 1;
        break;
    }
done:
    if (arg0->unk14 != (s8)original)
        func_8001540C(0, PAUSE_SOUND_MOVE, 0);
}

static void bar_merge_sub_tanks(void)
{
    s8 second = engine_obj.sub_tanks[1];

    if (second >= 0)
        return;
    engine_obj.sub_tanks[0] = second;
    engine_obj.sub_tanks[1] = TANK_DRAINED(second);
}

void func_80030A2C(struct BarObj* arg0)
{
    s32 frame = main_bss_state.frame_counter;
    u32 tank;
    u8 energy;
    u8 health;
    u8 player_health;

    if (frame & 1)
        return;
    tank = arg0->unk14 != 10;
    if (arg0->unk28 != 0) {
        energy = TANK_VALUE(engine_obj.sub_tanks[tank]);
        if (energy != 0) {
            engine_obj.sub_tanks[tank] = (energy - 1) | 0x80;
            health = HP_VALUE(g_Player.hp) + 1;
            if (engine_obj.max_hp < (s8)health)
                health = engine_obj.max_hp;
            g_Player.hp = health;
            if ((main_bss_state.frame_counter & 3) == 0)
                func_8001540C(0, PAUSE_SOUND_REFILL, 0);
            return;
        }
        if (g_Player.hp != engine_obj.max_hp) {
            health = HP_VALUE(g_Player.hp) + 1;
            if (engine_obj.max_hp < (s8)health)
                health = engine_obj.max_hp;
            g_Player.hp = health;
            if ((frame & 3) == 0)
                func_8001540C(0, PAUSE_SOUND_REFILL, 0);
            return;
        }
        arg0->unk5 = 1;
        arg0->unk28 = 0;
        if (tank == 0)
            bar_merge_sub_tanks();
        return;
    }
    energy = TANK_VALUE(engine_obj.sub_tanks[tank]);
    if (energy == 0) {
        arg0->unk5 = 1;
        if (tank == 0)
            bar_merge_sub_tanks();
        return;
    }
    engine_obj.sub_tanks[tank] = (energy - 1) | 0x80;
    player_health = g_Player.hp;
    health = HP_VALUE(player_health) + 1;
    if (engine_obj.max_hp < (s8)health)
        health = engine_obj.max_hp;
    g_Player.hp = health | HP_DAMAGE_FLAG(player_health);
    if ((main_bss_state.frame_counter & 3) == 0)
        func_8001540C(0, PAUSE_SOUND_REFILL, 0);
}

void func_80030C54(struct BarObj* arg0)
{
    u32 i;
    s32 refilled = 0;
    u8 energy;

    if (main_bss_state.frame_counter & 1)
        return;
    if (arg0->unk2C != 0) {
        for (i = 0; i < 9; i++) {
            if (g_Player.weapon_energy[i] < 0x30) {
                g_Player.weapon_energy[i]++;
                refilled = 1;
            } else {
                g_Player.weapon_energy[i] = 0x30;
            }
        }
        if (refilled == 0) {
            energy = TANK_VALUE(engine_obj.sub_tanks[2]);
            if (energy != 0) {
                engine_obj.sub_tanks[2] = energy - 1;
            } else {
                arg0->unk5 = 1;
                arg0->unk2C = 0;
            }
            return;
        }
    } else {
        if (TANK_VALUE(engine_obj.sub_tanks[2]) == 0) {
            arg0->unk5 = 1;
            return;
        }
        for (i = 0; i < 9; i++) {
            if (g_Player.weapon_energy[i] < 0x30 && (s8)(g_Player.weapon_energy[i] + 1) < 0x30) {
                g_Player.weapon_energy[i]++;
                refilled = 1;
            } else {
                g_Player.weapon_energy[i] = 0x30;
            }
        }
        if (refilled == 0) {
            arg0->unk5 = 1;
            return;
        }
    }
    energy = TANK_VALUE(engine_obj.sub_tanks[2]);
    engine_obj.sub_tanks[2] = energy != 0 ? energy - 1 : energy;
    if ((main_bss_state.frame_counter & 3) == 0)
        func_8001540C(0, PAUSE_SOUND_REFILL, 0);
}
#else
INCLUDE_ASM("main/nonmatchings/pause_menu", func_800304E4);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80030728);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80030A2C);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80030C54);
#endif

void func_80030DF8(struct BarObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        PAUSE_FADE_OUT();
        arg0->unk6++;
        PAUSE_DRAW();
        return;
    case 1:
        if (main_bss_state.transition.active == 0) {
            arg0->unk6++;
        }
        PAUSE_DRAW();
        return;
    case 2:
        func_8002A41C((struct GameInfo*)arg0);
        return;
    case 3:
#ifdef MMX4_SATURN
        saturn_pause_reload();
#endif
        PAUSE_FADE_IN();
        arg0->unk6++;
        PAUSE_DRAW();
        return;
    case 4:
        if (main_bss_state.transition.active == 0) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            return;
        }
        PAUSE_DRAW();
        return;
    }
}

#ifdef MMX4_SATURN
const char saturn_pause_disconnect_text[5][20] = {
    "A control pad has\0\377\377",
    "been disconnected.\0\377",
    "Please connect it\0\377\377",
    "properly and press\0\377",
    "start button.\0\0\0    ",
};

static void pause_window_step(s16 x_step, s16 y_step)
{
    SHADOW16(0xC0) += x_step;
    SHADOW16(0xC4) -= x_step;
    SHADOW16(0xC8) += x_step;
    SHADOW16(0xCC) -= x_step;
    SHADOW16(0xC2) += y_step;
    SHADOW16(0xC6) -= y_step;
    SHADOW16(0xCA) += y_step;
    SHADOW16(0xCE) -= y_step;
}

static void pause_print(const char* text)
{
    while (*text)
        saturn_debug_putchar((u8)*text++);
    saturn_text_dirty_b = 1;
}

void func_80030EC8(struct BarObj* arg0)
{
    u32 i;
    switch (arg0->unk6) {
    case 0:
        arg0->unk28 = PAUSE_WINDOW_STEPS_OPEN;
        SHADOW16(0xC0) = 0x138;
        SHADOW16(0xC2) = 0x74;
        SHADOW16(0xC4) = 0x148;
        SHADOW16(0xC6) = 0x7C;
        SHADOW16(0xC8) = 0x138;
        SHADOW16(0xCA) = 0x74;
        SHADOW16(0xCC) = 0x148;
        SHADOW16(0xCE) = 0x7C;
        SHADOW16(0xD0) = 0x0909;
        SHADOW16(0xD2) = 9;
        SHADOW16(0xD4) = 0x0900;
        SHADOW16(0xD6) = 0;
        for (i = 0; i < 5; i++) {
            saturn_debug_set_cursor(PAUSE_TEXT_COLUMN, (u16)(10 + i * 2));
            pause_print(saturn_pause_disconnect_text[i]);
        }
        PAUSE_DRAW();
        arg0->unk6++;
        return;
    case 1:
        if (--arg0->unk28 != 0) {
            pause_window_step(-8, 0);
        } else {
            arg0->unk28 = PAUSE_WINDOW_STEPS_MID;
            arg0->unk6++;
        }
        break;
    case 2:
        if (--arg0->unk28 != 0) {
            pause_window_step(0, -4);
        } else {
            arg0->unk28 = 0;
            arg0->unk6++;
        }
        break;
    case 3:
        if (saturn_pause_request == 0 && (saturn_pad_pressed & PAUSE_PAD_START)) {
            arg0->unk6++;
            arg0->unk28 = PAUSE_WINDOW_STEPS_MID;
            func_8001540C(0, PAUSE_SOUND_CONFIRM, 0);
        }
        break;
    case 4:
        if (--arg0->unk28 != 0) {
            pause_window_step(0, 4);
        } else {
            arg0->unk28 = PAUSE_WINDOW_STEPS_OPEN;
            arg0->unk6++;
        }
        break;
    case 5:
        if (--arg0->unk28 != 0) {
            pause_window_step(8, 0);
            break;
        }
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        saturn_pause_latch = saturn_pause_request;
        arg0->unk28 = 0;
        saturn_text_layers_clear(8);
        return;
    default:
        return;
    }
    PAUSE_DRAW();
}
#else
void func_80030EC8(struct BarObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        func_800129F0(8);
        arg0->unk6++;
        func_80023D90();
        return;
    case 1:
        if (main_bss_state.transition.active == 0) {
            arg0->unk6++;
        }
        func_80023D90();
        return;
    case 2:
        func_80021104((struct EngineObj*)arg0);
        return;
    case 3:
        func_800129A4(8);
        arg0->unk6++;
        func_80023D90();
        return;
    case 4:
        if (main_bss_state.transition.active == 0) {
            arg0->unk5 = arg0->unk28;
            arg0->unk6 = 0;
            return;
        }
        func_80023D90();
        return;
    }
}
#endif

void func_80030F9C(struct BarObj* arg0)
{
    D_800F4910[arg0->unk5](arg0);
}

void func_80030FD8(struct BarObj* arg0)
{
    PAUSE_FADE_OUT();
    PAUSE_DRAW();
    arg0->unk5 = 1;
}

void func_80031014(struct BarObj* arg0)
{
    if (main_bss_state.transition.active != 0) {
        PAUSE_DRAW();
    } else {
        PAUSE_LEAVE();
        arg0->unk5 = 2;
    }
}

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80031064(struct BarObj* arg0)
{
    if (arg0->unk30 == 0) {
        if (g_Player.unk2 == 0) {
            player_cancel_released_charge();
            if ((s8)PAUSE_SAVED_WEAPON != g_Player.weapon) {
                player_reset_charge(&g_Player);
                g_Player.stock_charge = 0;
            }
            player_update_shot_types(&g_Player);
            if ((s8)PAUSE_SAVED_WEAPON != g_Player.weapon)
                player_equip_weapon(&g_Player);
        }
#ifdef MMX4_SATURN
        saturn_sprite_reset_queues();
        func_80021158();
        PAUSE_RENDER();
#else
        func_80021158();
#endif
        PAUSE_FADE_IN();
    }
    arg0->unk5 = 3;
}
#else
INCLUDE_ASM("main/nonmatchings/pause_menu", func_80031064);
#endif

void func_80031130(struct BarObj* arg0)
{
    if (main_bss_state.transition.active == 0) {
        if (arg0->unk30 == 0) {
            engine_obj.unk1 = 0;
            arg0->state = 0;
#ifdef MMX4_SATURN
            if (engine_obj.stage == 5 && engine_obj.checkpoint == 0 && g_Player.ride_state < 0) {
                func_8001540C(5, 50, NULL);
            }
#endif
        } else {
            engine_obj.state = 9;
            engine_obj.unk1 = 0;
            engine_obj.unk2 = 0;
            engine_obj.unk10 = 0;
            engine_obj.unk11 = 0;
            engine_obj.unk12 = 0;
            engine_obj.unk13 = 0;
            engine_obj.unk14 = 0;
            engine_obj.unk15 = 0;
            engine_obj.unk16 = 0;
            engine_obj.unk17 = 0;
            arg0->state = 0;
        }
        arg0->unk5 = 0;
    }
    if (arg0->unk30 == 0) {
        PAUSE_RENDER();
    }
}

void (*D_800F48D4[3])(struct BarObj*) = {
    func_8002FCEC,
    func_80030128,
    func_80030F9C,
};

void (*D_800F48E0[3])(struct BarObj*) = {
    func_8002FD28,
    func_8002FD70,
    func_800300AC,
};

u8 D_800F48EC[8] = { 2, 6, 1, 4, 3, 0, 5, 7 };

void (*D_800F48F4[7])(struct BarObj*) = {
    func_800301BC,
    func_800304E4,
    func_80030728,
    func_80030A2C,
    func_80030C54,
    func_80030DF8,
    func_80030EC8,
};

void (*D_800F4910[4])(struct BarObj*) = {
    func_80030FD8,
    func_80031014,
    func_80031064,
    func_80031130,
};
