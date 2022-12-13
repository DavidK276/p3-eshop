//
// Created by david on 12.12.2022.
//

#include "Product.h"

Product::Product(const std::string &name0, const Price &price0) : category("Uncategorized"), stock(0) {
    this->name = name0;
    this->price = price0;
}

Product::Product(const std::string &name0, const Price &price0, const std::string &category0) : stock(0) {
    this->name = name0;
    this->category = category0;
    this->price = price0;
}
