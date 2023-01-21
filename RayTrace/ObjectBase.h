//
// Created by tomas on 16. 1. 2023.
//

#ifndef RAYTRACER_OBJECTBASE_H
#define RAYTRACER_OBJECTBASE_H
#include "eigen-3.4.0/Eigen/Dense"
#include "Ray.h"

namespace EGRayTracer{
    class ObjectBase {
    public:
        ObjectBase();
        virtual ~ObjectBase();

        //Testing intersections
        virtual bool TestIntersections(const Ray &castRay,Eigen::Vector3d &intPoint,Eigen::Vector3d &localNormal,const Eigen::Vector3d &localColor);

        bool CloseEnough(const double &f1,const double &f2);

    public:
        Eigen::Vector3d m_BaseColor;
    };
}



#endif //RAYTRACER_OBJECTBASE_H
