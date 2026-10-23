#include "common.h"
#include "saturn/platform.h"
#include "main/player_weapon.h"

#define SHADOW16(offset) (*(u16*)((u8*)saturn_vdp2_shadow + (offset)))
#define SHADOW32(offset) (*(u32*)((u8*)saturn_vdp2_shadow + (offset)))

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
#define PAUSE_SOUND_KIND 3
#define PAUSE_RIDE_SOUND_KIND 5
#define PAUSE_RIDE_SOUND 50
#define PAUSE_ITEM_TANK_A 10
#define PAUSE_ITEM_TANK_B 11
#define PAUSE_ITEM_WEAPON_TANK 12
#define PAUSE_ITEM_EXIT 13
#define PAUSE_ITEM_LAST 14
#define PAUSE_TANK_FULL 0x20
#define PAUSE_TANK_MASK 0x7F
#define PAUSE_TANK_SEEN 0x80
#define PAUSE_WEAPON_COUNT 9
#define PAUSE_WEAPON_ENERGY_MAX 48
#define PAUSE_PALETTE_WORDS 0x200
#define PAUSE_SHADOW_WORDS 0x90
#define PAUSE_SPRITE_COUNT_BYTES 20
#define PAUSE_SPRITE_LIST_WORDS (0xC80 / 4)
#define PAUSE_ARCHIVE ((s32*)0x002D0000)
#define PAUSE_GRAPHICS_VRAM 0x25E70000
#define PAUSE_GRAPHICS_BYTES 0x200
#define PAUSE_GRAPHICS_BANK_SHIFT 14
#define PAUSE_PRIORITY_MASK 0x0F00
#define PAUSE_PRIORITY_TEXT 4
#define PAUSE_WINDOW_STEPS_OPEN 19
#define PAUSE_WINDOW_STEPS_MID 11
#define PAUSE_TEXT_COLUMN 11
#define DMA_BUSY 2

extern struct BarObj bar_object;
extern u16 saturn_vdp2_shadow[];
extern volatile u16 saturn_pad_pressed;
extern volatile u32 saturn_frame_counter;
extern u8 saturn_text_dirty_b;
extern u16 saturn_color_ram_shadow[];
extern u16 saturn_pause_palette_save[];
extern u16 saturn_pause_shadow_save[];
extern u8 saturn_pause_sprite_counts_save[];
extern u32 saturn_pause_sprite_lists_save[];
extern u8 saturn_sprite_list_counts[];
extern u32 saturn_sprite_object_lists[];
extern u8 saturn_pause_player_visible;
void saturn_pause_enter(void);
void saturn_pause_reload(void);
void saturn_pause_leave(void);
extern u8 saturn_pause_weapon;
void saturn_fade_start_in(void);
void saturn_fade_start_out(void);
void saturn_render_frame(void);
void saturn_pause_draw(void);
void saturn_sprite_reset_queues(void);
void saturn_frame_dma_copy(u32 destination, u32 source, u32 count);
u32 saturn_frame_dma_result(void);
void saturn_background_refresh(void);
void saturn_text_layers_clear(u32 layers);
void saturn_music_request(s32 kind, s32 id, s32 pan, s32 unused);
void saturn_debug_set_cursor(u16 column, u16 row);
void saturn_debug_putchar(u8 character);
void func_80021158(void);
void player_cancel_released_charge(void);

static void pause_open(struct BarObj* self);
static void pause_open_start(struct BarObj* self);
static void pause_open_setup(struct BarObj* self);
static void pause_open_finish(struct BarObj* self);
static void pause_menu(struct BarObj* self);
static void pause_select_weapon(struct BarObj* self);
static void pause_select_tank(struct BarObj* self);
static void pause_select_exit(struct BarObj* self);
static void pause_use_tank(struct BarObj* self);
static void pause_use_weapon_tank(struct BarObj* self);
static void pause_options(struct BarObj* self);
static void pause_disconnected(struct BarObj* self);
static void pause_close(struct BarObj* self);
static void pause_close_start(struct BarObj* self);
static void pause_close_wait(struct BarObj* self);
static void pause_close_restore(struct BarObj* self);
static void pause_close_finish(struct BarObj* self);

