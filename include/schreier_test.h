#pragma once

#include "autotest.h"
#include "permutation.h"

class schreier_test: public Test {
private:
    void test_permutation_mult_id() noexcept;

    void test_permutation_mult_random_perm() noexcept;

    void test_permutation_mult_cycle() noexcept;

    void test_permutation_apply_id() noexcept;

    void test_permutation_apply_random_perm() noexcept;

    void test_permutation_apply_cycle() noexcept;

    void test_permutation_inv_id() noexcept;

    void test_permutation_inv_random_perm() noexcept;

    void test_permutation_inv_cycle() noexcept;

public:
    void run_all_tests() override;
};
