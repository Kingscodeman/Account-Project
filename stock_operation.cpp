#include "stock.h"
#include "account.h"
int stock::stock_number=0;
vector<stock_p> stock::stock_info = {};

float price_search(string names){
    float price_t=0;
    for(int j=0;j<stock::stock_info.size();j++){
        if(names==stock::stock_info[j].name){
            price_t=stock::stock_info[j].price;
        }
    }
    return price_t;
}

float eps_search(string names){
    float eps_t=0;
    for(int j=0;j<stock::stock_info.size();j++){
        if(names==stock::stock_info[j].name){
            eps_t=stock::stock_info[j].eps;
        }
    }
    return eps_t;
}


void stock::add(string names){
    stock_p info;

    int x=(rand()%30)+11;
    int y=(rand()%10)+1;
    info.name=names;
    info.price=x;
    info.eps=y;
    stock_info.push_back(info);
    cout.precision(2);
    cout.setf(ios::fixed);
    cout<<names<<"\t"<<"Price:"<<x<<"K\t"<<"EPS:$"<<y<<"\n";
    cout<<"\n";
    return ;
}

void stock::change(){
    cout<<"After changing:"<<"\n";

    for(int i=0;i<stock_info.size();i++){
        int price_t=((rand()%201)+1)+899;
        float price_f=(float)price_t;
        price_f/=1000;
        //float price_t = 0.9f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (1.1f - 0.9f));
        int eps_t=(rand()%10)+1;
        stock_info[i].price*=price_f;
        stock_info[i].eps=eps_t;
        cout.precision(2);
        cout.setf(ios::fixed);
        cout<<stock_info[i].name<<"\t"<<"Price:"<<stock_info[i].price<<"K\t"<<"EPS:$"<<stock_info[i].eps<<"\n";
    }
    cout<<"\n";
    return;
}

void stock::purchase(string names,int shares){
    float price_t;
    price_t=price_search(names);
    bool flag=true;
    for(int i=0;i<stock_account.size();i++){
        if(names==stock_account[i].name){
            stock_account[i].share+=shares;
            float mult=price_t*shares/1000;
            stock_account[i].value+=mult;
            flag=false;
        }
    }

    if(flag){
        stock_p tmp;
        tmp.value=price_t*shares/1000;
        tmp.share=shares;
        tmp.name = names;
        stock_account.push_back(tmp);
    }

    balance-=(price_t*shares/1000);
    cout<<id<<" purchase "<<shares<<" shares of "<<names<<", which is worth ";
    cout.precision(2);
    cout.setf(ios::fixed);
    cout<<price_t*shares/1000<<"K\n";
    cout<<"\n";
    return;
}

void stock::sell(string names,int shares){
    float price_t;
    price_t=price_search(names);
    for(int i=0;i<stock_account.size();i++){
        if(names==stock_account[i].name){
            stock_account[i].share-=shares;
            float mult=price_t*shares/1000;
            stock_account[i].value-=mult;
        }
    }

    balance+=(price_t*shares/1000);
    cout<<id<<" sell "<<shares<<" shares of "<<names<<", which is worth ";
    cout.precision(2);
    cout.setf(ios::fixed);
    cout<<price_t*shares/1000<<"K\n";
    cout<<"\n";
    return;
}

void stock::show() const {
    float total=0;
    for(int i=0;i<stock_account.size();i++){
        float price_t=price_search(stock_account[i].name);
        float tmp=price_t*stock_account[i].share/1000;
        total+=tmp;
    }
    cout<<"Total stock value: "<<total<<"K\n\n";
    return ;
}

void stock::yield(string names) const {
    float price_t;
    price_t=price_search(names);
    for(int i=0;i<stock_account.size();i++){
        if(stock_account[i].name==names){
            float eps_s=eps_search(names);
            float d=(stock_account[i].share*eps_s)/(stock_account[i].value*1000);
            cout.precision(2);
            cout.setf(ios::fixed);
            cout<<id<<"\'s "<<names<<" stock has a dividend yield of "<<d*100<<"%"<<"\n";
        }
    }
    cout<<"\n";
    return ;
}

void stock::revenue() const{
    float total=0;
    float cost=0;
    cout<<id<<"\n";
    for(int i=0;i<stock_account.size();i++){
        cost+=stock_account[i].value;
        float price_t=price_search(stock_account[i].name);
        float tmp=price_t*stock_account[i].share/1000;
        total+=tmp;
        cout<<stock_account[i].share<<" shares of "<<stock_account[i].name;
        cout.precision(2);
        cout.setf(ios::fixed);
        cout<<"\t"<<tmp<<"K\n";
    }
    cout.precision(2);
    cout.setf(ios::fixed);
    cout<<"Total stock value: "<<total<<"K\n";
    cout<<"ROI : "<<((total-cost)/cost)*100<<"%\n";
    cout<<"\n";
    return ;
}


int stock::partition(vector<stock_p>& arr ,int low,int high) {
    int pivot=arr[high].price;
    int i=low-1;

    for (int j=low;j<high;j++) {
        if (arr[j].price>pivot) {
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}

void stock::quickSort(vector<stock_p>& arr,int low,int high) {
    if (low < high) {
        int pi = partition(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
    return;
}


void stock::s_rank(){
    cout<<"Order by price:"<<"\n";
    quickSort(stock_info, 0, stock_info.size()-1);
    for(int i=0;i<stock_info.size();i++){
        cout<<i+1<<"."<<stock_info[i].name<<"\t"<<"Price:"<<stock_info[i].price<<"K\t"<<"EPS:$"<<stock_info[i].eps<<"\n";
    }
    cout<<"\n";
    return ;
}

void stock::deposit(float amount){
    balance+=amount;
    cout<<id<<" deposit "<<amount<<"K"<<" to Stock Account"<<"\n";
    cout<<"\n";
    return ;
}

void stock::withdraw(float amount){
    balance-=amount;
    cout<<id<<" withdraw "<<amount<<"K"<<" from Stock Account"<<"\n";
    cout<<"\n";
    return ;
}

void stock::show_balance() const {
    cout<<id<<"'s Stock Account balance: "<<balance<<"K"<<"\n";
    cout<<"\n";
    return ;
}



float stock::total_asset() const{
    float total=0;
    for(int i=0;i<stock_account.size();i++){
        float price_t=price_search(stock_account[i].name);
        total+=(stock_account[i].share/1000*price_t);
    }
    return total+balance;
}


stock::~stock(){
    return;
}
