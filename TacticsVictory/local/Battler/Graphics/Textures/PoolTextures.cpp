// 2021/12/14 9:17:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/Textures/PoolTextures.h"
#include "Utils/Math_.h"


using namespace Pi;

namespace Pi
{
    namespace PoolTextures
    {
        static Array<CanvasTexture *> textures;
    
        CanvasTexture *CreateLandscape();
        CanvasTexture *CreateSelect();
    }
}


void PoolTextures::Construct()
{
    textures.SetElementCount((int)CanvasTexture::Type::Count);

    textures[(int)CanvasTexture::Type::Landscape] = CreateLandscape();
    textures[(int)CanvasTexture::Type::Select] = CreateSelect();
}


void PoolTextures::Destruct()
{
    for(int i = 0; i < textures.GetElementCount(); i++)
    {
        delete textures[i];
    }
}
 

Texture *PoolTextures::Get(CanvasTexture::Type type)
{
    return textures[(uint)type]->GetTexture();
}


CanvasTexture *PoolTextures::CreateLandscape()
{
    CanvasTexture *canvas = new CanvasTexture(32, 32);

    canvas->BeginPaint({{0.0f, 0.3f, 0.0f}, 1.0f}, {0.0f, 0.0f, 0.3f});
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            canvas->SetColorBrush({{Math::RandomFloat(0.0f, 0.15f),
                                    Math::RandomFloat(0.3f, 0.45f),
                                    Math::RandomFloat(0.0f, 0.15f)},  1.0f});
            canvas->SetPixel(i, j);
        }
    }
    canvas->SetColorBrush({0.0f, 0.3f, 0.1f});
    canvas->DrawRectangle(2, 2, 28, 28);
    canvas->EndPaint();

    CanvasTexture *result = new CanvasTexture(32, 32);

    result->BeginPaint(K::white, K::white);

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            int ix[4] = {0, 1, 0, -1};
            int iy[4] = {-1, 0, 1, 0};

            ColorRGBA full = M::UINTtoColor(*canvas->Pixel(i, j));

            if(i != 0 && i != 31 && j != 0 && j != 31)
            {
                for (int ii = 0; ii < 4; ii++)
                {
                    uint colorPixel = *canvas->Pixel(i + ix[ii], j + iy[ii]);
                    ColorRGBA color = M::UINTtoColor(colorPixel);
                    full += color;
                }

                full /= 5;
            }

            result->SetColorBrush(full);
            result->SetPixel(i, j);
        }
    }

    result->EndPaint();

    delete canvas;

    return result;
}


CanvasTexture *PoolTextures::CreateSelect()
{
    CanvasTexture *canvas = new CanvasTexture(32, 32);

    canvas->BeginPaint({{0.0f, 0.0f, 0.0f}, 0.0f}, {0.25, 0.25, 0.25});
    canvas->DrawRectangle(0, 0, 32, 32);
    canvas->DrawLine(0, 0, 31, 31);
    canvas->DrawLine(31, 0, 0, 31);
    canvas->EndPaint();

    return canvas;
}
