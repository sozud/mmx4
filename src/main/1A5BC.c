#include "common.h"

s32 func_8002D6BC(struct PlayerObj* arg0, u8 arg1);
s32 func_8002CAF0(struct PlayerObj* arg0, u8 arg1);
s32 func_8002CC34(struct PlayerObj* arg0, u8 arg1);
s32 func_8002CD70(struct PlayerObj* arg0, u8 arg1);
void func_8002CA18(struct PlayerObj* arg0);
void func_8002CB58(struct PlayerObj* arg0);
void func_8002CC98(struct PlayerObj* arg0);

// might also be inlined inside reset_objects
void func_80029DBC(void)
{
    u16 a1;
    u16 var_v1;
    u8* a0;
    u8 fill = 0;

    for (a1 = 0; a1 < COUNT(unk_objects); a1++) {
        a0 = (u8*)&unk_objects[a1];
        var_v1 = sizeof(unk_objects[0]) - 1;
        do {
            *a0++ = fill;
        } while (var_v1-- != 0);
    }
}

void func_80029E1C(struct GameInfo* arg0)
{
    struct UnkObj* obj;
    u8* var_s1;

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->unk2 = 0x5E;
        obj->id = 0;
        obj->y_pos.i.hi = 0x10;
    }

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->id = 0;
        obj->unk2 = -1;
        if (D_80141BE0 != 0) {
            obj->unk50 = D_800F4568;
        } else {
            obj->unk50 = D_800F457C;
        }
#ifdef VERSION_JP
        obj->x_pos.i.hi = 0x20;
#else
        obj->x_pos.i.hi = 0x38;
#endif
    }

    if (D_80141BE0 != 0) {
        var_s1 = D_800F4508;
    } else {
        var_s1 = D_800F4560[engine_obj.cur_character];
    }
    while (var_s1[0] != 0xFF) {
        obj = find_free_unk_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0;
            obj->unk2 = var_s1[0];
            obj->y_pos.i.hi = var_s1[1];
            obj->unk7 = var_s1[2];
        }
        if (var_s1[2] == 7) {
            break;
        }
        var_s1 += 3;
    }

    var_s1 = D_800F457C;
    if (D_80141BE0 != 0) {
        var_s1 = D_800F4568;
    }
    if (var_s1[1] != 7) {
        do {
            obj = find_free_unk_obj();
            if (obj != NULL) {
                obj->active = 1;
                obj->id = 0;
                obj->unk2 = var_s1[1];
                obj->y_pos.i.hi = var_s1[0];
            }
            var_s1 += 2;
        } while (var_s1[1] != 7);
    }

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->unk2 = -2;
        obj->id = 0;
        obj->x_pos.i.hi = 0x20;
    }

    if (D_80141BE0 == 0) {
        func_8001E980(0);
    }
    D_80141BDF[0] = 0;
    func_800129A4(8);
    D_8013B7D0++;
}

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002A098);

void func_8002A394(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (D_80141BE0 != 0) {
            arg0->unk0 = 8;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
        } else {
            (*(s8*)&arg0->unk6)++;
        }
        func_80029DBC();
        if (D_80141BE0 != 0) {
            func_8001E980(1);
        }
        D_8013B7D0 = 0;
    }
}

void func_8002A41C(struct GameInfo* arg0)
{
    func_8002B460(); // no-op
    D_800F4590[D_8013B7D0](arg0);
    update_unk_objects();
    func_80016124();
    func_80025CDC();
}

