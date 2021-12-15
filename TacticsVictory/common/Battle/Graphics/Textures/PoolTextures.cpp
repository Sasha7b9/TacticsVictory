// 2021/12/14 9:17:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/Textures/PoolTextures.h"


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
    canvas->DrawRectangle(2, 2, 28, 28);
    canvas->EndPaint();

    return canvas;
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
