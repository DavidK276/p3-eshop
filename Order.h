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
    Inventory *inventory;
    std::list<OrderItem> items;
    OrderStatus status;
    std::string address;
public:
    explicit Order(Inventory *inventory0);

    ~Order() = default;

    const OrderItem *getItem(size_t index) const;

    size_t getNumberOfItems() const { return this->items.size(); }

    void addItem(const OrderItem &item);

    OrderStatus getStatus() const { return this->status; }

    void setStatus(OrderStatus status0) { this->status = status0; }

    const std::string &getAddress() const { return this->address; }

    void setAddress(const std::string &address0) { this->address = address0; }

    void replaceItems();

    void shipOrder();

    void saveItemsToFile(const std::string &filePath) const;

    bool suggestItems(const Product::Price &price);
};


#endif //ESHOP_ORDER_H
