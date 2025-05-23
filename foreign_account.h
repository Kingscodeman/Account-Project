#ifndef FOREIGN_ACCOUNT_H_INCLUDED
#define FOREIGN_ACCOUNT_H_INCLUDED
#include"account.h"
using namespace std;

struct Rate {
    string currency;
    float rate;
};


class ForeignAccount :public Account {
protected:
    string currency;
public:
    static vector<Rate> rate_table;

    ForeignAccount(string c,string name_) : Account(name_,true) {
        currency=c;
        balance=0;
        cout<<currency<<" account has been created.\n\n";
    }
    string get_currency(){
        return currency;
    }
    void deposit(float amount) override;
    void withdraw(float amount) override;
    void show_balance() const override;

    static void set_rate(const string, float) ;
    static float get_rate(const string);
    float get_value_twd() const;
};



inline void ForeignAccount::deposit(float amount) {
    balance+=amount;
    cout<<"Deposit "<<amount<<" "<<currency<<"\n\n";
    return ;
}

inline void ForeignAccount::withdraw(float amount) {
    if (balance>=amount) {
        balance-=amount;
        cout<<"Withdraw "<<amount<<" "<<currency <<"\n\n";
    }
    else{
        cout<<"Insufficient money in "<<currency<<" account.\n";
    }
    return ;
}


inline void ForeignAccount::set_rate(const string currency,float rate) {
    for (int i=0;i<rate_table.size();i++) {
        if (rate_table[i].currency==currency) {
            rate_table[i].rate=rate;
            return;
        }
    }
    Rate tmp;
    tmp.currency=currency;
    tmp.rate=rate;
    rate_table.push_back(tmp);
    return ;
}

inline float ForeignAccount::get_rate(const string currency) {
    for (int i=0;i<rate_table.size();i++) {
        if (rate_table[i].currency==currency) {
            return rate_table[i].rate;
        }
    }
}

inline float ForeignAccount::get_value_twd() const {
    float rate=get_rate(currency);
    return balance*rate;
}

inline void ForeignAccount::show_balance() const {
    cout<<currency<<" balance: "<<balance<<" "<<currency<<"\n";
    return ;
}

vector<Rate> ForeignAccount::rate_table = {
    {"USD",30.0},
    {"EUR",33.0}
};

#endif // FOREIGN_ACCOUNT_H_INCLUDED
