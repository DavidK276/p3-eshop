//
// Created by david on 12.12.2022.
//

#include "Product.h"

Product::Product(const std::string &name0, unsigned int price0) : name(name0), category("Uncategorized"), price(price0) {}

Product::Product(const std::string &name0, unsigned int price0, const std::string &category0) : name(name0),
                                                                                         category(category0),
                                                                                         price(price0) {}
