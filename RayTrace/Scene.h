//
// Created by tomas on 15. 1. 2023.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "Image.h"
#include "Camera.h"
#include "ObjectSphere.h"
#include "PointLight.hpp"


namespace EGRayTracer
{
    class Scene {
    public:
        Scene();

        bool Render(Image &outputImage);
    private:
        EGRayTracer::Camera m_Camera;

        //The list of objects
        std::vector<std::shared_ptr<EGRayTracer::ObjectBase>> m_ObjectList;
        
        std::vector<std::shared_ptr<EGRayTracer::LightBase>> m_LightList;
    
    };
}


#endif //RAYTRACER_SCENE_H
