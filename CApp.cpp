//
// Created by tomas on 15. 1. 2023.
//
#include "CApp.h"
#include "./RayTrace/vec3.h"
#include <iostream>

CApp::CApp()
{
    isRunning = true;
    pWindow = nullptr;
    pRenderer = nullptr;
}

bool CApp::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }
    pWindow = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if(pWindow != nullptr)
    {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

        m_Image.Initialize(1280, 720, pRenderer);

        //Test
        EGRayTracer::Camera testCamera;
        testCamera.SetPosition(vec3(0.0,0.0,0.0));
        testCamera.SetLookAt(vec3(0.0, 2.0, 0.0));
        testCamera.SetUp(vec3(0.0,0.0,1.0));
        testCamera.SetLength(1.0);
        testCamera.SetHorzSize(1.0);
        testCamera.SetAspect(1.0);
        testCamera.UpdateCameraGeometry();

        // Get the screen center and U,V vec
        auto screenCenter = testCamera.GetScreenCenter();
        auto screenU = testCamera.GetU();
        auto screenV= testCamera.GetV();

        //Display in terminal
        std::cout << "Camera screen center: " << std::endl;
        PrintVector(screenCenter);
        std::cout << "Camer U vec" << std::endl;
        PrintVector(screenU);
        std::cout << "Camer V vec" << std::endl;
        PrintVector(screenV);
    }
    else
    {
        return false;
    }

    return true;
}

int CApp::OnExecute()
{
    SDL_Event event;

    if (OnInit() == false)
    {
        return -1;
    }
    while (isRunning) {
        while (SDL_PollEvent(&event) != 0) {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }
    return 0;
}

void CApp::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void CApp::OnLoop()
{

}

void CApp::OnRender()
{
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);
    //Render scene
    m_Scene.Render(m_Image);

    m_Image.Display();

    SDL_RenderPresent(pRenderer);
}

void CApp::OnExit()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = nullptr;
    SDL_Quit();
}

void CApp::PrintVector(const vec3 &inputVector)
{
    for(int i=0; i<inputVector.value.size(); i++){
        std::cout << inputVector.value.at(i) << std::endl;
    }
}