const char saturn_pause_disconnect_text[5][20] = {
    "A control pad has\0\377\377",
    "been disconnected.\0\377",
    "Please connect it\0\377\377",
    "properly and press\0\377",
    "start button.\0\0\0    ",
};

static void (*const pause_states[])(struct BarObj*) = {
    pause_open,
    pause_menu,
    pause_close,
};

static void (*const pause_open_states[])(struct BarObj*) = {
    pause_open_start,
    pause_open_setup,
    pause_open_finish,
};

static const u8 pause_boss_order[8] = { 2, 6, 1, 4, 3, 0, 5, 7 };

static void (*const pause_menu_states[])(struct BarObj*) = {
    pause_select_weapon,
    pause_select_tank,
    pause_select_exit,
    pause_use_tank,
    pause_use_weapon_tank,
    pause_options,
    pause_disconnected,
};

static void (*const pause_close_states[])(struct BarObj*) = {
    pause_close_start,
    pause_close_wait,
    pause_close_restore,
    pause_close_finish,
};

void func_8002FCAC(void)
{
    pause_states[bar_object.state](&bar_object);
}

static void pause_open(struct BarObj* self)
{
    pause_open_states[self->unk5](self);
}

static void pause_open_start(struct BarObj* self)
{
    saturn_music_request(PAUSE_SOUND_KIND, 0, 0, 0);
    saturn_fade_start_out();
    saturn_render_frame();
    self->unk5 = 1;
}

static void pause_open_setup(struct BarObj* self)
{
    s8 weapon;
    u32 i;
    if (main_bss_state.transition.active != 0) {
        saturn_render_frame();
        return;
    }
    saturn_pause_enter();
    saturn_fade_start_in();
    self->unk5 = 2;
    self->unk14 = 0;
    if (g_Player.unk2 == 0) {
        self->options.fields.player[0] = 1;
        self->options.fields.player[1] = (((u8)g_Player.armor_parts) & 2) ? 1 : 0;
        for (i = 2; i < 10; i++)
            self->options.items[i] = (((u8)g_Player.boss_flags >> (i - 2)) & 1) ? 1 : 0;
    } else {
        for (i = 0; i < 8; i++)
            self->options.items[pause_boss_order[i]] = (((u8)g_Player.boss_flags >> i) & 1) ? 1 : 0;
        self->options.fields.weapons[7] = 0;
        self->options.fields.unk20 = 0;
    }
    if (engine_obj.collected_upgrades & 0x3000) {
        if (engine_obj.collected_upgrades & 0x1000) {
            self->options.fields.unk20 = 1;
            engine_obj.sub_tanks[0] |= PAUSE_TANK_SEEN;
        }
        if (engine_obj.collected_upgrades & 0x2000) {
            self->options.fields.unk21 = 1;
            engine_obj.sub_tanks[1] |= PAUSE_TANK_SEEN;
        }
    } else {
        self->options.fields.unk20 = 0;
        self->options.fields.unk21 = 0;
    }
    self->options.fields.unk22 = (engine_obj.collected_upgrades & 0x4000) ? 1 : 0;
    if (engine_obj.stage != 0) {
        self->options.fields.unk23 = ((((u8)engine_obj.palette_flags) >> (engine_obj.stage - 1)) & 1) ? 1 : 0;
    }
    self->options.fields.unk24 = 1;
    if (g_Player.unk2 != 0) {
        for (i = 0xA; i < 0xF; i++) {
            if (self->options.items[i] != 0) {
                self->unk14 = i;
                break;
            }
        }
    } else if ((engine_obj.stage == 5 && engine_obj.checkpoint == 0) || g_Player.ride_state < 0) {
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
        if (weapon != 0)
            self->unk14 = weapon + 1;
    }
    self->options.fields.unk25 = (engine_obj.collected_upgrades & 0x8000) ? 1 : 0;
    saturn_pause_weapon = g_Player.weapon;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk30 = 0;
}

