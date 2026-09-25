// object pools, movement and angle helpers
// 8002A6FC..8002BB80
#include "common.h"

extern s32 D_800F459C[];
extern s32 D_800F45C0[];
extern u32 D_800F45E4[10];

void reset_game_engine()
{
    s8 fill = 0;
    s8* a0 = (u8*)&engine_obj;
    s32 v1 = sizeof(struct EngineObj) - 1;
    do {
        *a0++ = fill;
    } while (v1-- != 0);
}

void reset_entity(struct PlayerObj* arg0)
{
    s8 fill = 0;
    s32 v1 = sizeof(struct PlayerObj) - 1;
    s8* a0 = (u8*)arg0;
    do {
        *a0++ = fill;
    } while (v1-- != 0);
}

void reset_main_and_shots()
{
    s8 fill = 0;
    s32 a2;
    s32 var_v1;
    s8* var_a0;
    s8* a0;
    u32 a1;

    for (a1 = 0; a1 < COUNT(main_objects); a1++) {
        a0 = (u8*)&main_objects[a1];
        var_v1 = sizeof(main_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }

    for (a1 = 0; a1 < COUNT(shot_objects); a1++) {
        a0 = (u8*)&shot_objects[a1];
        var_v1 = sizeof(shot_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }
}

// some kind of reset?
void reset_objects(void)
{
    s8 fill = 0;
    s32 a2;
    s32 var_v1;
    s8* a0;
    u32 a1;

    reset_entity(&g_Player);
    reset_entity(&g_Entity);

    for (a1 = 0; a1 < COUNT(foo_objects); a1++) {
        a0 = (u8*)&foo_objects[a1];
        var_v1 = sizeof(foo_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }

    for (a1 = 0; a1 < COUNT(baz_objects); a1++) {
        a0 = (u8*)&baz_objects[a1];
        var_v1 = sizeof(baz_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }

    for (a1 = 0; a1 < COUNT(weapon_objects); a1++) {
        a0 = (u8*)&weapon_objects[a1];
        var_v1 = sizeof(weapon_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }

    reset_main_and_shots(); // clear main_objects and shot_objects

    for (a1 = 0; a1 < COUNT(visual_objects); a1++) {
        a0 = (u8*)&visual_objects[a1];
        var_v1 = sizeof(visual_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }

    for (a1 = 0; a1 < COUNT(effect_objects); a1++) {
        a0 = (u8*)&effect_objects[a1];
        var_v1 = sizeof(effect_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }

    for (a1 = 0; a1 < COUNT(item_objects); a1++) {
        a0 = (u8*)&item_objects[a1];
        var_v1 = sizeof(item_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }

    for (a1 = 0; a1 < COUNT(misc_objects); a1++) {
        a0 = (u8*)&misc_objects[a1];
        var_v1 = sizeof(misc_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }

    for (a1 = 0; a1 < COUNT(unk_objects); a1++) {
        a0 = (u8*)&unk_objects[a1];
        var_v1 = sizeof(unk_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }

    for (a1 = 0; a1 < COUNT(layer_objects); a1++) {
        a0 = (u8*)&layer_objects[a1];
        var_v1 = sizeof(layer_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }

    for (a1 = 0; a1 < COUNT(g_QuadObjects); a1++) {
        a0 = (u8*)&g_QuadObjects[a1];
        var_v1 = sizeof(g_QuadObjects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }

    a0 = (u8*)&qux_object;
    var_v1 = sizeof(qux_object);
    while (var_v1-- != 0) {
        *a0++ = fill;
    }

    a0 = (u8*)&bar_object;
    var_v1 = sizeof(bar_object);
    while (var_v1-- != 0) {
        *a0++ = fill;
    }

    g_FilterAmountB = 0;
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 0;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 0;
    D_8013E188[0] = 0;
    D_8013E188[1] = 0;
    D_8013E188[2] = 0;
    D_8013E188[3] = 0;

    a0 = (u8*)&abc_object;
    var_v1 = sizeof(abc_object);
    while (var_v1-- != 0) {
        *a0++ = fill;
    }
}

void func_8002AB20()
{
    s8 fill = 0;
    u32 i;
    for (i = 0; i < 3; i++) {
        s8* a0 = (u8*)&background_objects[i];
        s32 v1 = sizeof(struct BackgroundObj) - 1;
        do {
            *a0++ = fill;
        } while (v1-- != 0);
        background_objects[i].unk2 = i;
    }
}

struct MainObj* find_free_main_obj(void)
{
    struct MainObj* var_v1;
    for (var_v1 = &main_objects[0]; var_v1 < &main_objects[0x30]; var_v1++) {
        if (!var_v1->active) {
            var_v1->unk50 = 0;
            var_v1->unk54 = 0;
            var_v1->unk68 = 0;
            var_v1->unk61 = 0;
            var_v1->unk64 = 0;
            var_v1->unk65 = 0;
            var_v1->unk66 = 0;
            var_v1->unk72 = 0;
            var_v1->unk73 = 0;
            var_v1->unk74 = 0;
            var_v1->unk76 = 0;
            var_v1->unk77 = 0;
            var_v1->unk78 = 0;
            var_v1->unk62 = 0;
            var_v1->unk63 = 0;
            var_v1->unk7A = 0;
            var_v1->unk5D = 0;
            var_v1->unk75 = 0;
            return var_v1;
        }
    }

    return NULL;
}

struct WeaponObj* find_free_weapon_obj()
{
    struct WeaponObj* current;
    for (current = &weapon_objects[0]; current < &weapon_objects[0x10]; current++) {
        if (!current->active) {
            current->unk50 = NULL;
            current->unk54 = 0;
            current->unk68 = 0;
            current->unk98 = 0;
            current->unk61 = 0;
            current->unk64 = 0;
            current->unk65 = 0;
            current->unk66 = 0;
            current->unk72 = 0;
            current->unk73 = 0;
            current->unk74 = 0;
            current->unk76 = 0;
            current->unk77 = 0;
            current->unk78 = 0;
            current->unk62 = 0;
            current->unk63 = 0;
            current->unk7A = 0;
            current->unk75 = 0;
            return current;
        }
    }

    return NULL;
}

struct ShotObj* find_free_shot_obj(void)
{
    struct ShotObj* current;
    for (current = &shot_objects[0]; current < &shot_objects[0x20]; current++) {
        if (!current->active) {
            current->unk50.data = NULL;
            current->unk54 = 0;
            current->unk68 = 0;
            current->unk98 = 0;
            current->unk61 = 0;
            current->unk64 = 0;
            current->unk65 = 0;
            current->unk66 = 0;
            current->unk72 = 0;
            current->unk73 = 0;
            current->unk74 = 0;
            current->unk76 = 0;
            current->unk77 = 0;
            current->unk78 = 0;
            current->unk62 = 0;
            current->unk63 = 0;
            current->unk7A = 0;
            current->unk75 = 0;
            return current;
        }
    }

    return NULL;
}

struct VisualObj* find_free_visual_obj()
{
    struct VisualObj* current;
    for (current = &visual_objects[0]; current < &visual_objects[0x20]; current++) {
        if (current->active == NULL) {
            return current;
        }
    }

    return NULL;
}

struct EffectObj* find_free_effect_obj(void)
{
    struct EffectObj* var_v0;
    for (var_v0 = &effect_objects[0]; var_v0 < &effect_objects[0x20]; var_v0++) {
        if (!var_v0->active) {
            return var_v0;
        }
    }
    return NULL;
}

struct ItemObj* find_free_item_obj()
{
    struct ItemObj* current;
    for (current = &item_objects[0]; current < &item_objects[0x20]; current++) {
        if (!current->active) {
            current->unk50 = NULL;
            current->unk54 = 0;
            current->unk68 = 0;
            current->unk61 = 0;
            current->unk64 = 0;
            current->unk65 = 0;
            current->unk66 = 0;
            current->unk72 = 0;
            current->unk73 = 0;
            current->unk74 = 0;
            current->unk76 = 0;
            current->unk77 = 0;
            current->unk78 = 0;
            current->unk62 = 0;
            current->unk63 = 0;
            current->unk7A = 0;
            current->unk75 = 0;
            return current;
        }
    }

    return NULL;
}

struct MiscObj* find_free_misc_obj(void)
{
    struct MiscObj* var_v0;
    for (var_v0 = &misc_objects[0]; var_v0 < &misc_objects[0x40]; var_v0++) {
        if (!var_v0->active) {
            return var_v0;
        }
    }
    return NULL;
}

struct MiscObj* func_8002AE90(struct MiscObj* arg0, s32 arg1)
{
    if (arg1 == 0) {
        if (arg0 == 0) {
            arg0 = misc_objects;
        } else {
            arg0++;
        }
        while (arg0 < &misc_objects[COUNT(misc_objects)]) {
            if (arg0->active == 0) {
                return arg0;
            }
            arg0++;
        }
    } else {
        if (arg0 == 0) {
            arg0 = &misc_objects[COUNT(misc_objects)] - 1;
        } else if (arg0 != misc_objects) {
            arg0--;
        } else {
            return NULL;
        }
        while (arg0 >= misc_objects) {
            if (arg0->active == 0) {
                return arg0;
            }
            arg0--;
        }
    }
    return NULL;
}

struct VisualObj* func_8002AF4C(struct VisualObj* arg0, s32 arg1)
{
    if (arg1 == 0) {
        if (arg0 == 0) {
            arg0 = visual_objects;
        } else {
            arg0++;
        }
        while (arg0 < &visual_objects[COUNT(visual_objects)]) {
            if (arg0->active == 0) {
                return arg0;
            }
            arg0++;
        }
    } else {
        if (arg0 == 0) {
            arg0 = &visual_objects[COUNT(visual_objects)] - 1;
        } else if (arg0 != visual_objects) {
            arg0--;
        } else {
            return NULL;
        }
        while (arg0 >= visual_objects) {
            if (arg0->active == 0) {
                return arg0;
            }
            arg0--;
        }
    }
    return NULL;
}

struct QuadObj* find_free_quad_obj()
{
    struct QuadObj* current = g_QuadObjects;
    struct QuadObj* end = &g_QuadObjects[32];

    while (current < end) {
        if (current->active == 0) {
            return current;
        }
        current++;
    }

    return NULL;
}

struct LayerObj* find_free_layer_obj()
{
    struct LayerObj* current;
    for (current = &layer_objects[0]; current < &layer_objects[4]; current++) {
        if (!current->active) {
            return current;
        }
    }

    return NULL;
}

struct UnkObj* find_free_unk_obj()
{
    struct UnkObj* current;

    for (current = &unk_objects[0]; current < &unk_objects[20]; current++) {
        if (!current->active) {
            return current;
        }
    }

    return NULL;
}

void func_8002B0C8(struct ObjectHeader* arg0)
{
    if (arg0->backref != NULL) {
        *(u8*)arg0->backref &= 0x70;
    }
    ZeroObjectState(arg0);
}

void func_8002B108(struct ObjectHeader* arg0)
{
    if (arg0->backref != NULL) {
        *(u8*)arg0->backref = 0x80;
    }
    ZeroObjectState(arg0);
}

void ZeroObjectState(struct ObjectHeader* arg0)
{
    arg0->active = 0;
    arg0->id = 0;
    arg0->unk2 = 0;
    arg0->on_screen = 0;
    arg0->state = 0;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

INCLUDE_ASM("main/nonmatchings/objects", func_8002B160);

INCLUDE_ASM("main/nonmatchings/objects", func_8002B1E8);

void is_on_screen(struct BaseObj* arg0)
{
    s16 x_pos;
    s16 y_pos;

    arg0->on_screen = 0;
    if (arg0->bg_offset < 0) {
        x_pos = arg0->x_pos.i.hi;
        y_pos = arg0->y_pos.i.hi;
    } else {
        x_pos = arg0->x_pos.i.hi - background_objects[arg0->bg_offset].x_pos.i.hi;
        y_pos = arg0->y_pos.i.hi - background_objects[arg0->bg_offset].y_pos.i.hi;
    }
    // check if the object is within 320x240 viewport += 32
    if (x_pos >= -32 && x_pos < 352 && y_pos >= -32 && y_pos < 272) {
        arg0->on_screen = 1;
    }
}

void func_8002B318(struct BaseObj* arg0, s32 arg1, s32 arg2)
{
    u16 x_pos, y_pos, y_pos_2;
    u16 x_diff, y_diff;

    arg0->on_screen = 0;
    if (arg0->bg_offset < 0) {
        x_pos = arg0->x_pos.i.hi;
        y_pos = arg0->y_pos.i.hi;
    } else {
        x_pos = arg0->x_pos.i.hi - background_objects[arg0->bg_offset].x_pos.i.hi;
        y_pos = arg0->y_pos.i.hi - background_objects[arg0->bg_offset].y_pos.i.hi;
    }
    x_pos += arg1;
    x_diff = 0x140 + arg1 + arg1;
    if (x_pos < x_diff) {
        y_pos_2 = y_pos + arg2;
        y_diff = 0xF0 + arg2 + arg2;
        if (y_pos_2 < y_diff) {
            arg0->on_screen = 1;
        }
    }
}

void func_8002B3C0(struct BaseObj* arg0)
{
    s16 x_pos;
    s16 y_pos;

    arg0->on_screen = 0;
    if (arg0->bg_offset < 0) {
        x_pos = arg0->x_pos.i.hi;
        y_pos = arg0->y_pos.i.hi;
    } else {
        x_pos = arg0->x_pos.i.hi - background_objects[arg0->bg_offset].x_pos.i.hi;
        y_pos = arg0->y_pos.i.hi - background_objects[arg0->bg_offset].y_pos.i.hi;
    }
    if (x_pos >= -0x60 && x_pos < 0x1A0 && y_pos >= -0x50 && y_pos < 0x140) {
        arg0->on_screen = 1;
    }
}

void func_8002B450(void)
{
}

void func_8002B458(struct QuadObj* arg0)
{
}

void func_8002B460(void)
{
}

struct EffectObj* func_8002B468(s8 id, s8 arg1)
{
    struct EffectObj* effect;
    s8 i;

    i = 0;
    if (id >= 0) {
        do {
            effect = &effect_objects[i];
            if (effect->active != 0 && effect->id == id && effect->unk2 == arg1) {
                return effect;
            }
            i++;
        } while (i < 0x20);
    } else {
        id &= 0x7F;
        do {
            effect = &effect_objects[i];
            if (effect->active != 0 && effect->id == id) {
                return effect;
            }
            i++;
        } while (i < 0x20);
    }
}

INCLUDE_ASM("main/nonmatchings/objects", func_8002B560);

void func_8002B694(struct AnimatedObj* arg0)
{
    arg0->x_pos.val += arg0->x_vel.val;
    arg0->y_pos.val -= arg0->y_vel.val;

    if (arg0->unk15) {
        arg0->x_vel.val += arg0->unk28;
    } else {
        arg0->x_vel.val -= arg0->unk28;
    }

    arg0->y_vel.val -= arg0->unk2C;
    if (arg0->y_vel.val < FIXED(-6.5)) {
        arg0->y_vel.val = FIXED(-6.5);
    }
}

void func_8002B718(struct MovingObj* arg0)
{
    arg0->x_pos.val += arg0->x_vel.val;
    arg0->y_pos.val -= arg0->y_vel.val;
}

u8 get_random()
{
    u16 temp = cur_random * 3;
    u32 temp_v1;
    u8 pad[2];

    temp_v1 = temp >> 8;
    cur_random += temp_v1;
    cur_random &= 0xFF;
    cur_random |= temp_v1 << 8;

    return cur_random;
}

s32 func_8002B780(void)
{
    s32 random_value;
    s32 result;

    random_value = get_random() & 0xFF;
    result = 1;
    if (random_value != 0) {
        result = random_value;
    }
    return result;
}

s32 func_8002B7B0(struct ObjectHeader* arg0, s32 arg1, s32 arg2)
{
    return func_8002B810(arg0->x_pos.val - arg1, arg0->y_pos.val - arg2) & 0xFF;
}

s32 func_8002B7DC(struct ObjectHeader* arg0, struct ObjectHeader* arg1)
{
    return func_8002B810(arg0->x_pos.val - arg1->x_pos.val,
               arg0->y_pos.val - arg1->y_pos.val)
        & 0xFF;
}

s32 func_8002B810(s32 arg0, s32 arg1)
{
    extern u32 D_800F45E4[];
    s32 temp_lo;
    s32 angle;
    s16 var_a3, var_a2;
    u32* ptr;

    var_a2 = -1;
    if (arg0 < 0) {
        var_a2 = 1;
        arg0 = -arg0;
    }
    var_a3 = 1;
    if (arg1 < 0) {
        var_a3 = -1;
        arg1 = -arg1;
    }

    if (arg1 >> 0x10 != 0) {
        temp_lo = arg0 / (arg1 >> 0x10);
        if (temp_lo <= 0xFFFF) {
            ptr = &D_800F45E4[4];
            while (temp_lo < *ptr) {
                ptr--;
            }
#ifdef MMX4_PC
            arg0 = ptr - D_800F45E4;
#else
            arg0 = ((u32)ptr - (u32)D_800F45E4) >> 2;
#endif
        } else {
            ptr = &D_800F45E4[5];
            while (*ptr < temp_lo) {
                ptr++;
            }
            arg0 = ptr - D_800F45E4 - 1;
        }
    } else {
        arg0 = 8;
    }

    if (var_a3 << 0x10 < 0) {
        if (var_a2 << 0x10 > 0) {
            if ((s16)arg0 == 8) {
                return 0;
            }
            angle = 0x18 + arg0;
        } else {
            angle = 0x18 - arg0;
        }
    } else {
        angle = (var_a2 << 0x10) <= 0 ? arg0 + 8 : 8 - arg0;
    }

    return angle & 0xFF;
}

extern s32 D_800F459C[];

extern s32 D_800F45C0[];

void func_8002B93C(struct MovingObj* arg0, s32 arg1)
{
    u8 angle;
    s16 var_a2, var_v0;
    s16 var_v1;

    angle = arg1;
    if (angle < 0x10) {
        var_a2 = 1;
        if (angle < 8) {
            var_v1 = 8 - angle;
            var_v0 = 1;
        } else {
            var_v1 = angle - 8;
            var_v0 = -1;
        }
    } else {
        var_a2 = -1;
        if (angle < 0x18) {
            var_v1 = 0x18 - angle;
            var_v0 = -1;
        } else {
            var_v1 = angle - 0x18;
            var_v0 = 1;
        }
    }
    arg0->x_vel.val = D_800F459C[var_v1] * var_v0;
    arg0->y_vel.val = D_800F45C0[var_v1] * var_a2;
}

void func_8002B9F0(s32* arg0, s32* arg1, u8 arg2)
{
    s16 var_a3, var_v0;
    s16 var_v1;

    if (arg2 < 0x10) {
        var_a3 = 1;
        if (arg2 < 8) {
            var_v1 = 8 - arg2;
            var_v0 = 1;
        } else {
            var_v1 = arg2 - 8;
            var_v0 = -1;
        }
    } else {
        var_a3 = -1;
        if (arg2 < 0x18) {
            var_v1 = 0x18 - arg2;
            var_v0 = -1;
        } else {
            var_v1 = arg2 - 0x18;
            var_v0 = 1;
        }
    }
    *arg0 = D_800F459C[var_v1] * var_v0;
    *arg1 = D_800F45C0[var_v1] * var_a3;
}

s16 func_8002BAA4(void)
{
    u16 flags = g_Player.pressed_input;
    s16 count = (flags & 0xF) != 0;
    if (flags & 0x1B0) {
        count++;
    }
    return count;
}

s16 func_8002BAD0(s16 arg0, s16 arg1, s16 arg2)
{
    struct BackgroundObj* temp_v1 = &background_objects[arg0];
    s16 var_x, var_y;
    s16 temp;

    var_x = (temp_v1->x_pos.i.hi + arg1) / 256;
    var_y = (temp_v1->y_pos.i.hi + arg2) / 256;
    temp = var_x + (arg0 * layout_size + layout_width * var_y);

    return SP_BG_TILEMAP[temp];
}

s32 D_800F459C[] = {
    0,
    0x31F1,
    0x61F7,
    0x8E39,
    0xB505,
    0xD4DB,
    0xEC83,
    0xFB14,
    0x10000,
};

s32 D_800F45C0[] = {
    0x10000,
    0xFB14,
    0xEC83,
    0xD4DB,
    0xB505,
    0x8E39,
    0x61F7,
    0x31F1,
    0,
};

u32 D_800F45E4[10] = {
    0,
    0x1936,
    0x4DA8,
    0x88D5,
    0xD218,
    0x137EF,
    0x1DEF1,
    0x34BEB,
    0xA2736,
    0xFFFFFFFF,
};
