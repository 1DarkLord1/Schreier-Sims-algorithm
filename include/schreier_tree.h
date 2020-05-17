#pragma once

namespace schreier_sims {
class schreier_tree {
public:
    schreier_tree(const std::vector<permutation>& perms_, uint32_t base_) noexcept;




private:
    struct node {
        const permutation& perm;
        uint32_t elem;
    };
    std::vector<node> par;
    const std::vector<permutation>& perms;
    uint32_t base;
};
}
