/**
 * @file startup.c
 * @author Blake Hildebrand (baugusthildebrand@gmail.com)
 * @brief Startup handler for cortex-m4 MCUs
 */

#include <stdint.h>

extern uint32_t _stack_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _text_end;

int main(void);
static void reset_handler(void);
static void nmi_handler(void);
static void hardfault_handler(void);

static void init_mem(void);

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

static void init_mem(void)
{
        uint32_t *data_value_ptr = &_text_end;

        for(uint32_t *bss_ptr = &_bss_start; bss_ptr < &_bss_end; bss_ptr++) {
                *bss_ptr = 0u;
        }

        for(uint32_t *data_ptr = &_data_start; data_ptr < &_data_end;) {
                *data_ptr++ = *data_value_ptr++;
        }
}

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
        while(1) {}
}