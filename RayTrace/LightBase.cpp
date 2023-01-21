#include "LightBase.hpp"

EGRayTracer::LightBase::LightBase(){

}

EGRayTracer::LightBase::~LightBase(){

}

bool EGRayTracer::LightBase::ComputeIllumination(const Eigen::Vector3d& intPoint, const Eigen::Vector3d& localNormal,
                                                 const std::vector<std::shared_ptr<EGRayTracer::ObjectBase>> &objectList,
                                                 const std::shared_ptr<EGRayTracer::ObjectBase> &currentObject, Eigen::Vector3d &color, double& intensity){
   return false; 
}