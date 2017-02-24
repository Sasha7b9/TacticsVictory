#pragma once
#include "Cursor.h"
#include "GUI/Elements/Image.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CursorShapes : public Object
{
    URHO3D_OBJECT(CursorShapes, Object);
public:
    CursorShapes();
    SharedPtr<ImageRTS> GetShape(TypeCursor type, int numFrame);

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
    void FillGradient(ImageRTS *image, TypeCursor type, int numFrame);

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
    HashMap<StructShape, SharedPtr<ImageRTS>> map;
    int dimensionTriangleSmall = 50;
    int dimensionTriangleBig = 100;

    void CalcXYforNormal(int numFrame, int *x1, int *y1, int *x2, int *y2);
};
