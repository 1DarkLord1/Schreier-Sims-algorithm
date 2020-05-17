#include "permutation.h"

using namespace shraer_sims;

permutation::permutation(std::size_t n_) noexcept: n(n_) {
    storage.resize(n);
    iota(storage.begin(), storage.end(), 0);
}

permutation::permutation(const std::vector<uint32_t>& storage_) noexcept: storage(storage_), n(storage_.size()) {}

bool permutation::operator== (const permutation& perm) noexcept {
    return (storage == perm.storage);
}

permutation& permutation::operator= (const permutation& perm) noexcept {
    n = perm.n;
    storage = perm.storage;
    return *this;
}

permutation& permutation::operator= (permutation&& perm) noexcept {
    n = perm.n;
    storage = std::move(perm.storage);
    return *this;
}


permutation::permutation(const permutation& perm) noexcept {
    *this = perm;
}

permutation::permutation(permutation&& perm) noexcept {
    *this = std::move(perm);
}


permutation permutation::operator* (const permutation& perm) const noexcept {
    permutation new_perm = *this;
    for(std::size_t i = 0; i < n; i++) {
        new_perm.storage[i] = storage[perm.storage[i]];
    }
    return new_perm;
}


uint32_t permutation::operator* (uint32_t num) const noexcept {
    return storage[num];
}

permutation permutation::inv() const noexcept {
    permutation new_perm = *this;
    for(std::size_t i = 0; i < n; i++) {
        new_perm.storage[storage[i]] = i;
    }
    return new_perm;
}

std::ostream& operator<< (std::ostream& os, const permutation& a) {
    for(auto x: a.storage) {
        os << x << ' ';
    }
    return os;
}
