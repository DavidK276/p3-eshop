// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "Product.h"

using namespace ::testing;
TEST(TestProduct, CreateProduct) {
    Product p1("iPhone 13", (Product::Price)1199.99);
    ASSERT_EQ("iPhone 13", p1.getName());
    ASSERT_EQ(1199.99, p1.getPrice());
    ASSERT_EQ("Uncategorized", p1.getCategory());
}

TEST(TestProduct, CreateProductWithCat) {
    Product p1("iPhone 13", 1199.99, "Mobily");
   ASSERT_EQ("Mobily", p1.getCategory());
}
