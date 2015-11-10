#pragma once


class lImage : public Resource
{
    URHO3D_OBJECT(lImage, Resource);
public:
    lImage(int width, int height);

    SharedPtr<Image> GetUImage();

    void Clear(const Color &color);
    void SetPoint(int x, int y, const Color& color);
    void DrawLine(int x0, int y0, int x1, int y1, const Color &color);
    void DrawRectangle(int x, int y, int width, int height, const Color &color);
    void FillRectangle(int x, int y, int width, int height, const Color &color);
    void FillRegion(int x, int y, const Color &color);
    void FillRegion(int x, int y, const Color &color, const Color &colorBound);
    void CopyImage(int x, int y, lImage &image);      // Those points which have transparency more than 0.5 are copied
    int GetWidth() const;
    int GetHeight() const;
    void DrawPolyline(const Color &color, int numPoints, int *xy);
    void DrawCircle(float x, float y, float radius, const Color &color, float step = 1.0f);
    IntVector2 GetHotSpot() const;
    void SetHotSpot(int x, int y);

private:
    lImage& operator=(const lImage&)
    {};
    SharedPtr<Image> image;

    void Replace4Points(int x, int y, const Color &color);
    void Replace4PointsBound(int x, int y, const Color &color);
    
    Color replacedColor;
    Color boundingColor;
    IntVector2 hotSpot;
};