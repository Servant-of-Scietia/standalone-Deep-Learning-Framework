#ifndef MODEL_INCLUDE_GUARD
#define MODEL_INCLUDE_GUARD

#include "dependencies.h"
#include "graph.h"
#include "cluster/input.h"
#include "cluster/cluster.h"
#include "cluster/dense.h"

class MODEL
{
    GRAPH __graph;
public:
    MODEL(){CLUSTER::set_graph(&__graph);};
    void load();
    void sequential(std::vector<std::shared_ptr<CLUSTER>> layers);
    void train(int epochs, double learning_rate);
};

void MODEL::load()
{
    CLUSTER::set_graph(&__graph);
}

void MODEL::sequential(std::vector<std::shared_ptr<CLUSTER>> layers)
{
    for(int i = 0; i < layers.size() - 1; i++)
    {
        layers[i]->add_output(layers[i+1]->input());
        layers[i+1]->add_input(layers[i]->output());
    }
}

void MODEL::train(int epochs, double learning_rate)
{
    __graph.forward();
    std::vector<bool> v(__graph.get_variables().size(),true);
    __graph.backprop(v,10);
}

#endif // MODEL_INCLUDE_GUARD