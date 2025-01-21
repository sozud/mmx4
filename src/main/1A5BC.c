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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033414);

s32 func_80033494(struct PlayerObj* arg0)
{
    if (func_80033694() != 0) {
        func_80034754(arg0);
        return 1;
    }
    if (arg0->unk80 & 0x80) {
        func_80034538(arg0);
        return 1;
    }
    return 0;
}

s32 func_800334F4(struct PlayerObj* arg0)
{
    if (arg0->unkC3) {
        return 0;
    }

    if (!(*(s16*)&arg0->unk7C & 3)) {
        return 0;
    }

    if (*(s16*)&arg0->unk7C & 1) {
        arg0->base.unk15 = 0x40;
        if (!(arg0->unk89 & 1)) {
            arg0->unk20 = FIXED(0.5);
            return 1;
        } else {
            return 0;
        }
    }

    arg0->base.unk15 = 0;
    if (!(arg0->unk89 & 2)) {
        arg0->unk20 = FIXED(-0.5);
        return 1;
    } else {
        return 0;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003356C);

void func_800335E4(struct PlayerObj* arg0)
{
    s8 temp_v1;

    temp_v1 = arg0->base.unk5; // fake
    if ((arg0->base.unk5 != 0) && (temp_v1 != 1) && (arg0->unk67 == 0) && (arg0->unkA4 <= 0) && (arg0->unkC5 >= 0) && (arg0->unkC4 == 0) && !(arg0->unk89 & 8)) {
        if (arg0->base.unk2 != 0) {
            func_80036054(arg0);
        }
        func_80034604(arg0);
    }
}

s32 func_80033694(struct PlayerObj* arg0)
{
    if (arg0->unkC3 || (!arg0->unk87 && !(arg0->unk80 & 0x100))) {
        return 0;
    }

    if (*(u16*)&arg0->unk7C & 1) {
        arg0->base.unk15 = 0x40;
    }
    if (*(u16*)&arg0->unk7C & 2) {
        arg0->base.unk15 = 0;
    }
    if (arg0->base.unk15 != 0) {
        if ((arg0->unk89 & 1)) {
            return 0;
        } else {
            arg0->unk20 = FIXED(6.5);
            return 1;
        }
    } else if (!(arg0->unk89 & 2)) {
        arg0->unk20 = FIXED(-6.5);
        return 1;
    } else {
        return 0;
    }
}

void func_80033750(struct PlayerObj* arg0)
{
    s8 temp_v1;

    arg0->unk87 = 0;
    if ((arg0->unkC3 == 0) && (temp_v1 = arg0->base.unk5, (temp_v1 != 0)) && (temp_v1 != 1)) {
        if (arg0->unk88 == 0) {
            arg0->unk82 = arg0->unk80 & 3;
            if (arg0->unk82 != 0) {
                arg0->unk88 = 0xC;
            }
        } else {
            arg0->unk88--;
            if (arg0->unk80 & arg0->unk82) {
                arg0->unk87 = 1;
                arg0->unk88 = 0;
            }
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800337DC);

void func_800338CC(struct PlayerObj* arg0)
{
    s32 var_v1;

    if (arg0->unkC4 > 0 && arg0->unkA4 <= 0) {
        func_80036054(arg0);

        // maybe these can be combined? couldn't get a match
        var_v1 = 0;
        if (arg0->base.unk17 == 5) {
            var_v1 = 1;
        }
        if (arg0->base.unk17 == 6) {
            var_v1 = 1;
        }
        if (arg0->base.unk17 == 0xC) {
            var_v1 = 1;
        }
        if (var_v1) {
            func_800350A4(arg0, 0x26);
        }

        arg0->base.unk15 = 0x40;
        arg0->unkC4 = -1;
        arg0->unk8C = 0;
        arg0->base.unk5 = 0x13;
        arg0->base.unk6 = 0;
    }
}

void func_80033974(struct PlayerObj* arg0)
{
    if (arg0->unkC5 > 0) {
        func_80036088();
        func_80038490(arg0);
        func_80036E98(arg0);
        arg0->unk68 = 0;
        arg0->unk67 = 1;
        arg0->unkC5 = -1;
        arg0->base.unk5 = 0x12;
        arg0->base.unk6 = 1;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800339E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033AC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033B34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033B8C);

void func_80033BC8(struct PlayerObj* arg0)
{
    s8 temp_v1;
    if (arg0->unkD9 == 0 && (temp_v1 = arg0->base.unk5, temp_v1 != 0) && (temp_v1 != 1)) {
        if ((arg0->unk89 & 0xC) == 0xC) {
            arg0->unk5C = -0x80;
        }
        if ((arg0->unk89 & 3) == 3) {
            arg0->unk5C = -0x80;
        }
        if (arg0->unk79 != 0 && arg0->unk61 == 0 && arg0->unk7A == 0) {
            arg0->unk5C = -0x80;
        }
        if (arg0->unk5C == -0x80) {
            arg0->unk5C = 0;
            engine_obj.unk1C = 1;
            func_80033D10(arg0);
            func_80038490(arg0);
            arg0->unk68 = 0;
            arg0->unk54 = 0;
            arg0->base.state = 2;
            arg0->base.unk5 = 0;
            arg0->base.unk6 = 0;
            return;
        }
        if (arg0->unk61 != 0) {
            arg0->unk61--;
            if (arg0->unk61 == 0) {
                arg0->unkA4 = 0;
                func_800361F8(arg0);
                return;
            }
        }
        if (arg0->unk5C <= 0) {
            func_80033D54(arg0);
        }
    }
}

void func_80033D10(struct PlayerObj* arg0)
{
    arg0->unkBF = 1;
    arg0->unk84 = 0;
    arg0->unk86 = 0;
    arg0->unk8C = 0;
    func_80036054(arg0);
    func_800360B0(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033D54);

s32 func_80033EA4(struct PlayerObj* arg0)
{
    if (arg0->unkC3 || arg0->unk92) {
        return 0;
    }
    if (*(u16*)&arg0->unk7C & 4 && func_8002D8B8(arg0) == 0x20) {
        func_80034BDC(arg0);
        return 1;
    }
    if (*(u16*)&arg0->unk7C & 8 && func_8002D94C(arg0) == 0x21) {
        func_80034CB0(arg0);
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033F5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033FF0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800340BC);

s32 func_80034100(struct PlayerObj* arg0)
{
    if (engine_obj.unkF != 0) {
        func_80034F7C();
        return 1;
    }

    if (arg0->unkC0 > 0) {
        func_80034E2C();
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034150);

s32 func_80034238(struct Unk11* arg0)
{
    s32 result = 0;

    if (arg0->unk89 & 0x4) {
        result = 1;
        arg0->unk24 = 0;
    }

    if (arg0->unk24 <= 0) {
        result = 1;
    }

    if (result != 0) {
        s8 index = arg0->unk02;
        func_800350A4(arg0, D_800F8B30[index]);

        if (arg0->unk02 != 0) {
            struct Unk11* new_obj = find_free_visual_obj();
            if (new_obj != NULL) {
                new_obj->unk00 = 1;
                new_obj->unk01 = 0x27;
                new_obj->unk02 = 0;
                new_obj->unk14 = arg0->unk14;
            }
        }

        arg0->unk67 = -1;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk06 = 3;
        return 1;
    } else {
        func_8002B694(arg0);
        func_80036B88(arg0);
        return 0;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034320);

void func_8003439C(void)
{
}

void func_800343A4(struct PlayerObj* arg0)
{
    s32 var_a2; // ???

    if (func_80034100(arg0) == 0) {
        arg0->base.unk5 = 2;
        arg0->base.unk6 = 0;
        if ((arg0->base.unk2 == 0) && (arg0->unk8E != 0)) {
            var_a2 = arg0->unk91 < 9;
            if (arg0->unk91 < 5) {
                var_a2 = 2;
            }
            func_8003516C(arg0, 0x5E, var_a2);
            if (arg0->unk91 >= 9) {
                arg0->unk44 = arg0->unk91 - 8;
            }
        } else {
            func_80036534(arg0);
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003443C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800344A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800344EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034538);

void func_80034604(struct PlayerObj* arg0)
{
    func_80038524(arg0, 0xB);
    arg0->unk2C = 0x4200;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk67 = -1;
    if (arg0->unk84 != 0) {
        arg0->unk84 = 0;
        arg0->unk8C = -1;
    }
    arg0->base.unk5 = 7;
    arg0->base.unk6 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034668);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003470C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034754);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800347D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003484C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800348B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003490C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034968);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800349F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034AFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034B64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034BDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034C58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034D20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034D64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034DC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80034F7C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80035048);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800350A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003516C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80035240);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800355C0);

void func_80035694(struct PlayerObj* arg0)
{
    struct EngineObj* engine = &engine_obj;
    s32 var_a0;

    if (arg0->unkD9 != 0) {
        arg0->base.on_screen = 1;
        func_800350A4(arg0, 0x61);
        arg0->base.unk5 = 0x24;
        arg0->base.state++;
        return;
    }
    if (engine->unk1E != 0) {
        arg0->base.on_screen = 1;
        engine->unk1F = 1;
        var_a0 = 0;
        switch (engine->stage) {
        case 3:
            if (engine->unk1E == -1 && engine->checkpoint != 0) {
                var_a0 = 1;
            }
            break;
        case 5:
            var_a0 = 2;
            if (engine->substage != 0) {
                if (engine->checkpoint == 0) {
                    var_a0 = 2;
                } else {
                    var_a0 = 0;
                }
            }
            break;
        case 6:
            if (engine->unk1E == -1) {
                var_a0 = 1;
            }
            break;
        case 12:
            if (engine->substage == 0) {
                if (engine->checkpoint >= 2) {
                    var_a0 = 1;
                }
            } else if (engine->checkpoint == 0) {
                var_a0 = 1;
            }
            break;
        }
        arg0->base.state++;
        D_800F8B44[var_a0](arg0);
    }
}

void func_80035848(struct PlayerObj* arg0)
{
    func_800350A4(arg0, 1);
    func_8001540C(1, 0xD, arg0);
    arg0->unk24 = 0xFFF80000;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = -1;
    arg0->base.unk5 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800358A4);

void func_80035A24(struct PlayerObj* arg0)
{
    qux_object.base.active = 1;
    arg0->unkA7 = engine_obj.unk47;
    arg0->unkB8 = engine_obj.unk48;
    arg0->unkC5 = -1;
    arg0->unkD4 = 0x29;
    arg0->unk67 = 1;
    arg0->base.unk5 = 0x12;
    arg0->base.unk6 = 1;
}

void func_80035A6C(struct PlayerObj* arg0)
{
    D_800F8B94[arg0->base.unk5](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80035AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80035B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80035C20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80035D00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80035D34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80035D84);

void func_80035DDC(struct PlayerObj* arg0)
{
}

void func_80035DE4(struct PlayerObj* arg0)
{
    u8 var_v0_2;
    u8 temp_v0;

    if (arg0->base.unk2 == 0) {
        if (arg0->unkD9 == 0) {
            temp_v0 = D_801193F0[arg0->cur_anim];
            if (D_801193F0[arg0->cur_anim] != 0) {
                arg0->unk54 = &D_801194F0[temp_v0];
                return;
            }
        }
        arg0->unk54 = NULL;
        return;
    }
    if (D_8011AF60[arg0->base.unk17] == 0) {
        var_v0_2 = D_8011A030[arg0->cur_anim];
    } else {
        var_v0_2 = D_8011A130[arg0->cur_anim];
    }
    if (var_v0_2 == 0) {
        arg0->unk54 = NULL;
        return;
    }
    arg0->unk54 = &D_8011A230[var_v0_2];
}

void func_80035EA4(struct PlayerObj* arg0)
{
    if (arg0->unkC5 < 0) {
        arg0->unk68 = NULL;
        return;
    }
    if (arg0->base.unk2 == 0) {
        arg0->unk68 = &D_800F8BC4;
        return;
    }
    arg0->unk68 = &D_800F8BC8;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80035EF0);

s32 func_80035FC4(s32 arg0)
{
    u16 result = 0;
    u32 var_a3 = 1;
    u32 var_i = 0;

    for (var_i = 0; var_i < 16; var_i++) {
        if (D_800EE430[var_i] & arg0) {
            result |= var_a3;
        }
        var_a3 *= 2;
    }

    if ((result & 3) == 3) {
        result &= ~0x3;
    }

    if ((result & 0xC) == 0xC) {
        result &= ~0xC;
    }

    return result;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80036034);

void func_80036054(struct PlayerObj* arg0)
{
    arg0->unk8E = 0;
    arg0->unk8F = 0;
    arg0->unk90 = 0;
    arg0->unk91 = 0;
    arg0->unk92 = 0;
    arg0->unkA2 = 0;
    func_800361F8(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80036088);

void func_800360B0(struct PlayerObj* arg0)
{
    arg0->unkA1 = 0;
}

void func_800360B8(struct PlayerObj* arg0)
{
    s8 temp_v1 = arg0->base.unk5; // likely fake
    if ((arg0->base.unk5 != 0) && (temp_v1 != 1) && (arg0->unkA4 <= 0)) {
        if (arg0->unkA2 != 0) {
            if (--arg0->unkA2 == 0) {
                func_800361F8(arg0);
            }
        }
        if (arg0->unkA4 < 0) {
            arg0->unkA1 = 0x23;
        }
        if (arg0->unkA1 != 0) {
            if (arg0->unk9F != 0) {
                arg0->unk9F--;
            } else {
                if (arg0->unkA0 == 0) {
                    func_800362F8(arg0, arg0->unkA1);
                } else {
                    func_800361F8(arg0);
                }
                arg0->unk9F = 1;
                arg0->unkA0 ^= 1;
            }
            arg0->unkA1 = 0;
        }
    }
}

void func_800361B0(struct PlayerObj* arg0, s32 arg1, s32 arg2)
{
    u16* var_a0;
    u16* var_v1;
    u32 var_a3;

    var_a0 = *(u16**)0x1F800024 + (arg1 << 4);
    var_v1 = *(u16**)0x1F800028 + (arg2 << 4);

    for (var_a3 = 0; var_a3 < 16; var_a3++) {
        *var_v1++ = *var_a0++;
    }
}

void func_800361F8(struct PlayerObj* arg0)
{
    u16* var_a0;
    u16* var_v1;
    u32 a2;
    s32 temp;

    if (arg0->base.unk2 == 0) {
        if (arg0->unkD9 == 0) {
            if (arg0->unk93 == 0) {
                func_800362F8(arg0, 0);
            } else {
                temp = ((arg0->unk93 - 1) << 6);
                var_a0 = *(u16**)0x1F800028;
                var_v1 = *(u16**)0x1F800024 + 0x30 + temp;
                for (a2 = 0; a2 < 0x20; a2++) {
                    *var_a0++ = *var_v1++;
                }
                var_a0 = *(u16**)0x1F800028 + 0x130;
                for (a2 = 0; a2 < 0x20; a2++) {
                    *var_a0++ = *var_v1++;
                }
            }
            need_palette_load |= 1;
        }
    } else {
        if (engine_obj.unk37) {
            func_800361B0(arg0, 0xD, 0);
        } else {
            func_800361B0(arg0, 0, 0);
        }
        need_palette_load |= 1;
    }
}

void func_800362F8(struct PlayerObj* arg0, s32 arg1)
{
    u16* var_a0;
    u16* var_v1;
    u32 var_a2;

    if (arg0->base.unk2 == 0) {
        if (arg0->unkD9 == 0) {
            var_a0 = *(u16**)0x1F800028;
            var_v1 = *(u16**)0x1F800024 + (arg1 << 4);
            for (var_a2 = 0; var_a2 < 0x10; var_a2++) {
                *var_a0++ = *var_v1++;
            }
            var_a0 = *(u16**)0x1F800028 + 0x130;
            for (var_a2 = 0; var_a2 < 0x20; var_a2++) {
                *var_a0++ = *var_v1++;
            }
            need_palette_load |= 1;
        }
    } else {
        func_800361B0(arg0, arg1, 0);
        need_palette_load |= 1;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800363B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800363EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80036470);

void func_80036534(struct PlayerObj* arg0)
{
    if (arg0->unk5C >= (engine_obj.unk46 / 3)) {
        func_800350A4(arg0, 5);
    } else {
        func_800350A4(arg0, 6);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800365A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003666C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800366C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800367F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003698C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80036A94);

void func_80036AE4(s8 arg0, s8 arg1)
{
    g_Player.unkC0 = 1;
    g_Player.unkC1 = arg0;
    g_Player.unkC2 = arg1;
    g_Player.unk7A = 1;
    engine_obj.unk1C = 1;
}

void func_80036B18(void)
{
    g_Player.unkC0 = 0;
    g_Player.unk7A = 0;
    engine_obj.unk1C = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80036B38);

void func_80036B88(struct PlayerObj* arg0)
{
    if (func_8002D900(arg0) == 0x24) {
        s16 temp = arg0->base.y_pos.i.hi + arg0->unk68->unk1 + arg0->unk68->unk3;
        func_80036BF4(arg0, temp & ~0xF);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80036BF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80036DA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80036E1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80036E98);

void func_80036EE8(struct PlayerObj* arg0)
{
    s8 temp_s0;

    if (arg0->base.unk2 == 0) {
        temp_s0 = arg0->unk93;
        func_80036F50(arg0);
        func_80037104(arg0);
        if (temp_s0 != arg0->unk93) {
            func_800371E4(arg0);
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80036F50);

void func_80037104(struct PlayerObj* arg0)
{
    if (arg0->unkD9 != 0) {
        arg0->unk94[0] = 0;
        arg0->unk94[1] = 0;
        return;
    }
    arg0->unk94[0] = arg0->unk93;
    if (arg0->unk93 != 0) {
        if (arg0->unk9B[0] == 2) {
            arg0->unk94[0] += 9;
        }
    } else {
        func_8003718C(arg0, 0);
    }
    arg0->unk94[1] = 0;
    func_8003718C(arg0, 1);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003718C);

void func_800371E4(struct PlayerObj* arg0)
{
    func_800361F8(arg0);
    if (arg0->unk93 == 5) {
        func_80036E1C(1, 0x1B, 0, 0);
    }
    if (arg0->unk93 == 6) {
        func_80036E1C(1, 0x12, 0, 0);
        func_80036DA0(1, 6, 3, 0);
        arg0->unkC8 = 0;
        arg0->unkCC = 0;
        arg0->unkD0 = 0;
    }
    if (arg0->unk93 == 8) {
        func_80036E1C(1, 0x1B, 1, 0);
    }
}

s32 func_80037290(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0) {
        return 0;
    }

    if (arg0->base.unk2 != 0) {
        return 0;
    }

    if (func_800375B4(arg0) != 0) {
        return 1;
    }

    func_80037708(arg0);

    if (arg0->unk8F == 0) {
        return 0;
    }

    if (D_800F8BF8[arg0->unk96] == 0) {
        return 0;
    }

    arg0->unk84 = 0;
    arg0->unk86 = 0;
    arg0->unk8C = 0;
    func_80037484(arg0, 0);

    return 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037338);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800373DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037484);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003751C);

s32 func_800375B4(struct PlayerObj* arg0)
{
    s32 var_v1;

    if (arg0->unk92 || !(arg0->unkA7 & 2) || arg0->unkA8 != 0x30 || arg0->unk86) {
        return 0;
    }

    var_v1 = 2;
    if (arg0->base.unk15) {
        var_v1 = 1;
    }
    if ((var_v1 & arg0->unk89) || !(arg0->unk80 & 0x40)) {
        return 0;
    }

    func_800350A4(arg0, 0x6A);
    func_80036054(arg0);
    func_80036E98(arg0);
    arg0->unk84 = 0;
    arg0->unk86 = 5;
    arg0->unk8C = 0;
    arg0->unk61 = 0;
    arg0->unkA4 = 0;
    arg0->unk67 = 1;
    if (engine_obj.unk37 == 0) {
        arg0->unkA8 = 0;
    }
    arg0->unk7A = 1;
    arg0->unkE0 = 1;
    arg0->unkE1 = 0x18;
    engine_obj.unk1C = 1;

    if (arg0->base.unk15) {
        arg0->unk20 = FIXED(2.5);
    } else {
        arg0->unk20 = FIXED(-2.5);
    }
    arg0->unk24 = 0x38000;
    arg0->unk2C = 0x4200;
    arg0->unk28 = 0;
    arg0->base.unk5 = 0x22;
    arg0->base.unk6 = 0;

    return 1;
}

void func_80037708(struct PlayerObj* arg0)
{
    s8 temp_s1;

    if (arg0->unk92 == 0) {
        arg0->unk96 = -1;
        func_8003795C(arg0);
        func_80037A24(arg0);
        temp_s1 = arg0->unk96;
        if (arg0->unk96 != -1 && arg0->unk98 < D_800F8CCC[arg0->unk96] && (D_800F8CE4[arg0->unk96] == 0 || arg0->unk99 == 0)) {
            if ((D_800F8C28[arg0->unk96] == 0 || arg0->unk99 == 0 || arg0->unk97 != arg0->unk96)) {
                if ((temp_s1 != 6 || arg0->unk99 != 0)) {
                    D_800F8C78[temp_s1](arg0);
                    arg0->unk97 = temp_s1;
                    arg0->unk8E = 1;
                    arg0->unk8F = 1;
                    arg0->unk90 = 0;
                    arg0->unk91 = D_800F8C4C[temp_s1 * 2];
                    arg0->unk92 = D_800F8C4D[temp_s1 * 2];
                    if (D_800F8CFC[temp_s1] != 0) {
                        arg0->unk98++;
                    }
                    if (D_800F8D14[temp_s1] != 0) {
                        arg0->unk99++;
                    }
                    if (++arg0->unk9A == 3) {
                        arg0->unk9A = 0;
                    }
                    if (temp_s1 == 0x13) {
                        arg0->unkA6--;
                    }
                    func_80037B1C(arg0, temp_s1);
                    if (arg0->unkD9 == 0 && arg0->unk93 == 0 && arg0->unkA4 == 0) {
                        if (temp_s1 == 0) {
                            arg0->unkA2 = 6;
                        }
                        if (temp_s1 == 9) {
                            arg0->unkA2 = 5;
                        }
                        if (temp_s1 == 0x12) {
                            arg0->unkA2 = 7;
                        }
                    }
                }
            }
        }
    }
}

void func_8003795C(struct PlayerObj* arg0)
{
    if (arg0->unk80 & 0x10) {
        if (arg0->unk93 != 0) {
            arg0->unkA6 = 0;
            if (func_80037A98(arg0) == 0) {
                return;
            }
        }
        arg0->unk96 = arg0->unk94[0];
    } else if ((arg0->unk7C & 0x100010) == 0x100000) { // flags?
        s8 temp = arg0->unk94[0];
        if ((temp != 0) && (D_800F8C10[temp] == 0) && (temp != 0x13)) {
            if (arg0->unk93 != 0) {
                arg0->unkA6 = 0;
                if (func_80037A98(arg0) == 0) {
                    return;
                }
            }
            arg0->unk96 = arg0->unk94[0];
        }
    }
}

void func_80037A24(struct PlayerObj* arg0)
{
    if (arg0->unk96 == -1) {
        if (arg0->unk80 & 0x20) {
            arg0->unk96 = arg0->unk94[1];
            return;
        }
        if ((arg0->unk7C & 0x200020) == 0x200000) {
            if ((arg0->unk94[1] != 0) && (arg0->unk94[1] != 0x13)) {
                arg0->unk96 = arg0->unk94[1];
            }
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037A98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037B1C);

void func_80037B90(struct PlayerObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037B98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037BC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037C28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037D08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037DB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037DFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037E4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037EAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037F78);

void func_80037FF0(struct PlayerObj* arg0)
{
    s8 temp_v1; // probably fake

    if ((arg0->base.unk2 == 0) && (arg0->unkD9 == 0) && (arg0->unkE0 == 0) && (temp_v1 = arg0->base.unk5, (arg0->base.unk5 != 0)) && (arg0->base.unk5 != 1) && (arg0->base.unk5 != 0x19) && (temp_v1 != 0x18) && (arg0->unkC5 == 0)) {
        if (func_80038158(arg0) != 0) {
            func_800384DC(arg0);
            if (arg0->unkA2 != 0) {
                func_800362F8(arg0, 0x32);
                return;
            }
            func_800361F8(arg0);
            return;
        }
        func_800381FC(arg0);
        func_80038378(arg0);
        if (func_800380F0(arg0, 0) == 0) {
            func_800380F0(arg0, 1);
        }
    }
}

s32 func_800380F0(struct PlayerObj* arg0, s8 arg1)
{
    s8 temp_v1_2;
    if (arg0->unk9B[arg1] == 0) {
        return 0;
    }
    if (arg0->unk9B[arg1] == 1) {
        arg0->unkA1 = 0x26;
    } else {
        temp_v1_2 = arg0->unk94[arg1];
        if (temp_v1_2 == 0x13) {
            arg0->unkA1 = 0x2C;
        } else {
            arg0->unkA1 = (temp_v1_2 == 0x14) ? 0x2F : 0x29;
        }
    }
    return 1;
}

s32 func_80038158(struct PlayerObj* arg0)
{
    if (arg0->unk80 & 0x10) {
        return 1;
    }
    if (arg0->unk80 & 0x20) {
        return 1;
    }
    if ((arg0->unk7C & 0x100010) == 0x100000) {
        return 1;
    }
    if ((arg0->unk7C & 0x200020) == 0x200000) {
        return 1;
    }
    if (arg0->unk9D && (*(u16*)&arg0->unk7C & 0x10) == 0) {
        return 1;
    }
    if (arg0->unk9E && !(*(u16*)&arg0->unk7C & 0x20)) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800381FC);

void func_80038378(struct PlayerObj* arg0)
{
    u8 var_a1;

    if ((*(u16*)&arg0->unk7C & 0x20) && (arg0->unk9B[1] != 2)) {
        arg0->unk9E++;
        if (arg0->unkB8 == 0) {
            var_a1 = 0x5A;
        }
        if (arg0->unkB8 == 1) {
            var_a1 = 0x96;
        }
        if (arg0->unkB8 == 2) {
            var_a1 = 0x5A;
        }
        if (arg0->unk9E == 0x19) {
            func_8001540C(1, 7, arg0);
            arg0->unk9B[1] = 1;
            return;
        }
        if (arg0->unk9E == var_a1) {
            arg0->unk9B[1] = 2;
        }
        if (arg0->unkB8 == 1) {
            if (arg0->unkA6 != 4) {
                if (arg0->unk9E == 0x5A) {
                    if (arg0->unkA6 < 2) {
                        arg0->unkA6 = 2;
                    }
                }
                if (arg0->unk9E == 0x78) {
                    arg0->unkA6 = 3;
                }
                if (arg0->unk9E == 0x96) {
                    arg0->unkA6 = 4;
                }
            }
        }
    }
}

void func_80038490(struct PlayerObj* arg0)
{
    if (arg0->base.unk2 == 0) {
        func_800384DC(arg0);
        func_80037104(arg0);
        func_800371E4(arg0);
    }
}

void func_800384DC(struct PlayerObj* arg0)
{
    func_80015930(1, 7);
    func_800360B0(arg0);
    arg0->unk9B[0] = 0;
    arg0->unk9B[1] = 0;
    arg0->unk9D = 0;
    arg0->unk9E = 0;
}

void func_80038524(struct PlayerObj* arg0, s32 arg1)
{
    if (arg0->base.unk2 == 0 && arg0->unk8E != 0) {
        arg1 += 0x70;
    }
    func_800350A4(arg0, arg1);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038568);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800385EC);

void func_80038678(struct PlayerObj* arg0)
{
    if (arg0->base.unk2 == 0) {
        if (arg0->unk8F != 0) {
            func_80038748(arg0);
            return;
        }
        if (arg0->unk90 != 0) {
            func_80036534(arg0);
            return;
        }
    }
    if (arg0->base.unk17 == 6) {
        if (arg0->unk5C >= engine_obj.unk46 / 3) {
            func_800350A4(arg0, 5);
            return;
        }
    }
    func_80015DC8(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038748);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800387A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800387F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038854);

void func_800388F0(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0) {
        func_80034604(arg0);
    } else if (func_80037338(arg0) == 0) {
        func_80015DC8(arg0);
        D_800F8D5C[arg0->base.unk6](arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038970);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800389DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038A80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038AE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038B80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038C10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038CA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038D38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038D88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038E44);

void func_80038E90(struct PlayerObj* arg0)
{
    if (arg0->unkC3 != 0) {
        arg0->unk7A = 0;
        arg0->unkE0 = 0;
        func_800361F8(arg0);
        func_8003470C(arg0);
    } else {
        func_80015DC8(arg0);
        D_800F8D88[arg0->base.unk6](arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038F0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038F64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003904C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800390C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039120);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039160);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039230);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039270);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039328);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039378);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039570);

void func_80039700(struct PlayerObj* arg0)
{
    func_80015DC8(arg0);
    D_800F8D94[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003974C);

void func_800397B0(struct PlayerObj* arg0)
{
    if (func_80034238(arg0) == 0) {
        func_80034320(arg0);
    }
}

void func_800397E8(struct PlayerObj* arg0)
{
    func_80034238(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039808);

s32 func_80039880(struct PlayerObj* arg0)
{
    if (arg0->base.unk2 == 0) {
        return 0;
    } else if (arg0->unkC3 != 0) {
        return 0;
    } else if (func_80039F28(arg0) != 0) {
        return 1;
    } else if (func_80039E5C(arg0) == 0) {
        return func_80039C34(arg0) != 0;
    }
    return 1;
}

s32 func_800398F0(struct PlayerObj* arg0)
{
    if (func_80039BB8(arg0) == 0) {
        return 0;
    }
    func_800350A4(arg0, 0x58);
    func_8001540C(1, 7, arg0);
    func_800363B8(arg0, 3);
    arg0->unk84 = 0;
    arg0->unk86 = 0;
    arg0->base.unk5 = 0x30;
    arg0->base.unk6 = 0;
    func_8003A104(arg0);
    return 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003996C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039A00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039AC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039B44);

s32 func_80039BB8(struct PlayerObj* arg0)
{
    if (arg0->base.unk2 != 0 && arg0->unkC3 == 0 && (arg0->unk80 & 0x10) && arg0->unk8E == 0) {
        func_80039C20(arg0);
        return 1;
    }
    return 0;
}

void func_80039C20(struct PlayerObj* arg0)
{
    arg0->unk8E = 1;
    arg0->unkBB = 0;
    arg0->unk8C = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039C34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039CC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039D9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039E5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039F28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003A000);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003A104);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003A1DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003A328);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003A374);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003A3EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003A5E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003A7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003A8A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003A9F0);

void func_8003AAE8(struct PlayerObj* arg0)
{
    func_80015DC8(arg0);
    D_800F8DAC[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003AB34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003ABE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003AD74);

void func_8003AE08(struct PlayerObj* arg0)
{
    func_80015DC8(arg0);
    D_800F8DB8[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003AE54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003AEE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003AF20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003AF58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003AFD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003B044);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003B1A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003B1E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003B24C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003B340);

void func_8003B3DC(struct QuxObj* arg0)
{
    arg0->unk8A = *(u16*)&g_Player.unk7C;
    arg0->unk8C = g_Player.unk80;
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;

    D_800F90D8[arg0->base.state](arg0);
    arg0->unk5C &= ~0x80;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003B458);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003B470);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003B694);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003B7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003B98C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003BA24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003BAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003BB20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003BDA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003BE28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003BF1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003C08C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003C584);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003C624);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003C6EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003C8F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003C9A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003CA44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003CB08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003CBCC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003CCBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003CD38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003CF24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003CF6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D01C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D164);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D254);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D338);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D35C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D39C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D3B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D3F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D4C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D638);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D6EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D7A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D7E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D8A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003D9E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DC1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DC44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DC50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DC8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DCD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DD14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DD2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DD54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DDA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DDDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DE08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DE84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003DF9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003E048);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003E0B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003E0D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003E274);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003E368);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003E488);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003E5F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003E750);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003E8A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003EA08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003EB4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003ED00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003EDF0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003EEF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003F068);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003F204);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003F244);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003F31C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003F44C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003F570);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003F618);