void func_8002A484(void)
{
    u32 mask;
    u32 color;
    u16 copy_color;
    u16* dst;
    u16* src;
    u32 component;
    u32 blue;
    u32 green;
    u32 color_index;
    u32 red;
    u32 palette_index;

    if ((((g_FilterAmountB | (g_FilterAmountR | g_FilterAmountG)) != 0) || (need_palette_load & 4)) && ((lastFilterAmountR != g_FilterAmountR) || (lastFilterAmountG != g_FilterAmountG) || (lastFilterAmountB != g_FilterAmountB) || (need_palette_load != 0))) {
        src = dst = SP_PALETTE;
        dst = D_80141F70;
        for (palette_index = 0; palette_index < 128; palette_index++, mask <<= 1) {
            if (!(palette_index & 0x1F)) {
                mask = D_8013E188[palette_index >> 5];
            }
            color_index = 0;
            if ((s32)mask < 0) {
                do {
                    color = *src;
                    src++;
                    if (color != 0) {
                        if (g_FilterModeR != 0) {
                            red = 0;
                            if ((color & 0x1F) >= g_FilterAmountR) {
                                red = (color & 0x1F) - g_FilterAmountR;
                            }
                        } else {
                            component = (color & 0x1F) + g_FilterAmountR;
                            red = 0x1F;
                            if (component < 0x20U) {
                                red = component;
                            }
                        }
                        if (g_FilterModeG != 0) {
                            green = 0;
                            if ((color & 0x3E0) >= g_FilterAmountG) {
                                green = (color & 0x3E0) - g_FilterAmountG;
                            }
                        } else {
                            component = (color & 0x3E0) + g_FilterAmountG;
                            green = 0x3E0;
                            if (component < 0x3E1U) {
                                green = component;
                            }
                        }
                        if (g_FilterModeB != 0) {
                            blue = 0;
                            if ((color & 0x7C00) >= g_FilterAmountB) {
                                blue = (color & 0x7C00) - g_FilterAmountB;
                            }
                        } else {
                            component = (color & 0x7C00) + g_FilterAmountB;
                            blue = 0x7C00;
                            if (component < 0x7C01U) {
                                blue = component;
                            }
                        }
                        *dst = red | green | blue | (color & 0x8000);
                    }
                    color_index += 1;
                    dst++;
                } while (color_index < 0x10U);
            } else {
                do {
                    copy_color = *src;
                    src++;
                    color_index += 1;
                    *dst = copy_color;
                    dst++;
                } while (color_index < 0x10U);
            }
        }
        need_palette_load = 2;
        lastFilterAmountR = g_FilterAmountR;
        lastFilterAmountG = g_FilterAmountG;
        lastFilterAmountB = g_FilterAmountB;
    }
}

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
            current->unk50 = 0;
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

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002B160);

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002B1E8);

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

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002B468);

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002B560);

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

u8 func_8002B7DC(struct ObjectHeader* arg0, struct ObjectHeader* arg1)
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
INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002BAA4);

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

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002BB80);

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002BD58);

s32 func_8002C160(struct CollisionObj* arg0, struct CollisionObj* arg1)
{
    s16 center0;
    s16 center1;
    s16 distance;
    struct Unk_unk68* bounds0;
    struct Unk_unk68* bounds1;
    struct Unk_unk68* initial_bounds0;
    struct Unk_unk68* initial_bounds1;
    struct CollisionObj* object1;
    struct CollisionObj* object0;

    object0 = arg0;
    object1 = arg1;
    initial_bounds0 = object0->collision_bounds;
    if (initial_bounds0 == NULL) {
        return 0;
    }
    initial_bounds1 = object1->collision_bounds;
    if (initial_bounds1 == NULL) {
        return 0;
    }

    center0 = object0->x_pos.i.hi + initial_bounds0->unk0;
    center1 = object1->x_pos.i.hi + initial_bounds1->unk0;
    if ((center0 - center1) >= 0) {
        distance = center0 - center1;
    } else {
        distance = center1 - center0;
    }

    bounds0 = object0->collision_bounds;
    bounds1 = object1->collision_bounds;
    if (distance >= bounds0->unk2 + bounds1->unk2) {
        return 0;
    }

    center0 = object0->y_pos.i.hi + bounds0->unk1;
    center1 = object1->y_pos.i.hi + bounds1->unk1;
    if ((center0 - center1) >= 0) {
        distance = center0 - center1;
    } else {
        distance = center1 - center0;
    }
    return distance < object0->collision_bounds->unk3 + object1->collision_bounds->unk3;
}

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002C26C);

