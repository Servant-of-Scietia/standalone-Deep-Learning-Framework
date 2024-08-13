
# Brainet

Brainet is an Deep Learning Engine build within C++ and CUDA, without external Libraries.
It provides a simple API to build and train neural networks, and is designed to be easy to use and extend.
The project is still in its early stages, and is not yet ready for production use. 
Brainet is currently under heavy development, so expect major changes to the API and the codebase. 



## Authors

- [@Servant-of-Scietia](https://github.com/Servant-of-Scietia)

## Performance

- [MNIST](https://yann.lecun.com/exdb/mnist/): 

    | Model | Accuracy | Training Time |
    |-------|----------|---------------|
    | 2-layer NN, 300 hidden units, mean square error | 95.4% | 10 min |
    

## Installation

To use Brainet, you need to have a CUDA compatible GPU and the [CUDA Toolkit](https://developer.nvidia.com/cuda-downloads) installed.

You'll also need a C++ compiler that supports at least C++17. I recommend using the [GNU Compiler Collection](https://gcc.gnu.org/).

To download the source code, run the following command in your terminal:

```bash
  git clone https://github.com/Neurologism/brainet
```