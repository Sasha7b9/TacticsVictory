#pragma once


namespace Pi
{

    class DrawingWidget : public Widget
    {
    
    public:
        DrawingWidget(const Vector2D &size);
        virtual ~DrawingWidget();
        
        void EndScene();
        void SetColorBackground(const ColorRGBA &color);
        void SetColorBrush(const ColorRGBA &color);
        void Clear();
        void DrawPoint(float x, float y);
        void DrawLine(float x0, float y0, float x1, float y1);
        void DrawLine(const Point2D &p0, const Point2D &p1);
        void DrawPolyLine(const Point2D *points, int numPoints);
        void DrawRectangle(const Point2D &leftTop, const Point2D &size);
        void DrawRectangle(float x, float y, float width, float height);
        void DrawCircle(float x, float y, float radius);
        void FillCircle(float x, float y, float radius);
        void FillRegion(float x, float y, const ColorRGBA &color);
        void FillRegion(float x, float y, float width, float height);
        void ClearAndFillRegion(const Point2D *points, int numPoints, const ColorRGBA &colorFill, const ColorRGBA &colorBorder, const Point2D &pointFill);
    
    private:
        Texture *texture = nullptr;
        Texture::Header *textureHeader = nullptr;
        uint *imageData = nullptr;
        ColorRGBA colorBackground;
        ColorRGBA colorBrush;
    
        uint GetColorUINT(int x, int y);
        bool FillFourPoints(float x, float y, uint colorUINT);
        bool SetPoint(float x, float y, uint colorUINT);
    };

}
