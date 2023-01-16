//
// Created by tomas on 15. 1. 2023.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H
#include "vec3.h"

namespace EGRayTracer{
    class Ray {
    public:
        Ray();
        Ray(const vec3 &point1, const vec3 &point2);

        const vec3 GetPoint1() const;
        const vec3 GetPoint2() const;
    public:
        vec3 m_Point1;
        vec3 m_Point2;
        vec3 m_lab;
    };
}



#endif //RAYTRACER_RAY_H
