#include "common.h"

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
        obj->base.active = 1;
        obj->base.unk2 = 0x5E;
        obj->base.id = 0;
        obj->base.y_pos.i.hi = 0x10;
    }

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->base.active = 1;
        obj->base.id = 0;
        obj->base.unk2 = -1;
        if (D_80141BE0 != 0) {
            obj->unk50 = &D_800F4568;
        } else {
            obj->unk50 = &D_800F457C;
        }
        obj->base.x_pos.i.hi = 0x38;
    }

    if (D_80141BE0 != 0) {
        var_s1 = &D_800F4508;
    } else {
        var_s1 = D_800F4560[engine_obj.cur_character];
    }
    while (var_s1[0] != 0xFF) {
        obj = find_free_unk_obj();
        if (obj != NULL) {
            obj->base.active = 1;
            obj->base.id = 0;
            obj->base.unk2 = var_s1[0];
            obj->base.y_pos.i.hi = var_s1[1];
            obj->base.unk7 = var_s1[2];
        }
        if (var_s1[2] == 7) {
            break;
        }
        var_s1 += 3;
    }

    var_s1 = &D_800F457C;
    if (D_80141BE0 != 0) {
        var_s1 = &D_800F4568;
    }
    if (var_s1[1] != 7) {
        do {
            obj = find_free_unk_obj();
            if (obj != NULL) {
                obj->base.active = 1;
                obj->base.id = 0;
                obj->base.unk2 = var_s1[1];
                obj->base.y_pos.i.hi = var_s1[0];
            }
            var_s1 += 2;
        } while (var_s1[1] != 7);
    }

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->base.active = 1;
        obj->base.unk2 = -2;
        obj->base.id = 0;
        obj->base.x_pos.i.hi = 0x20;
    }

    if (D_80141BE0 == 0) {
        func_8001E980(0);
    }
    D_80141BDF[0] = 0;
    func_800129A4(8);
    D_8013B7D0++;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002A098);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002A484);

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

