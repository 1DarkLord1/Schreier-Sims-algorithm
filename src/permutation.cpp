#pragma once

#include "permutation.h"

using namespace shraer_sims;


permutation::permutation(const std::vector<uint32_t>& _storage) noexcept: storage(_storage), n(_storage.size()) {}


permutation& permutation::operator= (const permutation& _perm) noexcept {
    perm = _perm.storage;
    return *this;
}


permutation::permutation(const permutation& _perm) noexcept {
    *this = _perm;
}


permutation& permutation::operator*= (const permutation& _perm) noexcept {
    for(std::size_t i = 0; i < n; i++) {
        storage[i] = storage[_perm.storage[i]];
    }
    return *this;
}


permutation permutation::operator* (const permutation& _perm) const noexcept {
    permutation new_perm = *this;
    return new_perm *= _perm;
}


std::vector<uint32_t> permutation::operator* (const std::vector<uint32_t>& _tuple) const noexcept {
    return (*this * permutation(_tuple)).storage;
}

permutaton permutation::inv() const noexcept {
    permutation new_perm = *this;
    for(std::size_t i = 0; i < n; i++) {
        new_perm.storage[storage[i]] = i;
    }
    return new_perm;
}
