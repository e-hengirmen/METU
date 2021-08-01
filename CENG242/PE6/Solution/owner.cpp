#include <iostream>
#include <string>
#include <vector>
#include "owner.h"

using namespace std;


Owner::Owner()
{
}

Owner::Owner(const string &name, float balance)
{
    this->name=name;
    this->balance=balance;
}

void Owner::print_info()
{
}

string &Owner::get_name()
{
    return name;
}

void Owner::add_property(Property *property)
{
    properties.push_back(property);
}

void Owner::buy(Property *property, Owner *seller)
{
    float val=property->valuate();
    cout<<"[BUY] Property: "<<property->get_name()
                <<" Value: "<<val<<"$ "
                <<seller->get_name()<<"--->"<<get_name()<<endl;
                
    if(balance>=val){
        
        unsigned int i=0;
        bool flag=false;
        for(;i<seller->properties.size();i++){
            if(seller->properties[i]==property){
                flag=true;
                break;
            }
        }
        
        if(flag){
            
            balance-=val;
            seller->balance+=val;
            
            property->set_owner(this);
            add_property(property);
            seller->properties.erase(seller->properties.begin()+i);
        }
        else{
            cout<<"[ERROR] Transaction  on  unowned  property"<<endl;
        }
    }
    else{
        cout<<"[ERROR] Unaffordable  property"<<endl;
    }
}

void Owner::sell(Property *property, Owner *owner)
{
    float val=property->valuate();
    
    cout<<"[SELL] Property: "<<property->get_name()
                <<" Value: "<<val<<"$ "
                <<get_name()<<"--->"<<owner->get_name()<<endl;
                
                
    if(owner->balance>=val){
        
        unsigned int i=0;
        bool flag=false;
        for(;i<properties.size();i++){
            if(properties[i]==property){
                flag=true;
                break;
            }
        }
        
        if(flag){
            
            balance+=val;
            owner->balance-=val;
            
            property->set_owner(owner);
            owner->add_property(property);
            properties.erase(properties.begin()+i);
        }
        else{
            cout<<"[ERROR] Transaction  on  unowned  property"<<endl;
        }
    }
    else{
        cout<<"[ERROR] Unaffordable  property"<<endl;
    }
}

void Owner::list_properties()
{
    cout<<"Properties of "<<name<<":"<<endl
        <<"Balance: "<<balance<<"$"<<endl;
        
    for(unsigned int i=0;i<properties.size();i++){
        cout<<i+1<<". "<<properties[i]->get_name()<<endl;
    }

}






