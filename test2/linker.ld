/* linker.ld - 適合 USTART 的簡易鏈結腳本 */
ENTRY(_start)
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 2048K
    RAM (rwx)  : ORIGIN = 0x24000000, LENGTH = 512K
}
SECTIONS
{
    .text : {
        *(.text*)
        *(.rodata*)
    } > FLASH

    .data : {
        __data_start__ = .;
        *(.data*)
        __data_end__ = .;
    } > RAM AT> FLASH

    .bss (NOLOAD) : {
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
    } > RAM

    _end = .;
}
