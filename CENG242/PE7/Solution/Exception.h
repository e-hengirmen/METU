#pragma once

#include <exception>
using namespace std;

//////////////////////////////////////////////////////
// // // // // DO NOT CHANGE THIS FILE! // // // // //
//////////////////////////////////////////////////////
class InvalidRequest : public exception {

    /* This exception class is used when the data request comes for a non-data node.
    */

public:
    virtual const char* what() const throw() {
        return "This is not data node!";
    }
};