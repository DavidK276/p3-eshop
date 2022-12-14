// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "Order.h"

using namespace ::testing;

TEST(TestOrder, CreateOrder) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99, 20);
    Product p2("iPhone SE", "Mobiles", 799.99, 11);
    Product p3("Logitech MX Master", "Mice", 98.9, 13);
    Product p4("Modre pero", "Pens", 0.89, 420);
    Product p5("Cierne pero", "Pens", 0.89, 210);
    inv.insertProduct(p1);
    inv.insertProduct(p2);
    inv.insertProduct(p3);
    inv.insertProduct(p4);
    inv.insertProduct(p5);
    OrderItem item(*inv["iPhone 13"], 1);
    Order order;
    order.addItem(item);
    ASSERT_EQ(1, order.getItem(0)->getQuantity());
}

TEST(TestOrder, ReplaceItems) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99, 20);
    Product p6("iPhone 13 Pro", "Mobiles", 1399.99, 31);
    Product p2("iPhone SE", "Mobiles", 799.99, 0);
    Product p3("Logitech MX Master", "Mice", 98.9, 13);
    Product p4("Modre pero", "Pens", 0.89, 420);
    Product p5("Cierne pero", "Pens", 0.89, 210);
    inv.insertProduct(p1);
    inv.insertProduct(p2);
    inv.insertProduct(p3);
    inv.insertProduct(p4);
    inv.insertProduct(p5);
    inv.insertProduct(p6);
    OrderItem item(*inv["iPhone SE"], 12);
    Order order;
    order.addItem(item);
    order.replaceItems(inv);
    ASSERT_EQ("iPhone 13 Pro", order.getItem(0)->getProductName());
    ASSERT_EQ(12, order.getItem(0)->getQuantity());
}

TEST(TestOrder, ShipOrder) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99, 20);
    Product p6("iPhone 13 Pro", "Mobiles", 1399.99, 31);
    Product p2("iPhone SE", "Mobiles", 799.99, 0);
    Product p3("Logitech MX Master", "Mice", 98.9, 13);
    Product p4("Modre pero", "Pens", 0.89, 420);
    Product p5("Cierne pero", "Pens", 0.89, 210);
    inv.insertProduct(p1);
    inv.insertProduct(p2);
    inv.insertProduct(p3);
    inv.insertProduct(p4);
    inv.insertProduct(p5);
    inv.insertProduct(p6);
    OrderItem item(*inv["iPhone SE"], 9);
    Order order;
    order.addItem(item);
    order.shipOrder(inv);
    ASSERT_EQ(OrderStatus::SHIPPED, order.getStatus());
    ASSERT_EQ(22, inv["iPhone 13 Pro"]->getStock());
    ASSERT_EQ(9, order.getItem(0)->getQuantity());
}