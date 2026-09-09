#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr_dma", startIntrDMA);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr_dma", trapIntrDMA);

typedef void (*Callback)();
extern volatile s32* D_8011DC58;

#define DMA_CALLBACKS ((Callback*)(&D_8011DC58 + 1))

Callback setIntrDMA(int index, Callback callback)
{
    Callback prev = DMA_CALLBACKS[index];
    if (callback != prev) {
        if (callback != 0) {
            DMA_CALLBACKS[index] = callback;
            *D_8011DC58 = (*D_8011DC58 & 0xFFFFFF) | 0x800000 | (1 << (index + 0x10));
        } else {
            DMA_CALLBACKS[index] = 0;
            *D_8011DC58 = ((*D_8011DC58 & 0xFFFFFF) | 0x800000) & ~(1 << (index + 0x10));
        }
    }
    return prev;
}

void memclr3(int* ptr, int size)
{
    int i;
    int* e = ptr;

    for (i = size - 1; i != -1; i--) {
        *e = 0;
        e++;
    }
}
