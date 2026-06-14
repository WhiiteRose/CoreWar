#include <criterion/criterion.h>
#include "corewar/arena.h"

Test(arena_wrap_addr, keeps_valid_adress) {
    cr_assert_eq(arena_wrap_addr(0), 0);
    cr_assert_eq(arena_wrap_addr(1), 1);
    cr_assert_eq(arena_wrap_addr(4095), 4095);
}

Test(arena_wrap_addr, wraps_adresses_after_memory_end) {
    cr_assert_eq(arena_wrap_addr(4097), 1);
    cr_assert_eq(arena_wrap_addr(4098), 2);
    cr_assert_eq(arena_wrap_addr(8192), 0);
}

Test(arena_wrap_addr, wraps_negative_adresses) {
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