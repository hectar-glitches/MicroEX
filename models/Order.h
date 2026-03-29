# include <ctime>
# include <string>

enum class OrderType {
    limitOrder,
    marketOrder
};

enum class Side {
    buy,
    sell
};

struct Order {
    int order_id;
    double price;
    int quantity;
    std::string symbol;
    time_t time;
    OrderType orderType;
    Side side;
};