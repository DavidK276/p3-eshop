//
// Created by david on 13.12.2022.
//

#ifndef ESHOP_ORDER_H
#define ESHOP_ORDER_H

#include "OrderItem.h"
#include <list>

enum class OrderStatus {
    PROCESSING, SHIPPED
};

class Order {
    std::list<OrderItem> items;
    OrderStatus status;
    std::string address;
public:
    Order();

    ~Order() = default;

    const OrderItem *getItem(size_t index) const;

    void addItem(const OrderItem &item);

    OrderStatus getStatus() const { return this->status; }

    void setStatus(OrderStatus status0) { this->status = status0; }

    const std::string &getAddress() const { return this->address; }

    void setAddress(const std::string &address0) { this->address = address0; }

    void replaceItems(const Inventory &inventory);

    void shipOrder(const Inventory &inventory);

    void saveItemsToFile(const std::string &filePath) const;
};


#endif //ESHOP_ORDER_H
