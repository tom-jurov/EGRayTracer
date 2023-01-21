//
// Created by tomas on 16. 1. 2023.
//

#include "ObjectBase.h"
#include <math.h>
#define EPSILON 1e-21f

EGRayTracer::ObjectBase::ObjectBase()
{

}

EGRayTracer::ObjectBase::~ObjectBase()
{

}

bool EGRayTracer::ObjectBase::TestIntersections(const Ray &castRay,Eigen::Vector3d &intPoint,Eigen::Vector3d &localNormal,Eigen::Vector3d &localColor) {
    return false;
}

bool EGRayTracer::ObjectBase::CloseEnough(const double &f1, const double &f2)
{
    return fabs(f1-f2) < EPSILON;
}

void EGRayTracer::ObjectBase::SetTransformMatrix(const EGRayTracer::TF &transformMatrix)
{
    m_transformMatrix = transformMatrix;
}

