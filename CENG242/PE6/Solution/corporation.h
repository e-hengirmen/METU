#ifndef CORPORATION_H
#define CORPORATION_H

#include <string>
#include "owner.h"

using namespace std;

class Corporation : public Owner
{
public:
    /** 
     * Constructor of Person class
     * 
     * Creates instance and add it to the owner's property list if the owner is not NULL.
     * 
     * @param name Name of the corporation
     * @param balance Balance value of the corporation
     * @param address Address of the corporation
    */
    Corporation(const std::string &name, float balance, std::string address);

    /**
     * Prints information about corporation:
     * 
     * Name: <name> Address: <age>
    */
    void print_info();

private:
    std::string address;
};

#endif //CORPORATION_H