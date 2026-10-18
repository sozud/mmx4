#include "test_runtime.h"
#include "main/weapons/weapon_58_ice_block_hitbox.h"
extern u8 ice_block_hitbox_box_0[4], ice_block_hitbox_box_1[4], ice_block_hitbox_box_2[4];

static u32 initialize_variant(s8 variant)
{
    struct PlayerObj owner;
    struct WeaponObj weapon;
    struct Unk_unk68 prior_box;
    memset(&owner, 0, sizeof(owner));
    memset(&weapon, 0, sizeof(weapon));
    memset(&prior_box, 0, sizeof(prior_box));
    owner.x_pos.val = 0x12345678;
    owner.y_pos.val = -0x102030;
    weapon.owner = &owner;
    weapon.unk2 = variant;
    weapon.unk54 = &owner;
    weapon.unk68 = &prior_box;
    func_800989CC(&weapon);
    assert(weapon.owner == &owner);
    assert(weapon.unk54 == NULL && weapon.unk68 == NULL);
    assert(weapon.state == 1 && weapon.unk5 == 12);
    assert(weapon.unk5C == 1 && weapon.unk60 == 3);
    assert(weapon.x_pos.val == owner.x_pos.val && weapon.y_pos.val == owner.y_pos.val);
    assert(owner.x_pos.val == 0x12345678 && owner.y_pos.val == -0x102030);
    if (weapon.unk50 == NULL)
        return 0;
    if (weapon.unk50 == ice_block_hitbox_box_0)
        return 1;
    if (weapon.unk50 == ice_block_hitbox_box_1)
        return 2;
    if (weapon.unk50 == ice_block_hitbox_box_2)
        return 3;
    assert(0);
    return ~0u;
}
#define VARIANT_CASE(name, variant)         \
    static u32 name(void)                   \
    {                                       \
        return initialize_variant(variant); \
    }
VARIANT_CASE(zero, 0)
VARIANT_CASE(one, 1)
VARIANT_CASE(two, 2)
VARIANT_CASE(three, 3)
VARIANT_CASE(outside, 4)
#define ENTRY(name) name,
static const CTestCase ice_hitbox_variants_cases[] = {
    ENTRY(zero)
        ENTRY(one)
            ENTRY(two)
                ENTRY(three)
                    ENTRY(outside)
};
static const u32 ice_hitbox_variants_cases_expected[] = { 0x1u, 0x3u, 0x2u, 0x0u, 0x1u };
#undef VARIANT_CASE
#undef ENTRY

const struct CTestGroup c_test_groups[] = {
    { "ice_hitbox_variants", ice_hitbox_variants_cases, ice_hitbox_variants_cases_expected, COUNT(ice_hitbox_variants_cases), 0 },
};
const u32 c_test_group_count = COUNT(c_test_groups);
const u32 c_test_count = COUNT(ice_hitbox_variants_cases);
