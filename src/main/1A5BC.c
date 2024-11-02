#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80029DBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80029E1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002A098);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002A394);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002A41C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002A484);

void func_8002A6FC()
{
    s8 fill = 0;
    s8* a0 = (u8*)&engine_obj;
    s32 v1 = 0x64 - 1;
    do {
        *a0++ = fill;
    } while (v1-- != 0);
}

void func_8002A728(struct PlayerObj* arg0)
{
    s8 fill = 0;
    s32 v1 = sizeof(struct PlayerObj) - 1;
    s8* a0 = (u8*)arg0;
    do {
        *a0++ = fill;
    } while (v1-- != 0);
}

void func_8002A74C()
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

    func_8002A728(&g_Player);
    func_8002A728(&g_Entity);

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

    func_8002A74C(); // clear main_objects and shot_objects

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

    D_8013E1BE = 0;
    D_80141BE6 = 0;
    D_80175EA0 = 0;
    D_8013E1BC = 0;
    D_80141BE4 = 0;
    D_80175E9C = 0;
    D_8013E188[0] = 0;
    D_8013E18C = 0;
    D_8013E190 = 0;
    D_8013E194 = 0;

    a0 = &D_8013BC28;
    var_v1 = 0x14;
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
        if (!current->active) {
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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B7B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B7DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B810);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B93C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002B9F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002BAA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002BAD0);

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
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E8D4);

// engine_state_3_update_funcs state 4
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E994);

// engine_state_3_update_funcs state 5
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002ED80);

// engine_state_3_update_funcs state 6
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002ED98);

// engine_state_3_update_funcs state 7
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002EDD4);

// engine_state_3_update_funcs state 8 (play video)
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002EF14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F048);

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
    if (D_8013BC34[0] != 0x80) {
        arg0->unk2++;
        func_8002F048();
    }
}

// briefing_room_state_9_update_funcs state 2
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F2A0);

// briefing_room_state_9_update_funcs state 3
void func_8002F47C(struct EngineObj* arg0)
{
    if ((D_8013BC34[0] == 1) || (D_8013BC34[0] == 0x80)) {
        arg0->unk2--;
        func_8002F048();
    }
}

// engine_state_3_update_funcs state 9 (briefing room)
void func_8002F4C4(struct EngineObj* arg0)
{
    arg0->unk40 = 0;
    briefing_room_state_9_update_funcs[arg0->unk2](arg0);
    func_80022730(&D_8013BC28);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F510);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F524);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F584);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F5E8);

// engine_state_3_update_funcs state 10
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F698);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F6E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F7A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F828);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F87C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F8F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F92C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002F9EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002FAB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002FAE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002FB54);

// engine_state_3_update_funcs state 11
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002FBDC);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002FCAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002FCEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002FD28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002FD70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800300AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030128);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800301BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800304E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030728);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030A2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030C54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030DF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030EC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030F9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80030FD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031014);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031064);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80031130);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800320E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032140);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032224);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032300);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032468);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003253C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800325EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003267C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032740);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003277C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800327CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032840);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800328CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032910);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032950);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032A28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80032B04);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80033694);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80035A6C);

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
            temp_v0 = D_801193F0[arg0->unk47];
            if (D_801193F0[arg0->unk47] != 0) {
                arg0->unk54 = &D_801194F0[temp_v0];
                return;
            }
        }
        arg0->unk54 = NULL;
        return;
    }
    if (D_8011AF60[arg0->base.unk17] == 0) {
        var_v0_2 = D_8011A030[arg0->unk47];
    } else {
        var_v0_2 = D_8011A130[arg0->unk47];
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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80035FC4);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80037708);

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

void func_80037B90(void)
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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800388F0);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80038E90);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80039700);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003974C);

void func_800397B0(struct Unk11* arg0)
{
    if (func_80034238(arg0) == 0) {
        func_80034320(arg0);
    }
}

void func_800397E8(struct Unk11* arg0)
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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003AAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003AB34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003ABE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003AD74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003AE08);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003B3DC);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8003F648);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80040608);

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

void func_800420E8(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800420F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80042120);

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

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048DD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048E0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048E70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048EF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048F34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80048F98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049028);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049064);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800490D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800491BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049288);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800492C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004932C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800493F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800494E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004955C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049654);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004970C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800497FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049884);

void func_800498C0(struct MainObj* arg0)
{
}

// didn't notice any differences when nopped out
void func_800498C8(struct MainObj* arg0)
{
    D_800FB0F4[arg0->unk4]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049904);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049AA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049C78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049CBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049CC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049DE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049E24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049E68);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049F20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80049FE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A0AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A0FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A178);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A31C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A378);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A468);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A5B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A5E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A644);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A690);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A6E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A718);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A78C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004A9F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004AB6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004ACDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004ACF0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004AD18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004ADE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004AE00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004AE20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004B040);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004B0A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004B280);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004B2BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004B418);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004B514);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004B668);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004B748);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004B808);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004B8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004B8FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004BAF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004BC14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004BC2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004BCC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004BCFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004BF5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004C210);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004C394);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004C56C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004C654);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004C694);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004C6C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004C734);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004C784);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004C860);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004C97C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004C9E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CA14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CA20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CA5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CA94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CBD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CC64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CCA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CDC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CE48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CE94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CEF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CF24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004CF60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D044);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D160);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D1C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D1D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D210);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D290);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D2E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D31C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D370);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D3C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D408);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D444);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D480);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D4D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D580);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D5E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D61C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D69C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D6CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D6FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D784);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D84C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D930);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004D9CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004DB10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004DCB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004DEA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004DF40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004DFEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004E128);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004E218);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004E300);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004E490);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004E55C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004E6A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004E810);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004E830);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004E890);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004E8E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004EA88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004EC44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004ECB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004ECE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004ED20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004ED60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004EF14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004EFA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004EFE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F0C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F118);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F1A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F228);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F264);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F2A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F34C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F424);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F460);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F4D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F62C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F67C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F6B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F7D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F910);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004F9B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004FAAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004FAE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004FBF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004FC50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004FC80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004FD38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004FF90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8004FFE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800500D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050238);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005026C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050278);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050418);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050480);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050540);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050644);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050690);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800506D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050708);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005077C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050874);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050A9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050BC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050BFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050C64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050C70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050CAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050D14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050E08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050E44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050EB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050F60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80050FE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051020);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051060);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800510D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005115C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800511E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800512BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051338);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051374);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800513DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800514A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051564);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051630);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051678);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005172C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051768);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800517D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051A4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051B74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051C94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051CD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051D60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051F68);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80051F94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052008);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052044);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005216C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800521B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800521DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052218);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800522A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800522C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052324);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052374);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800523EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052444);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052524);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052614);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800526AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800527C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800527F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005284C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800528BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052A68);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052B94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052C2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052C70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052CB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80052E94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800531B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80053224);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80053274);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80053338);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800535CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80053604);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80053640);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005368C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800537E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005398C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80053A88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80053B18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80053B54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80053D04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80053D24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80053EB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005402C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005440C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054518);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005458C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800545EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054710);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054738);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054758);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800548B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054B38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054B98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054BBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054C50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054CA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054D8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054EF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054F14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054F34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054F98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054FBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054FDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80054FE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055024);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055164);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005529C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800552C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800552D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005530C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055358);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800555B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055604);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055640);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005567C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800556D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055710);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055758);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800557B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800557FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055838);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055880);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800558D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055910);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005594C);

