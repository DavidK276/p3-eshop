//
// Created by david on 13.12.2022.
//

#include "Order.h"
#include <boost/range/adaptor/reversed.hpp>

Order::Order() : status(OrderStatus::PROCESSING) {}

/*
 * Retrieves the specified element from the list.
 * This is expensive and is only intended for testing.
 * Returns nullptr on failure.
 */
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

/*
 * Adds the item to the order.
 */
void Order::addItem(const OrderItem item) {
    this->items.push_back(item);
}

/*
 * Replaces out of stock items with the item of the same category and highest price.
 */
void Order::replaceItems(const Inventory &inventory) {
    for (auto iter = this->items.begin(); iter != this->items.end(); iter++) {
        if (!iter->getProduct()->inStock()) {
            auto potentialProducts = inventory.filterByCategory(iter->getProduct()->getCategory());
            bool foundSuitable = false;
            for (auto &product: boost::adaptors::reverse(potentialProducts)) {
                if (product.getStock() >= iter->getQuantity()) {
                    foundSuitable = true;
                    iter->setProduct(&product);
                    break;
                }
            }
            if (!foundSuitable) {
                this->items.erase(iter);
            }
        }
    }
}

/*
 * Replaces items, decreases stock of each item in the inventory and sets the order status to shipped.
 */
void Order::shipOrder(const Inventory &inventory) {
    this->replaceItems(inventory);
    for (const auto &item: this->items) {
        auto product = inventory.getProduct(item.getProductName());
        product->ship(item.getQuantity());
    }
    this->status = OrderStatus::SHIPPED;
}
