//
// Created by tomas on 15. 1. 2023.
//

#include "vec3.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

vec3::vec3()
{
    this->value = std::vector<double>();
}

vec3::vec3(double x, double y, double z)
{
    this->value.push_back(x);
    this->value.push_back(y);
    this->value.push_back(z);
}

vec3::vec3(std::vector<double> newVec)
{
    this->value = newVec;
}

double vec3::magnitude()
{
    int lenVector = this->value.size();

    double totalMagnitude = 0.0f;
    for(int i=0;i<lenVector;i++)
    {
        totalMagnitude += this->value[i]*this->value[i];
    }
    return std::sqrt(totalMagnitude);
}

vec3 vec3::subtract(const vec3 &otherVector)
{
    int thisLen = this->value.size();
    int otherLen = otherVector.value.size();

    if(thisLen != otherLen)
    {
        std::cout << thisLen << std::endl;
        for(int i=0; i<thisLen;i++)
        {
            std::cout << this->value[i] << std::endl;
        }

        std::cout << otherLen << std::endl;
        for(int i=0; i<otherLen;i++)
        {
            std::cout << otherVector.value[i] << std::endl;
        }
        throw std::invalid_argument("Vectors must be the same length to subtract.");
    }

    vec3 subtractedVector;
    for(int i=0; i<thisLen; i++)
    {
        subtractedVector.value.push_back(this->value[i]-otherVector.value[i]);
    }
    return subtractedVector;
}
vec3 vec3::subtract(double scalar)
{
    vec3 subtractedVector;
    for(int i=0; i<this->value.size(); i++)
    {
        subtractedVector.value.push_back(this->value[i]-scalar);
    }
    return subtractedVector;
}

vec3 vec3::add(const vec3 &otherVector)
{
    int thisLen = this->value.size();
    int otherLen = otherVector.value.size();

    if(thisLen != otherLen)
    {
        throw std::invalid_argument("Vectors must be the same length to subtract.");
    }
    vec3 addedVector;
    for(int i=0; i<thisLen; i++)
    {
        addedVector.value.push_back(this->value[i]+otherVector.value[i]);
    }
    return addedVector;
}

vec3 vec3::add(double scalar)
{
    vec3 addedVector;
    for(int i=0; i<this->value.size(); i++)
    {
        addedVector.value.push_back(this->value[i]+scalar);
    }
    return addedVector;
}

vec3 vec3::multiply(double multiplier)
{
    vec3 multipiedVec;
    for(int i=0; i<this->value.size(); i++)
    {
        multipiedVec.value.push_back(this->value[i]*multiplier);
    }
    return multipiedVec;
}

void vec3::normalize()
{
    auto x = this->value.at(0);
    auto y = this->value.at(1);
    auto z = this->value.at(2);
    float magnitude = sqrt(x*x + y*y + z*z);
    for(int i=0; i<this->value.size(); i++)
    {
        this->value.at(i) /= magnitude;
    }
}

vec3 vec3::divide(double divisor)
{
    return this->multiply(1/divisor);
}

vec3 vec3::crossProduct(const vec3 &otherVector)
{
    int thisLen = this->value.size();
    int otherLen = otherVector.value.size();

    if(thisLen != 3 || otherLen != 3)
    {
        if(thisLen != 3 ){
            std::cout << "Here1" << std::endl;
        }
        if(otherLen != 3 ){
            std::cout << "Here2" << std::endl;
        }
        throw std::invalid_argument("Cross product is not defined for non-3D vectors.");
    }

    vec3 crossVector;

    for(int i=0; i<thisLen; i++)
    {
        double result = (this->value[(i+1)%thisLen] * otherVector.value[(i+2)%thisLen])-(this->value[(i+2)%thisLen]*otherVector.value[(i+1)%thisLen]);
        crossVector.value.push_back(result);
    }
    return crossVector;
}


double vec3::dotProduct(const vec3 &leftVector, const vec3 &rightVector) {
    int lVecLen = leftVector.value.size();
    int rVecLen = rightVector.value.size();

    if(lVecLen != 3 || rVecLen != 3)
    {
        throw std::invalid_argument("Dot product is not defined for non-3D vectors.");
    }

    double resultOfDotProduct = 0;

    for(int i=0; i<lVecLen; i++)
    {
        resultOfDotProduct += leftVector.value[i] * rightVector.value[i];
    }
    return resultOfDotProduct;
}