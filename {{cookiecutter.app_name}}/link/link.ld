/* Include the linker script containing our memory regions. */
INCLUDE "link/mem.ld"

/* Size of the initial stack to be loaded in bytes */
STACK_SIZE = 0x1000;

SECTIONS
{
    /* Contains code that will only live in flash memory */
    .text :
    {
        /* Aligns this section to 4 bytes. Will pad out if alignment is not
         * met. */
        . = ALIGN(4);

        /* Tells the linker to expclicitly place the linker script at the start
         * of flash. Paired with "__attribute__ ((section(".vecs")))" in
         * vectors.c ensure our exception vectors are at the start of flash per
         * the cortex-m spec. */
        KEEP(*(.vecs*))

        /* All code to be executed lives in flash in the text section. */
        *(.text*)

        /* All constant values will live in the rodata section.
         *(Read-only data) */
        *(.rodata*)
        . = ALIGN(4);

    /* This command indicates what memory region to load the section into */
    } > FLASH

    /* Contains all file scoped and program scoped globals that are intialized
     * to 0. Note that any global not set to a value other than 0 goes into
     * BSS. The NOLOAD modifier indicates that it should not be loaeded into
     * flash. */
    .bss (NOLOAD) :
    {
        . = ALIGN(4);

        /* This operation assigns a variable in the symbol table at the current
         * address in the section. This specific example combined with the
         * _bss_end pointer gives us addresses to 0 out when initializing this
         * section later in startup.c.
         * See https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_chapter/ld_3.html#SEC10 */
        _bss_start = .;

        /* The COMMON section contains all global values that reach past file
         * scope. For C this is any variable outside of a function that does not
         * have the static keyword. */
        *(COMMON)

        /* All file scoped zero initalized data */
        *(.bss*)
        . = ALIGN(4);
        _bss_end = .;
    } > RAM

    /* Contains all global variables that are initialized to a non-zero value. */
    .data :
    {
        . = ALIGN(4);
        _data_start = .;
        *(.data*)
        . = ALIGN(4);
        _data_end = .;

    /* Since the data section has actual values loaded it has a different life
     * cycle than bss. The initial values are stored in flash to be preserved
     * across resets. This command indicates the values are going to end up in
     * RAM, but they are initially stored in FLASH. */
    } > RAM AT > FLASH

    /* This provides the load memory address for the data section. The LMA is
     * the beginning address where data is stored in FLASH. */
    _data_lma = LOADADDR(.data);

    /* This provides a chunk of RAM to be used as the stack. This memory does
     * not need to be initialized as the C memory model does not gaurantee the
     * value of stack memory */
    .stack (NOLOAD):
    {
        . = ALIGN(8);
        _stack_start = .;
        . = . + STACK_SIZE;
        . = ALIGN(8);
        _stack_end = .;
    } > RAM
}