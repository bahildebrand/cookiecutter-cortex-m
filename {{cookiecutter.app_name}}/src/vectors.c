/**
 * @file vectors.c
 * @author {{cookiecutter.full_name}} ({{cookiecutter.email}})
 * @brief Exception vectors for cortex-m MCUs
 */

#include <stdint.h>
#include <startup.h>

extern uint32_t _stack_end;

int main(void);

static void Reset_Handler(void);
static void NMI_Handler(void);
static void HardFault_Handler(void);
static void MemManage_Handler(void);
static void BusFault_Handler(void);
static void UsageFault_Handler(void);
static void SVC_Handler(void);
static void DebugMon_Handler(void);
static void PendSV_Handler(void);
static void SysTick_Handler(void);

/* Tells the linker to place vec_table in the .vecs section. This allows us to
 * place this section at the start of our memory map in the linker script. */
__attribute__((section(".vecs"))) void (*const vector_table[])(void) = {
    (void *)&_stack_end,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
};

static void Reset_Handler(void)
{
        init_mem();

        main();
}

static void NMI_Handler(void)
{
        while (1)
        {
                ;
        }
}

static void HardFault_Handler(void)
{
        while (1)
        {
                ;
        }
}

static void MemManage_Handler(void)
{
        while (1)
        {
                ;
        }
}

static void BusFault_Handler(void)
{
        while (1)
        {
                ;
        }
}

static void UsageFault_Handler(void)
{
        while (1)
        {
                ;
        }
}

static void SVC_Handler(void)
{
}

static void DebugMon_Handler(void)
{
        while (1)
        {
                ;
        }
}

static void PendSV_Handler(void)
{
}

static void SysTick_Handler(void)
{
}
