#ifndef L1_NORM_HPP
#define L1_NORM_HPP

#include "parameter_norm_penalty.hpp"

/**
 * @brief Used to add a L1 norm penalty to a weight matrix. This is used to prevent overfitting.
 */
class L1Norm : public ParameterNormPenalty
{
public:
    /**
    * @brief add a L1 norm penalty to the graph
    * @param lambda the lambda value to be used
    */
    L1Norm(double lambda) : ParameterNormPenalty(lambda) { mName = "L1Norm"; };
    ~L1Norm() = default;
    /**
    * @brief compute the L1 norm of the input tensor
    */
    void f(std::vector<std::shared_ptr<Variable>>& inputs) override;
    /**
    * @brief compute the gradient of the L1 norm penalty with respect to the input tensor
    * @param inputs the parents of the variable
    * @param focus this is the only variable everything else is constant
    * @param gradient the sum of the gradients of the consumers
    */
    std::shared_ptr<Tensor<double>> bprop(std::vector<std::shared_ptr<Variable>>& inputs, std::shared_ptr<Variable> & focus, std::shared_ptr<Tensor<double>> & gradient) override;
};

#endif // L1_NORM_HPP