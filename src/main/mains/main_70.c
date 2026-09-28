// MainObj, main_object_update_funcs[70]
// 80088BA0..80089AA4
#include "common.h"
#include "func_tables.h"

extern u8 D_80104A3C[];

void drone_pod_update(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    drone_pod_state_funcs[self->state](self);
}

void drone_pod_intro(struct MainObj* self)
{
    drone_pod_intro_funcs[self->unk5](self);
    func_8002B318(BASE_OBJECT(self), 0x20, 0x20);
}

// drone_pod_init
INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088C40);

void drone_pod_intro_wait_player(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi >= 0x8E9) {
        func_80036AE4(0x14, 0x40);
        func_80015D60(self, 2);
        self->unk5++;
    }
}

void drone_pod_intro_open(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        func_80015D60(self, 0);
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = self;
        self->unk7C = 3;
        self->unk5++;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void drone_pod_intro_fill_health(struct MainObj* self)
{
    s16 timer;
    u8 count;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        func_8001540C(0, 0xE, NULL);
        self->unk7C = 3;
    }
    count = self->unk5C + 1;
    self->unk5C = count;
    if ((s8)count == 0x30) {
        func_80036B18();
        self->unk5 = 3;
        self->unk6 = 0;
        self->unk7C = 0xA;
        self->state++;
    }
}

// drone_pod_run
INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088EA4);

void drone_pod_death(struct MainObj* self)
{
    drone_pod_death_funcs[self->unk5](self);
    if ((self->unk5 < 3) && (self->state != 0)) {
        func_8002B318(BASE_OBJECT(self), 0x20, 0x20);
    }
}

void drone_pod_death_start(struct MainObj* self)
{
    u8 i;

    for (i = 0; i < 4U; i++) {
        D_8013E188[i] = -1;
    }
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
    self->ext.main_70.alarm_color = 0;
    self->ext.main_70.alarm_timer = 0x28;
    self->ext.main_70.flash_timer = 4;
    engine_obj.enable_boss = 0;
    engine_obj.boss_ptr = NULL;
    self->unk7C = 0x28;
    self->unk7E = 5;
    self->unk42 &= ~0x8000;
    engine_obj.character_state.bytes[0] = 1;
    self->unk5++;
}

void drone_pod_death_explode(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0xA0;
        self->unk5++;
        return;
    }
    if (--self->unk7E == 0) {
        func_800AF878(BASE_OBJECT(self), 1, 0x10, 0x10);
        self->unk7E = 5;
    }
}

void drone_pod_death_alarm(struct MainObj* self)
{
    s16 countdown;
    u16 timer;

    if ((D_80141BD8.unk0 & 3) == 0) {
        drone_pod_random_explosion(self);
    }

    countdown = self->unk7E;
    if (countdown == 0) {
        drone_pod_alarm_flash(self);
    } else {
        self->unk7E = countdown - 1;
    }

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if ((timer << 0x10) == 0) {
        self->unk5 = (u8)self->unk5 + 1;
    }
}

void drone_pod_death_break_wall(struct MainObj* self)
{
    func_800C813C(4, &D_801049AC, self);
    background_objects[0].unk1C = 0xA00;
    background_objects[0].unk24 = 0xA00;
    func_800DABE4(0, 0x9E0, 0x350);
    engine_obj.character_state.bytes[0] = 0;
    self->unk7C = 0x5A;
    self->on_screen = 0;
    self->unk7E = 5;
    self->unk5++;
}

void drone_pod_death_debris(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        self->unk5++;
        return;
    }
    if ((D_80141BD8.unk0 & 7) == 0) {
        self->y_pos.i.hi = (get_random() & 0x7F) + 0x360;
        func_800C813C(5, &D_801049B0, self);
    }
    timer = self->unk7E - 1;
    self->unk7E = timer;
    if (timer == 0) {
        func_800AF878(BASE_OBJECT(self), 1, 0x20, 0x20);
        self->unk7E = 5;
    }
}

void drone_pod_death_finish(struct MainObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void drone_pod_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_70.saved_unk5;
}

void drone_pod_rest(struct MainObj* self)
{
    drone_pod_rest_funcs[self->unk6](self);
}

void drone_pod_rest_wait(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_80015D60(self, 1);
        self->unk7C = 0x18;
        self->unk6++;
    }
}

void drone_pod_rest_open(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->collision_data = (const u16*)D_80108104;
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void drone_pod_launch(struct MainObj* self)
{
    drone_pod_launch_funcs[self->unk6](self);
}

void drone_pod_launch_prepare(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    func_80015D60(self, 2);
    self->unk7C = 0x27;
    self->unk6++;
}

void drone_pod_launch_fire(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_80015D60(self, 0xD);
        func_80089588(self);
        self->unk7C = 0x18;
        self->unk6++;
    }
}

void drone_pod_launch_close(struct MainObj* self)
{
    func_80015DC8(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->collision_data = (const u16*)D_801060F0;
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7C = 0x5A;
    }
}

// drone_pod_spawn_drones
INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089588);

void drone_pod_random_explosion(struct MainObj* self)
{
    s16 x = background_objects[0].x_pos.i.hi;
    s16 y = background_objects[0].y_pos.i.hi;
    self->ext.main_70.unk85 = func_8002B780() % 4;
    switch (self->ext.main_70.unk85) {
    case 0:
        break;
    case 1:
        x += 0xA0;
        break;
    case 3:
        x += 0xA0;
        // Fall through.
    case 2:
        y += 0x78;
        break;
    }
    x += func_8002B780() % 0xA0;
    y += func_8002B780() % 0x78;
    func_800AFAB4(0, x, y, 0xFF);
    if ((D_80141BD8.unk0 & 3) == 0) {
        func_8001540C(0, D_80104A3C[(get_random() & 3) * 4], NULL);
    }
}

