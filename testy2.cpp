// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "Inventory.h"

using namespace ::testing;

TEST(TestInventory, EmptyInventory) {
    Inventory i;
    ASSERT_EQ(0, i.productCount());
    // get non existing product
    ASSERT_EQ(nullptr, i["iPhone 13"]);
    ASSERT_EQ(nullptr, i.getProduct(0));
}

TEST(TestInventory, EmptyFile) {
    std::string filePath = "emptyFile";
    [[maybe_unused]] std::ofstream file(filePath, std::ios::out);
    Inventory i;
    try {
        i.loadFromFile(filePath);
        ASSERT_TRUE(false);
    }
    catch (std::runtime_error &) {
        ASSERT_EQ(0, i.productCount());
    }
}

TEST(TestInventory, InvalidFile) {
    std::string filePath = "invalidFile";
    std::ofstream file(filePath, std::ios::out);
    file << "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore";
    Inventory i;
    try {
        i.loadFromFile(filePath);
        ASSERT_TRUE(false);
    }
    catch (std::runtime_error &) {
        ASSERT_EQ(0, i.productCount());
    }
}

TEST(TestInventory, EmptyInventoryFile) {
    std::string filePath = "emptyInventory.dat";
    Inventory i1;
    i1.saveToFile(filePath);
    Inventory i2;
    i2.loadFromFile(filePath);
    ASSERT_EQ(0, i2.productCount());
}

TEST(TestInventory, OneProduct) {
    Inventory i;
    Product p1("iPhone 13", 1199.99);
    i.insertProduct(p1);
    ASSERT_EQ(1, i.productCount());
    ASSERT_EQ(1199.99, i.getProduct("iPhone 13")->getPrice());
    // check for unwanted reference to p1
    Product p2(std::move(p1));
    ASSERT_EQ(1199.99, i.getProduct("iPhone 13")->getPrice());
    ASSERT_EQ("Uncategorized", i.getProduct("iPhone 13")->getCategory());
    ASSERT_FALSE(i.getProduct("iPhone 13")->inStock());
}

TEST(TestInventory, OneProductFile) {
    std::string filePath = "oneProduct.dat";
    Inventory i1;
    Product p1("iPhone 13", "Phones", 1199.99, 71);
    i1.insertProduct(p1);
    i1.saveToFile(filePath);
    Inventory i2;
    i2.loadFromFile(filePath);
    ASSERT_EQ(1, i2.productCount());
    auto product = i2["iPhone 13"];
    ASSERT_EQ("iPhone 13", product->getName());
    ASSERT_EQ("Phones", product->getCategory());
    ASSERT_EQ(1199.99, product->getPrice());
    ASSERT_EQ(71, product->getStock());
}

TEST(TestInventory, DuplicateProduct) {
    Inventory i;
    Product p1("iPhone 13", 1199.99);
    i.insertProduct(p1);
    // check for unwanted reference to p1
    p1.setPrice(10);
    p1.setCategory("Mobiles");
    try {
        i.insertProduct(p1);
        ASSERT_TRUE(false);
    }
    catch (std::invalid_argument &) {
        ASSERT_EQ(1, i.productCount());
        ASSERT_EQ(1199.99, i["iPhone 13"]->getPrice());
    }
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
        p1.setPrice(20);
        ASSERT_EQ(1199.99, i["iPhone 13"]->getPrice());
    }
    i.updateProduct(p2);
    p2.setPrice(12);
    ASSERT_EQ(10, i["iPhone 13"]->getPrice());
    i.upsertProduct(p1);
    ASSERT_EQ(20, i["iPhone 13"]->getPrice());
}

TEST(TestInventory, MultipleProducts) {
    Inventory i;
    Product p1("iPhone 13", 1199.99);
    Product p2("iPhone SE", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    i.insertProducts({p2, p1, p3, p4});
    ASSERT_EQ(4, i.productCount());
    ASSERT_EQ(4, i.getAllProducts().getCount());
    ASSERT_EQ(0.89, i.getProduct("Modre pero")->getPrice());
    i["Modre pero"]->stockUp(220);
    ASSERT_EQ(220, i["Modre pero"]->getStock());
}

TEST(TestInventory, MultipleProductsFile) {
    std::string filePath = "multipleProducts.dat";
    Inventory i1;
    Product p1("iPhone 13", "Mobiles", 1199.99, 0);
    Product p2("iPhone SE", "Mobiles", 799.99, 13);
    Product p3("Logitech MX Master", "Mice", 98.9, 79);
    Product p4("Modre pero", 0.87);
    Product p5("Cierne pero", "Pens", 0.89, 2147483647);
    i1.insertProducts({p5, p4, p3, p2, p1});
    i1.saveToFile(filePath);
    Inventory i2;
    i2.loadFromFile(filePath);
    ASSERT_EQ(5, i2.productCount());
    ASSERT_EQ(p1, *i2["iPhone 13"]);
    ASSERT_EQ(p2, *i2["iPhone SE"]);
    ASSERT_EQ(p3, *i2["Logitech MX Master"]);
    ASSERT_EQ(p4, *i2["Modre pero"]);
    ASSERT_EQ(p5, *i2["Cierne pero"]);
}

TEST(TestInventory, ProductSorting) {
    Inventory inv;
    Product p1("iPhone 13", 1199.99);
    Product p2("iPhone SE", 799.99);
    Product p3("Logitech MX Master", 98.9);
    Product p4("Modre pero", 0.89);
    Product p5("Cierne pero", 0.89);
    inv.insertProducts({p5, p4, p3, p2, p1});
    // check if products are sorted by price ascending
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
    i.insertProducts({p2, p1, p3, p4});
    MyRange<Product> x = i.filterByPriceRange(98.9, 799.99);
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
    i.insertProducts({p5, p4, p3, p2, p1});
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
    inv.insertProducts({p5, p4, p3, p2, p1});
    auto filteredProducts = inv.filterByCategory("Mobiles");
    for (const auto &product: filteredProducts) {
        ASSERT_EQ("Mobiles", product.getCategory());
    }
}

TEST(TestInventory, ClearInventory) {
    Inventory i1;
    Product p1("iPhone 13", "Mobiles", 1199.99, 0);
    Product p2("iPhone SE", "Mobiles", 799.99, 13);
    Product p3("Logitech MX Master", "Mice", 98.9, 79);
    Product p4("Modre pero", 0.87);
    Product p5("Cierne pero", "Pens", 0.89, 2147483647);
    i1.insertProducts({p5, p4, p3, p2, p1});
    i1.clear();
    ASSERT_EQ(0, i1.productCount());
}
