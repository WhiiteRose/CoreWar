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

Test(opcode_is_valid, returns_true_for_opcode_constants) {
    cr_assert(opcode_is_valid(OP_LIVE));
    cr_assert(opcode_is_valid(OP_LD));
    cr_assert(opcode_is_valid(OP_ST));
    cr_assert(opcode_is_valid(OP_ADD));
    cr_assert(opcode_is_valid(OP_SUB));
    cr_assert(opcode_is_valid(OP_AND));
    cr_assert(opcode_is_valid(OP_OR));
    cr_assert(opcode_is_valid(OP_XOR));
    cr_assert(opcode_is_valid(OP_ZJMP));
    cr_assert(opcode_is_valid(OP_LDI));
    cr_assert(opcode_is_valid(OP_STI));
    cr_assert(opcode_is_valid(OP_FORK));
    cr_assert(opcode_is_valid(OP_LLD));
    cr_assert(opcode_is_valid(OP_LLDI));
    cr_assert(opcode_is_valid(OP_LFORK));
    cr_assert(opcode_is_valid(OP_AFF));
}