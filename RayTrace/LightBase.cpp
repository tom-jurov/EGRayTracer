#include "LightBase.hpp"

EGRayTracer::LightBase::LightBase(){

}

EGRayTracer::LightBase::~LightBase(){

}

bool EGRayTracer::LightBase::ComputeIllumination(const vec3& intPoint, const vec3& localNormal, const std::vector<std::shared_ptr<EGRayTracer::ObjectBase>> &objectList, const std::shared_ptr<EGRayTracer::ObjectBase> &currentObject, vec3 &color, double& intensity){
   return false; 
}