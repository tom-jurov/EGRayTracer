//
// Created by tomas on 15. 1. 2023.
//

#ifndef TOMAS_CAPP_H
#define TOMAS_CAPP_H

#include <SDL2/SDL.h>
#include "./RayTrace/Image.h"
#include "./RayTrace/Scene.h"
#include "./RayTrace/Camera.h"
class CApp
{
public:
    CApp();

    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event *event);
    void OnRender();
    void OnExit();

private:
    void PrintVector(const Eigen::Vector3d &inputVector);

    Image m_Image;
    EGRayTracer::Scene m_Scene;

    bool isRunning;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;

};

#endif //TOMAS_CAPP_H
