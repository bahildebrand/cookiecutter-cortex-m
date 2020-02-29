/* Provides the addresses for the memory regions on the MCU. */
MEMORY
{
    FLASH (rx) : ORIGIN = {{cookiecutter.flash_origin}}, LENGTH = {{cookiecutter.flash_length}}
    RAM (rwx) :  ORIGIN = {{cookiecutter.ram_origin}}, LENGTH = {{cookiecutter.ram_length}}
}