#include <iostream>
#include "person.h"

using namespace std;

Person::Person(const string &name, float balance, int age)
:Owner(name,balance),age(age)
{
}

void Person::print_info()
{
    cout<<"Name: "<<name<<" Age: "<<age<<endl;
}