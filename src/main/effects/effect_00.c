// EffectObj, effect_object_update_funcs[0]
// 800B56F4..800B58A0
#include "common.h"

struct Effect00BackgroundUpdate {
    u16 object_index;
    u16 value;
};

void camera_trigger_update(struct EffectObj* self)
{
    camera_trigger_state_funcs[self->state](self);
}

void camera_trigger_init(struct EffectObj* self)
{
    self->ext.unk_effect.unk14 = 0;
    self->state++;
    self->ext.unk_effect.unk18 = *(camera_trigger_stage_scripts[((engine_obj.stage * 2) + engine_obj.substage)] + self->unk2);
    func_800B5798(self);
}

// camera_trigger_main
INCLUDE_ASM("main/nonmatchings/effects/effect_00", func_800B5798);

void (*camera_trigger_state_funcs[])(struct EffectObj*) = {
    camera_trigger_init,
    func_800B5798,
};

u16 camera_trigger_script_s00_0_0[8] = {
    0x0EFF,
    0x0EF0,
    0x01C0,
    0x0100,
    0x0001,
    0x0002,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s00_0_1[8] = {
    0x0F10,
    0x0F00,
    0x01C0,
    0x0100,
    0x0003,
    0x0001,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s00_0_2[8] = {
    0x10FF,
    0x10F0,
    0x0260,
    0x0180,
    0x0003,
    0x0001,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s00_0_3[6] = {
    0x1110,
    0x1100,
    0x0260,
    0x0180,
    0x0004,
    0x0000,
};

u16 camera_trigger_script_s00_0_4[6] = {
    0x0BD0,
    0x0BC0,
    0x01B0,
    0x0100,
    0x0010,
    0x0000,
};

u16 camera_trigger_script_s00_0_5[6] = {
    0x11C0,
    0x11B0,
    0x0260,
    0x0180,
    0x0024,
    0x0000,
};

u16* camera_trigger_scripts_s00_0[6] = {
    camera_trigger_script_s00_0_0,
    camera_trigger_script_s00_0_1,
    camera_trigger_script_s00_0_2,
    camera_trigger_script_s00_0_3,
    camera_trigger_script_s00_0_4,
    camera_trigger_script_s00_0_5,
};

u16 camera_trigger_script_s00_1_0[6] = {
    0x0EA0,
    0x0E20,
    0x01E0,
    0x01D0,
    0x0005,
    0x0000,
};

u16 camera_trigger_script_s00_1_1[6] = {
    0x0EA0,
    0x0E20,
    0x01CF,
    0x01C0,
    0x0002,
    0x0000,
};

u16 camera_trigger_script_s00_1_2[6] = {
    0x114C,
    0x113C,
    0x01F0,
    0x0100,
    0x0007,
    0x0000,
};

u16 camera_trigger_script_s00_1_3[6] = {
    0x0F10,
    0x0EA0,
    0x01E0,
    0x01D0,
    0x0005,
    0x0000,
};

u16 camera_trigger_script_s00_1_4[6] = {
    0x0F10,
    0x0EA0,
    0x01CF,
    0x01C0,
    0x0002,
    0x0000,
};

u16* camera_trigger_scripts_s00_1[5] = {
    camera_trigger_script_s00_1_0,
    camera_trigger_script_s00_1_1,
    camera_trigger_script_s00_1_2,
    camera_trigger_script_s00_1_3,
    camera_trigger_script_s00_1_4,
};

u16 camera_trigger_script_s01_0_0[6] = {
    0x01C0,
    0x01A0,
    0x0190,
    0x00E0,
    0x0006,
    0x0000,
};

u16 camera_trigger_script_s01_0_1[6] = {
    0x01D0,
    0x01C0,
    0x01B0,
    0x00E0,
    0x0001,
    0x0000,
};

u16 camera_trigger_script_s01_0_2[6] = {
    0x0850,
    0x0770,
    0x0220,
    0x0210,
    0x0009,
    0x0000,
};

u16 camera_trigger_script_s01_0_3[8] = {
    0x0850,
    0x0710,
    0x0580,
    0x0560,
    0x000A,
    0x000B,
    0x0008,
    0x0000,
};

u16 camera_trigger_script_s01_0_4[8] = {
    0x15C0,
    0x15B0,
    0x0580,
    0x04D0,
    0x0001,
    0x000F,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s01_0_5[8] = {
    0x1680,
    0x1650,
    0x01B0,
    0x01A0,
    0x0002,
    0x000C,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s01_0_6[6] = {
    0x17A0,
    0x1790,
    0x01B0,
    0x0100,
    0x000E,
    0x0000,
};

u16 camera_trigger_script_s01_0_7[8] = {
    0x15B0,
    0x15A0,
    0x0580,
    0x04D0,
    0x0008,
    0x0009,
    0x000B,
    0x0000,
};

u16 camera_trigger_script_s01_0_8[8] = {
    0x1670,
    0x1660,
    0x01C0,
    0x01B0,
    0x0008,
    0x000A,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s01_0_9[8] = {
    0x0850,
    0x0840,
    0x04B0,
    0x0470,
    0x0033,
    0x0034,
    0x0035,
    0x0000,
};

u16 camera_trigger_script_s01_0_10[8] = {
    0x0840,
    0x0830,
    0x04B0,
    0x0470,
    0x0001,
    0x0008,
    0x0036,
    0x0000,
};

u16* camera_trigger_scripts_s01_0[11] = {
    camera_trigger_script_s01_0_0,
    camera_trigger_script_s01_0_1,
    camera_trigger_script_s01_0_2,
    camera_trigger_script_s01_0_3,
    camera_trigger_script_s01_0_4,
    camera_trigger_script_s01_0_5,
    camera_trigger_script_s01_0_6,
    camera_trigger_script_s01_0_7,
    camera_trigger_script_s01_0_8,
    camera_trigger_script_s01_0_9,
    camera_trigger_script_s01_0_10,
};

u16 camera_trigger_script_s01_1_0[8] = {
    0x05E0,
    0x0560,
    0x01E0,
    0x01D0,
    0x0013,
    0x0001,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s01_1_1[8] = {
    0x05E0,
    0x0560,
    0x01F0,
    0x01E1,
    0x0014,
    0x001A,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s01_1_2[8] = {
    0x02E0,
    0x0200,
    0x02F0,
    0x02E0,
    0x0015,
    0x0006,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s01_1_3[8] = {
    0x02E0,
    0x0200,
    0x0300,
    0x02F0,
    0x0016,
    0x0017,
    0x0008,
    0x0000,
};

u16 camera_trigger_script_s01_1_4[6] = {
    0x0720,
    0x0710,
    0x0370,
    0x0300,
    0x0014,
    0x0000,
};

u16 camera_trigger_script_s01_1_5[6] = {
    0x0730,
    0x0720,
    0x0370,
    0x0300,
    0x001C,
    0x0000,
};

u16 camera_trigger_script_s01_1_6[8] = {
    0x07A0,
    0x0770,
    0x0500,
    0x04F0,
    0x000A,
    0x000B,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s01_1_7[8] = {
    0x0D90,
    0x0D80,
    0x05D0,
    0x0590,
    0x001D,
    0x001E,
    0x001F,
    0x0000,
};

u16 camera_trigger_script_s01_1_8[8] = {
    0x07A0,
    0x0770,
    0x04F0,
    0x04E0,
    0x0017,
    0x0016,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s01_1_9[8] = {
    0x1190,
    0x1180,
    0x05C0,
    0x0540,
    0x0008,
    0x000B,
    0x0000,
    0x0000,
};

u16* camera_trigger_scripts_s01_1[10] = {
    camera_trigger_script_s01_1_0,
    camera_trigger_script_s01_1_1,
    camera_trigger_script_s01_1_2,
    camera_trigger_script_s01_1_3,
    camera_trigger_script_s01_1_4,
    camera_trigger_script_s01_1_5,
    camera_trigger_script_s01_1_6,
    camera_trigger_script_s01_1_7,
    camera_trigger_script_s01_1_8,
    camera_trigger_script_s01_1_9,
};

u16 camera_trigger_script_s02_0_0[8] = {
    0x1798,
    0x1790,
    0x08C0,
    0x0870,
    0x0021,
    0x0022,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s02_0_1[6] = {
    0x1570,
    0x1568,
    0x0550,
    0x0500,
    0x0026,
    0x0000,
};

u16 camera_trigger_script_s02_0_2[6] = {
    0x1568,
    0x1560,
    0x0550,
    0x0500,
    0x0013,
    0x0000,
};

u16* camera_trigger_scripts_s02_0[3] = {
    camera_trigger_script_s02_0_0,
    camera_trigger_script_s02_0_1,
    camera_trigger_script_s02_0_2,
};

u16 camera_trigger_script_s02_1_0[6] = {
    0x04C0,
    0x0460,
    0x0120,
    0x0110,
    0x0006,
    0x0000,
};

u16 camera_trigger_script_s02_1_1[6] = {
    0x04C0,
    0x0460,
    0x0130,
    0x0120,
    0x0001,
    0x0000,
};

u16 camera_trigger_script_s02_1_2[8] = {
    0x0A50,
    0x0A40,
    0x0160,
    0x0100,
    0x0018,
    0x0005,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s02_1_3[8] = {
    0x0A60,
    0x0A50,
    0x0160,
    0x0100,
    0x0019,
    0x0002,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s02_1_4[6] = {
    0x0BD0,
    0x0BC0,
    0x01C0,
    0x0120,
    0x0020,
    0x0000,
};

u16 camera_trigger_script_s02_1_5[6] = {
    0x0390,
    0x0380,
    0x0080,
    0x0038,
    0x004A,
    0x0000,
};

u16 camera_trigger_script_s02_1_6[6] = {
    0x03A0,
    0x0390,
    0x0080,
    0x0038,
    0x0005,
    0x0000,
};

u16* camera_trigger_scripts_s02_1[7] = {
    camera_trigger_script_s02_1_0,
    camera_trigger_script_s02_1_1,
    camera_trigger_script_s02_1_2,
    camera_trigger_script_s02_1_3,
    camera_trigger_script_s02_1_4,
    camera_trigger_script_s02_1_5,
    camera_trigger_script_s02_1_6,
};

u16 camera_trigger_script_s03_0_0[6] = {
    0x0780,
    0x0770,
    0x0100,
    0x0000,
    0x0011,
    0x0000,
};

u16 camera_trigger_script_s03_0_1[6] = {
    0x0770,
    0x0760,
    0x0100,
    0x0000,
    0x0012,
    0x0000,
};

u16 camera_trigger_script_s03_0_2[8] = {
    0x1320,
    0x1310,
    0x0300,
    0x0200,
    0x0023,
    0x0025,
    0x0000,
    0x0000,
};

u16* camera_trigger_scripts_s03_0[3] = {
    camera_trigger_script_s03_0_0,
    camera_trigger_script_s03_0_1,
    camera_trigger_script_s03_0_2,
};

u16 camera_trigger_script_s03_1_0[6] = {
    0x1820,
    0x17E0,
    0x01CA,
    0x01B0,
    0x0002,
    0x0000,
};

u16* camera_trigger_scripts_s03_1[1] = {
    camera_trigger_script_s03_1_0,
};

u16 camera_trigger_script_s04_0_0[6] = {
    0x0450,
    0x0440,
    0x03C0,
    0x0200,
    0x0017,
    0x0000,
};

u16 camera_trigger_script_s04_0_1[6] = {
    0x0440,
    0x0430,
    0x03C0,
    0x0200,
    0x0027,
    0x0000,
};

u16 camera_trigger_script_s04_0_2[6] = {
    0x1540,
    0x1530,
    0x03C0,
    0x0200,
    0x0027,
    0x0000,
};

u16 camera_trigger_script_s04_0_3[6] = {
    0x1530,
    0x1520,
    0x03C0,
    0x0200,
    0x0017,
    0x0000,
};

u16 camera_trigger_script_s04_0_4[6] = {
    0x1778,
    0x1770,
    0x02B0,
    0x0220,
    0x0028,
    0x0000,
};

u16 camera_trigger_script_s04_0_5[6] = {
    0x1770,
    0x1768,
    0x02B0,
    0x0220,
    0x0005,
    0x0000,
};

u16* camera_trigger_scripts_s04_0[6] = {
    camera_trigger_script_s04_0_0,
    camera_trigger_script_s04_0_1,
    camera_trigger_script_s04_0_2,
    camera_trigger_script_s04_0_3,
    camera_trigger_script_s04_0_4,
    camera_trigger_script_s04_0_5,
};

u16 camera_trigger_script_s04_1_0[6] = {
    0x05B0,
    0x05A0,
    0x02C0,
    0x0200,
    0x0027,
    0x0000,
};

u16 camera_trigger_script_s04_1_1[6] = {
    0x05C0,
    0x05B0,
    0x02C0,
    0x0200,
    0x0001,
    0x0000,
};

u16 camera_trigger_script_s04_1_2[8] = {
    0x0BB0,
    0x0BA0,
    0x02C0,
    0x0200,
    0x002A,
    0x002B,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s04_1_3[6] = {
    0x0BA0,
    0x0B90,
    0x02C0,
    0x0200,
    0x0001,
    0x0000,
};

u16 camera_trigger_script_s04_1_4[8] = {
    0x14C0,
    0x1470,
    0x0208,
    0x01F8,
    0x002A,
    0x0029,
    0x002B,
    0x0000,
};

u16 camera_trigger_script_s04_1_5[8] = {
    0x11C0,
    0x11B0,
    0x02C0,
    0x0200,
    0x0001,
    0x0028,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s04_1_6[8] = {
    0x11B0,
    0x11A0,
    0x02C0,
    0x0200,
    0x002A,
    0x002B,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s04_1_7[6] = {
    0x0600,
    0x05F0,
    0x02C0,
    0x0200,
    0x002C,
    0x0000,
};

u16* camera_trigger_scripts_s04_1[8] = {
    camera_trigger_script_s04_1_0,
    camera_trigger_script_s04_1_1,
    camera_trigger_script_s04_1_2,
    camera_trigger_script_s04_1_3,
    camera_trigger_script_s04_1_4,
    camera_trigger_script_s04_1_5,
    camera_trigger_script_s04_1_6,
    camera_trigger_script_s04_1_7,
};

u16 camera_trigger_script_s05_1_0[6] = {
    0x4280,
    0x4270,
    0x00B0,
    0x0060,
    0x002D,
    0x0000,
};

u16* camera_trigger_scripts_s05_1[1] = {
    camera_trigger_script_s05_1_0,
};

u16 camera_trigger_script_s06_1_0[6] = {
    0x0780,
    0x0770,
    0x0380,
    0x0340,
    0x0001,
    0x0000,
};

u16 camera_trigger_script_s06_1_1[6] = {
    0x0770,
    0x0760,
    0x0380,
    0x0340,
    0x0017,
    0x0000,
};

u16 camera_trigger_script_s06_1_2[6] = {
    0x0780,
    0x0770,
    0x04C0,
    0x0480,
    0x0037,
    0x0000,
};

u16 camera_trigger_script_s06_1_3[6] = {
    0x0770,
    0x0760,
    0x04C0,
    0x0480,
    0x0034,
    0x0000,
};

u16* camera_trigger_scripts_s06_1[4] = {
    camera_trigger_script_s06_1_0,
    camera_trigger_script_s06_1_1,
    camera_trigger_script_s06_1_2,
    camera_trigger_script_s06_1_3,
};

u16 camera_trigger_script_s07_0_0[6] = {
    0x0757,
    0x0500,
    0x0102,
    0x00F0,
    0x0006,
    0x0000,
};

u16 camera_trigger_script_s07_0_1[6] = {
    0x0757,
    0x0500,
    0x0110,
    0x0102,
    0x0001,
    0x0000,
};

u16 camera_trigger_script_s07_0_2[6] = {
    0x07E0,
    0x07D0,
    0x0150,
    0x0100,
    0x0001,
    0x0000,
};

u16* camera_trigger_scripts_s07_0[3] = {
    camera_trigger_script_s07_0_0,
    camera_trigger_script_s07_0_1,
    camera_trigger_script_s07_0_2,
};

u16 camera_trigger_script_s07_1_0[8] = {
    0x0B60,
    0x0AC0,
    0x02B8,
    0x02A0,
    0x002E,
    0x002F,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s07_1_1[6] = {
    0x0B60,
    0x0AC0,
    0x02D0,
    0x02C0,
    0x0030,
    0x0000,
};

u16 camera_trigger_script_s07_1_2[6] = {
    0x09E0,
    0x09D0,
    0x02D0,
    0x01F0,
    0x0031,
    0x0000,
};

u16 camera_trigger_script_s07_1_3[6] = {
    0x0A60,
    0x0A50,
    0x02D0,
    0x01F0,
    0x0032,
    0x0000,
};

u16 camera_trigger_script_s07_1_4[6] = {
    0x0A80,
    0x0A70,
    0x02D0,
    0x01F0,
    0x0013,
    0x0000,
};

u16 camera_trigger_script_s07_1_5[6] = {
    0x0800,
    0x07A0,
    0x0320,
    0x0310,
    0x0027,
    0x0000,
};

u16 camera_trigger_script_s07_1_6[6] = {
    0x0800,
    0x07A0,
    0x0330,
    0x0320,
    0x0017,
    0x0000,
};

u16 camera_trigger_script_s07_1_7[8] = {
    0x0AB0,
    0x0AA0,
    0x03D0,
    0x03B0,
    0x003E,
    0x0027,
    0x0000,
    0x0000,
};

u16* camera_trigger_scripts_s07_1[8] = {
    camera_trigger_script_s07_1_0,
    camera_trigger_script_s07_1_1,
    camera_trigger_script_s07_1_2,
    camera_trigger_script_s07_1_3,
    camera_trigger_script_s07_1_4,
    camera_trigger_script_s07_1_5,
    camera_trigger_script_s07_1_6,
    camera_trigger_script_s07_1_7,
};

u16 camera_trigger_script_s10_0_0[6] = {
    0x0F70,
    0x0F60,
    0x08C0,
    0x0810,
    0x0039,
    0x0000,
};

u16 camera_trigger_script_s10_0_1[6] = {
    0x0F60,
    0x0F50,
    0x08C0,
    0x0810,
    0x0038,
    0x0000,
};

u16 camera_trigger_script_s10_0_2[6] = {
    0x0FF0,
    0x0ED0,
    0x0850,
    0x0840,
    0x003A,
    0x0000,
};

u16 camera_trigger_script_s10_0_3[6] = {
    0x0FF0,
    0x0ED0,
    0x0860,
    0x0850,
    0x0022,
    0x0000,
};

u16 camera_trigger_script_s10_0_4[8] = {
    0x0F70,
    0x0F40,
    0x03A0,
    0x0390,
    0x003B,
    0x003C,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s10_0_5[8] = {
    0x0F70,
    0x0F40,
    0x03B0,
    0x03A0,
    0x0021,
    0x003D,
    0x0000,
    0x0000,
};

u16* camera_trigger_scripts_s10_0[6] = {
    camera_trigger_script_s10_0_0,
    camera_trigger_script_s10_0_1,
    camera_trigger_script_s10_0_2,
    camera_trigger_script_s10_0_3,
    camera_trigger_script_s10_0_4,
    camera_trigger_script_s10_0_5,
};

u16 camera_trigger_script_s11_1_0[6] = {
    0x0280,
    0x0270,
    0x0150,
    0x0130,
    0x0014,
    0x0000,
};

u16 camera_trigger_script_s11_1_1[6] = {
    0x0270,
    0x0260,
    0x0150,
    0x0130,
    0x0038,
    0x0000,
};

u16 camera_trigger_script_s11_1_2[6] = {
    0x02B0,
    0x02A0,
    0x02D0,
    0x0290,
    0x0041,
    0x0000,
};

u16 camera_trigger_script_s11_1_3[6] = {
    0x02A0,
    0x0290,
    0x02D0,
    0x0290,
    0x0049,
    0x0000,
};

u16 camera_trigger_script_s11_1_4[6] = {
    0x03A0,
    0x0370,
    0x01D0,
    0x01C0,
    0x0042,
    0x0000,
};

u16 camera_trigger_script_s11_1_5[6] = {
    0x03A0,
    0x0370,
    0x01E0,
    0x01D0,
    0x0043,
    0x0000,
};

u16 camera_trigger_script_s11_1_6[8] = {
    0x03F0,
    0x03E0,
    0x01D0,
    0x01B0,
    0x0044,
    0x0045,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s11_1_7[8] = {
    0x03E0,
    0x03D0,
    0x01D0,
    0x01B0,
    0x0038,
    0x0046,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s11_1_8[8] = {
    0x0480,
    0x0440,
    0x01DB,
    0x01CB,
    0x0042,
    0x0045,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s11_1_9[8] = {
    0x0480,
    0x0440,
    0x01EB,
    0x01DB,
    0x0047,
    0x0048,
    0x0000,
    0x0000,
};

u16 camera_trigger_script_s11_1_10[6] = {
    0x0C10,
    0x0C00,
    0x01D0,
    0x01B0,
    0x0028,
    0x0000,
};

u16* camera_trigger_scripts_s11_1[11] = {
    camera_trigger_script_s11_1_0,
    camera_trigger_script_s11_1_1,
    camera_trigger_script_s11_1_2,
    camera_trigger_script_s11_1_3,
    camera_trigger_script_s11_1_4,
    camera_trigger_script_s11_1_5,
    camera_trigger_script_s11_1_6,
    camera_trigger_script_s11_1_7,
    camera_trigger_script_s11_1_8,
    camera_trigger_script_s11_1_9,
    camera_trigger_script_s11_1_10,
};

u16 camera_trigger_script_s12_0_0[8] = {
    0x0770,
    0x0720,
    0x00D0,
    0x00C0,
    0x003F,
    0x0040,
    0x0000,
    0x0000,
};

u16* camera_trigger_scripts_s12_0[1] = {
    camera_trigger_script_s12_0_0,
};

u16** camera_trigger_stage_scripts[26] = {
    camera_trigger_scripts_s00_0,
    camera_trigger_scripts_s00_1,
    camera_trigger_scripts_s01_0,
    camera_trigger_scripts_s01_1,
    camera_trigger_scripts_s02_0,
    camera_trigger_scripts_s02_1,
    camera_trigger_scripts_s03_0,
    camera_trigger_scripts_s03_1,
    camera_trigger_scripts_s04_0,
    camera_trigger_scripts_s04_1,
    NULL,
    camera_trigger_scripts_s05_1,
    NULL,
    camera_trigger_scripts_s06_1,
    camera_trigger_scripts_s07_0,
    camera_trigger_scripts_s07_1,
    NULL,
    NULL,
    NULL,
    NULL,
    camera_trigger_scripts_s10_0,
    NULL,
    NULL,
    camera_trigger_scripts_s11_1,
    camera_trigger_scripts_s12_0,
    NULL,
};

struct Effect00BackgroundUpdate camera_trigger_bound_values[74] = {
    { 2, 0x100 },
    { 3, 0x100 },
    { 3, 0x168 },
    { 2, 0x168 },
    { 3, 0x300 },
    { 2, 0 },
    { 0, 0x115C },
    { 3, 0x500 },
    { 0, 0x710 },
    { 1, 0x15D0 },
    { 2, 0x500 },
    { 1, 0x17A0 },
    { 0, 0x1680 },
    { 0, 0x17A0 },
    { 0, 0x1500 },
    { 0, 0xBA0 },
    { 1, 0xB80 },
    { 1, 0x6C0 },
    { 0, 0 },
    { 0, 0x200 },
    { 1, 0x4B0 },
    { 1, 0x700 },
    { 2, 0x300 },
    { 1, 0x9C0 },
    { 1, 0x1890 },
    { 2, 0x1E0 },
    { 3, 0x300 },
    { 0, 0x700 },
    { 0, 0xD00 },
    { 2, 0x400 },
    { 1, 0xFB0 },
    { 0, 0xB10 },
    { 3, 0x800 },
    { 2, 0x800 },
    { 0, 0x1200 },
    { 0, 0x1110 },
    { 1, 0x1200 },
    { 0, 0x14C0 },
    { 2, 0x200 },
    { 3, 0x200 },
    { 0, 0x13E0 },
    { 2, 0x1EB },
    { 3, 0x1EB },
    { 0, 0x570 },
    { 3, 0x80 },
    { 2, 0x1F8 },
    { 3, 0x1F8 },
    { 3, 0x300 },
    { 1, 0x8C0 },
    { 0, 0x8C0 },
    { 1, 0x8B0 },
    { 3, 0x400 },
    { 2, 0x400 },
    { 1, 0x710 },
    { 3, 0x700 },
    { 0, 0x100 },
    { 0, 0xEC0 },
    { 2, 0x2E0 },
    { 3, 0x2E0 },
    { 1, 0xF10 },
    { 1, 0xEC0 },
    { 0, 0xA00 },
    { 1, 0x750 },
    { 0, 0x600 },
    { 1, 0x2C0 },
    { 3, 0x110 },
    { 3, 0x200 },
    { 0, 0x3E0 },
    { 1, 0x400 },
    { 1, 0x2C0 },
    { 3, 0x250 },
    { 1, 0xAD0 },
    { 1, 0x230 },
    { 3, 0 },
};

u16* camera_trigger_bound_fields[4] = {
    &background_objects[0].unk26,
    &background_objects[0].unk24,
    &background_objects[0].unk2A,
    &background_objects[0].unk28,
};
