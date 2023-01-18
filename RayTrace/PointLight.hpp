#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "LightBase.hpp"

namespace EGRayTracer{
    class PointLight : public LightBase
    {
    public:
        PointLight();

        virtual ~PointLight() override;

        virtual bool ComputeIllumination (const vec3& intPoint, const vec3& localNormal, const std::vector<std::shared_ptr<EGRayTracer::ObjectBase>> &objectList, const std::shared_ptr<EGRayTracer::ObjectBase> &currentObject, vec3 &color, double& intensity) override;
    };
}

#endif