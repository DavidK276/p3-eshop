//
// Created by david on 13.12.2022.
//

#include "Order.h"

Order::Order() : status(OrderStatus::PROCESSING){}

const OrderItem *Order::getItem(size_t index) const {
    if (this->items.size() <= index) {
        return nullptr;
    }
    return &this->items[index];
}

void Order::addItem(const OrderItem &item) {
    this->items.push_back(item);
}
