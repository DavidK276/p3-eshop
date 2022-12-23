//
// Created by david on 12.12.2022.
//

#include "Product.h"

#include <utility>

Product::Product(Product &&product0) : name(std::move(product0.name)), category(std::move(product0.category)),
                                       price(std::move(product0.price)), stock(product0.stock) {
    product0.category = NO_CATEGORY;
}

Product::Product(std::string name0, Price price0) : name(std::move(name0)), category(NO_CATEGORY),
                                                    price(std::move(price0)), stock(0) {}

Product::Product(std::string name0, std::string category0, Price price0, unsigned int stock0)
        : name(std::move(name0)), category(std::move(category0)), price(std::move(price0)), stock(stock0) {}

Product &Product::operator=(const Product &product0) = default;

bool Product::operator==(const Product &product0) const {
    return product0.name == this->name && product0.category == this->category && product0.price == this->price &&
           product0.stock == this->stock;
}
