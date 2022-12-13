// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "Inventory.h"

using namespace ::testing;

TEST(TestInventory, EmptyInventory) {
    Inventory i;
    ASSERT_EQ(0, i.productCount());
}

TEST(TestInventory, OneProduct) {
    Inventory i;
    Product p1("iPhone 13", 119999);
    i.insertProduct(p1);
    ASSERT_EQ(1, i.productCount());
}

TEST(TestInventory, MultipleProducts) {
    Inventory i;
    Product p1("iPhone 13", 119999);
    Product p2("iPhone SE", 79999);
    Product p3("Logitech MX Master", 9890);
    Product p4("Modre pero", 89);
    i.insertProduct(p1);
    i.insertProduct(p2);
    i.insertProduct(p3);
    i.insertProduct(p4);
    ASSERT_EQ(4, i.productCount());
    ASSERT_EQ("iPhone 13", i.getProduct(3)->getName());
    ASSERT_EQ("iPhone SE", i.getProduct(2)->getName());
    ASSERT_EQ("Modre pero", i.getProduct(0)->getName());
    ASSERT_EQ("Logitech MX Master", i.getProduct(1)->getName());
}

TEST(TestInventory, ProductPriceRange) {
    Inventory i;
    Product p1("iPhone 13", 119999);
    Product p2("iPhone SE", 79999);
    Product p3("Logitech MX Master", 9890);
    Product p4("Modre pero", 89);
    i.insertProduct(p1);
    i.insertProduct(p2);
    i.insertProduct(p3);
    i.insertProduct(p4);
    MyRange<Product> x = i.filterByPriceRange(9000, 80000);
    ASSERT_EQ(2, x.getCount());
    ASSERT_EQ("Logitech MX Master", x.getFirst()->getName());
    ASSERT_EQ("iPhone SE", x.getFinal()->getName());
}

TEST(TestInventory, ProductPrice) {
    Inventory i;
    Product p1("iPhone 13", 119999);
    Product p2("iPhone SE", 79999);
    Product p3("Logitech MX Master 2S", 9890);
    Product p4("Modre pero", 89);
    Product p5("Logitech MX Master 3S", 9890);
    i.insertProduct(p1);
    i.insertProduct(p2);
    i.insertProduct(p3);
    i.insertProduct(p4);
    i.insertProduct(p5);
    MyRange<Product> products = i.filterByPrice(9890);
    ASSERT_EQ(2, products.getCount());
    products = i.filterByPrice(9889);
    ASSERT_EQ(0, products.getCount());
}
