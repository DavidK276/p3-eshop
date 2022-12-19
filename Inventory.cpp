//
// Created by david on 12.12.2022.
//

#include "Inventory.h"
#include <algorithm>


/*
 * Count of all products in inventory.
 */
size_t Inventory::productCount() const {
    return this->products.size();
}

/*
 * Get pointer to product by product name. Throws exception on failure.
 */
Product *Inventory::getProduct(const std::string &name) const {
    auto product = (*this)[name];
    if (product == nullptr) {
        throw std::invalid_argument("Product not found");
    }
    return product;
}

/*
 * Get pointer to product by its index in the vector. Used for testing. Returns nullptr on invalid index.
 */
const Product *Inventory::getProduct(const size_t index) const {
    if (index >= this->products.size()) {
        return nullptr;
    }
    return &this->products[index];
}

/*
 * Returns an iterator through all products.
 */
MyRange<Product> Inventory::getAllProducts() const {
    return {this->products.begin(), this->products.end()};
}

/*
 * Inserts the product into the inventory.
 * Uses binary search to find the appropriate position in the vector.
 */
void Inventory::insertProduct(Product product) {
    auto p = (*this)[product.getName()];
    if (p != nullptr) {
        throw std::invalid_argument("Product already exists");
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
    this->productNameMap.insert({product.getName(), &product});
}

void Inventory::insertProducts(std::initializer_list<Product> productList) {
    for (const auto& product : productList) {
        this->insertProduct(product);
    }
}

/*
 * Updates the data of an existing product. Throws exception on failure.
 */
void Inventory::updateProduct(Product &product) const {
    auto p = (*this)[product.getName()];
    if (p == nullptr) {
        throw std::invalid_argument("Product not found");
    }
    *p = product;
}

/*
 * Updates the data of an existing product. Inserts the product if it does not exist.
 */
void Inventory::upsertProduct(Product &product) {
    try {
        this->insertProduct(product);
    }
    catch (std::invalid_argument &) {
        this->updateProduct(product);
    }
}

/*
 * Returns an iterator through all products with the specified price.
 */
MyRange<Product> Inventory::filterByPrice(const Product::Price &price) const {
    return this->filterByPriceRange(price, price);
}

/*
 * Returns an iterator through all products with the specified price range, minPrice and maxPrice included.
 * Uses binary search to find the positions.
 */
MyRange<Product> Inventory::filterByPriceRange(const Product::Price &minPrice, const Product::Price &maxPrice) const {
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

/*
 * Return a vector of products with the specified category.
 */
std::vector<Product> Inventory::filterByCategory(const std::string &category) const {
    std::vector<Product> result(this->products.size());
    auto hasCategory = [&category](const Product &product) {
        return product.getCategory() == category;
    };
    auto final = std::copy_if(this->products.begin(), this->products.end(), result.begin(), hasCategory);
    result.erase(final, result.end());
    return result;
}

/*
 * Get pointer to product by product name. Returns nullptr on failure.
 */
Product *Inventory::operator[](const std::string &name) const {
    auto product = this->productNameMap.find(name);
    if (this->productNameMap.find(name) != this->productNameMap.end()) {
        return product->second;
    }
    return nullptr;
}