void func_800559B4(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800559BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055C54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055E04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055E9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055F1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80055FD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056018);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056054);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056230);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800562AC);

void func_80056470(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056478);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800564B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800565EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056618);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056718);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056738);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056788);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800567C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056AC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056BD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056BDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056C18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056D20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056DB4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80056EF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800570A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057100);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057160);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057308);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057488);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800574B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800574C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800574FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005754C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800576F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800577E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057824);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057874);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057978);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057A44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057A80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057AE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057C00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057D58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057D94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057E34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80057F34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058044);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005807C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800580AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058158);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058194);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058240);

void func_8005824C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058254);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800583B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800585F4);

void func_80058658(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058660);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058680);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800586F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058740);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058AC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058D50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058DBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058DF0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058DFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058E38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80058F94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059010);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005904C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800590BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059154);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800591F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005922C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059290);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059344);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800594D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005952C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059590);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059640);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059978);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800599B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059A94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059B0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059B7C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059C48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059C84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059D6C);

void func_80059E38(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059E40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80059F60);

void func_8005A3DC(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005A3E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005A460);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005A4AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005A4CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005A538);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005A6C0);

void func_8005A750(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005A758);

void func_8005AA0C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005AA14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005AB34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005ABC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005ACA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005AD00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005AEB4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005AF5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B24C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B2C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B3FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B438);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B504);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B52C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B578);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B64C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B708);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B760);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B7AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B818);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B894);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005B8D0);

void func_8005BA24(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005BA2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005BB70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005BC50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005BCA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005BD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005BDE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005BF48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005BFC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005C0E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005C474);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005C804);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005C824);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005C860);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005C960);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CADC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CAFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CB08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CB54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CB90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CC6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CCA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CCFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CD5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CDB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CDEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CE50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CE80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CEBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CF30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CF60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005CF9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D0A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D0D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D118);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D148);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D1F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D230);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D348);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D4E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D7E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D844);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D850);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D88C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D8B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005D9C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005DAB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005DB84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005DBC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005DC58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005DED4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005DF84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E044);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E0CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E108);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E1BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E298);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E3E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E424);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E47C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E500);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E570);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E5C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E754);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E7CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E7EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E860);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E8B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E8F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005E9C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EA18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EA78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EAF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EB40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EBF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EC38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EC58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005ECA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EE2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EF40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EF6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EF78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005EFB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F0F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F124);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F160);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F1A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F230);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F2F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F3D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F47C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F4E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F510);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F558);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F758);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F844);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F864);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F87C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F9A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005F9F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005FB38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005FBBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005FCAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005FCD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005FDBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8005FE1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060144);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060228);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006025C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060268);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800602A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060354);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800603A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800603DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800604A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800604EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060538);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060574);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800606D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060870);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800608CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006097C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800609C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060A10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060A58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060A88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060AC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060BC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060D3C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060DC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060E08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060E14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060E50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060E94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060F5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060F98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80060FF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006104C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061088);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800610F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006114C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061188);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800611E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061240);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006128C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800612C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061310);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006135C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061424);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800614E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061590);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800615CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006185C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800618F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061918);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061B58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061D18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061D90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061DFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80061F2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800620C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800621C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062240);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062338);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800623C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062400);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800624B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062550);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800625C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062650);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800626F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062778);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062910);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062A0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062AEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062BBC);

void func_80062D18(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062D20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062D60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062D9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062E70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062E90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80062F60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800630AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800630DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800631A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800631C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063234);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800632A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063334);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006346C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063600);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006364C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800636A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800637A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063814);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063854);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063914);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006398C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063B20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063F80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063FBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80063FE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800640B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800640F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064154);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064338);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064360);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800643B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006458C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800646B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800646EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800648D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800649C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064AE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064B38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064C84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064CF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064DC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064E58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064F24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80064FD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065088);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065168);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065268);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006528C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800652C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006530C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006537C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065458);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065538);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065574);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006565C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065704);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065794);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065898);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065910);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065930);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006596C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065A54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065B04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065B24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065B30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065B8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065BC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065CD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065DCC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80065EA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800661AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006630C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066478);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066580);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800665BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066804);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066858);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006689C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006692C);

void func_80066968(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066970);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066A48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066A84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066B00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066C40);

void func_80066C64(struct Unk* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066C74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066DAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066DE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80066F1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800671D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800672BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800672D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800672EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067350);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006738C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067550);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067628);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067640);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006767C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800676E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067740);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006777C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800677F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067860);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800678B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800678F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067A80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067BB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067C34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067D00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067DAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80067EE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068000);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068060);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068074);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006808C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800680C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068108);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068138);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800681C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068340);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068404);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800684BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800684F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068548);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800688B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068A10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068A68);

void func_80068B3C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068B44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068B80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068C2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068D4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068D6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80068F88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069000);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006917C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800691B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069248);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800692AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800692E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069330);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800693AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069414);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069450);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006951C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069610);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069660);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006970C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069748);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800698D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069A08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069A6C);

void func_80069A8C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069A94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069BE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069CE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069D74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069D94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069DA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069E28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069E64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069F28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80069FDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A018);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A078);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A0E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A130);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A16C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A1B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A208);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A26C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A2BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A388);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A450);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A50C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A55C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A638);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A70C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A740);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A74C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A788);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A7F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A83C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006A998);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006AA18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006AA54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006AAB4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006AC8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006ACC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006AD84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006AE0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006AE50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006AE80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006AF70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B114);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B180);

