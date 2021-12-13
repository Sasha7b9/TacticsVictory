// 2021/12/13 16:29:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/CanvasTexture.h"
#include "Utils/Math.h"


using namespace Pi;


CanvasTexture::CanvasTexture()
{
    header = new Texture::Header();

    header->textureType = TextureType::Rectangle;
    header->textureFlags = TextureFlag::ExternalStorage | TextureFlag::Dynamic;
    header->colorSemantic = Texture::Semantic::Diffuse;
    header->alphaSemantic = Texture::Semantic::Diffuse;
    header->imageFormat = Texture::Format::RGBA8;
    header->imageWidth = SIZE;
    header->imageHeight = SIZE;
    header->imageDepth = 1;
    header->wrapMode[0] = Texture::Wrap::Repeat;
    header->wrapMode[1] = Texture::Wrap::Repeat;
    header->wrapMode[2] = Texture::Wrap::Repeat;
    header->mipmapCount = 1;
    header->mipmapDataOffset = 0;
    header->auxiliaryDataSize = 0;
    header->auxiliaryDataOffset = 0;

    data = new uint[(size_t)(SIZE * SIZE)];

    SetColorBackground({0.0f, 0.3f, 0.0f});
    Clear();

    texture = Texture::Get(header, data);
}


CanvasTexture::~CanvasTexture()
{
//    delete header;
//    delete []data;
//    texture->Release();
}


void CanvasTexture::SetColorBackground(const ColorRGBA &color)
{
    colorBackground = Mathem::ColorToUINT(color);
}


void CanvasTexture::SetColorBrush(const ColorRGBA &color)
{
    colorBrush = Mathem::ColorToUINT(color);
}


void CanvasTexture::Clear()
{
    int num_pixels = header->imageHeight * header->imageWidth - 1;

    for (int i = 0; i < num_pixels; i++)
    {
        data[i] = colorBackground;
    }
}


void CanvasTexture::DrawLine(int x1, int y1, int x2, int y2)
{
    if (y1 == y2)
    {
        Mathem::PutInOrder(x1, x2);

        for (int x = x1; x <= x2; x++)
        {
            uint *pixel = Pixel(x, y1);
            *pixel = colorBrush;
        }
    }
    else if (x1 == x2)
    {

    }
    else
    {

    }
}


void CanvasTexture::FillRegion(int x0, int y0, int width, int height)
{
    for (int y = y0; y < y0 + height; y++)
    {
        DrawLine(x0, y, x0 + width, y);
    }
}


void CanvasTexture::EndPaint()
{
    texture->UpdateRect({0, 0, header->imageWidth, header->imageHeight}, 0, data);
}


uint *CanvasTexture::Pixel(int x, int y)
{
    static int width = header->imageWidth;
    static int height = header->imageHeight;

    if (x < 0 || y < 0 || x >= width || y >= height)
    {
        static uint empty;

        return &empty;
    }

    return data + (y * width + x);
}
