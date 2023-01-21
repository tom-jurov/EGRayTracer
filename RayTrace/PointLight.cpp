#include "PointLight.hpp"
#include <math.h>

EGRayTracer::PointLight::PointLight(){
    m_Color = Eigen::Vector3d(1.0, 1.0, 1.0);
    m_Intensity = 1.0;
}

EGRayTracer::PointLight::~PointLight(){
    
}

bool EGRayTracer::PointLight::ComputeIllumination(const Eigen::Vector3d& intPoint, const Eigen::Vector3d& localNormal,
                                                  const std::vector<std::shared_ptr<EGRayTracer::ObjectBase>> &objectList,
                                                  const std::shared_ptr<EGRayTracer::ObjectBase> &currentObject, Eigen::Vector3d &color, double& intensity)
{
    Eigen::Vector3d lightDir = m_Location - intPoint;
    lightDir.normalize();

    //Compute the starting point
    Eigen::Vector3d startPoint = intPoint;

    //compute the angle between local normal and light ray
    double angle = acos(localNormal.dot(lightDir));

    // If normal is pointing away from the light, then we have no illumination.
    if (angle > 1.5708)
    {
        // No illumination.
        color = m_Color;
        intensity = 0.0;
        return false;
    }
    else 
    {
        // We do have a illumination
        color = m_Color;
        intensity = m_Intensity * (1.0 - (angle / 1.5708));
        return true;
    }
}