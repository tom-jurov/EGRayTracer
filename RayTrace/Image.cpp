//
// Created by tomas on 15. 1. 2023.
//

#include "Image.h"
#include <memory>
#include <iostream>
Image::Image()
{
    m_xSize = 0;
    m_ySize = 0;
    m_pTexture = nullptr;
}

Image::~Image()
{
    if (m_pTexture != NULL)
        SDL_DestroyTexture(m_pTexture);
}

void Image::Initialize(const int &xSize, const int &ySize, SDL_Renderer *pRenderer)
{
    m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

    m_xSize = xSize;
    m_ySize = ySize;

    m_pRenderer = pRenderer;
    InitTexture();
}

void Image::SetPixel(const int &x, const int &y, const double &red, const double &green, const double &blue)
{
    m_rChannel[x][y] = red;
    m_gChannel[x][y] = green;
    m_bChannel[x][y] = blue;
}

const int Image::GetXSize() const
{
    return m_xSize;
}

const int Image::GetYSize() const
{
    return m_ySize;
}

void Image::Display()
{
    ComputeMaxValues();
    auto tempPixels = std::make_unique<Uint32[]>(m_xSize * m_ySize);

    memset(tempPixels.get(), 0, m_xSize * m_ySize * sizeof(Uint32));

    for(int y=0; y<m_ySize; ++y){
        for(int x=0; x<m_xSize; ++x){
            tempPixels[(y*m_xSize)+x] = ConvertColor(m_rChannel[x][y],m_gChannel[x][y],m_bChannel[x][y]);

        }
    }

    SDL_UpdateTexture(m_pTexture, nullptr, tempPixels.get(), m_xSize * sizeof(Uint32));
    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_xSize;
    srcRect.h = m_ySize;
    bounds = srcRect;
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);

}

void Image::InitTexture()
{
    Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    if(m_pTexture != nullptr)
    {
        SDL_DestroyTexture(m_pTexture);
    }
    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

Uint32 Image::ConvertColor(const double &red, const double &green, const double &blue)
{
    unsigned char r = static_cast<unsigned char>((red / m_overallMax) * 255.0);
    unsigned char g = static_cast<unsigned char>((green / m_overallMax) * 255.0);
    unsigned char b = static_cast<unsigned char>((blue / m_overallMax) * 255.0);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 pixelColor = (r<<24) | (g<<16) | (b<<8) | 255;
#else
    Uint32 pixelColor = (255<<24) | (b<<16) | (g<<8) | r;
#endif

    return pixelColor;
}

void Image::ComputeMaxValues()
{
    m_maxRed = 0.0;
    m_maxGreen = 0.0;
    m_maxBlue = 0.0;
    m_overallMax = 0.0;
    for (int y = 0; y < m_ySize; y++)
    {
        for (int x = 0; x < m_xSize; x++)
        {
            double redValue = m_rChannel[x][y];
            double greenValue = m_gChannel[x][y];
            double blueValue = m_bChannel[x][y];

            if (redValue > m_maxRed)
                m_maxRed = redValue;
            if (greenValue > m_maxGreen)
                m_maxGreen = greenValue;
            if (blueValue > m_maxBlue)
                m_maxBlue = blueValue;

            if (m_maxRed > m_overallMax)
                m_overallMax = m_maxRed;
            if (m_maxGreen > m_overallMax)
                m_overallMax = m_maxGreen;
            if (m_maxBlue > m_overallMax)
                m_overallMax = m_maxBlue;
        }
    }
}