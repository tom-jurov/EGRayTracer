//
// Created by tomas on 15. 1. 2023.
//

#include "Scene.h"
#include <chrono>

EGRayTracer::Scene::Scene()
{
    m_Camera.SetPosition(Eigen::Vector3d(0.0, -10.0, -1.0));
    m_Camera.SetLookAt(Eigen::Vector3d(0.0, 0.0, 0.0));
    m_Camera.SetUp(Eigen::Vector3d(0.0, 0.0, 1.0));
    m_Camera.SetHorzSize(0.25);
    m_Camera.SetAspect(16.0/9.0);
    m_Camera.UpdateCameraGeometry();

    // Construct the test Sphere
    m_ObjectList.push_back(std::make_shared<EGRayTracer::ObjectSphere>  (EGRayTracer::ObjectSphere()));
    m_ObjectList.push_back(std::make_shared<EGRayTracer::ObjectSphere>  (EGRayTracer::ObjectSphere()));
    m_ObjectList.push_back(std::make_shared<EGRayTracer::ObjectSphere>  (EGRayTracer::ObjectSphere()));

    //Construct plane
    m_ObjectList.push_back(std::make_shared<EGRayTracer::ObjectPlane>    (EGRayTracer::ObjectPlane()));
    m_ObjectList[3]->m_BaseColor = Eigen::Vector3d(0.5, 0.5, 0.5);

    EGRayTracer::TF planeMatrix;
    planeMatrix.SetTransform( Eigen::Vector3d(0.0, 0.0, 0.75),
                              Eigen::Vector3d(0.0, 0.0, 0.0),
                              Eigen::Vector3d(4.0, 4.0, 1.0));

    m_ObjectList[3]->SetTransformMatrix(planeMatrix);

    EGRayTracer::TF testMatrix1, testMatrix2, testMatrix3;
    testMatrix1.SetTransform(Eigen::Vector3d(-1.5, 0.0, 0.0),
                             Eigen::Vector3d(0.0, 0.0, 0.0),
                             Eigen::Vector3d(0.5, 0.5, 0.75));
    testMatrix2.SetTransform(Eigen::Vector3d(0.0, 0.0, 0.0),
                             Eigen::Vector3d(0.0, 0.0, 0.0),
                             Eigen::Vector3d(0.75, 0.5, 0.5));
    testMatrix3.SetTransform(Eigen::Vector3d(1.5, 0.0, 0.0),
                             Eigen::Vector3d(0.0, 0.0, 0.0),
                             Eigen::Vector3d(0.75, 0.75, 0.75));

    m_ObjectList[0]->SetTransformMatrix(testMatrix1);
    m_ObjectList[1]->SetTransformMatrix(testMatrix2);
    m_ObjectList[2]->SetTransformMatrix(testMatrix3);

    m_ObjectList[0]->m_BaseColor = Eigen::Vector3d(0.25, 0.5, 0.8);
    m_ObjectList[1]->m_BaseColor = Eigen::Vector3d(1.0, 0.5, 0.0);
    m_ObjectList[2]->m_BaseColor = Eigen::Vector3d(1.0, 0.8, 0.0);
    //Test light
    m_LightList.push_back(std::make_shared<EGRayTracer::PointLight> (EGRayTracer::PointLight()));
    m_LightList[0]->m_Location = Eigen::Vector3d(5.0, -10.0, -5.0);
    m_LightList[0]->m_Color = Eigen::Vector3d(0.0, 0.0, 1.0);

    m_LightList.push_back(std::make_shared<EGRayTracer::PointLight> (EGRayTracer::PointLight()));
    m_LightList[1]->m_Location = Eigen::Vector3d(-5.0, -10.0, -5.0);
    m_LightList[1]->m_Color = Eigen::Vector3d(1.0, 0.0, 0.0);

    m_LightList.push_back(std::make_shared<EGRayTracer::PointLight> (EGRayTracer::PointLight()));
    m_LightList[2]->m_Location = Eigen::Vector3d(0.0, -10.0, -5.0);
    m_LightList[2]->m_Color = Eigen::Vector3d(0.0, 1.0, 0.0);
}

bool EGRayTracer::Scene::Render(Image &outputImage)
{
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    EGRayTracer::Ray cameraRay;
    Eigen::Vector3d intPoint;
    Eigen::Vector3d localNormal;
    Eigen::Vector3d localColor;

    double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
    double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
    double minDist = 1e6;
    double maxDist = 0.0;
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int y=0; y<ySize; ++y) {
        for (int x = 0; x < xSize; ++x) {
            double normX = (static_cast<double>(x) * xFact) - 1.0;
            double normY = (static_cast<double>(y) * yFact) - 1.0;

            m_Camera.GenerateRay(normX, normY, cameraRay);

            std::shared_ptr<EGRayTracer::ObjectBase> closestObject;
            Eigen::Vector3d closestIntPoint;
            Eigen::Vector3d closestLocalNormal;
            Eigen::Vector3d closestLocalColor;
            double minDist = 1e6;
            bool intersectionFound = false;

            // Test for intersections
            for (auto &currentObject: m_ObjectList) {
                bool validInt = currentObject->TestIntersections(cameraRay, intPoint, localNormal, localColor);

                if (validInt) {
                    intersectionFound = true;

                    double dist = (intPoint - cameraRay.m_Point1).norm();

                    if (dist < minDist) {
                        minDist = dist;
                        closestObject = currentObject;
                        closestIntPoint = intPoint;
                        closestLocalNormal = localNormal;
                        closestLocalColor = localColor;
                    }
                }
            }
            if (intersectionFound)
            {
                double intensity;
                Eigen::Vector3d color;
                double red = 0.0;
                double green = 0.0;
                double blue = 0.0;
                bool validIllum = false;
                bool illumFound = false;
                for(auto& currentLight : m_LightList)
                {
                    validIllum = currentLight->ComputeIllumination(closestIntPoint, closestLocalNormal, m_ObjectList,closestObject, color, intensity);

                    if(validIllum)
                    {
                        illumFound = true;
                        red += color(0)*intensity;
                        green += color(1)*intensity;
                        blue += color(2)*intensity;
                    }
                }
                if (illumFound)
                {
                    red *= closestLocalColor(0);
                    green *= closestLocalColor(1);
                    blue *= closestLocalColor(2);
                    outputImage.SetPixel(x, y, red, green, blue);
                }
            }
        }
    }

    return true;
}