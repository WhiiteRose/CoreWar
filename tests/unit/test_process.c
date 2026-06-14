#include <criterion/criterion.h>
#include "corewar/process.h"

Test(process_init, initializes_process_fields) {
    process_t process;
    process_init(&process, 123);

    cr_assert_eq(process.pc, 123);
    cr_assert_eq(process.carry, 0);
    for (int i = 0; i < NUM_REGISTERS; i++) {
        cr_assert_eq(process.registers[i], 0);
    }
}

Test(process_init, initializes_pc_negative_value) {
    process_t process;
    process_init(&process, -1);

    cr_assert_eq(process.pc, 4095);
    cr_assert_eq(process.carry, 0);
    for (int i = 0; i < NUM_REGISTERS; i++) {
        cr_assert_eq(process.registers[i], 0);
    }
}

Test(process_init, initializes_pc_wrapped_value) {
    process_t process;
    process_init(&process, 4097);

    cr_assert_eq(process.pc, 1);
    cr_assert_eq(process.carry, 0);
    for (int i = 0; i < NUM_REGISTERS; i++) {
        cr_assert_eq(process.registers[i], 0);
    }
}

