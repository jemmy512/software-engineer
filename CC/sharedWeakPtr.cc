#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <cassert>
#include <functional>

using namespace std;
using namespace std::placeholders;

class Stock {
public:
    Stock(string str = ""): key_(str){}
    string key() const {
        return key_;
    }

private:
    string key_;
};

class StockFactory: public enable_shared_from_this<StockFactory> {
public:
    shared_ptr<Stock> get(const string &key) {

        shared_ptr<Stock> spStock;
        weak_ptr<Stock> &wpStock = stocks_[key];
        spStock = wpStock.lock();
        if (!spStock) {
            cout << "stock not exist: " << key << endl;
            spStock.reset(new Stock(key),
                          bind(&StockFactory::weakDeleteCB,
                               weak_ptr<StockFactory>(shared_from_this()), _1));
            wpStock = spStock;
        }
        return spStock;
    }

private:
    static void weakDeleteCB(const weak_ptr<StockFactory> wkFactory, Stock *stock) {
        shared_ptr<StockFactory> factory(wkFactory.lock());
        if (factory) {
            cout << "weakDeleteCB working..." << endl;
            factory->removeStock(stock);
        }
        delete stock;
    }

    void removeStock(Stock *stock) {
        if (stock) {
            cout << "remove stock from factory: " << stock->key() << endl;
            stocks_.erase(stock->key());
        }
    }

    map<string, weak_ptr<Stock>> stocks_;
};

int main() {
    shared_ptr<StockFactory> factory(new StockFactory());
    shared_ptr<Stock> stock1 = factory->get("Google");
    shared_ptr<Stock> stock2 = factory->get("Apple");
    assert(stock1 == stock2);
    stock1.reset();
}


