#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "account.h"
#include "stock.h"
#include "foreign_account.h"
class PersonAccount {
private:
    string name;
    Account* BasicAccount;
    stock* StockAccount;
    vector<ForeignAccount*> foreign_accounts;
public:

    Account* get_BasicAccount(){
        return BasicAccount;
    }

    stock* get_StockAccount(){
        return StockAccount;
    }

    PersonAccount(string name) {
        this->name=name;
        BasicAccount=new Account(name);
        StockAccount=new stock(name);
    }

    ~PersonAccount() {
        delete BasicAccount;
        delete StockAccount;
        for (int i=0;i<foreign_accounts.size();i++)
            delete foreign_accounts[i];
    }


    ForeignAccount* access_foreign_account(string currency) {
        for (int i=0;i<foreign_accounts.size();i++) {
            if (foreign_accounts[i]->get_currency()==currency)
                return foreign_accounts[i];
        }

        cout<<name<<"\'s ";
        //ForeignAccount* new_account = new ForeignAccount(currency);
        ForeignAccount* new_account = new ForeignAccount(currency,name);


        foreign_accounts.push_back(new_account);
        return new_account;
    }


    void add_foreign(string);
    void show_all() const;
    float show_foreign_accounts() const;
    void transfer_to_stock(float);
    void transfer_to_basic(float);

};


inline void PersonAccount::transfer_to_stock(float amount){
    if (BasicAccount->total_asset()>=amount){
        BasicAccount->withdraw(amount);
        StockAccount->deposit(amount);
        cout<<"Transfer"<<amount<<"K from Basic Account to Stock Account."<<"\n";
    }
    else {
        cout<<"Insufficient balance in Basic Account for transfer."<<"\n";
    }
}

inline void PersonAccount::transfer_to_basic (float amount){
    if (StockAccount->total_asset() >= amount){
        StockAccount->withdraw(amount);
        BasicAccount->deposit(amount);
        cout<<"Transfer"<<amount<<"K from Stock Account to Basic Account."<<"\n";
    }
    else{
        cout<<"Insufficient balance in Stock Account for transfer."<<"\n";
    }
}

inline float PersonAccount::show_foreign_accounts() const {
    float total=0;
    for (int i=0;i<foreign_accounts.size();i++) {
        foreign_accounts[i]->show_balance();
        float tmp=foreign_accounts[i]->get_value_twd();
        total+=tmp;
        cout<<"TWD value: "<<tmp<<"\n\n";
    }
    return total;
}

inline void PersonAccount::show_all() const {
    cout<<"Name: "<<name<<"\n";
    BasicAccount->show_balance();
    StockAccount->show_balance();
    StockAccount->show();
    float foreign_asset=show_foreign_accounts();
    float basic_asset=BasicAccount->total_asset();
    float stock_asset=StockAccount->total_asset();
    cout<<"Total Asset: "<<basic_asset+stock_asset+foreign_asset<<"K\n\n";
}
#endif // ACCOUNT2_H_INCLUDED
