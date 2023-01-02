//
// Created by david on 12.12.2022.
//

#ifndef ESHOP_PRODUCT_H
#define ESHOP_PRODUCT_H

#include <iostream>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <stdexcept>

#define NO_CATEGORY "Uncategorized"

class Product {
public:
    using Price = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<16>>;
private:
    std::string name;
    std::string category;
    Price price;
    unsigned int stock{};
public:
    Product() = default;

    Product(const Product &product0) = default;

    Product(Product &&product0) noexcept;

    Product(std::string name0, Price price0);

    Product(std::string name0, std::string category0, Price price0, unsigned int stock0 = 0);

    ~Product() = default;

    const std::string &getName() const { return this->name; }

    void setName(const std::string &name0) { this->name = name0; }

    const std::string &getCategory() const { return this->category; }

    void setCategory(const std::string &category0) { this->category = category0; }

    Price getPrice() const { return this->price; }

    void setPrice(const Price &price0) { this->price = price0; }

    unsigned int getStock() const { return this->stock; }

    void ship(unsigned int quantity) { this->stock -= quantity; }

    void stockUp(unsigned int quantity) { this->stock += quantity; }

    bool inStock() const { return this->stock > 0; }

    Product &operator=(const Product &product0);

    bool operator==(const Product &product0) const;
};


#endif //ESHOP_PRODUCT_H
