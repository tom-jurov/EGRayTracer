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
                                                  Eigen::Vector3d &localColor) {

    EGRayTracer::Ray bckRay = m_transformMatrix.Apply(castRay, EGRayTracer::BCKTFORM);
    Eigen::Vector3d vhat = bckRay.m_lab;
    vhat.normalize();
    //a is always one cuz normalized vec3
    //a = 1.0;

    double b = 2.0 * bckRay.m_Point1.dot(vhat);
    double c = bckRay.m_Point1.dot(bckRay.m_Point1) - 1.0;

    double intTest = (b*b) - 4.0 * c;

    Eigen::Vector3d poi;
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
                poi = vhat * t1 + bckRay.m_Point1;

            }
            else
            {
                poi = vhat * t2 + bckRay.m_Point1;

            }

            intPoint = m_transformMatrix.Apply(poi, EGRayTracer::FWDTFORM);
            Eigen::Vector3d objOrigin(0.0, 0.0, 0.0);
            Eigen::Vector3d newObjOrigin = m_transformMatrix.Apply(objOrigin, EGRayTracer::FWDTFORM);
            localNormal = intPoint - newObjOrigin;
            localNormal.normalize();

            localColor = m_BaseColor;
        }
        return true;
    }
    else
    {
        return false;
    }
}