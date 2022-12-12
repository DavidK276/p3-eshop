//
// Created by david on 12.12.2022.
//

#ifndef ESHOP_PRODUCT_H
#define ESHOP_PRODUCT_H

#include <iostream>


class Product {
    std::string name;
    std::string category;
    unsigned int price;
public:
    Product(const std::string &name0, unsigned int price0);

    Product(const std::string &name0, unsigned int price0, const std::string &category0);

    std::string getName() const { return this->name; }

    void setName(std::string &name0) { this->name = name0; }

    std::string getCategory() const { return this->category; }

    void setCategory(std::string &category0) { this->category = category0; }

    unsigned int getPrice() const { return this->price; }

    float getPriceFloat() const { return static_cast<float>(this->price) / 100; }

    void setPrice(unsigned int price0) { this->price = price0; }

};


#endif //ESHOP_PRODUCT_H