void func_8002C2EC(struct CollisionObj* arg0, struct CollisionObj* arg1)
{
    s16 center0;
    s16 center1;
    struct Unk_unk68* bounds1;
    struct Unk_unk68* bounds0;

    bounds0 = arg0->collision_bounds;
    bounds1 = arg1->collision_bounds;
    center0 = arg0->y_pos.i.hi + bounds0->unk1;
    center1 = arg1->y_pos.i.hi + bounds1->unk1;
    if (center0 > center1) {
        center0 = center0 - bounds0->unk3;
        center1 = bounds1->unk3 + center1;
    } else {
        center0 = bounds0->unk3 + center0;
        center1 = center1 - bounds1->unk3;
    }
    arg1->unk6E = center0 - center1;
}

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002C36C);

// megaman falls through floor in intro stage if nopped out
// asm(".rept 81 ; nop ; .endr");
void CollisionRelated(struct PlayerObj* arg0) // was func_8002C614
{
    s32 temp_v1;

    arg0->unk70 = 0;
    arg0->unk79 = 0;

    if (arg0->unk68 != NULL) {
        func_8002C760(arg0);
        temp_v1 = arg0->x_pos.val - arg0->unk18;
        D_8013B7D8 = 0;
        D_8013B7DC = 0;

        if (temp_v1 != 0) {
            if (temp_v1 > 0) {
                func_8002CB58(arg0);
            } else {
                func_8002CA18(arg0);
            }
        }

        if (arg0->y_pos.val - arg0->unk1C >= 0) {
            func_8002CDD4(arg0);
            if (D_8013B7D8 != 0) {
                return;
            }
        } else {
            func_8002CC98(arg0);
        }

        if (D_8013B7DC & 0xC) {
            if ((D_8013B7DC & 3) != 0) {
                if ((D_8013B7DC & 4) || (D_8013B804 >= -8)) {
                    func_8002C954(arg0);
                } else {
                    func_8002C99C(arg0);
                }
            } else {
                func_8002D25C(arg0);
            }
        } else if ((D_8013B7DC & 3) != 0) {
            func_8002D490(arg0);
        }

        func_8002C808(arg0);
    }
}

void func_8002C760(struct PlayerObj* arg0)
{
    struct Unk_unk68* temp_v1 = arg0->unk68;
    u16 temp_a1 = arg0->x_pos.i.hi;
    u16 temp_v0 = temp_v1->unk0;

    D_8013B7E8 = temp_v1->unk0;
    D_8013B7EC = temp_v1->unk1;
    D_8013B7E0 = temp_v1->unk2;
    D_8013B7E4 = temp_v1->unk3;

    D_8013B7F0 = temp_a1;
    D_8013B7F4 = arg0->y_pos.i.hi;

    if (arg0->unk15 == 0) {
        D_8013B7F8 = temp_a1 + temp_v0;
    } else {
        D_8013B7F8 = temp_a1 - temp_v0;
    }
    D_8013B7FC = D_8013B7F4 + D_8013B7EC;
}

void func_8002C808(struct PlayerObj* arg0)
{
    arg0->unk70 = 0;
    arg0->unk79 = 0;
    if (arg0->unk68 != NULL) {
        func_8002C760(arg0);
        if (func_8002D5E4(arg0, D_8013B7F8 - D_8013B7E0 - 1)) {
            arg0->unk70 |= 2;
        }
        if (func_8002D5E4(arg0, D_8013B7F8 + D_8013B7E0)) {
            arg0->unk70 |= 1;
        }
        if (func_8002D32C(arg0, D_8013B7F4 + D_8013B7EC + D_8013B7E4, 1)) {
            arg0->unk70 |= 8;
        }
        if (func_8002D32C(arg0, D_8013B7F4 + D_8013B7EC - D_8013B7E4 - 1, 0)) {
            arg0->unk70 |= 4;
        }
    }
}

