//
// Created by david on 13.12.2022.
//

#include "Order.h"

Order::Order() : status(OrderStatus::PROCESSING) {}

// expensive and only used for testing
const OrderItem *Order::getItem(size_t index) const {
    if (this->items.size() <= index) {
        return nullptr;
    }
    auto iter = this->items.begin();
    while (iter != this->items.end() && index > 0) {
        iter++;
        index--;
    }
    if (iter != this->items.end()) {
        return &*iter;
    }
    return nullptr;
}

void Order::addItem(const OrderItem &item) {
    this->items.push_back(item);
}

// replaces low stock items with item of same category and lowest price
void Order::replaceItems(const Inventory *inventory) {
    for (auto iter = this->items.begin(); iter != this->items.end(); iter++) {
        if (!iter->getProduct()->inStock()) {
            auto potentialProducts = inventory->filterByCategory(iter->getProduct()->getCategory());
            bool foundSuitable = false;
            for (const auto &product: potentialProducts) {
                if (product.getStock() >= iter->getQuantity()) {
                    foundSuitable = true;
                    iter->setProduct(product);
                    break;
                }
            }
            if (!foundSuitable) {
                this->items.erase(iter);
            }
        }
    }
}

void Order::shipOrder(const Inventory *inventory) {
    for (const auto &item: this->items) {
        inventory->getProduct(item.getProduct()->getName())->ship(item.getQuantity());
    }
    this->status = OrderStatus::SHIPPED;
}