void drone_pod_alarm_flash(struct MainObj* self)
{
    s16 timer;

    if (self->ext.main_70.alarm_flashing != 0) {
        drone_pod_alarm_funcs[self->ext.main_70.alarm_color](self);
    } else {
        timer = self->ext.main_70.alarm_timer - 1;
        self->ext.main_70.alarm_timer = timer;
        if (timer == 0) {
            self->ext.main_70.alarm_flashing = 1;
        }
    }
}

void drone_pod_alarm_red(struct MainObj* self)
{
    if (--self->ext.main_70.flash_timer == 0) {
        self->ext.main_70.alarm_timer = 0x5A;
        need_palette_load |= 1;
        self->ext.main_70.flash_timer = 4;
        self->ext.main_70.alarm_color ^= 1;
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        self->ext.main_70.alarm_flashing = 0;
    } else {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
    }
}

void drone_pod_alarm_white(struct MainObj* self)
{
    s16 timer;

    timer = self->ext.main_70.flash_timer - 1;
    self->ext.main_70.flash_timer = timer;
    if (timer == 0) {
        self->ext.main_70.alarm_timer = 0x28;
        need_palette_load |= 1;
        self->ext.main_70.flash_timer = 4;
        self->ext.main_70.alarm_color ^= 1;
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        self->ext.main_70.alarm_flashing = 0;
    } else {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
    }
}

struct Unk_unk68 D_80104914 = { -12, -13, 25, 26 };

union AnimationStep D_80104918[] = {
    { 0x00000008 },
};

union AnimationStep D_8010491C[] = {
    { 0x05010008 },
    { 0x06010008 },
    { 0x00000008 },
};

union AnimationStep D_80104928[] = {
    { 0x00010008 },
    { 0x01010007 },
    { 0x02010006 },
    { 0x03010005 },
    { 0x02010006 },
    { 0x01000007 },
};

union AnimationStep D_80104940[] = {
    { 0x04000008 },
};

union AnimationStep D_80104944[] = {
    { 0x07000008 },
};

union AnimationStep D_80104948[] = {
    { 0x08000008 },
};

union AnimationStep D_8010494C[] = {
    { 0x09000008 },
};

union AnimationStep D_80104950[] = {
    { 0x0A000008 },
};

union AnimationStep D_80104954[] = {
    { 0x0B000008 },
};

union AnimationStep D_80104958[] = {
    { 0x0C000008 },
};

union AnimationStep D_8010495C[] = {
    { 0x0D000008 },
};

union AnimationStep D_80104960[] = {
    { 0x0E000008 },
};

union AnimationStep D_80104964[] = {
    { 0x0F000008 },
};

union AnimationStep D_80104968[] = {
    { 0x00010008 },
    { 0x06010008 },
    { 0x05000008 },
};

union AnimationStep* D_80104974[14] = {
    D_80104918,
    D_8010491C,
    D_80104928,
    D_80104940,
    D_80104944,
    D_80104948,
    D_8010494C,
    D_80104950,
    D_80104954,
    D_80104958,
    D_8010495C,
    D_80104960,
    D_80104964,
    D_80104968,
};

struct Unk_unk68 D_801049AC = { 4, 5, 6, 7 };

struct Unk_unk68 D_801049B0[2] = {
    { 8, 9, 10, 11 },
    { 12, 0, 0, 0 },
};

u8 D_801049B8[20] = { 0x03, 0x04, 0x04, 0x05, 0x00, 0x01, 0x03, 0x05, 0x01, 0x02, 0x02, 0x03, 0x01, 0x03, 0x00, 0x02, 0xFF, 0x00, 0x00, 0x00 };

s16 D_801049CC[12] = {
    (s16)0x08F0,
    (s16)0x02E0,
    (s16)0x08A0,
    (s16)0x0370,
    (s16)0x08F0,
    (s16)0x0400,
    (s16)0x09C8,
    (s16)0x02E0,
    (s16)0x0A30,
    (s16)0x0370,
    (s16)0x09C8,
    (s16)0x0400,
};

void (*drone_pod_state_funcs[3])() = {
    drone_pod_intro,
    func_80088EA4,
    drone_pod_death,
};

void (*drone_pod_intro_funcs[4])() = {
    func_80088C40,
    drone_pod_intro_wait_player,
    drone_pod_intro_open,
    drone_pod_intro_fill_health,
};

void (*drone_pod_step_funcs[4])() = {
    func_8009216C,
    drone_pod_resume_step,
    drone_pod_rest,
    drone_pod_launch,
};

void (*drone_pod_death_funcs[6])(struct MainObj*) = {
    drone_pod_death_start,
    drone_pod_death_explode,
    drone_pod_death_alarm,
    drone_pod_death_break_wall,
    drone_pod_death_debris,
    drone_pod_death_finish,
};

void (*drone_pod_rest_funcs[2])() = {
    drone_pod_rest_wait,
    drone_pod_rest_open,
};

void (*drone_pod_launch_funcs[3])() = {
    drone_pod_launch_prepare,
    drone_pod_launch_fire,
    drone_pod_launch_close,
};

u8 D_80104A3C[16] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00 };

void (*drone_pod_alarm_funcs[2])(struct MainObj*) = {
    drone_pod_alarm_red,
    drone_pod_alarm_white,
};
