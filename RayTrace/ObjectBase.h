//
// Created by tomas on 16. 1. 2023.
//

#ifndef RAYTRACER_OBJECTBASE_H
#define RAYTRACER_OBJECTBASE_H
#include "vec3.h"
#include "Ray.h"

namespace EGRayTracer{
    class ObjectBase {
    public:
        ObjectBase();
        virtual ~ObjectBase();

        //Testing intersections
        virtual bool TestIntersections(const Ray &castRay,vec3 &intPoint,vec3 &localNormal,const vec3 &localColor);

        bool CloseEnough(const double &f1,const double &f2);

    public:
        vec3 m_BaseColor;
    };
}



#endif //RAYTRACER_OBJECTBASE_H
