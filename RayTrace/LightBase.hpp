#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "vec3.h"
#include "Ray.h"
#include "ObjectBase.h"

namespace EGRayTracer
{
    class LightBase
    {
    public:
        LightBase();
        virtual ~LightBase();

        // function to compute illumination contribution
        virtual bool ComputeIllumination(const vec3& intPoint, const vec3& localNormal, const std::vector<std::shared_ptr<EGRayTracer::ObjectBase>> &objectList, const std::shared_ptr<EGRayTracer::ObjectBase> &currentObject, vec3 &color, double& intensity);
    public:
        vec3 m_Color;
        vec3 m_Location;
        double m_Intensity;
    };
} 



#endif
