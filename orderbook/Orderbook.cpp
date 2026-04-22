#include "Orderbook.h"
#include <iostream>
#include <iomanip>

void Orderbook::addOrder(const Order& order) {
    if (order.side == Side::buy) {
        bids[order.price].push_back(order);
    } else {
        asks[order.price].push_back(order);
    }
}

void Orderbook::print() const {
    std::cout << std::fixed << std::setprecision(2);

    // Best ask (lowest)
    if (!asks.empty()) {
        auto& [price, level] = *asks.begin();
        int total = 0;
        for (const auto& o : level) total += o.quantity;
        std::cout << "Best Ask: " << price << "  qty: " << total << "\n";
    } else {
        std::cout << "Best Ask: none\n";
    }

    // Best bid (highest)
    if (!bids.empty()) {
        auto& [price, level] = *bids.begin();
        int total = 0;
        for (const auto& o : level) total += o.quantity;
        std::cout << "Best Bid: " << price << "  qty: " << total << "\n";
    } else {
        std::cout << "Best Bid: none\n";
    }

    // Full depth
    std::cout << "\n--- Ask Depth (low to high) ---\n";
    for (const auto& [price, level] : asks) {
        int total = 0;
        for (const auto& o : level) total += o.quantity;
        std::cout << "  " << price << "  qty: " << total
                  << "  orders: " << level.size() << "\n";
    }

    std::cout << "--- Bid Depth (high to low) ---\n";
    for (const auto& [price, level] : bids) {
        int total = 0;
        for (const auto& o : level) total += o.quantity;
        std::cout << "  " << price << "  qty: " << total
                  << "  orders: " << level.size() << "\n";
    }
}
