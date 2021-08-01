#ifndef OWNER_H
#define OWNER_H

#include <string>
#include <vector>
#include "property.h"

class Owner
{
public:
    /**
     * Empty constructor
    */
    Owner();

    /**
     * Constructor
     * 
     * Creates instance.
     * 
     * @param name Name of the owner
     * @param balance Balance value of the owner
    */
    Owner(const std::string &name, float balance);

    /**
     * Returns name of the owner
    */
    std::string &get_name();

    /**
     * Prints information about property:
     * 
     * If it is a person:
     * Name: <name> Age: <age>
     * If it is a corporation:
     * Name: <name> Address: <age>
    */
    virtual void print_info();

    /**
     * Adds property at the end of the property list.
     * 
     * @param property Pointer of the property
    */
    void add_property(Property *property);

    /**
     * Buy operation.
     * 
     * 1- Check balance
     * 2- Check whether the seller owns given property or not.
     * 3- Apply transaction if both OK.
     * 
     * @param property Pointer of the property
     * @param seller Pointer of the seller
    */
    void buy(Property *property, Owner *seller);

    /**
     * Sell operation.
     * 
     * 1- Check balance
     * 2- Check whether the seller owns given property or not.
     * 3- Apply transaction if both OK.
     * 
     * @param property Pointer of the property
     * @param buyer Pointer of the buyer
    */
    void sell(Property *property, Owner *buyer);

    /**
     * List wealth of the owner:
     * 
     * Properties of <name>
     * Balance: <balance>$
     * 1. <name of the property-1>
     * 2. <name of the property-2>
     * ....
     * n. <name of the property-n>
    */
    void list_properties();

protected:
    std::string name;
    float balance;
    std::vector<Property *> properties;
};

#endif //OWNER_H