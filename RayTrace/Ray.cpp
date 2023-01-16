//
// Created by tomas on 15. 1. 2023.
//

#include "Ray.h"

EGRayTracer::Ray::Ray() {
    m_Point1 = vec3(0.0, 0.0, 0.0);
    m_Point2 = vec3(0.0, 0.0, 1.0);
    m_lab = m_Point2.subtract(m_Point1);
}

EGRayTracer::Ray::Ray(const vec3 &point1, const vec3 &point2)
{
    m_Point1 = point1;
    m_Point2 = point2;
    m_lab = m_Point2.subtract(m_Point1);
}

const vec3 EGRayTracer::Ray::GetPoint1() const
{
    return m_Point1;
}

const vec3 EGRayTracer::Ray::GetPoint2() const
{
    return m_Point2;
}