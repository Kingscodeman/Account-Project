#include "stock.h"
#include "foreign_account.h"
#include "person.h"
using namespace std;

int main() {
    srand(time(NULL));
    cout<<"(1) Basic account operation"<<"\n";
    Account* Peggy=new Account("Peggy");
    Peggy->deposit(100);
    Peggy->withdraw(10);
    Peggy->show_balance();

    delete Peggy;
    cout<<"\n(2) Combination account operation (Stock & Basic account)\n";

    stock::add("NFLX");
    stock::add("WMT");
    stock::add("DIS");
    stock::add("NVDA");
    stock::s_rank();

    PersonAccount* Tom=new PersonAccount("Tom");
    ForeignAccount::set_rate("USD", 32.0);
    ForeignAccount::set_rate("JPY", 0.22);

    ForeignAccount* for_account=Tom->access_foreign_account("USD");
    Tom->set_account_num(949000509949);
    Tom->get_account_info();

    for_account->set_account_num(233000509949);
    for_account->get_account_info();

    Tom->access_foreign_account("USD")->deposit(100);
    Tom->access_foreign_account("JPY")->deposit(100);
    Tom->access_foreign_account("USD")->withdraw(50);

    Tom->Account::deposit(100);
    Tom->transfer_to_stock(50);
    Tom->Account::show_balance();
    Tom->stock::show_balance();
    Tom->stock::deposit(300);

    // StockAccount deposit purchase
    Tom->purchase("DIS",3000);
    Tom->purchase("NVDA",2000);
    Tom->purchase("WMT",1000);
    Tom->stock::show_balance();

    // sell stock and check balance
    Tom->sell("DIS", 1000);
    Tom->show_all();

    stock::change();
    Tom->yield("DIS");
    Tom->show_all();
    //ROI
    Tom->revenue();

    delete Tom;

    cout<<"(3) Basic Account & Stock Account Operations with vector\n";
    
    vector<Account*> account_list;
    account_list.push_back(new Account("Bob",false));
    account_list.push_back(new stock("Charlie"));

    for (int i=0;i<account_list.size();i++){
        account_list[i]->deposit(200);
        account_list[i]->withdraw(50);
        account_list[i]->show_balance();
    }

    for (auto person : account_list){
        delete person;
    }

    return 0;
}
