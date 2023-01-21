//
// Created by tomas on 21. 1. 2023.
//

#ifndef RAYTRACER_TF_H
#define RAYTRACER_TF_H
#include "eigen-3.4.0/Eigen/Dense"
#include "Ray.h"

namespace EGRayTracer {

    constexpr bool FWDTFORM = true;
    constexpr bool BCKTFORM = false;

    class TF {
    public:
        TF();
        ~TF();

        TF(const Eigen::Matrix4d &fwd, const Eigen::Matrix4d &bck);

        void SetTransform(const Eigen::Vector3d &translation,
                          const Eigen::Vector3d &rotation,
                          const Eigen::Vector3d &scale);

        Eigen::Matrix4d GetForward();
        Eigen::Matrix4d GetBackward();

        //Apply transform
        EGRayTracer::Ray Apply(const EGRayTracer::Ray &inputRay,const bool& dirFlag);
        Eigen::Vector3d Apply(const Eigen::Vector3d &inputVector,const bool& dirFLag);

        friend TF operator* (const EGRayTracer::TF &lhs, const EGRayTracer::TF &rhs);

        TF operator= (const TF &rhs);

        void PrintMatrix(const bool& dirFlag);

        static void PrintVector(const Eigen::Vector3d &inputVector);

    private:
        void Print(const Eigen::Matrix4d &matrix);

    private:
        Eigen::Matrix4d m_fwdtf;
        Eigen::Matrix4d m_bcktf;
    };
}


#endif //RAYTRACER_TF_H
