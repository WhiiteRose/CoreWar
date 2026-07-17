#include <criterion/criterion.h>
#include "corewar/opcode.h"

Test(opcode_is_valid, returns_true_for_valid_opcode) {
    cr_assert(opcode_is_valid(0x01));
}

Test(opcode_is_valid, returns_true_for_last_valid_opcode) {
    cr_assert(opcode_is_valid(0x10));
}

Test(opcode_is_valid, returns_false_for_opcode_below_range) {
    cr_assert_not(opcode_is_valid(0x00));
}

Test(opcode_is_valid, returns_false_for_opcode_above_range) {
    cr_assert_not(opcode_is_valid(0x11));
}