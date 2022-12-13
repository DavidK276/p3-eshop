//
// Created by david on 13.12.2022.
//

#ifndef ESHOP_ORDERITEM_H
#define ESHOP_ORDERITEM_H

#include "Inventory.h"


class OrderItem {
    Product product;
    unsigned int quantity;
public:
    OrderItem(const Product &product0, unsigned int quantity0);

    unsigned int getQuantity() const { return this->quantity; }

    const Product *getProduct() const;
};


#endif //ESHOP_ORDERITEM_H