void func_8002C954(struct PlayerObj* arg0)
{
    if ((func_8002D25C(arg0) != 0) && (func_8002D490(arg0) != 0)) {
        func_8002C9E4(arg0);
    }
}

void func_8002C99C(struct PlayerObj* arg0)
{
    if ((func_8002D490() != 0) && (func_8002D25C(arg0) != 0)) {
        func_8002C9E4(arg0);
    }
}

void func_8002C9E4(struct PlayerObj* arg0)
{
    arg0->x_pos.u.lo = 0;
    arg0->y_pos.u.lo = 0;
    arg0->x_pos.u.hi += D_8013B800;
    arg0->y_pos.u.hi += D_8013B804;
}

void func_8002CA18(struct PlayerObj* arg0)
{
    s16 temp_v0;

    temp_v0 = D_8013B7F8 - D_8013B7E0;
    if ((func_8002CAF0(arg0, func_8002D7E4(arg0, temp_v0, D_8013B7FC)) == 0) && (func_8002CAF0(arg0, func_8002D7E4(arg0, temp_v0, D_8013B7FC - D_8013B7E4)) == 0)) {
        func_8002CAF0(arg0,
            func_8002D7E4(arg0, temp_v0, D_8013B7FC + D_8013B7E4 - 1));
    }
}

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002CAF0);

void func_8002CB58(struct PlayerObj* arg0)
{
    s16 temp_v0;

    temp_v0 = (D_8013B7F8 + D_8013B7E0) - 1;
    if ((func_8002CC34(arg0, func_8002D7E4(arg0, temp_v0, D_8013B7FC)) == 0) && (func_8002CC34(arg0, func_8002D7E4(arg0, temp_v0, D_8013B7FC - D_8013B7E4)) == 0)) {
        func_8002CC34(arg0,
            func_8002D7E4(arg0, temp_v0, D_8013B7FC + D_8013B7E4 - 1));
    }
}

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002CC34);

void func_8002CC98(struct PlayerObj* arg0)
{
    s16 temp_v0;

    temp_v0 = D_8013B7FC - D_8013B7E4;
    if ((func_8002CD70(arg0, func_8002D7E4(arg0, D_8013B7F8, temp_v0)) == 0) && (func_8002CD70(arg0, func_8002D7E4(arg0, D_8013B7F8 - D_8013B7E0, temp_v0)) == 0)) {
        func_8002CD70(arg0,
            func_8002D7E4(arg0, D_8013B7F8 + D_8013B7E0 - 1, temp_v0));
    }
}

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002CD70);

void func_8002CDD4(struct PlayerObj* arg0)
{
    u8 temp_s3;
    u8 temp_s4;
    u8 temp_s5;
    u8 temp_v0_4;
    s32 var_s0;
    s16 temp_v0 = D_8013B7FC + D_8013B7E4;

    temp_s3 = func_8002D7E4(arg0, D_8013B7F8 - D_8013B7E0, temp_v0);
    temp_s4 = func_8002D7E4(arg0, D_8013B7F8 + D_8013B7E0 - 1, temp_v0);
    temp_s5 = func_8002D7E4(arg0, D_8013B7F8, temp_v0);

    if (func_8002CF98(arg0, temp_s5, D_8013B7F8, temp_v0) == 0) {
        if (arg0->unk67 == 0) {
            var_s0 = 0;
            if (temp_s3 > 0 && temp_s3 < 0x20) {
                var_s0 = 1;
            }
            if (temp_s4 > 0 && temp_s4 < 0x20) {
                var_s0 = 1;
            }

            temp_v0_4 = func_8002D7E4(arg0, D_8013B7F8, (temp_v0 + 0x10));
            if (temp_v0_4 > 0 && temp_v0_4 < 0x20) {
                var_s0 = 1;
            }

            if (var_s0) {
                arg0->y_pos.i.hi += 0x10;
                if (func_8002CF98(arg0, temp_v0_4, D_8013B7F8, temp_v0 + 0x10)) {
                    return;
                }
            }
        }

        if (func_8002D1F8(arg0, temp_s3, temp_v0) == 0) {
            func_8002D1F8(arg0, temp_s4, temp_v0);
        }
    }
}

