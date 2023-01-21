//
// Created by tomas on 15. 1. 2023.
//

#include "Scene.h"
#include <iostream>
#include <chrono>

EGRayTracer::Scene::Scene()
{
    m_Camera.SetPosition(Eigen::Vector3d(0.0, -10.0, 0.0));
    m_Camera.SetLookAt(Eigen::Vector3d(0.0, 0.0, 0.0));
    m_Camera.SetUp(Eigen::Vector3d(0.0, 0.0, 1.0));
    m_Camera.SetHorzSize(0.25);
    m_Camera.SetAspect(16.0/9.0);
    m_Camera.UpdateCameraGeometry();

    // Construct the test Sphere
    m_ObjectList.push_back(std::make_shared<EGRayTracer::ObjectSphere>  (EGRayTracer::ObjectSphere()));
    m_ObjectList.push_back(std::make_shared<EGRayTracer::ObjectSphere>  (EGRayTracer::ObjectSphere()));
    m_ObjectList.push_back(std::make_shared<EGRayTracer::ObjectSphere>  (EGRayTracer::ObjectSphere()));

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

    m_ObjectList[0]->m_BaseColor = Eigen::Vector3d(64.0, 128.0, 200.0);
    m_ObjectList[1]->m_BaseColor = Eigen::Vector3d(255.0, 128.0, 0.0);
    m_ObjectList[2]->m_BaseColor = Eigen::Vector3d(255.0, 200.0, 0.0);
    //Test light
    m_LightList.push_back(std::make_shared<EGRayTracer::PointLight> (EGRayTracer::PointLight()));
    m_LightList[0]->m_Location = Eigen::Vector3d(5.0, -10.0, -5.0);
    m_LightList[0]->m_Color = Eigen::Vector3d(255.0, 255.0, 255.0);
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
    
    for (int y=0; y<ySize; ++y){
        for (int x=0; x<xSize; ++x){
            double normX = (static_cast<double>(x) * xFact) - 1.0;
            double normY = (static_cast<double>(y) * yFact) - 1.0;

            m_Camera.GenerateRay(normX, normY, cameraRay);

            // Test for intersections
            for (auto &currentObject : m_ObjectList)
            {
                bool validInt = currentObject->TestIntersections(cameraRay, intPoint, localNormal, localColor);

                if (validInt)
                {
                    //Compute intensity of illumination
                    double intensity;
                    Eigen::Vector3d color;
                    bool validIllumination = false;
                    for (auto &currentLight : m_LightList)
                    {
                        validIllumination = currentLight->ComputeIllumination(intPoint, localNormal, m_ObjectList, currentObject, color, intensity);
                    }


                    double dist = (intPoint - cameraRay.m_Point1).norm();
                    if (dist > maxDist)
                        maxDist = dist;

                    if (dist < minDist)
                        minDist = dist;

                    //outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
                    if (validIllumination)
                    {
                        outputImage.SetPixel(x, y, localColor[0] * intensity,
                                                   localColor[1] * intensity,
                                                   localColor[2] * intensity);
                    }
                    else
                    {
                        //outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                    }
                }
                else
                {
                    //outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                }
            }

            //bool validInt = m_TestSphere.TestIntersections(cameraRay, intPoint, localNormal, localColor);


        }
    }

    std::cout << "Minimum distance: " << minDist << std::endl;
    std::cout << "Maximum distance: " << maxDist << std::endl;
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = finish - start;
    std::cout << "Elapsed Time: " << elapsed.count()/1000 << " seconds" << std::endl;
    return true;
}