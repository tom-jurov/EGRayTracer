//
// Created by tomas on 21. 1. 2023.
//

#include "ObjectPlane.h"
#include <cmath>

EGRayTracer::ObjectPlane::ObjectPlane()
{

}

EGRayTracer::ObjectPlane::~ObjectPlane(){}

bool EGRayTracer::ObjectPlane::TestIntersections(const Ray &castRay, Eigen::Vector3d &intPoint,
                                                 Eigen::Vector3d &localNormal, Eigen::Vector3d &localColor)
{
    EGRayTracer::Ray bckRay = m_transformMatrix.Apply(castRay, EGRayTracer::BCKTFORM);

    Eigen::Vector3d k = bckRay.m_lab;
    k.normalize();

    if(!CloseEnough(k(2), 0.0))
    {
        double t = bckRay.m_Point1(2) / -k(2);

        if (t > 0.0){
            double u = bckRay.m_Point1(0) + k(0)*t;
            double v = bckRay.m_Point1(1) + k(1)*t;

            if((abs(u)< 1.0) && (abs(v) < 1.0)){
                Eigen::Vector3d poi = bckRay.m_Point1 + t*k;

                intPoint = m_transformMatrix.Apply(poi, EGRayTracer::FWDTFORM);

                Eigen::Vector3d localOrigin(0.0, 0.0, 0.0);
                Eigen::Vector3d normalVector(0.0, 0.0, -1.0);
                Eigen::Vector3d globalOrigin = m_transformMatrix.Apply(localOrigin, EGRayTracer::FWDTFORM);
                localNormal = m_transformMatrix.Apply(normalVector, EGRayTracer::FWDTFORM) - globalOrigin;
                localNormal.normalize();

                localColor = m_BaseColor;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}