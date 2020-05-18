#pragma once

#include "autotest.h"
#include "permutation.h"
#include "schreier_tree.h"

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

    void test_schreier_tree_get_orbit_id() noexcept;

    void test_schreier_tree_get_orbit_random_perms() noexcept;

    void test_schreier_tree_get_orbit_cycles() noexcept;

    void test_schreier_tree_get_perm_id() noexcept;

    void test_schreier_tree_get_perm_random_perms() noexcept;

    void test_schreier_tree_get_perm_cycles() noexcept;

    void test_schreier_tree_get_perm_base() noexcept;

public:
    void run_all_tests() override;
};
