#pragma once

#include "permutation.h"
#include <queue>

namespace schreier_sims {
class schreier_tree {
public:
    schreier_tree(const std::vector<permutation>& perms_, std::size_t n_, uint32_t base_) noexcept;

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
    const std::vector<permutation>& perms;
    std::size_t n;
    uint32_t base;
};
}
