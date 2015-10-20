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


class vCursor : public Object
{
    OBJECT(vCursor)
public:
    vCursor();

    SharedPtr<Cursor> GetCursor();

    void Update(float dT);

    void SetNormal();
    void SetSelected();
    void Hide();
    void Show();
    TypeCursor GetType()    { return type; };

private:
    SharedPtr<Cursor> cursor;
    SharedPtr<vCursorShapes> shapes;

    vCursor& operator=(const vCursor&)
    {};

    bool selected = false;
    bool hidden = false;
    TypeCursor type = TypeCursor_Normal;
};