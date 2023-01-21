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

    //Construct a ray from the point of intersection to the light
    EGRayTracer::Ray lightRay (startPoint, startPoint + lightDir);

    Eigen::Vector3d poi;
    Eigen::Vector3d poiNormal;
    Eigen::Vector3d poiColor;
    bool validInt = false;
    for(auto& sceneObject : objectList)
    {
        if (sceneObject != currentObject)
        {
            validInt = sceneObject->TestIntersections(lightRay, poi, poiNormal, poiColor);
        }

        // If we have an inter, then there is no point checking futher
        if (validInt) {
            //std::cout << currentObject << std::endl;
            break;
        }
    }

    if(!validInt)
    {
        double angle = acos(localNormal.dot(lightDir));

        if(angle > 1.5708)
        {
            color = m_Color;
            intensity = 0.0;
            return false;
        }
        else
        {
            color = m_Color;
            intensity = m_Intensity * (1.0 - (angle / 1.5708));
            return true;
        }
    }
    else
    {
        color = m_Color;
        intensity = 0.0;
        return false;
    }

    return true;
}