void func_8003F648(struct QuxObj* arg0)
{
    if (!(arg0->unk97 & 2)) {
        D_800F9138[arg0->base.unk6](arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003F698);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003F76C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003F908);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003FA58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003FBD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003FD08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003FF14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003FF58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003FF9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800400C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800401F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80040248);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800402C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800403DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800405D4);

void func_80040608(struct MainObj* arg0)
{
    D_800F9974[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80040644);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80040760);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80040810);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80040838);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80040ABC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80040CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80040DF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80040E44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80040EFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80041020);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80041060);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800411D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80041384);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800413C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004140C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80041524);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80041564);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800415B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80041854);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80041958);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800419B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80041C94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80041DF0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80041F88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004205C);

void func_800420E8(struct MainObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800420F0);

void func_80042120(struct MainObj* arg0)
{
    D_800F9AEC[arg0->base.state](arg0);
    CollisionRelated(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042170);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042248);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004234C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042384);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800423A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042414);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800424CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004258C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800425C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042648);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800426BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004272C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800427C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042824);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042884);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042914);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042950);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042A48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042AFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042CC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042CE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042D20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042D60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042E18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042E70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042EB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042F18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042F80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042FBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043064);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800430C0);

void func_80043128(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043130);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004316C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043198);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043214);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043250);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043280);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800432F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043340);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043390);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800435C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800436D0);

