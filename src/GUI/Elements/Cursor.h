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


class lCursor : public Object
{
    OBJECT(lCursor)
public:
    lCursor();

    SharedPtr<Cursor> GetCursor();

    void Update(float dT);

    void SetNormal();
    void SetSelected();
    void Hide();
    void Show();
    TypeCursor GetType()    { return type; };

private:
    SharedPtr<Cursor> cursor;
    SharedPtr<lCursorShapes> shapes;

    lCursor& operator=(const lCursor&)
    {};

    bool selected = false;
    bool hidden = false;
    TypeCursor type = TypeCursor_Normal;
};