void func_8006B1BC(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B1C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B2A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B398);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B514);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B568);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B5F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B6B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B79C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B848);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B8BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006B8F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006BAA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006BAC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006BB00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006BB70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006BD1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006BFBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006BFF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006C07C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006C170);

void func_8006C278(struct Unk* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006C288);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006C2C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006C378);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006C598);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006C61C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006C670);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006C6AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006CA80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006CB14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006CB50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006CC3C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006CD80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006CDD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006CE9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006CED8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006CF2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006CFB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006D280);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006D368);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006D3DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006D69C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006D6D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006D830);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006D888);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006DB04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006DBE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006DC24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006DCF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006DD44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006DF68);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E034);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E260);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E2E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E334);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E414);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E450);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E594);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E604);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E674);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E6B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E750);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E7CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E88C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006E920);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006EA78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006EAA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006EB40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006ECC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006ED44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006EF28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F0A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F0DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F244);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F304);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F41C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F494);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F504);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F584);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F5F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F83C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006F86C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006FA24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006FABC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006FAE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006FB20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006FBFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006FCB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006FD50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006FEC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8006FFC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800700AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070118);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800701DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070294);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800702E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070348);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800703E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800704AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070514);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070648);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800706D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070778);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800708DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070948);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070A38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070C88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070CDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070D2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80070EE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007100C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800710D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071228);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800712A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800713A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071468);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800714C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800714F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071598);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800715D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007168C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071740);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800718F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007196C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800719FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071A38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071A74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071AD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071B60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071C00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071C60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071CB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071D1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071D30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071EEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80071F5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007203C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007211C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072158);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072194);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072204);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072240);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800722A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072418);

void func_800725DC(struct Unk* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800725EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072628);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800726CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800727C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800728C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072904);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072960);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072A14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072A84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072BCC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072C20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072CC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072D14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072DB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072DF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072E34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072EF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072F68);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80072FF0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073084);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073100);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073164);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800731A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073228);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073294);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007330C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007342C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800734A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073500);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007353C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800735BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073650);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007368C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800736DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073748);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800737FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073878);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800738EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073938);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073974);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800739D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073B00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073B58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073BDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073C08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073C44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073CA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073E10);

void func_80073E3C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073E44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073E80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80073F90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074068);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800740CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074158);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074194);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074220);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007427C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800742AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074368);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800743FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074438);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800745E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800747EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007482C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074838);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074874);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800748B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007491C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074958);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800749B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074A0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074A48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074B10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074B68);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074BD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074C14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074CB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074D10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074E84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074F4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074FC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80074FE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007501C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075064);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800750A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075128);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007517C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800751AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075320);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075630);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007566C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075700);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800757F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800758FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075908);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075944);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800759EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075A54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075B54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075BC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075C6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075D38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075DDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075E18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80075E78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007601C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800760C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800761A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007624C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076288);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076364);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007651C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007662C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800766FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007681C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800768CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076908);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800769FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076A74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076AB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076B14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076B84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076C1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076C70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076CAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076D14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076DB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076E1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076E88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076F14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076F74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80076FB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077028);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800770F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800771AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007720C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077258);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077318);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077444);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077490);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077504);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077580);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077614);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077694);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077738);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077798);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800777D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007781C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077868);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800778A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077954);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800779D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077A44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077A80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077B0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077B74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077BD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077C40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077C74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077CE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077D48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077DF0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077ED0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077F60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80077FFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800780D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80078180);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007826C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80078314);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007856C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800785E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800786AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007872C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007877C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800788E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80078DF0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80078E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80078EB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80078FA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800790AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800790E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800791D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007927C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079364);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800793AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079518);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079568);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079608);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079644);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800796DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079794);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800797E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079824);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079914);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007996C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079A50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079A8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079B50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80079FE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A048);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A09C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A12C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A168);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A1EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A2B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A3B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A444);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A4B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A4EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A63C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A7F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A854);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A8AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A930);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007A96C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007AB1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007ADB4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007AE2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007AFB4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B054);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B0F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B140);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B180);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B1BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B2FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B3A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B418);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B588);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B5F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B640);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B68C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B6BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B834);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007B90C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007BABC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007BB90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007BC0C);

void func_8007BC48(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007BC50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007BCC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007BD4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007BE40);

void func_8007BF74(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007BF7C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007BFB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007BFF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C090);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C144);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C2B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C2D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C30C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C3FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C5C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C5F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C69C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C6E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C7D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C824);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C860);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C890);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C914);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C968);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007C9B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007CA68);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007CC8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007CD54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007CDA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007CDE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007CE3C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007CE98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007CEF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007CF68);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007CFA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D010);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D0CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D138);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D174);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D234);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D2F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D324);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D374);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D3DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D424);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D470);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D4E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D558);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D594);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D5D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D710);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D838);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007D9AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007DA20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007DAFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007DBDC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007DC18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007DC54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007DD0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007DD98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007DF50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E01C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E098);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E128);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E1C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E25C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E2B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E350);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E45C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E498);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E4C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E5D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E66C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E6F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E848);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E918);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007E95C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007EA3C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007EA94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007EAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007EBD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007EC1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007EC74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007ECEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007EDC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007EE18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007EED8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007EF94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F00C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F05C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F0B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F174);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F2F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F360);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F3B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F404);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F50C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F564);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F5B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F690);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F71C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F780);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F878);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F93C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007F9C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007FA4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007FAA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007FB48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007FB98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007FBFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007FC78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007FCC4);

void func_8007FD1C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007FD24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007FE84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007FF00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8007FFFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800802A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008030C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80080370);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800804A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800805D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80080604);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80080640);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800806A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80080700);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80080834);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80080D20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80080D5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80080DF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80080F04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008107C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800810C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081104);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081198);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800811D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081230);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008127C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800812E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008134C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800813BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081404);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800814E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081508);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081564);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800815B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081624);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800816DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081718);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081830);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008186C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800818C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081954);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800819C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081B64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081BA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081CF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081D30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80081E44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082014);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082050);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800820A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082170);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008225C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082354);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082404);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082434);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082470);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082574);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800826C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082710);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082784);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008284C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008286C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082878);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800828B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800829EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082A28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082B2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082B68);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082BA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082C04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082C70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082CC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082D00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082D48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082D9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082E30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082E88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082F20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80082FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800830D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008318C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083218);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008329C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800833D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800834B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083544);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083574);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800835B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083688);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083710);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800837FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083954);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800839B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083A18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083A58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083B20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083BB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083C2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083D30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083DC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083E44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083E70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083EAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083F6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80083FFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800840D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084154);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800841D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084218);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084254);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084338);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084394);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008442C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800844AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084534);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084570);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800845C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008460C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800846D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084724);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084774);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800847B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084870);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084910);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008498C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800849FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084A40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084A7C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084B14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084CD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084DB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084E10);

