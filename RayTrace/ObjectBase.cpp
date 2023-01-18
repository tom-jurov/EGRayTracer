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

bool EGRayTracer::ObjectBase::TestIntersections(const Ray &castRay,vec3 &intPoint,vec3 &localNormal, const vec3 &localColor) {
    return false;
}

bool EGRayTracer::ObjectBase::CloseEnough(const double &f1, const double &f2)
{
    return fabs(f1-f2) < EPSILON;
}

