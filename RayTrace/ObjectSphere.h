//
// Created by tomas on 16. 1. 2023.
//

#ifndef RAYTRACER_OBJECTSPHERE_H
#define RAYTRACER_OBJECTSPHERE_H
#include "ObjectBase.h"
namespace EGRayTracer {
    class ObjectSphere : public ObjectBase{
    public:
        ObjectSphere();

        virtual ~ObjectSphere() override;

        virtual bool TestIntersections(const EGRayTracer::Ray &castRay,vec3 &intPoint,vec3 &localNormal, const vec3 &localColor);

    private:

    };
}


#endif //RAYTRACER_OBJECTSPHERE_H
