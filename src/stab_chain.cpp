#include "stab_chain.h"


using namespace schreier_sims;

stab_chain(const std::vector<permutation>& group_gen, const std::vector<uint32_t>& base_elems, std::size_t n_):
n(n_) {
    for(std::size_t i = 0; i < base_elems.size(); i++) {
        uint32_t cur_base = base_elem[i];
        const std::vector<permutation>& anc_gen = (i == 0 ? grup_gen: chain[i - 1].gen);
        chain.emplace_back(cur_base, tree(anc_gen, n, cur_base));
        chain[i].orbit = std::move(chain[i].tree.get_orbit());
        chain[i].gen = std::move(make_schreier_gen(anc_gen, chain[i].orbit));
    }
}


stab_chain stab_chain::get_stab_chain(std::size_t num) const noexcept {
    std::shared_ptr<stab_chain> cur_stab = std::make_shared<stab_chain>(*this);
    for(std::size_t i = 0; i < num; i++) {
        cur_stab = cur_stab->next;
    }
    return const_cast<const stab_chain&>(*cur_stab);
}

std::set<uint32_t> stab_chain::get_orbit(std::size_t i) const {
    auto& chain = get_stab_chain(i);
    return chain.orbit;
}

std::vector<permutation> stab_chain::get_gen(std::size_t num) const {
    auto& chain = get_stab_chain(num);
    return chain.gen;
}

std::vector<permutation> stab_gen::get_strong_gen() const {
    std::set<permutation> strong_gen;
    std::shared_ptr<stab_chain> cur_stab = std::make_shared<stab_chain>(*this);
    while(cur_stab->next) {
        strong_gen.insert(cur_stab->anc_gen.begin(), cur_stab->anc_gen.end());
        cur_stab = cur_stab->next;
    }
    strong_gen.insert(cur_stab->anc_gen.begin(), cur_stab->anc_gen.end());
    return std::vector<permutation>(strong_gen.begin(), strong_gen.end());
}


std::size_t stab_chain::len() const noexcept {
    return chain_len;
}


void stab_chain::filter(std::set<permutation>& stab_gen_set) {
    std::set<permutation> small_set;
    std::vector<std::map<uint32_t, permutation>> gen_base;
    for(auto perm: stab_gen_set) {
        for(uint32_t orb_e: orbit) {
            uint32_t new_e = perm * orb_e;
            if(new_e != orb_e) {
                if(gen_base[orb_e].find(new_e) != gen_base[orb_e].end()) {
                    perm = perm.inv() * gen_base[orb_e].at(orb_e);
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

std::vector<permutation> stab_chain::make_schreier_gen(const std::vector<permutation>& anc_gen, const std::set<permutation>& orbit) {
    std::set<permutation> stab_gen_set;
    for(auto& perm: anc_gen) {
        for(auto& orb_e: orbit) {
            stab_gen_set.insert(tree.get_perm(perm * orb_e).inv() * perm * tree.get_perm(orb_e));
        }
    }
    filter(stab_gen_set);
    return std::vector<permutaation>(stab_gen_set.begin(), stab_gen_set.end());
}

bool stab_chain::contain(permutation p) const noexcept {
    std::shared_ptr<stab_chain> cur_stab = std::make_shared<stab_chain>(*this);
    while(cur_stab->next) {
        uint32_t elem = p * cur_stab->base;
        permutation tree_p(n);
        try {
            tree_p = cur_stab->tree.get_perm(elem).inv();
        }
        catch(std::runtime_error e) {
            return false;
        }
        p = tree_p * p;
        cur_stab = cur_stab->next;
    }
    return (p == permutation::id(n));
}

std::vector<std::pair<int, std::size_t>> stab_chain::get_perm_expression(permutation p) const {
    std::vector<std::pair<int, std::size_t>> expr;
    std::shared_ptr<stab_chain> cur_stab = std::make_shared<stab_chain>(*this);
    while(cur_stab->next) {
        uint32_t elem = p * cur_stab->base;
        std::vector<std::pair<int, std::size_t>> decomp = cur_stab->tree.get_decomp(elem);
        expr.insert(expr.end(), decomp.begin(), decomp.end());
        cur_stab = cur_stab->next;
    }
    return expr;
}

InfInt stab_chain::get_group_size() const {
    InfInt sz = 1;
    std::shared_ptr<stab_chain> cur_stab = std::make_shared<stab_chain>(*this);
    while(cur_stab->next) {
        sz *= cur_stab->orbit.size();
        cur_stab = cur_stab->next;
    }
    return sz;
}
