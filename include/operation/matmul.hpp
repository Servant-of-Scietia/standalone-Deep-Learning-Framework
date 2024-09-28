#ifndef MATMUL_HPP
#define MATMUL_HPP

#include "operation.hpp"
#include "matmul.cuh"


/**
 * @brief Matmul class used to perform the dot product of two matrices. This is usually a bottleneck in neural networks. 
 * Expecting to replace this with a more efficient CUDA implementation in the future.
*/
class Matmul : public Operation
{   
protected:
    static const std::uint32_t threads = 200;
    /**
     * @brief  matrix vector multiplication function
     * @param left_matrix the left matrix
     * @param right_matrix the right matrix
     * @param result the result of the matrix multiplication
     * @param k the index of the coloum in the right matrix
     */
    void blockmul(std::shared_ptr<Tensor<double>> & left_matrix, std::shared_ptr<Tensor<double>> & right_matrix, std::shared_ptr<Tensor<double>> & result, std::uint32_t k);

    /**
     * @brief spawning threads for every coloum in the right matrix to execute the blockmul function in parallel
     * @param left_matrix the left matrix
     * @param right_matrix the right matrix
     * @return the result of the matrix multiplication
     */
    std::shared_ptr<Tensor<double>> matmul(std::shared_ptr<Tensor<double>> & left_matrix, std::shared_ptr<Tensor<double>> & right_matrix);
public:    
    Matmul(){mName = "Matmul";};
    ~Matmul(){};
    /**
     * @brief wrapper function for matmul. Does error checking and handles inputs and outputs.
     * @param inputs the input variables
     */
    void f(std::vector<std::shared_ptr<Variable>>& inputs) override;
    /**
     * @brief bprop for matmul. Outputs the gradient multiplied by the input != focus
     * @param inputs the input variables
     * @param focus the variable to calculate the gradient for
     * @param gradient the sum of the gradients of the consumers
     */
    std::shared_ptr<Tensor<double>> bprop(std::vector<std::shared_ptr<Variable>>& inputs, std::shared_ptr<Variable> & focus, std::shared_ptr<Tensor<double>> & gradient) override;
};

#endif // MATMUL_HPP