/**
 * @file startup.c
 * @author Blake Hildebrand (baugusthildebrand@gmail.com)
 * @brief Startup handler for cortex-m4 MCUs
 */

#include <stdint.h>

extern uint32_t _stack_end;

int main(void);
void reset_handler(void);
void nmi_handler(void);
void hardfault_handler(void);

struct vector_table {
        void *stack_val;
        void *reset;
        void *nmi;
        void *hard_fault;
        void *mem_management_fault;
        void *bus_fault;
        void *usage_fault;
        void *reservd[5];
        void *sv_call;
        void *pend_sv;
        void *systick;
};

__attribute__ ((section(".vecs")))
struct vector_table vec_table = {
        .stack_val = (void*) &_stack_end,
        .reset = (void*) reset_handler,
        .nmi = (void*) nmi_handler,
        .hard_fault = (void*) hardfault_handler,
};

void reset_handler(void)
{
        main();
}

void nmi_handler(void)
{

}

void hardfault_handler(void)
{

}