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

bool EGRayTracer::ObjectSphere::TestIntersections(const EGRayTracer::Ray &castRay, Eigen::Vector3d &intPoint, Eigen::Vector3d &localNormal,
                                                  const Eigen::Vector3d &localColor) {
    Eigen::Vector3d vhat = castRay.m_lab;
    vhat.normalize();
    //a is always one cuz normalized vec3
    //a = 1.0;

    double b = 2.0 * castRay.m_Point1.dot(vhat);
    double c = castRay.m_Point1.dot(castRay.m_Point1) - 1.0;

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
                intPoint = vhat * t1 + castRay.m_Point1;

            }
            else
            {
                intPoint = vhat * t2 + castRay.m_Point1;

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