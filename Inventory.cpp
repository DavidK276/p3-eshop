//
// Created by david on 12.12.2022.
//

#include "Inventory.h"
#include <algorithm>
#include <iterator>

size_t Inventory::productCount() const {
    return this->products.size();
}

const Product *Inventory::getProduct(const std::string &name) const {
    auto iter = this->products.end();
    while (iter != this->products.end()) {
        if (iter->getName() == name) {
            return iter.base();
        }
    }
    return nullptr;
}

const Product *Inventory::getProduct(const size_t index) const {
    return &this->products.at(index);
}

bool Inventory::insertProduct(Product &product) {
    auto p = this->getProduct(product.getName());
    if (p != nullptr) {
        return false;
    }
    auto first = this->products.begin();
    auto last = this->products.end();
    auto len = std::distance(first, last);
    while (len > 0) {
        auto half = len >> 1;
        auto middle = first;
        std::advance(middle, half);
        if (middle->getPrice() < product.getPrice()) {
            first = ++middle;
            len -= half + 1;
        } else {
            len = half;
        }
    }
    this->products.insert(first, product);
    return true;
}

std::vector<Product> Inventory::filterByPrice(unsigned int price) const {
    std::vector<Product> result;
    auto p = this->filterByPriceRange(price, price);
    for (auto iter = p.first; iter != p.second; iter++) {
        if (iter->getPrice() == price) {
            result.push_back(*iter.base());
        }
    }

    return result;
}

std::pair<std::vector<Product>::const_iterator, std::vector<Product>::const_iterator>
Inventory::filterByPriceRange(unsigned int minPrice, unsigned int maxPrice) const {
    auto first = this->products.begin();
    auto last = this->products.end();
    auto len = std::distance(first, last);
    while (len > 0) {
        auto half = len >> 1;
        auto middle = first;
        std::advance(middle, half);
        if (middle->getPrice() < minPrice) {
            first = ++middle;
            len -= half + 1;
        } else {
            len = half;
        }
    }
    auto minProduct = first;

    first = this->products.begin();
    last = this->products.end();
    len = std::distance(first, last);
    while (len > 0) {
        auto half = len >> 1;
        auto middle = first;
        std::advance(middle, half);
        if (maxPrice >= middle->getPrice()) {
            first = ++middle;
            len -= half + 1;
        } else {
            len = half;
        }
    }
    auto maxProduct = first;
    return {minProduct, maxProduct};
}