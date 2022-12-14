//
// Created by david on 12.12.2022.
//

#include "Product.h"

Product::Product(Product &&product0) : name(std::move(product0.name)), category(std::move(product0.category)),
                                       price(std::move(product0.price)), stock(product0.stock) {
    product0.category = NO_CATEGORY;
}

Product::Product(const std::string &name0, const Price &price0) : category(NO_CATEGORY), stock(0) {
    this->name = name0;
    this->price = price0;
}

Product::Product(const std::string &name0, const std::string &category0, const Price &price0, unsigned int stock0)
        : stock(stock0) {
    this->name = name0;
    this->category = category0;
    this->price = price0;
}

bool Product::operator==(const Product &product0) const {
    return product0.name == this->name && product0.category == this->category && product0.price == this->price &&
           product0.stock == this->stock;
}
