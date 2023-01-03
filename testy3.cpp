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

TEST(TestOrderItem, NullItem) {
    try {
        [[maybe_unused]] OrderItem item(nullptr, 1);
        ASSERT_TRUE(false);
    }
    catch (std::invalid_argument &) {

    }
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

TEST(TestOrderItem, NoReview) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99);
    Product p2("iPhone SE", "Mobiles", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    Product p5("Cierne pero", 0.89);
    inv.insertProducts({p5, p4, p3, p2, p1});
    OrderItem item(inv["iPhone 13"], 1);
    ASSERT_EQ(NO_RATING, item.getRating());
    ASSERT_EQ("", item.getComment());
}

TEST(TestOrderItem, AddReview) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99);
    Product p2("iPhone SE", "Mobiles", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    Product p5("Cierne pero", 0.89);
    inv.insertProducts({p5, p4, p3, p2, p1});
    OrderItem item(inv["iPhone 13"], 1);
    item.addReview(4, "Nic moc");
    ASSERT_EQ(4, item.getRating());
    ASSERT_EQ("Nic moc", item.getComment());
}
