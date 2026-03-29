# include <ctime>

struct Trade {
    int buy_order_id;
    int sell_order_id;
    double price;
    int quantity;
    time_t timestamp;
};