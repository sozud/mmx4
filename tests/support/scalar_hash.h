#include "test_runtime.h"
static u32 hash_bytes(u32 hash, const void* data, u32 size)
{
    const u8* bytes = data;
    while (size--)
        hash = hash * 31 + *bytes++;
    return hash;
}
#define HASH_SPAN(hash, object, first, last) \
    hash_bytes(hash, &(object)->first, (u32)((u8*)&(object)->last - (u8*)&(object)->first) + sizeof((object)->last))
static u32 hash_animated(u32 hash, const struct AnimatedObj* object)
{
    hash = hash_bytes(hash, object, 8);
    hash = hash * 31 + object->x_pos.val;
    hash = hash * 31 + object->y_pos.val;
    hash = HASH_SPAN(hash, object, bg_offset, unk2C);
    hash = hash * 31 + object->unk40;
    hash = hash * 31 + object->unk42;
    return hash * 31 + object->animation_step.packed;
}
static u32 hash_visuals(u32 hash, const void* owner)
{
    u32 i;
    for (i = 0; i < COUNT(visual_objects); i++) {
        const struct VisualObj* visual = &visual_objects[i];
        if (!visual->active)
            continue;
        hash = hash * 31 + i;
        hash = hash_bytes(hash, visual, 8);
        hash = hash * 31 + visual->x_pos.val;
        hash = hash * 31 + visual->y_pos.val;
        hash = hash * 31 + visual->unk42;
        hash = hash * 31 + visual->unk15 + (visual->unk16 << 8);
        hash = hash * 31 + ((const void*)visual->unk50 == owner);
    }
    return hash;
}
