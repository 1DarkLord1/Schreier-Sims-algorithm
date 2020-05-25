#include "stab_chain.h"


using namespace schreier_sims;

stab_chain::stab_chain(const std::vector<permutation>& group_gen_, const std::vector<uint32_t>& base_elems, std::size_t n_):
n(n_), group_gen(group_gen_) {
    for(std::size_t i = 0; i < base_elems.size(); i++) {
        uint32_t cur_base = base_elems[i];
        chain.emplace_back(cur_base, schreier_tree(i == 0 ? group_gen: chain[i - 1].gen, n, cur_base));
        chain[i].orbit = std::move(chain[i].tree.get_orbit());
        chain[i].gen = std::move(make_schreier_gen(i == 0 ? group_gen: chain[i - 1].gen, chain[i].orbit, chain[i].tree));
    }
}


stab_chain stab_chain::get_stab_chain(std::size_t i) const noexcept {
    if(i == 0) {
        return *this;
    }
    stab_chain new_chain = *this;
    new_chain.chain.erase(new_chain.chain.begin(), new_chain.chain.begin() + i);
    new_chain.group_gen = chain[i - 1].gen;
    return new_chain;
}

std::set<uint32_t> stab_chain::get_orbit(std::size_t i) const noexcept {
    return chain[i].orbit;
}

std::vector<permutation> stab_chain::get_gen(std::size_t i) const noexcept {
    return chain[i].gen;
}

std::vector<permutation> stab_chain::get_strong_gen() const noexcept {
    std::set<permutation> strong_gen(group_gen.begin(), group_gen.end());
    for(auto& st: chain) {
        strong_gen.insert(st.gen.begin(), st.gen.end());
    }
    return std::vector<permutation>(strong_gen.begin(), strong_gen.end());
}


std::size_t stab_chain::len() const noexcept {
    return chain.size();
}

void stab_chain::filter(std::set<permutation>& stab_gen_set, const std::set<uint32_t>& orbit) const noexcept {
    if(stab_gen_set.size() == 1) {
        return;
    }
    std::set<permutation> small_set;
    std::vector<std::map<uint32_t, permutation>> gen_base(n);
    for(auto perm: stab_gen_set) {
        for(uint32_t orb_e: orbit) {
            uint32_t new_e = perm * orb_e;
            if(new_e != orb_e) {
                if(gen_base[orb_e].find(new_e) != gen_base[orb_e].end()) {
                    perm = perm.inv() * gen_base[orb_e].at(new_e);
                }
                else {
                    gen_base[orb_e][new_e] = perm;
                    small_set.insert(perm);
                }
            }
        }
    }
    stab_gen_set.swap(small_set);
}

std::vector<permutation> stab_chain::make_schreier_gen(const std::vector<permutation>& anc_gen, const std::set<uint32_t>& orbit, const schreier_tree& tree) const noexcept {
    std::set<permutation> stab_gen_set;
    for(auto& perm: anc_gen) {
        for(uint32_t orb_e: orbit) {
            stab_gen_set.insert(tree.get_perm(perm * orb_e).inv() * perm * tree.get_perm(orb_e));
        }
    }
    filter(stab_gen_set, orbit);
    return std::vector<permutation>(stab_gen_set.begin(), stab_gen_set.end());
}

bool stab_chain::contain(permutation p) const noexcept {
    for(auto& st: chain) {
        uint32_t elem = p * st.base;
        permutation tree_p(n);
        try {
            tree_p = st.tree.get_perm(elem).inv();
        }
        catch(std::runtime_error e) {
            return false;
        }
        p = tree_p * p;
    }
    return (p == permutation::id(n));
}

std::vector<std::pair<int, std::size_t>> stab_chain::get_perm_expression(permutation p) const {
    std::vector<std::pair<int, std::size_t>> expr;
    for(auto& st: chain) {
        if(st.gen == std::vector<permutation>{permutation::id(n)}) {
            break;
        }
        uint32_t elem = p * st.base;
        std::vector<std::pair<int, std::size_t>> decomp = st.tree.get_decomp(elem);
        expr.insert(expr.end(), decomp.begin(), decomp.end());
    }
    return expr;
}

InfInt stab_chain::get_group_size() const noexcept {
    InfInt sz = 1;
    for(auto& st: chain) {
        sz *= st.orbit.size();
    }
    return sz;
}
