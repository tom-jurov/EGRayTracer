//
// Created by tomas on 21. 1. 2023.
//

#include "TF.h"
#include <iostream>
EGRayTracer::TF::TF()
{
    m_fwdtf.setIdentity();
    m_bcktf.setIdentity();

}
EGRayTracer::TF::~TF() {}

EGRayTracer::TF::TF(const Eigen::Matrix4d &fwd, const Eigen::Matrix4d &bck)
{
    if ((fwd.rows() != 4) || (fwd.cols() != 4) ||
        (bck.rows() != 4) || (bck.cols() != 4))
    {
        throw std::invalid_argument("Cannot construct TF, inputs are not all 4x4.");
    }

    m_fwdtf = fwd;
    m_bcktf = bck;
}

void EGRayTracer::TF::SetTransform(const Eigen::Vector3d &translation, const Eigen::Vector3d &rotation,
                                   const Eigen::Vector3d &scale)
{
    Eigen::Matrix4d translationMatrix;
    Eigen::Matrix4d rotationMatrixX;
    Eigen::Matrix4d rotationMatrixY;
    Eigen::Matrix4d rotationMatrixZ;
    Eigen::Matrix4d scaleMatrix;

    translationMatrix.setIdentity();
    rotationMatrixX.setIdentity();
    rotationMatrixY.setIdentity();
    rotationMatrixZ.setIdentity();
    scaleMatrix.setIdentity();

    // Populate
    translationMatrix(0,3) = translation(0);
    translationMatrix(1,3) = translation(1);
    translationMatrix(2,3) = translation(2);

    rotationMatrixZ(0,0) = cos(rotation(2));
    rotationMatrixZ(0,1) = sin(rotation(2));
    rotationMatrixZ(1,0) = -sin(rotation(2));
    rotationMatrixZ(1,1) = cos(rotation(2));

    rotationMatrixY(0,0) = cos(rotation(1));
    rotationMatrixY(0,2) = sin(rotation(1));
    rotationMatrixY(2,0) = -sin(rotation(1));
    rotationMatrixY(2,2) = cos(rotation(1));

    rotationMatrixZ(1,1) = cos(rotation(0));
    rotationMatrixZ(1,2) = -sin(rotation(0));
    rotationMatrixZ(2,1) = sin(rotation(0));
    rotationMatrixZ(2,2) = cos(rotation(0));

    scaleMatrix(0,0) = scale(0);
    scaleMatrix(1,1) = scale(1);
    scaleMatrix(2,2) = scale(2);

    m_fwdtf = translationMatrix * scaleMatrix * rotationMatrixX
                                              * rotationMatrixY
                                              * rotationMatrixZ;
    m_bcktf = m_fwdtf.inverse();
}

Eigen::Matrix4d EGRayTracer::TF::GetForward()
{
    return m_fwdtf;
}

Eigen::Matrix4d EGRayTracer::TF::GetBackward()
{
    return m_bcktf;
}

//Apply transform
EGRayTracer::Ray EGRayTracer::TF::Apply(const EGRayTracer::Ray &inputRay, const bool &dirFlag)
{
    EGRayTracer::Ray outputRay;
    outputRay.m_Point1 = this->Apply(inputRay.m_Point1, dirFlag);
    outputRay.m_Point2 = this->Apply(inputRay.m_Point2, dirFlag);
    outputRay.m_lab = outputRay.m_Point2 - outputRay.m_Point1;
    return outputRay;
}

Eigen::Vector3d EGRayTracer::TF::Apply(const Eigen::Vector3d &inputVector, const bool &dirFLag)
{
    Eigen::Vector4d tempVector(inputVector(0), inputVector(1), inputVector(2), 1.0);

    Eigen::Vector4d resultVector;
    if(dirFLag)
    {
        resultVector = m_fwdtf * tempVector;
    }
    else{
        resultVector = m_bcktf * tempVector;
    }

    return resultVector.head<3>();
}

namespace EGRayTracer
{
    EGRayTracer::TF operator* (const EGRayTracer::TF &lhs, const EGRayTracer::TF &rhs)
    {
        Eigen::Matrix4d fwdResult = lhs.m_fwdtf * rhs.m_fwdtf;

        Eigen::Matrix4d bckResult = fwdResult.inverse();

        EGRayTracer::TF finalResult(fwdResult, bckResult);

        return finalResult;
    }
}

EGRayTracer::TF EGRayTracer::TF::operator=(const TF &rhs)
{
    if (this != &rhs)
    {
        m_fwdtf = rhs.m_fwdtf;
        m_bcktf = rhs.m_bcktf;
    }

    return *this;
}

void EGRayTracer::TF::PrintMatrix(const bool &dirFlag)
{
    if (dirFlag)
    {
        Print(m_fwdtf);
    }
    else
    {
        Print(m_bcktf);
    }
}

void EGRayTracer::TF::Print(const Eigen::Matrix4d &matrix)
{
    int nRows = matrix.rows();
    int nCols = matrix.cols();
    for(int row=0; row<nRows; ++row){
        for (int col=0; col<nCols; ++col)
        {
            std::cout << matrix(row,col) << " ";
        }
        std::cout << std::endl;
    }
}

void EGRayTracer::TF::PrintVector(const Eigen::Vector3d &inputVector)
{
    int nRows = inputVector.size();
    for (int row=0; row<nRows; ++row){
        std::cout << inputVector(row) << std::endl;
    }
}