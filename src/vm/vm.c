#include <stdint.h>
#include "corewar/vm.h"


void vm_init(vm_t *vm)
{
    arena_init(&vm->arena);
    process_init(&vm->process, 0);
    vm->current_cycle = 0;
    vm->process_count = 1;
}

uint8_t vm_fetch_opcode(vm_t *vm)
{
    return arena_read_u8(&vm->arena, vm->process.pc);
}