struct Unk* find_free_main_obj(void)
{
    struct Unk* var_v1;
    for (var_v1 = &main_objects[0]; var_v1 < &main_objects[0x30]; var_v1++) {
        if (!var_v1->base.active) {
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
        if (!current->base.active) {
            current->unk50 = 0;
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
        if (!current->base.active) {
            current->unk50 = 0;
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
        if (current->base.active == NULL) {
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
        if (!current->base.active) {
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
        if (!var_v0->base.active) {
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
            if (arg0->base.active == 0) {
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
            if (arg0->base.active == 0) {
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
            if (arg0->base.active == 0) {
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
            if (arg0->base.active == 0) {
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
        if (!current->base.active) {
            return current;
        }
    }

    return NULL;
}

struct UnkObj* find_free_unk_obj()
{
    struct UnkObj* current;

    for (current = &unk_objects[0]; current < &unk_objects[20]; current++) {
        if (!current->base.active) {
            return current;
        }
    }

    return NULL;
}

void func_8002B0C8(struct Unk18* arg0)
{
    if (arg0->unk10 != NULL) {
        *arg0->unk10 &= 0x70;
    }
    ZeroObjectState(arg0);
}

void func_8002B108(struct Unk18* arg0)
{
    if (arg0->unk10 != NULL) {
        *arg0->unk10 = 0x80;
    }
    ZeroObjectState(arg0);
}

void ZeroObjectState(struct Unk18* arg0)
{
    arg0->unk0 = 0;
    arg0->unk1 = 0;
    arg0->unk2 = 0;
    arg0->unk3 = 0;
    arg0->unk4 = 0;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B160);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B1E8);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B318);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B3C0);

void func_8002B450(void)
{
}

void func_8002B458(struct QuadObj* arg0)
{
}

void func_8002B460(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B468);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B560);

void func_8002B694(struct Unk* arg0)
{
    arg0->base.x_pos.val += arg0->unk20;
    arg0->base.y_pos.val -= arg0->unk24;

    if (arg0->base.unk15) {
        arg0->unk20 += arg0->unk28;
    } else {
        arg0->unk20 -= arg0->unk28;
    }

    arg0->unk24 -= arg0->unk2C;
    if (arg0->unk24 < FIXED(-6.5)) {
        arg0->unk24 = FIXED(-6.5);
    }
}

void func_8002B718(struct Unk19* arg0)
{
    arg0->unk8 += arg0->unk20;
    arg0->unkC -= arg0->unk24;
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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B780);

u8 func_8002B7B0(struct MiscObj* arg0, s32 arg1, s32 arg2)
{
    return func_8002B810(arg0->base.x_pos.val - arg1, arg0->base.y_pos.val - arg2);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B7DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B810);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B93C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B9F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002BAA4);

s16 func_8002BAD0(s16 arg0, s16 arg1, s16 arg2)
{
    struct BackgroundObj* temp_v1 = &background_objects[arg0];
    s16 var_x, var_y;
    s16 temp;

    var_x = (temp_v1->x_pos.i.hi + arg1) / 256;
    var_y = (temp_v1->y_pos.i.hi + arg2) / 256;
    temp = var_x + (arg0 * layout_size + layout_width * var_y);

    return *(*(u8**)0x1F800004 + temp);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002BB80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002BD58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002C160);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002C26C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002C2EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002C36C);

// megaman falls through floor in intro stage if nopped out
// asm(".rept 81 ; nop ; .endr");
void CollisionRelated(struct PlayerObj* arg0) // was func_8002C614
{
    s32 temp_v1;

    arg0->unk70 = 0;
    arg0->unk79 = 0;

    if (arg0->unk68 != NULL) {
        func_8002C760(arg0);
        temp_v1 = arg0->base.x_pos.val - arg0->unk18;
        D_8013B7D8 = 0;
        D_8013B7DC = 0;

        if (temp_v1 != 0) {
            if (temp_v1 > 0) {
                func_8002CB58(arg0);
            } else {
                func_8002CA18(arg0);
            }
        }

        if (arg0->base.y_pos.val - arg0->unk1C >= 0) {
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
    u16 temp_a1 = arg0->base.x_pos.i.hi;
    u16 temp_v0 = temp_v1->unk0;

    D_8013B7E8 = temp_v1->unk0;
    D_8013B7EC = temp_v1->unk1;
    D_8013B7E0 = temp_v1->unk2;
    D_8013B7E4 = temp_v1->unk3;

    D_8013B7F0 = temp_a1;
    D_8013B7F4 = arg0->base.y_pos.i.hi;

    if (arg0->base.unk15 == 0) {
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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002C954);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002C99C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002C9E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002CA18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002CAF0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002CB58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002CC34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002CC98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002CD70);

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
                arg0->base.y_pos.i.hi += 0x10;
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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002CF98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002D180);

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
        arg0->base.y_pos.i.lo = 0;
        arg0->base.y_pos.i.hi += D_8013B804;
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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002D41C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002D490);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002D6BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002D724);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002D7E4);

u8 func_8002D8B8(struct PlayerObj* arg0)
{
    struct Unk_unk68* temp_v1 = arg0->unk68;
    return func_8002D724(arg0, arg0->base.x_pos.i.hi, arg0->base.y_pos.i.hi + temp_v1->unk1 - temp_v1->unk3);
}

u8 func_8002D900(struct PlayerObj* arg0)
{
    s16 x = arg0->base.x_pos.i.hi;
    s16 y = arg0->base.y_pos.i.hi + arg0->unk68->unk1 + arg0->unk68->unk3 - 1;

    return func_8002D724(arg0, x, y);
}

u8 func_8002D94C(struct PlayerObj* arg0)
{
    struct Unk_unk68* temp_v1 = arg0->unk68;
    return func_8002D724(arg0, arg0->base.x_pos.i.hi, arg0->base.y_pos.i.hi + temp_v1->unk1 + temp_v1->unk3);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002D994);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002D9BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002DD04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002DE30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002DF7C);

void func_8002E184(struct PlayerObj* arg0)
{
    if (arg0->unk68 != NULL) {
        func_8002E294(arg0, &g_Player);
        if (arg0->unk76 > 0) {
            func_8002E380(arg0, &g_Player, arg0->unk72);
        }
        func_8002C36C(arg0, &g_Player, 0);
        if (g_Entity.base.active != 0) {
            func_8002E294(arg0, &g_Entity);
            if (arg0->unk77 > 0) {
                func_8002E380(arg0, &g_Entity, arg0->unk73);
            }
            func_8002C36C(arg0, &g_Entity, 1);
        }
        if (qux_object.base.active != 0) {
            func_8002E294(arg0, (struct PlayerObj*)&qux_object);
            if (arg0->unk78 > 0) {
                func_8002E380(arg0, (struct PlayerObj*)&qux_object, arg0->unk74);
            }
            func_8002C36C(arg0, (struct PlayerObj*)&qux_object, 2);
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E294);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E380);

// engine_state_3_update_funcs state 0 (load video)
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E420);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E5E0);