void func_80084E4C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084E54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80084EE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008502C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800851FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085238);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800852C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800853A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085460);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085580);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085604);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085640);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800856C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085768);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800857C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085814);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800858DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085988);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085A44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085BE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085C38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085D38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085DCC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085E70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085ECC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085F08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085F50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80085F8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086008);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086124);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086268);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800862A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800862F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800863E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086488);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008649C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800864FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008654C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086640);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086704);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086740);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800867C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086860);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086900);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800869BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800869F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086A6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086B08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086B60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086B74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086BB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086C00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086C70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086D04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086D84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086E80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086F28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80086F78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008700C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087088);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800870FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087168);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800871C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087254);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800872E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087364);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087414);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008746C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008752C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008759C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087604);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008765C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087698);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087708);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800877A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087860);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087928);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087980);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087A00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087AF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087B98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087BE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087C70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087D3C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087E0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087ED4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087F30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087F78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80087FB4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088020);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800880BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088140);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800881F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088338);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800883CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800884D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088530);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088584);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800885DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088658);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800886A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800886F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800887DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008888C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800888D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088974);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800889A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800889DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088BA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088BE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088C40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088D30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088D8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088E04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088EA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088F78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80088FF0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800890B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089138);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800891C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008924C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089314);

void func_80089334(struct Unk* arg0)
{
    arg0->base.unk5 = arg0->unk94;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089340);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008937C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800893DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089438);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089474);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800894BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089524);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089588);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089798);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089910);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089984);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089A10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089AA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089B58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089C7C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089EBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089EC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089F58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089F94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089FAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80089FD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008A024);

void func_8008A05C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008A064);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008A180);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008A2E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008A3B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008A4D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008A60C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008A778);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008A8E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008A9F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008AAF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008AC20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008AC40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008AD48);

void func_8008AD74(void)
{
}

void func_8008AD7C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008AD84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008ADC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008ADFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008AE94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008AEC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008AED0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008AEE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008AF10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008AF30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B020);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B188);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B270);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B33C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B42C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B4B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B5C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B69C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B7D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B898);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B8B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B984);

void func_8008B9B0(void)
{
}

void func_8008B9B8(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B9C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008B9FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008BA38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008BB6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008BCB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008BD10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008BD5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008BDAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008BE74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008BEC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008BF00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008BF54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C014);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C0C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C10C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C204);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C240);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C27C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C30C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C360);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C39C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C3F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C43C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C4B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C5A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C664);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C7E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C888);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C8E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C95C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C998);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008C9E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008CA60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008CB2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008CBF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008CC7C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008CCD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008CD44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008CD80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008CF68);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008CFAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D050);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D0D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D138);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D19C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D278);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D2FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D340);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D37C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D3B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D410);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D460);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D4E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D548);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D590);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D5C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D764);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D830);

void func_8008D86C(struct Unk* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D874);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D8DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D95C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008D9C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008DAAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008DAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008DC5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008DC9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008DD38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008DDE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008DE5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008DEC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008DF1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008DF8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E040);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E0CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E14C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E18C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E1E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E244);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E318);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E354);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E3C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E404);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E45C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E4BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E590);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E5CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E638);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E67C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E6D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E748);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E8C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E99C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008E9B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008EA3C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008EA88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008EAE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008EBC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008EC48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008ED18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008EDE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008EED4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008EF94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F01C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F0A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F134);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F16C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F1A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F3F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F4BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F578);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F6FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F76C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F7F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F884);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F938);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008F974);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008FA0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008FA88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008FB38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008FBCC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008FD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008FDF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008FEE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8008FF50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009002C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800900E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090148);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800901B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009027C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090470);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090508);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800905D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800906E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090720);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090838);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009093C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009099C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090A28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090AC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090B04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090BD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090BE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090C54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090CFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090D24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090D6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090F0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80090FC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091008);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800910E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009114C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800911DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091218);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091448);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800914EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800915C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091754);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800917AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091898);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009197C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800919C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091A00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091AC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091C64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091D1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091E18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091E38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091EC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80091FC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009216C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800921E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009227C);

void func_800922D8(struct WeaponObj* arg0)
{
    D_80108728[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092314);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092408);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092490);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800924F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092598);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092600);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092614);

void func_80092648(struct WeaponObj* arg0)
{
    D_80108738[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092684);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009273C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800927B4);

void func_800927EC(struct WeaponObj* arg0)
{
    D_80108748[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092828);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092918);

void func_800929A0(struct WeaponObj* arg0)
{
    D_80108758[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800929DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092B5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092C2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092D64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80092F08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093014);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093130);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800931A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093260);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800932A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093310);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800933A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800933EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009343C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009347C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800934D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093524);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093564);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093610);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009372C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009377C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800937EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093858);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800938C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093930);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800939F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093A5C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093AAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093B4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093C08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093C54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093CBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093D78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093EB4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80093FC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009403C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094078);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094104);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094154);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009416C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800941D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094280);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800942E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009443C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800944B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009462C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800946F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094794);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009481C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009485C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800948D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094A04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094A78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094B24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094C18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094D40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094E50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094EC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094F14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80094F74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800951C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095254);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800953D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095430);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009547C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800954BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095538);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009564C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095770);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800957B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095854);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009596C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095A28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095AAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095B10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095B94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095BE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095C38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095CC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095D18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095D60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095DA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095E3C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80095F9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096018);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096060);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096170);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800961B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009633C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800963E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096584);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009663C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096794);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096834);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800968F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096994);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800969D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096A84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096B54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096C8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096E10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80096EA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097048);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800970EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097144);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800971D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097214);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097278);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800972C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800972DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097328);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097384);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097430);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800975DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097670);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800976DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097740);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097780);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800977D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097804);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097860);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800978DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097A24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097AC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097B14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097B28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097BA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097CF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097DD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097EEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80097FC4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098138);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800981CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098338);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098474);

