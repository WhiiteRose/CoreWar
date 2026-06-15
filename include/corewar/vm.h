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
} vm_t;

void vm_init(vm_t *vm);

#endif // _VM_H_