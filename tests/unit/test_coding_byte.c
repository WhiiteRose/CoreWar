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

Test(arg_type_size, returns_1_for_arg_reg) {
    cr_assert_eq(arg_type_size(ARG_REG), 1);
}

Test(arg_type_size, returns_4_for_arg_dir) {
    cr_assert_eq(arg_type_size(ARG_DIR), 4);
}

Test(arg_type_size, returns_2_for_arg_ind) {
    cr_assert_eq(arg_type_size(ARG_IND), 2);
}

Test(arg_type_size, returns_0_for_arg_none) {
    cr_assert_eq(arg_type_size(ARG_NONE), 0);
}