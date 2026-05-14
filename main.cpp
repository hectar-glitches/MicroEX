#include <iostream>
#include "orderbook/Orderbook.h"
#include "engine/MatchingEngine.h"

int main() {
    Orderbook book;
    MatchingEngine engine;

    // Helper to build an order quickly
    auto makeOrder = [](int id, Side side, double price, int qty) {
        Order o;
        o.order_id = id;
        o.side     = side;
        o.price    = price;
        o.quantity = qty;
        o.orderType = OrderType::limitOrder;
        o.symbol = "AAPL";
        o.time   = 0;

        return o;
    };

    Order sell = makeOrder(1,Side::sell, 100.0, 10);
    engine.match(sell, book);

    Order buy = makeOrder(2, Side::buy, 100.0, 6);
    auto trades = engine.match(buy, book);

    std::cout << "Trades executed: " << trades.size() << "\n";
    for (auto& t : trades) {
        std::cout << " buy #" << t.buy_order_id
            << " x sell #" << t.sell_order_id
            << " qty=" << t.quantity
            <<" price" << t.price << "\n";
    }

    auto orders = loadCSV("../data/sample_orders.csv");
    for (auto& o : orders) {
        auto trades = engine.match(o, book);
        for (auto& t : trades) {
            std::cout << "TRADE qty=" << t.quantity << " @ " << t.price << "\n";
        }
    }

    book.print();
    return 0;
}

std::vector<Order> loadCSV(const std::string& path) {
    std::vector<Order> orders;
    std::ifstream file(path);
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        Order o;

        std::getline(ss, token, ','); o.time = std::stoi(token);
        std::getline(ss, token, ','); o.order_id = std::stoi(token);
        std::getline(ss, token, ','); o.side = (token == "buy") ? Side::buy : Side::sell;
        std::getline(ss, token, ','); o.symbol = token;
        std::getline(ss, token, ','); o.price = std::stod(token);
        std::getline(ss, token, ','); o.quantity = std::stoi(token);

        orders.push_back(o);
    }
    return orders;
}