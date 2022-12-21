#include <iostream>
#include "orderbook.h"


void Order::print() const {
    std::cout << "ID: " << ID
              << " Price: " << price
              << " Quantity: " << quantity
              << " Type: " << orderType
              << std::endl;
}

void OrderBook::add_ask(Order order) {
    if (!m_ask->empty()) {
        for (auto it = m_ask->begin(); it != m_ask->end(); ++it) {
            if (order.price >= it->price) {
                m_ask->insert(it, order);
                return;
            }
        }
    }
    m_ask->push_back(order);
}

void OrderBook::add_bid(Order order) {
    if (!m_bid->empty()) {
        for (auto it = m_bid->begin(); it != m_bid->end(); ++it) {
            if (order.price >= it->price) {
                m_bid->insert(it, order);
                return;
            }
        }
    }
    m_bid->push_back(order);
}

std::vector<int> OrderBook::add(int ID, int price, int quantity, OrderType orderType) {
    Order order{ID, price, quantity, orderType};
    std::vector<int> transactions_IDs{};

    if (orderType == OrderType::ask) {
        if (!m_bid->empty() and m_bid->front().price >= order.price) {

            while (order.quantity != 0) {
                auto it = m_bid->begin();

                if (it->price >= order.price) {

                    if (it->quantity > order.quantity) {
                        transactions_IDs.push_back(m_transaction_log->add(it->ID, it->price, order.quantity));
                        transactions_IDs.push_back(m_transaction_log->add(order.ID, it->price, -order.quantity));

                        it->quantity -= order.quantity;
                        order.quantity = 0;
                    } else {
                        transactions_IDs.push_back(m_transaction_log->add(it->ID, it->price, it->quantity));
                        transactions_IDs.push_back(m_transaction_log->add(order.ID, it->price, -it->quantity));

                        m_bid->erase(it);
                        order.quantity -= it->quantity;
                    }

                } else
                    break;

            }
            if (order.quantity > 0)
                add_ask(order);

        } else
            add_ask(order);

    } else if (orderType == OrderType::bid) {
        if (!m_ask->empty() and m_ask->front().price <= order.price) {

            while (order.quantity != 0) {
                auto it = m_ask->begin();

                if (it->price <= order.price) {
                    transactions_IDs.push_back(m_transaction_log->add(it->ID, it->price, order.quantity));
                    transactions_IDs.push_back(m_transaction_log->add(order.ID, it->price, -order.quantity));

                    if (it->quantity > order.quantity) {
                        it->quantity -= order.quantity;
                        order.quantity = 0;
                    } else {
                        transactions_IDs.push_back(m_transaction_log->add(it->ID, it->price, it->quantity));
                        transactions_IDs.push_back(m_transaction_log->add(order.ID, it->price, -it->quantity));

                        m_bid->erase(it);
                        order.quantity -= it->quantity;
                    }

                } else
                    break;

            }
            if (order.quantity > 0)
                add_bid(order);
        } else
            add_bid(order);
    }
    return transactions_IDs;
}


void OrderBook::print_ask() {
    for (auto &it: *m_ask) {
        it.print();
    }
}

void OrderBook::print_bid() {
    for (auto &it: *m_bid) {
        it.print();
    }
}

void OrderBook::print() {
    print_ask();
    std::cout << "-------------------------------------" << std::endl;
    print_bid();
}

std::vector<Transaction> OrderBook::get_transactions(const std::vector<int> &transaction_IDs) const {
    std::vector<Transaction> transactions{};
    for (auto &it: transaction_IDs)
        transactions.push_back(m_transaction_log->get(it));
    return transactions;

}

void Transaction::print() const {
    std::cout << "Transaction ID: " << transaction_ID
              << " User ID: " << user_ID
              << " Price: " << price
              << " Quantity: " << quantity
              << std::endl;
}

int TransactionLog::transaction_ID() {
    static int transaction_ID = 0;
    return transaction_ID++;
}

int TransactionLog::add(int user_ID, double price, int quantity) {
    int trans_ID{transaction_ID()};
    Transaction transaction{trans_ID, user_ID, price, quantity};
    m_transaction_log->insert({trans_ID, transaction});
    return trans_ID;
}

void TransactionLog::print() const {
    for (auto &it: *m_transaction_log) {
        it.second.print();
    }
}

Transaction TransactionLog::get(int transaction_ID) {
    return m_transaction_log->at(transaction_ID);
}
