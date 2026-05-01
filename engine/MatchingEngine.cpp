#include "MatchingEngine.h"
#include "Orderbook.h"

std::vector<Trade> MatchingEngine::match(Order& incoming, Orderbook& book) {

    // Collect all trades
    std::vector<Trade> trades;

    if (incoming.side == Side::buy) {
        // getAsks() returns a reference to the map inside the book.
        
        auto& asks = book.getAsks();

        // Keep looking while there's still quantity to fill AND asks exist
        while (incoming.quantity > 0 && !asks.empty()) {
            // Iterator to lowest-price ask
            auto it = asks.begin();

            // It ->first = the key = the price
            double ask_price = it->first;
            
            // it -> second = the deque of orders at that price
            auto& level = it->second;

            // If buyer's limit is below best ask, no match is possible
            if (incoming.price < ask_price) break;

            // Iterate through all orders at the price level
            while (incoming.quantity > 0 && !level.empty()) {
                Order& resting = level.front();

                // Fill as much as both sides allow
                int fill_qty = std::min(incoming.quantity, resting.quantity);

                // Record the trade
                Trade t;
                t.buy_order_id = incoming.order_id;
                t.sell_order_id = resting.order_id;
                t.price = ask_price;
                t.quantity = fill_qty;
                t.timestamp = incoming.time;
                trades.push_back(t); // Append trade to our results vector
                
                // Reduce quantities on both sides
                incoming.quantity -= fill_qty; // buyer's remaining demand
                resting.quantity -= fill_qty; // seller's remaining supply

                // If the resting order is fully filled, remove it from queue
                
                if (resting.quantity == 0) {
                    level.pop_front();
                }

            }

            // If emptied this price level entirely, remove it from map
            if (level.empty()) {
                asks.erase(it);
            }
        }
    } else {
        // Incoming sell
        &auto bids = book.getBids();

        // Bids sorted highest-first
        while (incoming.quantity > 0 && !bids.empty()) {
            auto it = bids.begin();
            double bid_price = it->first;
            auto& level = it->second;

            // Seller's limit above best bed -> no match possible
            if (incoming.price > bid_price) break;

            while (incoming.quantity > 0 && !level.empty())
            {
                Order& resting = level.front();
                int fill_qty = std::min(incoming.quantity, resting.quantity);

                Trade t;
                t.buy_order_id = resting.order_id; //Resting bid is buyer
                t.sell_order_id = incoming.order_id; //Incoming ask is seller

                t.price = bid_price;
                t.quantity = fill_qty;
                t.timestamp = incoming.time;
                trades.push_back(t);

                incoming.quantity -= fill_qty;
                resting.quantity -= fill_qty;

                if (resting.quantity == 0) {
                    level.pop_front();
                }
            }

            if (level.empty()) {
                bids.erase(it);
            }
        }
    }

    // After matching: if anything is unfilled, add it to the book
    if (incoming.quantity > 0) {
        book.addOrder(incoming);
    }

    return trades; // return all trades generated
}
