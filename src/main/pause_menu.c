// BarObj, bar_object
// 8002FCAC..800311EC
#include "common.h"

void func_800170E0(void);
void func_800170B0(void);
extern u8 D_8013B818[0x10];
void func_80021104(struct EngineObj* arg0);
void func_80023D90(void);

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
    stop_sound(0xFF, 0);
    func_800129F0(8);
    func_80023D68();
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
        func_80023D68();
        return;
    }
    func_800170B0();
    func_800129A4(8);
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
    if (engine_obj.unk5A & 0x3000) {
        if (engine_obj.unk5A & 0x1000) {
            self->options.fields.unk20 = 1;
            engine_obj.unk5C[0] |= 0x80;
        }
        if (engine_obj.unk5A & 0x2000) {
            self->options.fields.unk21 = 1;
            engine_obj.unk5C[1] |= 0x80;
        }
    } else {
        self->options.fields.unk20 = 0;
        self->options.fields.unk21 = 0;
    }
    if (engine_obj.unk5A & 0x4000) {
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
    if (engine_obj.unk5A & 0x8000) {
        self->options.fields.unk25 = 1;
    } else {
        self->options.fields.unk25 = 0;
    }
    current_weapon = g_Player.weapon;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk30 = 0;
    D_8013B818[0] = current_weapon;
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
    }
    func_80023D90();
}

void func_80030128(struct BarObj* arg0)
{
    if (controller_input.pressed & PADselect) {
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

void func_800301BC(struct BarObj* arg0)
{
    s16 var_a1;
    u16 var_a1_2;
    s8 var_a2;
    s8 initial_unk14;

    var_a1 = 0;
    initial_unk14 = arg0->unk14;
    switch (controller_input.pressed) {
    case PADstart:
        arg0->state = 2;
        arg0->unk5 = 0;
        break;
    case PAD_CONFIRM:
        if (arg0->unk14 < 0xAU) {
            if (arg0->unk14 < 2) {
                g_Player.weapon = 0;
            } else {
                g_Player.weapon = arg0->unk14 - 1;
            }
        }
        func_8001540C(0, 0x22, 0);
        break;
    case PADLup:
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
    case PADLdown:
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
    case PADLright:
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
    case PADLleft:
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
        func_8001540C(0, 0xC, 0);
    }
}

INCLUDE_ASM("main/nonmatchings/pause_menu", func_800304E4);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80030728);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80030A2C);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80030C54);

void func_80030DF8(struct BarObj* arg0)
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
        func_8002A41C((struct GameInfo*)arg0);
        return;
    case 3:
        func_800129A4(8);
        arg0->unk6++;
        func_80023D90();
        return;
    case 4:
        if (main_bss_state.transition.active == 0) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            return;
        }
        func_80023D90();
        return;
    }
}

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
    if (main_bss_state.transition.active != 0) {
        func_80023D90();
    } else {
        func_800170E0();
        arg0->unk5 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80031064);

void func_80031130(struct BarObj* arg0)
{
    if (main_bss_state.transition.active == 0) {
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
