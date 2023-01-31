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
    OrderItem item(inv["iPhone 13"], 1);
    Order order(&inv);
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
    inv.insertProducts({p5, p4, p3, p2, p1, p6});
    OrderItem item(inv["iPhone SE"], 12);
    Order order(&inv);
    order.addItem(item);
    order.replaceItems();
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
    inv.insertProducts({p5, p4, p3, p2, p1, p6});
    OrderItem item(inv["iPhone SE"], 9);
    Order order(&inv);
    order.addItem(item);
    order.shipOrder();
    ASSERT_EQ(OrderStatus::SHIPPED, order.getStatus());
    ASSERT_EQ(22, inv["iPhone 13 Pro"]->getStock());
    ASSERT_EQ(9, order.getItem(0)->getQuantity());
}

TEST(TestOrder, ExportOrder) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99, 20);
    Product p6("iPhone 13 Pro", "Mobiles", 1399.99, 31);
    Product p2("iPhone SE", "Mobiles", 799.99, 0);
    Product p3("Logitech MX Master", "Mice", 98.9, 13);
    Product p4("Modre pero", "Pens", 0.89, 420);
    Product p5("Cierne pero", "Pens", 0.89, 210);
    inv.insertProducts({p5, p4, p3, p2, p1, p6});
    Order order(&inv);
    OrderItem item1(inv["iPhone SE"], 9);
    item1.addReview(8, "Moze byt");
    order.addItem(item1);
    OrderItem item2(inv["Logitech MX Master"], 1);
    item2.addReview(6, "Chyba softver pre Linux");
    order.addItem(item2);
    order.setAddress("Bratislava");
    std::string filePath = "orderExport.txt";
    order.saveItemsToFile(filePath);
}


TEST(TestOrder, SuggetsItemsEmtpy) {
    Inventory inv;
    Order order(&inv);
    order.suggestItems(30.22);
    ASSERT_EQ(0, order.getNumberOfItems());
}

TEST(TestOrder, SuggestImpossible) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99, 20);
    Product p6("iPhone 13 Pro", "Mobiles", 1399.99, 31);
    Product p2("iPhone SE", "Mobiles", 799.99, 0);
    Product p3("Logitech MX Master", "Mice", 98.9, 13);
    Product p4("Modre pero", "Pens", 0.89, 420);
    Product p5("Cierne pero", "Pens", 0.89, 210);
    inv.insertProducts({p5, p4, p3, p2, p1, p6});
    Order order(&inv);
    ASSERT_FALSE(order.suggestItems(0.81));
    ASSERT_EQ(0, order.getNumberOfItems());
}

TEST(TestOrder, SuggestOneItem) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99, 20);
    Product p6("iPhone 13 Pro", "Mobiles", 1399.99, 31);
    Product p2("iPhone 6", "Mobiles", 299.99, 0);
    Product p3("Logitech MX Master", "Mice", 98.9, 13);
    Product p4("Modre pero", "Pens", 0.89, 420);
    Product p5("Cierne pero", "Pens", 0.89, 210);
    inv.insertProducts({p5, p4, p3, p2, p1, p6});
    Order order(&inv);
    ASSERT_TRUE(order.suggestItems(0.89));
    ASSERT_EQ(1, order.getNumberOfItems());
    ASSERT_EQ(1, order.getItem(0)->getQuantity());
    ASSERT_EQ("Pens", order.getItem(0)->getProduct()->getCategory());
}

TEST(TestOrder, SuggestMultipleItems) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99, 20);
    Product p6("iPhone 13 Pro", "Mobiles", 1399.99, 31);
    Product p2("iPhone 6", "Mobiles", 299.99, 0);
    Product p3("Logitech MX Master", "Mice", 98.9, 13);
    Product p4("Modre pero", "Pens", 0.89, 420);
    Product p5("Cierne pero", "Pens", 0.89, 210);
    inv.insertProducts({p5, p4, p3, p2, p1, p6});
    Order order(&inv);
    ASSERT_TRUE(order.suggestItems(398.89));
    ASSERT_EQ(2, order.getNumberOfItems());
    ASSERT_EQ("Logitech MX Master", order.getItem(0)->getProduct()->getName());
    ASSERT_EQ("iPhone 6", order.getItem(1)->getProduct()->getName());
}

TEST(TestOrder, SuggestSameItem) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99, 20);
    Product p6("iPhone 13 Pro", "Mobiles", 1399.99, 31);
    Product p2("iPhone 6", "Mobiles", 299.99, 0);
    Product p3("Logitech MX Master", "Mice", 98.9, 13);
    Product p4("Modre pero", "Pens", 0.89, 420);
    Product p5("Cierne pero", "Pens", 0.89, 210);
    inv.insertProducts({p5, p4, p3, p2, p1, p6});
    Order order(&inv);
    ASSERT_TRUE(order.suggestItems(8.01));
    ASSERT_EQ(1, order.getNumberOfItems());
    ASSERT_EQ(9, order.getItem(0)->getQuantity());
    ASSERT_EQ("Pens", order.getItem(0)->getProduct()->getCategory());
}

TEST(TestOrder, SuggestSameItemAndMore) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99, 20);
    Product p6("iPhone 13 Pro", "Mobiles", 1399.99, 31);
    Product p2("iPhone 6", "Mobiles", 299.99, 0);
    Product p3("Logitech MX Master", "Mice", 98.9, 13);
    Product p4("Modre pero", "Pens", 0.89, 420);
    Product p5("Cierne pero", "Pens", 0.89, 210);
    inv.insertProducts({p5, p4, p3, p2, p1, p6});
    Order order(&inv);
    ASSERT_TRUE(order.suggestItems(205.81));
    ASSERT_EQ(2, order.getNumberOfItems());
    ASSERT_EQ(9, order.getItem(0)->getQuantity());
    ASSERT_EQ("Pens", order.getItem(0)->getProduct()->getCategory());
    ASSERT_EQ("Logitech MX Master", order.getItem(1)->getProduct()->getName());
}