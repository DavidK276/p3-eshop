//
// Created by david on 12.12.2022.
//

#ifndef ESHOP_INVENTORY_H
#define ESHOP_INVENTORY_H

#include "Product.h"
#include <vector>

class Inventory {
    std::vector<Product> products;
public:
    Inventory() = default;

    size_t productCount() const;

    void loadFromFile(std::string &filePath);

    void saveToFile(std::string &filePath) const;

    const Product *getProduct(const std::string &name) const;

    const Product *getProduct(const size_t index) const;

    // TODO: define proper return type
    bool insertProduct(Product &product);

    std::vector<Product> filterByPrice(unsigned int price) const;

    auto filterByPriceRange(unsigned int minPrice, unsigned int maxPrice) const;

};


#endif //ESHOP_INVENTORY_H
