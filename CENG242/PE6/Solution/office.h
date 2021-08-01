#ifndef OFFICE_H
#define OFFICE_H

#include "property.h"

class Office : public Property
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
     * @param having_wifi whether have provided wifi
     * @param having_reception whether have provided reception
    */
    Office(const std::string &property_name, int area, Owner *owner, bool having_wifi, bool having_reception);

    /**
     * Valuation method
     * 
     * area*5 * (1.3 if have wifi) * (1.5 if have reception)
     * 
     */
    float valuate();

private:
    bool having_wifi;
    bool having_reception;
};

#endif //OFFICE_H