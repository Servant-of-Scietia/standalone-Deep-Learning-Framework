#ifndef ONE_HOT_INCLUDE_GUARD
#define ONE_HOT_INCLUDE_GUARD

#include "../operation.h"

/**
 * @brief One hot encoding class, used to perform one hot encoding on the input tensor. Only supporting forward pass.
*/
class OneHot : public Operation
{
    std::uint32_t _size; // size of the one hot encoding
    double _on_value;
    double _off_value;

public:
    /**
     * @brief One hot encoding constructor.
     * @param size The size of the one hot encoding.
     * @param on_value The value to set the one hot encoding to.
     * @param off_value The value to set the rest of the tensor to.
     */
    OneHot(std::uint32_t size, double on_value, double off_value);
    ~OneHot() = default;

    /**
     * @brief Perform one hot encoding on the input tensor.
     */
    void f(std::vector<std::shared_ptr<Variable>>& inputs)override;

    /**
     * @brief Backward pass is not supported for one hot encoding.
     */
    std::shared_ptr<Tensor<double>> bprop(std::vector<std::shared_ptr<Variable>>& inputs, std::shared_ptr<Variable> & focus, std::shared_ptr<Tensor<double>> & gradient)override;
};

OneHot::OneHot(std::uint32_t size, double on_value, double off_value)
{
    _size = size;
    _on_value = on_value;
    _off_value = off_value;
    __dbg_name = "ONE_HOT";
}

void OneHot::f(std::vector<std::shared_ptr<Variable>>& inputs)
{
    // might try assigning input values to indices in the future
    if (inputs.size() != 1)
    {
        throw std::invalid_argument("OneHot::f: Invalid number of input variables.");
    }

    std::shared_ptr<Tensor<double>> _data = std::make_shared<Tensor<double>>(Tensor<double>({inputs.front()->get_data()->shape(0), _size}, _off_value)); // create a new tensor to store the result

    for (std::uint32_t i = 0; i < inputs.front()->get_data()->shape(0); i++)
    {
        if (inputs.front()->get_data()->at({i, 0}) >= _size)
        {
            throw std::invalid_argument("OneHot::f: Input value is larger than the size of the one hot encoding.");
        }
        _data->set({i, static_cast<std::uint32_t>(inputs.front()->get_data()->at({i, 0}))}, _on_value);
    }

    this->get_variable()->get_data() = _data; // store the result in the variable
}

std::shared_ptr<Tensor<double>> OneHot::bprop(std::vector<std::shared_ptr<Variable>>& inputs, std::shared_ptr<Variable> & focus, std::shared_ptr<Tensor<double>> & gradient)
{
    throw std::invalid_argument("OneHot::bprop: Backward pass is not supported for one hot encoding.");
}

#endif // ONE_HOT_INCLUDE_GUARD
    