//
// Created by tomas on 15. 1. 2023.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H
#include "eigen-3.4.0/Eigen/Dense"

namespace EGRayTracer{
    class Ray {
    public:
        Ray();
        Ray(const Eigen::Vector3d &point1, const Eigen::Vector3d &point2);

        const Eigen::Vector3d GetPoint1() const;
        const Eigen::Vector3d GetPoint2() const;
    public:
        Eigen::Vector3d m_Point1;
        Eigen::Vector3d m_Point2;
        Eigen::Vector3d m_lab;
    };
}



#endif //RAYTRACER_RAY_H
