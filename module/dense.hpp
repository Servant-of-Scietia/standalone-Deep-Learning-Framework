#ifndef DENSE_HPP
#define DENSE_HPP

#include "./module.hpp"
#include "../operation/matmul.hpp"
#include "../operation/processing/padding.hpp"
#include "../operation/activation_function/activation_function.hpp"
#include "../operation/norm/norm.hpp"

/**
 * @brief the dense module is intended for creating a dense (fully connected) layer in the graph. It owns 1 input and 1 output variable.
 */
class Dense : public Module
{
    // storing index of the variables in the graph
    std::shared_ptr<Variable> _weight_matrix_variable; // learnable parameters of the layer (weights + bias)
    std::shared_ptr<Variable> _matmul_variable; // multiplication of the input and the weights
    std::shared_ptr<Variable> _activation_variable; // activation function applied
    std::shared_ptr<Variable> _padding_variable; // used to pad the input with 1s for the bias
    std::shared_ptr<Variable> _norm_variable; // used to compute a norm of the weights

    static std::shared_ptr<NormVariant> _default_norm; // default norm to use
    std::shared_ptr<Operation> _norm = nullptr; // norm to use for regularization


public:
    /**
     * @brief add a dense layer to the graph
     * @param activation_function the operation representing the activation function.
     * @param units the number of neurons in the layer.
     */
    Dense(ActivationVariant activation_function, std::uint32_t units);
    /**
     * @brief add a dense layer to the graph
     * @param activation_function the operation representing the activation function.
     * @param units the number of neurons in the layer.
     * @param norm the norm to use for regularization.
     */
    Dense(ActivationVariant activation_function, std::uint32_t units, NormVariant norm);
    ~Dense() = default;
    /**
     * @brief used to mark variables as input for the module.
     */
    void add_input(std::shared_ptr<Variable> input, std::uint32_t input_units) override
    {
        _padding_variable->get_inputs().push_back(input);
        
        // init default norm
        if(_norm == nullptr && _default_norm != nullptr)
        {
            _norm = std::visit([](auto&& arg) {
                // Assuming all types in the variant can be dynamically casted to Operation*
                return std::shared_ptr<Operation>(std::make_shared<std::decay_t<decltype(arg)>>(arg));}, *_default_norm);
        }
        
        // +1 for the weight
        _weight_matrix_variable->get_data() = std::make_shared<Tensor<double>>(Tensor<double>({input_units+1,__units})); // initialize the weights randomly
        
        if (_norm != nullptr) // adding norm to activation function
        {
            _norm_variable = __graph->add_variable(std::make_shared<Variable>(Variable(_norm, {_weight_matrix_variable}, {})));
            __graph->add_output(_norm_variable);    
            _weight_matrix_variable->get_consumers().push_back(_norm_variable);
        }
    }
    /**
     * @brief used to mark variables as output for the module.
     */
    void add_output(std::shared_ptr<Variable> output) override
    {
        _activation_variable->get_consumers().push_back(output);
    }
    /**
     * @brief used to get the input variables of the module specified by the index.
     */
    std::shared_ptr<Variable> input(std::uint32_t index) override
    {
        return _padding_variable;
    }
    /**
     * @brief used to get the output variables of the module specified by the index.
     */
    std::shared_ptr<Variable> output(std::uint32_t index) override
    {
        return _activation_variable;
    }
    /**
     * @brief used to set the default norm to use for regularization.
     */
    static void set_default_norm(NormVariant const & norm)
    {
        _default_norm = std::make_shared<NormVariant>(norm);
    }
};

Dense::Dense(ActivationVariant activation_function, std::uint32_t units)
{
    // error checks
    if(__graph == nullptr)
    {
        throw std::runtime_error("graph is not set");
    }
    __units = units; // set the number of neurons in the layer

    // create the variables

    _padding_variable = __graph->add_variable(std::make_shared<Variable>(Variable(std::make_shared<Padding>(Padding(0,1,1)), {}, {}))); // pad for weights
    
    _weight_matrix_variable = __graph->add_variable(std::make_shared<Variable>(Variable(nullptr, {}, {}))); // nullptr because there is no operation
    __learnable_parameters.push_back(_weight_matrix_variable);

    _matmul_variable = __graph->add_variable(std::make_shared<Variable>(Variable(std::make_shared<Matmul>(Matmul()), {_padding_variable,_weight_matrix_variable}, {})));

    // turning the variant into a shared pointer to the operation class
    // Use std::visit to handle the variant
    std::shared_ptr<Operation> operation_ptr = std::visit([](auto&& arg) {
        // Assuming all types in the variant can be dynamically casted to Operation*
        return std::shared_ptr<Operation>(std::make_shared<std::decay_t<decltype(arg)>>(arg));}, ActivationVariant{activation_function});

    _activation_variable = __graph->add_variable(std::make_shared<Variable>(Variable(operation_ptr, {_matmul_variable}, {})));

    // conections within the module
    _padding_variable->get_consumers().push_back(_matmul_variable);
    _weight_matrix_variable->get_consumers().push_back(_matmul_variable);
    
    _matmul_variable->get_consumers().push_back(_activation_variable);    

    
}

Dense::Dense(ActivationVariant activation_function, std::uint32_t units, NormVariant norm)
{
    _norm = std::visit([](auto&& arg) {
        // Assuming all types in the variant can be dynamically casted to Operation*
        return std::shared_ptr<Operation>(std::make_shared<std::decay_t<decltype(arg)>>(arg));}, norm);
    Dense(activation_function, units);
}

std::shared_ptr<NormVariant> Dense::_default_norm = nullptr;

#endif // DENSE_HPP