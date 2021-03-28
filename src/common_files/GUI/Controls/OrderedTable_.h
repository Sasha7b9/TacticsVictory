// 2021/03/28 21:56:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class HeaderTable : public WindowT
{
    URHO3D_OBJECT(HeaderTable, WindowT);

public:

    HeaderTable();
};


class LineTable : public WindowT
{
    URHO3D_OBJECT(LineTable, WindowT);

public:

    LineTable(HeaderTable *header);
};


class OrderedTable : public WindowT
{
    URHO3D_OBJECT(OrderedTable, WindowT);

public:

    OrderedTable(UIElement *ui_element, char *title);
};
