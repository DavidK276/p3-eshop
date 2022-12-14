//
// Created by david on 13.12.2022.
//

#include "OrderItem.h"

OrderItem::OrderItem(const Product &product0, const unsigned int quantity0) : product(product0), quantity(quantity0) {}

const Product *OrderItem::getProduct() const {
    return &this->product;
}

std::string OrderItem::getProductName() const {
    return this->product.getName();
}
