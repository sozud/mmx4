#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", ResetGraph);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetGraphReverse);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetGraphDebug);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetGraphQueue);

extern u8 D_8011E188;

u8 GetGraphType(void)
{
    return D_8011E188;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", GetGraphDebug);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", DrawSyncCallback);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetDispMask);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", DrawSync);

typedef struct {
    u_long unk_00[2];
    s32 (*addque2)();
    void* clr;
    u_long unk_10[2];
    void (*cwc)();
    u_long unk_1C;
    void* dws;
    u_long unk_24[2];
    s32 (*otc)(u_long*, s32);
} GpuApi;

extern GpuApi* D_8011E180;

extern void (*D_8011E184)(const char*, ...);

extern u8 D_8011E18A;

extern s16 D_8011E18C;

extern s16 D_8011E18E;

void checkRECT(const char* log, RECT* r)
{
    switch (D_8011E18A) {
    case 1:
        if (r->w > D_8011E18C || r->w + r->x > D_8011E18C || r->y > D_8011E18E || r->y + r->h > D_8011E18E || r->w <= 0 || r->x < 0 || r->y < 0 || r->h <= 0) {
            D_8011E184("%s:bad RECT", log);
            D_8011E184("(%d,%d)-(%d,%d)\n", r->x, r->y, r->w, r->h);
        }
        break;
    case 2:
        D_8011E184("%s:", log);
        D_8011E184("(%d,%d)-(%d,%d)\n", r->x, r->y, r->w, r->h);
        break;
    }
}

extern const char D_80011E6C;

s32 ClearImage(RECT* rect, u_char r, u_char g, u_char b)
{
    checkRECT(&D_80011E6C, rect);
    return D_8011E180->addque2(
        D_8011E180->clr, rect, 8,
        (((b & 0xFF) << 0x10) | ((g & 0xFF) << 8) | (r & 0xFF)));
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", ClearImage2);

INCLUDE_RODATA("main/nonmatchings/psxsdk/libgpu/sys", D_80011E6C);

#ifdef VERSION_JP
int LoadImage(RECT* rect, u_long* p)
{
    checkRECT("LoadImage", rect);
    return D_8011E180->addque2(D_8011E180->dws, rect, 8, p);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", StoreImage);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", MoveImage);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", ClearOTag);

const char D_80011EB4[] __attribute__((section(".rodata"), aligned(4))) = "ClearOTagR(%08x,%d)...\n";

extern u8 D_8011E18A;
extern u32 D_8011E244;

u_long* ClearOTagR(u_long* ot, int n)
{
    if (D_8011E18A >= 2) {
        D_8011E184(D_80011EB4, ot, n);
    }

    D_8011E180->otc(ot, n);
    *ot = (s32)&D_8011E244 & 0xFFFFFF;
    return ot;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", DrawPrim);

extern u8 D_8011E18A;

void DrawOTag(u_long* p)
{
    if (D_8011E18A >= 2) {
        D_8011E184("DrawOTag(%08x)...\n", p);
    }
    D_8011E180->addque2(D_8011E180->cwc, p, 0, 0);
}

extern u8 D_8011E18A;
extern int SetDrawEnv2(DR_ENV*, DRAWENV*);

DRAWENV* PutDrawEnv(DRAWENV* env)
{
    typedef struct {
        unsigned int addr : 24;
        unsigned int len : 8;
    } PUTDRAWENV_TAG;
    typedef struct {
        s32 words[23];
    } PUTDRAWENV_COPY;

    GpuApi* queue;
    void* dr_env;
    u8* debug;

    debug = &D_8011E18A;
    if (*debug >= 2) {
        D_8011E184("PutDrawEnv(%08x)...\n", env);
    }

    dr_env = (u8*)env + 0x1C;
    SetDrawEnv2(dr_env, env);
    ((PUTDRAWENV_TAG*)dr_env)->addr = 0xFFFFFF;

    queue = D_8011E180;
    queue->addque2(queue->cwc, dr_env, 0x40, 0);
    *(PUTDRAWENV_COPY*)(debug + 0xE) = *(PUTDRAWENV_COPY*)env;

    return env;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", DrawOTagEnv);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", GetDrawEnv);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", PutDispEnv);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", GetDispEnv);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", GetODE);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetTexWindow);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetDrawArea);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetDrawOffset);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetPriority);

void SetDrawMode(DR_MODE* p, s32 dfe, s32 dtd, s32 tpage, RECT* tw)
{
    setlen(p, 2);
    p->code[0] = get_mode(dfe, dtd, tpage & 0xFFFF);
    p->code[1] = get_tw(tw);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetDrawEnv);

#define CLAMP(a, b, c) (a >= b ? (a > c ? c : a) : b)
#define LOW(x) (*(s32*)&(x))

extern s16 D_8011E18C;
extern s16 D_8011E18E;

int SetDrawEnv2(DR_ENV* dr_env, DRAWENV* env)
{
    DR_ENV* dr;
    RECT rect;
    s32 len = 0;

    dr = dr_env;
    dr->code[0] = get_cs(env->clip.x, env->clip.y);
    dr->code[1] = get_ce(
        (s32)(((u32)(u16)(env->clip).w + (u32)(u16)(env->clip).x + -1) * 0x10000) >> 0x10,
        (s32)(((u32)(u16)(env->clip).y + (u32)(u16)(env->clip).h + -1) * 0x10000) >> 0x10);
    dr->code[2] = get_ofs(env->ofs[0], env->ofs[1]);
    dr->code[3] = get_mode(env->dfe, env->dtd, env->tpage);
    dr->code[4] = get_tw(&env->tw);
    dr->code[5] = 0xE6000000;
    len = 7;
    if (env->isbg) {
        rect.x = env->clip.x;
        rect.y = env->clip.y;
        rect.w = env->clip.w;
        rect.h = env->clip.h;
        rect.w = CLAMP(rect.w, 0, D_8011E18C - 1);
        rect.h = CLAMP(rect.h, 0, D_8011E18E - 1);
        if (rect.x & 0x3F || rect.w & 0x3F) {
            rect.x -= env->ofs[0];
            rect.y -= env->ofs[1];
            (&dr->tag)[len++] = 0x60000000 | (env->b0 << 16) | (env->g0 << 8) | env->r0;
            (&dr->tag)[len++] = LOW(rect.x);
            (&dr->tag)[len++] = LOW(rect.w);
            rect.x += env->ofs[0];
            rect.y += env->ofs[1];
        } else {
            (&dr->tag)[len++] = 0x02000000 | (env->b0 << 16) | (env->g0 << 8) | env->r0;
            (&dr->tag)[len++] = LOW(rect.x);
            (&dr->tag)[len++] = LOW(rect.w);
        }
    }
    setlen(dr, len - 1);
    return;
}
#else
INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", LoadImage);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", StoreImage);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", MoveImage);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", ClearOTag);

