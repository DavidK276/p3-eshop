//
// Created by david on 13.12.2022.
//

#include "OrderItem.h"

OrderItem::OrderItem(Product *product0, const unsigned int quantity0) : product(product0), quantity(quantity0) {}

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
    if (this->product == nullptr) {
        return (std::string &) "";
    }
    return this->product->getName();
}
