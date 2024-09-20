//
// Created by servant-of-scietia on 20.09.24.
//
#include "operation/loss_functions/loss_function.hpp"

std::shared_ptr<Tensor<double>> LossFunction::bprop(std::vector<std::shared_ptr<Variable>> &inputs, std::shared_ptr<Variable> &focus, std::shared_ptr<Tensor<double>> &gradient)
{
    return std::make_shared<Tensor<double>>(Tensor<double>(focus->getData()->shape(), 0)); // return a tensor with the same shape as the focus variable filled with zeros (this variable has no gradient)
}