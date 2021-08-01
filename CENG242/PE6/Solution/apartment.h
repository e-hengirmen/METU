#ifndef APARTMENT_H
#define APARTMENT_H

#include "property.h"

class Apartment : public Property
{
public:
    Apartment(const std::string &property_name, int area, Owner *owner, int floor, bool having_elevator);
    float valuate();

private:
    int floor;
    bool having_elevator;
};

#endif //APARTMENT_H