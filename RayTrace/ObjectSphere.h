//
// Created by tomas on 16. 1. 2023.
//

#ifndef RAYTRACER_OBJECTSPHERE_H
#define RAYTRACER_OBJECTSPHERE_H
#include "ObjectBase.h"
#include "TF.h"

namespace EGRayTracer {
    class ObjectSphere : public ObjectBase{
    public:
        ObjectSphere();

        virtual ~ObjectSphere() override;

        virtual bool TestIntersections(const EGRayTracer::Ray &castRay,Eigen::Vector3d &intPoint,Eigen::Vector3d &localNormal,
                                       Eigen::Vector3d &localColor) override;

    private:

    };
}

#endif //RAYTRACER_OBJECTSPHERE_H
