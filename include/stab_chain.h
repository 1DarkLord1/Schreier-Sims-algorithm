#pragma once

#include "permutation.h"
#include "schreier_tree.h"
#include "InfInt.h"
#include <memory>

namespace schreier_sims {
class stab_chain {
public:
    stab_chain(const std::vector<permutation>& group_gen_, const std::vector<uint32_t>& base_elems, std::size_t n_);

    const stab_chain& get_stab_chain(std::size_t i) const noexcept;

    std::set<uint32_t> get_orbit(std::size_t i) const;

    std::vector<permutation> get_gen(std::size_t i) const;

    std::vector<permutation> get_strong_gen() const;

    std::size_t len() const noexcept;

    bool contain(permutation p) const noexcept;

    std::vector<std::pair<int, std::size_t>> get_perm_expression(permutation p) const;

    InfInt get_group_size() const;

private:
    void make_schreier_gen();

    void filter(std::set<permutation>& stab_gen);

private:
    std::size_t n;
    std::vector<permutation> group_gen;
    struct stab {
        uint32_t base;
        schreier_tree tree;
        std::set<uint32_t> orbit;
        std::vector<permutation> gen;

    };
    std::vector<stab_node> chain;
};
}
