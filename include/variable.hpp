#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "datatypes/tensor.hpp"
#include "operation/operation.hpp"

class Operation;

/**
 * @brief The variable class is an implementation of a variable in a computational graph.
 * It is used to store data and owns a pointer to the operation that calculates the data.
 */
class Variable
{
    std::vector<std::shared_ptr<Variable>> mChildren, mParents; // the children and parents of the variable in the computational graph
    std::shared_ptr<Operation> mpOperation;                     // the operation that calculates the data
    std::shared_ptr<Tensor> mpDataTensor;               // the data of the variable
    static std::uint32_t msCounter;                             // keep track of the number of variables created
    std::uint32_t mId;                                          // the unique id of the variable
    std::string mOperationName;                                 // the name of the operation that calculates the data

public:
    /**
     * @brief Construct a new Variable object.
     * @param op The operation that calculates the data.
     * @param parents The parents of the variable.
     * @param children The children of the variable.
     * @param data The initial data of the variable.
     */
    explicit Variable(const std::shared_ptr<Operation> &op, const std::vector<std::shared_ptr<Variable>> &parents = {}, const std::vector<std::shared_ptr<Variable>> &children = {}, const std::shared_ptr<Tensor> &data = nullptr);

    ~Variable() = default;

    /**
     * @brief This function returns the operation that calculates the data.
     * @return std::shared_ptr<Operation> The operation that calculates the data.
     */
    std::shared_ptr<Operation> getOperation();

    /**
     * @brief This function sets the operation that calculates the data.
     * @param op The new operation that calculates the data.
     */
    void setOperation(const std::shared_ptr<Operation> &op);

    /**
     * @brief This function returns the children of the variable.
     * @return std::vector<std::shared_ptr<Variable>> The children of the variable.
     */
    std::vector<std::shared_ptr<Variable>> &getConsumers();

    /**
     * @brief This function returns the parents of the variable.
     * @return std::vector<std::shared_ptr<Variable>> The parents of the variable.
     */
    std::vector<std::shared_ptr<Variable>> &getInputs();

    /**
     * @brief This function returns the data of the variable.
     * @return std::shared_ptr<Tensor> The data of the variable.
     */
    std::shared_ptr<Tensor> &getData();

    /**
     * @brief This function sets the data of the variable.
     * @param data The new data of the variable.
     */
    void setData(const std::shared_ptr<Tensor> &data);

    /**
     * @brief This function returns the id of the variable.
     * @return std::uint32_t The id of the variable.
     */
    [[nodiscard]] std::uint32_t getId() const;

    static void connectVariables(const std::shared_ptr<Variable> &parent, const std::shared_ptr<Variable> &child);
    static void disconnectVariables(const std::shared_ptr<Variable> &parent, const std::shared_ptr<Variable> &child);
};

#endif // VARIABLE_HPP