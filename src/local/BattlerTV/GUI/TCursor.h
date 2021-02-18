// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class CursorShapes : public Object
{
    URHO3D_OBJECT(CursorShapes, Object);
public:
    CursorShapes();
    SharedPtr<TImage> GetShape(TypeCursor type, int numFrame);

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
    void FillGradient(TImage *image, TypeCursor type, int numFrame);

public:
    struct StructShape
    {
        TypeCursor type;
        int numFrame;

        unsigned ToHash() const
        {
            return static_cast<uint>(type) + (numFrame << 4);
        }
    };

private:
    HashMap<StructShape, SharedPtr<TImage>> map;
    int dimensionTriangleSmall = 50;
    int dimensionTriangleBig = 100;

    void CalcXYforNormal(int numFrame, int *x1, int *y1, int *x2, int *y2);
};



class CursorTV : public Object
{
    URHO3D_OBJECT(CursorTV, Object)
public:
    CursorTV();
    SharedPtr<Cursor> GetCursor();
    void Update(float dT);
    void SetNormal();
    void SetSelected();
    void Hide();
    void Show();
    TypeCursor GetType()    { return type; };
    Drawable* GetRaycastNode(Vector3 *hitPos = 0);

private:
    SharedPtr<Cursor> cursor;
    SharedPtr<CursorShapes> shapes;
    SharedPtr<Node> nodeSprite;
    SharedPtr<Sprite2D> sprite;
    SharedPtr<StaticSprite2D> staticSprite;
    bool selected = false;
    bool hidden = false;
    TypeCursor type = TypeCursor_Normal;
};