void func_80043720(struct Unk* arg0)
{
    arg0->base.unk5 = arg0->unk90;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004372C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043768);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800437A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004381C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043858);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043898);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043900);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004393C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043978);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043A48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043A84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043B0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043CB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043D54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043D90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043E90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043ECC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043F04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80043F78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004415C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800441E4);

void func_80044314(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004431C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004441C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044458);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044508);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044630);

void func_80044694(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004469C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800446D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044738);

void func_800447A4(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800447AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800447E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044814);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800448C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800448E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044920);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044978);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800449D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044A4C);

void func_80044AA0(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044B18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044B78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044BE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044BFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044C58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044D8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044DE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044F4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80044F88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800450A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80045198);

void func_80045240(struct Unk* arg0)
{
    arg0->base.unk5 = arg0->unk8C;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004524C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800452B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800452FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004539C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80045404);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80045464);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800454A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004550C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80045560);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800455BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80045648);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80045694);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80045728);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800457A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004583C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800458B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80045940);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80045D80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80045DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046104);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046134);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004619C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046220);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004636C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046400);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046610);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046640);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800466A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004677C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046818);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046864);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800468CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800469A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046A4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046AA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046B30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046B80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80046C8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047038);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047078);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047084);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800470C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047140);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047188);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800471C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047244);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047314);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047378);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800473C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047404);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047660);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047794);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800477D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800477DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047818);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047900);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047974);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800479E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047A20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047A34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047B04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047C88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047D04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80047E58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004808C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800480D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004831C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048348);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800483AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800483E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048434);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800484C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004852C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048584);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048610);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048770);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800487AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800487F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048864);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800488F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048970);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048A1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048A58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048B04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048B98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048BD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048C20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048CF8);
