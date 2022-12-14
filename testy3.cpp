// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "OrderItem.h"

using namespace ::testing;

TEST(TestOrderitem, EmptyItem) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99);
    Product p2("iPhone SE", "Mobiles", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    Product p5("Cierne pero", 0.89);
    inv.insertProduct(p1);
    inv.insertProduct(p2);
    inv.insertProduct(p3);
    inv.insertProduct(p4);
    inv.insertProduct(p5);
    OrderItem item(*inv["iPhone 13"], 1);
    ASSERT_EQ(*inv["iPhone 13"], *item.getProduct());
    ASSERT_EQ(1, item.getQuantity());
    item.setProduct(*inv["iPhone SE"]);
    ASSERT_EQ("iPhone SE", item.getProductName());
}