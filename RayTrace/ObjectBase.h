//
// Created by tomas on 16. 1. 2023.
//

#ifndef RAYTRACER_OBJECTBASE_H
#define RAYTRACER_OBJECTBASE_H
#include "TF.h"
#include "Ray.h"

namespace EGRayTracer{
    class ObjectBase {
    public:
        ObjectBase();
        virtual ~ObjectBase();

        //Testing intersections
        virtual bool TestIntersections(const Ray &castRay,Eigen::Vector3d &intPoint,Eigen::Vector3d &localNormal,Eigen::Vector3d &localColor);

        //Function to set the transform matrix
        void SetTransformMatrix(const EGRayTracer::TF &transformMatrix);

        bool CloseEnough(const double &f1,const double &f2);

    public:
        Eigen::Vector3d m_BaseColor;

        // The geom transform applied to the object
        EGRayTracer::TF m_transformMatrix;
    };
}



#endif //RAYTRACER_OBJECTBASE_H