void func_800985F4(struct WeaponObj* arg0)
{
    D_80108B88[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098630);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098728);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800987A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800987DC);

void func_80098838(struct WeaponObj* arg0)
{
    D_80108BA8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098874);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800988C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098970);

void func_80098990(struct WeaponObj* arg0)
{
    D_80108BC0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800989CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098A78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098A9C);

void func_80098ABC(struct WeaponObj* arg0)
{
    D_80108BD8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098AF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098C08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098C84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098CC0);

void func_80098D64(struct ShotObj* arg0)
{
    D_80108BE4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098DA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098EA8);

void func_80098F4C(struct WeaponObj* arg0)
{
    D_80108C00[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80098F88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099118);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800992C4);

void func_800992FC(struct WeaponObj* arg0)
{
    D_80108C38[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099338);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099388);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099480);

void func_800994A0(struct ShotObj* arg0)
{
    D_80108C74[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800994DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099784);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009982C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800998D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800999D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099A28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099A8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099B0C);

void func_80099B30(struct ShotObj* arg0)
{
    D_80108CAC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099C68);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099CF0);

void func_80099D10(struct ShotObj* arg0)
{
}

void func_80099D18(struct ShotObj* arg0)
{
    D_80108CC4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099D54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099E34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099F28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_80099F48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A10C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A264);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A338);

void func_8009A358(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    CollisionRelated(arg0);
    D_80108CE4[arg0->base.state](arg0);
}

void func_8009A3B4(struct ShotObj* arg0)
{
    if (arg0->unk7C->base.unk15 == 0) {
        arg0->base.x_pos.val = arg0->unk7C->base.x_pos.val + FIXED(-75);
    } else {
        arg0->base.x_pos.val = arg0->unk7C->base.x_pos.val + FIXED(75);
    }
    arg0->base.y_pos.val = arg0->unk7C->base.y_pos.val + FIXED(2);
    arg0->unk42 = arg0->unk7C->unk42;
    arg0->base.on_screen = 0;
    D_80108CF8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A448);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A4F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A598);

void func_8009A5B8(struct ShotObj* arg0)
{
    D_80108D28[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A5F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A6B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A7D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A7F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A87C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A964);

void func_8009A984(struct ShotObj* arg0)
{
    if (arg0->unk84 == 0) {
        CollisionRelated(arg0);
    }
    D_80108D5C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009A9E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009AC40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009AD08);

void func_8009AD28(struct ShotObj* arg0)
{
}

void func_8009AD30(struct ShotObj* arg0)
{
    D_80108D74[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009AD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009ADF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009AEBC);

void func_8009AEDC(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009AEE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009AF98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B020);

void func_8009B040(struct ShotObj* arg0)
{
    D_80108D88[arg0->base.state](arg0);
}

void func_8009B07C(struct ShotObj* arg0)
{
    D_80108DA8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B0B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B12C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B1C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B1E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B2F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B3C8);

void func_8009B3E8(struct ShotObj* arg0)
{
    D_80108E48[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B424);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B594);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B654);

void func_8009B674(struct ShotObj* arg)
{
}

void func_8009B67C(struct ShotObj* arg0)
{
    D_80108E5C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B6B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B734);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B7D8);

void func_8009B7F8(struct ShotObj* arg0)
{
    D_80108E9C[arg0->base.state](arg0);
    if (arg0->base.state >= 3) {
        CollisionRelated(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B85C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009B9B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009BA4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009BA6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009BAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009BC14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009BD08);

void func_8009BD28(struct ShotObj* arg0)
{
    D_80108EBC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009BD64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009BE14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009BEF4);

void func_8009BF14(struct ShotObj* arg0)
{
    D_80108ECC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009BF50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009BFE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C0D0);

void func_8009C0F0(struct ShotObj* arg0)
{
    D_80108EDC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C12C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C238);

void func_8009C258(struct ShotObj* arg)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C260);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C298);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C344);

void func_8009C364(struct ShotObj* arg0)
{
    D_80108F54[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C3A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C45C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C588);

void func_8009C5F0(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    D_80108F6C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C638);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C784);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C860);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C96C);

void func_8009C9C8(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C9D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009C9F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009CAA0);

void func_8009CAC0(struct ShotObj* arg0)
{
    D_80108F90[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009CAFC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009CBA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009CC44);

void func_8009CC64(struct ShotObj* arg0)
{
    D_80108FAC[arg0->base.state](arg0);
    CollisionRelated(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009CCB4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009CD80);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009CDE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009CF18);

void func_8009CF38(struct ShotObj* arg0)
{
    D_80108FCC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009CF74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009D048);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009D1D8);

void func_8009D1F8(struct ShotObj* arg0)
{
}

void func_8009D200(struct ShotObj* arg0)
{
    D_80108FF4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009D23C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009D3F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009D560);

void func_8009D580(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009D588);

void func_8009D74C(struct ShotObj* arg0)
{
    D_80109008[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009D788);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009D85C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009D8F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009DA08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009DA28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009DA7C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009DB1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009DB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009DCF4);

void func_8009DD40(struct ShotObj* arg0)
{
    D_801090AC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009DD7C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009DE04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009DF40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009DF60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009DFA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E098);

void func_8009E0B8(struct ShotObj* arg0)
{
    D_8010910C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E0F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E188);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E34C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E3A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E490);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E5A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E5B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E608);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E690);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E718);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E7EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E8E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009E9EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009EAA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009EAF0);

void func_8009EB6C(struct ShotObj* arg0)
{
    D_80109160[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009EBA8);

void func_8009ED70(struct Unk* arg0)
{
    func_80015DC8(arg0);
    func_8002B694(arg0);
    func_8002D9BC(arg0);

    if (func_8002BB80(arg0, &g_Player) != 0) {
        if (arg0->base.unk2 & 0x40) {
        label:
            func_800AF808(arg0);
        }
    } else if (!(arg0->base.unk2 & 0x40) || (CollisionRelated(arg0), arg0->unk70 == 0)) {
        if (func_8002B160(arg0) == 0) {
            is_on_screen(arg0);
            return;
        }
    } else {
        goto label; // unfortunately seems to be necessary for a match
    }

    arg0->base.state++;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009EE40);

void func_8009EE60(void)
{
}

void func_8009EE68(struct ShotObj* arg0)
{
    if (arg0->unk84 == 0) {
        CollisionRelated(arg0);
    }
    D_8010918C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009EEC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F160);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F218);

