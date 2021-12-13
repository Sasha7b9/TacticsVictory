// 2021/12/13 16:30:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    // Основной класс для программно рисуемой текстуры
    class CanvasTexture
    {
    public:
        static const int SIZE = 32;
        CanvasTexture();
        ~CanvasTexture();
        void SetColorBackground(const ColorRGBA &color);
        void SetColorBrush(const ColorRGBA &color);
        void Clear();
        void DrawLine(int x1, int y1, int x2, int y2);
        void FillRegion(int x, int y, int width, int height);
        void EndPaint();
        Texture *GetTexture() const { return texture; };
    private:
        uint *Pixel(int x, int y);
        Texture::Header *header;
        uint *data;
        Texture *texture;
        uint colorBackground;
        uint colorBrush;
    };
}
