INCLUDE "link/mem.ld"

STACK_SIZE = 0x1000;

SECTIONS
{
    .text :
    {
        KEEP(*(.vecs*))
        *(.text*)
        *(.rodata*)
        _text_end = .;
    } > FLASH

    .bss (NOLOAD) :
    {
        _bss_start = .;
        *(COMMON)
        *(.bss*)
        _bss_end = .;
    } > RAM

    .data :
    {
        _data_start = .;
        *(.data*)
        _data_end = .;
    } > RAM AT > FLASH

    .stack (NOLOAD):
    {
        . = ALIGN(8);
        _stack_start = .;
        . = . + STACK_SIZE;
        . = ALIGN(8);
        _stack_end = .;
    } > RAM
}