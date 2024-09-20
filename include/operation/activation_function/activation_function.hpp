#ifndef ACTIVATIONFUNCTION_HPP
#define ACTIVATIONFUNCTION_HPP

#include"operation/operation.hpp"

/**
 * @brief Base class for operation functions. Template class to create an activation function that executes elementwise.
 */
class ActivationFunction : public Operation
{
public:
    /**
     * @brief Construct a new ActivationFunction object
     */
    ActivationFunction() { mName = "ActivationFunction"; }
    /**
     * @brief Forward pass is similar for all activation functions. It applies the activation function to each element of the input tensor.
     */
    void f(std::vector<std::shared_ptr<Variable>>& inputs) override;
    /**
     * @brief Backward pass is similar for all activation functions. It applies the derivative of the activation function to each element of the gradient tensor.
     */
    std::shared_ptr<Tensor<double>> bprop(std::vector<std::shared_ptr<Variable>>& inputs, std::shared_ptr<Variable> & focus, std::shared_ptr<Tensor<double>> & gradient) override;

    /**
     * @brief Activation function to be implemented by the derived class.
     */
    virtual double activationFunction(double x) = 0;
    /**
     * @brief Derivative of the activation function to be implemented by the derived class.
     */
    virtual double activationFunctionDerivative(double x) = 0;
};

// include all the activation functions to create an ActivationFunction_VARIANT

#include "rectified_linear_unit.hpp"
#include "hyperbolic_tangent.hpp"
#include "linear.hpp"
#include "heavyside_step.hpp"
#include "sigmoid.hpp"
#include "softmax.hpp"

using ActivationVariant = std::variant<ReLU, HyperbolicTangent, Sigmoid, Linear, Sigmoid, Softmax>;

#endif // ACTIVATIONFUNCTION_HPP