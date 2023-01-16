//
// Created by tomas on 15. 1. 2023.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H
#include <vector>
#include <SDL2/SDL.h>
#include "Image.h"
#include "Camera.h"
#include "ObjectSphere.h"

namespace EGRayTracer
{
    class Scene {
    public:
        Scene();

        bool Render(Image &outputImage);
    private:
        EGRayTracer::Camera m_Camera;

        EGRayTracer::ObjectSphere m_TestSphere;
    };
}


#endif //RAYTRACER_SCENE_H