static void pause_open_finish(struct BarObj* self)
{
    if (main_bss_state.transition.active == 0) {
        self->state = 1;
        self->unk5 = 0;
        if (g_Player.unk2 || self->unk2)
            self->unk5 = self->unk14 >= 0xD ? 2 : 1;
        if (saturn_pause_latch) {
            self->unk5 = 6;
            SHADOW16(0x20) |= 8;
            SHADOW16(0xFA) &= 0xFF;
            SHADOW16(0xFA) |= 0x304;
        }
    }
    saturn_pause_draw();
}

static void pause_menu(struct BarObj* self)
{
    pause_menu_states[self->unk5](self);
    if (self->unk5 < 5)
        saturn_pause_draw();
}

static void pause_sound(s32 id)
{
    func_8001540C(0, id, NULL);
}

static void pause_select_weapon(struct BarObj* self)
{
    s16 wrapped = 0;
    s8 initial = self->unk14;
    s8 next;
    u16 i;
    switch (saturn_pad_pressed) {
    case PAUSE_PAD_START:
        self->state = 2;
        self->unk5 = 0;
        break;
    case PAUSE_PAD_CONFIRM:
    case PAUSE_PAD_CONFIRM_ALT:
        if (self->unk14 >= 0 && self->unk14 <= 9)
            g_Player.weapon = self->unk14 <= 1 ? 0 : self->unk14 - 1;
        pause_sound(PAUSE_SOUND_CONFIRM);
        break;
    case PAUSE_PAD_UP:
        initial = self->unk14;
        next = initial;
        do {
            next -= 2;
            if (next < 0)
                next = self->unk14;
            if (self->unk14 == next || next == 0)
                break;
        } while (self->options.items[next] == 0);
        self->unk14 = next;
        break;
    case PAUSE_PAD_DOWN:
        initial = self->unk14;
        next = initial;
        do {
            next += 2;
            if (next < 0xA)
                continue;
            next = 9;
            for (i = 0; i < 5; i++) {
                next++;
                if (self->options.items[next] != 0) {
                    self->unk5 = next >= 0xD ? 2 : 1;
                    break;
                }
            }
            break;
        } while (self->unk14 != next && self->options.items[next] == 0);
        self->unk14 = next;
        break;
    case PAUSE_PAD_RIGHT:
        initial = self->unk14;
        next = initial + 1;
        if (!(next & 1))
            break;
        initial = next;
        if (self->options.items[next] == 0) {
            do {
                if (wrapped == 0) {
                    next += 2;
                    if (next > 10) {
                        next -= 2;
                        wrapped = 1;
                    }
                } else {
                    next -= 2;
                }
                if (next == initial) {
                    next = initial = self->unk14;
                    break;
                }
            } while (self->options.items[next] == 0);
        } else {
            initial--;
        }
        self->unk14 = next;
        break;
    case PAUSE_PAD_LEFT:
        initial = self->unk14;
        next = initial - 1;
        if (next & 1)
            break;
        initial = next;
        if (self->options.items[next] == 0) {
            do {
                if (wrapped == 0) {
                    next -= 2;
                    if (next < 0) {
                        next += 2;
                        wrapped = 1;
                    }
                } else {
                    next += 2;
                }
                if (next == initial) {
                    next = initial = self->unk14;
                    break;
                }
            } while (self->options.items[next] == 0);
        } else {
            initial++;
        }
        self->unk14 = next;
        break;
    }
    if (self->unk14 != initial)
        pause_sound(PAUSE_SOUND_MOVE);
}

