//
// Created by tomas on 15. 1. 2023.
//

#include "Ray.h"

EGRayTracer::Ray::Ray() {
    m_Point1 = Eigen::Vector3d(0.0, 0.0, 0.0);
    m_Point2 = Eigen::Vector3d(0.0, 0.0, 1.0);
    m_lab = m_Point2 - m_Point1;
}

EGRayTracer::Ray::Ray(const Eigen::Vector3d &point1, const Eigen::Vector3d &point2)
{
    m_Point1 = point1;
    m_Point2 = point2;
    m_lab = m_Point2 - m_Point1;
}

const Eigen::Vector3d EGRayTracer::Ray::GetPoint1() const
{
    return m_Point1;
}

const Eigen::Vector3d EGRayTracer::Ray::GetPoint2() const
{
    return m_Point2;
}