void func_8009F238(struct ShotObj* arg0)
{
}

void func_8009F240(struct ShotObj* arg0)
{
    D_801091B4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F27C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F3A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F44C);

void func_8009F46C(struct ShotObj* arg0)
{
    struct BaseObj* unk7C = arg0->unk7C;
    arg0->base.x_pos.val = unk7C->x_pos.val;
    arg0->base.y_pos.val = unk7C->y_pos.val;
    D_801091C4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F4C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F594);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F618);

void func_8009F638(struct ShotObj* arg0)
{
    D_801091F0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F674);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F89C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F94C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009F9E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009FB38);

void func_8009FB58(struct ShotObj* arg0)
{
}

void func_8009FB60(struct ShotObj* arg0)
{
    D_8010922C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009FB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009FD00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009FE38);

void func_8009FE58(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009FE60);

void func_8009FF10(struct ShotObj* arg0)
{
    D_80109248[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8009FF4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A00C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A0150);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A0170);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A02FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A035C);

void func_800A037C(struct ShotObj* arg0)
{
    D_8010925C[arg0->base.state](arg0);
}

void func_800A03B8(struct ShotObj* arg0)
{
    D_801094EC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A03F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A068C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A0A18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A0A38);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A0C4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A0FC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A0FE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A12EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A16DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A16FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A18A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A18F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A19A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A1B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A1BEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A1C90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A1CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A1E3C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A1F7C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2098);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A220C);

void func_800A2278(struct ShotObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    D_8010958C[arg0->base.state](arg0);
    CollisionRelated(arg0);
}

void func_800A22D4(struct ShotObj* arg0)
{
    D_801096F4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2310);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A23B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A23C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A23E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A241C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A24F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A25EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2748);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A27F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2870);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2928);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A29C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2A58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2AA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2B8C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2C70);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2D54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2E6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2EB4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A2F2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A3010);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A3078);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A3170);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A31CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A325C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A32B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A33A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A348C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A3520);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A3658);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A366C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A3758);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A382C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A38B0);

void func_800A3924(struct ShotObj* arg0)
{
    D_8010978C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A3960);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A3A4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A3C50);

void func_800A3C70(struct ShotObj* arg0)
{
}

void func_800A3C78(struct ShotObj* arg0)
{
    D_801097CC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A3CB4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A3FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4230);

void func_800A4284(struct ShotObj* arg0)
{
}

void func_800A428C(struct ShotObj* arg0)
{
    D_801097E4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A42C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4518);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A46D4);

void func_800A46F4(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A46FC);

void func_800A47C4(struct ShotObj* arg0)
{
    D_8010984C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4800);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4968);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4A50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4ABC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4ADC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4D00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4D20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4E48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4F04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4F24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A4FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5070);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A50EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5144);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5194);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5318);

void func_800A5348(struct ShotObj* arg0)
{
    D_801098B8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5384);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5404);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5460);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5500);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5540);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A56C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A56E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5A04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5AA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5BA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5C90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5D20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5D78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5DEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5E60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A5F4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6028);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6094);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A60D0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A61CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6238);

void func_800A6258(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6260);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A62D0);

void func_800A62F0(struct ShotObj* arg0)
{
    struct WeaponObj* temp_s0 = arg0->unk7C;
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    CollisionRelated(arg0);
    if (temp_s0->base.state == 2) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
        arg0->base.unk6 = 0;
    }
    D_80109950[arg0->base.state](arg0);
}

void func_800A6374(struct ShotObj* arg0)
{
    D_80109998[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A63B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6510);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6600);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A666C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6794);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A67FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6860);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6940);

void func_800A6960(struct ShotObj* arg0)
{
    D_801099C0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A699C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6C00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6C7C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6DCC);

void func_800A6DEC(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A6DF4);

void func_800A6FCC(struct ShotObj* arg0)
{
    D_801099E8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7008);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7104);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7208);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7240);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7318);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A73A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A73C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7458);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A74E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7504);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7570);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7600);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A766C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A77D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7820);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7878);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7928);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A79A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A79E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7A54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7A90);

void func_800A7AF0(struct ShotObj* arg0)
{
    D_80109A78[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7B2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7BC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7BE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7C50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7CE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7E10);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7E40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7E98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7F44);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A7FF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8074);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A80D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8164);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A81E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A826C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A829C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A82EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A833C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A836C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A83C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A84D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A858C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8628);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8A58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8AE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8B88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8C88);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8D1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8D68);

void func_800A8DB8(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8DC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8E50);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A8FBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9054);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A90C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A916C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A91D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9210);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A92C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9334);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A93FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A94A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A94D4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9544);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9654);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A96F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A97C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9818);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A98AC);

void func_800A9928(struct ShotObj* arg0)
{
    D_80109B7C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9964);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9AEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9C24);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9C7C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9CBC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9D98);

void func_800A9DB8(struct ShotObj* arg0)
{
    D_80109BC4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9DF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9EC0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9F30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800A9FD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA000);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA030);

void func_800AA10C(struct ShotObj* arg0)
{
    D_80109BE0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA148);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA20C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA2FC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA3A0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA488);

void func_800AA5A4(struct ShotObj* arg0)
{
    D_80109BF8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA5E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA68C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA730);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA7B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA85C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA954);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AA994);

void func_800AAA98(struct ShotObj* arg0)
{
    D_80109C20[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AAAD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AAB74);

void func_800AAC5C(struct ShotObj* arg0)
{
    D_80109C2C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AAC98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AAD44);

void func_800AAD64(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AAD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AAE94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AAFF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB050);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB128);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB170);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB224);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB32C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB384);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB3A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB4C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB518);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB564);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB5A4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB66C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB6C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB710);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB768);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB814);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB868);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB8EC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB98C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AB9C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ABB50);

void func_800ABB70(struct ShotObj* arg0)
{
    struct WeaponObj* temp_s1 = arg0->unk7C;
    if (temp_s1->unk94 == 2) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi - 20, -1);
    }
    if (temp_s1->unk94 == 1) {
        arg0->unk8C = 0;
        arg0->base.state = 1;
        arg0->base.unk5 = 3;
        arg0->base.unk6 = 0;
        arg0->base.unk7 = 1;
        arg0->unk50 = 0;
        temp_s1->unk8C = 0;
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi + 15, arg0->base.y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->base.x_pos.i.hi - 15, arg0->base.y_pos.i.hi - 20, -1);
        arg0->base.x_pos.i.hi = 0;
        arg0->base.y_pos.i.hi = 0;
        arg0->unk5C = 0x30;
        return;
    }
    arg0->base.on_screen = 0;
    D_80109D84[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ABE08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC114);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC180);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC204);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC31C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC364);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC3BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC440);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC4A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC4F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC550);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC5BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC610);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC66C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC6A8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC6E8);

