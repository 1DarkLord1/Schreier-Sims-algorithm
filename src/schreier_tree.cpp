#include "schreier_tree.h"

using namespace schreier_sims;

schreier_tree::schreier_tree(const std::vector<permutation>& perms_, std::size_t n_, uint32_t base_) noexcept:
perms(perms_), n(n_), base(base_) {
    build_tree(base);
}

void schreier_tree::build_tree(uint32_t elem) noexcept {
    std::queue<uint32_t> q;
    q.push(elem);
    while(!q.empty()) {
        elem = q.front();
        q.pop();
        for(auto& p: perms) {
            uint32_t new_elem = p * elem;
            if(tree.find(new_elem) != tree.end() || elem == new_elem || base == new_elem) {
                continue;
            }
            tree.insert({new_elem, edge{p, elem}});
            q.push(new_elem);
        }
    }
}

std::set<uint32_t> schreier_tree::get_orbit() const noexcept {
    std::set<uint32_t> orbit;
    orbit.insert(base);
    for(auto it = tree.begin(); it != tree.end(); it++) {
        orbit.insert(it->first);
    }
    return orbit;
}

permutation schreier_tree::get_perm(uint32_t elem) const {
    if(elem == base) {
        return permutation(n);
    }
    if(tree.find(elem) == tree.end()) {
        throw std::runtime_error("Access to the element in schreier tree error.");
    }
    permutation perm(n);
    while(tree.find(elem) != tree.end()) {
        perm *= tree.at(elem).perm;
        elem = tree.at(elem).anc;
    }
    return perm;
}
