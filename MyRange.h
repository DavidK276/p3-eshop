//
// Created by david on 13.12.2022.
//

#ifndef ESHOP_MYRANGE_H
#define ESHOP_MYRANGE_H

#include "Product.h"
#include <vector>

template<typename T>
class MyRange {
    using RangeIter = typename std::vector<T>::const_iterator;
    RangeIter first;
    RangeIter final;
    RangeIter last;
public:
    MyRange() = delete;

    [[maybe_unused]] MyRange(MyRange::RangeIter begin, MyRange::RangeIter end) : first(begin), last(end) {
        this->final = std::prev(end);
    }

    RangeIter getFirst() const { return this->first; }

    RangeIter getFinal() const { return this->final; }

    long getCount() const {
        return std::distance(this->first, this->last);
    }

    RangeIter begin() const { return this->first; }

    RangeIter end() const { return this->last; }
};


#endif //ESHOP_MYRANGE_H
