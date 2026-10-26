// EffectObj, effect_object_update_funcs[5]
// 800B60BC..800B6A0C
#include "common.h"
#include "main/effects/effect_05_tile_scanner.h"
#include "main/1CF60.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1CF60.h"
#endif

void tile_scanner_init(struct EffectObj*);

void (*tile_scanner_state_funcs[2])(struct EffectObj*) = {
    tile_scanner_init,
    func_800B64BC,
};

void (*tile_scanner_fill_funcs[1])(struct EffectObj*) = { func_800B6660 };

// tile_scanner_update

#if defined(MMX4_PC) || defined(MMX4_SATURN)
static u8 effect_05_probe(s16 x, s32 y_offset);
static void effect_05_dispatch(struct EffectObj* arg0);
void func_800B60BC(struct EffectObj* arg0);
void func_800B64BC(struct EffectObj* arg0);
static int effect_05_tile_slides(u8 tile);
void func_800B6660(struct EffectObj* arg0);
void func_800B6660(struct EffectObj* arg0);
static u8 effect_05_probe(s16 x, s32 y_offset)
{
    s16 y = (u16)g_Player.y_pos.i.hi + y_offset;

    if (g_Player.unk68 != NULL)
        y += (s8)g_Player.unk68->unk1 + g_Player.unk68->unk3;

    return func_8002D724(&g_Player, x, y);
}
static void effect_05_dispatch(struct EffectObj* arg0)
{
    if (arg0->state < 2)
        tile_scanner_state_funcs[arg0->state](arg0);
    else
        tile_scanner_fill_funcs[arg0->state - 2](arg0);
}
static int effect_05_tile_slides(u8 tile)
{
    return tile == 0x3C || tile == 0 || tile == 0x18 || tile == 0x1C || tile == 0x14 || tile == 0x1A;
}
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B60BC(struct EffectObj* arg0)
{
    struct Effect5Ext* ext = &arg0->ext.effect_5;
    s32 delta;
    s32 step;
    u8 tile;

    ext->unk21 = ext->unk20;
    ext->unk20 = effect_05_probe(g_Player.x_pos.i.hi, 0);
    delta = g_Player.x_pos.val - g_Player.unk18.val;
    if (g_Player.state != 1)
        goto facing;

    for (;;) {
        switch (ext->unk20) {
        case 0:
            if (arg0->state == 2)
                tile_scanner_fill_funcs[0](arg0);
            goto record;
        case 16:
            ext->unk20 = effect_05_probe(g_Player.x_pos.i.hi, -0x10);
            continue;
        case 17:
        case 18:
        case 19:
        case 20:
        case 25:
        case 26:
            arg0->state = 1;
            if (ext->unk21 == 0x3C && g_Player.unk15 != 0 && g_Player.unk5 != 0xC)
                goto hold;
            step = delta - 0x38000;
            if (step < -0x68000)
                step = -0x68000;
            goto push;
        case 21:
        case 22:
        case 23:
        case 24:
        case 27:
        case 28:
            arg0->state = 1;
            if (ext->unk21 == 0x3C && g_Player.unk15 == 0 && g_Player.unk5 != 0xC)
                goto hold;
            step = delta + 0x38000;
            if (step > 0x68000)
                step = 0x68000;
            goto push;
        case 60:
            effect_05_dispatch(arg0);
            goto record;
        default:
            arg0->state = 1;
            goto record;
        }
    }

hold:
    g_Player.x_pos.val = g_Player.unk18.val;
    goto probe;
push:
    g_Player.x_pos.val = g_Player.unk18.val + step;
probe:
    tile = effect_05_probe(g_Player.x_pos.i.hi, 0);
    ext->unk20 = tile;
    if (tile < 0x1D) {
        if (tile >= 0x10)
            goto facing;
        if (tile == 0 && arg0->state == 2)
            goto record;
    }
    effect_05_dispatch(arg0);
record:
    ext->unk1C = g_Player.unk5;
facing:
    if (g_Player.x_pos.val != g_Player.unk18.val)
        ext->unk1E = (g_Player.x_pos.val >= g_Player.unk18.val) << 6;
}
#else
INCLUDE_ASM("main/nonmatchings/effects/effect_05_tile_scanner", func_800B60BC);
#endif

void tile_scanner_init(struct EffectObj* self)
{
    self->state++;
    self->ext.effect_5.unk1C = 0;
    self->ext.effect_5.unk1E = 0;
    self->ext.effect_5.unk14 = 0;
    self->ext.effect_5.unk18 = 0;
}

