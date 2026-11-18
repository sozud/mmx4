#include "common.h"

long SpuClearReverbWorkArea(long mode)
{
    return 0;
}

void SsInit(void)
{
}

void SsSetTableSize(char* table, short s_max, short t_max)
{
}

void SsSetTickMode(long tick_mode)
{
}

void SsUtSetReverbDepth(short ldepth, short rdepth)
{
}

short SsUtSetReverbType(short type)
{
    return 1;
}

void SsVabClose(short vab_id)
{
}

void SsSepClose(short sep_access_num)
{
}

short SsSepOpenJ(unsigned long* addr, short vab_id, short seq_num)
{
    return 1;
}

void SsSetMVol(short voll, short volr)
{
}

void SsSetSerialAttr(char s_num, char attr, char mode)
{
}

void SsSetSerialVol(char s_num, short voll, short volr)
{
}

void SsStart(void)
{
}

void SsSepSetVol(short sep_access_num, short seq_num, short voll, short volr)
{
}
