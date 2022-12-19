// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "OrderItem.h"

using namespace ::testing;

TEST(TestOrderitem, CreateItem) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99);
    Product p2("iPhone SE", "Mobiles", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    Product p5("Cierne pero", 0.89);
    inv.insertProducts({p5, p4, p3, p2, p1});
    OrderItem item(inv["iPhone 13"], 1);
    ASSERT_EQ(*inv["iPhone 13"], *item.getProduct());
}

TEST(TestOrderItem, SetProduct) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99);
    Product p2("iPhone SE", "Mobiles", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    Product p5("Cierne pero", 0.89);
    inv.insertProducts({p5, p4, p3, p2, p1});
    OrderItem item(inv["iPhone 13"], 1);
    item.setProduct(inv["iPhone SE"]);
    ASSERT_EQ(*inv["iPhone SE"], *item.getProduct());
}

TEST(TestOrderItem, ItemQuantity) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99);
    Product p2("iPhone SE", "Mobiles", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    Product p5("Cierne pero", 0.89);
    inv.insertProducts({p5, p4, p3, p2, p1});
    OrderItem item(inv["iPhone 13"], 1);
    ASSERT_EQ(1, item.getQuantity());
}