// engine_state_3_update_funcs state 1 (load briefing room)
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E698);

// engine_state_3_update_funcs state 2
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E7BC);

// engine_state_3_update_funcs state 3
void func_8002E8D4(struct EngineObj* arg0)
{
    struct MiscObj* obj;

    if (arg0->unk3C->state == 2) {
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0xF;
            obj->base.unk2 = 0;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0xF;
            obj->base.unk2 = 1;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0xC;
            obj->base.unk2 = 9;
        }
        arg0->unk1++;
    }
}

// engine_state_3_update_funcs state 4
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E994);

// engine_state_3_update_funcs state 5
void func_8002ED80(struct EngineObj* arg0)
{
    arg0->unk40 = 0;
    arg0->unk2 = 0;
    arg0->unk1++;
}

// engine_state_3_update_funcs state 6
void func_8002ED98(struct EngineObj* arg0)
{
    func_800129F0(8);
    arg0->unk2 = 0;
    arg0->unk1++;
}

// engine_state_3_update_funcs state 7
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002EDD4);

// engine_state_3_update_funcs state 8 (play video)
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002EF14);

void func_8002F048(void)
{
    struct MiscObj* misc;
    struct EffectObj* effect;

    switch (*D_8013B80C) {
    case 0x0:
        D_8013B80C++;
        return;
    case 0x40:
        D_8013B80C++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->unk1 = 3;
            effect->unk2 = 0;
        }
        misc = find_free_misc_obj();
        D_8013B808 = misc;
        if (misc != NULL) {
            misc->base.active = 0x41;
            D_8013B808->base.id = 0xD;
            D_8013B808->base.unk2 = 1;
        }
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->base.active = 0x41;
            misc->base.id = 0xC;
            misc->base.unk2 = 8;
            misc->ext.ready_text.unk50 = D_8013B808;
            return;
        }
    case 0xFF:
        return;
    default:
        if (*D_8013B80C & 0x40) {
            ZeroObjectState(D_8013B808);
        }
        engine_obj.unk40 = *D_8013B80C & 0x3F;
        D_8013B80C++;
        break;
    }
}

// briefing_room_state_9_update_funcs state 0
void func_8002F1B4(struct EngineObj* arg0)
{
    // if the player presses a button, skip to the bottom
    if (controller_state & (PADRdown | PADstart)) {
        background_objects[0].y_pos.i.hi = 272;
        background_objects[0].unk4C = 1;
    }
    // scroll down
    if (background_objects[0].y_pos.i.hi < 272) {
        background_objects[0].y_pos.i.hi++;
        return;
    }
    arg0->unk2++;
    D_8013B80C = D_800F4830[arg0->unkE];
    func_8002217C(D_800F4776[arg0->unkE], 0xFF, 0);
}

// briefing_room_state_9_update_funcs state 1
void func_8002F264(struct EngineObj* arg0)
{
    if (abc_object.unkC != 0x80) {
        arg0->unk2++;
        func_8002F048();
    }
}

