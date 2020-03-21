/**
 * @file vectors.c
 * @author {{cookiecutter.full_name}} ({{cookiecutter.email}})
 * @brief Exception vectors for cortex-m MCUs
 */

#include <stdint.h>
#include <startup.h>

extern uint32_t _stack_end;

int main(void);

static void reset_handler(void);
static void nmi_handler(void);
static void hardfault_handler(void);
static void mem_management_fault_handler(void);
static void bus_fault_handler(void);
static void usage_fault_handler(void);
static void sv_call_handler(void);
static void pend_sv_handler(void);
static void systick_handler(void);

/* Cortex-M vector table. These are all the core vectors as defined in the
 * Cortex-M spec. MCU vendors will expand this table with interrupt vectors
 * after the systick vector.
 * https://developer.arm.com/docs/dui0553/latest/the-cortex-m4-processor/exception-model/vector-table */
struct vector_table {
        void *stack_val;
        void *reset;
        void *nmi;
        void *hard_fault;
        void *mem_management_fault;
        void *bus_fault;
        void *usage_fault;
        void *reserved1[4];
        void *sv_call;
        void *debug;
        void *reserved2;
        void *pend_sv;
        void *systick;
};

/* Tells the linker to place vec_table in the .vecs section. This allows us to
 * place this section at the start of our memory map in the linker script. */
__attribute__ ((section(".vecs")))
struct vector_table vec_table = {
        .stack_val = (void*) &_stack_end,
        .reset = (void*) reset_handler,
        .nmi = (void*) nmi_handler,
        .hard_fault = (void*) hardfault_handler,
        .mem_management_fault = (void*) mem_management_fault_handler,
        .bus_fault = (void*) bus_fault_handler,
        .usage_fault = (void*) usage_fault_handler,
        .sv_call = (void*) sv_call_handler,
        .pend_sv = (void*) pend_sv_handler,
        .systick = (void*) systick_handler,
};

static void reset_handler(void)
{
        init_mem();

        main();
}

static void nmi_handler(void)
{
        while(1) {;}
}

static void hardfault_handler(void)
{
        while(1) {;}
}

static void mem_management_fault_handler(void)
{
        while(1) {;}
}

static void bus_fault_handler(void)
{
        while(1) {;}
}

static void usage_fault_handler(void)
{
        while(1) {;}
}

static void sv_call_handler(void)
{

}

static void pend_sv_handler(void)
{

}

static void systick_handler(void)
{

}