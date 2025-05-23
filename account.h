#ifndef ACCOUNT_H_INCLUDED
#define ACCOUNT_H_INCLUDED

#include<iostream>
#include<string>
using namespace std;

class Account{
protected:
    string id;
    unsigned long long account_num;
    float balance;

public:
    Account(string id2, bool from_stock = false) {
        id=id2;
        balance=0;
        if (from_stock==false) {
            cout<<id<<"'s basic account has been created"<<"\n\n";
        }
    }
    ~Account() {};


    virtual void deposit(float amount) {
        balance+=amount;
        cout<<id<<" deposit "<<amount<<"K to Basic Account"<<"\n\n";
    }

    virtual void withdraw(float amount) {
        balance-=amount;
        cout<<id<<" withdraw "<<amount<<"K to Basic Account"<<"\n\n";
    }

    virtual void show_balance() const {
        cout<<id<<"'s Basic Account balance: "<<balance <<"K"<<"\n\n";
    }

    virtual float total_asset() const {
        return balance;
    }

    void set_account_num(unsigned long long new_num){
        account_num=new_num;
        return ;
    }

    void get_account_info() const {
        cout<<"Account owner: "<<id<<" ,Account number: "<<account_num<<"\n\n";
        return ;
    }
};

#endif // ACCOUNT_H_INCLUDED
