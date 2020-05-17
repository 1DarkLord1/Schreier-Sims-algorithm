#include "schreier_tree.h"

using namespace schreier_sims;

schreier_tree::schreier_tree(const std::vector<permutation>& perms_, uint32_t base_) noexcept: perms(perms_), base(base_) {
    build_tree(base);
}

void schreier_tree::build_tree(uint32_t elem) noexcept {
    for(auto& p: perms) {
        uint32_t new_elem = p * elem;
        if(tree.find(new_elem) == tree.end()) {
            continue;
        }
        tree[new_elem] = {p, elem};
        build_tree(new_elem);
    }
}

std::set<uint32_t> schreier_tree::get_orbit() const noexcept {
    std::set<uint32_t> orbit;
    for(auto const& [elem, edge]: par) {
        orbit.insert(elem);
    }
    return orbit;
}

permutation schreier_tree::get_perm(uint32_t elem) const {
    if(tree.find(elem) == tree.end()) {
        throw std::runtime_error("Access to the element in schreier tree error.")
    }
    permutation perm(tree[elem].perm.size());
    while(tree.find(elem) != tree.end()) {
        perm *= tree[elem].perm;
        elem = tree[elem].anc;
    }
    return perm.inv();
}
