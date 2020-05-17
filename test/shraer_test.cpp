#include "shraer_test.h"

using namespace shraer_sims;

void shraer_test::test_permutation_mult_id() noexcept {
    const uint32_t n = 5;
    permutation a(n), b(n);
    DO_CHECK((a * b == a));
}

void shraer_test::test_permutation_mult_random_perm() noexcept {
    permutation a({1, 2, 0, 4, 3}), b({3, 2, 0, 1, 4});
    DO_CHECK((a * b == permutation({4, 0, 1, 2, 3})));
}

void shraer_test::test_permutation_mult_cycle() noexcept {
    permutation a({1, 2, 3, 4, 0}), b({4, 3, 0, 2, 1});
    DO_CHECK((a * b == permutation({0, 4, 1, 3, 2})));
}

void shraer_test::test_permutation_apply_id() noexcept {
    const uint32_t n = 5;
    DO_CHECK((permutation(n) * 3 == 3));
}

void shraer_test::test_permutation_apply_random_perm() noexcept {
    DO_CHECK((permutation({3, 4, 0, 1, 5, 2}) * 2 == 0));
}

void shraer_test::test_permutation_apply_cycle() noexcept {
    DO_CHECK((permutation({1, 2, 3, 4, 0}) * 1 == 2));
}

void shraer_test::test_permutation_inv_id() noexcept {
    const uint32_t n = 5;
    permutation a(n);
    DO_CHECK((a.inv() == a));
}

void shraer_test::test_permutation_inv_random_perm() noexcept {
    DO_CHECK((permutation({4, 5, 2, 1, 3, 0}).inv() == permutation({5, 3, 2, 4, 0, 1})));
}

void shraer_test::test_permutation_inv_cycle() noexcept {
    DO_CHECK((permutation({1, 2, 3, 4, 0}).inv() == permutation({4, 0, 1, 2, 3})));
}

void shraer_test::run_all_tests() {
    test_permutation_mult_id();
    test_permutation_mult_random_perm();
    test_permutation_mult_cycle();
    test_permutation_apply_id();
    test_permutation_apply_random_perm();
    test_permutation_apply_cycle();
    test_permutation_inv_id();
    test_permutation_inv_random_perm();
    test_permutation_inv_cycle();
}