const char D_80011EB4[] = "ClearOTagR(%08x,%d)...\n";

extern u8 D_8011E18A;
extern u32 D_8011E244;

u_long* ClearOTagR(u_long* ot, int n)
{
    if (D_8011E18A >= 2) {
        D_8011E184(D_80011EB4, ot, n);
    }

    D_8011E180->otc(ot, n);
    *ot = (s32)&D_8011E244 & 0xFFFFFF;
    return ot;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", DrawPrim);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", DrawOTag);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", PutDrawEnv);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", DrawOTagEnv);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", GetDrawEnv);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", PutDispEnv);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", GetDispEnv);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", GetODE);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetTexWindow);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetDrawArea);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetDrawOffset);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetPriority);

void SetDrawMode(DR_MODE* p, s32 dfe, s32 dtd, s32 tpage, RECT* tw)
{
    setlen(p, 2);
    p->code[0] = get_mode(dfe, dtd, tpage & 0xFFFF);
    p->code[1] = get_tw(tw);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", SetDrawEnv);

#define CLAMP(a, b, c) (a >= b ? (a > c ? c : a) : b)
#define LOW(x) (*(s32*)&(x))

extern s16 D_8011E18C;
extern s16 D_8011E18E;

int SetDrawEnv2(DR_ENV* dr_env, DRAWENV* env)
{
    DR_ENV* dr;
    RECT rect;
    s32 len = 0;

    dr = dr_env;
    dr->code[0] = get_cs(env->clip.x, env->clip.y);
    dr->code[1] = get_ce(
        (s32)(((u32)(u16)(env->clip).w + (u32)(u16)(env->clip).x + -1) * 0x10000) >> 0x10,
        (s32)(((u32)(u16)(env->clip).y + (u32)(u16)(env->clip).h + -1) * 0x10000) >> 0x10);
    dr->code[2] = get_ofs(env->ofs[0], env->ofs[1]);
    dr->code[3] = get_mode(env->dfe, env->dtd, env->tpage);
    dr->code[4] = get_tw(&env->tw);
    dr->code[5] = 0xE6000000;
    len = 7;
    if (env->isbg) {
        rect.x = env->clip.x;
        rect.y = env->clip.y;
        rect.w = env->clip.w;
        rect.h = env->clip.h;
        rect.w = CLAMP(rect.w, 0, D_8011E18C - 1);
        rect.h = CLAMP(rect.h, 0, D_8011E18E - 1);
        if (rect.x & 0x3F || rect.w & 0x3F) {
            rect.x -= env->ofs[0];
            rect.y -= env->ofs[1];
            (&dr->tag)[len++] = 0x60000000 | (env->b0 << 16) | (env->g0 << 8) | env->r0;
            (&dr->tag)[len++] = LOW(rect.x);
            (&dr->tag)[len++] = LOW(rect.w);
            rect.x += env->ofs[0];
            rect.y += env->ofs[1];
        } else {
            (&dr->tag)[len++] = 0x02000000 | (env->b0 << 16) | (env->g0 << 8) | env->r0;
            (&dr->tag)[len++] = LOW(rect.x);
            (&dr->tag)[len++] = LOW(rect.w);
        }
    }
    setlen(dr, len - 1);
    return;
}
#endif

extern u8 D_8011E188;

s32 get_mode(s32 dfe, s32 dtd, s32 tpage)
{
    u8 version;

    version = D_8011E188;
    if (version == 1 || version == 2) {
        return 0xE1000000 | (dtd ? 0x800 : 0) | (dfe ? 0x1000 : 0) | (tpage & 0x27FF);
    } else {
        return 0xE1000000 | (dtd ? 0x200 : 0) | (dfe ? 0x400 : 0) | (tpage & 0x9FF);
    }
}

extern u8 D_8011E188;

extern s16 D_8011E18C;

extern s16 D_8011E18E;

s32 get_cs(s16 x, s16 y)
{
    x = x >= 0 ? (x > D_8011E18C - 1 ? D_8011E18C - 1 : x) : 0;
    y = y >= 0 ? (y > D_8011E18E - 1 ? D_8011E18E - 1 : y) : 0;
    if (D_8011E188 - 1 <= 1U) {
        return 0xE3000000 | ((y & 0xFFF) << 12) | (x & 0xFFF);
    } else {
        return 0xE3000000 | ((y & 0x3FF) << 10) | (x & 0x3FF);
    }
}

#define CLAMP(a, b, c) (a >= b ? (a > c ? c : a) : b)

s32 get_ce(s16 x, s16 y)
{
    x = CLAMP(x, 0, D_8011E18C - 1);
    y = CLAMP(y, 0, D_8011E18E - 1);

    if ((u32)(D_8011E188 - 1) < 2U) {
        return 0xE4000000 | ((y & 0xFFF) << 12) | (x & 0xFFF);
    } else {
        return 0xE4000000 | ((y & 0x3FF) << 10) | (x & 0x3FF);
    }
}

extern u8 D_8011E188;

u32 get_ofs(s32 arg0, u16 arg1)
{
    if ((u32)(D_8011E188 - 1) < 2U) {
        return 0xe5000000 | ((arg1 & 0xfff) << 0xC) | (arg0 & 0xfff);
    }
    return 0xe5000000 | ((arg1 & 0x7ff) << 0xB) | (arg0 & 0x7ff);
}

u32 get_tw(RECT* arg0)
{
    u32 pad[4];

    if (arg0 != 0) {
        pad[0] = (u8)arg0->x >> 3;
        pad[2] = (s32)(-arg0->w & 0xFF) >> 3;
        pad[1] = (u8)arg0->y >> 3;
        pad[3] = (s32)(-arg0->h & 0xFF) >> 3;
        return (pad[1] << 0xF) | 0xE2000000 | ((pad[0] << 0xA)) | (pad[3] << 5) | pad[2];
    }
    return 0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", get_dx);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _status);

extern volatile s32* D_8011E26C;

extern s32* D_8011E270;

extern volatile s32* D_8011E274;

extern volatile s32* D_8011E278;

#define OT_TYPE u_long

s32 _otc(OT_TYPE arg0, s32 arg1)
{
    s32 temp;

    *D_8011E278 |= 0x08000000;
    *D_8011E274 = 0;
    temp = arg0 - 4 + arg1 * 4;
    *D_8011E26C = temp;
    *D_8011E270 = arg1;
    *D_8011E274 = 0x11000002;
    set_alarm();
    if (*D_8011E274 & 0x01000000) {
        while (1) {
            if (get_alarm()) {
                return -1;
            } else {
                if (!(*D_8011E274 & 0x01000000)) {
                    break;
                }
            }
        }
    }
    return arg1;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _clr);

extern s16 D_8011E18C;

extern s16 D_8011E18E;

extern s32* D_8011E258;

extern volatile u32* D_8011E25C;

extern volatile u32* D_8011E260;

extern volatile u32* D_8011E264;

extern volatile u32* D_8011E268;

#define CLAMP(a, b, c) (a >= b ? (a > c ? c : a) : b)

#define D_80090CA0 D_8011E18C

#define D_80090CA2 D_8011E18E

#define GPU_STATUS D_8011E25C

#define GPU_DATA ((volatile u32*)D_8011E258)

#define DMA1_MADR ((s32**)D_8011E260)

#define DMA1_BCR D_8011E264

#define DMA1_CHCR D_8011E268

s32 _dws(RECT* arg0, s32* arg1)
{
    s32 temp_a0;
    s32 size;
    s32 var_s0;
    s32* img_ptr;
    s32 var_s4;

    img_ptr = arg1;
    set_alarm();
    var_s4 = 0;

    arg0->w = CLAMP(arg0->w, 0, D_80090CA0);
    arg0->h = CLAMP(arg0->h, 0, D_80090CA2);

    temp_a0 = ((arg0->w * arg0->h) + 1) / 2;
    if (temp_a0 <= 0) {
        return -1;
    }

    var_s0 = temp_a0 % 16;
    size = temp_a0 / 16;
    if (!(*GPU_STATUS & 0x04000000)) {
        while (1) {
            if (get_alarm()) {
                return -1;
            } else if (*GPU_STATUS & 0x04000000) {
                break;
            }
        }
    }

    *GPU_STATUS = 0x04000000;
    *GPU_DATA = 0x01000000;
    *GPU_DATA = var_s4 ? 0xB0000000 : 0xA0000000;
    *GPU_DATA = *(s32*)(&arg0->x);
    *GPU_DATA = *(s32*)(&arg0->w);

    for (var_s0 = var_s0 - 1; var_s0 != -1; var_s0--) {
        *GPU_DATA = *img_ptr++;
    }

    if (size != 0) {
        *GPU_STATUS = 0x04000002;
        *DMA1_MADR = img_ptr;
        *DMA1_BCR = (size << 0x10) | 0x10;
        *DMA1_CHCR = 0x01000201;
    }

    return 0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _drs);

extern volatile u32* D_8011E25C;

extern s8 D_8013BAF4[];

void _ctl(u32 arg0)
{
    *D_8011E25C = arg0;
    D_8013BAF4[arg0 >> 0x18] = (s8)arg0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _getctl);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _cwb);

extern volatile u32* D_8011E260;

extern volatile u32* D_8011E264;

extern volatile u32* D_8011E268;

void _cwc(s32 arg0)
{
    *D_8011E25C = 0x04000002;
    *D_8011E260 = arg0;
    *D_8011E264 = 0;
    *D_8011E268 = 0x01000401;
}

extern volatile u32* D_8011E25C;

extern s32* D_8011E258;

s32 _param(s32 arg0)
{
    *D_8011E25C = arg0 | 0x10000000;
    return *D_8011E258 & 0xFFFFFF;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _addque);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _addque2);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _exeque);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _reset);

