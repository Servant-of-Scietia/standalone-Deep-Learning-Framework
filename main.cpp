#pragma GCC optimize("O3")
#include "brainet.hpp"


std::int32_t main()
{
    typedef std::vector<std::vector<double>> dataType;
    dataType train_input = read_idx("datasets/mnist/train-images.idx3-ubyte");
    dataType train_target = read_idx("datasets/mnist/train-labels.idx1-ubyte");

    dataType test_input = read_idx("datasets/mnist/t10k-images.idx3-ubyte");
    dataType test_target = read_idx("datasets/mnist/t10k-labels.idx1-ubyte");

    SequentialModel model(Input(train_input[0].size()), { Dense(ReLU(),800)}, Output(Softmax(), 10, CrossEntropy()));

    for (std::uint32_t i = 0; i < train_input.size(); i++)
    {
        for (std::uint32_t j = 0; j < train_input[i].size(); j++)
        {
            train_input[i][j] /= 255;
        }
    }
    for (std::uint32_t i = 0; i < test_input.size(); i++)
    {
        for (std::uint32_t j = 0; j < test_input[i].size(); j++)
        {
            test_input[i][j] /= 255;
        }
    }

    model.train( train_input, train_target, 10, 200, SGD(0.1), 20, 0.995 );

    model.test(test_input,test_target);


    return 0; 
}