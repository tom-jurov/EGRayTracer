//
// Created by tomas on 15. 1. 2023.
//

#include "Scene.h"
#include <iostream>
#include <chrono>

EGRayTracer::Scene::Scene()
{
    m_Camera.SetPosition(vec3(0.0, -10.0, 0.0));
    m_Camera.SetLookAt(vec3(0.0, 0.0, 0.0));
    m_Camera.SetUp(vec3(0.0, 0.0, 1.0));
    m_Camera.SetHorzSize(0.25);
    m_Camera.SetAspect(16.0/9.0);
    m_Camera.UpdateCameraGeometry();
}

bool EGRayTracer::Scene::Render(Image &outputImage)
{
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    EGRayTracer::Ray cameraRay;
    vec3 intPoint;
    vec3 localNormal;
    vec3 localColor;

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

            bool validInt = m_TestSphere.TestIntersections(cameraRay, intPoint, localNormal, localColor);

            if (validInt)
            {
                double dist = sqrt(vec3::dotProduct((intPoint.subtract(cameraRay.m_Point1)),intPoint.subtract(cameraRay.m_Point1)));
                if (dist > maxDist)
                    maxDist = dist;

                if (dist < minDist)
                    minDist = dist;

                outputImage.SetPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
            }
            else
            {
                outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
            }

        }
    }

    std::cout << "Minimum distance: " << minDist << std::endl;
    std::cout << "Maximum distance: " << maxDist << std::endl;
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = finish - start;
    std::cout << "Elapsed Time: " << elapsed.count()/1000 << " seconds" << std::endl;
    return true;
}