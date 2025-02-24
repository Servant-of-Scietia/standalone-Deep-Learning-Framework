#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include "../dependencies.hpp"
#include "../graph.hpp"

/**
 * @brief The abstract class Optimizer is intended to be used as a base class for all optimization algorithms used to train the models.
 */
class Optimizer
{
public:
    Optimizer() = default;
    virtual ~Optimizer() = default;

    /**
     * @brief Updates the learnable parameters using the optimization algorithm.
     * @param rLearnableParameters The learnable parameters.
     */
    virtual void update(const std::vector<std::shared_ptr<Variable>> & rLearnableParameters) = 0;
};

#endif // OPTIMIZER_HPP