s32 func_8002CF98(struct PlayerObj* entity, u8 arg1, s16 arg2, s16 arg3)
{
    s32 flag;
    s16 var_a0;
    u32 temp_v1;
    s16 var_v0;

    flag = 0;
    if (arg1 == 0x10) {
        flag = 1;
        entity->y_pos.i.hi -= 0x10;
        arg1 = func_8002D7E4(entity, arg2, arg3 - 0x10);
    }

    switch (arg1) {
    case 0x9 ... 0xC:
    case 0x19 ... 0x1C:
        var_a0 = arg2 & 0xF;
        temp_v1 = arg1 & 0xF;
        if (temp_v1 == 0xA) {
            var_a0 |= 0x10;
        }
        if (temp_v1 == 0xC) {
            var_a0 += 0x10;
        }
        if (temp_v1 >= 0xB) {
            var_v0 = var_a0 / 2;
        } else {
            var_v0 = 0xF - var_a0 / 2;
        }
        return func_8002D180(entity, arg3, var_v0, flag);
    case 0x1 ... 0x8:
    case 0x11 ... 0x18:
        var_a0 = arg2 & 0xF;
        temp_v1 = arg1 & 0xF;
        if (temp_v1 == 2) {
            var_a0 |= 0x10;
        }
        if (temp_v1 == 6) {
            var_a0 += 0x10;
        }
        if (temp_v1 == 3) {
            var_a0 += 0x20;
        }
        if (temp_v1 == 7) {
            var_a0 += 0x20;
        }
        if (temp_v1 == 4) {
            var_a0 += 0x30;
        }
        if (temp_v1 == 8) {
            var_a0 += 0x30;
        }
        if (temp_v1 >= 5) {
            var_v0 = var_a0 / 4;
        } else {
            var_v0 = 0xF - var_a0 / 4;
        }
        return func_8002D180(entity, arg3, var_v0, flag);
    case 0x21:
    case 0x22:
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3E:
    case 0x3F:
        D_8013B7DC |= 8;
        D_8013B804 = -entity->unk6E;
        return -1;
    case 0:
    default:
        return 0;
    }
}

s32 func_8002D180(struct PlayerObj* arg0, s16 arg1, s16 arg2, s32 arg3)
{
    D_8013B7D8 = 1;

    if (arg0->unk67 != 0) {
        if (arg3 == 0) {
            if ((arg1 & 0xF) < arg2) {
                return 0;
            }
        }
    }

    arg0->unk70 = 8;
    arg0->y_pos.i.lo = 0;
    arg0->y_pos.i.hi -= arg1 - (arg2 + (arg1 & ~0xF));
    return -1;
}

s32 func_8002D1F8(struct PlayerObj* arg0, u8 arg1, s32 arg2)
{
    switch (arg1) {
    case 0x21:
    case 0x22:
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3E:
    case 0x3F:
        D_8013B7DC |= 8;
        D_8013B804 = -arg0->unk6E;
        return -1;
    default:
        return 0;
    }
}

s32 func_8002D25C(struct PlayerObj* arg0)
{
    s16 arg1;
    s32 arg2;

    if (D_8013B7DC & 4) {
        arg2 = 0;
        arg1 = D_8013B7F4 + D_8013B804 + D_8013B7EC - D_8013B7E4;
    } else {
        arg2 = 1;
        arg1 = D_8013B7F4 + D_8013B804 + D_8013B7EC + D_8013B7E4 - 1;
    }

    if (func_8002D32C(arg0, arg1, arg2) == 0) {
        arg0->y_pos.i.lo = 0;
        arg0->y_pos.i.hi += D_8013B804;
        return 0;
    } else {
        return -1;
    }
}

