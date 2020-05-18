/*#pragma once

#include "permutation.h"
#include "schreier_tree.h"

namespace schreier_sims {
class stab_chain {
public:
    stab_chain(const std::vector<permutation>& gen_) noexcept;

    std::set<uint32_t> get_orbit() const noexcept;

    permutation get_perm(uint32_t elem) const;

private:
    void build_tree(uint32_t elem) noexcept;

private:
    struct edge {
        const permutation& perm;
        uint32_t anc;
    };
    std::map<uint32_t, edge> tree;
    const std::vector<permutation>& gen;
    std::size_t n;
    uint32_t base;
};
}*/
