//
// Created by david on 13.12.2022.
//

#include "Order.h"
#include <boost/range/adaptor/reversed.hpp>

Order::Order(Inventory *inventory0) : inventory(inventory0), status(OrderStatus::PROCESSING) {}

/*
 * Retrieves the specified element from the list.
 * This is expensive and is only intended for testing.
 * Returns nullptr on failure.
 */
const OrderItem *Order::getItem(size_t index) const {
    if (this->items.size() <= index) {
        return nullptr;
    }
    auto iter = this->items.begin();
    while (iter != this->items.end() && index > 0) {
        iter++;
        index--;
    }
    if (iter != this->items.end()) {
        return &*iter;
    }
    return nullptr;
}

/*
 * Adds the item to the order.
 */
void Order::addItem(const OrderItem &item) {
    this->items.push_back(item);
}

/*
 * Replaces out of stock items with the item of the same category and highest price.
 */
void Order::replaceItems() {
    for (auto iter = this->items.begin(); iter != this->items.end(); iter++) {
        if (!iter->getProduct()->inStock()) {
            auto potentialProducts = inventory->filterByCategory(iter->getProduct()->getCategory());
            bool foundSuitable = false;
            for (auto &product: boost::adaptors::reverse(potentialProducts)) {
                if (product.getStock() >= iter->getQuantity()) {
                    foundSuitable = true;
                    iter->setProduct(&product);
                    break;
                }
            }
            if (!foundSuitable) {
                this->items.erase(iter);
            }
        }
    }
}

/*
 * Replaces items, decreases stock of each item in the inventory and sets the order status to shipped.
 */
void Order::shipOrder() {
    this->replaceItems();
    for (const auto &item: this->items) {
        auto product = inventory->getProduct(item.getProductName());
        product->ship(item.getQuantity());
    }
    this->status = OrderStatus::SHIPPED;
}

void Order::saveItemsToFile(const std::string &filePath) const {
    std::ofstream file(filePath, std::ios::out);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }
    file << "product name,quantity,rating,comment" << '\n';
    for (const auto &item: this->items) {
        file << '"' << item.getProduct()->getName() << '"' << ',' << item.getQuantity();
        if (item.getRating() != NO_RATING) {
            file << ',' << static_cast<char>(item.getRating() + '0') << ',' << '"' << item.getComment() << '"';
        }
        file << '\n';
    }
}
/*
 * Finds a combination of products with a total price equal to the input, then adds them to the order.
 * Returns false when no such combination exists and true otherwise.
 * This is a variant of the change-making problem.
 */
bool Order::suggestItems(const Product::Price &price) {
    auto priceCents = nearbyint(price * 100).convert_to<size_t>();
    auto products = inventory->getAllProducts();
    auto chosenNumber = std::vector<long>(priceCents + 1, std::numeric_limits<long>::max());
    chosenNumber[0] = 0;
    auto chosenProducts = std::vector<long>(priceCents + 1, std::numeric_limits<long>::max());
    long minChoice = 0;

    for (size_t i = 1; i <= priceCents; i++) {
        auto min = std::numeric_limits<long>::max();
        for (auto productIter = products.begin(); productIter < products.end(); productIter++) {
            if (productIter->getPriceCents() <= i) {
                if (chosenNumber[i - productIter->getPriceCents()] < min) {
                    min = chosenNumber[i - productIter->getPriceCents()];
                    minChoice = std::distance(products.begin(), productIter);
                }
            }
        }
        if (min != std::numeric_limits<long>::max()) {
            chosenNumber[i] = 1 + min;
            chosenProducts[i] = minChoice;
        }
    }

    if (chosenNumber[priceCents] == std::numeric_limits<long>::max()) {
        return false;
    }
    auto tmp = std::map<const Product*, unsigned int>();
    while (priceCents > 0) {
        auto chosenProduct = products.begin() + chosenProducts[priceCents];
        tmp[chosenProduct.base()] += 1;
        priceCents -= chosenProduct->getPriceCents();
    }
    for (const auto &[chosenProduct, quantity] : tmp) {
        OrderItem newItem(chosenProduct, quantity);
        this->addItem(newItem);
    }
    return true;
}
