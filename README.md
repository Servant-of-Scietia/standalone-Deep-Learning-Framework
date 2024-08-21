
# Brainet

Brainet is an Deep Learning Engine build within C++ and CUDA, without external Libraries.
It provides a simple API to build and train neural networks and is designed to be easy to use and extend.
The project is still in its early stages and is not yet ready for production use. 
Brainet is currently under heavy development, so expect major changes to the API and the codebase. 
A very early version of a documentation can be found in the example.cpp file. 
This is Version 0.2.0. For the latest version please visit the dev branch.

## Authors

- [@Servant-of-Scietia](https://github.com/Servant-of-Scietia)

## Performance

- [MNIST](https://yann.lecun.com/exdb/mnist/): 

    | Model | Test Error Rate | Training Time |
    |-------|----------|---------------|
    | 2-layer NN, 300 hidden units, mean square error | 8.66% | 40 min |
    

## Installation

To use Brainet, you need to have a CUDA compatible GPU and the [CUDA Toolkit](https://developer.nvidia.com/cuda-downloads) installed.

You'll also need a C++ compiler that supports at least C++17. I recommend using the [GNU Compiler Collection](https://gcc.gnu.org/).

To download the source code, run the following command in your terminal:

```bash
  git clone https://github.com/Neurologism/brainet
```

The only dataset that comes with Brainet is the MNIST dataset. 
The following contains a list of download links for other datasets that can be used with Brainet:
- [EMNIST](https://biometrics.nist.gov/cs_links/EMNIST/gzip.zip)
- Fashion MNIST: 
    - [Train](http://fashion-mnist.s3-website.eu-central-1.amazonaws.com/train-images-idx3-ubyte.gz)
    - [Test](http://fashion-mnist.s3-website.eu-central-1.amazonaws.com/t10k-images-idx3-ubyte.gz)
- [CIFAR-100](https://www.cs.toronto.edu/~kriz/cifar-100-binary.tar.gz)
- [CIFAR-10](https://www.cs.toronto.edu/~kriz/cifar-10-binary.tar.gz)

To use them, you will also need a tool to extract gzip and tar files. I recommend using [7-Zip](https://www.7-zip.org/).