//
// Created by servant-of-scietia on 20.09.24.
//
#include "operation/parameter_norm_penalties/L2_Norm.hpp"

void L2Norm::f(std::vector<std::shared_ptr<Variable>>& inputs)
{
    if (inputs.size() != 1)
    {
        throw std::runtime_error("L2Norm: number of inputs is not 1");
    }

    auto input = inputs[0]->getData();
    auto result = std::make_shared<Tensor>(Tensor({1}));

    double sum = 0;
    for (std::uint32_t i = 0; i < input->capacity(); i++)
    {
        if ((i-1) % input->shape(0) == 0) // no penalty on the bias
        {
            continue;
        }
        sum += input->at({i}) * input->at({i});
    }

    result->set({0}, 0.5 * _lambda * sum);

    this->getVariable()->getData() = result;
}


std::shared_ptr<Tensor> L2Norm::bprop(std::vector<std::shared_ptr<Variable>>& inputs, std::shared_ptr<Variable> & focus, std::shared_ptr<Tensor> & gradient)
{
    if (inputs.size() != 1)
    {
        throw std::runtime_error("L2Norm: number of inputs is not 1");
    }
    if (gradient->shape() != std::vector<size_t>({1}))
    {
        throw std::runtime_error("L2Norm: gradient shape is not {1}");
    }

    auto input = inputs[0]->getData();
    auto result = std::make_shared<Tensor>(input->shape());

    for (std::uint32_t i = 0; i < input->capacity(); i++)
    {
        if ((i-1) % input->shape(0) == 0) // no penalty on the bias
        {
            result->set(i, 0);
        }
        else
        {
            result->set(i, _lambda * input->at(i));
        }
    }

    return result;
}