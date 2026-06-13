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