s32 func_8002D32C(struct PlayerObj* arg0, s16 arg1, s32 arg2)
{
    if (func_8002D41C(arg0, func_8002D724(arg0, D_8013B7F8, arg1), arg2) == 0) {
        if (func_8002D41C(arg0, func_8002D724(arg0, D_8013B7F8 - D_8013B7E0, arg1), arg2) == 0) {
            if (func_8002D41C(arg0, func_8002D724(arg0, D_8013B7F8 + D_8013B7E0 - 1, arg1), arg2) == 0) {
                return 0;
            }
        }
    }
    return -1;
}

s32 func_8002D41C(struct PlayerObj* arg0, s32 arg1, s32 arg2)
{
    if (arg2 == 0) {
        switch (arg1 & 0xFF) {
        case 0x3E:
        case 0x3F:
            arg0->unk79 = 1;
            return -1;
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3C:
            return -1;
        default:
            return 0;
        }
    } else {
        switch (arg1 & 0xFF) {
        case 0x3E:
        case 0x3F:
            arg0->unk79 = 1;
            return -1;
        case 0x21:
        case 0x22:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3C:
            return -1;
        default:
            return 0;
        }
    }
}

s32 func_8002D490(struct PlayerObj* arg0)
{
    s16 var_v0_2;

    if (D_8013B7DC & 1) {
        if (arg0->unk15 != 0) {
            var_v0_2 = (D_8013B7E0 + (D_8013B7E8 + (D_8013B7F0 + D_8013B800))) - 1;
        } else {
            var_v0_2 = (D_8013B7E0 + ((D_8013B7F0 + D_8013B800) - D_8013B7E8)) - 1;
        }
    } else {
        if (arg0->unk15 != 0) {
            var_v0_2 = (D_8013B7E8 + (D_8013B7F0 + D_8013B800)) - D_8013B7E0;
        } else {
            var_v0_2 = ((D_8013B7F0 + D_8013B800) - D_8013B7E8) - D_8013B7E0;
        }
    }

    if (func_8002D5E4(arg0, var_v0_2) != 0) {
        return -1;
    }
    arg0->x_pos.i.lo = 0;
    arg0->x_pos.i.hi += D_8013B800;
    return 0;
}

s32 func_8002D5E4(struct PlayerObj* arg0, s16 arg1)
{
    if (func_8002D6BC(arg0, func_8002D724(arg0, arg1, D_8013B7FC - D_8013B7E4)) == 0) {
        if (func_8002D6BC(arg0, func_8002D724(arg0, arg1, D_8013B7FC)) == 0) {
            if (func_8002D6BC(arg0, func_8002D724(arg0, arg1, D_8013B7FC + D_8013B7E4 - 1)) == 0) {
                return 0;
            }
        }
    }
    return -1;
}

s32 func_8002D6BC(struct PlayerObj* arg0, u8 arg1)
{
    switch (arg1) {
    case 0x38:
    case 0x3A:
    case 0x3C:
        arg0->unk4A = 1;
        return -1;
    case 0x39:
        arg0->unk4A = 0;
        return -1;
    case 0x3E:
    case 0x3F:
        arg0->unk4A = 0;
        arg0->unk79 = 1;
        return -1;
    default:
        return 0;
    }
}

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002D724);

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002D7E4);

u8 func_8002D8B8(struct PlayerObj* arg0)
{
    struct Unk_unk68* temp_v1 = arg0->unk68;
    return func_8002D724(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi + temp_v1->unk1 - temp_v1->unk3);
}

u8 func_8002D900(struct PlayerObj* arg0)
{
    s16 x = arg0->x_pos.i.hi;
    s16 y = arg0->y_pos.i.hi + arg0->unk68->unk1 + arg0->unk68->unk3 - 1;

    return func_8002D724(arg0, x, y);
}