void func_800AC708(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC710);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC7CC);

void func_800AC7EC(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
    }
    arg0->base.on_screen = 0;
    D_80109DF8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC848);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AC8C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ACCAC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ACD04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ACD84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ACDE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ACE90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ACF60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD00C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD080);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD12C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD1B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD224);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD338);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD404);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD440);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD47C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD4DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD538);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD630);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD66C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD6DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD820);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD868);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD8C0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD92C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AD9C4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ADA0C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ADA64);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ADAD8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ADBE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ADCE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ADD40);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ADDB4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ADE04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ADE54);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ADED4);

void func_800ADEF4(struct ShotObj* arg0)
{
    D_80109EE8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800ADF30);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE1BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE2AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE2FC);

void func_800AE31C(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE324);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE3D4);

void func_800AE3F4(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->base.state = 2;
        arg0->base.unk5 = 0;
    }
    arg0->base.on_screen = 0;
    D_80109F44[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE450);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE4F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE594);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE63C);

void func_800AE65C(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->base.state = 3;
    }
    D_8010A064[arg0->base.state](arg0);
}

void func_800AE6B4(struct BazObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    arg0->base.x_pos.val = g_Player.base.x_pos.val;
    arg0->base.y_pos.val = g_Player.base.y_pos.val;

    if (arg0->base.state == 0) {
        func_800AE714(arg0, ptr);

    } else {
        func_800AE790(arg0, ptr);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE714);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE790);

void func_800AE7DC(struct UnkObj* arg0)
{
    struct PlayerObj* player = &g_Player;

    arg0->unk47 = player->unk47;
    arg0->unk15 = player->base.unk15;
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;

    if (arg0->unk4 == 0) {
        func_800AE848(arg0, player);
    } else {
        func_800AE88C(arg0, player);
    }
}

void func_800AE848(struct UnkObj* arg0, struct PlayerObj* player)
{
    if (player->unk8C != 0) {
        if (player->unk8C > 0) {
            arg0->unk3 = 1;
            func_800AEA58();
            return;
        }
        player->unk8C = 0;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE88C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE8E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE95C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AE9D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AEA58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AEAA0);

void func_800AEAC0(struct VisualObj* arg0)
{
    struct PlayerObj* var_a1;
    if (g_Player.unkDE == 0) {
        var_a1 = &g_Player;
    } else {
        var_a1 = &g_Entity;
    }
    D_8010A1A0[arg0->base.state](arg0, var_a1);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AEB1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AEBA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AEC48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AEC9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AED18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AEE5C);

void func_800AEED8(struct VisualObj* arg0)
{
    if (arg0->base.state == 0) {
        func_800AEF18(arg0);
    } else {
        func_800AF02C(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AEF18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF02C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF084);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF15C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF1AC);

void func_800AF22C(struct VisualObj* arg0)
{
    struct PlayerObj* var_a1 = &g_Entity;
    if (!(arg0->base.unk2 & 2)) {
        var_a1 = &g_Player;
    }
    if (arg0->base.state == 0) {
        func_800AF28C(arg0, var_a1);
    } else {
        func_800AF388(arg0, var_a1);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF28C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF388);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF488);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF504);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF58C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF610);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF658);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF6A0);

void func_800AF808(struct Unk* arg0)
{
    func_800AF828(arg0, 0);
}

void func_800AF828(struct Unk* arg0, s8 arg1)
{
    func_800AFAB4(arg1, arg0->base.x_pos.i.hi, arg0->base.y_pos.i.hi, (get_random() & 1) ^ 1);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF878);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AF95C);

struct Unk* func_800AFAB4(s8 arg0, s16 x, s16 y, u8 arg3)
{
    struct Unk* temp_v0 = find_free_visual_obj();
    if (temp_v0 != NULL) {
        temp_v0->base.active = 0x21;
        temp_v0->base.id = 4;
        temp_v0->base.unk2 = arg0;
        temp_v0->base.state = 0;
        temp_v0->base.unk5 = 0;
        temp_v0->base.unk6 = 0;
        temp_v0->unk5C = arg3;
        temp_v0->base.x_pos.i.hi = x;
        temp_v0->base.x_pos.i.lo = 0;
        temp_v0->base.y_pos.i.hi = y;
        temp_v0->base.y_pos.i.lo = 0;
        temp_v0->base.unk15 = 0;
        temp_v0->base.bg_offset = 0;
        temp_v0->base.unk16 = 1;
    }
    return temp_v0;
}

void func_800AFB50(struct VisualObj* arg0)
{
    if (arg0->base.state == 0) {
        func_800AFB90(arg0);
    } else {
        func_800AFC4C(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AFB90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AFC4C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AFC9C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AFD20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AFD6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AFDA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AFE20);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AFEA4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AFF08);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AFF28);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800AFF78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B0320);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B054C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B0600);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B06AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B0804);

void func_800B0890(struct VisualObj* arg0)
{
    D_8010A430[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B08CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B0B48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B0C78);

void func_800B0C98(struct VisualObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B0CA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B10E4);

void func_800B1354(struct VisualObj* arg0)
{
    if (arg0->base.state == 0) {
        func_800B1394(arg0);
    } else {
        func_800B1450(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1394);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1450);

void func_800B14E8(struct VisualObj* arg0)
{
    D_8010A4CC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1524);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B158C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B16B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1758);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B17AC);

void func_800B17CC(struct VisualObj* arg0)
{
    D_8010A4E0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1808);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1864);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B199C);

void func_800B19BC(struct VisualObj* arg0)
{
    D_8010A4EC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B19F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1A48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1AD8);

void func_800B1AF8(struct VisualObj* arg0)
{
    D_8010A520[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1B34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1B74);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1C3C);

void func_800B1C5C(struct VisualObj* arg0)
{
    D_8010A52C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1C98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1CF4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1D4C);