extern void _exeque(void);

extern s32 D_8011E28C;

extern s32 D_8011E290;

s32 _sync(s32 arg0)
{
    s32 temp_s0;

    if (!arg0) {
        set_alarm();
        while (D_8011E28C != D_8011E290) {
            _exeque();
            if (get_alarm())
                return -1;
        }

        while ((*D_8011E268 & 0x01000000) || !(*D_8011E25C & 0x04000000)) {
            if (get_alarm())
                return -1;
        }

        return 0;
    }

    temp_s0 = (D_8011E28C - D_8011E290) & 0x3F;
    if (temp_s0) {
        _exeque();
    }

    if ((*D_8011E268 & 0x01000000) || !(*D_8011E25C & 0x04000000)) {
        if (!temp_s0) {
            return 1;
        } else {
            return temp_s0;
        }
    }

    return temp_s0;
}

extern s32 D_8011E2A0;

extern s32 D_8011E2A4;

void set_alarm(void)
{
    D_8011E2A0 = VSync(-1) + 0xF0;
    D_8011E2A4 = 0;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", get_alarm);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/sys", _version);

void memset2(s8* dst, s8 value, s32 count)
{
    s8 scratch[8];
    s32 index;
    s8* ptr;

    ptr = dst;
    index = count - 1;
    if (count != 0) {
        do {
            *ptr = value;
            index -= 1;
            ptr += 1;
        } while (index != -1);
    }
}
