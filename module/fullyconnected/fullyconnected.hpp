#ifndef FULLYCONNECTED_HPP
#define FULLYCONNECTED_HPP

#include "../../operation/matmul.hpp"
#include "../../operation/processing/padding.hpp"
#include "../../operation/activation_function/activation_function.hpp"
#include "../../operation/parameter_norm_penalties/parameter_norm_penalty.hpp"
#include "../../weight_initialization/weight_initializer.hpp"
#include "../module.hpp"

/**
 * @brief The fully connected module is intended
 for creating a fully connected layer without activation function in the graph.
 It's the base class for the dense and output modules.
 */
class FullyConnected : public Module
{
protected:
    // storing index of the variables in the graph
    std::shared_ptr<Variable> mpWeightMatrixVariable; // learnable parameters of the layer (weights + bias)
    std::shared_ptr<Variable> mpMatmulVariable; // multiplication of the input and the weights
    std::shared_ptr<Variable> mpActivationVariable; // activation function applied
    std::shared_ptr<Variable> mpPaddingVariable; // used to pad the input with 1s for the bias
    std::shared_ptr<Variable> mpNormVariable; // used to compute a norm of the weights

    std::shared_ptr<WeightInitializer> mpWeightInitializer = std::make_shared<NormalizedInitialization>(); // weight initializer

    static std::shared_ptr<ParameterNormPenaltyVariant> mpsDefaultNorm; // default norm to use
    std::shared_ptr<Operation> mpNorm = nullptr; // norm to use for regularization

    void addInput(const std::shared_ptr<Variable> &input, const std::uint32_t &inputSize) override;
    void addOutput(const std::shared_ptr<Variable> &output) override;
public:
    /**
     * @brief add a fully connected layer to the graph
     * @param units the number of neurons in the layer
     * @param name the name of the module
     */
    explicit FullyConnected( std::uint32_t units, const std::string &name = "" );

    /**
     * @brief initialize the weight matrix of the layer with random values
     * @param inputUnits the number of weights each neuron has
     */
    void createWeightMatrix(std::uint32_t inputUnits);

    /**
     * @brief Set the default norm to use for regularization.
     * Layers are initialized with this norm if no other norm is specified.
     * @param norm the norm to use
     */
    static void setDefaultNorm(ParameterNormPenaltyVariant const & norm)
    {
        mpsDefaultNorm = std::make_shared<ParameterNormPenaltyVariant>(norm);
    }

};

inline FullyConnected::FullyConnected(const std::uint32_t units, const std::string &name) : Module(name)
{
    mUnits = units; // set the number of neurons in the layer

    // create the variables

    mpPaddingVariable = GRAPH->addVariable(std::make_shared<Variable>(Variable(std::make_shared<Padding>(Padding(0,1,1)), {}, {}))); // pad for weights
    
    mpWeightMatrixVariable = GRAPH->addVariable(std::make_shared<Variable>(Variable(nullptr, {}, {}))); // nullptr because there is no operation

    mpMatmulVariable = GRAPH->addVariable(std::make_shared<Variable>(Variable(std::make_shared<Matmul>(Matmul()), {mpPaddingVariable,mpWeightMatrixVariable}, {})));


    // connections within the module
    mpPaddingVariable->getConsumers().push_back(mpMatmulVariable);
    mpWeightMatrixVariable->getConsumers().push_back(mpMatmulVariable);
}

inline void FullyConnected::createWeightMatrix(std::uint32_t inputUnits)
{
    mpWeightMatrixVariable->getData() = std::make_shared<Tensor<double>>(Tensor<double>({inputUnits+1, mUnits})); // initialize the weights randomly

    // initialize the weights randomly
    mpWeightInitializer->createRandomEngine(inputUnits, mUnits);
    std::vector<double> weights = mpWeightInitializer->createRandomVector();

    for (std::uint32_t i = 0; i < inputUnits; i++) // load the weights into the weight matrix
    {
        for (std::uint32_t j = 0; j < mUnits; j++)
        {
            mpWeightMatrixVariable->getData()->set({i, j}, weights[i*mUnits+j]);
        }
    }

    // initialize the bias
    double bias = 0.0;
    
    std::type_info const & type = typeid(mpActivationVariable->getOperation());
    if (type == typeid(ReLU))
    {
        bias = 0.1;
    }

    for (std::uint32_t j = 0; j < mUnits; j++)
    {
        mpWeightMatrixVariable->getData()->set({inputUnits, j}, bias);
    }
    
}


std::shared_ptr<ParameterNormPenaltyVariant> FullyConnected::mpsDefaultNorm = nullptr;

#endif // FULLYCONNECTED_HPP