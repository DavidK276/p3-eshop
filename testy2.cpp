// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "Inventory.h"

using namespace ::testing;

TEST(TestInventory, EmptyInventory) {
    Inventory i;
    ASSERT_EQ(0, i.productCount());
    ASSERT_EQ(nullptr, i["iPhone 13"]);
    ASSERT_EQ(nullptr, i.getProduct(1));
}

TEST(TestInventory, OneProduct) {
    Inventory i;
    Product p1("iPhone 13", 1199.99);
    i.insertProduct(p1);
    ASSERT_EQ(1, i.productCount());
    ASSERT_EQ(1199.99, i.getProduct("iPhone 13")->getPrice());
    p1.setPrice(10);
    ASSERT_EQ(1199.99, i.getProduct("iPhone 13")->getPrice());
    ASSERT_FALSE(i.getProduct("iPhone 13")->inStock());
}

TEST(TestInventory, UpdateProduct) {
    Inventory i;
    Product p1("iPhone 13", "Phones", 1199.99);
    Product p2("iPhone 13", "Mobiles", 10);
    i.insertProduct(p1);
    try {
        i.insertProduct(p2);
        ASSERT_FALSE(true);
    }
    catch (std::invalid_argument &) {
        ASSERT_EQ(1199.99, i["iPhone 13"]->getPrice());
    }
    i.updateProduct(p2);
    ASSERT_EQ(10, i["iPhone 13"]->getPrice());
    i.upsertProduct(p1);
    ASSERT_EQ(1199.99, i["iPhone 13"]->getPrice());
}

TEST(TestInventory, MultipleProducts) {
    Inventory i;
    Product p1("iPhone 13", 1199.99);
    Product p2("iPhone SE", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    i.insertProduct(p1);
    i.insertProduct(p2);
    i.insertProduct(p3);
    i.insertProduct(p4);
    ASSERT_EQ(4, i.productCount());
    ASSERT_EQ(4, i.getAllProducts().getCount());
    ASSERT_EQ(0.89, i.getProduct("Modre pero")->getPrice());
    i["Modre pero"]->stockUp(220);
    ASSERT_EQ(220, i["Modre pero"]->getStock());
}

TEST(TestInventory, ProductSorting) {
    Inventory inv;
    Product p1("iPhone 13", 1199.99);
    Product p2("iPhone SE", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    Product p5("Cierne pero", 0.89);
    inv.insertProduct(p1);
    inv.insertProduct(p2);
    inv.insertProduct(p3);
    inv.insertProduct(p4);
    inv.insertProduct(p5);
    for (size_t i = 0; i < inv.productCount() - 1; i++) {
        ASSERT_TRUE(inv.getProduct(i)->getPrice() <= inv.getProduct(i)->getPrice());
    }
}

TEST(TestInventory, ProductPriceRange) {
    Inventory i;
    Product p1("iPhone 13", 1199.99);
    Product p2("iPhone SE", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    i.insertProduct(p1);
    i.insertProduct(p2);
    i.insertProduct(p3);
    i.insertProduct(p4);
    MyRange<Product> x = i.filterByPriceRange(90, 800);
    ASSERT_EQ(2, x.getCount());
    ASSERT_EQ("Logitech MX Master", x.getFirst()->getName());
    ASSERT_EQ("iPhone SE", x.getFinal()->getName());
}

TEST(TestInventory, ProductPrice) {
    Inventory i;
    Product p1("iPhone 13", 1199.99);
    Product p2("iPhone SE", 799.99);
    Product p3("Logitech MX Master 2S", 98.9);
    Product p4("Modre pero", 0.89);
    Product p5("Logitech MX Master 3S", 98.9);
    i.insertProduct(p1);
    i.insertProduct(p2);
    i.insertProduct(p3);
    i.insertProduct(p4);
    i.insertProduct(p5);
    MyRange<Product> products = i.filterByPrice(98.9);
    ASSERT_EQ(2, products.getCount());
    products = i.filterByPrice(98.89);
    ASSERT_EQ(0, products.getCount());
}

TEST(TestInventory, ProductCategory) {
    Inventory inv;
    Product p1("iPhone 13", "Mobiles", 1199.99);
    Product p2("iPhone SE", "Mobiles", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    Product p5("Cierne pero", 0.89);
    auto filteredProducts = inv.filterByCategory("Mobiles");
    for (const auto &product: filteredProducts) {
        ASSERT_EQ("Mobiles", product.getCategory());
    }
}
