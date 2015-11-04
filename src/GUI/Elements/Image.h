#pragma once


class Image : public Resource
{
    OBJECT(Image);
public:
    Image(int width, int height);

    SharedPtr<UImage> GetUImage();

    void Clear(const UColor &color);
    void SetPoint(int x, int y, const UColor& color);
    void DrawLine(int x0, int y0, int x1, int y1, const UColor &color);
    void DrawRectangle(int x, int y, int width, int height, const UColor &color);
    void FillRectangle(int x, int y, int width, int height, const UColor &color);
    void FillRegion(int x, int y, const UColor &color);
    void FillRegion(int x, int y, const UColor &color, const UColor &colorBound);
    void CopyImage(int x, int y, Image &image);      // Those points which have transparency more than 0.5 are copied
    int GetWidth() const;
    int GetHeight() const;
    void DrawPolyline(const UColor &color, int numPoints, int *xy);
    void DrawCircle(float x, float y, float radius, const UColor &color, float step = 1.0f);
    IntVector2 GetHotSpot() const;
    void SetHotSpot(int x, int y);

private:
    Image& operator=(const Image&)
    {};
    SharedPtr<UImage> image;

    void Replace4Points(int x, int y, const UColor &color);
    void Replace4PointsBound(int x, int y, const UColor &color);
    
    UColor replacedColor;
    UColor boundingColor;
    IntVector2 hotSpot;
};