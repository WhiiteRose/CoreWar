#include <criterion/criterion.h>
#include "corewar/vm.h"
#include "corewar/arena.h"
#include "corewar/process.h"
#include "corewar/opcode.h"

Test(vm_init, initializes_arena_and_process) {
    vm_t vm;
    vm_init(&vm);

    for (int i = 0; i < MEM_SIZE; i++) {
        cr_assert_eq(vm.arena.memory[i], 0);
    }

    cr_assert_eq(vm.process.pc, 0);
    cr_assert_eq(vm.process.carry, 0);
    for (int i = 0; i < NUM_REGISTERS; i++) {
        cr_assert_eq(vm.process.registers[i], 0);
    }
}

Test(vm_init, initializes_counters) {
    vm_t vm;
    vm_init(&vm);

    cr_assert_eq(vm.current_cycle, 0);
    cr_assert_eq(vm.process_count, 1);
}


Test(vm_init, initializes_live_state) {
    vm_t vm;
    vm_init(&vm);

    cr_assert_eq(vm.last_live_id, 0);
    cr_assert_eq(vm.last_live_cycle, 0);
    cr_assert_eq(vm.live_count, 0);
}

Test(vm_fetch_opcode, returns_correct_opcode) {
    vm_t vm;
    vm_init(&vm);

    vm.arena.memory[0] = 0x42;

    uint8_t opcode = vm_fetch_opcode(&vm);
    cr_assert_eq(opcode, 0x42);
}

Test(vm_fetch_opcode, returns_correct_opcode_at_nonzero_pc) {
    vm_t vm;
    vm_init(&vm);

    process_init(&vm.process, 5);
    vm.arena.memory[5] = 0x99;

    uint8_t opcode = vm_fetch_opcode(&vm);
    cr_assert_eq(opcode, 0x99);
}

Test(vm_step, advances_pc_by_one_for_invalid_opcode) {
    vm_t vm;
    vm_init(&vm);

    vm.arena.memory[0] = 0x00;

    uint32_t initial_current_cycle = vm.current_cycle;
    vm_step(&vm);

    cr_assert_eq(vm.process.pc, 1);
    cr_assert_eq(vm.current_cycle, initial_current_cycle + 1);
}

Test(vm_step, increments_current_cycle_if_opcode_invalid_at_end_of_memory) {
    vm_t vm;
    vm_init(&vm);
    process_init(&vm.process, MEM_SIZE - 1);
    vm.arena.memory[MEM_SIZE - 1] = 0x00;
    uint32_t initial_current_cycle = vm.current_cycle;
    vm_step(&vm);

    cr_assert_eq(vm.process.pc, 0);
    cr_assert_eq(vm.current_cycle, initial_current_cycle + 1);
}

Test(vm_step, advances_pc_by_live_size_for_live_opcode_at_zero_pc) {
    vm_t vm;
    vm_init(&vm);

    vm.arena.memory[0] = OP_LIVE;

    uint32_t initial_current_cycle = vm.current_cycle;
    vm_step(&vm);

    cr_assert_eq(vm.process.pc, 5);
    cr_assert_eq(vm.current_cycle, initial_current_cycle + 1);
}

Test(vm_step, advances_pc_by_live_size_for_live_opcode) {
    vm_t vm;
    vm_init(&vm);
    process_init(&vm.process, MEM_SIZE - 1);
    vm.arena.memory[MEM_SIZE - 1] = OP_LIVE;
    uint32_t initial_current_cycle = vm.current_cycle;
    vm_step(&vm);

    cr_assert_eq(vm.process.pc, 4);
    cr_assert_eq(vm.current_cycle, initial_current_cycle + 1);
}

Test(vm_read_live_argument, reads_correct_value) {
    vm_t vm;
    vm_init(&vm);

    vm.arena.memory[1] = 0x12;
    vm.arena.memory[2] = 0x34;
    vm.arena.memory[3] = 0x56;
    vm.arena.memory[4] = 0x78;

    uint32_t value = vm_read_live_argument(&vm);
    cr_assert_eq(value, 0x12345678);
}

Test(vm_read_live_argument, reads_correct_value_with_nonzero_pc) {
    vm_t vm;
    vm_init(&vm);
    process_init(&vm.process, 10);

    vm.arena.memory[11] = 0x12;
    vm.arena.memory[12] = 0x34;
    vm.arena.memory[13] = 0x56;
    vm.arena.memory[14] = 0x78;

    uint32_t value = vm_read_live_argument(&vm);
    cr_assert_eq(value, 0x12345678);
}

Test(vm_read_live_argument, reads_correct_value_with_wraparound) {
    vm_t vm;
    vm_init(&vm);
    process_init(&vm.process, MEM_SIZE - 2);

    vm.arena.memory[MEM_SIZE - 1] = 0x12;
    vm.arena.memory[0] = 0x34;
    vm.arena.memory[1] = 0x56;
    vm.arena.memory[2] = 0x78;

    uint32_t value = vm_read_live_argument(&vm);
    cr_assert_eq(value, 0x12345678);
}

Test(vm_step, live_stores_arguments) {
    vm_t vm;
    vm_init(&vm);

    vm.arena.memory[0] = OP_LIVE;
    vm.arena.memory[1] = 0x00;
    vm.arena.memory[2] = 0x00;
    vm.arena.memory[3] = 0x00;
    vm.arena.memory[4] = 0x42;

    uint32_t initial_current_cycle = vm.current_cycle;
    vm_step(&vm);

    cr_assert_eq(vm.last_live_id, 0x00000042);
    cr_assert_eq(vm.last_live_cycle, initial_current_cycle);
    cr_assert_eq(vm.live_count, 1);
}

Test(vm_execute_live, updates_live_state) {
    vm_t vm;
    vm_init(&vm);

    vm.arena.memory[0] = OP_LIVE;
    vm.arena.memory[1] = 0x00;
    vm.arena.memory[2] = 0x00;
    vm.arena.memory[3] = 0x00;
    vm.arena.memory[4] = 0x42;

    uint32_t initial_current_cycle = vm.current_cycle;
    vm_execute_live(&vm);

    cr_assert_eq(vm.last_live_id, 0x00000042);
    cr_assert_eq(vm.last_live_cycle, initial_current_cycle);
    cr_assert_eq(vm.live_count, 1);
    cr_assert_eq(vm.current_cycle, initial_current_cycle);
    cr_assert_eq(vm.process.pc, 5);
}

Test(vm_fetch_coding_byte, returns_correct_coding_byte) {
    vm_t vm;
    vm_init(&vm);

    vm.arena.memory[0] = OP_LD;
    vm.arena.memory[1] = 0x90;

    uint8_t coding_byte = vm_fetch_coding_byte(&vm);
    cr_assert_eq(coding_byte, 0x90);
}

Test(vm_fetch_coding_byte, returns_correct_coding_byte_pc_non_zero) {
    vm_t vm;
    vm_init(&vm);

    process_init(&vm.process, 10);
    vm.arena.memory[11] = 0x90;

    uint8_t coding_byte = vm_fetch_coding_byte(&vm);
    cr_assert_eq(coding_byte, 0x90);
}

Test(vm_fetch_coding_byte, returns_correct_coding_byte_pc_wraparound) {
    vm_t vm;
    vm_init(&vm);

    process_init(&vm.process, MEM_SIZE - 1);
    vm.arena.memory[0] = 0x90;

    uint8_t coding_byte = vm_fetch_coding_byte(&vm);
    cr_assert_eq(coding_byte, 0x90);
}

