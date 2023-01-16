#include <vector>
#include <algorithm>
#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H
/**
 * vec3 is a class which implements many common 3-vector operations using std::vector containers.
 *
 */
class vec3
{
public:
    // Members
    std::vector<double> value;

    // Member functions
    vec3(); //default constructor
    vec3(double x, double y, double z);
    vec3(std::vector<double> newVec);

    /**
     * Calculate the scalar magnitude for the vec3 object
     *
     */
    double magnitude();

    void normalize();

    /**
     * Perform element-wise subtraction with other vector.
     *
     * @param otherVector Another vector whose individual elements will be subtracted from the elements of this vector.
     * @returns the magnitude of this vector
     *
    */
    vec3 subtract(const vec3 &otherVector);

    /**
     * Subtract a scalar from all elements of this vector
     *
     * @param scalar A scalar value which will be subtracted from the elements of this vector.
     * @returns a new vec3 containing the result of the operation.
     *
    */
    vec3 subtract(double scalar);

    /**
     * Perform element-wise addition with other vector.
     *
     * @param otherVector Another vec3 whose individual elements will be added to the elements of this vector.
     * @returns a new vec3 containing the result of the operation.
     *
    */
    vec3 add(vec3 &otherVector);

    /**
     * Add a scalar to each element of this vector.
     *
     * @param scalar A scalar value which will be added to the elements of this vector
     * @returns a new vec3 containing the result of the operation.
     *
    */
    vec3 add(double scalar);

    /**
     * Divide each element of this vector by a scalar value
     *
     * @param divisor A scalar value which be used to divide each element of this vector
     * @returns a new vec3 containing the result of the operation.
     *
     */
    vec3 divide(double divisor);

    /**
     * Multiply each element of this vector by a scalar value.
     *
     * @param multiplicator A scalar value whic be used to multiply each element of this vector.
     * @returns a new vec3 containing the result of the operation.
     *
     */
    vec3& multiply(double multiplier);

    /**
     * Compute the vector cross product of this vector with another supplied vector.
     * Note: the cross product will be computed as (this->vector) x (otherVector).
     *
     * @param otherVector A reference to other vec3 which will combined with this vector using the cross product operation.
     * @returns a new vec3 containing the result of the operation.
     *
     */
    vec3 crossProduct(const vec3 &otherVector);

};
#endif //RAYTRACER_VEC3_H