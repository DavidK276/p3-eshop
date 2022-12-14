// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "Product.h"

using namespace ::testing;

TEST(TestProduct, CreateProduct) {
    Product p1("iPhone 13", 1199.99);
    ASSERT_EQ("iPhone 13", p1.getName());
    ASSERT_EQ(1199.99, p1.getPrice());
    ASSERT_EQ(NO_CATEGORY, p1.getCategory());
    ASSERT_EQ(0, p1.getStock());
}

TEST(TestProduct, CreateProductWithCat) {
    Product p1("iPhone 13", "Mobily", 1199.99);
    ASSERT_EQ("Mobily", p1.getCategory());
    ASSERT_EQ(0, p1.getStock());
}

TEST(TestProduct, StockUpProduct) {
    Product p1("iPhone 13", "Mobily", 1199.99);
    p1.stockUp(10);
    ASSERT_EQ(10, p1.getStock());
    p1.ship(2);
    ASSERT_EQ(8, p1.getStock());
}

TEST(TestProduct, CopyProduct) {
    Product p1("iPhone 13", "Mobily", 1199.99, 21);
    Product p2(p1);
    ASSERT_EQ(p1, p2);
    Product p3 = p2;
    ASSERT_EQ(p1, p3);
}

TEST(TestProduct, MoveProduct) {
    Product p1("iPhone 13", "Mobily", 1199.99, 21);
    Product p2 = std::move(p1);
    ASSERT_TRUE(std::empty(p1.getName()));
    ASSERT_EQ(NO_CATEGORY, p1.getCategory());
}