u8 func_8002D94C(struct PlayerObj* arg0)
{
    struct Unk_unk68* temp_v1 = arg0->unk68;
    return func_8002D724(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi + temp_v1->unk1 + temp_v1->unk3);
}

#ifdef VERSION_JP
u8 func_8002D994(struct PlayerObj* arg0)
{
    return func_8002D724(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi);
}
#else
u8 func_8002D994(struct PlayerObj* arg0)
{
    return func_8002D724(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi);
}
#endif

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002D9BC);

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002DD04);

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002DE30);

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002DF7C);

void func_8002E184(struct PlayerObj* arg0)
{
    if (arg0->unk68 != NULL) {
        func_8002E294(arg0, &g_Player);
        if (arg0->unk76 > 0) {
            func_8002E380(arg0, &g_Player, arg0->unk72);
        }
        func_8002C36C(arg0, &g_Player, 0);
        if (g_Entity.active != 0) {
            func_8002E294(arg0, &g_Entity);
            if (arg0->unk77 > 0) {
                func_8002E380(arg0, &g_Entity, arg0->unk73);
            }
            func_8002C36C(arg0, &g_Entity, 1);
        }
        if (qux_object.active != 0) {
            func_8002E294(arg0, (struct PlayerObj*)&qux_object);
            if (arg0->unk78 > 0) {
                func_8002E380(arg0, (struct PlayerObj*)&qux_object, arg0->unk74);
            }
            func_8002C36C(arg0, (struct PlayerObj*)&qux_object, 2);
        }
    }
}

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002E294);

INCLUDE_ASM("main/nonmatchings/1A5BC", func_8002E380);

u8 D_800F4508[0x20] = {
    0x5F,
    0x28,
    0x00,
    0x60,
    0x38,
    0x00,
    0x61,
    0x48,
    0x01,
    0x62,
    0x58,
    0x02,
    0x63,
    0x68,
    0x03,
    0x64,
    0x78,
    0x04,
    0x65,
    0x88,
    0x04,
    0x66,
    0x98,
    0x05,
    0x67,
    0xA8,
    0x06,
    0x70,
    0xB8,
    0x07,
    0xFF,
    0x00,
};

u8 D_800F4528[0x1C] = {
    0x5F,
    0x30,
    0x00,
    0x61,
    0x40,
    0x01,
    0x62,
    0x50,
    0x02,
    0x63,
    0x60,
    0x03,
    0x64,
    0x70,
    0x04,
    0x66,
    0x80,
    0x05,
    0x67,
    0x90,
    0x06,
    0x70,
    0xB0,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};

u8 D_800F4544[0x1C] = {
    0x60,
    0x30,
    0x00,
    0x61,
    0x40,
    0x01,
    0x62,
    0x50,
    0x02,
    0x63,
    0x60,
    0x03,
    0x65,
    0x70,
    0x04,
    0x66,
    0x80,
    0x05,
    0x67,
    0x90,
    0x06,
    0x70,
    0xB0,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};

u8* D_800F4560[2] = { D_800F4528, D_800F4544 };

u8 D_800F4568[0x14] = {
    0x30,
    0x00,
    0x48,
    0x01,
    0x58,
    0x02,
    0x68,
    0x03,
    0x80,
    0x04,
    0x98,
    0x05,
    0xA8,
    0x06,
    0xB8,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};

u8 D_800F457C[0x14] = {
    0x30,
    0x00,
    0x40,
    0x01,
    0x50,
    0x02,
    0x60,
    0x03,
    0x70,
    0x04,
    0x80,
    0x05,
    0x90,
    0x06,
    0xB0,
    0x07,
    0xFF,
    0x00,
    0x00,
    0x00,
};

void (*D_800F4590[])(struct GameInfo* arg0) = {
    func_80029E1C,
    func_8002A098,
    func_8002A394,
};
