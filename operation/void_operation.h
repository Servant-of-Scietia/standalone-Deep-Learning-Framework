#ifndef VOID_OPERATION_INCLUDE_GUARD
#define VOID_OPERATION_INCLUDE_GUARD

#include "operation.h"

/**
 * @brief VOID_OPERATION class is a class for creating an operation that does nothing.
*/
class VOID_OPERATION : public OPERATION
{
public:
    void f(){};
    std::vector<double> bprop(std::vector<double> & gradient){};
};