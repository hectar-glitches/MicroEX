#pragma once

#include <map>
#include <deque>
#include <functional>
#include "../models/Order.h"

class Orderbook {
public:
    // Add an order to the book
    void addOrder(const Order& order);

    // Print best bid, best ask, and full depth
    void print() const;

private:
    // Asks: lowest price first (default map ordering)
    std::map<double, std::deque<Order>> asks;

    // Bids: highest price first (reverse ordering)
    std::map<double, std::deque<Order>, std::greater<double>> bids;
};
