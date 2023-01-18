#include "PointLight.hpp"
#include <math.h>

EGRayTracer::PointLight::PointLight(){
    m_Color = vec3(1.0, 1.0, 1.0);
    m_Intensity = 1.0;
}

EGRayTracer::PointLight::~PointLight(){
    
}

bool EGRayTracer::PointLight::ComputeIllumination(const vec3& intPoint, const vec3& localNormal, const std::vector<std::shared_ptr<EGRayTracer::ObjectBase>> &objectList, const std::shared_ptr<EGRayTracer::ObjectBase> &currentObject, vec3 &color, double& intensity)
{
    vec3 lightDir = (m_Location.subtract(intPoint));
    lightDir.normalize();

    //Compute the starting point
    vec3 startPoint = intPoint;

    //compute the angle between local normal and light ray
    double angle = acos(vec3::dotProduct(localNormal, lightDir));

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