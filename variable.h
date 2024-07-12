#ifndef VARIABLE_INCLUDE_GUARD
#define VARIABLE_INCLUDE_GUARD

#include "dependencies.h"
#include "tensor.h"
#include "operation/operation.h"

class OPERATION;

/**
 * @brief VARIABLE class is a wrapper class for OPERATION class. It is used to create a graph of operations.
*/
class VARIABLE
{
    std::vector<std::shared_ptr<VARIABLE>> __children, __parents;
    std::shared_ptr<OPERATION> __op;
    std::shared_ptr<TENSOR<double>> __data;
    static int __counter; // keep track of the number of variables created
    int __id;

public:
    VARIABLE(const std::shared_ptr<OPERATION> & op, const std::vector<std::shared_ptr<VARIABLE>> & parents = {}, const std::vector<std::shared_ptr<VARIABLE>> & children = {}, const std::shared_ptr<TENSOR<double>> & data = nullptr);
    VARIABLE(std::shared_ptr<VARIABLE> & var)
    {
        throw std::runtime_error("A variable should not be copied. Use a shared pointer instead.");
    }
    VARIABLE & operator=(std::shared_ptr<VARIABLE> & var)
    {
        throw std::runtime_error("A variable should not be copied. Use a shared pointer instead.");
    }
    VARIABLE(VARIABLE && var)
    {
        std::cout << "VARIABLE MOVE CONSTRUCTOR" << std::endl;
    }
    VARIABLE & operator=(VARIABLE && var)
    {
        throw std::runtime_error("A variable should not be moved. Use a shared pointer instead.");
    }
    ~VARIABLE()
    {
    
    }
    std::shared_ptr<OPERATION> get_operation();
    std::vector<std::shared_ptr<VARIABLE>> & get_consumers();
    std::vector<std::shared_ptr<VARIABLE>> & get_inputs();
    std::shared_ptr<TENSOR<double>> & get_data();
    int get_id();
};


VARIABLE::VARIABLE(const std::shared_ptr<OPERATION> & op, const std::vector<std::shared_ptr<VARIABLE>> & parents, const std::vector<std::shared_ptr<VARIABLE>> & children, const std::shared_ptr<TENSOR<double>> & data)
{
    __id = __counter++;
    __op = op;
    __parents = parents;
    __children = children;
    __data = data;
};


/**
 * @brief returns the operation object
*/
std::shared_ptr<OPERATION> VARIABLE::get_operation()
{
    return __op;
}

/**
 * @brief returns the children of the variable
*/
std::vector<std::shared_ptr<VARIABLE>> & VARIABLE::get_consumers()
{
    return __children;
}

/**
 * @brief returns the parents of the variable
*/
std::vector<std::shared_ptr<VARIABLE>> & VARIABLE::get_inputs()
{
    return __parents;
}

/**
 * @brief returns the data of the operation
*/
std::shared_ptr<TENSOR<double>> & VARIABLE::get_data()
{
    return __data;
}

/**
 * @brief returns the id of the variable
*/
int VARIABLE::get_id()
{
    return __id;
}

int VARIABLE::__counter = 0;

#endif