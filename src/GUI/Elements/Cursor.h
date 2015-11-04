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


class Cursor : public Urho3D::Object
{
    OBJECT(Cursor)
public:
    Cursor();

    SharedPtr<UCursor> GetCursor();

    void Update(float dT);

    void SetNormal();
    void SetSelected();
    void Hide();
    void Show();
    TypeCursor GetType()    { return type; };
    UDrawable* GetRaycastNode(Vector3 *hitPos = 0);

private:
    SharedPtr<UCursor> cursor;
    SharedPtr<CursorShapes> shapes;

    Cursor& operator=(const Cursor&)
    {};

    bool selected = false;
    bool hidden = false;
    TypeCursor type = TypeCursor_Normal;
};