static void pause_select_tank(struct BarObj* self)
{
    s8 previous = self->unk14;
    s8 next;
    switch (saturn_pad_pressed) {
    case PAUSE_PAD_START:
        self->state = 2;
        self->unk5 = 0;
        break;
    case PAUSE_PAD_CONFIRM:
    case PAUSE_PAD_CONFIRM_ALT:
        self->unk28 = 0;
        self->unk2C = 0;
        switch (self->unk14) {
        case PAUSE_ITEM_TANK_A:
            self->unk5 = 3;
            if ((engine_obj.sub_tanks[0] & PAUSE_TANK_MASK) == PAUSE_TANK_FULL)
                self->unk28 = 1;
            break;
        case PAUSE_ITEM_TANK_B:
            self->unk5 = 3;
            if ((engine_obj.sub_tanks[1] & PAUSE_TANK_MASK) == PAUSE_TANK_FULL)
                self->unk28 = 1;
            break;
        case PAUSE_ITEM_WEAPON_TANK:
            self->unk5 = 4;
            if ((engine_obj.sub_tanks[2] & PAUSE_TANK_MASK) == PAUSE_TANK_FULL)
                self->unk2C = 1;
            break;
        }
        break;
    case PAUSE_PAD_UP:
        if (g_Player.unk2 == 0 && self->unk2 == 0) {
            for (next = 9; next != 0 && self->options.items[next] == 0; next--) { }
            self->unk5 = 0;
            self->unk14 = next;
        }
        break;
    case PAUSE_PAD_RIGHT:
        next = self->unk14;
        for (;;) {
            next++;
            if (next > 12) {
                if (self->options.items[next] == 0)
                    next++;
                self->unk5 = 2;
                break;
            }
            if (self->options.items[next] != 0)
                break;
        }
        self->unk14 = next;
        break;
    case PAUSE_PAD_LEFT:
        next = self->unk14;
        for (;;) {
            next--;
            if (next < 10) {
                next = previous;
                break;
            }
            if (self->options.items[next] != 0)
                break;
        }
        self->unk14 = next;
        break;
    }
    if (self->unk14 != previous)
        pause_sound(PAUSE_SOUND_MOVE);
}

static void pause_select_exit(struct BarObj* self)
{
    u16 pressed = saturn_pad_pressed;
    s8 previous = self->unk14;
    s8 next;
    if (pressed & PAUSE_PAD_START) {
        self->state = 2;
        self->unk5 = 0;
    } else {
        switch (pressed) {
        case PAUSE_PAD_CONFIRM:
        case PAUSE_PAD_CONFIRM_ALT:
            if (self->unk14 == PAUSE_ITEM_EXIT) {
                self->state = 2;
                self->unk5 = 0;
                self->unk30 = 1;
            } else {
                self->unk5 = 5;
                self->unk6 = 0;
                saturn_pause_draw();
            }
            pause_sound(PAUSE_SOUND_CONFIRM);
            break;
        case PAUSE_PAD_UP:
            next = self->unk14;
            if (g_Player.unk2 == 0 && self->unk2 == 0) {
                for (;;) {
                    next--;
                    if (next < PAUSE_ITEM_EXIT) {
                        for (next = 9; next != 0 && self->options.items[next] == 0; next--) { }
                        self->unk5 = 0;
                        break;
                    }
                    if (next == self->unk14 || self->options.items[next] != 0)
                        break;
                }
                self->unk14 = next;
            } else {
                next--;
                if (next < PAUSE_ITEM_EXIT)
                    next = PAUSE_ITEM_EXIT;
                if (self->options.items[next] != 0)
                    self->unk14 = next;
            }
            break;
        case PAUSE_PAD_DOWN:
            next = self->unk14;
            for (;;) {
                next++;
                if (next >= PAUSE_ITEM_LAST + 1) {
                    next = PAUSE_ITEM_LAST;
                    break;
                }
                if (next == self->unk14 || self->options.items[next] != 0)
                    break;
            }
            self->unk14 = next;
            break;
        case PAUSE_PAD_LEFT:
            if (g_Player.unk2 == 0 && self->unk2 == 0) {
                for (next = 12; next != 0 && self->options.items[next] == 0; next--) { }
                self->unk14 = next;
                self->unk5 = next > 9 ? 1 : 0;
            } else {
                for (next = 12; next > 9; next--) {
                    if (next == 0 || self->options.items[next] != 0) {
                        self->unk14 = next;
                        self->unk5 = 1;
                        break;
                    }
                }
            }
            break;
        }
    }
    if (self->unk14 != previous)
        pause_sound(PAUSE_SOUND_MOVE);
}

