//
// Created by tomas on 15. 1. 2023.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "vec3.h"
#include "Ray.h"
namespace EGRayTracer{
    class Camera {
    public:
        Camera();

        void SetPosition (const vec3 &newPosition);
        void SetLookAt (const vec3 &newLookAt);
        void SetUp (const vec3 &upVector);
        void SetLength (const double &newLength);
        void SetHorzSize (const double &newSize);
        void SetAspect (const double &newAspect);

        const vec3 GetPosition() const;
        const vec3 GetLookAt() const;
        const vec3 GetUp() const;
        const vec3 GetU() const;
        const vec3 GetV() const;
        const vec3 GetScreenCenter() const;
        const double GetLength() const;
        const double GetHorzSize() const;
        const double GetAspect() const;

        Ray GenerateRay(const float &proScreenX, const float &proScreenY);

        void UpdateCameraGeometry();

    private:
        vec3 m_CameraPosition;
        vec3 m_CameraLookAt;
        vec3 m_CameraUp;
        double m_CameraLength;
        double m_CameraHorzSize;
        double m_CameraAspectRatio;

        vec3 m_AlignmentVector;
        vec3 m_ProjectionScreenU;
        vec3 m_ProjectionScreenV;
        vec3 m_ProjectionScreenCenter;

    };
}


#endif //RAYTRACER_CAMERA_H
