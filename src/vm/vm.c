#include <stdint.h>
#include "corewar/vm.h"


void vm_init(vm_t *vm)
{
    arena_init(&vm->arena);
    process_init(&vm->process, 0);
    vm->current_cycle = 0;
    vm->process_count = 1;
}