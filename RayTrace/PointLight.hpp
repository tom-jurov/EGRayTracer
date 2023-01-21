#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "LightBase.hpp"

namespace EGRayTracer{
    class PointLight : public LightBase
    {
    public:
        PointLight();

        virtual ~PointLight() override;

        virtual bool ComputeIllumination (const Eigen::Vector3d& intPoint, const Eigen::Vector3d& localNormal,
                                          const std::vector<std::shared_ptr<EGRayTracer::ObjectBase>> &objectList,
                                          const std::shared_ptr<EGRayTracer::ObjectBase> &currentObject, Eigen::Vector3d &color, double& intensity) override;
    };
}

#endif