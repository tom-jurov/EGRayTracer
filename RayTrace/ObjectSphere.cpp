//
// Created by tomas on 16. 1. 2023.
//

#include "ObjectSphere.h"
#include <cmath>
#include <iostream>
EGRayTracer::ObjectSphere::ObjectSphere()
{

}

EGRayTracer::ObjectSphere::~ObjectSphere()

noexcept {}

bool EGRayTracer::ObjectSphere::TestIntersections(const EGRayTracer::Ray &castRay, vec3 &intPoint, vec3 &localNormal, const vec3 &localColor) {
    vec3 vhat = castRay.m_lab;
    vhat.normalize();
    //a is always one cuz normalized vec3
    //a = 1.0;

    double b = 2.0 * vec3::dotProduct(castRay.m_Point1, vhat);
    double c = vec3::dotProduct(castRay.m_Point1, castRay.m_Point1) - 1.0;

    double intTest = (b*b) - 4.0 * c;

    if (intTest > 0.0)
    {
        double numSQRT = sqrt(intTest);
        double t1 = (-b + numSQRT) / 2.0;
        double t2 = (-b - numSQRT) / 2.0;

        if((t1 < 0.0) || (t2 < 0.0))
        {
            return false;
        }
        else{
            if (t1 < t2)
            {
                intPoint = vhat.multiply(t1).add(castRay.m_Point1);

            }
            else
            {
                intPoint = vhat.multiply(t2).add(castRay.m_Point1);

            }

            localNormal = intPoint;
        }
        return true;
    }
    else
    {
        return false;
    }
}