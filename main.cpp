#include "stock.h"
#include "account.h"
#include "person.h"
using namespace std;

int main() {
    srand(time(NULL));
    cout<<"(1) Basic account operation"<<"\n";
    Account* Peggy=new Account("Peggy");
    Peggy->deposit(100);
    Peggy->withdraw(10);
    Peggy->show_balance();
    cout<<"\n(2) Combination account operation (Stock & Basic account)\n";

    stock::add("NFLX");
    stock::add("WMT");
    stock::add("DIS");
    stock::add("NVDA");
    stock::s_rank();


    PersonAccount *Tom=new PersonAccount("Tom");
    ForeignAccount::set_rate("USD",32.0);
    ForeignAccount::set_rate("JPY",0.22);
    ForeignAccount* for_account = Tom->access_foreign_account("USD");

    Tom->get_BasicAccount()->set_account_num(949000509949);
    Tom->get_BasicAccount()->get_account_info();

    for_account->set_account_num(233000509949);
    for_account->get_account_info() ;

    Tom->access_foreign_account("USD")->deposit(100);
    Tom->access_foreign_account("JPY")->deposit(100);
    Tom->access_foreign_account("USD")->withdraw(50);

    Tom->get_BasicAccount()->deposit(100);
    Tom->transfer_to_stock(50);
    Tom->get_BasicAccount()->show_balance();
    Tom->get_StockAccount()->show_balance();


    // StockAccount deposit purchase
    Tom->get_StockAccount()->deposit(300);
    Tom->get_StockAccount()->purchase("DIS", 3000);
    Tom->get_StockAccount()->purchase("NVDA", 2000);
    Tom->get_StockAccount()->purchase("WMT", 1000);
    Tom->get_StockAccount()->show_balance();

    // sell stock and check balance
    Tom->get_StockAccount()->sell("DIS", 1000);
    Tom->show_all();

    // renew stock info
    stock::change();

    Tom->get_StockAccount()->yield("DIS");
    Tom->show_all();
    //ROI
    Tom->get_StockAccount()->revenue();

    delete Tom;
    cout << "(3) Basic Account & Stock Account Operations with vector" << "\n";

    vector<PersonAccount*> account_list;

    account_list.push_back(new PersonAccount("Bob"));
    account_list.push_back(new PersonAccount("Charlie"));

    for (int i=0;i<account_list.size() ;i++) {
        account_list[i]->get_BasicAccount()->deposit(200);
        account_list[i]->get_BasicAccount()->withdraw(50);
        account_list[i]->get_StockAccount()->deposit(300);
        account_list[i]->get_StockAccount()->purchase("NVDA", 1000);
        account_list[i]->show_all();
    }


    for (auto person:account_list) {
        delete person;
    }
    return 0;

}

