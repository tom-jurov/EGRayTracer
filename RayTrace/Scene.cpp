//
// Created by tomas on 15. 1. 2023.
//

#include "Scene.h"
EGRayTracer::Scene::Scene()
{

}

bool EGRayTracer::Scene::Render(Image &outputImage)
{
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    for (int y=0; y<ySize; y++){
        for (int x=0; x<xSize; x++){
            double red = (static_cast<double>(x)/static_cast<double>(xSize))*255.0;
            double green = (static_cast<double>(y)/static_cast<double>(ySize))*255.0;
            outputImage.SetPixel(x, y, red, green, 0.0);
        }
    }
    return true;
}