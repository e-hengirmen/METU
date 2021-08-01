#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

class Owner;

class Property
{
public:
    /**
     * Empty constructor
    */
    Property();

    /**
     * Constructor
     * 
     * Creates instance and add it to the owner's property list if the owner is not NULL.
     * 
     * @param property_name Name of the property
     * @param area area of the property
     * @param owner owner of the property
    */
    Property(const std::string &property_name, int area, Owner *owner);

    /**
     * Returns name of the property
    */
    std::string &get_name();

    /**
     * Prints information about property:
     * 
     * If has owner:
     * <name of the property> (<area> m2) Owner: <name of the owner>
     * If it is NULL:
     * <name of the property> (<area> m2) Owner: No owner
     * 
    */
    void print_info();

    /**
     * Sets owner information
     * 
     * @param owner owner of the property (owner pointer or NULL)
    */
    void set_owner(Owner *owner);

    /**
     * Valuation method
    */
    virtual float valuate();

protected:
    std::string property_name;
    int area;
    Owner *owner;
};

#endif //PROPERTY_H