static void pause_tank_shift(void)
{
    if (engine_obj.sub_tanks[1] < 0) {
        engine_obj.sub_tanks[0] = engine_obj.sub_tanks[1];
        engine_obj.sub_tanks[1] &= PAUSE_TANK_SEEN;
    }
}

static void pause_hp_add(s32 keep_sign)
{
    s8 hp = g_Player.hp;
    s8 sign = (s8)(hp & 0x80);
    hp = (s8)((hp & PAUSE_TANK_MASK) + 1);
    if (hp > engine_obj.max_hp)
        hp = engine_obj.max_hp;
    g_Player.hp = keep_sign ? (s8)(hp | sign) : hp;
}

static void pause_use_tank(struct BarObj* self)
{
    u8 tank;
    s8* level;
    s8 value;
    if (saturn_frame_counter & 1)
        return;
    tank = self->unk14 == PAUSE_ITEM_TANK_A ? 0 : 1;
    level = &engine_obj.sub_tanks[tank];
    if (self->unk28 != 0) {
        if (*level & PAUSE_TANK_MASK) {
            value = (s8)(*level & PAUSE_TANK_MASK);
            if (value != 0)
                value--;
            *level = (s8)(value | PAUSE_TANK_SEEN);
            pause_hp_add(0);
            if (!(saturn_frame_counter & 3))
                pause_sound(PAUSE_SOUND_REFILL);
        } else if (g_Player.hp != engine_obj.max_hp) {
            pause_hp_add(0);
            if (!(saturn_frame_counter & 3))
                pause_sound(PAUSE_SOUND_REFILL);
        } else {
            self->unk5 = 1;
            self->unk28 = 0;
            if (tank == 0)
                pause_tank_shift();
        }
    } else if (*level & PAUSE_TANK_MASK) {
        *level = (s8)(((*level & PAUSE_TANK_MASK) - 1) | PAUSE_TANK_SEEN);
        pause_hp_add(1);
        if (!(saturn_frame_counter & 3))
            pause_sound(PAUSE_SOUND_REFILL);
    } else {
        self->unk5 = 1;
        if (tank == 0)
            pause_tank_shift();
    }
}

static void pause_drain_weapon_tank(void)
{
    s8 value = (s8)(engine_obj.sub_tanks[2] & PAUSE_TANK_MASK);
    if (value != 0)
        value--;
    engine_obj.sub_tanks[2] = value;
}

static s32 pause_fill_weapons(s32 strict)
{
    s32 filled = 0;
    u32 i;
    for (i = 0; i < PAUSE_WEAPON_COUNT; i++) {
        s8* energy = &g_Player.weapon_energy[i];
        if (*energy >= PAUSE_WEAPON_ENERGY_MAX) {
            *energy = PAUSE_WEAPON_ENERGY_MAX;
        } else {
            (*energy)++;
            if (strict ? *energy >= PAUSE_WEAPON_ENERGY_MAX : *energy > PAUSE_WEAPON_ENERGY_MAX) {
                *energy = PAUSE_WEAPON_ENERGY_MAX;
            } else {
                filled = 1;
            }
        }
    }
    return filled;
}

static void pause_use_weapon_tank(struct BarObj* self)
{
    if (saturn_frame_counter & 1)
        return;
    if (self->unk2C != 0) {
        if (pause_fill_weapons(0)) {
            pause_drain_weapon_tank();
            if (!(saturn_frame_counter & 3))
                pause_sound(PAUSE_SOUND_REFILL);
        } else if (engine_obj.sub_tanks[2] & PAUSE_TANK_MASK) {
            pause_drain_weapon_tank();
        } else {
            self->unk5 = 1;
            self->unk2C = 0;
        }
        return;
    }
    if (!(engine_obj.sub_tanks[2] & PAUSE_TANK_MASK)) {
        self->unk5 = 1;
        return;
    }
    if (pause_fill_weapons(1)) {
        pause_drain_weapon_tank();
        if (!(saturn_frame_counter & 3))
            pause_sound(PAUSE_SOUND_REFILL);
    } else {
        self->unk5 = 1;
    }
}

