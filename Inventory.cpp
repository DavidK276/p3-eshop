//
// Created by david on 12.12.2022.
//

#include "Inventory.h"

#define MAGIC_NUMBER "ZnamaFEshop1"

Inventory::~Inventory() {
    for (const auto &product: this->productNameMap) {
        delete product.second;
    }
}

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
void Inventory::insertProduct(const Product &product) {
    auto p = (*this)[product.getName()];
    if (p != nullptr) {
        throw std::invalid_argument("Product already exists");
    }
    auto newProduct = new Product(product);
    auto first = this->products.begin();
    auto last = this->products.end();
    auto len = std::distance(first, last);
    while (len > 0) {
        auto half = len >> 1;
        auto middle = first;
        std::advance(middle, half);
        if (middle->getPrice() < newProduct->getPrice()) {
            first = ++middle;
            len -= half + 1;
        } else {
            len = half;
        }
    }
    this->products.insert(first, *newProduct);
    this->productNameMap.insert({newProduct->getName(), newProduct});
}

void Inventory::insertProducts(std::initializer_list<Product> productList) {
    for (const auto &product: productList) {
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

/*
 * Loads products from file. Throws exception when inventory is not empty or when there is a problem with the file.
 */
void Inventory::loadFromFile(const std::string &filePath) {
    if (!std::empty(this->products)) {
        throw std::runtime_error("Inventory is not empty");
    }
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }
    constexpr auto l = std::char_traits<char>::length(MAGIC_NUMBER);
    char magicNumber[l + 1];
    file.read(magicNumber, l + 1);
    if (!file.good() || std::strcmp(magicNumber, MAGIC_NUMBER) != 0) {
        throw std::runtime_error("Invalid file format");
    }
    int productCount;
    file >> productCount;
    boost::archive::binary_iarchive archive(file);
    for (int i = 0; i < productCount; i++) {
        Product newProduct;
        archive >> newProduct;
        this->insertProduct(newProduct);
    }
    file.close();
}

/*
 * Saves products to file. Throws exception when the file can't be opened.
 */
void Inventory::saveToFile(const std::string &filePath) const {
    std::ofstream file(filePath, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    file << MAGIC_NUMBER << '\0';
    file << this->productCount();
    boost::archive::binary_oarchive archive(file);
    for (const auto& product: this->getAllProducts()) {
        archive << product;
    }
    file.close();
}

/*
 * Clears all products from inventory.
 */
void Inventory::clear() {
    for (const auto &product: this->productNameMap) {
        delete product.second;
    }
    this->products.clear();
    this->productNameMap.clear();
}
