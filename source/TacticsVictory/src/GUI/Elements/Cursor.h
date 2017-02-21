#pragma once


enum TypeCursor
{
    TypeCursor_Normal,
    TypeCursor_Selected,
    TypeCursor_Left,
    TypeCursor_Up,
    TypeCursor_Right,
    TypeCursor_Down,
    TypeCursor_TopLeft,
    TypeCursor_TopRight,
    TypeCursor_DownLeft,
    TypeCursor_DownRight,
    TypeCursor_Busy,
    TypeCursor_Size
};


class CursorShapes;


class CursorRTS : public Object
{
    URHO3D_OBJECT(CursorRTS, Object)
public:
    CursorRTS();

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

    CursorRTS& operator=(const CursorRTS&)
    {};

    bool selected = false;
    bool hidden = false;
    TypeCursor type = TypeCursor_Normal;
};