// briefing_room_state_9_update_funcs state 2
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F2A0);

// briefing_room_state_9_update_funcs state 3
void func_8002F47C(struct EngineObj* arg0)
{
    if ((abc_object.unkC == 1) || (abc_object.unkC == 0x80)) {
        arg0->unk2--;
        func_8002F048();
    }
}

// engine_state_3_update_funcs state 9 (briefing room)
void func_8002F4C4(struct EngineObj* arg0)
{
    arg0->unk40 = 0;
    briefing_room_state_9_update_funcs[arg0->unk2](arg0);
    func_80022730(&abc_object);
}

void func_8002F510(struct EngineObj* arg0)
{
    arg0->unk3 = 0;
    arg0->unk2++;
}

void func_8002F524(struct EngineObj* arg0)
{
    struct QuadObj* temp_v0 = find_free_quad_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = -0x7F;
        temp_v0->id = 1;
        temp_v0->unk2 = arg0->unk3 + 0x10;
        arg0->unk3C = temp_v0;
        arg0->unk2++;
    }
}

void func_8002F584(struct EngineObj* arg0)
{
    if (arg0->unk3C->state == 2) {
        func_8002217C(arg0->unk3, 0xFF, 0);
        arg0->unk2++;
    }
}

void func_8002F5E8(struct EngineObj* arg0)
{
    struct BaseObj* obj;

    if (abc_object.unkC == 0) {
        if (++arg0->unk3 < 8) {
            arg0->unk2 = 1;
            return;
        }
        arg0->unk5F = 3;
        arg0->unk1 = 4;
        arg0->unk2 = 0;
        arg0->unk3 = 0;
        obj = (struct BaseObj*)find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0xF;
            obj->unk2 = 0;
        }
        obj = (struct BaseObj*)find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0xF;
            obj->unk2 = 1;
        }
    }
}

// engine_state_3_update_funcs state 10
void func_8002F698(struct EngineObj* arg0)
{
    D_800F486C[arg0->unk2](arg0);
    func_80022730(&abc_object);
}

void func_8002F6E4(struct EngineObj* arg0)
{
    D_8013B810 = arg0->stage;
    D_8013B814 = arg0->substage;
    arg0->stage = 0xD;
    arg0->substage = 1;
    arg0->unk40 = D_8013B810;
    func_80013014();
    reset_objects();
    func_8002AB20();
    func_80028BF0();
    func_8002771C();
    func_80023CE0();
    background_objects[1].unk4C = 1;
    background_objects[1].x_pos.val = FIXED((D_8013B810 - 1) << 9);
    background_objects[2].x_pos.val = FIXED((D_8013B810 - 1) << 9);
    arg0->unk2++;
}

void func_8002F7A8(struct EngineObj* arg0)
{
    struct BaseObj* obj = (struct BaseObj*)find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x32;
        obj->x_pos.i.hi = 0x100;
        obj->y_pos.i.hi = 0x70;
        obj->unk2 = D_8013B810;
    }
    background_objects[2].unk4C = 1;
    func_800129A4(8);
    arg0->unk2++;
}

void func_8002F828(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unk2++;
        arg0->unk4 = 0x10;
        func_8001663C(D_8013B810 + 0x4F, 0x7F);
    }
}

void func_8002F87C(struct EngineObj* arg0)
{
    if (D_80173C84 == 2) {
        background_objects[1].y_pos.val -= FIXED(8 + 1.0 / 16);
        background_objects[2].y_pos.val += FIXED(8 + 1.0 / 16);
        if (background_objects[1].y_pos.val < 0) {
            background_objects[1].y_pos.val = 0;
            background_objects[2].y_pos.val = FIXED(256);
            arg0->unk4 = 0x1E;
            arg0->unk2++;
        }
    }
}

void func_8002F8F8(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        arg0->unk4 = 0x96;
        arg0->unk2++;
    }
}

