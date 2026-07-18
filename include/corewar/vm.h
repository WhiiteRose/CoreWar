#ifndef _VM_H_
#define _VM_H_
#include "corewar/arena.h"
#include "corewar/process.h"
#include <stdint.h>

typedef struct vm_s {
    arena_t arena;
    process_t process;
    uint32_t current_cycle;
    uint32_t process_count;
    uint32_t last_live_id;
    uint32_t last_live_cycle;
    uint32_t live_count;
} vm_t;

void vm_init(vm_t *vm);
uint8_t vm_fetch_opcode(vm_t *vm); 
void vm_step(vm_t *vm);
uint32_t vm_read_live_argument(vm_t *vm);
void vm_execute_live(vm_t *vm);
uint8_t vm_fetch_coding_byte(vm_t *vm);

#endif // _VM_H_