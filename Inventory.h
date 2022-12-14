//
// Created by david on 12.12.2022.
//

#ifndef ESHOP_INVENTORY_H
#define ESHOP_INVENTORY_H

#include "Product.h"
#include "MyRange.h"
#include <map>
#include <memory>
#include <algorithm>

class Inventory {
    std::vector<Product> products;
    std::map<std::string, Product *> productNameMap;
public:
    Inventory() = default;

    ~Inventory();

    size_t productCount() const;

    void loadFromFile(const std::string &filePath);

    void saveToFile(const std::string &filePath) const;

    void clear();

    Product *getProduct(const std::string &name) const;

    const Product *getProduct(size_t index) const;

    MyRange<Product> getAllProducts() const;

    void insertProduct(const Product &product);

    void insertProducts(std::initializer_list<Product> productList);

    void updateProduct(Product &product) const;

    void upsertProduct(Product &product);

    MyRange<Product> filterByPrice(const Product::Price &price) const;

    MyRange<Product> filterByPriceRange(const Product::Price &minPrice, const Product::Price &maxPrice) const;

    std::vector<Product> filterByCategory(const std::string &category) const;

    Product *operator[](const std::string &name) const;
};


#endif //ESHOP_INVENTORY_H
