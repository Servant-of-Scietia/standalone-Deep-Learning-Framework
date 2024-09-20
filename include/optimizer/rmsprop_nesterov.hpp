#ifndef RMSPROP_NESTEROV_HPP
#define RMSPROP_NESTEROV_HPP

#include "optimizer.hpp"

/**
 * @brief The RMSPropNesterov class represents the RMSProp optimizer with Nesterov momentum.
 * RMSProp is an optimizer that utilizes the magnitude of recent gradients to normalize the gradients.
 */
class RMSPropNesterov : public Optimizer
{
    double mLearningRate;
    double mDecayRate;
    double mDelta;
    double mMomentum;
    std::vector<Tensor<double>> mCache;
    std::vector<Tensor<double>> mVelocity;

public:

    /**
     * @brief Constructs a new RMSPropNesterov object.
     * @param learningRate The learning rate.
     * @param decayRate The decay rate.
     * @param delta The delta.
     * @param momentum The momentum.
     * @param initialCache The initial cache.
     * @param initialVelocity The initial velocity.
     */
    RMSPropNesterov(double learningRate, double decayRate = 0.9, double delta = 1e-7, double momentum = 0.9, std::vector<Tensor<double>> initialCache = {}, std::vector<Tensor<double>> initialVelocity = {});

    ~RMSPropNesterov() = default;

    /**
     * @brief Initializes the optimizer.
     * @param rLearnableParameters The learnable parameters.
     */
    void __init__(const std::vector<std::shared_ptr<Variable>> & rLearnableParameters) override;

    /**
     * @brief Updates the learnable parameters using the RMSProp with Nesterov momentum algorithm.
     * @param rLearnableParameters The learnable parameters.
     */
    void update(const std::vector<std::shared_ptr<Variable>> & rLearnableParameters) override;
};

#endif // RMSPROP_NESTEROV_HPP