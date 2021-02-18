/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "Core/_TMath.h"


TImage::TImage(Context *context) :
    Image(context)
{

}


TImage::~TImage()
{

}


void TImage::SetSize(int width, int height)
{
    Image::SetSize(width, height, 4); //-V112
}


void TImage::RegisterObject(Context* context)
{
    context->RegisterFactory<TImage>();
}


void TImage::SetPoint(int x, int y, const Color& color)
{
    if(x < GetWidth() && y < GetHeight())
    {
        SetPixel(static_cast<int>(x), static_cast<int>(y), color);
    }
}


void TImage::DrawLine(int x0, int y0, int x1, int y1, const Color &color)
{
    if((x1 - x0) == 0 && (y1 - y0) == 0)
    {
        x0++;
    }

    int x = x0;
    int y = y0;
    int dx = static_cast<int>(fabsf(static_cast<float>(x1 - x0)));
    int dy = static_cast<int>(fabsf(static_cast<float>(y1 - y0)));
    int s1 = Math::Sign(x1 - x0);
    int s2 = Math::Sign(y1 - y0);
    int temp;
    bool exchange;
    if(dy > dx)
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
    for(int i = 0; i <= dx; i++)
    {
        SetPoint(x, y, color);
        while(e >= 0)
        {
            if(exchange)
            {
                x += s1;
            }
            else
            {
                y += s2;
            }
            e -= 2 * dx;
        }
        if(exchange)
        {
            y += s2;
        }
        else
        {
            x += s1;
        }
        e += 2 * dy;
    }
}


void TImage::DrawRectangle(int x, int y, int width, int height, const Color &color)
{
    DrawLine(x, y, x + width, y, color);
    DrawLine(x + width, y, x + width, y + height, color);
    DrawLine(x, y + height, x + width, y + height, color);
    DrawLine(x, y, x, y + height, color);
}


void TImage::FillRectangle(int x0, int y0, int width, int height, const Color &color)
{
    for(int x = x0; x < x0 + width; x++)
    {
        DrawLine(x, y0, x, y0 + height, color);
    }
}


void TImage::FillRegion(int x, int y, const Color &color)
{
    replacedColor = GetPixel(x, y);

    SetPixel(x, y, color);

    Replace4Points(x, y, color);
}


void TImage::Replace4Points(int x, int y, const Color &color)
{
    if(y > 0)                       // upper pixel
    {
        if(GetPixel(x, y - 1) == replacedColor)
        {
            SetPixel(x, y - 1, color);
            Replace4Points(x, y - 1, color);
        }
    }
    if(x < GetWidth() - 1)   // rught pixel
    {
        if(GetPixel(x + 1, y) == replacedColor)
        {
            SetPixel(x + 1, y, color);
            Replace4Points(x + 1, y, color);
        }
    }
    if(y < GetHeight() - 1)
    {
        if(GetPixel(x, y + 1) == replacedColor)
        {
            SetPixel(x, y + 1, color);
            Replace4Points(x, y + 1, color);
        }
    }
    if(x > 0)
    {
        if(GetPixel(x - 1, y) == replacedColor)
        {
            SetPixel(x - 1, y, color);
            Replace4Points(x - 1, y, color);
        }
    }
}


void TImage::FillRegion(int x, int y, const Color &color, const Color &colorBound)
{
    UNUSED(x);
    UNUSED(y);
    UNUSED(color);
    UNUSED(colorBound);

//    boundingColor = colorBound;
//
//    if(GetPixel(x, y) != colorBound)
//    {
//        SetPixel(x, y, color);
//        Replace4PointsBound(x, y, color);
//    }
}


void TImage::CopyImage(int x0, int y0, const TImage &inImage)
{
    int xMin = x0;
    int xMax = xMin + inImage.GetWidth();
    if (xMax >= GetWidth())
    {
        xMax = GetWidth() - 1;
    }

    int yMin = y0;
    int yMax = yMin + inImage.GetHeight();
    if (yMax >= GetHeight())
    {
        yMax = GetHeight() - 1;
    }

    for (int x = x0; x < xMax; x++)
    {
        for (int y = y0; y < yMax; y++)
        {
            int curX = x - x0;
            int curY = y - y0;
            Color color = inImage.GetPixel(curX, curY);

            if (color.a_ > 0.5f)
            {
                SetPoint(x, y, color);
            }
        }
    }
}


#define FILL(a, b)                              \
    Color col = GetPixel(a, b);                 \
    if(col != boundingColor && col != color)    \
    {                                           \
        SetPixel(a, b, color);                  \
        Replace4PointsBound(a, b, color);       \
    }


void TImage::Replace4PointsBound(int x, int y, const Color &color)
{
    if(y > 0)
    {
        FILL(x, y - 1);
    }
    if(x < GetWidth() - 1)
    {
        FILL(x + 1, y);
    }
    if(y < GetHeight() - 1)
    {
        FILL(x, y + 1);
    }
    if(x > 0)
    {
        FILL(x - 1, y);
    }
}


void TImage::DrawPolyline(const Color &color, int numPoints, const int *xy)
{
    int numLines = numPoints - 1;

    for(int i = 0; i < numLines; i++)
    {
        DrawLine(xy[((uint64)i * 2)], xy[((uint64)i * 2 + 1)], xy[((uint64)i * 2 + 2)], xy[((uint64)i * 2 + 3)], color);
    }
}


void TImage::DrawCircle(float x, float y, float radius, const Color &color, float step)
{
    for (float angle = 0.0f; angle < 360.0f; angle += step) //-V1034
    {
        SetPoint((int)(x + Cos(angle) * radius + 0.5f), (int)(y + Sin(angle) * radius + 0.5f), color);
    }
}


IntVector2 TImage::GetHotSpot() const
{
    return hotSpot;
}


void TImage::SetHotSpot(int x, int y)
{
    hotSpot.x_ = x;
    hotSpot.y_ = y;
}
