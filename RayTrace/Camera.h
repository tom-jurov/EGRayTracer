//
// Created by tomas on 15. 1. 2023.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "eigen-3.4.0/Eigen/Dense"
#include "Ray.h"
namespace EGRayTracer{
    class Camera {
    public:
        Camera();

        void SetPosition (const Eigen::Vector3d &newPosition);
        void SetLookAt (const Eigen::Vector3d &newLookAt);
        void SetUp (const Eigen::Vector3d &upVector);
        void SetLength (const double &newLength);
        void SetHorzSize (const double &newSize);
        void SetAspect (const double &newAspect);

        const Eigen::Vector3d GetPosition() const;
        const Eigen::Vector3d GetLookAt() const;
        const Eigen::Vector3d GetUp() const;
        const Eigen::Vector3d GetU() const;
        const Eigen::Vector3d GetV() const;
        const Eigen::Vector3d GetScreenCenter() const;
        const double GetLength() const;
        const double GetHorzSize() const;
        const double GetAspect() const;

        bool GenerateRay(const float &proScreenX, const float &proScreenY, EGRayTracer::Ray &cameraRay);

        void UpdateCameraGeometry();

    private:
        Eigen::Vector3d m_CameraPosition;
        Eigen::Vector3d m_CameraLookAt;
        Eigen::Vector3d m_CameraUp;
        double m_CameraLength;
        double m_CameraHorzSize;
        double m_CameraAspectRatio;

        Eigen::Vector3d m_AlignmentVector;
        Eigen::Vector3d m_ProjectionScreenU;
        Eigen::Vector3d m_ProjectionScreenV;
        Eigen::Vector3d m_ProjectionScreenCenter;

    };
}


#endif //RAYTRACER_CAMERA_H
