//
// Created by david on 12.12.2022.
//

#ifndef ESHOP_PRODUCT_H
#define ESHOP_PRODUCT_H

#include <iostream>
#include <boost/multiprecision/cpp_dec_float.hpp>


class Product {
public:
    typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<16>> Price;
private:
    std::string name;
    std::string category;
    Price price;
public:
    Product(const std::string &name0, const Price &price0);

    Product(const std::string &name0, const Price &price0, const std::string &category0);

    std::string getName() const { return this->name; }

    void setName(std::string &name0) { this->name = name0; }

    std::string getCategory() const { return this->category; }

    void setCategory(std::string &category0) { this->category = category0; }

    Price getPrice() const { return this->price; }

    void setPrice(Price &price0) { this->price = price0; }
};


#endif //ESHOP_PRODUCT_H
