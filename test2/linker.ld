/* linker.ld - 簡易鏈結腳本 */
ENTRY(_start)
SECTIONS
{
    . = 0x08000000; /* base on  MCU flash setup address */
    .text : {
        *(.text*)
        *(.rodata*)
    }
    .data : {
        *(.data*)
    }
    .bss : {
        *(.bss*)
        *(COMMON)
    }
}
