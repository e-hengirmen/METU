#ifndef VILLA_H
#define VILLA_H

#include "property.h"

class Villa : public Property
{
public:
    /**
     * Constructor
     * 
     * Creates instance and add it to the owner's property list if the owner is not NULL.
     * 
     * @param property_name Name of the property
     * @param area area of the property
     * @param owner owner of the property
     * @param number_of_floors number of floors
     * @param having_garden whether have a backyard
    */
    Villa(const std::string &property_name, int area, Owner *owner, int number_of_floors, bool having_garden);

    /**
     * Valuation method
     * 
     * area*10 * (number_of_floors) * (2 if have garden)
     * 
     */
    float valuate();

private:
    int number_of_floors;
    bool having_garden;
};

#endif //VILLA_H