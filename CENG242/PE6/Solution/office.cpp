#include <iostream>
#include "office.h"
#include "owner.h"

using namespace std;

Office::Office(const string &property_name, int area, Owner *owner, bool having_wifi, bool having_reception)
:Property(property_name,area,owner),having_wifi(having_wifi),having_reception(having_reception)
{
}

float Office::valuate()
{
    return area*5*(1+0.3*having_wifi)*(1+0.5*having_reception);
}