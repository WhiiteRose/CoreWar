#include <criterion/criterion.h>
#include "corewar/coding_byte.h"

Test(coding_byte_get_arg_type, returns_none_for_arg_index_0) {
    cr_assert_eq(coding_byte_get_arg_type(0x40, 0), ARG_NONE);
}

Test(coding_byte_get_arg_type, returns_reg_for_arg_index_1) {
    cr_assert_eq(coding_byte_get_arg_type(0x40, 1), ARG_REG);
}

Test(coding_byte_get_arg_type, returns_dir_for_arg_index_2) {
    cr_assert_eq(coding_byte_get_arg_type(0x20, 2), ARG_DIR);
}

Test(coding_byte_get_arg_type, returns_ind_for_arg_index_3) {
    cr_assert_eq(coding_byte_get_arg_type(0x0c, 3), ARG_IND);
}

Test(coding_byte_get_arg_type, returns_ind_for_arg_index_3_with_coding_byte_0x90) {
    cr_assert_eq(coding_byte_get_arg_type(0x90, 1), ARG_DIR);
    cr_assert_eq(coding_byte_get_arg_type(0x90, 2), ARG_REG);
    cr_assert_eq(coding_byte_get_arg_type(0x90, 3), ARG_NONE);
}
