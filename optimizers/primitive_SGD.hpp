#ifndef PRIMITIVESGD_HPP
#define PRIMITIVESGD_HPP

#include "optimizer.hpp"
#include "../module/module.hpp"

/**
 * @brief The PrimitiveSGD class is a simple implementation of the stochastic gradient descent algorithm.
 */
class PrimitiveSGD : public Optimizer
{
    double mInitialLearningRate;
    double mDecayRate;

public:
    PrimitiveSGD(double initialLearningRate, double decayRate);
    ~PrimitiveSGD() = default;

    void update(const std::vector<std::shared_ptr<Variable>> & rLearnableParameters, std::uint32_t batchSize) override;
};

PrimitiveSGD::PrimitiveSGD(double initialLearningRate, double decayRate)
{
    mInitialLearningRate = initialLearningRate;
    mDecayRate = decayRate;
}

void PrimitiveSGD::update(const std::vector<std::shared_ptr<Variable>> & rLearnableParameters, std::uint32_t batchSize)
{
    for(std::uint32_t i = 0; i < rLearnableParameters.size(); i++)
    {
        for(std::uint32_t j = 0; j < rLearnableParameters[i]->getData()->capacity(); j++)
        {
            rLearnableParameters[i]->getData()->subtract(j, mInitialLearningRate * GRAPH->getGradient(rLearnableParameters[i])->at(j) / batchSize);
        }
    }
    mInitialLearningRate *= mDecayRate; // decay the learning rate
}

#endif // PRIMITIVESGD_HPP