//
// Created by tomas on 15. 1. 2023.
//

#ifndef TOMAS_IMAGE_H
#define TOMAS_IMAGE_H
#include <string>
#include "eigen-3.4.0/Eigen/Dense"
#include <SDL2/SDL.h>

class Image {
public:
    // The constructor.
    Image();

    ~Image();

    void Initialize(const int &xSize, const int &ySize, SDL_Renderer *pRenderer);

    void SetPixel(const int &x, const int &y, const double &red, const double &green, const double &blue);

    void Display();

    const int GetXSize() const;
    const int GetYSize() const;
private:
    Uint32 ConvertColor(const double &red, const double &green, const double &blue);
    void InitTexture();

private:
    std::vector<std::vector<double>> m_rChannel;
    std::vector<std::vector<double>> m_gChannel;
    std::vector<std::vector<double>> m_bChannel;

    int m_xSize, m_ySize;

    SDL_Renderer *m_pRenderer;
    SDL_Texture *m_pTexture;

};


#endif //TOMAS_IMAGE_H