void func_8002F92C(struct EngineObj* arg0)
{
    struct BaseObj* obj;
    if (--arg0->unk4 != 0) {
        if (!(func_8002B780() & 1)) {
            obj = (struct BaseObj*)find_free_quad_obj();
            if (obj != NULL) {
                obj->active = 1;
                obj->id = 6;
                obj->x_pos.i.hi = 0x9C0;
                obj->y_pos.i.hi = 0x70;
            }
        }
    } else {
        obj = (struct BaseObj*)find_free_effect_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 2;
            obj->unk2 = 0xC;
        }
        arg0->unk2++;
    }
}

void func_8002F9EC(struct EngineObj* arg0)
{
    struct BaseObj* obj;
    u32 var_a0;

    if (g_FilterAmountR == 0x1F) {
        func_8002B560(2, 0xC);
        for (var_a0 = 0; var_a0 < 4; var_a0++) {
            D_8013E188[var_a0] = 0;
        }
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        need_palette_load |= 1;
        obj = (struct BaseObj*)find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x32;
            obj->unk2 = 0;
        }
        arg0->unk4 = 0x78;
        arg0->unk2++;
    }
}

void func_8002FAB0(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        arg0->unk4 = 0x12C;
        arg0->unk2++;
    }
}

void func_8002FAE4(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        func_800129F0(8);
        arg0->unk2++;
    }
    background_objects[0].x_pos.val += FIXED(-6);
}

void func_8002FB54(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_8001D134();
        arg0->stage = D_8013B810;
        arg0->substage = D_8013B814;
        arg0->unk1 = 0;
        arg0->unk2 = 0;
        arg0->unk3 = 0;
        arg0->state++;
    } else {
        background_objects[0].x_pos.val += FIXED(-6);
    }
}

// engine_state_3_update_funcs state 11
void func_8002FBDC(struct EngineObj* arg0)
{
    background_objects[0].unk14.val = background_objects[0].x_pos.val;
    background_objects[0].unk18.val = background_objects[0].y_pos.val;
    D_800F487C[arg0->unk2](arg0);
}

// videos / loading / briefing room
void engine_state_3(struct EngineObj* arg0)
{
    func_8002B460();
    engine_state_3_update_funcs[arg0->unk1](arg0);
    update_effect_objects();
    update_misc_objects();
    update_quad_objects();
    func_8002A484();
    func_80023D68();
}

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
    func_80015930(0xFF, 0);
    func_800129F0(8);
    func_80023D68();
    arg0->unk5 = 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002FD70);

void func_800300AC(struct BarObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->state = 1;
        arg0->unk5 = 0;
        if (g_Player.base.unk2 || arg0->unk2) {
            if (arg0->unk14 >= 0xD) {
                arg0->unk5 = 2;
            } else {
                arg0->unk5 = 1;
            }
        }
    }
    func_80023D90();
}

void func_80030128(struct BarObj* arg0)
{
    if (controller_state & PADselect) {
        if (arg0->unk5 < 3) {
            arg0->unk28 = arg0->unk5;
            arg0->unk5 = 6;
            arg0->unk6 = 0;
        }
    }
    D_800F48F4[arg0->unk5](arg0);
    if (arg0->unk5 < 5) {
        func_80023D90();
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800301BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800304E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030728);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030A2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030C54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030DF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030EC8);

void func_80030F9C(struct BarObj* arg0)
{
    D_800F4910[arg0->unk5](arg0);
}

void func_80030FD8(struct BarObj* arg0)
{
    func_800129F0(8);
    func_80023D90();
    arg0->unk5 = 1;
}

