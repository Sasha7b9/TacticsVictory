#pragma once


class tvCursorShapes : public Object
{
    OBJECT(tvCursorShapes);
public:
    tvCursorShapes() : Object(gContext)
    {};
    SharedPtr<tvImage> GetShape(TypeCursor type, int numFrame);

private:

    void CreateNormal(int numFrame);
    void CreateSelected(int numFrame);
    void CreateLeft(int numFrame);
    void CreateUp(int numFrame);
    void CreateRight(int numFrame);
    void CreateDown(int numFrame);
    void CreateTopLeft(int numFrame);
    void CreateTopRight(int numFrame);
    void CreateDownLeft(int numFrame);
    void CreateDownRight(int numFrame);
    void CreateBusy(int numFrame);

    void FillGradient(tvImage *image, TypeCursor type, int numFrame);

public:
    struct StructShape
    {
        TypeCursor type;
        int numFrame;

        unsigned ToHash() const
        {
            return (uint)type + (numFrame << 4);
        }
    };

private:
    tvCursorShapes& operator=(const tvCursorShapes&)
    {};
    HashMap<StructShape, SharedPtr<tvImage> > map;

    int dimensionTriangleSmall = 50;
    int dimensionTriangleBig = 100;

    void CalcXYforNormal(int numFrame, int *x1, int *y1, int *x2, int *y2);
};