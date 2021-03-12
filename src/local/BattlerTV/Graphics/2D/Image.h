// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class ImageT : public Image
{
    URHO3D_OBJECT(ImageT, Image);
public:
    ImageT(Context *context);
    ~ImageT();
    static void RegisterObject();

    void SetSize(int width, int height);
    void SetPoint(int x, int y, const Color& color);
    void DrawLine(int x0, int y0, int x1, int y1, const Color &color);
    void DrawRectangle(int x, int y, int width, int height, const Color &color);
    void FillRectangle(int x, int y, int width, int height, const Color &color);
    void FillRegion(int x, int y, const Color &color);
    void FillRegion(int x, int y, const Color &color, const Color &colorBound);
    void CopyImage(int x, int y, const ImageT &image);      // Those points which have transparency more than 0.5 are copied
    void DrawPolyline(const Color &color, int numPoints, const int *xy);
    void DrawCircle(float x, float y, float radius, const Color &color, float step = 1.0f);
    IntVector2 GetHotSpot() const;
    void SetHotSpot(int x, int y);

private:

    Color replacedColor;
    Color boundingColor;
    IntVector2 hotSpot;

    void Replace4Points(int x, int y, const Color &color);
    void Replace4PointsBound(int x, int y, const Color &color);
};
