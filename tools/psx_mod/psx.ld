OUTPUT_ARCH(mips)
ENTRY(__start)

SECTIONS
{
    . = 0x80010000;

    .main : SUBALIGN(4) {
        /* @RODATA@ */
        *(.rodata .rodata.* .rdata)
        /* @TEXT@ */
        *(.text .text.*)
        /* @DATA@ */
        *(.data .data.* .sdata)
        . = ALIGN(4);
    }

    .bss (NOLOAD) : SUBALIGN(4) {
        __bss_start = .;
        /* @BSS@ */
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
        *(.sbss .scommon)
    }

    /DISCARD/ : {
        *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.mdebug*) *(.comment) *(.gnu.attributes) *(.note*)
    }
}

ASSERT(__bss_end <= 0x80178000, "BSS overlaps the archive arena at 0x80178000 (include/archive_memory.h)");
