#ifndef ENSEMBLE_HPP
#define ENSEMBLE_HPP

#include "model.hpp"

/**
 * @brief the ensemble module is intended for creating an ensemble of models in the graph. This is useful for techniques like bagging or boosting.
 */
class Ensemble : public Model
{
    std::vector<std::shared_ptr<Model>> mModels; // storing the models in the ensemble

public:
    Ensemble(std::vector<ModelVariant> models);

    ~Ensemble();

    void addModel(ModelVariant model);

    // should be supported in the future, need a rewrite of the train function
    void train(std::vector<Vector2D> const & inputs, std::vector<Vector2D> const & labels, std::uint32_t const epochs, std::uint32_t const batchSize, OptimizerVariant optimizer, std::uint32_t const earlyStoppingIteration = 20, double split = 0.8){};

    void test(std::vector<Vector2D> const & inputs, std::vector<Vector2D> const & labels);
};

Ensemble::Ensemble(std::vector<ModelVariant> models)
{
    for ( std::uint32_t i = 0; i < models.size(); i++)
    {
        std::shared_ptr<Model> modelPtr = std::visit([](auto&& arg) {
            return std::shared_ptr<Model>(std::make_shared<std::decay_t<decltype(arg)>>(arg));}, ModelVariant{models[i]});

        mModels.push_back(modelPtr);
    }

    
}



#endif // ENSEMBLE_HPP