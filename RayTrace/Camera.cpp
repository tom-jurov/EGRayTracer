//
// Created by tomas on 15. 1. 2023.
//

#include "Camera.h"
#include "Ray.h"
#include "iostream"

EGRayTracer::Camera::Camera()
{
    m_CameraPosition = Eigen::Vector3d(0.0, -10.0, 0.0);
    m_CameraLookAt = Eigen::Vector3d(0.0, 0.0, 0.0);
    m_CameraUp = Eigen::Vector3d(0.0, 0.0, 1.0);
    m_CameraLength = 1.0;
    m_CameraHorzSize = 1.0;
    m_CameraAspectRatio = 1.0;
}

void EGRayTracer::Camera::SetPosition(const Eigen::Vector3d &newPosition) {
    m_CameraPosition = newPosition;
}

void EGRayTracer::Camera::SetLookAt(const Eigen::Vector3d &newLookAt) {
    m_CameraLookAt = newLookAt;
}

void EGRayTracer::Camera::SetUp(const Eigen::Vector3d &upVector) {
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

const Eigen::Vector3d EGRayTracer::Camera::GetPosition() const {
    return m_CameraPosition;
}

const Eigen::Vector3d EGRayTracer::Camera::GetLookAt() const {
    return m_CameraLookAt;
}

const Eigen::Vector3d EGRayTracer::Camera::GetUp() const {
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

const Eigen::Vector3d EGRayTracer::Camera::GetU() const {
    return m_ProjectionScreenU;
}

const Eigen::Vector3d EGRayTracer::Camera::GetV() const {
    return m_ProjectionScreenV;
}

const Eigen::Vector3d EGRayTracer::Camera::GetScreenCenter() const {
    return m_ProjectionScreenCenter;
}

void EGRayTracer::Camera::UpdateCameraGeometry() {
    m_AlignmentVector = m_CameraLookAt - m_CameraPosition;
    m_AlignmentVector.normalize();


    m_ProjectionScreenU = m_AlignmentVector.cross(m_CameraUp);
    m_ProjectionScreenU.normalize();
    m_ProjectionScreenV = m_ProjectionScreenU.cross(m_AlignmentVector);
    m_ProjectionScreenV.normalize();
    m_ProjectionScreenCenter = m_CameraPosition + m_AlignmentVector * m_CameraLength;
    m_ProjectionScreenU = m_ProjectionScreenU * m_CameraHorzSize;
    m_ProjectionScreenV = m_ProjectionScreenV * (m_CameraHorzSize / m_CameraAspectRatio);
}

bool EGRayTracer::Camera::GenerateRay(const float &proScreenX, const float &proScreenY, EGRayTracer::Ray &cameraRay) {
    Eigen::Vector3d screenWorldTemp = m_ProjectionScreenCenter + m_ProjectionScreenU * proScreenX;
    Eigen::Vector3d screenWorldCoordinate = screenWorldTemp + m_ProjectionScreenV * proScreenY;
    cameraRay.m_Point1 = m_CameraPosition;
    cameraRay.m_Point2 = screenWorldCoordinate;
    cameraRay.m_lab    = screenWorldCoordinate - m_CameraPosition;

    return true;
}