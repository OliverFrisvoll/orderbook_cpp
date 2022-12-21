#ifndef ORDERBOOK_ORDERBOOK_H
#define ORDERBOOK_ORDERBOOK_H

#include <vector>
#include <memory>
#include <unordered_map>


enum OrderType {
    ask,
    bid
};

struct Order {
    // Variables
    int ID;
    int price;
    int quantity;
    OrderType orderType;

    // Functions
    void print() const;
};

struct Transaction {
    // Variables
    int transaction_ID;
    int user_ID;
    double price;
    int quantity;

    // Functions
    void print() const;
};

class TransactionLog {
private:
    // Variables
    std::unique_ptr<std::unordered_map<int, Transaction>> m_transaction_log{
            std::make_unique<std::unordered_map<int, Transaction>>()};

    // Functions
    static int transaction_ID();

public:
    // Functions
    int add(int user_ID, double price, int quantity);

    Transaction get(int transaction_ID);

    void print() const;
};

class OrderBook {
private:
    // Variables
    std::unique_ptr<std::vector<Order>> m_ask{std::make_unique<std::vector<Order>>()};
    std::unique_ptr<std::vector<Order>> m_bid{std::make_unique<std::vector<Order>>()};
    std::unique_ptr<TransactionLog> m_transaction_log{std::make_unique<TransactionLog>()};
public:
    // Functions
    void add_ask(Order order);

    void add_bid(Order order);

    std::vector<int> add(int ID, int price, int quantity, OrderType orderType);

    void print_ask();

    void print_bid();

    void print();

    std::vector<Transaction> get_transactions(const std::vector<int>& transaction_IDs) const;
};

#endif //ORDERBOOK_ORDERBOOK_H
