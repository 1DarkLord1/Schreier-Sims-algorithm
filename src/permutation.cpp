#include "permutation.h"

using namespace schreier_sims;

permutation::permutation(std::size_t n_) noexcept: storage(n_), n(n_) {
    iota(storage.begin(), storage.end(), 0);
}

permutation::permutation(const std::vector<uint32_t>& storage_) noexcept: storage(storage_), n(storage_.size()) {}

bool permutation::operator== (const permutation& perm) const noexcept {
    return (storage == perm.storage);
}

bool permutation::operator!= (const permutation& perm) const noexcept {
    return !(*this == perm);
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

permutation& permutation::operator*= (const permutation& perm) noexcept {
    *this = *this * perm;
    return *this;
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

bool permutation::operator< (const permutation& that) const {
    return storage < that.storage;
}

permutation permutation::id(std::size_t n_) {
    return permutation(n_);
}
