#ifndef STOCK_H_INCLUDED
#define STOCK_H_INCLUDED

#include "account.h"
#include<vector>
#include<string>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct stock_p {
    string name;
    int share;
    float price;
    float eps;
    float value;
};

class stock :public Account {
private:
    vector<stock_p> stock_account;

public:
    static int stock_number;
    static vector<stock_p> stock_info;

    stock(string id2) : Account(id2,true) {
        stock_number++;
        cout<<id<<"'s stock account has been created"<<"\n"<<"\n";
    }

    ~stock();

    static void add(string);
    static void change();
    static void s_rank();
    void purchase(string,int);
    void sell(string,int);
    void show() const;
    void yield(string) const;
    void revenue() const;

    static void quickSort(vector<stock_p>&,int,int);
    static int partition(vector<stock_p>&,int,int);

    void deposit(float) override;
    void withdraw(float) override;
    void show_balance() const override;
    float total_asset() const override ;

};

#endif // STOCK_H_INCLUDED
