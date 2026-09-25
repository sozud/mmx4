// 8001C6DC..8001D064
#include "common.h"

INCLUDE_RODATA("main/nonmatchings/memcard", D_80010094);

INCLUDE_RODATA("main/nonmatchings/memcard", D_800100A8);

#ifdef MMX4_PC
const struct MemcardPath D_800100C0 = { "bu00:" };
#else
INCLUDE_RODATA("main/nonmatchings/memcard", D_800100C0);
#endif

void InitMemcards(void)
{
    EnterCriticalSection();
    D_80139670 = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_80139674 = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80139678 = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    D_8013967C = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    D_80139680 = OpenEvent(HwCARD, EvSpIOE, EvMdNOINTR, NULL);
    D_80139684 = OpenEvent(HwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    D_80139688 = OpenEvent(HwCARD, EvSpERROR, EvMdNOINTR, NULL);
    ExitCriticalSection();
    EnableEvent(D_80139670);
    EnableEvent(D_80139674);
    EnableEvent(D_80139678);
    EnableEvent(D_8013967C);
    EnableEvent(D_80139680);
    EnableEvent(D_80139684);
    EnableEvent(D_80139688);
}

void func_8001C854(void)
{
    TestEvent(D_80139670);
    TestEvent(D_80139674);
    TestEvent(D_80139678);
    TestEvent(D_8013967C);
}

void func_8001C8AC(void)
{
    TestEvent(D_80139680);
    TestEvent(D_80139684);
    TestEvent(D_80139688);
}

INCLUDE_ASM("main/nonmatchings/memcard", func_8001C8F4);

INCLUDE_ASM("main/nonmatchings/memcard", func_8001CB24);

void func_8001CC5C(s32 device_num, struct MemcardFileList* list, const char* pattern)
{
    struct DIRENTRY dir;
    char path[0x20];

    *(struct MemcardPath*)path = D_800100C0;
    memset(path + 6, 0, 0x1A);
    strcpy(path + 5, pattern);
    path[2] += device_num;
    list->count = 0;
    list->total_size = 0;
    if (firstfile(path, &dir) == &dir) {
        do {
            strcpy(list->names[list->count], dir.name);
            list->sizes[list->count] = dir.size;
            list->total_size += dir.size;
            list->count++;
        } while (nextfile(&dir) == &dir);
    }
}

s32 func_8001CD70(s32 arg0)
{
    s32 retries;
    s32 result;

    retries = 3;
    func_8001C854();
    do {
        if (_card_load(arg0 * 0x10) != 0) {
            result = func_8001CEDC();
            if (result == 0) {
                return 0;
            }
        }
        retries--;
    } while (retries != 0);
    return result;
}

int func_8001CDE4(int arg0)
{
    int var_s0;
    int var_s1;
    int var_s2;

    var_s1 = 0x10;
    var_s2 = 0xFF;
    func_8001C854();
    do {
        if (_card_info(arg0 << 4) != 0) {
            var_s0 = func_8001CEDC();
            if ((var_s0 & 1) || (var_s0 != var_s2)) {
                var_s2 = var_s0;
            } else {
                break;
            }
        }
    } while (--var_s1 != 0);

    if (var_s0 == 2) {
        func_8001CFF4(arg0);
        var_s0 = 0;
    }
    return var_s0;
}

s32 func_8001CE84(s32 device_num)
{
    struct MemcardPath buf = D_800100C0;

    buf.path[2] += device_num;
    return format(buf.path) ^ 1;
}

s32 func_8001CEDC(void)
{
    const long MAX_LOOPS = 250000;
    long var_s0;

    for (var_s0 = MAX_LOOPS - 1; var_s0 != 0; var_s0--) {
        if (TestEvent(D_80139670)) {
            return 0;
        }
        if (TestEvent(D_80139674)) {
            return 1;
        }
        if (TestEvent(D_80139678)) {
            return 2;
        }
        if (TestEvent(D_8013967C)) {
            return 3;
        }
    }
    return 3;
}

INCLUDE_ASM("main/nonmatchings/memcard", func_8001CF74);

s32 func_8001CFF4(s32 arg0)
{
    s32 retries;
    s32 result;

    retries = 10;
    result = 2;
    func_8001C8AC();
    do {
        if (_card_clear(arg0 * 0x10) != 0) {
            result = func_8001CF74();
            if (result == 0) {
                break;
            }
        }
        retries--;
    } while (retries != 0);
    return result;
}
