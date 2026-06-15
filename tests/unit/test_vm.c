#include <criterion/criterion.h>
#include "corewar/vm.h"
#include "corewar/arena.h"
#include "corewar/process.h"

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