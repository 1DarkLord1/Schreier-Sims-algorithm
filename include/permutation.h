#pragma once

namespace shraer_sims {

    class permutation {
    public:
        permutation(const std::vector<uint32_t>& _storage) noexcept;

        permutation(const permutation& _perm) noexcept;

        permutation& operator= (const permutation& _perm) noexcept;

        permutation& operator*= (const permutation& _perm) noexcept;

        permutation operator* (const permutation& _perm) const noexcept;

        std::vector<uint32_t> operator* (const std::vector<uint32_t>& _tuple) const noexcept;

        permutation inv() const noexcept;

    private:
        std::vector<uint32_t> storage;
        std::size_t n;
    };
}
