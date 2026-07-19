#include <stdint.h>
#include "corewar/vm.h"
#include "corewar/opcode.h"
#include "corewar/process.h"
#include "corewar/coding_byte.h"


void vm_init(vm_t *vm)
{
    arena_init(&vm->arena);
    process_init(&vm->process, 0);
    vm->current_cycle = 0;
    vm->process_count = 1;
    vm->last_live_id = 0;
    vm->last_live_cycle = 0;
    vm->live_count = 0;
}

uint8_t vm_fetch_opcode(vm_t *vm)
{
    return arena_read_u8(&vm->arena, vm->process.pc);
}

void vm_step(vm_t *vm)
{
    uint8_t opcode = vm_fetch_opcode(vm);

    if (!opcode_is_valid(opcode)) {
        process_advance_pc(&vm->process, 1);
    } else if (opcode == OP_LIVE) {
        vm_execute_live(vm);
    }
    vm->current_cycle += 1;
}

uint32_t vm_read_live_argument(vm_t *vm)
{
    return arena_read_u32(&vm->arena, vm->process.pc + 1);
}

void vm_execute_live(vm_t *vm)
{
    vm->last_live_id = vm_read_live_argument(vm);
    vm->last_live_cycle = vm->current_cycle;
    vm->live_count += 1;
    process_advance_pc(&vm->process, 5);
}

uint8_t vm_fetch_coding_byte(vm_t *vm)
{
    return arena_read_u8(&vm->arena, vm->process.pc + 1);
}

uint8_t vm_instruction_size_with_coding_byte(vm_t *vm, int arg_count)
{
    return 1 + 1 + coding_byte_arguments_size(vm_fetch_coding_byte(vm), arg_count);
}