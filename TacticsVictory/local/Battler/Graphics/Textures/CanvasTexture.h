// 2021/12/13 16:30:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    // Основной класс для программно рисуемой текстуры
    class CanvasTexture
    {
    public:

        enum class Type
        {
            Landscape,          // Используется для отрисовки ландшафта
            Select,             // Используется для выделения юнитов
            Count
        };

        CanvasTexture(int width, int height);
        virtual ~CanvasTexture();

        void BeginPaint(const ColorRGBA &colorBackground, const ColorRGBA &colorBrush);
        void EndPaint();

        void SetPixel(int x, int y);
        void DrawLine(int x1, int y1, int x2, int y2);
        void FillRegion(int x, int y, int width, int height);
        void DrawRectangle(int x1, int y1, int width, int height);
        void SetColorBrush(const ColorRGBA &color);
        uint *Pixel(int x, int y);

        Texture *GetTexture() const { return texture; };
    private:
        void SetColorBackground(const ColorRGBA &color);

        void Clear();

        TextureHeader *header;
        uint *data;
        Texture *texture;
        uint colorBackground;
        uint colorBrush;
    };
}
