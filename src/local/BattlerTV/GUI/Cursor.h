// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class ImageT;
class CursorShapes;


class CursorT : public Cursor
{
    URHO3D_OBJECT(CursorT, Cursor)

public:

    struct Type { enum E {
        Normal,
        Selected,
        Left,
        Up,
        Right,
        Down,
        TopLeft,
        TopRight,
        DownLeft,
        DownRight,
        Busy,
        Count
    }; };

    CursorT(Context *context);
    static void RegisterObject();
    SharedPtr<Cursor> GetCursor();
    virtual void Update(float dT);
    void SetNormal();
    void SetSelected();
    void Hide();
    void Show();
    Type::E GetType()    { return type; };
    Drawable* GetRaycastNode(Vector3 *hitPos = 0);

private:
    SharedPtr<Cursor> cursor;
    SharedPtr<CursorShapes> shapes;
    SharedPtr<Node> nodeSprite;
    SharedPtr<Sprite2D> sprite;
    SharedPtr<StaticSprite2D> staticSprite;
    bool selected = false;
    bool hidden = false;
    Type::E type = Type::Normal;
    bool overElementGUI = false;    // true means that the cursor is over the interfact element and must be selected

    void SetSelectedOverUnit();

    void HandleHoverBeginElementGUI(StringHash, VariantMap &);
    void HandleHoverEndElementGUI(StringHash, VariantMap &);
};


class CursorShapes : public Object
{
    URHO3D_OBJECT(CursorShapes, Object);
public:
    CursorShapes();
    SharedPtr<ImageT> GetShape(CursorT::Type::E type, int numFrame);

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
    void FillGradient(ImageT *image, CursorT::Type::E type, int numFrame);

public:
    struct StructShape
    {
        CursorT::Type::E type;
        int numFrame;

        unsigned ToHash() const
        {
            return static_cast<uint>(type) + (numFrame << 4);
        }
    };

private:
    HashMap<StructShape, SharedPtr<ImageT>> map;
    int dimensionTriangleSmall = 50;
    int dimensionTriangleBig = 100;

    void CalcXYforNormal(int numFrame, int *x1, int *y1, int *x2, int *y2);
};