static void pause_options(struct BarObj* self)
{
    switch (self->unk6) {
    case 0:
        saturn_fade_start_out();
        self->unk6++;
        break;
    case 1:
        if (main_bss_state.transition.active == 0)
            self->unk6++;
        break;
    case 2:
        func_8002A41C((struct GameInfo*)self);
        return;
    case 3:
        saturn_pause_reload();
        saturn_fade_start_in();
        self->unk6++;
        break;
    case 4:
        if (main_bss_state.transition.active == 0) {
            self->unk5 = 2;
            self->unk6 = 0;
            return;
        }
        break;
    default:
        return;
    }
    saturn_pause_draw();
}

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

static void pause_disconnected(struct BarObj* self)
{
    u32 i;
    switch (self->unk6) {
    case 0:
        self->unk28 = PAUSE_WINDOW_STEPS_OPEN;
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
        saturn_pause_draw();
        self->unk6++;
        return;
    case 1:
        if (--self->unk28 != 0) {
            pause_window_step(-8, 0);
        } else {
            self->unk28 = PAUSE_WINDOW_STEPS_MID;
            self->unk6++;
        }
        break;
    case 2:
        if (--self->unk28 != 0) {
            pause_window_step(0, -4);
        } else {
            self->unk28 = 0;
            self->unk6++;
        }
        break;
    case 3:
        if (saturn_pause_request == 0 && (saturn_pad_pressed & PAUSE_PAD_START)) {
            self->unk6++;
            self->unk28 = PAUSE_WINDOW_STEPS_MID;
            pause_sound(PAUSE_SOUND_CONFIRM);
        }
        break;
    case 4:
        if (--self->unk28 != 0) {
            pause_window_step(0, 4);
        } else {
            self->unk28 = PAUSE_WINDOW_STEPS_OPEN;
            self->unk6++;
        }
        break;
    case 5:
        if (--self->unk28 != 0) {
            pause_window_step(8, 0);
            break;
        }
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
        saturn_pause_latch = saturn_pause_request;
        self->unk28 = 0;
        saturn_text_layers_clear(8);
        return;
    default:
        return;
    }
    saturn_pause_draw();
}

static void pause_close(struct BarObj* self)
{
    pause_close_states[self->unk5](self);
}

static void pause_close_start(struct BarObj* self)
{
    saturn_fade_start_out();
    saturn_pause_draw();
    self->unk5 = 1;
}

static void pause_close_wait(struct BarObj* self)
{
    if (main_bss_state.transition.active != 0) {
        saturn_pause_draw();
        return;
    }
    saturn_pause_leave();
    self->unk5 = 2;
}

static void pause_close_restore(struct BarObj* self)
{
    if (self->unk30 == 0) {
        if (g_Player.unk2 == 0) {
            player_cancel_released_charge();
            if (saturn_pause_weapon != g_Player.weapon) {
                player_reset_charge(&g_Player);
                g_Player.stock_charge = 0;
            }
            player_update_shot_types(&g_Player);
            if (saturn_pause_weapon != g_Player.weapon)
                player_equip_weapon(&g_Player);
        }
        saturn_sprite_reset_queues();
        func_80021158();
        saturn_render_frame();
        saturn_fade_start_in();
    }
    self->unk5 = 3;
}

static void pause_close_finish(struct BarObj* self)
{
    if (main_bss_state.transition.active == 0) {
        if (self->unk30 == 0) {
            engine_obj.unk1 = 0;
            self->state = 0;
            self->unk5 = 0;
            if (engine_obj.stage == 5 && engine_obj.checkpoint == 0 && g_Player.ride_state < 0) {
                func_8001540C(PAUSE_RIDE_SOUND_KIND, PAUSE_RIDE_SOUND, NULL);
            }
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
            self->state = 0;
            self->unk5 = 0;
        }
    }
    if (self->unk30 == 0)
        saturn_render_frame();
}