void func_800B1D6C(struct VisualObj* arg0)
{
    D_8010A538[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1DA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1DE4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1E84);

void func_800B1EA4(struct VisualObj* arg0)
{
    D_8010A544[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1EE0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B1F78);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2070);

void func_800B2090(struct VisualObj* arg0)
{
    D_8010A570[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B20CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2200);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B22B4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B23DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2444);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2544);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2698);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2880);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B28CC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2A3C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2AD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2C8C);

void func_800B2D48(struct VisualObj* arg0)
{
    D_8010A5B0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2D84);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2DD0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2E98);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B2F60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3000);

void func_800B3020(struct VisualObj* arg0)
{
    struct BaseObj* temp_v1 = arg0->unk50;

    arg0->base.x_pos.val = temp_v1->x_pos.val;
    arg0->base.y_pos.val = temp_v1->y_pos.val;
    D_8010A5C8[arg0->base.state](arg0);
}

void func_800B3074(struct VisualObj* arg0)
{
    D_8010A5D4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B30B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3100);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B320C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B322C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3358);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3444);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B34EC);

void func_800B3508(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    D_8010A5E4[arg0->base.unk2](arg0);
    is_on_screen(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B355C);

void func_800B357C(struct VisualObj* arg0)
{
    D_8010A5F0[arg0->base.state](arg0);
}

void func_800B35B8(struct VisualObj* arg0)
{
    D_8010A64C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B35F4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B36F0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B372C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3768);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B37F8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3848);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3884);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B392C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B397C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B39B8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3A60);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3AB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3B1C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3B58);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3B94);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3C34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3C90);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3CCC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3D3C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3DE8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3E20);

void func_800B3E40(struct VisualObj* arg0)
{
    D_8010A694[arg0->base.state](arg0);
}

void func_800B3E7C(struct VisualObj* arg0)
{
    D_8010A6A0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3EB8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B3FD4);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B41AC);

void func_800B41CC(struct VisualObj* arg0)
{
    D_8010A6AC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4208);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4274);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4450);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4480);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4558);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4578);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4598);

void func_800B4610(struct VisualObj* arg0)
{
    D_8010A6C8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B464C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B46C8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B46E8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4754);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4790);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4808);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4858);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4894);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B490C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4960);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B499C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4A18);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4A6C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4AA8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4B0C);

void func_800B4B64(struct VisualObj* arg0)
{
    D_8010A704[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4BA0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4CC8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4D00);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4E14);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B4E34);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B518C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B51E0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B522C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B5280);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B52D8);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B5348);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B5448);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B54B0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B54EC);

void func_800B5534(struct VisualObj* arg0)
{
    D_8010A784[arg0->base.state](arg0);
}

void func_800B5570(struct VisualObj* arg0)
{
    D_8010A790[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B55AC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B56D4);

void func_800B56F4(struct EffectObj* arg0)
{
    D_8010A798[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B5730);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B5798);

void func_800B58A0(struct EffectObj* arg0)
{
    D_8010AFAC[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B58DC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B58F4);

// scaling X animation in logo graphics
void TitleScalingXUpdate(struct EffectObj* arg0)
{
    g_TitleScalingXUpdateFuncs[arg0->state]();
}

// g_TitleScalingXUpdateFuncs state 0
void func_800B599C(struct EffectObj* arg0)
{
    u16 color;
    struct Unk14* temp_v0;
    struct EffectObj* current;
    u8 i;

    if (arg0->unk2 != -1) {
        temp_v0 = D_8010B1F8[arg0->unk2];
        arg0->unk14 = temp_v0;
        arg0->unk18.one.a = temp_v0->unk2;
        for (i = 0; i < 4; i++) {
            D_8013E188[i] = D_8010B23C[arg0->unk2][i];
        }
        D_80175E9C = arg0->unk14->unk3 & 1;
        D_80141BE4 = arg0->unk14->unk3 & 2;
        D_8013E1BC = arg0->unk14->unk3 & 4;
        color = arg0->unk14->unk0;
        D_80175EA0 = color & 0x1F;
        D_80141BE6 = color & 0x3E0;
        D_8013E1BE = color & 0x7C00;
        arg0->state++;
        return;
    }
    D_8013E1BE = 0;
    D_80141BE6 = 0;
    D_80175EA0 = 0;
    D_8013E1BC = 0;
    D_80141BE4 = 0;
    D_80175E9C = 0;

    for (current = &effect_objects[0]; current < &effect_objects[0x20]; current++) {
        if (current->unk2 == 2 && current != arg0) {
            func_8002B0C8(current);
        }
    }
    func_8002B0C8(arg0);
}

// g_TitleScalingXUpdateFuncs state 1
void func_800B5B54(struct EffectObj* arg0)
{
    u16 color;
    if (arg0->unk18.one.a-- == 0) {
        arg0->unk14++;
        if (arg0->unk14->unk0 == 0x8000) {
            if (arg0->unk14->unk3 == 1) {
                func_8002B0C8(arg0);
                return;
            }
            arg0->unk14 = &arg0->unk14[arg0->unk14->unk2];
        }
        color = arg0->unk14->unk0;
        arg0->unk18.one.a = arg0->unk14->unk2;
        D_80175EA0 = color & 0x1F;
        D_80141BE6 = color & 0x3E0;
        D_8013E1BE = color & 0x7C00;
        D_80175E9C = arg0->unk14->unk3 & 1;
        D_80141BE4 = arg0->unk14->unk3 & 2;
        D_8013E1BC = arg0->unk14->unk3 & 4;
        need_palette_load |= 5;
    }
}

void func_800B5C60(struct EffectObj* arg0)
{
    s32* var_a1;
    s32* var_a2;
    u32 var_v1;

    var_a2 = arg0->unk14;
    var_a1 = arg0->unk18.ptr;

    for (var_v1 = 0; var_v1 < arg0->unk20 * 8; var_v1++) {
        *var_a1++ = *var_a2++;
    }

    need_palette_load |= 1;
}

void func_800B5CC4(struct EffectObj* arg0)
{
    if (arg0->state == 0) {
        func_800B5D04(arg0);
        return;
    }
    func_800B5E2C(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B5D04);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B5E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B5EB0);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B5EEC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B6060);

void func_800B6080(struct EffectObj* arg0)
{
    D_8010B444[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B60BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B649C);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B64BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B6660);

void func_800B6A0C(struct EffectObj* arg0)
{
    D_8010B45C[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B6A48);

INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_800B6A90);
