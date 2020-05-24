#pragma once

#include <vector>
#include <numeric>
#include <cstdint>
#include <iostream>
#include <set>
#include <map>

namespace schreier_sims {
    class permutation;
}

std::ostream& operator<< (std::ostream& os, const schreier_sims::permutation& a);

bool operator< (const schreier_sims::permutation& a, const schreier_sims::permutation& b);

namespace schreier_sims {

    class permutation {
    public:
        permutation(std::size_t) noexcept;

        permutation(const std::vector<uint32_t>&) noexcept;

        permutation(const permutation&) noexcept;

        permutation(permutation&&) noexcept;

        bool operator== (const permutation&) const noexcept;

        bool operator!= (const permutation&) const noexcept;

        permutation& operator= (const permutation&) noexcept;

        permutation& operator= (permutation&&) noexcept;

        permutation operator* (const permutation&) const noexcept;

        permutation& operator*= (const permutation&) noexcept;

        uint32_t operator* (uint32_t) const noexcept;

        permutation inv() const noexcept;

        static permutation id(std::size_t n_);

        friend std::ostream& (::operator<<) (std::ostream& os, const permutation& a);

        friend bool (::operator<) (const permutation& a, const permutation& b);

    private:
        std::vector<uint32_t> storage;
        std::size_t n;
    };
}
