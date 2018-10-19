# pragma once

#include <iostream>
#include <vector>
#include "growing_array.hpp"

namespace ptl {

enum class hyphenation_type {
    none,
    wrong,
    correct,
    past
};

inline std::ostream& operator<<(std::ostream& os, hyphenation_type type) {
    switch (type) {
    case hyphenation_type::none: return os << "hyphenation_type::none";
    case hyphenation_type::wrong: return os << "hyphenation_type::wrong";
    case hyphenation_type::correct: return os << "hyphenation_type::correct";
    case hyphenation_type::past: return os << "hyphenation_type::past";
    default: return os << "hyphenation_type::NOT_VALID_ENUM_CASE";
    }
}

template <class Tin_alph, class Twt_type, class Tval_type>
class hyphenated_word : public std::vector<Tin_alph> {
    using base = std::vector<Tin_alph>;

public:
    growing_array<hyphenation_type> type;
    growing_array<Twt_type> weight;
    growing_array<Tval_type> level;
    growing_array<bool> no_more;

    hyphenated_word() : base(), type(hyphenation_type::none), weight(1), level(0), no_more(false) {}

    hyphenated_word(const hyphenation_type& s, const Twt_type& w, const Tval_type& l, const char& e) : base(), type(s), weight(w), level(l), no_more(e) {}

    void clear() {
        base::clear();
        type.clear();
        weight.clear();
        level.clear();
        no_more.clear();
    }

    Tin_alph& operator[](const std::size_t i) {
        return base::operator[](i - 1);
    }

    void print() {
        std::cout << "hyphenated_word";
        for (typename std::vector<Tin_alph>::iterator i = this->begin(); i != this->end(); ++i)
            std::cout << " " << *i;

        std::cout << std::endl << "dots";
        for (std::size_t i = 0; i <= this->size(); ++i)
            std::cout << " " << type[i];
        std::cout << std::endl << "dotw";
        for (std::size_t i = 0; i <= this->size(); ++i)
            std::cout << " " << weight[i];
        std::cout << std::endl << "hval";
        for (std::size_t i = 0; i <= this->size(); ++i)
            std::cout << " " << level[i];
        std::cout << std::endl << "no_m";
        for (std::size_t i = 0; i <= this->size(); ++i)
            if (no_more[i])
                std::cout << " t";
            else
                std::cout << " f";
        std::cout << std::endl;
    }

};

} // namespace ptl
