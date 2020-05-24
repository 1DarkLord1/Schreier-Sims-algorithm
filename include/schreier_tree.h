#pragma once

#include "permutation.h"
#include <queue>
#include <algorithm>

namespace schreier_sims {
class schreier_tree {
public:
    schreier_tree(const std::vector<permutation>& perms_, std::size_t n_, uint32_t base_);

    std::set<uint32_t> get_orbit() const noexcept;

    std::vector<std::pair<int, std::size_t>> get_decomp(uint32_t elem) const;

    permutation get_perm(uint32_t elem) const;

    std::size_t size() const noexcept;

private:
    void build_tree(uint32_t elem) noexcept;

private:
    struct edge {
        std::size_t idx;
        uint32_t anc;
    };
    std::map<uint32_t, edge> tree;
    std::vector<permutation> perms;
    std::size_t n;
    uint32_t base;
};
}
