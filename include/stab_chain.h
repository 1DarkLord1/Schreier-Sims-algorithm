pragma once

#include "permutation.h"
#include "schreier_tree.h"

namespace schreier_sims {
class stab_chain {
public:
    stab_chain(const std::vector<permutation>& gen_);

    stab_chain(const stab_chain&);

    stab_chain(stab_chain&&);

    stab_chain& operator= (const stab_chain&);

    stab_chain& operator= (stab_chain&&);

    const stab_chain& get_stab_chain(std::size_t num) const noexcept;

    std::set<uint32_t> get_orbit() const;

    std::vector<permutation> get_gen(std::size_t num) const;

    std::size_t len() const noexcept;

private:
    void make_schreier_gen();

    void filter();

private:
    std::size_t n, chain_len = 1;
    uint32_t base;
    std::vector<permutation> stab_gen;
    schreier_tree tree;
    std::unique_ptr<stab_chain> next;
};
}
