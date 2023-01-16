//
// Created by tomas on 15. 1. 2023.
//

#include "Camera.h"
#include "Ray.h"
#include "iostream"

EGRayTracer::Camera::Camera()
{
    m_CameraPosition = vec3(0.0, -10.0, 0.0);
    m_CameraLookAt = vec3(0.0, 0.0, 0.0);
    m_CameraUp = vec3(0.0, 0.0, 1.0);
    m_CameraLength = 1.0;
    m_CameraHorzSize = 1.0;
    m_CameraAspectRatio = 1.0;
}

void EGRayTracer::Camera::SetPosition(const vec3 &newPosition) {
    m_CameraPosition = newPosition;
}

void EGRayTracer::Camera::SetLookAt(const vec3 &newLookAt) {
    m_CameraLookAt = newLookAt;
}

void EGRayTracer::Camera::SetUp(const vec3 &upVector) {
    m_CameraUp = upVector;
}

void EGRayTracer::Camera::SetLength(const double &newLength) {
    m_CameraLength = newLength;
}

void EGRayTracer::Camera::SetHorzSize(const double &newHorzSize) {
    m_CameraHorzSize = newHorzSize;
}

void EGRayTracer::Camera::SetAspect(const double &newAspect) {
    m_CameraAspectRatio = newAspect;
}

const vec3 EGRayTracer::Camera::GetPosition() const {
    return m_CameraPosition;
}

const vec3 EGRayTracer::Camera::GetLookAt() const {
    return m_CameraLookAt;
}

const vec3 EGRayTracer::Camera::GetUp() const {
    return m_CameraUp;
}

const double EGRayTracer::Camera::GetLength() const {
    return m_CameraLength;
}

const double EGRayTracer::Camera::GetHorzSize() const {
    return m_CameraHorzSize;
}

const double EGRayTracer::Camera::GetAspect() const {
    return m_CameraAspectRatio;
}

const vec3 EGRayTracer::Camera::GetU() const {
    return m_ProjectionScreenU;
}

const vec3 EGRayTracer::Camera::GetV() const {
    return m_ProjectionScreenV;
}

const vec3 EGRayTracer::Camera::GetScreenCenter() const {
    return m_ProjectionScreenCenter;
}

void EGRayTracer::Camera::UpdateCameraGeometry() {
    m_AlignmentVector = m_CameraLookAt.subtract(m_CameraPosition);
    m_AlignmentVector.normalize();


    m_ProjectionScreenU = m_AlignmentVector.crossProduct(m_CameraUp);
    m_ProjectionScreenU.normalize();
    m_ProjectionScreenV = m_ProjectionScreenU.crossProduct(m_AlignmentVector);
    m_ProjectionScreenV.normalize();
    m_ProjectionScreenCenter = m_CameraPosition.add(m_AlignmentVector.multiply(m_CameraLength));
    m_ProjectionScreenU = m_ProjectionScreenU.multiply(m_CameraHorzSize);
    m_ProjectionScreenV = m_ProjectionScreenV.multiply(m_CameraHorzSize / m_CameraAspectRatio);
}

bool EGRayTracer::Camera::GenerateRay(const float &proScreenX, const float &proScreenY, EGRayTracer::Ray &cameraRay) {
    vec3 screenWorldTemp = m_ProjectionScreenCenter.add(m_ProjectionScreenU.multiply(proScreenX));
    vec3 screenWorldCoordinate = screenWorldTemp.add(m_ProjectionScreenV.multiply(proScreenY));
    cameraRay.m_Point1 = m_CameraPosition;
    cameraRay.m_Point2 = screenWorldCoordinate;
    cameraRay.m_lab    = screenWorldCoordinate.subtract(m_CameraPosition);

    return true;
}