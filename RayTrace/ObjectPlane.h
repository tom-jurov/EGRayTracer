//
// Created by tomas on 21. 1. 2023.
//

#ifndef RAYTRACER_OBJECTPLANE_H
#define RAYTRACER_OBJECTPLANE_H
#include "ObjectBase.h"
#include "TF.h"

namespace EGRayTracer{
    class ObjectPlane : public ObjectBase {
    public:
        ObjectPlane();

        virtual ~ObjectPlane() override;

        virtual bool TestIntersections(const Ray &castRay,Eigen::Vector3d &intPoint,
                                       Eigen::Vector3d &localNormal,Eigen::Vector3d &localColor) override;

    private:
    };
}

#endif //RAYTRACER_OBJECTPLANE_H
