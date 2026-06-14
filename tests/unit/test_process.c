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

Test(process_advance_pc, advances_pc_by_offset) {
    process_t process;
    process_init(&process, 100);
    process_advance_pc(&process, 50);

    cr_assert_eq(process.pc, 150);
}

Test(process_advance_pc, advances_pc_with_wraparound) {
    process_t process;
    process_init(&process, 4090);
    process_advance_pc(&process, 10);

    cr_assert_eq(process.pc, 4);
}

Test(process_advance_pc, advances_pc_with_negative_offset) {
    process_t process;
    process_init(&process, 10);
    process_advance_pc(&process, -20);

    cr_assert_eq(process.pc, 4086);
}

Test(process_valid_register, valid_registers) {
    for (int i = 1; i <= NUM_REGISTERS; i++) {
        cr_assert(process_valid_register(i));
    }
}

Test(process_valid_register, invalid_registers) {
    cr_assert_not(process_valid_register(0));
    cr_assert_not(process_valid_register(NUM_REGISTERS + 1));
    cr_assert_not(process_valid_register(-1));
}

Test(process_read_register, reads_valid_register) {
    process_t process;
    process_init(&process, 0);
    process.registers[0] = 42;

    unsigned int value = process_read_register(&process, 1);
    cr_assert_eq(value, 42);
}

Test(process_read_register, reads_invalid_register) {
    process_t process;
    process_init(&process, 0);

    unsigned int value = process_read_register(&process, 0);
    cr_assert_eq(value, 0);

    value = process_read_register(&process, NUM_REGISTERS + 1);
    cr_assert_eq(value, 0);

    value = process_read_register(&process, -1);
    cr_assert_eq(value, 0);
}

Test(process_write_register, writes_to_valid_register) {
    process_t process;
    process_init(&process, 0);

    process_write_register(&process, 1, 42);
    cr_assert_eq(process.registers[0], 42);
}

Test(process_write_register, writes_to_invalid_register) {
    process_t process;
    process_init(&process, 0);

    process_write_register(&process, 0, 42);
    for (int i = 0; i < NUM_REGISTERS; i++) {
        cr_assert_eq(process.registers[i], 0);
    }

    process_write_register(&process, NUM_REGISTERS + 1, 42);
    for (int i = 0; i < NUM_REGISTERS; i++) {
        cr_assert_eq(process.registers[i], 0);
    }

    process_write_register(&process, -1, 42);
    for (int i = 0; i < NUM_REGISTERS; i++) {
        cr_assert_eq(process.registers[i], 0);
    }
}