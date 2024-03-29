//
// Created by david on 13.12.2022.
//

#include "OrderItem.h"

OrderItem::OrderItem(const Product *product0, const unsigned int quantity0) : product(product0), quantity(quantity0) {
    if (this->product == nullptr) {
        throw std::invalid_argument("Null pointer exception");
    }
}

/*
 * Returns a pointer to the contained product.
 */
const Product *OrderItem::getProduct() const {
    return this->product;
}

/*
 * Returns the name of the contained product.
 */
const std::string &OrderItem::getProductName() const {
    return this->product->getName();
}

void OrderItem::addReview(char rating0, const std::string &comment0) {
    Review::rating = rating0;
    Review::comment = comment0;
}
