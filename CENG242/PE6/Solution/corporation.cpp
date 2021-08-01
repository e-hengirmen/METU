#include <iostream>
#include "corporation.h"

using namespace std;

Corporation::Corporation(const string &name, float balance, string address)
:Owner(name,balance),address(address)
{
}

void Corporation::print_info()
{
    cout<<"Name: "<<name<<" Address: "<<address<<endl;
}