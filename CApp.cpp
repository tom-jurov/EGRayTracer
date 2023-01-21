//
// Created by tomas on 15. 1. 2023.
//
#include "CApp.h"
#include "./RayTrace/eigen-3.4.0/Eigen/Dense"
#include <iostream>

CApp::CApp()
{
    isRunning = true;
    pWindow = nullptr;
    pRenderer = nullptr;
}

bool CApp::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error : " << SDL_GetError() << std::endl;
        return false;
    }
    pWindow = SDL_CreateWindow("RayTracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if(pWindow != nullptr)
    {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

        m_Image.Initialize(1280, 720, pRenderer);

        //Set the bg to white
        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        SDL_RenderClear(pRenderer);

        m_Scene.Render(m_Image);
        m_Image.Display();

        SDL_RenderPresent(pRenderer);
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

void CApp::OnRender()
{
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);
    //Render scene
    //m_Scene.Render(m_Image);

    //m_Image.Display();

    //SDL_RenderPresent(pRenderer);
}

void CApp::OnExit()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = nullptr;
    SDL_Quit();
}

void CApp::PrintVector(const Eigen::Vector3d &inputVector)
{
    for(int i=0; i<inputVector.size(); i++){
        std::cout << inputVector[i] << std::endl;
    }
}