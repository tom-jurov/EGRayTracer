#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "eigen-3.4.0/Eigen/Dense"
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
        virtual bool ComputeIllumination(const Eigen::Vector3d& intPoint, const Eigen::Vector3d& localNormal,
                                         const std::vector<std::shared_ptr<EGRayTracer::ObjectBase>> &objectList,
                                         const std::shared_ptr<EGRayTracer::ObjectBase> &currentObject, Eigen::Vector3d &color, double& intensity);
    public:
        Eigen::Vector3d m_Color;
        Eigen::Vector3d m_Location;
        double m_Intensity;
    };
} 



#endif
