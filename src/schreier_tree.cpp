#include "schreier_tree.h"

using namespace schreier_sims;

schreier_tree::schreier_tree(const std::vector<permutation>& perms_, std::size_t n_, uint32_t base_):
perms(perms_), n(n_), base(base_) {
    if(perms.size() == 0) {
        throw std::logic_error("Empty set of generator.");
    }
    build_tree(base);
}

void schreier_tree::build_tree(uint32_t elem) noexcept {
    std::queue<uint32_t> q;
    q.push(elem);
    while(!q.empty()) {
        elem = q.front();
        q.pop();
        for(std::size_t i = 0; i < perms.size(); i++) {
            uint32_t new_elem = perms[i] * elem;
            if(tree.find(new_elem) != tree.end() || elem == new_elem || base == new_elem) {
                continue;
            }
            tree.insert({new_elem, edge{i, elem}});
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
    std::vector<std::pair<int, std::size_t>> dec;
    try {
        dec = get_decomp(elem);
    }
    catch(...) {
        throw;
    }
    permutation perm(n);
    for(auto& p: dec) {
        perm *= (p.first == -1 ? perms[p.second].inv(): perms[p.second]);
    }
    return perm;
}

std::vector<std::pair<int, std::size_t>> schreier_tree::get_decomp(uint32_t elem) const {
    if(elem == base) {
        return {{1, 0}, {-1, 0}};
    }
    if(tree.find(elem) == tree.end()) {
        throw std::runtime_error("Access to the element in schreier tree error.");
    }
    std::vector<std::pair<int, std::size_t>> dec;
    while(tree.find(elem) != tree.end()) {
        dec.push_back({1, tree.at(elem).idx});
        elem = tree.at(elem).anc;
    }
    return dec;
}

std::size_t schreier_tree::size() const noexcept {
    return tree.size() + 1;
}
