#include <iostream>

#define P(x) std::cout << x << std::endl;

class OrderProcessTemplate {
public:
    void processOrder() {
        doSelect();
        doPayment();
        doDelivery();
    }

protected:
    virtual void doSelect() = 0;
    virtual void doPayment() = 0;
    virtual void doDelivery() = 0;
};


class NetOrder : public OrderProcessTemplate {
protected:
    void doSelect() override {
        P("Item added to online shopping cart");
        P("Get delivery address.");
    }

    void doPayment() override {
        P("Online Payment through Netbanking, card or Paytm");
    }

    void doDelivery() override {
        P("Ship the item through post to delivery address");
    }
};

class StoreOrder : public OrderProcessTemplate {
protected:
    void doSelect() override {
        P("Customer chooses the item from shelf.");
    }

    void doPayment() override {
        P("Pays at counter through cash/POS");
    }

    void doDelivery() override {
        P("Item delivered to in delivery counter.");
    }
};

int main() {
    NetOrder netOrder;
    netOrder.processOrder();
    P("");
    StoreOrder storeOrder;
    storeOrder.processOrder();
}

/**ˇ
 * Define the skeleton of an algorithm in an operation, deferring somesteps to subclasses.
 * Template Method lets subclasses redefine certain steps of an algorithm
 * without changing the algorithm's structure.
 *
 * Functionalities:
 * 1. Reuse: All subclasses can reuse the code of template method provided by parent class.
 * 2. Extension: Framework provides extension points through template method, so framework users can
 *    customize framework functions through the extension points without modifiying the framework.
 *
 * Callbacks and templates:
 * 0. Sync callbacks like template while async callbacks like observer
 * 1. Callbacks do not need to define new subclasses for new functions
 * 2. Callbacks do not need to implement unwanted template functions
 * 3. Callbacks are implemented by composition, transfor one object to another, are objects relationship
 * 4. Templates are implemented by inheritance, subclass overrides parent, are classes relationship */