//
// Created by david on 12.12.2022.
//

#ifndef ESHOP_INVENTORY_H
#define ESHOP_INVENTORY_H

#include "Product.h"
#include "MyRange.h"

class Inventory {
    std::vector<Product> products;
public:
    Inventory() = default;

    size_t productCount() const;

    void loadFromFile(std::string &filePath);

    void saveToFile(std::string &filePath) const;

    const Product *getProduct(const std::string &name) const;

    const Product *getProduct(size_t index) const;

    // TODO: define proper return type
    bool insertProduct(Product &product);

    MyRange<Product> filterByPrice(const Product::Price &price) const;

    MyRange<Product> filterByPriceRange(const Product::Price &minPrice, const Product::Price &maxPrice) const;

};


#endif //ESHOP_INVENTORY_H
