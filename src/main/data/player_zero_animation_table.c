#include "common.h"

extern u32 D_8011A248[];
extern u32 D_8011A250[];
extern u32 D_8011A288[];
extern u32 D_8011A2B4[];
extern u32 D_8011A2BC[];
extern u32 D_8011A2DC[];
extern u32 D_8011A2F8[];
extern u32 D_8011A328[];
extern u32 D_8011A350[];
extern u32 D_8011A35C[];
extern u32 D_8011A394[];
extern u32 D_8011A3A0[];
extern u32 D_8011A3E0[];
extern u32 D_8011A3F4[];
extern u32 D_8011A418[];
extern u32 D_8011A424[];
extern u32 D_8011A434[];
extern u32 D_8011A448[];
extern u32 D_8011A454[];
extern u32 D_8011A480[];
extern u32 D_8011A494[];
extern u32 D_8011A4B8[];
extern u32 D_8011A4C4[];
extern u32 D_8011A4E8[];
extern u32 D_8011A4F8[];
extern u32 D_8011A50C[];
extern u32 D_8011A51C[];
extern u32 D_8011A524[];
extern u32 D_8011A54C[];
extern u32 D_8011A574[];
extern u32 D_8011A584[];
extern u32 D_8011A5D4[];
extern u32 D_8011A5D8[];
extern u32 D_8011A5FC[];
extern u32 D_8011A60C[];
extern u32 D_8011A62C[];
extern u32 D_8011A630[];
extern u32 D_8011A634[];
extern u32 D_8011A644[];
extern u32 D_8011A648[];
extern u32 D_8011A64C[];
extern u32 D_8011A650[];
extern u32 D_8011A670[];
extern u32 D_8011A6B0[];
extern u32 D_8011A6EC[];
extern u32 D_8011A6F4[];
extern u32 D_8011A700[];
extern u32 D_8011A70C[];
extern u32 D_8011A718[];
extern u32 D_8011A724[];
extern u32 D_8011A740[];
extern u32 D_8011A744[];
extern u32 D_8011A748[];
extern u32 D_8011A754[];
extern u32 D_8011A758[];
extern u32 D_8011A768[];
extern u32 D_8011A790[];
extern u32 D_8011A7A0[];
extern u32 D_8011A7C8[];
extern u32 D_8011A7D8[];
extern u32 D_8011A800[];
extern u32 D_8011A81C[];
extern u32 D_8011A83C[];
extern u32 D_8011A854[];
extern u32 D_8011A860[];
extern u32 D_8011A870[];
extern u32 D_8011A878[];
extern u32 D_8011A880[];
extern u32 D_8011A888[];
extern u32 D_8011A890[];
extern u32 D_8011A898[];
extern u32 D_8011A8E0[];
extern u32 D_8011A924[];
extern u32 D_8011A970[];
extern u32 D_8011A998[];
extern u32 D_8011A9C8[];
extern u32 D_8011A9FC[];
extern u32 D_8011AA24[];
extern u32 D_8011AA48[];
extern u32 D_8011AA70[];
extern u32 D_8011AA94[];
extern u32 D_8011AACC[];
extern u32 D_8011AAEC[];
extern u32 D_8011AB1C[];
extern u32 D_8011AB38[];
extern u32 D_8011ABEC[];
extern u32 D_8011AC7C[];
extern u32 D_8011AD00[];
extern u32 D_8011AD6C[];
extern u32 D_8011AD94[];
extern u32 D_8011ADC0[];
extern u32 D_8011ADD4[];
extern u32 D_8011ADDC[];
extern u32 D_8011AE08[];
extern u32 D_8011AE2C[];
extern u32 D_8011AE5C[];
extern u32 D_8011AE6C[];
extern u32 D_8011AE84[];
extern u32 D_8011AE90[];
extern u32 D_8011AEF8[];
extern u32 D_8011AF38[];

const u32* D_8011AFF0[144] = {
    D_8011A2F8,
    D_8011A248,
    D_8011A250,
    D_8011A288,
    D_8011A2B4,
    D_8011A2F8,
    D_8011A328,
    D_8011A350,
    D_8011A35C,
    D_8011A394,
    D_8011A3E0,
    D_8011A3F4,
    D_8011A418,
    D_8011A424,
    D_8011A434,
    D_8011A448,
    D_8011A454,
    D_8011A480,
    D_8011A494,
    D_8011A4B8,
    D_8011A4C4,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A4E8,
    D_8011A4F8,
    D_8011A50C,
    D_8011A51C,
    D_8011A524,
    D_8011A54C,
    D_8011A574,
    D_8011A584,
    D_8011A2F8,
    D_8011A5D4,
    D_8011A5D8,
    D_8011A3A0,
    D_8011A2BC,
    D_8011A2DC,
    D_8011A5FC,
    D_8011A60C,
    D_8011A62C,
    D_8011A630,
    D_8011A634,
    D_8011A644,
    D_8011A648,
    D_8011A64C,
    D_8011A650,
    D_8011A670,
    D_8011A6B0,
    D_8011A6EC,
    D_8011A6F4,
    D_8011A700,
    D_8011A70C,
    D_8011A718,
    D_8011A724,
    D_8011A740,
    D_8011A740,
    D_8011A744,
    D_8011A740,
    D_8011A740,
    D_8011A748,
    D_8011A754,
    D_8011A758,
    D_8011A768,
    D_8011A790,
    D_8011A7A0,
    D_8011A7C8,
    D_8011A7D8,
    D_8011A800,
    D_8011A81C,
    D_8011A83C,
    D_8011A854,
    D_8011A860,
    D_8011A870,
    D_8011A878,
    D_8011A880,
    D_8011A888,
    D_8011A890,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A898,
    D_8011A8E0,
    D_8011A924,
    D_8011A9FC,
    D_8011AA48,
    D_8011AA94,
    D_8011AAEC,
    D_8011AB38,
    D_8011ABEC,
    D_8011AD6C,
    D_8011AD94,
    D_8011ADD4,
    D_8011ADDC,
    D_8011AE2C,
    D_8011AE5C,
    D_8011AE90,
    D_8011AEF8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A970,
    D_8011A998,
    D_8011A9C8,
    D_8011AA24,
    D_8011AA70,
    D_8011AACC,
    D_8011AB1C,
    D_8011AC7C,
    D_8011AD00,
    D_8011ADC0,
    D_8011AE08,
    D_8011AE6C,
    D_8011AE84,
    D_8011AF38,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
    D_8011A2F8,
};