// tile_scanner_scan
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/effects/effect_05_tile_scanner", func_800B64BC);
#else
void func_800B64BC(struct EffectObj* arg0)
{

    arg0->ext.effect_5.unk1F = 0;
    if (g_Player.state != 1)
        return;

    switch (g_Player.unk5) {
    case 48:
        if (arg0->ext.effect_5.unk1C != 0x32)
            return;
        arg0->ext.effect_5.unk14 = g_Player.x_vel.val;
        goto adjust;
    case 2:
        arg0->ext.effect_5.unk14 = g_Player.x_pos.val - g_Player.unk18.val;
    adjust:
        if (arg0->ext.effect_5.unk1C == 3)
            if (arg0->ext.effect_5.unk1E != 0)
                arg0->ext.effect_5.unk14 = 0x8000;
            else
                arg0->ext.effect_5.unk14 = -0x8000;
        if (arg0->ext.effect_5.unk1C == 4)
            if (arg0->ext.effect_5.unk1E != 0)
                arg0->ext.effect_5.unk14 = 0x20000;
            else
                arg0->ext.effect_5.unk14 = -0x20000;
        goto accelerate;
    case 5:
    case 8:
        arg0->ext.effect_5.unk14 = g_Player.x_vel.val;
    accelerate:
        if (arg0->ext.effect_5.unk1E != 0) {
            arg0->ext.effect_5.unk18 = -0x1800;
            arg0->ext.effect_5.unk1D = 1;
        } else {
            arg0->ext.effect_5.unk18 = 0x1800;
            arg0->ext.effect_5.unk1D = 0;
        }
        break;
    case 12: {
        s32 speed;

        if (g_Player.unk6 != 2)
            return;
        arg0->ext.effect_5.unk14 = 0;
        arg0->ext.effect_5.unk1F = (g_Player.x_vel.val >= 0 ? g_Player.x_vel.val : -g_Player.x_vel.val) / 0xC000;
        arg0->ext.effect_5.unk1E = g_Player.unk15;
        if (arg0->ext.effect_5.unk1E != 0) {
            arg0->ext.effect_5.unk18 = 0x2800;
            arg0->ext.effect_5.unk1D = 3;
        } else {
            arg0->ext.effect_5.unk18 = -0x2800;
            arg0->ext.effect_5.unk1D = 2;
        }
        break;
    }
    case 0:
    default:
        return;
    }
    arg0->state++;
}
#endif

// tile_scanner_flood_fill
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B6660(struct EffectObj* arg0)
{
    struct Effect5Ext* ext = &arg0->ext.effect_5;
    s16 x;
    s16 previous;

    if (g_Player.unk5 == 6 || g_Player.unk5 == 9 || (g_Player.unk88.bytes.collision_flags & 3)) {
        arg0->state = 1;
        return;
    }

    if (ext->unk1D < 2) {
        arg0->x_pos.val = g_Player.x_pos.val + ext->unk14;
        ext->unk14 += ext->unk18;
        if (!effect_05_tile_slides(effect_05_probe(arg0->x_pos.i.hi, 0))) {
            g_Player.x_pos.val = arg0->x_pos.val;
            arg0->state = 1;
            return;
        }
        g_Player.x_pos.val = arg0->x_pos.val;
        if (ext->unk1D != 0 ? ext->unk14 < 0 : ext->unk14 >= 0)
            arg0->state = 1;
    } else if (--ext->unk1F == 0xFF) {
        ext->unk18 = ext->unk18 > 0 ? -0x600 : 0x600;
        ext->unk1D -= 2;
        func_800B6660(arg0);
    } else {
        s32 moved;

        arg0->x_pos.val = g_Player.x_pos.val + ext->unk14;
        ext->unk14 += ext->unk18;
        if (!effect_05_tile_slides(effect_05_probe(arg0->x_pos.i.hi, 0))) {
            g_Player.x_pos.val = arg0->x_pos.val;
            arg0->state = 1;
            return;
        }
        g_Player.x_pos.val = arg0->x_pos.val;
        if (g_Player.unk5 != 0xC && g_Player.unk6 != 2) {
            moved = arg0->x_pos.val - g_Player.unk18.val;
            if (ext->unk14 > 0 ? ext->unk14 < moved : moved < ext->unk14)
                arg0->state = 1;
        }
    }

    x = g_Player.x_pos.i.hi;
    previous = g_Player.unk18.i.hi;
    if (ext->unk1D & 1) {
        if (g_Player.x_pos.val < g_Player.unk18.val && previous == x)
            arg0->state = 1;
    } else if (g_Player.unk18.val < g_Player.x_pos.val) {
        if (x - previous < 0 ? x != (s16)(previous - 1) : x - previous != 1)
            arg0->state = 1;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/effects/effect_05_tile_scanner", func_800B6660);
#endif
