SECTIONS
{
    GROUP:
    {
        .text ALIGN(0x4):{}
        .rodata ALIGN(0x8):{}
        .ctors ALIGN(0x4):{}
        .dtors ALIGN(0x4):{}
        .data ALIGN(0x20):{ *(.data) *(extabindex) *(extab) }
        .bss ALIGN(0x20):{}
    }
}

FORCEACTIVE
{
	$FORCEACTIVE
}
