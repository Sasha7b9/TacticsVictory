// 2021/12/13 16:29:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/Textures/CanvasTexture.h"
#include "Utils/Math_.h"


using namespace Pi;


CanvasTexture::CanvasTexture(int width, int height)
{
    header = new TextureHeader();

    header->textureType = PiTypeTexture::_2D;
    header->textureFlags = PiFlagTexture::ExternalStorage | PiFlagTexture::Dynamic;
    header->colorSemantic = PiSemanticTexture::Diffuse;
    header->alphaSemantic = PiSemanticTexture::Diffuse;
    header->imageFormat = PiFormatTexture::RGBA8;
    header->imageWidth = width; //-V525
    header->imageHeight = height;
    header->imageDepth = 1;
    header->wrapMode[0] = PiWrapTexture::Repeat;
    header->wrapMode[1] = PiWrapTexture::Repeat;
    header->wrapMode[2] = PiWrapTexture::Repeat;
    header->mipmapCount = 1;
    header->mipmapDataOffset = 0;
    header->auxiliaryDataSize = 0;
    header->auxiliaryDataOffset = 0;

    data = new uint[(size_t)(width * height)]; //-V1028

    texture = Texture::Get(header, data);
}


CanvasTexture::~CanvasTexture()
{
    texture->Release();
    delete header;
    delete []data;
}


void CanvasTexture::SetColorBackground(const ColorRGBA &color)
{
    colorBackground = M::ColorToUINT(color);
}


void CanvasTexture::SetColorBrush(const ColorRGBA &color)
{
    colorBrush = M::ColorToUINT(color);
}


void CanvasTexture::Clear()
{
    int num_pixels = header->imageHeight * header->imageWidth;

    for (int i = 0; i < num_pixels; i++)
    {
        data[i] = colorBackground;
    }
}


void CanvasTexture::SetPixel(int x, int y)
{
    *Pixel(x, y) = colorBrush;
}


void CanvasTexture::DrawLine(int x1, int y1, int x2, int y2)
{
    if (y1 == y2)
    {
        M::PutInOrder(x1, x2);
        int width = x2 - x1 + 1;

        uint *pixel = Pixel(x1, y1);

        while (width--)
        {
            *pixel++ = colorBrush;
        }
    }
    else if (x1 == x2)
    {
        M::PutInOrder(y1, y2);
        int height = y2 - y1 + 1;

        uint *pixel = Pixel(x1, y1);

        while (height--)
        {
            *pixel = colorBrush;
            pixel += header->imageWidth; //-V102
        }
    }
    else
    {
        int x0 = x1;
        x1 = x2;
        int y0 = y1;
        y1 = y2;

        int x = x0;
        int y = y0;
        int dx = (int)Fabs((float)(x1 - x0));
        int dy = (int)Fabs((float)(y1 - y0));
        int s1 = (int)Fsgn((float)(x1 - x0));
        int s2 = (int)Fsgn((float)(y1 - y0));
        int temp = 0;
        bool exchange = false;
        if (dy > dx)
        {
            temp = dx;
            dx = dy;
            dy = temp;
            exchange = true;
        }
        else
        {
            exchange = false;
        }
        int e = 2 * dy - dx;
        for (int i = 0; i <= dx; i++)
        {
            SetPixel(x, y);
            while (e >= 0)
            {
                if (exchange)
                {
                    x += s1;
                }
                else
                {
                    y += s2;
                }
                e -= 2 * dx;
            }
            if (exchange)
            {
                y += s2;
            }
            else
            {
                x += s1;
            }
            e = e + 2 * dy;
        }
    }
}


void CanvasTexture::FillRegion(int x0, int y0, int width, int height)
{
    for (int y = y0; y < y0 + height - 1; y++)
    {
        DrawLine(x0, y, x0 + width - 1, y);
    }
}


void CanvasTexture::DrawRectangle(int x1, int y1, int width, int height)
{
    int x2 = x1 + width - 1;
    int y2 = y1 + height - 1;

    DrawLine(x1, y1, x2, y1);
    DrawLine(x1, y2, x2, y2);

    DrawLine(x1, y1, x1, y2);
    DrawLine(x2, y1, x2, y2);
}


void CanvasTexture::EndPaint()
{
    texture->UpdateRect({0, 0, header->imageWidth, header->imageHeight}, 0, data);
}


void CanvasTexture::BeginPaint(const ColorRGBA &background, const ColorRGBA &brush)
{
    SetColorBackground(background);
    SetColorBrush(brush);
    Clear();
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
