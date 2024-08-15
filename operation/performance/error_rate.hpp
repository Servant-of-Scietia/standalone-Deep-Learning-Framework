#ifndef ERROR_RATE_HPP
#define ERROR_RATE_HPP

#include "performance_function.hpp"

/**
 * @brief the error rate operation is used to calculate the error rate of the model.
 */
class ErrorRate : public PerformanceFunction
{
public:
    /**
     * @brief constructor for the error rate operation
     */
    ErrorRate() { mName = "ERROR_RATE"; };
    ~ErrorRate() = default;

    /**
     * @brief calculate the error rate of the input tensors
     * @param inputs The input tensors
     * @note The first input tensor is the prediction and the second input tensor is the target.
     */
    void f(std::vector<std::shared_ptr<Variable>> &inputs) override;
};

void ErrorRate::f(std::vector<std::shared_ptr<Variable>> &inputs)
{
    if (inputs.size() != 2)
    {
        throw std::runtime_error("ErrorRate: number of inputs is not 2");
    }

    if (inputs[1]->getData()->shape(1) != 1)
    {
        throw std::runtime_error("ErrorRate: the target tensor must be 1D");
    }

    if (inputs[0]->getData()->shape(0) != inputs[1]->getData()->shape(0))
    {
        throw std::runtime_error("ErrorRate: the size of the prediction and target tensor must be the same");
    }

    double error = 0;
    for (std::uint32_t i = 0; i < inputs[0]->getData()->shape(0); i++)
    {
        double max = inputs[0]->getData()->at({i, 0});
        std::uint32_t maxIndex = 0;
        for (std::uint32_t j = 1; j < inputs[0]->getData()->shape(1); j++)
        {
            if (inputs[0]->getData()->at({i, j}) > max)
            {
                max = inputs[0]->getData()->at({i, j});
                maxIndex = j;
            }
        }
        if (maxIndex != inputs[1]->getData()->at({i}))
        {
            error++;
        }
    }
    std::cout << "Test error rate: " << error / inputs[0]->getData()->shape(0) << "%" << std::endl;
}

#endif // ERROR_RATE_HPP