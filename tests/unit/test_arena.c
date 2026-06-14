#include <criterion/criterion.h>
#include "corewar/arena.h"

Test(arena_wrap_addr, keeps_valid_address) {
    cr_assert_eq(arena_wrap_addr(0), 0);
    cr_assert_eq(arena_wrap_addr(1), 1);
    cr_assert_eq(arena_wrap_addr(4095), 4095);
}

Test(arena_wrap_addr, wraps_addresses_after_memory_end) {
    cr_assert_eq(arena_wrap_addr(4097), 1);
    cr_assert_eq(arena_wrap_addr(4098), 2);
    cr_assert_eq(arena_wrap_addr(8192), 0);
}

Test(arena_wrap_addr, wraps_negative_addresses) {
    cr_assert_eq(arena_wrap_addr(-1), 4095);
    cr_assert_eq(arena_wrap_addr(-2), 4094);
    cr_assert_eq(arena_wrap_addr(-4096), 0);
}

Test(arena_init, initializes_memory_to_zero) {
    arena_t arena;
    arena_init(&arena);

    for (int i = 0; i < MEM_SIZE; i++) {
        cr_assert_eq(arena.memory[i], 0);
    }
}

Test(arena_read_u8, reads_value_from_arena) {
    arena_t arena;
    arena_init(&arena);
    arena.memory[0] = 42;

    cr_assert_eq(arena_read_u8(&arena, 0), 42);
}

Test (arena_read_u8, reads_value_from_wrapped_address) {
    arena_t arena;
    arena_init(&arena);
    arena.memory[0] = 42;

    cr_assert_eq(arena_read_u8(&arena, 4096), 42);
}

Test(arena_read_u8, reads_value_from_negative_address) {
    arena_t arena;
    arena_init(&arena);
    arena.memory[4095] = 42;

    cr_assert_eq(arena_read_u8(&arena, -1), 42);
}

Test(arena_write_u8, writes_value_to_arena) {
    arena_t arena;
    arena_init(&arena);
    arena_write_u8(&arena, 0, 42);

    cr_assert_eq(arena.memory[0], 42);
}

Test(arena_write_u8, writes_value_to_wrapped_address) {
    arena_t arena;
    arena_init(&arena);
    arena_write_u8(&arena, 4096, 42);

    cr_assert_eq(arena.memory[0], 42);
}

Test(arena_write_u8, writes_value_to_negative_address) {
    arena_t arena;
    arena_init(&arena);
    arena_write_u8(&arena, -1, 42);

    cr_assert_eq(arena.memory[4095], 42);
}

Test(arena_write_u16, writes_value_to_arena) {
    arena_t arena;
    arena_init(&arena);
    arena_write_u16(&arena, 0, 0x1234);

    cr_assert_eq(arena.memory[0], 0x12);
    cr_assert_eq(arena.memory[1], 0x34);
}

Test(arena_write_u16, writes_value_to_wrapped_address) {
    arena_t arena;
    arena_init(&arena);
    arena_write_u16(&arena, 4095, 0x1234);

    cr_assert_eq(arena.memory[4095], 0x12);
    cr_assert_eq(arena.memory[0], 0x34);
}

Test(arena_write_u16, writes_value_to_negative_address) {
    arena_t arena;
    arena_init(&arena);
    arena_write_u16(&arena, -1, 0x1234);

    cr_assert_eq(arena.memory[4095], 0x12);
    cr_assert_eq(arena.memory[0], 0x34);
}

Test(arena_read_u16, reads_value_from_arena) {
    arena_t arena;
    arena_init(&arena);
    arena.memory[0] = 0x12;
    arena.memory[1] = 0x34;

    cr_assert_eq(arena_read_u16(&arena, 0), 0x1234);
}

Test(arena_read_u16, reads_value_from_wrapped_address) {
    arena_t arena;
    arena_init(&arena);
    arena.memory[4095] = 0x12;
    arena.memory[0] = 0x34;

    cr_assert_eq(arena_read_u16(&arena, 4095), 0x1234);
}

Test(arena_read_u16, reads_value_from_negative_address) {
    arena_t arena;
    arena_init(&arena);
    arena.memory[4095] = 0x12;
    arena.memory[0] = 0x34;

    cr_assert_eq(arena_read_u16(&arena, -1), 0x1234);
}

Test(arena_read_u32, reads_value_from_arena) {
    arena_t arena;
    arena_init(&arena);
    arena.memory[0] = 0x12;
    arena.memory[1] = 0x34;
    arena.memory[2] = 0x56;
    arena.memory[3] = 0x78;

    cr_assert_eq(arena_read_u32(&arena, 0), 0x12345678);
}

Test(arena_read_u32, reads_value_from_wrapped_address) {
    arena_t arena;
    arena_init(&arena);
    arena.memory[4095] = 0x12;
    arena.memory[0] = 0x34;
    arena.memory[1] = 0x56;
    arena.memory[2] = 0x78;

    cr_assert_eq(arena_read_u32(&arena, 4095), 0x12345678);
}

Test(arena_read_u32, reads_value_from_negative_address) {
    arena_t arena;
    arena_init(&arena);
    arena.memory[4095] = 0x12;
    arena.memory[0] = 0x34;
    arena.memory[1] = 0x56;
    arena.memory[2] = 0x78;

    cr_assert_eq(arena_read_u32(&arena, -1), 0x12345678);
}

Test(arena_write_u32, writes_value_to_arena) {
    arena_t arena;
    arena_init(&arena);
    arena_write_u32(&arena, 0, 0x12345678);

    cr_assert_eq(arena.memory[0], 0x12);
    cr_assert_eq(arena.memory[1], 0x34);
    cr_assert_eq(arena.memory[2], 0x56);
    cr_assert_eq(arena.memory[3], 0x78);
}

Test(arena_write_u32, writes_value_to_wrapped_address) {
    arena_t arena;
    arena_init(&arena);
    arena_write_u32(&arena, 4095, 0x12345678);

    cr_assert_eq(arena.memory[4095], 0x12);
    cr_assert_eq(arena.memory[0], 0x34);
    cr_assert_eq(arena.memory[1], 0x56);
    cr_assert_eq(arena.memory[2], 0x78);
}

Test(arena_write_u32, writes_value_to_negative_address) {
    arena_t arena;
    arena_init(&arena);
    arena_write_u32(&arena, -1, 0x12345678);

    cr_assert_eq(arena.memory[4095], 0x12);
    cr_assert_eq(arena.memory[0], 0x34);
    cr_assert_eq(arena.memory[1], 0x56);
    cr_assert_eq(arena.memory[2], 0x78);
}