void func_80031014(struct BarObj* arg0)
{
    if (D_80141BDC[0] != 0) {
        func_80023D90();
    } else {
        func_800170E0();
        arg0->unk5 = 2;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031064);

void func_80031130(struct BarObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (arg0->unk30 == 0) {
            engine_obj.unk1 = 0;
            arg0->state = 0;
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
        func_80023D68();
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800311EC);

void func_800312B4(struct PlayerObj* arg0)
{
    arg0->unkC3 = arg0->unkC0 | engine_obj.unkF;
    arg0->unkC3 |= arg0->unkC4;
    arg0->unk89 = arg0->unk70 | arg0->unk71;
    arg0->unk8F = 0;
    arg0->unk90 = 0;
    arg0->unkBF = 0;

    if (engine_obj.unk10 == 0) {
        func_80033BC8(arg0);
        if (arg0->unk5C == 0) {
            return;
        }

        if (arg0->unk92) {
            arg0->unk92--;
        }

        if (arg0->unk91 != 0) {
            arg0->unk91--;
            if (!arg0->unk91) {
                arg0->unk90 = 1;
                arg0->unk8E = 0;
            }
        }

        if (arg0->unkD7 > 0) {
            arg0->unkD7--;
            if (!arg0->unkD7) {
                arg0->unkD7 = -1;
            }
        }

        func_800338CC(arg0);
        func_80033974(arg0);
        func_80033750(arg0);
        func_800335E4(arg0);
        func_80036EE8(arg0);

        D_800F8990[arg0->base.unk5](arg0);
        arg0->unk71 = 0;
        arg0->unk4A = 0;
    }
    func_80037FF0(arg0);
    func_800360B8(arg0);
    func_80035DE4(arg0);
}

void func_80031410(struct PlayerObj* arg0)
{
    func_80015DC8();
    if (arg0->base.unk6 == 0) {
        if (arg0->unkBE != 0) {
            if (--arg0->unkBE == 0) {
                func_80035EA4(arg0);
            }
            func_8002B718(arg0);
            return;
        }
        if (arg0->unk89 & 8) {
            func_800350A4(arg0, 2);
            arg0->unk67 = 0;
            background_objects[0].unk44 = 1;
            background_objects[1].unk44 = 1;
            background_objects[2].unk44 = 1;
            arg0->base.unk6++;
            return;
        }
        func_8002B718(arg0);
        func_80036B88(arg0);
        return;
    }
    if (arg0->unk45 != 0) {
        arg0->unk45 = 0;
        arg0->unkA7 = engine_obj.unk47;
        arg0->unkB8 = engine_obj.unk48;
    }
    if (arg0->unk46 == 0) {
        engine_obj.unk1C = 0;
        func_800343A4(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031540);

void func_800315E0(struct PlayerObj* arg0)
{
    if (func_80034100(arg0) == 0 && func_80033EA4(arg0) == 0 && func_80037290(arg0) == 0 && func_80039880(arg0) == 0 && func_80033494(arg0) == 0 && func_800398F0(arg0) == 0) {
        if (func_800334F4(arg0) != 0) {
            func_800344A0(arg0);
        } else {
            func_80038678(arg0);
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031688);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031764);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031820);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800318D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031A24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031AE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031B90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031CAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031DD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031EDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031F1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003200C);

void func_800320E4(struct PlayerObj* arg0)
{
    if (func_80034100(arg0) == 0) {
        func_80015DC8(arg0);
        D_800F8A90[arg0->base.unk6](arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032140);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032224);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032300);

void func_80032468(struct PlayerObj* arg0)
{
    if (arg0->unk89 & 8) {
        func_80034668();
    } else if (arg0->unkC3 != 0) {
        func_80034604(arg0);

    } else if (arg0->base.unk2 == 0) {
        if (func_80037338(arg0) == 0) {
            if (arg0->unk8E != 0) {
                func_8003490C(arg0);
            } else {
                func_80015DC8(arg0);
                D_800F8A9C[arg0->base.unk6](arg0);
            }
        }
    } else {
        func_80015DC8(arg0);
        D_800F8A9C[arg0->base.unk6](arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003253C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800325EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003267C);

void func_80032740(struct PlayerObj* arg0)
{
    D_800F8AA8[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003277C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800327CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032840);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800328CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032910);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032950);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032A28);

void func_80032B04(struct PlayerObj* arg0)
{
    func_80015DC8(arg0);
    D_800F8ABC[arg0->unk63](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032B50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032BF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032D28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032E94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032F64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032FA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033054);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800330B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033108);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800331A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033210);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800332C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033368);
