#pragma once

#include <vector>
#include "../models/Order.h"
#include "../models/Trade.h"
#include "../orderbook/Orderbook.h"


class MatchingEngine {
    public:
        // Takes an order, mutates the book, returns all trades generated
        std::vector<Trade> match(Order& incoming, Orderbook& book);
};