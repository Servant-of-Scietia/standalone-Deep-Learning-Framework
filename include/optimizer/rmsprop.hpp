#ifndef RMSPROP_HPP
#define RMSPROP_HPP

#include "optimizer.hpp"

/**
 * @brief The RMSProp class represents the RMSProp optimizer.
 * RMSProp is an optimizer that utilizes the magnitude of recent gradients to normalize the gradients.
 */
class RMSProp : public Optimizer
{
    double mLearningRate;
    double mDecayRate;
    double mDelta;
    std::vector<Tensor<double>> mCache;

public:

    /**
     * @brief Constructs a new RMSProp object.
     * @param learningRate The learning rate.
     * @param decayRate The decay rate.
     * @param delta The delta.
     * @param initialCache The initial cache.
     */
    RMSProp(double learningRate, double decayRate = 0.9, double delta = 1e-7, std::vector<Tensor<double>> initialCache = {});

    ~RMSProp() = default;

    /**
     * @brief Initializes the optimizer.
     * @param rLearnableParameters The learnable parameters.
     */
    void __init__(const std::vector<std::shared_ptr<Variable>> & rLearnableParameters) override;

    /**
     * @brief Updates the learnable parameters using the RMSProp algorithm.
     * @param rLearnableParameters The learnable parameters.
     */
    void update(const std::vector<std::shared_ptr<Variable>> & rLearnableParameters) override;
};

#endif // RMSPROP_HPP