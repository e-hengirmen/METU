#include <iostream>
#include "villa.h"
#include "owner.h"

using namespace std;

Villa::Villa(const string &property_name, int area, Owner *owner, int number_of_floors, bool having_garden)
:Property(property_name,area,owner),number_of_floors(number_of_floors),having_garden(having_garden)
{
}

float Villa::valuate()
{
    return area*10*number_of_floors*(1+having_garden);
}