#include "orderbook.h"


int main() {
    OrderBook ob{};
    ob.add(1, 40, 10, OrderType::bid);
    ob.add(2, 20, 10, OrderType::bid);
    ob.add(3, 40, 10, OrderType::bid);
    ob.add(4, 10, 10, OrderType::bid);
    ob.add(5, 12, 10, OrderType::bid);
    ob.add(5, 40, 12, OrderType::bid);

    ob.add(6, 50, 10, OrderType::ask);
    ob.add(6, 60, 10, OrderType::ask);
    ob.add(6, 55, 10, OrderType::ask);
    ob.add(6, 43, 10, OrderType::ask);

    ob.add(7, 40, 5, OrderType::ask);
    ob.add(7, 40, 24, OrderType::ask);
    ob.add(8, 40, 3, OrderType::bid);


    ob.print();
    return 0;
}

