#include<iostream>

using namespace std;

class CashSuper {
public:
    double virtual acceptCash(double) = 0; 
};

class CashNormal: public CashSuper {
public:
    double acceptCash(double cash) {
        return cash;
    }
};

class CashReturn: public CashSuper {
private:
    double cashCondition;
    double cashReturn;
public:
    CashReturn(double con, double ret): cashCondition(con), cashReturn(ret) {}
    double acceptCash(double cash) {
        return cash - (int)(cash / cashCondition) * cashReturn;
    }
};

class CashRebate: public CashSuper {
private:
    double cashRebate;
public:
    CashRebate(double rebate): cashRebate(rebate) {}
    double acceptCash(double cash) {
        return cash * cashRebate;
    }
};

class CashContext {
public:
    CashSuper *cs;
    CashContext(int ct) {
        switch(ct) {
            case 0:
                cs = new CashNormal();
                break;
            case 1:
                cs = new CashRebate(0.8);
                break;
            case 2:
                cs = new CashReturn(300, 100);
                break;
        }
    }
};

int main(void) {
    CashContext ctx(2);
    cout << ctx.cs->acceptCash(500) << endl;
}