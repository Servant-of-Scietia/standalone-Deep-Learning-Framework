#ifndef TENSOR_INCLUDE_GUARD
#define TENSOR_INCLUDE_GUARD

#include "dependencies.h"

/**
 * @brief TENSOR class is a wrapper class for a vector of doubles. It is used to store the data of a variable.
 * It is used to access a 1D vector as a multidimensional tensor.
*/
template <class T>
class TENSOR
{
    std::vector<T> __data;
    std::vector<int> __shape;

    void error_check()
    {
        if (__data.size() != std::accumulate(__shape.begin(),__shape.end(),1, std::multiplies<int>()))
            throw std::invalid_argument("TENSOR::data: Data size does not match the dimensionality of the tensor");
          
    }
public:
    TENSOR(){};
    TENSOR(std::vector<int> dimensionality, int value = 0, bool random = false);
    TENSOR(const TENSOR<T> & tensor)
    {
        throw std::invalid_argument("TENSOR::TENSOR: Copy constructor not allowed");
    }
    TENSOR & operator=(const TENSOR<T> & tensor)
    {
        throw std::invalid_argument("TENSOR::operator=: Copy assignment not allowed");
    }
    TENSOR(TENSOR<T> && tensor) = default;
    TENSOR & operator=(TENSOR<T> && tensor) = default;
    ~TENSOR() = default;
    
    T at(std::vector<int> index);
    void set(std::vector<int> index, T value);
    std::vector<int> shape(){return __shape;};
    int shape(int index){return __shape[index];};
    int dimensionality(){return __shape.size();};
    int size(){return __data.size();};
    void resize(std::vector<int> dimensionality){__shape = dimensionality; __data.resize(std::accumulate(dimensionality.begin(),dimensionality.end(),1, std::multiplies<double>()));};
    std::vector<T> & data(){error_check();return __data;};
    std::shared_ptr<TENSOR<T>> transpose();
};

/**
 * @brief returns the value at the index
 * @param index vector of indices
 * @return the value at the index
*/
template <class T>
T TENSOR<T>::at(std::vector<int> index)
{
    if(index.size() != __shape.size())
        throw std::invalid_argument("TENSOR::at: Index size does not match the dimensionality of the tensor");
    int _block_size = std::accumulate(__shape.begin(), __shape.end(), 1, std::multiplies<int>());
    int _index = 0;
    for (int i = 0; i < index.size(); i++)
    {
        _block_size /= __shape[i];
        _index += index[i] * _block_size;
    }
    if(_index >= __data.size())
        throw std::out_of_range("Index out of range");
    return __data[_index];
}


template <class T>
TENSOR<T>::TENSOR(std::vector<int> dimensionality, int value, bool random)
{
    __data = std::vector<T>(std::accumulate(dimensionality.begin(),dimensionality.end(),1, std::multiplies<int>()), value);
    if(random)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-0.1, 0.1);
        for(int i = 0; i < __data.size(); i++)
        {
            // __data[i] = dis(gen);
            __data[i] = 1;
        }
    }
    __shape = dimensionality;
}

/**
 * @brief sets the value at the index
 * @param index vector of indices
 * @param value the value to be set
*/
template <class T>
void TENSOR<T>::set(std::vector<int> index, T value)
{
    if(index.size() != __shape.size())
        throw std::invalid_argument("TENSOR::set: Index size does not match the dimensionality of the tensor");
    int _block_size = std::accumulate(__shape.begin(), __shape.end(), 1, std::multiplies<int>());
    int _index = 0;
    for (int i = 0; i < index.size(); i++)
    {
        _block_size /= __shape[i];
        _index += index[i] * _block_size;
    }
    if(_index >= __data.size())
        throw std::out_of_range("Index out of range");
    __data[_index] = value;
}

/**
 * @brief transposes the tensor
*/
template <class T>
std::shared_ptr<TENSOR<T>> TENSOR<T>::transpose()
{
    if(__shape.size() != 2)
        throw std::invalid_argument("TENSOR::transpose: Tensor must be 2D");
    std::shared_ptr<TENSOR<T>> _tensor = std::make_shared<TENSOR<T>>(TENSOR<T>({__shape[1],__shape[0]}));
    std::vector<T> _data(__data.size());
    for(int i = 0; i < __shape[0]; i++)
    {
        for(int j = 0; j < __shape[1]; j++)
        {
            _data[j*__shape[0] + i] = __data[i*__shape[1] + j];
        }
    }
    _tensor->data() = _data;
    return _tensor;
}

#endif // TENSOR_INCLUDE_GUARD