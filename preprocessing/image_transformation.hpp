#ifndef IMAGETRANSFORMATION_HPP
#define IMAGETRANSFORMATION_HPP

#include "../dependencies.hpp"

/**
 * @brief Used to apply various transformations to an image. This is used to augment the dataset.
 */
class ImageTransformation
{
    typedef std::vector<std::vector<double>> data_type;

public:
    /**
     * @brief apply a random transformation to the input image
     * @param input the input image
     * @return the transformed image
     */
    static data_type randomTransform(const data_type & input);
    /**
     * @brief apply a random rotation to the input image
     * @param input the input image
     * @return the rotated image
     */
    static data_type randomRotation(const data_type & input);
    /**
     * @brief apply a random translation to the input image
     * @param input the input image
     * @return the translated image
     */
    static data_type randomTranslation(const data_type & input);
    /**
     * @brief apply a random scaling to the input image
     * @param input the input image
     * @return the scaled image
     */
    static data_type randomScaling(const data_type & input);
    /**
     * @brief apply a random shear to the input image
     * @param input the input image
     * @return the sheared image
     */
    static data_type randomShear(const data_type & input);
    /**
     * @brief apply a random flip to the input image
     * @param input the input image
     * @return the flipped image
     */
    static data_type randomFlip(const data_type & input);
    /**
     * @brief apply a random noise to the input image
     * @param input the input image
     * @return the noisy image
     */
    static data_type randomNoise(const data_type & input);
    /**
     * @brief apply a random blur to the input image
     * @param input the input image
     * @return the blurred image
     */
    static data_type randomBlur(const data_type & input);
    /**
     * @brief apply a random sharpen to the input image
     * @param input the input image
     * @return the sharpened image
     */
    static data_type randomSharpen(const data_type & input);
    /**
     * @brief apply a random contrast to the input image
     * @param input the input image
     * @return the contrasted image
     */
    static data_type randomContrast(const data_type & input);
    /**
     * @brief apply a random brightness to the input image
     * @param input the input image
     * @return the brightened image
     */
};

#endif // IMAGETRANSFORMATION_HPP